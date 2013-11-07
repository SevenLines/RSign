//---------------------------------------------------------------------------


#pragma hdrstop

#include "SignDesign.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TSignDesignData SDesignData;
TSignDesignRules SDesignRules;


bool __fastcall TSignDesignRules::CanHandle(TRoadObject *Obj, TDtaSource *Data,TDictSource *Dict)
{
return HandleObject(Obj,Data,Dict,false);
}

int __fastcall TSignDesignRules::HandleObject(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict, bool doit)
{
TRoadAttach *At=dynamic_cast<TRoadAttach*>(Obj);
if (At)
    return HandleAttach(At,Data,Dict,doit);
TTown *Tw=dynamic_cast<TTown*>(Obj);
if (Tw)
    return HandleTown(Tw,Data,Dict,doit);
TBusStop *Bs=dynamic_cast<TBusStop*>(Obj);
if (Bs)
    return HandleBusStop(Bs,Data,Dict,doit);
TRoadBridge *Br=dynamic_cast<TRoadBridge*>(Obj);
if (Br)
    return HandleBridge(Br,Data,Dict,doit);
return 0;
}

TAttachPlacement __fastcall TSignDesignRules::GetAttachPlacement(TRoadAttach *At,TDtaSource *Data,int &SPos, int &EPos)
{
if ((At->Placement!=apLeft)&&(At->Placement!=apRight))
    {
    SPos=EPos=At->L;
    return apCross;
    }
int ind1,ind2;
int count=Data->BinarySearch(At->L-SDesignData.CrossMaxLen,At->L+SDesignData.CrossMaxLen,ind1,ind2);
if (!count)
    {
    SPos=EPos=At->L;
    return At->Placement;
    }
while (ind1<=ind2)
    {
    TRoadAttach *T=dynamic_cast<TRoadAttach*>(Data->Objects->Items[ind1]);
    if (T)
        if (T->Placement!=At->Placement)
            {
            if (T->L<At->L)
                {
                SPos=T->L;
                EPos=At->L;
                }
            else
                {
                SPos=At->L;
                EPos=T->L;
                }
            return apCross;
            }
    ind1++;
    }
SPos=EPos=At->L;
return At->Placement;
}

bool __fastcall TSignDesignRules::IsInSity(TRoadObject *Obj, TDtaSource *Data)
{
int ind1,ind2;
int count=Data->BinarySearch(0,Obj->L,ind1,ind2);
if (!count)
    return false;
while (ind2>=ind1)
    {
    TTown *T=dynamic_cast<TTown*>(Data->Objects->Items[ind2]);
    if (T)
        return T->LMax>=Obj->L;
    ind2--;
    }
return false;
}



