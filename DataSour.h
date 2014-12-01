//---------------------------------------------------------------------------
#ifndef DataSourH
#define DataSourH
//#define GDIEDIT

//---------------------------------------------------------------------------
// Файл содержит два абстрактных класса обеспечивающих
// доступ к данным. Их потомки переопределяют методы Load
// для загрузки данных из определенных источников
// Wrote By Kirichenko K.D.
//---------------------------------------------------------------------------
//       ВАЖНО.            Для всех списков
//       идентификатор объекта должен быть его номером в списке!!!
//---------------------------------------------------------------------------
#include <ADODB.hpp>
#include "RoadObj.h"
#include "RoadDict.h"

#ifndef GDIEDIT
#endif
#include "ListForm.h"
#include "Factory.h"
#include "Document.h"
class TListFrm;
//---------------------------------------------------------------------------
class TSharedObjSource  : public TObject
{
protected:
TGDIList *FGorzGDIObjects;   // Список объектов GDI (перьев и кистей) для отображения горизонтально
TGDIList *FVertGDIObjects;   // Список объектов GDI (перьев и кистей) для отображения вертикально
                        // метод Load должен создавать объекты с помощью
                        // функций API
                        // CreatePen или СreateBrushIndirect или других.

TMetafileList *FMetas;   // Список имен метафайлов. Необходимо заполнить список
                        // именами метафайлов. Сами метафайлы создаются в момент
                        // отображения.
bool FReady;            // Эта переменная должна устанавливаться в истину, если
                        // загрузка данных прошла успешно
bool FOwnList;          // Переменная устанавливается в истину при создании списков и в 0 при копировании
public:
__fastcall TSharedObjSource(void);
__fastcall ~TSharedObjSource(void);
virtual void __fastcall Load(void) {}
virtual void __fastcall Save(void) {}
virtual void __fastcall Dump(String path);
void __fastcall CopyList(TSharedObjSource *);
__property TGDIList* GorzGDIObjects={read=FGorzGDIObjects};
__property TGDIList* VertGDIObjects={read=FVertGDIObjects};
__property TMetafileList* Metas={read=FMetas};
__property bool Ready={read=FReady};
};

class TDictSource : public TObject
{
protected:
bool FReady;            // Эта переменная должна устанавливаться в истину, если
                        // загрузка данных прошла успешно
bool FOwnList;          // Переменная устанавливается в истину при создании списков и в 0 при копировании
__int32 FDictId;
TNotifyEvent *FOnError; // Событие которое должно происходить при
                        //ошибке загрузки.
TObjList<TObjMetaClass> *FObjClasses; // Список имен типов объектов.
TObjList<TPropClassesRec> *FPropClasses; //Список имен типов свойств
TObjList<TTextPropRec> *FTextProps;      //Список значений свойств.
TObjList<TDrwProcRec> *FDrwProcs;        //Список отображающих процедур
TObjList<TDrwParamRec> *FDrwParams;      //Список параметров для отображающих
                                        //процедур
TObjList<TDrwPageRec> *FDrwPages;         // Список доступных страниц
TObjList<TDrwClassesRec> *FDrwClasses;   // Список соответствий объект+свойство
                                         //            -> параметры отображения
void __fastcall CreateClasses(void);

__int32 FRefCount;       // Количество ссылок на объект
friend class TResManager;
void __fastcall IncRefCount()
    {FRefCount++;}
void __fastcall DecRefCount()
    {FRefCount--;}
public:
void __fastcall BuildClassesTree(TTreeView*,TTreeNode *TopNode);
void __fastcall TextPropByClasses(TStrings*,__int32);
void __fastcall BuildPagesList(TStrings*);
void __fastcall ChangePropClasses(int firstnum,int lastnum,int *newnum);
void __fastcall ChangePropOrder(__int32 ClassId,int n,TTextPropRec **NewOrder);
__int32 __fastcall FindPropId(__int32 cid,String stit);
String __fastcall GetShortTitle(__int32 pid);
String __fastcall GetTitle(__int32 pid);
int _fastcall GetPropValIndex(__int32 pid);
bool __fastcall CalcCondition(char *s,TRoadObject *obj);
__int32 __fastcall SelectDrwParam(__int32 code,__int32 prop,__int32 PageIndex);
__int32 __fastcall SelectDrwParam(TRoadObject *obj,__int32 PageIndex);
__fastcall TDictSource(void);
void __fastcall CopyList(TDictSource *);
__fastcall ~TDictSource(void);
virtual void __fastcall Load(__int32 DictId) {}
virtual void __fastcall Save(void) {}
virtual void __fastcall Dump(String path);
__property bool Ready={read=FReady};
__property TNotifyEvent *OnError={read=FOnError,write=FOnError};
__property TObjList<TObjMetaClass> *ObjClasses={read=FObjClasses};
__property TObjList<TPropClassesRec> *PropClasses={read=FPropClasses};
__property TObjList<TTextPropRec> *TextProps={read=FTextProps};
__property TObjList<TDrwProcRec> *DrwProcs={read=FDrwProcs};
__property TObjList<TDrwParamRec> *DrwParams={read=FDrwParams};
__property TObjList<TDrwClassesRec> *DrwClasses={read=FDrwClasses};
__property TObjList<TDrwPageRec> *DrwPages={read=FDrwPages};
__property __int32 RefCount={read=FRefCount};
__property __int32 DictId={read=FDictId};
};

