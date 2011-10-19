// ============================================================== //
//
//  20100608 新增, 提供轉換table數值為Byte或由Byte數值轉為table值
//
// ============================================================== //
#ifndef table_typeH
#define table_typeH

struct IntTbl{
        int* Tbl;
        int Len;
};
struct ByteTbl{
        unsigned char* Tbl;
        int Len;
};

class ReadWrite_LUT
{
        public:
        bool Read_LUT4(IntTbl& Out, ByteTbl In, int type);
        bool Read_LUT5(IntTbl& Out, ByteTbl In, int type);  // 201007
        bool Read_LUT6(IntTbl& Out, ByteTbl In, int type);
        bool Read_LUT8(IntTbl& Out, ByteTbl In, int type);
        bool Read_LUT10(IntTbl& Out, ByteTbl In, int type);
        bool Read_LUT12(IntTbl& Out, ByteTbl In, int type);
        bool Read_LUT16(IntTbl& Out, ByteTbl In, int type);

        bool Write_LUT4(ByteTbl& Out, IntTbl In, int type);
        bool Write_LUT5(ByteTbl& Out, IntTbl In, int type);  // 201007
        bool Write_LUT6(ByteTbl& Out, IntTbl In, int type);
        bool Write_LUT8(ByteTbl& Out, IntTbl In, int type);
        bool Write_LUT10(ByteTbl& Out, IntTbl In, int type);
        bool Write_LUT12(ByteTbl& Out, IntTbl In, int type);
        bool Write_LUT16(ByteTbl& Out, IntTbl In, int type);
};

//==========================================================//
//         4 Bit                                            //
//==========================================================//
bool ReadWrite_LUT::Read_LUT4(IntTbl& Out, ByteTbl In, int type)
{
        if(type == 1){
                for(int i = 0; i < In.Len; i++){
                        Out.Tbl[i*2] = In.Tbl[i]%16;
                        Out.Tbl[i*2+1] = In.Tbl[i]/16%16;
                }
        }else if(type == 2){
                for(int i = 0; i < In.Len; i++)
                        Out.Tbl[i] = In.Tbl[i]%16;
        }
        return 1;
}
bool ReadWrite_LUT::Write_LUT4(ByteTbl& Out, IntTbl In, int type)
{
        if(type == 1){        //SP_LUT
                for (int i = 0; i < Out.Len; i++){
                        Out.Tbl[i] = In.Tbl[i*2]+ In.Tbl[i*2+1]*16;
                }
        }else if(type == 2){        //SP_LUT
                for (int i = 0; i < Out.Len; i++){
                        Out.Tbl[i] = In.Tbl[i]%16;
                }
        }
        return 1;
}
//==========================================================//
//         5 Bit                                            //
//==========================================================//
// 201007
bool ReadWrite_LUT::Read_LUT5(IntTbl& Out, ByteTbl In, int type)
{
        for(int i = 0; i < In.Len; i++)  //SP_LUT
                Out.Tbl[i] = In.Tbl[i]%32;
        return 1;
}
// 201007
bool ReadWrite_LUT::Write_LUT5(ByteTbl& Out, IntTbl In, int type)
{
        for (int i = 0; i < Out.Len; i++)
                Out.Tbl[i] = In.Tbl[i]%32;
        return 1;
}

//==========================================================//
//         6 Bit                                            //
//==========================================================//

bool ReadWrite_LUT::Read_LUT6(IntTbl& Out, ByteTbl In, int type)
{
        for(int i = 0; i < In.Len; i++)
                Out.Tbl[i] = In.Tbl[i]%64;
        return 1;
}

bool ReadWrite_LUT::Write_LUT6(ByteTbl& Out, IntTbl In,  int type)
{
        if(type == 1){        //SP_LUT
                for (int i = 0; i < Out.Len; i++){
                        Out.Tbl[i] = In.Tbl[i]%64;
                }
        }
        return 1;
}

