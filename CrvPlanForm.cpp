//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CrvPlanForm.h"
#include "VideoForm.h"
#include "MainUnit.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCrvPlan *frmCrvPlan;
#define COLCOUNT 5
const char GridCapt[COLCOUNT][16]={"км.","вход","круг.","вставка","выход"};
const int WNDBNDSPACE=5000;

TCurveParam::TCurveParam(TDangerCurve *in,TDangerCurve *crc,TDangerCurve *out)
{
L[0]=L[1]=L[2]=L[3]=0;
Rad=0;
InCrv=in;
OutCrv=out;
CrcCrv=crc;
if (CrcCrv)
    {
    L[0]=L[1]=CrcCrv->LMin;
    L[2]=L[3]=CrcCrv->LMax;
    Rad=CrcCrv->Radius;
    if (Rad>0)
        Direction=ckRightCurve;
    else
        Direction=ckLeftCurve;
    }
if (InCrv)
    {
    L[0]=InCrv->LMin;
    L[1]=InCrv->LMax;
    Direction=InCrv->Kind;
    }
if (OutCrv)
    {
    L[2]=OutCrv->LMin;
    L[3]=OutCrv->LMax;
    Direction=InCrv->Kind;
    }
}

void TCurveParam::WriteInGrid(TStringGrid *Grid,int Index)
{
int km=L[0]/100000;
Grid->Cells[0][Index]=km;
Grid->Cells[1][Index]=L[0]/100-km*1000;
Grid->Cells[2][Index]=L[1]/100-km*1000;
Grid->Cells[3][Index]=L[2]/100-km*1000;
Grid->Cells[4][Index]=L[3]/100-km*1000;
Grid->Objects[0][Index]=this;
}

//---------------------------------------------------------------------------
__fastcall TfrmCrvPlan::TfrmCrvPlan(TComponent* Owner)
    : TForm(Owner)
{
FData=NULL;
ArrayPos=NULL;
ArrayRad=NULL;
ArrayAngle=NULL;
ArrayX=NULL;
ArrayY=NULL;
ArraySize=0;
CurvesCount=0;
EditIndex=0;
for (int i=0;i<5;i++)
    Grid->Cells[i][0]=GridCapt[i];
}
//---------------------------------------------------------------------------
void __fastcall TfrmCrvPlan::Initialize(TDtaSource *data,TDictSource *dict)
{
FData=data;
FDict=dict;
ClearTable();
ShowTable();
Grid->FixedRows=1;
if (CurvesCount)
    EditIndex=1;
else
    EditIndex=0;
}

void __fastcall TfrmCrvPlan::AddTableItem(TDangerCurve *Crv_In,TDangerCurve *Crv_Crc,TDangerCurve *Crv_Out)
{
TCurveParam *CrvParam=new TCurveParam(Crv_In,Crv_Crc,Crv_Out);
if (CrvParam->Correct())
    {
    CurvesCount++;
    Grid->RowCount=CurvesCount+1;
    CrvParam->WriteInGrid(Grid,CurvesCount);
    }
else
    delete CrvParam;
}

void __fastcall TfrmCrvPlan::ClearTable(void)
{
for (int i=1;i<=CurvesCount;i++)
    {
    delete Grid->Objects[0][i];
    Grid->Objects[0][i]=NULL;
    }
CurvesCount=0;
Grid->RowCount=2;
}

void __fastcall TfrmCrvPlan::ShowTable(void)
{
if (FData)
    {
    int n=FData->Objects->Count;
    int Pos[4];
    TDangerCurve *Crv_In,*Crv_Out,*Crv_Crc;
    TDangerCurve *PrevCrv=NULL;
    Crv_In=Crv_Out=Crv_Crc=NULL;
    for (int i=0;i<n;i++)
        {
        TRoadObject *Obj=FData->Objects->Items[i];
        TDangerCurve *Crv=dynamic_cast<TDangerCurve*>(Obj);
        if (Crv)
            {
            if (Crv->Kind==ckLine)
                {
                AddTableItem(Crv_In,Crv_Crc,Crv_Out);
                Crv_In=Crv_Out=Crv_Crc=NULL;
                }
            else if (!PrevCrv)  // Это может быть только в самый первый раз если начинается не с прямой
                {
                if (Crv->Kind==ckCircle)
                    Crv_Crc=Crv;
                else
                    Crv_In=Crv;
                }
            else if (PrevCrv->LMax!=Crv->LMin) // был пропуск, надо сделать поворот
                {
                AddTableItem(Crv_In,Crv_Crc,Crv_Out);
                Crv_In=Crv_Crc=Crv_Out=NULL;
                if (Crv->Kind==ckCircle)
                    Crv_Crc=Crv;
                else
                    Crv_In=Crv;
                }
            else if (Crv->Kind==ckCircle)
                {
                if (Crv_Crc)
                    {
                    AddTableItem(Crv_In,Crv_Crc,Crv_Out);
                    Crv_In=Crv_Out=NULL;
                    }
                Crv_Crc=Crv;
                }
            else
                {
                if (Crv_In)
                    {
                    if (Crv_Out)
                        {
                        AddTableItem(Crv_In,Crv_Crc,Crv_Out);
                        Crv_In=Crv;
                        Crv_Crc=Crv_Out=NULL;
                        }
                    else
                        Crv_Out=Crv;
                    }
                else
                    Crv_In=Crv;
                }
            PrevCrv=Crv;
            }
        }
    }
}

