//---------------------------------------------------------------------------

#ifndef SelNewSignH
#define SelNewSignH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DataSour.h"
#include "DrawMan.h"
//---------------------------------------------------------------------------
class TAddSignFrm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label1;
    TImage *Image1;
    TLabel *Label3;
    TListBox *ListTypes;
    TButton *Button1;
    TButton *Button2;
    TEdit *GOSTCode;
    TPanel *Panel2;
    TLabel *Label2;
    TListBox *ListKinds;
    TSplitter *Splitter1;
    TPanel *Panel3;
    TLabel *Label4;
    TListBox *VariantList;
        void __fastcall ListTypesClick(TObject *Sender);
        void __fastcall ListKindsClick(TObject *Sender);
    void __fastcall ListKindsDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall VariantListDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
    void __fastcall VariantListMeasureItem(TWinControl *Control, int Index,
          int &Height);
    void __fastcall VariantListClick(TObject *Sender);
    void __fastcall Splitter1Moved(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
TObjList<TDrwClassesRec> *DrwVariantList;  // Список структур для отображения вариантов начертания знака
int FOldClass;
int FVariation;
int FSignClass;
int FNumCode;
TDictSource *FDict;
TDrawManager *FDrawMan;
String __fastcall GetCode(void);
void __fastcall TestAddEnabled(void);
int __fastcall GetValue(char *s);
void __fastcall SetVariantList(void);
void __fastcall SetListKinds(void);
public:		// User declarations
        __fastcall TAddSignFrm(TComponent* Owner);
bool __fastcall Execute(TDictSource*,int NumCode,int variation);
__property String Code={read=GetCode};
__property int Variation={read=FVariation};
__property int SignClass={read=FSignClass};
__property int NumCode={read=FNumCode};
};
//---------------------------------------------------------------------------
extern PACKAGE TAddSignFrm *AddSignFrm;
//---------------------------------------------------------------------------
#endif
