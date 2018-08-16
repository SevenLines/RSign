//---------------------------------------------------------------------------
#ifndef RoadObjH
#define RoadObjH
#include "RoadDict.h"                                        
#include "Lists.h"                                    
#include "Const.h"
#include "Metrics.h"
#include "Measures.h"
//---------------------------------------------------------------------------
// �������� �������� ���� �������� ��������
// Wrote By Kirichenko K.D.
//---------------------------------------------------------------------------

typedef String (__fastcall *GetTypeProc)(TObject*);
typedef void (__fastcall *SetStrValueProc)(TObject*,String);
typedef String (__fastcall *GetStrValueProc)(TObject*);
typedef void (__fastcall *SetBoolValueProc)(TObject*,bool);
typedef bool (__fastcall *GetBoolValueProc)(TObject*);
typedef void (__fastcall *SetFloatValueProc)(TObject*,double);
typedef double (__fastcall *GetFloatValueProc)(TObject*);
typedef void (__fastcall *SetIntValueProc)(TObject*,__int32);
typedef __int32 (__fastcall *GetIntValueProc)(TObject*);

#define DEFPROPERTY(Type,Name) protected:\
                               Type F##Name;\
                               __published:\
                               String __fastcall GetType##Name(void);\
                               Type __fastcall Get##Name(void);\
                               void __fastcall Set##Name(Type val);\
                               __property Type Name={read=F##Name}; \
                               protected:\

#define DEFPROPERTYRW(Type,Name) Type F##Name;\
                               __int32 FCode##Name;\
                               __published:\
                               String __fastcall GetType##Name(void);\
                               Type __fastcall Get##Name(void);\
                               void __fastcall Set##Name(Type val);\
                               __property Type Name={read=F##Name,write=Set##Name}; \
                               protected:\

#define IMPPROPERTY(Class,Type,Name) \
                               String __fastcall Class::GetType##Name(void)\
                               {return #Type;}\
                               Type __fastcall Class::Get##Name(void)\
                                {return F##Name;}\
                               void __fastcall Class::Set##Name(Type val)\
                                {F##Name=val;FModified=true;}\

#define CLASSESCOUNT 52
const char ClassesNames[CLASSESCOUNT][32]={"TRoadObject","TDescreetRoadObject",\
        "TDescreetDirRoadObject","TDescreetSideRoadObject",\
        "TContRoadObject","TBusStop",
        "TRoadSideObject","TLinearRoadSideObject",
        "TSquareRoadSideObject","TRoadPart",
        "TRoadBridge","TDangerPart",
        "TDangerSlope","TDangerCurve",
        "TRoadBridge","TSquareAttachObject",
        "TTown","TRoadAttach",
        "TCommRoadObject","TRailCross",
        "TRoadSign","TRoadBarrier",
        "TRoadMark","TRoadOut",
        "TRoadTube","TCommunication",
        "TObochina","TSquareCenterObject",
        "TRoadObstacle", "TCarePart", "TDTP",
        "TBandRoadPart","TRoadSignal","TDrainageObject",
        "TZemPolotno","TRoadDress","TRoadDefect",
        "TRoadDescription","TRoadWidthMeasure",
        "TSquareRoadSideObject_Kromka","TLinearCenterRoadObject",
        "TRoadCategory","TRoadLighting","TMoundHeight","TDivRoadPart",
        "TDangerVisMode","TDressLayer",
        "TDescreetCenterRoadObject","TMapObject",
        "TTrafficLight","TSpeedBump","TDescreetSideCenterRoadObject"};

class TRoad;
class TObjFrm;
class TDictSource;

enum TPlanKind {pkGorizontal,pkVertical};
enum TPlanDirect {pdDirect,pdUndirect};
enum TPtConvertMethod {pc1d,pc2d};

//����� ��������������
class TCharacter
{
private:
protected:
String FName; // �������� ��������������
virtual String __fastcall GetText(void) {return "";}
virtual void __fastcall PutText(String) {}
public:
__property String Text={read=GetText,write=PutText};
__property String Name={read=FName,write=FName};
};

class TIntCharacter : public TCharacter
{
private:
__int32 FValue;
protected:
virtual String __fastcall GetText(void)
    {return String(Value);}
virtual void __fastcall PutText(String s)
    {try {FValue=s.ToInt();} catch (...) {FValue=0;}}
public:
__fastcall TIntCharacter(String name,__int32 v)
    {FName=name,FValue=v;}
__property __int32 Value={read=FValue};
};

class TStringCharacter : public TCharacter
{
private:
String FValue;
protected:
virtual String __fastcall GetText(void)
    {return FValue;}
virtual void __fastcall PutText(String s)
    {FValue=s;}
public:
__fastcall TStringCharacter(String name,String value)
    {FName=name;FValue=value;}
};

class TCharList:public TObjList<TCharacter>
{
public:
bool __fastcall PutPropValue(String name,String value);
void __fastcall AddProperty(String name,String value);
String __fastcall GetPropValue(String name);
};


// ����������� �������� ������
const char RoadObjectInfo[]="����� ������ � �������� ������� �������� ��������.\
�������� ���� �������� L - ���������� �� ������ �������.\
������� ����� ������ �� ������������";

enum TLocalisation {locNone=0,locDescreet=1,locLinear=2,locSquare=3};

class TRoadObject : public TObject
{
protected:
bool FSelected;  // true ���� ������ �������
bool FModified;  // true ���� ������ ��� ������� -- ���� �� ������������

TRoadObject *FParent; // ��������� �� ��������
TRoadObject *FChild; // ��������� �� ������� ����
TRoadObject *FSibling; // ��������� �� �����. ������� ���� �� NULL;

__int32 FTag;    //��������� ���� ��� ������ ��������� �������� // ����� ���������� � �������� ������
__int32 FId;     //������������� �������
__int32 FDictId; //������������� ���� �� ��������������   (Id � ������� GDIObjType)
                 // TDictSource::ObjClasses->Items[FDictId]->Title
__int32 FDrwClassId; // ������������� ������ �����������. ������������� ����������
                     // SelectDrwParam
//__int32 FBaseId;     // ������������� ������� �� ���� ������
TCharList *FCharList;
TPolyline *FPoly;     // ������ �� ������� ������� (���� ����) ������� � ��������� �� ����!

DEFPROPERTYRW(__int32,L)
DEFPROPERTY(__int32,PrevId)     // ���������� Id ��� ����������� ��������
DEFPROPERTYRW(TSignTest,Test) //��������� ������ ��������
DEFPROPERTYRW(String,Note) // ����������� �������������� ��������


int __fastcall GetClassPropCount(void* MetaClass);
public:
virtual TLocalisation GetLocal(void) {return locNone;}
// �������, ������� ������ ���������� ����� ������ �������
void __fastcall PostSaveObject(void)
    {FModified=false;}
void __fastcall PostLoadObject(void)
    {FModified=false;}
virtual int __fastcall ComponentCount(void)  // ��� ��������, ��������� �� ������ ����� ������
    {return 0;}                              // �������� ��� ���������� ��������� - ����� ���������
void __fastcall AddChild(TRoadObject *ch);
void __fastcall RemoveChild(TRoadObject *ch);
void __fastcall PutProperty(String propname,String propvalue);
bool __fastcall PutPropValue(String propname,String propvalue);
String __fastcall GetPropValue(String propname);

int __fastcall GetPropCount(void);
String __fastcall GetPropName(int n);
// ��������� ���������� � ������ �����
// ��������� ������ �� ������
// ��������� ������ ������� �� �����
// ��������� ���������� ������� �� �����
void __fastcall Dump(TStringList*,TDictSource *Dict);
void __fastcall LoadDump(TStringList*,TDictSource *Dict);
void __fastcall BuildCard(TObjFrm *Card);
void __fastcall SaveCard(TObjFrm *Card);
void __fastcall UpdateCard(TObjFrm *Card);

__fastcall TRoadObject(__int32 id,__int32 code)
    {FId=id;FDictId=code;FSelected=false;FModified=true;FPrevId=0;FCharList=new TCharList;FPoly=NULL;
     FSibling=NULL;FParent=NULL;FChild=NULL;
    }

__fastcall TRoadObject()
    {
    FId=0;
    FDictId=0;
    FPrevId=0;
    FModified=true;
    FSelected=false;
    FCharList=new TCharList;
    FPoly=NULL;
    FSibling=NULL;
    FParent=NULL;
    FChild=NULL;
    }
__fastcall ~TRoadObject()
    {
    delete FCharList;
    delete FPoly;
    }

void __fastcall SetDictId(__int32 newdid)
    {
    if (newdid)
        FDictId=newdid;
    }
void __fastcall SetId(__int32 newid)
    {if (!FId)
        FId=newid;
    }
// ������� ������� ������ ����� ��� ������������ �����������
// n - ����� �����, Road - ������ ������. �� ������ ����������� ��� �������
// ������ � ��������� ������ ��� ����� ������, ������� ����� �� ������
virtual  TExtPolyline* __fastcall GetDefMetric(TRoad *Road)
    {return NULL;}
virtual TExtPolyline* __fastcall GetPolyMetric(TRoad* Road);
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p) {return false;}
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road) {return 0;}
virtual TExtPolyline* PrepareMetric(TRoad *Road);
virtual void __fastcall UpdatePoly(void);
virtual void __fastcall PostEditPoly(void)
    {FModified=true;UpdatePoly();}
// ������� ���������� ���������� �������� ��� �����������.
virtual int __fastcall GetTextsCount(void)
        {return 0;}
// ������� ���������� ������� ������� ���� ����������. ��� ������� ����������
// ��������� ���, �������� 0,1 �.�.�. ����� ��� ������� �������� ������ ������� 0
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict)
        {return NULL;}
virtual __int32 __fastcall getLMax(void) {return FL;}
String __fastcall FormatPlacement(int p);
void __fastcall MarkTagByTree(int);
__property __int32 Id={read=FId};
__property __int32 DictId={read=FDictId};
__property __int32 DrwClassId={read=FDrwClassId,write=FDrwClassId};
__property bool Modified={read=FModified};
__property bool Selected={read=FSelected,write=FSelected};
__property TCharList *CharList={read=FCharList};
__property TPolyline* Poly={read=FPoly,write=FPoly};
__property __int32 LMax={read=getLMax};
__property TRoadObject* Parent={read=FParent, write=FParent};
__property TRoadObject* Child={read=FChild, write=FChild};
__property TRoadObject* Sibling={read=FSibling, write=FSibling};
__property __int32 Tag={read=FTag,write=FTag};
};

// �������� ������ � �������� ������������


const char DescreetRoadObjectInfo[]="�������� ������ � �������� ������������. ���������� ��\
TRoadObject. ����� ������� �� ��������. ������� ����� ������ �������� ������� �� �����\
�����, ������� �� ������ ����� ������ �� �������� ���������� �� ������ ������.";

class TDescreetRoadObject :  public TRoadObject
{
protected:
public:
__fastcall TDescreetRoadObject(): TRoadObject() {}
__fastcall TDescreetRoadObject(__int32 id,__int32 code) : TRoadObject(id,code) {}
virtual TLocalisation GetLocal(void) {return locDescreet;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char MoundHeightInfo[]="������ �������� ������ ������, ���������� � �����.\
���������� �� TDescreetRoadObject. �������� ��� ����� ��������.\
Placement - ������������ (�����, ������). Height - ������ � �����������";
;

class TMoundHeight : public TDescreetRoadObject {
protected:
   DEFPROPERTY(TRoadSide,Placement)
   DEFPROPERTY(__int32,Height)
public:
__fastcall TMoundHeight(): TDescreetRoadObject() {}
__fastcall TMoundHeight(__int32 id,__int32 code) : TDescreetRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
    {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

// �������� ������ � �������� ������������ ����������� � ������ ������
// � ������� ����������� (������ - ��������)

const char DescreetDirRoadObjectInfo[]="�������� ������ � �������� ������������ � ������������.\
���������� �� TDescreetRoadObject. �������� ��� ����� ��������. DX - ��c������� �� ������ ������.\
Direction - ����������� (������, ��������). ������� �������� ���� �����, ������� ������\
�� ������ (� ������ �����������) �� ���������� DX �� ������";

class TDescreetDirRoadObject : public TDescreetRoadObject
{
protected:
DEFPROPERTY(TRoadDirection,Direction)
DEFPROPERTYRW(__int32,DX)
public:
__fastcall TDescreetDirRoadObject():TDescreetRoadObject() {}
__fastcall TDescreetDirRoadObject(__int32 id,__int32 code):TDescreetRoadObject(id,code)  {}
void __fastcall PutPosition(__int32 l,__int32 x,TRoadDirection dir)
    {FL=l;FDX=x;FDirection=dir;FModified=true;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p);
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road);
};

// �������� ������ � �������� ������������ ����������� � ������ ������
// � ������������� ����� ��� ������ �� ������.

const char DescreetSideRoadObjectInfo[]="�������� ������ � �������� ������������, ������������� ����� ��� ������ �� ������.\
���������� �� TDescreetRoadObject. �������� ��� ����� ��������. DX - ��c������� �� ������ ������.\
Placement - ������������ (�����, ������). ������� �������� ���� �����, ������� � ��������� �������\
�� ������ (� ������ �����������) �� ���������� DX �� ������";

class TDescreetSideRoadObject : public TDescreetRoadObject
{
private:
DEFPROPERTY(TRoadSide,Placement)
DEFPROPERTY(__int32,DX)
public:
__fastcall TDescreetSideRoadObject():TDescreetRoadObject() {}
__fastcall TDescreetSideRoadObject(__int32 id,__int32 code):TDescreetRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p);
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road);
};

const char DescreetCenterRoadObjectInfo[]="�������� ������ � �������� ������������, � ��������� � ��� ������\
���������� �� TDescreetRoadObject. �������� ��� ����� ��������. DX - ��c������� �� ������ ������.\
Placement - ������������ (�����, ������). ������� �������� ���� �����, ������� � ��������� �������\
�� ������ (� ������ �����������) �� ���������� DX �� ��� ������";

class TDescreetCenterRoadObject : public TDescreetRoadObject
{
private:
DEFPROPERTYRW(__int32,DX)
public:
__fastcall TDescreetCenterRoadObject():TDescreetRoadObject() {}
__fastcall TDescreetCenterRoadObject(__int32 id,__int32 code):TDescreetRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road);
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p)
   {if (p && p->Count>0) DX=p->Points[0].X; return true;}
};


// ��� ���������� ������
const char DescreetSideCenterRoadObject[]="��������� ���. ���������� �� TDescreetSideRoadObject\
��������� ����������� ���������� �� �������������� ������";

class TDescreetSideCenterRoadObject : public TDescreetSideRoadObject {
private:
public:
__fastcall TDescreetSideCenterRoadObject() : TDescreetSideRoadObject() {FDX=350;}
__fastcall TDescreetSideCenterRoadObject(__int32 id,__int32 code) : TDescreetSideRoadObject(id,code) {FDX=350;}
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p);
};

