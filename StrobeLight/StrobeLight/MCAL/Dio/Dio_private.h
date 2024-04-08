/*
 * Dio_private.h
 *
 * Created: 4/7/2024 8:53:24 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include "Dio_config.h"

extern const dio_pinStatus PinsStatusArray[TOTAL_PINS];  
static void dio_initPin(dio_pinNumber pin,dio_pinStatus status); // only set the status of one pin at a time

#endif /* DIO_PRIVATE_H_ */