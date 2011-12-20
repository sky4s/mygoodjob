//---------------------------------------------------------------------------


#ifndef TOutputFileFrameH
#define TOutputFileFrameH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//�����ؤ��Y���
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
    TLabel *Label_Warning;
    void __fastcall Button_BrowseDirClick(TObject * Sender);
    void __fastcall Edit_PrefixChange(TObject * Sender);
    void __fastcall Edit_DirectoryChange(TObject * Sender);
  private:			// User declarations
    int serialid;

    String_ptr _getOutputFilename();
  public:			// User declarations
     __fastcall TOutputFileFrame(TComponent * Owner);
    bool createDir();
    String_ptr getFullPrefix();
    String_ptr getOutputFilename();
    void updateWarning();
};
//---------------------------------------------------------------------------
extern PACKAGE TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
#endif

