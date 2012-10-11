//---------------------------------------------------------------------------
//    20100608 增加C3D Form
//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <vcl.h>
#include <ComCtrls.hpp>

//C系統文件
#include <stdio.h>
//C++系統文件

//vcl庫頭文件

//其他庫頭文件
#include <windows.h>
#include <Dialogs.hpp>
//本項目內頭文件
#include <addresstype/Address_type.h>
#include "gui_class.h"

//本項目內gui頭文件
//#include <colorip/gui/TSharpnessV1Form.h>
//#include <colorip/gui/TSharpnessV2Form.h>
#include <colorip/gui/ContrastEnhance1.h>

//---------------------------------------------------------------------------
class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *mn_Engineer;
    TMenuItem *mn_TCON;
    TMenuItem *mn_Function;
    TMenuItem *mn_DCR;
    TMenuItem *mn_Vender;
    TMenuItem *Device1;
    TMenuItem *mn_ImageProc;
    TMenuItem *mn_CM;
    TMenuItem *mn_Sharpness;
    TMenuItem *mn_CE;
    TPopupMenu *PopupMenu1;
    TMenuItem *popupmenu2;
    TMenuItem *Function1;
    TMenuItem *DCR1;
    TMenuItem *Vender1;
    TMenuItem *ImageProcess1;
    TMenuItem *ColorMatrix1;
    TMenuItem *Sharpness1;
    TMenuItem *ContrastEnhancement1;
    TStatusBar *StatusBar1;
    TMenuItem *AUO_12303;
    TMenuItem *mn_C3D;
    TMenuItem *C3D1;
    TMenuItem *AUO_11307;
    TMenuItem *mn_C3D_777;
    TMenuItem *mn_C3D_999;
    TMenuItem *mn_SAT;
    TMenuItem *mn_offset;
        TMenuItem *header2Address;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
        TMenuItem *loadAddressFromFile;
    TMenuItem *mn_HSV2;
    TMenuItem *HSV1;
    TMenuItem *mn_Sharpness12307;
    TMenuItem *Test1;
    TMenuItem *Example2;
    TMenuItem *Sharpness2;
        TMenuItem *Sharpnessv211;
    void __fastcall mn_TCONClick(TObject * Sender);
    void __fastcall mn_EngineerClick(TObject * Sender);
    void __fastcall mn_FunctionClick(TObject * Sender);
    void __fastcall mn_DCRClick(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall mn_VenderClick(TObject * Sender);
    void __fastcall AUO_11307Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall mn_CMClick(TObject * Sender);
    void __fastcall FormMouseDown(TObject * Sender, TMouseButton Button,
				  TShiftState Shift, int X, int Y);
    void __fastcall mn_SharpnessClick(TObject * Sender);
    void __fastcall mn_CEClick(TObject * Sender);
    void __fastcall mn_HSVClick(TObject * Sender);
    void __fastcall StatusBar1DblClick(TObject * Sender);
    void __fastcall AUO_12303Click(TObject * Sender);
    void __fastcall mn_C3DClick(TObject * Sender);
    void __fastcall mn_C3D_777Click(TObject * Sender);
    void __fastcall mn_C3D_999Click(TObject * Sender);
    void __fastcall mn_SATClick(TObject * Sender);
    void __fastcall mn_offsetClick(TObject * Sender);
    void __fastcall header2AddressClick(TObject * Sender);
    void __fastcall loadAddressFromFileClick(TObject * Sender);
    void __fastcall mn_HSV2Click(TObject * Sender);
    void __fastcall HSV1Click(TObject * Sender);
    void __fastcall mn_Sharpness12307Click(TObject * Sender);
    void __fastcall Sharpness2Click(TObject * Sender);
    void __fastcall Example2Click(TObject * Sender);
        void __fastcall Sharpnessv211Click(TObject *Sender);

  private:			// User declarations
     String getFileVersionInfo();
    void header2AddressFile(const AnsiString & header, const AnsiString & address);
    void closeAllForms();
    void setAddressFile(AnsiString filename);
  public:			// User declarations
     __fastcall TMainForm(TComponent * Owner);
    int C3D_type;
    void reload_all(TObject * Sender);
    void TCONFormNULL();
    void FunctionFormNULL();
    void DCRFormNULL();
    void VenderFormNULL();
    void CMFormNULL();
    void SharpnessFormNULL();
    void ContrastEnhanceFormNULL();
    void HSVFormNULL();
    void C3DFormNULL();
    void SATFormNULL();
    void offsetFormNULL();

 
    bool addressFromFile;
    static AnsiString AddressFile;

};


//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

