//---------------------------------------------------------------------------

#ifndef OpenSourceH
#define OpenSourceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "MainUnit.h"
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TOpenSourceDialog : public TForm
{
__published:	// IDE-managed Components
    TDBGrid *DBGrid1;
    TADODataSet *ADODataSet1;
    TDataSource *DataSource1;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall FormShow(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
    __int32 FSourcesCount;
    __int32 FRoadId;
    __int32 FDataSource;
public:		// User declarations
    __fastcall TOpenSourceDialog(TComponent* Owner);
    __property __int32 DataSource={read=FDataSource};
    __property __int32 RoadId={read=FRoadId,write=FRoadId};
};
//---------------------------------------------------------------------------
extern PACKAGE TOpenSourceDialog *OpenSourceDialog;
//---------------------------------------------------------------------------
#endif
