//---------------------------------------------------------------------------


#pragma hdrstop

#include "DesignPattern.h"
#include "MainUnit.h"
#include "AttachForm.h"
#include <math.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)

TDesignAttachVer1_1 DesignAttachVer1_1;
TDesignAttachVer1_2 DesignAttachVer1_2;
TDesignAttachVer2_1 DesignAttachVer2_1;
TDesignAttachVer2_2 DesignAttachVer2_2;
TDesignAttachVer3 DesignAttachVer3;

TDesignMetricsPattern *MarkDesigners[1]={&DesignAttachVer3};
TDesignMetricsPattern *Designers[4]={&DesignAttachVer1_1,&DesignAttachVer1_2,&DesignAttachVer2_1,&DesignAttachVer2_2};
String DesignersName[4]={"ѕримыкание у кромки","ѕримыкание у бровки","ѕримыкание у кромки и столбики","ѕримыкание у бровки и столбики"};
const int AttachPtCount=12;
const int SignalPointCount=4;
AttachCodes1RK[12]={0x3100,0x3101,0x3101,0x3101,0x3101,0x37351,0x38450,0x3101,0x3101,0x3101,0x3101,0x3101};
AttachCodes1LK[12]={0x4100,0x4101,0x4101,0x4101,0x4101,0x37361,0x38460,0x4101,0x4101,0x4101,0x4101,0x4101};
AttachCodes1RB[12]={0x1100,0x1101,0x1101,0x1101,0x1101,0x37351,0x38450,0x1101,0x1101,0x1101,0x1101,0x1101};
AttachCodes1LB[12]={0x2100,0x2101,0x2101,0x2101,0x2101,0x37361,0x38460,0x2101,0x2101,0x2101,0x2101,0x2101};

//int AttachCodes1RK[10]={0x130,0x37300,0x38405,0x3100,0x37351,0x38450,0x3101,0x37300,0x38405,0x130};
//int AttachCodes1LK[10]={0x140,0x37300,0x38405,0x4100,0x37361,0x38460,0x4101,0x37300,0x38405,0x140};
//int AttachCodes1RB[10]={0x110,0x37300,0x38405,0x3100,0x37351,0x38450,0x3101,0x37300,0x38405,0x110};
//int AttachCodes1LB[10]={0x120,0x37300,0x38405,0x4100,0x37361,0x38460,0x4101,0x37300,0x38405,0x120};

const int SignalCodes1R[4]={0x510,0x37300,0x38405,0x1500};
const int SignalCodes1L[4]={0x520,0x37300,0x38405,0x2500};
const int SignalCodes2R[4]={0x1500,0x37300,0x38405,0x510};
const int SignalCodes2L[4]={0x2500,0x37300,0x38405,0x520};

__fastcall TDesignAttachVer1_1::TDesignAttachVer1_1(void) : TDesignAttachVer1()
{
PtCount=AttachPtCount;
CodesL=AttachCodes1LK;
CodesR=AttachCodes1RK;
}

__fastcall TDesignAttachVer1_2::TDesignAttachVer1_2(void) : TDesignAttachVer1()
{
PtCount=AttachPtCount;
CodesL=AttachCodes1LB;
CodesR=AttachCodes1RB;
}

__fastcall TDesignAttachVer2_1::TDesignAttachVer2_1(void) : TDesignAttachVer2()
{
PtCount=AttachPtCount;
CodesL=AttachCodes1LK;
CodesR=AttachCodes1RK;
}

__fastcall TDesignAttachVer2_2::TDesignAttachVer2_2(void) : TDesignAttachVer2()
{
PtCount=AttachPtCount;
CodesL=AttachCodes1LB;
CodesR=AttachCodes1RB;
}

