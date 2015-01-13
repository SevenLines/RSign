//---------------------------------------------------------------------------


#pragma hdrstop

#include "SignPanel.h"
#include "DrawMan.h"
#include "MainUnit.h"
#include "Buttons.hpp"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TSignPanel::TSignPanel(TComponent *Owner) :
    TPanel(Owner)
{
BevelOuter=bvNone;
BevelInner=bvNone;
Caption="";
Codes=new TStringList;
Buttons=NULL;
}

__fastcall TSignPanel::~TSignPanel()
{
delete Codes;
delete[] Buttons;
}

void __fastcall TSignPanel::SetSigns(int count,int size)
{
Codes->Clear();
delete[] Buttons;
Buttons=new TSpeedButton* [count];
FCount=count;
FSize=size;
FActCount=0;
while (ComponentCount)
    delete Components[0];
for (int i=0;i<count;i++)
    {
    TSpeedButton *but=new TSpeedButton(this);
    but->Width=size;
    but->Height=size;
    but->Top=0;
    but->Left=i*size;
    but->Tag=i;
    but->Enabled=false;
    but->Flat=true;
    but->Parent=this;
    but->OnClick=ButtonClick;
    but->ShowHint=true;
    Buttons[i]=but;
    }
Width=size*count;
Height=size;
}

void __fastcall TSignPanel::ButtonClick(TObject *Sender)
{
TSpeedButton *but=dynamic_cast<TSpeedButton*>(Sender);
if (but)
    if (MainForm->ActiveRoad)
        if (but->Tag<Codes->Count)
            {
            MainForm->ActiveRoad->AddNewSign(Codes->Strings[but->Tag],0);
            }

}


void __fastcall TSignPanel::DrawBitmap(TDictSource *Dict,Graphics::TBitmap *bmp,String Code)
{
TDrawManager *DrwMan=new TDrawManager;
DrwMan->Road=new TRoad(0,0);
DrwMan->Dict=Dict;
DrwMan->Shared=MainForm->Shared;
DrwMan->BaseScaleX=1000;
TDrawContents *DrwCont=new TDrawBitmap();
DrwCont->SetSize(bmp->Width,bmp->Height);
DrwCont->SetParam(0,1,0,0,1);
int pid=Dict->FindPropId(SIGNGOSTCODE+Code[1]-'1',Code);
int drwcls=Dict->SelectDrwParam(SGNCODE+Code[1]-'0',pid,1);
if (drwcls)
    {
    TDrwClassesRec *Cls=Dict->DrwClasses->Items[drwcls];
    if (Cls->DrwParamId[0]>0)
        {
        TDrwParamRec *Rec=Dict->DrwParams->Items[Cls->DrwParamId[0]];
        TDrwParamRec3 *Rec3=dynamic_cast<TDrwParamRec3*>(Rec);
        if (Rec3)
            {
            TRect MRect;
            TExtPolyline Poly(1,1);
            Poly[0].x=bmp->Width>>1;
            Poly[0].y=bmp->Height>>1;
            DrwCont->PrepareUpdating();
            int dpi=MainForm->PixelsPerInch;
            int sclX=(1000*Rec3->Width*dpi)/(254*(double)bmp->Width);
            DrwMan->CallDrawFunc(DrwCont,&Poly,Rec,&MRect,2000,sclX,pkGorizontal,pdDirect,MainForm->PixelsPerInch/2.54,true);
            DrwCont->FinishUpdating();
            DrwCont->DrawTo(bmp->Canvas,0,0);
            }
        }
    }
delete DrwCont;
delete DrwMan->Road;
DrwMan->Road=NULL;
delete DrwMan;
}

void __fastcall TSignPanel::AddButton(TDictSource *Dict,String SignCode)
{
int i;
for (i=0;i<Codes->Count;i++)
    if (Codes->Strings[i]==SignCode)
        break;
if (i>FCount-1)
    i=FCount-1;
if (i==FActCount)
    Buttons[FActCount++]->Enabled=true;
if (i<Codes->Count)
    Codes->Delete(i);
Codes->Insert(0,SignCode);
for (;i>0;i--)
    {
    Buttons[i]->Glyph=Buttons[i-1]->Glyph;
    Buttons[i]->Hint=Buttons[i-1]->Hint;
//    Codes[i]=Codes[i-1];

    }
Graphics::TBitmap *Glyph=new Graphics::TBitmap();
//Codes[0]=SignCode;
Glyph->Width=FSize-1;
Glyph->Height=FSize-1;
DrawBitmap(Dict,Glyph,SignCode);
Buttons[0]->Glyph=Glyph;
delete Glyph;
Buttons[0]->Hint=SignCode+String("(")+Dict->GetTitle(Dict->FindPropId(SIGNGOSTCODE+SignCode[1]-'1',SignCode))+String(")");
}

