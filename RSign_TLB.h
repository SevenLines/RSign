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
// File generated on 28.11.2016 0:47:24 from Type Library described below.

// ************************************************************************  //
// Type Lib: D:\_DISTR\_ASUDOR\RSign\RSign.tlb (1)
// LIBID: {9585521C-1ADF-42FB-92EB-5C48218460F1}
// LCID: 0
// Helpfile: 
// HelpString: RSign Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// ************************************************************************ //
#ifndef   RSign_TLBH
#define   RSign_TLBH

#pragma option push -b -w-inl

#include <utilcls.h>
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0600)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary 
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an 
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// Forward reference of some VCL types (to avoid including STDVCL.HPP)    
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Rsign_tlb
{

// *********************************************************************//
// HelpString: RSign Library
// Version:    1.0
// *********************************************************************//


// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLSID_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
extern "C" const __declspec(selectany) GUID LIBID_RSign = {0x9585521C, 0x1ADF, 0x42FB,{ 0x92, 0xEB, 0x5C,0x48, 0x21, 0x84,0x60, 0xF1} };
extern "C" const __declspec(selectany) GUID IID_IRoadView = {0x999DEE0D, 0xFF95, 0x4903,{ 0xAF, 0x87, 0x3F,0x83, 0x65, 0x3C,0x9C, 0x14} };
extern "C" const __declspec(selectany) GUID CLSID_RoadView = {0xE6AFC872, 0xF336, 0x48BA,{ 0x9D, 0x87, 0xA7,0x0A, 0xB7, 0x7F,0xEE, 0x06} };

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
interface DECLSPEC_UUID("{999DEE0D-FF95-4903-AF87-3F83653C9C14}") IRoadView;
typedef TComInterface<IRoadView, &IID_IRoadView> IRoadViewPtr;


// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
//                                                                        
// The LIBID_OF_ macro(s) map a LIBID_OF_CoClassName to the GUID of this  
// TypeLibrary. It simplifies the updating of macros when CoClass name    
// change.                                                                
// *********************************************************************//
typedef IRoadView RoadView;
typedef IRoadViewPtr RoadViewPtr;

#define LIBID_OF_RoadView (&LIBID_RSign)
// *********************************************************************//
// Interface: IRoadView
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {999DEE0D-FF95-4903-AF87-3F83653C9C14}
// *********************************************************************//
interface IRoadView  : public IDispatch
{
public:
  virtual HRESULT STDMETHODCALLTYPE OpenRoad(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                             long OpenCopy/*[in]*/) = 0; // [1]
  virtual HRESULT STDMETHODCALLTYPE ActivateRoad(long RoadId/*[in]*/, long DataSource/*[in]*/) = 0; // [2]
  virtual HRESULT STDMETHODCALLTYPE CloseRoad(long RoadId/*[in]*/, long DataSource/*[in]*/) = 0; // [3]
  virtual HRESULT STDMETHODCALLTYPE IsRoadOpen(long RoadId/*[in]*/, long DataSource/*[in]*/) = 0; // [4]
  virtual HRESULT STDMETHODCALLTYPE ShowRoadPart(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                                 long StartPos/*[in]*/, long EndPos/*[in]*/) = 0; // [5]
  virtual HRESULT STDMETHODCALLTYPE ShowRoadObject(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                                   long ObjectId/*[in]*/) = 0; // [6]
  virtual HRESULT STDMETHODCALLTYPE SetConnectionString(BSTR Str/*[in]*/) = 0; // [7]
  virtual HRESULT STDMETHODCALLTYPE GetConnectionString(BSTR* Str/*[in]*/) = 0; // [9]

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)



#endif //   __TLB_NO_INTERFACE_WRAPPERS

};

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
// *********************************************************************//
// SmartIntf: TCOMIRoadView
// Interface: IRoadView
// *********************************************************************//
template <class T /* IRoadView */ >
class TCOMIRoadViewT : public TComInterface<IRoadView>, public TComInterfaceBase<IUnknown>
{
public:
  TCOMIRoadViewT() {}
  TCOMIRoadViewT(IRoadView *intf, bool addRef = false) : TComInterface<IRoadView>(intf, addRef) {}
  TCOMIRoadViewT(const TCOMIRoadViewT& src) : TComInterface<IRoadView>(src) {}
  TCOMIRoadViewT& operator=(const TCOMIRoadViewT& src) { Bind(src, true); return *this;}

