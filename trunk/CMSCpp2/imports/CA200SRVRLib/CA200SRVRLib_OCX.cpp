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
// File generated on 2010/1/11 ¤U¤È 08:10:39 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\CA-SDK\SDK\CA200Srvr.dll (1)
// LIBID: {81480671-9287-43D4-8A21-F0CB0157077F}
// LCID: 0
// Helpfile: 
// HelpString: CA200Srvr 1.1 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Error creating palette bitmap of (TCa200) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TCas) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TCa) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TMemory) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TProbes) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TProbe) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
//   Error creating palette bitmap of (TOutputProbes) : Server C:\Program Files\CA-SDK\SDK\CA200Srvr.dll contains no icons
// ************************************************************************ //

#include <vcl.h>
//#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "CA200SRVRLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Ca200srvrlib_tlb
{

ICa200Ptr& TCa200::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TCa200::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TCa200::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TCa200::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TCa200::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TCa200::ConnectTo(ICa200Ptr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TCa200::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Ca200;
  sd.IntfIID = __uuidof(ICa200);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

ICasPtr& TCas::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TCas::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TCas::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TCas::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TCas::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TCas::ConnectTo(ICasPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TCas::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Cas;
  sd.IntfIID = __uuidof(ICas);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

ICaPtr& TCa::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TCa::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TCa::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TCa::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TCa::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TCa::ConnectTo(ICaPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TCa::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Ca;
  sd.IntfIID = __uuidof(ICa);
  sd.EventIID= __uuidof(_ICaEvents);
  ServerData = &sd;
}

void __fastcall TCa::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 1: {
      if (OnExeCalZero) {
        (OnExeCalZero)(this);
      }
      break;
      }
    default:
      break;
  }
}

IMemoryPtr& TMemory::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TMemory::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TMemory::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TMemory::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TMemory::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TMemory::ConnectTo(IMemoryPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TMemory::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Memory;
  sd.IntfIID = __uuidof(IMemory);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IProbesPtr& TProbes::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TProbes::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TProbes::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TProbes::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TProbes::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TProbes::ConnectTo(IProbesPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TProbes::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Probes;
  sd.IntfIID = __uuidof(IProbes);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IProbePtr& TProbe::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TProbe::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TProbe::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TProbe::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TProbe::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TProbe::ConnectTo(IProbePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TProbe::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Probe;
  sd.IntfIID = __uuidof(IProbe);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IOutputProbesPtr& TOutputProbes::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TOutputProbes::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TOutputProbes::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TOutputProbes::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TOutputProbes::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TOutputProbes::ConnectTo(IOutputProbesPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TOutputProbes::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_OutputProbes;
  sd.IntfIID = __uuidof(IOutputProbes);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}


};     // namespace Ca200srvrlib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Ca200srvrlib_ocx
{

void __fastcall PACKAGE Register()
{
  // [7]
  TComponentClass cls_svr[] = {
                              __classid(Ca200srvrlib_tlb::TCa200), 
                              __classid(Ca200srvrlib_tlb::TCas), 
                              __classid(Ca200srvrlib_tlb::TCa), 
                              __classid(Ca200srvrlib_tlb::TMemory), 
                              __classid(Ca200srvrlib_tlb::TProbes), 
                              __classid(Ca200srvrlib_tlb::TProbe), 
                              __classid(Ca200srvrlib_tlb::TOutputProbes)
                           };
  RegisterComponents("COM+", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Ca200srvrlib_ocx
