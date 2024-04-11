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

#include "wdt_config.h"

#define CPU_CCP  _SFR_MEM8(0x0034)
#define WDT_CTRLA  _SFR_MEM8(0x0100)


void wdt_init(wdt_period_t value);
void wdt_deinit(void);

#endif /* WDG_H_ */