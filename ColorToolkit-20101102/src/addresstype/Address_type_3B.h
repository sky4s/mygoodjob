//-----------------------------------------------------------------------------
//      20100608 new  for class TBit3
//-----------------------------------------------------------------------------

#ifndef ADDRESS_TYPE_3BH
#define ADDRESS_TYPE_3BH
#include <math.h>
#include <stdlib.h>
#include "Address_type_1B.h"

//-----------------------------------------------------------------------------
//  class TBIT3
//-----------------------------------------------------------------------------

class TBit3:public AbstractAddressType
{
private:
  int divide1, divide2;
  int set(int _B1_addr, int _b1_addr, int _b1_num,
          int _B2_addr, int _b2_addr, int _b2_num,
          int _B3_addr, int _b3_addr, int _b3_num, AnsiString _name);
public:
  //String * choice;
  //int choice_nbr;
   TBit Byte1;
  TBit Byte2;
  TBit Byte3;
  int Divide1();
  int Divide2();
  int GetVal();
  void SetVal(int);


  virtual void _set(int_vector_ptr vector, AnsiString name)
  {
    using namespace java::lang;
    if (vector->size() != 9)
    {
      throw IllegalArgumentException();
    }
    set((*vector)[0], (*vector)[1], (*vector)[2], (*vector)[3], (*vector)[4],
        (*vector)[5], (*vector)[6], (*vector)[7], (*vector)[8], name);
  };
};

//====================================================================================================
//    �D�s�򪺤T��byte, �]���@�w���@��byte��8bit
//      int set(AnsiString _name) , �t�~�A��Byte1.set�PByte2.set�h�]�waddress
//====================================================================================================
int TBit3::set(int _B1_addr, int _b1_addr, int _b1_num, int _B2_addr,
               int _b2_addr, int _b2_num, int _B3_addr, int _b3_addr,
               int _b3_num, AnsiString _name)
{
  en = true;
  Byte1.set(_B1_addr, _b1_addr, _b1_num, "");   //high bit
  Byte2.set(_B2_addr, _b2_addr, _b2_num, "");
  Byte3.set(_B3_addr, _b3_addr, _b3_num, "");   //low bit
  b_num = Byte1.BitNum() + Byte2.BitNum() + Byte3.BitNum();
  divide1 = pow(2, Byte2.BitNum() + Byte3.BitNum());
  divide2 = pow(2, Byte3.BitNum());
  name = _name;
  return 1;
}


int TBit3::Divide1()
{
  return divide1;
}

int TBit3::Divide2()
{
  return divide2;
}

   /*
      LblE3[i]->Lble->Text = (int) read_val1 *LblE3[i]->Addr.Divide1()
      + (int) read_val2 *LblE3[i]->Addr.Divide2() + (int) read_val3;
    */
int TBit3::GetVal()
{
  int value = -1;
  if (Byte1.GetVal() == -1 || Byte2.GetVal() == -1 || Byte3.GetVal() == -1)
  {
    value = -1;
  }
  else
  {
    value =
      Byte1.GetVal() * divide1 + Byte2.GetVal() * divide2 + Byte3.GetVal();
  }
  return value;
}
void TBit3::SetVal(int val)
{
  //value = val;
  int val1 = floor((double)val / divide1);
  int val2 = floor((double)(val - val1 * divide1) / divide2);
  int val3 = val % divide2;
  Byte1.SetVal(val1);
  Byte2.SetVal(val2);
  Byte3.SetVal(val3);
}
#endif

