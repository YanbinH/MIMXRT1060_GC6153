/*
 * param.c
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */



#include "param.h"


/*!< Event handler used for synchronization
   bit 0  sync display
   bit 1  sync camera
   bit 2  sync pxp
*/
EventGroupHandle_t g_SyncInitEvents;




QueueHandle_t g_QCameraMsg;
