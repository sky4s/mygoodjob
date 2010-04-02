//---------------------------------------------------------------------------


#ifndef TOutputFileFrameH
#define TOutputFileFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
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
  public:			// User declarations
     __fastcall TOutputFileFrame(TComponent * Owner);
    void createDir();
    AnsiString getFullPrefix();
};
//---------------------------------------------------------------------------
extern PACKAGE TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
#endif

