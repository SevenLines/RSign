//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelNewObj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddObjFrm *AddObjFrm;
//---------------------------------------------------------------------------
__fastcall TAddObjFrm::TAddObjFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAddObjFrm::ShowObjList(void)
{
TreeView1->Items->Clear();
FDict->BuildClassesTree(TreeView1,NULL);
}

bool __fastcall TAddObjFrm::Execute(TDictSource *dict)
{
if (dict!=FDict)
    {
    FDict=dict;
    ShowObjList();
    }
bool res=ShowModal()==mrOk;
if (TreeView1->Selected)
    {
    FMetaClass=(TObjMetaClass*)TreeView1->Selected->Data;
    }
return res;
}
void __fastcall TAddObjFrm::FormActivate(TObject *Sender)
{
TreeView1->SetFocus();    
}
//---------------------------------------------------------------------------

void __fastcall TAddObjFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key){
     case VK_RETURN:
       Button1->Click();
     break;
     case VK_ESCAPE:
       Button2->Click();
     break;
  }   
}
//---------------------------------------------------------------------------

