/*
 * Dio_program.c
 *
 * Created: 4/7/2024 8:50:18 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "StdTypes.h"
#include "StdMacros.h"
#include "Dio_interface.h"
#include "Dio_private.h"

static void (*g_dioCallBackPtr)(void)=NULLPTR;

 /**To set the status of all pins at once (output, input, or pull-up). **/
void dio_init(void)
{  
	dio_pinNumber pin=0;
    bool_t flag_firstIn_PB=FALSE;
    bool_t flag_firstIn_PC=FALSE;
    uint8_t i;
	for ( i=0; i<TOTAL_PINS; i++)
	{
    if (i<8)
           { // PortA pins
		     dio_initPin(PA,pin,PinsStatusArray[i]);
             pin++;
           }
    else if (i<14)  //PortB pins 
           {
            if(flag_firstIn_PB==FALSE )
            {
              pin =DIO_PIN0;
              flag_firstIn_PB=TRUE;
            }
	        dio_initPin(PB, pin,PinsStatusArray[i]);
            pin++;
           }
    else
          {  //PORTC pins 
          if(flag_firstIn_PC==FALSE )
          {
           pin =DIO_PIN0;
           flag_firstIn_PC=TRUE;
          }
          dio_initPin(PC, pin,PinsStatusArray[i]);
          pin++;
          }

   }
}
/***To set the status of an individual pin at a time (output, input, or pull-up)***/
 void dio_initPin(dio_portNumber port,dio_pinNumber pin,dio_pinStatus status  )
{


	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_DIR,pin);            //PORT_Direction
			break;
			case PB:
			SET_BIT(PORTB_DIR,pin);
			break;
			case PC:
			SET_BIT(PORTC_DIR,pin);
			break;
		}
		break;
		case INPUT:
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_DIR,pin);                            // SET Direction to input
			CLEAR_BIT( _SFR_MEM8(0x0410+pin* 0x01),3);         // disable pull up
			break;
			case PB:
			CLEAR_BIT(PORTB_DIR,pin);
			CLEAR_BIT( _SFR_MEM8(0x0430+pin* 0x01),3);
			break;
			case PC:
			CLEAR_BIT(PORTC_DIR,pin);
			CLEAR_BIT( _SFR_MEM8(0x0450+pin* 0x01),3);
			break;

		}
		break;

		case INPULL:
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_DIR,pin);                // SET Direction to input
			SET_BIT( _SFR_MEM8(0x0410+pin* 0x01),3);            // Enable pull up
			break;
			case PB:
			CLEAR_BIT(PORTB_DIR,pin);
			SET_BIT( _SFR_MEM8(0x0430+pin* 0x01),3);
			break;
			case PC:
			CLEAR_BIT(PORTC_DIR,pin);
			SET_BIT( _SFR_MEM8(0x0450+pin* 0x01),3);
			break;
		}
		break;
			
	}
}



void dio_writePin(dio_portNumber port,dio_pinNumber pin,dio_pinVoltage_t voltage )
{
	if (voltage == HIGH_)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_OUT,pin);
			break;
			case PB:
			SET_BIT(PORTB_OUT,pin);
			break;
			case PC:
			SET_BIT(PORTC_OUT,pin);
			break;
		}
	}
	else if ( voltage==LOW_)
	{
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_OUT,pin);
			break;
			case PB:
			CLEAR_BIT(PORTB_OUT,pin);
			break;
			case PC:
			CLEAR_BIT(PORTC_OUT,pin);
			break;
		}
	}

}


dio_pinVoltage_t dio_readPin(dio_portNumber port,dio_pinNumber pin)
{

	dio_pinVoltage_t volt=LOW_;

	switch(port)
	{
		case PA:
		volt=GET_BIT(PORTA_IN,pin);
		break;
		case PB:
		volt=GET_BIT(PORTB_IN,pin);
		break;
		case PC:
		volt=BIT_IS_SET(PORTC_IN,pin);
		break;
	}
	return volt;
}

void dio_togglePin(dio_portNumber port, dio_pinNumber pin)
{

	switch(port)
	{
		case PA:
		TOGGLE_BIT(PORTA_OUT,pin);
		break;
		case PB:
		TOGGLE_BIT(PORTB_OUT,pin);
		break;
		case PC:
		TOGGLE_BIT(PORTC_OUT,pin);
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
		PORTB_OUT=value;
		break;
		case PC:
		PORTB_OUT=value;
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
		value=GET_REG(PORTA_IN);
		break;
		case PB:
		value=GET_REG(PORTB_IN);
		break;
		case PC:
		value=GET_REG(PORTC_IN);
		break;
		default:
		break;
	}
	return value;
}

uint8_t  dio_readFlags(dio_portNumber port)
{
	uint8_t value=0;
	switch(port)
	{
		case PA:
		value=GET_REG(PORTA_INTFLAGS);
		break;
		case PB:
		value=GET_REG(PORTB_INTFLAGS);
		break;
		case PC:
		value=GET_REG(PORTC_INTFLAGS);
		break;
		default:
		break;
	}
	return value;
}

void dio_resetFlags(dio_portNumber port,dio_pinNumber pin){
	
	switch(port)
	{
		case PA:
		SET_BIT(PORTA_INTFLAGS,pin);
		break;
		case PB:
		SET_BIT(PORTB_INTFLAGS,pin);
		break;
		case PC:
		SET_BIT(PORTC_INTFLAGS,pin);
		break;
		default:
		break;
	}
}
void dio_enableInterruptTrigger(dio_portNumber port,dio_pinNumber pin , dio_pinInterrupt interrupt){
	
	switch(port)
	{
		case PA:
		_SFR_MEM8(0x0410+pin* 0x01) |= interrupt ;            // Enable interrupt trigger
		break;
		case PB:
		_SFR_MEM8(0x0430+pin* 0x01) |= interrupt ;
		break;
		case PC:
		_SFR_MEM8(0x0450+pin* 0x01) |= interrupt ;
		break;
	}
	
}


void dio_setCallBack(void (*a_ptr)(void)){
	
	g_dioCallBackPtr=a_ptr;
}

ISR(PORTB_PORT_vect){
	if(g_dioCallBackPtr != NULLPTR){
		g_dioCallBackPtr();
	}
}

ISR(PORTC_PORT_vect){
	if(g_dioCallBackPtr != NULLPTR){
		g_dioCallBackPtr();
	}
}
