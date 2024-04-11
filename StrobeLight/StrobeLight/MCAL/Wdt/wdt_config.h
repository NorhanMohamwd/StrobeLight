/*
 * wdt_config.h
 *
 * Created: 4/10/2024 4:33:37 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef WDT_CONFIG_H_
#define WDT_CONFIG_H_

# define _WD_PS3_MASK      0x00
typedef enum {
 WDT_PERIOD_128MS = 0x05 ,               //0.128s
 WDT_PERIOD_250MS = 0x06 ,              // .250S 
 WDT_PERIOD_500MS = 0x07,             // 0.5s
 WDT_PERIOD_1S=0x08   ,            // 1.024s
 WDT_PERIOD_2S=0x09               // 2.048s
}wdt_period_t;



//#define wdt_init()  WDT_CTRLA = WDT_PERIOD_128MS;
//#define wdt_reset()  WDT_CTRLA = WDT_PERIOD_1S;



#endif /* WDT_CONFIG_H_ */