void __fastcall TfrmCrvPlan::Sinchronize(void)
{
// Для начала определимся с прямыми вставками
if (FData)
    {
    __int32 *LStart=new __int32 [CurvesCount+1];  // Начала прямых вставок.
    __int32 *LEnd=new __int32 [CurvesCount+1];    // Концы вставок.
    LStart[0]=FData->Road->LMin;
    LStart[CurvesCount]=FData->Road->LMax;
    for (int i=1;i<=CurvesCount;i++)
        {
        TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][i]);
        LStart[i]=Par->L[3];
        LEnd[i-1]=Par->L[0];
        }
    int n=FData->Objects->Count;
    int LineCount=0;
    for (int i=0;i<n;i++)
        {
        TRoadObject *Obj=FData->Objects->Items[i];
        TDangerCurve *Crv=dynamic_cast<TDangerCurve*>(Obj);
        if (Crv)
            {
            if (Crv->Kind==ckLine)
                {
                if (LineCount<=CurvesCount)
                    Crv->PutPosition(LStart[LineCount],LEnd[LineCount]);
                else
                    {
                    FData->DeleteObject(i);
                    i--;
                    n--;
                    }
                LineCount++;
                }
            }
        }
    for (int i=1;i<=CurvesCount;i++)
        {
        TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][i]);
        Par->InCrv=UpdateCurve(Par->InCrv,Par->L[0],Par->L[1],Par->Direction);
        Par->CrcCrv=UpdateCurve(Par->CrcCrv,Par->L[1],Par->L[2],ckCircle);
        if (Par->CrcCrv)
            Par->CrcCrv->Radius=Par->Rad;
        Par->OutCrv=UpdateCurve(Par->OutCrv,Par->L[2],Par->L[3],Par->Direction);
        }
    FData->AddFromBufer();
    MainForm->PostBroadCastMessage(CM_INSERTGROUP,0,(int)FData);
    MainForm->PostBroadCastMessage(CM_DELETEGROUP,0,(int)FData);
    }
}

TDangerCurve* __fastcall TfrmCrvPlan::UpdateCurve(TDangerCurve *Crv,__int32 L1,__int32 L2,TCurveKind knd)
{
TDangerCurve *Result=NULL;
if (L1==L2)
    {
    if (Crv)
        FData->DeleteObject(Crv);
    }
else if (Crv)
    {
    Crv->PutPosition(L1,L2);
    Result=Crv;
    }
else
    {
    Result=(TDangerCurve*)FData->Factory->CreateRoadObj("TDangerCurve",0,DANGERCURVECODE);
    Result->PutPosition(L1,L2);
    Result->Kind=knd;
    Result->Permissible=tpYes;
    Result->DrwClassId=FDict->SelectDrwParam(Result,1);
    FData->AddRoadObject(Result);    
    }
return Result;
}


TDangerCurve* __fastcall TfrmCrvPlan::GetCurve(__int32 Pos)
{
TDangerCurve *Crv=NULL;
TRoadObject *Obj=FData->FindRoadPart(DANGERCURVECODE,Pos);
if (Obj)
    Crv=dynamic_cast<TDangerCurve*>(Obj);
return Crv;
}


void __fastcall TfrmCrvPlan::FindCurveAt(__int32 Pos)
{
TCurveParam *Par;
int i;
for (i=1;i<=CurvesCount;i++)
    {
    Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][i]);
    if (Par)
        if ((Pos<=Par->L[3])&&(Pos>=Par->L[0]))
            break;
    }
if (i<=CurvesCount)
    {
    FCrvIn=Par->InCrv;
    FCrvOut=Par->OutCrv;
    FCrvCrcl=Par->CrcCrv;
    for (int j=0;j<4;j++)
        Bounds[j]=Par->L[j];
    WndBounds[0]=Bounds[0]-WNDBNDSPACE;
    WndBounds[1]=Bounds[3]+WNDBNDSPACE;
    Radius=Par->Rad;
    EditIndex=i;
    FHasCurves=true;
    Grid->Row=EditIndex;
    }
else
    {
//    Grid->Options>>goRowSelect;
//
    TGridRect Selection;
    Selection.Left = 0;
    Selection.Top = 0;
    Selection.Right = 0;
    Selection.Bottom = 0;
    Grid->Selection=Selection;
    EditIndex=0;
    FHasCurves=false;
    }
btnAdd->Enabled=!FHasCurves;
btnSave->Enabled=FHasCurves;
btnDelete->Enabled=FHasCurves;
BitBtn1->Enabled=FHasCurves;
BitBtn2->Enabled=FHasCurves;
BitBtn3->Enabled=FHasCurves;
}



void __fastcall TfrmCrvPlan::TestBounds(void)
{
if (Bounds[3]<Bounds[0])
    {
    int t=Bounds[0];
    Bounds[0]=Bounds[3];
    Bounds[3]=t;
    }
if (Bounds[1]<Bounds[0])
    Bounds[1]=Bounds[0];
if (Bounds[2]<Bounds[0])
    Bounds[2]=Bounds[0];
if (Bounds[1]>Bounds[3])
    Bounds[1]=Bounds[3];
if (Bounds[2]>Bounds[3])
    Bounds[2]=Bounds[3];
if (WndBounds[0]>Bounds[0])
    WndBounds[0]=Bounds[0];
if (WndBounds[1]<Bounds[3])
    WndBounds[1]=Bounds[3];
}

void __fastcall TfrmCrvPlan::EditCurves(void)
{
Edit_Pos->Text=String((double)FCpPosition/100);
if (FHasCurves)
    {
    ComboPartType->ItemIndex=1;
    Edit_L1->Text=String((double)Bounds[0]/100);
    Edit_L2->Text=String((double)Bounds[1]/100);
    Edit_L3->Text=String((double)Bounds[2]/100);
    Edit_L4->Text=String((double)Bounds[3]/100);
    Edit_W1->Text=String((double)WndBounds[0]/100);
    Edit_W2->Text=String((double)WndBounds[1]/100);
    Edit_Rad->Text=Radius;
    }
else
    {
    ComboPartType->ItemIndex=0;
    Edit_L1->Text="";
    Edit_L2->Text="";
    Edit_L3->Text="";
    Edit_L4->Text="";
    Edit_Rad->Text="";
    Edit_W1->Text="";
    Edit_W2->Text="";
    }
Edit_L1->Enabled=FHasCurves;
Edit_L2->Enabled=FHasCurves;
Edit_L3->Enabled=FHasCurves;
Edit_L4->Enabled=FHasCurves;
Edit_W1->Enabled=FHasCurves;
Edit_W2->Enabled=FHasCurves;
Edit_Rad->Enabled=FHasCurves;
PBox->Invalidate();
}

void __fastcall TfrmCrvPlan::GetCurves(void)
{
if (FHasCurves&&FData)
    {
    Bounds[0]=Edit_L1->Text.ToInt()*100;
    Bounds[1]=Edit_L2->Text.ToInt()*100;
    Bounds[2]=Edit_L3->Text.ToInt()*100;
    Bounds[3]=Edit_L4->Text.ToInt()*100;
    }
}

