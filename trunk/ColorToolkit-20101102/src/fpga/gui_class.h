#ifndef GUI_CLASSH
#define GUI_CLASSH

#include <vcl.h>
#include <addresstype/Address_type.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#include <stdio.h>

/*
  對應不同的TBit
  check box: 1bit
  combo box: 1/2bit  + TLabel(for name)
  label edit : 1/2/3/4bit
  scroll bar: 1/2bit + TLabel(for name) + TStaticText

  附屬項中, TLabel會為定值, 僅顯示name; TStaticText則被動顯示ScrollBar的結果

  目前的想法為:
  一個RegisterFramework的Class統整 RegisterType和UI的繫結
  RegisterType包括BitRegister和LUTRegister
  只要透過 RegisterFramework.bind("reg name",CheckBox)
  和RegisterFramework.bind("reg name",ComboBox,"option1","option2"...)
  兩隻函式就可以繫結 register<=>UI

  
*/

class _CHKB {
  public:
    __fastcall ~ _CHKB() {
	delete[]Chkb;		//多此一舉? bcb應該自己會關掉vcl
    };
    TCheckBox *Chkb;
    TBit Addr;			//應該一個新的形態, 直接包了_CHKB和TBbit, 或者說, 僅揭露_CHKB對外
};


class _CBOB {
  public:
    __fastcall ~ _CBOB() {
	delete[]Cbob;
	delete[] CbobL;
    };
    TComboBox *Cbob;
    TLabel *CbobL;
    TBit Addr;
};


class _CBOB2			//Address 為 2Byte
{
  public:
    __fastcall ~ _CBOB2() {
	delete[]Cbob;
	delete[] CbobL;
	//delete Addr.choice;
    };
    TComboBox *Cbob;
    TLabel *CbobL;
    TBit2 Addr;
};


class _LBLE4			//Address 為 4Byte
{
  public:
    __fastcall ~ _LBLE4() {
	delete[]Lble;
	//delete Addr.choice;
    };
    TLabeledEdit *Lble;
    TBit4 Addr;
};

class _LBLE3			//Address 為 3Byte
{
  public:
    __fastcall ~ _LBLE3() {
	delete[]Lble;
	//delete Addr.choice;
    };
    TLabeledEdit *Lble;
    TBit3 Addr;
};


class _LBLE2			//Address 為 2Byte
{
  public:
    __fastcall ~ _LBLE2() {
	delete[]Lble;
	//delete Addr.choice;
    };
    TLabeledEdit *Lble;
    TBit2 Addr;
};

class _LBLE			//Address 為 1 byte
{
  public:
    __fastcall ~ _LBLE() {
	delete[]Lble;
	//delete Addr.choice;
    };
    TLabeledEdit *Lble;
    TBit Addr;
};


class _ScrollBar2		//Address 為 2Byte
{
  public:
    __fastcall ~ _ScrollBar2() {
	delete[]Lbl;
	delete[] StTxt;
	delete[] ScrlB;
	//delete Addr.choice;
    };
    TLabel *Lbl;
    TScrollBar *ScrlB;
    TStaticText *StTxt;
    TBit2 Addr;
};

class _ScrollBar		//Address 為 1 byte
{
  public:
    __fastcall ~ _ScrollBar() {
	delete[]Lbl;
	delete[] StTxt;
	delete[] ScrlB;
	//delete Addr.choice;
    };
    TLabel *Lbl;
    TScrollBar *ScrlB;
    TStaticText *StTxt;
    TBit Addr;
};



class AbstractBase {
  private:
    static StringMap_ptr map;
    static StringMap_ptr aliasNameMap;
    static void initAliasNameMap();
    static int_vector_ptr getRegisterIntVector(string_vector_ptr registerTokens);
    static std::string AliasFilename;
  protected:

    static bool setAddress(AbstractAddressType * address, std::string text);
    static bool setAddressFromFile(AbstractAddressType * address, std::string tag);

  public:

    static AbstractAddress_ptr getAddress(std::string tag);
    static AbstractAddressType *getAddress2(std::string tag);
    static int_vector_ptr getValuesFromFile(std::string tag);
    static int getValueFromFile(std::string tag);
    static bool hasValueInFile(std::string tag);
    static void resetAddressMap();
    static StringMap_ptr getStringMap(std::string filename);
    static StringMap_ptr getStringMap(AnsiString filename);
};


class AbstHSV:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TLUT *SetLUT() = 0;
    virtual String HSV_EN_Name() = 0;	// 20100608 return the name of HSV_EN register
    int HSVChkBox_Nbr;
};



char *Load_File(String Fpath)
{
    long lSize;
    char *buffer;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "r")) == NULL) {
	return 0;
    }
    // obtain file size:
    fseek(fptr, 0, SEEK_END);
    lSize = ftell(fptr);
    rewind(fptr);

    // allocate memory to contain the whole file:
    buffer = new char[lSize + 1];
    if (buffer == NULL) {
	return 0;
    }
    // copy the file into the buffer:
    fread(buffer, 1, lSize, fptr);
    buffer[lSize] = '\0';
    fclose(fptr);
    return buffer;
}

