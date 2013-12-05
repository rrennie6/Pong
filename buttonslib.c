#include "buttons.h"

int startPressed(){
	if(KEY_DOWN_NOW(BUTTON_START)){
		return 1;
	}
	return 0;
}

int selectPressed(){
	if(KEY_DOWN_NOW(BUTTON_SELECT)){
		return 1;
	}
	return 0;
}

int leftPressed(){
	if(KEY_DOWN_NOW(BUTTON_LEFT)){
		return 1;
	}
	return 0;
}

int rightPressed(){
	if(KEY_DOWN_NOW(BUTTON_RIGHT)){
		return 1;
	}
	return 0;
}
