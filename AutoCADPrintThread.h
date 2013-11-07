//---------------------------------------------------------------------------

#ifndef AutoCADPrintThreadH
#define AutoCADPrintThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "acadexport.h"
#include "ProgressFrm.h"
//---------------------------------------------------------------------------
class AutoCadPrintThread : public TThread
{            
private:
        

        AnsiString ProgressFormCaption;
        int ProgressFormPosition;
        int ProgressFormMin, ProgressFormMax;
        AcadPViewportPtr vpTop;
        AcadPViewportPtr vpCenter;
        AcadPViewportPtr vpBottom;

        AcadTextPtr text;
        AcadTextPtr page;

protected:
        void __fastcall Execute();
        void __fastcall setProgressFormCaption();
        void __fastcall setProgressFormPosition();
        void __fastcall setProgressFormMinMax();
        void __fastcall ShowModalPF();
        bool BindViewports();     
public:
        __fastcall AutoCadPrintThread(bool CreateSuspended);
        TProgressForm *ProgressForm;

        bool finfo, fOnly;
        int iMin, iMax, iPage, vStep;
        int iTop,iCenter,iBottom;
        int vcBottom, vcCenter, vcTop;
        AnsiString pattern, FileName;
        AutoCADHelper helper;
};
//---------------------------------------------------------------------------
#endif
