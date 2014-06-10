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
#include <iostream>

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
    String __fastcall GetNote(void);
    void __fastcall SetNote(String s);
    int __fastcall GetPosition(void);

    void __fastcall SetPosition(int p);
    void __fastcall TProgressForm::setShowLog(bool value);
    void __fastcall TProgressForm::setShowCancel(bool value);
public:		// User declarations
    __fastcall TProgressForm(TComponent* Owner);
    void __fastcall SetMinMax(int mn,int mx);
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
