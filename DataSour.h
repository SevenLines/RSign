//---------------------------------------------------------------------------
#ifndef DataSourH
#define DataSourH
//#define GDIEDIT

//---------------------------------------------------------------------------
// ���� �������� ��� ����������� ������ ��������������
// ������ � ������. �� ������� �������������� ������ Load
// ��� �������� ������ �� ������������ ����������
// Wrote By Kirichenko K.D.
//---------------------------------------------------------------------------
//       �����.            ��� ���� �������
//       ������������� ������� ������ ���� ��� ������� � ������!!!
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
TGDIList *FGorzGDIObjects;   // ������ �������� GDI (������ � ������) ��� ����������� �������������
TGDIList *FVertGDIObjects;   // ������ �������� GDI (������ � ������) ��� ����������� �����������
                        // ����� Load ������ ��������� ������� � �������
                        // ������� API
                        // CreatePen ��� �reateBrushIndirect ��� ������.

TMetafileList *FMetas;   // ������ ���� ����������. ���������� ��������� ������
                        // ������� ����������. ���� ��������� ��������� � ������
                        // �����������.
bool FReady;            // ��� ���������� ������ ��������������� � ������, ����
                        // �������� ������ ������ �������
bool FOwnList;          // ���������� ��������������� � ������ ��� �������� ������� � � 0 ��� �����������
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
bool FReady;            // ��� ���������� ������ ��������������� � ������, ����
                        // �������� ������ ������ �������
bool FOwnList;          // ���������� ��������������� � ������ ��� �������� ������� � � 0 ��� �����������
__int32 FDictId;
TNotifyEvent *FOnError; // ������� ������� ������ ����������� ���
                        //������ ��������.
TObjList<TObjMetaClass> *FObjClasses; // ������ ���� ����� ��������.
TObjList<TPropClassesRec> *FPropClasses; //������ ���� ����� �������
TObjList<TTextPropRec> *FTextProps;      //������ �������� �������.
TObjList<TDrwProcRec> *FDrwProcs;        //������ ������������ ��������
TObjList<TDrwParamRec> *FDrwParams;      //������ ���������� ��� ������������
                                        //��������
TObjList<TDrwPageRec> *FDrwPages;         // ������ ��������� �������
TObjList<TDrwClassesRec> *FDrwClasses;   // ������ ������������ ������+��������
                                         //            -> ��������� �����������
void __fastcall CreateClasses(void);

__int32 FRefCount;       // ���������� ������ �� ������
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
__int32 FDataType;   // ���� ���������
__int32 FReadOnly;   // true ���� ���� ������ ��� ������
__int32 FNotExist;   // true ���� ���� �������� ������������� �������
__int32 FMetricsSource; // ������ ���������� ������� (0 - �� ��������)
                        // (1 - �� ������, ������)
__int32 FProfilKind;    // ������ ��������������� ������� (0 - �� ����� ������)
                        // ( 1 - �� ������������� �������)
                        // (2 - ���������)
__int32 FProfilMinLen;  // ����������� ����� ������� ��� �������
__int32 FProfilMaxDev;  // ����������� ���������� ������� � �������� �������
__int32 FProfilVal1;    // ������ ������ �������� ������� ��������� �������
__int32 FProfilVal2;    // ������ ���������� �� ������.

