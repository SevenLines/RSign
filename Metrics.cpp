//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Metrics.h"
#include "SettingFrm.h"
//---------------------------------------------------------------------------
#include <mem.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

bool __fastcall TRoadPoint::CrossPoint(__int32 BaseL1,__int32 BaseX1,__int32 BaseL2,__int32 BaseX2,double angle1,double angle2)
{
bool Res;
double sina1=sin(angle1);
double sina2=sin(angle2);
double cosa1=cos(angle1);
double cosa2=cos(angle2);
double det=sina2*cosa1-sina1*cosa2;
if (fabs(det)>0.0001)
    {
    double dx=BaseX2-BaseX1;
    double dl=BaseL2-BaseL1;
    double t=(sina2*dl-cosa2*dx)/det;
    X=BaseX1+t*sina1;
    L=BaseL1+t*cosa1;
    Res=true;
    }
else
    Res=false;
return Res;
}

void __fastcall TRoadPoint::LeepToLine(__int32 BaseL,__int32 BaseX,double angle)
{
        double A=-sin(angle);
        double B=cos(angle);
        double V=(L-BaseL)*A+(X-BaseX)*B;
        L-=((double)A*V);
        X-=((double)B*V);
}

bool __fastcall TRoadPoint::LeepToPolyline(__int32 BaseL,__int32 BaseX,__int32 shift,double angle, TPolyline *Poly)
{
bool Res=false;
int n=Poly->Count;
TRoadPoint *p=Poly->Points;
if (n>0)
    {
    int napr;
    if (((angle>0)&&(angle<=M_PI))||(angle<-M_PI/2.0))
        napr=-1;
    else
        napr=1;
    if (BaseX<(Poly->FindX(BaseL)+shift))
        napr=-napr;
    int Seg=Poly->FindSeg(BaseL);
    int spos,epos;
    if (Seg>=0)
        if (napr>0)
            spos=Seg,epos=n-1;
        else
            spos=Seg+1,epos=0;
    else if (BaseL<p[0].L)
        if (napr>0)
            spos=0,epos=n-1;
        else
            spos=epos=0;
    else
        if (napr<0)
            spos=n-1,epos=0;
        else
            spos=epos=0;
    double tana=fabs(tan(angle));
    int next;
    int DL,DX;
    for (;spos!=epos;spos+=napr)
        {
        next=spos+napr;
        DL=p[next].L-BaseL;
        DX=p[next].X+shift-BaseX;
        if (abs(DX)<tana*abs(DL))
            break;
        }
    if (spos!=epos)
        {
        double dx=sin(angle);
        double dl=cos(angle);
        int l_dl=p[next].L-p[spos].L;
        int l_dx=p[next].X-p[spos].X;
        double det=dx*l_dl-dl*l_dx;
        if (fabs(det)>0.00001)
            {
            double t=(l_dl*DX-l_dx*DL)/det;
            L=BaseL+dl*t;
            X=BaseX+dx*t;
            Res=true;
            }
        }
    }
return Res;
}

__fastcall TExtPolyline::TExtPolyline(void)
{
DirectionVal=1;
Count=0;
Points=NULL;
Codes=NULL;
Flags=NULL;
}
__fastcall TExtPolyline::TExtPolyline(int n)
{
DirectionVal=1;
Count=n;
Points=new POINT [n];
Codes=new TPointCode [n];
Flags=new int [n];
}

__fastcall TExtPolyline::TExtPolyline(int n,int defcode)
{
DirectionVal=1;
Count=n;
Points=new POINT [n];
Codes=new TPointCode [n];
Flags=new int [n];
for(int i=0;i<n;i++)
    {
    Codes[i]=defcode;
    Flags[i]=0;
    }
}

void __fastcall TExtPolyline::CopyExtPolyline(TExtPolyline *Source)
{
DirectionVal=Source->DirectionVal;
Count=Source->Count;
Points=new POINT[Count];
memcpy(Points,Source->Points,sizeof(POINT)*Count);
Codes=new TPointCode [Count];
memcpy(Codes,Source->Codes,sizeof(__int32)*Count);
Flags=new int [Count];
memcpy(Flags,Source->Flags,sizeof(__int32)*Count);
}

__fastcall TExtPolyline::TExtPolyline(TExtPolyline *Source)
{
CopyExtPolyline(Source);
}

void __fastcall TExtPolyline::DisSelect(void)
{
for (int i=0;i<Count;i++)
    Flags[i]=0;
}

void __fastcall TExtPolyline::Select(int n)
{
if ((n>=0)&&(n<Count))
    Flags[n]|=1;
}

__fastcall TExtPolyline::TExtPolyline(TExtPolyline *Source,int ofsx,int ofsy)
{
CopyExtPolyline(Source);
for (int i=0;i<Count;i++)
    Points[i].x+=ofsx,Points[i].y+=ofsy;
}


