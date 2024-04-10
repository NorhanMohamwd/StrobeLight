/*
 * Wdt.c
 *
 * Created: 4/10/2024 2:53:19 AM
 *  Author:  Nada Salloum - https://github.com/nadasalloum
 */ 

#include <avr/io.h>
#include"StdMacros.h"
#include "Wdt.h"
#include"wdt_config.h"

#define LOCK_PIN 7
#define SYNCBUSY_PIN 0

void wdt_init(void){
    /****put lock in private.h as pin 7 set it to zero to enable writing in ctla register **/
	CLEAR_BIT(WDT_STATUS,LOCK_PIN)  ;  
	
   /*******check if a previous write operation is in progress or not , the cMCU set that bit to zero after synchronization is finished*****/  
	while (GET_BIT(WDT_STATUS,SYNCBUSY_PIN));
	
	/***** enable wdt Period mode *****/
	WDT_CTRLA=WDT_PERIOD_1S; 
	
	
	/****** lock thepin status to prevent software from changing the wdt value ***/                     
	SET_BIT(WDT_STATUS,LOCK_PIN);
}


void wdt_reset(void){

	  /****put lock in private.h as pin 7 set it to zero to enable writing in ctla register **/
	  CLEAR_BIT(WDT_STATUS,LOCK_PIN)  ;
	  
	  /*******check if a previous write operation is in progress or not , the cMCU set that bit to zero after synchronization is finished*****/
	  while (GET_BIT(WDT_STATUS ,SYNCBUSY_PIN ));
	  
	  /***** enable wdt Period mode *****/
	  WDT_CTRLA=WDT_PERIOD_1S;
	  
	  
	  /****** lock thepin status to prevent software from changing the wdt value ***/
	  SET_BIT(WDT_STATUS,LOCK_PIN);
}