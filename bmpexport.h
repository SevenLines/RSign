//---------------------------------------------------------------------------

#ifndef bmpexportH
#define bmpexportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TBmpParam : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *FNameEdit;
    TLabel *Label2;
    TEdit *Edit2;
    TLabel *Label3;
    TEdit *Edit3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TButton *Button1;
    TButton *Button2;
    TUpDown *MinKm;
    TUpDown *MaxKm;
    TLabel *Label7;
    TEdit *Edit7;
    TUpDown *PLen;
    TComboBox *ScaleL;
    TComboBox *ScaleX;
    TComboBox *Dpi;
    TCheckBox *AutoScale;
    TButton *Button3;
    TButton *Button4;
    TSaveDialog *SaveDialog1;
    TLabel *Label8;
    TEdit *Edit1;
    TUpDown *StartPage;
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall ScaleLChange(TObject *Sender);
    void __fastcall Edit7Change(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
   void __fastcall FNameEditExit(TObject *Sender);
private:	// User declarations
    String FFileName;
    void __fastcall SetFileName(String NewName);
public:		// User declarations
    __fastcall TBmpParam(TComponent* Owner);
    __property String FileName={read=FFileName};
};
//---------------------------------------------------------------------------
extern PACKAGE TBmpParam *BmpParam;
//---------------------------------------------------------------------------
#endif
