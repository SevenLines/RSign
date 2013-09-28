//---------------------------------------------------------------------------

#ifndef MacrosFormH
#define MacrosFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Macroses.h"
#include "Lists.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMacros : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TLabel *Label1;
    TEdit *editMacrosName;
    TLabel *Label2;
    THotKey *HotKey;
    TGroupBox *GroupBox2;
    TMemo *memoMacrosText;
    TListBox *listMacroses;
    TSplitter *Splitter1;
    TSpeedButton *btnAddMacro;
    TSpeedButton *btnDelMacro;
    TSpeedButton *btnWriteMacro;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnAddMacroClick(TObject *Sender);
    void __fastcall listMacrosesClick(TObject *Sender);
    void __fastcall btnDelMacroClick(TObject *Sender);
    void __fastcall btnWriteMacroClick(TObject *Sender);
private:	// User declarations
TObjList<TMacros> *FMacrosList;
TRoadObject *FGlobalVar;  // Переменная для макросов
void __fastcall ShowActiveMacros(void);
void __fastcall LoadMacroses(void);
void __fastcall SaveMacroses(void);
public:		// User declarations

    TMacros* __fastcall GetMacros(String Name);
    TMacros* __fastcall GetMacros(int key);
    __fastcall TfrmMacros(TComponent* Owner);
    __property TRoadObject *GlobalVar={read=FGlobalVar}; 
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMacros *frmMacros;
//---------------------------------------------------------------------------
#endif
