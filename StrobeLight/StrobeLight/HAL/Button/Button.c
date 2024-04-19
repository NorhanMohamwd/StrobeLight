/*
 * Button.c
 *
 * Created: 4/7/2024 9:05:12 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include "Button.h"
#include "Dio_interface.h"
#include "Dio_config.h"
#include "Delay.h"



void button_init(void){
	dio_initPin(PC,LEFT_IN,INPULL);
	dio_initPin(PB,RIGHT_IN,INPULL);
	dio_initPin(PB,BACK_IN,INPULL);
	dio_initPin(PB,BRAKE_IN,INPULL);
}

union signalsUnion button_read(void){
	dio_pinVoltage_t pinValue = dio_readPin(PA,LEFT_IN);
	uint8_t currentButtonRead= ((dio_readPort(PB) & 0x07) | (pinValue<<3) ); /*puts the four readings into one variable*/
	static  uint8_t previousButtonStage = 0xFF;								/*initialize the previous state with HIGH*/
	uint8_t diffButtonStage = currentButtonRead ^ previousButtonStage;		/*to process only the changed value and discard old ones*/
	result.value = 0;
	current.value = currentButtonRead;
	diff.value = diffButtonStage;
	
	/*checks that it's a new value and that it's low*/
	if ((current.signal.LEFT == LOW ) && (diff.signal.LEFT == HIGH ) ){		
		result.signal.LEFT = HIGH;
	}
	else if ((current.signal.RIGHT == LOW ) && (diff.signal.RIGHT == HIGH )){
		result.signal.RIGHT = HIGH;
	}
	else if ((current.signal.BACK == LOW ) && (diff.signal.BACK == HIGH )){
		result.signal.BACK = HIGH;
	}
	else if ((current.signal.BRAKE == LOW ) && (diff.signal.BRAKE == HIGH )){
		result.signal.BRAKE = HIGH;
	}
			
	previousButtonStage = currentButtonRead;									/*save the current value in the previous one*/
	return result;
}

	