/*
 * timer.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#include "timer.h"

Std_Func_t Timer_Init(TIMERS_t TIMER) {
	uint8 retval;
	if (TIMER < TOTAL_TIMERS) {
		TIMER_cnfg_arr[TIMER].IS_OK = INITIALIZED;
	}
	else
	{
		TIMER_cnfg_arr[TIMER].IS_OK = NOT_INITIALIZED;
		return retval = NOK;
	}
	switch (TIMER)
	{
	case TIMER0:
		// To check on the TOMER0 operating mode
		if ((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL) {
				// In normal mode. clear bit WGM00, bit WGM01, COM00, COM01
			REG_TCCR0 &= ~((1u << WGM00) | (1u << WGM01));
			REG_TCCR0 &= ~((1u << COM00) | (1u << COM01)); //default hardware values
			if ((TIMER_cnfg_arr[TIMER0].COMPARE) == TOGGLE)
			{
				REG_TCCR0 |= (1u << COM00);
				REG_TCCR0 &= ~(1u << COM01);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
			{
				REG_TCCR0 |= (1u << COM01);
				REG_TCCR0 &= ~(1u << COM00);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
			{
				REG_TCCR0 |= ((1u << COM00) | (1u << COM01));
			}
			else {
					retval = NOK;
			}

		}
		else if ((TIMER_cnfg_arr[TIMER0].MODE) == PHASECORRECTPWM)
		{
			// In phase correct PWM mode.  Set bit WGM00
			if ((TIMER_cnfg_arr[TIMER0].COMPARE) == NORM)
			{
				REG_TCCR0 |= (1u << WGM00);
				REG_TCCR0 &= ~(1u << WGM01);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
			{
				REG_TCCR0 |= (1u << COM01);
				REG_TCCR0 &= ~(1u << COM00);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
			{
				REG_TCCR0 |= ((1u << COM00) | (1u << COM01));
			}
			else
			{
				retval = NOK;
			}
		}
		else if ((TIMER_cnfg_arr[TIMER0].MODE) == CTC)
		{
			REG_TCCR0 |= (1u << WGM01);
			REG_TCCR0 &= ~(1u << WGM00);
			if ((TIMER_cnfg_arr[TIMER0].COMPARE) == TOGGLE)
			{
				REG_TCCR0 |= (1u << COM00);
				REG_TCCR0 &= ~(1u << COM01);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
			{
				REG_TCCR0 |= (1u << COM01);
				REG_TCCR0 &= ~(1u << COM00);
			}
			else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
			{
				REG_TCCR0 |= ((1u << COM00) | (1u << COM01));
			}
			else
			{
				retval = NOK;
			}
		}
		else if ((TIMER_cnfg_arr[TIMER0].MODE) == FASTPWM)
		{
			REG_TCCR0 = REG_TCCR0 | ((1u << WGM01) | (1u << WGM00));
		}
		else
		{
			retval = NOK;
		}
		if ((TIMER_cnfg_arr[TIMER0].STATE) == POLLING)
		{
			REG_TCCR0 &= ~((1u << WGM00) | (1u << WGM01));
		}
		else if ((TIMER_cnfg_arr[TIMER0].STATE) == INTERRUPT)
		{
			if ((TIMER_cnfg_arr[TIMER0].MODE) == CTC)
			{
				// in CTC mode, set the OCIE0 bit in
				REG_TIMSK |= (1u << OCIE0);
			}
			else if ((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL)
			{
				REG_TIMSK |= (1u << TOIE0);
			}
			else
			{
				retval = NOK;
			}
		}
		else
		{
			retval = NOK;
		}
		break;
	case (TIMER1):
		if((TIMER_cnfg_arr[TIMER1].MODE) == NORMAL)
		{
			if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
			{
				if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
				{
					REG_TCCR1A &=~ (1u<<COM1A0);
					REG_TCCR1A &=~ (1u<<COM1A1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
				{
					REG_TCCR1A &=~ (1u<<COM1B0);
					REG_TCCR1A &=~ (1u<<COM1B1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
			{
				if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
				{
					REG_TCCR1A |=  (1u<<COM1A0);
					REG_TCCR1A &=~ (1u<<COM1A1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
				{
					REG_TCCR1A |=  (1u<<COM1B0);
					REG_TCCR1A &=~ (1u<<COM1B1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
			{
				if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
				{
					REG_TCCR1A &=~ (1u<<COM1A0);
					REG_TCCR1A |= (1u<<COM1A1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
				{
					REG_TCCR1A &=~ (1u<<COM1B0);
					REG_TCCR1A |= (1u<<COM1B1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
			{
				if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
				{
					REG_TCCR1A |= (1u<<COM1A0);
					REG_TCCR1A |= (1u<<COM1A1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
				{
					REG_TCCR1A |= (1u<<COM1B0);
					REG_TCCR1A |= (1u<<COM1B1);
					REG_TCCR1A &=~ (1u<<WGM10);
					REG_TCCR1A &=~ (1u<<WGM11);
					REG_TCCR1B &=~ (1u<<WGM12);
					REG_TCCR1B &=~ (1u<<WGM13);
				}
				else
				{
					retval = NOK;
				}
			}
			else
			{
				retval = NOK;
			}
		}
		else if ((TIMER_cnfg_arr[TIMER1].MODE) == CTC)
		{
			if ((TIMER_cnfg_arr[TIMER1].COMPARE) == OUTPUTCOMPARE)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~  (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].COMPARE) == INPUTCOMPARE)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~  (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~  (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}
			}
		}
		else if ((TIMER_cnfg_arr[TIMER1].MODE) == FASTPWM)
		{
			if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_8)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~  (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~  (1u<<COM1A0);
						REG_TCCR1A |=  (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A |=  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |=  (1u<<COM1A0);
						REG_TCCR1A |=  (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A |=  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A &=~ (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_9)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{

					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |= (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |= (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_10)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |= (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~ (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |= (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B |= (1u<<WGM12);
						REG_TCCR1B &=~ (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}
			}
			else
			{
				retval = NOK;
			}
		}
		else if ((TIMER_cnfg_arr[TIMER1].MODE) == PHASECORRECTPWM)
		{
			if ((TIMER_cnfg_arr[TIMER1].COMPARE) == NOTASSIGNED)
			{
				if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_8)
				{
					if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
					{
							if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
							{
								REG_TCCR1A &=~ (1u<<COM1A0);
								REG_TCCR1A &=~ (1u<<COM1A1);
								REG_TCCR1A |= (1u<<WGM10);
								REG_TCCR1A &=~ (1u<<WGM11);
								REG_TCCR1B &=~ (1u<<WGM12);
								REG_TCCR1B &=~ (1u<<WGM13);
							}
							else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
							{
								REG_TCCR1A &=~ (1u<<COM1B0);
								REG_TCCR1A &=~ (1u<<COM1B1);
								REG_TCCR1A |= (1u<<WGM10);
								REG_TCCR1A &=~ (1u<<WGM11);
								REG_TCCR1B &=~ (1u<<WGM12);
								REG_TCCR1B &=~ (1u<<WGM13);
							}
							else
							{
								retval = NOK;
							}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A &=~ (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |= (1u<<COM1B0);
							REG_TCCR1A &=~ (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A &=~ (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A &=~ (1u<<COM1B0);
							REG_TCCR1A |= (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |= (1u<<COM1B0);
							REG_TCCR1A |= (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A &=~ (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_9)
				{
					if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A &=~ (1u<<COM1A0);
							REG_TCCR1A &=~ (1u<<COM1A1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A &=~ (1u<<COM1B0);
							REG_TCCR1A &=~ (1u<<COM1B1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A &=~ (1u<<COM1A1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |= (1u<<COM1B0);
							REG_TCCR1A &=~ (1u<<COM1B1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A &=~ (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A &=~ (1u<<COM1B0);
							REG_TCCR1A |= (1u<<COM1B1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |= (1u<<COM1B0);
							REG_TCCR1A |= (1u<<COM1B1);
							REG_TCCR1A &=~ (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].BITS) == BIT_10)
				{
					if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A &=~ (1u<<COM1A0);
							REG_TCCR1A &=~ (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A &=~  (1u<<COM1B0);
							REG_TCCR1A &=~  (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A &=~ (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |=  (1u<<COM1B0);
							REG_TCCR1A &=~  (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A &=~ (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A &=~  (1u<<COM1B0);
							REG_TCCR1A |=  (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
					{
						if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
						{
							REG_TCCR1A |= (1u<<COM1A0);
							REG_TCCR1A |= (1u<<COM1A1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
						{
							REG_TCCR1A |=  (1u<<COM1B0);
							REG_TCCR1A |=  (1u<<COM1B1);
							REG_TCCR1A |= (1u<<WGM10);
							REG_TCCR1A |= (1u<<WGM11);
							REG_TCCR1B &=~ (1u<<WGM12);
							REG_TCCR1B &=~ (1u<<WGM13);
						}
						else
						{
							retval = NOK;
						}
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}
				}
			else if ((TIMER_cnfg_arr[TIMER1].COMPARE) == OUTPUTCOMPARE)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A &=~  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A &=~  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A |=  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A |=  (1u<<COM1B1);
						REG_TCCR1A |= (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER1].COMPARE) == INPUTCOMPARE)
			{
				if ((TIMER_cnfg_arr[TIMER1].STATUS) == NORM)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A &=~  (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == TOGGLE)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A &=~ (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A &=~ (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == CLEAR)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A &=~ (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A &=~  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else if ((TIMER_cnfg_arr[TIMER1].STATUS) == SET)
				{
					if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_A)
					{
						REG_TCCR1A |= (1u<<COM1A0);
						REG_TCCR1A |= (1u<<COM1A1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else if ((TIMER_cnfg_arr[TIMER1].UNIT) == UNIT_B)
					{
						REG_TCCR1A |=  (1u<<COM1B0);
						REG_TCCR1A |= (1u<<COM1B1);
						REG_TCCR1A &=~ (1u<<WGM10);
						REG_TCCR1A |= (1u<<WGM11);
						REG_TCCR1B &=~ (1u<<WGM12);
						REG_TCCR1B |= (1u<<WGM13);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}

			}
			else
			{
				retval = NOK;
			}
		}
		break;
	case (TIMER2):

		// To check on the TOMER0 operating mode
		if ((TIMER_cnfg_arr[TIMER2].MODE) == NORMAL) {
			REG_TCCR2 &= ~(1u << WGM20);
			REG_TCCR2 &= ~ (1u << WGM21);
			if ((TIMER_cnfg_arr[TIMER2].COMPARE) == NORM)
			{
				REG_TCCR2 &= ~(1u << COM20);
				REG_TCCR2 &= ~ (1u << COM21);
			}
			// In normal mode. clear bit WGM00, bit WGM01, COM00, COM01
		 //default hardware values
			else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == TOGGLE)
			{
				REG_TCCR2 |= (1u << COM20);
				REG_TCCR2 &= ~(1u << COM21);
			}
			else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == CLEAR) {
				REG_TCCR2 |= (1u << COM21);
				REG_TCCR2 &= ~(1u << COM20);
			}
			else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == SET)
			{
				REG_TCCR2 |= (1u << COM20);
				REG_TCCR2 |= (1u << COM21);
			}
			else {
				retval = NOK;
			}

		}
		else if ((TIMER_cnfg_arr[TIMER2].MODE) == PHASECORRECTPWM) {
				REG_TCCR2 &= ~ (1u << WGM20);
				REG_TCCR2 &= ~ (1u << WGM21);
				if ((TIMER_cnfg_arr[TIMER2].COMPARE) == NORM)
				{
					REG_TCCR2 &= ~ (1u << COM20);
					REG_TCCR2 &= ~(1u << COM21);
				}

				else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == CLEAR) {
					REG_TCCR2 |= (1u << COM20);
					REG_TCCR2 &= ~(1u << COM21);
				} else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == SET) {
					REG_TCCR2 |= (1u << COM20);
					REG_TCCR2 &= ~(1u << COM21);
				} else {
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER2].MODE) == CTC)
			{
				REG_TCCR2 &= ~(1u << WGM20);
				REG_TCCR2 |=  (1u << WGM21);
				if ((TIMER_cnfg_arr[TIMER2].COMPARE) == NORM)
				{
					REG_TCCR2 |= (1u << WGM01);
					REG_TCCR2 &= ~(1u << WGM00);
				}
				if ((TIMER_cnfg_arr[TIMER2].COMPARE) == TOGGLE)
				{
					REG_TCCR2 |= (1u << COM00);
					REG_TCCR2 &= ~(1u << COM01);
				}
				else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == CLEAR)
				{
					REG_TCCR2 |= (1u << COM01);
					REG_TCCR2 &= ~(1u << COM00);
				}
				else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == SET)
				{
					REG_TCCR2 |= ((1u << COM00) | (1u << COM01));
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER2].MODE) == FASTPWM)
			{
				REG_TCCR2 |= (1u << WGM20);
				REG_TCCR2 |= (1u << WGM21);
				if ((TIMER_cnfg_arr[TIMER2].COMPARE) == NORM)
				{
					REG_TCCR2 |= (1u << WGM01);
					REG_TCCR2 &= ~(1u << WGM00);
				}
				else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == CLEAR)
				{
					REG_TCCR2 |= (1u << COM01);
					REG_TCCR2 &= ~(1u << COM00);
				}
				else if ((TIMER_cnfg_arr[TIMER2].COMPARE) == SET)
				{
					REG_TCCR2 |= ((1u << COM00) | (1u << COM01));
				}
				else
				{
					return  NOK;
				}
			}
			else
			{
				return NOK;
			}
		break;
	}
}

Std_Func_t Timer_Wait(TIMERS_t timer , uint32 value)
{
	// return value will be in milliseconds
	uint32 prescalar = 0, return_value = 0, tick_time = 0, overflow_time = 0;
	switch (timer)
	{
	case TIMER0:
		if (((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL) || ((TIMER_cnfg_arr[TIMER0].MODE) == CTC))
		{
			if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
			{
				prescalar = 1000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_8)
			{
				prescalar = 8000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_64)
			{
				prescalar = 64000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_256)
			{
				prescalar = 256000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_1024)
			{
				prescalar = 1024000;
			}
			else
			{
				prescalar = 0;
			}
		}
		else
		{
			return NOK;
		}

		break;
	case TIMER1:
		if ((((TIMER_cnfg_arr[TIMER1].MODE) == NORMAL) || (TIMER_cnfg_arr[TIMER1].MODE) == CTC))
		{
			if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
			{
				prescalar = 1000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_8)
			{
				prescalar = 8000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_64)
			{
				prescalar = 64000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_256)
			{
				prescalar = 256000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_1024)
			{
				prescalar = 1024000;
			}
			else
			{
				prescalar = 0;
			}
		}
		else
		{
			return NOK;
		}
		break;
	case TIMER2:
		if ((((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL) || (TIMER_cnfg_arr[TIMER0].MODE) == CTC))
		{
			if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
			{
				prescalar = 1000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_8)
			{
				prescalar = 8000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_32)
			{
				prescalar = 32000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_64)
			{
				prescalar = 64000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_128)
			{
				prescalar = 128000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_256)
			{
				prescalar = 256000;
			}
			else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_1024)
			{
				prescalar = 1024000;
			}
			else
			{
				prescalar = 0;
			}
		}
		else
		{

			return NOK;
		}
		break;
	default:
		return NOK;
		break;
	}
	if ((TIMER_cnfg_arr[timer].MODE) == NORMAL)
	{
		if ((TIMER_cnfg_arr[timer].clock) == INTERNAL)
		{
			overflow_time = prescalar * OVERFLOW_VALUE;
			tick_time = overflow_time / CRYSTAL_FREQ;
			return_value = value / tick_time;

		}
		else if ((TIMER_cnfg_arr[timer].clock) == EXTERNAl)
		{
			overflow_time = prescalar * OVERFLOW_VALUE;
			tick_time = overflow_time / (TIMER_cnfg_arr[timer].clock);
			return_value = value / tick_time;
		}
		else
		{
			return NOK;
		}
	}
	else if ((TIMER_cnfg_arr[timer].MODE) == CTC)
	{
		if ((TIMER_cnfg_arr[timer].clock) == INTERNAL)
		{
			overflow_time = prescalar * value;
			tick_time = overflow_time / CRYSTAL_FREQ;
			return_value =  tick_time / OVERFLOW_VALUE;
		}
		else if ((TIMER_cnfg_arr[timer].clock) == EXTERNAl)
		{
			overflow_time = prescalar * value;
			tick_time = overflow_time / (TIMER_cnfg_arr[timer].clock);
			return_value = tick_time / OVERFLOW_VALUE;
		}
		else
		{
			return NOK;
		}
	}
	while(return_value > 0)
	{
		return_value--;
	}
	return OK;
}

Std_Func_t Timer_De_Init (TIMERS_t TIMER)
{
	switch (TIMER)
	{
	case TIMER0:
		REG_TCCR0 &= ~ (1u << CS00);
		REG_TCCR0 &= ~ (1u << CS11);
		REG_TCCR0 &= ~ (1u << CS02);
		return OK;
		break;
	case TIMER1:
		REG_TCCR1B &= ~ (1u << CS10);
		REG_TCCR1B &= ~ (1u << CS11);
		REG_TCCR1B &= ~ (1u << CS12);
		return OK;
		break;
	case TIMER2:
		REG_TCCR2 &= ~ (1u << CS20);
		REG_TCCR2 &= ~ (1u << CS21);
		REG_TCCR2 &= ~ (1u << CS22);
		return OK;
		break;
	default:
		return NOK;
		break;
	}
}

Std_Func_t Timer_Start(TIMERS_t TIMER)
{
	if (TIMER == TIMER0)
	{
		if ((TIMER_cnfg_arr[TIMER0].clock) == EXTERNAl) // To check if the clock connected externally
		{
			if ((TIMER_cnfg_arr[TIMER0].EDGE) == FALLING_EDGE)
			{
				REG_TCCR0 = REG_TCCR0 | ((1u << CS01) | (1u << CS02));
				REG_TCCR0 &= ~(1u << CS00);
			}
			else if ((TIMER_cnfg_arr[TIMER0].EDGE) == RISING_EDGE)
			{
				REG_TCCR0 = REG_TCCR0| ((1u << CS00) | (1u << CS01) | (1u << CS02));
			}
			else
			{
				TIMER_cnfg_arr[TIMER0].EDGE = DEFAULT;
			}
		}
		else if ((TIMER_cnfg_arr[TIMER0].clock) == INTERNAL)
		{
			if ((TIMER_cnfg_arr[TIMER0].frequency) == CRYSTAL_FREQ)
			{
				if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
				{
					REG_TCCR0 &= ~((1u << CS01) | (1u << CS02));
					REG_TCCR0 = REG_TCCR0 | (1u << CS00);
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_8)
				{
					REG_TCCR0 &= ~((1u << CS00) | (1u << CS02));
					REG_TCCR0 = REG_TCCR0 | (1u << CS01);
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_64)
				{
					REG_TCCR0 = REG_TCCR0 | ((1u << CS00) | (1u << CS01));
					REG_TCCR0 &= ~(1u << CS02);
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_256)
				{
					REG_TCCR0 = REG_TCCR0 | (1u << CS01);
					REG_TCCR0 &= ~((1u << CS01) | (1u << CS00));
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_1024) {
					REG_TCCR0 = REG_TCCR0| ((1u << CS00) | (1u << CS02));
					REG_TCCR0 &= ~(1u<< CS01);
				}
				else {
					return  NOK;
				}
			}
		}
		else
		{
			return NOK;
		}
	}
	else if (TIMER == TIMER1)
	{
		if ((TIMER_cnfg_arr[TIMER1].clock) == INTERNAL)
		{
			if ((TIMER_cnfg_arr[TIMER0].frequency) == CRYSTAL_FREQ)
			{
				if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
				{
					REG_TCCR1B |= ((1u << CS10));
					REG_TCCR1B &= ~((1u << CS11));
					REG_TCCR1B &= ~((1u << CS12));
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_8)
				{
					REG_TCCR1B &= ~((1u << CS10));
					REG_TCCR1B |= ((1u << CS11));
					REG_TCCR1B &= ~((1u << CS12));
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_64)
				{
					REG_TCCR1B |= ((1u << CS10));
					REG_TCCR1B |= ((1u << CS11));
					REG_TCCR1B &= ~((1u << CS12));
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_256)
				{
					REG_TCCR1B &= ~((1u << CS10));
					REG_TCCR1B &= ~((1u << CS11));
					REG_TCCR1B |= ((1u << CS12));
				}
				else if ((TIMER_cnfg_arr[TIMER0].PRESCALER)== PRESCALE_1024) {
					REG_TCCR1B |= ((1u << CS10));
					REG_TCCR1B &= ~((1u << CS11));
					REG_TCCR1B |= ((1u << CS12));
				}
				else {
					return  NOK;
				}
			}
		}
		else
		{
			return NOK;
		}
	}
	else if (TIMER == TIMER2)
	{
		if ((TIMER_cnfg_arr[TIMER2].clock) == INTERNAL)
		{
			if ((TIMER_cnfg_arr[TIMER2].frequency) == CRYSTAL_FREQ)
			{
				if ((TIMER_cnfg_arr[TIMER2].PRESCALER) == NONE)
				{
					REG_TCCR2 |= ((1u << CS20));
					REG_TCCR2 &= ~((1u << CS21));
					REG_TCCR2 &= ~((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_8)
				{
					REG_TCCR2 &= ~((1u << CS20));
					REG_TCCR2 |= ((1u << CS21));
					REG_TCCR2 &= ~((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_32)
				{
					REG_TCCR2 |= ((1u << CS20));
					REG_TCCR2 |= ((1u << CS21));
					REG_TCCR2 &= ~((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_64)
				{
					REG_TCCR2 &= ~((1u << CS20));
					REG_TCCR2 &= ~((1u << CS21));
					REG_TCCR2 |= ((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_128)
				{
					REG_TCCR2 |= ((1u << CS20));
					REG_TCCR2 &= ~((1u << CS21));
					REG_TCCR2 |= ((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_256)
				{
					REG_TCCR2 &= ~((1u << CS20));
					REG_TCCR2 |= ((1u << CS21));
					REG_TCCR2 |= ((1u << CS22));
				}
				else if ((TIMER_cnfg_arr[TIMER2].PRESCALER)== PRESCALE_1024)
				{
					REG_TCCR2 |= ((1u << CS20));
					REG_TCCR2 |= ((1u << CS21));
					REG_TCCR2 |= ((1u << CS22));
				}
				else {
					return NOK;
				}
			}
			else {
				return NOK;
			}

		}
		else {
			return NOK;
		}
	}
	else
	{
		return NOK;
	}

}

Std_Func_t Generate_PWM (uint8 DC)
{
return OK;
}
