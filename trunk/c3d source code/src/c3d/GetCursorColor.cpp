#include <vcl.h>
#pragma hdrstop
#include "GetCursorColor.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
#include <gui\c3d\TMainForm.h>
#include <gui/c3d/TC3DForm.h>

#pragma package(smart_init)

//---------------------------------------------------------------------------                       //---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TPColorThread1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TPColorThread1::TPColorThread1(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void TPColorThread1::SetName()
{
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = "PColorThread1";
        info.dwThreadID = -1;
        info.dwFlags = 0;

        __try
        {
                 RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
        }
        __except (EXCEPTION_CONTINUE_EXECUTION)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TPColorThread1::Execute()
{
        SetName();
        //---- Place thread code here ----
        while(! Terminated )
        {
          //Sleep(5);    // Delay program execution for 5 microseconds.
                HDC TargethDC;
	        HWND TargetHwnd;
	        DWORD ColorR;

	        TargetHwnd = GetDesktopWindow();
	        TargethDC = GetWindowDC(NULL);

	        POINT lp;
                POINT gMouse;
                GetCursorPos(&lp);

	        //ClientToScreen(TargetHwnd, &lp);
	        ColorR = GetPixel(TargethDC, lp.x, lp.y);
	        ReleaseDC(TargetHwnd,TargethDC);

	        int r = GetRValue(ColorR);
	        int g = GetGValue(ColorR);
	        int b = GetBValue(ColorR);
                C3DForm1->Edit1->Text = "R:"+IntToStr(r)+", G:"+IntToStr(g)+", B:"+IntToStr(b);
                Sleep(50);
        }
}
//---------------------------------------------------------------------------
/*
static HHOOK hHook,hMouseHook;
int ncode;
LRESULT CALLBACK MouseHook(int iCode, WPARAM wParam, LPARAM lParam)
{
    if(iCode < 0){
    CallNextHookEx(hMouseHook, iCode, wParam, lParam);
    return 1;
    }
    else if ( ncode==HC_ACTION ) {
    EVENTMSG* pEventMsg = (EVENTMSG*)lParam;
    if ( pEventMsg->message==WM_LBUTTONDOWN ) { // 處理 mouse down
        ShowMessage("Mouse Hook");// 自己要處理的部份
    }    ;
    } return NULL;
} */
