/*
 * Seven_Seg_Driver.h
 *
 * Created: 9/20/2019
 *  Author: Peter Kleber
 */
#ifndef SEVEN_SEG
#define SEVEN_SEG

#include "DIO.h"
#include "Registers.h"

#define CD4511B_Pin_A_PIN PIN0
#define CD4511B_Pin_A_PORT PORT_B

#define CD4511B_Pin_B_PIN PIN1
#define CD4511B_Pin_B_PORT PORT_B

#define CD4511B_Pin_C_PIN PIN2
#define CD4511B_Pin_C_PORT PORT_B

#define CD4511B_Pin_D_PIN PIN3
#define CD4511B_Pin_D_PORT PORT_B

#define CD4511B_Pin_EN1_Pin PIN2
#define CD4511B_Pin_EN1_PORT PORT_D

#define CD4511B_Pin_EN2_Pin PIN3
#define CD4511B_Pin_EN2_PORT PORT_D

#define CD4511B_Pin_DP_Pin PIN4
#define CD4511B_Pin_DP_PORT PORT_D


Std_Func_t Seven_Seg_Init(void);
Std_Func_t Seven_Seg_Write(uint8 num_to_display );

#endif
