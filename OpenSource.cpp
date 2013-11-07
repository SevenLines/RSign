//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OpenSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpenSourceDialog *OpenSourceDialog;
//---------------------------------------------------------------------------
__fastcall TOpenSourceDialog::TOpenSourceDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpenSourceDialog::FormShow(TObject *Sender)
{
if(ADODataSet1->Active) ADODataSet1->Active=false;
ADODataSet1->CommandText="select id_,FullTitle,Executor,Examiner,DateCreate,NumType\
 from ListDataSources where NumRoad="+String(RoadId)+" or id_<10 order by id_";
if(!ADODataSet1->Active) {
   ADODataSet1->Active=true;
   ADODataSet1->Last();/*лхью*/
}
}
//---------------------------------------------------------------------------


void __fastcall TOpenSourceDialog::Button1Click(TObject *Sender)
{
FDataSource=ADODataSet1->FieldByName("id_")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TOpenSourceDialog::FormKeyDown(TObject *Sender, WORD &Key,
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

void __fastcall TOpenSourceDialog::DBGrid1DblClick(TObject *Sender)
{
  Button1->Click(); /* гдеяэ ашк лхью */   
}
//---------------------------------------------------------------------------

