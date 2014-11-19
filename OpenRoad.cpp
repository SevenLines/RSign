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
   Mode=0;
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
    if (Mode==1) {
        ListRoads_DataSet->Filter="pid="+IntToStr(FRoadId);
        Button3->Caption="Титулы";
    } else if (Mode==0) {
       String f;

       bool fWas = false;

       // фильтр перечня
       // lastGroupId меняется при выборе перечня из выпадающего списка
       if (lastGroupId != -1 && lastGroupId < cbGroup->Items->Count) {
          if ((int)cbGroup->Items->Objects[lastGroupId]!=0) {
            int groupID = (int)cbGroup->Items->Objects[lastGroupId];
            f="NumGroup="+IntToStr(groupID);
            fWas = true;
          }
       }

       // фильтр по ID-ишнику
       if (!txtIDFilter->Text.IsEmpty()) {
          int id;
          if (TryStrToInt(txtIDFilter->Text, id)) {
            if (fWas) f+=" and ";
            f+="id_="+txtIDFilter->Text;
          }
       } else {
          // фильтр района
          if (cbDist->ItemIndex > -1 && cbDist->ItemIndex < cbDist->Items->Count) {
             if ((int)cbDist->Items->Objects[cbDist->ItemIndex]!=0) {
               if (fWas) f+=" and ";
               fWas = true;
               try {
                f +="did="+IntToStr((int)cbDist->Items->Objects[cbDist->ItemIndex]);
               } catch (...) {}
             }
          }
          // фильтр по названию
          if (!txtFilter->Text.IsEmpty()) {
             if (fWas) f+=" and ";
             fWas = true;
             f+="FullTitle like '%"+txtFilter->Text+"%'";
          }
       }
       ListRoads_DataSet->Filter=f;
       Button3->Caption="Подтитулы";
    }
}


void __fastcall TOpenRoadDialog::FormShow(TObject *Sender)
{
 SubTitul_DataSet->Open();
 TADODataSet *ds=new TADODataSet(this); 

 ds->Connection=MainForm->Connection;
 ds->CommandText="select * from ListTitleGroups";
 ds->Open();
 int oldid=-1;
 if (cbGroup->ItemIndex>=0)
    oldid=(int)cbGroup->Items->Objects[cbGroup->ItemIndex];
 cbGroup->Items->Clear();

 int all=0;
 for (int i=0;i<ds->RecordCount;i++) {
   int id=ds->FieldByName("id_")->AsInteger;
   if (id==oldid) all=i;
   else if (id==0 && oldid==-1) all=i;
   cbGroup->Items->AddObject(ds->FieldByName("FullTitle")->AsString,(TObject*)id);
   ds->Next();
 }
 ds->Close();
 // востанавливаем индекс перечня
 cbGroup->ItemIndex=lastGroupId;
 oldid=-1;
 if (cbDist->ItemIndex>=0)
    oldid=(int)cbDist->Items->Objects[cbDist->ItemIndex];
 cbDist->Items->Clear();
 ds->CommandText="select * from ListDistricts order by FullTitle";
 ds->Open();
 all=0;
 for (int i=0;i<ds->RecordCount;i++) {
   int id=ds->FieldByName("id_")->AsInteger;
   if (id==oldid) all=i;
   if (id==0 && oldid==-1) all=i;
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
  Button1->Click(); /* ЗДЕСЬ БЫЛ МИША */
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
   lastGroupId = cbGroup->ItemIndex; // меняем lastGroupId
   SetFilter(Sender); // обновляем фильтр
}
//---------------------------------------------------------------------------


void __fastcall TOpenRoadDialog::ListRoads_DataSetAfterScroll(
      TDataSet *DataSet)
{
   FRoadId=ListRoads_DataSet->FieldByName("id_")->AsInteger;
   SubTitul_DataSet->Filter="pid="+IntToStr(FRoadId);
   Button3->Enabled=SubTitul_DataSet->RecordCount>0 && RoadId>0 || Mode==1;
}
//---------------------------------------------------------------------------

void __fastcall TOpenRoadDialog::Button3Click(TObject *Sender)
{
   Mode=1-Mode;
   SetFilter(0);
}
//---------------------------------------------------------------------------

