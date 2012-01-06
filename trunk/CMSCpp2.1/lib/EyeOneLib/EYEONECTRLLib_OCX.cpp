// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.151.1.0.1.27  $
// File generated on 2012/1/6 ¤W¤È 10:22:28 from Type Library described below.

// ************************************************************************  //
// Type Lib: D:\WorkSpace\CMSCpp2.1\lib\EyeOneLib\EyeOne.dll (1)
// LIBID: {10A3A3EB-9E08-4B1A-8E14-7693FB50C5EC}
// LCID: 0
// Helpfile: D:\WorkSpace\CMSCpp2.1\lib\EyeOneLib\EyeOneCtrl.hlp
// HelpString: EyeOneCtrl ActiveX Control module
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Error creating palette bitmap of (TEyeOneCtrl) : Error reading control bitmap
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "EYEONECTRLLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Eyeonectrllib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TEyeOneCtrl which
// allows "EyeOneCtrl Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
TControlData TEyeOneCtrl::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x9F1BC874, 0x20E0, 0x4272,{ 0xAA, 0xE5, 0xC4,0x5C, 0x8D, 0x86,0x58, 0x19} }, // CoClass
  {0xDA563AD5, 0x1E29, 0x4F68,{ 0x87, 0x12, 0x5C,0x08, 0x42, 0xD0,0xCD, 0x14} }, // Events

  // Count of Events and array of their DISPIDs
  0, NULL,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004005)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, NULL,

  // Count of Pict Prop and array of their DISPIDs
  0, NULL,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TEyeOneCtrl::DEF_CTL_INTF = {0x390C4317, 0x0F4A, 0x4957,{ 0x96, 0x96, 0x57,0x9C, 0x37, 0x3C,0xA8, 0x65} };
TNoParam TEyeOneCtrl::OptParam;

static inline void ValidCtrCheck(TEyeOneCtrl *)
{
   delete new TEyeOneCtrl((TComponent*)(0));
};

void __fastcall TEyeOneCtrl::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TEyeOneCtrl::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

_DEyeOneCtrlDisp __fastcall TEyeOneCtrl::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

BSTR __fastcall TEyeOneCtrl::GetDeviceInfo(BSTR axKey)
{
  return GetDefaultInterface()->GetDeviceInfo(axKey);
}

long __fastcall TEyeOneCtrl::IsConnected(void)
{
  return GetDefaultInterface()->IsConnected();
}

long __fastcall TEyeOneCtrl::KeyPressed(void)
{
  return GetDefaultInterface()->KeyPressed();
}

long __fastcall TEyeOneCtrl::Calibrate(void)
{
  return GetDefaultInterface()->Calibrate();
}

long __fastcall TEyeOneCtrl::TriggerMeasurement(void)
{
  return GetDefaultInterface()->TriggerMeasurement();
}

long __fastcall TEyeOneCtrl::SetOption(BSTR axKey, BSTR axValue)
{
  return GetDefaultInterface()->SetOption(axKey, axValue);
}

BSTR __fastcall TEyeOneCtrl::GetOption(BSTR axKey)
{
  return GetDefaultInterface()->GetOption(axKey);
}

long __fastcall TEyeOneCtrl::SetSubstrate(LPSAFEARRAY* xySubstrateSpectrum)
{
  return GetDefaultInterface()->SetSubstrate(xySubstrateSpectrum);
}

long __fastcall TEyeOneCtrl::GetTriStimulus(LPSAFEARRAY* yxTriStimulus, long axIndex)
{
  return GetDefaultInterface()->GetTriStimulus(yxTriStimulus, axIndex);
}

long __fastcall TEyeOneCtrl::GetDensity(float* axDensity, long axIndex)
{
  return GetDefaultInterface()->GetDensity(axDensity, axIndex);
}

long __fastcall TEyeOneCtrl::GetDensities(LPSAFEARRAY* yxDensities, long* pxAutoDensityIndex, 
                                          long axIndex)
{
  return GetDefaultInterface()->GetDensities(yxDensities, pxAutoDensityIndex, axIndex);
}

long __fastcall TEyeOneCtrl::GetSpectrum(LPSAFEARRAY* yxSpectrum, long axIndex)
{
  return GetDefaultInterface()->GetSpectrum(yxSpectrum, axIndex);
}


};     // namespace Eyeonectrllib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Eyeonectrllib_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Eyeonectrllib_tlb::TEyeOneCtrl)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Eyeonectrllib_ocx
