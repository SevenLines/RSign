//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DBDataSource.h"
#include "MainUnit.h"
#include "SettingFrm.h"
#include "stdio.h"
#include "DBQuery.h"
#include "time.h"
#include "ProgressFrm.h"
#include <vector.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)


#define K_ 100

TDBDataModule *DBDataModule;

__fastcall TDBSharedObjSource::TDBSharedObjSource(void) : TSharedObjSource()
        {FConnection=NULL;}
__fastcall TDBSharedObjSource::TDBSharedObjSource(TADOConnection *con) : TSharedObjSource()
        {FConnection=con;
         Load();
        }
void __fastcall TDBSharedObjSource::Load(void)
{
if (!Connection)
    return;

   String AppPath=ExtractFileDir(Application->ExeName)+"\\";

   TADODataSet* GDI=new TADODataSet(NULL);
   GDI->Connection=Connection;
   int max;
   GDI->CommandText="select count(*) as m from GDI_Pen";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   GDI->CommandText="select count(*) as m from GDI_Brush";
   GDI->Open();
   max=max+GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   FGorzGDIObjects->Count=max+1;
   FVertGDIObjects->Count=max+1;
   GDI->CommandText="select * from GDI_Pen";
   GDI->Open();
   int id,cl,w,s;
   while(!GDI->Eof)
   {
      cl=GDI->FieldByName("PenColor")->AsInteger;
      w=GDI->FieldByName("PenWidth")->AsInteger;
      s=GDI->FieldByName("PenStyle")->AsInteger;
      id=GDI->FieldByName("id_")->AsInteger;
      LOGBRUSH lb;
      lb.lbStyle=BS_SOLID;
      lb.lbColor=cl;
      lb.lbHatch=0;
      FGorzGDIObjects->Items[id]=ExtCreatePen(PS_GEOMETRIC|s,w,&lb,0,NULL);
      FVertGDIObjects->Items[id]=ExtCreatePen(PS_GEOMETRIC|s,w,&lb,0,NULL);
      GDI->Next();
   }
   GDI->Active=false;

   GDI->CommandText="select *  from GDI_Brush";
   GDI->Open();
   while(!GDI->Eof)
   {
      cl=GDI->FieldByName("Brush")->AsInteger;
      s=GDI->FieldByName("Hatch")->AsInteger;
      id=GDI->FieldByName("id_")->AsInteger;
      String Name=GDI->FieldByName("Pattern")->AsString;
      if (Name!="")
        {
        void* bmp=LoadBitmap(Application->Handle,String(AppPath+Name).c_str());
        FGorzGDIObjects->Items[id]=CreatePatternBrush(bmp);
        // Сдесь надо написать разворот bmp на 90 *
        FVertGDIObjects->Items[id]=CreatePatternBrush(bmp);
        DeleteObject(bmp);
        }
      else if (s)
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
        FGorzGDIObjects->Items[id]=CreateSolidBrush(cl);
        FVertGDIObjects->Items[id]=CreateSolidBrush(cl);
        }
      GDI->Next();
   }
   GDI->Active=false;

   //MetaFile
   GDI->CommandText="select count(*) as m from GDI_MetaFile";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   Metas->SetCount((max+1)*4);
   GDI->CommandText="select * from GDI_MetaFile";
   GDI->Open();
   String c;
   while(!GDI->Eof)
   {
      id=GDI->FieldByName("id_")->AsInteger;
      c=GDI->FieldByName("Path")->AsString.Trim();
      Metas->Strings[id<<2]=String(c);
      GDI->Next();
   }
   GDI->Active=false;
   delete GDI;
}

void __fastcall TDBSharedObjSource::Save(void)
{
if (!FConnection)
    return;
TADOCommand* command=new TADOCommand(NULL);
command->Connection=Connection;
command->CommandText = "delete from GDI_Pen";
command->Execute();
for (int i=0;i<FGorzGDIObjects->Count;i++)
    {
    if (FGorzGDIObjects->Items[i])
        {
        if (GetObjectType((void*)(FGorzGDIObjects->Items[i]))==OBJ_EXTPEN)
            {
            EXTLOGPEN Pen;
            GetObject((void*)(FGorzGDIObjects->Items[i]),sizeof(EXTLOGPEN),&Pen);
            String Sql;
            Sql.sprintf("insert into GDI_Pen (PenColor,PenWidth,PenStyle,id_) values (%d,%d,%d,%d)",Pen.elpColor,Pen.elpWidth,Pen.elpPenStyle,i);
            command->CommandText=Sql;
            command->Execute();
            }
        }
    }
command->CommandText = "delete from GDI_Brush";
command->Execute();
for (int i=0;i<FGorzGDIObjects->Count;i++)
    {
    if (FGorzGDIObjects->Items[i])
        {
        if (GetObjectType((void*)(FGorzGDIObjects->Items[i]))==OBJ_BRUSH)
            {
            LOGBRUSH Brush;
            GetObject((void*)(FGorzGDIObjects->Items[i]),sizeof(LOGBRUSH),&Brush);
            String Sql;
            int h=Brush.lbHatch;
            if (Brush.lbStyle==BS_HATCHED)
                h++;
            Sql.sprintf("insert into GDI_Brush (id_,Brush,Hatch) values (%ld,%ld,%ld)",i,Brush.lbColor,h);
            command->CommandText=Sql;
            command->Execute();
            }
        }
    }
command->CommandText = "delete from GDI_MetaFile";
command->Execute();
for (int i=0;i<Metas->Count;i+=4)
    if (Metas->Strings[i]!="")
        {
        String Sql;
        Sql.sprintf("insert into GDI_MetaFile (id_,Path) values (%ld,'%s')",i>>2,Metas->Strings[i].c_str());
        command->CommandText=Sql;
        command->Execute();
        }
delete command;
}

__fastcall TDBDictSource::TDBDictSource(void) : TDictSource()
{FConnection=NULL;}

__fastcall TDBDictSource::TDBDictSource(__int32 Id,TADOConnection *con) : TDictSource()
{
FConnection=con;
Load(Id);
}

int __fastcall DivByDots(String s)
{
char *c=s.c_str();
int v1[3];
int *v2=v1;
v1[0]=v1[1]=v1[2]=0;
while (*c)
    {
    if ((*c)=='.')
        v2++;
    else
        *v2=*v2*10+*c-'0';
    c++;
    }
return v1[0]*10000+v1[1]*100+v1[2];
}

/*
int __fastcall PropCompare(void* Item1, void* Item2)
{
TTextPropRec *Rec1=(TTextPropRec*)Item1;
TTextPropRec *Rec2=(TTextPropRec*)Item2;
if (!Rec1)
    return -1;
else if (!Rec2)
    return 1;
else if (Rec1->PropId<Rec2->PropId)
    return -1;
else if (Rec1->PropId>Rec2->PropId)
    return 1;
else if ((Rec1->PropId<=SIGNGOSTCODE+7)&&(Rec1->PropId>=SIGNGOSTCODE))
    {
    if (Rec1->Tag<Rec2->Tag)
        return -1;
    else if (Rec1->Tag>Rec2->Tag)
        return 1;
    else
        return 0;
    }
else
    return 0;
}
*/

void __fastcall TDBDictSource::Load(__int32 Id)
{
if (!Connection)
    return;

   TADODataSet* GDI=new TADODataSet(NULL);
   GDI->Connection=Connection;
   int max;
   //ObjType
   GDI->CommandText="select max(id_) as m from ListRoadObjects";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   ObjClasses->Count=max+1;
   GDI->CommandText="select Ro.FullTitle,Ro.Parent,Ro.OneTitle,Ot.* from ListRoadObjects Ro join GDI_ObjType Ot on Ro.id_=Ot.NumObj order by Ro.id_";
   GDI->Open();

   TStringList *lstprop=new TStringList;
   TStringList *lstflag=new TStringList;

   while(!GDI->Eof)
   {
     int id=GDI->FieldByName("NumObj")->AsInteger;
     int parent=GDI->FieldByName("Parent")->AsInteger;
     String title=GDI->FieldByName("FullTitle")->AsString.Trim();
     String otit=GDI->FieldByName("OneTitle")->AsString.Trim();
     String tablename=GDI->FieldByName("TableName")->AsString.Trim();
     int flags=GDI->FieldByName("Flags")->AsInteger;
     String classname=GDI->FieldByName("ClassName")->AsString.Trim();
     String proplist=GDI->FieldByName("PropList")->AsString.Trim();
     String propflag=GDI->FieldByName("PropFlag")->AsString.Trim();
     int mainprop=GDI->FieldByName("MainProp")->AsInteger;
     String sqlload=GDI->FieldByName("SqlLoad")->AsString.Trim();
     String sqlsave=GDI->FieldByName("SqlSave")->AsString.Trim();
     String sqlappend=GDI->FieldByName("SqlAppend")->AsString.Trim();
     String sqldelete=GDI->FieldByName("SqlDelete")->AsString.Trim();

     TObjMetaClass *meta=new TObjMetaClass(id,parent,title,otit);
     meta->SetParams(tablename,flags,classname);
     meta->SetSQL(sqlload,sqlsave,sqlappend,sqldelete);
     lstprop->CommaText=proplist;
     lstflag->CommaText=propflag;
     meta->LoadDumpProp(lstprop,lstflag);
     meta->SetMainProp(mainprop);
     lstprop->Clear();
     lstflag->Clear();
     ObjClasses->Items[id]=meta;
     GDI->Next();
   }
   delete lstprop;
   delete lstflag;

   GDI->Active=false;

   //GDIPropName
   GDI->CommandText="select max(id_) as m from GDI_PropName";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   PropClasses->Count=max+1;
   GDI->CommandText="select * from GDI_PropName";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("id_")->AsInteger;
      String title=GDI->FieldByName("FullTitle")->AsString.Trim();
      String stitle=GDI->FieldByName("ShortTitle")->AsString.Trim();
      String classname=GDI->FieldByName("ClassName")->AsString.Trim();
      String field=GDI->FieldByName("FieldName")->AsString.Trim();
      int type=GDI->FieldByName("Type")->AsInteger;

      TPropClassesRec *prop=new TPropClassesRec(id);
      prop->SetValue(title,stitle,classname,field,TPropClassesType(type));
      PropClasses->Items[id]=prop;
      GDI->Next();
   }
   GDI->Active=false;
