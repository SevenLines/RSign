//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FileSour.h"
#include <fstream.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TFileSharedObjSource::TFileSharedObjSource(void) : TSharedObjSource()
{}

void __fastcall TFileSharedObjSource::Load(void)
{
char c[1024];
ifstream in("0.dcs");
if (in.is_open())
    {
    int n,max;
    in>>n>>max; // Максимальный Ид объекта
    in.getline(c,1024);
    GorzGDIObjects->Count=max+1;
    VertGDIObjects->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id,t,cl,w,s;
        in >> id >> t;
        if (t==1)
          {
          in>>cl>>w>>s;
          LOGBRUSH lb;
          lb.lbStyle=BS_SOLID;
          lb.lbColor=cl;
          lb.lbHatch=0;
          GorzGDIObjects->Items[id]=ExtCreatePen(PS_GEOMETRIC|s,w,&lb,0,NULL);
          VertGDIObjects->Items[id]=ExtCreatePen(PS_GEOMETRIC|s,w,&lb,0,NULL);
          }
        else if (t==2)
          {
          in>>cl>>s;
          if (s)
            {
            GorzGDIObjects->Items[id]=CreateHatchBrush(s-1,cl);
            s--;
            if (s==HS_HORIZONTAL)
                s=HS_VERTICAL;
            else if (s==HS_VERTICAL)
                s=HS_HORIZONTAL;
            VertGDIObjects->Items[id]=CreateHatchBrush(s,cl);
            }
          else
            {
            GorzGDIObjects->Items[id]=CreateSolidBrush(cl);
            VertGDIObjects->Items[id]=CreateSolidBrush(cl);
            }

          }
        in.getline(c,1024);
        }
    in>>n>>max; // Максимальный ИД метафайла
    in.getline(c,1024);
    Metas->SetCount((max+1)*4);
    for (int i=0;i<n;i++)
        {
        int id;
        in>>id;
        in.getline(c,1024);
        Metas->Strings[id]=String(c);
        }
    }
}

__fastcall TFileDictSource::TFileDictSource(void) : TDictSource()
{}

__fastcall TFileDictSource::TFileDictSource(__int32 Id) : TDictSource()
{Load(Id);}

void __fastcall TFileDictSource::Load(__int32 id_)
{
int n,max;
char c[4096];
char d[4096];
FDictId=id_;
ifstream in(String(String(id_)+".dct").c_str());
if (in.is_open())
    {
    TStringList *lst=new TStringList;
    in>>n>>max; // Максимальный Id типа объекта
    in.getline(c,1024);
    ObjClasses->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id;
        in.getline(c,4096);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        ObjClasses->Items[id]=new TObjMetaClass();
        ObjClasses->Items[id]->LoadDump(lst);
        }
    in>>n>>max; // Максимальный Id типа класса
    in.getline(c,1024);
    PropClasses->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id;
        in.getline(c,1024);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        PropClasses->Items[id]=new TPropClassesRec();
        PropClasses->Items[id]->LoadDump(lst);
        }
    in>>n; // Максимальный Id текстового свойства
    in.getline(c,1024);
    TextProps->Count=n;
    for (int i=0;i<n;i++)
        {
        in.getline(c,1024);
        lst->CommaText=c;
        TextProps->Items[i]=new TTextPropRec();
        TextProps->Items[i]->LoadDump(lst);
        }
    in>>n>>max; // Максимальный Id процедуры
    in.getline(c,1024);
    DrwProcs->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id;
        in.getline(c,1024);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        DrwProcs->Items[id]=new TDrwProcRec();
        DrwProcs->Items[id]->LoadDump(lst);
        }
    // Чтение параметров надо дополнять
    in>>n>>max; // Максимальный Id параметров
    in.getline(c,1024);
    DrwParams->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id,pid;
        in.getline(c,1024);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        pid=lst->Values["ProcId"].ToInt();
        switch (pid)
                {
                case 1:DrwParams->Items[id]=new TDrwParamRec1;break;
                case 2:DrwParams->Items[id]=new TDrwParamRec2;break;
                case 3:DrwParams->Items[id]=new TDrwParamRec3;break;
                case 4:DrwParams->Items[id]=new TDrwParamRec4;break;
                case 5:DrwParams->Items[id]=new TDrwParamRec5;break;
                case 6:DrwParams->Items[id]=new TDrwParamRec6;break;
                case 7:DrwParams->Items[id]=new TDrwParamRec7;break;
                case 8:DrwParams->Items[id]=new TDrwParamRec8;break;                
                }
        DrwParams->Items[id]->LoadDump(lst);
        }
    in>>n>>max; // Количество страниц
    in.getline(c,1024);
    DrwPages->Count=n;
    for (int i=0;i<n;i++)
        {
        int id;
        in.getline(c,1024);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        DrwPages->Items[id]=new TDrwPageRec();
        DrwPages->Items[id]->LoadDump(lst);
        }
    in>>n>>max; // Максимальный Id типов отображения
    in.getline(c,1024);
    DrwClasses->Count=max+1;
    for (int i=0;i<n;i++)
        {
        int id;
        in.getline(c,1024);
        lst->CommaText=c;
        id=lst->Values["Id"].ToInt();
        DrwClasses->Items[id]=new TDrwClassesRec();
        DrwClasses->Items[id]->LoadDump(lst);
        }
    delete lst;
    }
}


