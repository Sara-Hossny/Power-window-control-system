
/*
 * main.c
 *
 *  Created on: May 12, 2024
 *      Author: Rana Hossny
 *      Author: Sara Hossny
 */

#include "vTask.h"

/********************* Driver Semaphore Handles **************************/

/* Semaphore for Driver up */
SemaphoreHandle_t x_Driver_UP_Semaphore;

/* Semaphore for Driver down */
SemaphoreHandle_t x_Driver_DOWN_Semaphore;


/******************** Passenger Semaphore Handles ********************/

/* Semaphore for Passenger up */
SemaphoreHandle_t x_Passenger_UP_Semaphore;

/* Semaphore for Passenger down */
SemaphoreHandle_t x_Passenger_DOWN_Semaphore;

/******************** Jam Semaphore Handle ********************/

/* Semaphore for Jamming */
SemaphoreHandle_t x_Jam_Semaphore;

/***************************** Semaphore Handle *****************************/

/* Mutex Semaphore for synchronization */
xSemaphoreHandle xMutex;

/* Task handles for Driver, Passenger, and Jam tasks */
xTaskHandle Driver_up_Handle;
xTaskHandle Passenger_up_Handle;
xTaskHandle Passenger_down_Handle;
xTaskHandle Jam_Handle;

/* Variables to track movement states */
uint8 move_up = 0; /* Indicates if the window is moving up */
uint8 move_down = 0; /* Indicates if the window is moving down */
uint8 jam = 0; /* Indicates if there's a jam situation */


int main(void) {
    /* Initialize the peripheral for window control */
    Window_contorl_init();

    /* Create Semaphores for each task */
    vSemaphoreCreateBinary(x_Driver_UP_Semaphore);            /* Semaphore for Driver up */
    vSemaphoreCreateBinary(x_Driver_DOWN_Semaphore);          /* Semaphore for Driver down */
    vSemaphoreCreateBinary(x_Passenger_UP_Semaphore);         /* Semaphore for Passenger up */
    vSemaphoreCreateBinary(x_Passenger_DOWN_Semaphore);       /* Semaphore for Passenger down */
    vSemaphoreCreateBinary(x_Jam_Semaphore);                  /* Semaphore for Jamming */

    /* Check if Semaphore creation was successful */
    if ((x_Driver_UP_Semaphore && x_Driver_DOWN_Semaphore && x_Passenger_UP_Semaphore &&
         x_Passenger_DOWN_Semaphore && x_Jam_Semaphore) != NULL) {

        /* Create Jamming Task and configure it as highest priority */
        xTaskCreate(v_Jam_Task, "v_Jam_Task", 150, NULL, 4, Jam_Handle);

        /* Create Driver’s Tasks and configure their priorities */
        xTaskCreate(v_Driver_UP_Task, "v_Driver_UP_Task", 150, NULL, 3, &Driver_up_Handle);
        xTaskCreate(v_Driver_Down_Task, "v_Driver_Down_Task", 150, NULL, 3, NULL);

        /* Create shotgun’s Tasks and configure their priorities as lowest priority */
        xTaskCreate(v_Passenger_UP_Task, "v_Passenger_UP_Task", 150, NULL, 2, &Passenger_up_Handle);
        xTaskCreate(v_Passenger_Down_Task, "v_Passenger_Down_Task", 150, NULL, 2, &Passenger_down_Handle);
    }

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Infinite loop to keep the program running */
    for (;;) ;
}
