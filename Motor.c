/*
 * Motor.c
 *
 *  Created on: May 5, 2024
 *      Author: Rana Hossny
 *           Sara Hossny
 */
#include "Motor.h"
#include "Motor_config.h"


void Motor_stop(void){
    /* Stop the motor by setting all control pins to 0 */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_ENABLE_PIN | MOTOR_IN1_PIN | MOTOR_IN2_PIN, 0);
}

void Motor_enable(){
    /* Enable the motor by setting the motor enable pin to high */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_ENABLE_PIN, MOTOR_ENABLE_PIN);
}

void Motor_up(){
    /* Move the motor up by setting the direction control pin */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_IN2_PIN, 0); /* Set IN2 to low */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_IN1_PIN, MOTOR_IN1_PIN); /* Set IN1 to high */
}

void Motor_down(){
    /* Move the motor down by setting the direction control pin */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_IN1_PIN, 0); /* Set IN1 to low */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_IN2_PIN, MOTOR_IN2_PIN); /* Set IN2 to high */
}

