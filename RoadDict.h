//---------------------------------------------------------------------------
#ifndef RoadDictH
#define RoadDictH
//---------------------------------------------------------------------------
// ���� ������ ��� ��������������� �������� ��������
// ������� ���������������� �� ����������� �� �����
// ��� ������� �������� � ���� �����, ���� �� ����������� ���������
// Wrote By Kirichenko K.D.
//---------------------------------------------------------------------------
#include <fstream.h>
#include "const.h"
#include <vcl.h>

class TFontRec
{
private:
        __int32 FId;
        LOGFONT FLog;
public:
        virtual void __fastcall Dump(TStringList *lst);
        __fastcall TFontRec(__int32 id,void *font);
};

// ������ �������������� ��������

#define MAXOBJPROPCOUNT 32
#define PR_NECESSARY 1
#define PR_PUBLISHED 2
#define PR_READONLY  4


class TObjMetaClass : public TObject
{
private:
String FTitle;  // �������� ������ �������� (����. ����������)
String FOneTitle; // �������� ������� � ��. �����
__int32 FId;    // �������������
__int32 FParentId; // ������������� ��������
__int32 FFlags; // ����� ������� (1 - ������������ � RSign)
String FClassName;                   // ��� ������ �������
String FSql;                         // Sql ������ ��� �������� �������
String FSqlSave;                     // Sql ������ ��� ���������� �������
String FSqlAppend;                   // Sql ������ ��� ���������� �������
String FSqlDelete;                   // Sql ������ ��� �������� �������
String FTableName;                   // ��� ������� � ������� �������� �������
__int32 FPropCount;
__int32 FMainPropId;
__int32 FPropFlags[MAXOBJPROPCOUNT]; // ����� ������� ��������
__int32 FPropIds[MAXOBJPROPCOUNT];   // ������ ������� �� ��������������
__int32 __fastcall GetPropIds(int n)
        {if ((n>=0)&&(n<FPropCount))
                return FPropIds[n];
         return 0;}
__int32 __fastcall GetPropFlags(int n)
        {if ((n>=0)&&(n<FPropCount))
                return FPropFlags[n];
         return 0;}
public:
        virtual void __fastcall Dump(TStringList *lst);
        virtual void __fastcall LoadDump(TStringList *lst);
        virtual void __fastcall DumpProp(TStringList *lstprop,TStringList *lstflag);
        virtual void __fastcall LoadDumpProp(TStringList *lstprop,TStringList *lstflag);
        __fastcall TObjMetaClass(void)
                {}
        __fastcall TObjMetaClass(__int32 id)
                {FId=id;}
        __fastcall TObjMetaClass(__int32 id,__int32 parid,String title,String otitle)
                {FId=id;FParentId=parid;FTitle=title;FOneTitle=otitle;}
        void __fastcall SetSQL(String newsql,String sqlsave,String sqlapp,String sqdel)
                {FSql=newsql;FSqlSave=sqlsave;FSqlAppend=sqlapp;FSqlDelete=sqdel;}
        void __fastcall SetParams(String table,__int32 flags,String classname)
                {
                FTableName=table;
                FFlags=flags;
                FClassName=classname;
                }
        void __fastcall SetMainProp(__int32 mainprop)
                {FMainPropId=mainprop;}
        void __fastcall ClearPropeties(void)
                {
                FPropCount=0;
                FMainPropId=0;
                }
        bool __fastcall AddProperty(int flag,int id)
        {if (FPropCount<MAXOBJPROPCOUNT)
                {FPropFlags[FPropCount]=flag;
                 FPropIds[FPropCount]=id;
                 FPropCount++;
                 return true;
                }
        return false;
        }
        bool __fastcall ReplaceProperty(int n,int flag,int id)
        {
        if ((n<FPropCount)&&(n>=0))
                {FPropIds[n]=id,FPropFlags[n]=flag;return true;}
        return false;
        }
__property __int32 Id={read=FId};
__property __int32 ParentId={read=FParentId};
__property String Title={read=FTitle};
__property String OneTitle={read=FOneTitle};
__property __int32 Flags={read=FFlags};
__property __int32 MainPropId={read=FMainPropId};
__property String ClassName={read=FClassName};
__property __int32 PropCount={read=FPropCount};
__property __int32 PropIds[int]={read=GetPropIds};
__property __int32 PropFlags[int]={read=GetPropFlags};
__property String Sql={read=FSql};
__property String SqlSave={read=FSqlSave};
__property String SqlAppend={read=FSqlAppend};
__property String SqlDelete={read=FSqlDelete};
__property String TableName={read=FTableName};
};

