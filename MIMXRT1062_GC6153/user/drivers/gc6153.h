/*
 * gc6153.h
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */

#ifndef DRIVERS_GC6153_H_
#define DRIVERS_GC6153_H_

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_lpi2c_freertos.h"
#include "fsl_lpi2c.h"
#include "camera_gc6153.h"
#include "fsl_gpio.h"
#include "fsl_lpspi.h"
#include "param.h"
#include "FreeRTOS.h"
#include "fsl_debug_console.h"



#define CAMERA_I2C_MASTER LPI2C1
#define LPI2C_CLOCK_FREQUENCY 10000000U
#define GC6153_I2C_INTPRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#define GC6153_SPI_INTPRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)
#define IMAGE_WIDTH 240
#define IMAGE_HIGHT 320
#define TRANSFER_SIZE IMAGE_HIGHT*488//157453
#define BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL_MASK 0x04000000U /*!< GPIO1 and GPIO6 share same IO MUX function, GPIO_MUX1 selects one GPIO function: affected bits mask */



typedef enum
{
	Frame_Start,
	Line_Start,
	Recv_Line,
	Frame_Stop

}GC6153_Status;



status_t GC6153_Init(void);

#endif /* DRIVERS_GC6153_H_ */
