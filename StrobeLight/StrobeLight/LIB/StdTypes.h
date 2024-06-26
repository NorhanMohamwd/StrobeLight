/*
 * StdTypes.h
 *
 * Created: 4/7/2024 6:07:20 PM
 *  Author: Nada Salloum - https://github.com/nadasalloum
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

#define LOW     0
#define HIGH    1

typedef unsigned char    uint8_t;
typedef   signed char    sint8_t;

//typedef unsigned short   uint16_t;
typedef   signed short   sint16_t;

typedef unsigned long    uint32_t;
typedef   signed long    sint32_t;


#define   NULLPTR  ((void*)0)

typedef enum{
	FALSE=0,
	TRUE
}bool_t;


#endif /* STDTYPES_H_ */