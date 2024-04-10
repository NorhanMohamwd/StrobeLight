/*
 * Timer_program.c
 *
 * Created: 4/7/2024 8:56:11 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer_interface.h"
#include "StdMacros.h"
#include "StdTypes.h"

void Timer_init(const Timer_configType * Config_ptr){
	if (Config_ptr-> timer == TIMERA)
	{	timerName = TIMERA;
		Timer_disable(timerName);
		if (Config_ptr-> mode == NORMAL_MODE)
		{
			CLEAR_BIT(TCA0_SINGLE_CTRLB,SPLITM);	/*disable split mode*/
			TCA0_SINGLE_CTRLB = (TCA0_SINGLE_CTRLB & 0xF8) | (Config_ptr->mode);
		
			if(Config_ptr->prescaler < 8 &&  Config_ptr->prescaler > -1)
			{
				TCA0_SINGLE_CTRLA = (TCA0_SINGLE_CTRLA & 0xF1) | (Config_ptr->prescaler <<1);
				gl_prescaler = Config_ptr->prescaler;
			
				if (Config_ptr->direction == COUNTING_DOWN)	
				SET_BIT(TCA0_SINGLE_CTRLESET,DIR);
				else if (Config_ptr->direction == COUNTING_UP)
				SET_BIT(TCA0_SINGLE_CTRLECLR,DIR);
			
				//SET_BIT(TCA0_SINGLE_INTCTRL,OVF);
			}
		}
	}
	else if (Config_ptr->timer == TIMERB)
	{
		timerName = TIMERB;
		Timer_disable(timerName);
		if (Config_ptr-> mode == PERIDIC_INTERRUPT)
		{
			TCB0_CTRLB = ( TCB0_CTRLB & 0xF8) | (Config_ptr->mode);
			TCB0_CTRLA = ( TCB0_CTRLA & 0xF9) | (Config_ptr->prescaler <<1);
			SET_BIT(TCB0_INTCTRL,CAPT);
			TCB0_CCMP = REQUIRED_TICKS;
			Timer_enable(timerName);
		}
	}
}

static uint32_t calculatePrescaler (uint8_t g_prescaler){
	uint32_t prescaler;
	switch(g_prescaler){
		case 0:
		{
			prescaler = 1;
			break;
		}
		case 1:
		{
			prescaler = 2;
			break;
		}
		case 2:
		{
			prescaler = 4;
			break;
		}
		case 3:
		{
			prescaler = 8;
			break;
		}
		case 4:
		{
			prescaler = 16;
			break;
		}
		case 5:
		{
			prescaler = 64;
			break;
		}
		case 6:
		{
			prescaler = 256;
			break;
		}
		case 7:
		{
			prescaler = 1024;
			break;
		}
		default:
		return 0;
	}
	return prescaler;
}

void Timer_setDelay(uint32_t ms)
{
	/*add top value*/
	//TCA0_SINGLE_PER = ( ms *  CPU_FREQUENCY ) / (prescaler * 1000 * TIMER_MAX_TICKS);
	uint32_t prescaler =  calculatePrescaler(gl_prescaler);
	float timeTick_ms = ((float)prescaler / CPU_FREQUENCY) *1000 ;
	TCA0_SINGLE_PER = ms / timeTick_ms;
	
	/*restart counter*/
	SET_BIT(TCA0_SINGLE_CTRLESET,CMD1);
	SET_BIT(TCA0_SINGLE_CTRLECLR,CMD0);
}

void Timer_disable(Timer_timerType timerName)
{
	if (timerName == TIMERA)
	{
		CLEAR_BIT(TCA0_SINGLE_CTRLA,ENABLE);
	}
	else if (timerName == TIMERB)
	{
		CLEAR_BIT(TCB0_CTRLA,ENABLE);
	}
	
}
void Timer_enable(Timer_timerType timerName)
{
	if (timerName == TIMERA)
	{
		SET_BIT(TCA0_SINGLE_CTRLA,ENABLE);
	}
	else if (timerName == TIMERB)
	{
		SET_BIT(TCB0_CTRLA,ENABLE);
	}
	
}

bool_t Timer_getFlag(void)
{
	if (BIT_IS_SET(TCA0_SINGLE_INTFLAGS,OVF))
	{
		SET_BIT(TCA0_SINGLE_INTFLAGS,OVF);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void TimerB_setCallBack(void (*a_ptr)(void)){
	
	g_timerCallBackPtr=a_ptr;
}

void Timer_resetWDG(void){
	static uint8_t overFlows =0;
	overFlows++;
	if (overFlows==15)
	{
		overFlows=0;
		/*reset wdg*/
	}
}

ISR(TCB0_INT_vect){
	if(g_timerCallBackPtr != NULLPTR){
		(*g_timerCallBackPtr)();
	}
}

