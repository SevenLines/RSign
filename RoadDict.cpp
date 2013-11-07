//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RoadDict.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall DelLineBreaks(char *s)
{
char *p=s;
while (*s)
    {
    if ((*s!='\n')&&(*s!='\r'))
        *(p++)=*(s++);
    else
        *(p++)=' ',s++;
    }
}

void __fastcall TObjMetaClass::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("Title="+FTitle);
lst->Add("OneTitle="+FOneTitle);
lst->Add("ParentId="+String(FParentId));
lst->Add("Flags="+String(FFlags));
lst->Add("ClassName="+FClassName);
lst->Add("TableName="+FTableName);
DelLineBreaks(FSql.c_str());
lst->Add("SQL="+FSql);
DelLineBreaks(FSqlSave.c_str());
lst->Add("SQLSave="+FSqlSave);
DelLineBreaks(FSqlAppend.c_str());
lst->Add("SQLAppend="+FSqlAppend);
DelLineBreaks(FSqlDelete.c_str());
lst->Add("SQLDelete="+FSqlDelete);
lst->Add("PropCount="+String(FPropCount));
lst->Add("MainPropId="+String(FMainPropId));
for (int i=0;i<FPropCount;i++)
        {
        lst->Add("PropFlag"+String(i)+"="+String(FPropFlags[i]));
        lst->Add("PropId"+String(i)+"="+String(FPropIds[i]));
        }
}

void __fastcall TObjMetaClass::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...){FId=0;}
try {FTitle=lst->Values["Title"];} catch (...) {FTitle="";}
try {FOneTitle=lst->Values["OneTitle"];} catch (...) {FOneTitle="";}
try {FParentId=lst->Values["ParentId"].ToInt();} catch (...){FParentId=0;}
try {FFlags=lst->Values["Flags"].ToInt();} catch (...){FFlags=0;}
try {FClassName=lst->Values["ClassName"];} catch (...){FClassName="";}
try {FTableName=lst->Values["TableName"];} catch (...){FTableName="";}
try {FSql=lst->Values["SQL"];} catch (...){FSql="";}
try {FSqlSave=lst->Values["SQLSave"];} catch (...){FSqlSave="";}
try {FSqlAppend=lst->Values["SQLAppend"];} catch (...){FSqlAppend="";}
try {FSqlDelete=lst->Values["SQLDelete"];} catch (...){FSqlDelete="";}
try {FPropCount=lst->Values["PropCount"].ToInt();} catch (...){FPropCount=0;}
try {FMainPropId=lst->Values["MainPropId"].ToInt();} catch (...){FMainPropId=0;}
for (int i=0;i<FPropCount;i++)
        {
        try {FPropFlags[i]=lst->Values["PropFlag"+String(i)].ToInt();} catch (...){FPropFlags[i]=0;}
        try {FPropIds[i]=lst->Values["PropId"+String(i)].ToInt();} catch (...){FPropIds[i]=0;}
        }
}

void __fastcall TObjMetaClass::DumpProp(TStringList *lstprop,TStringList *lstflag)
{
for (int i=0;i<FPropCount;i++)
    {
    lstprop->Add(String(FPropIds[i]));
    lstflag->Add(String(FPropFlags[i]));
    }
}
void __fastcall TObjMetaClass::LoadDumpProp(TStringList *lstprop,TStringList *lstflag)
{
FPropCount=lstprop->Count;
if (lstflag->Count<FPropCount)
    FPropCount=lstflag->Count;
if (FPropCount>MAXOBJPROPCOUNT)
    FPropCount=MAXOBJPROPCOUNT;
for (int i=0;i<FPropCount;i++)
    {
    try {FPropIds[i]=lstprop->Strings[i].ToInt();} catch (...){FPropIds[i]=0;}
    try {FPropFlags[i]=lstflag->Strings[i].ToInt();} catch (...){FPropFlags[i]=0;}
    }
}


void __fastcall TPropClassesRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("ShortName="+FShortName);
lst->Add("PropName="+FPropName);
lst->Add("ClassName="+FClassName);
lst->Add("FieldName="+FFieldName);
lst->Add("Type="+String(int(FType)));
}
void __fastcall TPropClassesRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FShortName=lst->Values["ShortName"];} catch (...) {FShortName="";}
try {FPropName=lst->Values["PropName"];} catch (...) {FPropName="";}
try {FClassName=lst->Values["ClassName"];} catch (...) {FClassName="";}
try {FFieldName=lst->Values["FieldName"];} catch (...) {FFieldName="";}
try {FType=TPropClassesType(lst->Values["Type"].ToInt());} catch (...) {FType=prUnknown;}
}

void __fastcall TTextPropRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("PropId="+String(FPropId));
lst->Add("ShortText="+FShortText);
lst->Add("Text="+FText);
}
void __fastcall TTextPropRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FPropId=lst->Values["PropId"].ToInt();} catch (...) {FPropId=0;}
try {FShortText=lst->Values["ShortText"];} catch (...) {FShortText="";}
try {FText=lst->Values["Text"];} catch (...) {FText="";}
}

