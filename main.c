//Nguyen Ngo

// Driverlib includes
#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "spi.h"
#include "uart.h"
#include "interrupt.h"
#include "pinmux.h"
#include "utils.h"
#include "prcm.h"
#include "gpio.h"
#include "systick.h"
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

// Common interface include
#include "uart_if.h"

// Includes Adafruit
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "glcdfont.h"

// Includes test
#include "test.h"

//*****************************************************************************
//                          MACROS                                  
//*****************************************************************************

#define SPI_IF_BIT_RATE  100000
#define TR_BUFF_SIZE     100
//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
volatile int g_iCounter = 0;

#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif


volatile uint64_t bitsequence;
volatile int index;
char ReceivedChar;
char MessageTx[8];
char MessageRx[8];
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************

//*****************************************************************************
//                      LOCAL DEFINITION                                   
//*****************************************************************************

//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
static void
DisplayBanner()
{
    Report("\t\t****************************************************\n\r");
    Report("\t\t Part 2: Each pressed button will be displayed on the terminal\n\r");
    Report("\t\t Part 3: Pressing mute will send the text message \n\r");
    Report("\t\t****************************************************\n\r");
}

//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

void SPIInit(){
	// Reset SPI
	MAP_SPIReset(GSPI_BASE);

	//Enables the transmit and/or receive FIFOs.
	//Base address is GSPI_BASE, SPI_TX_FIFO || SPI_RX_FIFO are the FIFOs to be enabled
	MAP_SPIFIFOEnable(GSPI_BASE, SPI_TX_FIFO || SPI_RX_FIFO);

	// Configure SPI interface
	MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
					 SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
					 (SPI_SW_CTRL_CS |
					 SPI_4PIN_MODE |
					 SPI_TURBO_OFF |
					 SPI_CS_ACTIVELOW |
					 SPI_WL_8));

	// Enable SPI for communication
	MAP_SPIEnable(GSPI_BASE);
}

void sendMessage(char str[8]){
	//Disables UART interrupt while sending characters
	MAP_UARTIntDisable(UARTA1_BASE, UART_INT_RX | UART_INT_RT);
	int i;
	for(i = 0; i < 8; i++){
		//Sends the charactesr in the MessageTx array to the UART1 register
		MAP_UARTCharPut(UARTA1_BASE, str[i]);
		//Creates a small delay to ensure that the hardware functions correctly
		MAP_UtilsDelay(80000);
	}
	//Enables UART interrupts
	MAP_UARTIntEnable(UARTA1_BASE, UART_INT_RX | UART_INT_RT);
}

void receiveMessage(){
	int i;
	unsigned long ulStatus;
	//Get status of UART interrupt
	ulStatus = MAP_UARTIntStatus(UARTA1_BASE, true);
	UARTIntClear(UARTA1_BASE, ulStatus );
	//Create a small delay to ensure that the hardware functions correctly
	MAP_UtilsDelay(80000);
	for(i = 0; i < 8; i++){
		//Get the character from UART1 register
		MessageRx[i] = MAP_UARTCharGet(UARTA1_BASE);
		MAP_UtilsDelay(80000);
		//Draw the received char on the OLED
		drawChar(6*i, 64, MessageRx[i], WHITE, BLACK, 0x01);
		MAP_UtilsDelay(80000);
	}

	UARTIntEnable(UARTA1_BASE, UART_INT_RX|UART_INT_RT);
}

void UART1IntInit(){
	//configure Uart
	MAP_UARTConfigSetExpClk(UARTA1_BASE, MAP_PRCMPeripheralClockGet(PRCM_UARTA1),
	            UART_BAUD_RATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
	            UART_CONFIG_PAR_NONE));
	UARTEnable(UARTA1_BASE);
	// Disable FIFO so RX interrupt triggers on any character
	MAP_UARTFIFODisable(UARTA1_BASE);
	// Set interrupt handlers
	MAP_UARTIntRegister(UARTA1_BASE,receiveMessage);
	// Clear any interrupts that may have been present
	MAP_UARTIntClear(UARTA1_BASE, UART_INT_RX);
	// Enable interrupt
	MAP_UARTIntEnable(UARTA1_BASE, UART_INT_RX|UART_INT_RT);
	UARTFIFOEnable(UARTA1_BASE);

}

