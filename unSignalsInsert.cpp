//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unSignalsInsert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfrmSignalsInsert *frmSignalsInsert;
//---------------------------------------------------------------------------
__fastcall TfrmSignalsInsert::TfrmSignalsInsert(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::FormShow(TObject *Sender)
{
   if(RoadSignal){
     edtEnd->Text = _iBegin = RoadSignal->LMax;
     edtBegin->Text = _iEnd = RoadSignal->LMin;
     edtEveryChange(0);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::FormClose(TObject *Sender, TCloseAction &Action)
{

  RoadSignal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::edtEveryChange(TObject *Sender)
{
  TCSpinEdit *spin = dynamic_cast<TCSpinEdit*>(Sender);
  if(spin&&RoadSignal){
    int iBegin,iEnd, val;
    float tf;
    if(TryStrToInt(edtBegin->Text,iBegin)){
      _iBegin = iBegin;
    }
    if(TryStrToInt(edtEnd->Text,iEnd)){
      _iEnd = iEnd;
    }
    if(TryStrToInt(spin->Text, val)) {
      if(val>0) {
        tf = RoundTo((float)(_iEnd - _iBegin)/(val*100),0)+1;
        AnsiString str = lblCount->Caption.sprintf("итого: %i ст.",(int)tf);
        lblCount->Caption = str;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::Button1Click(TObject *Sender)
{
  int iBegin,iEnd, iTemp;

  if(RoadSignal){
    float tf;
    if(!RoadSignal->Kind)RoadSignal->Kind = skStolb;
    iTemp = RoadSignal->DX;
    if(!RoadSignal->Placement)RoadSignal->Placement = opLeft;
    if(TryStrToInt(edtBegin->Text,iBegin)){
      _iBegin = iBegin;//RoadSignal->SetL(iBegin);
    }
    if(TryStrToInt(edtEnd->Text,iEnd)){
      _iEnd = iEnd;//RoadSignal->SetLMax(iEnd);
    }
    switch(rgMain->ItemIndex){
       case 0:
         tf = RoundTo((float)(_iEnd - _iBegin)/(edtEvery->Value*100),0)+1;
         RoadSignal->Count = tf;
         RoadSignal->SetL(_iBegin);
         RoadSignal->SetLMax(_iEnd);
       break;
       
       case 1:
         RoadSignal->SetL(_iEnd - edtEvery->Value*100*(edtCount->Value-1));
         RoadSignal->Count = edtCount->Value;
         RoadSignal->SetLMax(_iEnd);
       break;

       case 2:
         RoadSignal->SetL(_iBegin);
         RoadSignal->Count = edtCount->Value;
         RoadSignal->SetLMax(_iBegin+edtEvery->Value*100*(edtCount->Value-1));
       break;
       case 3:
         iTemp = edtEvery->Value*100*(edtCount->Value-1);
         RoadSignal->SetL(_iBegin-iTemp/2);
         RoadSignal->Count = edtCount->Value;
         RoadSignal->SetLMax(_iBegin+iTemp/2);
       break;
    }

  }        
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key){
    case VK_RETURN:
      Button1->Click();
    break;
    case VK_ESCAPE:
      ModalResult = mrCancel;
    break;
  }
  Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignalsInsert::FormMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
  if(edtEvery->Focused()){
      edtEvery->Value += WheelDelta>0?1:-1;
  }
  if(edtCount->Focused()){
      edtCount->Value += WheelDelta>0?1:-1;
  }
  Handled = true;
}
//---------------------------------------------------------------------------
