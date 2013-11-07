//---------------------------------------------------------------------------


#pragma hdrstop

#include "Measures.h"
#include "math.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

class TPartTree
{
public:
TPartTree* LeftNode;
TPartTree* RightNode;
int LeftInd;
int RightInd;
__fastcall TPartTree(int ind1,int ind2)
    {LeftInd=ind1;RightInd=ind2;LeftNode=RightNode=NULL;}
};

int __fastcall TRoadGeometry::BuildPartTree(TPartTree* Node,int *DirVals,int *UnDirVals,__int32 MinLen,__int32 Dev)
{
int Res=1;
// Проверяем, надо ли разбивать участок
int i=Node->LeftInd;
int j=Node->RightInd;
__int32 LeftL=L[i];
__int32 RightL=L[j];
while ((i<j)&&(L[i]-LeftL<MinLen))  // Пробегаем расстояние MinLen слева
    i++;
while ((i<j)&&(RightL-L[j]<MinLen))  // Пробегаем MinLen справа
    j--;
int Min1,Max1,Min2,Max2;
Min1=Max1=DirVals[i];
Min2=Max2=UnDirVals[i];
for (int k=i+1;k<=j;k++)
    {
    if (Min1>DirVals[k])
        Min1=DirVals[k];
    if (Max1<DirVals[k])
        Max1=DirVals[k];
    if (Min2>UnDirVals[k])
        Min2=UnDirVals[k];
    if (Max2<UnDirVals[k])
        Max2=UnDirVals[k];
    }
if ((Max1-Min1>Dev)||(Max2-Min2>Dev))   // Надо разбивать участки
    {
    int MaxD=0;
    int DivPos=0;
    for (int k=i;k<=j;k++)
        {
        int val=abs(DirVals[k]-UnDirVals[k]);
        if (MaxD<val)
            MaxD=val,DivPos=k;
        }
    if (DivPos)
        {
        Node->LeftNode=new TPartTree(Node->LeftInd,DivPos);
        Node->RightNode=new TPartTree(DivPos,Node->RightInd);
        Res=BuildPartTree(Node->LeftNode,DirVals,UnDirVals,MinLen,Dev);
        Res+=BuildPartTree(Node->RightNode,DirVals,UnDirVals,MinLen,Dev);
        }
    }
return Res;
}

void __fastcall TRoadGeometry::ClearPartTree(TPartTree* Node)
{
if (Node)
    {
    ClearPartTree(Node->LeftNode);
    ClearPartTree(Node->RightNode);
    delete Node;
    }
}

TSlopesPart* __fastcall TRoadGeometry::PartTreeToArray(TSlopesPart* Array,TPartTree *Node)
{
if (Node)
    if ((Node->LeftNode==NULL)&&(Node->RightNode==NULL))  // Только листья
        {
        int n=Node->RightInd;
        int SlopeNorm=0;
        for (int i=Node->LeftInd;i<n;i++)
            SlopeNorm+=(L[i+1]-L[i])*(Values[i].LongSlope+Values[i+1].LongSlope);
        *Array=TSlopesPart(L[Node->LeftInd],L[Node->RightInd],SlopeNorm/((L[n]-L[Node->LeftInd])*2));
        Array++;
        }
    else
        {
        Array=PartTreeToArray(Array,Node->LeftNode);
        Array=PartTreeToArray(Array,Node->RightNode);
        }
return Array;
}

