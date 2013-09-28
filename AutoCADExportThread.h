//---------------------------------------------------------------------------

#ifndef AutoCADExportThreadH
#define AutoCADExportThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "ProgressFrm.h"
#include "DataSour.h"
#include "acadexport.h"

//---------------------------------------------------------------------------
class AutoCADExportThread : public TThread
{            
private:
        AnsiString Note;
        int min,max;
        int pos;

protected:
        void __fastcall Execute();
public:
        __fastcall AutoCADExportThread(bool CreateSuspended);
        TDtaSource *MetricData;
        TRoad *R;
        TDictSource *Dict;
        TAcadExport *aexp;
        TProgressForm *frmProgress;
        void __fastcall UpdateProgress();
        void __fastcall UpdateCaption();
        void __fastcall UpdateMinMax();
};
//---------------------------------------------------------------------------
#endif
