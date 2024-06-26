/*
 * Interrupt.h
 *
 * Created: 4/10/2024 1:50:27 AM
 *  Author: Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "StdMacros.h"

#define INTERRUPT_PIN 7

/************* API ***********/

/*enables global interrupt*/
void enableGlobalInterrupt(void);
/*disables global interrupt*/
void disableGlobalInterrupt(void);


#endif /* INTERRUPT_H_ */