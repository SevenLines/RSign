//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
                                                                          
#include "DataSour.h"
#include "DBDataSource.h"
#include "FileSour.h"

#include "common.h"
#include <vector>
#include <algorithm>

#ifdef GDIEDIT // << Костя, я отключил GDEDIT в common.h, а то не компилиться (МИША) 
    #include "GdiEForm.h"
#else
    #include "SettingFrm.h"
    #include "MainUnit.h"
    #include "ErrorObjectDlg.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)

int __fastcall GetNotEmptyCount(TList *l)
{
int n=0;
int max=l->Count;
void** pt=l->List;
for (int i=0;i<max;i++)
        if (pt[i])
                n++;
return n;
}
int __fastcall GetNotEmptyCount(TStringList *l)
{
int n=0;
int max=l->Count;
for (int i=0;i<max;i++)
        if (l->Strings[i]!="")
                n++;
return n;
}

__fastcall TSharedObjSource::TSharedObjSource(void)
{
FGorzGDIObjects=new TGDIList;
FVertGDIObjects=new TGDIList;
FMetas=new TMetafileList;
FReady=false;
FOwnList=true;
}

void __fastcall TSharedObjSource::CopyList(TSharedObjSource *S)
{
FOwnList=false;
FReady=true;
FMetas=S->Metas;
FGorzGDIObjects=S->GorzGDIObjects;
FVertGDIObjects=S->VertGDIObjects;
}

__fastcall TSharedObjSource::~TSharedObjSource(void)
{
if (FOwnList)
    {
    delete Metas;
    delete FGorzGDIObjects;
    delete FVertGDIObjects;
    }
}

void __fastcall TSharedObjSource::Dump(String path)
{
String folder=path+"\\0.dcs";
ofstream out(folder.c_str());
out<<GetNotEmptyCount(FGorzGDIObjects)<<" "<<FGorzGDIObjects->Count-1<<endl;
for (int i=0;i<FGorzGDIObjects->Count;i++)
        if (FGorzGDIObjects->Items[i])
                {
                if (GetObjectType(FGorzGDIObjects->Items[i])==OBJ_BRUSH)
                        {
                        LOGBRUSH b;
                        GetObject(FGorzGDIObjects->Items[i],sizeof(LOGBRUSH),&b);
                        if (b.lbStyle==BS_HATCHED)
                                out<<i<<" "<<OBJ_BRUSH<<" "<<b.lbColor<<" "<<b.lbHatch+1<<endl;
                        else
                                out<<i<<" "<<OBJ_BRUSH<<" "<<b.lbColor<<" "<<0<<endl;
                        }
                else if (GetObjectType(FGorzGDIObjects->Items[i])==OBJ_EXTPEN)
                        {
                        EXTLOGPEN p;
                        GetObject(FGorzGDIObjects->Items[i],sizeof(EXTLOGPEN),&p);
                        out<<i<<" "<<OBJ_PEN<<" "<<p.elpColor<<" "<<p.elpWidth<<" "<<p.elpPenStyle<<endl;
                        }
                }
out<<GetNotEmptyCount(FMetas)<<" "<<FMetas->Count-1<<endl;
for (int i=0;i<FMetas->Count;i+=4)
        if (FMetas->Strings[i]!="")
                out<<i<<" "<<FMetas->Strings[i].c_str()<<endl;
out.close();
}

__fastcall TDictSource::TDictSource(void)
{
CreateClasses();
}

void __fastcall TDictSource::CreateClasses(void)
{
FOwnList=true;
FDictId=0;
FRefCount=0;
FObjClasses=new TObjList<TObjMetaClass>;
FPropClasses=new TObjList<TPropClassesRec>;
FTextProps=new TObjList<TTextPropRec>;
FDrwProcs=new TObjList<TDrwProcRec>;
FDrwParams=new TObjList<TDrwParamRec>;
FDrwClasses=new TObjList<TDrwClassesRec>;
FDrwPages=new TObjList<TDrwPageRec>;

FReady=false;
FOnError=NULL;
}

void __fastcall TDictSource::CopyList(TDictSource *S)
{
FOwnList=false;
FDictId=S->DictId;
FRefCount=S->RefCount;
FObjClasses=S->ObjClasses;
FPropClasses=S->PropClasses;
FTextProps=S->TextProps;
FDrwProcs=S->DrwProcs;
FDrwParams=S->DrwParams;
FDrwClasses=S->DrwClasses;
FDrwPages=S->DrwPages;
FReady=true;
}

