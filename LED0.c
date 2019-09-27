#include "LED0.h"

//LED_Init() a function used to initialize led0
Std_Func_t LED0_Init() {
	return DIO_init(LED0);
}

//LED_ON() a function used to turn on led0
Std_Func_t LED0_ON() {
	return DIO_write(PORT_B, PIN4, HIGH, LED0);
}

//LED_OFF() a function used to turn off led0
Std_Func_t LED0_OFF() {
	return DIO_write(PORT_B, PIN4, LOW, LED0);
}


//LED_Init() a function used to initialize led0
Std_Func_t LED1_Init() {
	return DIO_init(LED1);
}

//LED_ON() a function used to turn on led0
Std_Func_t LED1_ON() {
	return DIO_write(PORT_B, PIN5, HIGH, LED1);
}

//LED_OFF() a function used to turn off led0
Std_Func_t LED1_OFF() {
	return DIO_write(PORT_B, PIN5, LOW, LED1);
}

//LED_Init() a function used to initialize led0
Std_Func_t LED2_Init() {
	return DIO_init(LED2);
}

//LED_ON() a function used to turn on led0
Std_Func_t LED2_ON() {
	return DIO_write(PORT_B, PIN6, HIGH, LED2);
}

//LED_OFF() a function used to turn off led0
Std_Func_t LED2_OFF() {
	return DIO_write(PORT_B, PIN6, LOW, LED2);
}

//LED_Init() a function used to initialize led0
Std_Func_t LED3_Init() {
	return DIO_init(LED2);
}

//LED_ON() a function used to turn on led0
Std_Func_t LED3_ON() {
	return DIO_write(PORT_B, PIN7, HIGH, LED3);
}

//LED_OFF() a function used to turn off led0
Std_Func_t LED3_OFF() {
	return DIO_write(PORT_B, PIN7, LOW, LED3);
}

