/*
 * gc6153.c
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */


#include "gc6153.h"



static lpi2c_rtos_handle_t master_rtos_handle;


static uint8_t Rxdata;
static uint8_t slaveRxData[TRANSFER_SIZE];
static volatile uint32_t xfercnt = 0;
static uint16_t image_data[IMAGE_HIGHT*IMAGE_WIDTH];
static uint8_t pre_data[3];
static GC6153_Status img_status = Frame_Stop;
static uint16_t *pIMAGE = image_data;


static void display_process(uint16_t *data, const uint8_t *buff)
{
	uint16_t *pdst = data;
	const uint8_t *psrc = buff+8;
	for( ; psrc<buff+TRANSFER_SIZE; psrc+=8, data+=IMAGE_WIDTH)
	{
		for(; pdst<data+IMAGE_WIDTH; pdst++, psrc+=2)
		{
			*pdst = (*psrc)<<8 | *(psrc+1);
		}

	}
}



static void image_process(void)
{

	if(img_status==Recv_Line)
	{
		slaveRxData[xfercnt++]= Rxdata;
		if(xfercnt%488==0)
		{
			img_status = Frame_Start;
		}
	}

	if(Rxdata == GC6153_SYNC_HEADER23_16)
	{
		pre_data[2]=pre_data[1];
		pre_data[1]=pre_data[0];
		pre_data[0]=Rxdata;
	}

	if(pre_data[0]==GC6153_SYNC_HEADER23_16&&pre_data[1]==GC6153_SYNC_HEADER15_08
			&&pre_data[2]==GC6153_SYNC_HEADER07_00&&Rxdata!=GC6153_SYNC_HEADER23_16)
	{
		pre_data[2]=0;
		pre_data[1]=0;
		pre_data[0]=0;

		if(Rxdata==GC6153_FRAMESTART_SYNCCODE0&&img_status==Frame_Stop)
		{
			img_status=Frame_Start;
		}
		else if(Rxdata==GC6153_LINESTART_SYNCCODE1&&img_status!=Frame_Stop)
		{
			img_status = Recv_Line;
		}
		else if(Rxdata==GC6153_FRAMEEND_SYNCCODE3)
		{
			img_status=Frame_Stop;
			xfercnt = 0;
			display_process(image_data, slaveRxData);
			LPSPI_DisableInterrupts(LPSPI1, kLPSPI_RxInterruptEnable);

			static BaseType_t pxHigherPriorityTaskWoken;
			xQueueSendFromISR(g_QCameraMsg, &pIMAGE, &pxHigherPriorityTaskWoken);
			if(pdTRUE == pxHigherPriorityTaskWoken)
			{
				portYIELD_FROM_ISR(pdTRUE);
			}

		}
	}

}


void LPSPI1_IRQHandler(void)
{
	Rxdata = LPSPI_ReadData(LPSPI1);
	image_process();
}


static status_t GC6153_I2C_Transfer(uint8_t deviceAddress,
        uint32_t regAddress, size_t regAddressSize,
        uint8_t *data, size_t dataSize)
{
	status_t status;
	lpi2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = regAddress;
    masterXfer.subaddressSize = regAddressSize;
    masterXfer.data           = data;
    masterXfer.dataSize       = dataSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    status = LPI2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);

    return status;
}


static status_t GC6153_I2C_Receive(uint8_t deviceAddress,
        uint32_t regAddress, size_t regAddressSize,
        uint8_t *data, size_t dataSize)
{
	status_t status;
	lpi2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = regAddress;
    masterXfer.subaddressSize = regAddressSize;
    masterXfer.data           = data;
    masterXfer.dataSize       = dataSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;
    status = LPI2C_RTOS_Transfer(&master_rtos_handle, &masterXfer);
    return status;
}

static void GC6153_PWDN(uint8_t val)
{
    if(val)
    {
        GPIO_PinWrite(GPIO1, 26, 1);
    }
    else
    {
        GPIO_PinWrite(GPIO1, 26, 0);
    }
}



static gc6153_handler_t gc6153_handle =
{
		.i2cAddr = GC6153_I2C_ADDR,
        .i2cSend = GC6153_I2C_Transfer,
        .i2cRead = GC6153_I2C_Receive,
		.pwdn = GC6153_PWDN,
};




static void GC6153_InitPins(void)
{
	CLOCK_EnableClock(kCLOCK_Iomuxc);

	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_CCM_CLKO1, 0U);
	IOMUXC_GPR->GPR26 = ((IOMUXC_GPR->GPR26 &
	(~(BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL_MASK)))
	  | IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL(0x00U)
	);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 0xF8B0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 0xF8B0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_CCM_CLKO1, 0x10B0U);
	gpio_pin_config_t gpio_config = {
		kGPIO_DigitalOutput,
		1,
	};
    GPIO_PinInit(GPIO1, 26, &gpio_config);


	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_LPSPI1_SCK, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_LPSPI1_PCS0, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_LPSPI1_SDO, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_LPSPI1_SDI, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_LPSPI1_SCK, 0x10B0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_LPSPI1_PCS0, 0xB8B0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_LPSPI1_SDO, 0x10B0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_03_LPSPI1_SDI, 0x10B0U);

}

static void Camera_i2cinit(void)
{
	lpi2c_master_config_t masterConfig;
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = 400000;
    LPI2C_RTOS_Init(&master_rtos_handle, CAMERA_I2C_MASTER, &masterConfig, LPI2C_CLOCK_FREQUENCY);
    NVIC_SetPriority(LPI2C1_IRQn, GC6153_I2C_INTPRIORITY);
    EnableIRQ(LPI2C1_IRQn);
}


static void Camera_spiinit(void)
{
	lpspi_slave_config_t slaveConfig;
    LPSPI_SlaveGetDefaultConfig(&slaveConfig);
    LPSPI_SlaveInit(LPSPI1, &slaveConfig);
    LPSPI_EnableInterrupts(LPSPI1, kLPSPI_RxInterruptEnable);
    NVIC_SetPriority(LPSPI1_IRQn, GC6153_SPI_INTPRIORITY);
    EnableIRQ(LPSPI1_IRQn);
}




status_t GC6153_Init(void)
{
	status_t status;

	GC6153_InitPins();

    Camera_i2cinit();

    Camera_spiinit();

    status = GC6153_Open(&gc6153_handle);

    return status;
}
