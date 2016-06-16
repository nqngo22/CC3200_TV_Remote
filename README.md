# CC3200_TV_Remote

This application uses the AT&T S10-S3 Remote Control to compose text messages using the multi-tap text entry <br />
system and sends text messages back and forth between two CC3200 LaunchPad boards over UART1. The application <br />
allows the user to input a text string via the IR and display the message on the local OLED. After the MUTE <br />
key is pressed, the message will be transmitted to the remote board and will be displayed on the remote OLED <br />
display. Incoming text messages are be displayed on the bottom half of the OLED. Messages under composition <br />
are displayed on the top half of the display.<br />
