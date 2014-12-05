//---------------------------------------------------------------------------

#include <vcl.h>

#include "without_autocad.h"
#ifndef WITHOUT_AUTOCAD

#pragma hdrstop

#include "AcadExportThread.h"
#pragma package(smart_init)

#include "MickMacros.h"
#include "AcadExportObjects.h"
#include "AutoCADExportForm.h"
#include "DataSour.h"
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



#define SET_PROGRESS_FORM_CAPTION(caption) \
 ProgressFormCaption = caption;\
ProgressFormLogLine = caption;\
Synchronize(setProgressFormCaption);\
Synchronize(addProgressFormLogLine);


#define SET_PROGRESS_FORM_POSITION(position) ProgressFormPosition = position; Synchronize(setProgressFormPosition);
#define SET_PROGRESS_FORM_MINMAX(min, max) ProgressFormMin = min; ProgressFormMax = max; Synchronize(setProgressFormMinMax);
#define SET_PROGRESS_FORM_CAPTION_EX(caption) \
     SET_PROGRESS_FORM_CAPTION("[" + IntToStr(currentItem) +"/" +  IntToStr(countOfExportItems) + "] " + caption)

#define ADD_PROGRESS_FORM_LINE(line) \
     ProgressFormLogLine = line;    \
    Synchronize(addProgressFormLogLine);

void AcadExportThread::OutInfoLog(AnsiString str)
{
    SET_PROGRESS_FORM_CAPTION(str);
}


void AcadExportThread::ProgressChanged(int progress, AnsiString message)
{
    SET_PROGRESS_FORM_POSITION(progress);
}


int __fastcall AcadExportThread::ExportTowns(TDtaSource* data, TAcadExport* aexp)
{
      SET_PROGRESS_FORM_POSITION(0;)
      aexp->AddLayer("RoadTown");
      for (int i=0;i<data->Objects->Count;i++) {
          if (Terminated) return -1;
          if (data->Objects->Items[i]->DictId==TOWNCODE) {
              SET_PROGRESS_FORM_POSITION(i;)
              TTown *t=dynamic_cast<TTown*>(data->Objects->Items[i]);
              if (t) {
                  TExtPolyline *p=t->PrepareMetric(R);
                  aexp->ExportTown(p, t);
                  delete p;
              }
          }
      }
      return 0;
}

int __fastcall AcadExportThread::ExportPlan(TDtaSource* data, TAcadExport* aexp)
{
    SET_PROGRESS_FORM_POSITION(0;)
    aexp->AddLayer("RoadPlan");
    for (int i=0;i<data->Objects->Count;i++) {
        if (Terminated) return -1;
        if (data->Objects->Items[i]->DictId==ROADPLANCODE) {
            SET_PROGRESS_FORM_POSITION(i;)
            TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(data->Objects->Items[i]);
            int kind=t->GetPropValue("Kind").ToInt();;
            if (t) {
                TExtPolyline *p=t->PrepareMetric(R);
                aexp->ExportPlan(p,t,kind);
                delete p;
            }
        }
    }
    aexp->ExportPlan(0,0,0,true);
    return 0;
}

int __fastcall AcadExportThread::ExportSurface(TDtaSource* data, TAcadExport* aexp)
{
    SET_PROGRESS_FORM_POSITION(0;)
    aexp->AddLayer("RoadSurface");
    for (int i=0;i<data->Objects->Count;i++) {
        if (Terminated) return -1;
        if (data->Objects->Items[i]->DictId==ROADSURFACECODE) {
            SET_PROGRESS_FORM_POSITION(i;)
            TRoadPart *t=dynamic_cast<TRoadPart*>(data->Objects->Items[i]);
            if (t) {
                TExtPolyline *p=t->PrepareMetric(R);
                aexp->ExportRoadCover(p, t);
                delete p;
            }
        }
    }
    aexp->ExportRoadCover(0,0,true);
    return 0;
}


