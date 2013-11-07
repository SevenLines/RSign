//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SqlEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSqlEditFrm *SqlEditFrm;
//---------------------------------------------------------------------------
__fastcall TSqlEditFrm::TSqlEditFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool __fastcall TSqlEditFrm::Execute(TObjMetaClass *meta)
{
FSql[0]=meta->Sql;
FSql[1]=meta->SqlSave;
FSql[2]=meta->SqlAppend;
FSql[3]=meta->SqlDelete;
Memo1->Modified=false;
RadioGroup1Click(NULL);
bool res=ShowModal()==mrOk;
if (res)
    {
    RadioGroup1Click(NULL);
    meta->SetSQL(FSql[0],FSql[1],FSql[2],FSql[3]);
    }
return res;
}
void __fastcall TSqlEditFrm::RadioGroup1Click(TObject *Sender)
{
if (Memo1->Modified)
    FSql[FOldIndex]=Memo1->Text;
FOldIndex=RadioGroup1->ItemIndex;
Memo1->Text=FSql[FOldIndex];
Memo1->Modified=false;
}
//---------------------------------------------------------------------------


