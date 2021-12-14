/*
 * camera_gc6153.c
 *
 *  Created on: Dec 14, 2021
 *      Author: nxf75461
 */


#include "camera_gc6153.h"





static status_t I2C_Write_GC6153_Reg(gc6153_handler_t *handle, uint8_t addr, uint8_t reg, uint8_t value)
{
    handle->i2cSend(addr, reg, 1, &value, 1);
    return kStatus_Success;
}

static status_t I2C_Read_GC6153_Reg(gc6153_handler_t *handle, uint8_t addr, uint8_t reg, uint8_t *value, uint8_t size)
{
    handle->i2cRead(addr, reg, 1, value, size);
    return kStatus_Success;
}



 void GC6153_Initial_Setting(gc6153_handler_t *handle)
 {

		/*SYS*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0xa0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0xa0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0xa0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfa, 0x11);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfc, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xf6, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfc, 0x12); //1a herve 20181207

		/*ANALOG & CISCTL*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x01, 0x40);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x02, 0x12);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x0d, 0x40);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x14, MIRROR);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x16, AD_NUM);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x17, COL_SWITCH);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x1c, 0x31);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x1d, 0xbb);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x24, 0x55);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x1f, 0x3f);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x73, 0x20);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x74, 0x71);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x77, 0x22);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x7a, 0x08);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x11, 0x18);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x13, 0x48);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x12, 0xc8);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x70, 0xc8);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x7b, 0x18);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x7d, 0x30);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x7e, 0x02);

		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x10);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x10);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);

		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x49, 0x61);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x4a, 0x40);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x4b, 0x58);

		/*ISP*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x39, 0x02);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x3a, 0x80);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x20, 0x7e);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x26, 0x87);

		/*BLK*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x33, 0x10);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x37, 0x06);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x2a, 0x21);

		/*GAIN*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x3f, 0x16);

		/*DNDD*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x52, 0xa6);///ab-0909    //a6   0917
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x53, 0x81);///81-0909   //84  0917
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x54, 0x43);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x56, 0x78);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x57, 0xaa);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x58, 0xff);

		/*ASDE*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x5b, 0x60);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x5c, 0x50);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xab, 0x2a);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xac, 0xb5);

		/*INTPEE*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x5e, 0x06);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x5f, 0x06);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x60, 0x44);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x61, 0xff);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x62, 0x69);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x63, 0x13);///13-0909   //14   0917

		/*CC*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x65, 0x13);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x66, 0x26);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x67, 0x07);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x68, 0xf5);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x69, 0xea);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x6a, 0x21);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x6b, 0x21);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x6c, 0xe4);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x6d, 0xfb);

		/*YCP*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x81, 0x3b);///3b-0909
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x82, 0x3b);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x83, 0x4b);///4b-0909    50   0917
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x84, 0x90);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x86, 0xf0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x87, 0x1d);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x88, 0x16);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x8d, 0x74);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x8e, 0x25);

		/*AEC*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x90, 0x36);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x92, 0x43);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x9d, 0x32);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x9e, 0x81);//81   0917
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x9f, 0xf4);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xa0, 0xa0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xa1, 0x04);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xa3, 0x2d);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xa4, 0x01);

		/*AWB*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb0, 0xc2);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb1, 0x1e);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb2, 0x10);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb3, 0x20);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb4, 0x2d);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb5, 0x1b);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb6, 0x2e);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xb8, 0x13);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xba, 0x60);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xbb, 0x62);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xbd, 0x78);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xbe, 0x55);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xbf, 0xa0);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc4, 0xe7);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc5, 0x15);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc6, 0x16);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc7, 0xeb);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc8, 0xe4);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xc9, 0x16);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xca, 0x16);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xcb, 0xe9);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x22, 0xf8);

		/*SPI*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x02);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x01, 0x01);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x02, 0x80);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x03, 0x20);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x04, 0x20);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x0a, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x13, 0x10);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x24, 0x00);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0x28, 0x03);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);

		/*OUTPUT*/
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xf2, 0x03);
		I2C_Write_GC6153_Reg(handle, handle->i2cAddr, 0xfe, 0x00);

 }


 /**
  * @brief
  * @param[in]  None
  * @retval None
  */

void GC6153_Set_Clock(gc6153_handler_t *handle, GC6153_SERIALSensor* cmos_senser, uint32_t InternalClock)
{
    if (cmos_senser->InternalClock == InternalClock)
    {
        return;
    }
    cmos_senser->InternalClock = InternalClock;
    uint8_t ClkDiv;
    /* add PLL comment here */
    switch (InternalClock)
    {
		case GC6153_SERIAL_MCLK / 2:
			ClkDiv = 0x00;
			break; /* pclk = mclk */
		case GC6153_SERIAL_MCLK / 4:
			ClkDiv = 0x11;
			break; /* pclk = mclk / 2 */
		case GC6153_SERIAL_MCLK / 8:
			ClkDiv = 0x32;
			break; /* pclk = mclk / 4 */
		default:
			return;
			break;
     }
    I2C_Write_GC6153_Reg(handle, handle->i2cAddr,  0xfa, ClkDiv);
}


/**
  * @brief This function initialize the registers of CMOS sensor
  * @note    the output format should be YUV422, order: YUYV
*            data output should be at pclk falling edge
*            VSYNC should be low active
*            HSYNC should be hight active
  * @param[in]  None
  * @retval sensor Id
  */

void GC6153_Power_On(gc6153_handler_t *handle)
{
    handle->pwdn(0);
    //handle->delayMs(1);

}

/**
  * @brief   This function initialize the registers of CMOS sensor
  * @note    the output format should be YUV422, order: YUYV
*            data output should be at pclk falling edge
*            VSYNC should be low active
*            HSYNC should be hight active
  * @param[in]  None
  * @retval None
  */
void GC6153_Power_Down(gc6153_handler_t *handle)
{
    handle->pwdn(1);
    //handle->delayMs(1);
}


int32_t GC6153_Check_Id(gc6153_handler_t *handle)
{
    int32_t SensorId;
    uint8_t u8TempVal0 = 0 ,u8TempVal1 = 0;

    handle->pwdn(0);
    //handle->delayMs(1);

    I2C_Read_GC6153_Reg(handle, handle->i2cAddr, 0xf0, &u8TempVal0, 1);
    I2C_Read_GC6153_Reg(handle, handle->i2cAddr, 0xf1, &u8TempVal1, 1);

    SensorId = u8TempVal0<<8 | u8TempVal1;

    return SensorId;
}



int32_t GC6153_Open(gc6153_handler_t *handle)
{

    if (GC6153_Check_Id(handle) != 0x6153)
    {
        return -1;
    }

    GC6153_Initial_Setting(handle); /* apply the sensor initial setting */

    return 0;
}


