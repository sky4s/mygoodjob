//-----------------------------------------------------------------------------
//      20100608 new  for class TBit4
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_4BH
#define ADDRESS_TYPE_4BH
#include <math.h>
#include <stdlib.h>
#include "Address_type_1B.h"

//-----------------------------------------------------------------------------
//  class TBIT4
//-----------------------------------------------------------------------------

class TBit4:public AbstractAddressType {
  private:
    int divide1, divide2, divide3;
    int set(int _B1_addr, int _b1_addr, int _b1_num,
	    int _B2_addr, int _b2_addr, int _b2_num,
	    int _B3_addr, int _b3_addr, int _b3_num,
	    int _B4_addr, int _b4_addr, int _b4_num, AnsiString _name);
  public:
     TBit Byte1;
    TBit Byte2;
    TBit Byte3;
    TBit Byte4;
    int Divide1();
    int Divide2();
    int Divide3();
    int GetVal();
    void SetVal(int);


    virtual void _set(int_vector_ptr vector, AnsiString name) {
	using namespace java::lang;
	if (vector->size() != 12) {
	    throw IllegalArgumentException();
	}
	set((*vector)[0], (*vector)[1], (*vector)[2], (*vector)[3],
	    (*vector)[4], (*vector)[5], (*vector)[6], (*vector)[7],
	    (*vector)[8], (*vector)[9], (*vector)[10], (*vector)[11],
	    name);
    };
};

//====================================================================================================
//    非連續的三個byte, 也不一定有一個byte為8bit
//      int set(AnsiString _name) , 另外再由Byte1.set與Byte2.set去設定address
//====================================================================================================
int TBit4::set(int _B1_addr, int _b1_addr, int _b1_num,
	       int _B2_addr, int _b2_addr, int _b2_num, int _B3_addr,
	       int _b3_addr, int _b3_num, int _B4_addr, int _b4_addr,
	       int _b4_num, AnsiString _name)
{
    en = true;
    Byte1.set(_B1_addr, _b1_addr, _b1_num, "");	//high bit
    Byte2.set(_B2_addr, _b2_addr, _b2_num, "");
    Byte3.set(_B3_addr, _b3_addr, _b3_num, "");
    Byte4.set(_B4_addr, _b4_addr, _b4_num, "");	//low bit
    b_num =
	Byte1.BitNum() + Byte2.BitNum() + Byte3.BitNum() + Byte4.BitNum();
    divide1 = pow(2, Byte2.BitNum() + Byte3.BitNum() + Byte4.BitNum());
    divide2 = pow(2, Byte3.BitNum() + Byte4.BitNum());
    divide3 = pow(2, Byte4.BitNum());
    name = _name;
    return 1;
}

int TBit4::Divide1()
{
    return divide1;
}

int TBit4::Divide2()
{
    return divide2;
}

int TBit4::Divide3()
{
    return divide3;
}


/*
            LblE4[idx]->Lble->Text = (int)val1*LblE4[idx]->Addr.Divide1()
                   +(int)val2*LblE4[idx]->Addr.Divide2()
                   +(int)val3*LblE4[idx]->Addr.Divide3()+(int)val4;
*/
int TBit4::GetVal()
{
    int value = -1;
    if (Byte1.GetVal() == -1 || Byte2.GetVal() == -1
	|| Byte3.GetVal() == -1 || Byte4.GetVal() == -1) {
	value = -1;
    } else {
	value = Byte1.GetVal() * divide1 + Byte2.GetVal() * divide2
	    + Byte3.GetVal() * divide3 + Byte4.GetVal();
    }
    return value;
}
void TBit4::SetVal(int val)
{
    int val1 = floor((double) val / divide1);
    int val2 = floor((double) (val - val1 * divide1) / divide2);
    int val3 =
	floor((double) (val - val1 * divide1 - val2 * divide2) / divide3);
    int val4 = val % divide3;
    Byte1.SetVal(val1);
    Byte2.SetVal(val2);
    Byte3.SetVal(val3);
    Byte4.SetVal(val4);
}
#endif

