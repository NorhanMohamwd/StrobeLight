/*
 * Dio_private.h
 *
 * Created: 4/7/2024 8:53:24 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include "Dio_config.h"

extern const DIO_PinStatus_t PinsStatusArray[TOTAL_PINS];  
static void DIO_InitPin(DIO_Pin_Number pin,DIO_PinStatus_t status);

#endif /* DIO_PRIVATE_H_ */