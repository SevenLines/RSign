//---------------------------------------------------------------------------

#ifndef MeasuresH
#define MeasuresH
#include <fstream.h>
#include <system.hpp>
#include <SysUtils.hpp>
#include <math.h>
//---------------------------------------------------------------------------

class TGeometryVal
{
public:
__int32 Z;
__int32 X;
__int32 Y;
__int32 LongSlope;
__int32 LeftSlope;
__int32 RightSlope;
__int32 DirectRad;
__int32 UnDirectRad;
__fastcall TGeometryVal()
    {}
__fastcall TGeometryVal(__int32 x,__int32 y,__int32 z,__int32 longs,__int32 lefts,__int32 rights,__int32 drad,__int32 udrad)
{
X=x;
Y=y;
Z=z;
LongSlope=longs;
LeftSlope=lefts;
RightSlope=rights;
DirectRad=drad;
UnDirectRad=udrad;
}

void __fastcall Extrapolate(TGeometryVal &V1,TGeometryVal &V2,__int32 L,__int32 L1,__int32 L2)
    {
    Z=V1.Z;
    LongSlope=V1.LongSlope;
    LeftSlope=V1.LeftSlope;
    RightSlope=V1.RightSlope;
    DirectRad=V1.DirectRad;
    UnDirectRad=V1.UnDirectRad;
    if (L2>L1)
        {
        double K=(double)(L-L1)/(L2-L1);
        X+=(V2.X-V1.X)*K;
        Y+=(V2.Y-V1.Y)*K;
        Z+=(V2.Z-V1.Z)*K;
        LongSlope+=(V2.LongSlope-V1.LongSlope)*K;
        LeftSlope+=(V2.LeftSlope-V1.LeftSlope)*K;
        RightSlope+=(V2.RightSlope-V1.RightSlope)*K;
        double V2Sp;
        if (V2.DirectRad)
            V2Sp=1.0/(V2.DirectRad);
        else
            V2Sp=0;
        double V1Sp;
        if (V1.DirectRad)
            V1Sp=1.0/(V1.DirectRad);
        else
            V1Sp=0;
        double Sp=(V2Sp-V1Sp)*K+V1Sp;
        if (fabs(Sp)>0.000001)
            DirectRad=1/Sp;
        else
            DirectRad=0;

        if (V2.UnDirectRad)
            V2Sp=1.0/(V2.UnDirectRad);
        else
            V2Sp=0;
        if (V1.UnDirectRad)
            V1Sp=1.0/(V1.UnDirectRad);
        else
            V1Sp=0;
        Sp=(V2Sp-V1Sp)*K+V1Sp;
        if (fabs(Sp)>0.000001)
            UnDirectRad=1/Sp;
        else
            UnDirectRad=0;
        }
    }
String __fastcall GetString(void)
    {
    return String(Z)+"#"+String(LongSlope)+"#"+String(LeftSlope)+"#"+String(RightSlope)+"#"+String(DirectRad)+"#"+String(UnDirectRad)+"#";
    }
void __fastcall SetString(String s)
    {
    int n=0;
    int val=0;
    int sgn=1;
    char *c=s.c_str();
    while (*c)
        {
        if (*c=='#')
            {
            switch (n)
                {
                case 0:Z=sgn*val;break;
                case 1:LongSlope=sgn*val;break;
                case 2:LeftSlope=sgn*val;break;
                case 3:RightSlope=sgn*val;break;
                case 4:DirectRad=sgn*val;break;
                case 5:UnDirectRad=sgn*val;break;
                }
            n++;
            val=0;
            sgn=1;
            }
        else if (*c=='-')
            sgn=-1;
        else if ((*c<='9')&&(*c>='0'))
            val=val*10+*c-'0';
        c++;
        }
    }
};

class TVideoTimeVal
{
public :
__int32 Time;
__int32 HighIndex;
__fastcall TVideoTimeVal()
    {}
__fastcall TVideoTimeVal(__int32 time,__int32 high)
    {Time=time;HighIndex=high;}
void __fastcall Extrapolate(TVideoTimeVal &V1,TVideoTimeVal &V2,__int32 L,__int32 L1,__int32 L2)
    {
    HighIndex=V1.HighIndex;
    Time=V1.Time;
    if ((V1.HighIndex==V2.HighIndex)&&(L1<L2))
        Time+=((V2.Time-V1.Time)*(L-L1))/(L2-L1);
    }
String __fastcall GetString(void)
    {
    return String(Time)+"#"+String(HighIndex)+"#";
    }
void __fastcall SetString(String s)
    {
    int n=0;
    int val=0;
    int sgn=1;
    char *c=s.c_str();
    while (*c)
        {
        if (*c=='#')
            {
            switch (n)
                {
                case 0:Time=sgn*val;break;
                case 1:HighIndex=sgn*val;break;
                }
            n++;
            val=0;
            sgn=1;
            }
        else if (*c=='-')
            sgn=-1;
        else if ((*c<='9')&&(*c>='0'))
            val=val*10+*c-'0';
        c++;
        }
    }
};

