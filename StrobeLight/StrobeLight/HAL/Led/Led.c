/*
 * Leds.c
 *
 * Created: 4/7/2024 9:04:36 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 

#include "Dio_interface.h"
#include "Led.h"

void LED_TurnOn  ( LED_t led ){

	
	DIO_WritePin( led,HIGH);
	
}


void LED_TurnOff ( LED_t led )
{
	
	DIO_WritePin( led,LOW);
	
}