/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: siu.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "siu.h"
#include "xpc56el.h"

/*
 * @brief	SIU pin configuration function
 *
 * @param	void
 * @retval	void
 */
void SIU_Init(void)
{
	// Configure all pins which are required for your task here

	/* TO-DO: your task implementations **************************************/


	/* Input pin configurations */

	//SIU.PCR[...].R = ...;
	SIU.PCR[52].R = 0x100;
	SIU.PCR[53].R = 0x100;
	SIU.PCR[60].R = 0x100;
	SIU.PCR[62].R = 0x100;
	SIU.PCR[54].R = 0x100;
	SIU.PCR[55].R = 0x100;



	/* Output pin configurations */

	//SIU.PCR[...].R = ...;
	SIU.PCR[56].R = 0x200;
	SIU.PCR[57].R = 0x200;
	SIU.PCR[58].R = 0x200;
	SIU.PCR[59].R = 0x200;
	SIU.PCR[43].R = 0x200;
	SIU.PCR[6].R =  0x200;




	/* Analog pin configurations */

	//SIU.PCR[...].R = ...;
	SIU.PCR[66].R = 0x2500;
	SIU.PCR[32].R = 0x2500;

	/*************************************************************************/
}

// Map function from arduino
long map(long x, long in_min, long in_max, long out_min, long out_max)
{

      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}

void leds_off(void)
{
	int leds[] = {56, 57, 58, 59, 43, 6};
	for (int i = 0; i < 6; i++) {
		SIU.GPDO[leds[i]].R = 0;
	}
	
}

void counter_leds(int counter) {

	SIU.GPDO[59].R = (counter & 0x1);
	SIU.GPDO[43].R = (counter & 0x2) >> 1;
	SIU.GPDO[6].R  = (counter & 0x4) >> 2;	

}