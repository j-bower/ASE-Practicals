/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-1
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"

#include "xpc56el.h"
#include "siu.h"			


/* Global variables **********************************************************/

// put any global variables you need here
int leds[] = {56, 57, 58, 59, 43, 6};
int counter = 0;
bool updateCounter = false;
bool countDir = true;

/* Task-1 implementation *****************************************************/
void task_pot(int x){

	int val = map(x, 0, 4095, 0, 6);

	leds_off();
	for (int i = 0; i < val+1; i++) {
		SIU.GPDO[leds[i]].R = 1;
	}

}

/* Task-2 implementation *****************************************************/
void task_ldr(int x){

	int val = map(x, 0, 4095, 0, 6);

	leds_off();
	for (int i = 0; i < val+1; i++) {
		SIU.GPDO[leds[i]].R = 1;
	}
}

/* Task-3 implementation *****************************************************/
void task_counter(int B1, int B2){

	if (B1) {
		countDir = true;
	}
	if (B2) {
		countDir = false;
	}
}

/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization, do not remove */
	peripheralsInit();


	/* TO-DO: your task implementations **************************************/


	/* Configure and start timer channels */	
    PIT_ConfigureTimer(1, 1000);
	PIT_StartTimer(1);

	/* main program */
	while(1){
		/* System function, do not remove */
		systemFunction();
		/* TO-DO: your task implementations **********************************/
        
		int SW1 = SIU.GPDI[52].R;
		int SW2 = SIU.GPDI[53].R;
		int SW3 = SIU.GPDI[54].R;
		int SW4 = SIU.GPDI[55].R;
		int B1  = SIU.GPDI[60].R;
		int B2  = SIU.GPDI[62].R;
		int potVal = (ADC0.CDR[5].R & 0x00000FFF);
		int ldrVal = (ADC1.CDR[3].R & 0x00000FFF);

		if (SW4) {
			updateCounter = true;
		} else {
			updateCounter = false;
		}


		if (SW1 && !SW2 && !SW3) {
			task_pot(potVal);
		} else if (!SW1 && SW2 && !SW3) {
			task_ldr(ldrVal);
		} else if (SW3 && !SW1 && !SW2) {
			task_counter(B1, B2);
		}
		else {
			leds_off();
		}

		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void){

	if (updateCounter) {
		if (countDir) {
			counter = (counter + 1) % 8;
		} else {
			counter = (counter == 0) ? 7 : (counter - 1);
		}

		counter_leds(counter);
	}	

}


/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void){

	/* TO-DO: your task implementations **************************************/


	/*************************************************************************/
}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){

	/* TO-DO: your task implementations **************************************/


	/*************************************************************************/
}
