//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MoveForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmoveDialog *moveDialog;
//---------------------------------------------------------------------------
__fastcall TmoveDialog::TmoveDialog(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
