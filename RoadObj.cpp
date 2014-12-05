//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RoadObj.h"                                                  
#include "ObjForm.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)


IMPPROPERTY(TRoadObject,__int32,L)
IMPPROPERTY(TRoadObject,__int32,PrevId)
IMPPROPERTY(TRoadObject,TSignTest,Test)
IMPPROPERTY(TRoadObject,String,Note)


IMPPROPERTY(TCommunication,TCommunicationPlacement,Placement)
IMPPROPERTY(TCommunication,TGroundPlacement,PlaceGround)
IMPPROPERTY(TCommunication,TCommunicationKind,CommKind)

IMPPROPERTY(TRoadTube,int,Length)
IMPPROPERTY(TRoadTube,TTubePlacement,Placement)
IMPPROPERTY(TRoadTube,String,Scheme)

IMPPROPERTY(TDescreetDirRoadObject,TRoadDirection,Direction)
IMPPROPERTY(TDescreetDirRoadObject,__int32,DX)

IMPPROPERTY(TDescreetSideRoadObject,TRoadSide,Placement)
IMPPROPERTY(TDescreetSideRoadObject,__int32,DX)

IMPPROPERTY(TDescreetCenterRoadObject,__int32,DX)

IMPPROPERTY(TMoundHeight,TRoadSide,Placement)
IMPPROPERTY(TMoundHeight,__int32,Height)

IMPPROPERTY(TRoadLighting,TLampKind,Kind);

IMPPROPERTY(TBusStop,String,Name)
IMPPROPERTY(TBusStop,bool,StopArea)
IMPPROPERTY(TBusStop,bool,Pavilion)

IMPPROPERTY(TContRoadObject,__int32,LMax)

IMPPROPERTY(TRoadDefect,TDefectKind,Kind)
IMPPROPERTY(TRoadDefect,TRoadSide,Placement)

IMPPROPERTY(TRoadSideObject,__int32,DX)
IMPPROPERTY(TRoadSideObject,TObjPlacement,Placement)
IMPPROPERTY(TRoadSideObject,TMetricsKind,MetricsKind)

IMPPROPERTY(TDrainageObject,TDrainageKind,Kind)

IMPPROPERTY(TObochina,TRoadSide,Placement)
IMPPROPERTY(TObochina,__int32,DX)

IMPPROPERTY(TRoadAttach,TRoadClass,Tech)
IMPPROPERTY(TRoadAttach,String,Name)
IMPPROPERTY(TRoadAttach,TAttachPlacement,Placement)
IMPPROPERTY(TRoadAttach,int,Angle)
IMPPROPERTY(TRoadAttach,int,Width)
IMPPROPERTY(TRoadAttach,String,Comment)

IMPPROPERTY(TRoadOut,TRoadSurface,Surface)
IMPPROPERTY(TRoadOut,int,Length)
IMPPROPERTY(TRoadOut,TAttachWildness,Wildness)

IMPPROPERTY(TDressLayer,TLayer,Layer)
IMPPROPERTY(TDressLayer,__int32,UpperDeep)
IMPPROPERTY(TDressLayer,__int32,LowerDeep)



IMPPROPERTY(TRoadMark,int, Area)
IMPPROPERTY(TRoadMark,int, Length)
IMPPROPERTY(TRoadMark,int, Offset)
IMPPROPERTY(TRoadMark,int, K)
IMPPROPERTY(TRoadMark,TRoadDirection,Direction)
IMPPROPERTY(TRoadMark,TMarkKind,Kind)

IMPPROPERTY(TTrafficLight,__int32,Direction)
IMPPROPERTY(TTrafficLight,TTrafficLightsPlacement,Placement)
IMPPROPERTY(TTrafficLight,TTrafficLightsKind,Kind)


IMPPROPERTY(TRoadBarrier,TBarrierConstruction,Construction)
IMPPROPERTY(TRoadSignal,int,Count)
IMPPROPERTY(TRoadSignal,TRoadSignalKind,Kind)

IMPPROPERTY(TRoadSign,__int32,NumRoadSign)
IMPPROPERTY(TRoadSign,__int32,ViewKind)
IMPPROPERTY(TRoadSign,String,Label)
IMPPROPERTY(TRoadSign,TRoadSignPlacement,Placement)
IMPPROPERTY(TRoadSign,String,OldTitle)
IMPPROPERTY(TRoadSign,TSignAttach,OnAttach)
IMPPROPERTY(TRoadSign,TSignBackColor,Color)

IMPPROPERTY(TRailCross,TRailKind,RailKind)
IMPPROPERTY(TRailCross,TRailCrossSignal,SignalKind)
IMPPROPERTY(TRailCross,int,RailCount)
IMPPROPERTY(TRailCross,bool,Light)
IMPPROPERTY(TRailCross,bool,Guard)

IMPPROPERTY(TTown,String,Title)

IMPPROPERTY(TMapObject,String,Title)

IMPPROPERTY(TRoadBridge,String,Scheme)                    // Схема моста
IMPPROPERTY(TRoadBridge,String,ObstacleName)              //Имя преграды
IMPPROPERTY(TRoadBridge,TObstacleKind,ObstacleKind)        //Тип преграды
IMPPROPERTY(TRoadBridge,__int32,Width)                    // Ширина моста в сантиметрах
IMPPROPERTY(TRoadBridge,TBridgeKind,Kind)                 // Тип конструкции моста
IMPPROPERTY(TRoadBridge,TBridgeConstruction,Construction) // Тип пролетных строений
IMPPROPERTY(TRoadBridge,TBridgeMaterial,Material)         //материал покрытия
IMPPROPERTY(TRoadBridge,__int32,Tonnage1)                 //В потоке общая грузоподъемность
IMPPROPERTY(TRoadBridge,__int32,Tonnage2)                 //В потоке осевая
IMPPROPERTY(TRoadBridge,__int32,Tonnage3)                 //В одиночном порядке

IMPPROPERTY(TRoadObstacle,String,ObstacleName)              //Имя преграды
IMPPROPERTY(TRoadObstacle,TObstacleKind,ObstacleKind)        //Тип преграды
IMPPROPERTY(TRoadObstacle,__int32,Width)                    // Ширина моста в сантиметрах

IMPPROPERTY(TDTP, __int32, CarCount)                       // Количество машин в ДТП

IMPPROPERTY(TBandRoadPart,__int32, Width)                // Ширина участка дороги
IMPPROPERTY(TBandRoadPart,__int32, EWidth)               // Окончательная Ширина участка дороги
IMPPROPERTY(TZemPolotno,__int32,TopWidth)                // Ширина зем полотна по верху

IMPPROPERTY(TRoadDress,TDressMaterial,Material)
IMPPROPERTY(TRoadDress,int,Height)
IMPPROPERTY(TRoadDress,TLayerKind,LayerKind)
IMPPROPERTY(TRoadDress,int,LayerNum)

IMPPROPERTY(TDangerSlope,int,Radius)
IMPPROPERTY(TDangerSlope,int,Promille)
IMPPROPERTY(TDangerSlope,TPermiss,Permissible)

IMPPROPERTY(TDangerCurve,int,Radius)
IMPPROPERTY(TDangerCurve,TCurveKind,Kind)
IMPPROPERTY(TDangerCurve,TPermiss, Permissible)

IMPPROPERTY(TDangerVisMode,__int32, Length)
IMPPROPERTY(TDangerVisMode,TRoadDirection,Direction)

IMPPROPERTY(TRoadDescription,String,Description)
IMPPROPERTY(TRoadDescription,String,BeginName)
IMPPROPERTY(TRoadDescription,String,EndName)

IMPPROPERTY(TSquareRoadSideObject,__int32,Width)

IMPPROPERTY(TCarePart,TDangPartKind,Reason)
IMPPROPERTY(TCarePart,TRoadSide,Placement)
IMPPROPERTY(TCarePart,double,NormaSquare)
IMPPROPERTY(TCarePart,double,HandlingSquare)

IMPPROPERTY(TRoadCategory,TRoadClass,Value);

bool __fastcall TCharList::PutPropValue(String name,String value)
{
int i;
for (i=0;i<Count;i++)
        if (Items[i]->Name==name)
                {
                Items[i]->Text=value;
                return true;
                }
return false;
}
void __fastcall TCharList::AddProperty(String name,String value)
{
// Надо сделать создание с помощью фабрики !!!!!!!!!
Add(new TStringCharacter(name,value));
}

String __fastcall TCharList::GetPropValue(String name)
{
int i;
for (i=0;i<Count;i++)
        if (Items[i]->Name==name)
                {
                return Items[i]->Text;
                }
return "NULL";
}

bool __fastcall TRoadObject::PutPropValue(String propname,String propvalue)
{
bool fail=true;
GetTypeProc p=(GetTypeProc)MethodAddress("GetType"+propname);
if (p)
        {
        String type;
        type=(p)(this);
        if (type=="String")
                {
                SetStrValueProc proc=(SetStrValueProc)MethodAddress("Set"+propname);
                if (proc)
                        {
                        proc(this,propvalue);
                        fail=false;
                        }
                }
        else if (type=="double")
                {
                SetFloatValueProc proc=(SetFloatValueProc)MethodAddress("Set"+propname);
                if (proc)
                        {
                        proc(this,propvalue.ToDouble());
                        fail=false;
                        }
                }
        else if (type=="bool")
                {
                SetBoolValueProc proc=(SetBoolValueProc)MethodAddress("Set"+propname);
                if (proc)
                        {
                        proc(this,propvalue.ToInt());
                        fail=false;
                        }
                }
        else
                {
                SetIntValueProc proc=(SetIntValueProc)MethodAddress("Set"+propname);
                if (proc)
                        {
                        if (propvalue!="")
                            proc(this,propvalue.ToInt());
                        else
                            proc(this,0);
                        fail=false;
                        }
                }
        }
if (fail)
        return FCharList->PutPropValue(propname,propvalue);
FModified=true;
return true;
}

void __fastcall TRoadObject::PutProperty(String propname,String propvalue)
{
if (!PutPropValue(propname,propvalue))
        FCharList->AddProperty(propname,propvalue);
FModified=true;
}

String __fastcall TRoadObject::GetPropValue(String propname)
{
bool fail=true;
String propvalue;
GetTypeProc p=(GetTypeProc)MethodAddress("GetType"+propname);
if (p)
        {
        String type=p(this);
        if (type=="String")
                {
                GetStrValueProc proc=(GetStrValueProc)MethodAddress("Get"+propname);
                if (proc)
                        {
                        propvalue=proc(this);
                        fail=false;
                        }
                }
        else if (type=="double")
                {
                GetFloatValueProc proc=(GetFloatValueProc)MethodAddress("Get"+propname);
                if (proc)
                        {
                        propvalue=proc(this);
                        fail=false;
                        }
                }
        else if (type=="bool")
                {
                GetBoolValueProc proc=(GetBoolValueProc)MethodAddress("Get"+propname);
                if (proc)
                        {
                        propvalue=(int)proc(this);
                        fail=false;
                        }
                }
        else
                {
                GetIntValueProc proc=(GetIntValueProc)MethodAddress("Get"+propname);
                if (proc)
                        {
                        int pval=proc(this);
                        propvalue=pval;
                        fail=false;
                        }
                }
        }
if (fail)
        propvalue=FCharList->GetPropValue(propname);
return propvalue;
}

int __fastcall TRoadObject::GetClassPropCount(void* MetaClass)
{
int res=0;
__int32 *vmt=*((__int32**)this);
if (*(vmt-9))
        {
        res=GetClassPropCount((void*)*(vmt-9));
        }
res+=*(vmt-13)/3;
return res;
}

int __fastcall TRoadObject::GetPropCount(void)
{
return GetClassPropCount(this)+FCharList->Count;
}

String __fastcall TRoadObject::GetPropName(int n)
{
return "";
}

void __fastcall TRoadObject::AddChild(TRoadObject *ch)
{
ch->Parent=this;
if (FChild==NULL)
    FChild=ch;
else
    {
    TRoadObject *nobj=FChild;
    while (nobj->Sibling!=NULL)
        nobj=nobj->Sibling;
    nobj->Sibling=ch;
    }
}

