//---------------------------------------------------------------------------

#ifndef ShowSignsH
#define ShowSignsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>

#include "DataSour.h"
#include "VPattern.h"
//---------------------------------------------------------------------------
class TSignForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TScrollBox *ScrollBox1;
    TSpeedButton *SpeedButton1;
    TLabel *Label1;
    TComboBox *PageList;
    TLabel *Label2;
    TComboBox *MsList;
    TImage *Image1;
    TSpeedButton *SpeedButton2;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall MsListChange(TObject *Sender);
    void __fastcall PageListChange(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
    __int32 FPageIndex;
    TDrawBitmap *BCont;
    void __fastcall BuildPageList(void);
    TDrawPattern* __fastcall GetCurrentPat(void);
    void __fastcall ChangeImage(void);
    void __fastcall DrawPat(TDrawPattern* Pat,TDrawContents *Cont,double K,int dx,int dy);
    void __fastcall PrintImage(void);
    void __fastcall ImageToBmp(void);
public:		// User declarations
    __fastcall TSignForm(TComponent* Owner);
   __property  __int32 PageIndex={read=FPageIndex,write=FPageIndex};
};
//---------------------------------------------------------------------------
extern PACKAGE TSignForm *SignForm;
//---------------------------------------------------------------------------
#endif
