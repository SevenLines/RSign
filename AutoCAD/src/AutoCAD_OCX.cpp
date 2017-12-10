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
// File generated on 09.02.2015 17:27:59 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Common Files\Autodesk Shared\acax18enu.tlb (1)
// LIBID: {E072BCE4-9027-4F86-BAE2-EF119FD0A0D3}
// LCID: 0
// Helpfile: C:\Program Files\Common Files\Autodesk Shared\ACADAUTO.CHM
// HelpString: AutoCAD 2012 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\system32\stdole2.tlb)
// Errors:
//   Hint: Symbol 'Update' renamed to '_Update'
//   Hint: Symbol 'Update' renamed to '_Update'
//   Hint: Symbol 'Update' renamed to '_Update'
//   Hint: Symbol 'Update' renamed to '_Update'
//   Error creating palette bitmap of (TAcadAcCmColor) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadSortentsTable) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadTableStyle) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadMLeaderStyle) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadDatabase) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadSecurityParams) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadLayerStateManager) : No Server registered for this CoClass
//   Error creating palette bitmap of (TAcadDocument) : No Server registered for this CoClass
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "AutoCAD_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Autocad_tlb
{

IAcadAcCmColorPtr& TAcadAcCmColor::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadAcCmColor::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadAcCmColor::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadAcCmColor::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadAcCmColor::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadAcCmColor::ConnectTo(IAcadAcCmColorPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadAcCmColor::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadAcCmColor;
  sd.IntfIID = __uuidof(IAcadAcCmColor);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IAcadSortentsTablePtr& TAcadSortentsTable::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadSortentsTable::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadSortentsTable::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadSortentsTable::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadSortentsTable::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadSortentsTable::ConnectTo(IAcadSortentsTablePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadSortentsTable::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadSortentsTable;
  sd.IntfIID = __uuidof(IAcadSortentsTable);
  sd.EventIID= __uuidof(IAcadObjectEvents);
  ServerData = &sd;
}

void __fastcall TAcadSortentsTable::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 768: {
      if (OnModified) {
        (OnModified)(this, (Autocad_tlb::IAcadObject*)(LPDISPATCH)TVariant(params[0]));
      }
      break;
      }
    default:
      break;
  }
}

IAcadTableStylePtr& TAcadTableStyle::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadTableStyle::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadTableStyle::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadTableStyle::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadTableStyle::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadTableStyle::ConnectTo(IAcadTableStylePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadTableStyle::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadTableStyle;
  sd.IntfIID = __uuidof(IAcadTableStyle);
  sd.EventIID= __uuidof(IAcadObjectEvents);
  ServerData = &sd;
}

void __fastcall TAcadTableStyle::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 768: {
      if (OnModified) {
        (OnModified)(this, (Autocad_tlb::IAcadObject*)(LPDISPATCH)TVariant(params[0]));
      }
      break;
      }
    default:
      break;
  }
}

IAcadMLeaderStylePtr& TAcadMLeaderStyle::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadMLeaderStyle::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadMLeaderStyle::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadMLeaderStyle::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadMLeaderStyle::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadMLeaderStyle::ConnectTo(IAcadMLeaderStylePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadMLeaderStyle::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadMLeaderStyle;
  sd.IntfIID = __uuidof(IAcadMLeaderStyle);
  sd.EventIID= __uuidof(IAcadObjectEvents);
  ServerData = &sd;
}

void __fastcall TAcadMLeaderStyle::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 768: {
      if (OnModified) {
        (OnModified)(this, (Autocad_tlb::IAcadObject*)(LPDISPATCH)TVariant(params[0]));
      }
      break;
      }
    default:
      break;
  }
}

