/*
 * elcdif_rgb.h
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */

#ifndef DRIVERS_ELCDIF_RGB_H_
#define DRIVERS_ELCDIF_RGB_H_


#include "fsl_common.h"
#include "fsl_elcdif.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"


#define APP_ELCDIF 	   LCDIF
#define APP_IMG_HEIGHT 272
#define APP_IMG_WIDTH  480
#define APP_HSW        41
#define APP_HFP        4
#define APP_HBP        8
#define APP_VSW        10
#define APP_VFP        4
#define APP_VBP        2
#define APP_POL_FLAGS \
    (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)
#define APP_LCDIF_DATA_BUS kELCDIF_DataBus16Bit

#define LCD_IMG_HEIGHT 320
#define LCD_IMG_WIDTH  240

#define LCD_BL_GPIO     GPIO2
#define LCD_BL_GPIO_PIN 31
#define ELCDIF_INITPINS_IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL_MASK 0x80000000U


void ELCDIF_Init(LCDIF_Type *base);
void ELCDIF_Start(LCDIF_Type *base);
void ELCDIF_SetBuff(LCDIF_Type *base, const uint16_t *buff);



#endif /* DRIVERS_ELCDIF_RGB_H_ */
