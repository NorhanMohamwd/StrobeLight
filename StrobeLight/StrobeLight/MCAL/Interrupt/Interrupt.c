/*
 * Interrupt.c
 *
 * Created: 4/10/2024 1:50:06 AM
 *  Author: Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 
#include <avr/io.h>
#include "Interrupt.h"

void enableGlobalInterrupt(void){
	SET_BIT(SREG,INTERRUPT_PIN);
}

void disableGlobalInterrupt(void){
	CLEAR_BIT(SREG,INTERRUPT_PIN);
}