//  Классификатор
   GDI->CommandText="select V.NumVal,V.NumPropName,C.FullTitle as FTitl,C.ShortTitle from GDI_PropValues V,Classifier C where (V.NumVal & 251658240)=0 and (V.NumVal & 16777215)=C.id_ order by V.NumPropName,V.id_";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("NumVal")->AsInteger;
      int pid=GDI->FieldByName("NumPropName")->AsInteger;
      String title=GDI->FieldByName("FTitl")->AsString.Trim();
      String stitle=GDI->FieldByName("ShortTitle")->AsString.Trim();
      TTextPropRec *Rec=new TTextPropRec(id,pid,title,stitle);
      if ((Rec->PropId<=SIGNGOSTCODE+7)&&(Rec->PropId>=SIGNGOSTCODE))
        Rec->Tag=DivByDots(stitle);

      TextProps->Add(Rec);
      GDI->Next();
   }
   GDI->Active=false;
// Справочник материалов
   GDI->CommandText="select V.NumVal,V.NumPropName,C.FullTitle as FTitl,C.ShortTitle from GDI_PropValues V,ListMaterials C where (V.NumVal & 251658240)=16777216 and (V.NumVal & 16777215)=C.id_ order by V.NumPropName,V.id_";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("NumVal")->AsInteger;
      int pid=GDI->FieldByName("NumPropName")->AsInteger;
      String title=GDI->FieldByName("FTitl")->AsString.Trim();
      String stitle=GDI->FieldByName("ShortTitle")->AsString.Trim();
      TTextPropRec *Rec=new TTextPropRec(id,pid,title,stitle);
      if ((Rec->PropId<=SIGNGOSTCODE+7)&&(Rec->PropId>=SIGNGOSTCODE))
        Rec->Tag=DivByDots(stitle);

      TextProps->Add(Rec);
      GDI->Next();
   }
   GDI->Active=false;
// Справочник дефектов
   GDI->CommandText="select V.NumVal,V.NumPropName,C.FullTitle as FTitl,C.FullTitle as ShortTitle from GDI_PropValues V,av_ListDefects C where (V.NumVal & 251658240)=33554432 and (V.NumVal & 16777215)=C.id_ order by V.NumPropName,V.id_";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("NumVal")->AsInteger;
      int pid=GDI->FieldByName("NumPropName")->AsInteger;
      String title=GDI->FieldByName("FTitl")->AsString.Trim();
      String stitle=GDI->FieldByName("ShortTitle")->AsString.Trim();
      TTextPropRec *Rec=new TTextPropRec(id,pid,title,stitle);
      if ((Rec->PropId<=SIGNGOSTCODE+7)&&(Rec->PropId>=SIGNGOSTCODE))
        Rec->Tag=DivByDots(stitle);

      TextProps->Add(Rec);
      GDI->Next();
   }
   GDI->Active=false;

//   TextProps->Sort(PropCompare);

   //GDIProc
   GDI->CommandText="select max(id_) as m from GDI_Proc";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   DrwProcs->Count=max+1;
   GDI->CommandText="select * from GDI_Proc";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("id_")->AsInteger;
      String title=GDI->FieldByName("FullTitle")->AsString.Trim();
      DrwProcs->Items[id]=new TDrwProcRec(id,title);
      GDI->Next();
   }
   GDI->Active=false;

   //GDIParams
   GDI->CommandText="select max(id_) as m from GDI_Params";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   DrwParams->Count=max+1;
   GDI->CommandText="select * from GDI_Params";
   TStringList *lst=new TStringList;
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("id_")->AsInteger;
      int pid=GDI->FieldByName("NumProc")->AsInteger;
      String param=GDI->FieldByName("ParamStr")->AsString.Trim();
      TDrwParamRec *Par;
       switch (pid)
           {
           case 1: Par=new TDrwParamRec1(id,pid); break;
           case 2: Par=new TDrwParamRec2(id,pid); break;
           case 3: Par=new TDrwParamRec3(id,pid); break;
           case 4: Par=new TDrwParamRec4(id,pid); break;
           case 5: Par=new TDrwParamRec5(id,pid); break;
           case 6: Par=new TDrwParamRec6(id,pid); break;
           case 7: Par=new TDrwParamRec7(id,pid); break;
           case 8: Par=new TDrwParamRec8(id,pid); break;
           }
       lst->CommaText=param;
       Par->LoadParDump(lst);
       lst->Clear();
       DrwParams->Items[id]=Par;

      GDI->Next();
   }
   delete lst;
   GDI->Active=false;
   //GDIPages
   GDI->CommandText="select * from GDI_Pages";
   GDI->Open();
   while(!GDI->Eof)
    {
    int id=GDI->FieldByName("id_")->AsInteger;
    String fname=GDI->FieldByName("FullName")->AsString.Trim();
    String sname=GDI->FieldByName("ShortName")->AsString.Trim();
    DrwPages->Add(new TDrwPageRec(id,fname,sname));
    GDI->Next();
    }
   GDI->Active=false;

   //GDIShow
   GDI->CommandText="select max(id_) as m from GDI_Show";
   GDI->Open();
   max=GDI->FieldByName("m")->AsInteger;
   GDI->Active=false;

   DrwClasses->Count=max+1;
   GDI->CommandText="select * from GDI_Show";
   GDI->Open();
   while(!GDI->Eof)
   {
      int id=GDI->FieldByName("id_")->AsInteger;
      int pid=GDI->FieldByName("NumPropValues")->AsInteger;
      int cid=GDI->FieldByName("NumObjType")->AsInteger;
      int pset=GDI->FieldByName("PagesSet")->AsInteger;
      int parid1=GDI->FieldByName("NumParam1")->AsInteger;
      int parid2=GDI->FieldByName("NumParam2")->AsInteger;
      int parid3=GDI->FieldByName("NumParam3")->AsInteger;
      int parid4=GDI->FieldByName("NumParam4")->AsInteger;
      int pri=GDI->FieldByName("Priority")->AsInteger;
      String cond=GDI->FieldByName("Condition")->IsNull ? String(""):GDI->FieldByName("Condition")->AsString;
      TDrwClassesRec *Drw=new TDrwClassesRec(id);
      Drw->SetClassId(cid,pid);
      Drw->SetDrwParam(parid1,parid2,parid3,parid4);
      Drw->SetPriority(pri);
      Drw->SetPagesSet(pset);
      Drw->Condition=cond;
      DrwClasses->Items[id]=Drw;
      GDI->Next();
   }
   GDI->Active=false;

   delete GDI;
}

void __fastcall SmartCopy(char *dest,char *sour)
{
while (*sour)
    if (*sour=='\'')
        *(dest++)='\'',*(dest++)='\'',sour++;
    else
        *(dest++)=*(sour++);
*dest=0;
}

