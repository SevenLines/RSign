//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SaveViewForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSaveViewFrm *SaveViewFrm;
//---------------------------------------------------------------------------
__fastcall TSaveViewFrm::TSaveViewFrm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSaveViewFrm::ShowList(void)
{
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
    }
else
    Hide();
}

void __fastcall TSaveViewFrm::SetButtons(void)
{
ButOk->Enabled=ADODataSet1->RecordCount;
ButDelete->Enabled=ADODataSet1->RecordCount;
}

void __fastcall TSaveViewFrm::FormShow(TObject *Sender)
{
ShowList();
SetButtons();
}
//---------------------------------------------------------------------------
void __fastcall TSaveViewFrm::ButOkClick(TObject *Sender)
{
FViewId=ADODataSet1->FieldByName("id_")->AsInteger;
FViewName=ADODataSet1->FieldByName("Title")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TSaveViewFrm::ButDeleteClick(TObject *Sender)
{
if (ADODataSet1->RecordCount)
    {
    int VId=ADODataSet1->FieldByName("id_")->AsInteger;
    TADOCommand *Cm=new TADOCommand(this);
    Cm->Connection=MainForm->Connection;
    Cm->CommandText="delete from ELEM_Visible where NumView="+String(VId);
    Cm->Execute();
    delete Cm;
    ADODataSet1->Delete();
    }
SetButtons();
}
//---------------------------------------------------------------------------

void __fastcall TSaveViewFrm::ButAddClick(TObject *Sender)
{
ADODataSet1->Append();
SetButtons();
}
//---------------------------------------------------------------------------


void __fastcall TSaveViewFrm::ADODataSet1AfterDelete(TDataSet *DataSet)
{
SetButtons();  
}
//---------------------------------------------------------------------------

