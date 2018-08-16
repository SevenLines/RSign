//---------------------------------------------------------------------------
#ifndef RoadObjH
#define RoadObjH
#include "RoadDict.h"                                        
#include "Lists.h"                                    
#include "Const.h"
#include "Metrics.h"
#include "Measures.h"
//---------------------------------------------------------------------------
// Описания структур всех дорожных объектов
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

//Класс характеристика
class TCharacter
{
private:
protected:
String FName; // Название характеристики
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


// Абстрактный дорожный объект
const char RoadObjectInfo[]="Общий предок в иерархии классов дорожных объектов.\
Содержит одно свойство L - расстояние до начала объекта.\
Объекты этого класса не отображаются";

enum TLocalisation {locNone=0,locDescreet=1,locLinear=2,locSquare=3};

class TRoadObject : public TObject
{
protected:
bool FSelected;  // true если объект выделен
bool FModified;  // true если объект был изменен -- пока не используется

TRoadObject *FParent; // Указатель на родителя
TRoadObject *FChild; // Указатель на первого сына
TRoadObject *FSibling; // Указатель на брата. Младший брат на NULL;

__int32 FTag;    //Служебное поле для работы некоторых процедур // может изменяться в процессе работы
__int32 FId;     //Идентификатор объекта
__int32 FDictId; //Идентификатор типа по классификатору   (Id в таблице GDIObjType)
                 // TDictSource::ObjClasses->Items[FDictId]->Title
__int32 FDrwClassId; // Идентификатор класса отображения. Высчитывается процедурой
                     // SelectDrwParam
//__int32 FBaseId;     // Идентификатор объекта из базы данных
TCharList *FCharList;
TPolyline *FPoly;     // Ссылка на метрику объекта (если есть) удалять и создавать не надо!

DEFPROPERTYRW(__int32,L)
DEFPROPERTY(__int32,PrevId)     // Предыдущий Id для достоверных объектов
DEFPROPERTYRW(TSignTest,Test) //Результат ручной проверки
DEFPROPERTYRW(String,Note) // Обоснование автоматической проверки


int __fastcall GetClassPropCount(void* MetaClass);
public:
virtual TLocalisation GetLocal(void) {return locNone;}
// Функция, которая должна вызываться после записи объекта
void __fastcall PostSaveObject(void)
    {FModified=false;}
void __fastcall PostLoadObject(void)
    {FModified=false;}
virtual int __fastcall ComponentCount(void)  // Для объектов, состоящих из частей число частей
    {return 0;}                              // Например для сигнальных устройств - число столбиков
void __fastcall AddChild(TRoadObject *ch);
void __fastcall RemoveChild(TRoadObject *ch);
void __fastcall PutProperty(String propname,String propvalue);
bool __fastcall PutPropValue(String propname,String propvalue);
String __fastcall GetPropValue(String propname);

int __fastcall GetPropCount(void);
String __fastcall GetPropName(int n);
// Процедура сохранения в список строк
// Процедура чтения из списка
// Процедура вывода объекта на форму
// Процедура сохранения объекта из формы
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
// Функция создает массив точек для последующего отображения
// n - число точек, Road - объект дорога. Он должен создаваться для каждого
// вызова и содержать только тот кусок дороги, который виден на экране
virtual  TExtPolyline* __fastcall GetDefMetric(TRoad *Road)
    {return NULL;}
virtual TExtPolyline* __fastcall GetPolyMetric(TRoad* Road);
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p) {return false;}
virtual TPolyline* __fastcall GetDefaultPlacement(TRoad* Road) {return 0;}
virtual TExtPolyline* PrepareMetric(TRoad *Road);
virtual void __fastcall UpdatePoly(void);
virtual void __fastcall PostEditPoly(void)
    {FModified=true;UpdatePoly();}
// Функция возвращает количество подписей для отображения.
virtual int __fastcall GetTextsCount(void)
        {return 0;}
// функция возвращпет подписи которые надо отображать. Эта функция вызывается
// несколько раз, сномером 0,1 и.т.д. Когда все подписи выведены должна вернуть 0
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

// Дорожный объект с точечной локализацией


const char DescreetRoadObjectInfo[]="Дорожный объект с точечной локализацией. Произведен от\
TRoadObject. Новых свойств не содержит. Объекты этого класса содержат метрику из одной\
точки, лежащей на осевой линии дороги на заданном расстоянии от начала дороги.";

class TDescreetRoadObject :  public TRoadObject
{
protected:
public:
__fastcall TDescreetRoadObject(): TRoadObject() {}
__fastcall TDescreetRoadObject(__int32 id,__int32 code) : TRoadObject(id,code) {}
virtual TLocalisation GetLocal(void) {return locDescreet;}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char MoundHeightInfo[]="Объект хранящий высоту насыпи, измеренную в точке.\
Произведен от TDescreetRoadObject. Вводятся два новых свойства.\
Placement - расположение (слева, справа). Height - Высота в сантиметрах";
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

// Дорожный объект с точечной локализацией привязанный к кромке дороги
// и имеющий направление (прямое - обратное)

const char DescreetDirRoadObjectInfo[]="Дорожный объект с точечной локализацией и направлением.\
Произведен от TDescreetRoadObject. Вводятся два новых свойства. DX - раcстояние от кромки дороги.\
Direction - направление (прямое, обратное). Метрика содержит одну точку, лежащую справа\
от дороги (с учетом направления) на расстоянии DX от кромки";

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

// Дорожный объект с точечной локализацией привязанный к кромке дороги
// и расположенный слева или справа от дороги.

const char DescreetSideRoadObjectInfo[]="Дорожный объект с точечной локализацией, расположенный слева или справа от дороги.\
Произведен от TDescreetRoadObject. Вводятся два новых свойства. DX - раcстояние от кромки дороги.\
Placement - расположение (слева, справа). Метрика содержит одну точку, лежащую с указанной стороны\
от дороги (в прямом направлении) на расстоянии DX от кромки";

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

const char DescreetCenterRoadObjectInfo[]="Дорожный объект с точечной локализацией, с привязкой к оси дороги\
Произведен от TDescreetRoadObject. Вводятся два новых свойства. DX - раcстояние от центра дороги.\
Placement - расположение (слева, справа). Метрика содержит одну точку, лежащую с указанной стороны\
от дороги (в прямом направлении) на расстоянии DX от оси дороги";

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


// Еще дискретный объект
const char DescreetSideCenterRoadObject[]="Рекламный щит. Произведен от TDescreetSideRoadObject\
Добавлена возможность размещения на разделительной полосе";

class TDescreetSideCenterRoadObject : public TDescreetSideRoadObject {
private:
public:
__fastcall TDescreetSideCenterRoadObject() : TDescreetSideRoadObject() {FDX=350;}
__fastcall TDescreetSideCenterRoadObject(__int32 id,__int32 code) : TDescreetSideRoadObject(id,code) {FDX=350;}
virtual bool __fastcall SetDefaultPlacement(TRoad* Road,TPolyline *p);
};

// Столб освещения
const char RoadLightingInfo[]="Столб уличного освещения. Произведен от TDescreetSideRoadObject\
Поведение полностью унаследовано.";

class TRoadLighting : public TDescreetSideCenterRoadObject {
private:
DEFPROPERTY(TLampKind,Kind)
public:
__fastcall TRoadLighting() : TDescreetSideCenterRoadObject() {FDX=350;}
__fastcall TRoadLighting(__int32 id,__int32 code) : TDescreetSideCenterRoadObject(id,code) {FDX=350;}
};


const char BusStopInfo[]="Автобусная остановка. Объект произведен от TDescreetSideRoadObject.\
Вводятся три новых свойства. Name - название остановки. bool StopArea - наличие остановочной\
площадки. bool Pavilion - наличие павильона. Поведение полностью унаследовано.";

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

const char SpeedBumpInfo[]="Лежачий полицейский";

class TSpeedBump : public TDescreetRoadObject {
public:
    __fastcall TSpeedBump(): TDescreetRoadObject() {}
    __fastcall TSpeedBump(__int32 id,__int32 code) : TDescreetRoadObject(id,code) {}
    virtual TLocalisation GetLocal(void) {return locLinear;}
    virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

const char RoadTubeInfo[]="Труба";
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

const char RoadWidthMeasureInfo[]="Точка измерения ширины дороги";
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

// Дорожный объект с не дискретной локализацией
const char ContRoadObjectInfo[]="Дорожный объект, имеющий начало локализации и конец.\
Произведен от TRoadObject. Свойство L определяет начало локализации. Вводится свойство\
LMax - конец локализации. Объекты этого класса не отображаются.";
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


// Дорожный объект привязанный к кромке дороги
const char RoadSideObjectInfo[]="Дорожный объект, привязанный к кромке или бровке дороги. Произведен от\
TContRoadObject. Вводятся три новых свойства DX - расстояние от кромки дороги.\
Placement - вид расположения (слева, справа, на разделительной полосе).\
Объекты этого типа не отображаются";
class TRoadSideObject : public TContRoadObject
{
protected:
DEFPROPERTYRW(__int32,DX)                   // Расстояние от кромки дороги
DEFPROPERTYRW(TObjPlacement,Placement)      // Направление расположения (слева справа между)
DEFPROPERTYRW(TMetricsKind,MetricsKind)            // Кромка или бровка
virtual TPolyline* __fastcall GetAttachPoly(TRoad *Road);
public:
__fastcall TRoadSideObject():TContRoadObject() {}
__fastcall TRoadSideObject(__int32 id,__int32 code):TContRoadObject(id,code)
    {FDX=0;FPlacement=TObjPlacement(0);FMetricsKind=TMetricsKind(0);}
};

// Дорожный объект с линейной локализацией
// Привязанный к кромке дороги
const char LinearRoadSideObjectInfo[]="Дорожный объект, привязанный к кромке или бровке дороги, представляемый\
линией. Произведен от TRoadSideObject. Метрика объекта является линией расположенной на\
расстоянии DX от нужной кромки или бровки дороги в зависимости от расположения и параллельной ей.";
class TLinearRoadSideObject : public TRoadSideObject
{
private:

public:
__fastcall TLinearRoadSideObject():TRoadSideObject() {}
__fastcall TLinearRoadSideObject(__int32 id,__int32 code):TRoadSideObject(id,code)  {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
};
// Объект ситуации

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

// Водоотводное сооружение
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

// Дорожный объект с линейной локализацией фиксированной
// конечной ширины привязанный к центру дороги
// Ширина не выражается в масштабе

const char FixedRoadObjectInfo[]="";
class TFixedRoadObject : public TContRoadObject
{
public:
__fastcall TFixedRoadObject(__int32 id,__int32 code):TContRoadObject(id,code) {}

};

// Дорожный объект с линейной локализацией фиксированной ширины,
// находящийся на дороге расположение которого зависит от ширины дороги
// Это разметка то есть ;) (может быть, пока не знаю...)

const char RoadMarkInfo[]="";
class TRoadMark : public TContRoadObject
{
protected:
DEFPROPERTYRW(int, Length)   // Длина
DEFPROPERTYRW(int, Area)   // Площадь
DEFPROPERTYRW(int, Offset)   // Смещение
DEFPROPERTYRW(int, K)        // Коэффициент.
DEFPROPERTY(TRoadDirection,Direction) // Направление
DEFPROPERTY(TMarkKind,Kind)  // Вид разметки
// Местоположение определяется по формуле Width*K/1000+Offset, где
// Width это расстояние от центра дороги до кромки
public:
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locLinear;}
__fastcall TRoadMark():TContRoadObject() {};
__fastcall TRoadMark(__int32 id,__int32 code):TContRoadObject(id,code) {};
virtual int __fastcall GetTextsCount(void)
    {return 3;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

//Дорожный объект площадной локализации, привязанный к дороге с одной стороны
const char SquareRoadSideObjectInfo[]="Дорожный объект площадной локализации привязанный\
к кромке дороги с одной стороны и уходящий в бесконечность с другой. Произведен от\
TRoadSideObject. Метрика состоит из полигона с одной стороны привязанного к кромке на\
расстоянии DX в зависимости от расположения, и этого же полигона на расстоянии Width\
области, с краев - по началу и концу локализации.";
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

// Обочина
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

// Дорожный объект с линейной локализацией, не зависящей
// от дороги (пока потомков нет)

const class TLinearRoadObject : public TContRoadObject
{
protected:
public:
};

//Участок дороги
//Главная характеристика это значение характеристики по которой
// участок выделен (напр, по материалу покрытия, значение асфальтобетон)
const char RoadPartInfo[]="Объект участок дороги. Произведен от TContRoadObject.\
Метрика состоит из полигона, ограниченного с двух сторон краями дороги, а с двух\
других вертикальными линиями в точках начала и конца участка.";

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

const char RoadDressInfo[]="Дорожная одежда";
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

const char RoadCategoryInfo[]="Участок дороги по технической категории";
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

const char DivRoadPartInfo[]="Объект разделительная полоса";
class TDivRoadPart : public TBandRoadPart
{
public:
__fastcall TDivRoadPart(): TBandRoadPart() {FLineBound=3;}
__fastcall TDivRoadPart(__int32 id,__int32 code): TBandRoadPart(id,code) {FLineBound=3;}
};


const char ZemPolotnoInfo[]="Земляное полотно";
class TZemPolotno : public TBandRoadPart
{
protected:
DEFPROPERTY(__int32,TopWidth)
public:
__fastcall TZemPolotno(): TBandRoadPart() {}
__fastcall TZemPolotno(__int32 id,__int32 code): TBandRoadPart(id,code)
    {FLineBound=2;}
};

const char SquareCenterObjectInfo[]="Площадной дорожный объект выровненный по центру дороги";
class TSquareCenterObject : public TBandRoadPart
{
protected:
public:
__fastcall TSquareCenterObject():TBandRoadPart() {}
__fastcall TSquareCenterObject(__int32 id,__int32 code):TBandRoadPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual TLocalisation GetLocal(void) {return locSquare;}
};

const char LinearCenterObjectInfo[]="Линейный дорожный объект выровненный по оси дороги";
class TLinearCenterRoadObject : public TContRoadObject
{
protected:
public:
__fastcall TLinearCenterRoadObject():TContRoadObject() {}
__fastcall TLinearCenterRoadObject(__int32 id,__int32 code):TContRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

// опасные участки уклоны и повороты
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

const char CarePartInfo[]="Участки дорог на которых необходима подсыпка";
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
DEFPROPERTY(String,Scheme)                    // Схема моста
DEFPROPERTY(String,ObstacleName)              //Имя преграды
DEFPROPERTY(TObstacleKind,ObstacleKind)        //Тип преграды
DEFPROPERTY(__int32,Width)                    // Ширина моста в сантиметрах
DEFPROPERTY(TBridgeKind,Kind)                 // Тип конструкции моста
DEFPROPERTY(TBridgeConstruction,Construction) // Тип пролетных строений
DEFPROPERTY(TBridgeMaterial,Material)         //материал покрытия
DEFPROPERTY(__int32,Tonnage1)                 //В потоке общая грузоподъемность
DEFPROPERTY(__int32,Tonnage2)                 //В потоке осевая
DEFPROPERTY(__int32,Tonnage3)                 //В одиночном порядке
public:
__fastcall TRoadBridge():TRoadPart() {}
__fastcall TRoadBridge(__int32 id,__int32 code):TRoadPart(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
virtual int __fastcall GetTextsCount(void)
        {return 1;}
virtual TPlanLabel* __fastcall GetText(int n,TRoad *Road,TDictSource *Dict);
};

// Площадной объект зависящий от дороги и уходящий в бесконечность, например нас.пункт
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
// Описание примыканий
// Класс примыкания
// Установка полей возможна только при создании объекта
const char RoadAttachInfo[]="";
class TRoadAttach : public TDescreetRoadObject
{
private:
DEFPROPERTY(TRoadClass,Tech)            // Тех категория дороги
DEFPROPERTY(String,Name)                //Наименование примыкания
DEFPROPERTY(TAttachPlacement,Placement) //Направление примыкания
DEFPROPERTYRW(int,Angle)                  // Угол примыкания
DEFPROPERTY(int,Width)                  // Ширина примыкающей дороги в точке примыкания
DEFPROPERTY(String,Comment)             //Наименование примыкания
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
// Описание съездов
// Класс съезд
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
// Объекты в одну линию, пересекающие дорогу
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
DEFPROPERTY(TRailKind,RailKind)          // Класс путей
DEFPROPERTY(TRailCrossSignal,SignalKind)  // Вид сигнализации
DEFPROPERTY(int,RailCount)                // Число путей
DEFPROPERTY(bool,Light)                   // Наличие электроосвещения
DEFPROPERTY(bool,Guard)                   // Наличие охраны
public:
__fastcall TRailCross():TCommRoadObject() {}
__fastcall TRailCross(__int32 id,__int32 code):TCommRoadObject(id,code) {}
};

const char RoadObstacleInfo[]="";
class TRoadObstacle : public TCommRoadObject
{
private:
DEFPROPERTY(String,ObstacleName)              //Имя преграды
DEFPROPERTY(TObstacleKind,ObstacleKind)        //Тип преграды
DEFPROPERTY(__int32,Width)                    // Ширина моста в сантиметрах
public:
__fastcall TRoadObstacle(): TCommRoadObject() {}
__fastcall TRoadObstacle(__int32 id,__int32 code):TCommRoadObject(id,code) {}
virtual TExtPolyline* __fastcall GetDefMetric(TRoad *Road);
};

// Светофоры
const char TrafficLightInfo[]="Светофор";
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


// Описание дорожных знаков
// Установка полей пока возможна только при создании объекта
const char RoadSignInfo[]="";
class TRoadSign : public TDescreetDirRoadObject
{
protected:
DEFPROPERTYRW(__int32,NumRoadSign)  // Номер знака по таблице
DEFPROPERTYRW(__int32,ViewKind)   // Для некоторых знаков дополнительные виды отображения
DEFPROPERTYRW(String,Label)      // Надпись на знаке
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
// Функция находит ориентацию знака
// 0 - без поворота 3 - 90 гр по часовой стрелке
// 2 - 180 гр. 1 - 90 гр против часовой стрелки
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
DEFPROPERTY(__int32, CarCount)  // Количество машин в ДТП
public:
__fastcall TDTP():TDescreetRoadObject() {}
__fastcall TDTP(__int32 id,__int32 code): TDescreetRoadObject(id,code) {}
};

// Класс ограждение
const char RoadBarrierInfo[]="";
class TRoadBarrier : public TLinearRoadSideObject
{
protected:
DEFPROPERTY(TBarrierConstruction,Construction) // Тип конструкции ограждения
public:
__fastcall TRoadBarrier():TLinearRoadSideObject() {}
__fastcall TRoadBarrier(__int32 id,__int32 code):TLinearRoadSideObject(id,code) {}
};

// Сигнальное устройство
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


//Объекты отображаемые в виде полосы переменной ширины
//Полоса задается в виде двух линий. В силу дорожной
//специфики L_{n+1}>=L_{n}
//Пока единственным примером является сама дорога.
class TBandRoadObject : public TContRoadObject
{
protected:
public:
__fastcall TBandRoadObject(__int32 id,__int32 code):TContRoadObject(id,code)
        {}
TPolyline LeftLine; // левая кромка дороги (край покрытия)
TPolyline RightLine; // правая кромка дороги
};

//Дорога целиком
class TRoad :public TBandRoadObject
{
private:
// Рамка дороги по ширине
__int32 FXMin,FXMax;
__int32 FOutYMin,FOutYMax,FOutXMin,FOutXMax;
// Границы дороги в окне FrameLPos положение маркера
__int32 FFrameLMin,FFrameLMax,FFrameXMin,FFrameXMax,FFrameLPos;
__int32 FZMin,FZMax;
// Расстояние между соседними точками в см при аппроксимации
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
TPolyline LeftSide; // левая бровка дороги
TPolyline RightSide;  // правая бровка дороги
TPolyline LeftZem; // Левый край зем полотна
TPolyline RightZem; // Правый край зем полотна
TPolyline LeftDivPart; // Край разделительной полосы слева
TPolyline RightDivPart; // Край разделительной полосы справа
TPolyline LeftBound;    // Граница укрепленной части дороги с учетом перекрестков
TPolyline RightBound;   // Граница укрепленной части дороги с учетом перекрестков

TCurvePlan CurvePlan;   // Схематический план дороги
// Находим координаты точек на схематическом плане дороги
void __fastcall CalcCurvePlanPoints(void);

TRoadGeometry Geometry; // Продольный профиль дороги
bool GeometryMoved;     // true после редактирования геометрических параметров
__fastcall TRoad(__int32 id,__int32 code):TBandRoadObject(id,code)
        {GeometryMoved=false;FStep=100;}
void __fastcall SetBound(__int32 minx,__int32 maxx,__int32 miny,__int32 maxy);
void __fastcall SetFrame(__int32 lmin,__int32 lmax,__int32 lcur,__int32 xmin,__int32 xmax,TPlanKind pk,TPlanDirect dr);
void __fastcall SetOutBound(__int32 lmin,__int32 lmax,__int32 xmin,__int32 xmax);
void __fastcall ConvertPoint(__int32 L,__int32 X,__int32 &PX,__int32 &PY);
bool __fastcall RConvertPoint(__int32 X,__int32 Y,__int32 &PL,__int32 &PX);
void __fastcall ConvertPointsArray(__int32 n, TRoadPoint *in, POINT *out);
void __fastcall ConvertPolyline(TPolyline &src,TExtPolyline &dst);
// Вычисляет значения точек в интервале от head до tale включительно
void __fastcall CalcPointsInterval(TPolyline *Poly,int head,int tale,TRoadObject* RefObj);
//void __fastcall CalcPointPos(TRoadPoint &p);
void __fastcall CalcPointPos(TPolyline*,int i,TRoadObject*);
// Пересчитывает параметры по текущей позиции для точки номер i
// ind1,ind2 -- границы интервала точек, которые при этом тоже изменились
void __fastcall SetPointPos(TPolyline *Poly,int i,TRoadObject *RefObj,int &ind1,int &ind2);
void __fastcall CalcPointsPos(TPolyline*,TRoadObject *);
void __fastcall CalcPointParam(TRoadPoint &p,__int32 BaseL,__int32 BaseX);
//Старый вариант функции
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
