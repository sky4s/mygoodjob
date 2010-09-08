//--------------------------------------------------------------------------
//      This file contains signal setting of Print Port I2C
//      support 06T11 & 04T25   Revised by RSEE4 LynneLin & RichardYCTsai
//      date: 20090804
//
//      revise information:
//      1.remove wating Ack             date: 20090819
//      2.Add Ack_stop,                 date: 20090818
//      when Ack_stop = 1, set SCL high if no ack, but if Ack_stop = 0, SCL low.
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
//      Support AUO 04T25 & AUO 06T11
//      LPT has 3 base registers: Data register, Status Register, Control
//      Register (0x378~0x37A)
//      for 06T11 SDAgate(or SDA enable):Data7, SDA:Data0, SCL:Control bit0
//      for 04T25 SDA:Data7, SCL:Data6
//      SDA signal is two-way transmision, SCL is one-way transmision
//      P.S for 06T11, SDA set to GND, SDAgate is SDA inverse
//--------------------------------------------------------------------------

#include "HWINTERFACELib_TLB.h"
#include "HWINTERFACELib_OCX.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#define LPT_DATA_PORT (short)0x378
#define LPT_STATUS_PORT (short)0x379
#define LPT_CTRL_PORT (short)0x37A

typedef unsigned short u16;
typedef short _stdcall (*inpfuncPtr)(short portaddr);
typedef void _stdcall (*oupfuncPtr)(short portaddr, short datum);
static HINSTANCE hLib;
static inpfuncPtr inp32;
static oupfuncPtr oup32;
static int i2c_card_select = 1;
static HANDLE hEvent;
static unsigned char current_lpt_data=0x7f;
static unsigned char current_lpt_ctrl=0xff;
static int sig_delay = 0;
static bool Half_freq = 0;
static bool Ack_stop = 1;

void lpt_send_byte_ctrl(unsigned char data);
void lpt_send_byte_data(unsigned char data);
int Link_LPT();
unsigned char lpt_read_byte_st(void);
void i2c_set_vdd(void);
void i2c_set_scl(void);
void i2c_reset_scl(void);
void i2c_set_sda(void);
void i2c_reset_sda(void);
unsigned char i2c_read_sda(void);
void i2c_start(void);
void i2c_end(void);
bool i2c_initial(void);
bool i2c_send_byte(unsigned char data);
bool i2c_read_byte_seq(unsigned char dev_addr, unsigned char * data_read, int data_cnt);
bool i2c_read_byte(unsigned char dev_addr, unsigned char* data_read);
void SetCardLarge();
void SetCardSmall();


void Ack_Stop_remove()
{
        Ack_stop = 0;
}

int LPT_disconnect()
{
        FreeLibrary(hLib);
        return 1;
}
int Link_LPT()
{
        hLib = LoadLibrary("inpout32.dll");
                if (hLib == NULL) {
                        return 0;
                }

                /* get the address of the function */
                inp32 = (inpfuncPtr) GetProcAddress(hLib, "Inp32");
                if (inp32 == NULL) {
                        return -1;
                }

                oup32 = (oupfuncPtr) GetProcAddress(hLib, "Out32");
                if (oup32 == NULL) {
                       return -1;
                }

                hEvent=CreateEvent(
                        NULL,   // no security attributes
                        TRUE,  // auto-reset event object
                        TRUE,  // initial state is nonsignaled
                        NULL);

                return 1;
}

void lpt_send_byte_data(unsigned char data)
{
        for(int i = 0; i < (Half_freq?2:1);i++){
        	current_lpt_data=data;
	        WaitForSingleObject(hEvent,INFINITE);  // wait for control right
                oup32(LPT_DATA_PORT,data);      //send data byte
	        SetEvent(hEvent);               // release the control right
        }
}

void lpt_send_byte_ctrl(unsigned char data)
{
        for(int i = 0; i < (Half_freq?2:1);i++){
        	current_lpt_ctrl=data;
                WaitForSingleObject(hEvent,INFINITE);  // wait for control right
                oup32(LPT_CTRL_PORT,~data);     //send control byte
	        SetEvent(hEvent);               // release the control right
        }
}

unsigned char lpt_read_byte_st(void)
{
        short ret_data;
        for(int i = 0; i < (Half_freq?2:1);i++){
                WaitForSingleObject(hEvent,INFINITE);  // wait for control right
                ret_data=inp32(LPT_STATUS_PORT);
                SetEvent(hEvent);  // release the control right
                if(ret_data<0)
                        ret_data = 0;
                if(ret_data>255)
                        ret_data = 255;
        }
        return LOBYTE(ret_data);
}

void i2c_set_vdd(void)
{
        lpt_send_byte_data(current_lpt_data);
        lpt_send_byte_ctrl(current_lpt_ctrl);
}


void i2c_set_scl(void)  //clock high
{
	unsigned char lpt_data,tmp_lpt_data;

        if (i2c_card_select==0){
        	tmp_lpt_data=0x01;  // SCL bit high active
        	lpt_data=(current_lpt_ctrl & (0xfe)) | tmp_lpt_data;
        	lpt_send_byte_ctrl(lpt_data);
        }else{
        	tmp_lpt_data=0x40;  // SCL bit low active
        	lpt_data=(current_lpt_data & (0xbf)) & ~tmp_lpt_data;
	        lpt_send_byte_data(lpt_data);
        }

}
void i2c_reset_scl(void)   //clock low
{
	unsigned char lpt_data,tmp_lpt_data;

        if (i2c_card_select==0){
        	tmp_lpt_data=0x01;  // SCL bit high active
        	lpt_data=(current_lpt_ctrl & (0xfe)) & ~tmp_lpt_data;
        	lpt_send_byte_ctrl(lpt_data);
        }else{
        	tmp_lpt_data=0x40;  // SCL bit low active
        	lpt_data=(current_lpt_data & (0xbf)) | tmp_lpt_data;
	        lpt_send_byte_data(lpt_data);
        }
}