/*
__fastcall TExtPolyline::TExtPolyline(TExtPolyline* Source,double offset)
{
if ((abs(offset)<0.5)||(Source->Count<2))
    CopyExtPolyline(Source);
else if (Source->Count==2)
    {
    CopyExtPolyline(Source);
    double dx=Points[1].x-Points[0].x;
    double dy=Points[1].y-Points[0].y;
    double len=sqrt(dx*dx+dy*dy);
    if (len>0.5)
        {
        Points[0].x=Points[0].x+dy*offset/len+0.5;
        Points[0].y=Points[0].y-dx*offset/len+0.5;
        Points[1].x=Points[1].x+dy*offset/len+0.5;
        Points[1].y=Points[1].y-dx*offset/len+0.5;
        }
    }
else
    {
    int i;
    POINT *SP=Source->Points;
    int SCount=Source->Count;
    TPointCode *SCodes=Source->Codes;
    if (SCodes[0].Connection()==2)
        i=2;
    else if (SCodes[SCount-1].Connection()==2)
        i=1;
    else
        i=0;
    while (i<SCount)
        {
        int c1=SCodes[(i+1)%SCount].Connection();
        int c2=SCodes[(i+2)%SCount].Connection();
        while (((c1!=1)||(c2==2))&&(i<SCount) // Ищем начало сегмента из ломаной
            {
            i++;
            c1=c2;
            c2=SCodes[(i+2)%SCount].Connection();
            }
        int St=i;
        i++;
        c1=c2;
        c2=SCodes[(i+2)%SCount].Connection();
        while (((c1==1)&&(c2!=2))&&(i<SCount) // Ищем конец сегмента из ломаной
            {
            i++;
            c1=c2;
            c2=SCodes[(i+2)%SCount].Connection();
            }
        int En=i%SCount;

        }
    }
// Надо посчитать количество нарисованных углов
/*
int SCount=Source->Count;
int *SCodes=Source->Codes;
POINT *SPoints=Source->Points;
int k=0;
for (int i=0;i<SCount;i++)
    {
    if (SCodes[i]==1)    // К узлу идет прямая
        {
        int ni=(i+1)%SCount;
        if (SCodes[ni]==1)    // К следующему узлу тоже прямая
            {
            int nni=(ni+1)%SCount;
            if (SCodes[nni]!=2)  // не начало участка Безье
                {
                int pi=(i+SCount-1)%SCount;
                if (SCodes[pi]!=2)  // не конец участка Безье
                    {
                    int dx1=SPoints[ni].x-SPoints[pi].x;
                    int dx2=SPoints[i].x-SPoints[pi].x;
                    int dy1=SPoints[ni].y-SPoints[pi].y;
                    int dy2=SPoints[i].y-SPoints[pi].y;
                    int s=dx1*dy2-dx2*dy1;
                    if (s*offset<0)        // поворот в сторону
                        k++;
                    }
                }
            }
        }
    }

Count=SCount+k;
Points=new POINT [Count];
Codes=new __int32 [Count];
}  */

__fastcall TExtPolyline::~TExtPolyline(void)
{
delete[] Points;
delete[] Codes;
delete[] Flags;
Points=NULL;
Codes=NULL;
Flags=NULL;
Count=0;
}

void __fastcall TExtPolyline::DrawBezierSeg(void *dc,int n)
{
int n1=(n+1)%Count;
int p1=(n+Count-1)%Count;
POINT pt[3];
pt[0].x=Points[p1].x;
pt[0].y=Points[p1].y;
pt[1].x=Points[n].x;
pt[1].y=Points[n].y;
pt[2].x=Points[n1].x;
pt[2].y=Points[n1].y;
PolyBezierTo(dc,pt,3);
}

void __fastcall TExtPolyline::DrawArcSeg(void *dc,int n)
{
LineTo(dc,Points[n].x,Points[n].y);
}

void __fastcall TExtPolyline::DrawPoly(void *dc,void *pen1,void *pen2)
{
if (Count>0) {
   void *oldpen=SelectObject(dc,pen1);
   MoveToEx(dc,Points[Count-1].x,Points[Count-1].y,NULL);
   for (int i=0;i<Count;i++)
    {
    if (Codes[i].Visible())
        SelectObject(dc,pen1);
    else
        SelectObject(dc,pen2);

    int cd=Codes[i].Connection();
    if ((cd==2)&&(Count>2))
        {
        POINT pt[4];
        int p2=(i+Count-2)%Count;
        MoveToEx(dc,Points[p2].x,Points[p2].y,NULL);
        DrawBezierSeg(dc,i);
        MoveToEx(dc,Points[i].x,Points[i].y,NULL);
        }
    else if ((cd==1)&&(Count>2))
        DrawArcSeg(dc,i);
    else
        LineTo(dc,Points[i].x,Points[i].y);
    }
   SelectObject(dc,oldpen);
   }
}

void __fastcall TExtPolyline::PolyDraw(void *dc, void *pen, TRect &VR)
{
void *oldpen=SelectObject(dc,pen);
if (Count>2)
    {
    byte *C=new byte [Count];
    bool *InRect=new bool [Count];
    bool *CrossRect=new bool [Count];
    for (int i=0;i<Count;i++)
        {
        InRect[i]=(Points[i].x<=VR.right)&&(Points[i].x>=VR.left)&&(Points[i].y<VR.bottom)&&(Points[i].y>VR.top);
        int prev_i=(i+Count-1)%Count;
        CrossRect[i]=((Points[i].x>VR.right)&&(Points[prev_i].x<VR.left))||
                      ((Points[prev_i].x>VR.right)&&(Points[i].x<VR.left))||
                      ((Points[prev_i].y>VR.bottom)&&(Points[i].x<VR.top))||
                      ((Points[i].y>VR.bottom)&&(Points[prev_i].x<VR.top));
        }

    for (int i=0;i<Count;i++)
        {
        int prev_i=(i+Count-1)%Count;
        int next_i=(i+1)%Count;
        if (!Codes[i].Visible())
            C[i]=PT_MOVETO;
        else if ((Codes[i].Connection()==2)&&(i>0)&&(i+1<Count))
            {
            if (InRect[prev_i]||InRect[i]||InRect[next_i])
                {C[i-1]=C[i]=C[i+1]=PT_BEZIERTO;i++;}
            else
                {C[i-1]=C[i]=C[i+1]=PT_MOVETO;i++;}
            }
        else
            {
            if (InRect[prev_i]||InRect[i]||CrossRect[i])
                C[i]=PT_LINETO;
            else
                C[i]=PT_MOVETO;
            }

        }
    C[0]=PT_MOVETO;
    if (Codes[0].Visible())
        C[Count-1]|=PT_CLOSEFIGURE;
    ::PolyDraw(dc,Points,C,Count);
    delete[] C;
    delete[] InRect;
    delete[] CrossRect;
    }
else
    {
    Polyline(dc,Points,Count);
    }
SelectObject(dc,oldpen);
}