bool __fastcall TDesignAttachVer1::Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict)
{
bool Res=false;
TRoadAttach *Att=dynamic_cast<TRoadAttach*>(Obj);
if (Att) {
    angle=Att->Angle;
    if (angle==0)
       angle=90;
    ewidth=600;
    bwidth=3*ewidth/2+(int)((ewidth/100)/sin(angle*M_PI/180))*100;
    elength=600;
    int ang;
    // –асчет параметров по метрике
    if (Att->Poly && Att->Poly->Count>=4) {
      int last=Att->Poly->Count-1;
      int pos;  // »щем точку с фиксированным углом от предыдущей точки
      for (pos=1;pos<=last;pos++)
         if (Att->Poly->Points[pos].Code()&0x17300==0x17300 &&
           (Att->Poly->Points[pos].Code.Leep()==5 || Att->Poly->Points[pos].Code.Leep()==6))
              break;
      if (pos<last) {
         ang=abs(Att->Poly->Points[pos].BasePar1)%360000;
         if (ang>180000)
           ang=360000-ang;
         angle=(ang+500)/1000;
         elength=abs(Att->Poly->Points[pos].X-Att->Poly->Points[0].X);
         ewidth=abs(Att->Poly->Points[pos+1].L-Att->Poly->Points[pos].L)*sin(ang*M_PI/180000)+0.5;
      }
      bwidth=abs(Att->Poly->Points[0].L-Att->Poly->Points[last].L);

    }
    frmAttachParams->edAngle->Text=IntToStr(angle);
    frmAttachParams->edLength->Text=IntToStr(elength);
    frmAttachParams->edBegWidth->Text=IntToStr(bwidth);
    frmAttachParams->edEndWidth->Text=IntToStr(ewidth);
    if (frmAttachParams->ShowModal()==mrOk) {
      angle=frmAttachParams->edAngle->Text.ToInt();
      elength=frmAttachParams->edLength->Text.ToInt();
      bwidth=frmAttachParams->edBegWidth->Text.ToInt();
      ewidth=frmAttachParams->edEndWidth->Text.ToInt();
      if (!Att->Poly){
        Att->Poly=new TPolyline(PtCount,0);
        Data->PolyList->Add(Att->Poly);
      } else
        Att->Poly->Count=PtCount;
      Att->Angle=angle;
      const int *Codes;
      if (Att->Placement==apLeft)
         Codes=CodesL;
      else
         Codes=CodesR;
      // rad=dl*tan(a/2)*tan((180-a)/2)/(tan(a/2)+tan((180-a)/2))
      double ta1=tan(angle*M_PI/360);
      double ta2=tan((180-angle)*M_PI/360);
      double rad=(bwidth-ewidth/sin(angle*M_PI/180))*ta1*ta2/(ta1+ta2);
      int last=PtCount/2-2;
      int sign;
      if (Att->Placement==apLeft)
        Codes=CodesL,sign=-1;
      else
        Codes=CodesR,sign=1;
      double maxa=1-cos((angle>90? angle:180-angle)*M_PI/180);
      for (int i=0;i<=last;i++) {
         double alf=(angle)*i*M_PI/(180*last);
         double x=-bwidth/2+rad*sin(alf);
         double y=/*elength*(1-cos(alf))/maxa*/  rad*(1-cos(alf));
         Att->Poly->Points[i].Code=Codes[i];
         Att->Poly->Points[i].LeepPar=0;
         Att->Poly->Points[i].BasePar1=x;
         Att->Poly->Points[i].BasePar2=sign*y;
         alf=(180-angle)*i*M_PI/(180*last);
         x=bwidth/2-rad*sin(alf);
         y=/*elength*(1-cos(alf))/maxa*/ rad*(1-cos(alf));
         Att->Poly->Points[PtCount-1-i].Code=Codes[PtCount-1-i];
         Att->Poly->Points[PtCount-1-i].LeepPar=0;
         Att->Poly->Points[PtCount-1-i].BasePar1=x;
         Att->Poly->Points[PtCount-1-i].BasePar2=sign*y;
      }
      Att->Poly->Points[last+1].Code=Codes[last+1];
      Att->Poly->Points[last+1].LeepPar=0;
      Att->Poly->Points[last+2].Code=Codes[last+2];
      Att->Poly->Points[last+2].LeepPar=0;
      Att->Poly->Points[last+1].BasePar1=sign*angle*1000;
      Att->Poly->Points[last+2].BasePar1=sign*angle*1000;
      // BasePar2 будет пересчитано автоматически далее
      Data->Road->CalcPointsPos(Att->Poly,Att);
      MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)Att,(int)Data);
    }
}
/*
    int W1=0;
    int L=Att->L;
    int L1=0;  // L начала закруглени€ ближней дуги
    int L2=0;  // L начала закруглени€ дальней дуги
    int L3=0;  // L конца закруглени€ ближней дуги
    int L4=0;  // L конца закруглени€ дальней дули
    int DX1=0; // DX конца закруглени€ ближней дуги (без знака)
    int DX2=0; // DX конца закруглени€ дальней дуги (без знака)
    int SDX1,SDX2; // “оже самое, но со знаком в зависимости от направлени€
    if (Att->Poly)
        if (Att->Poly->Count>1)
            {
            L1=Att->Poly->Points[0].L;
            L2=Att->Poly->Points[Att->Poly->Count-1].L;
            if (Att->Poly->Count==4)
                {
                DX1=abs(Att->Poly->Points[1].X-Att->Poly->Points[0].X);
                DX2=abs(Att->Poly->Points[2].X-Att->Poly->Points[3].X);
                L3=Att->Poly->Points[1].L;
                L4=Att->Poly->Points[2].L;
                }
            else if (Att->Poly->Count==10)
                {
                DX1=abs(Att->Poly->Points[3].X-Att->Poly->Points[0].X);
                DX2=abs(Att->Poly->Points[6].X-Att->Poly->Points[9].X);
                L3=Att->Poly->Points[3].L;
                L4=Att->Poly->Points[6].L;
                }
            }
    if (L2<L1)
        {
        int t=L2;
        L2=L1;
        L1=t;
        t=DX1;
        DX1=DX2;
        DX2=t;
        }
    W1=L2-L1;
    if (W1==0)
        W1=Att->Width;
    if (W1==0)
        W1=Att->DefaultWidth()*2;
    if ((L1==0)&&(L2==0))
        {
        L1=L-W1/2;
        L2=L+W1/2;
        }
    if ((L3==0)&&(L4==0))
        {
        L3=L1+W1/4;
        L4=L2-W1/4;
        }
    else if (L4<L3)
        {
        int t=L4;
        L4=L3;
        L3=t;
        }
    if ((DX1==0)&&(DX2==0))
        DX1=DX2=2000;
    if (Att->Placement==apLeft)
        SDX1=-DX1,SDX2=-DX2;
    else
        SDX1=DX1,SDX2=DX2;

    if (!Att->Poly)
        {
        Att->Poly=new TPolyline(PtCount,0);
        Data->PolyList->Add(Att->Poly);
        }
    else
        Att->Poly->Count=PtCount;
    int ang=Att->Angle;
    if (!ang)
        ang=90;
    if (Att->Placement!=apRight)
        ang=-ang;
    ang*=1000;
    int backang;
    if (ang<=0)
        backang=180000+ang;
    else
        backang=-180000+ang;
    const int *Codes;
    if (Att->Placement==apLeft)
        Codes=CodesL;
    else
        Codes=CodesR;
    for (int i=0;i<PtCount;i++)
        {
        Att->Poly->Points[i].Code=Codes[i];
        Att->Poly->Points[i].LeepPar=0;
        }
// ”станавливаем не прив€занные точки
    TRoadPoint *P=Att->Poly->Points;
    P[0].BasePar1=L1-L;
    P[0].BasePar2=0;
    P[9].BasePar1=L2-L;
    P[9].BasePar2=0;

    int R=DX1/tan(fabs((double)ang*M_PI/180000));
    P[1].BasePar1=0;
    P[1].BasePar2=(L3-L1-R)/2;

    R=DX2/tan(fabs((double)ang*M_PI/180000));
    P[8].BasePar1=180000;
    P[8].BasePar2=(L2-L4+R)/2;

    P[2].BasePar1=backang;
    P[2].BasePar2=DX1/2;
    P[7].BasePar1=backang;
    P[7].BasePar2=DX2/2;

    P[3].BasePar1=L3-L;
    P[3].BasePar2=SDX1;
    P[6].BasePar1=L4-L;
    P[6].BasePar2=SDX2;

    P[4].BasePar1=ang;
    P[4].BasePar2=0;
    P[5].BasePar1=ang;
    P[5].BasePar2=0;
    Data->Road->CalcPointsPos(Att->Poly,Att);
    MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)Att,(int)Data);
    }
else
    Res=TDesignMetricsPattern::Design(Obj, Data, Dict);
*/
return Res;
}

