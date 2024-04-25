/*
 * App.c
 *
 * Created: 4/7/2024 9:10:50 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include "App.h"
#include "StdTypes.h"
#include "Delay.h"
#include "Dio_interface.h"
#include "Button.h"
#include "Led.h"
#include "Timer_interface.h"
#include "Interrupt.h"
#include "Wdt.h"
#include "Eeprom.h"

uint8_t LEFT, RIGHT, BACK, BRAKE, STROBE_1 , STROBE_2 = LOW;
union signalsUnion buttonFlags;
Timer_counters updatedCounters;
app_subMode subMode = LEFT_NOW;
app_sysMode sysMode = MODE_A;
void app_init(void)
{   	
	wdt_init();	                    /*initializes the watchdog timer module*/
	button_init();			       /*initializes button module*/     
	led_init();					  /*initializes led module*/					         
	delay_init();				 /*initializes delay module*/
	Timer_configType configTimerB = {TIMERB,PERIDIC_INTERRUPT,CLKDIV1,COUNTING_DOWN};		/*create a configuration struct for TIMERB*/
	Timer_init(&configTimerB , 200);			/*initializes TIMERB*/
	TimerB_setCallBack(Timer_isrFunction);			/*sets the timer callback*/
	dio_setCallBack(button_detectPress);
	button_setCallBack(app_processSignals);
	enableGlobalInterrupt();					/*enables global interrupt*/
}

void app_runnable(void){
	
	//eeprom_read 
	static uint8_t first_enterA=0;
	static uint8_t first_enterB=0;
	static uint8_t first_enterC=0;
	readModeFromEeprom(&sysMode);
	// Change them to mode state and check for it's variable 
	// switch_case for modes 
	if (buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS){
		if (sysMode==MODE_A){
			sysMode=MODE_B;
			if(first_enterA==0){
				//write eeprom
				first_enterA=1;
				first_enterB=0;
				first_enterC=0;
				writeModeToEeprom(sysMode);
			}
		}
		else if (sysMode==MODE_B){
			sysMode=MODE_A;
				if(first_enterB==0){
					//write eeprom
					first_enterA=0;
					first_enterB=1;
					first_enterC=0;
				writeModeToEeprom(sysMode);
				}
		}
	}
	else if (buttonFlags.signal.LEFT_PRESSED == LONG_PRESS){
		sysMode=MODE_C;
			if(first_enterC==0){
				//write eeprom
				first_enterA=0;
				first_enterB=0;
				first_enterC=1;
			writeModeToEeprom(sysMode);
			}
	}
	switch(sysMode)
	{
		case MODE_A:
		{
			app_modeA();
			break;
		}
		case MODE_B:
		{
			app_modeB();
			break;
		}
		case MODE_C:
		{
			app_modeC();
			break;
		}
		default:
		break;
	}
	
   
}







void app_processSignals(union signalsUnion x){
	
	buttonFlags= x;
}

