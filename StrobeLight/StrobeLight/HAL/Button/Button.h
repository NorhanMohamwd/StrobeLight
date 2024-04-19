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

 /*** Typedefs ***/
 
typedef enum
{
	LEFT_IN=DIO_PIN0,
	RIGHT_IN=DIO_PIN0,
	BACK_IN=DIO_PIN1,
	BRAKE_IN=DIO_PIN2
 } button_t ;


/************* API ***********/

/*initializes all buttons as input pull up*/
void button_init(void);
/*reads the buttons' values*/
union signalsUnion button_read(void);


#endif /* BUTTON_H_ */