/*
 * CAN_Handler.h
 *
 *  Created on: Dec 23, 2022
 *      Author: codek
 */

#ifndef INC_CAN_HANDLER_H_
#define INC_CAN_HANDLER_H_

#include "main.h"

void CAN_FilterInit(CAN_HandleTypeDef *hcan);
int CAN_Start(CAN_HandleTypeDef *hcan);

void CAN_SendMsg(CAN_HandleTypeDef *hcan, CanTxMsg_Struct *canMsg);

#endif /* INC_CAN_HANDLER_H_ */
