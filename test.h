#ifndef TEST_H
#define TEST_H


// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define	RED             0xF800
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

void delay(unsigned long ulCount);
void drawAllFont();
void printHelloWorld();
void drawHorizontalLines();
void drawVerticalLines();
void testlines(unsigned int color);
void testfastlines(unsigned int color1, unsigned int color2);
void testdrawrects(unsigned int color);
void testfillcircles(unsigned char radius, unsigned int color);
void testdrawcircles(unsigned char radius, unsigned int color);
void testroundrects();
void testtriangles();

#endif
