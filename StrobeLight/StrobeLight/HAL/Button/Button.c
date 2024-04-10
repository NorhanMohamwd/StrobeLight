/*
 * Button.c
 *
 * Created: 4/7/2024 9:05:12 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include "Button.h"



void button_init(void){
	dio_initPin(LEFT_IN,INPULL);
	dio_initPin(RIGHT_IN,INPULL);
	dio_initPin(BACK_IN,INPULL);
	dio_initPin(BRAKE_IN,INPULL);
}

union signalsUnion button_read(void){

	uint8_t currentButtonRead= ((dio_readPort(PB) & 0xF8) | (dio_readPin(PINC0)<<3) );
	static  uint8_t previousButtonStage = 0xFF;
	uint8_t diffButtonStage = currentButtonRead ^ previousButtonStage;
	current.value=currentButtonRead;
	diff.value= diffButtonStage;
			
	if (current.signal.LEFT == LOW && diff.signal.LEFT == HIGH ){
		result.signal.LEFT = HIGH;
	}
	else if (current.signal.RIGHT == LOW && diff.signal.RIGHT == HIGH){
		result.signal.RIGHT = HIGH;
	}
	else if (current.signal.BACK == LOW && diff.signal.BACK == HIGH){
		result.signal.BACK = HIGH;
	}
	else if (current.signal.BRAKE == LOW && diff.signal.BRAKE == HIGH){
		result.signal.BRAKE = HIGH;
	}
			
	previousButtonStage = currentButtonRead;
	return result;
}

	