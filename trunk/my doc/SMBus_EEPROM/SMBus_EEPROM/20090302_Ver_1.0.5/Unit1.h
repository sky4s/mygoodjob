//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <IniFiles.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
typedef struct
{
    AnsiString  Sou_File_Name; // in TestConfigIni.ini Set for Name Display
    AnsiString  Sou_File_Path; // for Path Display
    AnsiString  Sou_File_Path_Name; // for fread
    AnsiString  Sav_File_Path_Name; // for fwrite
    AnsiString I2C_Device_Address; // in TestConfigIni.ini Set
    int Burn_in_Set_Option; // in TestConfigIni.ini Set
    int IO_Delay_Time; // in TestConfigIni.ini Set
    int Save_To_BackUp; // in TestConfigIni.ini Set
}TestConfigIni;
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label5;
        TLabel *Label3;
        TLabel *Label4;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TMemo *BefBurnin_Info;
        TMemo *AftBurnin_Info;
        TPanel *Panel1;
        TCheckBox *CheckBox1;
        TEdit *Edit1;
        TEdit *Edit2;
        TBitBtn *BitBtn4;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TMemo *SouFile_Info;
        TBitBtn *BitBtn1;
        TOpenDialog *OpenDialog1;
        TBitBtn *BitBtn2;
        TLabel *Label7;
        TEdit *Edit3;
        TBitBtn *BitBtn3;
        TLabel *Label8;
        TEdit *Edit4;
        TLabel *Label10;
        TEdit *Edit6;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit7;
        TEdit *Edit8;
        TLabel *Label9;
        TEdit *Edit9;
        TBitBtn *BitBtn5;
        TPanel *Panel2;
        TCheckBox *CheckBox2;
        TBitBtn *BitBtn6;
        TSaveDialog *SaveDialog1;
        TImage *Image1;
        TLabel *Label13;
        TEdit *Edit5;
        TPanel *Panel3;
        TCheckBox *CheckBox3;
        TBitBtn *BitBtn7;
        TBitBtn *BitBtn8;
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall Edit6KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Edit7KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Edit8KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BitBtn8Click(TObject *Sender);
private:	// User declarations
        bool bWinIoInitOK;
        int I2CReadRegByte(unsigned int SMBusBase, int I2CDeviceAddress, int I2CDeviceReg, int *I2CRegValue5);
        int I2CWriteRegByte(unsigned int SMBusBase, int I2CDeviceAddress, int I2CDeviceReg, int WriteValue);
        int IN_Port_Long(unsigned long PortBase, int PortOffset, unsigned long *PortRegValue);
        int Out_Port_Long(unsigned long PortBase, int PortOffset, int PortRegValue);
        int AtoiHex(char s[]);
        unsigned long LongAtoiDcb(char s[]);
        bool AtoiIntCHK(char s[]);
        void ReadSourceFile(void);
        void Set_Object_Property(void);
        void Object_Property_Recovery(void);
        void Object_Property_Disabled(void);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        TestConfigIni TestConfigIniFile;
        int PassFlag;
        unsigned long SMBusIOBase;
        int Sou_Data[256], Read_String[256];
        bool Object_Property[12];
        bool SaveFlag, CompareFlag;
        };
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
