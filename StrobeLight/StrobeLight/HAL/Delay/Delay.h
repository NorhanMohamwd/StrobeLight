/*
 * Delay.h
 *
 * Created: 4/8/2024 1:27:17 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef DELAY_H_
#define DELAY_H_


#include "StdTypes.h"

/************* API ***********/

/*initializes delay module*/
void delay_init(void);
/*runs the delay with conigurable value in milliseconds*/
void delay_ms(uint32_t ms);


#endif /* DELAY_H_ */