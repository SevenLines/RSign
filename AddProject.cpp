//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddProjectForm *AddProjectForm;
//---------------------------------------------------------------------------
__fastcall TAddProjectForm::TAddProjectForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddProjectForm::ProjNameChange(TObject *Sender)
{
Button1->Enabled=(ProjName->Text!="")&&(ExecName->Text!="")&&(ExamName->Text!="")&&(!OrgName->KeyValue.IsNull());
}
//---------------------------------------------------------------------------
void __fastcall TAddProjectForm::FormShow(TObject *Sender)
{
if(ADODataSet1->Active) ADODataSet1->Active=false;
ADODataSet1->CommandText="select * from ListOrganizations where NumTypeOrg=2 order by FullTitle";
if(!ADODataSet1->Active) ADODataSet1->Active=true;
OrgName->ListField="FullTitle";
OrgName->KeyField="id_";
}
//---------------------------------------------------------------------------

