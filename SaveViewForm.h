//---------------------------------------------------------------------------

#ifndef SaveViewFormH
#define SaveViewFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TSaveViewFrm : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TDBGrid *DBGrid1;
  TADODataSet *ADODataSet1;
  TDataSource *DataSource1;
  TButton *ButOk;
  TButton *ButCancel;
  TButton *ButAdd;
  TButton *ButDelete;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButOkClick(TObject *Sender);
  void __fastcall ButDeleteClick(TObject *Sender);
  void __fastcall ButAddClick(TObject *Sender);
  void __fastcall ADODataSet1AfterDelete(TDataSet *DataSet);
private:	// User declarations
  __int32 FRoadId;
  __int32 FViewId;
  String FViewName;
  void __fastcall ShowList(void);
  void __fastcall SetButtons(void);
public:		// User declarations
  __fastcall TSaveViewFrm(TComponent* Owner);
  __property __int32 RoadId={read=FRoadId,write=FRoadId};
  __property __int32 ViewId={read=FViewId};
  __property String ViewName={read=FViewName};
};
//---------------------------------------------------------------------------
extern PACKAGE TSaveViewFrm *SaveViewFrm;
//---------------------------------------------------------------------------
#endif
