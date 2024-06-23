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
uint8_t PREVIOUS_LEFT, PREVIOUS_RIGHT, PREVIOUS_BACK, PREVIOUS_BRAKE, PREVIOUS_STROBE_1 , PREVIOUS_STROBE_2 = LOW;
union signalsUnion buttonFlags;
union signalsUnion previous_signal; 
volatile Timer_counters updatedCounters;
app_subMode subMode = LEFT_NOW;
//app_subMode subMode = RIGHT_NOW;
app_sysMode sysMode = MODE_A;
app_sysMode previous_sysMode = MODE_A;
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
	
	static bool_t flag_firstEnterRunnable=FALSE;
	static bool_t flag_ModeChanged=TRUE;
	uint8_t counts =0;

	//eeprom_read 
	if(flag_firstEnterRunnable==FALSE)
	{
		
	readModeFromEeprom(&sysMode);   // to read the mode only when restarting the system 
	if(sysMode==0xFF)
	{
		
	sysMode=MODE_A;
	flag_firstEnterRunnable=TRUE;
	flag_ModeChanged=TRUE;
	}
	}
	
	// Change them to mode state and check for it's variable 
	// switch_case for modes 
	if (buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS){
		if (sysMode==MODE_A){
			sysMode=MODE_B;
		 	LEFT = RIGHT = BACK = BRAKE  = STROBE_1=STROBE_2 = 0;
		 	buttonFlags.signal.BRAKE = LOW;
			 flag_ModeChanged=TRUE;
			 
		}
		else if (sysMode==MODE_B){
			sysMode=MODE_A;
			LEFT = RIGHT = BACK = BRAKE  = STROBE_1=STROBE_2 = 0;
			buttonFlags.signal.BRAKE = LOW;
			flag_ModeChanged=TRUE;
			
		}
		
				 timer_resetLedCounter();
				 updatedCounters= timer_getCounter();
				 while (counts < 5){
					 updatedCounters= timer_getCounter();
					 if (updatedCounters.leds >= 50)
					 {
						
						 led_toggle(BRAKE_OUT);
						 timer_resetLedCounter();
						 counts++;
					 }
					 
				 }
		 buttonFlags.signal.BRAKE_PRESSED =SHORT_PRESS;
	}
	if (buttonFlags.signal.LEFT_PRESSED == LONG_PRESS){
		if (sysMode == MODE_C){}
		else{
		previous_sysMode = sysMode;
		sysMode=MODE_C;
		buttonFlags.signal.LEFT = LOW;
		flag_ModeChanged=TRUE;
		 //buttonFlags.signal.LEFT_PRESSED =SHORT_PRESS;
		}
	}
	
	else {
		if(sysMode==MODE_C){
			sysMode =previous_sysMode;
			previous_sysMode = MODE_C;
			flag_ModeChanged=TRUE;
		}
		

	}
		if(flag_ModeChanged==TRUE)
		{
			writeModeToEeprom(sysMode);  // to write the mode after executing the signal at least one time
			flag_ModeChanged==FALSE;
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







void app_processSignals(union signalsUnion x,union signalsUnion y){
	
	buttonFlags= x;
	previous_signal=y;
}

void app_modeA(void){

	
	 /*checks if the new value is LEFT*/
	 if (buttonFlags.signal.LEFT == HIGH){
		 RIGHT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 LEFT = !LEFT;
		 buttonFlags.signal.LEFT = LOW;
		 timer_resetLedCounter();
	 }
	 else if (buttonFlags.signal.RIGHT == HIGH){
		 LEFT = BACK = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 RIGHT = !RIGHT;
		 buttonFlags.signal.RIGHT = LOW;
		 timer_resetLedCounter();
	 }
	 else if (buttonFlags.signal.BACK == HIGH){
		 LEFT = RIGHT = BRAKE = STROBE_1 =  STROBE_2 = 0;
		 BACK = !BACK;
		 buttonFlags.signal.BACK = LOW;
		 timer_resetLedCounter();
	 }
	 else if (buttonFlags.signal.BRAKE == HIGH){
		 LEFT = RIGHT = BACK= STROBE_1=  STROBE_2 = 0;
		 BRAKE = !BRAKE;
		 buttonFlags.signal.BRAKE = LOW;
		 timer_resetLedCounter();
	 }
	 else if (buttonFlags.signal.BTN_1 == HIGH){
		 LEFT = RIGHT = BACK = BRAKE  = STROBE_2 = 0;
		 STROBE_1 = !STROBE_1;
		 buttonFlags.signal.BTN_1 = LOW;
		 timer_resetLedCounter();
	 }
	 else if (buttonFlags.signal.BTN_2 == HIGH){
		 LEFT = RIGHT = BACK = BRAKE = STROBE_1 = 0;
		 STROBE_2 = !STROBE_2;
		 buttonFlags.signal.BTN_2 = LOW;
		 timer_resetLedCounter();
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
		 //led_on (POWER_OFF);
	 }	
}

void app_modeB(void)
{
	static bool_t Newsignal_detected =FALSE ;

	if (buttonFlags.signal.LEFT == HIGH)
	{
		
		LEFT = !LEFT;
		buttonFlags.signal.LEFT = LOW;
		Newsignal_detected=TRUE;
		if(RIGHT)
		{
			RIGHT = !RIGHT;
		}
		timer_resetLedCounter();
	}
	else if (buttonFlags.signal.RIGHT == HIGH)
	{
		RIGHT = !RIGHT;
		buttonFlags.signal.RIGHT = LOW;
		Newsignal_detected=TRUE;
		if(LEFT)
		{
			LEFT = !LEFT;
		}
		timer_resetLedCounter();
	}
	else if (buttonFlags.signal.BACK == HIGH)
	{
		
		BACK = !BACK;
		buttonFlags.signal.BACK = LOW;
		Newsignal_detected=TRUE;
	}
	else if (buttonFlags.signal.BRAKE == HIGH)
	{
		BRAKE = !BRAKE;
		buttonFlags.signal.BRAKE = LOW;
		Newsignal_detected=TRUE;
	}
	else if (buttonFlags.signal.BTN_1 == HIGH)
	{
		STROBE_1 = !STROBE_1;
		buttonFlags.signal.BTN_1 = LOW;
		Newsignal_detected=TRUE;
	}
	else if (buttonFlags.signal.BTN_2 == HIGH)
	{
		STROBE_2 = !STROBE_2;
		buttonFlags.signal.BTN_2 = LOW;
		Newsignal_detected=TRUE;
	}
	
	if(Newsignal_detected==TRUE)
	{
		if((LEFT)||(RIGHT))
		{
			
			if(LEFT)
			{

				led_off(RIGHT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
			}

			else if( RIGHT)
			{
				led_off(LEFT_OUT);
				led_off(BACK_OUT);
				led_off(BRAKE_OUT);
				led_off(STROBE1_OUT);
				led_off(STROBE2_OUT);
			}
		}
		else
		{
			led_off(LEFT_OUT);
			led_off(RIGHT_OUT);
			led_off(BACK_OUT);
			led_off(BRAKE_OUT);
			led_off(STROBE1_OUT);
			led_off(STROBE2_OUT);

		}

		Newsignal_detected=FALSE;
	}
	
	if(BRAKE)
	{
		if((LEFT)||(RIGHT))
		{
			if(LEFT)
			{
				led_on(RIGHT_OUT);
				led_on(BRAKE_OUT);
				
			}

			else if( RIGHT)
			{
				led_on(LEFT_OUT);
				led_on(BRAKE_OUT);
			}

		}
		else if((!LEFT)&&(!RIGHT))
		{
			led_on(LEFT_OUT);
			led_on(RIGHT_OUT);
			led_on(BRAKE_OUT);
		}
	}
	if(LEFT)
	{

		updatedCounters = timer_getCounter();
		if (updatedCounters.leds  >=secCounts)
		{
			led_toggle(LEFT_OUT);
			timer_resetLedCounter();
		}
		
	}
	if(RIGHT)
	{
		
		updatedCounters = timer_getCounter();
		if (updatedCounters.leds  >= secCounts)
		{
			led_toggle(RIGHT_OUT);
			timer_resetLedCounter();
		}
		

	}
	if(BACK)
	{
		led_on(BACK_OUT);
	}
	if(STROBE_1)
	{
		led_on(STROBE1_OUT);
	}
	if(STROBE_2)
	{
		led_on(STROBE2_OUT);
	}
	if ((!LEFT) &&(!RIGHT) && (!BACK) && (!BRAKE) && (!STROBE_1)&&(!STROBE_2)) {
		led_off(LEFT_OUT) ;
		led_off(RIGHT_OUT);
		led_off(BACK_OUT) ;
		led_off(BRAKE_OUT);
		led_off(STROBE1_OUT);
		led_off(STROBE1_OUT);
		//led_on (POWER_OFF);
	}
}



void app_modeC(void){
	//timer_resetLedCounter();
	static uint8_t blinkCounts =0;
	switch (subMode){
		case LEFT_NOW:
		{  
			timer_resetLedCounter(); 
			updatedCounters= timer_getCounter();
			while ((blinkCounts < 7)&&(buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS)){
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds >= 75)
				{
					led_toggle(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_off(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
					timer_resetLedCounter();
					blinkCounts++;
				}
				
			}
			
			timer_resetLedCounter();
			blinkCounts=0;
			subMode = RIGHT_NOW;
			//subMode = BACK_NOW;
			break;
		}
		
		case RIGHT_NOW:
		{
			timer_resetLedCounter();
			updatedCounters= timer_getCounter();
			while ((blinkCounts < 7)&&(buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS)){
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds >= 75)
				{
					led_off(LEFT_OUT);
					led_toggle(RIGHT_OUT);
					led_off(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
					timer_resetLedCounter();
					blinkCounts++;
				}
				
			}
			
			timer_resetLedCounter();
			blinkCounts=0;
			subMode = BACK_NOW;
		//	subMode = LEFT_NOW;
			
		break;	
		}
		

		case BACK_NOW:
		{
			timer_resetLedCounter();
			updatedCounters= timer_getCounter();
			while ((blinkCounts < 7)&&(buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS)){
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds >= 75)
				{
					led_off(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_toggle(BACK_OUT);
					led_off(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
					timer_resetLedCounter();
					blinkCounts++;
				}
				
			}
			
			timer_resetLedCounter();
			blinkCounts=0;
			subMode = BRAKE_NOW;
		break;	
		}
		
		
		case BRAKE_NOW:
		{
			timer_resetLedCounter();
			updatedCounters= timer_getCounter();
			while ((blinkCounts < 7)&&(buttonFlags.signal.BRAKE_PRESSED == LONG_PRESS)){
				updatedCounters= timer_getCounter();
				if (updatedCounters.leds >= 75)
				{
					led_off(LEFT_OUT);
					led_off(RIGHT_OUT);
					led_off(BACK_OUT);
					led_toggle(BRAKE_OUT);
					led_off(STROBE1_OUT);
					led_off(STROBE2_OUT);
					timer_resetLedCounter();
					blinkCounts++;
				}
				
			}
			
			timer_resetLedCounter();
			blinkCounts=0;
			//subMode = LEFT_NOW;
			subMode = RIGHT_NOW;
		break;		
		}
		
	}
}