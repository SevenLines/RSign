//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OpenViewForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpenViewFrm *OpenViewFrm;
//---------------------------------------------------------------------------
__fastcall TOpenViewFrm::TOpenViewFrm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpenViewFrm::FormShow(TObject *Sender)
{
MainForm->Connection->Connected=true;
if (MainForm->Connection->Connected)
    {
    ADODataSet1->Connection=MainForm->Connection;
    if(ADODataSet1->Active) ADODataSet1->Active=false;
    ADODataSet1->CommandText="select id_,Title,NumRoad from ELEM_ListView where NumRoad="+String(RoadId);
    if(!ADODataSet1->Active) ADODataSet1->Active=true;
    TADOCommand *Cm=new TADOCommand(this);
    Cm->Connection=MainForm->Connection;
    Cm->CommandText="delete from ELEM_ListView where NumRoad is NULL";
    Cm->Execute();
    delete Cm;
    ButOk->Enabled=ADODataSet1->RecordCount;
    ADODataSet1->Last();/*ÌÈØÀ*/
    }
else
    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TOpenViewFrm::ButOkClick(TObject *Sender)
{
FViewId=ADODataSet1->FieldByName("id_")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TOpenViewFrm::DBGrid1DblClick(TObject *Sender)
{
  ButOk->Click(); /* ÇÄÅÑÜ ÁÛË ÌÈØÀ */
}
//---------------------------------------------------------------------------

void __fastcall TOpenViewFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   switch(Key){
      case VK_RETURN:
         ButOk->Click();
      break;
      
      case VK_ESCAPE:
         ButCancel->Click();
      break;
   }   
}
//---------------------------------------------------------------------------

