//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BrForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBrushEdit *BrushEdit;
//---------------------------------------------------------------------------
__fastcall TBrushEdit::TBrushEdit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBrushEdit::ComboBox1Change(TObject *Sender)
{
SetBrush();
}
//---------------------------------------------------------------------------
void __fastcall TBrushEdit::Shape1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (ColorDialog1->Execute())
        {
        SetBrush();
        }
}

void __fastcall TBrushEdit::SetBrush(void)
{
if (ComboBox1->ItemIndex>0)
        Shape1->Brush->Handle=CreateHatchBrush(ComboBox1->ItemIndex-1,ColorDialog1->Color);
else
        Shape1->Brush->Handle=CreateSolidBrush(ColorDialog1->Color);
}
//---------------------------------------------------------------------------
void __fastcall TBrushEdit::FormActivate(TObject *Sender)
{
SetBrush();        
}
//---------------------------------------------------------------------------