bool __fastcall TDesignAttachVer2::Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict)
{
bool Res;
Res=TDesignAttachVer1::Design(Obj,Data,Dict);
TRoadAttach *Att=dynamic_cast<TRoadAttach*>(Obj);
if (Att)
if (Att->Poly)
    if (Att->Poly->Count==10)
        {
        Data->DeleteChildObjects(Att);
        TObjMetaClass *Meta=Dict->ObjClasses->Items[ROADSIGNALCODE];
        if (Meta)
            {
            TRoadSignal *Signal=(TRoadSignal*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADSIGNALCODE);
            Signal->Count=6;
            Signal->PutPosition(Att->Poly->Points[0].L,Att->Poly->Points[3].L);
            Signal->Placement=(TObjPlacement)Att->Placement;
            Signal->Kind=skStolb;
            Signal->DrwClassId=Dict->SelectDrwParam(Signal,1);
            Att->AddChild(Signal);
            Signal->Poly=new TPolyline(SignalPointCount,0);
            Data->PolyList->Add(Signal->Poly);
            Signal->Poly->Count=SignalPointCount;
            TRoadPoint *AttP=Att->Poly->Points;
            TRoadPoint *P=Signal->Poly->Points;
            const int *Codes;
            if (Signal->Placement==opLeft)
                Codes=SignalCodes1L;
            else
                Codes=SignalCodes1R;
            for (int i=0;i<SignalPointCount;i++)
                {
                P[i]=AttP[i];
                P[i].Code=Codes[i];
                }
            P[0].BasePar1-=200;
            P[SignalPointCount-1].BasePar1-=200;
            Data->Road->CalcPointsPos(Signal->Poly,Signal);
            Signal->UpdatePoly();

            Data->Buffer->Add(Signal);
            Signal=(TRoadSignal*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADSIGNALCODE);
            Signal->Count=6;
            Signal->PutPosition(Att->Poly->Points[6].L,Att->Poly->Points[9].L);
            Signal->Placement=(TObjPlacement)Att->Placement;
            Signal->Kind=skStolb;
            Signal->DrwClassId=Dict->SelectDrwParam(Signal,1);
            Att->AddChild(Signal);
            Signal->Poly=new TPolyline(SignalPointCount,0);
            Data->PolyList->Add(Signal->Poly);
            Signal->Poly->Count=SignalPointCount;
            P=Signal->Poly->Points;
            if (Signal->Placement==opLeft)
                Codes=SignalCodes2L;
            else
                Codes=SignalCodes2R;
            for (int i=0;i<SignalPointCount;i++)
                {
                P[i]=AttP[PtCount-SignalPointCount+i];
                P[i].Code=Codes[i];
                }
            P[0].BasePar1+=200;
            P[SignalPointCount-1].BasePar1+=200;
            Data->Road->CalcPointsPos(Signal->Poly,Signal);
            Signal->UpdatePoly();
            Data->Buffer->Add(Signal);
            Data->AddFromBufer();
            MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)Data);
            }
        }
