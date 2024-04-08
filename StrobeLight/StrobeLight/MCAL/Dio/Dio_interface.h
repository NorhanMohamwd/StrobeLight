/*
 * Dio_interface.h
 *
 * Created: 4/7/2024 8:53:03 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "StdTypes.h"
typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
}DIO_Pin_Number;

typedef enum{
	OUTPUT=7,
	INPUT,
	INPULL
}DIO_PinStatus_t;

typedef enum{
	PA,
	PB,
	PC
}DIO_Port_t;

typedef enum{
	LOW=0,
	HIGH=1
}DIO_PinVoltage_t;




void DIO_INIT(void);                                     //TO Set the status of all the pins at once whether it's( output,input , inpull)
void DIO_WritePin(DIO_Pin_Number pin,DIO_PinVoltage_t voltage );
DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_Number pin);
void DIO_TogglePIN(DIO_Pin_Number pin);

void DIO_WritePort(DIO_Port_t port,uint8_t value);
uint8_t DIO_ReadPort(DIO_Port_t port);



#endif /* DIO_INTERFACE_H_ */