class TDtaSource : public TObject
{
protected:
__int32 FId;
__int32 FDataClass;  // Source
__int32 FDataType;   // Виды источника
__int32 FReadOnly;   // true если слой только для чтения
__int32 FNotExist;   // true если слой содержит проектируемые объекты
__int32 FMetricsSource; // Способ построения метрики (0 - по участкам)
                        // (1 - по кромке, бровке)
__int32 FProfilKind;    // Способ масштабирования профиля (0 - по длине дороги)
                        // ( 1 - по отображаемому участку)
                        // (2 - участками)
__int32 FProfilMinLen;  // Минимальная длина участка для профиля
__int32 FProfilMaxDev;  // Максимально допустимый разброс в пределах участка
__int32 FProfilVal1;    // Наклон меньше которого участки считаются ровными
__int32 FProfilVal2;    // Наклон допустимый по Снипам.

__int32 FProfilLen;     // Расстояние для отображения профиля по пикетажу
String FRoadName;
String FSourceName;
TRoad *FRoad;
TRoadObjFactory *FFactory;
TObjList<TRoadObject> *FObjects;
//TObjList<TPolyline> *FPolyList;
TObjList<TRoadObject> *FBuffer;
TObjList<TRoadObject> *FDelBuffer;
TObjList<TDocument> *FDocList;
TObjList<TVideoTime> *FUnDirVideoTime;
TObjList<TVideoTime> *FDirVideoTime;
bool VideoMoved;
//TVideoTime *FDirVideoTime; // Привязка видео по времени и заездам
//TVideoTime *FUnDirVideoTime; // Привязка видео по времени и заездам
TObjList<TVideoHigh> *FVideoHighList; //Видео файлы
int FDirVideoId;
int FUnDirVideoId;
bool FReady;
bool FDestCopy;
TNotifyEvent *FOnError;
String FDumpName;
String FDumpPath;
String __fastcall GetDumpName(void);
void __fastcall SetDumpName(String);
String __fastcall GetDumpPath(void);
void __fastcall SetDumpPath(String);
void __fastcall SetRoadBound(__int32 minl,__int32 maxl,__int32 minx,__int32 maxx)
    {FRoad->SetBound(minl,maxl,minx,maxx);}

void __fastcall CreateClasses(void);
void __fastcall FreeClasses(void);
__int32 FRefCount;       // Количество ссылок на объект
friend class TResManager;
void __fastcall IncRefCount()
    {FRefCount++;}
void __fastcall DecRefCount()
    {FRefCount--;}
void __fastcall SetMarker(int);
void __fastcall DeleteMarkedObjects(int marker);
void __fastcall DeleteMarkedObjects(int marker,int command);

friend class TSignRules;
friend class TfrmSetSigns;
friend class TSignDesignRules;
TRoadSign* __fastcall AddPrjSign(TDictSource* Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String Code,String Label,String Note,TSignAttach onattach);
friend class TRoadFrm;
TRoadSign* __fastcall AddManSign(TDictSource* Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String Code,String Label,String Note);
TRoadSign* __fastcall CreateManSign(TDictSource* Dict,TRoadDirection dir,TRoadSignPlacement pl, __int32 fl,__int32 fx,String Code,String Label,String Note);
bool __fastcall GetHaveDirVideo(void)
    {return FDirVideoTime->Count>0;}
bool __fastcall GetHaveUnDirVideo(void)
    {return FUnDirVideoTime->Count>0;}
void __fastcall SetDirVideoId(int nid) {
   if (nid>=0 && nid<FDirVideoTime->Count)
      FDirVideoId=nid;
}
void __fastcall SetUnDirVideoId(int nid) {
   if (nid>=0 && nid<FUnDirVideoTime->Count)
      FUnDirVideoId=nid;
}
public:
__fastcall TDtaSource(void);
__fastcall ~TDtaSource(void);
// Проверяет есть ли несохраненные объекты
virtual bool __fastcall TestNeedSave(void);
// Записывает метрику в полилинию из списка объектов. Выбираются объекты
// приводимые к TContRoadObject. Ширина полосы хранится в свойстве с именем WidthName
// b=false, если отсутствующие участки должны быть 0
// b=true, если отсутствующие участки должны аппроксимироваться
void __fastcall BuildRoadMetrics(int MetSour=-1);
void __fastcall BuildLongSlopesPart(TDictSource *Dict,int sp,int ep);
void __fastcall BuildSimplePart(int spos,int epos,int step,TDictSource *Dict);
void __fastcall BuildWidePart(int spos,int epos,int step,int roundval,TDictSource *Dict);
void __fastcall BuildRoadSides(int spos,int epos,TRoadSide side,int step,int roundval,int ref,TDictSource *dict);
void __fastcall BuildWidthMeasure(int step,TDictSource *Dict);
//Разрывает кромку и бровку по примыканиям
void __fastcall BreakRoadLines(void);

void __fastcall CalcMetrics(TRoad *RefRoad);
// Функция считает геометрию дороги по объектам
void __fastcall CalcGeometry(int MinL,int MaxL);
// Функция считает CurvePlan по объектам
void __fastcall CalcCurvePlan(int MinL,int MaxL);
void __fastcall Recreate(TDictSource *Dict);
void virtual __fastcall Load(__int32 id_,__int32 dataclass_,TDictSource *Dict);
virtual TRoadObject * __fastcall CopyObject(TRoadObject *obj,TDictSource *Dict,int newid=0);
void __fastcall CopySelectedObjects(TDictSource *Dict);
void __fastcall RemoveSelectedObjects(void);
virtual void __fastcall Dump(TDictSource *Dict,bool savegeom);
void virtual __fastcall Apply(TDictSource *Dict);
TRoadObject* __fastcall FindObject(__int32 id);
//Функция ищет объекты, начала которых расположены между lmin и lmax
//Возвращает количество объектов ind1, ind2 после выхода содержат индексы первого объекта
//в участке и последнего. Если объектов в участке нет, то индексы указывают на ближайший
// справа и слева от участка.
__int32 BinarySearch(__int32 lmin,__int32 lmax,__int32 &ind1,__int32 &ind2);
// Ищет объект типа dictid начало которого может располагаться в интервале от lmin до lmax
// если index>=0, то поиск начинается от объекта с index. Индекс содержит номер найденного объекта
TRoadObject* __fastcall FindNext(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index);
TRoadObject* __fastcall FindPred(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index);
// Ищет участок дороги типа dictid внутри которого лежит точка l
// предолагается, что участки не пересекаются
TRoadObject* __fastcall FindRoadPart(__int32 dictid,__int32 l);
//Функция помечает объект как неправильнй
void __fastcall DeleteObjectEx(TRoadObject* robj);
// Функция удаляет объект из списка
void __fastcall DeleteObject(TRoadObject* robj);
void __fastcall DeleteChildObjects(TRoadObject *robj);
void __fastcall DeleteObject(int index);
void __fastcall MoveAllObjects(int len,TRoad *RefRoad);
void __fastcall MoveSelectedObjects(int len,TRoad *RefRoad);
void __fastcall ConnectSelectedToBaseLine(int ln,TRoad *RefRoad);
// Функция удаляет метрику у дискретных объектов перетаскивая ее в свойства
void __fastcall MoveMetricToProp(TRoad *RefRoad);
void __fastcall MoveVideo(int len);
// Функция добавляет объект в отсортированный список
void __fastcall AddRoadObject(TRoadObject *obj);
void __fastcall AddRoadLine(TDictSource *Dict,TPolyline *Poly,int plc,int knd);
void __fastcall BuildRoadLines(TDictSource *Dict);
void __fastcall CalculateRoadMarkLength(int AttachDist);
void __fastcall SortByPlacement(void);
// Функция добавляет объекты из буфера
void __fastcall AddFromBufer(void);
//TPolyline* __fastcall FindPolyline(__int32 id);
int __fastcall GetDocumentsCount(__int32 AId,__int32 ADictId);
void __fastcall GetDocuments(TStrings*,__int32 AId,__int32 ADictId);
__property __int32 Id={read=FId};
__property __int32 DataClass={read=FDataClass};
__property __int32 DataType={read=FDataType};
__property TRoad *Road={read=FRoad};
//__property TObjList<TPolyline> *PolyList={read=FPolyList};
__property TObjList<TRoadObject> *Objects={read=FObjects};
__property TObjList<TRoadObject> *Buffer={read=FBuffer};
__property TObjList<TDocument> *DocList={read=FDocList};
__property TObjList<TVideoTime> *DirVideoTime={read=FDirVideoTime};
__property TObjList<TVideoTime> *UnDirVideoTime={read=FUnDirVideoTime};
__property TObjList<TVideoHigh> *VideoHighList={read=FVideoHighList};
__property bool Ready={read=FReady};
__property TNotifyEvent *OnError={read=FOnError,write=FOnError};
__property __int32 RefCount={read=FRefCount};
__property __int32 ReadOnly={read=FReadOnly};
// Процедура для снятия параметра (ReadOnly)
void __fastcall ClearReadOnly(void)
    {FReadOnly=false;}
__property __int32 NotExist={read=FNotExist};
__property TRoadObjFactory* Factory={read=FFactory};
__property String RoadName={read=FRoadName};
__property String SourceName={read=FSourceName};
__property int MetricsSource={read=FMetricsSource,write=FMetricsSource};
__property int ProfilKind={read=FProfilKind,write=FProfilKind};
__property __int32 ProfilMinLen={read=FProfilMinLen,write=FProfilMinLen};
__property __int32 ProfilMaxDev={read=FProfilMaxDev,write=FProfilMaxDev};
__property __int32 ProfilVal1={read=FProfilVal1,write=FProfilVal1};
__property __int32 ProfilVal2={read=FProfilVal2,write=FProfilVal2};
__property __int32 HaveDirVideo={read=GetHaveDirVideo};
__property __int32 HaveUnDirVideo={read=GetHaveUnDirVideo};
__property int DirVideoId={read=FDirVideoId,write=SetDirVideoId};
__property int UnDirVideoId={read=FUnDirVideoId,write=SetUnDirVideoId};
__property String DumpName={read=GetDumpName,write=SetDumpName};
__property String DumpPath={read=GetDumpPath,write=SetDumpPath};
};

