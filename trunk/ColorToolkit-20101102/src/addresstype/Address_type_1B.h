//-----------------------------------------------------------------------------
//      20100608 new  for class TBit
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_1BH
#define ADDRESS_TYPE_1BH
#include <math.h>
#include <stdlib.h>

class TBit:public AbstractAddressType {
  private:
    int B_addr;
    int b_addr;
    int value;

  public:

    /*
       return val:1=>bit address range fault, 2=>number of bits fault, 3=>1&2 fault
     */
    int set(int _B_addr, int _b_addr, int _b_num, AnsiString _name);	//set address,
    int Addr();
    int ShiftBit();		//number of bits the stored value shift
    int StbBit();		//stable bit value
    int GetVal();		//AbstractAddressType 才用的到
    void SetVal(int);		//AbstractAddressType才用的到
     TBit() {
	B_addr = 0;
	b_addr = 0;
	value = -1;
    };
    virtual void _set(int_vector_ptr vector, AnsiString name) {
	//using namespace java::lang;
	int size = vector->size();
	set((*vector)[0], (*vector)[1], (*vector)[2], name);
    };
};

//---------------------------------TBit_Ctrl--------------------------------

/*
  HSV_EN,208,0,1
  ^^^^^^1^^^2^3^4
  1. _name
  2. _B_addr, address
  3. _b_addr, start bit
  4. _b_num, length

  return val:1=>bit address range fault, 2=>number of bits fault, 3=>1&2 fault
*/
int TBit::set(int _B_addr, int _b_addr, int _b_num, AnsiString _name)
{
    int rtn_val = 0;
    en = true;
    B_addr = _B_addr;
    name = _name;
    if (_b_addr <= 7 && _b_addr >= 0) {
	b_addr = _b_addr;
    } else {
	//error??
	rtn_val += 1;		//bit address out of range(0~7), return value
    }
    if (_b_num <= 8 && _b_num >= 0) {
	b_num = _b_num;
	return rtn_val;
    } else {
	return (rtn_val + 2);
    }
}


int TBit::GetVal()
{
    return value;
}
void TBit::SetVal(int val)
{
    value = val;
};

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
    if (b_num == 1) {
	return (0xff - pow(2, b_addr));
    } else if (b_num == 8) {
	return 0;
    } else {
	return (255 - pow(2, b_addr + b_num) + pow(2, b_addr));
    }
}

#endif

