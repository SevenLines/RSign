//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bmpexport.h"
#include "MainUnit.h.h"
#include "PreView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBmpParam *BmpParam;
//---------------------------------------------------------------------------
__fastcall TBmpParam::TBmpParam(TComponent* Owner)
    : TForm(Owner)
{
SetFileName("Export");
}

void __fastcall TBmpParam::SetFileName(String NewName)
{
int p1=NewName.LastDelimiter(".");
if (p1)
    FFileName=NewName.SubString(1,p1-1);
else
    FFileName=NewName;
p1=FFileName.LastDelimiter("\\");
if (p1)
    FNameEdit->Text=FFileName.SubString(p1+1,256);
else
    FNameEdit->Text=FFileName;
}

//---------------------------------------------------------------------------
void __fastcall TBmpParam::Button3Click(TObject *Sender)
{
if (SaveDialog1->Execute())
    {
    SetFileName(SaveDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TBmpParam::ScaleLChange(TObject *Sender)
{
if (AutoScale->Checked)
    {
    int x,y;
    if (MainForm->Pattern->GetPlanSize(x,y))
        {
        PLen->Position=(ScaleL->Text.ToInt()*x)/10000000;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TBmpParam::Edit7Change(TObject *Sender)
{
if (AutoScale->Checked)
    {
    int x,y;
    if (MainForm->Pattern->GetPlanSize(x,y))
        {
        ScaleL->Text=(Edit7->Text.ToInt()*10000000)/x;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TBmpParam::Button4Click(TObject *Sender)
{
PreViewFrm->SetPageList(MinKm->Position*1000,MaxKm->Position*1000,PLen->Position*1000,1);
PreViewFrm->ShowModal();    
}
//---------------------------------------------------------------------------


void __fastcall TBmpParam::FNameEditExit(TObject *Sender)
{
SetFileName(FNameEdit->Text);
}
//---------------------------------------------------------------------------

