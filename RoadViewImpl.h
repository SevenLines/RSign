// ROADVIEWIMPL.H : Declaration of the TRoadViewImpl

#ifndef RoadViewImplH
#define RoadViewImplH

#define ATL_APARTMENT_THREADED

#include "RSign_TLB.H"


/////////////////////////////////////////////////////////////////////////////
// TRoadViewImpl     Implements IRoadView, default interface of RoadView
// ThreadingModel : Apartment
// Dual Interface : TRUE
// Event Support  : FALSE
// Default ProgID : RSign.RoadView
// Description    : Система отображения
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE TRoadViewImpl : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<TRoadViewImpl, &CLSID_RoadView>,
  public IDispatchImpl<IRoadView, &IID_IRoadView, &LIBID_RSign>
{
public:
  TRoadViewImpl()
  {
  }

  // Data used when registering Object 
  //
  DECLARE_THREADING_MODEL(otApartment);
  DECLARE_PROGID("RSign.RoadView");
  DECLARE_DESCRIPTION("Система отображения");

  // Function invoked to (un)register object
  //
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TTypedComServerRegistrarT<TRoadViewImpl> 
    regObj(GetObjectCLSID(), GetProgID(), GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }


BEGIN_COM_MAP(TRoadViewImpl)
  COM_INTERFACE_ENTRY(IRoadView)
  COM_INTERFACE_ENTRY2(IDispatch, IRoadView)
END_COM_MAP()

// IRoadView
public:
 
  STDMETHOD(ActivateRoad(long RoadId, long DataSource));
  STDMETHOD(CloseRoad(long RoadId, long DataSource));
  STDMETHOD(IsRoadOpen(long RoadId, long DataSource));
  STDMETHOD(OpenRoad(long RoadId, long DataSource, long OpenCopy));
  STDMETHOD(ShowRoadObject(long RoadId, long DataSource, long ObjectId));
  STDMETHOD(ShowRoadPart(long RoadId, long DataSource, long StartPos,
      long EndPos));
  STDMETHOD(SetConnectionString(BSTR Str));
  STDMETHOD(GetConnectionString(BSTR* Str));
};

#endif //RoadViewImplH
