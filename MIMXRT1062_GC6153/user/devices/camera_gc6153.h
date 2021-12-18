/*
 * camera_gc6153.h
 *
 *  Created on: Dec 14, 2021
 *      Author: HYB
 */

#ifndef DEVICES_CAMERA_GC6153_H_
#define DEVICES_CAMERA_GC6153_H_

#include "fsl_common.h"

#define GC6153_I2C_ADDR (0x40)


#define GC6153_SERIAL_MCLK                          10000000
#define GC6153_SERIAL_WRITE_ID_0                    (0x80)
/* SENSOR PREVIEW SIZE */
#define GC6153_SERIAL_IMAGE_SENSOR_PV_WIDTH         (240)
#define GC6153_SERIAL_IMAGE_SENSOR_PV_HEIGHT        (320)

/* SENSOR CAPTURE SIZE */
#define GC6153_SERIAL_IMAGE_SENSOR_FULL_WIDTH       (240)
#define GC6153_SERIAL_IMAGE_SENSOR_FULL_HEIGHT      (320)

/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
#define GC6153_SERIAL_PV_PERIOD_PIXEL_NUMS          (240)
#define GC6153_SERIAL_PV_PERIOD_LINE_NUMS           (320)
#define GC6153_SERIAL_FULL_PERIOD_PIXEL_NUMS        (240)
#define GC6153_SERIAL_FULL_PERIOD_LINE_NUMS         (320)

/* ===============================================================================
   ========================= No Changing The Macro Below =========================
   ===============================================================================
*/
/* CONFIG THE ISP GRAB START X & START Y, CONFIG THE ISP GRAB WIDTH & HEIGHT */
#define GC6153_SERIAL_PV_GRAB_START_X               (0)
#define GC6153_SERIAL_PV_GRAB_START_Y               (1)
#define GC6153_SERIAL_FULL_GRAB_START_X             (0)
#define GC6153_SERIAL_FULL_GRAB_START_Y             (1)
#define GC6153_SERIAL_PV_GRAB_WIDTH                 (GC6153_SERIAL_IMAGE_SENSOR_PV_WIDTH - 2)
#define GC6153_SERIAL_PV_GRAB_HEIGHT                (GC6153_SERIAL_IMAGE_SENSOR_PV_HEIGHT - 2)
#define GC6153_SERIAL_FULL_GRAB_WIDTH               (GC6153_SERIAL_IMAGE_SENSOR_FULL_WIDTH - 2)
#define GC6153_SERIAL_FULL_GRAB_HEIGHT              (GC6153_SERIAL_IMAGE_SENSOR_FULL_HEIGHT - 2)

/* FLICKER OF FREQUENCY */
#define GC6153_SERIAL_50HZ                          100
#define GC6153_SERIAL_60HZ                          120

/* HW I2C SPEED */
#define GC6153_SERIAL_HW_I2C_SPEED                  100 /* Kbps */

/* FRAME RATE UNIT */
#define GC6153_SERIAL_FPS(x)                        ((uint32_t)(10 * (x)))


#define IMAGE_NORMAL

#ifdef IMAGE_NORMAL
#define MIRROR 0x7c
#define AD_NUM 0x05
#define COL_SWITCH 0x18
#endif

#ifdef IMAGE_H_MIRROR
#define MIRROR 0x69
#define AD_NUM 0x04
#define COL_SWITCH 0x19
#endif

#ifdef IMAGE_V_MIRROR
#define MIRROR 0x7e
#define AD_NUM 0x05
#define COL_SWITCH 0x18
#endif

#ifdef IMAGE_HV_MIRROR
#define MIRROR 0x6b
#define AD_NUM 0x04
#define COL_SWITCH 0x19
#endif


#define GC6153_SYNC_HEADER23_16 0xff  //first
#define GC6153_SYNC_HEADER15_08 0xff
#define GC6153_SYNC_HEADER07_00 0xff

#define GC6153_FRAMESTART_SYNCCODE0		0x01
#define GC6153_LINESTART_SYNCCODE1		0x02
#define GC6153_DATAPACKET_SYNCCODE2		0x40
#define GC6153_FRAMEEND_SYNCCODE3		0x00
#define GC6153_FRAME_DATAID		0x00


typedef struct
{
    bool BypassAe;
    bool BypassAwb;
    bool CapState; ///< KAL_TRUE: in capture state, else in preview state
    bool PvMode; ///< KAL_TRUE: preview size output, else full size output
    bool VideoMode; ///< KAL_TRUE: video mode, else preview mode
	bool NightMode;///< KAL_TRUE:work in night mode, else normal mode
    uint8_t BandingFreq; ///< GC6153_SERIAL_50HZ or GC6153_SERIAL_60HZ for 50Hz/60Hz
    uint32_t InternalClock; ///< internal clock which using process pixel(for exposure)
    uint32_t Pclk; ///< output clock which output to baseband
    uint32_t Gain; ///< base on 0x40
    uint32_t Shutter; ///< unit is (linelength / internal clock) s
    uint32_t FrameLength; ///< total line numbers in one frame(include dummy line)
    uint32_t LineLength; ///< total pixel numbers in one line(include dummy pixel)

    void (*Rst_Set)(int i);
    void (*Pwn_Set)(int i);
    void (*Clk_Set)(bool option);
} GC6153_SERIALSensor;



typedef status_t (*gc6153_i2c_send_func_t)(uint8_t deviceAddress,
        uint32_t regAddress, size_t regAddressSize,
        uint8_t *data, size_t dataSize);

typedef status_t (*gc6153_i2c_read_func_t)(uint8_t deviceAddress,
        uint32_t regAddress, size_t regAddressSize,
        uint8_t *data, size_t dataSize);

typedef void (*gc6153_delay_func_t)(uint32_t ms);


typedef void (*gc6153_pwdn_func_t)(uint8_t value);


/*! @brief gc6153 handler configuration structure */
typedef struct gc6153_handler {
    uint8_t                i2cAddr;
    gc6153_i2c_send_func_t i2cSend;
    gc6153_i2c_read_func_t i2cRead;
    gc6153_delay_func_t    delayMs;
    gc6153_pwdn_func_t pwdn;
} gc6153_handler_t;




void GC6153_Set_Clock(gc6153_handler_t *handle, GC6153_SERIALSensor* cmos_senser, uint32_t InternalClock);

/**
 * @brief
 *
 * @param cmos_senser
 * @return int32_t
 */
int32_t GC6153_Open(gc6153_handler_t *handle);

/**
  * @brief This function initialize the registers of CMOS sensor
  * @note    the output format should be YUV422, order: YUYV
*            data output should be at pclk falling edge
*            VSYNC should be low active
*            HSYNC should be hight active
  * @param[in]  None
  * @retval None
  */
void GC6153_Initial_Setting(gc6153_handler_t *handle);

 /**
  * @brief This function initialize the registers of CMOS sensor
  * @note    the output format should be YUV422, order: YUYV
*            data output should be at pclk falling edge
*            VSYNC should be low active
*            HSYNC should be hight active
  * @param[in]  None
  * @retval sensor Id
  */
 void GC6153_Power_On(gc6153_handler_t *handle);

/**
  * @brief This function initialize the registers of CMOS sensor
  * @note    the output format should be YUV422, order: YUYV
*            data output should be at pclk falling edge
*            VSYNC should be low active
*            HSYNC should be hight active
  * @param[in]  None
  * @retval None
  */
 void GC6153_Power_Down(gc6153_handler_t *handle);


#endif /* DEVICES_CAMERA_GC6153_H_ */
