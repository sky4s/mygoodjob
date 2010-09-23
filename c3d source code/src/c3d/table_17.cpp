//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
        int TBL_SIZE = 17;
        int Ratio = 16;
        int r[4913], g[4913], b[4913];
        int idx = 0;

	for(int k = 0; k < TBL_SIZE; k+=2)
                for(int j = 0; j < TBL_SIZE; j+=2)
                        for(int i = 0; i < TBL_SIZE; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                         }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 0; i <TBL_SIZE; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                         }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-0; i+=2){
                                r[idx] = i*Ratio;
                                g[idx] = j*Ratio;
                                b[idx] = k*Ratio;
                                idx++;
                        }

        FILE* stream = fopen("17x17x17.txt", "w");
        for(int i = 0; i < 4913; i++)
                fprintf(stream,"%d\t%d\t%d\n",r[i],g[i],b[i]);
        fclose(stream);
        return 0;
}
//---------------------------------------------------------------------------
