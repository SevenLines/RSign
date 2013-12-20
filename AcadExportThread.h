//---------------------------------------------------------------------------

#ifndef AcadExportThreadH
#define AcadExportThreadH

#include "acadexport.h"
#include "ProgressFrm.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
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
        void __fastcall setProgressFormCaption();
        void __fastcall setProgressFormPosition();
        void __fastcall setProgressFormMinMax();
        void __fastcall addProgressFormLogLine();
public:
        __fastcall AcadExportThread(bool CreateSuspended);
        void __fastcall Clear();
        void OutInfoLog(AnsiString &str);

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
#endif
