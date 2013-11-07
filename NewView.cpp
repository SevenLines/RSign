//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewView.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewViewDialog *NewViewDialog;
//---------------------------------------------------------------------------
__fastcall TNewViewDialog::TNewViewDialog(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNewViewDialog::FormShow(TObject *Sender)
{
SourcesList->Items->BeginUpdate();
SourcesList->Items->Clear();
ADODataSet1->Connection=MainForm->Connection;
MainForm->Connection->Connected=true;
if (MainForm->Connection->Connected)
    {
    ADODataSet1->CommandText=String("select id_,FullTitle from \
        ListDataSources where NumRoad=")+String(RoadId)+String(" or id_<10 order by id_");
    ADODataSet1->Open();
    for (int i=0;i<ADODataSet1->RecordCount;i++)
        {
        String Title=ADODataSet1->FieldByName("FullTitle")->AsString;
        __int32 id=ADODataSet1->FieldByName("id_")->AsInteger;
        SourcesList->Items->AddObject(Title,(TObject*)id);
        ADODataSet1->Next();
        }
    ADODataSet1->Close();
    }
SourcesList->Items->EndUpdate();
FSourcesCount=0;
Button1->Enabled=false;
}
//---------------------------------------------------------------------------
__int32 __fastcall TNewViewDialog::GetDataSource(int n)
{
for (int i=0;i<SourcesList->Items->Count;i++)
    if (SourcesList->Checked[i])
        if (n)
            n--;
        else
            {
            return (__int32)(SourcesList->Items->Objects[i]);
            }
return -1;
}
void __fastcall TNewViewDialog::SourcesListClickCheck(TObject *Sender)
{
FSourcesCount=0;
for (int i=0;i<SourcesList->Items->Count;i++)
    if (SourcesList->Checked[i])
        FSourcesCount++;
Button1->Enabled=FSourcesCount;  
}
//---------------------------------------------------------------------------
