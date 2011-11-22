#ifndef ADDRESS_TYPEH
#define ADDRESS_TYPEH

#define NEW_ADDRESS_TYPE	//新的address type宣告方式, 去除冗餘宣告
#ifdef NEW_ADDRESS_TYPE

#define Num_ASIC 4
#define ADDRESS_FILE "tcon.txt"

#include <lib/CMSCpp2.1/src/includeall.h>

class AbstractAddressType {
  private:
    virtual void _set(int_vector_ptr vector, AnsiString name) = 0;
  protected:
     bool en;			//若被設定過則會en == true
    int b_num;
    AnsiString name;
     AbstractAddressType() {
	en = false;
	b_num = 0;
	name = "";
	choice = NULL;
	choice_nbr = 0;
    };
  public:
    String * choice;
    int choice_nbr;

    void set(int *values, int n, std::string name) {
	int_vector_ptr vector(new int_vector(n));
	for (int x = 0; x < n; x++) {
	    (*vector)[x] = values[x];
	};
	_set(vector, name.c_str());
    };
    void set(int_vector_ptr vector, std::string name) {
	_set(vector, name.c_str());
    };

    bool FuncEn() {
	return en;
    }
    int BitNum() {
	return b_num;
    }
    AnsiString Name() {
	return name;
    }
};


#include "Address_type_1B.h"
#include "Address_type_1L.h"
#include "Address_type_2B.h"
#include "Address_type_3B.h"
#include "Address_type_4B.h"

#else				//NEW_ADDRESS_TYPE



//C系統文件
#include <math.h>
#include <stdlib.h>
//C++系統文件

//vcl庫頭文件
#include <vcl.h>

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件


#define Num_ASIC 4


class TBit {
  private:
    bool en;
    int B_addr;
    int b_addr;
    int b_num;
    AnsiString name;
  public:
     String * choice;
    int choice_nbr;
    int set(int, int, int, AnsiString);	//set address,
    //return val:1=>bit address range fault, 2=>number of bits fault, 3=>1&2 fault
    bool FuncEn();		//function enable or not
    int Addr();
    int ShiftBit();		//number of bits the stored value shift
    int StbBit();		//stable bit value
    int BitNum();
    AnsiString Name();
     TBit() {
	en = false;
	B_addr = 0;
	b_addr = 0;
	b_num = 0;
	name = "";
	choice = NULL;
	choice_nbr = 0;
    } ~TBit() {;
    }
};
int TBit::BitNum()
{
    return b_num;
}

class TBit2 {
  private:
    bool en;
    int b_num;
    int type;
    AnsiString name;
    int divide;

  public:
    String * choice;
    int choice_nbr;
    TBit Byte1;
    TBit Byte2;
    int Divide();
    bool FuncEn();		//function enable or not
    int BitNum();
    int set(int _B_addr, int _b_num, AnsiString _name);
    int set(int _B_addr1, int _B_addr2, int _b_num, int _b1_addr, AnsiString _name);
    int set(AnsiString _name);
    int set(int _B1_addr, int _b1_addr, int _b1_num, int _B2_addr, int _b2_addr, int _b2_num,
	    AnsiString _name);
    AnsiString Name();
    TBit2() {
	en = false;
	b_num = 0;
	name = "";
    } ~TBit2() {;
    }
};
int TBit2::BitNum()
{
    return b_num;
}

//====================================================================================================
//    TBit2的Set函數有三種,
//    1.連續兩個byte, 第一個為high 第二個為low,
//      int set(int _B_addr, int _b_num, AnsiString _name)
//      說明:第一個byte為high bit, bit排列方式靠右ex:(3:0), 第二個byte為low bit (7:0)
//    2.非連續的兩byte,
//      int set(int _B_addr1, int _B_addr2, int _b_num, int _b1_addr, AnsiString _name)
//      _B_addr1:第一個byte address(high bit),
//      _B_addr2:第二個byte address(low bit),長度固定為8bit
//      _b_num:總長度
//      _b1_addr:第一個byte的bit address, 從哪個bit以上為使用的
//    3.非連續的兩byte, 也不一定有一個byte為8bit
//      int set(AnsiString _name) , 另外再由Byte1.set與Byte2.set去設定address
//====================================================================================================
int TBit2::set(int _B1_addr, int _b1_addr, int _b1_num, int _B2_addr, int _b2_addr, int _b2_num,
	       AnsiString _name)
{
    en = true;
    Byte1.set(_B1_addr, _b1_addr, _b1_num, "");	//high bit
    Byte2.set(_B2_addr, _b2_addr, _b2_num, "");	//low bit
    b_num = Byte1.BitNum() + Byte2.BitNum();
    divide = pow(2, Byte2.BitNum());
    name = _name;
    return 1;
}

int TBit2::set(AnsiString _name)
{
    en = true;
    b_num = Byte1.BitNum() + Byte2.BitNum();
    divide = pow(2, Byte2.BitNum());
    name = _name;
    return 1;
}

