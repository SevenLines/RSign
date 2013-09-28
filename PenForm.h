//---------------------------------------------------------------------------

#ifndef PenFormH
#define PenFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPenEdit : public TForm
{
__published:	// IDE-managed Components
        TComboBox *ComboBox1;
        TLabel *Label1;
        TColorDialog *ColorDialog1;
        TEdit *Edit1;
        TUpDown *UpDown1;
        TLabel *Label2;
        TLabel *Label3;
        TShape *Shape1;
        TPaintBox *PBox;
        TButton *Button1;
        TButton *Button2;
    TLabel *Label4;
    TComboBox *ComboBox2;
    TLabel *Label5;
    TComboBox *ComboBox3;
        void __fastcall PBoxPaint(TObject *Sender);
        void __fastcall Shape1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
    void __fastcall SetColor(int n)
        {Shape1->Brush->Color=TColor(n);}
    void __fastcall SetStyle(int n)
        {
        ComboBox1->ItemIndex=n&15;
        ComboBox2->ItemIndex=(n>>8)&7;
        ComboBox3->ItemIndex=(n>>12)&7;
        }
    void __fastcall SetWidth(int n)
        {UpDown1->Position=n;}
    int __fastcall GetColor(void)
        {return Shape1->Brush->Color;}
    int __fastcall GetStyle(void)
        {return ComboBox1->ItemIndex|(ComboBox2->ItemIndex<<8)|(ComboBox3->ItemIndex<<12);}
    int __fastcall GetWidth(void)
        {return UpDown1->Position;}
public:		// User declarations
    __fastcall TPenEdit(TComponent* Owner);
    __property int Style={read=GetStyle,write=SetStyle};
    __property int Color={read=GetColor,write=SetColor};
    __property int Width={read=GetWidth,write=SetWidth};
};
//---------------------------------------------------------------------------
extern PACKAGE TPenEdit *PenEdit;
//---------------------------------------------------------------------------
#endif
