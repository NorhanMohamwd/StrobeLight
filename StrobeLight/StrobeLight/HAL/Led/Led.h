/*
 * Leds.h
 *
 * Created: 4/7/2024 9:04:52 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#define TOTAL_LEDS 5   /*total number of leds */

/*** configurable pins for all the leds ***/
typedef enum
{
	LEFT_OUT   =PINC3,
	RIGHT_OUT  =PINC2,
	BACK_OUT   =PINC1,
	BRAKE_OUT  =PINB5,
	PIN_LED    =PINA2,
	POWER_OFF  =PINA1,
} led_t ;

/***** API *****/
void led_init(void);
void led_on  ( led_t led );
void led_off ( led_t led );



#endif /* LEDS_H_ */