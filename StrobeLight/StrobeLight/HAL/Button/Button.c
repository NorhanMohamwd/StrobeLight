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
    dio_initPin(PB,BUTTON_1,INPULL);
	dio_initPin(PB,BUTTON_2,INPULL);
    
}

union signalsUnion button_read(void){
	dio_pinVoltage_t pinValue = dio_readPin(PC,LEFT_IN);
    uint8_t portValue = dio_readPort(PB);
	uint8_t currentButtonRead= (( portValue & 0x1F) | (pinValue<<5) ); /*puts the six readings into one variable*/
	static  uint8_t previousButtonStage = 0xFF;								/*initialize the previous state with HIGH*/
	uint8_t diffButtonStage = currentButtonRead ^ previousButtonStage;		/*to process only the changed value and discard old ones*/
	result.value = 0;
	current.value = currentButtonRead;
	diff.value = diffButtonStage;
	
	/*checks that it's a new value and that it's low*/
	if ((current.signal.LEFT == LOW ) && (diff.signal.LEFT == HIGH ) ){	
        delay_ms(50);
        if (dio_readPin(PC,LEFT_IN)==LOW){
        	result.signal.LEFT = HIGH;
        }
	}
	else if ((current.signal.RIGHT == LOW ) && (diff.signal.RIGHT == HIGH )){
        delay_ms(50);
        if (dio_readPin(PB,RIGHT_IN)==LOW){
        	result.signal.RIGHT = HIGH;
        }
	}
	else if ((current.signal.BACK == LOW ) && (diff.signal.BACK == HIGH )){
        delay_ms(50);
        if (dio_readPin(PB,BACK_IN)== LOW){
            result.signal.BACK = HIGH;
        }
	}
	else if ((current.signal.BRAKE == LOW ) && (diff.signal.BRAKE == HIGH )){
        delay_ms(50);
        if (dio_readPin(PB,BRAKE_IN)== LOW){
      		result.signal.BRAKE = HIGH;
        }
	}
    else if ((current.signal.BTN_1 == LOW ) && (diff.signal.BTN_1 == HIGH )){
        delay_ms(50);
        if (dio_readPin(PB,BUTTON_1)== LOW){
      		result.signal.BTN_1 = HIGH;
        }
	}
    else if ((current.signal.BTN_2 == LOW ) && (diff.signal.BTN_2 == HIGH )){
        delay_ms(50);
        if (dio_readPin(PB,BUTTON_2)== LOW){
      		result.signal.BTN_2 = HIGH;
        }
	}
			
	previousButtonStage = currentButtonRead;									/*save the current value in the previous one*/
	return result;
}

	