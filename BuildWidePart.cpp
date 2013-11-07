//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BuildWidePart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWidePartDialog *frmWidePartDialog;
//---------------------------------------------------------------------------
__fastcall TfrmWidePartDialog::TfrmWidePartDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmWidePartDialog::FormShow(TObject *Sender)
{
comboSideKind->Items->Clear();
if (FDict)
    FDict->TextPropByClasses(comboSideKind->Items,SIDESTRENGTHCODE);
}
//---------------------------------------------------------------------------