void __fastcall TExtPolyline::CreatePath(void *dc)
{
BeginPath(dc);
void *oldpen=SelectObject(dc,GetStockObject(BLACK_PEN));
int i=0;
if (Count>2)
    {
    if (Codes[0].Connection()==2)
        i=2;
    else if (Codes[Count-1].Connection()==2)
        i=1;
    int p1=(i+Count-1)%Count;
    MoveToEx(dc,Points[p1].x,Points[p1].y,NULL);
    for (;i<Count;i++)
        {
        int n1=(i+1)%Count;
        if (Codes[i].Connection()==1)
            DrawArcSeg(dc,i);
        else if (Codes[n1].Connection()==2)
            {
            DrawBezierSeg(dc,n1);
            i+=2;
            }
        else
            LineTo(dc,Points[i].x,Points[i].y);
        }
    }
else
    {
    Polyline(dc,Points,Count);
    }
EndPath(dc);
SelectObject(dc,oldpen);
}

void __fastcall TExtPolyline::DrawTo(void *dc,void *pen,void *brush)
{
CreatePath(dc);
if (brush)
    {
    void* oldbrush=SelectObject(dc,brush);
    if (pen)
        {
        void *oldpen=SelectObject(dc,pen);
        StrokeAndFillPath(dc);
        SelectObject(dc,oldpen);
        }
    else
        FillPath(dc);
    SelectObject(dc,oldbrush);
    }
else if (pen)
    {
    void *oldpen=SelectObject(dc,pen);
    StrokePath(dc);
    SelectObject(dc,oldpen);
    }
}

double __fastcall TExtPolyline::LenTo(POINT Cur,POINT &Ret,int &index)
{
double Result;
if (Count>0)
    {
    double dx=Cur.x-Points[0].x;
    double dy=Cur.y-Points[0].y;
    double lpred,lcur=dx*dx+dy*dy;
    Result=lcur;
    Ret.x=Cur.x;
    Ret.y=Cur.y;
    index=0;
    // Бежим по отрезкам. lpred- расстояние до начала отрезка от точки
    // lcur - расстояние до конца отрезка
    // l - длина отрезка
    for (int j=1;j<Count;j++)
        {
        lpred=lcur;
        dx=Cur.x-Points[j].x;
        dy=Cur.y-Points[j].y;
        lcur=dx*dx+dy*dy;
        if (lcur<Result)
            {
            Result=lcur;
            Ret.x=Points[j].x;
            Ret.y=Points[j].y;
            index=j-1;
            }
        double dx1=Points[j-1].x-Points[j].x;
        double dy1=Points[j-1].y-Points[j].y;
        double l=dx1*dx1+dy1*dy1;
// Если точка проецируется  на отрезок
        if ((lpred<lcur+l)&&(lcur<lpred+l))
            {
            double ln=(dx*dy1-dy*dx1);
            ln=ln*ln;
            ln/=l;
            if (ln<Result)
                {
                Result=ln;
                double dl=sqrt(lcur-ln);
                double sl=sqrt(l);
                Ret.x=Points[j].x+dx1*dl/sl+0.5;
                Ret.y=Points[j].y+dy1*dl/sl+0.5;
                index=j-1;
                }
            }
        }
    Result=sqrt(Result);
    }
else
    {
    Result=0;
    Ret.x=Cur.x;
    Ret.y=Cur.y;
    index=-1;
    }
return Result;
}


__fastcall TPolyline::TPolyline(void)
{
FCount=FCapacity=0;
FPoints=NULL;
}

__fastcall TPolyline::TPolyline(__int32 NCount)
{
FCount=NCount;
FCapacity=NCount+INCCAPVALUE;
FPoints=new TRoadPoint[FCapacity];
}

__fastcall TPolyline::TPolyline(__int32 NCount,__int32 id)
{
FCount=NCount;
FCapacity=NCount+INCCAPVALUE;
FPoints=new TRoadPoint[FCapacity];
FId=id;
}

__fastcall TPolyline::TPolyline(TPolyline *Poly,__int32 id)
{
FId=id;
FCount=FCapacity=0;
FPoints=NULL;
SetCount(Poly->Count);
for (int i=0;i<FCount;i++)
    FPoints[i]=(*Poly)[i];
}

__fastcall TPolyline::~TPolyline(void)
{
FreePoints();
}

void __fastcall TPolyline::FreePoints(void)
{
delete[] FPoints;
FPoints=NULL;
FCount=FCapacity=0;
}

void __fastcall TPolyline::CopyPoints(TPolyline *src) {
FreePoints();
SetCount(src->Count);
for (int i=0;i<FCount;i++)
   FPoints[i]=src->Points[i];
}

void __fastcall TPolyline::DeletePoint(int num)
{
if ((num>=0)&&(num<FCount))
    {
    for (int i=num+1;i<FCount;i++)
        FPoints[i-1]=FPoints[i];
    FCount--;
    }
}

