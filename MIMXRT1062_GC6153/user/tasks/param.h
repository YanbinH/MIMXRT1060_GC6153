/*
 * param.h
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */

#ifndef TASKS_PARAM_H_
#define TASKS_PARAM_H_

#include "fsl_common.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "queue.h"

typedef enum
{
	SYNC_DISPLAY = 1<<0,
	SYNC_CAMERA = 1<<1,
	SYNC_PXP = 1<<2,

}EventSyncInit;

extern EventGroupHandle_t g_SyncInitEvents;

extern QueueHandle_t g_QCameraMsg;


#endif /* TASKS_PARAM_H_ */