int __fastcall AcadExportThread::ExportRoadMetrics(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0);
	aexp->AddLayer("RoadMetrics");

	if (Terminated) return -1;

	for (int i=0;i<data->Objects->Count;i++) {
		if (data->Objects->Items[i]->DictId==ROADMETRIC) {
			SET_PROGRESS_FORM_POSITION(i);
            if (Terminated) return -1;            
			TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportRoadMetric(p,t->MetricsKind);
				delete p;
			}
		}
	}
	aexp->ExportRoadMetric(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportProfile(TDtaSource* metricData, TRoad* road, TAcadExport* aexp)
{
    SET_PROGRESS_FORM_POSITION(0);
    aexp->AddLayer("RoadProfile");
    TRect PrRect=TRect(metricData->Road->LMin,0,metricData->Road->LMax,-aexp->profileHeight); // Миша, вместо 100 поставь любое другое значение
    // Это условная высота бокса
    TExtPolyline *p = road->GetProfilMetric(PrRect);
    aexp->ExportProfil(p);
    delete p;
	return 0;
}

int __fastcall AcadExportThread::ExportAttachments(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0);
	aexp->AddLayer("RoadAttachments");

	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==ROADATTACH) {
			SET_PROGRESS_FORM_POSITION(i);
			TRoadAttach *t=dynamic_cast<TRoadAttach*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportAttach(p,t);
				delete p;
			}
		}
	}
	aexp->ExportAttach(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportRoadSideObjects(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0);
	aexp->AddLayer("RoadSideObjects");

	for (int i=0;i<MetricData->Objects->Count;i++) {
		if (Terminated) return -1;
		SET_PROGRESS_FORM_POSITION(i);
		if (MetricData->Objects->Items[i]->DictId==RESTZONECODE) {
			TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(MetricData->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportRestZone(p,t);
				delete p;
			}
		}
	}
	aexp->ExportRestZone(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportCommunications(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadCommunication");
	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==COMMUNICATIONCODE) {
			SET_PROGRESS_FORM_POSITION(i;)
			TCommunication *t=dynamic_cast<TCommunication*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportCommunication(p,t);
				delete p;
			}
		}
	}
	return 0;
}

int __fastcall AcadExportThread::ExportTrafficLights(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)

	aexp->AddLayer("RoadTrafficLights");

    vector<pair<TExtPolyline*, TTrafficLight*> > tlights;

    for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==77) {
			TTrafficLight *t=dynamic_cast<TTrafficLight*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
                tlights.push_back(make_pair(p, t));
			}
		}
	}

    vector<pair<TExtPolyline*, TTrafficLight*> > tlightGroup;
    vector<TTrafficLight*> trafficLights;
    int progressCounter = 0;

    SET_PROGRESS_FORM_MINMAX(0,tlights.size());

    for (int i=0;i<tlights.size();++i) {
        if (Terminated) return -1;
        tlightGroup.clear();
        tlightGroup.push_back(tlights[i]);

        ++progressCounter;

        POINT p1 = tlights[i].first->Points[0];
        // form trafficlights group
        for (int j=i+1;j<tlights.size();++j) {
            POINT p2 = tlights[j].first->Points[0];
            if (abs(p1.x - p2.x) <= 50 && abs(p1.y - p2.y) <= 50) {
                ++progressCounter;
                tlightGroup.push_back(tlights[j]);
                tlights.erase(tlights.begin() + j);
                --j;
            }
        }

        trafficLights.clear();
        for (int j=0;j<tlightGroup.size();++j) {
            trafficLights.push_back(tlightGroup[j].second);
        }
        aexp->ExportTrafficLight(tlights[i].first, trafficLights);

        // clear memory
        for (int j=0;j<tlightGroup.size();++j) {
            delete tlightGroup[j].first;
        }
        SET_PROGRESS_FORM_POSITION(progressCounter)
    }

    /*for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==77) {
			SET_PROGRESS_FORM_POSITION(i;)
			TTrafficLight *t=dynamic_cast<TTrafficLight*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportTrafficLight(p,t);
				delete p;
			}
		}
	} */

    /*for (int i=0;i<signs.size();++i) {
        sgrp.clear();
        sgrp.push_back(signs[i].s);
        for (int j=i+1;j<signs.size();++j) {
            if (signgroup(signs[i],signs[j])) {
                sgrp.push_back(signs[j].s);
                signs.erase(signs.begin() + j);
                --j;
            }
        }
        aexp->ExportSigns(signs[i].p,sgrp.begin(),sgrp.size());
        SET_PROGRESS_FORM_MINMAX(0,signs.size());
        SET_PROGRESS_FORM_POSITION(i);
    }*/


	return 0;
}

int __fastcall AcadExportThread::ExportCityObjects(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadTrafficLights");
	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==76) {
			/*SET_PROGRESS_FORM_POSITION(i;)
			TTrafficLight *t=dynamic_cast<TTrafficLight*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportTrafficLight(p,t);
				delete p;
			} */
		}
	}
	return 0;
}