void __fastcall TPolyline::InsertPoint(TRoadPoint& pt,int n)
{
if (n<=FCount)
    {
    SetCount(FCount+1);
    for (int i=FCount-1;i>n;i--)
        FPoints[i]=FPoints[i-1];
    FPoints[n]=pt;
    }
}

void __fastcall TPolyline::LoadFromStream(TMemoryStream *Mem)
{
int *P=(int*)Mem->Memory;
for (int i=0;i<FCount;i++)
    {
    FPoints[i].L=P[6*i];
    FPoints[i].X=P[6*i+1];
    FPoints[i].Code=P[6*i+2];
    FPoints[i].BasePar1=P[6*i+3];
    FPoints[i].BasePar2=P[6*i+4];
    FPoints[i].LeepPar=P[6*i+5];
    }
}

void __fastcall TPolyline::SaveToStream(TMemoryStream *Mem)
{
Mem->Size=FCount*sizeof(int)*6;
int *P=(int*)Mem->Memory;
for (int i=0;i<FCount;i++)
    {
    P[6*i]=FPoints[i].L;
    P[6*i+1]=FPoints[i].X;
    P[6*i+2]=FPoints[i].Code();
    P[6*i+3]=FPoints[i].BasePar1;
    P[6*i+4]=FPoints[i].BasePar2;
    P[6*i+5]=FPoints[i].LeepPar;
    }
}

bool __fastcall TPolyline::GetMinMax(int &Min,int &Max)
{
bool Res=false;
if (FCount)
    {
    Res=true;
    Min=FPoints[0].L;
    Max=Min;
    for (int i=1;i<FCount;i++)
        {
        if (Min>FPoints[i].L)
            Min=FPoints[i].L;
        if (Max<FPoints[i].L)
            Max=FPoints[i].L;
        }
    }
return Res;
}

bool __fastcall TPolyline::GetMinMaxVal(int &Min,int &Max)
{
bool Res=false;
if (FCount)
    {
    Res=true;
    Min=FPoints[0].X;
    Max=Min;
    for (int i=1;i<FCount;i++)
        {
        if (Min>FPoints[i].X)
            Min=FPoints[i].X;
        if (Max<FPoints[i].X)
            Max=FPoints[i].X;
        }
    }
return Res;
}

void __fastcall TPolyline::Dump(ofstream& out)
{
out<<FId<<" "<<FCount<<endl;
for (int i=0;i<FCount;i++)
  out<<FPoints[i].L<<" "<<FPoints[i].X<<" "<<FPoints[i].Code()<<" "<<
  FPoints[i].LeepPar<<" "<<FPoints[i].BasePar1<<" "<<FPoints[i].BasePar2<<endl;
}

void __fastcall TPolyline::LoadDump(ifstream& in)
{
int npt;
char c[1024];
in>>FId;
in>>npt;
Count=npt;
in.getline(c,1024);
for (int i=0;i<npt;i++)
    {
    int L,X,C,P1,P2,P3;
    in>>L>>X>>C>>P1>>P2>>P3;
    in.getline(c,1024);
    Points[i]=TRoadPoint(L,X,C,P1,P2,P3);
    }
}

void __fastcall TPolyline::Trim(void)
{
int i=0;
while (i<FCount-2)
    {
    if (FPoints[i].X)
        break;
    i++;
    }

if (i) // i Номер последнего нуля
    {
    for (int j=i;j<FCount;j++)
        FPoints[j-i]=FPoints[j];
    FCount-=i;
    }
while ((FCount>2)&&(FPoints[FCount-1].X==0))  // Убираем все нули 
    FCount--;
}

double __fastcall TPolyline::Length(void) {
   double L=0;
   for (int i=1;i<FCount;i++) {
      double dl=FPoints[i].L-FPoints[i-1].L;
      double dx=FPoints[i].X-FPoints[i-1].X;
      L+=sqrt(dl*dl+dx*dx);
   }
   return L;
}


void __fastcall TPolyline::ChangeOrientation(void)
{
int n=FCount>>1;
for (int i=0,j=FCount-1;i<n;i++,j--)
    {
    TRoadPoint tmp=FPoints[i];
    FPoints[i]=FPoints[j];
    FPoints[j]=tmp;
    }
}


void __fastcall TPolyline::ReplaceNullPart(TPolyline *Ref)
{
if (Ref->Count)
    {
    for (int i=1;i<FCount;i++)
        {
        if ((FPoints[i-1].X==0)&&(FPoints[i].X==0))
            {
            TPolyline tmp;
            tmp.CopyAndCut(Ref,FPoints[i-1].L,FPoints[i].L);
            int n=FCount;
            int s=tmp.Count-2;
            SetCount(FCount+tmp.Count-2);
            for (int j=n-1;j>i;j--)
                FPoints[j+s]=FPoints[j];
            for (int j=0;j<tmp.Count;j++)
                FPoints[i+j-1]=tmp[j];
            i+=s;
            }
        }
    }
}

