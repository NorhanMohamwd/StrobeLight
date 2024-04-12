/*
 * Leds.c
 *
 * Created: 4/7/2024 9:04:36 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 

#include "Dio_interface.h"
#include "Led.h"




void led_init(void)
{   // initialize led pins direction as output 
	dio_initPin(PIN_LED  , OUTPUT);
	dio_initPin(LEFT_OUT , OUTPUT);
	dio_initPin(RIGHT_OUT, OUTPUT);
	dio_initPin(BACK_OUT , OUTPUT);
	dio_initPin(BRAKE_OUT, OUTPUT);
	dio_initPin(POWER_OFF, OUTPUT);

	// to turn off all the leds at the begging (active low leds)     
	dio_writePin(LEFT_OUT  ,HIGH);
	dio_writePin(RIGHT_OUT ,HIGH);
	dio_writePin(BACK_OUT  ,HIGH);
	dio_writePin(BRAKE_OUT ,HIGH);
	dio_writePin(PIN_LED   ,HIGH);
	dio_writePin(POWER_OFF ,HIGH);
	
									 
}

void led_on  ( led_t led )
{

	dio_writePin( led,LOW);
	
}


void led_off ( led_t led )
{

	dio_writePin( led,HIGH);

}