void __fastcall TRoadObject::RemoveChild(TRoadObject *ch)
{
TRoadObject *nobj=FChild;
if (nobj==ch)
    FChild=nobj->Sibling;
while (nobj->Sibling!=NULL)
    {
    if (nobj->Sibling==ch)
        {
        nobj->Sibling=nobj->Sibling->Sibling;
        break;
        }
    nobj=nobj->Sibling;
    }
}

String __fastcall TRoadObject::FormatPlacement(int p)
{
p=(p%100000)/100;
String Res=String(p);
while (Res.Length()<3)
    Res="0"+Res;
return Res;
}

void __fastcall TRoadObject::Dump(TStringList *lst,TDictSource *Dict)
{
lst->Add("Id="+String(FId));
lst->Add("PrevId="+String(FPrevId));;
lst->Add("Code="+String(FDictId));
int pnum=0;
if (FPoly)
    pnum=FPoly->Id;
lst->Add("Poly="+String(pnum));
TObjMetaClass *meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[FDictId]);
if (meta)
        {
        for (int i=0;i<meta->PropCount;i++)
                {
                int pid=meta->PropIds[i];
                String val=GetPropValue(Dict->PropClasses->Items[pid]->ClassName);
                lst->Add(String(pid)+"="+val);
                }
        }
}
void __fastcall TRoadObject::LoadDump(TStringList *lst,TDictSource *Dict)
{
PutProperty("PrevId",lst->Values["PrevId"]);
for (int i=4;i<lst->Count;i++)
        {
        int code=lst->Names[i].ToInt();
        String name=Dict->PropClasses->Items[code]->ClassName;
        PutProperty(name,lst->Values[String(code)]);
        }
}

void __fastcall TRoadObject::BuildCard(TObjFrm *Card)
{
TObjMetaClass *meta=dynamic_cast<TObjMetaClass*>(Card->Dict->ObjClasses->Items[FDictId]);
bool rw=!(Card->Data->ReadOnly);
Card->AddText(1,0,"Источник",Card->Data->SourceName,false);
if (meta)
    for (int i=0;i<meta->PropCount;i++)
        {
        int pid=meta->PropIds[i];
        String val=GetPropValue(Card->Dict->PropClasses->Items[pid]->ClassName);
        TPropClassesRec *rec=Card->Dict->PropClasses->Items[pid];
        if (((val=="")||(val=="NULL"))&&(rec->Type!=prString))
            val="0";
        switch (rec->Type)
            {
            case prEnum:Card->AddCombo(1,pid,rec->ShortName,val.ToInt(),rw);break;
            case prInteger: Card->AddText(1,pid,rec->ShortName,val,rw);break;
            case prBoolean: Card->AddCheckBox(1,pid,rec->ShortName,val.ToInt(),rw);break;
            case prFloat: Card->AddText(1,pid,rec->ShortName,val,rw);break;
            case prString: Card->AddText(1,pid,rec->ShortName,val,rw);break;
            }
        }
Card->AlignGroup(1);
}

#ifndef GDIEDIT
void __fastcall TRoadObject::SaveCard(TObjFrm *Card)
{
TObjMetaClass *meta=dynamic_cast<TObjMetaClass*>(Card->Dict->ObjClasses->Items[FDictId]);
int code;
if (meta)
        for (int i=0;i<meta->PropCount;i++)
              if (!Card->Data->ReadOnly)
            //    if ((!(meta->PropFlags[i]&PR_READONLY))||(FExist==seNotExist))
                        {
                        int pid=meta->PropIds[i];
                        TPropClassesRec *rec=Card->Dict->PropClasses->Items[pid];
                        String val=Card->SValue[pid];
                        PutProperty(rec->ClassName,val);
                        }
FDrwClassId=Card->Dict->SelectDrwParam(this,1);
}

void __fastcall TRoadObject::UpdateCard(TObjFrm *Card)
{
TObjMetaClass *meta=dynamic_cast<TObjMetaClass*>(Card->Dict->ObjClasses->Items[FDictId]);
if (meta)
        for (int i=0;i<meta->PropCount;i++)
//                if ((!(meta->PropFlags[i]&PR_READONLY))||(FExist==seNotExist))
                        {
                        int pid=meta->PropIds[i];
                        String val=GetPropValue(Card->Dict->PropClasses->Items[pid]->ClassName);
                        Card->SValue[pid]=val;
                        }
}

#endif

void __fastcall TRoadObject::MarkTagByTree(int marker)
{
FTag=marker;
TRoadObject *nobj=FChild;
while (nobj!=NULL)
    {
    nobj->MarkTagByTree(marker);
    nobj=nobj->Sibling;
    }
}

void __fastcall TRoadObject::UpdatePoly(void)
{
if (FPoly)
    {
    int n=FPoly->Count;
    if (n==0) {
       delete FPoly;
       FPoly=0;
    } else {
        int i;
        for (i=0;i<n;i++)
            {
            int c=FPoly->Points[i].Code.LBase();
            if ((c==1)||(c==2))
                break;
            }
        if (i==n)
            {
            int mn,mx;
            if (FPoly->GetMinMax(mn,mx))
                FL=(mn+mx)>>1;
            }
        }
    }
}

TExtPolyline* __fastcall TRoadObject::GetPolyMetric(TRoad* Road)
{
TExtPolyline *Res=NULL;
if (FPoly && FPoly->Count>0)
    {
    Res=new TExtPolyline();
    Road->ConvertPolyline(*FPoly,*Res);
    }
return Res;
}

TExtPolyline* TRoadObject::PrepareMetric(TRoad *Road)
{
TExtPolyline *Res=GetPolyMetric(Road);
if (Res==NULL || Res->Count==0)
    Res=GetDefMetric(Road);
return Res;
}

void __fastcall TContRoadObject::UpdatePoly(void)
{
if (FPoly)
    {
    int i;
    int n=FPoly->Count;
    for (i=0;i<n;i++)
        {
        int c=FPoly->Points[i].Code.LBase();
        if ((c==1)||(c==2))
            break;
        }
    if (i==n)
        {
        int mn,mx;
        if (FPoly->GetMinMax(mn,mx))
            FL=mn,FLMax=mx;
        }
    }
}


TExtPolyline* __fastcall TDescreetRoadObject::GetDefMetric(TRoad *Road)
{
TExtPolyline *Res=new TExtPolyline(1,0);
int x,y;
Road->ConvertPoint(FL,0,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
return Res;
}

TExtPolyline* __fastcall TTrafficLight::GetDefMetric(TRoad *Road)
{
TExtPolyline *Res=new TExtPolyline(2,0);
int x,y;
Road->ConvertPoint(FL,DX,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
Road->ConvertPoint(FL+100*cos(Direction*M_PI/180),DX+100*sin(Direction*M_PI/180),x,y);
Res->Points[1].x=x;
Res->Points[1].y=y;
return Res;
}

TExtPolyline* __fastcall TMoundHeight::GetDefMetric(TRoad *Road) {
   TRoadPoint Rp[2];
   TExtPolyline *Res=new TExtPolyline(2,1);
   Rp[0].L=FL;
   Rp[1].L=FL-Height/2;
   if (Placement==cpLeft) {
      Rp[0].X=Road->LeftSide.FindX(FL);
      Rp[1].X=Rp[0].X-Height;
   } else {
      Rp[0].X=Road->RightSide.FindX(FL);
      Rp[1].X=Rp[0].X+Height;
   }
   Res->Codes[0]=0;
   Road->ConvertPointsArray(2,Rp,Res->Points);
   return Res;
}

TPlanLabel* __fastcall TMoundHeight::GetText(int n,TRoad *Road,TDictSource *Dict) {
TPlanLabel *l=NULL;
if (n==0)
    {
    l=new TPlanLabel(0,IntToStr(Height));
    TRoadPoint p;
    p.L=FL;
    int x,y;
    if (Placement==cpLeft)
         p.X=Road->LeftSide.FindX(FL)-Height-500;
    else
       p.X=Road->RightSide.FindX(FL)+Height+100;
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(aLeft,aBaseline,oOrto,skByL);
    }
return l;
}



TExtPolyline* __fastcall TCommunication::GetDefMetric(TRoad *Road)
{
TPolyline Rp(2);
TExtPolyline *Res=new TExtPolyline;
Rp.Points[0].Code=0;
Rp.Points[1].Code=0;
if (Placement==cpLeft)
    {
    Rp.Points[0].L=LMin;
    Rp.Points[0].X=Road->XMin*2/3;
    Rp.Points[1].L=LMax;
    Rp.Points[1].X=Road->XMin*2/3;
    Res->DirectionVal=-1;
    }
else if (Placement==cpRight)
    {
    Rp.Points[0].L=LMin;
    Rp.Points[0].X=Road->XMax*2/3;
    Rp.Points[1].L=LMax;
    Rp.Points[1].X=Road->XMax*2/3;
    }
else
    {
    Rp.Points[0].L=LMin;
    Rp.Points[0].X=Road->XMin;
    Rp.Points[1].L=LMax;
    Rp.Points[1].X=Road->XMax;
    }
if (Rp.Points[0].L<Road->LMin)
    Rp.Points[0].L=Road->LMin;
if (Rp.Points[1].L>Road->LMax)
    Rp.Points[1].L=Road->LMax;
Road->ConvertPolyline(Rp,*Res);
return Res;
}

TExtPolyline* __fastcall TSpeedBump::GetDefMetric(TRoad *Road) {
TRoadPoint Rp[2];
int rx=Road->RightSide.FindX(FL);
int lx=Road->LeftSide.FindX(FL);
Rp[0].L=Rp[1].L=FL;
Rp[0].X=lx;
Rp[1].X=rx;
TExtPolyline *Res=new TExtPolyline(2,1);
Res->Codes[0]=0;
Road->ConvertPointsArray(2,Rp,Res->Points);
return Res;
}

TExtPolyline* __fastcall TRoadTube::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[2];
TExtPolyline *Res=new TExtPolyline(2,1);
Res->Codes[0]=0;
int len=FLength;
int rx=Road->RightSide.FindX(FL);
int lx=Road->LeftSide.FindX(FL);
if (!len)
    len=rx-lx;
if (Placement==tuLeft)
    {
    Rp[0].X=Rp[1].X=lx-100;
    Rp[0].L=FL-(len>>1);
    Rp[1].L=FL+(len>>1);
    Res->DirectionVal=-1;
    }
else if (Placement==tuRight)
    {
    Rp[0].X=Rp[1].X=rx+100;
    Rp[0].L=FL-(len>>1);
    Rp[1].L=FL+(len>>1);
    }
else
    {
    int dl=len-rx+lx;
    if (dl<0)
        dl=0;
    Rp[0].L=Rp[1].L=FL;
    Rp[0].X=lx-(dl>>1);
    Rp[1].X=rx+(dl>>1);
    }
Road->ConvertPointsArray(2,Rp,Res->Points);
return Res;
}

TPlanLabel* __fastcall TMapObject::GetText(int n,TRoad *Road,TDictSource *Dict)
{
TPlanLabel *l=NULL;
if (n==0 && Title.Length()>0)
    {
    l=new TPlanLabel(0,Title);
    double midX;
    if (FPoly && FPoly->Count) {
        for (int i=0;i<FPoly->Count;i++)
            midX+=FPoly->Points[i].X;
        midX/=FPoly->Count;
    } else
        midX=(Placement==opLeft ? Road->XMin:Road->XMax)/2;
    TRoadPoint p;
    p.L=(L+LMax)/2;
    p.X=midX;
    int x,y;
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(aCenter,aBaseline,oOrto,skByL);
    }
return l;
}

TPlanLabel* __fastcall TRoadTube::GetText(int n,TRoad *Road,TDictSource *Dict)
{
TPlanLabel *l=NULL;
if (n==0)
    {
    l=new TPlanLabel(0,FormatPlacement(L));
    TRoadPoint p;
    p.L=L;
    p.X=Road->RightSide.FindX(FL)+200;
    int x,y;
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(aLeft,aBaseline,oOrto,skByL);
    }
return l;
}

TExtPolyline* __fastcall TRoadWidthMeasure::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[2];
TExtPolyline *Res=new TExtPolyline(2,1);
Res->Codes[0]=0;
Rp[0].L=Rp[1].L=FL;
Rp[0].X=Road->RightSide.FindX(FL);;
Rp[1].X=Road->LeftSide.FindX(FL);
Road->ConvertPointsArray(2,Rp,Res->Points);
return Res;
}

