/*
 * Timer_interface.h
 *
 * Created: 4/7/2024 8:57:37 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
#include "StdTypes.h"
#include "Timer_config.h"





typedef enum{
	TIMERA,
	TIMERB
}Timer_timerType;

typedef enum{
	NORMAL_MODE =0,
	PERIDIC_INTERRUPT =0
}Timer_modeType;


typedef enum{
	DIV1,
	DIV2,
	DIV4,
	DIV8,
	DIV16,
	DIV64,
	DIV256,
	DIV1024,
	CLKDIV1=0,	/*for TIMERB*/
	CLKDIV2=1,
	CLKTCA=3
	
}Timer_prescaler;

typedef enum{
	COUNTING_UP,
	COUNTING_DOWN
}Timer_countDirection;



typedef struct {
	Timer_timerType timer;
	Timer_modeType mode;
	Timer_prescaler prescaler;
	Timer_countDirection direction;
}Timer_configType;

Timer_timerType timerName;

void Timer_init(const Timer_configType * Config_ptr , uint32_t ms);
void Timer_setDelay(uint32_t ms);
void Timer_disable(Timer_timerType timerName);
void Timer_enable(Timer_timerType timerName);
bool_t Timer_getFlag(void);
void TimerB_setCallBack(void (*a_ptr)(void));
void Timer_resetWDG(void);
/*
typedef enum{
	NONE,
	UPDATE,
	RESTART,
	RESET
}Timer_counterCommands;
*/


/*
typedef enum{
	ErrorInMode,
	ErrorInPrescaler
}Timer_errorType;

typedef enum {
	SUCCESSFUL,
	UNSUCCESSFUL
}Timer_errorStatus;
*/



#endif /* TIMER_INTERFACE_H_ */