void GPIOIntHandler(){
	//THis function is called when a button on the remote is pressed
	//Disables the GPIO interrupt
	GPIOIntDisable(GPIOA1_BASE, 0x10);
	//Enables Systick
	SysTickEnable();
}

void GPIOIntInit(){
	//Enables GPIO interrupt
    MAP_IntEnable(INT_GPIOA1);
    //Register GPIO interrup with the function GIOPIntHandler()
    GPIOIntRegister(GPIOA1_BASE, GPIOIntHandler);
    //Enables the GPIO interrupt
    GPIOIntEnable(GPIOA1_BASE, 0x10);
    //Set type to falling edge
    GPIOIntTypeSet(GPIOA1_BASE, 0x10, GPIO_FALLING_EDGE);
}

void SystickIntHandler(){
	//Samples the voltage on pin 3
	if (GPIOPinRead(GPIOA1_BASE, 0x10)){
		//modify the bitsequence using logic AND
		//Use bitwise operation here to save memory. Another option is to use an aray
		bitsequence = bitsequence | (1LL << (64-index));
	}
	//Increments the next index of the bit in bitsequence to be modified
	index++;
	//Clear the GPIO interrupt
	GPIOIntClear(GPIOA1_BASE, 0x10);
	//Enables the GPIO interrupt
	GPIOIntEnable(GPIOA1_BASE, 0x10);
	if(index == 60)
	{
		//If 60 bits have been written, it's time to check what number on the remote the bit sequence reprensent.
		SysTickDisable();
		GPIOIntDisable(GPIOA1_BASE, 0x10);
	}
}

void SystickIntInit(){
	//Enables Systick
	SysTickIntEnable();
	//Registers the Systick interrupt handler
	SysTickIntRegister(SystickIntHandler);
	//Set the countdown time to about .1 ms
	SysTickPeriodSet(90000);
}

