typedef unsigned short u16;
#include "buttons.h"
#include "pong.h"
#include "score.h"
#include "gameOver.h"
#include "winner.h"
extern u16 *videoBuffer;

#define REG_DISPCTL *(u16 *)0x4000000
#define RGB(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define BLACK 0
#define RED RGB(31, 0,0)
#define WHITE RGB(31,31,31)
#define LTGRAY RGB(20, 20, 20)

void setPixel(int r, int c, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawRect(int r, int c, int width, int height, u16 color);
int startPressed();
void clearScreen();
void colorScreen(u16 bgcolor);
void waitForVblank();
int selectPressed();
int rightPressed();
int leftPressed();
void drawBkwdDiag(int r, int c, int height, u16 color);

int main(void){
	
        REG_DISPCTL = MODE3 | BG2_ENABLE;

	int livesValue = 220;
	int scorePosition = 75;

	//player bar
	int barRow = 90;
	int const barHeight = 2;
	int barCol = 110;
	int oldBarRow = barRow;
	int oldBarCol = barCol;
	int const barCD = 2;
	int length = 20;
	int oldLength = length;

	//box  stuff
        int row = 80;
        int col = 120;
        int oldrow = row;
        int oldcol = col;
        int rd = 1;
        int cd = 1;
        int size = 5;
        int oldsize = size;

	//player info
	int playerLives = 3;
	int playerScore = 0;
	u16 bgcolor = BLACK;

	//opening image
	drawImage3(0,0,240,160,pong);
	while(!startPressed()==1);

	//setup game
	clearScreen();	
	drawImage3(120,0,240,40,score);
	drawRect(110,0,240,10,RED);
	
	//lives
	drawRect(135, 200, 5, 5, BLACK);
	drawRect(135, 210, 5, 5, BLACK);
	drawRect(135, 220, 5, 5, BLACK);

	//run game
	while(1){
		//player movement
		if(leftPressed()){
			barCol -= barCD;
                	if(barCol<0){
				barCol = 0;
			}
            	}
            	if(rightPressed()){
                	barCol += barCD;
			if(barCol > 239-length+1){
				barCol = 239-length+1;
			}
            	}

		//collision detection
		if((barCol<col) & (col<barCol+length) & (row == barRow-2)){
			playerScore++;
			if(playerScore>=10){
				break;
			}else if(playerScore>15){
				drawRect(135, scorePosition, 1, 10, BLACK);
			}else{
				drawRect(122, scorePosition, 1, 10, BLACK);
			}
			scorePosition += 2;
			if(scorePosition>=105){
				scorePosition = 75;
			}	
			rd = -rd;
		}

		//block movement
		row -= rd;
                col -= cd;
		if(row<0){
                	row = 0;
                	rd = -rd;
            	}
            	if(row>109-size+1){
                	playerLives--;
			if(playerLives<=0){
				break;	
			}
			drawRect(135, livesValue, 5, 5, WHITE);
			livesValue -= 10;
			row = 80;
			col = 120;
			rd = -rd;
			
            	}
            	if(col < 0){
                	col = 0;
                	cd = -cd;
            	}
            	if(col > 239-size+1)
            	{
                	col = 239-size+1;
                	cd = -cd;
            	}
            	waitForVblank();
		
		//player bar drawing
		drawRect(oldBarRow, oldBarCol, oldLength, barHeight, bgcolor);
		drawRect(barRow, barCol, length, barHeight, WHITE);
		oldBarRow = barRow;
		oldBarCol = barCol;
		oldLength = length;
				

		//box drawing
            	drawRect(oldrow, oldcol, oldsize, oldsize, bgcolor);
            	drawRect(row, col, size, size, RED);
            	oldrow = row;
            	oldcol = col;
            	oldsize = size;

		//reset
		if(selectPressed()==1){
			
			drawRect(0,0,240,160,BLACK);
			drawImage3(120,0,240,40,score);
			drawRect(110,0,240,10,RED);

			drawRect(135, 200, 5, 5, BLACK);
			drawRect(135, 210, 5, 5, BLACK);
			drawRect(135, 220, 5, 5, BLACK);

			barCol = 110;
			oldBarRow = barRow;
			oldBarCol = barCol;
			length = 20;
			oldLength = length;

			row = 80;
			col = 120;
			oldrow = row;
			oldcol = col;
			rd = 1;
			cd = 1;
			size = 5;
			oldsize = size;

			playerLives = 3;
			playerScore = 0;
			livesValue = 220;
			scorePosition = 75;
		}
	}

	//closing image
	if(playerLives <= 0){
		drawImage3(0,0,240,160, gameOver);
	}else{
		drawImage3(0,0,240,160, winner);
	}		
}
