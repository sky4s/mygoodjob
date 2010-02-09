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

#include "CA200SRVRLib_TLB.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Ca200srvrlib_tlb {


// *********************************************************************//
// GUIDS declared in the TypeLibrary                                      
// *********************************************************************//
    const GUID LIBID_CA200SRVRLib =
	{ 0x81480671, 0x9287, 0x43D4, {0x8A, 0x21, 0xF0, 0xCB, 0x01, 0x57,
				       0x07, 0x7F} };
    const GUID CLSID_Ca200 =
	{ 0x006B0650, 0xAF9A, 0x4EE1, {0xB1, 0x8F, 0xB5, 0x74, 0x00, 0x04,
				       0xD7, 0xCE} };
    const GUID IID_ICa200 =
	{ 0xDB87A8F6, 0xFAF3, 0x433A, {0xB7, 0xF3, 0x31, 0xBB, 0x4D, 0x75,
				       0x93, 0x61} };
    const GUID IID_ICas =
	{ 0x5415C7C6, 0xD982, 0x46EE, {0xBA, 0x22, 0xFB, 0x6D, 0xC1, 0xAD,
				       0x5D, 0xE0} };
    const GUID IID_ICa =
	{ 0xA930F0DB, 0xF79A, 0x467A, {0x84, 0x79, 0xF8, 0x36, 0x9B, 0x06,
				       0x3B, 0x8D} };
    const GUID IID_IProbes =
	{ 0xB455EFE8, 0x1576, 0x481C, {0xBA, 0xC6, 0xA1, 0xC5, 0x06, 0xBF,
				       0x4E, 0x81} };
    const GUID IID_IProbe =
	{ 0xB2FDD51E, 0xCBA7, 0x45CE, {0xAF, 0x0A, 0xDD, 0x96, 0x2E, 0x46,
				       0xB7, 0x4F} };
    const GUID IID_IOutputProbes =
	{ 0x3EE4760C, 0xB9F3, 0x47B1, {0x95, 0x3F, 0xF5, 0xA2, 0xF8, 0x3F,
				       0xF6, 0x88} };
    const GUID IID_IMemory =
	{ 0x20EA33BB, 0x6914, 0x465A, {0xB9, 0x8E, 0x8D, 0xBD, 0x4E, 0x38,
				       0x6C, 0xD0} };
    const GUID CLSID_Cas =
	{ 0xC1F0B433, 0x1841, 0x4330, {0x96, 0x0E, 0xDB, 0x74, 0x03, 0x63,
				       0x5D, 0xB3} };
    const GUID DIID__ICaEvents =
	{ 0xF7663750, 0x5900, 0x45EB, {0x90, 0x5F, 0x78, 0xC5, 0xD5, 0x37,
				       0x84, 0x81} };
    const GUID IID_IProbeInfo =
	{ 0x5C542273, 0x19D5, 0x4C56, {0xA1, 0x2A, 0xA5, 0x8B, 0x1B, 0xAA,
				       0xD6, 0x5E} };
    const GUID CLSID_Ca =
	{ 0x3B5F9680, 0x00A6, 0x469B, {0xBA, 0xDE, 0x04, 0xC7, 0x81, 0xAA,
				       0xFA, 0xA1} };
    const GUID IID_ICaOption =
	{ 0x3CBE6157, 0x1D53, 0x4CAE, {0xB4, 0xB0, 0x33, 0xAC, 0xC3, 0x0E,
				       0x64, 0x21} };
    const GUID CLSID_Memory =
	{ 0x0C0A2E9B, 0xEFA3, 0x4B95, {0xAC, 0x32, 0x98, 0xB8, 0x50, 0x6F,
				       0x95, 0xEF} };
    const GUID CLSID_Probes =
	{ 0xBFA8834E, 0x4853, 0x4D35, {0x98, 0xFC, 0xBA, 0xF5, 0x90, 0x6D,
				       0xAA, 0x83} };
    const GUID CLSID_Probe =
	{ 0xA1874391, 0x65BA, 0x402A, {0xA0, 0xF8, 0xAE, 0x9F, 0x9A, 0x11,
				       0xEB, 0x8B} };
    const GUID CLSID_OutputProbes =
	{ 0xDF97B9A4, 0x49FF, 0x44CC, {0xA5, 0xB8, 0x06, 0xD7, 0xC6, 0xFB,
				       0xC9, 0xB6} };

};				// namespace Ca200srvrlib_tlb

