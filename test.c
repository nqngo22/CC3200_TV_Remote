//Nguyen Ngo
//Surinder Singh

#include "test.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"


void delay(unsigned long ulCount){
	//function that causes a delay
	int i;

  do{
    ulCount--;
		for (i=0; i< 65535; i++) ;
	}while(ulCount);
}

void drawAllFont(){
	//first font to be drawn is ascii 0
	unsigned char Font = 0;
	//clears the screen
	fillScreen(BLACK);
	//set initial coordinate to draw the first ascii character
	char x = 0;
	char y = 0;
	while(1){ // loop until all 256 characters are drawn
		//In case x and y run out of bounds
		if(x > 127 || y > 127){
			break;
		}
		//draw the charcter at x and y with the color white and size 1
		drawChar(x, y, Font, 0xFFFF, 0x0000, 1);
		//Change next position of pixel to be drawn.
		//Each font takes up 5x7 pixels
		x += 6;
		if( x > 120){ //go to the next line if the x coordinate is at the maximum pixel
			x = 0;//reset x to 0
			y += 8;//go to the next line
		}
		if(Font == 255) //if the font drawn is the last font then break out of the loop and ends the function
			break;
		else
			Font++; //set next font to be drawn
	}
}

void printHelloWorld(){
	//Fills screen with black
	fillScreen(BLACK);
	//Prints the string Hello world at the middle of the screen.
	//Color is white, size is 1
	drawChar(0, 64, 'H', 0xFFFF, 0x0000, 1);
	drawChar(6, 64, 'e', 0xFFFF, 0x0000, 1);
	drawChar(12, 64, 'l', 0xFFFF, 0x0000, 1);
	drawChar(18, 64, 'l', 0xFFFF, 0x0000, 1);
	drawChar(24, 64, 'o', 0xFFFF, 0x0000, 1);
	drawChar(30, 64, ' ', 0xFFFF, 0x0000, 1);
	drawChar(36, 64, 'w', 0xFFFF, 0x0000, 1);
	drawChar(42, 64, 'o', 0xFFFF, 0x0000, 1);
	drawChar(48, 64, 'r', 0xFFFF, 0x0000, 1);
	drawChar(54, 64, 'l', 0xFFFF, 0x0000, 1);
	drawChar(60, 64, 'd', 0xFFFF, 0x0000, 1);
}


void drawHorizontalLines(){
	//reset the screen to black
	fillScreen(BLACK);
	int y;
	for(y = 0; y < 16; y++){
		//draw 16 lines for each color so that the whole screen is filled with colored bars
		//Uses library function drawFastHLine()
	   drawFastHLine(0, y, width()-1, BLACK);
	   drawFastHLine(0, y + 16, width()-1, BLUE);
	   drawFastHLine(0, y + 32, width()-1, GREEN);
	   drawFastHLine(0, y + 48, width()-1, CYAN);
	   drawFastHLine(0, y + 64, width()-1, RED);
	   drawFastHLine(0, y + 80, width()-1, MAGENTA);
	   drawFastHLine(0, y + 96, width()-1, YELLOW);
	   drawFastHLine(0, y + 112, width()-1, WHITE);
	}

}

void drawVerticalLines(){
	//reset the screen to black
	fillScreen(BLACK);
	int x;
	for(x = 0; x < 16; x++){
		//draw 16 lines for each color so that the whole screen is filled with colored bars
		//Uses library function drawFastVLine()
		drawFastVLine(x, 0, height()-1, BLACK);
	   drawFastVLine(16+x, 0, height()-1, BLUE);
	   drawFastVLine(32+x, 0, height()-1, GREEN);
	   drawFastVLine(48+x, 0, height()-1, CYAN);
	   drawFastVLine(64+x, 0, height()-1, RED);
	   drawFastVLine(80+x, 0, height()-1, MAGENTA);
	   drawFastVLine(96+x, 0, height()-1, YELLOW);
	   drawFastVLine(112+x, 0, height()-1, WHITE);
	}
}
//these functions are given
void testlines(unsigned int color) {
	unsigned int x;
	unsigned int y;

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(0, 0, x, height()-1, color);
   }
	 delay(10);
   for (y=0; y < height()-1; y+=6) {
     drawLine(0, 0, width()-1, y, color);
   }
	 delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(width()-1, 0, x, height()-1, color);
   }
	 delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(width()-1, 0, 0, y, color);
   }
	 delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(0, height()-1, x, 0, color);
   }
	 delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(0, height()-1, width()-1, y, color);
   }
	 delay(100);

   fillScreen(BLACK);
   for (x=0; x < width()-1; x+=6) {
     drawLine(width()-1, height()-1, x, 0, color);
   }
	 delay(100);
   for (y=0; y < height()-1; y+=6) {
     drawLine(width()-1, height()-1, 0, y, color);
   }
	 delay(100);
}

void testfastlines(unsigned int color1, unsigned int color2) {
	unsigned int x;
	unsigned int y;

   fillScreen(BLACK);
   for (y=0; y < height()-1; y+=8) {
     drawFastHLine(0, y, width()-1, color1);
   }
	 delay(100);
   for (x=0; x < width()-1; x+=8) {
     drawFastVLine(x, 0, height()-1, color2);
   }
	 delay(100);
}

void testdrawrects(unsigned int color) {
	unsigned int x;

 fillScreen(BLACK);
 for (x=0; x < height()-1; x+=6) {
   drawRect((width()-1)/2 -x/2, (height()-1)/2 -x/2 , x, x, color);
	 delay(10);
 }
}

void testfillcircles(unsigned char radius, unsigned int color) {
	unsigned char x;
	unsigned char y;
	fillScreen(BLACK);
  for (x=radius; x < width()-1; x+=radius*2) {
    for (y=radius; y < height()-1; y+=radius*2) {
      fillCircle(x, y, radius, color);
			delay(10);
    }
  }
}

void testdrawcircles(unsigned char radius, unsigned int color) {
	unsigned char x;
	unsigned char y;
	fillScreen(BLACK);
  for (x=0; x < width()-1+radius; x+=radius*2) {
	for (y=0; y < height()-1+radius; y+=radius*2) {
	  drawCircle(x, y, radius, color);
			delay(10);
	}
  }
}

void testroundrects() {
	fillScreen(BLACK);
  int color = 100;

	int i;
  int x = 0;
  int y = 0;
  int w = width();
  int h = height();

  fillScreen(BLACK);

  for(i = 0 ; i <= 24; i++) {
    drawRoundRect(x, y, w, h, 5, color);
    x+=2;
    y+=3;
    w-=4;
    h-=6;
    color+=1100;
  }
}

void testtriangles() {
  int color = 0xF800;
  int t;
  int w = width()/2;
  int x = height()-1;
  int y = 0;
  int z = width()-1;

  fillScreen(BLACK);
  for(t = 0 ; t <= 15; t+=1) {
    drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
		delay(10);
  }
}