void __fastcall TfrmCrvPlan::GetWndBounds(void)
{
if (FHasCurves&&FData)
    {
    WndBounds[0]=Edit_W1->Text.ToInt()*100;
    WndBounds[1]=Edit_W2->Text.ToInt()*100;
    }
}

void __fastcall TfrmCrvPlan::GetRadiusData(void)
{
delete[] ArrayPos;
delete[] ArrayRad;
delete[] ArrayAngle;
delete[] ArrayX;
delete[] ArrayY;
ArrayPos=NULL;
ArrayRad=NULL;
ArrayAngle=NULL;
ArrayX=NULL;
ArrayY=NULL;
ArraySize=0;
if (FData&&FHasCurves)
    {
    int indexes[6];
    TGeometryVal boundval[6];
    __int32 boundpos[6];
    TGeometryVal *Values=FData->Road->Geometry.Values;
    __int32 *L=FData->Road->Geometry.L;
    indexes[0]=FData->Road->Geometry.GetMesValue(boundpos[0]=WndBounds[0],boundval[0]);
    for (int i=0;i<4;i++)
        indexes[i+1]=FData->Road->Geometry.GetMesValue(boundpos[i+1]=Bounds[i],boundval[i+1]);
    indexes[5]=FData->Road->Geometry.GetMesValue(boundpos[5]=WndBounds[1],boundval[5]);
    InStart=indexes[1]-indexes[0]+1;
    CrclStart=indexes[2]-indexes[0]+2;
    CrclEnd=indexes[3]-indexes[0]+3;
    OutEnd=indexes[4]-indexes[0]+4;
    ArraySize=indexes[5]-indexes[0]+6;
    ArrayRad=new __int32 [ArraySize];
    ArrayPos=new __int32 [ArraySize];
    ArrayAngle=new double [ArraySize];
    ArrayX=new double [ArraySize];
    ArrayY=new double [ArraySize];
    if (Combo_Dir->ItemIndex==0)  // прямое направление
        {
        int i=0;
        int j=indexes[0]+1;
        ArrayPos[i]=boundpos[0];
        ArrayRad[i]=boundval[0].DirectRad;
        i++;
        for (int k=1;k<6;k++)
            {
            for (;j<=indexes[k];i++,j++)
                {
                ArrayPos[i]=L[j];
                ArrayRad[i]=Values[j].DirectRad;
                }
            ArrayPos[i]=boundpos[k];
            ArrayRad[i]=boundval[k].DirectRad;
            i++;
            }
        }
    else
        {
        int i=0;
        int j=indexes[0]+1;
        ArrayPos[i]=boundpos[0];
        ArrayRad[i]=boundval[0].UnDirectRad;
        i++;
        for (int k=1;k<6;k++)
            {
            for (;j<=indexes[k];i++,j++)
                {
                ArrayPos[i]=L[j];
                ArrayRad[i]=Values[j].UnDirectRad;
                }
            ArrayPos[i]=boundpos[k];
            ArrayRad[i]=boundval[k].UnDirectRad;
            i++;
            }
        }
    double CurAngle=0;
    double CurX=0;
    double CurY=0;
    ArrayAngle[0]=0;
    ArrayX[0]=CurX;
    ArrayY[0]=CurY;
    double CurSpeed,PrevSpeed;
    if (ArrayRad[0])
        CurSpeed=1/(double)ArrayRad[0];
    else
        CurSpeed=0;
    for (int i=1;i<ArraySize;i++)
        {
        PrevSpeed=CurSpeed;
        if (ArrayRad[i])
            CurSpeed=1/(double)ArrayRad[i];
        else
            CurSpeed=0;
        int dl=ArrayPos[i]-ArrayPos[i-1];
        if (dl)
            {
            CurAngle+=((CurSpeed+PrevSpeed)*50)/(dl);  //*100/2
            double sinAng=sin(CurAngle);
            double cosAng=cos(CurAngle);
            double dl1=(double)dl/100.0;
            double Acs=(CurSpeed-PrevSpeed)/(2*dl1); // Половина углового усконения
            double dl2=dl1*dl1;
            double dl3=dl2*dl1;
            CurX+=dl1*sinAng+cosAng*PrevSpeed*dl2/2.0+cosAng*Acs*dl3/3.0; // Несколько членов ряда Тэйлора для функции
            CurY+=dl1*cosAng-sinAng*PrevSpeed*dl2/2.0-sinAng*Acs*dl3/3.0;
            }
        ArrayAngle[i]=CurAngle;
        ArrayX[i]=CurX;
        ArrayY[i]=CurY;
        }
    }
}

void __fastcall TfrmCrvPlan::DrawCurve(void)
{
if ((FData)&&(FHasCurves))
    {
    double Len=(WndBounds[1]-WndBounds[0])/100;
    double mpp=(ArrayY[ArraySize-1])/PBox->Height; //Метров на пиксел
    int cx,cy;
    POINT *P=new POINT [ArraySize];
    if (ArrayX[ArraySize-1]>0)
        cx=PBox->Width/4;
    else
        cx=(PBox->Width*3)/4;
    cy=PBox->Height;
    for (int i=0;i<ArraySize;i++)
        {
        P[i].x=ArrayX[i]/mpp+0.5+cx;
        P[i].y=cy-ArrayY[i]/mpp+0.5;
        }
    LOGBRUSH lb;
    lb.lbStyle=BS_SOLID;
    lb.lbColor=clWhite;
    void *pen1=ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT,5,&lb,0,NULL);
    lb.lbColor=clYellow;
    void *pen2=ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT,5,&lb,0,NULL);
    lb.lbColor=clBlue;
    void *pen3=ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT,5,&lb,0,NULL);
    lb.lbColor=clRed;
    void *pen4=ExtCreatePen(PS_GEOMETRIC|PS_SOLID|PS_ENDCAP_FLAT,1,&lb,0,NULL);
    void *dc=PBox->Canvas->Handle;
    void *oldpen=SelectObject(dc,pen1);
    Polyline(dc,P,InStart);
    SelectObject(dc,pen2);
    Polyline(dc,P+InStart,CrclStart-InStart);
    SelectObject(dc,pen3);
    Polyline(dc,P+CrclStart,CrclEnd-CrclStart);
    SelectObject(dc,pen2);
    Polyline(dc,P+CrclEnd,OutEnd-CrclEnd);
    SelectObject(dc,pen1);
    Polyline(dc,P+OutEnd,ArraySize-OutEnd);