void i2c_set_sda(void)     //data high
{
	unsigned char lpt_data,tmp_lpt_data;

        if (i2c_card_select==0){
                tmp_lpt_data=0x00;    // SDA gate is inverse sda
                lpt_data=(current_lpt_data & (0x7e)) | tmp_lpt_data;
       	        lpt_send_byte_data(lpt_data);
        }else{
                tmp_lpt_data=0x80;    // SDA bit low active
	        lpt_data=(current_lpt_data & (0x7f)) & ~tmp_lpt_data;
        	lpt_send_byte_data(lpt_data);
        }
}


void i2c_reset_sda(void)     //data low
{
	unsigned char lpt_data,tmp_lpt_data;

        if (i2c_card_select==0){
                tmp_lpt_data=0x80;    // SDA gate is inverse sda
                lpt_data=(current_lpt_data & (0x7e)) | tmp_lpt_data;
       	        lpt_send_byte_data(lpt_data);
        }else{
                tmp_lpt_data=0x80;    // SDA bit low active
	        lpt_data=(current_lpt_data & (0x7f)) | tmp_lpt_data;
        	lpt_send_byte_data(lpt_data);
        }
}

unsigned char i2c_read_sda(void)
{
        unsigned char ret_data;

	ret_data=lpt_read_byte_st();
	if (i2c_card_select==0){
        	ret_data= ret_data<<3;  //sda feedback in state bit 4
        }else{
        	ret_data= ~ret_data;    //sda feedback in state bit 7
        }
        return ret_data;
}

void i2c_start(void)
{
        i2c_set_sda();  //sda high
        i2c_set_scl();  //scl high
	i2c_reset_sda(); //sda turn low while scl high
}

void i2c_end(void)
{
        i2c_reset_sda();   //sda low
	i2c_set_scl();     //scl high
	i2c_set_sda();     //sda turn high while scl high
}


bool i2c_initial(void) //Pull SDA & SCL high
{
        i2c_set_vdd();
        int i;
        for(i=0;i<10;i++){      //reset EEPROM state machine
                i2c_start();
                i2c_end();
                Sleep(11);      //Wrt, Write time(for EEPROM)
        }
        return 1;
}

bool i2c_send_byte(unsigned char data) //if ack fail, return 1, else return 0
{
	int i,j,k;
	for(i=7;i>=0;i--){      //send 8 bits data
		i2c_reset_scl();           //scl low
		if(((data>>i)&0x01)!=0){
			i2c_set_sda();     //data:1 -> sda high
                }else{
                       	i2c_reset_sda();   //data:0 -> sda low
                }
                i2c_set_scl();             //scl high
	}
	i2c_reset_scl();                   //scl low
	i2c_set_sda();                     //sda high (master send high when Ack)
	i2c_set_scl();                     //scl high (Ack clock)

        unsigned char st_data;
        st_data = i2c_read_sda() & 0x80;        //read ack data
        i2c_reset_scl();                     //scl low

        if(st_data == 0)        //Ack signal get
                return 1;
        if(Ack_stop)
                i2c_set_scl();     //scl high
        Ack_stop = 1;
        return 0;
}

bool i2c_read_byte_seq(unsigned char dev_addr, unsigned char * data_read, int data_cnt)
{
        i2c_start();
        i2c_send_byte(dev_addr | 0x01);      //read

        unsigned char st_data;
        unsigned char read_data;
        i2c_reset_scl();            //scl low
        for(int k=0;k<data_cnt;k++){
            read_data = 0;
            for(int i=0;i<8;i++){
                i2c_set_scl();          //scl high
                st_data = i2c_read_sda();    //read state byte
                if((st_data & 0x80)==0){     //0
                        read_data <<=1;
                }else{                       //1
                        read_data <<=1;
                        read_data |=1;
                }
                i2c_reset_scl();        //scl low
            }
            data_read[k]= read_data;
            if(k<(data_cnt -1)){ //not last one, should generate ack data
                i2c_reset_sda();        //sda low -- Ack
                i2c_set_scl();          //scl high (Ack clock high)
                i2c_reset_scl();        //scl low  (Ack clock low)
                i2c_set_sda();        //sda high
            }
        }
        i2c_reset_scl();   //scl low
        i2c_set_sda();  //sda high -- no Ack
        i2c_set_scl();   //scl high (Ack clock high)
        i2c_reset_scl(); //scl low (Ack clock low)
        i2c_end();       //stop
        return 1;
}

bool i2c_read_byte(unsigned char dev_addr, unsigned char* data_read)
{
        i2c_start();
        i2c_send_byte(dev_addr | 0x01); //read

        unsigned char st_data;
        unsigned char read_data=0;
        i2c_reset_scl();            //scl low
        for(int i=0;i<8;i++){
            i2c_set_scl();              //scl high
            st_data = i2c_read_sda();   //read data
            if((st_data & 0x80)==0){        //0
                    read_data <<=1;
            }else{                          //1
                    read_data <<=1;
                    read_data |=1;
            }
            i2c_reset_scl();            //scl low
        }
        i2c_set_sda();          //gen no-ack signal, sda high
        i2c_set_scl();          //scl high
        i2c_reset_scl();        //scl low
        i2c_end();
        *data_read = read_data;
        return 1;
}
void SetCardLarge()
{
        i2c_card_select=0;
}
void SetCardSmall()
{
        i2c_card_select=1;
}
void SetHalfFreq()
{
        Half_freq = 1;
}
void SetOrigFreq()
{
        Half_freq = 0;
}
