/*
 * elcdif_rgb.c
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */


#include "elcdif_rgb.h"



static uint16_t displaybuff[APP_IMG_HEIGHT*APP_IMG_WIDTH];


static void ELCDIF_InitPins(void)
{

	CLOCK_EnableClock(kCLOCK_Iomuxc);

	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LCD_CLK, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LCD_ENABLE, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LCD_HSYNC, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LCD_VSYNC, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LCD_DATA00, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LCD_DATA01, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_LCD_DATA02, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_LCD_DATA03, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LCD_DATA04, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LCD_DATA05, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_LCD_DATA06, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_LCD_DATA07, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_LCD_DATA08, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_LCD_DATA09, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_LCD_DATA10, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_LCD_DATA11, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LCD_DATA12, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LCD_DATA13, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LCD_DATA14, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LCD_DATA15, 1U);


	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_GPIO2_IO31, 1U);
	IOMUXC_GPR->GPR27 = ((IOMUXC_GPR->GPR27 &
	(~(ELCDIF_INITPINS_IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL_MASK)))
	  | IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL(0x00U)
	);


    gpio_pin_config_t config = {
        kGPIO_DigitalOutput,
        0,
        kGPIO_NoIntmode,
    };

    /* Backlight. */
    config.outputLogic = 1;
    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);

}

void ELCDIF_Init(LCDIF_Type *base)
{

	ELCDIF_InitPins();

    const elcdif_rgb_mode_config_t config = {
        .panelWidth    = APP_IMG_WIDTH,
        .panelHeight   = APP_IMG_HEIGHT,
        .hsw           = APP_HSW,
        .hfp           = APP_HFP,
        .hbp           = APP_HBP,
        .vsw           = APP_VSW,
        .vfp           = APP_VFP,
        .vbp           = APP_VBP,
        .polarityFlags = APP_POL_FLAGS,
        .bufferAddr    = (uint32_t)NULL,
        .pixelFormat   = kELCDIF_PixelFormatRGB565,
        .dataBus       = APP_LCDIF_DATA_BUS,
    };

#if (defined(APP_ELCDIF_HAS_DISPLAY_INTERFACE) && APP_ELCDIF_HAS_DISPLAY_INTERFACE)
    BOARD_InitDisplayInterface();
#endif

    ELCDIF_RgbModeInit(base, &config);

}


void ELCDIF_Start(LCDIF_Type *base)
{
	ELCDIF_RgbModeStart(base);
}




void ELCDIF_SetBuff(LCDIF_Type *base, const uint16_t *buff)
{

	for(uint32_t i=0; i<LCD_IMG_HEIGHT; i++)
	{
		for(uint32_t j=0; j<LCD_IMG_WIDTH; j++)
		{
			displaybuff[2*LCD_IMG_WIDTH*(LCD_IMG_WIDTH-1-j)+i] = buff[i*LCD_IMG_WIDTH+j];
		}
	}

    ELCDIF_SetNextBufferAddr(base, displaybuff);
}