void __fastcall TDBDictSource::Save(void)
{
if (!FConnection)
    return;
TStringList *plst=new TStringList;
TStringList *flst=new TStringList;
TADOCommand* command=new TADOCommand(NULL);
command->Connection=FConnection;
for (int i=0;i<ObjClasses->Count;i++)
    {
    TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(ObjClasses->Items[i]);
    if (Meta)
        {
        char sql1[2048];
        char sql2[2048];
        char sql3[2048];
        char sql4[2048];
        SmartCopy(sql1,Meta->Sql.c_str());
        SmartCopy(sql2,Meta->SqlSave.c_str());
        SmartCopy(sql3,Meta->SqlAppend.c_str());
        SmartCopy(sql4,Meta->SqlDelete.c_str());
        Meta->DumpProp(plst,flst);
        String Sql;
        Sql.sprintf("update GDI_ObjType set Flags='%ld',ClassName='%s',TableName='%s',PropList='%s',\
                    PropFlag='%s',MainProp=%ld,SqlLoad='%s',SqlSave='%s',SqlAppend='%s',SqlDelete='%s'\
                    where NumObj=%ld",Meta->Flags,Meta->ClassName.c_str(),
                    Meta->TableName.c_str(),plst->CommaText.c_str(),flst->CommaText.c_str(),
                    Meta->MainPropId,sql1,sql2,sql3,sql4,Meta->Id);
        command->CommandText = Sql;
        command->Execute();
        plst->Clear();
        flst->Clear();
        }
    }
delete plst;
delete flst;

command->CommandText = "delete from GDI_PropName";
command->Execute();
for (int i=0;i<PropClasses->Count;i++)
    {
    TPropClassesRec *Prop=PropClasses->Items[i];
    if (Prop)
        {
        String Sql;
        Sql.sprintf("insert into GDI_PropName\
              (id_,FullTitle,ShortTitle,ClassName,FieldName,Type)\
            values  (%ld,'%s','%s','%s','%s',%ld)",Prop->Id , Prop->PropName.c_str(),Prop->ShortName.c_str(),
              Prop->ClassName.c_str(),Prop->FieldName.c_str(),int(Prop->Type));
        command->CommandText=Sql;
        command->Execute();
        }
    }

command->CommandText = "delete from GDI_PropValues";
command->Execute();
for (int i=0;i<TextProps->Count;i++)
    {
    TTextPropRec *Text=TextProps->Items[i];
    if (Text)
        {
        String Sql;
        Sql.sprintf("insert into GDI_PropValues (id_,NumPropName,NumVal) values (%ld,%ld,%ld)",i,Text->PropId,Text->Id);
        command->CommandText=Sql;
        command->Execute();
        }
    }
command->CommandText = "delete from GDI_Params";
command->Execute();
TStringList *lst=new TStringList;
for (int i=0;i<DrwParams->Count;i++)
    {
    TDrwParamRec *Par=DrwParams->Items[i];
    if (Par)
        {
        Par->ParDump(lst);
        String Sql;
        Sql.sprintf("insert into GDI_Params (id_,NumProc,ParamStr) values (%ld,%ld,'%s')",Par->Id,Par->ProcId,lst->CommaText);
        lst->Clear();
        command->CommandText=Sql;
        command->Execute();
        }
    }                                        
delete lst;

command->CommandText = "delete from GDI_Show";
command->Execute();
for (int i=0;i<DrwClasses->Count;i++)
    {
    TDrwClassesRec *Drw=DrwClasses->Items[i];
    if (Drw)
        {
        String Sql;
        String Cond;
        if (Drw->Condition=="")
            Cond="NULL";
        else
            Cond=String("'")+Drw->Condition+String("'");
        Sql.sprintf("insert into GDI_Show\
           (id_,NumObjType,NumPropValues,PagesSet,Priority,NumParam1,NumParam2,NumParam3,NumParam4,Condition)\
           values (%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%s)", Drw->Id,Drw->ObjClassId,Drw->PropValueId,Drw->PagesSet,
           Drw->Priority,Drw->DrwParamId[0],Drw->DrwParamId[1],Drw->DrwParamId[2],Drw->DrwParamId[3],Cond.c_str());
        command->CommandText=Sql;
        command->Execute();
        }
    }

delete command;
}

__fastcall TDBDataSource::TDBDataSource(void) : ::TDtaSource()
{
FConnection=NULL;}

__fastcall TDBDataSource::TDBDataSource(__int32 id_,__int32 dataclass_,TDictSource *Dict,TADOConnection *con,TRoadObjFactory *factory) : ::TDtaSource()
{
FFactory=factory;
FConnection=con;
Load(id_,dataclass_,Dict);
}

int __inline AsInt(OleVariant R)
{
if (R.IsNull())
    return 0;
return R;
}

#ifndef GDIEDIT

void __fastcall TDBDataSource::Load(__int32 id_,__int32 dataclass_,TDictSource *Dict)
{
if (!FConnection)
    return;

   ProgressForm->Caption="Идет загрузка";
   ProgressForm->Show();

   __int32 MinL=0,MaxL=0,MaxW=500;

   FId=id_;
   FDataClass=dataclass_;
   FDataType=DBDataModule->GetSourceType(FDataClass);
   FRoadName=DBDataModule->GetRoadName(FId);
   FSourceName=DBDataModule->GetSourceName(FDataClass);
   FReadOnly=((FDataType!=0)&&(FDataType!=3));
   FNotExist=FDataType==3;   
   DBDataModule->GetRoadBound(FId,FDataClass,MinL,MaxL);

   TADODataSet* DB=new TADODataSet(NULL);
   DB->Connection=Connection;
// Читаем список документов

    ProgressForm->Note="Загружается список документов";
    DB->CommandTimeout=600;
    DB->CommandText=ReplaceNameVal(DocumentLoad,NULL,0);
    DB->Open();
    while (!DB->Eof)
        {
        __int32 docid=DB->FieldByName("DocId")->AsInteger;
        __int32 objid=DB->FieldByName("ObjId")->AsInteger;
        __int32 dictid=DB->FieldByName("DictId")->AsInteger;
/* Убрать когда DictId будут синхронизированы */
/*    switch (dictid)
        {
        case 261:dictid=ROADBRIDGE;break;   // мост
        case 555:dictid=ROADTUBE;break;   // труба
        }
*/
        String name=DB->FieldByName("Name")->AsString;
        String path=DB->FieldByName("Path")->AsString;
        String driver=DB->FieldByName("Driver")->AsString;
        TDocument *Doc=new TDocument(docid,objid,dictid,name,driver+path);
        FDocList->Add(Doc);
        DB->Next();
        }
    DB->Close();
// Читаем метрику

    ProgressForm->Note="Загружается метрическая информация";
/*
    DB->CommandText=ReplaceNameVal(ListMetricsLoad,NULL,0);
    DB->Open();
    while (!DB->Eof)
        {
        __int32 NumLine=DB->FieldByName("NumLine")->AsInteger;
        __int32 LCount=DB->FieldByName("LCount")->AsInteger;
        PolyList->Add(new TPolyline(LCount,NumLine));
        DB->Next();
        }
    DB->Close();
    if (PolyList->Count)
        {
        DB->CommandText=ReplaceNameVal(MetricsLoad,NULL,0);
        DB->Open();
        int i=0;
        int n=0;
        ProgressForm->SetMinMax(0,DB->RecordCount);
        TPolyline *Poly=PolyList->Items[i];
        while (!DB->Eof)
            {
            ProgressForm->Position=n;
            __int32 NumLine=DB->FieldByName("NumLine")->AsInteger;
            __int32 L=DB->FieldByName("L")->AsInteger;
            __int32 X=DB->FieldByName("X")->AsInteger;
            __int32 Code=DB->FieldByName("Code")->AsInteger;
            __int32 LeepPar=DB->FieldByName("LeepPar")->AsInteger;
            __int32 BasePar1=DB->FieldByName("BasePar1")->AsInteger;
            __int32 BasePar2=DB->FieldByName("BasePar2")->AsInteger;
            __int32 NumPoint=DB->FieldByName("NumPoint")->AsInteger;
            if (Poly->Id!=NumLine)
                while (i<PolyList->Count)
                    if ((Poly=PolyList->Items[i++])->Id==NumLine)
                        break;
            if (Poly->Id!=NumLine)
                break;
            if (NumPoint<Poly->Count)
                (*Poly)[NumPoint]=TRoadPoint(L,X,Code,LeepPar,BasePar1,BasePar2);
            DB->Next();
            n++;
            }
        DB->Close();
        }
*/
    for (int i=0;i<Dict->ObjClasses->Count;i++)
      if (Dict->ObjClasses->Items[i])
        {
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[i]);
        if (Meta)
            if (Meta->Sql!="")
                {
                 DB->CommandText=ReplaceNameVal(Meta->Sql,NULL,0);
                 DB->Open();
                 ProgressForm->SetMinMax(0,DB->RecordCount);
                 ProgressForm->Note="Загружаются "+Meta->Title;
                 int n=0;
                 while (!DB->Eof)
                    {
                    ProgressForm->Position=n;
                    __int32 id_=DB->FieldByName("id_")->AsInteger;
                    TRoadObject *Obj=Factory->CreateRoadObj(Meta->ClassName,id_,i);
                    try
                        {
                        for (int j=0;j<Meta->PropCount;j++)
                            {
                            TPropClassesRec *Prop=Dict->PropClasses->Items[Meta->PropIds[j]];
                            if (Prop)
                                {
                                String val;
                                if (Prop->Type==prBoolean)
                                    val=String((int)DB->FieldByName(Prop->FieldName)->AsBoolean);
                                else
                                    {
                                    val=Trim(DB->FieldByName(Prop->FieldName)->AsString);
                                    if ((val=="")&&(Prop->Type!=prString))
                                        val="0";
                                    }
                                Obj->PutProperty(Prop->ClassName,val);
                                }
                            }
                        TField *Fld_Count=DB->FindField("PointsCount");
                        TField *Fld_Points=DB->FindField("Points");
                        if (Fld_Count&&Fld_Points)
                            {
                            int n=Fld_Count->AsInteger;
                            TMemoryStream *Mem=new TMemoryStream;
                            dynamic_cast<TBlobField*>(Fld_Points)->SaveToStream(Mem);
                            Obj->Poly=new TPolyline(n);
                            Obj->Poly->LoadFromStream(Mem);
                            delete Mem;
                            }
/*
                        TField *LNum=DB->FindField("NumLine");
                        if (LNum)
                            {
                            __int32 NumLine=LNum->AsInteger;
                            if (NumLine)
                                Obj->Poly=FindPolyline(NumLine);
                            }
*/
                        Obj->PutProperty("PrevId",DB->FieldByName("Prev_Id")->AsInteger);
                        Obj->DrwClassId=Dict->SelectDrwParam(Obj,1);
                        Objects->Add(Obj);
                        if (Obj->L<MinL)
                            MinL=Obj->L;
                        TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(Obj);
                        if (cobj)
                            if (cobj->LMax>MaxL)
                                MaxL=cobj->LMax;
                        TBandRoadPart *bobj=dynamic_cast<TBandRoadPart*>(Obj);
                        if (bobj)
                            if (bobj->Width>MaxW)
                                MaxW=bobj->Width;
                        }
                    catch (...)
                        {
                        ShowMessage("Ошибка при выполнении запроса "+DB->CommandText+";\n Объект Id="+String(id_));
                        }
                    DB->Next();
                    Obj->PostLoadObject();
                    n++;
                    }
                 DB->Close();
                }
        }
