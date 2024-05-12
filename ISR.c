/*
 * ISR.c
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *              Sara Hossny
 */


/***************************** PORTA ISR *****************************/
#include "ISR.h"
void GPIOA_Handler(void) {
    /* Declare a variable to track if a higher priority task should be woken */
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* Read the status of interrupts on GPIO port A */
    uint8 state = GPIOIntStatus(GPIO_PORTA_BASE, true);

    /* Check if the interrupt was triggered by the JAM_PIN */
    if (state == JAM_PIN) {
        /* Give a semaphore to indicate JAM_PIN interrupt */
        xSemaphoreGiveFromISR(x_Jam_Semaphore, &xHigherPriorityTaskWoken);
    }

    /* Check if the interrupt was triggered by DRIVER_BUTTON_UP_PIN */
    else if ((state == DRIVER_BUTTON_UP_PIN) && (move_up == 0)) {
        /* Set 'jam' flag to 1 */
        jam = 1;
        /* Give a semaphore to indicate DRIVER_BUTTON_UP_PIN interrupt */
        xSemaphoreGiveFromISR(x_Driver_UP_Semaphore, &xHigherPriorityTaskWoken);
    }

    /* Check if the interrupt was triggered by DRIVER_BUTTON_DOWN_PIN */
    else if ((state == DRIVER_BUTTON_DOWN_PIN) && (move_down == 0)) {
        /* Give a semaphore to indicate DRIVER_BUTTON_DOWN_PIN interrupt */
        xSemaphoreGiveFromISR(x_Driver_DOWN_Semaphore, &xHigherPriorityTaskWoken);
    }

    /* No action required for other interrupt states */
    else {
        /* MISRA rule */
    }

    /* Clear interrupt flags for DRIVER_BUTTON_UP_PIN, DRIVER_BUTTON_DOWN_PIN, and JAM_PIN */
    GPIOIntClear(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN | DRIVER_BUTTON_DOWN_PIN | JAM_PIN);

    /* End the interrupt service routine, potentially waking up higher priority tasks */
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/***************************** PORTB ISR *****************************/

void GPIOB_Handler(void) {

    /* Declare a variable to track if a higher priority task should be woken */
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* Read the status of interrupts on GPIO port B */
    uint8 state = GPIOIntStatus(GPIO_PORTB_BASE, true);

    /* Check if the interrupt was triggered by PASSENGER_BUTTON_UP_PIN */
    /* and if the move_up is not ongoing and LOCK_BUTTON_PIN is not pressed */
    if ((state == PASSENGER_BUTTON_UP_PIN) && (move_up == 0) && (GPIOPinRead(GPIO_PORTC_BASE, LOCK_BUTTON_PIN) != 0)) {
        /* Set 'jam' flag to 1 */
        jam = 1;
        /* Give a semaphore to indicate PASSENGER_BUTTON_UP_PIN interrupt */
        xSemaphoreGiveFromISR(x_Passenger_UP_Semaphore, &xHigherPriorityTaskWoken);
    }

    /* Check if the interrupt was triggered by PASSENGER_BUTTON_DOWN_PIN */
    /* and if the move_down is not ongoing and LOCK_BUTTON_PIN is not pressed */
    else if ((state == PASSENGER_BUTTON_DOWN_PIN) && (move_down == 0) && (GPIOPinRead(GPIO_PORTC_BASE, LOCK_BUTTON_PIN) != 0)) {
        /* Give a semaphore to indicate PASSENGER_BUTTON_DOWN_PIN interrupt*/
        xSemaphoreGiveFromISR(x_Passenger_DOWN_Semaphore, &xHigherPriorityTaskWoken);
    }

    /* No action required for other interrupt states */
    else {
        /* MISRA rule */
    }

    /* Clear interrupt flags for PASSENGER_BUTTON_UP_PIN and PASSENGER_BUTTON_DOWN_PIN */
    GPIOIntClear(GPIO_PORTB_BASE, PASSENGER_BUTTON_UP_PIN | PASSENGER_BUTTON_DOWN_PIN);

    /* End the interrupt service routine, potentially waking up higher priority tasks */
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