void __fastcall TPolyline::AddPoly(TPolyline * Added)
{
if (Added->Count)
    {
    int Lmin=(*Added)[0].L;
    int Lmax=(*Added)[Added->Count-1].L;
    int i,j;
    // В текущей полилинии находим первую точку, расположенную до первой точки
    // добавляемой полилинии. Участок после этой точки будет заменен на добавленный
    for (i=FCount-1;i>=0;i--)  // Цикл от последней точки, поскольку предполагается
        if (FPoints[i].L<Lmin) // Что добавляемый участок пристыковывается к существующему
            break;
    i++;                       // Теперь i - первая точка текущей линии которая находится после начала добавляемой линии
    for (j=FCount-1;j>=0;j--)    // Находим точку следующую после последней точки
        if (FPoints[j].L<Lmax)   // добавляемой полилинии
            break;
    j++;
    int FOldCount=FCount;
    if ((i==FCount)&&(FCount>0))  // Добавляемая линия находится дальше конца текущей линии
        {                        // При этом отсутствующий участок делаем нулевым
        SetCount(FCount+2+Added->Count);
        FPoints[i]=FPoints[i-1];
        FPoints[i].X=0;
        i++;
        FPoints[i]=(*Added)[0];
        FPoints[i].X=0;
        i++;
        for (int k=0;k<Added->Count;k++)
            FPoints[i+k]=(*Added)[k];
        }
    else if ((j==0)&&(FCount>0)) // Добавляемая линия находится до начала текущей
        {                        // При этом отсутствующий участок делаем нулевым
        SetCount(FCount+2+Added->Count);
        int mv=2+Added->Count;
        for (int k=FOldCount-1;k>=0;k--)
            FPoints[k+mv]=FPoints[k];
        for (int k=0;k<Added->Count;k++)
            FPoints[k]=(*Added)[k];
        FPoints[Added->Count]=FPoints[Added->Count-1];
        FPoints[Added->Count].X=0;
        FPoints[Added->Count+1]=FPoints[Added->Count+2];
        FPoints[Added->Count+1].X=0;
        }
    else                  // Добавляемая линия пересекает текущую
        {
        int n=0;
        bool first0=false;
        bool last0=false;
        if (i>0)
            if (FPoints[i-1].X==0)
                n++,first0=true;
        if (j<FCount)
            if (FPoints[j].X==0)
                n++,last0=true;
        SetCount(FCount+Added->Count+i-j+n);
        int mv=Added->Count+i-j+n;
        if (mv>0)   // В полученной линии точек больше, поэтому точки надо сдвинуть вперед
            for (int k=FOldCount-1;k>=j;k--)
                FPoints[k+mv]=FPoints[k];
        else if (mv<0) // В полученной линии точек меньше, поэтому точки надо сдвинуть назад
            for (int k=j;k<FOldCount;k++)
                FPoints[k+mv]=FPoints[k];
        if (first0)
            {
            FPoints[i]=(*Added)[0];
            FPoints[i].X=0;
            i++;
            }
        for (int k=0;k<Added->Count;k++)
            FPoints[i+k]=(*Added)[k];
        i+=Added->Count;
        if (last0)
            {
            FPoints[i]=FPoints[i-1];
            FPoints[i].X=0;
            }
        }
    }
}

void __fastcall TPolyline::AddLine(bool b,int L1, int L2, int X)
{
if (L1<=L2)  // Прочие участки не обрабатываются
    {
    if (FCount==0)
        {
        SetCount(2);
        Points[0].L=L1;
        Points[0].X=X;
        Points[1].L=L2;
        Points[1].X=X;
        }
    else if (Points[FCount-1].L==L1)
        {
        int add;
        if (L2>L1)
            add=2;
        else
            add=1;
        if (FCount>1)
            if (Points[FCount-2].L==L1) // Уже есть 2 точки на отрезке
                add--;
        SetCount(FCount+add);
        Points[FCount-1].L=L2;
        Points[FCount-1].X=X;
        if ((add)&&(L2!=L1))
            {
            Points[FCount-2].L=L1;
            Points[FCount-2].X=X;
            }
        }
    else if (Points[FCount-1].L<L1)
        {
        if (!b)
            AddLine(b,Points[FCount-1].L,L1,0);
        SetCount(FCount+2);
        Points[FCount-2].L=L1;
        Points[FCount-2].X=X;
        Points[FCount-1].L=L2;
        Points[FCount-1].X=X;
        }
    }
}

__int32 __fastcall TPolyline::FindSeg(__int32 L)
{
int Res=-1;
if (Count>0)                // Ищем точку i что FPoints[i].L>=L и FPoints[i-1].L<=L
    if ((FPoints[0].L<=L)&&(FPoints[Count-1].L>=L))
        {
        int b=Count-1;            // Предусловие цикла FPoints[a-1].L<=L и FPoints[b].L>=L
        int a=1;
        while (a<b)
            {
            int c=(a+b)>>1;
            if (FPoints[c].L<L)
                a=c+1;
            else b=c;
            }
        Res=a-1;
        }
return Res;
}

__int32 __fastcall TPolyline::FindX(__int32 L1)
{
__int32 Res;
if (FCount>0)
    {
    if (L1<=FPoints[0].L)
        Res=FPoints[0].X;
    else if (L1>=FPoints[FCount-1].L)
        Res=FPoints[FCount-1].X;
    else
        {
        int Seg=FindSeg(L1);
        if (Seg>=0)
            {
            __int32 DL=Points[Seg+1].L-Points[Seg].L;
            __int32 DX=Points[Seg+1].X-Points[Seg].X;
            Res=Points[Seg].X+(double)DX*(L1-Points[Seg].L)/DL;
            }
        else
            Res=0;
        }
    }
else
    Res=0;
return Res;
}

