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

#define FIVE_SEC_COUNT		500



 /*** Typedefs ***/
 

typedef enum
{
	LEFT_IN=DIO_PIN0,
	RIGHT_IN=DIO_PIN0,
	BACK_IN=DIO_PIN1,
	BRAKE_IN=DIO_PIN2,
    BUTTON_1=DIO_PIN3,
    BUTTON_2=DIO_PIN4
            
 } button_t ;

typedef enum
{
	LEFT_IND=0,
	RIGHT_IND,
	BACK_IND,
	BRAKE_IND,
	BUTTON_1D,
	BUTTON_2D
	
}button_index;

typedef enum
{
	SHORT_PRESS,
	LONG_PRESS
	} button_pressTime;
	
typedef enum{
	NO_AUTO_MODE,
	AUTO_MODE_
	} button_autoMode;

union signalsUnion{
	volatile struct  {
		uint8_t  RIGHT		   : 1;		/*PORT B PIN0*/
		uint8_t  BACK		   : 1;		/*PORT B PIN1*/
		uint8_t  BRAKE         : 1;		/*PORT B PIN2*/
		uint8_t  BTN_1         : 1;     /*PORT B PIN3*/
		uint8_t  BTN_2         : 1;     /*PORT B PIN4*/
		uint8_t  LEFT          : 1;		/*PORT C PIN0*/
		button_pressTime  LEFT_PRESSED  : 1;
		button_pressTime  BRAKE_PRESSED : 1;
		button_autoMode   AUTO_MODE		: 1;
		uint8_t	arrOfPresses[6];
		uint8_t previous     ;
	} signal;
	uint8_t value ;
};

/************* API ***********/

/*initializes all buttons as input pull up*/
void button_init(void);
/*reads the buttons' values*/
void button_detectPress(void);

void button_setCallBack(void (*a_ptr)(union signalsUnion));


#endif /* BUTTON_H_ */