TPlanLabel* __fastcall TRoadWidthMeasure::GetText(int n,TRoad *Road,TDictSource *Dict)
{
TPlanLabel *l=NULL;
if (n==0)
    {
    TRoadPoint p;
    int w1,w2;
    p.L=L;
    w1=Road->RightSide.FindX(FL);
    p.X=w1+200;
    w2=Road->RightLine.FindX(FL);
    int x,y;
    String S1=String((double)(w2/10)/10);
    String S2=String((double)((w1-w2)/10)/10);
    l=new TPlanLabel(0,S1+"|"+S2);
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(aLeft,aBaseline,oOrto,skByL);
    }
else if (n==1)
    {
    TRoadPoint p;
    int w1,w2;
    p.L=L;
    w1=Road->LeftSide.FindX(FL);
    w2=Road->LeftLine.FindX(FL);
    p.X=w1-200;
    String S1=String((double)(-w2/10)/10);
    String S2=String((double)((w2-w1)/10)/10);
    l=new TPlanLabel(0,S2+"|"+S1);
    int x,y;
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(aRight,aBaseline,oOrto,skByL);
    }
return l;
}

TExtPolyline* __fastcall TRoadDescription::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[4];
Rp[0].X=Road->XMin;
Rp[0].L=LMin;
Rp[1].X=Road->XMax;
Rp[1].L=LMin;
Rp[2].X=Road->XMax;
Rp[2].L=LMax;
Rp[3].X=Road->XMin;
Rp[3].L=LMax;
TExtPolyline *Res=new TExtPolyline(4,1);
Road->ConvertPointsArray(4,Rp,Res->Points);
Res->Codes[0]=0;
Res->Codes[2]=0;
return Res;
}

TPlanLabel* __fastcall TRoadDescription::GetText(int n,TRoad *Road,TDictSource *Dict)
{
if (n==0)
    {
    TPlanLabel *l=new TPlanLabel(0,"Начало автодороги:"+BeginName);
    TRoadPoint p;
    int x,y;
    Road->ConvertPoint(LMin,0,x,y);
    l->SetMetric(x,y,0,0);
    TVertAlign al=Road->PlDirect==pdDirect? aTop: aBottom;
    l->SetAlign(aCenter,al,oOrto,skByL);
    l->SetSize(13);
    return l;
    }
else if (n==1)
    {
    TPlanLabel *l=new TPlanLabel(0,"Конец автодороги:"+EndName);
    TRoadPoint p;
    int x,y;
    Road->ConvertPoint(LMax,0,x,y);
    l->SetMetric(x,y,0,0);
    TVertAlign al=Road->PlDirect==pdDirect? aBottom: aTop;
    l->SetAlign(aCenter,al,oOrto,skByL);
    l->SetSize(14);
    return l;
    }
return NULL;
}

TExtPolyline* __fastcall TRoadDefect::GetDefMetric(TRoad *Road)
{
int L1=LMin>Road->LMin? LMin : Road->LMin;
int L2=LMax<Road->LMax? LMax : Road->LMax;
TExtPolyline *Res=NULL;
/*
+            case 1020101: {loc=1;AR->Param1=67;}break;//Одиночные трещины
+            case 1020102: {loc=0;AR->Param1=94;}break;//Заплаты
+            case 1020103: {loc=0;AR->Param1=2; }break; //Выбоины
+            case 1020104: {loc=0;AR->Param1=85;}break; //Участки с сеткой трещин
+            case 1020105: {loc=1;AR->Param1=96;}break; //Разрушение кромки
+            case 1020106: {loc=2;AR->Param1=16;}break; //Колейность
+            case 1020107: {loc=0;AR->Param1=12;}break; //Застой воды
+            case 1020108: {loc=1;AR->Param1=1; }break; //Ступенька у обочины
+            case 1020109: {loc=0;AR->Param1=83;}break; //Участки обочин размытые или разрушенные
+            case 1020110: {loc=0;AR->Param1=88;}break; //Участки проезжей части разрушенные
+            case 1020111: {loc=0;AR->Param1=56;}break; //Ямы
+            case 1020112: {loc=0;AR->Param1=89;}break; //Участки дорог с массовыми разрушениями покрытия
+            case 1020113: {loc=2;AR->Param1=3; }break; //Гребенка
            case 1020114: {loc=0;AR->Param1=95;}break; //Выкрашивание покрытия
+            case 1020115: {loc=2;AR->Param1=84;}break; //Участки единичных трещин
*/
if ((Kind==dk12)||(Kind==dk83)||(Kind==dk84)||(Kind==dk88)||(Kind==dk89)||(Kind==dk85)||(Kind==dk3)||(Kind==dk95)||(Kind==dk16))  //дефекты в виде участков дорог
    {
    TPolyline *PL=new TPolyline;
    TPolyline *PR=new TPolyline;
    switch (Kind)
        {
        case dk12:
        case dk83:
            {
            if (Placement==rsLeft)
                {
                PL->CopyAndCut(&(Road->LeftSide),L1,L2);
                PR->CopyAndCut(&(Road->LeftLine),L1,L2);
                }
            else
                {
                PL->CopyAndCut(&(Road->RightLine),L1,L2);
                PR->CopyAndCut(&(Road->RightSide),L1,L2);
                }
            } break;
        case dk3:
        case dk16:
        case dk84:
        case dk85:
        case dk88:
        case dk89:
        case dk95:
            {
            PL->CopyAndCut(&(Road->LeftLine),L1,L2);
            PR->CopyAndCut(&(Road->RightLine),L1,L2);
            } break;
        }
    int n=PL->Count+PR->Count;
    Res=new TExtPolyline(n,1);
    // В дефекты точки пока не добавляем
    Road->ConvertPointsArray(PR->Count,PR->Points,Res->Points);
    Road->ConvertPointsArray(PL->Count,PL->Points,Res->Points+PR->Count);
    __int32 i,j;
    for (i=PR->Count,j=n-1;i<j;i++,j--)
        {
        __int32 tmp=Res->Points[i].x;
        Res->Points[i].x=Res->Points[j].x;
        Res->Points[j].x=tmp;
        tmp=Res->Points[i].y;
        Res->Points[i].y=Res->Points[j].y;
        Res->Points[j].y=tmp;
        }
    delete PL;
    delete PR;
    }
else if ((Kind==dk2)||(Kind==dk56)||(Kind==dk94)) // Выбоины ямы заплаты
    {
    Res=new TExtPolyline(4,1);
    TRoadPoint Rp[4];
    Rp[0].L=L1;
    Rp[0].X=Road->LeftLine.FindX(L1)/2;
    Rp[1].L=L1;
    Rp[1].X=Road->RightLine.FindX(L1)/2;
    Rp[2].L=L2;
    Rp[2].X=Road->RightLine.FindX(L2)/2;
    Rp[3].L=L2;
    Rp[3].X=Road->LeftLine.FindX(L2)/2;
    Road->ConvertPointsArray(4,Rp,Res->Points);
    }
else if ((Kind==dk1)||(Kind==dk96))               // кромка ступенька
    {
    TPolyline *P=new TPolyline;
    if (Placement==rsLeft)
        P->CopyAndCut(&(Road->LeftLine),L1,L2);
    else
        P->CopyAndCut(&(Road->RightLine),L1,L2);
    Res=new TExtPolyline(P->Count,1);
    Res->Codes[0]=0;
    Road->ConvertPointsArray(P->Count,P->Points,Res->Points);
    delete P;
    }
else if (Kind==dk17)   // Заросший кювет
    {
    TPolyline *P=new TPolyline;
    int DX;
    if (Placement==rsLeft)
        {
        P->CopyAndCut(&(Road->LeftSide),L1,L2);
        DX=-100;
        }
    else
        {
        P->CopyAndCut(&(Road->RightSide),L1,L2);
        DX=100;
        }
    for (int i=0;i<P->Count;i++)
        P->Points[i].X+=DX;
    Res=new TExtPolyline(P->Count,1);
    Res->Codes[0]=0;
    Road->ConvertPointsArray(P->Count,P->Points,Res->Points);
    delete P;
    }
else if (Kind==dk67)  //Трещины
    {
    TRoadPoint Rp[4];
    Rp[0].X=Road->RightLine.FindX(L1);
    Rp[0].L=L1;
    Rp[1].X=Road->LeftLine.FindX(L2);
    Rp[1].L=L2;

    Res=new TExtPolyline(2,1);
    Res->Codes[0]=0;
    Road->ConvertPointsArray(2,Rp,Res->Points);
    }
if (Res)
    if (Placement==rsLeft)
        Res->DirectionVal=-1;
return Res;
}

bool __fastcall TDescreetDirRoadObject::SetDefaultPlacement(TRoad* Road,TPolyline *p) {
if (p && p->Count>0) {
   __int32 cx=p->Points[0].X;
   if (FDirection!=roDirect && FDirection!=roUnDirect)
      FDirection= cx<0 ? roUnDirect : roDirect;
   if (FDirection==roDirect)
      FDX=cx-Road->RightLine.FindX(L);
   else
      FDX=Road->LeftLine.FindX(L)-cx;
    return true;
}
return false;
}

TPolyline* __fastcall TDescreetDirRoadObject::GetDefaultPlacement(TRoad* Road) {
   TPolyline *p=new TPolyline(1);
   p->Points[0].L=FL;
   if (FDirection==roDirect)
    p->Points[0].X=Road->RightLine.FindX(L)+FDX;
   else
    p->Points[0].X=Road->LeftLine.FindX(L)-FDX;
   p->Points[0].BasePar1=FL;
   p->Points[0].BasePar2=p->Points[0].X;
   p->Points[0].Code=0;
    return p;
}