void __fastcall TPolyline::CopyAndCut(TPolyline* Poly,__int32 L1,__int32 L2)
{
int j,i;
int s=0;
FreePoints();
TRoadPoint *Sour=Poly->Points;
int n=Poly->Count;
// Здесь можно написать двоичный поиск.
for (i=0;i<n;i++)     // i - номер первой точки в области вывода
   if (Sour[i].L>=L1)
      break;

for (j=i;j<n;j++)       // j - первая точка за областью вывода
   if (Sour[j].L>L2)
      break;

if ((i==n)||(j==0))
    return;         // Точки начинаются за областью вывода
SetCount(j-i+2);
if (i>0)
    {
    FPoints[s].L=L1;
    int DL=Sour[i].L-Sour[i-1].L;
    FPoints[s].X=Sour[i-1].X+(double)(Sour[i].X-Sour[i-1].X)*(L1-Sour[i-1].L)/(DL);
    s++;
    }
memcpy(FPoints+s,Sour+i,(j-i)*sizeof(TRoadPoint));
s+=j-i;
if ((j<n)&&(j>0))
    {
    FPoints[s].L=L2;
    int DL=Sour[j].L-Sour[j-1].L;
    FPoints[s].X=Sour[j-1].X+(double)(Sour[j].X-Sour[j-1].X)*(L2-Sour[j-1].L)/(DL);
    s++;
    }
FCount=s;
}

void __fastcall TPolyline::SetCount(__int32 NCount)
{
if (NCount>=0)
    {
    if (NCount<FCapacity)
        FCount=NCount;
    else
        {
        int NCapacity=NCount+INCCAPVALUE;
        TRoadPoint *NPoints=new TRoadPoint[NCapacity];
        memcpy(NPoints,FPoints,FCount*sizeof(TRoadPoint));
        delete[] FPoints;
        FPoints=NPoints;
        FCapacity=NCapacity;
        FCount=NCount;
        }
    }
}
// Функция возвращает координату X по координате L
// При этом известна точка n, такая что Points[n].L>=L, а
// Points[n-1].L<L, n>0;
// и Points[n].L<=L,
// То есть предыдущая точка меньше чем текущая (если она есть)
//  Если точка на отрезке то n надо увеличить
int __fastcall TPolyline::SumGetXPred(int L,int &n)
{
int X;
int L1=Points[n].L;
if (L==L1)  // Точка на конце отрезка
    {
    X=FPoints[n].X;
    n++;
    }
else if ((n>0)&&(n<Count)) //Точка внутри отрезка
    {
    int LC=FPoints[n].L;
    int XC=FPoints[n].X;
    int LP=FPoints[n-1].L;
    int XP=FPoints[n-1].X;
    X=XP+((XC-XP)*(L-LP))/(LC-LP);
    }
else
    X=0;       //Точка вне линии
return X;
}
// Функция возвращает координату X по координате L
// При этом известна точка n, такая что Points[n].L<=L,
// а Points[n+1].L>L, n<Count-1
// То есть следующая точка больше чем текущая (если она есть)
//  Если точка на отрезке то n надо увеличить
int __fastcall TPolyline::SumGetXNext(int L,int &n)
{
int X;
int L1=Points[n].L;
if (L==L1)  // Точка на конце отрезка
    {
    X=FPoints[n].X;
    n++;
    }
else if ((n>=0)&&(n<=Count-1))
    {
    int LC=FPoints[n].L;
    int XC=FPoints[n].X;
    int LN=FPoints[n+1].L;
    int XN=FPoints[n+1].X;
    X=XC+((XN-XC)*(L-LC))/(LN-LC);
    }
else
    X=0;
return X;
}

void __fastcall TPolyline::Sum(TPolyline *Fir,TPolyline *Sec,int K1,int K2)
{
SetCount(Fir->Count+Sec->Count);
int k,i,j;
k=i=j=0;
int n1=Fir->Count;
int n2=Sec->Count;
while ((i<n1)||(j<n2))
    {
// Инвариант: i-1 точка имеет координату L меньшую, чем i. Аналогично j.
    int L;
// Находим L, такую что если одна из линий закончилась, то точка из другой линии, иначе
// L - минимум из координат
    if (i<n1)
        {
        int L1=Fir->Points[i].L;
        if (j<n2)
            {
            int L2=Sec->Points[j].L;
            if (L1<L2)
                L=L1;
            else
                L=L2;
            }
        else
            L=L1;
        }
    else
        L=Sec->Points[j].L;

// В силу инварианта вызов корректный. Либо i либо j увеличатся. (возможно обе)
    int X1=Fir->SumGetXPred(L,i);
    int X2=Sec->SumGetXPred(L,j);
    Points[k].L=L;
    Points[k].X=X1*K1+X2*K2;
    k++;

// Находим точку, такую что следующая точка имеет большую L.
    while (i<n1-1)
        {
        if (L!=Fir->Points[i+1].L)
            break;
        i++;
        }
    while (j<n2-1)
        {
        if (L!=Sec->Points[j+1].L)
            break;
        j++;
        }
    if ((L==Fir->Points[i].L)||(L==Sec->Points[j].L))  // То есть в хотя бы одной линии с одной координатой L есть хотя бы 2 точки
        {
        if (L==Fir->Points[i].L)
            X1=Fir->SumGetXNext(L,i);
        if (L==Sec->Points[j].L)
            X2=Sec->SumGetXNext(L,j);
        Points[k].L=L;
        Points[k].X=X1*K1+X2*K2;
        k++;
        }
// Если текущая точка имеет координату L, то переходим к следующей. То есть
// инвариант восстановлен
    }
SetCount(k);
}

void __fastcall TPolyline::MulDiv(int Mul,int Div)
{
for (int i=0;i<FCount;i++)
    FPoints[i].X=(FPoints[i].X*Mul)/Div;
}

void __fastcall TPolyline::AddX(int DX)
{
for (int i=0;i<FCount;i++)
    FPoints[i].X+=DX;
}

