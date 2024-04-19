/*
 * Leds.h
 *
 * Created: 4/7/2024 9:04:52 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef LEDS_H_
#define LEDS_H_
#include"Dio_interface.h"


typedef enum
{   PIN_LED  =0 ,
	POWER_OFF   ,
	BRAKE_OUT   ,
	LEFT_OUT    ,
	RIGHT_OUT   ,
	BACK_OUT    ,
	TOTAL_LEDS       /*total number of leds */
} led_t ;

typedef struct 
{
	
	dio_pinNumber Led_pin ;
	dio_portNumber led_port;
	
}led_Sruct;
/***** API *****/
void led_init(void);
void led_on  (led_t led );
void led_off (led_t led );



#endif /* LEDS_H_ */