//-----------------------------------------------------------------------------
//      20100608 new  for class TLUT
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_1LH
#define ADDRESS_TYPE_1LH
#include <math.h>
#include <stdlib.h>

class TLUT:public AbstractAddressType {
  private:
    int B_addr;
    int Lut_num;
    int type;
  public:
    int Addr();
    int LutNum();
    int Type();
    int set(int _B_addr, int _Lut_num, int _b_num, int _type, AnsiString _name);
     TLUT() {
	B_addr = 0;
	Lut_num = 0;
    };
    ~TLUT() {
    };

    virtual void _set(int_vector_ptr vector, AnsiString name) {
	using namespace java::lang;
	switch (vector->size()) {
	case 4:
	    set((*vector)[0], (*vector)[1], (*vector)[2], (*vector)[3], name);
	    break;
	case 3:
	    set((*vector)[0], (*vector)[1], (*vector)[2], 1, name);
	    break;
	default:
	    throw IllegalArgumentException();
	}

    };
};

//----------------------TLUT--------------------------------------

/*
  SP_LUT,608,32,5
  ^^^^^^1^^^2^^3^4
  1. _name
  2. _B_addr : address
  3. _Lut_num  : length(size)?
  4. _b_num
*/
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

int TLUT::Addr()
{
    return B_addr;
}

int TLUT::LutNum()
{
    return Lut_num;
}

int TLUT::Type()
{
    return type;
}



#endif