void __fastcall TPolyline::MakeWidePart(TPolyline *P,int Par1,int RoundVal)
{
int n=P->Count;
int *Markers=new int [n+1]; // Последний - стражник
double *SegSquare=new double [n]; // Площадь участка под отрезком от n до n+1 точки
double *PartSquare=new double [n]; // Площадь участка в объединенных кусках
double *XVal=new double [n];  // Значение высоты объединенных кусков
for (int i=0;i<n;i++)
    {
    PartSquare[i]=0;
    Markers[i]=i;
    XVal[i]=P->Points[i].X;
    }
Markers[n]=n; // Записываем стражника
for (int i=1;i<n;i++)
    SegSquare[i-1]=(double)(P->Points[i].X+P->Points[i-1].X)*(P->Points[i].L-P->Points[i-1].L)/2;

bool continueflag=true;
while (continueflag)
    {                       // Ищем два соседних участка разность высот на которых минимальна
    int minval=Par1+1;
    int index;
    int prevval=XVal[0];
    for (int i=1;i<n;i++)
        {
        if (Markers[i]==i)
            {
            int dval=abs(XVal[i]-prevval);
            if (dval<minval)
                minval=dval,index=i;
            prevval=XVal[i];
            }
        }
    if (minval<Par1)                        // index - Номер точки начала второго участка
        {
        int StartIndex=Markers[index-1]; //Номер точки начала первого участка
        double S1,L1,S2,L2,S3,L3,X2,X3;
        if (StartIndex>0)
            {
            L2=P->Points[StartIndex].L-P->Points[StartIndex-1].L;
            S2=SegSquare[StartIndex-1];
            X2=XVal[StartIndex-1];
            }
        else
            L2=S2=X2=0;
        int EndIndex=index;  // Номер точки следующей за присоединенным участком
        while (Markers[EndIndex]==Markers[index])  // В конце стражник
            EndIndex++;
        if (EndIndex<n)
            {
            L3=P->Points[EndIndex].L-P->Points[EndIndex-1].L;
            S3=SegSquare[EndIndex-1];
            X3=XVal[EndIndex];
            }
        else
            L3=S3=X3=0;
        L1=P->Points[EndIndex-1].L-P->Points[StartIndex].L;
        // S1 площадь первого объединяемого участка, второго и сегмента между ними
        // L1 длина обеих участков и сегиента между ними
        // S2 площадь сегмента до первого участка
        // S3 площадь сегмента после второго участка
        // L2,L3 длины ссответствующих сегментов
        // X2,X3 высоты точек прилегающих к соединяемым участкам
        // До соединения площадь равна S1+S2+S3.
        // После соединения площадь равна H*L1+(X2+H)*L2/2 + (X3+H)*L3/2
        // Отсюда H=(S1+S2+S3-X2*L2/2-X3*L3/2)/(L1+L2/2+L3/2)
        S1=SegSquare[index-1]+PartSquare[StartIndex]+PartSquare[index];
        double H;
        if (L1+L2+L3>0)
            H=(S1+S2+S3-X2*L2/2-X3*L3/2)/(L1+(L2+L3)/2);
        else
            H=XVal[EndIndex-1];
        PartSquare[StartIndex]=H*L1;
        if (StartIndex>0)                          // Площадь сегмента до соединенного участка изменилась
            SegSquare[StartIndex-1]=((H+X2)*L2)/2;
        if (EndIndex<n)
            SegSquare[EndIndex-1]=((H+X3)*L3)/2;
        for (int i=StartIndex;i<EndIndex;i++)  // Соединяем сегменты и ставим общую высоту
            {
            Markers[i]=StartIndex;
            XVal[i]=H;
            }
        }
    else
        continueflag=0;
    }
// Считаем количество сегментов
int npart=0;
for (int i=0;i<n;i++)
    if (Markers[i]==i)
        npart++;
// Создаем линию
SetCount(npart*2);
int k=0;
for (int i=0;i<n;i++)
    if (Markers[i]==i)
        {
        int j=i+1;
        while (Markers[j]==i)  // В конце стражник
            j++;
        // сегмент от i до j-1
        double L1,X1,L2,X2,L3,X3;
        L1=P->Points[j-1].L-P->Points[i].L; // Параметры участка
        X1=XVal[i];
        if (i>0)                            //Параметры сегментов до и после участка
            {
            L2=P->Points[i].L-P->Points[i-1].L;
            X2=XVal[i-1];
            }
        else
            L2=X2=0;
        if (j<n)
            {
            L3=P->Points[j].L-P->Points[j-1].L;
            X3=XVal[j];
            }
        else
            L3=X3=0;

        FPoints[k].L=P->Points[i].L-L2/2;    // Граница между участками будет проходить по середине сегмента
        FPoints[k+1].L=P->Points[j-1].L+L3/2;
          // Площадь равна L1*X1+(3X1+X2)*L2/8+(3X1+X3)*L3/8  (площадь половины трапеции)
        double H=(L1*X1+((3*X1+X2)*L2+(3*X1+X3)*L3)/8)/(L1+(L2+L3)/2);
        H=(H+RoundVal/2)/RoundVal;
        H*=RoundVal;
        FPoints[k].X=FPoints[k+1].X=H;
        k+=2;
        }
delete[] Markers;
delete[] SegSquare;
delete[] PartSquare;
delete[] XVal;
}
/*
void __fastcall TPolyline::MakeWidePart(TPolyline *P,int Par1,int RoundVal)
{
SetCount(P->Count*2);
int prevind=0;
int minval=P->Points[0].X;
int maxval=P->Points[0].X;
int k=0;
for (int i=1;i<P->Count;i++)
    {
    if (maxval<P->Points[i].X)
        maxval=P->Points[i].X;
    if (minval>P->Points[i].X)
        minval=P->Points[i].X;
    if ((maxval-minval>Par1)||(i==P->Count-1))
        {
        int S=0;  // Cчитаем площадь участка
        for (int j=prevind;j<i;j++)
            S+=(P->Points[j].X+P->Points[j+1].X)*(P->Points[j+1].L-P->Points[j].L);
        if (P->Points[i].L>P->Points[prevind].L)
            {
            S/=2*(P->Points[i].L-P->Points[prevind].L);
            S=(S+RoundVal/2)/RoundVal;
            S*=RoundVal;
            FPoints[k].X=S;
            FPoints[k].L=P->Points[prevind].L;
            k++;
            FPoints[k].X=S;
            FPoints[k].L=P->Points[i].L;
            k++;
            }
        prevind=i;
        minval=maxval=P->Points[i].X;
        }
    }
SetCount(k);
} */