//==========================================================//
//         8 Bit                                            //
//==========================================================//
bool ReadWrite_LUT::Read_LUT8(IntTbl& Out, ByteTbl In, int type)
{
        for(int i = 0; i <In.Len; i++)
                Out.Tbl[i] = In.Tbl[i];
        return 1;
}
bool ReadWrite_LUT::Write_LUT8(ByteTbl& Out, IntTbl In, int type)
{
        for(int i = 0; i < Out.Len;i++)
                Out.Tbl[i] = In.Tbl[i];
        return 1;
}
//==========================================================//
//         10 Bit                                           //
//==========================================================//

bool ReadWrite_LUT::Read_LUT10(IntTbl& Out, ByteTbl In, int type)
{
        int n_idx;
        if(type == 1){     //CM 10 bit [9:2],[1:0]
                for(int i = 0; i < Out.Len; i++)
                        Out.Tbl[i] = In.Tbl[2*i]+In.Tbl[2*i+1]*4;
        }else if(type == 2){    //CM 10bit [9:8],[7:0]
                for(int i = 0; i < Out.Len; i++)
                        Out.Tbl[i] = In.Tbl[2*i]*256+In.Tbl[2*i+1];
        }else if(type == 3){
                for(int i = 0; i < In.Len; i+=5){
                        n_idx = floor((double)i/5*4); //for Out
                        Out.Tbl[n_idx] = In.Tbl[i]*4+In.Tbl[i+1]/64;
                        if(n_idx+1 < Out.Len){
                                Out.Tbl[n_idx+1] = In.Tbl[i+1]%64*16+In.Tbl[i+2]/16;
                                if(n_idx+2 < Out.Len){
                                        Out.Tbl[n_idx+2] = In.Tbl[i+2]%16*64+In.Tbl[i+3]/4;
                                        if(n_idx+3 < Out.Len){
                                                Out.Tbl[n_idx+3] = In.Tbl[i+3]%4*256+In.Tbl[i+4];
                                        }
                                }
                        }
                }
        }else if(type == 4){     //未測試
                for(int i = 0; i < In.Len; i+=5){
                        n_idx = floor((double)i/5*4);
                        Out.Tbl[n_idx] = In.Tbl[i]+In.Tbl[i+1]%4*256;
                        if(n_idx+1 < Out.Len){
                                Out.Tbl[n_idx+1] = In.Tbl[i+1]/4+In.Tbl[i+2]%16*64;
                                if(n_idx+2 < Out.Len){
                                        Out.Tbl[n_idx+2] = In.Tbl[i+2]/16+In.Tbl[i+3]%64*16;
                                        if(n_idx+3 < Out.Len){
                                                Out.Tbl[n_idx+3] = In.Tbl[i+3]/64+In.Tbl[i+4]*4;
                                        }
                                }
                        }
                }
        }else if(type == 5){    // AUO12307 CM offset
                for(int i = 0; i < Out.Len; i++)
                {
                        if(Out.Len%2==0)
                                Out.Tbl[i] = In.Tbl[3*i]/16*256+In.Tbl[3*i+1];
                        else
                                Out.Tbl[i] = In.Tbl[3*i]%16*256+In.Tbl[3*i+2];
                }
        }else if(type == 6){    // AUO12307 CM set
                for(int i = 0; i < Out.Len; i++)
                {
                        if(Out.Len%2==1)
                                Out.Tbl[i] = In.Tbl[3*i]/16*256+In.Tbl[3*i+1];
                        else
                                Out.Tbl[i] = In.Tbl[3*i]%16*256+In.Tbl[3*i+2];
                }
        }
        return 1;
}

