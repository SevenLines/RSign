//---------------------------------------------------------------------------

#ifndef unSignalsInsertH
#define unSignalsInsertH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include "Const.h"
#include "RoadObj.h"
//#include "MainUnit.h"
#include <Math.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSignalsInsert : public TForm
{
__published:	// IDE-managed Components
        TEdit *edtBegin;
        TEdit *edtEnd;
        TButton *Button1;
        TLabel *Label1;
        TLabel *Label2;
        TCSpinEdit *edtEvery;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *lblCount;
        TCSpinEdit *edtCount;
        TRadioGroup *rgMain;
        TCheckBox *chkAuto;
        TLabel *Label5;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall edtEveryChange(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
private:	// User declarations
        int _iBegin,_iEnd;

public:		// User declarations
        TRoadSignal *RoadSignal;
        __fastcall TfrmSignalsInsert(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSignalsInsert *frmSignalsInsert;
//---------------------------------------------------------------------------
#endif