int TBit2::set(int _B_addr1, int _B_addr2, int _b_num, int _b1_addr, AnsiString _name)
{
    en = true;
    name = _name;
    b_num = _b_num;

    if (_b_num == 9) {
	Byte1.set(_B_addr1, _b1_addr, 1, "");	//high bit
	Byte2.set(_B_addr2, 0, 8, "");	//low bit
	divide = 256;
    } else if (_b_num == 10) {
	Byte1.set(_B_addr1, _b1_addr, 2, "");	//high bit
	Byte2.set(_B_addr2, 0, 8, "");	//low bit
	divide = 256;
    } else if (_b_num == 11) {
	Byte1.set(_B_addr1, _b1_addr, 3, "");	//high bit
	Byte2.set(_B_addr2, 0, 8, "");	//low bit
	divide = 256;
    } else if (_b_num == 12) {
	Byte1.set(_B_addr1, _b1_addr, 4, "");	//high bit
	Byte2.set(_B_addr2, 0, 8, "");	//low bit
	divide = 256;
    }
    return 1;
}
int TBit2::set(int _B_addr, int _b_num, AnsiString _name)
{
    en = true;
    type = 1;
    divide = 256;
    name = _name;
    b_num = _b_num;
    if (_b_num == 7) {
	divide = 1;
	Byte1.set(_B_addr, 0, 7, "");
	Byte2.set(_B_addr + 1, 0, 0, "");
    } else if (_b_num == 8) {
	divide = 1;
	Byte1.set(_B_addr, 0, 8, "");
	Byte2.set(_B_addr + 1, 0, 0, "");
    } else if (_b_num == 9) {
	Byte1.set(_B_addr, 0, 1, "");
	Byte2.set(_B_addr + 1, 0, 8, "");
    } else if (_b_num == 10) {
	Byte1.set(_B_addr, 0, 2, "");
	Byte2.set(_B_addr + 1, 0, 8, "");
    } else if (_b_num == 11) {
	Byte1.set(_B_addr, 0, 3, "");
	Byte2.set(_B_addr + 1, 0, 8, "");
    } else if (_b_num == 12) {
	Byte1.set(_B_addr, 0, 4, "");
	Byte2.set(_B_addr + 1, 0, 8, "");
    } else if (_b_num == 16) {
	Byte1.set(_B_addr, 0, 8, "");
	Byte2.set(_B_addr + 1, 0, 8, "");
    }
    return 1;
}

int TBit2::Divide()
{
    return divide;
}

AnsiString TBit2::Name()
{
    return name;
}

bool TBit2::FuncEn()
{
    return (en);
}

class TLUT {
  private:
    bool en;
    int B_addr;
    int Lut_num;
    int b_num;
    int type;
    AnsiString name;
  public:
    int Addr();
    int LutNum();
    int Type();
    int BitNum();
    AnsiString Name();
    int set(int _B_addr, int _Lut_num, int _b_num, int _type, AnsiString _name);
    int set(int _B_addr, int _Lut_num, int _b_num, AnsiString _name);
    TLUT() {
	en = false;
	B_addr = 0;
	Lut_num = 0;
	b_num = 0;
	name = "";
    } ~TLUT() {;
    }
};

//----------------------TLUT--------------------------------------
int TLUT::Addr()
{
    return B_addr;
}
int TLUT::set(int _B_addr, int _Lut_num, int _b_num, AnsiString _name)
{
    int rtn_val = 0;
    en = true;
    B_addr = _B_addr;
    Lut_num = _Lut_num;
    b_num = _b_num;
    type = 1;
    name = _name;
    return rtn_val;
}
int TLUT::set(int _B_addr, int _Lut_num, int _b_num, int _type, AnsiString _name)
{
    int rtn_val = 0;
    en = true;
    B_addr = _B_addr;
    Lut_num = _Lut_num;
    b_num = _b_num;
    type = _type;
    name = _name;
    return rtn_val;
}

int TLUT::LutNum()
{
    return Lut_num;
}

int TLUT::Type()
{
    return type;
}

int TLUT::BitNum()
{
    return b_num;
}

AnsiString TLUT::Name()
{
    return name;
}

//---------------------------------TBit_Ctrl--------------------------------

int TBit::set(int _B_addr, int _b_addr, int _b_num, AnsiString _name)
{
    int rtn_val = 0;
    en = true;
    B_addr = _B_addr;
    name = _name;
    if (_b_addr <= 7 && _b_addr >= 0) {
	b_addr = _b_addr;
    } else {
	rtn_val += 1;		//bit address out of range(0~7), return value
    }
    if (_b_num <= 8 && _b_num >= 0) {
	b_num = _b_num;
	return rtn_val;
    } else {
	return (rtn_val + 2);
    }
}
bool TBit::FuncEn()
{
    return (en);
}

int TBit::Addr()
{
    return (B_addr);
}

int TBit::ShiftBit()
{
    return (b_addr);
}

int TBit::StbBit()
{
    if (b_num == 1)
	return (0xff - pow(2, b_addr));
    else if (b_num == 8)
	return 0;
    else
	return (255 - pow(2, b_addr + b_num) + pow(2, b_addr));
}

AnsiString TBit::Name()
{
    return name;
}
#endif				//NEW_ADDRESS_TYPE
#endif				//ADDRESS_TYPEH