// Читаем профиль
    ProgressForm->Note="Загружаются геометрические параметры";
    if (!LoadGeometryBlob() && !LoadGeometry())
            {
            CalcGeometry(MinL,MaxL);
            if (Road->Geometry.Count<2) {
               Road->Geometry.SetCount(2);
               Road->Geometry.L[0]=MinL;
               Road->Geometry.L[1]=MaxL;
               Road->Geometry.Values[0]=TGeometryVal(MinL,0,0,0,20,20,0,0);
               Road->Geometry.Values[1]=TGeometryVal(MaxL,0,0,0,20,20,0,0);
               }
            }
   else {
   // Убрать когда высота будет соответствовать наклону
      TGeometryVal *Geom=Road->Geometry.Values;
       __int32 *L=Road->Geometry.L;
      double Cur_Z=Geom[0].Z;
      for (int i=1;i<Road->Geometry.Count;i++)
          {
          // Уклон от (i-1) до (i) точки предположительно меняется равномерно
          // Поэтому уклон для получения превышения усредняем
          Cur_Z+=(double)((L[i]-L[i-1])*(Geom[i].LongSlope+Geom[i-1].LongSlope))/2000;
          Geom[i].Z=Cur_Z;
          }
      }

   Road->CalcMinMaxZ();
   FReady=true;
   DB->Active=false;
   if (MaxW<4000)
    MaxW=4000;
   SetRoadBound(MinL,MaxL,-MaxW,MaxW);
   SortByPlacement();
   BuildRoadMetrics();

   ProgressForm->Note="Загружаются данные привязки видеоинформации";
   if (!LoadVideoInfo1())
       LoadVideoInfo();
   delete DB;
   ProgressForm->Hide();
}


#endif

bool __fastcall TDBDataSource::LoadGeometryBlob(void)
{
bool Res=false;
TADODataSet* DB=new TADODataSet(NULL);
DB->Connection=FConnection;
DB->CommandText=ReplaceNameVal(BlobProfilLoad,NULL,0);
DB->Open();
if (DB->RecordCount)
    {
    TMemoryStream *L_M=new TMemoryStream;
    TMemoryStream *X_M=new TMemoryStream;
    TMemoryStream *Y_M=new TMemoryStream;
    TMemoryStream *Z_M=new TMemoryStream;
    TMemoryStream *LongSlope_M=new TMemoryStream;
    TMemoryStream *LeftSlope_M=new TMemoryStream;
    TMemoryStream *RightSlope_M=new TMemoryStream;
    TMemoryStream *LeftRadius_M=new TMemoryStream;
    TMemoryStream *RightRadius_M=new TMemoryStream;
    (dynamic_cast<TBlobField*>(DB->FieldByName("L")))->SaveToStream(L_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("X")))->SaveToStream(X_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("Y")))->SaveToStream(Y_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("Z")))->SaveToStream(Z_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("LongSlope")))->SaveToStream(LongSlope_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("LeftSlope")))->SaveToStream(LeftSlope_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("RightSlope")))->SaveToStream(RightSlope_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("LeftRadius")))->SaveToStream(LeftRadius_M);
    (dynamic_cast<TBlobField*>(DB->FieldByName("RightRadius")))->SaveToStream(RightRadius_M);
    double* L_A=(double*)L_M->Memory;
    double* X_A=(double*)X_M->Memory;
    double* Y_A=(double*)Y_M->Memory;
    double* Z_A=(double*)Z_M->Memory;
    int* LongSlope_A=(int*)LongSlope_M->Memory;
    int* LeftSlope_A=(int*)LeftSlope_M->Memory;
    int* RightSlope_A=(int*)RightSlope_M->Memory;
    int* LeftRadius_A=(int*)LeftRadius_M->Memory;
    int* RightRadius_A=(int*)RightRadius_M->Memory;

    int n=L_M->Size/sizeof(double);
    Road->Geometry.SetCount(n);
    TGeometryVal *Geom=Road->Geometry.Values;
    __int32 *L=Road->Geometry.L;
    for (int i=0;i<n;i++)
        {
        ProgressForm->Position=i;
        L[i]=L_A[i]*100;
        Geom[i].X=X_A[i]*100;
        Geom[i].Y=Y_A[i]*100;
        Geom[i].Z=Z_A[i]*100;
        Geom[i].LongSlope=LongSlope_A[i];
        Geom[i].LeftSlope=LeftSlope_A[i];
        Geom[i].RightSlope=RightSlope_A[i];
        Geom[i].DirectRad=RightRadius_A[i];
        Geom[i].UnDirectRad=LeftRadius_A[i];
        }
    delete L_M;
    delete X_M;
    delete Y_M;
    delete Z_M;
    delete LongSlope_M;
    delete LeftSlope_M;
    delete RightSlope_M;
    delete LeftRadius_M;
    delete RightRadius_M;
    Res=true;
    }
delete DB;
return Res;
}

bool __fastcall TDBDataSource::LoadGeometry(void)
{
bool Res=false;
// Временно не загружаем эту хрень (а теперь загружаем)
// return Res;
TADODataSet* DB=new TADODataSet(NULL);
DB->Connection=FConnection;

DB->CommandText=ReplaceNameVal(ProfilCount,NULL,0);
DB->Open();
int count=DB->FieldByName("c")->AsInteger;
DB->Close();
if (count>0)
    {
    Road->Geometry.SetCount(count);
    TGeometryVal *Geom=Road->Geometry.Values;
    __int32 *L=Road->Geometry.L;
    DB->CommandText=ReplaceNameVal(ProfilLoad,NULL,0);
    DB->Open();
    int Bounds[2]={0,8};
    OleVariant Param=VarArrayCreate(Bounds,1,varVariant);
    Param.PutElement(WideString("L"),0);
    Param.PutElement(WideString("X"),1);
    Param.PutElement(WideString("Y"),2);
    Param.PutElement(WideString("Z"),3);
    Param.PutElement(WideString("LongSlope"),4);
    Param.PutElement(WideString("LeftSlope"),5);
    Param.PutElement(WideString("RightSlope"),6);
    Param.PutElement(WideString("RightRadius"),7);
    Param.PutElement(WideString("LeftRadius"),8);
    OleVariant R;
    DB->Recordset->GetRows(count,0,Param,R);
    ProgressForm->SetMinMax(0,count);
    if (R.IsArray())
        {
        int k=R.ArrayHighBound(1)+1;
        int n=R.ArrayHighBound(2)+1;
        OleVariant *Array=(OleVariant*)R.ArrayLock();
        for (int i=0;i<n;i++)
            {
            ProgressForm->Position=i;
            L[i]=AsInt(Array[k*i]);
            Geom[i].X=AsInt(Array[k*i+1]);
            Geom[i].Y=AsInt(Array[k*i+2]);
            Geom[i].Z=AsInt(Array[k*i+3]);
            Geom[i].LongSlope=AsInt(Array[k*i+4]);
            Geom[i].LeftSlope=AsInt(Array[k*i+5]);
            Geom[i].RightSlope=AsInt(Array[k*i+6]);
            Geom[i].DirectRad=AsInt(Array[k*i+7]);
            Geom[i].UnDirectRad=AsInt(Array[k*i+8]);
            }
        R.ArrayUnlock();
        Res=true;
        }
    DB->Close();
    }
delete DB;
return Res;
}

