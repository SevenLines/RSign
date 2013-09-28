//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DumpForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDumpDialog *DumpDialog;
//---------------------------------------------------------------------------
__fastcall TDumpDialog::TDumpDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDumpDialog::Button1Click(TObject *Sender)
{
SvDialog->FileName=FilePath->Text+String("\\")+FileName->Text;
if (SvDialog->Execute())
    {
    int pos=SvDialog->FileName.LastDelimiter("\\");
    FilePath->Text=SvDialog->FileName.SubString(1,pos-1);
    FileName->Text=SvDialog->FileName.SubString(pos+1,1000);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDumpDialog::Button2Click(TObject *Sender)
{
if (DataSrcList->ItemIndex>=0)
    {
    TDtaSource *Dta=dynamic_cast<TDtaSource*>(DataSrcList->Items->Objects[DataSrcList->ItemIndex]);
    Dta->DumpName=FileName->Text;
    Dta->DumpPath=FilePath->Text;
    bool savegeom=SaveGeom->Checked;
    MainForm->Shared->Dump(Dta->DumpPath);
    FCurrentDict->Dump(Dta->DumpPath);
    Dta->Dump(FCurrentDict,savegeom);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDumpDialog::SetCurrentData(TDtaSource* data)
{
for (int i=0;i<DataSrcList->Items->Count;i++)
    if (DataSrcList->Items->Objects[i]==data)
        {
        DataSrcList->ItemIndex=i;
        DataSrcListChange(DataSrcList);
        break;
        }
}

void __fastcall TDumpDialog::DataSrcListChange(TObject *Sender)
{
if (DataSrcList->ItemIndex>=0)
    {
    TDtaSource *Dta=dynamic_cast<TDtaSource*>(DataSrcList->Items->Objects[DataSrcList->ItemIndex]);
    FilePath->Text=Dta->DumpPath;
    FileName->Text=Dta->DumpName;
    }
}
//---------------------------------------------------------------------------