// Рисуем расчетную линию
    SelectObject(dc,pen4);
    double x,y;
    if (ArrayX[ArraySize-1]>0)
        x=PBox->Width/4;
    else
        x=(PBox->Width*3)/4;
    y=PBox->Height;
    MoveToEx(dc,x+0.5,y+0.5,NULL);
    if (Radius)
        {
        double Rad=Radius;
        y-=(Bounds[0]-WndBounds[0])/(mpp*100);
        LineTo(dc,x+0.5,y+0.5);
        int CLen=(Bounds[1]-Bounds[0])/100;
        double CurAngle=0;// Текущий угол в радианах от вертикали
        if (CLen)
            {
            double RL=Rad*CLen;
            double BR2=1.0/(2.0*RL);
            for (int i=0;i<CLen;i++)
                {
                double sina=sin(CurAngle);
                double cosa=cos(CurAngle);
                double PrevSpeed=(double)i/RL;
                x+=(sina+cosa*PrevSpeed/2.0+cosa*BR2/3.0)/mpp;
                y-=(cosa-sina*PrevSpeed/2.0-sina*BR2/3.0)/mpp;
                LineTo(dc,x+0.5,y+0.5);
                CurAngle+=PrevSpeed+BR2;
                }
            }
        CLen=(Bounds[2]-Bounds[1])/100;
        double AngSpeed=1/(double)Rad;
        for (int i=1;i<=CLen;i++)
            {
            x-=((cos(CurAngle+AngSpeed)-cos(CurAngle))/AngSpeed)/mpp;
            y-=((sin(CurAngle+AngSpeed)-sin(CurAngle))/AngSpeed)/mpp;
            CurAngle+=AngSpeed;
            LineTo(dc,x+0.5,y+0.5);
            }
        CLen=(Bounds[3]-Bounds[2])/100;
        if (CLen)
            {
            double RL=Rad*CLen;
            double BR2=-1.0/(2.0*RL);
            for (int i=CLen;i>0;i--)
                {
                double sina=sin(CurAngle);
                double cosa=cos(CurAngle);
                double PrevSpeed=(double)i/RL;
                x+=(sina+cosa*PrevSpeed/2.0+cosa*BR2/3.0)/mpp;
                y-=(cosa-sina*PrevSpeed/2.0-sina*BR2/3.0)/mpp;
                LineTo(dc,x+0.5,y+0.5);
                CurAngle+=PrevSpeed+BR2;
                }
            }
        x+=sin(CurAngle)*(WndBounds[1]-Bounds[3])/(100*mpp);
        y-=cos(CurAngle)*(WndBounds[1]-Bounds[3])/(100*mpp);
        LineTo(dc,x+0.5,y+0.5);
        }
    else
        {
        y-=Len/mpp;
        LineTo(dc,x+0.5,y+0.5);
        }
    SelectObject(dc,oldpen);
    DeleteObject(pen1);
    DeleteObject(pen2);
    DeleteObject(pen3);
    DeleteObject(pen4);
    delete[] P;
    }
}