bool __fastcall TDBDataSource::LoadVideoInfo1(void)
{
bool Res=false;
TADODataSet* DB=new TADODataSet(NULL);
DB->Connection=FConnection;

DB->CommandText="select * from ELEM_VideoInfo where NumDataSource="+String(FDataClass);
DB->Open();
TMemoryStream *MemL=new TMemoryStream();
TMemoryStream *MemSrv=new TMemoryStream();
TMemoryStream *MemFrames=new TMemoryStream();
Res=DB->RecordCount;
int Files[1024];
int FilesCount=0;
while (!DB->Eof) // Читаем данные из файлов
    {
    int n=DB->FieldByName("Frames_Count")->AsInteger;
    int dir=DB->FieldByName("Direction")->AsInteger;
    TVideoTime *VT=new TVideoTime;
    switch (dir)
        {
        case 1: {FDirVideoId=VT->Id=FDirVideoTime->Count;FDirVideoTime->Add(VT);}break;
        case 2: {FUnDirVideoId=VT->Id=FUnDirVideoTime->Count;FUnDirVideoTime->Add(VT);}break;
        }
    if (!VT)
        break;
    VT->SetCount(n);
    VT->Description=DB->FieldByName("Description")->AsString.Trim();
    dynamic_cast<TBlobField*>(DB->FieldByName("L_Array"))->SaveToStream(MemL);
    dynamic_cast<TBlobField*>(DB->FieldByName("FileId_Array"))->SaveToStream(MemSrv);
    dynamic_cast<TBlobField*>(DB->FieldByName("Frames_Array"))->SaveToStream(MemFrames);
    int *L=(int*)MemL->Memory;
    int *Srv=(int*)MemSrv->Memory;
    int *Frames=(int*)MemFrames->Memory;
    int *A_L=VT->L;
    TVideoTimeVal *Val=VT->Values;
    for (int i=0;i<n;i++)
        {
        A_L[i]=L[i];
        Val[i].Time=Frames[i];
        int j=0;                // составляем список видеофайлов
        Files[FilesCount]=Srv[i];
        while (Files[j]!=Srv[i])
            j++;
        if (j==FilesCount)
            FilesCount++;
        Val[i].HighIndex=j;
        }
    MemL->Clear();
    MemSrv->Clear();
    MemFrames->Clear();
    DB->Next();
    Res=true;
    }
DB->Close();
delete MemL;
delete MemSrv;
delete MemFrames;
// Читаем видео файлы
for (int i=0;i<FilesCount;i++)
    {
    TVideoHigh *VH=new TVideoHigh(Files[i],0);
    FVideoHighList->Add(VH);
//  DB->CommandText="select PathToVideo from ELEM_VideoFiles where id_="+String(Files[i]);
    DB->CommandText="select PathToVideo from v_High where id_High="+String(Files[i]);
    DB->Open();
    if (!DB->Eof)
        VH->FileName=DB->FieldByName("PathToVideo")->AsString;
    else
        VH->FileName="";
    DB->Close();
    }
/*


DB->CommandText="select * from ELEM_VideoFiles where NumDataSource="+String(FDataClass);
DB->Open();
while (!DB->Eof)
    {
    int id=DB->FieldByName("id_")->AsInteger;
    TVideoHigh *VH=new TVideoHigh(id,0);
    VH->FileName=DB->FieldByName("PathToVideo")->AsString;
//    int dir=DB->FieldByName("Direction")->AsInteger;
    FVideoHighList->Add(VH);
    DB->Next();
    }
DB->Close();

DB->CommandText="select * from ELEM_VideoInfo where NumDataSource="+String(FDataClass);
DB->Open();
TMemoryStream *MemL=new TMemoryStream();
TMemoryStream *MemSrv=new TMemoryStream();
TMemoryStream *MemFrames=new TMemoryStream();
Res=DB->RecordCount;
while (!DB->Eof)
    {
    int n=DB->FieldByName("Frames_Count")->AsInteger;
    int dir=DB->FieldByName("Direction")->AsInteger;
    TVideoTime *VT=NULL;
    switch (dir)
        {
        case 1: VT=FDirVideoTime;break;
        case 2: VT=FUnDirVideoTime;break;
        }
    if (!VT)
        break;
    VT->SetCount(n);
    dynamic_cast<TBlobField*>(DB->FieldByName("L_Array"))->SaveToStream(MemL);
    dynamic_cast<TBlobField*>(DB->FieldByName("FileId_Array"))->SaveToStream(MemSrv);
    dynamic_cast<TBlobField*>(DB->FieldByName("Frames_Array"))->SaveToStream(MemFrames);
    int *L=(int*)MemL->Memory;
    int *Srv=(int*)MemSrv->Memory;
    int *Frames=(int*)MemFrames->Memory;
    int *A_L=VT->L;
    TVideoTimeVal *Val=VT->Values;
    for (int i=0;i<n;i++)
        {
        A_L[i]=L[i];
        Val[i].Time=Frames[i];
        for (int j=0;j<FVideoHighList->Count;j++)
            if (Srv[i]==FVideoHighList->Items[j]->Id)
                {Val[i].HighIndex=j;break;}
        }
    DB->Next();
    MemL->Clear();
    MemSrv->Clear();
    MemFrames->Clear();
    }
*/
delete DB;
return Res;
}

