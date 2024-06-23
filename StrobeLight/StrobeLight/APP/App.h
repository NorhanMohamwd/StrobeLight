/*
 * App.h
 *
 * Created: 4/7/2024 9:11:31 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef APP_H_
#define APP_H_

#include "Button.h"

#define secCounts 75
#define _850MS_COUNT 85

typedef enum{
	LEFT_NOW,
	RIGHT_NOW,
	BRAKE_NOW,
	BACK_NOW
	}app_subMode;
	
typedef enum{
	MODE_A,
	MODE_B,
	MODE_C
}app_sysMode;
	
	

/************* API ***********/

/*starts all the system's modules*/
void app_init(void);
/*processes input signals and turns on/off corresponding leds*/
void app_runnable(void);

void app_processSignals(union signalsUnion x,union signalsUnion y);

void app_modeA(void);

void app_modeB(void);

void app_modeC(void);

#endif /* APP_H_ */