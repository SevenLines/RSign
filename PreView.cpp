//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PreView.h"
#include "PrnForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPreViewFrm *PreViewFrm;
const int MsArray[8]={800,400,200,100,75,50,25,10};
//---------------------------------------------------------------------------
__fastcall TPreViewFrm::TPreViewFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void _fastcall TPreViewFrm::SetPageList(int skm,int ekm,int pkm,int devkind)
{
FStartKm=skm;
FEndKm=ekm;
FKmPerPage=pkm;
FDeviceKind=devkind;
PageList->Items->BeginUpdate();
PageList->Items->Clear();
for (int i=skm;i<ekm;i+=pkm)
    {
    int t=i+pkm;
    if (t>ekm)
        t=ekm;
    PageList->Items->Add(String(i/1000)+"κμ-"+String(t/1000)+"κμ");
    }
PageList->Items->EndUpdate();
PageList->ItemIndex=0;
}

void __fastcall TPreViewFrm::MakeCurrentPage(void)
{
Image1->ControlStyle=Image1->ControlStyle>>csOpaque;
if (PageList->ItemIndex>=0)
    if (MainForm->ActiveRoad)
        {
        int a=FStartKm+(PageList->ItemIndex)*FKmPerPage;
        int lms=PrnParam->ScaleL->Text.ToInt();
        int xms=PrnParam->ScaleX->Text.ToInt();
        int page=PrnParam->StartPage->Position+PageList->ItemIndex;
        Image1->Picture->Bitmap->ReleaseHandle();
        if (FDeviceKind==0)
            MainForm->ActiveRoad->MakePreViewPage(BCont,a*100,(a+FKmPerPage)*100,lms,xms,MsArray[MsList->ItemIndex],page);
        else
            {
            int wdpi=GetDeviceCaps(Canvas->Handle,LOGPIXELSX);
            wdpi=(wdpi*MsArray[MsList->ItemIndex])/100;
            MainForm->ActiveRoad->MakeBmpPage(BCont,a*100,(a+FKmPerPage)*100,lms,xms,wdpi,page);
            }
        Image1->Picture->Bitmap->Handle=BCont->Bitmap;
        Image1->ControlStyle=Image1->ControlStyle<<csOpaque;
        ScrollBox1->HorzScrollBar->Range=BCont->Width;
        ScrollBox1->VertScrollBar->Range=BCont->Height;
        ScrollBox1->HorzScrollBar->Position=0;
        ScrollBox1->VertScrollBar->Position=0;
        ScrollBox1->Realign();
        }
}

void __fastcall TPreViewFrm::PageListChange(TObject *Sender)
{
MakeCurrentPage();
}
//---------------------------------------------------------------------------

void __fastcall TPreViewFrm::FormCreate(TObject *Sender)
{
DoubleBuffered=true;
BCont=new TDrawBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TPreViewFrm::FormDestroy(TObject *Sender)
{
delete BCont;
BCont=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TPreViewFrm::FormShow(TObject *Sender)
{
MakeCurrentPage();
}
//---------------------------------------------------------------------------

void __fastcall TPreViewFrm::SpeedButton1Click(TObject *Sender)
{
if (PageList->ItemIndex>=0)
    if (MainForm->ActiveRoad)
        {
        int a=FStartKm+(PageList->ItemIndex)*FKmPerPage;
        int lms=PrnParam->ScaleL->Text.ToInt();
        int xms=PrnParam->ScaleX->Text.ToInt();
        int page=PrnParam->StartPage->Position+PageList->ItemIndex;
        MainForm->ActiveRoad->Print(a*100,(a+FKmPerPage)*100,FKmPerPage*100,lms,xms,page);
        }
}
//---------------------------------------------------------------------------

