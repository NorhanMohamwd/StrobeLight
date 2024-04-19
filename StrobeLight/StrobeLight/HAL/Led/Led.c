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
	dio_initPin(PA,PIN_LED  , OUTPUT);
	dio_initPin(PA,POWER_OFF, OUTPUT);
	dio_initPin(PB,BRAKE_OUT, OUTPUT);
	dio_initPin(PC,LEFT_OUT , OUTPUT);
	dio_initPin(PC,RIGHT_OUT, OUTPUT);
	dio_initPin(PC,BACK_OUT , OUTPUT);

	// to turn off all the leds at the beginning (active low leds)     
// 	dio_writePin(PC,LEFT_OUT  ,HIGH);
// 	dio_writePin(PC,RIGHT_OUT ,HIGH);
// 	dio_writePin(PCBACK_OUT  ,HIGH);
// 	dio_writePin(PB,BRAKE_OUT ,HIGH);
// 	dio_writePin(PA,PIN_LED   ,HIGH);
// 	dio_writePin(PA,POWER_OFF ,HIGH);
	
									 
}

void led_on  (uint8_t port, led_t led )
{

	dio_writePin( port,led,LOW);
	
}


void led_off (uint8_t port, led_t led )
{

	dio_writePin(port, led,HIGH);

}