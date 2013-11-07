//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowSigns.h"
#include "MainUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSignForm *SignForm;

const int MsArray[8]={800,400,200,100,75,50,25,10};
//---------------------------------------------------------------------------
__fastcall TSignForm::TSignForm(TComponent* Owner)
    : TForm(Owner)
{
DoubleBuffered=true;
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::BuildPageList(void)
{
PageList->Items->Clear();
String Folder=Application->ExeName;
int Pos=Folder.LastDelimiter("\\");
if (Pos)
    {
    Folder.Delete(Pos+1,64);
    Folder=Folder+"VPatterns\\*.vps";
    TSearchRec sr;
    if (!FindFirst(Folder,faAnyFile,sr))
        {
        do
            {
            int p=sr.Name.LastDelimiter(".");
            PageList->Items->Add(sr.Name.SubString(1,p-1));
            }
        while (!FindNext(sr));
        FindClose(sr);
        }
    }
}
void __fastcall TSignForm::FormShow(TObject *Sender)
{
int index=PageList->ItemIndex;
BuildPageList();
if ((index<0)||(index>=PageList->Items->Count))
    index=0;
PageList->ItemIndex=index;
ChangeImage();
}
//---------------------------------------------------------------------------

TDrawPattern* __fastcall TSignForm::GetCurrentPat(void)
{
TDrawPattern *Res=NULL;
if (PageList->ItemIndex>=0)
    {
    String Folder=Application->ExeName;
    int Pos=Folder.LastDelimiter("\\");
    Folder.Delete(Pos+1,64);
    Folder+=String("VPatterns\\")+PageList->Text+String(".vps");
    Res=new TDrawPattern();
    Res->LoadFromFile(Folder);
    }
return Res;
}

void __fastcall TSignForm::DrawPat(TDrawPattern* Pat,TDrawContents *Cont,double K,int dx,int dy)
{
if (MainForm->ActiveRoad)
    {
    TDrawManager *DrwMan=new TDrawManager();
    DrwMan->BaseScaleL=4000;
    DrwMan->BaseScaleX=1000;
    DrwMan->Dict=MainForm->ActiveRoad->Dict;
    DrwMan->Shared=MainForm->ActiveRoad->Shared;
    DrwMan->Road=new TRoad(0,0);
    Cont->PrepareUpdating();
    SetBkMode(Cont->DC,TRANSPARENT);
    DrwMan->FillCont(Cont);
    Pat->DrawTo(DrwMan,Cont,K,dx,dy,pkVertical,pdDirect,FPageIndex);
    Cont->FinishUpdating();
    delete DrwMan->Road;
    DrwMan->Road=NULL;
    delete DrwMan;
    }
}

void __fastcall TSignForm::ChangeImage(void)
{
Image1->ControlStyle=Image1->ControlStyle>>csOpaque;
TDrawPattern *Pat=GetCurrentPat();
if (Pat)
    {
    int w,h;
    if (!Pat->GetPageSize(w,h))
        {
        w=297;
        h=210;
        }
    int ms=MsArray[MsList->ItemIndex];
    BCont->SetSize((double)w*PixelsPerInch*ms/2540,(double)h*PixelsPerInch*ms/2540);
    DrawPat(Pat,BCont,(double)PixelsPerInch*ms/25400,0,0);
    delete Pat;
    Image1->Picture->Bitmap->ReleaseHandle();
    Image1->Picture->Bitmap->Handle=BCont->Bitmap;
    Image1->ControlStyle=Image1->ControlStyle<<csOpaque;
    ScrollBox1->HorzScrollBar->Range=BCont->Width;
    ScrollBox1->VertScrollBar->Range=BCont->Height;
    ScrollBox1->HorzScrollBar->Position=0;
    ScrollBox1->VertScrollBar->Position=0;
    ScrollBox1->Realign();
    }
}

void __fastcall TSignForm::ImageToBmp(void)
{
int w,h;
TDrawPattern *Pat=GetCurrentPat();
if (Pat)
    if (Pat->GetPageSize(w,h))
        {
        int pdpi=300;
        TDrawBitmap *bitcont=new TDrawBitmap;
        bitcont->SetSize((double)(w*pdpi)/25.4,(double)(h*pdpi)/25.4);
        bitcont->SetParam(0,100000,-10000,10000);
        DrawPat(Pat,bitcont,(double)pdpi/254,0,0);
        Graphics::TBitmap *bmp=new Graphics::TBitmap;
        bmp->Handle=bitcont->Bitmap;
        bmp->SaveToFile("Signs.bmp");
        bmp->Handle=NULL;
        delete bmp;
        delete bitcont;
        delete Pat;
        }
}

void __fastcall TSignForm::PrintImage(void)
{
if (Printer()==NULL)
    return;
TDrawPattern *Pat=GetCurrentPat();
if (Pat)
    {
    if (Image1->Width>Image1->Height)
        Printer()->Orientation=poLandscape;
    else
        Printer()->Orientation=poPortrait;
    void *dc=Printer()->Handle;
    int pdpi=GetDeviceCaps(dc,LOGPIXELSX);
    int hofs=GetDeviceCaps(dc,PHYSICALOFFSETX);
    int vofs=GetDeviceCaps(dc,PHYSICALOFFSETY);
    TPrintContents *PCont=new TPrintContents;
    PCont->SetParam(0,100000,-10000,10000);
    DrawPat(Pat,PCont,(double)pdpi/254,-hofs,-vofs);
    delete PCont;
    delete Pat;
    }
}

void __fastcall TSignForm::FormCreate(TObject *Sender)
{
BCont=new TDrawBitmap;
BCont->SetParam(0,100000,-10000,10000);
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::FormDestroy(TObject *Sender)
{
delete BCont;
BCont=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::MsListChange(TObject *Sender)
{
ChangeImage();    
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::PageListChange(TObject *Sender)
{
ChangeImage();    
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::SpeedButton1Click(TObject *Sender)
{
PrintImage();
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::SpeedButton2Click(TObject *Sender)
{
ImageToBmp();
}
//---------------------------------------------------------------------------

