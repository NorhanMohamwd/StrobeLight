/*
 * Leds.h
 *
 * Created: 4/7/2024 9:04:52 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef LEDS_H_
#define LEDS_H_



#define LEFT_IN PINC0
#define RIGHT_IN PINB0
#define BACK_IN PINB1
#define BRAKE_IN PINB2

typedef enum
{
	LEFT_OUT   =PINC3  ,
	RIGHT_OUT  =PINC2  ,
	BACK_OUT   =PINC1  ,
	BRAKE_OUT  =PINB5  ,
	PIN_LED    =PINA2 ,
	POWER_OFF  =PINA1,
} LED_t ;



void LED_TurnOn  ( LED_t led );
void LED_TurnOff ( LED_t led );



#endif /* LEDS_H_ */