void main()
{
	//Set the bit sequence to 0. The Systick interrupt handler will modify the bits in this variable
    bitsequence = 0;
    //Index of the bits in the variable bitsequence to be modified
    index = 0;
    //Index of the Transmitting char array
    int MsgTxIndex = 0;
    //Initialize the value of previous char to 0
    char PreviousChar = 0;
    //Initilze the value of pevious number to 1. 1 is used be cause it does not represent any letters on the remote control.
    char PreviousNum = 1;
    //Initialize the transmitting arrays and receiving arrays to spaces
    memset(MessageTx, ' ', 8);
    memset(MessageRx, ' ', 8);
    // Initailizing the board
    BoardInit();
    // Muxing for Enabling UART_TX and UART_RX.
    PinMuxConfig();
    //Initialize GPIO interrupt
    GPIOIntInit();
    //Initialize Systick interrupt
    SystickIntInit();
    //Initialize Uart interrupt
    UART1IntInit();
    //Initialize SPI
    SPIInit();
    //Initalize Adafruit
    Adafruit_Init();
	//MAP_PRCMPeripheralReset(PRCM_GSPI);
    // Initialising the Terminal.
    InitTerm();
    // Clearing the Terminal.
    ClearTerm();
    DisplayBanner();

    //Sequence of 64 bit code represented in base 10
    uint64_t one = 127238051012453696;
    uint64_t two = 127238050878367040;
	uint64_t three = 127238051075237184;
	uint64_t four = 127238050811290944;
	uint64_t five = 127238051041715520;
	uint64_t six = 127238050907563328;
	uint64_t seven = 127238051089884480;
	uint64_t eight = 127238050777744704;
	uint64_t nine =127238051024946496;
	uint64_t zero = 127238050752931136;
	uint64_t delete1 =11385099857992613856;
	uint64_t delete2 =11529215046068469728;
	uint64_t mute =127238050886751552;

	fillScreen(BLACK);
    while(1){
    	//printf("index: %d\n", index);
        if(index == 60){
        	//printf("%" PRIu64 "\n", bitsequence);
        	if(bitsequence == one){
        		Report("One\n\r");
        	}else if(bitsequence == two){
        		if(PreviousNum == 2){
        			//If the same button is pressed, then modify the current character rather than moving on to the next index
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'a':
        			//If previous character is an a, then put b into the char array
        			MessageTx[MsgTxIndex] = 'b';
        			break;
        		case 'b':
        			//If previous character is an b, then put b into the char array
        			MessageTx[MsgTxIndex] = 'c';
        			break;
        		default:
        			//If previous character is anything other than a or b, then put a into the char array
        			MessageTx[MsgTxIndex] = 'a';
        			break;
        		}
        		//Set the previous num so that we will know what the previous number is in the next iteration of the while loop
        		PreviousNum = 2;
        		//Set the previous char so that we will know what the previous char is in the next iteration of the while loop
        		//Increments the index value
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Two\n\r");
        	}else if(bitsequence == three){
        		if(PreviousNum == 3){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'e':
        			MessageTx[MsgTxIndex] = 'f';
        			break;
        		case 'f':
        			MessageTx[MsgTxIndex] = 'd';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'e';
        			break;
        		}
        		PreviousNum = 3;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Three\n\r");
        	}else if(bitsequence == four){
        		if(PreviousNum == 4){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'g':
        			MessageTx[MsgTxIndex] = 'h';
        			break;
        		case 'h':
        			MessageTx[MsgTxIndex] = 'i';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'g';
        			break;
        		}
        		PreviousNum = 4;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Four\n\r");
        	}else if(bitsequence == five){
        		if(PreviousNum == 5){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'j':
        			MessageTx[MsgTxIndex] = 'k';
        			break;
        		case 'k':
        			MessageTx[MsgTxIndex] = 'l';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'j';
        			break;
        		}
        		PreviousNum = 5;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Five\n\r");
        	}else if(bitsequence == six){
        		if(PreviousNum == 6){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'm':
        			MessageTx[MsgTxIndex] = 'n';
        			break;
        		case 'n':
        			MessageTx[MsgTxIndex] = 'o';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'm';
        			break;
        		}
        		PreviousNum = 6;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Six\n\r");
        	}else if(bitsequence == seven){
        		printf("seven\n");
        		if(PreviousNum == 7){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'p':
        			MessageTx[MsgTxIndex] = 'q';
        			break;
        		case 'q':
        			MessageTx[MsgTxIndex] = 'r';
        			break;
        		case 'r':
        			MessageTx[MsgTxIndex] = 's';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'p';
        			break;
        		}
        		PreviousNum = 7;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Seven\n\r");
        	}else if(bitsequence == eight){
        		if(PreviousNum == 8){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 't':
        			MessageTx[MsgTxIndex] = 'u';
        			break;
        		case 'u':
        			MessageTx[MsgTxIndex] = 'v';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 't';
        			break;
        		}
        		PreviousNum = 8;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Eight\n\r");
        	}else if(bitsequence == nine){
        		if(PreviousNum == 9){
        			MsgTxIndex--;
        		}
        		switch(PreviousChar){
        		case 'w':
        			MessageTx[MsgTxIndex] = 'x';
        			break;
        		case 'x':
        			MessageTx[MsgTxIndex] = 'y';
        			break;
        		case 'y':
        			MessageTx[MsgTxIndex] = 'z';
        			break;
        		default:
        			MessageTx[MsgTxIndex] = 'w';
        			break;
        		}
        		PreviousNum = 9;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Nine\n\r");
        	}else if(bitsequence == zero){
        		MessageTx[MsgTxIndex] = ' ';
        		PreviousNum = 0;
        		PreviousChar = MessageTx[MsgTxIndex++];
        		Report("Zero\n\r");
        	}else if (bitsequence == delete1 || bitsequence == delete2){
        		MessageTx[MsgTxIndex--] = ' ';
        		MessageTx[MsgTxIndex] = ' ';
        		Report("Delete\n\r");
        	}else if (bitsequence == mute){
        		Report("Mute\n\r");
        		//if the button is mute, then we send the message array to the UART
        		sendMessage(MessageTx);
        	}

        	//draw the entered characters on the OLED
        	int i = 0;
        	for(i = 0; i < 8; i++){
        		drawChar(6*i, 0, MessageTx[i], WHITE, BLACK, 0x01);
        	}
    		index = 0;
    		//reset the bit sequence in order to capture the next bit ssequence
    		bitsequence = 0;
    		GPIOIntEnable(GPIOA1_BASE, 0x10);
        }
    }
}