void __fastcall TDBDataSource::LoadVideoInfo(void)
{
TADODataSet* DB=new TADODataSet(NULL);
DB->Connection=FConnection;
DB->CommandText=ReplaceNameVal(HighDistinct,NULL,0);
DB->Open();
while (!DB->Eof)
    {
    int idhigh=DB->FieldByName("id_high")->AsInteger;
    int dir=DB->FieldByName("Direction")->AsInteger;
    FVideoHighList->Add(new TVideoHigh(idhigh,dir));
    DB->Next();
    }
DB->Close();
for (int i=0;i<FVideoHighList->Count;i++)
    {
    TVideoHigh *VH=FVideoHighList->Items[i];
    DB->CommandText="select distinct PosOfSVPD,PosOfInv from vi_points where id_high="+String(VH->Id)+" and NumDataSource="+String(FDataClass)+" order by PosOfInv";
    DB->Open();
    VH->SetCount(DB->RecordCount);
    int n=0;
    while (!DB->Eof)
        {
        int swpdpos=DB->FieldByName("PosOfSVPD")->AsFloat*100+0.5;
        int invpos=DB->FieldByName("PosOfInv")->AsFloat*100+0.5;
        VH->L[n]=invpos;
        VH->Values[n]=TSvpdConvertVal(swpdpos);
        DB->Next();
        n++;
        }
    DB->Close();
    }
// Надо отсортировать заезды по возрастанию координат
int n=FVideoHighList->Count;
for (int i=0;i<n-1;i++)
    {
    TVideoHigh *VH=FVideoHighList->Items[i];
    int k=i;
    for (int j=i+1;j<n;j++)
        {
        TVideoHigh *VHT=FVideoHighList->Items[j];
        if (VH->L[0]>VHT->L[0])
            VH=VHT,k=j;
        }
    FVideoHighList->Items[k]=FVideoHighList->Items[i];
    FVideoHighList->Items[i]=VH;
    }

/*
DB->CommandText=ReplaceNameVal(HighLoad,NULL,0);
DB->Open();
while (!DB->Eof)
    {
    int idhigh=DB->FieldByName("id_high")->AsInteger;
    int swpdpos=DB->FieldByName("PosOfSVPD")->AsInteger;
    int invpos=DB->FieldByName("PosOfInv")->AsInteger;
    int dir=DB->FieldByName("Direction")->AsInteger;
    int i;
    for (i=0;i<FVideoHighList->Count;i++)
        if (FVideoHighList->Items[i]->Id==idhigh)
            break;
    if (i<FVideoHighList->Count)
        FVideoHighList->Items[i]->SetEndPos(invpos,swpdpos);
    else
        FVideoHighList->Add(new TVideoHigh(idhigh,invpos,swpdpos,dir));
    DB->Next();
    }
DB->Close();
*/
for (int i=0;i<FVideoHighList->Count;i++)
    {
    DB->CommandText=String("select * from v_high where id_high=")+String(FVideoHighList->Items[i]->Id);
    DB->Open();
    FVideoHighList->Items[i]->FileName=DB->FieldByName("pathToVideo")->AsString;
    DB->Close();
    }
int count1=0;
int count2=0;
int count[512];
bool No_File=false;
for (int i=0;i<FVideoHighList->Count;i++)
    {
    TVideoHigh *VH=FVideoHighList->Items[i];
    int n=VH->Count-1;
//    if (FileExists(VH->FileName))
        {
        if (VH->Direction==1)
            DB->CommandText=String("select count(*) as c from v_TimeDist where id_high=")+
            String(VH->Id)+String(" and Distance<=")+String(VH->Values[n].SvpdPos/100)+
            String(" and Distance>=")+String(VH->Values[0].SvpdPos/100);
        else
            DB->CommandText=String("select count(*) as c from v_TimeDist where id_high=")+
            String(VH->Id)+String(" and Distance<=")+String(VH->Values[0].SvpdPos/100)+
            String(" and Distance>=")+String(VH->Values[n].SvpdPos/100);
        DB->Open();
        count[i]=DB->FieldByName("c")->AsInteger;
        if (VH->Direction==1)
            count1+=count[i]+2;  // Плюс два для занесения координат краев заездов
        else
            count2+=count[i]+2;
        DB->Close();
        }
//    else
//        No_File=true;
    }
FDirVideoId=FUnDirVideoId=0;    
FDirVideoTime->Add(new TVideoTime);
FDirVideoTime->Items[0]->SetCount(count1);
TVideoTimeVal *DirVal=FDirVideoTime->Items[0]->Values;
__int32 *DirL=FDirVideoTime->Items[0]->L;


FUnDirVideoTime->Add(new TVideoTime);
FUnDirVideoTime->Items[0]->SetCount(count2);
TVideoTimeVal *UnDirVal=FUnDirVideoTime->Items[0]->Values;
__int32 *UnDirL=FUnDirVideoTime->Items[0]->L;

int pos1=0;
int pos2=0;
ProgressForm->SetMinMax(0,count1+count2);
for (int i=0;i<FVideoHighList->Count;i++)
    {
    TVideoHigh *VH=FVideoHighList->Items[i];
    __int32 VH_start=VH->Values[0].SvpdPos;
    __int32 VH_end=VH->Values[VH->Count-1].SvpdPos;
    __int32 VH_startL=VH->L[0];
    __int32 VH_endL=VH->L[VH->Count-1];
    TSvpdConvertVal *VHVal=VH->Values;
    __int32 *VHL=VH->L;
//    if (FileExists(VH->FileName))
        {
        if (VH->Direction==1)
            DB->CommandText=String("select cast(Times*1000 as integer) as Times,\
                cast(Distance*100 as integer) as Distance from v_TimeDist where id_high=")+String(VH->Id)+
//                String(" and Distance<=")+String(VH->WayEndPos/100)+
//                String(" and Distance>=")+String(VH->WayStartPos/100)+
                String(" order by Distance");
        else
            DB->CommandText=String("select cast(Times*1000 as integer) as Times,\
                cast(Distance*100 as integer) as Distance from v_TimeDist where id_high=")+String(VH->Id)+
//                String(" and Distance<=")+String(VH->WayStartPos/100)+
//                String(" and Distance>=")+String(VH->WayEndPos/100)+
                String(" order by Distance desc");
        DB->Open();
        int Bounds[2]={0,1};
        OleVariant Param=VarArrayCreate(Bounds,1,varVariant);
        Param.PutElement(WideString("Times"),0);
        Param.PutElement(WideString("Distance"),1);
        OleVariant R;
        DB->Recordset->GetRows(DB->RecordCount,0,Param,R);
        int k=R.ArrayHighBound(1)+1;
        int n=R.ArrayHighBound(2)+1;
        OleVariant *Array=(OleVariant*)R.ArrayLock();
        double Koef=(double)(VHL[1]-VHL[0])/(double)(VHVal[1].SvpdPos-VHVal[0].SvpdPos);
        if (VH->Direction==1)
            {
            int j;
            int vhpos=0;
            for (j=0;j<n;j++)
                {
                int Pos=Array[k*j+1];
                if (Pos>VH_start)
                    break;
                }
            if (j)
                {
                DirL[pos1]=VH_startL;
                int Tm1=Array[k*(j-1)];
                int Tm2=Array[k*j];
                int L1=Array[k*(j-1)+1];
                int L2=Array[k*j+1];
                DirVal[pos1]=TVideoTimeVal(Tm1+((Tm2-Tm1)*(VH_start-L1))/(L2-L1),i);
                pos1++;
                }
            for (;j<n;j++,pos1++)
                {
                int Tm=Array[k*j];
                int Pos=Array[k*j+1];
                if (Pos>VH_end)
                    break;
                while (VHVal[vhpos+1].SvpdPos<Pos)
                    vhpos++;
                Koef=(double)(VHL[vhpos+1]-VHL[vhpos])/(double)(VHVal[vhpos+1].SvpdPos-VHVal[vhpos].SvpdPos);
                DirL[pos1]=VHL[vhpos]+(Pos-VHVal[vhpos].SvpdPos)*Koef;
                DirVal[pos1]=TVideoTimeVal(Tm,i);
                }
            if (j<n)
                {
                DirL[pos1]=VH_endL;
                int Tm1=Array[k*(j-1)];
                int Tm2=Array[k*j];
                int L1=Array[k*(j-1)+1];
                int L2=Array[k*j+1];
                DirVal[pos1]=TVideoTimeVal(Tm1+((Tm2-Tm1)*(VH_end-L1))/(L2-L1),i);
                pos1++;
                }
            }
        else
            {
            int j;
            int vhpos=0;
            for (j=0;j<n;j++)
                {
                int Pos=Array[k*j+1];
                if (Pos<VH_start)
                    break;
                }
            if (j>0)
                {
                UnDirL[pos2]=VH_startL;
                int Tm1=Array[k*(j-1)];
                int Tm2=Array[k*j];
                int L1=Array[k*(j-1)+1];
                int L2=Array[k*j+1];
                UnDirVal[pos2]=TVideoTimeVal(Tm1+((Tm2-Tm1)*(VH_start-L1))/(L2-L1),i);
                pos2++;
                }
            for (;j<n;j++,pos2++)
                {
                int Tm=Array[k*j];
                int Pos=Array[k*j+1];
                if (Pos<VH_end)
                    break;
                while (VHVal[vhpos+1].SvpdPos>Pos)
                    vhpos++;
                Koef=(double)(VHL[vhpos+1]-VHL[vhpos])/(double)(VHVal[vhpos+1].SvpdPos-VHVal[vhpos].SvpdPos);
                UnDirL[pos2]=VHL[vhpos]+(Pos-VHVal[vhpos].SvpdPos)*Koef;
                UnDirVal[pos2]=TVideoTimeVal(Tm,i);
                }
            if (j<n)
                {
                UnDirL[pos2]=VH_endL;
                int Tm1=Array[k*(j-1)];
                int Tm2=Array[k*j];
                int L1=Array[k*(j-1)+1];
                int L2=Array[k*j+1];
                UnDirVal[pos2]=TVideoTimeVal(Tm1+((Tm2-Tm1)*(VH_end-L1))/(L2-L1),i);
                pos2++;
                }
            }
        R.ArrayUnlock();
        DB->Close();
        }
    ProgressForm->Position=pos1+pos2;
    }
if (No_File)
    ShowMessage("Один или несколько видеофайлов отсутствуют по заданному пути.\
 Для поиска видеофайлов воспользуйтесь утилитой привязки видеофайлов из\
 главного меню asudor пункт Инструменты.");

FDirVideoTime->Items[0]->SetCount(pos1);
FUnDirVideoTime->Items[0]->SetCount(pos2);
if (count1==0) {
   FDirVideoTime->Clear();
   FDirVideoId=-1;
   }
if (count2==0) {
   FUnDirVideoTime->Clear();
   FUnDirVideoId=-1;
   }
delete DB;
}

String __fastcall TDBDataSource::ReplaceNameVal(String Sql,TRoadObject *Obj,int Param)
{
char Result[2048];
char *res=Result;
char Name[2048];
char *nm=Name;
char *str=Sql.c_str();
bool s=false;
while (*str)
    {
    if (*str=='$')
        {
        if (s)
            {
            *nm=0;
            String Val="NULL";
            if (String(Name)=="NumRoad")
                Val=String(Id);
            else if (String(Name)=="NumSource")
                {
                Val=String(DataClass);
                }
            else if (String(Name)=="SourceType")
                {
                Val=String(DataType);
                }
            else if (String(Name)=="Id")
                {
                if (Obj)
                    Val=String(Obj->Id);
                }
            else if (String(Name)=="NumLine")
                {
                if (Obj)
                    if (Obj->Poly)
                         Val=String(Obj->Poly->Id);
                }
            else if (String(Name)=="PolyL")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].L);
                }
            else if (String(Name)=="PolyX")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].X);
                }
            else if (String(Name)=="PolyCode")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].Code());
                }
            else if (String(Name)=="PolyLeep")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].LeepPar);
                }
            else if (String(Name)=="PolyBase1")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].BasePar1);
                }
            else if (String(Name)=="PolyBase2")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        if (Param<Obj->Poly->Count)
                            Val=String((*Obj->Poly)[Param].BasePar2);
                }
            else if (String(Name)=="PolyNum")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        Val=String(Param);
                }
            else if (String(Name)=="PolyCount")
                {
                Val="0";
                if (Obj)
                    if (Obj->Poly)
                        Val=String(Obj->Poly->Count);
                }
            else
                {
                if (Obj)
                    {
                    Val=Obj->GetPropValue(Name);
                    }
                }
            strcpy(res,Val.c_str());
            res+=Val.Length();
            nm=Name;
            }
        s=!s;
        }
    else
        {
        if (s)
            *(nm++)=*str;
        else
            *(res++)=*str;
        }
    str++;
    }
*res=0;
return String(Result);
}

void __fastcall TDBDataSource::Apply(TDictSource *Dict)
{
if (ReadOnly)
    return;
TADODataSet* dataset=new TADODataSet(NULL);
dataset->Connection=Connection;
TADOCommand* command=new TADOCommand(NULL);
command->Connection=Connection;
for (int i=0;i<Objects->Count;i++)
    {
    TRoadObject *Obj=Objects->Items[i];
    if (Obj)
      if (Obj->Modified)
        {
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[Obj->DictId]);
        if (Meta)
            {
            if (Obj->Id>0)  // Объект из базы
                {
//                SaveObjMetrics(command,dataset,Obj);
                if (Meta->SqlSave!="")
                    {
                    command->CommandText = ReplaceNameVal(Meta->SqlSave,Obj,0);
                    command->Execute();
                    }
                }
            else if (Obj->Id==0)
                {
                if (Meta->SqlAppend!="")
                    {
//                    SaveObjMetrics(command,dataset,Obj);
                    dataset->CommandText=ReplaceNameVal(Meta->SqlAppend,Obj,0);
                    dataset->Open();
                    dataset->First();
                    int id_=dataset->FieldByName("Identity")->AsInteger;
                    dataset->Close();
                    Obj->SetId(id_);
                    }
                }
            }
        }
    }
SaveMetrics(Dict);
for (int i=0;i<Objects->Count;i++)
    {
    TRoadObject *Obj=Objects->Items[i];
    if (Obj)
      if (Obj->Modified)
        Obj->PostSaveObject();
    }
