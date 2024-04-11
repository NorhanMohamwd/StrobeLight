/*
 * StrobeLight.c
 *
 * Created: 4/7/2024 5:56:25 PM
 * Author : Nada Salloum - https://github.com/nadasalloum
			Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 

#include <avr/io.h>
#include "app.h"
#include "wdt_config.h"
#include "wdt.h"
#include "StdMacros.h"
#include "Delay.h"


int main(void)
 {
	app_init();

    while (1) 
    {
		app_runnable();
	
    }
}

