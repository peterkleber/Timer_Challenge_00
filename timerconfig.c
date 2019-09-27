/*
 * timerconfig.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#include"DIO.h"
#include "timerconfig.h"
#include "timer.h"

TIMER_cnfg_t TIMER_cnfg_arr[TOTAL_TIMERS] = { { TIMER0, CRYSTAL_FREQ, INTERNAL,
		NORMAL, POLLING, NORM, INPUTCOMPARE, BIT_8, NA, NA, FALLING_EDGE,
		PRESCALE_8, UNIT_A, OK } };
