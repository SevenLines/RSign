//---------------------------------------------------------------------------

#ifndef ConstHelpH
#define ConstHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "DataSour.h"
//---------------------------------------------------------------------------
class TfrmConstHelp : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TListView *listObjects;
    TPanel *Panel1;
    TTabSheet *TabSheet3;
    TPanel *Panel2;
    TListView *listPropertys;
    TTabSheet *TabSheet2;
    TPanel *Panel3;
    TListView *listValues;
    void __fastcall listObjectsChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
    void __fastcall listPropertysChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    TDictSource *FDict;
public:		// User declarations
    __fastcall TfrmConstHelp(TComponent* Owner);
    void __fastcall SetDictionary(TDictSource *dict);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConstHelp *frmConstHelp;
//---------------------------------------------------------------------------
#endif
