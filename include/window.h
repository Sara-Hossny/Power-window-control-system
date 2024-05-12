/*
 * Window_control.h
 *
 *  Created on: May 5, 2024
 *      Author: Rana Hossny
 *            Sara Hossny
 */

#ifndef INCLUDE_WINDOW_CONTROL_H_
#define INCLUDE_WINDOW_CONTROL_H_

#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "Motor_config.h"
#include "gpio_config.h"

#define DRIVER_BUTTON_UP_PIN                        GPIO_PIN_6
#define DRIVER_BUTTON_UP_PORT                       GPIO_PORTA_BASE

#define LOCK_BUTTON_PIN                        GPIO_PIN_7
#define LOCK_BUTTON__PORT                       GPIO_PORTC_BASE

#define DRIVER_BUTTON_DOWN_PIN                      GPIO_PIN_7
#define DRIVER_BUTTON_DOWN_PORT                     GPIO_PORTA_BASE

#define PASSENGER_BUTTON_UP_PIN                     GPIO_PIN_1
#define PASSENGER_BUTTON_UP_PORT                    GPIO_PORTB_BASE

#define PASSENGER_BUTTON_DOWN_PIN                   GPIO_PIN_0
#define PASSENGER_BUTTON_DOWN_PORT                  GPIO_PORTB_BASE


#define JAM_PIN                                     GPIO_PIN_5
#define JAM_PORT                                    GPIO_PORTA_BASE

#define LIMIT_SWITCH_UP                             GPIO_PIN_3
#define LIMIT_SWITCH_UP_PORT                        GPIO_PORTB_BASE


#define LIMIT_SWITCH_DOWN                           GPIO_PIN_7
#define LIMIT_SWITCH_DOWN_DOWN_PORT                 GPIO_PORTB_BASE



void Window_contorl_init(void);


#endif /* INCLUDE_WINDOW_CONTROL_H_ */
