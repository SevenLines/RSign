//---------------------------------------------------------------------------

#ifndef RoadMarkH
#define RoadMarkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DataSour.h"
#include "DrawMan.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMarkParam : public TForm
{
__published:	// IDE-managed Components
    TListBox *ListKinds;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label5;
    TLabel *Label4;
    TLabel *Label6;
    TEdit *editStart;
    TEdit *editEnd;
    TComboBox *comboKind;
    TComboBox *comboDirection;
    TEdit *editK;
    TEdit *editX;
    TUpDown *updX;
    TUpDown *updK;
    TPanel *Panel2;
    TButton *Button2;
    TButton *Button1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall comboKindChange(TObject *Sender);
    void __fastcall ListKindsDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
TDictSource *FDict;
TRoadMark *FObj;
TDrawManager *FDrawMan;
    void __fastcall BuildKindList(void);
public:		// User declarations
    __fastcall TfrmMarkParam(TComponent* Owner);
    bool __fastcall Execute(TDictSource *dict,TRoadMark *obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMarkParam *frmMarkParam;
//---------------------------------------------------------------------------
#endif
