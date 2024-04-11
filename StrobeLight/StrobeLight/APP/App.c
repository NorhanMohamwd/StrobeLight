/*
 * App.c
 *
 * Created: 4/7/2024 9:10:50 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include "App.h"
#include "Delay.h"
#include "Button.h"
#include "Led.h"
#include "Timer_interface.h"
#include "Interrupt.h"
#include "Wdt.h"


uint8_t LEFT, RIGHT, BACK, BRAKE =LOW;

void app_init(void)
{
	wdt_init(WDT_PERIOD_1S);
	button_init();
	delay_init();
	Timer_configType configTimerB = {TIMERB,PERIDIC_INTERRUPT,CLKDIV1,COUNTING_DOWN};
	Timer_init(&configTimerB , 250);
	TimerB_setCallBack(Timer_resetWDG);
	enableGlobalInterrupt();
}

void app_runnable(void){
	union signalsUnion signalProcessing;
	signalProcessing = button_read();
	if (signalProcessing.signal.LEFT == HIGH){
		RIGHT = BACK = BRAKE = 0;
		delay_ms(316);
		LEFT = !LEFT;
		signalProcessing.signal.LEFT = LOW;
	}
	else if (signalProcessing.signal.RIGHT == HIGH){
		LEFT = BACK = BRAKE = 0;
		delay_ms(316);
		RIGHT = !RIGHT;
		signalProcessing.signal.RIGHT = LOW;
	}
	else if (signalProcessing.signal.BACK == HIGH){
		LEFT = RIGHT = BRAKE = 0;
		delay_ms(316);
		BACK = !BACK;
		signalProcessing.signal.BACK = LOW;
	}
	else if (signalProcessing.signal.BRAKE == HIGH){
		LEFT = RIGHT = BACK = 0;
		delay_ms(316);
		BRAKE = !BRAKE;
		signalProcessing.signal.BRAKE = LOW;
	}
	
	if (LEFT)
	{
		led_on(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
	}
	else if (RIGHT)
	{
		led_off(LEFT_OUT);
		led_on(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
	}
	else if (BACK)
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_on(BACK_OUT);
		led_off(BRAKE_OUT);
	}
	else if (BRAKE)
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_off(BACK_OUT);
		led_on(BRAKE_OUT);
	}
	else 
	{
		led_off(LEFT_OUT);
		led_off(RIGHT_OUT);
		led_off(BACK_OUT);
		led_off(BRAKE_OUT);
		led_on(POWER_OFF);
	}
}