void app_modeA(void){
	
	 /*checks if the new value is LEFT*/
	 if (buttonFlags.signal.LEFT == HIGH){
		 RIGHT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 LEFT = !LEFT;
		 buttonFlags.signal.LEFT = LOW;
	 }
	 else if (buttonFlags.signal.RIGHT == HIGH){
		 LEFT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 RIGHT = !RIGHT;
		 buttonFlags.signal.RIGHT = LOW;
	 }
	 else if (buttonFlags.signal.BACK == HIGH){
		 LEFT = RIGHT = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 BACK = !BACK;
		 buttonFlags.signal.BACK = LOW;
	 }
	 else if (buttonFlags.signal.BRAKE == HIGH){
		 LEFT = RIGHT = BACK= STROBE_1=  STROBE_2 = 0;
		 BRAKE = !BRAKE;
		 buttonFlags.signal.BRAKE = LOW;
	 }
	 else if (buttonFlags.signal.BTN_1 == HIGH){
		 LEFT = RIGHT = BACK = BRAKE  = STROBE_2 = 0;
		 STROBE_1 = !STROBE_1;
		 buttonFlags.signal.BTN_1 = LOW;
	 }
	 else if (buttonFlags.signal.BTN_2 == HIGH){
		 LEFT = RIGHT = BACK = BRAKE = STROBE_1 = 0;
		 STROBE_2 = !STROBE_2;
		 buttonFlags.signal.BTN_2 = LOW;
	 }
	 
	 /*checks which signal is on to turn on/off corresponding led*/
	 
	 if (LEFT)
	 {
		 updatedCounters = timer_getCounter();
		 if (updatedCounters.leds >= secCounts){
			 led_toggle(LEFT_OUT);
			 led_off(RIGHT_OUT);
			 led_off(BACK_OUT);
			 led_off(BRAKE_OUT);
			 led_off(STROBE1_OUT);
			 led_off(STROBE2_OUT);
			 timer_resetLedCounter();
		 }
	 }
	 else if (RIGHT)
	 {
		 updatedCounters = timer_getCounter();
		 if (updatedCounters.leds >= secCounts){
			 led_off(LEFT_OUT);
			 led_toggle(RIGHT_OUT);
			 led_off(BACK_OUT);
			 led_off(BRAKE_OUT);
			 led_off(STROBE1_OUT);
			 led_off(STROBE2_OUT);
			 timer_resetLedCounter();
		 }
	 }
	 else if (BACK)
	 {
		 led_off(LEFT_OUT);
		 led_off(RIGHT_OUT);
		 led_on(BACK_OUT);
		 led_off(BRAKE_OUT);
		 led_off(STROBE1_OUT);
		 led_off(STROBE2_OUT);
	 }
	 else if (BRAKE)
	 {
		 led_off(LEFT_OUT);
		 led_off(RIGHT_OUT);
		 led_off(BACK_OUT);
		 led_on(BRAKE_OUT);
		 led_off(STROBE1_OUT);
		 led_off(STROBE2_OUT);
	 }
	 else if (STROBE_1)
	 {
		 led_off(LEFT_OUT);
		 led_off(RIGHT_OUT);
		 led_off(BACK_OUT);
		 led_off(BRAKE_OUT);
		 led_on(STROBE1_OUT);
		 led_off(STROBE2_OUT);
	 }
	 else if (STROBE_2)
	 {
		 led_off(LEFT_OUT);
		 led_off(RIGHT_OUT);
		 led_off(BACK_OUT);
		 led_off(BRAKE_OUT);
		 led_off(STROBE1_OUT);
		 led_on(STROBE2_OUT);
	 }
	 else
	 {
		 led_off(LEFT_OUT) ;
		 led_off(RIGHT_OUT);
		 led_off(BACK_OUT) ;
		 led_off(BRAKE_OUT);
		 led_off(STROBE1_OUT);
		 led_off(STROBE1_OUT);
		 led_on (POWER_OFF);
	 }	
}
void app_modeB(void)
{


	if (buttonFlags.signal.LEFT == HIGH)
	{
		RIGHT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		LEFT = !LEFT;
		buttonFlags.signal.LEFT = LOW;
	}
	else if (buttonFlags.signal.RIGHT == HIGH)
	{
		LEFT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		RIGHT = !RIGHT;
		buttonFlags.signal.RIGHT = LOW;
	}
	else if (buttonFlags.signal.BACK == HIGH)
	{
		LEFT = RIGHT = BRAKE = STROBE_1 =  STROBE_2 = 0;
		BACK = !BACK;
		buttonFlags.signal.BACK = LOW;
	}
	else if (buttonFlags.signal.BRAKE == HIGH)
	{
		LEFT = RIGHT = BACK= STROBE_1=  STROBE_2 = 0;
		BRAKE = !BRAKE;
		buttonFlags.signal.BRAKE = LOW;
	}
	else if (buttonFlags.signal.BTN_1 == HIGH)
	{
		LEFT = RIGHT = BACK = BRAKE  = STROBE_2 = 0;
		STROBE_1 = !STROBE_1;
		buttonFlags.signal.BTN_1 = LOW;
	}
	else if (buttonFlags.signal.BTN_2 == HIGH)
	{
		LEFT = RIGHT = BACK = BRAKE = STROBE_1 = 0;
		STROBE_2 = !STROBE_2;
		buttonFlags.signal.BTN_2 = LOW;
	}
	
	// check which signal is on/off 
	if (LEFT)
	{
		// check previous state was brake or not
		if((buttonFlags.signal.previous&BRAKE_MASK))
		{

			updatedCounters = timer_getCounter();
			if (updatedCounters.leds >= secCounts)
			{
				led_toggle(LEFT_OUT);
				led_on(RIGHT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
				timer_resetLedCounter();
			}
		}
		else
		{
			updatedCounters = timer_getCounter();
			if (updatedCounters.leds >= secCounts)
			{
				led_toggle(LEFT_OUT);
				led_off(RIGHT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
				timer_resetLedCounter();
			}

		}
	}
	else if (RIGHT)
	{
		// check previous state was brake or not
		if((buttonFlags.signal.previous&BRAKE_MASK))
		{
			updatedCounters = timer_getCounter();
			if (updatedCounters.leds >= secCounts)
			{
				led_on(LEFT_OUT);
				led_toggle(RIGHT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
				timer_resetLedCounter();
			}
		}
		else
		{
			updatedCounters = timer_getCounter();
			if (updatedCounters.leds >= secCounts)
			{
				led_off(LEFT_OUT);
				led_toggle(RIGHT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
				timer_resetLedCounter();
			}

		}
	}
	else if (BACK)
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_on(BACK_OUT);
		led_off(BRAKE_OUT);
		led_off(STROBE1_OUT);
		led_off(STROBE2_OUT);
	}
	else if (BRAKE)
	{
		led_on(LEFT_OUT);
		led_on(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
		led_off(STROBE1_OUT);
		led_off(STROBE2_OUT);
	}
	else if (STROBE_1)
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
		led_on(STROBE1_OUT);
		led_off(STROBE2_OUT);
	}
	else if (STROBE_2)
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
		led_off(STROBE1_OUT);
		led_on(STROBE2_OUT);
	}
	else
	{
		led_off(LEFT_OUT) ;
		led_off(RIGHT_OUT);
		led_off(BACK_OUT) ;
		led_off(BRAKE_OUT);
		led_off(STROBE1_OUT);
		led_off(STROBE1_OUT);
		led_on (POWER_OFF);
	}
}

void app_modeC(void){

	switch (subMode){
		case LEFT_NOW:
		{
			timer_resetLedCounter(); 
			updatedCounters= timer_getCounter();
			while (updatedCounters.leds < FIVE_SEC_COUNT)
			{
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds % _500MS_COUNT == 0){
					led_toggle(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_off(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
				}
			}
			timer_resetLedCounter();
			subMode = RIGHT_NOW;
			break;
		}
		case RIGHT_NOW:
		{
			updatedCounters= timer_getCounter();
			while (updatedCounters.leds < FIVE_SEC_COUNT)
			{
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds % _500MS_COUNT == 0){
					led_off(LEFT_OUT);
					led_toggle(RIGHT_OUT);
					led_off(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
				}
			}
			timer_resetLedCounter();
			subMode = BRAKE_NOW;
			break;
		}
		case BRAKE_NOW:
		{
			updatedCounters= timer_getCounter();
			while (updatedCounters.leds < FIVE_SEC_COUNT)
			{
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds % _500MS_COUNT == 0){
					led_off(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_off(BACK_OUT);
					led_toggle(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
				}
			}
			timer_resetLedCounter();
			subMode = BACK_NOW;
			break;
		}
		case BACK_NOW:
		{
			updatedCounters= timer_getCounter();
			while (updatedCounters.leds < FIVE_SEC_COUNT)
			{
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds % _500MS_COUNT == 0){
					led_off(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_toggle(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
				}
			}
			timer_resetLedCounter();
			subMode = LEFT_NOW;
			break;
		}
	}
}