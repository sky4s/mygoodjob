//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TCA210SettingFrame.h"
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

/*void TCA210SettingFrame::setCA210(bptr < cms::measure::meter::CA210 >
				  ca210)
{
    this->ca210 = ca210;
    this->ca210API = ca210->getCA210API();
}*/

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
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::Button_DisconnectClick(TObject *
							   Sender)
{
    if (ca210API == null) {
	return;
    };
    ca210API->setRemoteMode(ca210api::Off);
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::ComboBox_SyncModeChange(TObject *
							    Sender)
{
    if (ca210API == null) {
	return;
    };
    int index = this->ComboBox_SyncMode->ItemIndex;
    using namespace ca210api;
    SyncMode mode;
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
    }
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

