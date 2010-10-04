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
// File generated on 2006/7/11 ¤U¤È 08:47:59 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\WINDOWS\system32\hwinterface.ocx (1)
// LIBID: {BD6BB71B-5C9A-4FB3-877E-8B513D28B951}
// LCID: 0
// Helpfile: C:\WINDOWS\system32\hwinterface.hlp
// HelpString: hwinterface ActiveX Control module
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\Stdole2.tlb)
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "HWINTERFACELib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Hwinterfacelib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class THwinterface which
// allows "Hwinterface Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
TControlData THwinterface::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0xB9022892, 0xEA92, 0x4F94,{ 0x81, 0x01, 0xB9,0xCD, 0xE3, 0x0E,0x66, 0x7D} }, // CoClass
  {0xD7A782FE, 0xF757, 0x4C7C,{ 0x9A, 0x29, 0x8C,0xF0, 0x22, 0x76,0x0A, 0xD6} }, // Events

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

GUID     THwinterface::DEF_CTL_INTF = {0x39F91450, 0x46FA, 0x41A9,{ 0x91, 0x0B, 0x66,0x27, 0x3D, 0x10,0x5E, 0xBB} };
TNoParam THwinterface::OptParam;

static inline void ValidCtrCheck(THwinterface *)
{
   delete new THwinterface((TComponent*)(0));
};

void __fastcall THwinterface::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall THwinterface::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

_DHwinterfaceDisp __fastcall THwinterface::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

short __fastcall THwinterface::InPort(short Address)
{
  return GetDefaultInterface()->InPort(Address);
}

void __fastcall THwinterface::OutPort(short Address, short Data)
{
  GetDefaultInterface()->OutPort(Address, Data);
}

void __fastcall THwinterface::AboutBox(void)
{
  GetDefaultInterface()->AboutBox();
}


};     // namespace Hwinterfacelib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Hwinterfacelib_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Hwinterfacelib_tlb::THwinterface)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Hwinterfacelib_ocx