class TSvpdConvertVal
{
public:
__int32 SvpdPos;
__fastcall TSvpdConvertVal()
    {}
__fastcall TSvpdConvertVal(__int32 svpd)
    {SvpdPos=svpd;}
void __fastcall Extrapolate(TSvpdConvertVal &V1,TSvpdConvertVal &V2,__int32 L,__int32 L1,__int32 L2)
    {
    SvpdPos=V1.SvpdPos;
    if (L1<L2)
        SvpdPos+=((V2.SvpdPos-V1.SvpdPos)*(L-L1))/(L2-L1);
    }
};

class TSlopesPart
{
public:
__int32 L1,L2;
__int32 Value;
__fastcall TSlopesPart(__int32 l1,__int32 l2,__int32 val)
    {L1=l1;L2=l2;Value=val;}
__fastcall TSlopesPart(void) {}
};

template <class VAL>
class TRoadMeasure
{
protected:
int FCapacity;
int FCount;
__int32 *FL;
VAL* FValues;
public:
__fastcall TRoadMeasure(void);
__fastcall TRoadMeasure(__int32 NCount);
__fastcall ~TRoadMeasure(void);
void __fastcall Move(int len) {
   for (int i=0;i<FCount;i++)
      FL[i]+=len;
}
void __fastcall SetCount(int);
void __fastcall Free(void);
VAL& __fastcall operator[](int n)
    {return FValues[n];}
void __fastcall CopyAndCut(TRoadMeasure<VAL>* Source,__int32 LMin,__int32 LMax);
int __fastcall GetMesValue(__int32 Pos,VAL& Value);
void __fastcall Dump(ofstream &out)
{
out<<FCount<<endl;
for (int i=0;i<FCount;i++)
    out<<L[i]<<" "<<FValues[i].GetString().c_str()<<endl;
}
void __fastcall LoadDump(ifstream &in)
{
char c[1024];
int n;
in>>n;
in.getline(c,1024);
SetCount(n);
for (int i=0;i<n;i++)
    {
    in>>L[i];
    in.getline(c,1024);
    FValues[i].SetString(c);
    }
}
__property __int32 *L={read=FL};
__property VAL *Values={read=FValues};
__property int Count={read=FCount};
};


class TPartTree;
class TRoadGeometry : public TRoadMeasure<TGeometryVal>
{
private:
int __fastcall BuildPartTree(TPartTree* Node,int *DirVals,int *UnDirVals,__int32 MinLen,__int32 Dev);
void __fastcall ClearPartTree(TPartTree* Node);
TSlopesPart* __fastcall PartTreeToArray(TSlopesPart* Array,TPartTree *Node);
public :
void __fastcall GetMinMaxZ(__int32 &mn,__int32 &mx);
TSlopesPart* __fastcall BuildSlopesPart(__int32 MinLen,__int32 Dev,int &Count);
};

class TVideoTime : public TRoadMeasure<TVideoTimeVal>
{
private:
   String FDescription;
   int FId;
   int FCol,FRow; // Схема камеры в виде положения кнопки
   int FIcon;     // Номер изображения на кнопке
   void __fastcall SetDescription(String s);
public :
  __fastcall TVideoTime(void) : TRoadMeasure<TVideoTimeVal>(),FId(0),FRow(0),FCol(0), FIcon(0) {}
  int __fastcall FindPosition(int Time,int &Position);
  __property String Description={read=FDescription,write=SetDescription};
  __property int Id={read=FId,write=FId};
  __property int Row={read=FRow,write=FRow};
  __property int Col={read=FCol,write=FCol};
  __property int Icon={read=FIcon,write=FIcon};

};

class TVideoHigh : public TRoadMeasure<TSvpdConvertVal>
{
public:
    int Id;
    int Direction;
    String FileName;
    __fastcall TVideoHigh(int id,int dir)
        {Id=id;Direction=dir;}
    __fastcall TVideoHigh(void)
        {}
};

template <class VAL>
__fastcall TRoadMeasure<VAL>::TRoadMeasure(void)
{
FCount=FCapacity=0;
FL=NULL;
FValues=NULL;
}

