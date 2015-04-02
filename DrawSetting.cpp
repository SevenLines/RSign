//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DrawSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDrwSetFrm *DrwSetFrm;
const int LScaleCount=3;
const int LScale[3]={20000,8000,4000};
const int XScaleCount=6;
const int XScale[6]={2000,1000,500,300,200,100};
const int XObjCount=5;
const int XObj[5]={5,10,15,25,50};
const int XBoundCount=5;
const int XBound[5]={10,25,50,75,100};
const int FontSizeCount=6;
const int FontSizes[6]={6,8,10,12,14,16};
//---------------------------------------------------------------------------
__fastcall TDrwSetFrm::TDrwSetFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDrwSetFrm::FormCreate(TObject *Sender)
{
for (int i=0;i<LScaleCount;i++)
    ComboScaleL->Items->Add(String(LScale[i]));
for (int i=0;i<XScaleCount;i++)
    {
    ComboScaleX->Items->Add(String(XScale[i]));
    ComboScaleP->Items->Add(String(XScale[i]));
    }
for (int i=0;i<XBoundCount;i++)
    ComboBoundX->Items->Add(String(XBound[i]));
for (int i=0;i<XObjCount;i++)
    ComboObjX->Items->Add(String(XObj[i]));
for (int i=0;i<FontSizeCount;i++)
    ComboFontSize->Items->Add(String(FontSizes[i]));
}
//---------------------------------------------------------------------------

int __fastcall TDrwSetFrm::GetScaleX(void)
{
return ComboScaleX->Text.ToInt();
}

int __fastcall TDrwSetFrm::GetScaleP(void)
{
return ComboScaleP->Text.ToInt();
}

int __fastcall TDrwSetFrm::GetBoundX(void)
{
return ComboBoundX->Text.ToInt();
}

int __fastcall TDrwSetFrm::GetScaleL(void)
{
return ComboScaleL->Text.ToInt();
}

int __fastcall TDrwSetFrm::GetFontSize(void)
{
return ComboFontSize->Text.ToInt();
}

void _fastcall TDrwSetFrm::SetScaleL(int x)
{
for (int i=0;i<LScaleCount;i++)
    if (x==LScale[i])
        {
        ComboScaleL->ItemIndex=i;
        return;
        }
ComboScaleL->Text=String(x);
}

void _fastcall TDrwSetFrm::SetScaleX(int x)
{
for (int i=0;i<XScaleCount;i++)
    if (x==XScale[i])
        {
        ComboScaleX->ItemIndex=i;
        return;
        }
ComboScaleX->Text=String(x);
}

void _fastcall TDrwSetFrm::SetScaleP(int x)
{
for (int i=0;i<XScaleCount;i++)
    if (x==XScale[i])
        {
        ComboScaleP->ItemIndex=i;
        return;
        }
ComboScaleP->Text=String(x);
}

void _fastcall TDrwSetFrm::SetBoundX(int x)
{
for (int i=0;i<XBoundCount;i++)
    if (x==XBound[i])
        {
        ComboBoundX->ItemIndex=i;
        return;
        }
ComboBoundX->Text=String(x);
}

void __fastcall TDrwSetFrm::SetObjX(int x)
{
for (int i=0;i<XObjCount;i++)
    if (x==XObj[i])
        {
        ComboObjX->ItemIndex=i;
        return;
        }
ComboObjX->Text=String(x);
}

void __fastcall TDrwSetFrm::SetFontSize(int x)
{
for (int i=0;i<FontSizeCount;i++)
    if (x==FontSizes[i])
        {
        ComboFontSize->ItemIndex=i;
        return;
        }
ComboFontSize->Text=String(x);
}

int __fastcall TDrwSetFrm::GetObjX(void)
{
return ComboObjX->Text.ToInt();
}

void __fastcall TDrwSetFrm::SetMetSource(int x)
{
GroupMetSource->ItemIndex=x;
}

int __fastcall TDrwSetFrm::GetMetSource(void)
{
return GroupMetSource->ItemIndex;
}

void __fastcall TDrwSetFrm::SetProfilKind(int x)
{
GroupProfKind->ItemIndex=x&1;
GroupProfilKind->ItemIndex=x>>1;
}

int __fastcall TDrwSetFrm::GetProfilKind(void)
{
return (GroupProfilKind->ItemIndex<<1)+GroupProfKind->ItemIndex;
}

void __fastcall TDrwSetFrm::SetKmInPage(int n)
{
KmUpDown->Position=n;
}

int __fastcall TDrwSetFrm::GetKmInPage(void)
{
return KmUpDown->Position;
}

void __fastcall TDrwSetFrm::SetHashFrameSize(int n) {
HashSizeUpDown->Position=n;
}

int __fastcall TDrwSetFrm::GetHashFrameSize(void) {
return HashSizeUpDown->Position;
}

void __fastcall TDrwSetFrm::ComboScaleXKeyPress(TObject *Sender, char &Key)
{
if (((Key<'0') || (Key>'9'))&&(Key!=8))
    Key=0;
}
//---------------------------------------------------------------------------

