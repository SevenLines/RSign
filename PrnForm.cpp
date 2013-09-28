//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrnForm.h"
#include "PreView.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnParam *PrnParam;
//---------------------------------------------------------------------------
__fastcall TPrnParam::TPrnParam(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPrnParam::Button3Click(TObject *Sender)
{
PrintDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TPrnParam::Button4Click(TObject *Sender)
{
int plen=PLen->Position*1000+PLenM->Position;
int skm=MinKm->Position*1000+PrnParam->MinKmM->Position;
int ekm=MaxKm->Position*1000+PrnParam->MaxKmM->Position;
PreViewFrm->SetPageList(skm,ekm,plen,0);
PreViewFrm->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TPrnParam::Edit7Change(TObject *Sender)
{
if (AutoScale->Checked)
    {
    int x,y;
    if (MainForm->Pattern->GetPlanSize(x,y))
        {
        int plen=PLen->Position*1000+PLenM->Position;
        ScaleL->Text=(plen*10000)/x;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrnParam::ScaleLChange(TObject *Sender)
{
if (AutoScale->Checked)
    {
    int x,y;
    if (MainForm->Pattern->GetPlanSize(x,y))
        {
        int plen=(ScaleL->Text.ToInt()*x)/10000;
        PLen->Position=plen/1000;
        PLenM->Position=plen%1000;
        }
    }
}
//---------------------------------------------------------------------------