/*
void __fastcall TfrmCrvPlan::GetCircleParams(double* Params)
{
double Rad=CalcMidleRad(CrclStart,CrclEnd);
double MaxDev=0;  // Максимальное отклонение
double S_Kv=0;   // Среднеквадратичное отклонение
if ((fabs(Rad)>1)&&(CrclEnd>CrclStart))
    {
    double AngSpeed=1/Rad;
    for (int i=CrclStart;i<=CrclEnd;i++)
        {
        double CurSpeed;
        if (ArrayRad[i])
            CurSpeed=1.0/(double)ArrayRad[i];
        else
            CurSpeed=0;
        double DiffSpeed=CurSpeed-AngSpeed;
        S_Kv+=DiffSpeed*DiffSpeed;
        if (fabs(MaxDev)<fabs(DiffSpeed))
            MaxDev=DiffSpeed;
        }
    S_Kv=sqrt(S_Kv/(CrclEnd-CrclStart+1));
    }
Params[0]=Rad;
Params[1]=MaxDev;
Params[2]=S_Kv;
}

void __fastcall TfrmCrvPlan::GetInCurveParams(double* Params,double InRad)
{
double MesInRad=ArrayRad[CrclStart]; // Радиус по данным измерений
int InLen=ArrayPos[CrclStart]-ArrayPos[0];
double MaxDev=0;  // Максимальное отклонение
double S_Kv=0;   // Среднеквадратичное отклонение
if ((InLen)&&(fabs(InRad)>=1))
    {
    for (int i=0;i<=CrclStart;i++)
        {
        double CalcSpeed=double(ArrayPos[i]-ArrayPos[0])/(InLen*InRad); // Расчетная скорость
        double CurSpeed;
        if (ArrayRad[i])
            CurSpeed=1.0/(double)ArrayRad[i];
        else
            CurSpeed=0;
        double DiffSpeed=CalcSpeed-CurSpeed;
        if (fabs(MaxDev)<fabs(DiffSpeed))
            MaxDev=DiffSpeed;
        S_Kv+=DiffSpeed*DiffSpeed;
        }
    }
S_Kv=sqrt(S_Kv/(CrclStart+1));
Params[0]=MesInRad;
Params[1]=MaxDev;
Params[2]=S_Kv;
}

void __fastcall TfrmCrvPlan::GetOutCurveParams(double* Params,double OutRad)
{
double MesOutRad=ArrayRad[CrclEnd];  // Радиус по данным измерений
int OutLen=ArrayPos[ArraySize-1]-ArrayPos[CrclEnd];
double MaxDev=0;  // Максимальное отклонение
double S_Kv=0;   // Среднеквадратичное отклонение
if ((OutLen)&&(fabs(OutRad)>=1))
    {
    for (int i=ArraySize-1;i>=CrclEnd;i--)
        {
        double CalcSpeed=double(ArrayPos[ArraySize-1]-ArrayPos[i])/(OutLen*OutRad); // Расчетная скорость
        double CurSpeed;
        if (ArrayRad[i])
            CurSpeed=1.0/(double)ArrayRad[i];
        else
            CurSpeed=0;
        double DiffSpeed=CalcSpeed-CurSpeed;
        if (fabs(MaxDev)<fabs(DiffSpeed))
            MaxDev=DiffSpeed;
        S_Kv+=DiffSpeed*DiffSpeed;
        }
    S_Kv=sqrt(S_Kv/(ArraySize-CrclEnd));
    }
Params[0]=MesOutRad;
Params[1]=MaxDev;
Params[2]=S_Kv;
}

*/
double __fastcall TfrmCrvPlan::GetMaxDevLen(int *InBnd,int Rad)
{
double MaxDev=0;
if (Rad)
    {
    double CurX=0;
    double CurY=0;
    double CurAngle=0;
    double CurLen=(double)WndBounds[0]/100;
    int i=0;
    for (;(i<ArraySize)&&(ArrayPos[i]<InBnd[0]);i++)  // Двигаемся по прямой строго вверх
        {
        double dl=(double)ArrayPos[i]/100-CurLen;
        CurY+=dl;
        CurLen+=dl;
        double dx=CurX-ArrayX[i];
        double dy=CurY-ArrayY[i];
        double CurDev=dx*dx+dy*dy;
        if (CurDev>MaxDev)
            MaxDev=CurDev;
        }
    CurY+=((double)InBnd[0]/100-CurLen);  //     участок прямой между двух точек
    CurLen=(double)InBnd[0]/100;
    double CurveLen=(double)(InBnd[1]-InBnd[0])/100.0;  // Длина клотоиды
    if (CurveLen>0.001)                                   // Если есть клотоида
        {
        double RL=(double)Rad*CurveLen;  // (угловое ускорение)^-1
        double AngAc=0.5/(RL);        // Половина углового ускорения
        double CurveStart=(double)InBnd[0]/100;
        for (;(i<ArraySize)&&(ArrayPos[i]<InBnd[1]);i++)  // Двигаемся по клотоиде
            {
            double dl=(double)ArrayPos[i]/100-CurLen;
            double sina=sin(CurAngle);
            double cosa=cos(CurAngle);
            double AngSpeed=(CurLen-CurveStart)/RL;       // Угловая скорость
            CurX+=((1.0/3.0*cosa*AngAc*dl+1.0/2.0*cosa*AngSpeed)*dl+sina)*dl;
            CurY+=((1.0/3.0*sina*AngAc*dl+1.0/2.0*sina*AngSpeed)*dl+cosa)*dl;
            CurAngle+=(AngAc*dl+AngSpeed)*dl;
            CurLen+=dl;
            double dx=CurX-ArrayX[i];
            double dy=CurY-ArrayY[i];
            double CurDev=dx*dx+dy*dy;
            if (CurDev>MaxDev)
                MaxDev=CurDev;
            }
        double dl=(double)InBnd[1]/100-CurLen;  // Последний фрагмент клотоиды
        double sina=sin(CurAngle);
        double cosa=cos(CurAngle);
        double AngSpeed=(CurLen-CurveStart)/RL;       // Угловая скорость
        CurX+=((1.0/3.0*cosa*AngAc*dl+1.0/2.0*cosa*AngSpeed)*dl+sina)*dl;
        CurY+=((1.0/3.0*sina*AngAc*dl+1.0/2.0*sina*AngSpeed)*dl+cosa)*dl;
        CurAngle+=(AngAc*dl+AngSpeed)*dl;
        }
    CurLen=(double)InBnd[1]/100;
    CurveLen=(double)(InBnd[2]-InBnd[1])/100.0; // Длина кругового участка
    if (CurveLen>0.001)                         //Если есть круговой участок
        {
        double AngSpeed=1.0/(double)Rad;    // Угловая скорость на участке
        for (;(i<ArraySize)&&(ArrayPos[i]<InBnd[2]);i++)  // Двигаемся по круговому участку
            {
            double dl=(double)ArrayPos[i]/100-CurLen;
            double cosa=cos(CurAngle);
            double sina=sin(CurAngle);
            CurAngle+=AngSpeed*dl;
            CurLen+=dl;
            CurX-=(cos(CurAngle)-cosa)*dl/AngSpeed;
            CurY+=(sin(CurAngle)-sina)*dl/AngSpeed;
            double dx=CurX-ArrayX[i];
            double dy=CurY-ArrayY[i];
            double CurDev=dx*dx+dy*dy;
            if (CurDev>MaxDev)
                MaxDev=CurDev;
            }
        double dl=(double)InBnd[2]/100-CurLen;  // Последний фрагмент кругового участка
        double cosa=cos(CurAngle);
        double sina=sin(CurAngle);
        CurAngle+=AngSpeed*dl;
        CurX-=(cos(CurAngle)-cosa)*dl/AngSpeed;
        CurY+=(sin(CurAngle)-sina)*dl/AngSpeed;
        }
    CurLen=(double)InBnd[2]/100;
    CurveLen=(double)(InBnd[3]-InBnd[2])/100.0; // Длина клотоиды выхода из поворота
    if (CurveLen>0.001)                         //Если есть клотоида
        {
        double RL=(double)Rad*CurveLen;  // - (угловое ускорение)^-1
        double AngAc=-0.5/(RL);        // Половина углового ускорения
        double CurveEnd=(double)InBnd[3]/100;
        for (;(i<ArraySize)&&(ArrayPos[i]<InBnd[3]);i++)  // Двигаемся по клотоиде
            {
            double dl=(double)ArrayPos[i]/100-CurLen;
            double sina=sin(CurAngle);
            double cosa=cos(CurAngle);
            double AngSpeed=(CurveEnd-CurLen)/RL;       // Угловая скорость
            CurX+=((1.0/3.0*cosa*AngAc*dl+1.0/2.0*cosa*AngSpeed)*dl+sina)*dl;
            CurY+=((1.0/3.0*sina*AngAc*dl+1.0/2.0*sina*AngSpeed)*dl+cosa)*dl;
            CurAngle+=(AngAc*dl+AngSpeed)*dl;
            CurLen+=dl;
            double dx=CurX-ArrayX[i];
            double dy=CurY-ArrayY[i];
            double CurDev=dx*dx+dy*dy;
            if (CurDev>MaxDev)
                MaxDev=CurDev;
            }
        double dl=(double)InBnd[3]/100-CurLen;  // Последний фрагмент клотоиды
        double sina=sin(CurAngle);
        double cosa=cos(CurAngle);
        double AngSpeed=(CurveEnd-CurLen)/RL;       // Угловая скорость
        CurX+=((1.0/3.0*cosa*AngAc*dl+1.0/2.0*cosa*AngSpeed)*dl+sina)*dl;
        CurY+=((1.0/3.0*sina*AngAc*dl+1.0/2.0*sina*AngSpeed)*dl+cosa)*dl;
        CurAngle+=(AngAc*dl+AngSpeed)*dl;
        }
    CurLen=(double)InBnd[3]/100;
    for (;i<ArraySize;i++)                     // Двигаемся по прямой
        {
        double dl=(double)ArrayPos[i]/100-CurLen;
        CurLen+=dl;
        CurX+=sin(CurAngle)*dl;
        CurY+=cos(CurAngle)*dl;
        double dx=CurX-ArrayX[i];
        double dy=CurY-ArrayY[i];
        double CurDev=dx*dx+dy*dy;
        if (CurDev>MaxDev)
            MaxDev=CurDev;
        }
    }
else     // Если радиус равен нулю, то есть вся линия это прямая строго вверх
    {
    for (int i=0;i<ArraySize;i++)                     // Двигаемся по прямой
        {
        double dy=(double)ArrayPos[i]/100-ArrayY[i];
        double dx=ArrayX[i];
        double CurDev=dx*dx+dy*dy;
        if (CurDev>MaxDev)
            MaxDev=CurDev;
        }
    }
return MaxDev;
}