int __fastcall TSignDesignRules::HandleAttach(TRoadAttach *At,TDtaSource *Data, TDictSource *Dict,bool doit)
{
int Res=0;
int SLAt=Dict->FindPropId(SIGNGOSTCODE+1,"2.3.3");
int SRAt=Dict->FindPropId(SIGNGOSTCODE+1,"2.3.2");
int SCAt=Dict->FindPropId(SIGNGOSTCODE+1,"2.3.1");
int SUAt=Dict->FindPropId(SIGNGOSTCODE+1,"2.4");
int SDefAt;
String CodeStr;

bool InSity=IsInSity(At,Data);
int l1;
int l2;
int l3;
if (InSity)
    {
    l1=SDesignData.MaxLenToAttachSignInSity;
    l2=SDesignData.LenToAttachSignInSity;
    l3=SDesignData.SignToSignInSity;
    }
else
    {
    l1=SDesignData.MaxLenToAttachSign;
    l2=SDesignData.LenToAttachSign;
    l3=SDesignData.SignToSign;
    }
int SPos,EPos;  // Если примыкание имеет ширину (перекресток, где улицы не совсем напротив )
TAttachPlacement pl=GetAttachPlacement(At,Data,SPos,EPos);
if (pl==apLeft)
    SDefAt=SLAt,CodeStr="2.3.3";
else if (pl==apRight)
    SDefAt=SRAt,CodeStr="2.3.2";
else
    SDefAt=SCAt,CodeStr="2.3.1";
int MinPos=SPos-l1;
TRoadSign *prevsgn=FindSign(Data,SLAt,SPos-l1,SPos-1,false,roDirect,spRight,SDesignData.IsBreakAttachObject,MinPos);
if (!prevsgn)
    {
    prevsgn=FindSign(Data,SRAt,SPos-l1,SPos-1,false,roDirect,spRight,SDesignData.IsBreakAttachObject,MinPos);
    if (!prevsgn)
        {
        prevsgn=FindSign(Data,SCAt,SPos-l1,SPos-1,false,roDirect,spRight,SDesignData.IsBreakAttachObject,MinPos);
        }
    }
if (prevsgn)
    if (prevsgn->NumRoadSign!=SDefAt)
        {
        if (doit)
            Data->DeleteObjectEx(prevsgn);
        prevsgn=NULL;
        }
if (!prevsgn)
    {
    MinPos+=SDesignData.AttachToSign;
    int CurPos=MinPos;
    if (CurPos<SPos-l2)
        CurPos=SPos-l2;
    if (doit)
        {
        TRoadSign *NewSgn=Data->AddPrjSign(Dict,roDirect,spRight,CurPos,FindSignX(Data,roDirect,CurPos),CodeStr,"","",TSignAttach(0));
        SetSignPlacement(Data,l3,MinPos,SPos-1,NewSgn);
        }
    Res++;
    }
if (pl==apLeft)
    SDefAt=SRAt,CodeStr="2.3.2";
else if (pl==apRight)
    SDefAt=SLAt,CodeStr="2.3.3";
else
    SDefAt=SCAt,CodeStr="2.3.1";
int MaxPos=EPos+l1;
TRoadSign *postsgn=FindSign(Data,SLAt,EPos+1,EPos+l1,true,roUnDirect,spRight,SDesignData.IsBreakAttachObject,MaxPos);
if (!postsgn)
    {
    postsgn=FindSign(Data,SRAt,EPos+1,EPos+l1,true,roUnDirect,spRight,SDesignData.IsBreakAttachObject,MaxPos);
    if (!postsgn)
        postsgn=FindSign(Data,SCAt,EPos+1,EPos+l1,true,roUnDirect,spRight,SDesignData.IsBreakAttachObject,MaxPos);
    }
if (postsgn)
    if (postsgn->NumRoadSign!=SDefAt)
        {
        if (doit)
            Data->DeleteObjectEx(postsgn);
        postsgn=NULL;
        }
if (!postsgn)
    {
    MaxPos-=SDesignData.AttachToSign;
    int CurPos=MaxPos;
    if (CurPos>EPos+l2)
        CurPos=EPos+l2;
    if (doit)
        {
        TRoadSign *NewSgn=Data->AddPrjSign(Dict,roUnDirect,spRight,CurPos,FindSignX(Data,roUnDirect,CurPos),CodeStr,"","",TSignAttach(0));
        SetSignPlacement(Data,l3,EPos+1,MaxPos,NewSgn);
        }
    Res++;
    }
if ((pl==apLeft)||(pl==apCross))
    {
    int t;
    TRoadSign *lsgn=FindSign(Data,SUAt,SPos-1000,EPos+1000,false,roUnDirect,spRight,NULL,t);
    if (!lsgn)
        lsgn=FindSign(Data,SUAt,SPos-1000,EPos+1000,false,roDirect,spLeft,NULL,t);
    if (!lsgn)
        {
        if (doit)
            Data->AddPrjSign(Dict,roUnDirect,spRight,(SPos+EPos)>>1,SDesignData.Sign24ToAttach,"2.4","","",saIn);
        Res++;
        }
    }
if ((pl==apRight)||(pl==apCross))
    {
    int t;
    TRoadSign *rsgn=FindSign(Data,SUAt,SPos-1000,EPos+1000,false,roDirect,spRight,NULL,t);
    if (!rsgn)
        rsgn=FindSign(Data,SUAt,SPos-1000,EPos+1000,false,roUnDirect,spLeft,NULL,t);
    if (!rsgn)
        {
        if (doit)
            Data->AddPrjSign(Dict,roDirect,spRight,(SPos+EPos)>>1,SDesignData.Sign24ToAttach,"2.4","","",saIn);
        Res++;
        }
    }
return Res;
}

int __fastcall TSignDesignRules::FindSignX(TDtaSource *Data,TRoadDirection dir,int Pos)
{
int x;
if (dir==roDirect)
    x=Data->Road->RightSide.FindX(Pos)-Data->Road->RightLine.FindX(Pos);
else
    x=Data->Road->LeftLine.FindX(Pos)-Data->Road->LeftSide.FindX(Pos);
if (x<=0)
    x=SDesignData.SignOffset;
return x;
}

