//---------------------------------------------------------------------------

#ifndef NewViewH
#define NewViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TNewViewDialog : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TButton *Button2;
  TButton *Button1;
  TCheckListBox *SourcesList;
  TDataSource *DataSource1;
  TADODataSet *ADODataSet1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall SourcesListClickCheck(TObject *Sender);
private:	// User declarations
  __int32 FSourcesCount;
  __int32 FRoadId;
  __int32 __fastcall GetDataSource(int n);  
public:		// User declarations
  __fastcall TNewViewDialog(TComponent* Owner);
  __property __int32 SourcesCount={read=FSourcesCount};
  __property __int32 RoadId={read=FRoadId,write=FRoadId};
  __property __int32 DataSource[int n]={read=GetDataSource};
};
//---------------------------------------------------------------------------
extern PACKAGE TNewViewDialog *NewViewDialog;
//---------------------------------------------------------------------------
#endif
