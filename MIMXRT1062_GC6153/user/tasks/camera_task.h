/*
 * camera_task.h
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */

#ifndef TASKS_CAMERA_TASK_H_
#define TASKS_CAMERA_TASK_H_

#include "fsl_common.h"
#include "FreeRTOSConfig.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "param.h"
#include "gc6153.h"


#define CAMERAINITTASK_PRIORITY  (configMAX_PRIORITIES - 1UL)
#define CAMERAINITTASK_STACKSIZE 256

#define CAMERATASK_PRIORITY  (configMAX_PRIORITIES - 1UL)
#define CAMERATASK_STACKSIZE 256

void Camera_Start(void);


#endif /* TASKS_CAMERA_TASK_H_ */
