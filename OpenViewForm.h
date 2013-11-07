//---------------------------------------------------------------------------

#ifndef OpenViewFormH
#define OpenViewFormH
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
class TOpenViewFrm : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TButton *ButOk;
  TButton *ButCancel;
  TADODataSet *ADODataSet1;
  TDataSource *DataSource1;
  TDBGrid *DBGrid1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ButOkClick(TObject *Sender);
   void __fastcall DBGrid1DblClick(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  __int32 FRoadId;
  __int32 FViewId;
public:		// User declarations
  __fastcall TOpenViewFrm(TComponent* Owner);
  __property __int32 RoadId={read=FRoadId,write=FRoadId};
  __property __int32 ViewId={read=FViewId};
};
//---------------------------------------------------------------------------
extern PACKAGE TOpenViewFrm *OpenViewFrm;
//---------------------------------------------------------------------------
#endif
