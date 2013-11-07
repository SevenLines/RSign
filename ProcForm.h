//---------------------------------------------------------------------------

#ifndef ProcFormH
#define ProcFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RoadDict.h"
//---------------------------------------------------------------------------
class TProcEdit : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TButton *Button1;
        TButton *Button2;
        TGroupBox *GroupBox2;
        TEdit *PenNum2;
        TLabel *Label1;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TEdit *PenNum1;
        TLabel *Label3;
        TEdit *BrushNum1;
        TGroupBox *GroupBox3;
        TLabel *Label4;
        TEdit *MetaNum3;
        TEdit *Width3;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Height3;
        TLabel *Label7;
        TEdit *DX3;
        TLabel *Label8;
        TEdit *DY3;
        TGroupBox *GroupBox4;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *PenNum4;
        TEdit *Length4;
        TGroupBox *GroupBox5;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *PenNum5;
        TEdit *BrushNum5;
        TEdit *Shift5;
        TEdit *Width5;
        TEdit *Dash5;
        TEdit *Space5;
        TEdit *Offset5;
        TGroupBox *GroupBox6;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TEdit *PenNum6;
        TEdit *BrushNum6;
        TComboBox *Kind6;
        TEdit *Size6;
        TEdit *Shift6;
        TLabel *Label22;
        TEdit *Space6;
        TLabel *Label23;
        TEdit *Offset6;
        TLabel *Label24;
    TGroupBox *GroupBox7;
    TLabel *Label25;
    TEdit *PenNum7;
    TLabel *Label26;
    TEdit *Shift7;
    TEdit *PenWidth2;
    TLabel *Label27;
    TLabel *Label28;
    TComboBox *PenScale2;
    TEdit *PenWidth4;
    TLabel *Label29;
    TLabel *Label30;
    TComboBox *PenScale4;
    TLabel *Label31;
    TEdit *PenStyle2;
    TLabel *Label32;
    TEdit *OrSize6;
    TLabel *Label33;
    TEdit *Left3;
    TEdit *Top3;
    TEdit *Right3;
    TEdit *Bottom3;
    TLabel *Label34;
    TEdit *PenOffset2;
    TLabel *Label35;
    TComboBox *PenScale6;
    TLabel *Label36;
    TComboBox *MetaMeasure3;
    TGroupBox *GroupBox8;
    TEdit *PenNum8;
    TLabel *Label37;
    TEdit *Length8;
    TLabel *Label38;
    TComboBox *Kind8;
    TLabel *Label39;
        void __fastcall RadioGroup1Click(TObject *Sender);
private:	// User declarations
        int FId;
public:		// User declarations
        __fastcall TProcEdit(TComponent* Owner);
   void __fastcall SetParams(TDrwParamRec*);
   TDrwParamRec* __fastcall GetParams(void);
   __property int Id={read=FId,write=FId};
};
//---------------------------------------------------------------------------
extern PACKAGE TProcEdit *ProcEdit;
//---------------------------------------------------------------------------
#endif
