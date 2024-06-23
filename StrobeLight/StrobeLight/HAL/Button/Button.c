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
#include "Timer_interface.h"

static void (*g_buttonCallBackPtr)(union signalsUnion,union signalsUnion)=NULLPTR;

dio_pinInterrupt left_edge = FALLING;
dio_pinInterrupt brake_edge = FALLING;

union signalsUnion current;
union signalsUnion diff;
union signalsUnion result;
union signalsUnion previous;
 Timer_counters button_counter;

void button_init(void){
	dio_initPin(PC,LEFT_IN,INPULL);
	dio_initPin(PB,RIGHT_IN,INPULL);
	dio_initPin(PB,BACK_IN,INPULL);
	dio_initPin(PB,BRAKE_IN,INPULL);
    dio_initPin(PB,BUTTON_1,INPULL);
	dio_initPin(PB,BUTTON_2,INPULL);
	
	dio_enableInterruptTrigger(PC,LEFT_IN,BOTHEDGES);
	dio_enableInterruptTrigger(PB,RIGHT_IN,FALLING);
	dio_enableInterruptTrigger(PB,BACK_IN,FALLING);
	dio_enableInterruptTrigger(PB,BRAKE_IN,BOTHEDGES);
	dio_enableInterruptTrigger(PB,BUTTON_1,FALLING);
	dio_enableInterruptTrigger(PB,BUTTON_2,FALLING);
}

void button_detectPress(void){
	uint8_t currentButtonRead = (dio_readFlags(PB) & 0x1F ) | (dio_readFlags(PC)<<5) ; 
	//result.signal.previous= previousButtonStage;   // update the previous value before writing the new one 
	current.value = currentButtonRead;
	static  uint8_t previousButtonStage = 0x00;	 
  previous.value= previousButtonStage; // update the previous value before writing the new one 
	result.value = 0;
	uint8_t diffButtonStage = currentButtonRead ^ previousButtonStage;
	diff.value=diffButtonStage;
	if (current.signal.LEFT == HIGH )
	{	
		dio_resetFlags(PC,LEFT_IN);
		if (left_edge == FALLING)
		{
			timer_resetButtonCounter();
		//	dio_enableInterruptTrigger(PC,LEFT_IN,RISING);
			left_edge = RISING;
			current.signal.LEFT=LOW;
		}
		else if (left_edge== RISING)
		{
			button_counter = timer_getCounter();
			if (button_counter.buttons < FIVE_SEC_COUNT){
				result.signal.LEFT_PRESSED=SHORT_PRESS;
				result.signal.BRAKE_PRESSED=SHORT_PRESS;
			}
			else {
				result.signal.LEFT_PRESSED=LONG_PRESS;
				result.signal.BRAKE_PRESSED=SHORT_PRESS;
			}
		//	dio_enableInterruptTrigger(PC,LEFT_IN,FALLING);
			left_edge = FALLING;
			current.signal.LEFT=HIGH;
			result.signal.LEFT=HIGH;
			
		}
	}
	else if ((current.signal.RIGHT == HIGH)  && (diff.signal.RIGHT == HIGH ) )
	{
		dio_resetFlags(PB,RIGHT_IN);
		result.signal.RIGHT=HIGH;
		result.signal.LEFT_PRESSED=SHORT_PRESS;
		result.signal.BRAKE_PRESSED=SHORT_PRESS;
	}
	else if ((current.signal.BACK == HIGH ) && (diff.signal.BACK == HIGH ))
	{
		dio_resetFlags(PB,BACK_IN);
		result.signal.BACK=HIGH;
		result.signal.LEFT_PRESSED=SHORT_PRESS;
		result.signal.BRAKE_PRESSED=SHORT_PRESS;
	}
	else if (current.signal.BRAKE == HIGH )
	{
		dio_resetFlags(PB,BRAKE_IN);
		if (brake_edge == FALLING)
		{
			timer_resetButtonCounter();
	//		dio_enableInterruptTrigger(PB,BRAKE_IN,RISING);
			brake_edge = RISING;
			current.signal.BRAKE=LOW;
		}
		else if (brake_edge== RISING)
		{
			button_counter = timer_getCounter();
			if (button_counter.buttons < FIVE_SEC_COUNT){
				result.signal.BRAKE_PRESSED=SHORT_PRESS;
				result.signal.LEFT_PRESSED=SHORT_PRESS;
			}
			else {
				result.signal.BRAKE_PRESSED=LONG_PRESS;
				result.signal.LEFT_PRESSED=SHORT_PRESS;
			}
		//	dio_enableInterruptTrigger(PB,BRAKE_IN,FALLING);
			brake_edge = FALLING;
			current.signal.BRAKE=HIGH;
			result.signal.BRAKE=HIGH;
			
		}
	}
	else if ((current.signal.BTN_1 == HIGH )  && (diff.signal.BTN_1 == HIGH ))
	{
		dio_resetFlags(PB,BUTTON_1);
		result.signal.BTN_1=HIGH;
		result.signal.LEFT_PRESSED=SHORT_PRESS;
		result.signal.BRAKE_PRESSED=SHORT_PRESS;
	}
	else if ((current.signal.BTN_2 == HIGH ) && (diff.signal.BTN_2 == HIGH ))
	{
		dio_resetFlags(PB,BUTTON_2);
		result.signal.BTN_2=HIGH;
		result.signal.LEFT_PRESSED=SHORT_PRESS;
		result.signal.BRAKE_PRESSED=SHORT_PRESS;
	}
	previousButtonStage = 	current.value;
	g_buttonCallBackPtr(result,previous);
}

void button_setCallBack(void (*a_ptr)(union signalsUnion ,union signalsUnion)){
	
	g_buttonCallBackPtr=a_ptr;
}