__fastcall TFileDataSource::TFileDataSource(void) : TDtaSource()
{}

__fastcall TFileDataSource::TFileDataSource(String filename,TDictSource *Dict,TRoadObjFactory *factory) : TDtaSource()
{
FFactory=factory;
FFileName=filename;
Load(0,0,Dict);
}

#ifndef GDIEDIT

void __fastcall TFileDataSource::Load(__int32 id_,__int32 dataclass_,TDictSource *Dict)
{
int npt;
char c[4096];
__int32 MinL,MaxL,MinX,MaxX;

FId=id_;
FDataClass=dataclass_;
ifstream in(FFileName.c_str());
if (in.is_open())
    {
    in.getline(c,4096);
    FRoadName=c;
    in.getline(c,4096);
    FSourceName=c;
    in>>FId;
    in>>FDataType;
    in>>FDataClass;
    FReadOnly=((FDataType!=0)&&(FDataType!=3));
    FNotExist=FDataType==3;
    in.getline(c,4096);
    in>>MinL;
    in>>MaxL;
    in>>MinX;
    in>>MaxX;
    in.getline(c,4096);
    SetRoadBound(MinL,MaxL,MinX,MaxX);
/*    Road->RightLine.LoadDump(in);
    Road->LeftLine.LoadDump(in);
    Road->RightSide.LoadDump(in);
    Road->LeftSide.LoadDump(in);
    MaxX=0;
    for (int i=0;i<Road->RightLine.Count;i++)
        if (Road->RightLine.Points[i].X>MaxX)
            MaxX=Road->RightLine.Points[i].X;
    MinX=0;
    for (int i=0;i<Road->LeftLine.Count;i++)
        if (Road->LeftLine.Points[i].X<MinX)
            MinX=Road->LeftLine.Points[i].X;

    if (Road->RightLine.Points[0].L<Road->LeftLine.Points[0].L)
        MinL=Road->RightLine.Points[0].L;
    else
        MinL=Road->LeftLine.Points[0].L;
    if (Road->RightLine.Points[Road->RightLine.Count-1].L<Road->LeftLine.Points[Road->LeftLine.Count-1].L)
        MaxL=Road->LeftLine.Points[Road->LeftLine.Count-1].L;
    else
        MaxL=Road->RightLine.Points[Road->RightLine.Count-1].L;
    SetRoadBound(MinL,MaxL,MinX*5,MaxX*5);
*/
    in>>npt;
    in.getline(c,4096);
    for (int i=0;i<npt;i++)
        {
        TPolyline *Poly=new TPolyline;
        Poly->LoadDump(in);
        //FPolyList->Add(Poly);
        }
    FRoad->Geometry.LoadDump(in);
    FRoad->CalcMinMaxZ();    
    in>>npt;
    in.getline(c,4096);
    TStringList *slst=new TStringList;
    for (int i=0;i<npt;i++)
        {
        in.getline(c,4096);
        slst->CommaText=c;
        __int32 id=slst->Values["Id"].ToInt();
        __int32 code=slst->Values["Code"].ToInt();
        __int32 poly=slst->Values["Poly"].ToInt();
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[code]);
        TRoadObject *obj=FFactory->CreateRoadObj(Meta->ClassName,id,code);
        obj->LoadDump(slst,Dict);
        //if (poly)
        //    obj->Poly=FindPolyline(poly);
        obj->DrwClassId=Dict->SelectDrwParam(obj,1);
        FObjects->Add(obj);
        obj->PostLoadObject();
        slst->Clear();
        }
    SortByPlacement();
    BuildRoadMetrics();
    FReady=true;
    }
}

#endif
