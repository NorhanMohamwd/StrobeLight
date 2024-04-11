/*
 * Wdg.h
 *
 * Created: 4/10/2024 2:53:35 AM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 

/*
 * wdt.h
 *
 * Created: 4/10/2024 4:33:37 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 
#ifndef WDG_H_
#define WDG_H_



/* reset wdt to it's initial configurable value */
#define wdt_reset() __asm__ __volatile__ ("wdr")
         
/* Enable  the wdt with configurable value */
void wdt_init(void);

/* disable wdt */
void wdt_deinit(void);

#endif /* WDG_H_ */