__int32 FProfilLen;     // ���������� ��� ����������� ������� �� ��������
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
//TVideoTime *FDirVideoTime; // �������� ����� �� ������� � �������
//TVideoTime *FUnDirVideoTime; // �������� ����� �� ������� � �������
TObjList<TVideoHigh> *FVideoHighList; //����� �����
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
__int32 FRefCount;       // ���������� ������ �� ������
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
// ��������� ���� �� ������������� �������
virtual bool __fastcall TestNeedSave(void);
// ���������� ������� � ��������� �� ������ ��������. ���������� �������
// ���������� � TContRoadObject. ������ ������ �������� � �������� � ������ WidthName
// b=false, ���� ������������� ������� ������ ���� 0
// b=true, ���� ������������� ������� ������ ������������������
void __fastcall BuildRoadMetrics(int MetSour=-1);
void __fastcall BuildLongSlopesPart(TDictSource *Dict,int sp,int ep);
void __fastcall BuildSimplePart(int spos,int epos,int step,TDictSource *Dict);
void __fastcall BuildWidePart(int spos,int epos,int step,int roundval,TDictSource *Dict);
void __fastcall BuildRoadSides(int spos,int epos,TRoadSide side,int step,int roundval,int ref,TDictSource *dict);
void __fastcall BuildWidthMeasure(int step,TDictSource *Dict);
//��������� ������ � ������ �� �����������
void __fastcall BreakRoadLines(void);

void __fastcall CalcMetrics(TRoad *RefRoad);
// ������� ������� ��������� ������ �� ��������
void __fastcall CalcGeometry(int MinL,int MaxL);
// ������� ������� CurvePlan �� ��������
void __fastcall CalcCurvePlan(int MinL,int MaxL);
void __fastcall Recreate(TDictSource *Dict);
void virtual __fastcall Load(__int32 id_,__int32 dataclass_,TDictSource *Dict);
virtual TRoadObject * __fastcall CopyObject(TRoadObject *obj,TDictSource *Dict,int newid=0);
void __fastcall CopySelectedObjects(TDictSource *Dict);
void __fastcall RemoveSelectedObjects(void);
virtual void __fastcall Dump(TDictSource *Dict,bool savegeom);
void virtual __fastcall Apply(TDictSource *Dict);
TRoadObject* __fastcall FindObject(__int32 id);
//������� ���� �������, ������ ������� ����������� ����� lmin � lmax
//���������� ���������� �������� ind1, ind2 ����� ������ �������� ������� ������� �������
//� ������� � ����������. ���� �������� � ������� ���, �� ������� ��������� �� ���������
// ������ � ����� �� �������.
__int32 BinarySearch(__int32 lmin,__int32 lmax,__int32 &ind1,__int32 &ind2);
// ���� ������ ���� dictid ������ �������� ����� ������������� � ��������� �� lmin �� lmax
// ���� index>=0, �� ����� ���������� �� ������� � index. ������ �������� ����� ���������� �������
TRoadObject* __fastcall FindNext(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index);
TRoadObject* __fastcall FindPred(__int32 dictid,__int32 lmin,__int32 lmax,__int32 &index);
// ���� ������� ������ ���� dictid ������ �������� ����� ����� l
// �������������, ��� ������� �� ������������
TRoadObject* __fastcall FindRoadPart(__int32 dictid,__int32 l);
//������� �������� ������ ��� �����������
void __fastcall DeleteObjectEx(TRoadObject* robj);
// ������� ������� ������ �� ������
void __fastcall DeleteObject(TRoadObject* robj);
void __fastcall DeleteChildObjects(TRoadObject *robj);
void __fastcall DeleteObject(int index);
void __fastcall MoveAllObjects(int len,TRoad *RefRoad);
void __fastcall MoveSelectedObjects(int len,TRoad *RefRoad);
void __fastcall ConnectSelectedToBaseLine(int ln,TRoad *RefRoad);
// ������� ������� ������� � ���������� �������� ������������ �� � ��������
void __fastcall MoveMetricToProp(TRoad *RefRoad);
void __fastcall MoveVideo(int len);
// ������� ��������� ������ � ��������������� ������
void __fastcall AddRoadObject(TRoadObject *obj);
void __fastcall AddRoadLine(TDictSource *Dict,TPolyline *Poly,int plc,int knd);
void __fastcall BuildRoadLines(TDictSource *Dict);
void __fastcall CalculateRoadMarkLength(int AttachDist);
void __fastcall SortByPlacement(void);
// ������� ��������� ������� �� ������
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
// ��������� ��� ������ ��������� (ReadOnly)
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