int __fastcall TSignDesignRules::AssistHandleTown(TTown *T,TDtaSource *Data,
    TDictSource *Dict,int Pos,TRoadDirection defdir,int defcode,int poscode,String scode,bool doit)
{
int Res=0;
bool napr=defdir==roDirect;
int dx=SDesignData.TownToSign;
int t;
TRoadSign *sgn=FindSign(Data,defcode,Pos-dx,Pos+dx,napr,defdir,(TRoadSignPlacement)0,NULL,t);
if (!sgn)
    sgn=FindSign(Data,poscode,Pos-dx,Pos+dx,napr,defdir,(TRoadSignPlacement)0,NULL,t);

if (sgn)
    if (sgn->Placement==spLeft)
        {
        if (doit)
            Data->DeleteObjectEx(sgn);
        sgn=NULL;
        }
if (sgn)
    if (sgn->Label=="")
        if (doit)
            sgn->Label=T->Title;
if (!sgn)
    {
    if (doit)
        Data->AddPrjSign(Dict,defdir,spRight,Pos,FindSignX(Data,defdir,Pos),scode,T->Title,"",TSignAttach(0));
    Res++;
    }
return Res;
}

int __fastcall TSignDesignRules::HandleTown(TTown *T,TDtaSource *Data, TDictSource *Dict,bool doit)
{
int Res=0;
int WSTw=Dict->FindPropId(SIGNGOSTCODE+4,"5.22");
int WETw=Dict->FindPropId(SIGNGOSTCODE+4,"5.23");
int BSTw=Dict->FindPropId(SIGNGOSTCODE+4,"5.24");
int BETw=Dict->FindPropId(SIGNGOSTCODE+4,"5.25");
if (T->L>Data->Road->LMin)
    {
    Res+=AssistHandleTown(T,Data,Dict,T->L,roDirect,WSTw,BSTw,"5.22",doit);
    Res+=AssistHandleTown(T,Data,Dict,T->L,roUnDirect,WETw,BETw,"5.23",doit);
    }
if (T->LMax<Data->Road->LMax)
    {
    Res+=AssistHandleTown(T,Data,Dict,T->LMax,roUnDirect,WSTw,BSTw,"5.22",doit);
    Res+=AssistHandleTown(T,Data,Dict,T->LMax,roDirect,WETw,BETw,"5.23",doit);
    }
return Res;
}

int __fastcall TSignDesignRules::HandleBusStop(TBusStop *B,TDtaSource *Data, TDictSource *Dict,bool doit)
{
int Res=0;
int BSt=Dict->FindPropId(SIGNGOSTCODE+4,"5.12");
int t;
TRoadDirection dir;
if (B->Placement==rsLeft)
    dir=roUnDirect;
else
    dir=roDirect;
TRoadSign *sgn;
if (dir==roDirect)
    sgn=FindSign(Data,BSt,B->L-SDesignData.MaxSignToBusStop,B->L,false,dir,spRight,NULL,t);
else
    sgn=FindSign(Data,BSt,B->L,B->L+SDesignData.MaxSignToBusStop,true,dir,spRight,NULL,t);
if (!sgn)
    {
    int Pos;
    if (dir==roDirect)
        Pos=B->L-SDesignData.SignToBusStop;
    else
        Pos=B->L+SDesignData.SignToBusStop;
    if (doit)
        Data->AddPrjSign(Dict,dir,spRight,Pos,FindSignX(Data,dir,Pos),"5.12","","",TSignAttach(0));
    Res++;
    }
return Res;
}

int __fastcall TSignDesignRules::HandleBridge(TRoadBridge *B,TDtaSource *Data, TDictSource *Dict,bool doit)
{
int Res=0;
if ((B->ObstacleKind==ok95)&&(B->ObstacleName!=""))
    {
    int BNm=Dict->FindPropId(SIGNGOSTCODE+4,"5.26");
    int BWidth=(B->LMax-B->L)>>1;
    int t;
    TRoadSign *sgn=FindSign(Data,BNm,B->L-SDesignData.MaxSignToBridge,B->L+BWidth,false,roDirect,spRight,NULL,t);
    if (!sgn)
        {
        if (doit)
            Data->AddPrjSign(Dict,roDirect,spRight,B->L,FindSignX(Data,roDirect,B->L),"5.26",B->ObstacleName,"",TSignAttach(0));
        Res++;
        }
    else if (sgn->Label=="")
        if (doit)
            sgn->Label=B->ObstacleName;
    sgn=FindSign(Data,BNm,B->LMax-BWidth,B->LMax+SDesignData.MaxSignToBridge,false,roUnDirect,spRight,NULL,t);
    if (!sgn)
        {
        if (doit)
            Data->AddPrjSign(Dict,roUnDirect,spRight,B->LMax,FindSignX(Data,roDirect,B->LMax),"5.26",B->ObstacleName,"",TSignAttach(0));
        Res++;
        }
    else if (sgn->Label=="")
        sgn->Label=B->ObstacleName;
    }
return Res;
}

