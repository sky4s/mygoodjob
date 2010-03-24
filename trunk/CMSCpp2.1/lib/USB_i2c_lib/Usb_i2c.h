/****************************************************************************
* File: USB_I2C.h                                                           *
* Description: Control Byte of I2C-USB Bridge definition                    *
*                                                                           *
*                                                                           *
* History:                                                                  *
*   2008/06/20; Adonis Huang; Comment                                       *
*   2008/06/22; Adonis Huang; Initial version                               *
****************************************************************************/
#ifndef _USB_I2C_H_
#define _USB_I2C_H_

//Control Byte of USB-I2C Bridge definition
#define I2C_START      		0x02
#define I2C_RESTART		0x04
#define I2C_STOP        	0x08
#define I2C_DEV_READ  		0x01
#define I2C_DEV_WRITE   	0x00
#define I2C_REINIT		0x10

//Control Byte of USB-I2C Reconfiguration
#define	CLOCK_RATE_400KHZ	0x24
#define	CLOCK_RATE_100KHZ	0x20
#define	CLOCK_RATE_50KHZ	0x28

//Control Byte of USB-I2C Power definition
#define POWER_CTRL		0x80
#define POWER_EXTERNAL		0
#define POWER_INTERNAL_5V	1
#define POWER_INTERNAL_3P3V	2

#endif
/******************************* End Of File *******************************/
