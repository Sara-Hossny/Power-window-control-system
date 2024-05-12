/*
 * vTask.c
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *      Author: Sara Hossny
 */
#include "vTask.h"
#include "mode.h"
#include "led_config.h"
/***************************** Jamming Task *****************************/
/*---------------------------------------------------------------------*/
void v_Jam_Task(void* pvParameters)
{
    // Wait for the Jam semaphore to be available
    xSemaphoreTake(x_Jam_Semaphore, 0);

    for (;;) {
        /* Wait indefinitely to acquire the Jam semaphore */
        xSemaphoreTake(x_Jam_Semaphore, portMAX_DELAY);

         /* Check if there's a jam situation*/
        if (jam == 1) {
            /* Enter critical section to safely update shared variables */
            taskENTER_CRITICAL();
            {
                jam = 0;  /* Reset jam flag */
                move_down = 1;  /* Set move_down flag */
                move_up = 0; /* Reset move_up flag */
            }
            taskEXIT_CRITICAL();

             /* Enable motor and move it downwards */
            Motor_enable();
            Motor_down();

            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, LED_PIN);
            #endif

            /* Delay for motor action */
            vTaskDelay(500 / portTICK_RATE_MS);

            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, 0);
            #endif

            /* Stop motor */
            Motor_stop();
        }
    }
}

/***************************** DRIVER  (UP) Task *****************************/
/*-------------------------------------------------------------------------------------*/
void v_Driver_UP_Task(void *pvParameters)
{
    /* Wait for the Driver UP semaphore to be available */
    xSemaphoreTake(x_Driver_UP_Semaphore, 0);

    for (;;) {
        /* Wait indefinitely to acquire the Driver UP semaphore */
        xSemaphoreTake(x_Driver_UP_Semaphore, portMAX_DELAY);

        /* Enter critical section to safely update shared variable */
        taskENTER_CRITICAL();
        {
            move_up = 1; /* Set move_up flag */
        }
        taskEXIT_CRITICAL();

        /* Enable motor for UP movement */
        Motor_enable();

        /* Delay for motor action */
        vTaskDelay(3000 / portTICK_RATE_MS);

        /* Check Maunal model and stop if the limit switch up is pressed or the jam has happened */
        if ((!GPIOPinRead(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN)) && (!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_UP)) && jam == 1) {
            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, LED_PIN);
            #endif

             /* Enter critical section to safely update shared variable */
            taskENTER_CRITICAL();
            {
                move_down = 0;  /*Reset move_down flag */
            }
            taskEXIT_CRITICAL();

            /* Move motor UP */
            Motor_up();

             /* Wait until conditions are met to stop UP movement */
            while ((!GPIOPinRead(GPIO_PORTA_BASE, DRIVER_BUTTON_UP_PIN)) && (!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_UP)) && jam == 1);

            #if DEBUG
             /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, 0);
            #endif
        }
        /* check auto mode and stop if the limit switch up is pressed or the jam has happened */
        else if ((!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_UP)) && jam == 1) {
            uint32 i = 1000000;
            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, LED_PIN);
            #endif

            /* Enter critical section to safely update shared variable */
            taskENTER_CRITICAL();
            {
                move_down = 0;  /* Reset move_down flag */
            }
            taskEXIT_CRITICAL();

            /* Move motor UP */
            Motor_up();

            /* Wait until conditions are met to stop UP movement or timeout */
            while ((!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_UP)) && (i > 0) && (jam == 1)) {
                i--;
            }

            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, 0);
            #endif
        }
        else {
             /* Reset move_up flag */
            taskENTER_CRITICAL();
            {
                move_up = 0;
            }
            taskEXIT_CRITICAL();
        }

        /* Stop motor */
        Motor_stop();
        /* Reset jam flag */
        jam = 0;
    }
}

/***************************** DRIVER  (DOWN) Task *****************************/
/*-------------------------------------------------------------------------------------*/
void v_Driver_Down_Task(void *pvParameters)
{
    /* Wait for the Driver DOWN semaphore to be available */
    xSemaphoreTake(x_Driver_DOWN_Semaphore, 0);

    for (;;) {
        /* Wait indefinitely to acquire the Driver DOWN semaphore */
        xSemaphoreTake(x_Driver_DOWN_Semaphore, portMAX_DELAY);

        /* Enter critical section to safely update shared variable */
        taskENTER_CRITICAL();
        {
            move_down = 1; /* Set move_down flag */
        }
        taskEXIT_CRITICAL();

        /* Enable motor for DOWN movement */
        Motor_enable();

        /* Delay for motor action */
        vTaskDelay(3000 / portTICK_RATE_MS);

        /* Check Maunal model and stop if the limit switch down is pressed */
        if ((!GPIOPinRead(GPIO_PORTA_BASE, DRIVER_BUTTON_DOWN_PIN)) && (!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_DOWN))) {
            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, LED_PIN);
            #endif

            /* Enter critical section to safely update shared variable */
            taskENTER_CRITICAL();
            {
                move_up = 0; /* Reset move_up flag */
            }
            taskEXIT_CRITICAL();

            /* Move motor DOWN */
            Motor_down();

            /* Wait until conditions are met to stop DOWN movement */
            while ((!GPIOPinRead(GPIO_PORTA_BASE, DRIVER_BUTTON_DOWN_PIN)) && (!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_DOWN)));

            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, 0);
            #endif
        }
         /* check auto mode and stop if the limit switch down is pressed */
        else if ((!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_DOWN))) {
            uint32 i = 1000000;
            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, LED_PIN);
            #endif

            /* Enter critical section to safely update shared variable */
            taskENTER_CRITICAL();
            {
                move_up = 0; /* Reset move_up flag */
            }
            taskEXIT_CRITICAL();

            /* Move motor DOWN */
            Motor_down();

            /* Wait until conditions are met to stop DOWN movement or timeout */
            while ((!GPIOPinRead(GPIO_PORTB_BASE, LIMIT_SWITCH_DOWN)) && (i > 0)) {
                i--;
            }

            #if DEBUG
            /* Toggle debug LED */
            GPIOPinWrite(LED_GPIO_BASE, LED_PIN, 0);
            #endif
        }
        else {
            /* Reset move_down flag */
            taskENTER_CRITICAL();
            {
                move_down = 0;
            }
            taskEXIT_CRITICAL();
        }

        /* Stop motor */
        Motor_stop();
    }
}
