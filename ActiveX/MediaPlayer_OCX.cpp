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
// File generated on 11.02.2005 14:42:47 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\WINNT\System32\msdxm.ocx (1)
// LIBID: {22D6F304-B0F6-11D0-94AB-0080C74C7E95}
// LCID: 0
// Helpfile: 
// HelpString: Windows Media Player
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINNT\System32\stdole2.tlb)
// Errors:
//   Hint: TypeInfo 'MediaPlayer' changed to 'MediaPlayer_'
//   Hint: Symbol 'Click' renamed to '_Click'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "MediaPlayer_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Mediaplayer_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TSMediaPlayer which
// allows "Windows Media Player" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TSMediaPlayer::EventDispIDs[14] = {
    0x000005E1, 0x00000BBA, 0x00000BC3, 0x00000BC4, 0x00000BB9, 0x00000BBB,
    0x00000BC2, 0x00000BBE, 0x00000BC1, 0x00000BC0, 0x00000BBC, 0x00000002,
    0x00000033, 0xFFFFFD9F};

TControlData TSMediaPlayer::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x22D6F312, 0xB0F6, 0x11D0,{ 0x94, 0xAB, 0x00,0x80, 0xC7, 0x4C,0x7E, 0x95} }, // CoClass
  {0x2D3A4C40, 0xE711, 0x11D0,{ 0x94, 0xAB, 0x00,0x80, 0xC7, 0x4C,0x7E, 0x95} }, // Events

  // Count of Events and array of their DISPIDs
  14, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x00000000)

  // Flags for OnChanged PropertyNotification
  0x00000008,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, NULL,

  // Count of Pict Prop and array of their DISPIDs
  0, NULL,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TSMediaPlayer::DEF_CTL_INTF = {0x22D6F311, 0xB0F6, 0x11D0,{ 0x94, 0xAB, 0x00,0x80, 0xC7, 0x4C,0x7E, 0x95} };
TNoParam TSMediaPlayer::OptParam;

static inline void ValidCtrCheck(TSMediaPlayer *)
{
   delete new TSMediaPlayer((TComponent*)(0));
};

void __fastcall TSMediaPlayer::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TSMediaPlayer::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMIMediaPlayer __fastcall TSMediaPlayer::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TSMediaPlayer::Play(void)
{
  GetDefaultInterface()->Play();
}

void __fastcall TSMediaPlayer::Stop(void)
{
  GetDefaultInterface()->Stop();
}

void __fastcall TSMediaPlayer::Pause(void)
{
  GetDefaultInterface()->Pause();
}

double __fastcall TSMediaPlayer::GetMarkerTime(long MarkerNum/*[in]*/)
{
  return GetDefaultInterface()->GetMarkerTime(MarkerNum/*[in]*/);
}

BSTR __fastcall TSMediaPlayer::GetMarkerName(long MarkerNum/*[in]*/)
{
  return GetDefaultInterface()->GetMarkerName(MarkerNum/*[in]*/);
}

void __fastcall TSMediaPlayer::AboutBox(void)
{
  GetDefaultInterface()->AboutBox();
}

TOLEBOOL __fastcall TSMediaPlayer::GetCodecInstalled(long CodecNum/*[in]*/)
{
  return GetDefaultInterface()->GetCodecInstalled(CodecNum/*[in]*/);
}

BSTR __fastcall TSMediaPlayer::GetCodecDescription(long CodecNum/*[in]*/)
{
  return GetDefaultInterface()->GetCodecDescription(CodecNum/*[in]*/);
}

BSTR __fastcall TSMediaPlayer::GetCodecURL(long CodecNum/*[in]*/)
{
  return GetDefaultInterface()->GetCodecURL(CodecNum/*[in]*/);
}

BSTR __fastcall TSMediaPlayer::GetMoreInfoURL(Mediaplayer_tlb::MPMoreInfoType MoreInfoType/*[in]*/)
{
  return GetDefaultInterface()->GetMoreInfoURL(MoreInfoType/*[in]*/);
}

BSTR __fastcall TSMediaPlayer::GetMediaInfoString(Mediaplayer_tlb::MPMediaInfoType MediaInfoType/*[in]*/)
{
  return GetDefaultInterface()->GetMediaInfoString(MediaInfoType/*[in]*/);
}

void __fastcall TSMediaPlayer::Cancel(void)
{
  GetDefaultInterface()->Cancel();
}

void __fastcall TSMediaPlayer::Open(BSTR bstrFileName/*[in]*/)
{
  GetDefaultInterface()->Open(bstrFileName/*[in]*/);
}

TOLEBOOL __fastcall TSMediaPlayer::IsSoundCardEnabled(void)
{
  return GetDefaultInterface()->IsSoundCardEnabled();
}

void __fastcall TSMediaPlayer::Next(void)
{
  GetDefaultInterface()->Next();
}

void __fastcall TSMediaPlayer::Previous(void)
{
  GetDefaultInterface()->Previous();
}

void __fastcall TSMediaPlayer::StreamSelect(long StreamNum/*[in]*/)
{
  GetDefaultInterface()->StreamSelect(StreamNum/*[in]*/);
}

void __fastcall TSMediaPlayer::FastForward(void)
{
  GetDefaultInterface()->FastForward();
}

void __fastcall TSMediaPlayer::FastReverse(void)
{
  GetDefaultInterface()->FastReverse();
}

BSTR __fastcall TSMediaPlayer::GetStreamName(long StreamNum/*[in]*/)
{
  return GetDefaultInterface()->GetStreamName(StreamNum/*[in]*/);
}

long __fastcall TSMediaPlayer::GetStreamGroup(long StreamNum/*[in]*/)
{
  return GetDefaultInterface()->GetStreamGroup(StreamNum/*[in]*/);
}

TOLEBOOL __fastcall TSMediaPlayer::GetStreamSelected(long StreamNum/*[in]*/)
{
  return GetDefaultInterface()->GetStreamSelected(StreamNum/*[in]*/);
}

LPDISPATCH __fastcall TSMediaPlayer::get_ActiveMovie(void)
{
  return GetDefaultInterface()->get_ActiveMovie();
}

LPDISPATCH __fastcall TSMediaPlayer::get_NSPlay(void)
{
  return GetDefaultInterface()->get_NSPlay();
}


};     // namespace Mediaplayer_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Mediaplayer_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Mediaplayer_tlb::TSMediaPlayer)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Mediaplayer_ocx