int __fastcall AcadExportThread::ExportTubes(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadTubes");
	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==ROADTUBECODE) {
			SET_PROGRESS_FORM_POSITION(i;)
			TRoadTube *t=dynamic_cast<TRoadTube*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportTube(p,t);
				delete p;
			}
		}
	}
	aexp->ExportTube(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportBridges(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadBridges");
	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==ROADBRIDGECODE) {
			SET_PROGRESS_FORM_POSITION(i;)
			TRoadBridge *t=dynamic_cast<TRoadBridge*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportBridge(p,t);
				delete p;
			}
		}
	}
	aexp->ExportBridge(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportBusstops(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadBusStops");
	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==BUSSTOPCODE) {
			SET_PROGRESS_FORM_POSITION(i;)
			TBusStop *t=dynamic_cast<TBusStop*>(data->Objects->Items[i]);
			if (t) {
				TExtPolyline *p=t->PrepareMetric(R);
				aexp->ExportBusStop(p,t);
				delete p;
			}
		}
	}
	aexp->ExportBusStop(0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportMoundHeights(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0;)
	aexp->AddLayer("RoadMoundHeights");

	for (int fase =0;fase <2;fase++) {
		for (int i=0;i<data->Objects->Count;i++) {
			if (Terminated) return -1;
			if (data->Objects->Items[i]->DictId==MOUNDHEIGHTCODE) {
				if (fase) SET_PROGRESS_FORM_POSITION(i);
				TMoundHeight *m=dynamic_cast<TMoundHeight*>(data->Objects->Items[i]);
				if (m) {
					aexp->ExportMoundHeight(m,fase);
				}
			}
		}
	}
	aexp->ExportMoundHeight(0,0,true);
	return 0;
}

// ЗНАКИ

#define SSCOUNT 10
const char SingleSign[SSCOUNT][5]={"1.34","5.23","5.24","5.25","5.26","6.9.","6.10","6.11","6.12","6.13"};
const int SignPrior[8]={2,1,5,3,4,6,7,8};

struct wpsign {
    double x,y;
    TExtPolyline *p;
    TRoadSign *s;
    wpsign(TRoadSign *_s,TExtPolyline *_p) {
        s=_s;        p=_p;
        x=p->Points[0].x;
        y=p->Points[0].y;
    }
};

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


int __fastcall AcadExportThread::ExportRoadSigns(TDtaSource* data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0);
	aexp->AddLayer("RoadSigns");

	std::vector<wpsign> signs;

	if (data) {
		for (int i=0;i<data->Objects->Count;i++) {
			if (Terminated) return -1;
			if (data->Objects->Items[i]->DictId>=SGNCODE && data->Objects->Items[i]->DictId<SGNCODE+10) {
				TRoadSign *t=dynamic_cast<TRoadSign*>(data->Objects->Items[i]);
				if (t) {
					TExtPolyline *p=t->PrepareMetric(R);
					signs.push_back(wpsign(t,p));
				}
			}
		}
	}

	sort(signs.begin(),signs.end());
	vector<pair<TExtPolyline*, TRoadSign*> > sgrp;
    vector<TRoadSign*> signsGroup;

    int progressCounter = 0;

    SET_PROGRESS_FORM_MINMAX(0,signs.size());

    for (int i=0;i<signs.size();++i) {
        if (Terminated) return -1;
        sgrp.clear();
        sgrp.push_back(make_pair(signs[i].p, signs[i].s));

        ++progressCounter;
        for (int j=i+1;j<signs.size();++j) {
            if (signgroup(signs[i],signs[j])) {
                sgrp.push_back(make_pair(signs[j].p, signs[j].s));
                signs.erase(signs.begin() + j);
                --j;
                ++progressCounter;
            }
        }

        signsGroup.clear();
        for (int j=0;j<sgrp.size();++j) {
            signsGroup.push_back(sgrp[j].second);
        }

        aexp->ExportSigns(signs[i].p,signsGroup.begin(),signsGroup.size());

        SET_PROGRESS_FORM_POSITION(progressCounter);

        for (int j=0;j<sgrp.size();++j) {
            delete sgrp[j].first;
        }
    }

	aexp->ExportSigns(0,0,0,true);
	
	return 0;
}

// ЗНАКИ