int __fastcall TSignDesignRules::SetKmSign(TDtaSource *Data, TDictSource *Dict)
{
int Res=0;
int BKm=Dict->FindPropId(SIGNGOSTCODE+5,"6.13");
int MaxKm=Data->Road->LMax/100000;
int DPos=SDesignData.MaxSignToKm;
TRoadSign **Marked=new TRoadSign* [2*MaxKm];
int MarkCount=0;
for (int Pos=1;Pos<=MaxKm;Pos++)
    {
    int t;
    TRoadSign *sgn=FindSign(Data,BKm,Pos*100000-DPos,Pos*100000+DPos,false,roDirect,spRight,NULL,t);
    if (sgn)
        {
        if (sgn->Label=="")
            {
            sgn->Label=Pos;
            Marked[MarkCount++]=sgn;
            }
        else
            {
            String s=sgn->Label.Trim();
            int n=s.Length();
            int i=1;
            int km=0;
            while ((i<=n)&&(s[i]<='9')&&(s[i]>='0'))
                {
                km=km*10+s[i]-'0';
                i++;
                }
            if (km==Pos)
                Marked[MarkCount++]=sgn;
            }
        }
    else
        {
        Data->AddPrjSign(Dict,roDirect,spRight,Pos*100000,FindSignX(Data,roDirect,Pos*100000),"6.13",String(Pos),"",TSignAttach(0));
        Res++;
        }
    }
int n=Data->Objects->Count;
int k=0;
for (int i=0;i<n;i++)
    {
    TRoadSign *sgn=dynamic_cast<TRoadSign*>(Data->Objects->Items[i]);
    if (sgn)
        if (sgn->NumRoadSign==BKm)
            {
            bool del=true;
            if (k<MarkCount)
                if (sgn==Marked[k])
                    k++,del=false;
            if (del)
                {
                Data->DeleteObjectEx(sgn);
                if (sgn!=Data->Objects->Items[i])
                    i--;
                }
            }
    }
delete[] Marked;
return Res;
}

TRoadSign* __fastcall TSignDesignRules::FindSign(TDtaSource *Data,__int32 SCode,__int32 SPos,__int32 EPos, bool napr, TRoadDirection dir, TRoadSignPlacement pl,TTestBreak Test,int &Pos)
{
int ind1,ind2;
int i1,i2;
if (napr)
    i1=1,i2=0;
else
    i1=0,i2=1;
int count=Data->BinarySearch(SPos,EPos,ind1,ind2);
if (!count)
    return NULL;
while (ind1<=ind2)
    {
    TRoadObject *Obj;
    if (napr)
        Obj=Data->Objects->Items[ind1];
    else
        Obj=Data->Objects->Items[ind2];
    if (Test)
        if (Test(Obj))
            {
            Pos=Obj->L;
            return NULL;
            }
    TRoadSign *Sgn=dynamic_cast<TRoadSign*>(Obj);
    if (Sgn)
        if ((Sgn->Direction==dir)||((int)dir==0))
            if ((Sgn->Placement==pl)||((int)pl==0))
                if (Sgn->NumRoadSign==SCode)
                    return Sgn;
    ind1+=i1;
    ind2-=i2;
    }
return NULL;
}

void __fastcall TSignDesignRules::SetSignPlacement(TDtaSource *Data,int sgntosgn,int SPos,int EPos,TRoadSign *Sgn)
{
int ind1,ind2;
int count=Data->BinarySearch(SPos,EPos,ind1,ind2);
if (count)
    while (ind1<=ind2)
        {
        TRoadObject *Obj=Data->Objects->Items[ind1];
        ind1++;
        TRoadSign *B=NULL;
        TRoadSign *S=dynamic_cast<TRoadSign*>(Obj);
        if (S)
            if ((S->Direction==Sgn->Direction)&&(S->Placement==Sgn->Placement))
                {
                if (!B)
                    B=S;
                else
                    if (abs(B->L-Sgn->L)>abs(S->L-Sgn->L))
                        B=S;
                }
        if (B)
            if (abs(B->L-Sgn->L)<sgntosgn)
                {Sgn->L=B->L;Sgn->DX=B->DX;}
        }
if (Sgn->L<Data->Road->LMin)
    Sgn->L=Data->Road->LMin;
if (Sgn->L>Data->Road->LMax)
    Sgn->L=Data->Road->LMax;
}
