/*
 * wdt_config.h
 *
 * Created: 4/10/2024 4:33:37 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef WDT_CONFIG_H_
#define WDT_CONFIG_H_


typedef enum {
 WDT_PERIOD_128MS=0x5 ,               //0.128s
 WDT_PERIOD_250MS=0x6 ,              // .250S 
 WDT_PERIOD_500MS=0x07,             // 0.5s
 WDT_PERIOD_1S=0x08   ,            // 1.024s
 WDT_PERIOD_2S=0x09               // 2.048s
}wdt_period_t;





// conifgration

wdt_period_t wdt_period=WDT_PERIOD_1S;



#endif /* WDT_CONFIG_H_ */