int __fastcall AcadExportThread::ExportRoadMark(TDtaSource* data, TAcadExport* aexp, int lineWidth, int* leftMax, int* rightMax)
{
	SET_PROGRESS_FORM_POSITION(0);
	aexp->AddLayer("RoadMark");

    bool onlyCountLines = (leftMax != 0) & (rightMax != 0);
    if (onlyCountLines) {
      *leftMax = 0;
      *rightMax = 0;
    }


	for (int i=0;i<data->Objects->Count;i++) {
		if (Terminated) return -1;
		if (data->Objects->Items[i]->DictId==ROADMARKCODE) {
			SET_PROGRESS_FORM_POSITION(i);
			TRoadMark *t=dynamic_cast<TRoadMark*>(data->Objects->Items[i]);
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
						if (lineWidth<=0) {
						  if (tcat) {
							  if (tcat->Value==rc1a || tcat->Value==rc1 || tcat->Value==rc1b || tcat->Value==rc2 || tcat->Value==rc3)
								  defwidth=350;
							  else if (tcat->Value==rc5)
								  defwidth=250;
						  }
						} else {
							defwidth = lineWidth;
						}
						midx/=(2*dl);
						if (abs(minx)<50 && abs(maxx)<50)  {
							line=0;
						} else {
							if (midx-minx<50 || maxx-midx<50)
								line=RoundTo((float)(midx+(midx>0 ? defwidth/2:-defwidth/2))/defwidth-(Sign(midx)*0.1),0);
						}
					}
                    if (onlyCountLines) {
                      switch(t->Kind) {
                      case ma1_park:
                      case ma14_1:
                      case ma14_2:
                      case ma14_3:
                      case ma12:
                      case ma13:
                      case ma14_1e:
                      case ma18p:
                      case ma18r:
                      case ma18l:
                      case ma18pr:
                      case ma18pl:
                      case ma18rl:
                      case ma18prl:
                      case ma19_1:
                      case ma19_2:
                      case ma20:
                      case ma23:
                      case ma24_1:
                      case ma24_2:
                      case ma24_3:
                      case ma24_4:
                      case ma25:
                        break;
                      default:
                        if (line<0) {
                            if (*leftMax < -line && line > -10) {
                                *leftMax = -line;
                            }
                        } else if (line > 0) {
                            if (*rightMax < line && line < 10) {
                                *rightMax = line;
                            }
                        }
                      }
                    }
				}
                if (!onlyCountLines)
    				aexp->ExportRoadMark(p,t,line,s);
				delete p;
			}
		}
	}
    if (!onlyCountLines)
	    aexp->ExportRoadMark(0,0,0,0,true);
	return 0;
}

