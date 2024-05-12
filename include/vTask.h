/*
 * vTask.h
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *              Sara Hossny
 */


#ifndef VTASK_H_
#define VTASK_H_
#include"STD_Types.h"
#include "FreeRTOS.h"
#include "task.h"
#include <queue.h>
#include <semphr.h>
#include "Motor.h"
#include "window.h"
void v_Jam_Task(void* pvParameters);
void v_Driver_UP_Task(void *pvParameters);
void v_Driver_Down_Task(void *pvParameters);
void v_Passenger_UP_Task(void *pvParameters);
void v_Passenger_Down_Task(void *pvParameters);
extern SemaphoreHandle_t x_Driver_UP_Semaphore;
extern SemaphoreHandle_t x_Driver_DOWN_Semaphore;
extern SemaphoreHandle_t x_Passenger_UP_Semaphore;
extern SemaphoreHandle_t x_Passenger_DOWN_Semaphore;
extern SemaphoreHandle_t x_Jam_Semaphore;
extern xSemaphoreHandle xMutex;
extern uint8 move_up ;
extern uint8 move_down ;
extern uint8 jam;


#endif /* VTASK_H_ */