bool ReadWrite_LUT::Write_LUT10(ByteTbl& Out, IntTbl In, int type)
{
        if(type == 1){     //CM 10 bit [9:2],[1:0]
                for(int i = 0; i < In.Len; i++){
                        Out.Tbl[i*2] = In.Tbl[i]/4;
                        Out.Tbl[i*2+1] = In.Tbl[i]%4*64;
                }
        }else if(type == 2){    //CM 10bit [9:8](at low bit)  [7:0]
                for(int i = 0; i < In.Len; i++){
                        Out.Tbl[i*2] = In.Tbl[i]/256;
                        Out.Tbl[i*2+1] = In.Tbl[i]%256;
                }
        }else if(type == 3){       //DG 10 bit
		//Out.Len = ceil((double)In.Len*5/4);
                int remain = In.Len % 4;
                int InCycleLen = In.Len-remain;
                int idx;
                for(int i = 0; i < InCycleLen; i+=4){
                        idx = (int)floor((double)i/4)*5;
                        Out.Tbl[idx] = In.Tbl[i]/4;
                        Out.Tbl[idx+1] = In.Tbl[i]%4*64+In.Tbl[i+1]/16;
                        Out.Tbl[idx+2] = In.Tbl[i+1]%16*16+In.Tbl[i+2]/64;
                        Out.Tbl[idx+3] = In.Tbl[i+2]%64*4+In.Tbl[i+3]/256;
                        Out.Tbl[idx+4] = In.Tbl[i+3]%256;
                }
                if(remain==1){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]/4;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]%4*64;
                }else if(remain==2){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]/4;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]%4*64+In.Tbl[InCycleLen+1]/16;
                        Out.Tbl[idx+2] = In.Tbl[InCycleLen+1]%16*16;
                }else if(remain==3){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]/4;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]%4*64+In.Tbl[InCycleLen+1]/16;
                        Out.Tbl[idx+2] = In.Tbl[InCycleLen+1]%16*16+In.Tbl[InCycleLen+2]/64;
                        Out.Tbl[idx+3] = In.Tbl[InCycleLen+2]%64*4;
                }
        }else if(type == 4){       //DG 10 bit
                //Out.Len = ceil((double)In.Len*5/4);
                int remain = In.Len % 4;
                int InCycleLen = In.Len-remain;
                int idx;
                for(int i = 0; i < InCycleLen; i+=4){
                        idx = (int)floor((double)i/4)*5;
                        Out.Tbl[idx] = In.Tbl[i]%256;
                        Out.Tbl[idx+1] = In.Tbl[i]/256+In.Tbl[i+1]%64*4;
                        Out.Tbl[idx+2] = In.Tbl[i+1]/64+In.Tbl[i+2]%16*16;
                        Out.Tbl[idx+3] = In.Tbl[i+2]/16+In.Tbl[i+3]%4*64;
                        Out.Tbl[idx+4] = In.Tbl[i+3]/4;
                }
                if(remain==1){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]%256;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]/256;
                }else if(remain==2){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]%256;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]/256+In.Tbl[InCycleLen+1]%64*4;
                        Out.Tbl[idx+2] = In.Tbl[InCycleLen+1]/64;
                }else if(remain==3){
                        idx = (int)floor((double)InCycleLen/4)*5;
                        Out.Tbl[idx] = In.Tbl[InCycleLen]%256;
                        Out.Tbl[idx+1] = In.Tbl[InCycleLen]/256+In.Tbl[InCycleLen+1]%64*4;
                        Out.Tbl[idx+2] = In.Tbl[InCycleLen+1]/64+In.Tbl[InCycleLen+2]%16*16;
                        Out.Tbl[idx+3] = In.Tbl[InCycleLen+2]/16;
                }
        }
        return 1;
}

//==========================================================//
//         12 Bit                                           //
//==========================================================//

bool ReadWrite_LUT::Read_LUT12(IntTbl& Out, ByteTbl In, int type)
{
        //int idx;
        int n_idx;
        if (type == 1){
                n_idx = 0;
                for(int i = 0; i < In.Len; i+=3,n_idx+=2){
                        Out.Tbl[n_idx] = In.Tbl[i]+In.Tbl[i+1]%16*256;
                        if(n_idx+1<Out.Len)
                                Out.Tbl[n_idx+1] =In.Tbl[i+1]/16;
                        if(i+2<In.Len){
                                Out.Tbl[n_idx+1] += In.Tbl[i+2]*16;
                        }
                }
                if(Out.Len==257){    // for DG
                        int bit_13 = 0;
                        if((In.Tbl[In.Len-1]/16)%2==1)
                                bit_13 = 1;
                        Out.Tbl[Out.Len-1] += (bit_13)*pow(2,12);
                }
        }else if (type == 2){
                n_idx = 0;
                for(int i = 0; i < In.Len; i+=3,n_idx+=2){
                        Out.Tbl[n_idx] = In.Tbl[i]*16 + In.Tbl[i+1]/16%16;
                        if(n_idx+1<Out.Len)
                                Out.Tbl[n_idx+1] = In.Tbl[i+1]%16*256;
                        if(i+2<In.Len){
                                Out.Tbl[n_idx+1] += In.Tbl[i+2];
                        }
                }
        }
        return 1;
}