IAcadDatabasePtr& TAcadDatabase::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadDatabase::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadDatabase::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadDatabase::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadDatabase::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadDatabase::ConnectTo(IAcadDatabasePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadDatabase::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadDatabase;
  sd.IntfIID = __uuidof(IAcadDatabase);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IAcadSecurityParamsPtr& TAcadSecurityParams::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadSecurityParams::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadSecurityParams::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadSecurityParams::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadSecurityParams::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadSecurityParams::ConnectTo(IAcadSecurityParamsPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadSecurityParams::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadSecurityParams;
  sd.IntfIID = __uuidof(IAcadSecurityParams);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IAcadLayerStateManagerPtr& TAcadLayerStateManager::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadLayerStateManager::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadLayerStateManager::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadLayerStateManager::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadLayerStateManager::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadLayerStateManager::ConnectTo(IAcadLayerStateManagerPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadLayerStateManager::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadLayerStateManager;
  sd.IntfIID = __uuidof(IAcadLayerStateManager);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

IAcadDocumentPtr& TAcadDocument::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TAcadDocument::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TAcadDocument::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TAcadDocument::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TAcadDocument::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TAcadDocument::ConnectTo(IAcadDocumentPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TAcadDocument::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_AcadDocument;
  sd.IntfIID = __uuidof(IAcadDocument);
  sd.EventIID= __uuidof(_DAcadDocumentEvents);
  ServerData = &sd;
}

void __fastcall TAcadDocument::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 1: {
      if (OnBeginSave) {
        (OnBeginSave)(this, TVariant(params[0]));
      }
      break;
      }
    case 2: {
      if (OnEndSave) {
        (OnEndSave)(this, TVariant(params[0]));
      }
      break;
      }
    case 6: {
      if (OnBeginCommand) {
        (OnBeginCommand)(this, TVariant(params[0]));
      }
      break;
      }
    case 7: {
      if (OnEndCommand) {
        (OnEndCommand)(this, TVariant(params[0]));
      }
      break;
      }
    case 8: {
      if (OnBeginLisp) {
        (OnBeginLisp)(this, TVariant(params[0]));
      }
      break;
      }
    case 9: {
      if (OnEndLisp) {
        (OnEndLisp)(this);
      }
      break;
      }
    case 10: {
      if (OnLispCancelled) {
        (OnLispCancelled)(this);
      }
      break;
      }
    case 11: {
      if (OnSelectionChanged) {
        (OnSelectionChanged)(this);
      }
      break;
      }
    case 12: {
      if (OnActivate) {
        (OnActivate)(this);
      }
      break;
      }
    case 13: {
      if (OnDeactivate) {
        (OnDeactivate)(this);
      }
      break;
      }
    case 14: {
      if (OnBeginRightClick) {
        (OnBeginRightClick)(this, TVariant(params[0]));
      }
      break;
      }
    case 15: {
      if (OnBeginShortcutMenuDefault) {
        IDispatch* tmp0 = TVariant(params[0]);
        (OnBeginShortcutMenuDefault)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0);
      }
      break;
      }
    case 16: {
      if (OnBeginShortcutMenuEdit) {
        IDispatch* tmp0 = TVariant(params[0]);
        IDispatch* tmp1 = TVariant(params[1]);
        (OnBeginShortcutMenuEdit)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0, (Autocad_tlb::IAcadSelectionSet**)&tmp1);
      }
      break;
      }
    case 17: {
      if (OnBeginShortcutMenuCommand) {
        IDispatch* tmp0 = TVariant(params[0]);
        (OnBeginShortcutMenuCommand)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0, TVariant(params[1]));
      }
      break;
      }
    case 18: {
      if (OnBeginShortcutMenuGrip) {
        IDispatch* tmp0 = TVariant(params[0]);
        (OnBeginShortcutMenuGrip)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0);
      }
      break;
      }
    case 19: {
      if (OnBeginShortcutMenuOsnap) {
        IDispatch* tmp0 = TVariant(params[0]);
        (OnBeginShortcutMenuOsnap)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0);
      }
      break;
      }
    case 30: {
      if (OnEndShortcutMenu) {
        IDispatch* tmp0 = TVariant(params[0]);
        (OnEndShortcutMenu)(this, (Autocad_tlb::IAcadPopupMenu**)&tmp0);
      }
      break;
      }
    case 20: {
      if (OnBeginDoubleClick) {
        (OnBeginDoubleClick)(this, TVariant(params[0]));
      }
      break;
      }
    case 21: {
      if (OnObjectAdded) {
        (OnObjectAdded)(this, TVariant(params[0]));
      }
      break;
      }
    case 22: {
      if (OnObjectErased) {
        (OnObjectErased)(this, TVariant(params[0]));
      }
      break;
      }
    case 23: {
      if (OnObjectModified) {
        (OnObjectModified)(this, TVariant(params[0]));
      }
      break;
      }
    case 24: {
      if (OnBeginPlot) {
        (OnBeginPlot)(this, TVariant(params[0]));
      }
      break;
      }
    case 25: {
      if (OnEndPlot) {
        (OnEndPlot)(this, TVariant(params[0]));
      }
      break;
      }
    case 29: {
      if (OnWindowMovedOrResized) {
        (OnWindowMovedOrResized)(this, TVariant(params[0]), TVariant(params[1]));
      }
      break;
      }
    case 31: {
      if (OnLayoutSwitched) {
        (OnLayoutSwitched)(this, TVariant(params[0]));
      }
      break;
      }
    case 32: {
      if (OnWindowChanged) {
        (OnWindowChanged)(this, (Autocad_tlb::AcWindowState)(int)TVariant(params[0]));
      }
      break;
      }
    case 33: {
      if (OnBeginClose) {
        (OnBeginClose)(this);
      }
      break;
      }
    case 34: {
      if (OnBeginDocClose) {
        (OnBeginDocClose)(this, TVariant(params[0]));
      }
      break;
      }
    default:
      break;
  }
}


};     // namespace Autocad_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Autocad_ocx
{

void __fastcall PACKAGE Register()
{
  // [8]
  TComponentClass cls_svr[] = {
                              __classid(Autocad_tlb::TAcadAcCmColor), 
                              __classid(Autocad_tlb::TAcadSortentsTable), 
                              __classid(Autocad_tlb::TAcadTableStyle), 
                              __classid(Autocad_tlb::TAcadMLeaderStyle), 
                              __classid(Autocad_tlb::TAcadDatabase), 
                              __classid(Autocad_tlb::TAcadSecurityParams), 
                              __classid(Autocad_tlb::TAcadLayerStateManager), 
                              __classid(Autocad_tlb::TAcadDocument)
                           };
  RegisterComponents("ActiveX", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Autocad_ocx
