//---------------------------------------------------------------------------

#ifndef VisCondEH
#define VisCondEH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RoadDict.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TVisCondEdit : public TForm
{
__published:	// IDE-managed Components
    TLabel *ObjCaption;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TEdit *CondEdit;
    TListBox *PropList;
    TSplitter *Splitter1;
    TListBox *ValList;
    void __fastcall FormHide(TObject *Sender);
    void __fastcall PropListClick(TObject *Sender);
    void __fastcall PropListDblClick(TObject *Sender);
    void __fastcall ValListDblClick(TObject *Sender);
private:	// User declarations
    TObjMetaClass *FObjClass;
    TDictSource *FDict;
    void __fastcall SetCondition(String s)
        {CondEdit->Text=s;}
    String __fastcall GetCondition(void)
        {return CondEdit->Text;}
public:		// User declarations
    void __fastcall SetObjClass(TObjMetaClass *obj,TDictSource *dict);
    __fastcall TVisCondEdit(TComponent* Owner);
    __property String Condition={read=GetCondition,write=SetCondition};
};
//---------------------------------------------------------------------------
extern PACKAGE TVisCondEdit *VisCondEdit;
//---------------------------------------------------------------------------
#endif
