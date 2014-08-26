//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "WinIO.h"
//---------------------------------------------------------------------------
unsigned char  inportbNT(unsigned short p) { asm mov dx, p; asm in al, dx; return _AL; }
unsigned short inportwNT(unsigned short p) { asm mov dx, p; asm in ax, dx; return _AX; }
unsigned long  inportdNT(unsigned short p) { asm mov dx, p; asm in eax,dx; return _EAX;}
void outportbNT(unsigned short p, unsigned char  v) { asm mov dx, p; asm mov al, v; asm out dx,al; }
void outportwNT(unsigned short p, unsigned short v) { asm mov dx, p; asm mov ax, v; asm out dx,ax; }
void outportdNT(unsigned short p, unsigned long  v) { asm mov dx, p; asm mov eax,v; asm out dx,eax;}
//---------------------------------------------------------------------------
unsigned char  inportb9x(unsigned short p) { unsigned long v = 0; GetPortVal(p, &v, 1); return v; }
unsigned short inportw9x(unsigned short p) { unsigned long v = 0; GetPortVal(p, &v, 2); return v; }
unsigned long  inportd9x(unsigned short p) { unsigned long v = 0; GetPortVal(p, &v, 4); return v; }
void outportb9x(unsigned short p, unsigned char  v) { SetPortVal(p,v,1); }
void outportw9x(unsigned short p, unsigned short v) { SetPortVal(p,v,2); }
void outportd9x(unsigned short p, unsigned long  v) { SetPortVal(p,v,4); }
//---------------------------------------------------------------------------
unsigned char  (*inportb)(unsigned short) = inportbNT;
unsigned short (*inportw)(unsigned short) = inportwNT;
unsigned long  (*inportd)(unsigned short) = inportdNT;
void (*outportb)(unsigned short, unsigned char ) = outportbNT;
void (*outportw)(unsigned short, unsigned short) = outportwNT;
void (*outportd)(unsigned short, unsigned long ) = outportdNT;
//---------------------------------------------------------------------------
void InitPortFuncs(void)
{
  OSVERSIONINFO osVer = {sizeof(OSVERSIONINFO)};
  GetVersionEx(&osVer);

  if(osVer.dwPlatformId == VER_PLATFORM_WIN32_NT)
   {
     inportb = inportbNT; outportb = outportbNT;
     inportw = inportwNT; outportw = outportwNT;
     inportd = inportdNT; outportd = outportdNT;
   }
  else
   {
     inportb = inportb9x; outportb = outportb9x;
     inportw = inportw9x; outportw = outportw9x;
     inportd = inportd9x; outportd = outportd9x;
   }
}
//---------------------------------------------------------------------------
bool ReadHddParams(unsigned short *params, int pn, int dn)
{
}
//---------------------------------------------------------------------------
void WordToStr(unsigned char *s, unsigned short *w, int n)
{

}
//---------------------------------------------------------------------------

