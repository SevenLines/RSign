//---------------------------------------------------------------------------

#ifndef DBDataSourceH
#define DBDataSourceH
//---------------------------------------------------------------------------
#include "DataSour.h"
#include "VisSetForm.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>

class TDBSharedObjSource : public TSharedObjSource
{
private:
TADOConnection *FConnection;
public:
__fastcall TDBSharedObjSource(void);
__fastcall TDBSharedObjSource(TADOConnection *con);
void virtual __fastcall Load(void);
void virtual __fastcall Save(void);
__property TADOConnection* Connection={read=FConnection,write=FConnection};
};

class TDBDictSource : public TDictSource
{
private:
TADOConnection *FConnection;
public:
__fastcall TDBDictSource(void);
__fastcall TDBDictSource(__int32,TADOConnection *con);
void virtual __fastcall Load(__int32 Id);
void virtual __fastcall Save(void);
__property TADOConnection* Connection={read=FConnection,write=FConnection};
};

class TDBDataSource : public ::TDtaSource
{
private:
TADOConnection *FConnection;
String __fastcall ReplaceNameVal(String Sql,TRoadObject *Obj,int Param);
void __fastcall SaveObjMetrics(TADOCommand *command,TADODataSet *DB,TRoadObject *Obj);
void __fastcall LoadVideoInfo(void); // Процедура для загрузки видео информации из Славиных табличек
bool __fastcall LoadVideoInfo1(void); //Процедура для загрузки видео информации из моих табличек
bool __fastcall LoadGeometry(void);
bool __fastcall LoadGeometryBlob(void);
void __fastcall SaveMetrics(TDictSource *Dict);
public:

__fastcall ~TDBDataSource() {}
__fastcall TDBDataSource(void);
__fastcall TDBDataSource(__int32 id_,__int32 dataclass_,TDictSource *Dict,TADOConnection *con,TRoadObjFactory *factory);
void virtual __fastcall Load(__int32 id_,__int32 dataclass_,TDictSource *Dict);
void virtual __fastcall Apply(TDictSource *Dict);
virtual TRoadObject * __fastcall CopyObject(TRoadObject *obj,TDictSource *Dict,int newid=0);
__property TADOConnection* Connection={read=FConnection,write=FConnection};
};

class TDBDataModule
{
private:
TADOConnection *FConnection;
TADODataSet *DB;
TADOCommand *Cmd;
String __fastcall GetCurrentDate(void);
__int32 __fastcall DataNum(TDtaSource *Dta);
public:
__fastcall TDBDataModule(TADOConnection *connection)
    {DB=new TADODataSet(NULL);
     Cmd=new TADOCommand(NULL);
     FConnection=connection;
     }
__fastcall ~TDBDataModule(void)
    {delete DB;delete Cmd;}
void __fastcall SaveView(TRoadFrm *Frm,__int32 ViewId,String ViewName);
void __fastcall LoadViewSources(__int32 RoadId,__int32 ViewId);
void __fastcall LoadViewParam(TRoadFrm *Frm,__int32 ViewId);
void __fastcall ReleaseViewSources(__int32 RoadId,__int32 ViewId);
void __fastcall LoadVisible(__int32 RoadId,__int32 ViewId,TVisSetFrm *VisSet);
String __fastcall GetRoadName(__int32 id);
String __fastcall GetDistrName(__int32 id);
String __fastcall GetInspectName(__int32 id);
String __fastcall GetSourceName(__int32 id);
String __fastcall GetViewName(__int32 id);
bool __fastcall GetRoadBound(int id,int datasource,int &LMin,int &LMax);
int __fastcall GetSourceType(__int32 id);
int __fastcall AddProject(__int32 RoadId,String PrjName,__int32 OrgNum, String ExecName, String ExamName);
};

extern PACKAGE TDBDataModule *DBDataModule;

#endif


