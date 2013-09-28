//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AutoCADExportThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall AutoCADExport::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

void __fastcall AutoCADExportThread::UpdateProgress()
{
   frmProgress->Position = pos;
}

void __fastcall AutoCADExportThread::UpdateCaption()
{
   frmProgress->Note = Note;
}

void __fastcall AutoCADExportThread::UpdateMinMax()
{
   frmProgress->SetMinMax(min,max);
}

__fastcall AutoCADExportThread::AutoCADExportThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall AutoCADExportThread::Execute()
{
   //if(FAutoCADExport->ExportMark){
     Note = "Выводим разметку...";
     Synchronize(UpdateCaption);
     pos = 0;
     Synchronize(UpdateProgress);
     for (int i=0;i<MetricData->Objects->Count;i++) {
        pos = 0;
        Synchronize(UpdateProgress);
        if (MetricData->Objects->Items[i]->DictId==ROADMARKCODE) {
           TRoadMark *t=dynamic_cast<TRoadMark*>(MetricData->Objects->Items[i]);
           if (t) {
              TExtPolyline *p=t->PrepareMetric(R);
              TPlanLabel *l=t->GetText(0,R,Dict);
              String s=l->Caption.c_str();
              delete l;
              int line=100;
              char *ps=s.c_str();
              int code=0;
              for (;*ps!='.' && *ps;ps++) {}
              if (*ps)
                 ps++;
              for (;*ps!='.' && *ps;ps++)
                 code=code*10+*ps-'0';
              if (code>0 && code<=11 && p->Count>1) {
                 int minx=p->Points[0].y;
                 int maxx=p->Points[0].y;
                 long long midx=0;
                 long long dl=0;
                 for (int i=1;i<p->Count;i++) {
                    if (minx>p->Points[i].y)
                       minx=p->Points[i].y;
                    if (maxx<p->Points[i].y)
                       maxx=p->Points[i].y;
                    midx+=(p->Points[i].y+p->Points[i-1].y)*abs(p->Points[i].x-p->Points[i-1].x);
                    dl+=abs(p->Points[i].x-p->Points[i-1].x);
                 }
                 if (dl>100) {
                    int defwidth=300;
                    TRoadObject *tobj=MetricData->FindRoadPart(ROADCATEGORY,(t->LMin+t->LMax)/2);
                    TRoadCategory *tcat=dynamic_cast<TRoadCategory*>(tobj);
                    if (tcat) {
                       if (tcat->Value==rc1a || tcat->Value==rc1 || tcat->Value==rc1b || tcat->Value==rc2 || tcat->Value==rc3)
                          defwidth=350;
                       else if (tcat->Value==rc5)
                          defwidth=250;
                     }
                     midx/=(2*dl);
                     if (abs(minx)<50 && abs(maxx)<50)
                        line=0;
                     if (midx-minx<50 || maxx-midx<50)
                        line=(midx+(midx>0 ? defwidth/2:-defwidth/2))/defwidth;
                     }
              }
              aexp->ExportRoadMark(p,t,line,s);
              delete p;
           }
        }
     }
   //}
}
//---------------------------------------------------------------------------
