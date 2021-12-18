/*
 * camera_task.c
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */

#include "camera_task.h"



static TaskHandle_t  s_CameraInitTaskHandle;
static TaskHandle_t  s_CameraTaskHandle;



static void Camera_Init_Task(void *param)
{
	g_SyncInitEvents = xEventGroupCreate();
	g_QCameraMsg = xQueueCreate(1, sizeof(size_t *));
	if(g_QCameraMsg == NULL)
	{
		PRINTF("[ERROR] g_QCameraMsg Create failed!");
	}

	if(kStatus_Success == GC6153_Init())
	{
		xEventGroupSetBits(g_SyncInitEvents, SYNC_CAMERA);
	}

	vTaskDelete(NULL);
}



static void Camera_Task(void *param)
{

	xEventGroupWaitBits(g_SyncInitEvents, (SYNC_CAMERA | SYNC_DISPLAY), pdTRUE, pdTRUE, portMAX_DELAY);

	while(1)
	{
		taskYIELD();
	}

}


void Camera_Start(void)
{

#if (configSUPPORT_STATIC_ALLOCATION == 1)
    if (NULL == xTaskCreateStatic(Camera_Init_Task, "Camera_Init_Task", CAMERAINITTASK_STACKSIZE, NULL, CAMERAINITTASK_PRIORITY,
                                    s_CameraInitTaskStack, &s_CameraInitTaskTCB))
#else
    if (xTaskCreate(Camera_Init_Task, "Camera_Init_Task", CAMERAINITTASK_STACKSIZE, NULL, CAMERAINITTASK_PRIORITY, &s_CameraInitTaskHandle) != pdPASS)
#endif
    {
        PRINTF("[ERROR]Camera Init created failed\r\n");

        while (1)
            ;
    }


#if (configSUPPORT_STATIC_ALLOCATION == 1)
    if (NULL == xTaskCreateStatic(Camera_Task, "Camera_Task", CAMERATASK_STACKSIZE, NULL, CAMERATASK_PRIORITY,
                                    s_CameraInitTaskStack, &s_CameraInitTaskTCB))
#else
    if (xTaskCreate(Camera_Task, "Camera_Task", CAMERATASK_STACKSIZE, NULL, CAMERATASK_PRIORITY, &s_CameraTaskHandle) != pdPASS)
#endif
    {
        PRINTF("[ERROR]Camera Task created failed\r\n");

        while (1)
            ;
    }

}