for (int i=0;i<FDelBuffer->Count;i++)
    {
    TRoadObject *Obj=FDelBuffer->Items[i];
    if (Obj)
      if (Obj->Id)
        {
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[Obj->DictId]);
        if (Meta)
            {
            if (Meta->SqlDelete!="")
                {
                if (Obj->Poly)
                    {
                    Obj->Poly->Count=0;
//                    SaveObjMetrics(command,dataset,Obj);
                    Obj->Poly=NULL;
                    }
                command->CommandText = ReplaceNameVal(Meta->SqlDelete,Obj,0);
                command->Execute();
                }
            }
        }
    }
FDelBuffer->Clear();
delete command;
delete dataset;
}

void __fastcall TDBDataSource::SaveMetrics(TDictSource *Dict)
{
TADODataSet* dataset=new TADODataSet(NULL);
dataset->Connection=Connection;
TMemoryStream *Mem=new TMemoryStream;
for (int i=0;i<Objects->Count;i++)
    {
    TRoadObject *Obj=Objects->Items[i];
    if (Obj)
      if (Obj->Modified)
        {
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[Obj->DictId]);
        if (Meta)
            if (Meta->TableName!="")
                {
                String Sql="select * from "+Meta->TableName+" where id_="+Obj->Id;
                dataset->CommandText=Sql;
                dataset->Open();
                if (dataset->RecordCount==1)
                    {
                    TField *FldCount=dataset->FindField("PointsCount");
                    TBlobField *FldPoints=dynamic_cast<TBlobField*>(dataset->FindField("Points"));
                    if (FldCount&&FldPoints)
                        {
                        dataset->Edit();
                        int pcount=0;
                        if (Obj->Poly)
                            pcount=Obj->Poly->Count;
                        FldCount->AsInteger=pcount;
                        if (pcount)
                            {
                            Obj->Poly->SaveToStream(Mem);
                            FldPoints->LoadFromStream(Mem);
                            }
                        else
                            {
                            FldPoints->Clear();
                            }
                        dataset->Post();
                        }
                    }
                dataset->Close();
                }
        }
    }
delete Mem;
delete dataset;
}

TRoadObject * __fastcall TDBDataSource::CopyObject(TRoadObject *obj,TDictSource *Dict,int newid)
{
if (obj->Id) // Если объект записан
    {
/*
    bool doinsert=true;
    for (int i=0;i<Dict->ObjClasses->Count;i++)
        {
        TObjMetaClass *Meta=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[i]);
            if (Meta)
                if (Meta->Id==obj->DictId)
                    {
                    if (Meta->TableName!="")
                        {
                        TADODataSet* dataset=new TADODataSet(NULL);
                        dataset->Connection=Connection;
                        if (FrmSetting->CopyIndex==1)
                            {
                            dataset->CommandText="select id_ from "+Meta->TableName+" where Prev_id="+String(obj->Id);
                            dataset->Open();
                            if (dataset->RecordCount)
                                doinsert=false;
                            dataset->Close();
                            }
                        else if (FrmSetting->CopyIndex==0)  // Замещать существующие объекты
                            {
                            TADOCommand *command=new TADOCommand(NULL);
                            command->Connection=Connection;
                            command->CommandText="delete from "+Meta->TableName+" where Prev_id="+String(obj->Id);
                            command->Execute();
                            delete command;
                            doinsert=true;
                            }
                        if (doinsert)
                            {
                            int dc;
                            if (FDataType!=3)
                                dc=FDataClass;
                            else
                                dc=0;
                            dataset->CommandText="exec ChangeDataSource "+String(obj->Id)+String(",")+
                                    Meta->TableName+String(",")+String(dc);
                            dataset->Open();
                            dataset->First();
                            if (dataset->RecordCount)
                                newid=dataset->FieldByName("New_ID")->AsInteger;
                            }
                        delete dataset;
                        }
                    break;
                    }
            }
*/
    }
return TDtaSource::CopyObject(obj,Dict,newid);
}


void __fastcall TDBDataSource::SaveObjMetrics(TADOCommand *command,TADODataSet *DB,TRoadObject *Obj)
{
TPolyline *Poly=Obj->Poly;
if (Poly)
    {
    if (Poly->Count)
        {
        if (Poly->Id)
            {
            command->CommandText=ReplaceNameVal(MetricsDelete,Obj,0);
            command->Execute();
            for (int i=0;i<Poly->Count;i++)
                {
                command->CommandText=ReplaceNameVal(MetricsAppend,Obj,i);
                command->Execute();
                }
            command->CommandText=ReplaceNameVal(ListMetricsSave,Obj,0);
            command->Execute();
            }
        else
            {
            DB->CommandText=ReplaceNameVal(ListMetricsAppend,Obj,0);
            DB->Open();
            DB->First();
            int id=DB->FieldByName("Identity")->AsInteger;
            Poly->SetId(id);
            DB->Close();
            for (int i=0;i<Poly->Count;i++)
                {
                command->CommandText=ReplaceNameVal(MetricsAppend,Obj,i);
                command->Execute();
                 }
            }
        }
    else
        {
        command->CommandText=ReplaceNameVal(MetricsDelete,Obj,0);
        command->Execute();
        command->CommandText=ReplaceNameVal(ListMetricsDelete,Obj,0);
        command->Execute();
        }
    }

}

void __fastcall TDBDataModule::LoadViewSources(__int32 RoadId,__int32 ViewId)
{
FConnection->Connected=true;
if (FConnection->Connected)
    {
    TADODataSet *ADB=new TADODataSet(MainForm);
    ADB->Connection=FConnection;
    ADB->CommandText=String("select NumDataSource from ELEM_Visible where NumView=")+String(ViewId);
    ADB->Open();
    while (!ADB->Eof)
        {
        __int32 Num=ADB->FieldByName("NumDataSource")->AsInteger;
        String Capt=GetRoadName(RoadId).Trim()+String(" : ")+GetSourceName(Num).Trim();
        MainForm->ResManager->AddDataSource(Capt,RoadId,Num,0,MainForm->Connection,MainForm->Factory);
        ADB->Next();
        }
    ADB->Close();
    delete ADB;
    }
}
void __fastcall TDBDataModule::ReleaseViewSources(__int32 RoadId,__int32 ViewId)
{
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select NumDataSource from ELEM_Visible where NumView=")+String(ViewId);
    DB->Open();
    while (!DB->Eof)
        {
        __int32 Num=DB->FieldByName("NumDataSource")->AsInteger;
        MainForm->ResManager->ReleaseDataSource(RoadId,Num);
        DB->Next();
        }
    DB->Close();
    }
}

void __fastcall TDBDataModule::LoadVisible(__int32 RoadId,__int32 ViewId,TVisSetFrm *VisSet)
{
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select NumDataSource,Visible from ELEM_Visible where NumView=")+String(ViewId);
    DB->Open();
    while (!DB->Eof)
        {
        __int32 Num=DB->FieldByName("NumDataSource")->AsInteger;
        TDtaSource *Dta=MainForm->ResManager->GetSource(RoadId,Num);
        if (Dta)
            {
            String VStr=DB->FieldByName("Visible")->AsString;
            bool mask[MAXCODEID];
            int n=MAXCODEID;
            if (VStr.Length()<n)
               n=VStr.Length();
            for (int i=0;i<n;i++)
               mask[i]=VStr[i+1]-'0';
            VisSet->SetVisible(MAXCODEID,mask,Dta);
            DB->Next();
            }
        }
    DB->Close();
    }
}

void __fastcall TDBDataModule::LoadViewParam(TRoadFrm *Frm,__int32 ViewId)
{
FConnection->Connected=true;
if (FConnection->Connected)
    {
    TVisSetFrm *VSet=Frm->VisSet;
    DB->Connection=FConnection;
    DB->CommandText=String("select * from ELEM_ListView where id_=")+String(ViewId);
    DB->Open();
    int rid=DB->FieldByName("NumRoad")->AsInteger;
    int sid=DB->FieldByName("NumMetricSource")->AsInteger;
    TDtaSource *Dta=MainForm->ResManager->GetSource(rid,sid);
    if (Dta)
        VSet->MetricSource=Dta;
    sid=DB->FieldByName("NumVideoSource")->AsInteger;
    Dta=MainForm->ResManager->GetSource(rid,sid);
    if (Dta)
        VSet->VideoSource=Dta;
    sid=DB->FieldByName("NumProfilSource")->AsInteger;
    Dta=MainForm->ResManager->GetSource(rid,sid);
    if (Dta)
        VSet->ProfilSource=Dta;
    sid=DB->FieldByName("NumCurveSource")->AsInteger;
    Dta=MainForm->ResManager->GetSource(rid,sid);
    if (Dta)
        VSet->CurveSource=Dta;
    sid=DB->FieldByName("NumEditedSource")->AsInteger;
    Dta=MainForm->ResManager->GetSource(rid,sid);
    if (Dta)
        VSet->EditedSource=Dta;
    int basel=DB->FieldByName("BaseScaleL")->AsInteger;
    int basex=DB->FieldByName("BaseScaleX")->AsInteger;
    int basep=DB->FieldByName("BaseScaleP")->AsInteger;
    Frm->SetBaseScale(basel,basex,basep);
    int w=DB->FieldByName("WindowWidth")->AsInteger;
    int h=DB->FieldByName("WindowHeight")->AsInteger;
    if (w&&h)
        Frm->SetBounds(Frm->Left,Frm->Top,w,h);
    TPlanKind pkind=(TPlanKind)(DB->FieldByName("PlanOrientation")->AsInteger);
    if (pkind!=Frm->PlanKind)
        Frm->ChangeOrientation();
    TPlanDirect pdirect=(TPlanDirect)(DB->FieldByName("PlanOrientation")->AsInteger);
    if (pdirect!=Frm->PlanDirect)
        Frm->ChangeDirection();
    int plmin=DB->FieldByName("VLMin")->AsInteger;
    int plmax=DB->FieldByName("VLMax")->AsInteger;
    Frm->SetViewPosition(plmin,plmax);
    int boundx=DB->FieldByName("BoundX")->AsInteger;
    int objx=DB->FieldByName("ObjXMax")->AsInteger;
    Frm->SetXBounds(boundx,objx);
    int fnsize=DB->FieldByName("FontSize")->AsInteger;
    Frm->PlanFontSize=fnsize;
    if (VSet->MetricSource)
        {
        int ms=DB->FieldByName("MetricsTech")->AsInteger;
        if (ms!=VSet->MetricSource->MetricsSource)
            {
            VSet->MetricSource->MetricsSource=ms;
            VSet->MetricSource->BuildRoadMetrics();
            }
        }
    DB->Close();
    }
}