void __fastcall TDrwProcRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("Name="+FName);
}
void __fastcall TDrwProcRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FName=lst->Values["Name"];} catch (...) {FName="";}
}

void __fastcall TDrwParamRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("ProcId="+String(FProcId));
ParDump(lst);
}

void __fastcall TDrwParamRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FProcId=lst->Values["ProcId"].ToInt();} catch (...) {FProcId=0;}
LoadParDump(lst);
}

void __fastcall TDrwParamRec1::ParDump(TStringList *lst)
{
lst->Add("PenId="+String(FPenId));
lst->Add("BrushId="+String(FBrushId));
}
void __fastcall TDrwParamRec1::LoadParDump(TStringList *lst)
{
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FBrushId=lst->Values["BrushId"].ToInt();} catch (...) {FBrushId=0;}
}

void __fastcall TDrwParamRec::SetStyle(String s)
{
FStyleCount=0;
s=s.Trim();
while (s!="")
    {
    int p=s.Pos(" ");
    if (p<=0)
        p=s.Length()+1;
    FStyles[FStyleCount]=s.SubString(1,p-1).ToInt();
    FStyleCount++;
    s=s.Delete(1,p);
    s=s.Trim();
    }
}

String __fastcall TDrwParamRec::GetStyle(void)
{
String Res="";
for (int i=0;i<FStyleCount;i++)
    Res=Res+String(FStyles[i])+String(" ");
return Res;
}

void __fastcall TDrwParamRec2::ParDump(TStringList *lst)
{
lst->Add("PenId="+String(FPenId));
lst->Add("Width="+String(FWidth));
lst->Add("ScaleKind="+String((int)FScaleKind));
lst->Add("Style="+GetStyle());
lst->Add("Offset="+String(FOffset));
}
void __fastcall TDrwParamRec2::LoadParDump(TStringList *lst)
{
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch (...) {FWidth=0;}
try {FScaleKind=TScaleKind(lst->Values["ScaleKind"].ToInt());} catch (...) {FScaleKind=skByX;}
try {SetStyle(lst->Values["Style"]);} catch (...) {SetStyle("");}
try {FOffset=lst->Values["Offset"].ToInt();} catch (...) {FOffset=0;}
}

void __fastcall TDrwParamRec3::ParDump(TStringList *lst)
{
lst->Add("Measure="+String(FMeasure));
lst->Add("MetaId="+String(FMetaId));
lst->Add("DX="+String(FDX));
lst->Add("DY="+String(FDY));
lst->Add("Width="+String(FWidth));
lst->Add("Height="+String(FHeight));
lst->Add("DataLeft="+String(FDataRect.left));
lst->Add("DataRight="+String(FDataRect.right));
lst->Add("DataTop="+String(FDataRect.top));
lst->Add("DataBottom="+String(FDataRect.bottom));
}
void __fastcall TDrwParamRec3::LoadParDump(TStringList *lst)
{
try {FMeasure=lst->Values["Measure"].ToInt();} catch (...) {FMeasure=0;}
try {FMetaId=lst->Values["MetaId"].ToInt();} catch (...) {FMetaId=0;}
try {FDX=lst->Values["DX"].ToInt();} catch (...) {FDX=0;}
try {FDY=lst->Values["DY"].ToInt();} catch (...) {FDY=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch (...) {FWidth=0;}
try {FHeight=lst->Values["Height"].ToInt();} catch (...) {FHeight=0;}
try {FDataRect.left=lst->Values["DataLeft"].ToInt();} catch (...) {FDataRect.left=0;}
try {FDataRect.right=lst->Values["DataRight"].ToInt();} catch (...) {FDataRect.right=FWidth;}
try {FDataRect.top=lst->Values["DataTop"].ToInt();} catch (...) {FDataRect.top=0;}
try {FDataRect.bottom=lst->Values["DataBottom"].ToInt();} catch (...) {FDataRect.bottom=FHeight;}
}

void __fastcall TDrwParamRec4::ParDump(TStringList *lst)
{
lst->Add("PenId="+String(FPenId));
lst->Add("Width="+String(FWidth));
lst->Add("ScaleKind="+String((int)FScaleKind));
lst->Add("TaleLength="+String(FTaleLength));
}
void __fastcall TDrwParamRec4::LoadParDump(TStringList *lst)
{
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch (...) {FWidth=0;}
try {FScaleKind=TScaleKind(lst->Values["ScaleKind"].ToInt());} catch (...) {FScaleKind=skByX;}
try {FTaleLength=lst->Values["TaleLength"].ToInt();} catch (...) {FTaleLength=0;}
}

void __fastcall TDrwParamRec5::ParDump(TStringList *lst)
{
lst->Add("Width="+String(FWidth));
lst->Add("Shift="+String(FShift));
lst->Add("Dash="+String(FDash));
lst->Add("Space="+String(FSpace));
lst->Add("Offset="+String(FOffset));
lst->Add("Scaleable="+String(int(FScaleable)));
lst->Add("PenId="+String(FPenId));
lst->Add("BrushId="+String(FBrushId));
}
void __fastcall TDrwParamRec5::LoadParDump(TStringList *lst)
{
try {FWidth=lst->Values["Width"].ToInt();} catch (...) {FWidth=0;}
try {FShift=lst->Values["Shift"].ToInt();} catch (...) {FShift=0;}
try {FDash=lst->Values["Dash"].ToInt();} catch (...) {FDash=0;}
try {FSpace=lst->Values["Space"].ToInt();} catch (...) {FSpace=0;}
try {FOffset=lst->Values["Offset"].ToInt();} catch (...) {FOffset=0;}
try {FScaleable=lst->Values["Scaleable"].ToInt();} catch (...) {FScaleable=0;}
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FBrushId=lst->Values["BrushId"].ToInt();} catch (...) {FBrushId=0;}
}

