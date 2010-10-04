//-----------------------------------------------------------------------------
//      20100608 new  for class TLUT
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_1LH
#define ADDRESS_TYPE_1LH
#include <math.h>
#include <stdlib.h>

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

int TLUT::BitNum()
{
    return b_num;
}

AnsiString TLUT::Name()
{
    return name;
}

#endif
