/*
 * Leds.c
 *
 * Created: 4/7/2024 9:04:36 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 

#include "Dio_interface.h"
#include "Led.h"

void led_on  ( led_t led )
{


	dio_writePin( led,HIGH);

}


void led_off ( led_t led )
{

	dio_writePin( led,LOW);

}