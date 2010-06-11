//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TCA210SettingFrame.h"
#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCA210SettingFrame *CA210SettingFrame;
//---------------------------------------------------------------------------
__fastcall TCA210SettingFrame::TCA210SettingFrame(TComponent * Owner)
:TFrame(Owner)
{
}

//---------------------------------------------------------------------------


void TCA210SettingFrame::setCA210API(bptr < ca210api::CA210API > ca210API)
{
    this->ca210API = ca210API;
};

void __fastcall TCA210SettingFrame::Button_ConnectClick(TObject * Sender)
{
    if (ca210API == null) {
	return;
    };
    ca210API->setRemoteMode(ca210api::Locked);
    //MainForm->connectMeter();

}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::Button_DisconnectClick(TObject *
							   Sender)
{
    if (ca210API == null) {
	return;
    };
    ca210API->setRemoteMode(ca210api::Off);
    //MainForm->disconnectMeter();
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::ComboBox_SyncModeChange(TObject *
							    Sender)
{

    int index = this->ComboBox_SyncMode->ItemIndex;
    using namespace ca210api;
    SyncMode mode;
    this->Edit_Hz->Enabled = false;
    switch (index) {
    case 0:
	mode = NTSC;
	break;
    case 1:
	mode = PAL;
	break;
    case 2:
	mode = EXT;
	break;
    case 3:
	mode = UNIV;
	break;
    case 4:
	this->Edit_Hz->Enabled = true;
	break;
    }
    if (ca210API == null) {
	return;
    };
    ca210API->setSyncMode(mode);
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::ComboBox_CalStandardChange(TObject *
							       Sender)
{
    if (ca210API == null) {
	return;
    };
    int index = this->ComboBox_CalStandard->ItemIndex;

    using namespace ca210api;
    CalStandard std;
    switch (index) {
    case 0:
	std = D6500k;
	break;
    case 1:
	std = D9300k;
	break;
    }

    ca210API->setCalStandard(std);
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::Edit_HzChange(TObject * Sender)
{
    int hz = this->Edit_Hz->Text.ToInt();
    ca210API->setSyncHz(hz);
}

//---------------------------------------------------------------------------