bool ReadWrite_LUT::Write_LUT12(ByteTbl& Out, IntTbl In, int type)
{
	if(type == 1){      //DG 12 bit //3D LUT
                int remain = In.Len % 2;
                //Out.Len = ceil((double)In.Len*3/2);
		int InCycleLen = In.Len-remain;
		int idx = 0;

                for(int i = 0; i < InCycleLen; i=i+2){
                        Out.Tbl[idx] = In.Tbl[i]%256;
                        Out.Tbl[idx+1] = In.Tbl[i+1]%16*16+In.Tbl[i]/256;
                        Out.Tbl[idx+2] = In.Tbl[i+1]/16;
                        idx += 3;
                }

                if(remain==1){
                        Out.Tbl[Out.Len-2] = In.Tbl[InCycleLen]%256;
                        Out.Tbl[Out.Len-1] = In.Tbl[InCycleLen]/256;
                              /* // String str = "Last 2 LUT:"+Out.Tbl[Byte_num-1]+""+Out.Tbl[Byte_num-2];
                                char str[1000];
                                sprintf(str,"Write last 2 table value %d, %d", Out.Tbl[Byte_num-1],Out.Tbl[Byte_num-2]);
                                ShowMessage((String)str); */
                } 
        }else if(type == 2){      //DCR DIM LUT (因為BL table為8 bit, 實際使用的code在dcr1.cpp)
                int remain = In.Len % 2;
				//Out.Len = ceil((double)In.Len*3/2);
		int InCycleLen = In.Len-remain;
                int idx = 0;
                for(int i = 0; i < InCycleLen; i=i+2){
                        Out.Tbl[idx] = In.Tbl[i]/16;
                        Out.Tbl[idx+1] = In.Tbl[i]%16*16+In.Tbl[i+1]/256;
                        Out.Tbl[idx+2] = In.Tbl[i+1]%256;
                        idx += 3;
                }
                if(remain==1){
                        Out.Tbl[Out.Len-2] = In.Tbl[InCycleLen]/16;
                        Out.Tbl[Out.Len-1] = In.Tbl[InCycleLen]%16*16;
                }
       }
	   return 1;
}
//==========================================================//
//         16 Bit                                           //
//==========================================================//

bool ReadWrite_LUT::Read_LUT16(IntTbl& Out, ByteTbl In, int type)
{
        if(type == 1){
                for(int i = 0; i < Out.Len; i++){
                        Out.Tbl[i] = In.Tbl[i*2]*256+In.Tbl[i*2+1];
                }
        }else if(type == 2){ // 201007
                for(int i = 0; i < Out.Len; i++){
                         Out.Tbl[i] = In.Tbl[i*2]+In.Tbl[i*2+1]*256;
                }
        }
        return 1;
}

bool ReadWrite_LUT::Write_LUT16(ByteTbl& Out, IntTbl In,  int type)
{
        if(type == 1){
                for(int i = 0; i < In.Len; i++){
                        Out.Tbl[i*2] = In.Tbl[i]/256;
                        Out.Tbl[i*2+1] = In.Tbl[i]%256;
                }
        }else if(type == 2){     // 201007
                for(int i = 0; i < In.Len; i++){
                        Out.Tbl[i*2+1] = In.Tbl[i]/256;
                        Out.Tbl[i*2] = In.Tbl[i]%256;
                }
        }
	return 1;
}


#endif