//---------------------------------------------------------------------------

#ifndef BrFormH
#define BrFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TBrushEdit : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TShape *Shape1;
        TButton *Button1;
        TButton *Button2;
        TColorDialog *ColorDialog1;
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Shape1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
        void __fastcall SetBrush(void);
public:		// User declarations
        __fastcall TBrushEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBrushEdit *BrushEdit;
//---------------------------------------------------------------------------
#endif
