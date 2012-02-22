//----------------------------------------------------------------------------
#ifndef TAboutBoxH
#define TAboutBoxH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TAboutBox:public TForm {
    __published:TPanel * Panel1;
    TLabel *ProductName;
    TLabel *Version;
    TLabel *Copyright;
    TLabel *Comments;
    TButton *OKButton;
    TImage *Image1;
    TMemo *Memo1;
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall FormCreate(TObject * Sender);
  private:
  public:
     virtual __fastcall TAboutBox(TComponent * AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif

