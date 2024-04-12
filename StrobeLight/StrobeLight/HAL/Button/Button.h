/*
 * Button.h
 *
 * Created: 4/7/2024 9:05:24 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "StdTypes.h"
#include "Dio_interface.h"

union signalsUnion{
	volatile struct  {
		uint8_t  RIGHT     : 1;		/*PORT B PIN0*/
		uint8_t  BACK      : 1;		/*PORT B PIN1*/
		uint8_t  BRAKE     : 1;		/*PORT B PIN2*/
		uint8_t  LEFT      : 1;		/*PORT C PIN0*/
	} signal;
	uint8_t value ;
};

union signalsUnion current;
union signalsUnion diff;
union signalsUnion result;

typedef enum
{
	LEFT_IN=PINC0,
	RIGHT_IN=PINB0,
	BACK_IN=PINB1,
	BRAKE_IN=PINB2
 } button_t ;


void button_init(void);
union signalsUnion button_read(void);


#endif /* BUTTON_H_ */