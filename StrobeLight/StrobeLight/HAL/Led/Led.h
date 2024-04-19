/*
 * Leds.h
 *
 * Created: 4/7/2024 9:04:52 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef LEDS_H_
#define LEDS_H_
#include"Dio_interface.h"
#define TOTAL_LEDS 5   /*total number of leds */

#define LEDS_PORTA		PA
#define LEDS_PORTB      PB
#define LEDS_PORTC      PC

/*** configurable pins for all the leds ***/
typedef enum
{
	LEFT_OUT   =DIO_PIN3,
	RIGHT_OUT  =DIO_PIN2,
	BACK_OUT   =DIO_PIN1,
	BRAKE_OUT  =DIO_PIN5,
	PIN_LED    =DIO_PIN2,
	POWER_OFF  =DIO_PIN1
} led_t ;

/***** API *****/
void led_init(void);
void led_on  ( uint8_t port,led_t led );
void led_off (uint8_t port, led_t led );



#endif /* LEDS_H_ */