// ����� ���������
const char RoadLightingInfo[]="����� �������� ���������. ���������� �� TDescreetSideRoadObject\
��������� ��������� ������������.";

class TRoadLighting : public TDescreetSideCenterRoadObject {
private:
DEFPROPERTY(TLampKind,Kind)
public:
__fastcall TRoadLighting() : TDescreetSideCenterRoadObject() {FDX=350;}
__fastcall TRoadLighting(__int32 id,__int32 code) : TDescreetSideCenterRoadObject(id,code) {FDX=350;}
};


const char BusStopInfo[]="���������� ���������. ������ ���������� �� TDescreetSideRoadObject.\
�������� ��� ����� ��������. Name - �������� ���������. bool StopArea - ������� ������������\
��������. bool Pavilion - ������� ���������. ��������� ��������� ������������.";

class TBusStop : public TDescreetSideRoadObject
{
private:
DEFPROPERTY(String,Name)
DEFPROPERTY(bool,StopArea)
DEFPROPERTY(bool,Pavilion)
public:
__fastcall TBusStop() : TDescreetSideRoadObject() {FDX=350;}
__fastcall TBusStop(__int32 id,__int32 code) : TDescreetSideRoadObject(id,code) {FDX=350;}
};

const char SpeedBumpInfo[]="������� �����������";

