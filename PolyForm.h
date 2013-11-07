//---------------------------------------------------------------------------

#ifndef PolyFormH
#define PolyFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>

#include "Metrics.h"
#include "RoadObj.h"
#include "ShowRoad.h"
#include <Buttons.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TPolyFrm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel2;
    TGroupBox *GroupBox1;
    TCheckListBox *PolyList;
    TPanel *Panel3;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TComboBox *Connection;
    TComboBox *Leep;
    TComboBox *LBase;
    TComboBox *XBase;
    TComboBox *Polar;
    TEdit *LeepPar;
    TEdit *BasePar1;
    TCheckBox *BaseFixed1;
    TCheckBox *BaseFixed2;
    TEdit *BasePar2;
    TButton *Button1;
    TButton *Button2;
    TCheckBox *Visible;
    TSpeedButton *btnSelectAll;
    TSpeedButton *btnCopy;
    TSpeedButton *btnCut;
    TSpeedButton *btnPaste;
    TSpeedButton *btnErase;
    TSpeedButton *btnAdd;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
   TSpeedButton *btnSavePar;
   TSpeedButton *SpeedButton3;
   TPopupMenu *PatMenu;
   TMenuItem *N1;
    void __fastcall PolyListClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnSelectAllClick(TObject *Sender);
    void __fastcall btnEraseClick(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnPasteClick(TObject *Sender);
    void __fastcall btnCopyClick(TObject *Sender);
    void __fastcall btnCutClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btnSaveParClick(TObject *Sender);
   void __fastcall SpeedButton3Click(TObject *Sender);
   void __fastcall N1Click(TObject *Sender);
private:	// User declarations
    TStringList *FPatterns;
    void __fastcall LoadPatterns(void);
    void __fastcall SavePatterns(void);
    void __fastcall BuildMenu(void);
    void __fastcall CopyPointFromPattern(TObject *Sender);
    TPolyline *FPoly;
    TExtPolyline *FVector;
    TPolyline *FBuffer;
    TRoadObject *FRefObj;
    TRoad *FRefRoad;
    TRoadFrm *FRefForm;
    void __fastcall BuildProp(int Num);
    String __fastcall GetPointInfo(int);
    void __fastcall BuildList(void);
    TPointCode __fastcall GetCode(void);
    // Устанавливает выделение в векторе по выделению из списка
    void __fastcall RefreshSelection(void);
    void __fastcall CopySelectedPoints(void);
    void __fastcall RemoveSelectedPoints(void);
    void __fastcall CutSelectedPoints(void);
    void __fastcall SelectAllPoints(void);
    void __fastcall PastePoints(void);
    void __fastcall AddPoints(void);
    void __fastcall ReplaceSelectedToWidePart(void);
public:		// User declarations
    TPointCode ParamCode;
    void __fastcall ShowForm(TRoadFrm*,TRoad*,TPolyline*,TExtPolyline*,TRoadObject*);
    void __fastcall UpdatePoly(TExtPolyline*);
    void __fastcall UpdatePoint(int);
    void __fastcall SelectPoint(int);
    void __fastcall SetActivePoint(int,bool exclusive);
    __fastcall TPolyFrm(TComponent* Owner);
    __fastcall ~TPolyFrm(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPolyFrm *PolyFrm;
//---------------------------------------------------------------------------
#endif
