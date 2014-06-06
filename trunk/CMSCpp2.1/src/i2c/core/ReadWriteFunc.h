//---------------------------------------------------------------------------
#ifndef ReadWriteFuncH
#define ReadWriteFuncH
//---------------------------------------------------------------------------

#include <USB_i2c_lib/USBHIDIOC.H>


class RW_Func {
  public:
    RW_Func();
    int LPT_Read_Byte(unsigned char dev_addr, unsigned char *data_addr,
		      int data_addr_cnt, unsigned char *data_read);
    int LPT_Write(unsigned char dev_addr, unsigned char *data_addr,
		  int data_addr_cnt, unsigned char *data_write, int data_len);
    int LPT_Read_seq(unsigned char dev_addr, unsigned char *data_addr,
		     int data_addr_cnt, unsigned char *data_read, int data_cnt);
    bool USB_read(unsigned char dev_addr, unsigned char *data_addr,
		  int data_addr_cnt, unsigned char *data_read, int data_len);
    bool USB_write(unsigned char dev_addr, unsigned char *data_addr,
		   int data_addr_cnt, unsigned char *data_write, int data_len);
    bool USB_write_serial(unsigned char dev_addr, unsigned char *data_addr,
			  int data_addr_cnt, unsigned char *data_write, int data_len, int flag);
    int LPT_Read_Byte_Skip_Ack(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_read);

    int USB_connect(int pwr_i, int clck_i);
    int LPT_connect(void);
    bool USB_disconnect(void);

    bool USB_start();
    bool USB_stop();

    // 20100608 for USB sequential read/ write
    bool USB_seq_write_P1(unsigned char dev_addr, unsigned char *data_addr, int data_addr_cnt,
			  unsigned char *data_write, int data_len, bool overflag);
    bool USB_Data_Package(unsigned char *data_write, int data_len, bool overflag);
    bool USB_seq_read_P1(unsigned char dev_addr, unsigned char *data_addr, int data_addr_cnt,
			 unsigned char *data_read, int data_len, bool overflag);
    bool USB_r_Data_Package(unsigned char *data_read, int data_len, bool overflag);

    // 20140603 for DoDoBird I2C Card
    bool DoDoBird_connect(void);
    void DoDoBird_disconnect(void);
    bool DoDoBird_initialize(void);
    bool DoDoBird_write(unsigned char dev_addr, unsigned char *data_addr,
		        int data_addr_cnt, unsigned char *data_write, int data_len);
    bool DoDoBird_read(unsigned char dev_addr, unsigned char *data_addr,
		       int data_addr_cnt, unsigned char *data_read, int data_len);

};

extern CUsbhidioc USB;		// USB I/O function class
extern bool DeviceDetected;	// Check if System is active
extern unsigned int VendorID;	// Uses Microchip's Vendor ID.
extern unsigned int ProductID;	// UIB Board

#endif

