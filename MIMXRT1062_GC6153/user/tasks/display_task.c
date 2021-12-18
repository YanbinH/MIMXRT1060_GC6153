/*
 * display_task.c
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */


#include "display_task.h"
#include "gc6153.h"


static TaskHandle_t  s_DisplayInitTaskHandle;
static TaskHandle_t  s_DisplayTaskHandle;


static uint16_t *pImgBuff;


static void Display_Init_Task(void *param)
{
	ELCDIF_Init(APP_ELCDIF);
	ELCDIF_Start(APP_ELCDIF);
	xEventGroupSetBits(g_SyncInitEvents, SYNC_DISPLAY);
	vTaskDelete(NULL);
}


static void Display_Task(void *param)
{

	xEventGroupWaitBits(g_SyncInitEvents, (SYNC_CAMERA | SYNC_DISPLAY), pdTRUE, pdTRUE, portMAX_DELAY);

    while(1)
    {
    	if(pdTRUE == xQueueReceive(g_QCameraMsg, &pImgBuff, portMAX_DELAY))
    	{
			ELCDIF_SetBuff(APP_ELCDIF, (uint16_t *)pImgBuff);
			LPSPI_EnableInterrupts(LPSPI1, kLPSPI_RxInterruptEnable);
    	}
    	taskYIELD();
    }

}




void Display_Start(void)
{

#if (configSUPPORT_STATIC_ALLOCATION == 1)
    if (NULL == xTaskCreateStatic(Display_Init_Task, "Display_Init_Task", DISPLAYINITTASK_STACKSIZE, NULL, DISPLAYINITTASK_PRIORITY,
                                    s_CameraInitTaskStack, &s_CameraInitTaskTCB))
#else
    if (xTaskCreate(Display_Init_Task, "Display_Init_Task", DISPLAYINITTASK_STACKSIZE, NULL, DISPLAYINITTASK_PRIORITY, &s_DisplayInitTaskHandle) != pdPASS)
#endif
    {
        PRINTF("[ERROR]Display Init created failed\r\n");

        while (1)
            ;
    }


#if (configSUPPORT_STATIC_ALLOCATION == 1)
    if (NULL == xTaskCreateStatic(Display_Task, "Display_Task", DISPLAYTASK_STACKSIZE, NULL, DISPLAYTASK_PRIORITY,
                                    s_CameraInitTaskStack, &s_CameraInitTaskTCB))
#else
    if (xTaskCreate(Display_Task, "Display_Task", DISPLAYTASK_STACKSIZE, NULL, DISPLAYTASK_PRIORITY, &s_DisplayTaskHandle) != pdPASS)
#endif
    {
        PRINTF("[ERROR]Display Task created failed\r\n");

        while (1)
            ;
    }

}
