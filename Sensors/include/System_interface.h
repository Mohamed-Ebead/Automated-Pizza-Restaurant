/*
 *
 *  Created on: Dec 15, 2020
 *      Author: Mohamed  Ebead
 */

#ifndef SYSTEM_INTERFACE_H_
#define SYSTEM_INTERFACE_H_



void TempSensor_voidGPIOInit       (void);
void HumeditySensor_voidGPIOInit   (void);

void TempSensor_Start     (void);
u32  TempSensor_GetValue  (void);


void HumeditySensor_Start     (void);
u32  HumeditySensor_GetValue  (void);






#endif /* SYSTEM_INTERFACE_H_ */




