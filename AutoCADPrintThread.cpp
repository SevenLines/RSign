//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AutoCADPrintThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall AutoCadPrintThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------


void __fastcall AutoCadPrintThread::setProgressFormCaption()
{
     ProgressForm->Note = ProgressFormCaption;
}

void __fastcall AutoCadPrintThread::setProgressFormPosition()
{
     ProgressForm->Position = ProgressFormPosition;
}

void __fastcall AutoCadPrintThread::setProgressFormMinMax()
{
     ProgressForm->SetMinMax(ProgressFormMin, ProgressFormMax);
}

#define SET_PROGRESS_FORM_CAPTION2(caption) ProgressFormCaption = caption; Synchronize(setProgressFormCaption);
#define SET_PROGRESS_FORM_POSITION2(position) ProgressFormPosition = position; Synchronize(setProgressFormPosition);
#define SET_PROGRESS_FORM_MINMAX2(min, max) ProgressFormMin = min; ProgressFormMax = max; Synchronize(setProgressFormMinMax);


bool AutoCadPrintThread::BindViewports()
{
  bool ffirst = true;
  AcadEntityPtr e;
  vpTop.Unbind();
  vpCenter.Unbind();
  vpBottom.Unbind();
  text.Unbind();
  page.Unbind();

  if(!helper.ActiveDocument) return false;
  helper.ActiveDocument->Activate();

     
  int cur = 0;
  int count = helper.ActiveDocument->PaperSpace->Count;
  for(int i=0;i<count;i++){
      e = helper.ActiveDocument->PaperSpace->Item(Variant(i));
      if(e->EntityType == acPViewport){
         if(ffirst){
           ffirst = false;
           continue;
         }
         if(cur==iTop){
           vpTop = e;
         }
         if(cur==iCenter){
           vpCenter = e;
         }
         if(cur==iBottom){
           vpBottom = e;                                                                  
         }
         cur++;
      }else if(finfo&&e->EntityType==acText){
         if(!wcscmp(e->Layer,L"@info")){
           text = e;
         }
         if(!wcscmp(e->Layer,L"@page")){
           page = e;
         }
      }
   }
   return true;
}

void __fastcall AutoCadPrintThread::ShowModalPF()
{
}

__fastcall AutoCadPrintThread::AutoCadPrintThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall AutoCadPrintThread::Execute()
{
}
//---------------------------------------------------------------------------