#define TYPESCOUNT 6
const char TypesNames[TYPESCOUNT][32]={"��� ����������","������������","�������������","���������","������������","���������"};
enum TPropClassesType {prUnknown=0,prEnum=1,prInteger=2,prBoolean=3,prFloat=4,prString=5};
// ������ �������������� ������� ��������
class TPropClassesRec : public TObject
{
private:
    __int32 FId;       // �������������
    TPropClassesType FType; // ��� ��������������
    String FClassName; // ��� �������� � ������ C++
    String FShortName; // ����������� �������� ��������������
    String FPropName;  // �������� �������������� �������
    String FFieldName; // ��� ���� � ������� ��� �������� �������� �� ����
friend class TDictSource;
    void __fastcall ChangeId(__int32 newid)
        {FId=newid;}
public:
    virtual void __fastcall Dump(TStringList *lst);
    virtual void __fastcall LoadDump(TStringList *lst);
    void __fastcall SetValue(String propname,String shortname,String classname,String fieldname,TPropClassesType type)
        {FPropName=propname;FShortName=shortname;FClassName=classname;FFieldName=fieldname;FType=type;}
    __fastcall TPropClassesRec(void)
        {}
    __fastcall TPropClassesRec(__int32 id)
        {FId=id;}
    __fastcall TPropClassesRec(String nm,String st,__int32 id)
        {FPropName=nm.Trim();FShortName=st;FId=id;}
    __property __int32 Id={read=FId};
    __property String PropName={read=FPropName};
    __property String ShortName={read=FShortName};
    __property String ClassName={read=FClassName};
    __property TPropClassesType Type={read=FType};
    __property String FieldName={read=FFieldName};
};
// ������ ������� �������� ��������� ������� ��������
class TTextPropRec : public TObject
{
private:
    String FText;        //�������� �������������� �� ������
    String FShortText;   //����������� ��������
    __int32 FPropId;     //������������� �������������� � ������ ��������� ��������
    __int32 FId;         //�������������
    __int32 FTag;
friend class TDictSource;
    void __fastcall ChangePropId(__int32 newid)
        {FPropId=newid;}
public:
virtual void __fastcall Dump(TStringList *lst);
virtual void __fastcall LoadDump(TStringList *lst);
    __fastcall TTextPropRec(void) {}
    __fastcall TTextPropRec(__int32 id,__int32 pid,String t,String st)
        {FId=id;FPropId=pid;FText=t.Trim();FShortText=st.Trim();}
__property __int32 Id={read=FId};
__property __int32 PropId={read=FPropId};
__property String Text={read=FText};
__property String ShortText={read=FShortText};
__property int Tag={read=FTag,write=FTag};
};

// ������ �������������� �������� �����������
// ��������.
// 1 --- ����������� �������������� �������� ����� � ������
// 2 --- ����������� ���������
// 3 --- ����������� ����� �������� �����
class TDrwProcRec : public TObject
{
private:
    String FName;      //��� ���������
    __int32 FId;       //�������������
public:
virtual void __fastcall Dump(TStringList *lst);
virtual void __fastcall LoadDump(TStringList *lst);
    __fastcall TDrwProcRec() {}
    __fastcall TDrwProcRec(__int32 id,String nm)
        {FId=id;FName=nm;}
__property __int32 Id={read=FId};
__property String Name={read=FName};
};
// ������ ���������� �������� �����������
// ��� ������ ��������� ���� ����� ����� �������� �����������
class TDrwParamRec : public TObject
{
protected:
    __int32 FId;       //������������� ������
    __int32 FProcId;   //������������� ���������
    __int32 FPenId;    //������������� ����
    __int32 FWidth;  // ������� ����� 0.1 �� � �������� �����
    TScaleKind FScaleKind; //������ ���������������
    int FStyleCount;
    unsigned long FStyles[8];
    String __fastcall GetStyle(void);
    unsigned long * __fastcall GetStyles(void)
        {return FStyles;}
public:
void __fastcall SetStyle(String);
void __fastcall SetPenId(__int32 penid)
    {FPenId=penid;}
void __fastcall SetPen(__int32 penid,__int32 wid,TScaleKind scale)
    {FPenId=penid;FWidth=wid;FScaleKind=scale;}
virtual void __fastcall Dump(TStringList *lst);
virtual void __fastcall LoadDump(TStringList *lst);
virtual void __fastcall ParDump(TStringList *lst)
    {}
virtual void __fastcall LoadParDump(TStringList *lst)
    {}
    __fastcall TDrwParamRec(void) {}
    __fastcall TDrwParamRec(__int32 id,__int32 pid)
        {FId=id;FProcId=pid;FStyleCount=0;FScaleKind=skByX;FWidth=0;}
__property __int32 Id={read=FId};
__property __int32 ProcId={read=FProcId};
__property __int32 PenId={read=FPenId};
__property __int32 Width={read=FWidth};
__property TScaleKind ScaleKind={read=FScaleKind};
__property String Style={read=GetStyle};
__property int StyleCount={read=FStyleCount};
__property long* Styles={read=GetStyles};
};