void __fastcall TfrmCrvPlan::CalcParams(void)
{
if (FData&&FHasCurves)
    {
    int MinRad=10000;
    for (int i=0;i<ArraySize;i++)
        {
        int t=abs(ArrayRad[i]);
        if ((t<abs(MinRad))&&(t>0))
            MinRad=t;
        }
    Edit_MinR->Text=String(MinRad);
    Edit_In_Rad->Text=ArrayRad[InStart];
    Edit_Out_Rad->Text=ArrayRad[OutEnd];
    Edit_CrIn_Rad->Text=ArrayRad[CrclStart];
    Edit_CrOut_Rad->Text=ArrayRad[CrclEnd];
    Edit_DMax->Text=sqrt(GetMaxDevLen(Bounds,Radius));
    }
}

void __fastcall TfrmCrvPlan::CalcExternBounds(void)
{
if (FData&&FHasCurves)
    {
    TGeometryVal *Values=FData->Road->Geometry.Values;
    __int32 *L=FData->Road->Geometry.L;
    int GeomCount=FData->Road->Geometry.Count;
    TGeometryVal TVal;
    int pos=FData->Road->Geometry.GetMesValue(FCpPosition,TVal);
    int pos1,pos2;
    pos1=pos;
    pos2=pos;
    if (Combo_Dir->ItemIndex==0)  // прямое направление
        {
        int sgn=TVal.DirectRad>0 ? 1 : TVal.DirectRad<0 ? -1 : 0;
        while ((pos1>0)&&(Values[pos1].DirectRad*sgn>0))
            pos1--;
        int Space=WNDBNDSPACE;
        while ((pos1>0)&&(Values[pos1].DirectRad*sgn>=0)&&(Space>0))
            {pos1--;
            Space-=L[pos1+1]-L[pos1];
            }
        while ((pos2<GeomCount-1)&&(Values[pos2].DirectRad*sgn>0))
            pos2++;
        Space=WNDBNDSPACE;
        while ((pos2<GeomCount-1)&&(Values[pos2].DirectRad*sgn>=0)&&(Space>=0))
            {pos2++;
            Space-=L[pos2]-L[pos2-1];
            }
        }
    else
        {
        int sgn=TVal.UnDirectRad>0 ? 1 : TVal.UnDirectRad<0 ? -1 : 0;
        while ((pos1>0)&&(Values[pos1].UnDirectRad*sgn>0))
            pos1--;
        int Space=WNDBNDSPACE;
        while ((pos1>0)&&(Values[pos1].UnDirectRad*sgn>=0)&&(Space>0))
            {pos1--;
            Space-=L[pos1+1]-L[pos1];
            }
        while ((pos2<GeomCount-1)&&(Values[pos2].UnDirectRad*sgn>0))
            pos2++;
        Space=WNDBNDSPACE;
        while ((pos2<GeomCount-1)&&(Values[pos2].UnDirectRad*sgn>=0)&&(Space>0))
            {
            pos2++;
            Space-=L[pos2]-L[pos2-1];
            }
        }
    pos1--;
    pos2++;
    WndBounds[0]=L[pos1];
    WndBounds[1]=L[pos2];
    TestBounds();
    EditCurves();
    GetRadiusData();
    SetTrackParam();
    if (AutoCalcRad->Down)
        CalcCircleRad();
    CalcParams();
    }
}

void __fastcall TfrmCrvPlan::CalcCircleBounds(void)
{
double MinDev=1000000000;
int Besti,Bestj;
int StepCount=20;
int Step=ArraySize/(StepCount-1);
double MidPtSpace=(double)(WndBounds[1]-WndBounds[0])/(ArraySize*100); // Грубое расстояние между двумя точками
for (int i=0;i<ArraySize;i+=Step)
    for (int j=i+Step;j<ArraySize;j+=Step)
        {
        int Rad=GetCircleRad(i,j);  // Нашли радиус
        if (Rad)
            {
            double AngSpeed=1.0/(double)Rad;
            double Ang=ArrayAngle[i];
            double l=fabs(2*Ang/AngSpeed);
            int T_Start=ArrayPos[i]-l*100;
            Ang=ArrayAngle[ArraySize-1]-ArrayAngle[j];
            l=fabs(2*Ang/AngSpeed);
            int T_End=ArrayPos[j]+l*100;
            if ((T_Start>=WndBounds[0])&&(T_End<=WndBounds[1])) // Если границы в пределах зоны поворота
                {
                int TestBounds[4];
                TestBounds[0]=T_Start;
                TestBounds[1]=ArrayPos[i];
                TestBounds[2]=ArrayPos[j];
                TestBounds[3]=T_End;
                double dev=GetMaxDevLen(TestBounds,Rad);
                if (dev<MinDev)
                    MinDev=dev;
                }
            }
        }

for (int i=0;i<ArraySize;i++)      // i - точка начала поворота
    for (int j=i+1;j<ArraySize;j++)  // j - точка конца поворота
        {
        int Rad=GetCircleRad(i,j);  // Нашли радиус
        if (Rad)
            {                                 //Ищем расчетные границы поворота
            double AngSpeed=1.0/(double)Rad;
            double Ang=ArrayAngle[i];
            double l=fabs(2*Ang/AngSpeed);
            int T_Start=ArrayPos[i]-l*100;
            Ang=ArrayAngle[ArraySize-1]-ArrayAngle[j];
            l=fabs(2*Ang/AngSpeed);
            int T_End=ArrayPos[j]+l*100;
            if ((T_Start>=WndBounds[0])&&(T_End<=WndBounds[1])) // Если границы в пределах зоны поворота
                {
                int TestBounds[4];
                TestBounds[0]=T_Start;
                TestBounds[1]=ArrayPos[i];
                TestBounds[2]=ArrayPos[j];
                TestBounds[3]=T_End;
                double Dev=GetMaxDevLen(TestBounds,Rad);
                if (Dev<MinDev)
                    MinDev=Dev,Besti=i,Bestj=j;
                else
                    j+=(Dev-MinDev)/MidPtSpace;
                }
            }
        }
Bounds[1]=ArrayPos[Besti];
Bounds[2]=ArrayPos[Bestj];
CalcInOutBounds();
GetRadiusData();
CalcCircleRad();
CalcInOutBounds();
EditCurves();
SetTrackParam();
CalcParams();
}



