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
    lastGroupId = -1;
}
//---------------------------------------------------------------------------
void __fastcall TOpenRoadDialog::Button1Click(TObject *Sender)
{
   FRoadName=ListRoads_DataSet->FieldByName("FullTitle")->AsString;
   FRoadId=ListRoads_DataSet->FieldByName("id_")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::SetFilter(TObject *Sender) {
   String f;
   bool fWas = false;
   int groupID = -1;
   if (lastGroupId != -1 && lastGroupId < cbGroup->Items->Count) {
      groupID = (int)cbGroup->Items->Objects[lastGroupId];
      f="NumGroup="+IntToStr(groupID);
      fWas = true;
   }
   if (!txtIDFilter->Text.IsEmpty()) {
      if (fWas) f+=" and ";
      f+="id_="+txtIDFilter->Text;
   } else {
      if (groupID > 0) {
         if (fWas) f+=" and ";
         fWas = true;
         f +="did="+IntToStr((int)cbDist->Items->Objects[cbDist->ItemIndex]);
      }
      if (!txtFilter->Text.IsEmpty()) {
         if (fWas) f+=" and ";
         fWas = true;
         f+="FullTitle like '%"+txtFilter->Text+"%'";
      }
   }
   ListRoads_DataSet->Filter=f;
}


void __fastcall TOpenRoadDialog::FormShow(TObject *Sender)
{
 TADODataSet *ds=new TADODataSet(this);
 ds->Connection=MainForm->Connection;
 ds->CommandText="select * from ListTitleGroups";
 ds->Open();
 cbGroup->Items->Clear();

 int all=0;
 for (int i=0;i<ds->RecordCount;i++) {
   int id=ds->FieldByName("id_")->AsInteger;
   if (id==0) all=i;
   cbGroup->Items->AddObject(ds->FieldByName("FullTitle")->AsString,(TObject*)id);
   ds->Next();
 }
 ds->Close();
 cbGroup->ItemIndex=lastGroupId;
 cbDist->Items->Clear();
 ds->CommandText="select * from ListDistricts order by FullTitle";
 ds->Open();
 all=0;
 for (int i=0;i<ds->RecordCount;i++) {
   int id=ds->FieldByName("id_")->AsInteger;
   if (id==0) all=i;
   cbDist->Items->AddObject(ds->FieldByName("FullTitle")->AsString,(TObject*)id);
   ds->Next();
 }
 cbDist->ItemIndex=all;
 ds->Close();
 delete ds;
 if(!ListRoads_DataSet->Active)ListRoads_DataSet->Active=true;
  txtIDFilter->SetFocus();  //TDBListBox
 SetFilter(0); 
}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::DBGrid1DblClick(TObject *Sender)
{
  Button1->Click(); /* ����� ��� ���� */
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
void TOpenRoadDialog::LoadIni(TIniFile *ini)
{
    txtFilter->Text = ini->ReadString("OpenRoadDialog", "txtFilter", "");
    txtIDFilter->Text = ini->ReadString("OpenRoadDialog", "txtIDFilter", "");
    lastGroupId = ini->ReadInteger("OpenRoadDialog", "lastGroupId", -1);
}
//---------------------------------------------------------------------------
void TOpenRoadDialog::SaveIni(TIniFile *ini)
{
    ini->WriteString("OpenRoadDialog", "txtFilter", txtFilter->Text);
    ini->WriteString("OpenRoadDialog", "txtIDFilter", txtIDFilter->Text);
    ini->WriteInteger("OpenRoadDialog", "lastGroupId", lastGroupId);
}
//---------------------------------------------------------------------------
void __fastcall TOpenRoadDialog::cbGroupChange(TObject *Sender)
{
   lastGroupId = cbGroup->ItemIndex;
   SetFilter(Sender);
}
//---------------------------------------------------------------------------