class TDrwParamRecB : public TDrwParamRec
{
protected:
__int32 FBrushId;
public:
__fastcall TDrwParamRecB(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {}
__fastcall TDrwParamRecB(void) : TDrwParamRec()
        {}
void __fastcall SetBrushId(__int32 brid)
        {FBrushId=brid;};
__property __int32 BrushId={read=FBrushId};
};

// ����� ���������� ��� ������� ��������� ���������� ������� ������
// � �������� �������
class TDrwParamRec1 : public TDrwParamRecB
{
private:
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec1(void) : TDrwParamRecB() {}
    __fastcall TDrwParamRec1(__int32 id,__int32 pid) : TDrwParamRecB(id,pid)
        {FPenId=0;FBrushId=0;}
    __fastcall TDrwParamRec1(__int32 pi,__int32 bi,__int32 id,__int32 pid)
        : TDrwParamRecB(id,pid)
        {FPenId=pi;FBrushId=bi;}
};

// ����� ���������� ��� ��������� ������� ��������� �������� �������
// ���� ������� ����� 0, �� ������� ������������� �� ����
// ���� ScaleKind ��������� �� ������ ���������������
class TDrwParamRec2 : public TDrwParamRec
{
private:
    __int32 FOffset;
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec2(void) : TDrwParamRec() {}
    __fastcall TDrwParamRec2(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {FPenId=0;FOffset=0;}
    __fastcall TDrwParamRec2(__int32 pi,__int32 id,__int32 pid,__int32 ofs)
        : TDrwParamRec(id,pid)
        {FPenId=pi;FOffset=ofs;}
void __fastcall SetOffset(__int32 ofs)
    {FOffset=ofs;}
__property __int32 Offset={read=FOffset};
};

// ����� ���������� ��� ��������� ���������
class TDrwParamRec3: public TDrwParamRec
{
private:
    __int32 FMeasure; // ������ ������� ��������� 0 -- � 0.1 �� �� ������ 1 -- � �� �� ���������
    __int32 FMetaId; // ������������� ���������
    __int32 FDX;     // �������� �� ������
    __int32 FDY;     // ��� ���������� � 0.1 �� �� ������
//    __int32 FWidth; // ����� � ������ ��������������� ��������������
    __int32 FHeight;  // FWidth �������� � ������
    TRect FDataRect;  // ������ ���������� ����� ���-�� ����������
                      // ��� ������������� ������� ������
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec3(void) : TDrwParamRec()
        {}
    __fastcall TDrwParamRec3(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {FMeasure=0;FMetaId=0;FWidth=0;FHeight=0;FDX=0;FDY=0;}
    __fastcall TDrwParamRec3(__int32 meas,__int32 mid,__int32 w,__int32 h,__int32 dx,__int32 dy,__int32 id,__int32 pid)
        : TDrwParamRec(id,pid)
        {FMeasure=meas;FMetaId=mid;FWidth=w;FHeight=h;FDX=dx;FDY=dy;
         FDataRect=TRect(0,0,w,h);
        }
__property __int32 Measure={read=FMeasure};
__property __int32 MetaId={read=FMetaId};
__property __int32 DX={read=FDX};
__property __int32 DY={read=FDY};
__property __int32 Height={read=FHeight};
__property TRect DataRect={read=FDataRect,write=FDataRect};
};

//����� ���������� ��� ��������� ������
class TDrwParamRec4 : public TDrwParamRec
{
private:
    __int32 FTaleLength; // ����� ������� �� ����� � 0.1 �� � ��������
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec4(void) : TDrwParamRec() {}
    __fastcall TDrwParamRec4(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {FPenId=0;FTaleLength=0;}
    __fastcall TDrwParamRec4(__int32 id,__int32 pid,__int32 lenght) : TDrwParamRec(id,pid)
        {FTaleLength=lenght;}
__property __int32 TaleLength={read=FTaleLength};
};

// ����� ���������� ��� ��������� ����������� ����� ��������� �������
// ����� ������� �� ������� ��������� �������. ������������ ������� �����������
// ������, ������� - �����.
class TDrwParamRec5: public TDrwParamRecB
{
private:
__int32 FShift;  // �������� ������������ ����� � 0.1 ��
__int32 FDash;   // ����� ������ � 0.1 ��
__int32 FSpace;  // ����� ������� � 0.1 ��
__int32 FOffset;   // �������� �� ������ ����� �� ������ ������
bool FScaleable;   // true - ���� ����� ������ ���������� � ������������ �������. ��� ����
                   // ������ ����� ���� ���������.
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
void __fastcall SetDrawParam(__int32 pen,__int32 brush)
        {FPenId=pen;FBrushId=brush;}
void __fastcall SetLineParam(__int32 width,__int32 shift)
        {FWidth=width;FShift=shift;}
void __fastcall SetDashParam(__int32 dash,__int32 space,__int32 offset,bool scaleable)
        {FDash=dash;FSpace=space;FOffset=offset;FScaleable=scaleable;}
    __fastcall TDrwParamRec5(void) : TDrwParamRecB() {}
    __fastcall TDrwParamRec5(__int32 id,__int32 pid)
        : TDrwParamRecB(id,pid)
        {}
__property __int32 Shift={read=FShift};
__property __int32 Dash={read=FDash};
__property __int32 Space={read=FSpace};
__property __int32 Offset={read=FOffset};
__property bool Scaleable={read=FScaleable};
};
// ����� ���������� ��� ��������� ����� �� �������
class TDrwParamRec6:public TDrwParamRecB
{
private:
__int32 FKind;
__int32 FSize;
__int32 FOrSize;
__int32 FSpace;
__int32 FOffset;
__int32 FShift;
bool FScaleable;
public:
        virtual void __fastcall ParDump(TStringList *lst);
        virtual void __fastcall LoadParDump(TStringList *lst);
        void __fastcall SetFigureParam(__int32 kind,__int32 size,__int32 orsize)
            {FSize=size;FOrSize=orsize;FKind=kind;}
        void __fastcall SetDrawParam(__int32 pen,__int32 brush)
            {FBrushId=brush;FPenId=pen;}
        void __fastcall SetLineParam(__int32 space,__int32 offset,__int32 shift,bool scale)
            {FShift=shift;FSpace=space;FOffset=offset;FScaleable=scale;}
        __fastcall TDrwParamRec6(void) : TDrwParamRecB() {}
        __fastcall TDrwParamRec6(__int32 id,__int32 pid)
            :TDrwParamRecB(id,pid)
            {}
__property __int32 Shift={read=FShift};
__property __int32 Space={read=FSpace};
__property __int32 Kind={read=FKind};
__property __int32 Size={read=FSize};
__property __int32 OrSize={read=FOrSize};
__property __int32 Offset={read=FOffset};
};

class TDrwParamRec7 : public TDrwParamRec
{
private:
__int32 FShift;
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec7(void) : TDrwParamRec() {}
    __fastcall TDrwParamRec7(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {FPenId=0;FShift=0;}
    __fastcall TDrwParamRec7(__int32 pi,__int32 id,__int32 pid)
        : TDrwParamRec(id,pid)
        {FPenId=pi;FShift=0;}
    __fastcall TDrwParamRec7(__int32 pi,__int32 shift,__int32 id,__int32 pid)
        : TDrwParamRec(id,pid)
        {FPenId=pi;FShift=shift;}
    __property __int32 Shift={read=FShift,write=FShift};
};

class TDrwParamRec8 : public TDrwParamRec
{
private:
    __int32 FLength;
    __int32 FKind;   // ��� � ����� ����� 1 - ������ � ������ 2 -������ � ����� 3 - ���
public:
virtual void __fastcall ParDump(TStringList *lst);
virtual void __fastcall LoadParDump(TStringList *lst);
    __fastcall TDrwParamRec8(void) : TDrwParamRec() {}
    __fastcall TDrwParamRec8(__int32 id,__int32 pid) : TDrwParamRec(id,pid)
        {FPenId=0;FLength=0;}
    __fastcall TDrwParamRec8(__int32 pi,__int32 id,__int32 pid)
        : TDrwParamRec(id,pid)
        {FPenId=pi;FLength=0;}
    __fastcall TDrwParamRec8(__int32 pi,__int32 len,__int32 knd,__int32 id,__int32 pid)
        : TDrwParamRec(id,pid)
        {FPenId=pi;FLength=len;FKind=knd;}
    __property __int32 Length={read=FLength,write=FLength};
    __property __int32 Kind={read=FKind,write=FKind};
};

// ������ ������� �����������
class TDrwPageRec : public TObject
{
private:
__int32 FId;             //�������������
String FFullName;        //������ ��� ��������
String FShortName;       //������� ��� ��������
public:
virtual void __fastcall Dump(TStringList *lst);
virtual void __fastcall LoadDump(TStringList *lst);
__fastcall TDrwPageRec(void) : TObject()
    {}
__fastcall TDrwPageRec(__int32 id) : TObject()
    {FId=id;FFullName="";FShortName="";}
__fastcall TDrwPageRec(__int32 id,String fname,String sname) : TObject()
    {FId=id;FFullName=fname;FShortName=sname;}
__property __int32 Id={read=FId};
__property String FullName={read=FFullName};
__property String ShortName={read=FShortName};
};

// ������ ����������� ������������ ���������� ��������
// ���������� �����������. ������� �������, �������� � �����������
// �� �������� �������������� �� ������, ������������� ���������
// ����� ���������� ��� �����������
#define MAXDRWPARAM 4
class TDrwClassesRec : public TObject
{
private:
__int32 FId;             // �������������
__int32 FObjClassId;     // ������������� ���� �������
__int32 FPropValueId;    // ������������� �������� ��������
__int32 FDrwParamId[MAXDRWPARAM];     // ������������� ����������
__int32 FPriority;       // ��������� �����������
__int32 FPagesSet;       // ��������� ������� �����������
String FCondition;       // ������� ���������� ������� �����������
__int32 GetDrwParamId(int n)
        { if ((n>=0)&&(n<MAXDRWPARAM))
                return FDrwParamId[n];
        return 0;
        }
public:
virtual void __fastcall Dump(TStringList *lst);
virtual void __fastcall LoadDump(TStringList *lst);
__fastcall TDrwClassesRec(void) {}
__fastcall TDrwClassesRec(__int32 id)
        {FId=id;}
__fastcall TDrwClassesRec(__int32 id,__int32 cid,__int32 vid,__int32 pid,__int32 pr)
        {FId=id;FObjClassId=cid;FPropValueId=vid;FDrwParamId[0]=pid;FPriority=pr;
        for (int i=1;i<MAXDRWPARAM;i++)
                FDrwParamId[i]=0;
        FCondition="";
        }
__fastcall TDrwClassesRec(__int32 id,__int32 classid,__int32 propid,TDrwClassesRec *Rec)
        {
        FId=id;FObjClassId=classid;FPropValueId=propid;FPriority=Rec->Priority;
        FCondition=Rec->Condition;
        for (int i=0;i<MAXDRWPARAM;i++)
                FDrwParamId[i]=Rec->DrwParamId[i];
        }
void __fastcall SetDrwParam(int num,__int32 par)
        {if ((num>=0)&&(num<MAXDRWPARAM)) FDrwParamId[num]=par;}
void __fastcall SetDrwParam(__int32 p1,__int32 p2,__int32 p3,__int32 p4)
        {FDrwParamId[0]=p1;FDrwParamId[1]=p2;FDrwParamId[2]=p3;FDrwParamId[3]=p4;}
void __fastcall SetClassId(__int32 classid,__int32 propid)
        {FObjClassId=classid;FPropValueId=propid;}
void __fastcall SetPriority(__int32 prior)
        {FPriority=prior;}
void __fastcall SetPagesSet(__int32 pset)
        {FPagesSet=pset;}
__property __int32 Id={read=FId};
__property __int32 ObjClassId={read=FObjClassId};
__property __int32 PagesSet={read=FPagesSet};
__property __int32 PropValueId={read=FPropValueId};
__property __int32 DrwParamId[int]={read=GetDrwParamId};
__property __int32 Priority={read=FPriority};
__property String Condition={read=FCondition,write=FCondition};
};

#endif
