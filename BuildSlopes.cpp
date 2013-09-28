//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BuildSlopes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBuildSlopes *frmBuildSlopes;
//---------------------------------------------------------------------------
__fastcall TfrmBuildSlopes::TfrmBuildSlopes(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmBuildSlopes::SetProfilMinLen(int x)
    {ProfMinLen->Position=x;}
int __fastcall TfrmBuildSlopes::GetProfilMinLen(void)
    {return ProfMinLen->Position;}
void __fastcall TfrmBuildSlopes::SetProfilMaxDev(int x)
    {ProfMaxDev->Position=x;}
int __fastcall TfrmBuildSlopes::GetProfilMaxDev(void)
    {return ProfMaxDev->Position;}
void __fastcall TfrmBuildSlopes::SetProfilVal1(int x)
    {ProfVal1->Position=x;}
int __fastcall TfrmBuildSlopes::GetProfilVal1(void)
    {return ProfVal1->Position;}
void __fastcall TfrmBuildSlopes::SetProfilVal2(int x)
    {ProfVal2->Position=x;}
int __fastcall TfrmBuildSlopes::GetProfilVal2(void)
    {return ProfVal2->Position;}
void __fastcall TfrmBuildSlopes::SetStartPos(int x)
    {edtStartPos->Text=String(x);}
int __fastcall TfrmBuildSlopes::GetStartPos(void)
    {return edtStartPos->Text.ToInt();}
void __fastcall TfrmBuildSlopes::SetEndPos(int x)
    {edtEndPos->Text=String(x);}
int __fastcall TfrmBuildSlopes::GetEndPos(void)
    {return edtEndPos->Text.ToInt();}
