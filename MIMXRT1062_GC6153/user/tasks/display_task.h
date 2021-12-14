/*
 * display_task.h
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */

#ifndef TASKS_DISPLAY_TASK_H_
#define TASKS_DISPLAY_TASK_H_

#include "fsl_common.h"
#include "FreeRTOSConfig.h"
#include "fsl_debug_console.h"
#include "elcdif_rgb.h"
#include "FreeRTOS.h"
#include "param.h"



#define DISPLAYINITTASK_PRIORITY  (configMAX_PRIORITIES - 1UL)
#define DISPLAYINITTASK_STACKSIZE 256

#define DISPLAYTASK_PRIORITY  (configMAX_PRIORITIES - 1UL)
#define DISPLAYTASK_STACKSIZE 256

void Display_Start(void);

#endif /* TASKS_DISPLAY_TASK_H_ */
