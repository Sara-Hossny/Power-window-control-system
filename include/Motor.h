/*
 * Motor.h
 *
 *  Created on: May 5, 2024
 *      Author: Rana Hossny
 *          Sara Hossny
 */

#ifndef INCLUDE_MOTOR_H_
#define INCLUDE_MOTOR_H_
#include <stdint.h>
#include "driverlib/gpio.h"
void Motor_enable(void);
void Motor_stop(void);
void Motor_up(void);
void Motor_down(void);


#endif /* INCLUDE_MOTOR_H_ */
