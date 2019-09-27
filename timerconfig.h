/*
 * timerconfig.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#ifndef TIMERCONFIG_H_
#define TIMERCONFIG_H_

#include "stdtypes.h"
#include "registers.h"

#define PRESCALAR_1 0
#define PRESCALAR_8 1
#define PRESCALAR_64 2
#define PRESCALAR_256 3
#define PRESCALAR_1024 4

typedef enum {TIMER0, TIMER1, TIMER2, TOTAL_TIMERS} TIMERS_t;
typedef enum {NORMAL, CTC, FASTPWM, PHASECORRECTPWM, POLLING = 0, INTERRUPT, EXTERNAl = 0, 	INTERNAL} MODES_t;
typedef enum {NONE, PRESCALE_8, PRESCALE_32,PRESCALE_64, PRESCALE_128,PRESCALE_256, PRESCALE_1024} PRESCALE_t;
typedef enum {FALLING_EDGE, RISING_EDGE, DEFAULT} EXTERNALCLK_t;
typedef enum {INPUTCOMPARE, OUTPUTCOMPARE, NOTASSIGNED}COMPARE_t;
typedef enum {CLEAR,SET,TOGGLE, NORM}STATUS_t;
typedef enum {BIT_8,BIT_9,BIT_10}BIT_t;
typedef enum {UNIT_A, UNIT_B}UNIT_t;
typedef struct
{
	TIMERS_t TIMER;
	uint32 frequency; // In case of external clock "In HZ"
	MODES_t clock;
	MODES_t MODE;
	MODES_t STATE; // To check  polling or i
	STATUS_t STATUS;
	COMPARE_t COMPARE;
	BIT_t BITS;
	uint8 pin;
	uint8 port;
	EXTERNALCLK_t EDGE;
	PRESCALE_t PRESCALER;
	UNIT_t UNIT;
	uint8 IS_OK;
}TIMER_cnfg_t;

extern TIMER_cnfg_t TIMER_cnfg_arr [TOTAL_TIMERS];



#endif /* TIMERCONFIG_H_ */
