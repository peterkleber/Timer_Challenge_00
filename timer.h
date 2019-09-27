/*
 * timer.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"DIO.h"
#include "registers.h"
#include "stdtypes.h"
#include "timerconfig.h"
// Register TCCR0 Bits
#define F0C0 7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02 2
#define CS01 1
#define CS00 0
// Register TIMSK Bits
#define TOIE0 0
#define OCIE0 1
// Internal clock frequency "in HZ"
#define CRYSTAL_FREQ 8000000
#define OVERFLOW_VALUE 256
// Register TCCR1A Bits
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A 3
#define FOC1B 2
#define WGM11 1
#define WGM10 0
// Register TCCR1B Bits
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0
//  Register TIMSK Bits
#define TICIE1 5
#define OCIE1A 4
#define OCIE1B 3
#define TOIE1 2

#define CS20 0
#define CS21 1
#define CS22 2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2 7


Std_Func_t Timer_Init (TIMERS_t TIMER);
Std_Func_t Timer_Wait(TIMERS_t TIMER, uint32 value_in_ms);
Std_Func_t Generate_PWM (uint8 DC);
Std_Func_t Timer_De_Init (TIMERS_t TIMER);





#endif /* TIMER_H_ */