return Res;
}

bool __fastcall TDesignAttachVer3::Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict)
{
bool Res=false;
TRoadAttach *Att=dynamic_cast<TRoadAttach*>(Obj);
TObjMetaClass *Meta=Dict->ObjClasses->Items[ROADMARKCODE];
if (Meta && Att && Att->Poly) {
      int last=Att->Poly->Count-1;
      int pos;  // »щем точку с фиксированным углом от предыдущей точки
      for (pos=1;pos<=last-2;pos++)
         if (Att->Poly->Points[pos].Code()&0x17300==0x17300 &&
           (Att->Poly->Points[pos].Code.Leep()==5 || Att->Poly->Points[pos].Code.Leep()==6))
              break;
      if (pos<last) {
         TRoadMark *mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
         mark->Poly=new TPolyline(pos+1,0);
         mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
         mark->SetKind(ma2_1);
         for (int i=0;i<pos;i++) {
            mark->Poly->Points[i].BasePar1=Att->Poly->Points[i].L+50;
            mark->Poly->Points[i].BasePar2=Att->Poly->Points[i].X;
            mark->Poly->Points[i].Code=(i==0?0:1);
         }
         int left=mark->Poly->Points[0].BasePar1=((Att->Poly->Points[0].L+99)/100)*100;
         mark->Poly->Points[pos]=Att->Poly->Points[pos];
         mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
         Data->Road->CalcPointsPos(mark->Poly,mark);
         mark->UpdatePoly();
         Data->Buffer->Add(mark);

         mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
         mark->Poly=new TPolyline(last-pos,0);
         mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
         mark->SetKind(ma2_1);
         for (int i=0;i<last-pos-1;i++) {
            mark->Poly->Points[i].BasePar1=Att->Poly->Points[last-i].L-50;
            mark->Poly->Points[i].BasePar2=Att->Poly->Points[last-i].X;
            mark->Poly->Points[i].Code=(i==0?0:1);
         }
         int right=mark->Poly->Points[0].BasePar1=((Att->Poly->Points[last].L)/100)*100;
         mark->Poly->Points[last-pos-1]=Att->Poly->Points[pos];
         mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
         Data->Road->CalcPointsPos(mark->Poly,mark);
         mark->UpdatePoly();
         Data->Buffer->Add(mark);

         mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
         mark->Poly=new TPolyline(3,0);
         mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
         mark->SetKind(ma1);
         int center=mark->Poly->Points[0].BasePar1=((Att->Poly->Points[0].L+Att->Poly->Points[last].L+100)/200)*100;
         mark->Poly->Points[0].BasePar2=Att->Poly->Points[0].X;
         mark->Poly->Points[0].Code=0;
         if (abs(Att->Poly->Points[pos-1].X)>abs(Att->Poly->Points[pos+2].X)) {
            mark->Poly->Points[1].BasePar1=Att->Poly->Points[pos-1].L+(Att->Poly->Points[pos+1].L-Att->Poly->Points[pos].L)/2;
            mark->Poly->Points[1].BasePar2=Att->Poly->Points[pos-1].X;
         } else {
            mark->Poly->Points[1].BasePar1=Att->Poly->Points[pos+2].L-(Att->Poly->Points[pos+1].L-Att->Poly->Points[pos].L)/2;
            mark->Poly->Points[1].BasePar2=Att->Poly->Points[pos+2].X;
         }
         mark->Poly->Points[1].Code=1;
         mark->Poly->Points[2]=Att->Poly->Points[pos];
         mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
         Data->Road->CalcPointsPos(mark->Poly,mark);
         mark->UpdatePoly();
         Data->Buffer->Add(mark);

         mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
         mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
         mark->SetKind(ma7);
         mark->K=1000;
         mark->Offset=0;
         if (Att->Placement==opRight)
            mark->PutPosition(left,center);
         else
            mark->PutPosition(center,right);
         mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
         Data->Buffer->Add(mark);

         mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
         mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
         mark->SetKind(ma13);
         mark->K=1000;
         mark->Offset=0;
         if (Att->Placement==opRight)
            mark->PutPosition(center,right);
         else
            mark->PutPosition(left,center);
         mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
         Data->Buffer->Add(mark);


         Data->AddFromBufer();
         MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)Data);
         Res=true;
         }
      }

