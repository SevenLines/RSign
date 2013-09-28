//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AutoCADAddRowsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAddRows *FAddRows;
//---------------------------------------------------------------------------
__fastcall TFAddRows::TFAddRows(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFAddRows::FormShow(TObject *Sender)
{
   Edit2->Text = path;
}
//---------------------------------------------------------------------------
void __fastcall TFAddRows::Button1Click(TObject *Sender)
{
   SaveDialog1->FileName = path;
   if(SaveDialog1->Execute()) {
      Edit2->Text = SaveDialog1->FileName;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFAddRows::FormHide(TObject *Sender)
{
   path = Edit2->Text;
}
//---------------------------------------------------------------------------
