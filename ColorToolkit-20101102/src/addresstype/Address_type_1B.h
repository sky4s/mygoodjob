//-----------------------------------------------------------------------------
//      20100608 new  for class TBit
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_1BH
#define ADDRESS_TYPE_1BH
#include <math.h>
#include <stdlib.h>

class TBit:public AbstractAddressType {
  private:
    //bool en;
    int B_addr;
    int b_addr;
    //int b_num;
    int value;
    //AnsiString name;
  public:
     String * choice;
    int choice_nbr;
    int set(int, int, int, AnsiString);	//set address,
    //return val:1=>bit address range fault, 2=>number of bits fault, 3=>1&2 fault
    //bool FuncEn();		//function enable or not
    int Addr();
    int ShiftBit();		//number of bits the stored value shift
    int StbBit();		//stable bit value
    //int BitNum();
    int GetVal();
    void SetVal(int);
    //AnsiString Name();
     TBit() {
	en = false;
	B_addr = 0;
	b_addr = 0;
	b_num = 0;
	name = "";
	choice = NULL;
	choice_nbr = 0;
	value = -1;
    };
    /*~TBit() {
       }; */
    virtual void _set(int_vector_ptr vector, AnsiString name) {
	//using namespace java::lang;
	int size = vector->size();
	set((*vector)[0], (*vector)[1], (*vector)[2], name);
    };
};

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

int TBit::GetVal()
{
    return value;
}
void TBit::SetVal(int val)
{
    value = val;
};
/*int TBit::BitNum()
{
    return b_num;
}

bool TBit::FuncEn()
{
    return (en);
}*/

int TBit::Addr()
{
    return (B_addr);
}

int TBit::ShiftBit()
{
    return (b_addr);
}

/*AnsiString TBit::Name()
{
    return name;
}*/

int TBit::StbBit()
{
    if (b_num == 1)
	return (0xff - pow(2, b_addr));
    else if (b_num == 8)
	return 0;
    else
	return (255 - pow(2, b_addr + b_num) + pow(2, b_addr));
}

#endif

