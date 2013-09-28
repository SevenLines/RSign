//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OpenRoad.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpenRoadDialog *OpenRoadDialog;
//---------------------------------------------------------------------------
__fastcall TOpenRoadDialog::TOpenRoadDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpenRoadDialog::Button1Click(TObject *Sender)
{
   FRoadName=ListRoads_DataSet->FieldByName("FullTitle")->AsString;
   FRoadId=ListRoads_DataSet->FieldByName("id_")->AsInteger;
}
//---------------------------------------------------------------------------


void __fastcall TOpenRoadDialog::txtFilterChange(TObject *Sender)
{
  ListRoads_DataSet->Filtered=false;
  if(txtFilter->Text.IsEmpty())
  {
    return;
  }
  AnsiString f;
  f.sprintf("FullTitle like '%%%s%%'",txtFilter->Text.c_str());
  ListRoads_DataSet->Filter=f;
  ListRoads_DataSet->Filtered=true;
}
//---------------------------------------------------------------------------
void __fastcall TOpenRoadDialog::txtIDFilterChange(TObject *Sender)
{
  ListRoads_DataSet->Filtered=false;
  if(txtIDFilter->Text.IsEmpty())
  {
    return;
  }
  AnsiString f;
  f.sprintf("id_=%s",txtIDFilter->Text.c_str());
  ListRoads_DataSet->Filter=f;
  ListRoads_DataSet->Filtered=true;

}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::FormShow(TObject *Sender)
{
  if(!ListRoads_DataSet->Active)ListRoads_DataSet->Active=true;
  txtIDFilter->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::DBGrid1DblClick(TObject *Sender)
{
  Button1->Click(); /* ÇÄÅÑÜ ÁÛË ÌÈØÀ */
}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::FormKeyDown(TObject *Sender, WORD &Key,
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

