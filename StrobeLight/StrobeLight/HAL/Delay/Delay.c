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
	Timer_init(&configType , 195);
}

void delay_ms(uint32_t ms)
{	static uint8_t getFlag =0;
	timerName=TIMERA;
	Timer_setDelay(ms);			/*pass the desired delay to the timer*/
	Timer_enable(timerName);
	getFlag= Timer_getFlag();
	
	/*wait till the flag is raised*/
	while(getFlag==FALSE){		
		getFlag= Timer_getFlag();
	}
	getFlag=FALSE;
	
	Timer_disable(timerName);
}