__int32 __fastcall TDBDataModule::DataNum(TDtaSource *Dta)
{
return Dta?Dta->DataClass:-1;
}

String __fastcall TDBDataModule::GetDistrName(__int32 id)
{
String Res="";
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText="select O.FullTitle from ListRoads L left join ListDistricts O on L.NumDistrict=O.id_ where L.id_="+String(id);
    DB->Open();
    if (DB->RecordCount)
        Res=DB->FieldByName("FullTitle")->AsString.Trim();
    DB->Close();
    }
return Res;
}

String __fastcall TDBDataModule::GetInspectName(__int32 id)
{
String Res="";
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText="select O.FullTitle from ListRoadParts L left join ListOrganizations O on L.Reference=O.id_ where NumPartType=28 and NumDataSource=0 and NumRoad="+String(id);
    DB->Open();
    if (DB->RecordCount)
        Res=DB->FieldByName("FullTitle")->AsString.Trim();
    DB->Close();
    }
return Res;
}

void __fastcall TDBDataModule::SaveView(TRoadFrm *Frm,__int32 ViewId,String ViewName)
{
FConnection->Connected=true;
if (FConnection->Connected)
    {
    TVisSetFrm *VSet=Frm->VisSet;
    Cmd->Connection=FConnection;
    Cmd->CommandText=String("delete from ELEM_Visible where NumView=")+String(ViewId);
    Cmd->Execute();
    String Param="";
    Param+=String(",NumMetricSource=")+String(DataNum(VSet->MetricSource));
    Param+=String(",NumVideoSource=")+String(DataNum(VSet->VideoSource));
    Param+=String(",NumProfilSource=")+String(DataNum(VSet->ProfilSource));
    Param+=String(",NumCurveSource=")+String(DataNum(VSet->CurveSource));
    Param+=String(",NumEditedSource=")+String(DataNum(VSet->EditedSource));
    Param+=String(",PlanOrientation=")+String(Frm->PlanKind);
    Param+=String(",PlanDirect=")+String(Frm->PlanDirect);
    Param+=String(",VLMin=")+String(Frm->PMinL);
    Param+=String(",VLMax=")+String(Frm->PMaxL);
    Param+=String(",WindowWidth=")+String(Frm->Width);
    Param+=String(",WindowHeight=")+String(Frm->Height);
    Param+=String(",BaseScaleL=")+String(Frm->BaseScaleL);
    Param+=String(",BaseScaleX=")+String(Frm->BaseScaleX);
    Param+=String(",BaseScaleP=")+String(Frm->BaseScaleP);
    Param+=String(",BoundX=")+String(Frm->MaxX);
    Param+=String(",ObjXMax=")+String(VSet->MetricSource->Road->XMax);
    Param+=String(",FontSize=")+String(Frm->PlanFontSize);
    if (VSet->MetricSource)
        Param+=String(",MetricsTech=")+String(VSet->MetricSource->MetricsSource);
    Cmd->CommandText=String("update ELEM_ListView set NumRoad=")+String(Frm->RoadId)+
            String(" ,Title='")+ViewName+String("'")+Param+String(" where id_=")+String(ViewId);
    Cmd->Execute();
    for (int i=0;i<VSet->DataList->Count;i++)
        {
        TDtaSource *Dta=VSet->DataList->Items[i];
        if (VSet->SourceVisible(Dta)||VSet->MetricSource==Dta||VSet->VideoSource==Dta||
         VSet->ProfilSource==Dta||VSet->CurveSource==Dta||VSet->EditedSource==Dta)
            {
            bool mask[MAXCODEID];
            VSet->GetVisible(MAXCODEID,mask,Dta);
            String VStr="";
            for (int i=0;i<MAXCODEID;i++)
            if (mask[i])
                VStr+='1';
            else
                VStr+='0';
            Cmd->CommandText=String("insert into ELEM_Visible (NumView,NumDataSource,Visible) VALUES (")+
                    String(ViewId)+String(",")+String(Dta->DataClass)+String(",'")+VStr+String("')");
            Cmd->Execute();
            }
        }
    }
}

String __fastcall TDBDataModule::GetRoadName(__int32 id)
{
String Res="";
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select FullTitle from ListRoads where id_=")+String(id);
    DB->Open();
    Res=DB->FieldByName("FullTitle")->AsString.Trim();
    DB->Close();
    }
return Res;
}

String __fastcall TDBDataModule::GetViewName(__int32 id)
{
String Res="";
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select Title from ELEM_ListView where id_=")+String(id);
    DB->Open();
    Res=DB->FieldByName("Title")->AsString.Trim();
    DB->Close();
    }
return Res;
}

int __fastcall TDBDataModule::GetSourceType(__int32 id)
{
int Res=-1;
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select NumType from ListDataSources where id_=")+String(id);
    DB->Open();
    Res=DB->FieldByName("NumType")->AsInteger;
    DB->Close();
    }
return Res;
}

String __fastcall TDBDataModule::GetSourceName(__int32 id)
{
String Res="";
FConnection->Connected=true;
if (FConnection->Connected)
    {
    DB->Connection=FConnection;
    DB->CommandText=String("select FullTitle from ListDataSources where id_=")+String(id);
    DB->Open();
    Res=DB->FieldByName("FullTitle")->AsString.Trim();
    DB->Close();
    }
return Res;
}

String __fastcall TDBDataModule::GetCurrentDate(void)
{
TDateTime t=TDateTime::CurrentDate();
unsigned short d,m,y;
t.DecodeDate(&y,&m,&d);
return "convert(smalldatetime,'"+String(d)+"."+String(m)+"."+String(y)+"',104)";
}

bool __fastcall TDBDataModule::GetRoadBound(int id,int datasource,int &LMin,int &LMax)
{
bool Res=true;
FConnection->Connected=true;
DB->Connection=FConnection;
DB->CommandText="select cast(StartPos*100+0.5 as integer) as StartPos,\
    cast(EndPos*100+0.5 as integer) as EndPos from ListRoadParts \
    where NumPartType=33 and NumRoad="+String(id)+" and NumDataSource="+String(datasource);
DB->Open();
if (DB->RecordCount>0)
    {
    LMin=DB->FieldByName("StartPos")->AsInteger;
    LMax=DB->FieldByName("EndPos")->AsInteger;
    }
else
    {
    DB->Close();
    DB->CommandText="select cast(StartPos*100+0.5 as integer) as StartPos,\
        cast(EndPos*100+0.5 as integer) as EndPos from ListRoads where id_="+String(id);
    DB->Open();
    LMin=DB->FieldByName("StartPos")->AsInteger;
    LMax=DB->FieldByName("EndPos")->AsInteger;
    }
DB->Close();
return Res;
}

int __fastcall TDBDataModule::AddProject(__int32 RoadId,String PrjName,__int32 OrgNum, String ExecName, String ExamName)
{
int Res=-1;
FConnection->Connected=true;
DB->Connection=FConnection;
DB->CommandText=String("insert into ListDataSources (FullTitle,NumRoad,NumType,\
        NumOrganization,Executor,Examiner,DateCreate,DateBegin)\
        values ('")+PrjName+String("',")+String(RoadId)+String(",3,")+String(OrgNum)+
        String(",'")+ExecName+String("','")+ExamName+
        String("',")+GetCurrentDate()+String(",")+GetCurrentDate()+
        String(") select @@IDENTITY as 'Identity'");
DB->Open();
DB->First();
Res=DB->FieldByName("Identity")->AsInteger;
DB->Close();
int lmin,lmax;
GetRoadBound(RoadId,Res,lmin,lmax);
DB->CommandText=String("insert into ListRoadParts (NumPartType, NumRoad, StartPos, EndPos,\
    DataSource, NumDataSource) values (33,")+String(RoadId)+String(",")+String(lmin/100)+ 
    String(",")+String(lmax/100)+String(",3,")+String(Res)+
    String(") select @@IDENTITY as 'Identity'");
DB->Open();
DB->Close();
return Res;
}
