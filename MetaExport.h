//---------------------------------------------------------------------------

#ifndef MetaExportH
#define MetaExportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TMetaParam : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *FNameEdit;
    TEdit *Edit2;
    TEdit *Edit3;
    TButton *Button1;
    TButton *Button2;
    TUpDown *MinKm;
    TUpDown *MaxKm;
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
    void __fastcall Edit7Change(TObject *Sender);
    void __fastcall ScaleLChange(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
    String FFileName;
public:		// User declarations
    void __fastcall SetFileName(String NewName);
    __fastcall TMetaParam(TComponent* Owner);
    __property String FileName={read=FFileName};    
};
//---------------------------------------------------------------------------
extern PACKAGE TMetaParam *MetaParam;
//---------------------------------------------------------------------------
#endif