double __fastcall TfrmCrvPlan::CalcMidleRad(int lb, int ub)
{
double AnSp=0;  // Сумма угловых скоростей
if (FData&&FHasCurves)
    {
    double prevSp;
    double curSp;
    if (ArrayRad[lb])
        curSp=1.0/(double)ArrayRad[lb];
    else
        curSp=0.0;
    for (int i=lb+1;i<=ub;i++)
        {
        prevSp=curSp;
        if (ArrayRad[i])
            {
            curSp=1/(double)(ArrayRad[i]);
            AnSp+=(curSp+prevSp)*(ArrayPos[i]-ArrayPos[i-1]);
            }
        }
    if (ArrayPos[ub]==ArrayPos[lb])
        AnSp=ArrayRad[ub];
    else if (fabs(AnSp)>0.00000001)
        AnSp=(2*(ArrayPos[ub]-ArrayPos[lb]))/AnSp;
    else
        AnSp=0;
    }
return AnSp;
}

int __fastcall TfrmCrvPlan::GetCircleRad(int beg,int end)
{
int Result;
int CirLen=ArrayPos[end]-ArrayPos[beg];
if (CirLen)
    {
    double AngSpeed=((ArrayAngle[end]-ArrayAngle[beg])*100.0)/CirLen;
    if ((AngSpeed>0.0001)||(AngSpeed<-0.0001))
        Result=1.0/AngSpeed;
    else
        Result=0;
    }
else
    Result=ArrayRad[beg];
return Result;
}

void __fastcall TfrmCrvPlan::CalcCircleRad(void)
{
if (FData&&FHasCurves)
    Edit_Rad->Text=Radius=GetCircleRad(CrclStart,CrclEnd);
}

void __fastcall TfrmCrvPlan::CalcInOutBounds(void)
{
if ((FHasCurves)&&(FData))
    {
    if (Radius)
        {
        double AngSpeed=1.0/(double)Radius;
        double Ang=ArrayAngle[CrclStart];
        double l=fabs(2*Ang/AngSpeed);
        Bounds[0]=(int(Bounds[1]/100-l+0.5))*100;
        Ang=ArrayAngle[ArraySize-1]-ArrayAngle[CrclEnd];
        l=fabs(2*Ang/AngSpeed);
        Bounds[3]=(int(Bounds[2]/100+l+0.5))*100;
        TestBounds();
        }
    }
}

void __fastcall TfrmCrvPlan::SetTrack(int mn,int mx,int pos)
{
TNotifyEvent EV=Track->OnChange;
Track->OnChange=NULL;
Track->Min=0;
Track->Max=mx;
Track->Min=mn;
Track->Position=pos;
Track->OnChange=EV;
}

void __fastcall TfrmCrvPlan::SetTrackParam(void)
{
Track->Visible=FData&&FHasCurves;
if (FData&&FHasCurves)
    {
    switch (SelTrack->ItemIndex)
        {
        case 0: SetTrack(WndBounds[0]/100,Bounds[1]/100,Bounds[0]/100);
             break;
        case 1: SetTrack(Bounds[0]/100,Bounds[2]/100,Bounds[1]/100);
             break;
        case 2: SetTrack(Bounds[1]/100,Bounds[3]/100,Bounds[2]/100);
             break;
        case 3: SetTrack(Bounds[2]/100,WndBounds[1]/100,Bounds[3]/100);
             break;
        }
    }
}

void __fastcall TfrmCrvPlan::SetViewPos(__int32 Pos)
{
FCpPosition=Pos;
FindCurveAt(Pos);
TestBounds();
EditCurves();
GetRadiusData();
SetTrackParam();
CalcParams();
}

