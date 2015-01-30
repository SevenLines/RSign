//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ItemSelectDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TItemSelectDialogForm *ItemSelectDialogForm;
//---------------------------------------------------------------------------
__fastcall TItemSelectDialogForm::TItemSelectDialogForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TItemSelectDialogForm::setOptions(map<AnsiString, AnsiString> &items, AnsiString message)
{
   cmbOptions->Clear();
   lblMessage->Caption = message;
   
   if (items.size() > 0) {
     map<AnsiString, AnsiString>::iterator it = items.begin();
     for(;it!=items.end(); ++it) {
        cmbOptions->AddItem(it->first, 0);
        params[it->first] = it->second;
     }
     cmbOptions->ItemIndex = 0;
   }
}

AnsiString TItemSelectDialogForm::selectedItem()
{
   if (cmbOptions->ItemIndex == -1) return "";
   AnsiString key = cmbOptions->Items->Strings[cmbOptions->ItemIndex];
   return params[key];
}
void __fastcall TItemSelectDialogForm::FormKeyPress(TObject *Sender,
      char &Key)
{
   switch(Key) {
   case VK_ESCAPE:
       ModalResult = mrCancel;
       break;
   }
}
//---------------------------------------------------------------------------

