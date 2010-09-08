//-----------------------------------------------------------------------------
//      20100608 new  for class TBit3
//-----------------------------------------------------------------------------


#include <math.h>
#include <stdlib.h>
#include "Address_type_1B.h"

//-----------------------------------------------------------------------------
//  class TBIT3
//-----------------------------------------------------------------------------

class TBit3
{
        private:
                bool en;
                int b_num;
                int type;
                AnsiString name;
                int divide1,divide2;
                int value;

        public:
                String* choice;
                int choice_nbr;
                TBit Byte1;
                TBit Byte2;
                TBit Byte3;
                int Divide1();
                int Divide2();
                bool FuncEn();          //function enable or not
                int BitNum();
                int GetVal();
                void SetVal(int);
                int set(int _B1_addr, int _b1_addr, int _b1_num,
                        int _B2_addr, int _b2_addr, int _b2_num, int _B3_addr,
			int _b3_addr, int _b3_num,AnsiString _name);
                AnsiString Name();
                TBit3()
                {
                        value = -1;                
                        en = false;
                        b_num = 0;
                        name = "";
                }
                ~TBit3(){;}
};

//====================================================================================================
//    非連續的三個byte, 也不一定有一個byte為8bit
//      int set(AnsiString _name) , 另外再由Byte1.set與Byte2.set去設定address
//====================================================================================================
int TBit3::set(int _B1_addr, int _b1_addr, int _b1_num, int _B2_addr,
  int _b2_addr, int _b2_num,int _B3_addr, int _b3_addr, int _b3_num, AnsiString _name)
{
        en = true;
        Byte1.set( _B1_addr, _b1_addr, _b1_num,"");      //high bit
        Byte2.set( _B2_addr, _b2_addr, _b2_num,"");
        Byte3.set( _B3_addr, _b3_addr, _b3_num,"");      //low bit
        b_num = Byte1.BitNum()+Byte2.BitNum()+Byte3.BitNum();
        divide1 = pow(2,Byte2.BitNum()+Byte3.BitNum());
        divide2 = pow(2,Byte3.BitNum());
        name = _name;
        return 1;
}

int TBit3::BitNum() { return b_num; }
int TBit3::Divide1() { return divide1; }
int TBit3::Divide2() { return divide2; }
bool TBit3::FuncEn() { return (en); }
AnsiString TBit3::Name() { return name; }


int TBit3::GetVal()
{
        if(Byte1.GetVal()==-1 || Byte2.GetVal()==-1 || Byte3.GetVal()==-1)
                value = -1;
        else
                value = Byte1.GetVal()*divide1+Byte2.GetVal()*divide2+Byte3.GetVal();
        return value;
}
void TBit3::SetVal(int val)
{
        value = val;
        int val1 = floor((double)value/divide1);
        int val2 = floor((double)(value-val1*divide1)/divide2);
        int val3 = value%divide2;
        Byte1.SetVal(val1);
        Byte2.SetVal(val2);
        Byte3.SetVal(val3);
}