void __fastcall TDictSource::Dump(String path)
{
String folder=path+String("\\")+String(FDictId)+".dct";;
ofstream out(folder.c_str());
TStringList *lst=new TStringList;
out<<GetNotEmptyCount(FObjClasses)<<" "<<FObjClasses->Count-1<<endl;
for (int i=0;i<FObjClasses->Count;i++)
        if (FObjClasses->Items[i])
                {
                FObjClasses->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FPropClasses)<<" "<<FPropClasses->Count-1<<endl;
for (int i=0;i<FPropClasses->Count;i++)
        if (FPropClasses->Items[i])
                {
                FPropClasses->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FTextProps)<<" "<<FTextProps->Count-1<<endl;
for (int i=0;i<FTextProps->Count;i++)
        if (FTextProps->Items[i])
                {
                FTextProps->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FDrwProcs)<<" "<<FDrwProcs->Count-1<<endl;
for (int i=0;i<FDrwProcs->Count;i++)
        if (FDrwProcs->Items[i])
                {
                FDrwProcs->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FDrwParams)<<" "<<FDrwParams->Count-1<<endl;
for (int i=0;i<FDrwParams->Count;i++)
        if (FDrwParams->Items[i])
                {
                FDrwParams->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FDrwPages)<<" "<<FDrwPages->Count-1<<endl;
for (int i=0;i<FDrwPages->Count;i++)
        if (FDrwPages->Items[i])
                {
                FDrwPages->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
out<<GetNotEmptyCount(FDrwClasses)<<" "<<FDrwClasses->Count-1<<endl;
for (int i=0;i<FDrwClasses->Count;i++)
        if (FDrwClasses->Items[i])
                {
                FDrwClasses->Items[i]->Dump(lst);
                out<<lst->CommaText.c_str()<<endl;
                lst->Clear();
                }
delete lst;
out.close();
}


__fastcall TDictSource::~TDictSource(void)
{
if (FOwnList)
    {
    delete DrwClasses;
    delete DrwParams;
    delete DrwProcs;
    delete TextProps;
    delete PropClasses;
    delete ObjClasses;
    delete DrwPages;
    }
}

void __fastcall TDictSource::ChangePropOrder(__int32 ClassId,int n,TTextPropRec **NewOrder)
{
int j=0;
for (int i=0;(i<TextProps->Count)&&(j<n);i++)
    {
    if (TextProps->Items[i]->PropId==ClassId)
        TextProps->Items[i]=NewOrder[j++];
    }
}

void __fastcall TDictSource::BuildClassesTree(TTreeView* tree,TTreeNode *TopNode)
{
TTreeNode **HashNode=new TTreeNode* [ObjClasses->Count];
for (int i=0;i<ObjClasses->Count;i++)
    {
    HashNode[i]=NULL;
    TObjMetaClass *rec=ObjClasses->Items[i];
    if (rec)
        if (rec->ParentId==0)
            {
            TTreeNode *Head=tree->Items->AddChild(TopNode,rec->Title);
            Head->Data=rec;
            HashNode[i]=Head;
            }
    }
bool flag=true;
while (flag)
    {
    flag=false;
    for (int i=0;i<ObjClasses->Count;i++)
        {
        TObjMetaClass *rec=ObjClasses->Items[i];
        if ((rec)&&(HashNode[i]==NULL))
            if (HashNode[rec->ParentId]!=NULL)
                {
                TTreeNode *newnod=tree->Items->AddChild(HashNode[rec->ParentId],rec->Title);
                HashNode[i]=newnod;
                newnod->Data=rec;
                flag=true;
                }
        }
    }
delete[] HashNode;
}

void __fastcall TDictSource::BuildPagesList(TStrings *slist)
{
slist->BeginUpdate();
slist->Clear();
for (int i=0;i<DrwPages->Count;i++)
    {
    TDrwPageRec *Rec=dynamic_cast<TDrwPageRec*>(DrwPages->Items[i]);
    if (Rec)
        slist->AddObject(Rec->ShortName,Rec);
    }
slist->EndUpdate();    
}

void __fastcall TDictSource::TextPropByClasses(TStrings* slist,__int32 id)
{
slist->BeginUpdate();
slist->Clear();
int n=FTextProps->Count;
for (int i=0;i<n;i++)
    {
    TTextPropRec *rec=FTextProps->Items[i];
    if (rec)
        if (rec->PropId==id)
            {
            if (rec->ShortText!="")
                slist->AddObject(rec->ShortText+" ("+rec->Text+")",(TObject*)rec);
            else
                slist->AddObject(rec->Text,(TObject*)rec);
            }
    }
slist->EndUpdate();
}

void __fastcall TDictSource::ChangePropClasses(int firstnum,int lastnum,int *newnum)
{
int n=FTextProps->Count;
for (int i=0;i<n;i++)
    {
    TTextPropRec *rec=FTextProps->Items[i];
    if (rec)
        if ((rec->PropId>=firstnum)&&(rec->PropId<=lastnum))
            rec->ChangePropId(newnum[rec->PropId-firstnum]);
    }
n=FObjClasses->Count;
for (int i=0;i<n;i++)
    {
    TObjMetaClass *rec=dynamic_cast<TObjMetaClass*>(FObjClasses->Items[i]);
    if (rec)
        {
        for (int j=0;j<rec->PropCount;j++)
                if ((rec->PropIds[j]>=firstnum)&&(rec->PropIds[j]<=lastnum))
                        rec->ReplaceProperty(j,rec->PropFlags[j],newnum[rec->PropIds[j]-firstnum]);
        }
    }
n=FPropClasses->Count;
for (int i=0;i<n;i++)
    {
    TPropClassesRec *rec=FPropClasses->Items[i];
    if (rec)
        if ((rec->Id>=firstnum)&&(rec->Id<=lastnum))
            rec->ChangeId(newnum[rec->Id-firstnum]);
    }
}

__int32 __fastcall TDictSource::FindPropId(__int32 cid,String stit)
{
stit=stit.Trim();
int n=FTextProps->Count;
TTextPropRec **Recs=(TTextPropRec**)FTextProps->List;
for (int i=0;i<n;i++)
  if (Recs[i])
    if (Recs[i]->PropId==cid)
      if (Recs[i]->ShortText==stit)
        return Recs[i]->Id;
return 0;
}

int _fastcall TDictSource::GetPropValIndex(__int32 pid)
{
int n=FTextProps->Count;
TTextPropRec **Recs=(TTextPropRec**)FTextProps->List;
for (int i=0;i<n;i++)
  if (Recs[i])
    if (Recs[i]->Id==pid)
        return i;
return -1;
}

String __fastcall TDictSource::GetShortTitle(__int32 pid)
{
int n=FTextProps->Count;
TTextPropRec **Recs=(TTextPropRec**)FTextProps->List;
for (int i=0;i<n;i++)
  if (Recs[i])
    if (Recs[i]->Id==pid)
        return Recs[i]->ShortText;
return "";
}

String __fastcall TDictSource::GetTitle(__int32 pid)
{
int n=FTextProps->Count;
TTextPropRec **Recs=(TTextPropRec**)FTextProps->List;
for (int i=0;i<n;i++)
  if (Recs[i])
    if (Recs[i]->Id==pid)
        return Recs[i]->Text;
return "";
}


__int32 __fastcall TDictSource::SelectDrwParam(__int32 code,__int32 prop,__int32 PageIndex)
{
__int32 res=0;
int n=DrwClasses->Count;
for (int i=0;i<n;i++)
        {
        TDrwClassesRec *Rec=DrwClasses->Items[i];
        if (Rec)
            if ((Rec->ObjClassId==code)&&(Rec->PagesSet&PageIndex))
                {
                if (Rec->PropValueId==prop)
                        {res=i;break;}
                else if (Rec->PropValueId==0)
                    res=i;
                }
        }
return res;
}

bool __fastcall TDictSource::CalcCondition(char *s,TRoadObject *obj)
{
char *c=s;
int npar=0;
char *lastpar=NULL;
char *firstpar=NULL;
char *sgnpos=NULL;
while (*c)
    {
    switch (*c)
        {
        case '(' : {if (!firstpar) firstpar=c;
                    npar++;}break;
        case ')' : {npar--;lastpar=c;}break;
        case '&' : if (!npar)
            {*c=0;
            bool res=CalcCondition(s,obj)&CalcCondition(c+1,obj);
            *c='&';
            return res;
            } break;
        case '|' : if (!npar)
            {*c=0;
            bool res=CalcCondition(s,obj)&CalcCondition(c+1,obj);
            *c='|';
            return res;
            } break;
        case '=': case '<': case '>': sgnpos=c;break;
        }
    c++;
    }
if (firstpar&&lastpar)
    {
    *lastpar=0;
    bool res=CalcCondition(firstpar+1,obj);
    *lastpar=')';
    return res;
    }
else if (sgnpos)
    {
    char op=*sgnpos;
    *sgnpos=0;
    String ChrName=Trim(String(s));
    String ChrVal=Trim(String(sgnpos+1));
    *sgnpos=op;
    bool res=false;
    try
        {
        int val=ChrVal.ToInt();
        int cod;
        int objval=obj->GetPropValue(ChrName).ToInt();
        switch (op)
            {
            case '=': res=objval==val;break;
            case '<': res=objval<val;break;
            case '>': res=objval>val;break;
            }
        }
    catch (...)
        {}
    return res;
    }
return false;
}

__int32 __fastcall TDictSource::SelectDrwParam(TRoadObject *obj,__int32 PageIndex)
{
int n=DrwClasses->Count;
for (int i=0;i<n;i++)
    {
    TDrwClassesRec *Rec=DrwClasses->Items[i];
    if (Rec)
        if ((Rec->ObjClassId==obj->DictId)&&(Rec->PagesSet&PageIndex))
            if (Rec->Condition!="")
                {
                if (CalcCondition(Rec->Condition.c_str(),obj))
                    return i;
                }
    }
__int32 res=0;
__int32 val=-1;
TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(ObjClasses->Items[obj->DictId]);
if (Meta)
        {
        if (Meta->MainPropId>0)
                {
                TPropClassesRec *Prop=PropClasses->Items[Meta->MainPropId];
                if (Prop)
                        {
                        try {
                            val=obj->GetPropValue(Prop->ClassName).ToInt();
                            }
                        catch (...)
                                {}
                        }
                }
        res=SelectDrwParam(obj->DictId,val,PageIndex);
        }
return res;
}

/*
__int32 __fastcall TDictSource::SelectDrwParam(TRoadObject *obj)
{
__int32 res=0;
__int32 val=-1;
TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(ObjClasses->Items[obj->DictId]);
if (Meta)
        {
        if (Meta->MainPropId>0)
                {
                TPropClassesRec *Prop=PropClasses->Items[Meta->MainPropId];
                if (Prop)
                        {
                        __int32 c;
                        try {
                            val=obj->GetPropValue(Prop->ClassName,c).ToInt();
                            }
                        catch (...)
                                {}
                        }
                }
        res=SelectDrwParam(obj->DictId,val);
        }
return res;
}
*/

__fastcall TDtaSource::TDtaSource(void)
{
FId=0;
FRefCount=0;
FOnError=NULL;
FMetricsSource=0;
FProfilKind=0;
FProfilMinLen=100;
FProfilMaxDev=20;
FProfilVal1=20;
FProfilVal2=50;
FDirVideoId=-1;
FUnDirVideoId=-1;
VideoMoved=false;
CreateClasses();
}

void __fastcall TDtaSource::CreateClasses(void)
{
FObjects=new TObjList<TRoadObject>;
FBuffer=new TObjList<TRoadObject>;
FDelBuffer=new TObjList<TRoadObject>;
FPolyList=new TObjList<TPolyline>;
FDocList=new TObjList<TDocument>;
FDirVideoTime=new TObjList<TVideoTime>;
FUnDirVideoTime=new TObjList<TVideoTime>;
FVideoHighList=new TObjList<TVideoHigh>;
FRoad=new TRoad(0,0);
FReady=false;
}

void __fastcall TDtaSource::FreeClasses(void)
{
delete FRoad;
FRoad=NULL;
delete FObjects;
FObjects=NULL;
delete FBuffer;
FBuffer=NULL;
delete FDelBuffer;
FDelBuffer=NULL;
delete FPolyList;
FPolyList=NULL;
delete FDocList;
FDocList=NULL;
delete FDirVideoTime;
FDirVideoTime=NULL;
delete FUnDirVideoTime;
FUnDirVideoTime=NULL;
delete FVideoHighList;
FVideoHighList=NULL;
}


__fastcall TDtaSource::~TDtaSource(void)
{
FreeClasses();
}

void __fastcall TDtaSource::Recreate(TDictSource *Dict)
{
FreeClasses();
CreateClasses();
}

bool __fastcall TDtaSource::TestNeedSave(void)
{
bool NeedSave=false;
if (FDelBuffer->Count)
    NeedSave=true;
else {
    if (Road->GeometryMoved||VideoMoved)
      NeedSave=true;
    for (int i=0;i<Objects->Count;i++)
        if (Objects->Items[i]->Modified)
            {NeedSave=true;break;}
}
return NeedSave;
}

#ifndef GDIEDIT

void __fastcall TDtaSource::CalculateRoadMarkLength(int AttachDist)
{
ErrorObjectDialog->NewSession();
for (int i=FObjects->Count-1;i>=0;i--)
    {
    TRoadMark *mark=dynamic_cast<TRoadMark*>(FObjects->Items[i]);
    if (mark)
        {
        if (mark->Kind==0)
            ErrorObjectDialog->Execute(mark,this,"Не указан тип разметки","Разметка");
        if (mark->LMax<mark->LMin)
            ErrorObjectDialog->Execute(mark,this,"Указанное начало разметки дальше окончания","Разметка");
        mark->Area=0;
        bool havept=false;
        if (mark->Poly)
            if (mark->Poly->Count)
                {
                int maxA=-1;
                int posL;
                int signA;
                for (int i=0;i<mark->Poly->Count;i++)
                    {
                    int absA=abs(mark->Poly->Points[i].X);
                    if (absA>maxA)
                        {
                        maxA=absA;
                        if (mark->Poly->Points[i].X>0)
                            signA=1;
                        else
                            signA=-1;
                        posL=mark->Poly->Points[i].L;
                        }
                    }
                int roadA;
                if (signA>0)
                    roadA=Road->RightLine.FindX(posL);
                else
                    roadA=-Road->LeftLine.FindX(posL);
/*                if (maxA>roadA+800)  // Линия уходит от дороги далее чем за 8 метров
                    mark->Length=AttachDist;
                else   // Считаем длину линии  */
                    {
                    double len=0;
                    for (int i=1;i<mark->Poly->Count;i++)
                        {
                        double dl=mark->Poly->Points[i].L-mark->Poly->Points[i-1].L;
                        double dx=mark->Poly->Points[i].X-mark->Poly->Points[i-1].X;
                        len+=sqrt(dl*dl+dx*dx);
                        }
                    mark->Length=len+0.5;
                    }
                // А здесь посчитаем площадь
                if (mark->Kind==ma16_1 || mark->Kind==ma16_2 || mark->Kind==ma16_3) {
                    long long s=0;
                    for (int i=2;i<mark->Poly->Count;i++) {
                       long long dl1=mark->Poly->Points[i-1].L-mark->Poly->Points[0].L;
                       long long dx1=mark->Poly->Points[i-1].X-mark->Poly->Points[0].X;
                       long long dl2=mark->Poly->Points[i].L-mark->Poly->Points[0].L;
                       long long dx2=mark->Poly->Points[i].X-mark->Poly->Points[0].X;
                       s+=dl1*dx2-dl2*dx1;
                    }
                    mark->Area=(s<0?-s:s)/2;
                }
                havept=true;
                }
        if (!havept)
            mark->Length=mark->LMax-mark->LMin;
        }
    }

}

struct dpart {
   int begin,end,prom;
   dpart(int b,int e,int p) : begin(b),end(e),prom(p) {}
};
bool operator<(const dpart &a,const dpart &b) {
   return a.begin<b.begin||a.begin==b.begin && a.end<b.end;
}

void __fastcall TDtaSource::CalcGeometry(int MinL,int MaxL) {
   vector<dpart> V;
   for (int i=0;i<FObjects->Count;i++)
      {
      TRoadObject *Obj=FObjects->Items[i];
      if (Obj->DictId==DANGERSLOPECODE) {
         TDangerSlope *slp=dynamic_cast<TDangerSlope*>(Obj);
         if (slp)
            V.push_back(dpart(slp->LMin,slp->LMax,slp->Promille));
         }
   }
   sort(V.begin(),V.end());
   int k=1;
   int L=MinL;
   for (unsigned i=0;i<V.size();i++) {
      if (V[i].begin>L)
         L=V[i].begin,k++;
      if (V[i].end>L)
         L=V[i].end,k++;
   }
   if (MaxL>L)
      k++;
   Road->Geometry.SetCount(k);
   Road->Geometry.L[0]=MinL;
   L=MinL;
   int CZ=0;
   k=1;
   Road->Geometry.Values[0]=TGeometryVal(L,0,CZ,0,20,20,0,0);
   for (unsigned i=0;i<V.size();i++) {
      if (V[i].begin>L) {
         L=V[i].begin;
         Road->Geometry.L[k]=L;
         Road->Geometry.Values[k]=TGeometryVal(L,0,CZ,0,20,20,0,0);
         k++;
      }
      if (V[i].end>L) {
         CZ+=(V[i].end-L)*V[i].prom/1000;
         L=V[i].end;
         Road->Geometry.L[k]=L;
         Road->Geometry.Values[k]=TGeometryVal(L,0,CZ,0,20,20,0,0);
         k++;
      }
   }
   if (MaxL) {
         L=MaxL;
         Road->Geometry.L[k]=L;
         Road->Geometry.Values[k]=TGeometryVal(L,0,CZ,0,20,20,0,0);
         k++;
   }
}

void __fastcall TDtaSource::BuildLongSlopesPart(TDictSource *Dict,int sp,int ep)
{
for (int i=FObjects->Count-1;i>=0;i--)
    {
    TRoadObject *Obj=FObjects->Items[i];
    if (Obj->DictId==DANGERSLOPECODE)
        DeleteObject(i);
    }
int n;
TSlopesPart* Parts=Road->Geometry.BuildSlopesPart(ProfilMinLen*100,ProfilMaxDev,n);
for (int i=0;i<n;i++)
    {
    TDangerSlope *Slp=dynamic_cast<TDangerSlope*>(FFactory->CreateRoadObj("TDangerSlope",0,DANGERSLOPECODE));
    if ((Parts[i].L2>sp)&&(Parts[i].L1<ep))
        {
        int Start=Parts[i].L1<sp ? sp: Parts[i].L1;
        int End=Parts[i].L2>ep ? ep: Parts[i].L2;
        Slp->PutPosition(Start,End);
        Slp->Promille=Parts[i].Value;
        if (abs(Parts[i].Value)<=FProfilVal2)
            Slp->Permissible=tpYes;
        else
            Slp->Permissible=tpNo;
        Slp->DrwClassId=Dict->SelectDrwParam(Slp,1);
        FBuffer->Add(Slp);
        }
    }
delete[] Parts;
AddFromBufer();
}

void __fastcall TDtaSource::BuildSimplePart(int spos,int epos,int step,TDictSource *Dict) {
TPolyline T,Q,P;
T.Sum(&(Road->RightLine),&(Road->LeftLine),1,-1);
Q.CopyAndCut(&T,spos,epos);
P.MakeSimplePart(&Q,step);
  for (int i=1;i<P.Count;i++) {
        TObjMetaClass *Rec=Dict->ObjClasses->Items[WIDTHCODE];
        TRoadObject *RObj=Factory->CreateRoadObj(Rec->ClassName,0,WIDTHCODE);
        RObj->PutProperty("L",String(P.Points[i-1].L));
        RObj->PutProperty("LMax",String(P.Points[i].L));
        RObj->PutProperty("Width",P.Points[i-1].X);
        RObj->PutProperty("EWidth",P.Points[i].X);        
        RObj->DrwClassId=Dict->SelectDrwParam(RObj,1);
        FBuffer->Add(RObj);
  }
AddFromBufer();  
}

void __fastcall TDtaSource::BuildWidePart(int spos,int epos,int step,int roundval,TDictSource *Dict)
{
TPolyline T,Q,P;
T.Sum(&(Road->RightLine),&(Road->LeftLine),1,-1);
Q.CopyAndCut(&T,spos,epos);
P.MakeWidePart(&Q,step,roundval);
for (int i=1;i<P.Count;i+=2)
    {
    if (P.Points[i].X>=roundval)
        {
        TObjMetaClass *Rec=Dict->ObjClasses->Items[WIDTHCODE];
        TRoadObject *RObj=Factory->CreateRoadObj(Rec->ClassName,0,WIDTHCODE);
        RObj->PutProperty("L",String(P.Points[i-1].L));
        RObj->PutProperty("LMax",String(P.Points[i].L));
        RObj->PutProperty("Width",P.Points[i].X);
        RObj->DrwClassId=Dict->SelectDrwParam(RObj,1);
        FBuffer->Add(RObj);
        }
    }
AddFromBufer();
}

void __fastcall TDtaSource::BuildRoadSides(int spos,int epos,TRoadSide side,int step,int roundval,int ref,TDictSource *Dict)
{
TPolyline T,P,Q;
if (side==rsRight)
    T.Sum(&(Road->RightSide),&(Road->RightLine),1,-1);
else
    T.Sum(&(Road->LeftSide),&(Road->LeftLine),-1,1);
Q.CopyAndCut(&T,spos,epos);
P.MakeWidePart(&Q,step,roundval);
for (int i=1;i<P.Count;i+=2)
    {
    if (P.Points[i].X>=roundval)
        {
        TObjMetaClass *Rec=Dict->ObjClasses->Items[ROADSIDECODE];
        TRoadObject *RObj=Factory->CreateRoadObj(Rec->ClassName,0,ROADSIDECODE);
        RObj->PutProperty("L",String(P.Points[i-1].L));
        RObj->PutProperty("LMax",String(P.Points[i].L));
        RObj->PutProperty("DX",String(P.Points[i].X));
        RObj->PutProperty("Placement",String(int(side)));
        RObj->PutProperty("Strength",String(int(ref)));
        RObj->DrwClassId=Dict->SelectDrwParam(RObj,1);
        FBuffer->Add(RObj);
        }
    }
AddFromBufer();
}

void __fastcall TDtaSource::BreakRoadLines(void) {
   for (int i=0;i<FObjects->Count;i++) {
      if (FObjects->Items[i]->DictId==ROADMETRIC) {
         TLinearRoadSideObject *t=dynamic_cast<TLinearRoadSideObject*>(FObjects->Items[i]);
         if (t && t->Poly) {
            for (int j=0;j<FObjects->Count;j++) {
               if (FObjects->Items[j]->DictId==ROADATTACH) {
                  TRoadAttach *a=dynamic_cast<TRoadAttach*>(FObjects->Items[j]);
                  if (t->MetricsKind==mkKromka && (a->Tech==rc5 || a->Tech==rcnone))
                     continue;
                  if (a && a->Poly) {
                     TRoadPoint p1,p2;
                     int n1=0,n2=0,k,h;    //Номера точек отрезок после которых пересекается с примыканием
                     int sind=1,eind=a->Poly->Count;
                     // В начале проверим конечные точки примыкания
                     if (t->Poly->LenTo(a->Poly->Points[0],p1,h)<2.0)
                        n1=h+1,sind++;
                     if (t->Poly->LenTo(a->Poly->Points[a->Poly->Count-1],p2,h)<2.0) {
                        eind--;
                        if (n1)
                           n2=h+1;
                        else
                           n1=h+1,p1=p2;
                     }
                     for (k=sind;n2==0 && k<eind;k++) {
                        (n1==0?n1:n2)=t->Poly->CrossLine(a->Poly->Points[k-1],a->Poly->Points[k],(n1==0?p1:p2));
                        if (n2 && abs (p2.L-p1.L)<100)
                           n2=0;
                     }
                     if (n2>0) {
                        p2.Code=1;
                        p1.Code=1;
                        p1.BasePar1=p1.L;
                        p1.BasePar2=p1.X;
                        p2.BasePar1=p2.L;
                        p2.BasePar2=p2.X;
                        if (n2<n1 || n2==n1 && p2.L<p1.L) {
                           swap(n1,n2);
                           swap(p1,p2);
                        }
                        if (p1.X==t->Poly->Points[n1-1].X && p1.L==t->Poly->Points[n1-1].L)
                           n1--;
                        else if (p1.X==t->Poly->Points[n1].X && p1.L==t->Poly->Points[n1].L)
                            {}
                        else {
                           t->Poly->InsertPoint(p1,n1);
                           n2++;
                        }
                        if (p2.X==t->Poly->Points[n2-1].X && p2.L==t->Poly->Points[n2-1].L)
                           n2--;
                        else if (p2.X==t->Poly->Points[n2].X && p2.L==t->Poly->Points[n2].L)
                            {}
                        else {
                           t->Poly->InsertPoint(p2,n2);
                        }
                        for (int i=n1+1;i<=n2;i++)
                           t->Poly->Points[i].Code.SetVisible(0);
                     }
                  }
               }
            }
         }
      }
   }
}

void __fastcall TDtaSource::BuildWidthMeasure(int step,TDictSource *Dict)
{
for (int i=FObjects->Count-1;i>=0;i--)
    {
    TRoadObject *Obj=FObjects->Items[i];
    if (Obj->DictId==WIDTHMEASURECODE)
        DeleteObject(i);
    }
for (int i=(Road->LMin+step-1)/step;i<Road->LMax/step;i++)
    {
    TObjMetaClass *Rec=Dict->ObjClasses->Items[WIDTHMEASURECODE];
    TRoadObject *RObj=Factory->CreateRoadObj(Rec->ClassName,0,WIDTHMEASURECODE);
    RObj->PutProperty("L",String(i*step));
    RObj->DrwClassId=Dict->SelectDrwParam(RObj,1);
    FBuffer->Add(RObj);
    }
AddFromBufer();
}

void __fastcall TDtaSource::BuildRoadMetrics(int MetSour)
{
if (MetSour<0)
    MetSour=FMetricsSource;
if (MetSour==0)
    {
    TPolyline MovePart; // Проезжая часть
    TPolyline DivPart;  // Разделительная полоса
    TPolyline SpeedPartL; //Полоса разгона слева
    TPolyline SpeedPartR; //Полоса разгона справа
    TPolyline ObochinaL;
    TPolyline ObochinaR;
    TPolyline SumMoveDiv;
    TPolyline SumSpeed;
    TPolyline Sum;
    Road->LeftLine.Count=0;
    Road->RightLine.Count=0;
    Road->LeftSide.Count=0;
    Road->RightSide.Count=0;
    Road->LeftZem.Count=0;
    Road->RightZem.Count=0;
    Road->LeftDivPart.Count=0;
    Road->RightDivPart.Count=0;
    int n=Objects->Count;
    for (int i=0;i<n;i++)
        {
        TBandRoadPart *pobj=dynamic_cast<TBandRoadPart*>(Objects->Items[i]);
        if (pobj)
            switch (pobj->DictId)
                {
                case WIDTHCODE:
                    {
                    if (!MovePart.Count)
                        MovePart.AddLine(true,Road->LMin,pobj->L,0);
                    MovePart.AddLine(true,pobj->L,pobj->LMax,pobj->Width);
                    }break;
                case DIVPARTCODE:
                    {
                    if (!DivPart.Count) {
                        DivPart.AddLine(false,Road->LMin,pobj->L,0);
                        Road->LeftDivPart.AddLine(false,Road->LMin,pobj->L,0);
                        Road->RightDivPart.AddLine(false,Road->LMin,pobj->L,0);
                    }
                    DivPart.AddLine(false,pobj->L,pobj->LMax,pobj->Width);
                    Road->LeftDivPart.AddLine(false,pobj->L,pobj->LMax,-pobj->Width/2);
                    Road->RightDivPart.AddLine(false,pobj->L,pobj->LMax,pobj->Width/2);
                    } break;
                case ADDPARTCODE:
                    {
                    TRoadSide pl=TRoadSide(pobj->GetPropValue("Placement").ToInt());
                    if (pl==rsLeft)
                        {
                        if (!SpeedPartL.Count)
                            SpeedPartL.AddLine(false,Road->LMin,pobj->L,0);
                        SpeedPartL.AddLine(false,pobj->L,pobj->LMax,pobj->Width);
                        }
                    else
                        {
                        if (!SpeedPartR.Count)
                            SpeedPartR.AddLine(false,Road->LMin,pobj->L,0);
                        SpeedPartR.AddLine(false,pobj->L,pobj->LMax,pobj->Width);
                        }
                    } break;
                case ZEMPOLOTNOCODE:
                    {
                    if (!Road->LeftZem.Count)
                        {
                        Road->LeftZem.AddLine(true,Road->LMin,pobj->L,0);
                        Road->RightZem.AddLine(true,Road->LMin,pobj->L,0);
                        }
                    Road->LeftZem.AddLine(true,pobj->L,pobj->LMax,-pobj->Width/2);
                    Road->RightZem.AddLine(true,pobj->L,pobj->LMax,pobj->Width/2);
                    }
                }
        TObochina *bobj=dynamic_cast<TObochina*>(Objects->Items[i]);
        if (bobj)
            {
            if (bobj->Placement==rsLeft)
                {
                if (!ObochinaL.Count)
                    ObochinaL.AddLine(false,Road->LMin,bobj->L,0);
                ObochinaL.AddLine(false,bobj->L,bobj->LMax,bobj->DX);
                }
            else
                {
                if (!ObochinaR.Count)
                    ObochinaR.AddLine(false,Road->LMin,bobj->L,0);
                ObochinaR.AddLine(false,bobj->L,bobj->LMax,bobj->DX);
                }
            }
        }
    if (!MovePart.Count)
        MovePart.AddLine(true,Road->LMin,Road->LMax,0);
    else
        MovePart.AddLine(true,MovePart.Points[MovePart.Count-1].L,Road->LMax,0);

    if (!DivPart.Count)
        DivPart.AddLine(false,Road->LMin,Road->LMax,0);
    else
        DivPart.AddLine(false,DivPart.Points[DivPart.Count-1].L,Road->LMax,0);

    if (!SpeedPartL.Count)
        SpeedPartL.AddLine(false,Road->LMin,Road->LMax,0);
    else
        SpeedPartL.AddLine(false,SpeedPartL.Points[SpeedPartL.Count-1].L,Road->LMax,0);

    if (!SpeedPartR.Count)
        SpeedPartR.AddLine(false,Road->LMin,Road->LMax,0);
    else
        SpeedPartR.AddLine(false,SpeedPartR.Points[SpeedPartR.Count-1].L,Road->LMax,0);
    if (!ObochinaL.Count)
        ObochinaL.AddLine(false,Road->LMin,Road->LMax,0);
    else
        ObochinaL.AddLine(false,ObochinaL.Points[ObochinaL.Count-1].L,Road->LMax,0);
    if (!ObochinaR.Count)
        ObochinaR.AddLine(false,Road->LMin,Road->LMax,0);
    else
        ObochinaR.AddLine(false,ObochinaR.Points[ObochinaR.Count-1].L,Road->LMax,0);

    SumMoveDiv.Sum(&MovePart,&DivPart,1,1);
    SumSpeed.Sum(&SpeedPartL,&SpeedPartR,1,1);
    Sum.Sum(&SumMoveDiv,&SumSpeed,1,-1);
    Sum.MulDiv(1,2);
    Road->RightLine.Sum(&Sum,&SpeedPartR,1,1);
    Road->LeftLine.Sum(&Sum,&SpeedPartL,-1,-1);
    Road->LeftSide.Sum(&(Road->LeftLine),&ObochinaL,1,-1);
    Road->RightSide.Sum(&(Road->RightLine),&ObochinaR,1,1);
    Road->RightLine.MakeMiddlePart(2000);
    Road->LeftLine.MakeMiddlePart(2000);
    Road->RightSide.MakeMiddlePart(2000);
    Road->LeftSide.MakeMiddlePart(2000);
    Road->LeftBound.CopyPoints(&(Road->LeftLine));
    Road->RightBound.CopyPoints(&(Road->RightLine));    
    }
else
    {
    Road->LeftLine.Count=2;
    Road->RightLine.Count=2;
    Road->LeftSide.Count=2;
    Road->RightSide.Count=2;
    Road->LeftDivPart.Count=2;
    Road->RightDivPart.Count=2;
    Road->LeftBound.Count=2;
    Road->RightBound.Count=2;
    Road->LeftLine[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->LeftLine[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->RightLine[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->RightLine[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->LeftSide[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->LeftSide[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->RightSide[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->RightSide[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->LeftDivPart[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->LeftDivPart[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->RightDivPart[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->RightDivPart[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->LeftBound[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->LeftBound[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    Road->RightBound[0]=TRoadPoint(Road->LMin,0,1,Road->LMin,0,0);
    Road->RightBound[1]=TRoadPoint(Road->LMax,0,1,Road->LMax,0,0);
    int n=Objects->Count;
    for (int i=0;i<n;i++)
        {
        TLinearRoadSideObject *pobj=dynamic_cast<TLinearRoadSideObject*>(Objects->Items[i]);
        if (pobj)
            if (pobj->DictId==ROADMETRIC)
                if (pobj->Poly)
                    {
                    if (pobj->MetricsKind==mkKromka)
                        {
                        TPolyline *Poly;
                        if (pobj->Placement==opRight)
                            Poly=&(FRoad->RightLine);
                        else
                            Poly=&(FRoad->LeftLine);
                        Poly->AddPoly(pobj->Poly);
                        }
                    else if (pobj->MetricsKind==mkBoundLine) {
                        TPolyline *Poly;
                        if (pobj->Placement==opRight)
                            Poly=&(FRoad->RightBound);
                        else
                            Poly=&(FRoad->LeftBound);
                        Poly->AddPoly(pobj->Poly);
                        }

                    }
        }
    if (FRoad->RightBound.Count==2)
        FRoad->RightBound.AddPoly(&(FRoad->RightLine));
    if (FRoad->LeftBound.Count==2)
        FRoad->LeftBound.AddPoly(&(FRoad->LeftLine));
    for (int i=0;i<n;i++)
        {
        TLinearRoadSideObject *pobj=dynamic_cast<TLinearRoadSideObject*>(Objects->Items[i]);
        if (pobj)
            if (pobj->DictId==ROADMETRIC)
                if (pobj->Poly)
                    {
                    if (pobj->MetricsKind==mkBrovka)
                        {
                        TPolyline *Poly;
                        if (pobj->Placement==opRight)
                            Poly=&(FRoad->RightSide);
                        else
                            Poly=&(FRoad->LeftSide);
                        Poly->AddPoly(pobj->Poly);
                        }
                    }
        }
    for (int i=0;i<n;i++)
        {
        TLinearRoadSideObject *pobj=dynamic_cast<TLinearRoadSideObject*>(Objects->Items[i]);
        if (pobj)
            if (pobj->DictId==ROADMETRIC)
                if (pobj->Poly)
                    {
                    if (pobj->MetricsKind==mkDivPart)
                        {
                        TPolyline *Poly;
                        if (pobj->Placement==opRight)
                            Poly=&(FRoad->RightDivPart);
                        else
                            Poly=&(FRoad->LeftDivPart);
                        Poly->AddPoly(pobj->Poly);
                        }
                    }
        }
    Road->LeftSide.ReplaceNullPart(&(Road->LeftLine));
    Road->RightSide.ReplaceNullPart(&(Road->RightLine));
    Road->RightLine.ReplaceNullPart(&(Road->RightSide));
    Road->LeftLine.ReplaceNullPart(&(Road->LeftSide));
    Road->RightLine.ReplaceNullPart(&(Road->RightDivPart));
    Road->LeftLine.ReplaceNullPart(&(Road->LeftDivPart));
    }
Road->LeftSide.Trim();
Road->RightSide.Trim();
Road->RightLine.Trim();
Road->LeftLine.Trim();
Road->LeftLine.FastSetParam();
Road->RightLine.FastSetParam();
Road->LeftSide.FastSetParam();
Road->RightSide.FastSetParam();
}

void __fastcall TDtaSource::CalcMetrics(TRoad *RefRoad)
{
for (int i=0;i<FObjects->Count;i++)
    {
    TRoadObject *Obj=FObjects->Items[i];
    if (Obj->Poly)
        RefRoad->CalcPointsPos(Obj->Poly,Obj);
    }
for (int i=0;i<FDelBuffer->Count;i++)
    {
    TRoadObject *Obj=FDelBuffer->Items[i];
    if (Obj->Poly)
        RefRoad->CalcPointsPos(Obj->Poly,Obj);
    }
}

#endif

String __fastcall TDtaSource::GetDumpName(void)
{
if (FDumpName=="")
    {
    if (FReady)
        return RoadName+String("_")+String(FId)+String("_")+String(FDataType)+String(".dta");
    else
        return "Empty.dta";
    }
else
    return FDumpName;
}
void __fastcall TDtaSource::SetDumpName(String s)
{
FDumpName=s;
}
String __fastcall TDtaSource::GetDumpPath(void)
{
if (FDumpPath=="")
    return Application->ExeName.Delete(Application->ExeName.LastDelimiter("\\"),1024);
else
    return FDumpPath;
}
void __fastcall TDtaSource::SetDumpPath(String s)
{
FDumpPath=s;
}

void __fastcall TDtaSource::Dump(TDictSource *Dict,bool savegeom)
{
String folder=GetDumpPath()+String("\\")+GetDumpName();
ofstream out(folder.c_str());
out<<FRoadName.c_str()<<endl;
out<<FSourceName.c_str()<<endl;
out<<FId<<" "<<FDataType<<" "<<FDataClass<<endl;
out<<FRoad->LMin<<" "<<FRoad->LMax<<" "<<FRoad->XMin<<" "<<FRoad->XMax<<endl;
//Road->RightLine.Dump(out);
//Road->LeftLine.Dump(out);
//Road->RightSide.Dump(out);
//Road->LeftSide.Dump(out);
out<<PolyList->Count<<endl;
for (int i=0;i<PolyList->Count;i++)
    PolyList->Items[i]->Dump(out);
if (savegeom)
    FRoad->Geometry.Dump(out);
else
    out<<0<<endl;
out<<Objects->Count<<endl;
TStringList *slst=new TStringList;
for (int i=0;i<Objects->Count;i++)
  {
  Objects->Items[i]->Dump(slst,Dict);
  out<<slst->CommaText.c_str();
  out<<endl;
  slst->Clear();
  }
out.close();
}

void __fastcall TDtaSource::Load(__int32 id_,__int32 dataclass_,TDictSource *Dict)
{}

void __fastcall TDtaSource::Apply(TDictSource *Dict)
{}


TRoadObject* __fastcall TDtaSource::CopyObject(TRoadObject *obj,TDictSource *Dict,int newid)
{
TRoadObject* Res=NULL;

#ifndef GDIEDIT

bool doinsert=true;
obj->DictId;
TObjMetaClass *Meta=(TObjMetaClass*)Dict->ObjClasses->Items[obj->DictId];
if (Meta)
    {
    Res=FFactory->CreateRoadObj(Meta->ClassName,newid,obj->DictId);
    if (Res)
        {
        if (obj->Id)
            {
            int n=Objects->Count;
            TRoadObject *oldobj=NULL;
            for (int i=0;i<n;i++)
                {
                TRoadObject *xobj=Objects->Items[i];
                if (xobj)
                    if (xobj->PrevId==obj->Id)
                        {oldobj=xobj;break;}
                }
            if (FrmSetting->CopyIndex==0)
                {
                if (oldobj)
                    DeleteObject(oldobj);
                }
            else if (FrmSetting->CopyIndex==1)
                {
                if (oldobj)
                    {delete Res;Res=oldobj;doinsert=false;}
                }
            }
        if (doinsert)
            {
            for (int i=0;i<Meta->PropCount;i++)
                {
                int pid=Meta->PropIds[i];
                String val=obj->GetPropValue(Dict->PropClasses->Items[pid]->ClassName);
                TPropClassesRec *rec=Dict->PropClasses->Items[pid];
                Res->PutProperty(rec->ClassName,val);
                }
            if (obj->Poly)
                {
                Res->Poly=new TPolyline(obj->Poly,0);
                Road->CalcPointsPos(Res->Poly,obj);
                FPolyList->Add(Res->Poly);
                }
            Res->PutProperty("PrevId",obj->Id);
            FBuffer->Add(Res);
            }
        }
    }
#endif    
return Res;
}

void __fastcall TDtaSource::DeleteObjectEx(TRoadObject* robj)
{
#ifndef GDIEDIT
SetMarker(0);
robj->MarkTagByTree(1);
TRoadObject **FList=(TRoadObject**)FObjects->List;
for (int i=FObjects->Count-1;i>=0;i--)
    if (FList[i]->Tag==1)
        {
        FList[i]->Test=stBad;
        MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)FList[i],(int)this);
        }
#endif
}

void __fastcall TDtaSource::DeleteObject(int index)
{
if ((index>=0)&&(index<FObjects->Count))
    {
    TRoadObject* Obj=FObjects->Items[index];
    if (Obj->Parent)
        Obj->Parent->RemoveChild(Obj);
    Obj->Parent=NULL;
    Obj->Child=NULL;
    Obj->Sibling=NULL;
    if (Obj->Id>0)
        FDelBuffer->Add(Obj);
    else
        {
        if (Obj->Poly)
            {
            FPolyList->Remove(Obj->Poly);
            delete Obj->Poly;
            }
        delete Obj;
        }
    FObjects->Delete(index);
    }
}

#ifndef GDIEDIT

void __fastcall TDtaSource::CopySelectedObjects(TDictSource *Dict)
{
TDtaSource *Dest=MainForm->ResManager->CopyDestination;
if (Dest==this)
    {
    ShowMessage("Нельзя копировать объекты в себя");
    return;
    }
if (Dest)
    {
    Dest->Apply(Dict);
    for (int i=0;i<Objects->Count;i++)
        {
        TRoadObject *ro=Objects->Items[i];
        if (ro)
            if (ro->Selected)
                {
                TRoadObject* Nobj=Dest->CopyObject(ro,Dict);
                if (Nobj)
                    {
                    Nobj->DrwClassId=Dict->SelectDrwParam(Nobj,1);
                    ro->Selected=false;
                    }
                }
        }
    Dest->AddFromBufer();
    Dest->BuildRoadMetrics();
    MainForm->SendBroadCastMessage(CM_SELECTOFF,0,(int)this);
    MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)Dest);
    }
}


void __fastcall TDtaSource::AddRoadLine(TDictSource *Dict,TPolyline *Poly,int plc,int knd)
{
TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[ROADMETRIC]);
if (Meta)
    {
    TLinearRoadSideObject *Obj=dynamic_cast<TLinearRoadSideObject*>(FFactory->CreateRoadObj(Meta->ClassName,0,ROADMETRIC));
    if (Obj)
        {
        Obj->Poly=Poly;
        Obj->Placement=TObjPlacement(plc);
        Obj->MetricsKind=TMetricsKind(knd);
        Obj->DrwClassId=Dict->SelectDrwParam(Obj,1);
        if (Poly)
            if (Poly->Count)
                {
                Obj->PutPosition((*Poly)[0].L,(*Poly)[Poly->Count-1].L);
                (*Poly)[0].Code=0;
                int n=Poly->Count;
                for (int i=1;i<n;i++)
                    (*Poly)[i].Code=1;
                }
        FBuffer->Add(Obj);
        }
    }
}

void __fastcall TDtaSource::BuildRoadLines(TDictSource *Dict)
{
for (int i=FObjects->Count-1;i>=0;i--)
    {
    TRoadObject *Obj=FObjects->Items[i];
    if (Obj->DictId==ROADMETRIC)
        DeleteObject(i);
    }
TPolyline *pl=new TPolyline(&(Road->LeftSide),0);
FPolyList->Add(pl);
AddRoadLine(Dict,pl,rsLeft,mkBrovka);

pl=new TPolyline(&(Road->RightSide),0);
FPolyList->Add(pl);
AddRoadLine(Dict,pl,rsRight,mkBrovka);

pl=new TPolyline(&(Road->LeftLine),0);
FPolyList->Add(pl);
AddRoadLine(Dict,pl,rsLeft,mkKromka);

pl=new TPolyline(&(Road->RightLine),0);
FPolyList->Add(pl);
AddRoadLine(Dict,pl,rsRight,mkKromka);
AddFromBufer();
}

void __fastcall TDtaSource::RemoveSelectedObjects(void)
{
SetMarker(0);
for (int i=Objects->Count-1;i>=0;i--)
    {
    TRoadObject *ro=Objects->Items[i];
    if (ro)
        if (ro->Selected)
            ro->MarkTagByTree(1);
    }
DeleteMarkedObjects(1);
MainForm->SendBroadCastMessage(CM_SELECTOFF,0,(int)this);
MainForm->SendBroadCastMessage(CM_DELETEGROUP,0,(int)this);
}

TRoadObject* __fastcall TDtaSource::FindObject(__int32 id)
{
int n=Objects->Count;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
for (int i=0;i<n;i++)
    if (ObjList[i])
        if (ObjList[i]->Id==id)
            return ObjList[i];
return NULL;
}

__int32 TDtaSource::BinarySearch(__int32 lmin,__int32 lmax,__int32 &ind1,__int32 &ind2)
{
int n=Objects->Count;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
int hpos=0;
int epos=n;
while (hpos<epos)
    {
    int mid=(hpos+epos)>>1;
    if (ObjList[mid]->L<lmin)
        hpos=mid+1;
    else
        epos=mid;
    }  // epos указавает на элемент >= lmin , указавает на элемент меньший lmin или
       // первый, который >= , в конце  hpos=epos   |->
        // hpos указыват на первый элемент >= lmin или на n-1
int apos=-1;
int bpos=n-1;
while (apos<bpos)
    {
    int mid=(apos+bpos+1)>>1;
    if (ObjList[mid]->L>lmax)
        bpos=mid-1;
    else
        apos=mid;
    }        // bpos указывает на элемент > lmax или первый <=lmax
             // apos указывает на элемент <= lmax . В конце apos=bpos |->
             // bpos указывает на первый элемент <= lmax или на 0
int res=bpos-hpos+1;
if (res<0)
    res=0;
ind1=hpos;
ind2=bpos;
return res;
}

TRoadObject* __fastcall TDtaSource::FindNext(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index)
{
int n=Objects->Count;
int ind2;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
if (index<0)
    BinarySearch(lmin,lmax,index,ind2);
while (index<n)
    {
    int L=ObjList[index]->L;
    if (L>lmax)
        return NULL;
    else if ((L>=lmin)&&(ObjList[index]->DictId==dictid))
        return ObjList[index];
    index++;
    }
return NULL;
}

TRoadObject* __fastcall TDtaSource::FindPred(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index)
{
int ind1;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
if (index<0)
    BinarySearch(lmin,lmax,ind1,index);
while (index>=0)
    {
    int L=ObjList[index]->L;
    if (L<lmin)
        return NULL;
    else if ((L<=lmax)&&(ObjList[index]->DictId==dictid))
        return ObjList[index];
    index--;
    }
return NULL;
}

TRoadObject* __fastcall TDtaSource::FindRoadPart(__int32 dictid,__int32 l)
{
int ind1,ind2;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
BinarySearch(l,l,ind1,ind2);
while (ind2>=0)
    {
    if (ObjList[ind2]->DictId==dictid)
        {
        TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(ObjList[ind2]);
        if (cobj)
            if (cobj->LMax>=l)
                return cobj;
            else
                return NULL;
        }
    ind2--;
    }
return NULL;
}

void __fastcall TDtaSource::SortByPlacement(void)
{
int stkm=Road->LMin/100000;
int endkm=Road->LMax/100000;
int nkm=endkm-stkm+1;
int *nobj=new int [nkm];
TRoadObject ***objs=new TRoadObject** [nkm];
for (int i=0;i<nkm;i++)
    nobj[i]=0;
int n=Objects->Count;
TRoadObject **ObjList=(TRoadObject**)Objects->List;
for (int i=0;i<n;i++)
  {
    int km=ObjList[i]->L/100000-stkm;
    if (km<0)
      km=0;
    else if (km>=nkm)
      km=nkm-1;
    nobj[km]++;
  }
for (int i=0;i<nkm;i++)
    objs[i]=new TRoadObject* [nobj[i]];
for (int i=0;i<nkm;i++)
    nobj[i]=0;
for (int i=0;i<n;i++)
    {
    int km=ObjList[i]->L/100000-stkm;
    if (km<0)
      km=0;
    else if (km>=nkm)
      km=nkm-1;
    objs[km][nobj[km]++]=ObjList[i];
    }
for (int i=0;i<nkm;i++)
    {
    TRoadObject **obarray=objs[i];
    int arsize=nobj[i];
    for (int j=0;j<arsize;j++)
        {
        TRoadObject *MinObj=obarray[j];
        int minnum=j;
        for (int k=j+1;k<arsize;k++)
            if (MinObj->L>obarray[k]->L)
                MinObj=obarray[k],minnum=k;
            else if (MinObj->L==obarray[k]->L)
                {
// Упорядочивание объектов по коду
                if (MinObj->DictId>obarray[k]->DictId)
                    MinObj=obarray[k],minnum=k;
// упорядочивание объектов по направлению, если это знаки
                else if (MinObj->DictId==obarray[k]->DictId)
                    {
                    TRoadSign *Min=dynamic_cast<TRoadSign*>(MinObj);
                    TRoadSign *Cur=dynamic_cast<TRoadSign*>(obarray[k]);
                    if ((Min)&&(Cur))
                        if ((Cur->Direction==roDirect)&&(Min->Direction==roUnDirect))
                            MinObj=obarray[k],minnum=k;
                        else if (Cur->Placement>Min->Placement)
                            MinObj=obarray[k],minnum=k;
                    }
                }
        obarray[minnum]=obarray[j];
        obarray[j]=MinObj;
        }
    }
int k=0;
for (int i=0;i<nkm;i++)
    for (int j=0;j<nobj[i];j++)
        ObjList[k++]=objs[i][j];
for (int i=0;i<nkm;i++)
    delete[] objs[i];
delete[] objs;
delete[] nobj;
}

TRoadSign* __fastcall TDtaSource::AddPrjSign(TDictSource *Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String code,String label,String note,TSignAttach onattach)
{
int id;
int cid;
int pid;
int did;
if ((code[1]<='7')&&(code[1]>='0'))
  {
  did=SGNCODE+code[1]-'0';
  cid=SIGNGOSTCODE+code[1]-'1';
  pid=Dict->FindPropId(cid,code);

  TRoadSign *s=new TRoadSign(0,did);
  s->Placement=pl;
  s->PutPosition(fl,fx,dir);
  s->SetAutoTest(stGood,note);
  s->NumRoadSign=pid;
  s->Label=label;
  s->OldTitle=code;
  s->OnAttach=onattach;
//  TRoadSign *s=new TRoadSign(seNotExist,stGood,Note,stUnknown,"",Code,Label,dir,pl,fl,fx,id,did,cid,pid,0);
  s->DrwClassId=Dict->SelectDrwParam(s,1);
  FBuffer->Add(s);
  return s;
  }
return NULL;
}

TRoadSign* __fastcall TDtaSource::CreateManSign(TDictSource *Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String code,String label,String note)
{
int id;
int cid;
int pid;
int did;
if ((code[1]<='8')&&(code[1]>='0'))
  {
  did=SGNCODE+code[1]-'0';
  cid=SIGNGOSTCODE+code[1]-'1';
  pid=Dict->FindPropId(cid,code);
  TRoadSign *s=new TRoadSign(0,did);
  s->Placement=pl;
  s->PutPosition(fl,fx,dir);
  s->SetAutoTest(stGood,note);
  s->NumRoadSign=pid;
  s->Label=label;
  s->OldTitle=code;
  s->OnAttach=TSignAttach(0);
  s->DrwClassId=Dict->SelectDrwParam(s,1);
  return s;
  }
return NULL;
}

TRoadSign* __fastcall TDtaSource::AddManSign(TDictSource *Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String code,String label,String note)
{
TRoadSign *s=CreateManSign(Dict,dir,pl,fl,fx,code,label,note);
if (s)
    AddRoadObject(s);
return s;
}

void __fastcall TDtaSource::AddFromBufer(void)
{
TRoadObject **FList=(TRoadObject**)FBuffer->List;
int n=FBuffer->Count;
for (int i=0;i<n;i++)
  {
  FObjects->Add(FList[i]);
  FList[i]=NULL;
  }
FBuffer->Clear();
SortByPlacement();
}

#endif

void __fastcall TDtaSource::SetMarker(int marker)
{
TRoadObject **FList=(TRoadObject**)FObjects->List;
int n=FObjects->Count;
for (int i=0;i<n;i++)
    FList[i]->Tag=marker;
}

void __fastcall TDtaSource::DeleteMarkedObjects(int marker,int command)
{
TRoadObject **FList=(TRoadObject**)FObjects->List;
for (int i=FObjects->Count-1;i>=0;i--)
    if (FList[i]->Tag==marker)
        {
        MainForm->SendBroadCastMessage(command,(int)FList[i],(int)this);
        DeleteObject(i);
        }
}

void __fastcall TDtaSource::DeleteMarkedObjects(int marker)
{
TRoadObject **FList=(TRoadObject**)FObjects->List;
for (int i=FObjects->Count-1;i>=0;i--)
    if (FList[i]->Tag==marker)
        DeleteObject(i);
}

void __fastcall TDtaSource::DeleteObject(TRoadObject* robj)
{
SetMarker(0);
robj->MarkTagByTree(1);
DeleteMarkedObjects(1,CM_REMOVEOBJ);
}

void __fastcall TDtaSource::DeleteChildObjects(TRoadObject *robj)
{
SetMarker(0);
robj->MarkTagByTree(1);
robj->Tag=0;
DeleteMarkedObjects(1,CM_REMOVEOBJ);
}

void __fastcall TDtaSource::AddRoadObject(TRoadObject *obj)
{
int n=FObjects->Count;
FObjects->Add(NULL);
TRoadObject **FList=(TRoadObject**)FObjects->List;
int i;
for (i=n-1;i>=0;i--)
  {
  TRoadObject *ob=(TRoadObject*)FList[i];
  if (ob)
    if (ob->L<obj->L)
      break;
  FList[i+1]=FList[i];
  }
FList[i+1]=obj;
}

void __fastcall TDtaSource::MoveSelectedObjects(int len,TRoad *RefRoad) {
   int n=FObjects->Count;
   TRoadObject **FList=(TRoadObject**)FObjects->List;
   for (int i=0;i<n;i++) {
      TRoadObject *ob=dynamic_cast<TRoadObject*>(FList[i]);
      if (ob && ob->Selected) {
         ob->Selected=false;
         ob->L+=len*100;
         TContRoadObject *cob=dynamic_cast<TContRoadObject*>(ob);
         if (cob)
            cob->SetLMax(cob->LMax+len*100);
         if (ob->Poly) {
            ob->Poly->Move(len*100);
            ob->PostEditPoly();
         }
      }
   }
   SortByPlacement();
   CalcMetrics(RefRoad);
}

void __fastcall TDtaSource::MoveAllObjects(int len,TRoad *RefRoad) {
   int n=FObjects->Count;
   TRoadObject **FList=(TRoadObject**)FObjects->List;
   for (int i=0;i<n;i++) {
      TRoadObject *ob=dynamic_cast<TRoadObject*>(FList[i]);
      if (ob) {
         ob->L+=len*100;
         TContRoadObject *cob=dynamic_cast<TContRoadObject*>(ob);
         if (cob)
            cob->SetLMax(cob->LMax+len*100);
         if (ob->Poly) {
            ob->Poly->Move(len*100);
            ob->PostEditPoly();
         }
      }
   }
   SortByPlacement();
   CalcMetrics(RefRoad);
}

void __fastcall TDtaSource::MoveVideo(int len) {
   VideoMoved=true;
   for (int i=0;i<FDirVideoTime->Count;i++)
      FDirVideoTime->Items[i]->Move(len);
   for (int i=0;i<FUnDirVideoTime->Count;i++)
      FUnDirVideoTime->Items[i]->Move(len);
}

TPolyline* __fastcall TDtaSource::FindPolyline(__int32 id)
{
TPolyline *Res=NULL;
int hpos=0;
int epos=PolyList->Count-1;
if (epos>=0)
    {
    while (hpos<epos)
        {
        int mid=(hpos+epos)>>1;
        int k=PolyList->Items[mid]->Id;
        if (k<id)
            hpos=mid+1;
        else
            epos=mid;
        }
    if (PolyList->Items[hpos]->Id==id)
        Res=PolyList->Items[hpos];
    }
return Res;
}

int __fastcall TDtaSource::GetDocumentsCount(__int32 AId,__int32 ADictId)
{
int n=FDocList->Count;
int c=0;
for (int i=0;i<n;i++)
    {
    TDocument *Doc=FDocList->Items[i];
    if ((Doc->ObjId==AId)&&(Doc->DictId==ADictId))
        c++;
    }
return c;
}

void __fastcall TDtaSource::GetDocuments(TStrings* lst,__int32 AId,__int32 ADictId)
{
int n=FDocList->Count;
for (int i=0;i<n;i++)
    {
    TDocument *Doc=FDocList->Items[i];
    if ((Doc->ObjId==AId)&&(Doc->DictId==ADictId))
        lst->AddObject(Doc->Name,Doc);
    }
}

__fastcall TResManager::TResManager(void)
{
DataList=new TObjList<TDtaSource>;
DictList=new TObjList<TDictSource>;
ListList=new TObjList<TListFrm>;
FCopyDestination=NULL;
}

__fastcall TResManager::~TResManager(void)
{
for (int i=0;i<DataList->Count;i++)
    {
    delete DataList->Items[i];
    DataList->Items[i]=NULL;
    }
delete DataList;
for (int i=0;i<ListList->Count;i++)
    {
    if (ListList->Items[i]) {
       ListList->Items[i]->Release();
       ListList->Items[i]=NULL;
       }
    }
delete ListList;
for (int i=0;i<DictList->Count;i++)
    {
    delete DictList->Items[i];
    DictList->Items[i]=NULL;
    }
delete DictList;
}

TDictSource* __fastcall TResManager::GetDict(__int32 n)
{
for (int i=0;i<DictList->Count;i++)
    if (DictList->Items[i]->DictId==n)
        return DictList->Items[i];
return NULL;
}

TDtaSource* __fastcall TResManager::GetSource(__int32 n,__int32 dataclass)
{
for (int i=0;i<DataList->Count;i++)
    {
    TDtaSource *d=DataList->Items[i];
    if ((d->Id==n)&&(d->DataClass==dataclass))
        return DataList->Items[i];
    }
return NULL;
}

TDtaSource* __fastcall TResManager::GetData(int Index)
{
TDtaSource *Res=NULL;
if (Index<DataList->Count)
    Res=DataList->Items[Index];
return Res;
}

TListFrm* __fastcall TResManager::GetListFrm(__int32 dataclass)
{
for (int i=0;i<DataList->Count;i++)
    {
    TDtaSource *d=DataList->Items[i];
    if (d->DataClass==dataclass)
        return ListList->Items[i];
    }
return NULL;
}

void __fastcall TResManager::BuildMenuList(void)
{
#ifndef GDIEDIT
TMenuItem *It=MainForm->N56;
It->Clear();
for (int i=0;i<DataList->Count;i++)
    {
    TDtaSource *Dta=DataList->Items[i];
    TMenuItem *NIt=new TMenuItem(It);
    NIt->Caption=Dta->RoadName+" : "+Dta->SourceName;
    NIt->Tag=Dta->DataClass;
    NIt->OnClick=MainForm->ListObjectClick;
    It->Add(NIt);
    }
#endif
}

TDtaSource* __fastcall TResManager::AddDataSource(String FormCaption,__int32 id,__int32 dataclass,__int32 DictId,TADOConnection *con,TRoadObjFactory *factory)
{
TDtaSource *newdta=GetSource(id,dataclass);
if (newdta==NULL)
    {
    TDictSource *dict=GetDict(DictId);
    newdta=new TDBDataSource(id,dataclass,dict,con,factory);
    DataList->Add(newdta);
    TListFrm *ListFrm;
    Application->CreateForm(__classid(TListFrm), &ListFrm);
    ListFrm->Caption=FormCaption;
    if (dict)
        ListFrm->BuildClassesTree(newdta,dict);
    ListList->Add(ListFrm);
    MainForm->SendBroadCastMessage(CM_OPENDATASOURCE,0,(int)newdta);
    }
newdta->IncRefCount();
BuildMenuList();
return newdta;
}

TDtaSource* __fastcall TResManager::AddFileDataSource(String filename,__int32 DictId,TRoadObjFactory *factory)
{
TDtaSource *newdta=NULL;//GetSource(id,dataclass);
if (newdta==NULL)
    {
    TDictSource *dict=GetDict(DictId);
    newdta=new TFileDataSource(filename,dict,factory);
    DataList->Add(newdta);
    TListFrm *ListFrm;
    Application->CreateForm(__classid(TListFrm), &ListFrm);
    if (dict)
        ListFrm->BuildClassesTree(newdta,dict);
    ListList->Add(ListFrm);
    MainForm->SendBroadCastMessage(CM_OPENDATASOURCE,0,(int)newdta);
    }
newdta->IncRefCount();
BuildMenuList();
return newdta;
}

TDictSource* __fastcall TResManager::AddFileDictSource(__int32 id)
{
for (int i=0;i<DictList->Count;i++)
    if (DictList->Items[i]->DictId==id)
        {
        DictList->Items[i]->IncRefCount();
        return DictList->Items[i];
        }
TDictSource *newdta=new TFileDictSource(id);
newdta->IncRefCount();
DictList->Add(newdta);
return newdta;
}

void __fastcall TResManager::UseDictSource(TDictSource *dict)
{
dict->IncRefCount();
}

TDictSource* __fastcall TResManager::AddDictSource(__int32 id,TADOConnection *con)
{
for (int i=0;i<DictList->Count;i++)
    if (DictList->Items[i]->DictId==id)
        {
        DictList->Items[i]->IncRefCount();
        return DictList->Items[i];
        }
TDictSource *newdta=new TDBDictSource(id,con);
newdta->IncRefCount();
DictList->Add(newdta);
return newdta;
}

// Процедура на случай удаления окна источника данных до удаления источника данных
void __fastcall TResManager::OnReleaseListForm(TDtaSource *Dta)
{
for (int i=0;i<DataList->Count;i++)
    {
    if (Dta==DataList->Items[i])
        ListList->Items[i]=NULL;
    }
}

void __fastcall TResManager::ReleaseDataSourceByIndex(int index)
{
TDtaSource *d=DataList->Items[index];
d->DecRefCount();
if (!d->RefCount)
  {
  if (d->TestNeedSave())
    {
    if (Application->MessageBox(String("Данные в источнике "+d->SourceName+" не сохранены. Сохранить?").c_str(),"Предупреждение",MB_YESNO)==ID_YES)
        {
        if (DictList->Count)
            {
            d->Apply(DictList->Items[0]);
            }
        }
    }
  MainForm->SendBroadCastMessage(CM_CLOSEDATASOURCE,0,(int)d);
  delete d;
  DataList->Delete(index);
  TListFrm *l=ListList->Items[index];
  if (l)
      l->Release();
  ListList->Delete(index);
  BuildMenuList();
  }
}

void __fastcall TResManager::ReleaseDataSource(TDtaSource* Dta)
{
int i;
TDtaSource *d;
for (i=0;i<DataList->Count;i++)
    if (DataList->Items[i]==Dta)
        break;
if (i<DataList->Count)
  ReleaseDataSourceByIndex(i);
}

void __fastcall TResManager::ReleaseDataSource(__int32 id,__int32 dataclass)
{
int i;
TDtaSource *d;
for (i=0;i<DataList->Count;i++)
    {
    d=DataList->Items[i];
    if ((d->Id==id)&&(d->DataClass==dataclass))
        break;
    }
if (i<DataList->Count)
  ReleaseDataSourceByIndex(i);
}

void __fastcall TResManager::ReleaseDictSource(__int32 id)
{
int i;
for (i=0;i<DictList->Count;i++)
    if (DictList->Items[i]->DictId==id)
        break;
if (i<DictList->Count)
    {
    TDictSource *d=DictList->Items[i];
    d->DecRefCount();
    if (!d->RefCount)
        {
        delete d;
        DictList->Delete(i);
        }
    }
}

void __fastcall TResManager::SetCopyDestination(TDtaSource *dta)
{
FCopyDestination=dta;
MainForm->SendBroadCastMessage(CM_CHANGECOPYDEST,0,(int)dta);
}