class TResManager : public TObject
{
TObjList<TDtaSource> *DataList;
TObjList<TDictSource> *DictList;
TObjList<TListFrm> *ListList;
TDtaSource *FCopyDestination;
void __fastcall SetCopyDestination(TDtaSource* dta);
int __fastcall GetDataCount(void)
    {return DataList->Count;}
int __fastcall GetDictCount(void)
    {return DictList->Count;}
TDtaSource* __fastcall GetData(int Index);
void __fastcall BuildMenuList(void);
void __fastcall ReleaseDataSourceByIndex(int index);
public:
__fastcall TResManager(void);
__fastcall ~TResManager(void);
TDtaSource* __fastcall AddDataSource(String FormCaption,__int32 id,__int32 dataclass1,__int32 DictId,TADOConnection *con,TRoadObjFactory *factory);
void __fastcall UseDataSource(TDtaSource* Dta)
  {Dta->IncRefCount();}
TDtaSource* __fastcall AddFileDataSource(String filename,__int32 DictId,TRoadObjFactory *factory);
void __fastcall ReleaseDataSource(__int32 id,__int32 dataclass);
void __fastcall ReleaseDataSource(TDtaSource*);
void __fastcall OnReleaseListForm(TDtaSource *Dta);
TDictSource* __fastcall AddFileDictSource(__int32 id);
TDictSource* __fastcall AddDictSource(__int32 id,TADOConnection *con);
void __fastcall UseDictSource(TDictSource *dict);
void __fastcall ReleaseDictSource(__int32 id);
TDictSource* __fastcall GetDict(__int32 n);
TDtaSource* __fastcall GetSource(__int32 n,__int32 dataclass);
TListFrm* __fastcall GetListFrm(__int32 dataclass);
__property TDtaSource* CopyDestination={read=FCopyDestination,write=SetCopyDestination};
__property int DataCount={read=GetDataCount};
__property int DictCount={read=GetDictCount};
__property TDtaSource* Data[int]={read=GetData};
};

#endif
