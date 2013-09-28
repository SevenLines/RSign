//---------------------------------------------------------------------------

#ifndef ProgressFrmH
#define ProgressFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CGAUGES.h"
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TProgressForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TPanel *Panel3;
        TCGauge *ProgressBar;
        TPanel *pnlCancel;
        TButton *cmdAbort;
        TLabel *Label;
        TPanel *pnLog;
        TRichEdit *edtLog;
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall cmdAbortClick(TObject *Sender);
private:	// User declarations
    String __fastcall GetNote(void)
        {return Label->Caption;}
    void __fastcall SetNote(String s)
        {Label->Caption=s;
         Repaint();}
    int __fastcall GetPosition(void)
        {return ProgressBar->Progress;}

    void __fastcall SetPosition(int p)
        {ProgressBar->Progress=p;
         if(windowBelow) {
           SetWindowPos(Handle, HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
         }
        }
    void __fastcall TProgressForm::setShowLog(bool value);
    void __fastcall TProgressForm::setShowCancel(bool value);
public:		// User declarations
    __fastcall TProgressForm(TComponent* Owner);
    void __fastcall SetMinMax(int mn,int mx)
        {ProgressBar->MinValue=mn;
         ProgressBar->MaxValue=mx;
        }

    void __fastcall addLogLine(AnsiString &line);
    void __fastcall clearLog();

    bool   Terminated;
    __property String Note={read=GetNote,write=SetNote};
    __property int Position={read=GetPosition,write=SetPosition};
    __property bool ShowLog={read=showLog, write=setShowLog};
    __property bool ShowCancel={read=showCancel, write=setShowCancel};
    TThread *Thread;
    bool showCancel;
    bool showLog;
    HWND windowBelow;
};
//---------------------------------------------------------------------------
extern PACKAGE TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
#endif