void __fastcall TfrmCrvPlan::btSetCpPosClick(TObject *Sender)
{
if (frmVideoForm->Data==FData)
    SetViewPos(frmVideoForm->Position);
else if (MainForm->ActiveRoad)
    {
    if (MainForm->ActiveRoad->VisSet->SourceVisible(FData))
        SetViewPos(MainForm->ActiveRoad->MarkerL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::AutoCalcRadClick(TObject *Sender)
{
if (AutoCalcRad->Down)
    CalcCircleRad();
PBox->Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TfrmCrvPlan::SpeedButtonClick(TObject *Sender)
{
TSpeedButton *but=dynamic_cast<TSpeedButton*>(Sender);
if (but)
    if ((frmVideoForm->Data==FData)&&(frmVideoForm->Visible))
        {
        Bounds[but->Tag]=frmVideoForm->Position;
        TestBounds();
        EditCurves();
        GetRadiusData();
        if (AutoCalcRad->Down)
            CalcCircleRad();
        CalcParams();
        SetTrackParam();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::SelTrackChange(TObject *Sender)
{
SetTrackParam();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::TrackChange(TObject *Sender)
{
Bounds[SelTrack->ItemIndex]=Track->Position*100;
if (AutoCalcInOut->Down)
    CalcInOutBounds();
TestBounds();
EditCurves();
GetRadiusData();
if (AutoCalcRad->Down)
    CalcCircleRad();
CalcParams();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::BitBtn2Click(TObject *Sender)
{
CalcExternBounds();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::BitBtn3Click(TObject *Sender)
{
CalcCircleBounds();
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::EditExit(TObject *Sender)
{
GetCurves();
TestBounds();
EditCurves();
GetRadiusData();
SetTrackParam();
if (AutoCalcRad->Down)
    CalcCircleRad();
CalcParams();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::EditKeyPress(TObject *Sender, char &Key)
{
if (Key==13)
    EditExit(this);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCrvPlan::VideoClick(TObject *Sender)
{
if ((frmVideoForm->Data==FData)&&(frmVideoForm->Visible))
    {
    TSpeedButton *but=dynamic_cast<TSpeedButton*>(Sender);
    if (but)
        frmVideoForm->Position=Bounds[but->Tag];
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::GridSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
if (ARow>0)
    {
    TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][ARow]);
    if ((Par)&&(ARow!=EditIndex))
        {
        SetViewPos((Par->L[0]+Par->L[3])>>1);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::btnDeleteClick(TObject *Sender)
{
if (EditIndex)
    {
    TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][EditIndex]);
    if (Par->InCrv)
        FData->DeleteObject(Par->InCrv);
    if (Par->OutCrv)
        FData->DeleteObject(Par->OutCrv);
    if (Par->CrcCrv)
        FData->DeleteObject(Par->CrcCrv);
    delete Grid->Objects[0][EditIndex];
    Grid->Objects[0][EditIndex]=NULL;
    while (EditIndex<CurvesCount)
        {
        Grid->Objects[0][EditIndex]=Grid->Objects[0][EditIndex+1];
        for (int j=0;j<COLCOUNT;j++)
            Grid->Cells[j][EditIndex]=Grid->Cells[j][EditIndex+1];
        EditIndex++;
        }
    CurvesCount--;
    if (CurvesCount)
        Grid->RowCount=CurvesCount+1;
    else
        Grid->RowCount=2;
    SetViewPos(FCpPosition);
    }
Sinchronize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::GridClick(TObject *Sender)
{
Grid->Options<<goRowSelect;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_PosExit(TObject *Sender)
{
int Pos=Edit_Pos->Text.ToInt();
SetViewPos(Pos*100);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_PosKeyPress(TObject *Sender, char &Key)
{
if (Key==13)
    Edit_PosExit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::btnSaveClick(TObject *Sender)
{
int i;
for (i=1;i<=CurvesCount;i++)
    if (i!=EditIndex)
        {
        TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][i]);
        if (Par)
            {
            if ((Bounds[3]>Par->L[0])&&(Bounds[0]<Par->L[3]))
                break;
            }
        }
if (i<=CurvesCount)
    ShowMessage("Введенный участок поворота имеет пересечения с другими участками поворотов, что недопустимо");
else
    {
    TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][EditIndex]);
    if (Par)
        {
        Par->Rad=Radius;
        if (Radius>0)
            Par->Direction=ckRightCurve;
        else if (Radius<0)
            Par->Direction=ckLeftCurve;
        else if (ArrayRad[CrclStart]>0)
            Par->Direction=ckRightCurve;
        else
            Par->Direction=ckLeftCurve;
        for (int i=0;i<4;i++)
            Par->L[i]=Bounds[i];
        Par->WriteInGrid(Grid,EditIndex);
        }
    }
Sinchronize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::btnAddClick(TObject *Sender)
{
if (!FHasCurves)
    {
    int i;
    int LB=0;
    int UB=1000000000;
    for (i=1;i<=CurvesCount;i++)
        {
        TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][i]);
        if (Par)
            {
            if ((FCpPosition>Par->L[3])&&(LB<Par->L[3]))
                LB=Par->L[3];
            if ((FCpPosition<Par->L[0])&&(UB>Par->L[0]))
                UB=Par->L[0];
            if ((FCpPosition<Par->L[3])&&(FCpPosition>Par->L[0]))
                break;
            }
        }
    if (i<=CurvesCount)
        ShowMessage("Невозможно добавить участок поворота, так как участок поворота в этой точке уже введен");
    else
        {
         TCurveParam *Param=new TCurveParam(NULL,NULL,NULL);
         if (LB<FCpPosition-2000)
            LB=FCpPosition-2000;
         if (UB>FCpPosition+2000)
            UB=FCpPosition+2000;
         Param->L[0]=LB;
         Param->L[1]=(FCpPosition+LB)>>1;
         Param->L[2]=(FCpPosition+UB)>>1;
         Param->L[3]=UB;
         Param->Rad=Radius;
         Param->Direction=ckRightCurve;
         Grid->RowCount=CurvesCount+2;
         for (EditIndex=CurvesCount;EditIndex>0;EditIndex--)
            {
            TCurveParam *Par=dynamic_cast<TCurveParam*>(Grid->Objects[0][EditIndex]);
            if (Par)
                {
                if (Par->L[3]<=Param->L[0])
                    break;
                Grid->Objects[0][EditIndex+1]=Grid->Objects[0][EditIndex];
                for (int j=0;j<COLCOUNT;j++)
                    Grid->Cells[j][EditIndex+1]=Grid->Cells[j][EditIndex];
                }
            }
         EditIndex++;
         Param->WriteInGrid(Grid,EditIndex);
         CurvesCount++;
         SetViewPos(FCpPosition);
         CalcExternBounds();
        }
    Sinchronize();
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmCrvPlan::PBoxPaint(TObject *Sender)
{
DrawCurve();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_RadExit(TObject *Sender)
{
Radius=Edit_Rad->Text.ToInt();
CalcParams();
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_RadKeyPress(TObject *Sender, char &Key)
{
if (Key==13)
    Edit_RadExit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_BndExit(TObject *Sender)
{
GetWndBounds();
TestBounds();
EditCurves();
GetRadiusData();
SetTrackParam();
CalcParams();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::Edit_BndKeyPress(TObject *Sender, char &Key)
{
if (Key==13)
    Edit_BndExit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCrvPlan::BitBtn1Click(TObject *Sender)
{
if ((FHasCurves)&&(FData))
    {
    CalcInOutBounds();
    EditCurves();
    GetRadiusData();
    SetTrackParam();
    CalcParams();
    }
}
//---------------------------------------------------------------------------


