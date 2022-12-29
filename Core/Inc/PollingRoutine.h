/*
 * PollingRoutine.h
 *
 *  Created on: Dec 23, 2022
 *      Author: codek
 */

#ifndef INC_POLLINGROUTINE_H_
#define INC_POLLINGROUTINE_H_

#include "main.h"

void PollingInit(void);
void PollingRoutine(void);

void CAN_ParseMsg(CanRxMsg_Struct *canMsg);


void BlinkLED(void);
void DebouncePB(void);

void CAN_SendSomeData(void);

#endif /* INC_POLLINGROUTINE_H_ */