TExtPolyline* __fastcall TDescreetDirRoadObject::GetDefMetric(TRoad *Road)
{
__int32 cx;
if (FDirection==roDirect)
    cx=Road->RightLine.FindX(L)+FDX;
else
    cx=Road->LeftLine.FindX(L)-FDX;
TExtPolyline *Res=new TExtPolyline(1,0);
int x,y;
Road->ConvertPoint(FL,cx,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
return Res;
}

bool __fastcall TRoadSign::SetDefaultPlacement(TRoad* Road,TPolyline *p) {
if (p && p->Count>0) {
   FL=p->Points[0].L;
   __int32 kx,cx=p->Points[0].X;
   if (Direction!=roDirect && Direction!=roUnDirect)
       FDirection=(cx>=0? roDirect : roUnDirect);
   if (cx>=0)
      kx=Road->RightLine.FindX(L);
   else
      kx=Road->LeftLine.FindX(L);
   if (Placement!=spLeft && Placement!=spRight && Placement!=spBetween && Placement!=spUp) {
      if (fabs(kx)>fabs(cx))
         FPlacement=spUp;
      else
         FPlacement=spRight;
   }
   if (Placement!=spLeft && Placement !=spRight)
       FDX=cx;
   else {
       bool b=Placement==spRight;
       if (Direction==roUnDirect)
          b=!b;
       if (b)
          FDX=cx-Road->RightLine.FindX(L);
       else
          FDX=Road->LeftLine.FindX(L)-cx;
   }
   return true;
}
return false;
}

TPolyline* __fastcall TRoadSign::GetDefaultPlacement(TRoad* Road) {
__int32 cx;
if ((Placement!=spLeft)&&(Placement!=spRight))
    cx=FDX;
else
    {
    bool b=Placement==spRight;
    if (Direction==roUnDirect)
        b=!b;
    if (b)
        cx=Road->RightLine.FindX(L)+FDX;
    else
        cx=Road->LeftLine.FindX(L)-FDX;
    }
TPolyline *pl=new TPolyline(1);
pl->Points[0].BasePar1=pl->Points[0].L=FL;
pl->Points[0].BasePar2=pl->Points[0].X=cx;
pl->Points[0].Code=0;
return pl;
}

TExtPolyline* __fastcall TRoadSign::GetDefMetric(TRoad *Road)
{
__int32 cx;
if ((Placement!=spLeft)&&(Placement!=spRight))
    cx=FDX;
else
    {
    bool b=Placement==spRight;
    if (Direction==roUnDirect)
        b=!b;
    if (b)
        cx=Road->RightLine.FindX(L)+FDX;
    else
        cx=Road->LeftLine.FindX(L)-FDX;
    }
if (cx<Road->XMin)
        cx=Road->XMin;
if (cx>Road->XMax)
        cx=Road->XMax;
TExtPolyline *Res=new TExtPolyline(1,0);
int x,y;
Road->ConvertPoint(FL,cx,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
return Res;
}

TExtPolyline* __fastcall TSquareCenterObject::GetDefMetric(TRoad *Road)
{
TPolyline Rp(4);
int L1=LMin>Road->LMin ? LMin : Road->LMin;
int L2=LMax<Road->LMax ? LMax : Road->LMax;
int X=FWidth>>1;
Rp.Points[0].L=L1;
Rp.Points[0].X=X;
Rp.Points[0].Code=1;
Rp.Points[1].L=L2;
Rp.Points[1].X=X;
Rp.Points[1].Code=1;
Rp.Points[2].L=L2;
Rp.Points[2].X=-X;
Rp.Points[2].Code=1;
Rp.Points[3].L=L1;
Rp.Points[3].X=-X;
Rp.Points[3].Code=1;
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(Rp,*Res);
return Res;
}

TExtPolyline* __fastcall TLinearCenterRoadObject::GetDefMetric(TRoad *Road)
{
TPolyline Rp;
int L1=LMin>Road->LMin ? LMin : Road->LMin;
int L2=LMax<Road->LMax ? LMax : Road->LMax;
Rp.Points[0].L=L1;
Rp.Points[0].X=0;
Rp.Points[0].Code=0;
Rp.Points[1].L=L2;
Rp.Points[1].X=0;
Rp.Points[1].Code=1;
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(Rp,*Res);
return Res;
}

TExtPolyline* __fastcall TRoadPart::GetDefMetric(TRoad *Road)
{
int L1,L2;
TPolyline *PL,*PR;
if (LMin>Road->LMin)
    L1=LMin;
else
    L1=Road->LMin;
if (LMax<Road->LMax)
    L2=LMax;
else
    L2=Road->LMax;
PL=new TPolyline;
PR=new TPolyline;
if (FLineBound==4)
    {
    PL->CopyAndCut(&(Road->LeftBound),L1,L2);
    PR->CopyAndCut(&(Road->RightBound),L1,L2);
    }
else if (FLineBound==3)
    {
    PL->CopyAndCut(&(Road->LeftDivPart),L1,L2);
    PR->CopyAndCut(&(Road->RightDivPart),L1,L2);
    }
else if (FLineBound==2)
    {
    PL->CopyAndCut(&(Road->LeftZem),L1,L2);
    PR->CopyAndCut(&(Road->RightZem),L1,L2);
    }
else
    {
    PL->CopyAndCut(&(Road->LeftLine),L1,L2);
    PR->CopyAndCut(&(Road->RightLine),L1,L2);
    }
int n=PL->Count+PR->Count;
TPolyline R(n);
for (int i=0;i<PR->Count;i++)
    R.Points[i]=PR->Points[i],R.Points[i].Code=1;
for (int i=0;i<PL->Count;i++)
    R.Points[n-1-i]=PL->Points[i],R.Points[n-i-1].Code=1;

TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(R,*Res);
delete PL;
delete PR;
return Res;
}

TPolyline* __fastcall TRoadSideObject::GetAttachPoly(TRoad *Road)
    {
    if (FPlacement==opRight)
        if (MetricsKind==mkKromka)
            return &(Road->RightLine);
        else
            return &(Road->RightSide);
    else if (MetricsKind==mkKromka)
        return &(Road->LeftLine);
    else
        return &(Road->LeftSide);
    }

TExtPolyline* __fastcall TLinearRoadSideObject::GetDefMetric(TRoad *Road)
{
__int32 L1,L2;
__int32 dx;
TPolyline *pl;
TExtPolyline *Res;

pl=new TPolyline;
L1=max(LMin,Road->LMin);
L2=min(LMax,Road->LMax);
if (FPlacement==opRight)
    dx=FDX;
else
    dx=-FDX;
pl->CopyAndCut(GetAttachPoly(Road),L1,L2);
TRoadPoint *p=pl->Points;
int n=pl->Count;
for (__int32 i=0;i<n;i++)
    p[i].X+=dx;
if (FPlacement!=opRight)
    {
    int i,j;
    for (i=0,j=n-1;i<j;i++,j--)
        {
        int t=p[i].X;
        p[i].X=p[j].X;
        p[j].X=t;
        t=p[i].L;
        p[i].L=p[j].L;
        p[j].L=t;
        }
    }
for (int i=0;i<n;i++)
    p[i].X+=dx,p[i].Code=1;
p[0].Code=0;
Res=new TExtPolyline;
Road->ConvertPolyline(*pl,*Res);
delete pl;
if (FPlacement==opLeft)
    Res->DirectionVal=-1;
return Res;
}

TExtPolyline* __fastcall TSquareRoadSideObject::GetPolyMetric(TRoad *Road)
{
TExtPolyline *Res=NULL;
if (FPoly)
    {
    if (FPoly->Count)
        FPoly->Points[0].Code.SetVisible(1);
    Res=TRoadSideObject::GetPolyMetric(Road);
    }
return Res;
/*
TExtPolyline *Res=NULL;
if (FPoly)
    {
    TPolyline *pl=new TPolyline;
    int L1=LMin>Road->LMin? LMin : Road->LMin;
    int L2=LMax<Road->LMax? LMax : Road->LMax;
    pl->CopyAndCut(GetAttachPoly(Road),L1,L2);
    int n=pl->Count+FPoly->Count;
    if (n>2)
        {
        Res=new TExtPolyline(n);
        TExtPolyline *Tmp=new TExtPolyline(FPoly->Count);
        Road->ConvertPoly(pl->Count,pl->Points,Res->Points);
        Road->ConvertPoly(FPoly->Count,FPoly->Points,Tmp->Points);
        for (int i=0;i<FPoly->Count;i++)
            Res->Points[pl->Count+i]=Tmp->Points[Tmp->Count-1-i];

        for (int i=0;i<pl->Count;i++)
            Res->Codes[i]=pl->Points[i].Code.VisCon();
        for (int i=0;i<Tmp->Count;i++)
            Res->Codes[pl->Count+i]=FPoly->Points[FPoly->Count-1-i].Code.VisCon();
        }
    }
return Res;
*/
}

TExtPolyline* __fastcall TSquareRoadSideObject::GetDefMetric(TRoad *Road)
{
__int32 L1,L2;
__int32 dx,wid;
TPolyline *pl;
pl=new TPolyline;
if (LMin>Road->LMin)
    L1=LMin;
else
    L1=Road->LMin;
if (LMax<Road->LMax)
    L2=LMax;
else
    L2=Road->LMax;
int drwwid=FWidth ? FWidth : 100;
if (FPlacement==opRight)
    dx=FDX,wid=drwwid;
else
    dx=-FDX,wid=-drwwid;
pl->CopyAndCut(GetAttachPoly(Road),L1,L2);
int n=pl->Count;
TPolyline R(2*n);
for (int i=0;i<n;i++) {
   R.Points[i]=pl->Points[i];
   R.Points[i].X+=dx;
   R.Points[i].Code=1;
   R.Points[2*n-i-1]=pl->Points[i];
   R.Points[2*n-i-1].X+=dx+wid;
   R.Points[2*n-i-1].Code=1;
}
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(R,*Res);
delete pl;
return Res;
}

TExtPolyline* __fastcall TObochina::GetDefMetric(TRoad *Road)
{
TPolyline p1,p2;
__int32 L1,L2;
if (LMin>Road->LMin)
    L1=LMin;
else
    L1=Road->LMin;
if (LMax<Road->LMax)
    L2=LMax;
else
    L2=Road->LMax;
if (FPlacement==opRight)
    {
    p1.CopyAndCut(&(Road->RightLine),L1,L2);
    p2.CopyAndCut(&(Road->RightSide),L1,L2);
    }
else
    {
    p1.CopyAndCut(&(Road->LeftLine),L1,L2);
    p2.CopyAndCut(&(Road->LeftSide),L1,L2);
    }
int n=p1.Count+p2.Count;
TPolyline R(n);
for (int i=0;i<p1.Count;i++)
    R.Points[i]=p1.Points[i],R.Points[i].Code=1;
for (int i=0;i<p2.Count;i++)
    R.Points[n-1-i]=p2.Points[i],R.Points[n-i-1].Code=1;

TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(R,*Res);

if (FPlacement==opLeft)
    Res->DirectionVal=-1;
return Res;
}



TPlanLabel* __fastcall TRoadMark::GetText(int n,TRoad *Road,TDictSource *Dict)
{
TPlanLabel *l=NULL;
int L1=FL<Road->LMin ? Road->LMin:FL;
int L2=FLMax>Road->LMax ? Road->LMax:FLMax;
if (n==0)   // Рисуем код разметки
    {
    __int32 L,A=0;
    L=(L1+L2)>>1;
    if (FPoly)
        if (FPoly->Count)
            {
            A=FPoly->FindX(L);
            }
    if (!A)
        {
        if (Direction==roDirect)
            A=Road->RightLine.FindX(L)*FK/1000+FOffset;
        else
            A=Road->LeftLine.FindX(L)*FK/1000-FOffset;
        }
    TVertAlign va=aBottom;
    if ((Direction==roDirect)&&((FKind==ma21)||(FKind==ma22)))
        va=aTop;
    int x,y;
    Road->ConvertPoint(L,A,x,y);
    l=new TPlanLabel(0,Dict->GetShortTitle(Kind));
    l->SetMetric(x,y,0,0);
    l->SetAlign(aCenter,va,oAway,skByL);
    l->SetSize(8);
    }
else if (n==1) // Рисуем текст позиции начала разметки
    {
    int x,y;
    __int32 A;
    THorzAlign ha;
    bool outbnd=false;
    if (L1>Road->LMin)
        {
        if (MarkLongLines.Elem(Kind))
            outbnd=true;
        if (MarkCrossLines.Elem(Kind))
            outbnd=true;
        else if (MarkArrows.Elem(Kind)&&(Direction==roDirect))
            outbnd=true;
        }
    if ((outbnd)&&(Poly)) // Если есть точки
        {
        if (Poly->Count)
            {       // Ищем точку с мин координатой и если она далее 1 метра от края то текст не выводим
            int MinL=Poly->Points[0].L;
            int MinInd=0;
            for (int i=1;i<Poly->Count;i++)
                if (MinL>Poly->Points[i].L)
                    {
                    MinL=Poly->Points[i].L;
                    MinInd=i;
                    }
            int RX;
            if (Direction==roUnDirect)
                RX=Road->LeftLine.FindX(L);
            else
                RX=Road->RightLine.FindX(L);
            int X=Poly->Points[MinInd].X;
            if (abs(X)>abs(RX)+100)
                outbnd=false;
            }
        }
    if (outbnd)
        {
        if (Direction==roDirect)
            ha=aRight,A=Road->XMax-100;
        else
            ha=aLeft,A=Road->XMin+100;
        L1=(L1/100)*100;
        Road->ConvertPoint(L1,A,x,y);
        l=new TPlanLabel(0,FormatPlacement(L1));
        l->SetMetric(x,y,0,0);
        l->SetAlign(ha,aBaseline,oOrto,skByL);
        l->SetSize(8);
        }
    }
else if (n==2)
    {
    int x,y;
    __int32 A;
    THorzAlign ha;
    bool outbnd=false;
    if (L2<Road->LMax)
        {
        if (MarkLongLines.Elem(Kind))
            outbnd=true;
        else if (MarkArrows.Elem(Kind)&&(Direction==roUnDirect))
            outbnd=true;
        }
    if ((outbnd)&&(Poly)) // Если есть точки
        {
        if (Poly->Count)
            {       // Ищем точку с макс координатой и если она далее 1 метра от края то текст не выводим
            int MaxL=Poly->Points[0].L;
            int MaxInd=0;
            for (int i=1;i<Poly->Count;i++)
                if (MaxL<Poly->Points[i].L)
                    {
                    MaxL=Poly->Points[i].L;
                    MaxInd=i;
                    }
            int RX;
            if (Direction==roUnDirect)
                RX=Road->LeftLine.FindX(L);
            else
                RX=Road->RightLine.FindX(L);
            int X=Poly->Points[MaxInd].X;
            if (abs(X)>abs(RX)+100)
                outbnd=false;
            }
        }
    if (outbnd)
        {
        if (Direction==roDirect)
            ha=aRight,A=Road->XMax-100;
        else
            ha=aLeft,A=Road->XMin+100;
        L2=(L2/100)*100;
        Road->ConvertPoint(L2,A,x,y);
        l=new TPlanLabel(0,FormatPlacement(L2));
        l->SetMetric(x,y,0,0);
        l->SetAlign(ha,aBaseline,oOrto,skByL);
        l->SetSize(8);
        }
    }
return l;
}

TExtPolyline* __fastcall TRoadMark::GetDefMetric(TRoad *Road)
{
__int32 L1,L2;
__int32 offs;
TPolyline *pl=new TPolyline;
if (LMin>Road->LMin)
    L1=LMin;
else
    L1=Road->LMin;
if (LMax<Road->LMax)
    L2=LMax;
else
    L2=Road->LMax;
if (FDirection==roDirect)
    {
    offs=FOffset;
    pl->CopyAndCut(&(Road->RightLine),L1,L2);
    }
else
    {
    pl->CopyAndCut(&(Road->LeftLine),L1,L2);
    offs=-FOffset;
    }
TRoadPoint *p=pl->Points;
int n=pl->Count;
for (__int32 i=0;i<n;i++)
    p[i].X=(p[i].X*FK)/1000+offs,p[i].Code=1;
p[0].Code=0;
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(*pl,*Res);
if (FDirection==roUnDirect)
    {
    int i,j=Res->Count;
    for (i=0,j=Res->Count-1;i<j;i++,j--)
        {
        POINT tmp=Res->Points[i];
        Res->Points[i]=Res->Points[j];
        Res->Points[j]=tmp;
        }
    }
delete pl;
return Res;
}

int __fastcall TRoadAttach::DefaultWidth(void)
{
int Res;
switch (FTech)
    {
    case rc1a:Res=2000;break;
    case rc1:Res=1800;break;
    case rc1b:Res=1600;break;
    case rc2:Res=1400;break;
    case rc3:Res=1200;break;
    case rc4:Res=1000;break;
    case rc5:Res=800;break;
    default: Res=600;
    }
return Res;
}

TExtPolyline* __fastcall TRoadAttach::GetDefMetric(TRoad *Road)
{
int Wid=FWidth;
if (Wid==0)
    Wid=DefaultWidth();
TRoadPoint Rp[4];
Rp[1].L=Rp[0].L=L-(Wid>>1);
Rp[2].L=Rp[3].L=L+(Wid>>1);
if (Placement==apLeft)
    {
    Rp[0].X=Road->LeftLine.FindX(Rp[0].L);
    Rp[3].X=Road->LeftLine.FindX(Rp[3].L);;
    Rp[1].X=Rp[2].X=Road->XMin;
    }
else if (Placement==apRight)
    {
    Rp[0].X=Rp[3].X=Road->XMax;
    Rp[1].X=Road->RightLine.FindX(Rp[1].L);
    Rp[2].X=Road->RightLine.FindX(Rp[2].L);;
    }
else
    {
    Rp[0].X=Rp[3].X=Road->XMin;
    Rp[1].X=Rp[2].X=Road->XMax;
    }
TExtPolyline *Res=new TExtPolyline(4,1);
Res->Codes[0]=0;
Res->Codes[2]=0;
Road->ConvertPointsArray(4,Rp,Res->Points);
return Res;
}

TPlanLabel* __fastcall TRoadAttach::GetText(int n,TRoad *Road,TDictSource *Dict)
{
TPlanLabel *l=NULL;
THorzAlign al;
TRoadPoint p;
p.L=L;
if (Road->PlDirect==pdUndirect)
    al=Placement==apLeft ? aLeft : aRight;
else
    al=Placement==apRight ? aLeft : aRight;
if (n==0)
        {
        l=new TPlanLabel(0,Name);
        p.X=Placement==apLeft? Road->LeftLine.FindX(L)-500 : Road->RightLine.FindX(L)+500;
        int x,y;
        Road->ConvertPoint(p.L,p.X,x,y);
        l->SetMetric(x,y,0,0);
        l->SetAlign(al,aBottom,oOrto,skByL);
        l->SetSize(8);
        }
else if (n==1)
    {
    l=new TPlanLabel(0,FormatPlacement(L));
    TRoadPoint p;
    p.L=L;
    p.X=Placement==apLeft ? Road->XMin-100: Road->XMax+100;
    int x,y;
    Road->ConvertPoint(p.L,p.X,x,y);
    l->SetMetric(x,y,0,0);
    l->SetSize(8);
    l->SetAlign(al,aBaseline,oOrto,skByL);
    }
return l;
}

TPlanLabel* __fastcall TTown::GetText(int n,TRoad *Road,TDictSource *Dict)
{
__int32 L1,L2;
if (LMin>Road->LMin)
    L1=LMin;
else
    L1=Road->LMin;
if (LMax<Road->LMax)
    L2=LMax;
else
    L2=Road->LMax;
int x,y;
Road->ConvertPoint((L1+L2)>>1,(Road->XMin*4)/5,x,y);
TPlanLabel *l=new TPlanLabel(0,Title);
l->SetMetric(x,y,0,0);
l->SetAlign(aCenter,aBottom,oAway,skByL);
l->SetSize(16);
return l;
}

TExtPolyline* __fastcall TRoadAttach::GetPolyMetric(TRoad* Road)
{
TExtPolyline *Res=NULL;
if (FPoly)
    if (FPoly->Count>2)
        Res=TRoadObject::GetPolyMetric(Road);
return Res;
}

TExtPolyline* __fastcall TRoadOut::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[4];
Rp[1].L=Rp[0].L=L-(Width>>1);
Rp[2].L=Rp[3].L=L+(Width>>1);
int l;
if (FLength>100)
    l=FLength;
else if (Wildness==awWild)
    l=500;
else
    l=0;
if ((Surface==rs233)||(Surface==rs234))
    {
    if (Placement==apLeft)
        {
        Rp[0].X=Rp[3].X=Road->LeftLine.FindX(L);
        if (l)
            Rp[1].X=Rp[2].X=-l+Road->LeftLine.FindX(L);
        else
            Rp[1].X=Rp[2].X=Road->XMin;
        }
    else
        {
        Rp[1].X=Rp[2].X=Road->RightLine.FindX(L);
        if (l)
            Rp[0].X=Rp[3].X=l+Road->RightLine.FindX(L);
        else
            Rp[0].X=Rp[3].X=Road->XMax;
        }
    }
else
    {
    if (Placement==apLeft)
        {
        Rp[0].X=Rp[3].X=Road->LeftSide.FindX(L);
        if (l)
            Rp[1].X=Rp[2].X=-l+Road->LeftSide.FindX(L);
        else
            Rp[1].X=Rp[2].X=Road->XMin;
        }
    else
        {
        Rp[1].X=Rp[2].X=Road->RightSide.FindX(L);
        if (l)
            Rp[0].X=Rp[3].X=l+Road->RightSide.FindX(L);
        else
            Rp[0].X=Rp[3].X=Road->XMax;
        }
    }
TExtPolyline *Res=new TExtPolyline(4,1);
Res->Codes[0]=0;
Res->Codes[2]=0;
Road->ConvertPointsArray(4,Rp,Res->Points);
return Res;
}

TExtPolyline* __fastcall TCommRoadObject::GetDefMetric(TRoad *Road)
{
TPolyline Rp(2);
Rp[1].L=Rp[0].L=L;
Rp[0].Code=0;
Rp[1].Code=1;
Rp[0].X=Road->XMin;
Rp[1].X=Road->XMax;
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(Rp,*Res);
return Res;
}

TExtPolyline* __fastcall TRoadObstacle::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[16];
Rp[0].X=Rp[15].X=Road->XMin;
Rp[3].X=Road->LeftSide.FindX(L-Width/4);
Rp[4].X=Road->RightSide.FindX(L-Width/4);
Rp[7].X=Rp[8].X=Road->XMax;
Rp[11].X=Road->RightSide.FindX(L+Width/4);
Rp[12].X=Road->LeftSide.FindX(L+Width/4);

Rp[0].L=Rp[3].L=Rp[4].L=Rp[7].L=L-Width/4;
Rp[8].L=Rp[11].L=Rp[12].L=Rp[15].L=L+Width/4;

Rp[1].X=Rp[2].X=Rp[13].X=Rp[14].X=Road->XMin/2;
Rp[5].X=Rp[6].X=Rp[9].X=Rp[10].X=Road->XMax/2;

Rp[1].L=Rp[13].L=Rp[5].L=Rp[9].L=L;
Rp[2].L=Rp[6].L=L-Width/2;
Rp[10].L=Rp[14].L=L+Width/2;

TExtPolyline *Res=new TExtPolyline(16,0);
Res->Codes[2]=5;
Res->Codes[6]=5;
Res->Codes[10]=5;
Res->Codes[14]=5;
Road->ConvertPointsArray(16,Rp,Res->Points);
return Res;
}