void __fastcall TDrwParamRec6::ParDump(TStringList *lst)
{
lst->Add("Kind="+String(FKind));
lst->Add("Size="+String(FSize));
lst->Add("OrSize="+String(FOrSize));
lst->Add("Space="+String(FSpace));
lst->Add("Shift="+String(FShift));
lst->Add("ScaleKind="+String((int)FScaleKind));
lst->Add("Offset="+String(FOffset));
lst->Add("Scaleable="+String(int(FScaleable)));
lst->Add("PenId="+String(FPenId));
lst->Add("BrushId="+String(FBrushId));
}
void __fastcall TDrwParamRec6::LoadParDump(TStringList *lst)
{
try {FKind=lst->Values["Kind"].ToInt();} catch (...) {FKind=0;}
try {FSize=lst->Values["Size"].ToInt();} catch (...) {FSize=0;}
try {FOrSize=lst->Values["OrSize"].ToInt();} catch (...) {FOrSize=0;}
try {FSpace=lst->Values["Space"].ToInt();} catch (...) {FSpace=0;}
try {FShift=lst->Values["Shift"].ToInt();} catch (...) {FShift=0;}
try {FOffset=lst->Values["Offset"].ToInt();} catch (...) {FOffset=0;}
try {FScaleable=lst->Values["Scaleable"].ToInt();} catch (...) {FScaleable=0;}
try {FScaleKind=TScaleKind(lst->Values["ScaleKind"].ToInt());} catch (...) {FScaleKind=skByX;}
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FBrushId=lst->Values["BrushId"].ToInt();} catch (...) {FBrushId=0;}
}

void __fastcall TDrwParamRec7::LoadParDump(TStringList *lst)
{
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FShift=lst->Values["Shift"].ToInt();} catch (...) {FShift=0;}
}

void __fastcall TDrwParamRec7::ParDump(TStringList *lst)
{
lst->Add("PenId="+String(FPenId));
lst->Add("Shift="+String(FShift));
}

void __fastcall TDrwParamRec8::LoadParDump(TStringList *lst)
{
try {FPenId=lst->Values["PenId"].ToInt();} catch (...) {FPenId=0;}
try {FLength=lst->Values["Length"].ToInt();} catch (...) {FLength=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch (...) {FWidth=0;}
try {FKind=lst->Values["Kind"].ToInt();} catch (...) {FKind=3;}
}

void __fastcall TDrwParamRec8::ParDump(TStringList *lst)
{
lst->Add("PenId="+String(FPenId));
lst->Add("Length="+String(FLength));
lst->Add("Width="+String(FWidth));
lst->Add("Kind="+String(FKind));
}

void __fastcall TDrwPageRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("FullName="+FFullName);
lst->Add("ShortName="+FShortName);
}

void __fastcall TDrwPageRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FFullName=lst->Values["FullName"];} catch (...) {FFullName="";}
try {FShortName=lst->Values["ShortName"];} catch (...) {FShortName="";}
}

void __fastcall TDrwClassesRec::Dump(TStringList *lst)
{
lst->Add("Id="+String(FId));
lst->Add("ObjClassId="+String(FObjClassId));
lst->Add("PropValueId="+String(FPropValueId));
lst->Add("PagesSet="+String(FPagesSet));
for (int i=0;i<MAXDRWPARAM;i++)
        lst->Add("DrwParamId"+String(i)+"="+String(FDrwParamId[i]));
lst->Add("Priority="+String(FPriority));
lst->Add("Condition="+FCondition);
}
void __fastcall TDrwClassesRec::LoadDump(TStringList *lst)
{
try {FId=lst->Values["Id"].ToInt();} catch (...) {FId=0;}
try {FObjClassId=lst->Values["ObjClassId"].ToInt();} catch (...) {FObjClassId=0;}
try {FPropValueId=lst->Values["PropValueId"].ToInt();} catch (...) {FPropValueId=0;}
try {FPagesSet=lst->Values["PagesSet"].ToInt();} catch (...) {FPagesSet=0;}
for (int i=0;i<MAXDRWPARAM;i++)
        try {FDrwParamId[i]=lst->Values["DrwParamId"+String(i)].ToInt();} catch (...) {FDrwParamId[i]=0;}
try {FPriority=lst->Values["Priority"].ToInt();} catch (...) {FPriority=0;}
try {FCondition=lst->Values["Condition"];} catch (...) {FCondition="";}
}