/*==========================================================================
AbstSP為一自定的class, 具有可傳回IC中關於Sharpness address定義的函式
===========================================================================*/
class AbstSP:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;	//傳回CheckBox的address定義
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;	//傳回ScrollBar的address定義
    virtual TBit2 *SetLblE2() = 0;	// Add by Michelle 20100702
    virtual TBit3 *SetLblE3() = 0;	// Add by Michelle 20100702
    virtual TLUT *SetSPLUT() = 0;	//傳回sharpness lookup table的address定義

    int SPChkBox_Nbr;
    int SPCboBox_Nbr;
    int SPScrollBar;
    int SPLblE2_Nbr;		// Add by Michelle  20100702
    int SPLblE3_Nbr;
    int SPScrollBar_Nbr;
};

class AbstCE:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;
    virtual TLUT *SetJNDlut() = 0;
    virtual TLUT *SetSTlut() = 0;
    virtual TLUT *SetMAXlut() = 0;
    virtual TLUT *SetMINlut() = 0;
    int CEChkBox_Nbr;
    int CECboBox_Nbr;
    int CEScrollBar_Nbr;
};

/*==========================================================================
AbstCM為一自定的class, 具有可傳回IC中關於Color Matrix address定義的函式
===========================================================================*/

class AbstCM:public AbstractBase {
  public:
    //CM
    virtual TBit * SetChkBx() = 0;	//傳回CheckBox的address定義
    virtual TBit *SetCboBx() = 0;	//傳回ComboBox的address定義
    virtual TLUT *Setval() = 0;	//傳回3組CM的address定義
    virtual TLUT *Setofs() = 0;	//傳回3組offset的address定義
    virtual int Setofs_type() = 0;
    //傳回offset address的type 1: offset range(-127.75,127.75)
    //type 2:offset range(-63.875,63.875)

    int CMChkBox_Nbr;
    int CMCboBox_Nbr;
    int CMval_Nbr;
    int CMofs_Nbr;
};

//---------------------------------------------------------------------------
//Abstract class of Vender
class AbstVender:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;
    virtual TBit2 *SetScrollBar2() = 0;

    virtual TBit *SetDebugChkBx() = 0;
    virtual TBit *SetDebugCboBx() = 0;
    virtual TBit2 *SetDebugLblE2() = 0;

    virtual TBit *SetStaCboBx() = 0;
    virtual TBit2 *SetStaLblE2() = 0;
    virtual TBit2 *SetLblE2() = 0;

    int VendChkBox_Nbr;
    int VendCboBox_Nbr;
    int VendScrollBar_Nbr;
    int VendScrollBar2_Nbr;
    int VendLblE2_Nbr;
    int DebugChkBox_Nbr;
    int DebugCboBox_Nbr;
    int DebugLblE2_Nbr;
    int VStaCboBox_Nbr;
    int VStaLblE2_Nbr;
};

//Abstract class of TCON
class AbstTCON:public AbstractBase {
  public:
    //device
    virtual TBit * SetDevChkBx() = 0;
    virtual TBit *SetDevCboBx() = 0;
    virtual TBit2 *SetDevLblE2() = 0;

    //status
    virtual TBit *SetStaCboBx() = 0;
    virtual TBit2 *SetStaLblE2() = 0;

    //Input/Output
    virtual TBit *SetIOChkBx() = 0;
    virtual TBit *SetIOCboBx() = 0;
    //Driving
    virtual TBit *SetDrvChkBx() = 0;
    virtual TBit *SetDrvCboBx() = 0;
    virtual TBit2 *SetDrvLblE() = 0;
    virtual TBit3 *SetDrvLblE3() = 0;	//Add by Michelle 20100625
    //Timing
    virtual TBit2 *SetTimLblE2() = 0;
    virtual TBit3 *SetTimLblE3() = 0;

    int DevChkBox_Nbr;		//Number of CheckBox in device page
    int DevCboBox_Nbr;		//Number of ComboBox in device page
    int DevLblE2_Nbr;

    int IOChkBox_Nbr;		//Number of CheckBox in input/output page
    int IOCboBox_Nbr;		//Number of ComboBox in input/output page

    int DrvChkBox_Nbr;		//Number of CheckBox in Driving page
    int DrvCboBox_Nbr;		//Number of ComboBox in Driving page
    int DrvLblE2_Nbr;		//Number of LabeledEdit in Driving page
    int DrvLblE3_Nbr;

    int TimLblE2_Nbr;		//Number of LabeledEdit2 in Timing page
    int TimLblE3_Nbr;
    int StaCboBox_Nbr;
    int StaLblE2_Nbr;
};

//Abstract class of FunctionForm
class AbstFunc:public AbstractBase {
  public:
    //frc_dg
    virtual TBit * SetFrcDgChkBx() = 0;
    virtual TBit *SetFrcDgCboBx() = 0;
    virtual TBit *SetFrcDgLblE() = 0;
    virtual TLUT *SetDGLUT() = 0;
    virtual String DG_EN_Name() = 0;

