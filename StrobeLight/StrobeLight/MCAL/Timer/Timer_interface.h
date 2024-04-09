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

//static volatile void (*g_timerCallBackPtr)(void)=NULLPTR;
uint8_t gl_prescaler;

#define CPU_FREQUENCY	20000000

#define SPLITM		    0 
#define DIR	            0
#define OVF	            0
#define ENABLE			0
#define CMD1			3
#define CMD0			2


typedef enum{
	NORMAL_MODE
}Timer_modeType;

typedef enum{
	DIV1,
	DIV2,
	DIV4,
	DIV8,
	DIV16,
	DIV64,
	DIV256,
	DIV1024
}Timer_prescaler;

typedef enum{
	COUNTING_UP,
	COUNTING_DOWN
}Timer_countDirection;



typedef struct {
	Timer_modeType mode;
	Timer_prescaler prescaler;
	Timer_countDirection direction;
}Timer_configType;

void Timer_init(const Timer_configType * Config_ptr);
void Timer_setDelay(uint32_t ms);
void Timer_disable(void);
void Timer_enable(void);
bool_t Timer_getFlag(void);
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