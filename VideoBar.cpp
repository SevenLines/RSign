//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VideoBar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmVideoBar *frmVideoBar;
//---------------------------------------------------------------------------
__fastcall TfrmVideoBar::TfrmVideoBar(TComponent* Owner)
    : TForm(Owner)
{
}
void __fastcall TfrmVideoBar::CreateParams(TCreateParams &Params) {
  TForm::CreateParams(Params);
  Params.Style=(Params.Style) & ~WS_CAPTION;
  
}
//---------------------------------------------------------------------------