  HRESULT         __fastcall OpenRoad(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                      long OpenCopy/*[in]*/);
  HRESULT         __fastcall ActivateRoad(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall CloseRoad(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall IsRoadOpen(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall ShowRoadPart(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                          long StartPos/*[in]*/, long EndPos/*[in]*/);
  HRESULT         __fastcall ShowRoadObject(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                            long ObjectId/*[in]*/);
  HRESULT         __fastcall SetConnectionString(BSTR Str/*[in]*/);
  HRESULT         __fastcall GetConnectionString(BSTR* Str/*[in]*/);

};
typedef TCOMIRoadViewT<IRoadView> TCOMIRoadView;

// *********************************************************************//
// DispIntf:  IRoadView
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {999DEE0D-FF95-4903-AF87-3F83653C9C14}
// *********************************************************************//
template<class T>
class IRoadViewDispT : public TAutoDriver<IRoadView>
{
public:
  IRoadViewDispT(){}

  IRoadViewDispT(IRoadView *pintf)
  {
    TAutoDriver<IRoadView>::Bind(pintf, false);
  }

  IRoadViewDispT(IRoadViewPtr pintf)
  {
    TAutoDriver<IRoadView>::Bind(pintf, true);
  }

  IRoadViewDispT& operator=(IRoadView *pintf)
  {
    TAutoDriver<IRoadView>::Bind(pintf, false);
    return *this;
  }

  IRoadViewDispT& operator=(IRoadViewPtr pintf)
  {
    TAutoDriver<IRoadView>::Bind(pintf, true);
    return *this;
  }

  HRESULT BindDefault()
  {
    return OLECHECK(Bind(CLSID_RoadView));
  }

  HRESULT BindRunning()
  {
    return BindToActive(CLSID_RoadView);
  }

  HRESULT         __fastcall OpenRoad(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                      long OpenCopy/*[in]*/);
  HRESULT         __fastcall ActivateRoad(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall CloseRoad(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall IsRoadOpen(long RoadId/*[in]*/, long DataSource/*[in]*/);
  HRESULT         __fastcall ShowRoadPart(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                          long StartPos/*[in]*/, long EndPos/*[in]*/);
  HRESULT         __fastcall ShowRoadObject(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                            long ObjectId/*[in]*/);
  HRESULT         __fastcall SetConnectionString(BSTR Str/*[in]*/);
  HRESULT         __fastcall GetConnectionString(BSTR* Str/*[in]*/);

};
typedef IRoadViewDispT<IRoadView> IRoadViewDisp;

// *********************************************************************//
// SmartIntf: TCOMIRoadView
// Interface: IRoadView
// *********************************************************************//
template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::OpenRoad(long RoadId/*[in]*/, long DataSource/*[in]*/, long OpenCopy/*[in]*/)
{
  return (*this)->OpenRoad(RoadId, DataSource, OpenCopy);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::ActivateRoad(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  return (*this)->ActivateRoad(RoadId, DataSource);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::CloseRoad(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  return (*this)->CloseRoad(RoadId, DataSource);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::IsRoadOpen(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  return (*this)->IsRoadOpen(RoadId, DataSource);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::ShowRoadPart(long RoadId/*[in]*/, long DataSource/*[in]*/, long StartPos/*[in]*/, 
                                long EndPos/*[in]*/)
{
  return (*this)->ShowRoadPart(RoadId, DataSource, StartPos, EndPos);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::ShowRoadObject(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                  long ObjectId/*[in]*/)
{
  return (*this)->ShowRoadObject(RoadId, DataSource, ObjectId);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::SetConnectionString(BSTR Str/*[in]*/)
{
  return (*this)->SetConnectionString(Str);
}

template <class T> HRESULT __fastcall
TCOMIRoadViewT<T>::GetConnectionString(BSTR* Str/*[in]*/)
{
  return (*this)->GetConnectionString(Str);
}

// *********************************************************************//
// DispIntf:  IRoadView
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {999DEE0D-FF95-4903-AF87-3F83653C9C14}
// *********************************************************************//
template <class T> HRESULT __fastcall
IRoadViewDispT<T>::OpenRoad(long RoadId/*[in]*/, long DataSource/*[in]*/, long OpenCopy/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("OpenRoad"), DISPID(1));
  TAutoArgs<3> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  _args[3] = OpenCopy /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::ActivateRoad(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("ActivateRoad"), DISPID(2));
  TAutoArgs<2> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::CloseRoad(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("CloseRoad"), DISPID(3));
  TAutoArgs<2> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::IsRoadOpen(long RoadId/*[in]*/, long DataSource/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("IsRoadOpen"), DISPID(4));
  TAutoArgs<2> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::ShowRoadPart(long RoadId/*[in]*/, long DataSource/*[in]*/, long StartPos/*[in]*/
                                , long EndPos/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("ShowRoadPart"), DISPID(5));
  TAutoArgs<4> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  _args[3] = StartPos /*[VT_I4:0]*/;
  _args[4] = EndPos /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::ShowRoadObject(long RoadId/*[in]*/, long DataSource/*[in]*/, 
                                  long ObjectId/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("ShowRoadObject"), DISPID(6));
  TAutoArgs<3> _args;
  _args[1] = RoadId /*[VT_I4:0]*/;
  _args[2] = DataSource /*[VT_I4:0]*/;
  _args[3] = ObjectId /*[VT_I4:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::SetConnectionString(BSTR Str/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("SetConnectionString"), DISPID(7));
  TAutoArgs<1> _args;
  _args[1] = Str /*[VT_BSTR:0]*/;
  return OleFunction(_dispid, _args);
}

template <class T> HRESULT __fastcall
IRoadViewDispT<T>::GetConnectionString(BSTR* Str/*[in]*/)
{
  _TDispID _dispid(*this, OLETEXT("GetConnectionString"), DISPID(9));
  TAutoArgs<1> _args;
  _args[1] = Str /*[VT_BSTR:1]*/;
  return OleFunction(_dispid, _args);
}

// *********************************************************************//
// The following typedefs expose classes (named CoCoClassName) that       
// provide static Create() and CreateRemote(LPWSTR machineName) methods   
// for creating an instance of an exposed object. These functions can     
// be used by client wishing to automate CoClasses exposed by this        
// typelibrary.                                                           
// *********************************************************************//

// *********************************************************************//
// COCLASS DEFAULT INTERFACE CREATOR
// CoClass  : RoadView
// Interface: TCOMIRoadView
// *********************************************************************//
typedef TCoClassCreatorT<TCOMIRoadView, IRoadView, &CLSID_RoadView, &IID_IRoadView> CoRoadView;
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Rsign_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Rsign_tlb;
#endif

#pragma option pop

#endif // RSign_TLBH
