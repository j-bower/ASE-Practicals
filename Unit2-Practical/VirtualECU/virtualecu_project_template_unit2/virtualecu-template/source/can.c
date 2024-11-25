/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "can.h"
#include "xpc56el.h"

/*
 * @brief	CAN0 initialization function
 *
 * @param	void
 * @retval	void
 */
void CAN_Init(void){
	can_lld_start(&CAND1, &can_config_cfg0);


	/* TO-DO: pre-configure message buffer(s) for sending here ***********************/

	// Engine On buffer
	CAN_0.BUF[10].MSG_CS.B.IDE = 1;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */
	CAN_0.BUF[10].MSG_ID.B.STD_ID = 0;		/* Message ID for standard frame */
	CAN_0.BUF[10].MSG_ID.B.EXT_ID = 0xD40;		/* Message ID for extended frame*/
	CAN_0.BUF[10].MSG_CS.B.RTR = 0;		/* Remote Transmission Request; 0 = Data Frame */
	CAN_0.BUF[10].CS.B.LENGTH = 0;			/* Length of Payload, 0 - 8*/

	// Start/Stop Engine Buffer
	// Speed Buffer
	// Lights Buffer
	// RPM Buffer

	/*************************************************************************/
}


/*
 * @brief	CAN message transmit function
 *
 * @param	CANTxFrame	txMsg
 * @param	canmbx_t	mbx
 * @retval	void
 */
void CAN_TxMessage(CANTxFrame txMsg, canmbx_t mbx){
	// nop
}