void __fastcall TPolyline::MakeMiddlePart(int DL)
{
int n=FCount-2;
DL>>=1;
for (int i=1;i<n;i++)
    if (FPoints[i].L==FPoints[i+1].L)
        {
        int DL1=(FPoints[i].L-FPoints[i-1].L)/3;
        int DL2=(FPoints[i+2].L-FPoints[i+1].L)/3;
        int d=DL;
        if (DL1<d)
            d=DL1;
        if (DL2<d)
            d=DL2;
        FPoints[i].L-=d;
        FPoints[i+1].L+=d;
        }
}

void __fastcall TPolyline::FastSetParam(void)
{
for (int i=0;i<FCount;i++)
    {
    FPoints[i].BasePar1=FPoints[i].L;
    FPoints[i].BasePar2=FPoints[i].X;
    }
}

bool __fastcall sorted(double A,double B,double C) {
   return (A<=B && B<=C || A>=B && B>=C);
}

bool __fastcall Cross(TRoadPoint &a,TRoadPoint &b,TRoadPoint &c,TRoadPoint &d,TRoadPoint &p) {
   long double A1=b.X-a.X;
   long double B1=a.L-b.L;
   long double C1=(long double)a.L*b.X-(long double)b.L*a.X;
   long double A2=d.X-c.X;
   long double B2=c.L-d.L;
   long double C2=(long double)c.L*d.X-(long double)d.L*c.X;
   long double D=A1*B2-B1*A2;
   if (fabs(D)<0.000000001) {
      if (fabs(C1/sqrt(A1*A1+B1*B1)-C2/sqrt(A2*A2+B2*B2))<0.00000001) {
         if (sorted(a.X,c.X,b.X)&&sorted(a.L,c.L,b.L))
            {p=c;return true;}
         else if (sorted(a.X,d.X,b.X)&&sorted(a.L,d.L,b.L))
            {p=d;return true;}
         else if (sorted(c.X,a.X,d.X)&&sorted(c.L,a.L,d.L))
            {p=a;return true;}
         else if (sorted(c.X,b.X,d.X)&&sorted(c.L,b.L,d.L))
            {p=b;return true;}
      }
   } else {
      p.X=(A1*C2-A2*C1)/D;
      p.L=(B2*C1-B1*C2)/D;
      if (sorted(a.L,p.L,b.L) && sorted(a.X,p.X,b.X) && sorted (c.L,p.L,d.L) && sorted(c.X,p.X,d.X))
         return true;
   }
   return false;
}

int __fastcall TPolyline::CrossLine(TRoadPoint &a,TRoadPoint &b,TRoadPoint &p) {
   if (a.L!=b.L || a.X!=b.X) {
      for (int i=1;i<FCount;i++)
         if (FPoints[i-1].L!=FPoints[i].L || FPoints[i-1].X!=FPoints[i].X)
            if (Cross(FPoints[i-1],FPoints[i],a,b,p))
               return i;
   }
   return 0;
}

double __fastcall TPolyline::LenTo(TRoadPoint &Cur,TRoadPoint &Ret,int &index)
{
double Result;
if (Count>0)
    {
    double dx=Cur.L-Points[0].L;
    double dy=Cur.X-Points[0].X;
    double lpred,lcur=dx*dx+dy*dy;
    Result=lcur;
    Ret.L=Cur.L;
    Ret.X=Cur.X;
    index=0;
    // Бежим по отрезкам. lpred- расстояние до начала отрезка от точки
    // lcur - расстояние до конца отрезка
    // l - длина отрезка
    for (int j=1;j<Count;j++)
        {
        lpred=lcur;
        dx=Cur.L-Points[j].L;
        dy=Cur.X-Points[j].X;
        lcur=dx*dx+dy*dy;
        if (lcur<Result)
            {
            Result=lcur;
            Ret.L=Points[j].L;
            Ret.X=Points[j].X;
            index=j-1;
            }
        double dx1=Points[j-1].L-Points[j].L;
        double dy1=Points[j-1].X-Points[j].X;
        double l=dx1*dx1+dy1*dy1;
// Если точка проецируется  на отрезок
        if ((lpred<lcur+l)&&(lcur<lpred+l))
            {
            double ln=(dx*dy1-dy*dx1);
            ln=ln*ln;
            ln/=l;
            if (ln<Result)
                {
                Result=ln;
                double dl=sqrt(lcur-ln);
                double sl=sqrt(l);
                Ret.L=Points[j].L+dx1*dl/sl+0.5;
                Ret.X=Points[j].X+dy1*dl/sl+0.5;
                index=j-1;
                }
            }
        }
    Result=sqrt(Result);
    }
else
    {
    Result=0;
    Ret.L=Cur.L;
    Ret.X=Cur.X;
    index=-1;
    }
return Result;
}