int __fastcall AcadExportThread::SortCurrentAndProjectObjects(TDtaSource* dataCurrent, TDtaSource* dataProject, vector<pair<int,wpbar> > &out)
{
	if (dataProject) {
		SET_PROGRESS_FORM_MINMAX(0,dataProject->Objects->Count-1);
		SET_PROGRESS_FORM_POSITION(0)
		for (int i=0;i<dataProject->Objects->Count;i++) {
			SET_PROGRESS_FORM_POSITION(i)
			if (Terminated) return -1;
			if (dataProject->Objects->Items[i]->DictId==ROADSIGNALCODE) {
				TRoadSignal *t=dynamic_cast<TRoadSignal*>(dataProject->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
			} else if (dataProject->Objects->Items[i]->DictId==ROADBARRIERCODE) {
				TRoadBarrier *t=dynamic_cast<TRoadBarrier*>(dataProject->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
			} else if (dataProject->Objects->Items[i]->DictId==SIDEWALKCODE) {
				TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(dataProject->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
			} else if (dataProject->Objects->Items[i]->DictId==ROADLAMPCODE) {
				TRoadLighting *t=dynamic_cast<TRoadLighting*>(dataProject->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
			} else if (dataProject->Objects->Items[i]->DictId==ROADBORDERCODE) {
				TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(dataProject->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,false)));
			}
		}
	}
	// только для столбиков требуется в настройках поставить дополнительную галочку
	// для вывода существующих столбиков
	if (dataCurrent) {
		SET_PROGRESS_FORM_MINMAX(0,dataCurrent->Objects->Count-1);
		SET_PROGRESS_FORM_POSITION(0)
		// столбики из существующего выводим всегда если не указан проектируемый источник,
		// иначе только если стоит галочка в настройках
		//bool fIncludeSignalExist = dataProject!=0?FAutoCADExport->ExportSignalExistToo:true;
		for (int i=0;i<dataCurrent->Objects->Count;i++) {
			SET_PROGRESS_FORM_POSITION(i)
			if (Terminated) return -1;
			if (dataCurrent->Objects->Items[i]->DictId==ROADSIGNALCODE) {
				TRoadSignal *t=dynamic_cast<TRoadSignal*>(dataCurrent->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
			} else if (dataCurrent->Objects->Items[i]->DictId==ROADBARRIERCODE) {
				TRoadBarrier *t=dynamic_cast<TRoadBarrier*>(dataCurrent->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
			} else if (dataCurrent->Objects->Items[i]->DictId==SIDEWALKCODE) {
				TSquareRoadSideObject_Kromka *t=dynamic_cast<TSquareRoadSideObject_Kromka*>(dataCurrent->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
			}  else if (dataCurrent->Objects->Items[i]->DictId==ROADLAMPCODE) {
				TRoadLighting *t=dynamic_cast<TRoadLighting*>(dataCurrent->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
			} else if (dataCurrent->Objects->Items[i]->DictId==ROADBORDERCODE) {
				TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(dataCurrent->Objects->Items[i]);
				if (t)
					out.push_back(pair<int,wpbar>(t->L,wpbar(t,true)));
			}
		}
	}
}

int __fastcall AcadExportThread::ExportSignal(vector<pair<int,wpbar> > &data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0)
	aexp->AddLayer("RoadSignals");
	
	for (vector<pair<int,wpbar> >::iterator i=data.begin();i!=data.end();i++) {
		if (Terminated) return -1;
		SET_PROGRESS_FORM_POSITION((i - data.begin()));
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
	return 0;
}


int __fastcall AcadExportThread::ExportSidewalks(vector<pair<int,wpbar> > &data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0)
	aexp->AddLayer("RoadSidewalks");
	
    vector<KromkaObject> sidewalks;
	vector<KromkaObjectGroup> sidewalksGroups;
    // формируем массив тротуаров, чтобы убрать пересечения
    for(int i=0;i<data.size();++i) {
        if (data[i].second.w) {
          KromkaObject k;
          k.obj = data[i].second.w;
          k.exist = data[i].second.exist;
          sidewalks.push_back(k);
        }
    }
	
	// формируем группы
	for(int i=0;i<sidewalks.size();++i) {
		KromkaObject &obj1 = sidewalks[i];
		sidewalksGroups.push_back(KromkaObjectGroup(R));
		sidewalksGroups.back().addObject(obj1);
		for(int j=i+1;j<sidewalks.size();++j) {
			KromkaObject &obj2 = sidewalks[j];
			if (sidewalksGroups.back().isOverlap(obj2)) {
				sidewalksGroups.back().addObject(obj2);
				sidewalks.erase(sidewalks.begin() + j);
				--j;
			}
		}
	}

    SET_PROGRESS_FORM_MINMAX(0,sidewalksGroups.size());
	// выводим тротуары группами
	for(int i=0;i<sidewalksGroups.size();++i) {
        if (Terminated) return -1;
		aexp->ExportSidewalk(&sidewalksGroups[i]);
        SET_PROGRESS_FORM_POSITION(i)
	}
	/*for(int i=0;i<sidewalks.size();++i) {
		TExtPolyline* p = sidewalks[i].obj->PrepareMetric(R);
		aexp->ExportSidewalk(p,sidewalks[i].obj,sidewalks[i].exist);
		delete p;
	}*/
	
	aexp->ExportSidewalk(0,true);
    
	return 0;
}

int __fastcall AcadExportThread::ExportLamps(vector<pair<int,wpbar> > &data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0)
	aexp->AddLayer("Lights");
	
	for (vector<pair<int,wpbar> >::iterator i=data.begin();i!=data.end();i++) {
		if (Terminated) return -1;
		SET_PROGRESS_FORM_POSITION((i - data.begin()));
		if (i->second.l) {
			TExtPolyline *p=i->second.l->PrepareMetric(R);
			aexp->ExportLighting(p,i->second.l,i->second.exist);
			delete p;
		}
	}
	aexp->ExportLighting(0,0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportBorders(vector<pair<int,wpbar> > &data, TAcadExport* aexp) 
{
	SET_PROGRESS_FORM_POSITION(0)
	aexp->AddLayer("Borders");
	
	for (vector<pair<int,wpbar> >::iterator i=data.begin();i!=data.end();i++) {
		if (Terminated) return -1;
		SET_PROGRESS_FORM_POSITION((i - data.begin()));
		if (i->second.a) {
			TExtPolyline *p=i->second.a->PrepareMetric(R);
			aexp->ExportBorder(p,i->second.a,i->second.exist);
			delete p;
		}
	}
	aexp->ExportBorder(0,0,0,true);
	return 0;
}

int __fastcall AcadExportThread::ExportSlope(TDtaSource* data, TAcadExport* aexp)
{
	SET_PROGRESS_FORM_POSITION(0)
    aexp->AddLayer("RoadSlopes");

    for (int i=0;i<data->Objects->Count;i++) {
        if (Terminated) return -1;
        SET_PROGRESS_FORM_POSITION(i)
        if (data->Objects->Items[i]->DictId==DANGERSLOPECODE) {
            TDangerSlope *t=dynamic_cast<TDangerSlope*>(data->Objects->Items[i]);
            if (t) {
                aexp->ExportSlope(t);
            }
        }
    }
    aexp->ExportSlope(0,0,true);
    return 0;
}

int __fastcall AcadExportThread::ExportCurves(TDtaSource* data, TAcadExport* aexp)
{
	SET_PROGRESS_FORM_POSITION(0)
    aexp->AddLayer("RoadCurves");

    for (int i=0;i<data->Objects->Count;i++) {
        if (Terminated) return -1;
        SET_PROGRESS_FORM_POSITION(i)
        if (data->Objects->Items[i]->DictId==DANGERCURVECODE) {
            TDangerCurve *t=dynamic_cast<TDangerCurve*>(data->Objects->Items[i]);
            if (t) {
                aexp->ExportCurve(t);
            }
        }
    }
    aexp->ExportCurve(0,true);
    return 0;
}


void __fastcall AcadExportThread::Execute()
{

#define ACAD_EXPORT_ERROR  SET_PROGRESS_FORM_CAPTION_EX("возникли непредвиденные ошибки"); \
    BUILDER_ERROR("возникли непредвиденные ошибки");    \
    fWickedErrorWas = true;

#define EXPORT_ITEM(function, message) \
    currentItem++; \
    SET_PROGRESS_FORM_CAPTION_EX(message); \
    try {           \
        if (function == -1) goto export_end; \
    } catch (...) { ACAD_EXPORT_ERROR } \

    if (!MetricData) return;

    bool fWickedErrorWas = false; // проверка на наличие неопределенных ошибок

    RESET_ERROR_FLAG; // сброс глобального флага ошибок

    aexp = new TAcadExport();
    aexp->RoadName = RoadName;
    int L1=MetricData->Road->LMin;
    int L2=MetricData->Road->LMax;
    int DX=10000;
    bool fDeleteLayerObjects = false;

    R = new TRoad(MetricData->Road,L1,L2);
    R->SetBound(L1,L2,-DX,DX);
    R->SetFrame(L1,L2,-DX,DX,pkGorizontal,pdDirect);
    R->SetOutBound(L1,L2,-DX,DX);

    aexp->OutInfoLog = OutInfoLog;
    aexp->ProgressChanged = ProgressChanged;

    if (FAutoCADExport->ExportAddRows) {
        if ( !(aexp->ExportTopAddRows(FAutoCADExport->EditTopAddRows,true)
                || aexp->ExportBottomAddRows(FAutoCADExport->EditTopAddRows,true)) ) {
            int result = Application->MessageBox("По пути указаному для дополнительных строк не было найденно не одного файла."
                                                 "Желаете ли вернуться и указать другой путь(No) или оставить все как есть и продолжить(Yes)?", "Предупреждение", MB_YESNO );
            switch ( result ) {
            case IDNO:
                delete aexp;
                delete R;
                goto export_end;
                break;
            }
        }
    }

    if (aexp->BeginDocument(R)) {
        ProgressForm->Caption = "Идет экспорт в AutoCAD";
        SET_PROGRESS_FORM_CAPTION("Пробую подключиться к AutoCAD")
        SET_PROGRESS_FORM_POSITION(0);
        ProgressForm->ShowLog = true;
        ProgressForm->clearLog();
        ProgressForm->Thread = this;
        ProgressForm->Show();

        TDtaSource *CurData=(TDtaSource*)FAutoCADExport->cbCurList->Items->Objects[FAutoCADExport->cbCurList->ItemIndex];
        TDtaSource *PrjData=(TDtaSource*)FAutoCADExport->cbPrjList->Items->Objects[FAutoCADExport->cbPrjList->ItemIndex];
        TDtaSource *DataPrj = PrjData==0?CurData:PrjData; // для обектов выводимых приоритено из проектного источника
        TDtaSource *DataCur = CurData==0?PrjData:CurData; // для обектов выводимых приоритено из текущего источника

        int countOfExportItems = FAutoCADExport->CountOfExports();
        int currentItem = 0;

        switch (FAutoCADExport->ExportTo) {
        case 0:
            ADD_PROGRESS_FORM_LINE("Подключение к активному документу");
            if (!aexp->BindActiveDocument()) {
                goto export_end;
            }
            break;
        case 1:
            ADD_PROGRESS_FORM_LINE("Создание нового документа");
            if (!aexp->OpenDocument(FAutoCADExport->FileName)) {
                goto export_end;
            }
            break;
        default:
            goto export_end;
        }


        if (FAutoCADExport->ExportHideAutoCAD) {
            ADD_PROGRESS_FORM_LINE("Скрываю AutoCAD");
            aexp->hideApplication();
        } else {
            aexp->showApplication();
        }
        // -- Подсчет разметки от осевой -- 
        int iMarksLinesTop = FAutoCADExport->TableRowLinesTop;
        int iMarksLinesBottom = FAutoCADExport->TableRowLinesBottom;
        aexp->iMarkLinesBottom = aexp->iMarkLinesTop = 0;

        if (DataPrj && (!FAutoCADExport->TableRowLinesBottom || !FAutoCADExport->TableRowLinesTop)) {
			int iLeftMax = 0, iRightMax = 0;
			
            SET_PROGRESS_FORM_MINMAX(0, DataPrj->Objects->Count-1);
			currentItem--;
			EXPORT_ITEM(ExportRoadMark(DataPrj, aexp, FAutoCADExport->LineWidth, &iLeftMax, &iRightMax), "Считаем разметку...");
            
            FAutoCADExport->TableRowLinesTop = iLeftMax;
            FAutoCADExport->TableRowLinesBottom = iRightMax;
        }
        // \ конец Подсчет разметки от осевой 
		
        ADD_PROGRESS_FORM_LINE("Инициализация настроек таблицы");
        aexp->ExportTables(FAutoCADExport);  /*инициализация настроек таблицы*/

        /* -- вернем значени для разметки обратно -- */
        FAutoCADExport->TableRowLinesTop = iMarksLinesTop;
        FAutoCADExport->TableRowLinesBottom = iMarksLinesBottom;
        /* -- */

        if (FAutoCADExport->ExportGridStep) {
            aexp->AddLayer("Grid"); // вывод сетки
            aexp->DrawGrid(FAutoCADExport->GridStep);
        }

        if (FAutoCADExport->ExportRuler) {
            aexp->AddLayer("Ruler"); // вывод линейки
            aexp->ExportRuler(L1, L2, false);
        }

		if (MetricData) {
			SET_PROGRESS_FORM_MINMAX(0,MetricData->Objects->Count-1);
			
			if (FAutoCADExport->ExportRoadMetrics) {
				EXPORT_ITEM(ExportRoadMetrics(MetricData, aexp), "Выводим метрику дороги...");
			}
			
			if (FAutoCADExport->ExportProfile) {
				EXPORT_ITEM(ExportProfile(MetricData, R, aexp), "Выводим профиль дороги..");
			}
			
			if (FAutoCADExport->ExportAttachments) {
				EXPORT_ITEM(ExportAttachments(MetricData, aexp), "Выводим примыкания...");
			}
			
			if (FAutoCADExport->ExportRoadSideObjects) {
				EXPORT_ITEM(ExportRoadSideObjects(MetricData, aexp), "Выводим участки отдыха...");
			}
		}
	
		/* Трубы, мосты ,автобусные остановки и высоты насыпей
		выводим приоритетно из существующих данных  */
		if (DataCur) {
			SET_PROGRESS_FORM_MINMAX(0,DataCur->Objects->Count-1);

			if (FAutoCADExport->ExportTown) {
				EXPORT_ITEM(ExportTowns(DataCur, aexp), "Выводим населенные пункты...");
			}

			if (FAutoCADExport->ExportPlan) { 
				EXPORT_ITEM(ExportPlan(DataCur, aexp), "Выводим план...");
			}

			if (FAutoCADExport->ExportSurface) {
				EXPORT_ITEM(ExportSurface(DataCur, aexp), "Выводим участки по покрытиям...");
			}

			if (FAutoCADExport->ExportCommunications) {
				EXPORT_ITEM(ExportCommunications(DataCur, aexp), "Выводим коммуникации...");
			}

			if (FAutoCADExport->ExportTrafficLights) {
				EXPORT_ITEM(ExportTrafficLights(DataCur, aexp), "Выводим светофоры...");
			}

			if (FAutoCADExport->ExportCityObjects) {
				EXPORT_ITEM(ExportCityObjects(DataCur, aexp), "Выводим городские объекты...");
			}

			if (FAutoCADExport->ExportTubes) {
				EXPORT_ITEM(ExportTubes(DataCur, aexp), "Выводим трубы...");
			}

			if (FAutoCADExport->ExportBridges) {
				EXPORT_ITEM(ExportBridges(DataCur, aexp), "Выводим мосты...");
			}

			if (FAutoCADExport->ExportBusstops) {
				EXPORT_ITEM(ExportBusstops(DataCur, aexp), "Выводим автобусные остановки...");
			}
			
			if (FAutoCADExport->ExportMoundHeights) {
				EXPORT_ITEM(ExportMoundHeights(DataCur, aexp), "Выводим высоты насыпей...");
			}
		}
		
		if (DataPrj) {
			SET_PROGRESS_FORM_MINMAX(0,DataPrj->Objects->Count-1);
			// знаки приоритетно выводим из проектируемого источника
			if (FAutoCADExport->ExportRoadSigns) {
				EXPORT_ITEM(ExportRoadSigns(DataPrj, aexp), "Выводим дорожные знаки...");
			}
			// разметку приоритетно выводим из проектируемого источника
            SET_PROGRESS_FORM_MINMAX(0,DataPrj->Objects->Count-1);
			if (FAutoCADExport->ExportMark) {
				EXPORT_ITEM(ExportRoadMark(DataPrj, aexp, FAutoCADExport->LineWidth), "Выводим разметку");
			}
		}

		// Выводим ограждения, сигнальные устройства, тротуары, бордюры из обоих источников одновременно
		if (FAutoCADExport->ExportSignal || FAutoCADExport->ExportSidewalks || FAutoCADExport->ExportLamps || FAutoCADExport->ExportBorders) {
			vector<pair<int,wpbar> > bvec;
            currentItem--;
			EXPORT_ITEM(SortCurrentAndProjectObjects(CurData, PrjData, bvec), "Сортируем проектируемые и существующие ограждения, сигнальные устройства, тротуары, освещение...");
			
			if (bvec.size()) {
				sort(bvec.begin(),bvec.end());
				SET_PROGRESS_FORM_MINMAX(0,bvec.size()-1);

				if (FAutoCADExport->ExportSignal) {
					EXPORT_ITEM(ExportSignal(bvec, aexp), "Выводим ограждения и сигнальные устройства...");
				}

				if (FAutoCADExport->ExportSidewalks) {
					EXPORT_ITEM(ExportSidewalks(bvec, aexp), "Выводим тротуары...");
				}

				if (FAutoCADExport->ExportLamps) {
					EXPORT_ITEM(ExportLamps(bvec, aexp), "Выводим фонари...");
				}

				if (FAutoCADExport->ExportBorders) {
					EXPORT_ITEM(ExportBorders(bvec, aexp), "Выводим бордюры...");
				}
			}
		}

        // Участки уклонов выводим из слоя с профилем
        if (ProfilData) {
            if (FAutoCADExport->ExportSlope) {
                SET_PROGRESS_FORM_MINMAX(0,ProfilData->Objects->Count-1);
                EXPORT_ITEM(ExportSlope(ProfilData, aexp), "Выводим участки уклонов ...");
            }
        }

        // Схематический план выводим из слоя с планом
        if (CurveData) {
            if (FAutoCADExport->ExportCurves) {
                SET_PROGRESS_FORM_MINMAX(0,CurveData->Objects->Count-1);
                EXPORT_ITEM(ExportCurves(CurveData, aexp), "Выводим кривые в плане...");
            }
        }

        try {
            if (FAutoCADExport->ExportAddRows) {
                currentItem++;
                SET_PROGRESS_FORM_CAPTION_EX("выводим дополнительные строки из файлов в верхнюю таблицу")
                SET_PROGRESS_FORM_MINMAX(0,100);
                SET_PROGRESS_FORM_POSITION(0)
                if (aexp->ExportTopAddRows(FAutoCADExport->EditTopAddRows)==-1) {
                    goto export_end;
                }

                SET_PROGRESS_FORM_MINMAX(0,100);
                SET_PROGRESS_FORM_POSITION(0)
                currentItem++;
                SET_PROGRESS_FORM_CAPTION_EX("выводим дополнительные строки из файлов в нижнюю таблицу")
                if (aexp->ExportBottomAddRows(FAutoCADExport->EditTopAddRows)==-1) {
                    goto export_end;
                }
            }
        } catch (...) {
            ACAD_EXPORT_ERROR;
        }

        try {
            if (FAutoCADExport->ExportGraphic) {
                currentItem++;
                SET_PROGRESS_FORM_CAPTION("выводим дополнительные строки графика")
                aexp->ExportGraphic(FAutoCADExport->EditTopAddRows,false);
            }
        } catch (...) {
            ACAD_EXPORT_ERROR;
        }

        try {
            if (FAutoCADExport->ExportTable) {
                currentItem++;
                aexp->AddLayer("Table");
                aexp->DrawTables(FAutoCADExport->ExportRuler);
            }
        } catch (...) {
            ACAD_EXPORT_ERROR;
        }

        try {
            SET_PROGRESS_FORM_CAPTION("Завершение процесса...");
        } catch (...) {
            BUILDER_ERROR("Ошибка, на последнем этапе O_O, да не может быть!");
        }
    } else {
        BUILDER_ERROR("Невозможно начать работу с AutoCad");
        ShowMessage("Невозможно начать работу с AutoCad");
    }

// МЕТКА :D
export_end:
    //if (FAutoCADExport->ExportHideAutoCAD) {
    aexp->showApplication();
    //}
    ProgressForm->Hide();
    if ( ERROR_WAS ) {
        if (!fWickedErrorWas) {
            ShowMessage("Во время исполнения были обнаружены небольшие ошибки. Рекомендуется ознакомиться с журналом.");
        } else {
            ShowMessage("Во время исполнения были обнаружены серьезные ошибки. Возможно что некотороые строки не были выведены.\nРекомендуется ознакомиться с журналом.");
        }
    }
    aexp->EndDocument();
    FlashWindow(Application->Handle, true);
    delete aexp;
    delete R;
}
//---------------------------------------------------------------------------


#endif // WITHOUT_AUTOCAD

