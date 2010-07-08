//---------------------------------------------------------------------------


#ifndef TOutputFileFrameH
#define TOutputFileFrameH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
#include <java/lang.h>

//---------------------------------------------------------------------------
class TOutputFileFrame:public TFrame {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox_OutputFile;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_Prefix;
    TEdit *Edit_Directory;
    TButton *Button_BrowseDir;
    void __fastcall Button_BrowseDirClick(TObject * Sender);
  private:			// User declarations
    int serialid;
  public:			// User declarations
     __fastcall TOutputFileFrame(TComponent * Owner);
    bool createDir();
    String_ptr getFullPrefix();
    String_ptr getOutputFilename();
};
//---------------------------------------------------------------------------
extern PACKAGE TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
#endif

