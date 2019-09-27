/*
 * DIO_LINK_cnfg.c
 *
 * Created: 9/13/2019 10:22:43 AM
 * Author : Peter
 */

#include "Registers.h"
//#include <util/delay.h>
#include "DIO_cnfg.h"
#include "DIO.h"
#include "Seven_Seg_Driver.h"
#include "LED0.h"
#include "Timer.h"

//Report_Error () a function used to report error
void Report_Error() {
	LED0_ON(); //If an error happened the led0 will turn on
}

Std_Func_t Car_Move_Forward() {
	return LED1_ON();
}
Std_Func_t Car_Move_Backward() {
	return LED2_ON();
}
Std_Func_t Car_Move_Stop() {
	return LED3_ON();
}

int main() {

	LED0_Init();
	LED1_Init();
	LED2_Init();
	LED3_Init();

	LED0_OFF();
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();

	if (Seven_Seg_Init() != OK) {
		Report_Error();
	}

	if (Timer_Init (TIMER0) != OK) {
		Report_Error();
	}


	while (1) {


		Car_Move_Forward();

		for (uint8 i = 0; i < 10; i++) {

			if (Seven_Seg_Write(i) != OK) {
				Report_Error();
			}
			//_delay_ms(500);
			Timer_Wait(TIMER0,1000);

		}

		Car_Move_Backward();

		for (sint8 i = 9; i >= 0; i--) {

			if (Seven_Seg_Write(i) != OK) {
				Report_Error();
			}
			//_delay_ms(500);
			Timer_Wait(TIMER0,1000);

		}

		Car_Move_Stop();

	}
}
