#include "DMA.h"
unsigned short *videoBuffer = (unsigned short *)0x6000000;

#define OFFSET(r, c, rowlen) ((r)*(rowlen) + (c))
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color){
	videoBuffer[OFFSET(r, c, 240)] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color){
	int row,col;
	for(row=0; row<height; row++)
	{
		for(col=0; col<width; col++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

/* drawimage3
* A function that will draw an arbitrary sized image
* onto the screen (with DMA).
* @param r row to draw the image
* @param c column to draw the image
* @param width width of the image
* @param height height of the image
* @param image Pointer to the first element of the image.
*/
void drawImage3(int r, int c, int width, int height, const u16* image){
	for(int Z = 0; Z<height; Z++){
		DMA[3].src = image + Z * width;
		DMA[3].dst = videoBuffer + (r+Z)*240+c;
		DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_ON;
	}
}

void clearScreen(){
	int BLACK = 0;
	DMA[3].src = &BLACK;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160)| DMA_SOURCE_FIXED | DMA_ON;
}

void colorScreen(int bgcolor){
	DMA[3].src = &bgcolor;
        DMA[3].dst = videoBuffer;
        DMA[3].cnt = (240*160) | DMA_SOURCE_FIXED | DMA_ON;
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}
