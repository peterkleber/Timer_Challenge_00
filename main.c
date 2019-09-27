/*
 * DIO_LINK_cnfg.c
 *
 * Created: 9/13/2019 10:22:43 AM
 * Author : Peter
 */

#include "Registers.h"
#include <util/delay.h>
#include "DIO_cnfg.h"
#include "DIO.h"
#include "Seven_Seg_Driver.h"


int main() {

	DIO_init(LED0);

	Seven_Seg_Init();

	while (1) {

		DIO_write(PORT_B, PIN4, HIGH, LED0); //turn on LED0
		_delay_ms(500); // delay 500 ms
		DIO_write(PORT_B, PIN4, LOW, LED0); //turn off LED0
		_delay_ms(500); //delay 500 ms

		for(uint8 i = 0 ; i < 10 ; i++){
			Seven_Seg_Write(i);
			_delay_ms(500);
		}

	}
}
