/*
 * Delay.c
 *
 * Created: 4/8/2024 1:27:01 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include "Delay.h"
#include "Timer_interface.h"

void delay_init(void)
{
	Timer_configType configType={TIMERA,NORMAL_MODE,DIV1024,COUNTING_UP};
	Timer_init(&configType , 250);
}

void delay_ms(uint32_t ms)
{	static uint8_t getFlag =0;
	timerName=TIMERA;
	Timer_setDelay(ms);
	Timer_enable(timerName);
	getFlag= Timer_getFlag();
	while(getFlag==FALSE){
		getFlag= Timer_getFlag();
	}
	getFlag=FALSE;
	
	Timer_disable(timerName);
}
