//---------------------------------------------------------------------------

#ifndef AutoCADAddRowsFormH
#define AutoCADAddRowsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFAddRows : public TForm
{
__published:	// IDE-managed Components
   TEdit *Edit2;
   TButton *Button1;
   TLabel *Label1;
   TPanel *Panel1;
   TSaveDialog *SaveDialog1;
   TButton *Button2;
   TButton *Button3;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall FormHide(TObject *Sender);
private:	// User declarations
public:		// User declarations
   AnsiString path;
   __fastcall TFAddRows(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAddRows *FAddRows;
//---------------------------------------------------------------------------
#endif
