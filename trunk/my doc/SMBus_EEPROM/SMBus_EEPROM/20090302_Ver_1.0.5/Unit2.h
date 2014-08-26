//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
extern unsigned char  (*inportb)(unsigned short);
extern unsigned short (*inportw)(unsigned short);
extern unsigned long  (*inportd)(unsigned short);
extern void (*outportb)(unsigned short, unsigned char );
extern void (*outportw)(unsigned short, unsigned short);
extern void (*outportd)(unsigned short, unsigned long );
//---------------------------------------------------------------------------
extern void InitPortFuncs(void);
//---------------------------------------------------------------------------
#endif
 