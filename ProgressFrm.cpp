//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgressFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
#include "AcadExportThread.h"
#include "MickMacros.h"

TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
__fastcall TProgressForm::TProgressForm(TComponent* Owner)
    : TForm(Owner)
{
   setShowLog(false);
}
//---------------------------------------------------------------------------

void __fastcall TProgressForm::FormHide(TObject *Sender)
{
    Thread = 0;
    windowBelow = 0;
    showCancel = 0;
    setShowLog(false);
}
//---------------------------------------------------------------------------

void __fastcall TProgressForm::FormShow(TObject *Sender)
{
   pnlCancel->Visible = (bool)(Thread||showCancel);
   Terminated = false;
}
//---------------------------------------------------------------------------

void __fastcall TProgressForm::addLogLine(AnsiString &line)
{
   edtLog->Lines->Add(line);
   edtLog->SelStart = edtLog->GetTextLen();
   edtLog->Perform(EM_SCROLLCARET, 0, 0);
   BUILDER_INFO(line.c_str());
}

void __fastcall TProgressForm::cmdAbortClick(TObject *Sender)
{
  if(Thread){
      Thread->Terminate();
      ModalResult = mrOk;
  }
  Terminated = true;
  BUILDER_INFO("Отмена");
}
//---------------------------------------------------------------------------
void __fastcall TProgressForm::setShowLog(bool value) {
   showLog = value;
   Height = showLog?319:117;
   pnLog->Height = showLog?200:0;
   pnLog->Visible = showLog;
}

void __fastcall TProgressForm::setShowCancel(bool value) {
   showCancel = value;
   pnlCancel->Visible = showCancel;
}

void __fastcall TProgressForm::clearLog()
{
   edtLog->Lines->Clear();
}

void __fastcall TProgressForm::SetMinMax(int mn,int mx)
{
    ProgressBar->MinValue = -999999;
    ProgressBar->MaxValue = 0;
    ProgressBar->MaxValue=mx;
    ProgressBar->MinValue=mn;
}

void __fastcall TProgressForm::SetPosition(int p)
{
    ProgressBar->Progress=p;
    if(windowBelow) {
      SetWindowPos(Handle, HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    }
}

int __fastcall TProgressForm::GetPosition(void)
{
    return ProgressBar->Progress;
}

void __fastcall TProgressForm::SetNote(String s)
{
   Label->Caption=s;
   Repaint();
   Realign();
}

String __fastcall TProgressForm::GetNote(void)
{
    return Label->Caption;
}
