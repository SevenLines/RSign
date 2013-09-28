// ROADVIEWIMPL : Implementation of TRoadViewImpl (CoClass: RoadView, Interface: IRoadView)

#include <vcl.h>
#include "MainUnit.h"
#pragma hdrstop




































































































































































































































































































#include "ROADVIEWIMPL.H"

/////////////////////////////////////////////////////////////////////////////
// TRoadViewImpl

STDMETHODIMP TRoadViewImpl::ActivateRoad(long RoadId, long DataSource)
{
return MainForm->ActivateRoad(RoadId,DataSource);
}

STDMETHODIMP TRoadViewImpl::CloseRoad(long RoadId, long DataSource)
{
return MainForm->CloseRoad(RoadId,DataSource);
}

STDMETHODIMP TRoadViewImpl::IsRoadOpen(long RoadId, long DataSource)
{
return MainForm->IsRoadOpen(RoadId,DataSource);
}

STDMETHODIMP TRoadViewImpl::OpenRoad(long RoadId, long DataSource,
  long OpenCopy)
{
return MainForm->OpenRoadById(RoadId,DataSource,OpenCopy);
}

STDMETHODIMP TRoadViewImpl::ShowRoadObject(long RoadId, long DataSource,
  long ObjectId)
{
return MainForm->ShowRoadObject(RoadId,DataSource,ObjectId);
}

STDMETHODIMP TRoadViewImpl::ShowRoadPart(long RoadId, long DataSource,
  long StartPos, long EndPos)
{
return MainForm->ShowRoadPart(RoadId,DataSource,StartPos,EndPos);
}


STDMETHODIMP TRoadViewImpl::SetConnectionString(BSTR Str)
{
MainForm->Connection->ConnectionString = AnsiString(Str);
return true;
}


STDMETHODIMP TRoadViewImpl::GetConnectionString(BSTR* Str)
{
*Str = WideString(MainForm->Connection->ConnectionString).Detach();
return true;
}


