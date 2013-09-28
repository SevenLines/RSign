//---------------------------------------------------------------------------

#ifndef SelNewObjH
#define SelNewObjH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DataSour.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAddObjFrm : public TForm
{
__published:	// IDE-managed Components
    TTreeView *TreeView1;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall FormActivate(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    TDictSource *FDict;
    TObjMetaClass *FMetaClass;
public:		// User declarations
    __fastcall TAddObjFrm(TComponent* Owner);
    bool __fastcall Execute(TDictSource *dict);
    void __fastcall ShowObjList(void);
    __property TObjMetaClass *MetaClass={read=FMetaClass};
};
//---------------------------------------------------------------------------
extern PACKAGE TAddObjFrm *AddObjFrm;
//---------------------------------------------------------------------------
#endif
