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

#define pull_offset() 
void DIO_INIT(void)
{
	DIO_Pin_Number i;
	for (i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}

}

static void DIO_InitPin(DIO_Pin_Number pin,DIO_PinStatus_t status){
	
	DIO_Port_t port=pin/8;
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
			CLEAR_BIT(PORTA_DIR,pin_num);                 // SET Direction to input 
			CLEAR_BIT(PORTA_PIN0CTRL,pin_num);           // disable pull up  
			break;
			case PB:
			CLEAR_BIT(PORTB_DIR,pin_num);
			CLEAR_BIT(PORTB_PIN0CTRL,pin_num);        
			break;
			case PC:
			CLEAR_BIT(PORTC_DIR,pin_num);
			CLEAR_BIT(PORTC_PIN0CTRL,pin_num);        
			break;
			
		}
		break;
		
		case INPULL:
		switch(port)
		{
		  case PA:
		  CLEAR_BIT(PORTA_DIR,pin_num);                 // SET Direction to input
		  SET_BIT(PORTA_PIN0CTRL,pin_num);             // Enable pull up  
		  break;
		  case PB:
		  CLEAR_BIT(PORTB_DIR,pin_num);
	  	  SET_BIT(PORTB_PIN0CTRL,pin_num);
		  break;
		  case PC:
		  CLEAR_BIT(PORTC_DIR,pin_num);
		  SET_BIT(PORTC_PIN0CTRL,pin_num);
		  break;
		}
		break;
	}
}
	


void DIO_WritePin(DIO_Pin_Number pin,DIO_PinVoltage_t voltage )
{   
	

	DIO_Port_t port=pin/8;
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


DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_Number pin)
{
	
	DIO_Port_t port=pin/8;
	uint8_t pin_num=pin%8;
	DIO_PinVoltage_t volt=LOW;
	
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

void DIO_TogglePIN( DIO_Pin_Number pin){
	
	DIO_Port_t port=pin/8;
	uint8_t pin_num =pin%8;
	switch(port){
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


void WRITE_PORT(DIO_Port_t port,uint8_t value){
	
	
	switch(port){
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

uint8_t DIO_ReadPort(DIO_Port_t port){
	uint8_t value=0;
	switch(port){
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