/*
 * Wdt.c
 *
 * Created: 4/10/2024 2:53:19 AM
 *  Author:  Nada Salloum - https://github.com/nadasalloum
 */ 

#include <avr/io.h>
#include "StdMacros.h"
#include "wdt_private.h"
#include "Wdt.h"
#include "wdt_config.h"



void wdt_init(void){
	/** wdt key protection */
	CPU_CCP = (0xD8<<0);
	__asm__ __volatile__  ( "mov r16 , %0\n"
	"STS 0x0100, r16\n"
	::"r" (wdt_period)  /* set timer interval with config value */
	);

}

void wdt_deinit(void)
{   /** wdt key protection */
	CPU_CCP = (0xD8<<0);
	__asm__ __volatile__  ( "ldi r16 , 0x00\n"
	"STS 0x0100, r16\n" /* Turn off the wdt */
	::
	);
}
