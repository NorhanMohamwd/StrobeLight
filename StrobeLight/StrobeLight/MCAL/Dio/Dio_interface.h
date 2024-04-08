/*
 * Dio_interface.h
 *
 * Created: 4/7/2024 8:53:03 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "StdTypes.h"
typedef enum
{
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
} dio_pinNumber;

typedef enum
{
    OUTPUT=7,
    INPUT,
    INPULL
} dio_pinStatus;

typedef enum
{
    PA,
    PB,
    PC
} dio_portNumber;

typedef enum
{
    LOW=0,
    HIGH=1
} dio_pinVoltage_t;




void dio_init(void)                                              ;            //To set the status of all pins at once (output, input, or pull-up).
void dio_writePin(dio_pinNumber pin,dio_pinVoltage_t voltage )   ;
dio_pinVoltage_t dio_readPin(dio_pinNumber pin)                  ;
void dio_togglePin(dio_pinNumber pin)                            ;
void dio_writePort(dio_portNumber port,uint8_t value)            ;
uint8_t dio_readPort(dio_portNumber port)                        ;



#endif /* DIO_INTERFACE_H_ */