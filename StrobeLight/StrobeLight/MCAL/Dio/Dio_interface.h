/*
 * Dio_interface.h
 *
 * Created: 4/7/2024 8:53:03 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "StdTypes.h"

 /*** Typedefs ***/
typedef enum
{
    OUTPUT=7,
    INPUT,
    INPULL
} dio_pinStatus;
typedef enum
{
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7,
} dio_pinNumber;
typedef enum
{
    PA=0,
    PB=1,
    PC=2
} dio_portNumber;

typedef enum
{
    LOW=0,
    HIGH=1
} dio_pinVoltage_t;


/************* API ***********/

void dio_init(void)                                              ;            //To set the status of all pins at once (output, input, or pull-up).
void dio_initPin(dio_portNumber port,dio_pinNumber pin,dio_pinStatus status)         ;           //To set the status of an individual pin at a time (output, input, or pull-up).
void dio_writePin(dio_portNumber port,dio_pinNumber pin,dio_pinVoltage_t voltage )   ;          
dio_pinVoltage_t dio_readPin(dio_portNumber port,dio_pinNumber pin)                  ;
void dio_togglePin(dio_portNumber port,dio_pinNumber pin)                            ;
void dio_writePort(dio_portNumber port,uint8_t value)            ;
uint8_t dio_readPort(dio_portNumber port)                        ;



#endif /* DIO_INTERFACE_H_ */