template <class VAL>
__fastcall TRoadMeasure<VAL>::TRoadMeasure(int NCount)
{
if (NCount>0)
    {
    FCapacity=NCount+INCCAPVALUE;
    FL=new __int32 [FCapacity];
    FValues=new VAL [FCapacity];
    FCount=NCount;
    }
else
    {
    FCount=FCapacity=0;
    FL=NULL;
    FValues=NULL;
    }
}

template <class VAL>
__fastcall TRoadMeasure<VAL>::~TRoadMeasure(void)
{
Free();
}

template <class VAL>
void __fastcall TRoadMeasure<VAL>::Free(void)
{
delete[] FL;
delete[] FValues;
FL=NULL;
FValues=NULL;
FCount=FCapacity=0;
}

template <class VAL>
void __fastcall TRoadMeasure<VAL>::SetCount(int NCount)
{
if (NCount>=0)
    {
    if (NCount<FCapacity)
        FCount=NCount;
    else
        {
        VAL *OldVal=FValues;
        __int32 *OldL=FL;
        FCapacity=NCount+INCCAPVALUE;
        FValues=new VAL [FCapacity];
        FL=new __int32 [FCapacity];
        for (int i=0;i<FCount;i++)
            {
            FL[i]=OldL[i];
            FValues[i]=OldVal[i];
            }
        FCount=NCount;
        }
    }
}

template <class VAL>
void __fastcall TRoadMeasure<VAL>::CopyAndCut(TRoadMeasure<VAL> *Source,__int32 L1,__int32 L2)
{
int j,i;
Free();
int n=Source->Count;
__int32 *L=Source->L;
VAL *SVal=Source->Values;
// Здесь можно написать двоичный поиск.
for (i=0;i<n;i++)     // i - номер первой точки в области вывода
   if (L[i]>=L1)
      break;

for (j=i;j<n;j++)       // j - первая точка за областью вывода
   if (L[j]>L2)
      break;

if ((i==n)||(j==0))
    return;         // Точки начинаются за областью вывода
SetCount(j-i+2);
int s=0;
if (i>0)
    {
    FL[s]=L1;
    FValues[s].Extrapolate(SVal[i-1],SVal[i],L1,L[i-1],L[i]);
    s++;
    }
for (int k=i;k<j;k++,s++)
    {
    FL[s]=L[k];
    FValues[s]=SVal[k];
    }
if ((j<n)&&(j>0))
    {
    FL[s]=L2;
    FValues[s].Extrapolate(SVal[j-1],SVal[j],L2,L[j-1],L[j]);
    s++;
    }
FCount=s;
}

template <class VAL>
int __fastcall TRoadMeasure<VAL>::GetMesValue(__int32 Pos,VAL& Value)
{
int Index=-1;
if (FCount>0)
    {
    if (Pos<=FL[0])
        Index=0,Value=FValues[0];
    else if (Pos>=FL[FCount-1])
        Index=FCount-1,Value=FValues[FCount-1];
    else
        {
        int st=0;
        int end=FCount-1;
        while (end-st>1)
            {
            int mid=(st+end)>>1;
            if (Pos>FL[mid])
                st=mid;
            else
                end=mid;
            }
        Index=st;
        Value.Extrapolate(FValues[st],FValues[end],Pos,FL[st],FL[end]);
        }
    }
return Index;
}


void __fastcall TRoadGeometry::GetMinMaxZ(__int32 &mn,__int32 &mx)
{
if (FCount>0)
    {
    mx=mn=FValues[0].Z;
    for (int i=1;i<FCount;i++)
        {
        __int32 z=FValues[i].Z;
        if (mx<z)
            mx=z;
        if (mn>z)
            mn=z;
        }
    }
}

class TCurvePoint {
public :
   double bR; // Обратный радиус кривизны в точке           
              // Поворот налево радиус отрицательный, направо - положительный
   double X,Y;// Относительные координаты точки (используются при двумерном выводе)
   double A;//Угол касательной в данной точке
   __fastcall TCurvePoint() : bR(0) {}
   __fastcall TCurvePoint(double _br) : bR(_br) {}
   void __fastcall Extrapolate(TCurvePoint &V1,TCurvePoint &V2,__int32 L,__int32 L1,__int32 L2)
    {
    bR=(V1.bR*(L2-L)+V2.bR*(L-L1))/(L2-L1);
    }
};

class TCurvePlan : public TRoadMeasure<TCurvePoint> {

};





#endif
