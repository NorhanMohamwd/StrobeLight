/*
 * Dio_program.c
 *
 * Created: 4/7/2024 8:50:18 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 
#include <avr/io.h>
#include "StdTypes.h"
#include "StdMacros.h"
#include "Dio_interface.h"
#include "Dio_private.h"


void dio_init(void)
{
	dio_pinNumber i;
	for (i=PINA0; i<TOTAL_PINS; i++)
	{
		dio_initPin(i,PinsStatusArray[i]);
	}

}

static void dio_initPin(dio_pinNumber pin,dio_pinStatus status)
{

	dio_portNumber port=pin/8;
	uint8_t pin_num=pin%8;

	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_DIR,pin_num);            //PORT_Direction
			case PB:
			SET_BIT(PORTB_DIR,pin_num);
			break;
			case PC:
			SET_BIT(PORTC_DIR,pin_num);
			break;
		}
		break;
		case INPUT:
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_DIR,pin_num);                            // SET Direction to input
			CLEAR_BIT( _SFR_MEM8(0x0410+pin_num* 0x01),3);         // disable pull up
			break;
			case PB:
			CLEAR_BIT(PORTB_DIR,pin_num);
			CLEAR_BIT( _SFR_MEM8(0x0430+pin_num* 0x01),3);
			break;
			case PC:
			CLEAR_BIT(PORTC_DIR,pin_num);
			CLEAR_BIT( _SFR_MEM8(0x0450+pin_num* 0x01),3);
			break;

		}
		break;

		case INPULL:
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_DIR,pin_num);                  // SET Direction to input
			SET_BIT( _SFR_MEM8(0x0410+pin_num* 0x01),3);            // Enable pull up
			break;
			case PB:
			CLEAR_BIT(PORTB_DIR,pin_num);
			SET_BIT( _SFR_MEM8(0x0430+pin_num* 0x01),3);
			break;
			case PC:
			CLEAR_BIT(PORTC_DIR,pin_num);
			SET_BIT( _SFR_MEM8(0x0450+pin_num* 0x01),3);
			break;
		}
		break;
	}
}



void dio_writePin(dio_pinNumber pin,dio_pinVoltage_t voltage )
{


	dio_portNumber port=pin/8;
	uint8_t pin_num=pin%8;
	if (voltage == HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_OUT,pin_num);
			break;
			case PB:
			SET_BIT(PORTB_OUT,pin_num);
			break;
			case PC:
			SET_BIT(PORTC_OUT,pin_num);
			break;
		}
	}
	else if ( voltage==LOW)
	{
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_OUT,pin_num);
			break;
			case PB:
			CLEAR_BIT(PORTB_OUT,pin_num);
			break;
			case PC:
			CLEAR_BIT(PORTC_OUT,pin_num);
			break;
		}
	}

}


dio_pinVoltage_t dio_readPin(dio_pinNumber pin)
{

	dio_portNumber port=pin/8;
	uint8_t pin_num=pin%8;
	dio_pinVoltage_t volt=LOW;

	switch(port)
	{
		case PA:
		volt=GET_BIT(PORTA_IN,pin_num);
		break;
		case PB:
		volt=GET_BIT(PORTB_IN,pin_num);
		break;
		case PC:
		volt=GET_BIT(PORTC_IN,pin_num);
		break;
	}
	return volt;
}

void dio_togglePin( dio_pinNumber pin)
{

	dio_portNumber port=pin/8;
	uint8_t pin_num =pin%8;
	switch(port)
	{
		case PA:
		TOGGLE_BIT(PORTA_OUT,pin_num);
		break;
		case PB:
		TOGGLE_BIT(PORTB_OUT,pin_num);
		break;
		case PC:
		TOGGLE_BIT(PORTC_OUT,pin_num);
		break;
		default:
		break;
	}
}


void dio_writePort(dio_portNumber port,uint8_t value)
{


	switch(port)
	{
		case PA:
		PORTA_OUT=value;
		break;
		case PB:
		PORTA_OUT=value;
		break;
		case PC:
		PORTA_OUT=value;
		break;
		default:
		break;
	}

}

uint8_t  dio_readPort(dio_portNumber port)
{
	uint8_t value=0;
	switch(port)
	{
		case PA:
		value=GET_REG(PORTA_OUT);
		break;
		case PB:
		value=GET_REG(PORTB_OUT);
		break;
		case PC:
		value=GET_REG(PORTC_OUT);
		break;
		default:
		break;
	}
	return value;
}