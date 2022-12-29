/*
 * PollingRoutine.c
 *
 *  Created on: Dec 23, 2022
 *      Author: codek
 */

#include "main.h"
#include "PollingRoutine.h"

extern CAN_HandleTypeDef hcan2;

extern CanRxMsg_Struct can2_rxMsg;
extern CanTxMsg_Struct can2_txMsg;
CanTxMsgTemp_Struct canTxMsgTemp;

extern UartTxBufferStruct uart2_txMsg;
extern UartRxBufferStruct uart2_rxMsg;


/*
 * Description: Is called before main while loop. Initialize what you need here
 *
 */
void PollingInit(void)
{
	CAN_FilterInit(&hcan2);
	CAN_Start(&hcan2);

	UART_HandlerInitBuffer();

	UART_Enable_ReceiveIT(&uart2_rxMsg);


	NotifyUser(&uart2_txMsg, "MCU_Ready", true);

	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, true);
}

/*
 * Description: main while loop
 *
 */
void PollingRoutine(void)
{

	CAN_ParseMsg(&can2_rxMsg);
	CAN_SendMsg(&hcan2, &can2_txMsg);

	UART_SortRx_CHAR_Buffer(&uart2_rxMsg);
	UART_ReceiveIT_ErrorHandler(&uart2_rxMsg);

	UART_SendMessage(&uart2_txMsg, UART_PORT_2);
}

/*
 * Description: Parse any rxMsg and do whatever task
 *
 */
void CAN_ParseMsg(CanRxMsg_Struct *canMsg)
{
	if(CAN_MsgAvailable(canMsg, &canTxMsgTemp))
	{
		switch(canTxMsgTemp.header.StdId)
		{
		case 0x101:
			if(canTxMsgTemp.data[0] == 0)
			{
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET); // Amber LED
			}
			else if(canTxMsgTemp.data[0] == 1)
			{
				HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET); // Amber LED
			}
			else if(canTxMsgTemp.data[0] == 2)
			{
				canTxMsgTemp.header.StdId = 0x104;
				canTxMsgTemp.header.DLC = 3;
				canTxMsgTemp.data[0] = 0x55;
				canTxMsgTemp.data[1] = 0x99;
				canTxMsgTemp.data[2] = 0xCC;

				CAN_AddTxBuffer(&can2_txMsg, &canTxMsgTemp);
			}
			break;
		case 0x103:
			CAN_SendSomeData();
			break;
		}
	}
}


void BlinkLED(void)
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

/*
 * Description: Just loading the txMsg buffer with some data
 *
 */
void CAN_SendSomeData(void)
{
	static uint8_t counter = 0;

	canTxMsgTemp.header.StdId = 0x102;
	canTxMsgTemp.header.DLC = 8;
	canTxMsgTemp.header.IDE = CAN_ID_STD;

	canTxMsgTemp.data[0] = ++counter;
	canTxMsgTemp.data[1] = 0xAA;

	CAN_AddTxBuffer(&can2_txMsg, &canTxMsgTemp);
}


