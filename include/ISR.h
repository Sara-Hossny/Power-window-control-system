/*
 * ISR.h
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *              Sara Hossny
 */

#ifndef ISR_H_
#define ISR_H_
#include <window.h>
#include "FreeRTOS.h"
#include <queue.h>
#include <semphr.h>
#include "STD_Types.h"
#include "driverlib/gpio.h"
#include "STD_Types.h"


void GPIOA_Handler(void);
void GPIOB_Handler(void) ;
extern SemaphoreHandle_t x_Driver_UP_Semaphore;
extern SemaphoreHandle_t x_Driver_DOWN_Semaphore;
extern SemaphoreHandle_t x_Passenger_UP_Semaphore;
extern SemaphoreHandle_t x_Passenger_DOWN_Semaphore;
extern SemaphoreHandle_t x_Jam_Semaphore;
extern uint8 move_up ;
extern uint8 move_down ;
extern uint8 jam;
#endif /* ISR_H_ */
