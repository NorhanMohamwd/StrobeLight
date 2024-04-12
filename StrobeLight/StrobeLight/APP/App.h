/*
 * App.h
 *
 * Created: 4/7/2024 9:11:31 PM
 *  Author: Norhan Mohamed - https://github.com/NorhanMohamwd
 */ 


#ifndef APP_H_
#define APP_H_


/************* API ***********/

/*starts all the system's modules*/
void app_init(void);
/*processes input signals and turns on/off corresponding leds*/
void app_runnable(void);

#endif /* APP_H_ */