    //P-state
    virtual TBit *SetPstateChkBx() = 0;
    virtual TBit *SetPstateCboBx() = 0;
    virtual TBit2 *SetPstateLblE2() = 0;

    //AGBS
    virtual TBit *SetAGBSChkBx() = 0;
    virtual TBit *SetAGBSCboBx() = 0;
    virtual TBit2 *SetAGBSLblE2() = 0;

    //OD
    virtual TBit *SetODChkBx() = 0;
    virtual TBit *SetODCboBx() = 0;
    virtual TBit2 *SetODCboBx2() = 0;
    virtual TBit *SetODScrollBar() = 0;
    virtual TLUT *SetODLUT() = 0;
    virtual String OD_EN_Name() = 0;
    virtual int ODLUT_IP_Type() = 0;

    // OD table Address Arrange
    // ODLUT_IP_Type 1: AUO IP ,
    // ODLUT_IP_Type 2: Vender IP

    int PstateChkBox_Nbr;	//Number of CheckBox in Pstate page
    int PstateCboBox_Nbr;	//Number of ComboBox in Pstate page
    int PstateLblE2_Nbr;	//Number of LabeledEdit2 in Pstate page

    int AGBSChkBox_Nbr;		//Number of CheckBox in AGBS page
    int AGBSCboBox_Nbr;		//Number of ComboBox in AGBS page
    int AGBSLblE2_Nbr;		//Number of LabeledEdit2 in AGBS page

    int FrcDgChkBox_Nbr;	//Number of CheckBox in FrcDg page
    int FrcDgCboBox_Nbr;	//Number of ComboBox in FrcDg page
    int FrcDgLblE_Nbr;		//Number of LabeledEdit in FrcDg page
    int DGLUT_Nbr;

    int ODChkBox_Nbr;		//Number of CheckBox in OD page
    int ODCboBox_Nbr;		//Number of ComboBox in OD page
    int ODCboBox2_Nbr;		//Number of ComboBox2 in OD page
    int ODScrollBar_Nbr;	//Number of ScrollBar in OD page

};

//Abstract class of DCR
class AbstDCR:public AbstractBase {
  public:
    //DCR setting
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;

    virtual TBit *SetScrollBar() = 0;
    virtual TBit2 *SetScrollBar2() = 0;

    virtual TLUT *SetLUT() = 0;
    virtual TBit3 *SetLblE3() = 0;

    virtual TBit2 *SetDCRLblE2() = 0;

    //ALS SMBUS
    virtual TBit *SetALSChkBx() = 0;
    virtual TBit *SetALSCboBx() = 0;
    virtual TBit *SetALSScrollBar() = 0;
    //HDR
    virtual TBit *SetHDRCboBx() = 0;
    virtual TBit *SetHDRScrollBar() = 0;
    virtual TBit2 *SetHDRScrollBar2() = 0;
    virtual TBit2 *SetHDRLblE2() = 0;

    virtual String DCR_BL_EN_Name() = 0;	// 20100608 return the name of BL_EN register
    virtual String DCR_GLT_EN_Name() = 0;	// 20100608 return the name of GLT_EN register

    int DCRScrollBar_Nbr;
    int DCRScrollBar2_Nbr;

    int DCRCboBox_Nbr;
    int DCRChkBox_Nbr;
    int DCRLblE3_Nbr;
    int DCRLblE2_Nbr;

    int ALSScrollBar_Nbr;
    int ALSChkBox_Nbr;
    int ALSCboBox_Nbr;

    int HDRCboBox_Nbr;
    int HDRScrollBar_Nbr;
    int HDRScrollBar2_Nbr;
    int HDRLblE2_Nbr;
    int DCRLUT_Nbr;		// 20100608 set number of DCR table
};
class AbstC3D:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TLUT *SetLUT() = 0;
    virtual String C3D_EN_Name() = 0;	// 20100608 return the name of C3D enable register
    int C3DChkBox_Nbr;
    int C3DLUT_Nbr;
};

//Abstract class of SATForm
class AbstSATForm:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;
    virtual TBit2 *SetScrollBar2() = 0;
    virtual TBit3 *SetLblE3() = 0;
    virtual TBit4 *SetLblE4() = 0;

    int ScrollBar_Nbr;
    int ScrollBar2_Nbr;
    int CboBox_Nbr;
    int ChkBox_Nbr;
    int LblE3_Nbr;
    int LblE4_Nbr;
};

//Abstract class of offsetForm
class AbstoffsetForm:public AbstractBase {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;
    virtual TBit2 *SetScrollBar2() = 0;
    virtual TBit3 *SetLblE3() = 0;
    virtual TBit4 *SetLblE4() = 0;

    int ScrollBar_Nbr;
    int ScrollBar2_Nbr;
    int CboBox_Nbr;
    int ChkBox_Nbr;
    int LblE3_Nbr;
    int LblE4_Nbr;
};
#endif