/*

        int c1=0;
        int c2=0;
        for (int i=1;i<Att->Poly->Count;i++)
            if (!Att->Poly->Points[i].Code.Visible())
                {
                c1=i+1;
                c2=Att->Poly->Count-c1;
                break;
                }
        if (c1&&c2)
            {
            TObjMetaClass *Meta=Dict->ObjClasses->Items[ROADMARKCODE];
            if (Meta)
                {
                TRoadMark *mark=(TRoadMark*)Data->Factory->CreateRoadObj(Meta->ClassName,0,ROADMARKCODE);
                mark->Poly=new TPolyline(c1,0);
                mark->SetDirection((Att->Placement==opRight) ? roDirect:roUnDirect);
                mark->SetKind(ma22);
                mark->Poly->Count=c1;
                mark->L=Att->L;
                mark->SetLMax(Att->LMax);
                for (int i=0;i<c1;i++)
                    mark->Poly->Points[i]=Att->Poly->Points[i];
                mark->DrwClassId=Dict->SelectDrwParam(mark,ROADMARKPAGE);
                Att->AddChild(mark);
                Data->Road->CalcPointsPos(mark->Poly,mark);
                mark->UpdatePoly();
                Data->Buffer->Add(mark);
                Data->AddFromBufer();
                MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)Data);
                Res=true;
                }
            }
        }
*/
return Res;
}