TSlopesPart* __fastcall TRoadGeometry::BuildSlopesPart(__int32 MinLen,__int32 Dev,int &PartCount)
{
int *ContDirSlp=new int [FCount];
int *ContBackSlp=new int [FCount];
int CurLen=0;
double SlopeNorm=0;
int MidSlopeVal;
// Считаем средний уклон на ровно MinLen метров после точки
// Если точка близко к краю то растояние меньше
int i,j;// i - начало полоски, j- конец полоски
for (i=0,j=1;i<FCount-1;i++)
    {
    while (j<FCount)  // Набираем длину из отрезков
        {
        int DL=L[j]-L[j-1];
        if (CurLen+DL>MinLen)
            break;
        CurLen+=DL;
        SlopeNorm+=(Values[j].LongSlope+Values[j-1].LongSlope)*DL;
        j++;
        }
    if (j<FCount) // Есть отрезок
        {
        int DL=L[j]-L[j-1];
        double TmpVal=Values[j-1].LongSlope+((Values[j].LongSlope-Values[j-1].LongSlope)*(MinLen-CurLen))/DL;
        MidSlopeVal=(SlopeNorm+(TmpVal+Values[j-1].LongSlope)*(MinLen-CurLen))/(2*MinLen);
        }
    else
        MidSlopeVal=SlopeNorm/(2*CurLen);
    ContDirSlp[i]=MidSlopeVal;
    int DL=L[i+1]-L[i];
    CurLen-=DL;
    SlopeNorm-=(Values[i+1].LongSlope+Values[i].LongSlope)*DL;
    }
ContDirSlp[FCount-1]=ContDirSlp[FCount-2];
// Считаем средний уклон на ровно MinLen метров до точки
// Тот же алгоритм только в обратную сторону
for (i=FCount-1,j=FCount-2;i>0;i--)
    {
    while (j>=0)
        {
        int DL=L[j+1]-L[j];
        if (CurLen+DL>MinLen)
            break;
        CurLen+=DL;
        SlopeNorm+=(Values[j+1].LongSlope+Values[j].LongSlope)*DL;
        j--;
        }
    if (j>=0)
        {
        int DL=L[j+1]-L[j];
        double TmpVal=Values[j+1].LongSlope+((Values[j].LongSlope-Values[j+1].LongSlope)*(MinLen-CurLen))/DL;
        MidSlopeVal=(SlopeNorm+(TmpVal+Values[j+1].LongSlope)*(MinLen-CurLen))/(2*MinLen);
        }
    else
        MidSlopeVal=SlopeNorm/(2*CurLen);
    ContBackSlp[i]=MidSlopeVal;
    int DL=L[i]-L[i-1];
    CurLen-=DL;
    SlopeNorm-=(Values[i].LongSlope+Values[i-1].LongSlope)*DL;
    }
ContBackSlp[0]=ContBackSlp[1];
TPartTree *Head=new TPartTree(0,FCount-1);
PartCount=BuildPartTree(Head,ContDirSlp,ContBackSlp,MinLen,Dev);
TSlopesPart *Parts=new TSlopesPart[PartCount];
PartTreeToArray(Parts,Head);
ClearPartTree(Head);
return Parts;
/*
int EstPartCount=0;
int PrevI=0;

int CurLen=0;
double SlopeNorm=0;
int PageStart=0;
// Считаем средний уклон на MinLen метров после точки
for (int i=0;i<FCount;i++)
    {
    int DL=L[i]-L[i-1];

    CurLen+=DL;
    SlopeNorm+=DL*(FValues[i].LongSlope+FValues[i-1].LongSlope);
    if (CurLen>MinLen)
        {
        int SlopeVal=SlopeNorm/((L[i]-L[PageStart])*2);
        for (int j=PageStart;j<=i;j++)
            ContSlpVal[j]=SlopeVal;
        DL=L[PageStart+1]-L[PageStart];
        CurLen-=DL;
        SlopeNorm-=DL*(FValues[PageStart+1].LongSlope+FValues[PageStart].LongSlope);
        PageStart++;
        }
    }

for (int i=0;i<FCount;i++)
    if (abs(FValues[i].LongSlope-FValues[PrevI].LongSlope)>Dev)
        {
        PrevI=i;
        EstPartCount++;
        }
EstPartCount++;
int n=0;
double SlopesVal=0;
PrevI=0;
int MinVal,MaxVal;
MinVal=MaxVal=ContSlpVal[0];
TSlopesPart *Parts=new TSlopesPart[EstPartCount];
for (int i=1;i<FCount;i++)
    {
    double NewSlopeVal=SlopesVal+(L[i]-L[i-1])*(FValues[i].LongSlope+FValues[i-1].LongSlope);
    double MidVal=NewSlopeVal/((L[i]-L[PrevI])*2);
    if (((MidVal-MinVal>Dev)||(MaxVal-MidVal>Dev))&&(L[i]-L[PrevI]>MinLen))
        {
        Parts[n]=TSlopesPart(L[PrevI],L[i],MidVal);
        PrevI=i;
        SlopesVal=0;
        MinVal=MaxVal=ContSlpVal[i];
        n++;
        }
    else
        {
        SlopesVal=NewSlopeVal;
        if (MinVal>ContSlpVal[i])
            MinVal=ContSlpVal[i];
        if (MaxVal<ContSlpVal[i])
            MaxVal=ContSlpVal[i];
        }
    }
if (PrevI<FCount-1)
    {
    SlopesVal/=(L[FCount-1]-L[PrevI])*2;
    Parts[n++]=TSlopesPart(L[PrevI],L[FCount-1],SlopesVal);
    }
delete[] ContSlpVal;
PartCount=n;
return Parts;
*/
}
