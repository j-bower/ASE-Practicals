/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"


/* Global variables **********************************************************/
int speed = 0;
int rpm = 8000;
int lightData = 0;
bool rpmDirection = false;
bool engineOn = false; 


void can_send_engine_on(void){

	/* TO-DO: your task implementations **************************************/

    // set payload bytes, if necessary
    //CAN_0.BUF[10].DATA.B[0] = 0;

	// write the correct CODE value to this register to instruct the CAN controller to transmit the CAN message
	CAN_0.BUF[10].CS.B.CODE = 0xC;
}

void can_send_speed(int value){
	
	int speed = map(value, 0, 4095, 0, 240);
	CAN_0.BUF[9].DATA.B[0] = speed;
	CAN_0.BUF[9].CS.B.CODE = 0xC;

}

void can_send_rpm(int value){
	
	uint8_t upper = (value >> 8) & 0xFF;
	uint8_t lower = value & 0xFF;
	CAN_0.BUF[8].DATA.B[0] = lower;
	CAN_0.BUF[8].DATA.B[1] = upper;
	CAN_0.BUF[8].CS.B.CODE = 0xC;

}

void can_send_lights(void){

	if (SW1 && SW2) {
		lightData = 3;
	} else if (SW1) {
		lightData = 2;
	} else if (SW2) {
		lightData = 1;
	} else {
		lightData = 0;
	}
	CAN_0.BUF[11].DATA.B[0] = lightData;
	CAN_0.BUF[11].CS.B.CODE = 0xC;

}

void can_send(void){

	if (engineOn) {
		can_send_engine_on();
		can_send_speed(POT);
		can_send_rpm(rpm);
		can_send_lights();
		osalThreadDelayMilliseconds(100UL);
	}

}


/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization */
	peripheralsInit();



	/* TO-DO: your task implementations **************************************/

	/* Configure and start timer channels */
	/* PIT timer channel 1, period = 1000 ms */
    PIT_ConfigureTimer(1, 1000);
	PIT_ConfigureTimer(2, 500);
	PIT_StartTimer(1);
	PIT_StartTimer(2);

	/*************************************************************************/


	/* main program */
	while(1){
		/* System function */
		systemFunction();

		/* TO-DO: your task implementations **********************************/

		can_send();

		

		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	CAN receive interrupt
 *
 * @param   CANDriver   canp	The CAN controller which received a message
 * @param	CANRxFrame	crfp	The message which was received
 * @retval	void
 */
void can_receive(CANRxFrame crfp) {
    if(crfp.IDE == CAN_IDE_STD) // a standard message frame has been received
    {
        /* TO-DO: your task implementations ******************************/
        if (crfp.SID == 0x11) {
			LED_P = 1;
			engineOn = true;
        } else if (crfp.SID == 0x10) {
			engineOn = false;
			LED_P = 0;
		}
    }
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void){

	if (rpm == 0) {
		rpmDirection = true;
	} else if (rpm == 8000) {
		rpmDirection = false;
	}

	if (rpmDirection) {
		rpm += 250;
	} else {
		rpm -= 250;
	}
}


/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void){
	
	switch (lightData)
	{
	case 3:
		LED_U1 = !LED_U1;
		LED_U3 = LED_U1;
		break;
	
	case 2:
		LED_U1 = 0;
		LED_U3 = !LED_U3;
		break;
	
	case 1:
		LED_U1 = !LED_U1;
		LED_U3 = 0;
		break;

	default:
		LED_U1 = 0;
		LED_U3 = 0;
		break;
	}

}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){
	/* TO-DO: your task implementations **************************************/


}
