//---------------------------------------------------------------------------

#ifndef AcadExportThreadH
#define AcadExportThreadH

#include "without_autocad.h"
#ifndef WITHOUT_AUTOCAD

#include "acadexport.h"
#include "ProgressFrm.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

class TDtaSource;

struct wpbar {
    TRoadBarrier *b;
    TRoadSignal *s;
    TSquareRoadSideObject_Kromka *w;
    TRoadLighting *l;
    TLinearRoadSideObject *a;
    bool exist;
    wpbar(TRoadBarrier *_b,bool e) {
        b=_b;        exist=e;        s=0;        w=0;        l=0;        a=0;
    }
    wpbar(TRoadSignal *_s,bool e) {
        b=0;        exist=e;        s=_s;        w=0;        l=0;        a=0;
    }
    wpbar(TSquareRoadSideObject_Kromka *_w,bool e) {
        b=0;        exist=e;        s=0;        w=_w;        l=0;        a=0;
    }
    wpbar(TRoadLighting *_l,bool e) {
        b=0;        exist=e;        s=0;        w=0;        l=_l;        a=0;
    }
    wpbar(TLinearRoadSideObject *_a,bool e) {
        b=0;        exist=e;        s=0;        w=0;        l=0,a=_a;
    }
};

class AcadExportThread : public TThread
{
private:
        TAcadExport *aexp;
        TRoad *R;

        AnsiString ProgressFormCaption;
        AnsiString ProgressFormLogLine;
        int ProgressFormPosition;
        int ProgressFormMin, ProgressFormMax;

protected:
        void __fastcall Execute();
        void __fastcall deleteRoad();
        void __fastcall setProgressFormCaption();
        void __fastcall setProgressFormPosition();
        void __fastcall setProgressFormMinMax();
        void __fastcall addProgressFormLogLine();

        int __fastcall ExportTowns(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportPlan(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportSurface(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportRoadMetrics(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportProfile(TDtaSource* metricData, TRoad* road, TAcadExport* aexp);
        int __fastcall ExportAttachments(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportRoadSideObjects(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportCommunications(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportCityObjects(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportTrafficLights(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportTubes(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportBridges(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportBusstops(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportMoundHeights(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportRoadSigns(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportRoadMark(TDtaSource* data, TAcadExport* aexp, int linewidth, int* leftMax=0, int* rightMax=0);
        int __fastcall SortCurrentAndProjectObjects(TDtaSource* dataCurrent, TDtaSource* dataProject, vector<pair<int,wpbar> > &out);
        int __fastcall ExportSignal(vector<pair<int,wpbar> > &data, TAcadExport* aexp);
        int __fastcall ExportSidewalks(vector<pair<int,wpbar> > &data, TAcadExport* aexp);
        int __fastcall ExportLamps(vector<pair<int,wpbar> > &data, TAcadExport* aexp);
        int __fastcall ExportBorders(vector<pair<int,wpbar> > &data, TAcadExport* aexp);
        int __fastcall ExportSlope(TDtaSource* data, TAcadExport* aexp);
        int __fastcall ExportCurves(TDtaSource* data, TAcadExport* aexp);        
public:
        __fastcall AcadExportThread(bool CreateSuspended, TRoad *r);
        void __fastcall Clear();
        void OutInfoLog(AnsiString str);
        void ProgressChanged(int progress, AnsiString message);

        __property bool IsTerminated = {read = Terminated};

        int ExportTo;
        int ExportTable;
        AnsiString FileName;
        AnsiString RoadName;

        TFAutoCADExport *FAutoCADExport;
        TProgressForm *ProgressForm;
        TDtaSource *MetricData;
        TDictSource* Dict;
        TDtaSource* ProfilData;
        TDtaSource* CurveData; 
};
//---------------------------------------------------------------------------

#endif // WITHOUT_AUTOCAD

#endif

