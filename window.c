/*
 * window.c
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *             Sara Hossny
 */
#include <window.h>
#include "ISR.h"

/***************************** Window Control Initialization *****************************/
/*-------------------------------------------------------------------------------------*/
void Window_contorl_init(void){
    /* Set the system clock to 80MHz */
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    /* Enable GPIO peripherals */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    /* Enable GPIOF peripheral for LED control (if DEBUG flag is enabled) */
#if DEBUG
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    /* Configure LED pin as output  */
    GPIOPinTypeGPIOOutput(LED_GPIO_BASE, LED_PIN);
#endif

    /*  Configure lock button pin (GPIOC) as input with pull-up resistor enabled */
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, LOCK_BUTTON_PIN);
    GPIOPadConfigSet(GPIO_PORTC_BASE, LOCK_BUTTON_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

     /*  Configure driver and passenger button pins (GPIOA and GPIOB) as inputs with pull-up resistors enabled */
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN|DRIVER_BUTTON_DOWN_PIN|JAM_PIN);
    GPIOPadConfigSet(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN|DRIVER_BUTTON_DOWN_PIN|JAM_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, PASSENGER_BUTTON_UP_PIN|PASSENGER_BUTTON_DOWN_PIN|LIMIT_SWITCH_UP|LIMIT_SWITCH_DOWN);
    GPIOPadConfigSet(GPIO_PORTB_BASE, PASSENGER_BUTTON_UP_PIN|PASSENGER_BUTTON_DOWN_PIN|LIMIT_SWITCH_UP|LIMIT_SWITCH_DOWN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

     /*  Configure motor control pins (GPIOA) as outputs */
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, MOTOR_ENABLE_PIN | MOTOR_IN1_PIN | MOTOR_IN2_PIN);
     /*  Turn off motor initially */
    GPIOPinWrite(GPIO_PORTA_BASE, MOTOR_ENABLE_PIN | MOTOR_IN1_PIN | MOTOR_IN2_PIN, 0);

    /* Register GPIO interrupt handlers for GPIOA and GPIOB */
    GPIOIntRegister(GPIO_PORTA_BASE, GPIOA_Handler);
    GPIOIntRegister(GPIO_PORTB_BASE, GPIOB_Handler);

    /* Set interrupt type for GPIOA pins */
    GPIOIntTypeSet(GPIO_PORTA_BASE, JAM_PIN, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN|DRIVER_BUTTON_DOWN_PIN|JAM_PIN, GPIO_FALLING_EDGE);

    /* Set interrupt type for GPIOB pins */
    GPIOIntTypeSet(GPIO_PORTB_BASE, PASSENGER_BUTTON_UP_PIN|PASSENGER_BUTTON_DOWN_PIN, GPIO_FALLING_EDGE);

    /* Enable interrupts for GPIOA and GPIOB pins */
    GPIOIntEnable(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN|DRIVER_BUTTON_DOWN_PIN|JAM_PIN);
    GPIOIntEnable(GPIO_PORTB_BASE, PASSENGER_BUTTON_UP_PIN|PASSENGER_BUTTON_DOWN_PIN);

    /* Enable master interrupt */
    IntMasterEnable();
}
