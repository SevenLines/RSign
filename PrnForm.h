//---------------------------------------------------------------------------

#ifndef PrnFormH
#define PrnFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TPrnParam : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *Edit2;
    TEdit *Edit3;
    TUpDown *MinKm;
    TUpDown *MaxKm;
    TLabel *Label7;
    TEdit *Edit7;
    TUpDown *PLen;
    TComboBox *ScaleL;
    TComboBox *ScaleX;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TPrintDialog *PrintDialog1;
    TButton *Button4;
    TCheckBox *AutoScale;
    TLabel *Label1;
    TEdit *Edit1;
    TUpDown *StartPage;
    TEdit *Edit4;
    TUpDown *PLenM;
    TEdit *Edit5;
    TUpDown *MinKmM;
    TEdit *Edit6;
    TUpDown *MaxKmM;
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Edit7Change(TObject *Sender);
    void __fastcall ScaleLChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TPrnParam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnParam *PrnParam;
//---------------------------------------------------------------------------
#endif
