/*
 * Leds.c
 *
 * Created: 4/7/2024 9:04:36 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 

#include "Dio_interface.h"
#include "Led.h"
#include "StdTypes.h"


/* Configurable to change ports and pins for the leds */
led_Sruct led_arr[TOTAL_LEDS]={{DIO_PIN2,PA},      // pin led
                               {DIO_PIN1,PA},     //power off               
                               {DIO_PIN5,PB},    //brake out
						       {DIO_PIN3,PC},   // left out	   
						       {DIO_PIN2,PC},  //right out 	   
						       {DIO_PIN1,PC} //back out 	   
						      };
void led_init(void)       
{  
	
	 // initialize led pins direction as output 
	for(uint8_t i=0;i<TOTAL_LEDS;i++)
	   {
		
	     dio_initPin(led_arr[i].led_port,led_arr[i].Led_pin , OUTPUT);
	   }
	
	/* to turn off all the leds at the beginning (active HIGH leds)  
	   if the leds are active low write the voltage HIGH
	 */
		for(uint8_t i=0;i<TOTAL_LEDS;i++)
		{
			
		  dio_writePin(led_arr[i].led_port,led_arr[i].Led_pin ,LOW);
	    }   

	
									 
}


/* this logic is for the active high leds 
   if it's active low change the voltage in the 2 functions from LOW TO HIGH 
*/

void led_on  ( led_t led )
{
	dio_writePin(led_arr[led].led_port,led_arr[led].Led_pin ,HIGH);
	
}


void led_off ( led_t led )
{
	dio_writePin(led_arr[led].led_port,led_arr[led].Led_pin ,LOW);
}

void led_toggle ( led_t led )
{
	dio_togglePin(led_arr[led].led_port,led_arr[led].Led_pin);
}