//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GeomControls.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmGeomControls *frmGeomControls;
//---------------------------------------------------------------------------
__fastcall TfrmGeomControls::TfrmGeomControls(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGeomControls::FormShow(TObject *Sender)
{
//
    this->clbCeomControls->Clear();
    for(int i = 0; i < frmShowVideo->ssSizeOf; i++)
    {
        this->clbCeomControls->AddItem(frmShowVideo->GeomControls[i].ssCaption, NULL);
        this->clbCeomControls->Checked[i] = frmShowVideo->GeomControls[i].ssVisible;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGeomControls::Button1Click(TObject *Sender)
{
    for(int i = 0; i < clbCeomControls->Items->Count; i++)
    {
        frmShowVideo->GeomControls[i].ssVisible = this->clbCeomControls->Checked[i];
    }
}
//---------------------------------------------------------------------------
