//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AcadExportThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall AcadExport::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall AcadExportThread::AcadExportThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------



struct wpsign {
   double x,y;
   TExtPolyline *p;
   TRoadSign *s;
   wpsign(TRoadSign *_s,TExtPolyline *_p) {
      s=_s;p=_p;
      x=p->Points[0].x;
      y=p->Points[0].y;
   }
};

struct wpbar {
   TRoadBarrier *b;
   TRoadSignal *s;
   TSquareRoadSideObject_Kromka *w;
   TRoadLighting *l;
   TLinearRoadSideObject *a;
   bool exist;
   wpbar(TRoadBarrier *_b,bool e) {
      b=_b;exist=e;s=0;w=0;l=0;a=0;
   }
   wpbar(TRoadSignal *_s,bool e) {
      b=0;exist=e;s=_s;w=0;l=0;a=0;
   }
   wpbar(TSquareRoadSideObject_Kromka *_w,bool e) {
      b=0;exist=e;s=0;w=_w;l=0;a=0;
   }
   wpbar(TRoadLighting *_l,bool e) {
      b=0;exist=e;s=0;w=0;l=_l;a=0;
   }
   wpbar(TLinearRoadSideObject *_a,bool e) {
      b=0;exist=e;s=0;w=0;l=0,a=_a;
   }
};

#define SSCOUNT 10
const char SingleSign[SSCOUNT][5]={"1.34","5.23","5.24","5.25","5.26","6.9.","6.10","6.11","6.12","6.13"};
const int SignPrior[8]={2,1,5,3,4,6,7,8};

bool signgroup(const wpsign &s1,const wpsign &s2) {
   if (abs((float)(s2.x-s1.x))<=50 && abs((float)(s2.y-s1.y))<=50) {
      string a=s1.s->OldTitle.SubString(0,4).c_str();
      string b=s2.s->OldTitle.SubString(0,4).c_str();
      bool single=false;
      for (int i=0;i<SSCOUNT && !single;i++)
        single=(a==SingleSign[i]);
      for (int i=0;i<SSCOUNT && !single;i++)
        single=(b==SingleSign[i]);
      return !single;
   }
   return false;
}

bool operator<(const wpsign &s1,const wpsign &s2) {
   if (s2.x-s1.x>50) // первый знак раньше более чем на 50 см
      return true;
   else if (s1.x-s2.x<50) {// расстояние по x меньше 50 см
      if (s2.y-s1.y>50) // первый знак по y раньше более 50 см
         return true;
      else {            // знаки в одной точке
            string a=s1.s->OldTitle.SubString(0,4).c_str();
            string b=s2.s->OldTitle.SubString(0,4).c_str();
            char da=a[0]-'1';
            char db=b[0]-'1';
            bool single=false;
            for (int i=0;i<SSCOUNT && !single;i++)
               single=(a==SingleSign[i]);
            for (int i=0;i<SSCOUNT && !single;i++)
               single=(b==SingleSign[i]);
            if (single)
               return (s1.x<s2.x || s1.x==s2.x && s1.y<s2.y);
            else if (da<8 && db<8 && da>=0 && db>=0)
               return SignPrior[da]<SignPrior[db] ||
                  SignPrior[da]==SignPrior[db] && s1.s->OldTitle<s2.s->OldTitle;
          }
      }
   return false;
}


bool operator<(const wpbar &s1,const wpbar &s2) {
   return false;
}

void __fastcall AcadExportThread::setProgressFormCaption()
{
     ProgressForm->Note = ProgressFormCaption;
}

void __fastcall AcadExportThread::setProgressFormPosition()
{
     ProgressForm->Position = ProgressFormPosition;
}

void __fastcall AcadExportThread::setProgressFormMinMax()
{
     ProgressForm->SetMinMax(ProgressFormMin, ProgressFormMax);
}

void __fastcall AcadExportThread::addProgressFormLogLine()
{
     ProgressForm->addLogLine(ProgressFormLogLine);
}