class TSpeedBump : public TDescreetRoadObject {
public:
    __fastcall TSpeedBump(): TDescreetRoadObject() {}
    __fastcall TSpeedBump(__int32 id,__int32 code) : TDescreetRoadObject(id,code) {}
    virtual TLocalisation GetLocal(void) {return locLinear;}
    virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char RoadTubeInfo[]="�����";
class TRoadTube : public TDescreetRoadObject
{
private:
DEFPROPERTY(int,Length)
DEFPROPERTY(TTubePlacement,Placement)
DEFPROPERTY(String,Scheme)
public:
__fastcall TRoadTube(): TDescreetRoadObject() {}
__fastcall TRoadTube(__int32 id,__int32 code) : TDescreetRoadObject(id,code) {}
virtual TLocalisation GetLocal(void) {return locLinear;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
    {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

const char RoadWidthMeasureInfo[]="����� ��������� ������ ������";
class TRoadWidthMeasure : public TDescreetRoadObject
{
public:
__fastcall TRoadWidthMeasure(): TDescreetRoadObject() {}
__fastcall TRoadWidthMeasure(__int32 id,__int32 code) : TDescreetRoadObject(id,code) {}
virtual TLocalisation GetLocal(void) {return locLinear;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
    {return 2;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

// �������� ������ � �� ���������� ������������
const char ContRoadObjectInfo[]="�������� ������, ������� ������ ����������� � �����.\
���������� �� TRoadObject. �������� L ���������� ������ �����������. �������� ��������\
LMax - ����� �����������. ������� ����� ������ �� ������������.";
class TContRoadObject : public TRoadObject
{
protected:
DEFPROPERTY(__int32,LMax)
public:
__fastcall TContRoadObject(): TRoadObject() {}
__fastcall TContRoadObject(__int32 id,__int32 code): TRoadObject(id,code) {}
void __fastcall PutPosition(__int32 min,__int32 max)
    {FL=min;FLMax=max;FModified=true;}
virtual __int32 __fastcall getLMax(void) {return FLMax;}    
virtual void __fastcall UpdatePoly(void);
__property __int32 LMin={read=FL};
virtual TLocalisation GetLocal(void) {return locLinear;}
};

const char CommunicationInfo[]="";
class TCommunication : public TContRoadObject
{
protected:
DEFPROPERTY(TCommunicationPlacement,Placement)
DEFPROPERTY(TGroundPlacement,PlaceGround)
DEFPROPERTY(TCommunicationKind,CommKind)
public:
__fastcall TCommunication(): TContRoadObject() {}
__fastcall TCommunication(__int32 id,__int32 code): TContRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};


const char DressLayerInfo[]="";
class TDressLayer : public TContRoadObject {
protected:
DEFPROPERTY(TLayer,Layer)
DEFPROPERTY(__int32,UpperDeep)
DEFPROPERTY(__int32,LowerDeep)
public:
__fastcall TDressLayer(): TContRoadObject() {}
__fastcall TDressLayer(__int32 id,__int32 code): TContRoadObject(id,code) {}
//virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
} ;


// �������� ������ ����������� � ������ ������
const char RoadSideObjectInfo[]="�������� ������, ����������� � ������ ��� ������ ������. ���������� ��\
TContRoadObject. �������� ��� ����� �������� DX - ���������� �� ������ ������.\
Placement - ��� ������������ (�����, ������, �� �������������� ������).\
������� ����� ���� �� ������������";
class TRoadSideObject : public TContRoadObject
{
protected:
DEFPROPERTYRW(__int32,DX)                   // ���������� �� ������ ������
DEFPROPERTYRW(TObjPlacement,Placement)      // ����������� ������������ (����� ������ �����)
DEFPROPERTYRW(TMetricsKind,MetricsKind)            // ������ ��� ������
virtual TPolyline* __fastcall GetAttachPoly(TRoad *Road);
public:
__fastcall TRoadSideObject():TContRoadObject() {}
__fastcall TRoadSideObject(__int32 id,__int32 code):TContRoadObject(id,code)
    {FDX=0;FPlacement=TObjPlacement(0);FMetricsKind=TMetricsKind(0);}
};

// �������� ������ � �������� ������������
// ����������� � ������ ������
const char LinearRoadSideObjectInfo[]="�������� ������, ����������� � ������ ��� ������ ������, ��������������\
������. ���������� �� TRoadSideObject. ������� ������� �������� ������ ������������� ��\
���������� DX �� ������ ������ ��� ������ ������ � ����������� �� ������������ � ������������ ��.";
class TLinearRoadSideObject : public TRoadSideObject
{
private:

public:
__fastcall TLinearRoadSideObject():TRoadSideObject() {}
__fastcall TLinearRoadSideObject(__int32 id,__int32 code):TRoadSideObject(id,code)  {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
};
// ������ ��������

const char MapObjectInfo[]="";
class TMapObject : public TLinearRoadSideObject {
private:
DEFPROPERTY(String,Title)
public:
__fastcall TMapObject():TLinearRoadSideObject() {}
__fastcall TMapObject(__int32 id,__int32 code):TLinearRoadSideObject(id,code)
    {FDX=800;FMetricsKind=mkKromka;}
virtual int __fastcall GetTextsCount(void)
    {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

// ������������ ����������
const char DrainageObjectInfo[]="";
class TDrainageObject : public TLinearRoadSideObject
{
private:
DEFPROPERTY(TDrainageKind,Kind)
public:
__fastcall TDrainageObject():TLinearRoadSideObject() {}
__fastcall TDrainageObject(__int32 id,__int32 code):TLinearRoadSideObject(id,code)
    {FDX=100;}
};

const char RoadDefectInfo[]="";
class TRoadDefect : public TContRoadObject
{
DEFPROPERTY(TDefectKind,Kind)
DEFPROPERTY(TRoadSide,Placement)
public:
__fastcall TRoadDefect():TContRoadObject() {}
__fastcall TRoadDefect(__int32 id,__int32 code):TContRoadObject(id,code)
    {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

// �������� ������ � �������� ������������ �������������
// �������� ������ ����������� � ������ ������
// ������ �� ���������� � ��������

const char FixedRoadObjectInfo[]="";
class TFixedRoadObject : public TContRoadObject
{
public:
__fastcall TFixedRoadObject(__int32 id,__int32 code):TContRoadObject(id,code) {}

};

// �������� ������ � �������� ������������ ������������� ������,
// ����������� �� ������ ������������ �������� ������� �� ������ ������
// ��� �������� �� ���� ;) (����� ����, ���� �� ����...)

const char RoadMarkInfo[]="";
class TRoadMark : public TContRoadObject
{
protected:
DEFPROPERTYRW(int, Length)   // �����
DEFPROPERTYRW(int, Area)   // �������
DEFPROPERTYRW(int, Offset)   // ��������
DEFPROPERTYRW(int, K)        // �����������.
DEFPROPERTY(TRoadDirection,Direction) // �����������
DEFPROPERTY(TMarkKind,Kind)  // ��� ��������
// �������������� ������������ �� ������� Width*K/1000+Offset, ���
// Width ��� ���������� �� ������ ������ �� ������
public:
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
__fastcall TRoadMark():TContRoadObject() {};
__fastcall TRoadMark(__int32 id,__int32 code):TContRoadObject(id,code) {};
virtual int __fastcall GetTextsCount(void)
    {return 3;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

//�������� ������ ��������� �����������, ����������� � ������ � ����� �������
const char SquareRoadSideObjectInfo[]="�������� ������ ��������� ����������� �����������\
� ������ ������ � ����� ������� � �������� � ������������� � ������. ���������� ��\
TRoadSideObject. ������� ������� �� �������� � ����� ������� ������������ � ������ ��\
���������� DX � ����������� �� ������������, � ����� �� �������� �� ���������� Width\
�������, � ����� - �� ������ � ����� �����������.";
class TSquareRoadSideObject : public TRoadSideObject
{
protected:
DEFPROPERTY(__int32,Width)
public:
__fastcall TSquareRoadSideObject():TRoadSideObject() {};
__fastcall TSquareRoadSideObject(__int32 id,__int32 code):TRoadSideObject(id,code) {};
virtual TExtPolyline* __fastcall GetPolyMetric(TRoad* Road);
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

const char SquareRoadSide_KromkaInfo[]="";
class TSquareRoadSideObject_Kromka : public TSquareRoadSideObject
{
protected:
public:
__fastcall TSquareRoadSideObject_Kromka():TSquareRoadSideObject()
    {FMetricsKind=mkKromka;}
__fastcall TSquareRoadSideObject_Kromka(__int32 id,__int32 code):TSquareRoadSideObject(id,code)
    {FMetricsKind=mkKromka;}
};

// �������
const char ObochinaInfo[]="";
class TObochina : public TContRoadObject
{
DEFPROPERTY(TRoadSide,Placement)
DEFPROPERTY(__int32,DX)
public:
__fastcall TObochina():TContRoadObject() {};
__fastcall TObochina(__int32 id,__int32 code):TContRoadObject(id,code) {};
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

// �������� ������ � �������� ������������, �� ���������
// �� ������ (���� �������� ���)

const class TLinearRoadObject : public TContRoadObject
{
protected:
public:
};

//������� ������
//������� �������������� ��� �������� �������������� �� �������
// ������� ������� (����, �� ��������� ��������, �������� �������������)
const char RoadPartInfo[]="������ ������� ������. ���������� �� TContRoadObject.\
������� ������� �� ��������, ������������� � ���� ������ ������ ������, � � ����\
������ ������������� ������� � ������ ������ � ����� �������.";

class TRoadPart : public TContRoadObject
{
protected:
int FLineBound;
public:
__fastcall TRoadPart(): TContRoadObject() {};
__fastcall TRoadPart(__int32 id,__int32 code): TContRoadObject(id,code)
    {FLineBound=4;};
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

const char RoadDressInfo[]="�������� ������";
class TRoadDress : public TRoadPart
{
DEFPROPERTY(TDressMaterial,Material)
DEFPROPERTY(int,Height)
DEFPROPERTY(TLayerKind,LayerKind)
DEFPROPERTY(int,LayerNum)
public:
__fastcall TRoadDress(): TRoadPart() {};
__fastcall TRoadDress(__int32 id,__int32 code): TRoadPart(id,code) {}
};

const char RoadDescriptionInfo[]="";
class TRoadDescription: public TRoadPart
{
DEFPROPERTY(String,Description)
DEFPROPERTY(String,BeginName)
DEFPROPERTY(String,EndName)
public:
__fastcall TRoadDescription(): TRoadPart() {};
__fastcall TRoadDescription(__int32 id,__int32 code): TRoadPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
virtual int __fastcall GetTextsCount(void)
        {return 2;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

const char RoadCategoryInfo[]="������� ������ �� ����������� ���������";
class TRoadCategory: public TRoadPart
{
protected:
DEFPROPERTY(TRoadClass,Value)
public:
__fastcall TRoadCategory(): TRoadPart() {}
__fastcall TRoadCategory(__int32 id,__int32 code): TRoadPart(id,code) {}
};

const char BandRoadPartInfo[]="";
class TBandRoadPart : public TRoadPart
{
protected:
DEFPROPERTY(__int32,Width)
DEFPROPERTY(__int32,EWidth)
public:
__fastcall TBandRoadPart(): TRoadPart() {}
__fastcall TBandRoadPart(__int32 id,__int32 code): TRoadPart(id,code) {}
};

const char DivRoadPartInfo[]="������ �������������� ������";
class TDivRoadPart : public TBandRoadPart
{
public:
__fastcall TDivRoadPart(): TBandRoadPart() {FLineBound=3;}
__fastcall TDivRoadPart(__int32 id,__int32 code): TBandRoadPart(id,code) {FLineBound=3;}
};


const char ZemPolotnoInfo[]="�������� �������";
class TZemPolotno : public TBandRoadPart
{
protected:
DEFPROPERTY(__int32,TopWidth)
public:
__fastcall TZemPolotno(): TBandRoadPart() {}
__fastcall TZemPolotno(__int32 id,__int32 code): TBandRoadPart(id,code)
    {FLineBound=2;}
};

const char SquareCenterObjectInfo[]="��������� �������� ������ ����������� �� ������ ������";
class TSquareCenterObject : public TBandRoadPart
{
protected:
public:
__fastcall TSquareCenterObject():TBandRoadPart() {}
__fastcall TSquareCenterObject(__int32 id,__int32 code):TBandRoadPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

const char LinearCenterObjectInfo[]="�������� �������� ������ ����������� �� ��� ������";
class TLinearCenterRoadObject : public TContRoadObject
{
protected:
public:
__fastcall TLinearCenterRoadObject():TContRoadObject() {}
__fastcall TLinearCenterRoadObject(__int32 id,__int32 code):TContRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

// ������� ������� ������ � ��������
const char DangerPartInfo[]="";
class TDangerPart : public TRoadPart
{
protected:
public:
__fastcall TDangerPart():TRoadPart() {};
__fastcall TDangerPart(__int32 id,__int32 code):TRoadPart(id,code) {};
};

const char DangerSlopeInfo[]="";
class TDangerSlope : public TDangerPart
{
private:
DEFPROPERTYRW(int,Promille)
DEFPROPERTYRW(int,Radius)
DEFPROPERTYRW(TPermiss,Permissible)
public:
__fastcall TDangerSlope():TDangerPart() {};
__fastcall TDangerSlope(__int32 id,__int32 code):TDangerPart(id,code) {};
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char DangerCurveInfo[]="";
class TDangerCurve : public TDangerPart
{
DEFPROPERTYRW(double, Radius)
DEFPROPERTYRW(TCurveKind, Kind)
DEFPROPERTYRW(TPermiss, Permissible)
public:
__fastcall TDangerCurve():TDangerPart() {}
__fastcall TDangerCurve(__int32 id,__int32 code):TDangerPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char DangerVisModeInfo[]="";
class TDangerVisMode : public TDangerPart {
DEFPROPERTYRW(__int32, Length)
DEFPROPERTYRW(TRoadDirection,Direction)
public:
__fastcall TDangerVisMode():TDangerPart() {}
__fastcall TDangerVisMode(__int32 id,__int32 code):TDangerPart(id,code) {}
};

const char CarePartInfo[]="������� ����� �� ������� ���������� ��������";
class TCarePart : public TRoadPart
{
private:
DEFPROPERTY(TDangPartKind,Reason)
DEFPROPERTY(TRoadSide,Placement)
DEFPROPERTY(double,NormaSquare)
DEFPROPERTY(double,HandlingSquare)
public:
__fastcall TCarePart():TRoadPart() {};
__fastcall TCarePart(__int32 id,__int32 code):TRoadPart(id,code) {};
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
    {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

const char RoadBridgeInfo[]="";
class TRoadBridge : public TRoadPart
{
private:
DEFPROPERTY(String,Scheme)                    // ����� �����
DEFPROPERTY(String,ObstacleName)              //��� ��������
DEFPROPERTY(TObstacleKind,ObstacleKind)        //��� ��������
DEFPROPERTY(__int32,Width)                    // ������ ����� � �����������
DEFPROPERTY(TBridgeKind,Kind)                 // ��� ����������� �����
DEFPROPERTY(TBridgeConstruction,Construction) // ��� ��������� ��������
DEFPROPERTY(TBridgeMaterial,Material)         //�������� ��������
DEFPROPERTY(__int32,Tonnage1)                 //� ������ ����� ����������������
DEFPROPERTY(__int32,Tonnage2)                 //� ������ ������
DEFPROPERTY(__int32,Tonnage3)                 //� ��������� �������
public:
__fastcall TRoadBridge():TRoadPart() {}
__fastcall TRoadBridge(__int32 id,__int32 code):TRoadPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
        {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

// ��������� ������ ��������� �� ������ � �������� � �������������, �������� ���.�����
const char SquareAttachObjectInfo[]="";
class TSquareAttachObject : public TContRoadObject
{
public:
__fastcall TSquareAttachObject():TContRoadObject() {}
__fastcall TSquareAttachObject(__int32 id,__int32 code):TContRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

const char TownInfo[]="";
class TTown : public TSquareAttachObject
{
protected:
DEFPROPERTY(String,Title)
public:
__fastcall TTown():TSquareAttachObject() {}
__fastcall TTown(__int32 id,__int32 code):TSquareAttachObject(id,code) {}
virtual int __fastcall GetTextsCount(void)
        {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

//-----------------------------------------------------
// �������� ����������
// ����� ����������
// ��������� ����� �������� ������ ��� �������� �������
const char RoadAttachInfo[]="";
class TRoadAttach : public TDescreetRoadObject
{
private:
DEFPROPERTY(TRoadClass,Tech)            // ��� ��������� ������
DEFPROPERTY(String,Name)                //������������ ����������
DEFPROPERTY(TAttachPlacement,Placement) //����������� ����������
DEFPROPERTYRW(int,Angle)                  // ���� ����������
DEFPROPERTY(int,Width)                  // ������ ����������� ������ � ����� ����������
DEFPROPERTY(String,Comment)             //������������ ����������
public:
__fastcall TRoadAttach():TDescreetRoadObject() {}
__fastcall TRoadAttach(__int32 id,__int32 code):TDescreetRoadObject(id,code)
    {FWidth=0;FAngle=0;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TExtPolyline* __fastcall GetPolyMetric(TRoad* Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
virtual int __fastcall GetTextsCount(void)
        {return 2;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
virtual int __fastcall DefaultWidth(void);
};
//-----------------------------------------------------
// �������� �������
// ����� �����
const char RoadOutInfo[]="";
class TRoadOut : public TRoadAttach
{
private:
DEFPROPERTY(TAttachWildness,Wildness)
DEFPROPERTY(TRoadSurface,Surface)
DEFPROPERTY(int,Length)
public:
__fastcall TRoadOut():TRoadAttach() {}
__fastcall TRoadOut(__int32 id,__int32 code):TRoadAttach(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

//-----------------------------------------------------
// ������� � ���� �����, ������������ ������
const char CommRoadObjectInfo[]="";
class TCommRoadObject: public TDescreetRoadObject
{
private:
public:
__fastcall TCommRoadObject():TDescreetRoadObject() {}
__fastcall TCommRoadObject(__int32 id,__int32 code):TDescreetRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
};

const char RailCrossInfo[]="";
class TRailCross : public TCommRoadObject
{
private:
DEFPROPERTY(TRailKind,RailKind)          // ����� �����
DEFPROPERTY(TRailCrossSignal,SignalKind)  // ��� ������������
DEFPROPERTY(int,RailCount)                // ����� �����
DEFPROPERTY(bool,Light)                   // ������� ����������������
DEFPROPERTY(bool,Guard)                   // ������� ������
public:
__fastcall TRailCross():TCommRoadObject() {}
__fastcall TRailCross(__int32 id,__int32 code):TCommRoadObject(id,code) {}
};

const char RoadObstacleInfo[]="";
class TRoadObstacle : public TCommRoadObject
{
private:
DEFPROPERTY(String,ObstacleName)              //��� ��������
DEFPROPERTY(TObstacleKind,ObstacleKind)        //��� ��������
DEFPROPERTY(__int32,Width)                    // ������ ����� � �����������
public:
__fastcall TRoadObstacle(): TCommRoadObject() {}
__fastcall TRoadObstacle(__int32 id,__int32 code):TCommRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

// ���������
const char TrafficLightInfo[]="��������";
class TTrafficLight : public TDescreetCenterRoadObject {
protected:
DEFPROPERTYRW(__int32,Direction)
DEFPROPERTYRW(TTrafficLightsPlacement,Placement)
DEFPROPERTYRW(TTrafficLightsKind,Kind)
public:
__fastcall TTrafficLight():TDescreetCenterRoadObject() {}
__fastcall TTrafficLight(__int32 id,__int32 code):TDescreetCenterRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};


// �������� �������� ������
// ��������� ����� ���� �������� ������ ��� �������� �������
const char RoadSignInfo[]="";
class TRoadSign : public TDescreetDirRoadObject
{
protected:
DEFPROPERTYRW(__int32,NumRoadSign)  // ����� ����� �� �������
DEFPROPERTYRW(__int32,ViewKind)   // ��� ��������� ������ �������������� ���� �����������
DEFPROPERTYRW(String,Label)      // ������� �� �����
DEFPROPERTYRW(TRoadSignPlacement,Placement)
DEFPROPERTYRW(String,OldTitle)
DEFPROPERTYRW(TSignAttach,OnAttach)
DEFPROPERTYRW(TSignBackColor,Color)
friend class TSignRules; void __fastcall SetAutoTest(TSignTest tst)
  {FTest=tst;}
void __fastcall SetAutoDescription(String s)
  {FNote=s;}
public:
__fastcall TRoadSign():TDescreetDirRoadObject() {}
__fastcall TRoadSign(__int32 id,__int32 code):TDescreetDirRoadObject(id,code) {}
// ������� ������� ���������� �����
// 0 - ��� �������� 3 - 90 �� �� ������� �������
// 2 - 180 ��. 1 - 90 �� ������ ������� �������
virtual int __fastcall GetSignDirection(TPlanKind pk,TPlanDirect pd);
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
void __fastcall SetAutoTest(TSignTest Tst,String note)
    {FTest=Tst;
     FNote=note;}
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p);
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road);
};

const char DTPInfo[]="";
class TDTP : public TDescreetRoadObject
{
protected:
DEFPROPERTY(__int32, CarCount)  // ���������� ����� � ���
public:
__fastcall TDTP():TDescreetRoadObject() {}
__fastcall TDTP(__int32 id,__int32 code): TDescreetRoadObject(id,code) {}
};

// ����� ����������
const char RoadBarrierInfo[]="";
class TRoadBarrier : public TLinearRoadSideObject
{
protected:
DEFPROPERTY(TBarrierConstruction,Construction) // ��� ����������� ����������
public:
__fastcall TRoadBarrier():TLinearRoadSideObject() {}
__fastcall TRoadBarrier(__int32 id,__int32 code):TLinearRoadSideObject(id,code) {}
};

// ���������� ����������
const char RoadSignalInfo[]="";
class TRoadSignal : public TLinearRoadSideObject
{
DEFPROPERTYRW(int,Count)
DEFPROPERTYRW(TRoadSignalKind,Kind)
public:
virtual int __fastcall ComponentCount(void) {return FCount;}
__fastcall TRoadSignal():TLinearRoadSideObject() {}
__fastcall TRoadSignal(__int32 id,__int32 code):TLinearRoadSideObject(id,code) {}
};


//������� ������������ � ���� ������ ���������� ������
//������ �������� � ���� ���� �����. � ���� ��������
//��������� L_{n+1}>=L_{n}
//���� ������������ �������� �������� ���� ������.
class TBandRoadObject : public TContRoadObject
{
protected:
public:
__fastcall TBandRoadObject(__int32 id,__int32 code):TContRoadObject(id,code)
        {}
TPolyline LeftLine; // ����� ������ ������ (���� ��������)
TPolyline RightLine; // ������ ������ ������
};

//������ �������
class TRoad :public TBandRoadObject
{
private:
// ����� ������ �� ������
__int32 FXMin,FXMax;
__int32 FOutYMin,FOutYMax,FOutXMin,FOutXMax;
// ������� ������ � ���� FrameLPos ��������� �������
__int32 FFrameLMin,FFrameLMax,FFrameXMin,FFrameXMax,FFrameLPos;
__int32 FZMin,FZMax;
// ���������� ����� ��������� ������� � �� ��� �������������
__int32 FStep;
double FKx,FKl;
__int32 FGeoXMin,FGeoXMax,FGeoYMin,FGeoYMax;
double FGeoKx,FGeoKy;
TPlanKind FPlKind;
TPlanDirect FPlDirect;
TPtConvertMethod FConvertMethod;
void __fastcall CalcConvertion(void);
void __fastcall SetPlanKind(TPlanKind pk);
void __fastcall SetPlanDirect(TPlanDirect pd);
protected:

public:
TPolyline LeftSide; // ����� ������ ������
TPolyline RightSide;  // ������ ������ ������
TPolyline LeftZem; // ����� ���� ��� �������
TPolyline RightZem; // ������ ���� ��� �������
TPolyline LeftDivPart; // ���� �������������� ������ �����
TPolyline RightDivPart; // ���� �������������� ������ ������
TPolyline LeftBound;    // ������� ����������� ����� ������ � ������ ������������
TPolyline RightBound;   // ������� ����������� ����� ������ � ������ ������������

TCurvePlan CurvePlan;   // ������������� ���� ������
// ������� ���������� ����� �� ������������� ����� ������
void __fastcall CalcCurvePlanPoints(void);

TRoadGeometry Geometry; // ���������� ������� ������
bool GeometryMoved;     // true ����� �������������� �������������� ����������
__fastcall TRoad(__int32 id,__int32 code):TBandRoadObject(id,code)
        {GeometryMoved=false;FStep=100;}
void __fastcall SetBound(__int32 minx,__int32 maxx,__int32 miny,__int32 maxy);
void __fastcall SetFrame(__int32 lmin,__int32 lmax,__int32 lcur,__int32 xmin,__int32 xmax,TPlanKind pk,TPlanDirect dr);
void __fastcall SetOutBound(__int32 lmin,__int32 lmax,__int32 xmin,__int32 xmax);
void __fastcall ConvertPoint(__int32 L,__int32 X,__int32 &PX,__int32 &PY);
bool __fastcall RConvertPoint(__int32 X,__int32 Y,__int32 &PL,__int32 &PX);
void __fastcall ConvertPointsArray(__int32 n, TRoadPoint *in, POINT *out);
void __fastcall ConvertPolyline(TPolyline &src,TExtPolyline &dst);
// ��������� �������� ����� � ��������� �� head �� tale ������������
void __fastcall CalcPointsInterval(TPolyline *Poly,int head,int tale,TRoadObject* RefObj);
//void __fastcall CalcPointPos(TRoadPoint &p);
void __fastcall CalcPointPos(TPolyline*,int i,TRoadObject*);
// ������������� ��������� �� ������� ������� ��� ����� ����� i
// ind1,ind2 -- ������� ��������� �����, ������� ��� ���� ���� ����������
void __fastcall SetPointPos(TPolyline *Poly,int i,TRoadObject *RefObj,int &ind1,int &ind2);
void __fastcall CalcPointsPos(TPolyline*,TRoadObject *);
void __fastcall CalcPointParam(TRoadPoint &p,__int32 BaseL,__int32 BaseX);
//������ ������� �������
//void __fastcall GetBase(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 &BaseL,__int32 &BaseX);
void __fastcall GetBaseL(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 &BaseL);
void __fastcall GetBaseX(TPolyline *Poly,int i,TRoadObject *RefObj,__int32 L,__int32 &BaseX);
virtual TExtPolyline* __fastcall GetProfilMetric(TRect &OutRect);
void __fastcall CalcMinMaxZ(void)
    {Geometry.GetMinMaxZ(FZMin,FZMax);
    if (FZMin==FZMax)
      FZMax=FZMin+100;
    }
__fastcall TRoad(TRoad* Rd,__int32 L1,__int32 L2);
__property __int32 XMin={read=FXMin};
__property __int32 XMax={read=FXMax};
__property __int32 ZMin={read=FZMin};
__property __int32 ZMax={read=FZMax};
__property TPlanKind PlKind={read=FPlKind};
__property TPlanDirect PlDirect={read=FPlDirect};
__property TPtConvertMethod ConvertMethod={read=FConvertMethod,write=FConvertMethod};
__property __int32 FrameLMin={read=FFrameLMin};
__property __int32 FrameLMax={read=FFrameLMax};
__property __int32 FrameLPos={read=FFrameLPos};
__property __int32 FrameXMin={read=FFrameXMin};
__property __int32 FrameXMax={read=FFrameXMax};
__property __int32 Step={read=FStep,write=FStep};
__property double Kx={read=FKx};
__property double Kl={read=FKl};

};



#endif
