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

void TCA210SettingFrame::setCA210(bptr < cms::measure::meter::CA210 >
				  ca210)
{
    this->ca210 = ca210;
    this->ca210API = ca210->getCA210API();
}


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
    ca210API->setSyncMode(index);
}

//---------------------------------------------------------------------------

void __fastcall TCA210SettingFrame::ComboBox_CalStandardChange(TObject *
							       Sender)
{
    if (ca210API == null) {
	return;
    };
    int index = this->ComboBox_CalStandard->ItemIndex;
    ca210API->setCalStandard(index);
}

//---------------------------------------------------------------------------