#define SET_PROGRESS_FORM_CAPTION(caption) ProgressFormCaption = caption; ProgressFormLogLine = caption; Synchronize(setProgressFormCaption); Synchronize(addProgressFormLogLine);
#define SET_PROGRESS_FORM_POSITION(position) ProgressFormPosition = position; Synchronize(setProgressFormPosition);
#define SET_PROGRESS_FORM_MINMAX(min, max) ProgressFormMin = min; ProgressFormMax = max; Synchronize(setProgressFormMinMax);
#define ADD_PROGRESS_FORM_LINE(line) ProgressFormLogLine = line; Synchronize(addProgressFormLogLine);


void AcadExportThread::OutInfoLog(AnsiString &str)
{
   SET_PROGRESS_FORM_CAPTION(str);
}


void __fastcall AcadExportThread::Execute()
{
    if(!MetricData) return;

    aexp=new TAcadExport();
    aexp->RoadName = RoadName;
    int L1=MetricData->Road->LMin;
    int L2=MetricData->Road->LMax;
    int DX=1200;
    bool fDeleteLayerObjects = false;

    R=new TRoad(MetricData->Road,L1,L2);
    R->SetBound(L1,L2,-DX,DX);
    R->SetFrame(L1,L2,-DX,DX,pkGorizontal,pdDirect);
    R->SetOutBound(L1,L2,-DX,DX);

    aexp->OutInfoLog = OutInfoLog;

    if(aexp->BeginDocument(R)) {
      ProgressForm->Caption = "Идет экспорт в AutoCAD";
      SET_PROGRESS_FORM_CAPTION("Пробую подключиться к AutoCAD, десу")
      SET_PROGRESS_FORM_POSITION(0);
      ProgressForm->ShowLog = true;
      ProgressForm->clearLog();
      ProgressForm->Thread = this;
      ProgressForm->Show();



      try{
          TDtaSource *CurData=(TDtaSource*)FAutoCADExport->cbCurList->Items->Objects[FAutoCADExport->cbCurList->ItemIndex];
          TDtaSource *PrjData=(TDtaSource*)FAutoCADExport->cbPrjList->Items->Objects[FAutoCADExport->cbPrjList->ItemIndex];
          TDtaSource *DataPrj = PrjData==0?CurData:PrjData; // для обектов выводимых приоритено из проектного источника
          TDtaSource *DataCur = CurData==0?PrjData:CurData; // для обектов выводимых приоритено из текущего источника
          switch(FAutoCADExport->ExportTo){
             case 0:
                   ADD_PROGRESS_FORM_LINE("Подключение к активному документу");
                   if(!aexp->BindActiveDocument()){
                      return;
                   }
             break;
             case 1:
                   ADD_PROGRESS_FORM_LINE("Создание нового документа");
                   if(!aexp->OpenDocument(FAutoCADExport->FileName)){
                      return;
                   }
             break;
             default:
                  return;
          }


          /* -- Подсчет разметки от осевой -- */
           int iLeftMax = 0, iRightMax = 0;
           int iMarksLinesTop = FAutoCADExport->TableRowLinesTop;

           int iMarksLinesBottom = FAutoCADExport->TableRowLinesBottom;
           aexp->iMarkLinesBottom = aexp->iMarkLinesTop = 0;

           
           if(DataPrj&&(!FAutoCADExport->TableRowLinesBottom||!FAutoCADExport->TableRowLinesTop)){

             SET_PROGRESS_FORM_MINMAX(0,DataPrj->Objects->Count-1);
             SET_PROGRESS_FORM_CAPTION("Считаем разметку...")
             SET_PROGRESS_FORM_POSITION(0);
             for (int i=0;i<DataPrj->Objects->Count;i++) {
                if(Terminated) return;
                if (DataPrj->Objects->Items[i]->DictId==ROADMARKCODE) {
                   SET_PROGRESS_FORM_POSITION(i);
                   TRoadMark *t=dynamic_cast<TRoadMark*>(DataPrj->Objects->Items[i]);
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
                            float t1;
                            TRoadObject *tobj=MetricData->FindRoadPart(ROADCATEGORY,(t->LMin+t->LMax)/2);
                            TRoadCategory *tcat=dynamic_cast<TRoadCategory*>(tobj);
                            if (tcat) {
                               if (tcat->Value==rc1a || tcat->Value==rc1 || tcat->Value==rc1b || tcat->Value==rc2 || tcat->Value==rc3)
                                  defwidth=350;
                               else if (tcat->Value==rc5)
                                  defwidth=250;
                             }
                             midx/=(2*dl);
                             if (abs(minx)<50 && abs(maxx)<50)  {
                                line=0;
                             } else {
                               if (midx-minx<50 || maxx-midx<50)
                                  line=RoundTo((float)(midx+(midx>0 ? defwidth/2:-defwidth/2))/defwidth-(Sign(midx)*0.1),0);
                               }
                             }
                      }
                      if(line<0) {
                        if(iLeftMax<-line && line>-10) {
                           iLeftMax = -line;
                        }
                      } else if(line > 0&& line<10) {
                        if(iRightMax<line) {
                           iRightMax = line;
                        }
                      }
                      delete p;
                   }
                }
             }
             FAutoCADExport->TableRowLinesBottom = iRightMax;
             FAutoCADExport->TableRowLinesTop = iLeftMax;
           }
          /* -- */

          aexp->ExportTables(FAutoCADExport);  /*инициализация настроек таблицы*/



          /* -- вернем значени для разметки обратно -- */
          FAutoCADExport->TableRowLinesTop = iMarksLinesTop;
          FAutoCADExport->TableRowLinesBottom = iMarksLinesBottom;
          /* -- */

          if(FAutoCADExport->ExportGridStep) {
              aexp->AddLayer("Grid");
              aexp->DrawGrid(FAutoCADExport->GridStep);
          }

          if(FAutoCADExport->ExportRuler) {
                aexp->AddLayer("Ruler");
                aexp->ExportRuler(L1, L2, false);
          }

         if(DataCur) {
           SET_PROGRESS_FORM_MINMAX(0,DataCur->Objects->Count-1);

           if (FAutoCADExport->ExportTown) {
             SET_PROGRESS_FORM_CAPTION("Выводим населенные пункты...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadTown");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==TOWNCODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TTown *t=dynamic_cast<TTown*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportTown(p, t);
                      delete p;
                   }
                }
             }
           }

           if (FAutoCADExport->ExportPlan) {
             SET_PROGRESS_FORM_CAPTION("Выводим план...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadPlan");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==ROADPLANCODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(DataCur->Objects->Items[i]);
                   int kind=t->GetPropValue("Kind").ToInt();;
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportPlan(p,t,kind);
                      delete p;
                   }
                }
             }
             aexp->ExportPlan(0,0,0,true);
           }

           if (FAutoCADExport->ExportSurface) {
             SET_PROGRESS_FORM_CAPTION("Выводим участки по покрытиям...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadSurface");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==ROADSURFACECODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TRoadPart *t=dynamic_cast<TRoadPart*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportRoadCover(p, t);
                      delete p;
                   }
                }
             }
             aexp->ExportRoadCover(0,0,true);
           }
         }

          if (MetricData) {
             SET_PROGRESS_FORM_MINMAX(0,MetricData->Objects->Count-1);
             if(FAutoCADExport->ExportRoadMetrics){
               SET_PROGRESS_FORM_CAPTION("Выводим метрику дороги...")
               SET_PROGRESS_FORM_POSITION(0);
               aexp->AddLayer("RoadMetrics");

               if(Terminated) return;
               
               for (int i=0;i<MetricData->Objects->Count;i++) {
                  if (MetricData->Objects->Items[i]->DictId==ROADMETRIC) {
                     SET_PROGRESS_FORM_POSITION(i);
                     TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(MetricData->Objects->Items[i]);
                     if (t) {
                        TExtPolyline *p=t->PrepareMetric(R);
                        aexp->ExportRoadMetric(p,t->MetricsKind);
                        delete p;
                     }
                  }
               }
               aexp->ExportRoadMetric(0,0,true);
             }

             if (FAutoCADExport->ExportProfile) { // Выводим профиль
               SET_PROGRESS_FORM_CAPTION("Выводим профиль дороги...")
               SET_PROGRESS_FORM_POSITION(0);
               aexp->AddLayer("RoadProfile");
               TRect PrRect=TRect(L1,0,L2,-aexp->profileHeight); // Миша, вместо 100 поставь любое другое значение
                                                // Это условная высота бокса
               TExtPolyline *p=R->GetProfilMetric(PrRect);
               aexp->ExportProfil(p);
               delete p;
             }
             if(FAutoCADExport->ExportAttachments){
               SET_PROGRESS_FORM_CAPTION("Выводим примыкания...")
               SET_PROGRESS_FORM_POSITION(0);
               aexp->AddLayer("RoadAttachments");

               for (int i=0;i<MetricData->Objects->Count;i++) {
                  if(Terminated) return;
                  if (MetricData->Objects->Items[i]->DictId==ROADATTACH) {
                     SET_PROGRESS_FORM_POSITION(i);
                     TRoadAttach *t=dynamic_cast<TRoadAttach*>(MetricData->Objects->Items[i]);
                     if (t) {
                        TExtPolyline *p=t->PrepareMetric(R);
                        aexp->ExportAttach(p,t);
                        delete p;
                     }
                  }
               }
               aexp->ExportAttach(0,0,true);
             }

             if(FAutoCADExport->ExportRoadSideObjects){
               SET_PROGRESS_FORM_CAPTION("Выводим площадки отдыха...")
               SET_PROGRESS_FORM_POSITION(0);
               aexp->AddLayer("RoadSideObjects");

               for (int i=0;i<MetricData->Objects->Count;i++) {
                  if(Terminated) return;
                  SET_PROGRESS_FORM_POSITION(i);
                  if (MetricData->Objects->Items[i]->DictId==RESTZONECODE){
                     TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(MetricData->Objects->Items[i]);
                     if (t) {
                        TExtPolyline *p=t->PrepareMetric(R);
                        aexp->ExportRestZone(p,t);
                        delete p;
                     }
                  }
               }
               aexp->ExportRestZone(0,0,true);
             }
          }
         if ((CurData||PrjData) && MetricData) {
           if(FAutoCADExport->ExportRoadSigns){
             SET_PROGRESS_FORM_CAPTION("Выводим дорожные знаки...")
             SET_PROGRESS_FORM_POSITION(0);
             aexp->AddLayer("RoadSigns");

             std::vector<wpsign> A;
             
             /*Знаки, по умолчанию выводим только проектируемые знаки*/ 
             if(DataPrj) {
               for (int i=0;i<DataPrj->Objects->Count;i++) {
                  if(Terminated) return;
                  if (DataPrj->Objects->Items[i]->DictId>=SGNCODE && DataPrj->Objects->Items[i]->DictId<SGNCODE+10) {
                     TRoadSign *t=dynamic_cast<TRoadSign*>(DataPrj->Objects->Items[i]);
                     if (t) {
                        TExtPolyline *p=t->PrepareMetric(R);
                        A.push_back(wpsign(t,p));
                     }
                  }
               }
             }

             sort(A.begin(),A.end());
             vector<TRoadSign*> sgrp;
             SET_PROGRESS_FORM_MINMAX(0,A.size());
             for (vector<wpsign>::iterator i=A.begin();i!=A.end();) {
                if(Terminated){
                   for (vector<wpsign>::iterator j=A.begin();j!=A.end();j++)
                     delete j->p;
                   return;
                }
                sgrp.clear();
                sgrp.push_back(i->s);
                vector<wpsign>::iterator j;
                for (j=i+1;j!=A.end() && signgroup(*i,*j);j++)
                   sgrp.push_back(j->s);
                aexp->ExportSigns(i->p,sgrp.begin(),sgrp.size());
                i=j;
                SET_PROGRESS_FORM_POSITION(i-A.begin());
             }
             for (vector<wpsign>::iterator i=A.begin();i!=A.end();i++)
                delete i->p;
             aexp->ExportSigns(0,0,0,true);
           }

           // разметку приоритетно выводим из проектируемого источника
           if(DataPrj) {
             if(FAutoCADExport->ExportMark){
               SET_PROGRESS_FORM_MINMAX(0,DataPrj->Objects->Count-1);
               SET_PROGRESS_FORM_CAPTION("Выводим разметку...")
               SET_PROGRESS_FORM_POSITION(0);
               aexp->AddLayer("RoadMark");
               for (int i=0;i<DataPrj->Objects->Count;i++) {
                  if(Terminated) return;
                  if (DataPrj->Objects->Items[i]->DictId==ROADMARKCODE) {
                     SET_PROGRESS_FORM_POSITION(i);
                     TRoadMark *t=dynamic_cast<TRoadMark*>(DataPrj->Objects->Items[i]);
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
                              float t1;
                              TRoadObject *tobj=MetricData->FindRoadPart(ROADCATEGORY,(t->LMin+t->LMax)/2);
                              TRoadCategory *tcat=dynamic_cast<TRoadCategory*>(tobj);
                              if (tcat) {
                                 if (tcat->Value==rc1a || tcat->Value==rc1 || tcat->Value==rc1b || tcat->Value==rc2 || tcat->Value==rc3)
                                    defwidth=350;
                                 else if (tcat->Value==rc5)
                                    defwidth=250;
                               }
                               midx/=(2*dl);
                               if (abs(minx)<50 && abs(maxx)<50)  {
                                  line=0;
                               } else {
                                 if (midx-minx<50 || maxx-midx<50)
                                    line=RoundTo((float)(midx+(midx>0 ? defwidth/2:-defwidth/2))/defwidth-(Sign(midx)*0.1),0);
                                 }
                               }
                        }
                        aexp->ExportRoadMark(p,t,line,s);
                        delete p;
                     }
                  }
               }
               aexp->ExportRoadMark(0,0,0,0,true);
             }
           }

        /* Трубы, мосты ,автобусные остановки и высоты насыпей
           выводим приоритетно из существующих данных  */

        if (DataCur) {
           if (FAutoCADExport->ExportCommunications) {
             SET_PROGRESS_FORM_CAPTION("Выводим коммуникации...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadCommunication");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==COMMUNICATIONCODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TCommunication *t=dynamic_cast<TCommunication*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportCommunication(p,t);
                      delete p;
                   }
                }
             }
           }
           if(FAutoCADExport->ExportTubes){
             SET_PROGRESS_FORM_CAPTION("Выводим трубы...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadTubes");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==ROADTUBECODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TRoadTube *t=dynamic_cast<TRoadTube*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportTube(p,t);
                      delete p;
                   }
                }
             }
             aexp->ExportTube(0,0,true);
           }
           if(FAutoCADExport->ExportBridges){
             SET_PROGRESS_FORM_CAPTION("Выводим мосты...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadBridges");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==ROADBRIDGECODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TRoadBridge *t=dynamic_cast<TRoadBridge*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportBridge(p,t);
                      delete p;
                   }
                }
             }
             aexp->ExportBridge(0,0,true);
           }
           if(FAutoCADExport->ExportBusstops){
             SET_PROGRESS_FORM_CAPTION("Выводим автобусные остановки...")
             SET_PROGRESS_FORM_POSITION(0;)
             aexp->AddLayer("RoadBusStops");
             for (int i=0;i<DataCur->Objects->Count;i++) {
                if(Terminated) return;
                if (DataCur->Objects->Items[i]->DictId==BUSSTOPCODE) {
                   SET_PROGRESS_FORM_POSITION(i;)
                   TBusStop *t=dynamic_cast<TBusStop*>(DataCur->Objects->Items[i]);
                   if (t) {
                      TExtPolyline *p=t->PrepareMetric(R);
                      aexp->ExportBusStop(p,t);
                      delete p;
                   }
                }
             }
             aexp->ExportBusStop(0,0,true);
           }
           if (FAutoCADExport->ExportMoundHeights) {
               SET_PROGRESS_FORM_CAPTION("Выводим высоты насыпей...")
               SET_PROGRESS_FORM_POSITION(0;)
               aexp->AddLayer("RoadMoundHeights");

               for(int fase =0;fase <2;fase++){
                 for (int i=0;i<DataCur->Objects->Count;i++) {
                     if(Terminated) return;
                     if (DataCur->Objects->Items[i]->DictId==MOUNDHEIGHTCODE) {
                        if(fase) SET_PROGRESS_FORM_POSITION(i);
                        TMoundHeight *m=dynamic_cast<TMoundHeight*>(DataCur->Objects->Items[i]);
                        if (m) {
                           aexp->ExportMoundHeight(m,fase);
                        }
                     }
                 }
               }
               aexp->ExportMoundHeight(0,0,true);
           }
          }

           // Выводим ограждения, сигнальные устройства, тротуары, бордюры
           vector<pair<int,wpbar> > bvec;
           if(FAutoCADExport->ExportSignal || FAutoCADExport->ExportSidewalks ||
              FAutoCADExport->ExportLamps || FAutoCADExport->ExportBorders){

             //ограждения берем из обоих источников
             if (PrjData) {
                SET_PROGRESS_FORM_MINMAX(0,PrjData->Objects->Count-1);
                SET_PROGRESS_FORM_CAPTION("Ищем проектируемые ограждения,сигнальные устройства, тротуары, освещение...")
                SET_PROGRESS_FORM_POSITION(0)
                for (int i=0;i<PrjData->Objects->Count;i++) {
                   SET_PROGRESS_FORM_POSITION(i)
                   if (FAutoCADExport->ExportSignal && PrjData->Objects->Items[i]->DictId==ROADSIGNALCODE) {
                      TRoadSignal *t=dynamic_cast<TRoadSignal*>(PrjData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
                   }else if (FAutoCADExport->ExportSignal && PrjData->Objects->Items[i]->DictId==ROADBARRIERCODE) {
                      TRoadBarrier *t=dynamic_cast<TRoadBarrier*>(PrjData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
                   } else if (FAutoCADExport->ExportSidewalks && PrjData->Objects->Items[i]->DictId==SIDEWALKCODE) {
                      TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(PrjData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
                   } else if (FAutoCADExport->ExportLamps && PrjData->Objects->Items[i]->DictId==ROADLAMPCODE) {
                      TRoadLighting *t=dynamic_cast<TRoadLighting*>(PrjData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
                   } else if (FAutoCADExport->ExportBorders && PrjData->Objects->Items[i]->DictId==ROADBORDERCODE) {
                      TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(PrjData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
                   }
                }
             }
             // только для столбиков требуется в настройках поставить дополнительную галочку
             // для вывода существующих столбиков
             if (CurData && CurData!=PrjData) {
                SET_PROGRESS_FORM_CAPTION("Ищем существующие ограждения тротуары и столбы освещения")
                SET_PROGRESS_FORM_MINMAX(0,CurData->Objects->Count-1);
                SET_PROGRESS_FORM_POSITION(0)
                // столбики из существующего выводим всегда если не указан проектируемый источник,
                // иначе только если стоит галочка в настройках
                bool fIncludeSignalExist = PrjData!=0?FAutoCADExport->ExportSignalExistToo:true;
                for (int i=0;i<CurData->Objects->Count;i++) {
                    SET_PROGRESS_FORM_POSITION(i)
                    if(Terminated) return;
                    if (fIncludeSignalExist&&FAutoCADExport->ExportSignal && CurData->Objects->Items[i]->DictId==ROADSIGNALCODE) {
                      TRoadSignal *t=dynamic_cast<TRoadSignal*>(CurData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
                    }else if (CurData->Objects->Items[i]->DictId==ROADBARRIERCODE) {
                      TRoadBarrier *t=dynamic_cast<TRoadBarrier*>(CurData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
                    } else if (FAutoCADExport->ExportSidewalks && CurData->Objects->Items[i]->DictId==SIDEWALKCODE) {
                      TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(CurData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
                   }  else if (FAutoCADExport->ExportLamps && CurData->Objects->Items[i]->DictId==ROADLAMPCODE) {
                      TRoadLighting *t=dynamic_cast<TRoadLighting*>(CurData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
                   } else if (FAutoCADExport->ExportBorders && CurData->Objects->Items[i]->DictId==ROADBORDERCODE) {
                      TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(CurData->Objects->Items[i]);
                      if (t)
                         bvec.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
                   }
                }
             }
             if (bvec.size()) {
                sort(bvec.begin(),bvec.end());

                SET_PROGRESS_FORM_MINMAX(0,bvec.size()-1);

                if(FAutoCADExport->ExportSignal){
                  SET_PROGRESS_FORM_POSITION(0)
                  SET_PROGRESS_FORM_CAPTION("Выводим ограждения и сигнальные устройства...")
                  aexp->AddLayer("RoadSignals");
                  for (vector<pair<int,wpbar> >::iterator i=bvec.begin();i!=bvec.end();i++) {
                      if(Terminated) return;
                      SET_PROGRESS_FORM_POSITION((ProgressFormPosition+1));
                      if (i->second.s) {
                           TExtPolyline *p=i->second.s->PrepareMetric(R);
                           aexp->ExportSignal(p,i->second.s,i->second.exist);
                           delete p;
                      } else if (i->second.b) {
                           TExtPolyline *p=i->second.b->PrepareMetric(R);
                           aexp->ExportBarrier(p,i->second.b,i->second.exist);
                           delete p;
                      }
                  }
                  aexp->ExportBarrier(0,0,0,true);
                }

                if(FAutoCADExport->ExportSidewalks){
                  SET_PROGRESS_FORM_POSITION(0;)
                  SET_PROGRESS_FORM_CAPTION("Выводим тротуары...")
                  aexp->AddLayer("Sidewalks");
                  for (vector<pair<int,wpbar> >::iterator i=bvec.begin();i!=bvec.end();i++) {
                      if(Terminated) return;
                      SET_PROGRESS_FORM_POSITION((ProgressFormPosition+1));
                      if (i->second.w) {
                           TExtPolyline *p=i->second.w->PrepareMetric(R);
                           aexp->ExportSidewalk(p,i->second.w,i->second.exist);
                           delete p;
                      }
                  }
                  aexp->ExportSidewalk(0,0,0,true);
                }

                if(FAutoCADExport->ExportLamps){
                  SET_PROGRESS_FORM_POSITION(0;)
                  SET_PROGRESS_FORM_CAPTION("Выводим фонари...")
                  aexp->AddLayer("Lights");
                  for (vector<pair<int,wpbar> >::iterator i=bvec.begin();i!=bvec.end();i++) {
                      if(Terminated) return;
                      SET_PROGRESS_FORM_POSITION((ProgressFormPosition+1));
                      if (i->second.l) {
                           TExtPolyline *p=i->second.l->PrepareMetric(R);
                           aexp->ExportLighting(p,i->second.l,i->second.exist);
                           delete p;
                      }
                  }
                  aexp->ExportLighting(0,0,0,true);
                }
                if(FAutoCADExport->ExportBorders){
                  SET_PROGRESS_FORM_POSITION(0;)
                  SET_PROGRESS_FORM_CAPTION("Выводим бордюры...")
                  aexp->AddLayer("Borders");
                  for (vector<pair<int,wpbar> >::iterator i=bvec.begin();i!=bvec.end();i++) {
                      if(Terminated) return;
                      SET_PROGRESS_FORM_POSITION((ProgressFormPosition+1));
                      if (i->second.a) {
                           TExtPolyline *p=i->second.a->PrepareMetric(R);
                           aexp->ExportBorder(p,i->second.a,i->second.exist);
                           delete p;
                      }
                  }
                  aexp->ExportBorder(0,0,0,true);
                }
              }
             }
           }

        /* Участки уклонов выводим из слоя с профилем */

        if (ProfilData) {
           if(FAutoCADExport->ExportSlope){
             SET_PROGRESS_FORM_MINMAX(0,ProfilData->Objects->Count-1);
             // Выводим опасные участки
             SET_PROGRESS_FORM_POSITION(0)
             SET_PROGRESS_FORM_CAPTION("Выводим участки уклонов ...")
             aexp->AddLayer("RoadSlopes");
             for (int i=0;i<ProfilData->Objects->Count;i++) {
                if(Terminated) return;
                SET_PROGRESS_FORM_POSITION(i)
                if (ProfilData->Objects->Items[i]->DictId==DANGERSLOPECODE) {
                   TDangerSlope *t=dynamic_cast<TDangerSlope*>(ProfilData->Objects->Items[i]);
                   if (t) {
                      aexp->ExportSlope(t);
                   }
                }
             }
             aexp->ExportSlope(0,0,true);
           }

        }
        /* Схематический план выводим из слоя с планом */

        if (CurveData) {
           if(FAutoCADExport->ExportCurves){
             SET_PROGRESS_FORM_MINMAX(0,CurveData->Objects->Count-1);
             // Выводим опасные участки
             SET_PROGRESS_FORM_CAPTION("Выводим участки кривых ...")
             SET_PROGRESS_FORM_POSITION(0)
             aexp->AddLayer("RoadCurves");
             for (int i=0;i<CurveData->Objects->Count;i++) {
                if(Terminated) return;
                SET_PROGRESS_FORM_POSITION(i)
                if (CurveData->Objects->Items[i]->DictId==DANGERCURVECODE) {
                   TDangerCurve *t=dynamic_cast<TDangerCurve*>(CurveData->Objects->Items[i]);
                   if (t) {
                      aexp->ExportCurve(t);
                   }
                }
             }
             aexp->ExportCurve(0,true);
           }

        }

        if(true){
          SET_PROGRESS_FORM_CAPTION("выводим дополнительные строки из файлов в верхнюю таблицу")
          aexp->ExportTopAddRows(FAutoCADExport->EditTopAddRows); 
        }

        if(true){
          SET_PROGRESS_FORM_CAPTION("выводим дополнительные строки из файлов в нижнюю таблицу")
          aexp->ExportBottomAddRows(FAutoCADExport->EditTopAddRows);
        }

        if(FAutoCADExport->ExportGraphic){
          SET_PROGRESS_FORM_CAPTION("выводим дополнительные строки графика")
          aexp->ExportGraphic(FAutoCADExport->EditTopAddRows,false); 
        }

        if(FAutoCADExport->ExportTable){
             aexp->AddLayer("Table");
             aexp->DrawTables(FAutoCADExport->ExportRuler);
        }

        SET_PROGRESS_FORM_CAPTION("Завершение процесса...");
      } __finally {
          ProgressForm->Hide();
          aexp->EndDocument();
          FlashWindow(Application->Handle, true);
          delete aexp;
          delete R;
          return;
      }
    }else {
        ShowMessage("Невозможно начать работу с AutoCad");
    }
    delete aexp;
    delete R;
    //Synchronize(Clear);
}
//---------------------------------------------------------------------------
