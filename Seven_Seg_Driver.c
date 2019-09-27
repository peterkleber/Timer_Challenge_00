/*
 * Seven_Seg_Driver.c
 *
 * Created: 9/20/2019
 *  Author: Peter Kleber
 */
#include"Seven_Seg_Driver.h"

uint8 CD4511B_Output_Values [10][4] = { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 0, 1, 0, 0 },
		{ 1, 1, 0, 0 }, { 0, 0, 1, 0 }, { 1, 0, 1, 0 },
		{ 0, 1, 1, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 1 },
		{ 1, 0, 0, 1 } };

Std_Func_t Seven_Seg_Init(){

	uint8 retval = OK ;

	if(DIO_init(CD4511B_Pin_A) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_B) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_C) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_D) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_EN1) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_EN2) != OK){
		retval = NOK ;
	}

	if(DIO_init(CD4511B_Pin_DP) != OK){
		retval = NOK ;
	}

	return retval;

}


uint8 Seven_Seg_Write(uint8 num_to_display) {

	if ((num_to_display > 0) || (num_to_display < 9)) {
		DIO_write(CD4511B_Pin_EN1_PORT, CD4511B_Pin_EN1_Pin, HIGH, CD4511B_Pin_EN1);
		DIO_write(CD4511B_Pin_EN2_PORT, CD4511B_Pin_EN2_Pin, LOW,CD4511B_Pin_EN2);
		DIO_write(CD4511B_Pin_DP_PORT, CD4511B_Pin_DP_Pin, LOW,CD4511B_Pin_DP);

		DIO_write(CD4511B_Pin_A_PORT, CD4511B_Pin_A_PIN,
				CD4511B_Output_Values[num_to_display][0], CD4511B_Pin_A);
		DIO_write(CD4511B_Pin_B_PORT, CD4511B_Pin_B_PIN,
				CD4511B_Output_Values[num_to_display][1], CD4511B_Pin_B);
		DIO_write(CD4511B_Pin_C_PORT, CD4511B_Pin_C_PIN,
				CD4511B_Output_Values[num_to_display][2], CD4511B_Pin_C);
		DIO_write(CD4511B_Pin_D_PORT, CD4511B_Pin_D_PIN,
				CD4511B_Output_Values[num_to_display][3], CD4511B_Pin_D);
		return OK;
	} else {
		return NOK;
	}
}

