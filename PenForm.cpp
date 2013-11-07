//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PenForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPenEdit *PenEdit;
//---------------------------------------------------------------------------
__fastcall TPenEdit::TPenEdit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPenEdit::PBoxPaint(TObject *Sender)
{
PBox->Canvas->Pen->Color=Shape1->Brush->Color;
PBox->Canvas->Pen->Width=UpDown1->Position;
PBox->Canvas->Pen->Style=TPenStyle(ComboBox1->ItemIndex);
PBox->Canvas->MoveTo(10,PBox->Height>>1);
PBox->Canvas->LineTo(PBox->Width-10,PBox->Height>>1);
}
//---------------------------------------------------------------------------
void __fastcall TPenEdit::Shape1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (ColorDialog1->Execute())
        {
        Shape1->Pen->Color=ColorDialog1->Color;
        Shape1->Brush->Color=ColorDialog1->Color;
        PBox->Invalidate();        
        }
}
//---------------------------------------------------------------------------
void __fastcall TPenEdit::Edit1Change(TObject *Sender)
{
PBox->Invalidate();
}
//---------------------------------------------------------------------------
