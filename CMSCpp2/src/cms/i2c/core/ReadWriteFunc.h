//---------------------------------------------------------------------------
#ifndef ReadWriteFuncH
#define ReadWriteFuncH
//---------------------------------------------------------------------------
#include "PrintPortI2C.h"
#include <HWINTERFACELib_TLB.h>
#include <HWINTERFACELib_OCX.h>
#include <USB_i2c_lib/USBHIDIOC.H>
#include <USB_i2c_lib/USB_I2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>


class RW_Func {
  public:
    RW_Func();
    int LPT_Read_Byte(unsigned char dev_addr, unsigned char *data_addr,
		      int data_addr_cnt, unsigned char *data_read);
    int LPT_Write(unsigned char dev_addr, unsigned char *data_addr,
		  int data_addr_cnt, unsigned char *data_write,
		  int data_len);
    int LPT_Read_seq(unsigned char dev_addr, unsigned char *data_addr,
		     int data_addr_cnt, unsigned char *data_read,
		     int data_cnt);
    bool USB_read(unsigned char dev_addr, unsigned char *data_addr,
		  int data_addr_cnt, unsigned char *data_read,
		  int data_len);
    bool USB_write(unsigned char dev_addr, unsigned char *data_addr,
		   int data_addr_cnt, unsigned char *data_write,
		   int data_len);
    bool USB_write_serial(unsigned char dev_addr, unsigned char *data_addr,
			  int data_addr_cnt, unsigned char *data_write,
			  int data_len, int flag);
    int LPT_Read_Byte_Skip_Ack(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_read);

    int USB_connect(int pwr_i, int clck_i);
    int LPT_connect(void);
    bool USB_disconnect(void);
};

extern CUsbhidioc USB;		// USB I/O function class
extern bool DeviceDetected;	// Check if System is active
extern unsigned int VendorID;	// Uses Microchip's Vendor ID.
extern unsigned int ProductID;	// UIB Board

#endif
