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

//C++系統文件

//vcl庫頭文件

//其他庫頭文件
#include <windows.h>
//本項目內頭文件
#include <addresstype/Address_type.h>
#include "gui_class.h"

//本項目內gui頭文件
#include "Engineering.h"
#include "TCON1.h"
#include "Function1.h"
#include "DCR1.h"
#include "Vender1.h"
#include "CM1.h"
#include "Sharpness1.h"
#include "ContrastEnhance1.h"
#include "HueSatVal1.h"
#include "C3D1.h"
#include "SAT.h"
#include "Offset.h"

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
    TMenuItem *mn_HSV;
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
    TCheckBox *cb_address_txt;
    TMenuItem *AUO_12303;
    TMenuItem *mn_C3D;
    TMenuItem *C3D1;
    TMenuItem *AUO_11307;
    TMenuItem *mn_C3D_777;
    TMenuItem *mn_C3D_999;
    TMenuItem *mn_SAT;
    TMenuItem *mn_offset;
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
    void __fastcall cb_address_txtClick(TObject * Sender);
    void __fastcall StatusBar1DblClick(TObject * Sender);
    void __fastcall AUO_12303Click(TObject * Sender);
    void __fastcall mn_C3DClick(TObject * Sender);
    void __fastcall mn_C3D_777Click(TObject * Sender);
    void __fastcall mn_C3D_999Click(TObject * Sender);
    void __fastcall mn_SATClick(TObject * Sender);
    void __fastcall mn_offsetClick(TObject * Sender);

  private:			// User declarations
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
    String TCON_DEV;
    int addr_place;		//0:auo_12401_address.h   1:auo_12401_address.txt

};
char *Load_File(String Fpath)
{
    long lSize;
    char *buffer;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "r")) == NULL)
	return 0;

    // obtain file size:
    fseek(fptr, 0, SEEK_END);
    lSize = ftell(fptr);
    rewind(fptr);

    // allocate memory to contain the whole file:
    buffer = new char[lSize + 1];
    if (buffer == NULL)
	return 0;
    // copy the file into the buffer:
    fread(buffer, 1, lSize, fptr);
    buffer[lSize] = '\0';
    fclose(fptr);
    return buffer;
}

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