TExtPolyline* __fastcall TDescreetSideRoadObject::GetDefMetric(TRoad *Road)
{
__int32 cx;
if (FPlacement==rsRight)
    cx=Road->RightLine.FindX(L)+FDX;
else
    cx=Road->LeftLine.FindX(L)-FDX;
TExtPolyline *Res=new TExtPolyline(1,0);
int x,y;
Road->ConvertPoint(FL,cx,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
return Res;
}

TPolyline* __fastcall TDescreetSideRoadObject::GetDefaultPlacement(TRoad* Road) {
   TPolyline *p=new TPolyline(1);
   p->Points[0].L=FL;
   if (FPlacement==rsRight)
    p->Points[0].X=Road->RightLine.FindX(L)+FDX;
   else
    p->Points[0].X=Road->LeftLine.FindX(L)-FDX;
   p->Points[0].BasePar1=FL;
   p->Points[0].BasePar2=p->Points[0].X;
   p->Points[0].Code=0;
    return p;
}

bool __fastcall TDescreetSideRoadObject::SetDefaultPlacement(TRoad* Road,TPolyline *p) {
if (p && p->Count>0) {
   __int32 cx=p->Points[0].X;
   if (FPlacement!=rsLeft && FPlacement!=rsRight)
       FPlacement= cx<0 ? rsLeft : rsRight;
   if (FPlacement==rsRight)
      FDX=cx-Road->RightLine.FindX(L);
   else
      FDX=Road->LeftLine.FindX(L)-cx;
   return true;
}
return false;
}

TExtPolyline* __fastcall TDescreetCenterRoadObject::GetDefMetric(TRoad *Road)
{
TExtPolyline *Res=new TExtPolyline(1,0);
int x,y;
Road->ConvertPoint(FL,FDX,x,y);
Res->Points[0].x=x;
Res->Points[0].y=y;
return Res;
}

TPolyline* __fastcall TDescreetCenterRoadObject::GetDefaultPlacement(TRoad* Road) {
   TPolyline *p=new TPolyline(1);
   p->Points[0].L=FL;
   p->Points[0].X=FDX;
   p->Points[0].BasePar1=FL;
   p->Points[0].BasePar2=FDX;
   p->Points[0].Code=0;
   return p;
}


TExtPolyline* __fastcall TSquareAttachObject::GetDefMetric(TRoad *Road)
{
TPolyline Rp(4);
int lmin=LMin;
if (lmin<Road->LMin)
    lmin=Road->LMin;
int lmax=LMax;
if (lmax>Road->LMax)
    lmax=Road->LMax;
Rp.Points[0].X=Road->XMin;
Rp.Points[0].L=lmin;
Rp.Points[0].Code=1;
Rp.Points[1].X=Road->XMax;
Rp.Points[1].L=lmin;
Rp.Points[1].Code=1;
Rp.Points[2].X=Road->XMax;
Rp.Points[2].L=lmax;
Rp.Points[2].Code=1;
Rp.Points[3].X=Road->XMin;
Rp.Points[3].L=lmax;
Rp.Points[3].Code=1;
TExtPolyline *Res=new TExtPolyline;
Road->ConvertPolyline(Rp,*Res);
return Res;
}

TExtPolyline* __fastcall TDangerSlope::GetDefMetric(TRoad *Road)
{
return NULL;
//return new TExtPolyline(0,0);
/*
TRoadPoint Rp[4];
if (FPromille<0)
  {
  Rp[0].X=Road->FrameXMin;
  Rp[0].L=LMin;
  Rp[1].X=Road->FrameXMax;
  Rp[1].L=LMin;
  Rp[2].X=Road->FrameXMax;
  Rp[2].L=LMax;
  }
else
  {
  Rp[0].X=Road->FrameXMax;
  Rp[0].L=LMin;
  Rp[1].X=Road->FrameXMin;
  Rp[1].L=LMax;
  Rp[2].X=Road->FrameXMin;
  Rp[2].L=LMax;
  }
TExtPolyline *Res=new TExtPolyline(4,1);
Road->ConvertPoly(4,Rp,Res->Points);
return Res;
*/
}

TExtPolyline* __fastcall TDangerCurve::GetDefMetric(TRoad *Road)
{
TRoadPoint Rp[3];
Rp[0].X=(Road->FrameXMin+Road->FrameXMax)>>1;
Rp[0].L=LMin;
Rp[2].X=(Road->FrameXMin+Road->FrameXMax)>>1;
Rp[2].L=LMax;
Rp[1].L=(LMin+LMax)>>1;
//if (FPromille<0)
//  Rp[1].X=Road->FrameXMin;
//else
  Rp[1].X=Road->FrameXMax;
TExtPolyline *Res=new TExtPolyline(3,1);
Road->ConvertPointsArray(3,Rp,Res->Points);
return Res;
}

TExtPolyline* __fastcall TCarePart::GetDefMetric(TRoad *Road)
{
int L1=LMin>Road->LMin ? LMin: Road->LMin;
int L2=LMax<Road->LMax ? LMax: Road->LMax;
TPolyline *PL,*PR;
PL=new TPolyline;
PR=new TPolyline;
if (FReason==dpBusStop)
    {
    if (FPlacement==rsLeft)
        {
        PL->CopyAndCut(&(Road->LeftLine),L1,L2);
        PR->CopyAndCut(&(Road->LeftLine),L1,L2);
        PL->AddX(-300);
        }
    else
        {
        PL->CopyAndCut(&(Road->RightLine),L1,L2);
        PR->CopyAndCut(&(Road->RightLine),L1,L2);
        PR->AddX(300);
        }
    }
else if (FReason==dpAttach)
    {
    if (FPlacement==rsLeft)
        {
        PR->CopyAndCut(&(Road->LeftLine),L1,L2);
        PL->Count=2;
        PL->Points[0].L=L1;
        PL->Points[0].X=Road->XMin;
        PL->Points[1].L=L2;
        PL->Points[1].X=Road->XMin;
        }
    else
        {
        PL->CopyAndCut(&(Road->RightLine),L1,L2);
        PR->Count=2;
        PR->Points[0].L=L1;
        PR->Points[0].X=Road->XMax;
        PR->Points[1].L=L2;
        PR->Points[1].X=Road->XMax;
        }
    }
else
    {
    PL->CopyAndCut(&(Road->LeftLine),L1,L2);
    PR->CopyAndCut(&(Road->RightLine),L1,L2);
    }
int n=PL->Count+PR->Count;
TExtPolyline *Res=new TExtPolyline(n,1);
// Опасные участки пока не будем изгибать
Road->ConvertPointsArray(PR->Count,PR->Points,Res->Points);
Road->ConvertPointsArray(PL->Count,PL->Points,Res->Points+PR->Count);
__int32 i,j;
for (i=PR->Count,j=n-1;i<j;i++,j--)
    {
    __int32 tmp=Res->Points[i].x;
    Res->Points[i].x=Res->Points[j].x;
    Res->Points[j].x=tmp;
    tmp=Res->Points[i].y;
    Res->Points[i].y=Res->Points[j].y;
    Res->Points[j].y=tmp;
    }
delete PL;
delete PR;
return Res;
}

/*
TExtPolyline* __fastcall TDressLayer::GetDefMetric(TRoad *Road) {
    TRoadPoint Rp[4];
    int dh=Road->FrameXMax-Road->FrameXMin;
    Rp[0].L=LMin;
    Rp[0].X=Road->FrameXMin;
    Rp[1].L=LMin;
    Rp[1].X=Road->FrameXMax;
    Rp[2].L=LMax;
    Rp[2].X=Road->FrameXMax;
    Rp[3].L=LMax;
    Rp[3].X=Road->FrameXMin;
    TExtPolyline *Res=new TExtPolyline(4,1);
    Road->ConvertPoly(4,Rp,Res->Points);
    return Res;
} */

TPlanLabel* __fastcall TCarePart::GetText(int n,TRoad *Road,TDictSource *Dict)
{
String Str="";
int L1=LMin>Road->LMin ? LMin: Road->LMin;
int L2=LMax<Road->LMax ? LMax: Road->LMax;
int LMid=(L1+L2)/2;
int len=(LMax-LMin+50)/100;
Str=String(len)+"*6=";
int ns=FNormaSquare==0 ? len*6 : int(FNormaSquare*1000+0.5);
Str+=String(ns);
if ((FHandlingSquare>0)&&(FHandlingSquare!=ns))
    Str+="("+String((int)(FHandlingSquare*1000))+")";
int color=0;
TPlanLabel *l=new TPlanLabel(0,Str);
int x,y;
TVertAlign val;
if (FReason==dpBusStop)
    {
    if (FPlacement==rsLeft)
        {
        val=aBottom;
        Road->ConvertPoint(LMid,Road->LeftLine.FindX(LMid),x,y);
        }
    else
        {
        val=aTop;
        Road->ConvertPoint(LMid,Road->RightLine.FindX(LMid),x,y);
        }
    }
else if (FReason==dpAttach)
    {
    if (FPlacement==rsLeft)
        {val=aBottom;
        Road->ConvertPoint(LMid,Road->LeftLine.FindX(LMid)+100,x,y);
        }
    else
        {
        val=aTop;
        Road->ConvertPoint(LMid,Road->RightLine.FindX(LMid)-100,x,y);
        }
    }
else
    {
    val=aBaseline;
    Road->ConvertPoint((LMin+LMax)/2,0,x,y);
    }
l->SetMetric(x,y,0,0);
l->SetAlign(aCenter,val,oAway,skByL);
l->SetSize(12);
l->SetColor(color);
return l;
}

TExtPolyline* __fastcall TRoadBridge::GetDefMetric(TRoad *Road)
{
int lmin=LMin;
if (lmin<Road->LMin)
        lmin=Road->LMin;
int lmax=LMax;
if (lmax>Road->LMax)
        lmax=Road->LMax;
TRoadPoint Rp[4];
Rp[0].L=lmin;
Rp[1].L=lmax;
Rp[2].L=lmax;
Rp[3].L=lmin;
if (FWidth>0)
  {
  Rp[0].X=FWidth>>1;
  Rp[1].X=FWidth>>1;
  Rp[2].X=-(FWidth>>1);
  Rp[3].X=-(FWidth>>1);
  }
else
    {
    Rp[0].X=Road->RightLine.FindX(lmin);
    Rp[1].X=Road->RightLine.FindX(lmax);
    Rp[2].X=Road->LeftLine.FindX(lmax);
    Rp[3].X=Road->LeftLine.FindX(lmin);
    }
TExtPolyline *Res=new TExtPolyline(4,1);
Res->Codes[0]=0;
Res->Codes[2]=0;
// Бывают ли изогнутые мосты?
Road->ConvertPointsArray(4,Rp,Res->Points);
return Res;
}

TPlanLabel* __fastcall TRoadBridge::GetText(int n,TRoad *Road,TDictSource *Dict)
{
String Str="";
int color=0;
switch (ObstacleKind)
    {
    case ok95:
        {color=clBlue;
        if (ObstacleName!="")
            Str=ObstacleName.c_str();
        else
            Str="Ручей";
        }break;
    case ok96:Str="Суходол ";break;
    case ok97:Str="Железная дорога ";break;
    case ok98:Str="Автодорога ";break;
    case ok99:Str="Плотина ";break;
    case ok100:Str="Путепровод ";break;
    case ok101:{color=clBlue;Str="Канал ";}break;
    case ok102:{color=clBlue;Str="Озеро ";}break;
    default : {Str=ObstacleName.c_str();}
    }
TPlanLabel *l=new TPlanLabel(0,Str);
int x,y;
Road->ConvertPoint((LMin+LMax)/2,Road->RightSide.FindX(LMax)+400,x,y);
l->SetMetric(x,y,0,0);
l->SetAlign(aLeft,aBottom,oOrto,skByL);
l->SetSize(12);
l->SetColor(color);
return l;
}

__fastcall TRoad::TRoad(TRoad* Rd,__int32 L1,__int32 L2)
    : TBandRoadObject(Rd->Id,Rd->DictId)
{

FL=L1;
FLMax=L2;
FZMin=Rd->ZMin;
FZMax=Rd->ZMax;

FConvertMethod=Rd->FConvertMethod;

FDrwClassId=Rd->DrwClassId;
LeftLine.CopyAndCut(&(Rd->LeftLine),L1,L2);
RightLine.CopyAndCut(&(Rd->RightLine),L1,L2);
LeftSide.CopyAndCut(&(Rd->LeftSide),L1,L2);
RightSide.CopyAndCut(&(Rd->RightSide),L1,L2);
LeftZem.CopyAndCut(&(Rd->LeftZem),L1,L2);
RightZem.CopyAndCut(&(Rd->RightZem),L1,L2);
LeftDivPart.CopyAndCut(&(Rd->LeftDivPart),L1,L2);
RightDivPart.CopyAndCut(&(Rd->RightDivPart),L1,L2);
LeftBound.CopyAndCut(&(Rd->LeftBound),L1,L2);
RightBound.CopyAndCut(&(Rd->RightBound),L1,L2);

Geometry.CopyAndCut(&(Rd->Geometry),L1,L2);
CurvePlan.CopyAndCut(&(Rd->CurvePlan),L1,L2);

FXMin=Rd->XMin;
FXMax=Rd->XMax;
}

void __fastcall TRoad::SetBound(__int32 minl,__int32 maxl,__int32 minx,__int32 maxx)
{
FL=minl;
FLMax=maxl;
FXMin=minx;
FXMax=maxx;
}

void __fastcall TRoad::SetFrame(__int32 lmin,__int32 lmax,__int32 xmin,__int32 xmax,TPlanKind pk,TPlanDirect pd)
{
FPlKind=pk;
FPlDirect=pd;
FFrameLMin=lmin;
FFrameLMax=lmax;
FFrameXMin=xmin;
FFrameXMax=xmax;
}

void __fastcall TRoad::CalcConvertion(void)
{
__int32 dx=FFrameXMax-FFrameXMin;
if (!dx)
    dx=1;
__int32 dl=FFrameLMax-FFrameLMin;
if (!dl)
    dl=1;
if (FPlKind==pkGorizontal)
    {
    FKx=(double)(FOutYMax-FOutYMin)/dx;
    FKl=(double)(FOutXMax-FOutXMin)/dl;
    }
else
    {
    FKx=(double)(FOutXMax-FOutXMin)/dx;
    FKl=(double)(FOutYMax-FOutYMin)/dl;
    }
/*  Кусок кода для 2D версии
TGeometryVal V1,V2;
int pos1=Geometry.GetMesValue(FFrameLMin,V1);
int pos2=Geometry.GetMesValue(FFrameLMax,V2);
FGeoXMin=FGeoXMax=V1.X;
FGeoYMin=FGeoYMax=V1.Y;
if (FGeoXMin>V2.X)
    FGeoXMin=V2.X;
if (FGeoXMax<V2.X)
    FGeoXMax=V2.X;
if (FGeoYMin>V2.Y)
    FGeoYMin=V2.Y;
if (FGeoYMax<V2.Y)
    FGeoYMax=V2.Y;
pos1++;
TGeometryVal *Values=Geometry.Values;
while (pos1<=pos2)
    {
    int VX=Values[pos1].X;
    int VY=Values[pos1].Y;
    if (FGeoXMin>VX)
        FGeoXMin=VX;
    if (FGeoXMax<VX)
        FGeoXMax=VX;
    if (FGeoYMin>VY)
        FGeoYMin=VY;
    if (FGeoYMax<VY)
        FGeoYMax=VY;
    pos1++;
    }
*/
}

void __fastcall TRoad::SetOutBound(__int32 minx,__int32 maxx,__int32 miny,__int32 maxy)
{
FOutXMin=minx;
FOutXMax=maxx;
FOutYMin=miny;
FOutYMax=maxy;
CalcConvertion();
}

// Функция изменяет координаты точки которая двигается по дуге
// с изменяющимся радиусом кривизны от BR1 до BR2
inline void Calc2D(double &X,double &Y, double &A,double L,double BR1,double BR2) {
  if (fabs(L)<0.01) return;
  if (BR1==BR2) {// Дуга или прямая
     if (BR1==0) // Прямая
        X+=L*cos(A),Y+=L*sin(A);
     else {
        BR1/=100;
        double DA=L*BR1;//Изменение угла
        double DY=(1-cos(DA))/BR1; //Приращение при угле в 0 градусов
        double DX=sin(DA)/BR1;
        X+=cos(A)*DX-sin(A)*DY;
        Y+=+sin(A)*DX+cos(A)*DY;
        A+=DA;
     }
  } else {
      double c=(BR2-BR1)/L; // Центробежное ускорение
  }
}

void __fastcall TRoad::ConvertPoint(__int32 L,__int32 X,__int32 &PX,__int32 &PY)
{
if (FConvertMethod==pc2d) {
    int k;
    for (k=0;FrameLMin>CurvePlan.L[k];++k); // Ищем участок плана где начинается окно
    double CX=0,CY=0,CA=0; // Координаты в системе карты повернутые
    double PL;
    TCurvePoint CR(0.0);
    if (k==0) {// FrameLMin<=L[0] {
        Calc2D(CX,CY,CA,CurvePlan.L[0]-FrameLMin,0.0,0.0);
        k=1;
        PL=CurvePlan.L[0];
        CR=CurvePlan.Values[0];
    } else {   //FrameLMin<=L[k],k>0
        CR.Extrapolate(CurvePlan.Values[k-1],CurvePlan.Values[k],FrameLMin,CurvePlan.L[k-1],CurvePlan.L[k]);
        PL=FrameLMin;
    }
    for (;k<CurvePlan.Count && L>CurvePlan.L[k];k++) {
        Calc2D(CX,CY,CA,CurvePlan.L[k]-PL,CR.bR,CurvePlan.Values[k].bR);
        CR=CurvePlan.Values[k];
        PL=CurvePlan.L[k];
    }
    if (k<CurvePlan.Count) { // L<=CurvePlan.L[k] && k>0
        TCurvePoint TR;
        TR.Extrapolate(CurvePlan.Values[k-1],CurvePlan.Values[k],LMin,CurvePlan.L[k-1],CurvePlan.L[k]);
        Calc2D(CX,CY,CA,L-PL,CR.bR,TR.bR);
        TR.bR=0;
    } else //ТОчка после окончания плана
        Calc2D(CX,CY,CA,L-PL,0,0);
    CX-=X*sin(CA);
    CY+=X*cos(CA);
    PX=FOutXMin+(CX)*FKl;
    PY=FOutYMin+(CY-FFrameXMin)*FKx;//FKx; Масштаб всегда одинаковый
}
else {
if (FPlKind==pkGorizontal)
    {
    if (FPlDirect==pdDirect)
        {
        PX=FOutXMin+(L-FFrameLMin)*FKl;
        PY=FOutYMin+(X-FFrameXMin)*FKx;
        }
    else
        {
        PX=FOutXMax-(L-FFrameLMin)*FKl;
        PY=FOutYMax-(X-FFrameXMin)*FKx;
        }
    }
else
    {
    if (FPlDirect==pdDirect)
        {
        PY=FOutYMax-(L-FFrameLMin)*FKl;
        PX=FOutXMin+(X-FFrameXMin)*FKx;
        }
    else
        {
        PY=FOutYMin+(L-FFrameLMin)*FKl;
        PX=FOutXMax-(X-FFrameXMin)*FKx;
        }
    }
    }
}

void __fastcall TRoad::CalcPointsInterval(TPolyline *Poly,int head,int tale,TRoadObject *RefObj)
{
int n=Poly->Count;
while (head!=tale)
    {
    if (!(*Poly)[tale].Code.DependPred())
        {
        CalcPointPos(Poly,tale,RefObj);
        tale=(tale+n-1)%n;
        }
    else
        {
        CalcPointPos(Poly,head,RefObj);
        head=(head+1)%n;
        }
    }
CalcPointPos(Poly,head,RefObj);
}

void __fastcall TRoad::CalcPointsPos(TPolyline *Poly,TRoadObject *RefObj)
{
int i;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
for (i=0;i<n;i++)
    if (p[i].Code.Undepended())
        break;
if (i==n) // ошибка. все точки зависят друг от друга
    for (i=0;i<n;i++)
        CalcPointPos(Poly,i,RefObj);
else      // i - Номер первой независимой точки
    {
    CalcPointPos(Poly,i,RefObj);
    int j=i+1;
    int pred=j%n;  // теперь pred номер точки следующей за независимой
    while (j<n)
        {
        for (;j<n;j++)
            if (p[j].Code.Undepended())
                break;
        if (j<n)   // Теперь j номер следующей независимой точки
            {
            CalcPointPos(Poly,j,RefObj);
            if (j>pred+1)  // Если есть интервал
                CalcPointsInterval(Poly,pred,j-1,RefObj);
            j++;
            pred=j%n;
            }
        else  if (i>0 || pred>0 )  // Если есть последний интервал
            CalcPointsInterval(Poly,pred,(i+n-1)%n,RefObj);
        }
    }
RefObj->UpdatePoly();
}

void __fastcall TRoad::CalcPointPos(TPolyline *Poly, int i,TRoadObject *RefObj)
{
__int32 BaseL,BaseX;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
TPointCode Code=p[i].Code;
//GetBase(Poly,i,RefObj,BaseL,BaseX);
GetBaseL(Poly,i,RefObj,BaseL);
if (Code.Polar())
    {
    double angle=(p[i].BasePar1*M_PI)/180000;
    double sina=sin(angle);
    double cosa=cos(angle);
    p[i].L=BaseL+cosa*p[i].BasePar2;
    GetBaseX(Poly,i,RefObj,p[i].L,BaseX);
    p[i].X=BaseX+sina*p[i].BasePar2;
    }
else
    {
    p[i].L=BaseL+p[i].BasePar1;
    GetBaseX(Poly,i,RefObj,p[i].L,BaseX);    
    p[i].X=BaseX+p[i].BasePar2;
    }
int leep=Code.Leep();
if (leep>0)
    {
    if ((Code.BaseFixed1()==0)&&(Code.BaseFixed2()==0))
        {
        switch (leep)
            {
            case 1: p[i].X=RightSide.FindX(p[i].L)+p[i].LeepPar;break;
            case 2: p[i].X=LeftSide.FindX(p[i].L)+p[i].LeepPar;break;
            case 3: p[i].X=RightLine.FindX(p[i].L)+p[i].LeepPar;break;
            case 4: p[i].X=LeftLine.FindX(p[i].L)+p[i].LeepPar;break;
            case 5: p[i].X=XMax+p[i].LeepPar;break;
            case 6: p[i].X=XMin+p[i].LeepPar;break;
            case 7:
                {
                int pred=(i+n-1)%n;
                p[i].LeepToLine(p[pred].L,p[pred].X,(p[i].LeepPar*M_PI)/180000);
                break;
                }
            case 8:
                {
                int next=(i+1)%n;
                p[i].LeepToLine(p[next].L,p[next].X,(p[i].LeepPar*M_PI)/180000);
                }
            }
        }
    else if ((Code.BaseFixed1()==1)&&(Code.BaseFixed2()==0))
        {
        if (Code.Polar())
            {
            switch (leep)
                {
                case 1:p[i].LeepToPolyline(BaseL,BaseX,p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,&RightSide);break;
                case 2:p[i].LeepToPolyline(BaseL,BaseX,p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,&LeftSide);break;
                case 3:p[i].LeepToPolyline(BaseL,BaseX,p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,&RightLine);break;
                case 4:p[i].LeepToPolyline(BaseL,BaseX,p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,&LeftLine);break;
                case 5:p[i].CrossPoint(BaseL,BaseX,p[i].L,XMax+p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,0); break;
                case 6:p[i].CrossPoint(BaseL,BaseX,p[i].L,XMin+p[i].LeepPar,(p[i].BasePar1*M_PI)/180000,0); break;
                case 7:
                    {
                    int pred=(i+n-1)%n;
                    p[i].CrossPoint(BaseL,BaseX,p[pred].L,p[pred].X,(p[i].BasePar1*M_PI)/180000,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                case 8:
                    {
                    int next=(i+1)%n;
                    p[i].CrossPoint(BaseL,BaseX,p[next].L,p[next].X,(p[i].BasePar1*M_PI)/180000,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                }
            }
        else
            {
            switch (leep)
                {
                case 1: p[i].X=RightSide.FindX(p[i].L)+p[i].LeepPar;break;
                case 2: p[i].X=LeftSide.FindX(p[i].L)+p[i].LeepPar;break;
                case 3: p[i].X=RightLine.FindX(p[i].L)+p[i].LeepPar;break;
                case 4: p[i].X=LeftLine.FindX(p[i].L)+p[i].LeepPar;break;
                case 5: p[i].X=XMax+p[i].LeepPar;break;
                case 6: p[i].X=XMin+p[i].LeepPar;break;
                case 7:
                    {
                    int pred=(i+n-1)%n;
                    p[i].CrossPoint(p[i].L,0,p[pred].L,p[pred].X,M_PI/2.0,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                case 8:
                    {
                    int next=(i+1)%n;
                    p[i].CrossPoint(p[i].L,0,p[next].L,p[next].X,M_PI/2.0,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                }
            }
        }
    else if ((Code.BaseFixed1()==0)&&(Code.BaseFixed2()==1))
        {
        if (Code.Polar())
            {
            }
        else
            {
            switch (leep)
                {
                case 7:
                    {
                    int pred=(i+n-1)%n;
                    p[i].CrossPoint(p[i].L,p[i].X,p[pred].L,p[pred].X,0,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                case 8:
                    {
                    int next=(i+1)%n;
                    p[i].CrossPoint(p[i].L,p[i].X,p[next].L,p[next].X,0,(p[i].LeepPar*M_PI)/180000);
                    break;
                    }
                }
            }
        }
    CalcPointParam(p[i],BaseL,BaseX);
    }
else
    {
    }
}
void __fastcall TRoad::GetBaseL(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 &BaseL) {
    BaseL=0;
    int n=Poly->Count;
    TRoadPoint *p=Poly->Points;
    TPointCode Code=p[i].Code;
    int pred_i=(i+n-1)%n;
    int next_i=(i+1)%n;
    TRoadObject *ParObj=RefObj->Parent;
    if (ParObj==NULL)
        ParObj=RefObj;
    switch (Code.LBase()) {
        case 1: BaseL=RefObj->L; break;
        case 2: BaseL=RefObj->LMax; break;
        case 3: BaseL=p[pred_i].L;break;
        case 4: BaseL=p[next_i].L;break;
        case 5: BaseL=ParObj->L; break;
        case 6: BaseL=ParObj->LMax; break;
    }
}
void __fastcall TRoad::GetBaseX(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 L,__int32 &BaseX)
{
BaseX=0;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
TPointCode Code=p[i].Code;
int pred_i=(i+n-1)%n;
int next_i=(i+1)%n;
TRoadObject *ParObj=RefObj->Parent;
if (ParObj==NULL)
    ParObj=RefObj;
switch (Code.XBase())
    {
    case 1: BaseX=RightSide.FindX(L); break;
    case 2: BaseX=LeftSide.FindX(L); break;
    case 3: BaseX=RightLine.FindX(L); break;
    case 4: BaseX=LeftLine.FindX(L); break;
    case 5: BaseX=XMax;break;
    case 6: BaseX=XMin;break;
    case 7: BaseX=p[pred_i].X;break;
    case 8: BaseX=p[next_i].X;break;
    }
}
/*
void __fastcall TRoad::GetBase(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 &BaseL,__int32 &BaseX)
{
BaseL=0;
BaseX=0;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
TPointCode Code=p[i].Code;
int pred_i=(i+n-1)%n;
int next_i=(i+1)%n;
TRoadObject *ParObj=RefObj->Parent;
if (ParObj==NULL)
    ParObj=RefObj;
switch (Code.LBase())
    {
    case 1: BaseL=RefObj->L; break;
    case 2: BaseL=RefObj->LMax; break;
    case 3: BaseL=p[pred_i].L;break;
    case 4: BaseL=p[next_i].L;break;
    case 5: BaseL=ParObj->L; break;
    case 6: BaseL=ParObj->LMax; break;
    }
switch (Code.XBase())
    {
    case 1: BaseX=RightSide.FindX(BaseL); break;
    case 2: BaseX=LeftSide.FindX(BaseL); break;
    case 3: BaseX=RightLine.FindX(BaseL); break;
    case 4: BaseX=LeftLine.FindX(BaseL); break;
    case 5: BaseX=XMax;break;
    case 6: BaseX=XMin;break;
    case 7: BaseX=p[pred_i].X;break;
    case 8: BaseX=p[next_i].X;break;
    }
}
*/

void __fastcall TRoad::CalcPointParam(TRoadPoint &p,__int32 BaseL,__int32 BaseX)
{
int DL=p.L-BaseL;
int DX=p.X-BaseX;
TPointCode Code=p.Code;
if (Code.Polar())
    {
    if (!p.Code.BaseFixed1())
        {
        double a;
        if (DL>0)
            a=atan((double)DX/DL);
        else if (DL<0)
            a=M_PI-atan(-(double)DX/DL);
        else if (DX>0)
            a=M_PI/2;
        else
            a=-M_PI/2;
        p.BasePar1=(a*180000)/M_PI;
        if (p.BasePar1>180000)
            p.BasePar1-=360000;
        }
    if (!p.Code.BaseFixed2())
        p.BasePar2=sqrt((double)DL*DL+(double)DX*DX)+0.5;
    }
else
    {
    if (!p.Code.BaseFixed1())
        p.BasePar1=DL;
    if (!p.Code.BaseFixed2())
        p.BasePar2=DX;
    }
}

void __fastcall TRoad::SetPointPos(TPolyline *Poly,int i,TRoadObject *RefObj,int &ind1,int &ind2)
{
__int32 BaseL,BaseX;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
//GetBase(Poly,i,RefObj,BaseL,BaseX);
GetBaseL(Poly,i,RefObj,BaseL);
GetBaseX(Poly,i,RefObj,p[i].L,BaseX);
CalcPointParam(p[i],BaseL,BaseX);
CalcPointPos(Poly,i,RefObj);
if (n>1)           // Считаем интервал точек, которые изменятся после изменения текущей точки
    {
    int j=(i+1)%n;
    bool recalcall=false;  // true, если есть круговая зависимость
    while (j!=i)  // сначала идем вперед
        {
        if (p[j].Code.DependPred())
            CalcPointPos(Poly,j,RefObj);
        else
            break;
        j=(j+1)%n;
        }
    if (i==j)
        recalcall=true;
    ind2=(j+n-1)%n;
    j=(i+n-1)%n;
    while (j!=i)
        {
        if (p[j].Code.DependNext())
            CalcPointPos(Poly,j,RefObj);
        else
            break;
        j=(j+n-1)%n;
        }
    if (i==j)
        recalcall=true;
    ind1=(j+1)%n;
    if (recalcall)
        ind1=0,ind2=n-1;
    }
else
    ind1=ind2=0;
}
/*
CalcPointPos(p[i]);
if (n>2)
    {
    int i1,i2;
    int c=p[i].Code.Leep();
    switch (c)
        {
        case 12: i1=(i-1+n)%n,i2=(i+1)%n;break;
        case 13: i1=(i-2+n)%n,i2=(i-1+n)%n;break;
        case 14: i1=(i+1)%n,i2=(i+2)%n;break;
        }
    if (c>=12)
        {
        double A=p[i1].X-p[i2].X;
        double B=p[i2].L-p[i1].L;
        double C=-(p[i1].L*A+p[i1].X*B);
        double D=A*A+B*B;
        double V=A*p[i].L+B*p[i].X+C;
        p[i].L-=((double)A*V)/D;
        p[i].X-=((double)B*V)/D;
        }
    }
}

void __fastcall TRoad::CalcPointPos(TRoadPoint &p)
{
int c=p.Code.Leep();
switch (c)
    {
    case 1: p.X=RightSide.FindX(p.L);break;
    case 2: p.X=LeftSide.FindX(p.L);break;
    case 3: p.X=RightLine.FindX(p.L);break;
    case 4: p.X=LeftLine.FindX(p.L);break;
    case 5: p.X=XMax;break;
    case 6: p.X=XMin;break;
    case 7: p.X=0;break;
    }
}

void __fastcall TRoad::CalcPointsPos(TRoadPoint *p,int n)
{
for (int i=0;i<n;i++)
    {
    CalcPointPos(p,n,i);
    }
}

*/

void __fastcall TRoad::RConvertPoint(__int32 X,__int32 Y,__int32 &PL,__int32 &PX)
{
    if (FPlKind==pkGorizontal)
        {
        if (FPlDirect==pdDirect)
            {
            PL=FFrameLMin+(X-FOutXMin)/FKl;
            PX=FFrameXMin+(Y-FOutYMin)/FKx;
            }
        else
            {
            PL=FFrameLMin+(FOutXMax-X)/FKl;
            PX=FFrameXMin+(FOutYMax-Y)/FKx;
            }
        }
    else
        {
        if (FPlDirect==pdDirect)
            {
            PL=FFrameLMin+(FOutYMax-Y)/FKl;
            PX=FFrameXMin+(X-FOutXMin)/FKx;
            }
        else
            {
            PL=FFrameLMin+(Y-FOutYMin)/FKl;
            PX=FFrameXMin+(FOutXMax-X)/FKx;
            }
        }
}

void __fastcall TRoad::ConvertPolyline(TPolyline &src,TExtPolyline &dst) {
if (FConvertMethod==pc2d) {
    dst.ReSize(0);
    double stepl=100000; // Пока будем ставить точки через 10 метров.
    // Еще в будущем надо учитывать что не все точки соеденены отрезками
    int n=src.Count+src.Points[0].Code.VisCon(); // Для замыкания полигона
    __int32 x,y,k=0;
    dst.ReSize(n+1);
    double CL=src.Points[0].L, CX=src.Points[0].X;
    ConvertPoint(CL,CX,x,y);
    dst.Points[k].x=x;
    dst.Points[k].y=y;
    dst.Codes[k]=src.Points[0].Code.VisCon();
    k=1;
    for (int i=1;i<n;k++) {
       int cind=i%src.Count;
       double dl=src.Points[cind].L-CL;
       double dx=src.Points[cind].X-CX;
       double ds=sqrt(dl*dl+dx*dx);
       if (ds>stepl)  { // Добавляем точку
          CL+=stepl*dl/ds;
          CX+=stepl*dx/ds;
       } else {         // Переходим к следующей точке
          CL=src.Points[cind].L;
          CX=src.Points[cind].X;
          i++;
       }
       dst.ReSize(k+1);
       ConvertPoint(CL,CX,x,y);
       dst.Points[k].x=x;
       dst.Points[k].y=y;
       dst.Codes[k]=src.Points[cind].Code.VisCon();
    }
//    ConvertPointsArray(src.Count,src.Points,dst.Points);
} else {
    __int32 n=src.Count;
    __int32 d=src.Points[0].Code.VisCon();
    dst.ReSize(n+d);
    ConvertPointsArray(src.Count,src.Points,dst.Points);
    for (int i=0;i<n;i++)
       dst.Codes[i]=src.Points[i].Code.VisCon();
    if (d)
       dst.Codes[n]=dst.Codes[0],dst.Points[n]=dst.Points[0];
    }
}

void __fastcall TRoad::ConvertPointsArray(__int32 n, TRoadPoint *in, POINT *out)
{
if (FConvertMethod==pc2d) {
   for (int i=0;i<n;i++) {
      __int32 x,y;
      ConvertPoint(in[i].L,in[i].X,x,y);
      out[i].x=x,out[i].y=y;
   }
} else {
if (FPlKind==pkGorizontal)
    {
    if (FPlDirect==pdDirect)
        for (int i=0;i<n;i++)
            {
            out[i].x=FOutXMin+(in[i].L-FFrameLMin)*FKl;
            out[i].y=FOutYMin+(in[i].X-FFrameXMin)*FKx;
            }
    else
        for (int i=0;i<n;i++)
            {
            out[i].x=FOutXMax-(in[i].L-FFrameLMin)*FKl;
            out[i].y=FOutYMax-(in[i].X-FFrameXMin)*FKx;
            }
    }
else
    {
    if (FPlDirect==pdDirect)
        for (int i=0;i<n;i++)
            {
            out[i].y=FOutYMax-(in[i].L-FFrameLMin)*FKl;
            out[i].x=FOutXMin+(in[i].X-FFrameXMin)*FKx;
            }
    else
        for (int i=0;i<n;i++)
            {
            out[i].y=FOutYMin+(in[i].L-FFrameLMin)*FKl;
            out[i].x=FOutXMax-(in[i].X-FFrameXMin)*FKx;
            }
    }
}
}


TExtPolyline* __fastcall TRoad::GetProfilMetric(TRect &OutRect)
{
int mn,mx;
TGeometryVal *P=Geometry.Values;
__int32 *L=Geometry.L;
int n=Geometry.Count;
TExtPolyline *Res=new TExtPolyline(n+4,0);
POINT *Pt=Res->Points;
int dl,dx,sl,sx;
if (FPlKind==pkGorizontal)
    {
    Pt[0].y=Pt[n+3].y=OutRect.bottom;
    sx=OutRect.bottom+5;
    Pt[1].y=Pt[n+2].y=sx;
    dx=OutRect.top-OutRect.bottom-5;
    if (FPlDirect==pdDirect)
        {
        Pt[0].x=Pt[1].x=OutRect.left;
        Pt[n+2].x=Pt[n+3].x=OutRect.right;
        sl=OutRect.left;
        dl=OutRect.right-OutRect.left;
        }
    else
        {
        Pt[0].x=Pt[1].x=OutRect.right;
        Pt[n+2].x=Pt[n+3].x=OutRect.left;
        sl=OutRect.right;
        dl=OutRect.left-OutRect.right;
        }
    }
else
    {
    Pt[0].x=Pt[n+3].x=OutRect.right;
    dx=OutRect.left-OutRect.right-5;
    sx=OutRect.right-5;
    Pt[1].x=Pt[n+2].x=sx;
    if (FPlDirect==pdDirect)
        {
        Pt[0].y=Pt[1].y=OutRect.bottom;
        Pt[n+2].y=Pt[n+3].y=OutRect.top;
        sl=OutRect.bottom;
        dl=OutRect.top-OutRect.bottom;
        }
    else
        {
        Pt[0].y=Pt[1].y=OutRect.top;
        Pt[n+2].y=Pt[n+3].y=OutRect.bottom;
        sl=OutRect.top;
        dl=OutRect.bottom-OutRect.top;
        }
    }
if (n>0)
    {
    int dz=FZMax-FZMin;
    if (dz==0)
        dz=2;
    int rlen=LMax-LMin;
    int i,j;
    if (FPlKind==pkGorizontal)
        {
        for (i=0,j=2;i<n;i++,j++)
            {
            Pt[j].x=(double)(L[i]-LMin)*dl/rlen+sl;
            Pt[j].y=(double)((P[i].Z-FZMin)*dx)/dz+sx;
            }
        }
    else
        {
        for (i=0,j=2;i<n;i++,j++)
            {
            Pt[j].x=(double)((P[i].Z-FZMin)*dx)/dz+sx;
            Pt[j].y=(double)(L[i]-LMin)*dl/rlen+sl;
            }
        }
    }
return Res;
}
