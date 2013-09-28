//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unAutoPoints.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFAutoPoints *FAutoPoints;
//---------------------------------------------------------------------------
__fastcall TFAutoPoints::TFAutoPoints(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TFAutoPoints::ReadIni(TIniFile *ini)
{
  edtFreq->Value = ini->ReadInteger("MISHADD","AutoPointFreq",3);
}

void TFAutoPoints::WriteIni(TIniFile *ini)
{
  ini->WriteInteger("MISHADD","AutoPointFreq",edtFreq->Value);
}

void __fastcall TFAutoPoints::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
  edtFreq->Value+= WheelDelta>0?1:-1;
}

int TFAutoPoints::getAutoPointsFreq()
{
   return edtFreq->Value;
}
//---------------------------------------------------------------------------
void __fastcall TFAutoPoints::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  TIniFile * ini;
  switch(Key){
     case VK_RETURN:
       ModalResult = mrOk;
       ini =new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
       WriteIni(ini);
       delete ini;
     break;
     case VK_ESCAPE:
       ModalResult = mrCancel;     
     break;
  }   
}
//---------------------------------------------------------------------------
void __fastcall TFAutoPoints::FormShow(TObject *Sender)
{
  TIniFile * ini =new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
  ReadIni(ini);
  delete ini;
}
//---------------------------------------------------------------------------
