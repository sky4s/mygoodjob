//-----------------------------------------------------------------------------
//      20100608 new  for class TBit2
//-----------------------------------------------------------------------------
#ifndef ADDRESS_TYPE_2BH
#define ADDRESS_TYPE_2BH
#include <math.h>
#include <stdlib.h>
#include "Address_type_1B.h"

class TBit2:public AbstractAddressType {
  private:
    int type;
    int divide;
    int value;
  public:
     String * choice;
    int choice_nbr;
    TBit Byte1;
    TBit Byte2;
    int Divide();
    int GetVal();
    void SetVal(int);
    int set(int _B_addr, int _b_num, AnsiString _name);
    int set(int _B_addr1, int _B_addr2, int _b_num, int _b1_addr, AnsiString _name);
    int set(AnsiString _name);
    int set(int _B1_addr, int _b1_addr, int _b1_num, int _B2_addr, int _b2_addr, int _b2_num,
	    AnsiString _name);
    //AnsiString Name();
     TBit2() {
	en = false;
	b_num = 0;
	name = "";
	value = -1;
    };
    ~TBit2() {
    };

    virtual void _set(int_vector_ptr vector, AnsiString name) {
	using namespace java::lang;
	int size = vector->size();
	switch (size) {
	/*case 2:
	    set((*vector)[0], (*vector)[1], name);
	    break;*/
	case 3:
	    set((*vector)[0], (*vector)[1], (*vector)[2], 0, 0, 0, name);
	    break;
	/*case 4:
	    set((*vector)[0], (*vector)[1], (*vector)[2], (*vector)[3], name);
	    break;*/
	case 6:
	    set((*vector)[0], (*vector)[1], (*vector)[2], (*vector)[3], (*vector)[4], (*vector)[5],
		name);
	    break;
	default:
	    throw IllegalArgumentException();
	}

    };
};

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

/*int TBit2::BitNum()
{
    return b_num;
}*/

int TBit2::Divide()
{
    return divide;
}

/*bool TBit2::FuncEn()
{
    return (en);
}

AnsiString TBit2::Name()
{
    return name;
}*/

int TBit2::GetVal()
{
    if (Byte1.GetVal() == -1 || Byte2.GetVal() == -1)
	value = -1;
    else
	value = Byte1.GetVal() * divide + Byte2.GetVal();
    return value;
}
void TBit2::SetVal(int val)
{
    value = val;
    int val1 = floor((double) value / divide);
    int val2 = value % divide;
    Byte1.SetVal(val1);
    Byte2.SetVal(val2);
}

#endif

