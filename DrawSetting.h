//---------------------------------------------------------------------------
#ifndef DrawSettingH
#define DrawSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDrwSetFrm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl;
    TTabSheet *Page1;
    TGroupBox *GroupBox1;
    TComboBox *ComboScaleX;
    TGroupBox *GroupBox2;
    TComboBox *ComboBoundX;
    TGroupBox *GroupBox3;
    TComboBox *ComboScaleL;
    TGroupBox *GroupBox4;
    TLabel *Label1;
    TEdit *Edit1;
    TUpDown *KmUpDown;
    TGroupBox *GroupBox5;
    TComboBox *ComboObjX;
    TRadioGroup *GroupMetSource;
    TTabSheet *Page2;
    TRadioGroup *GroupProfKind;
    TRadioGroup *GroupProfilKind;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox8;
    TComboBox *ComboScaleP;
    TGroupBox *GroupBox9;
    TComboBox *ComboFontSize;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ComboScaleXKeyPress(TObject *Sender, char &Key);
private:	// User declarations
    void __fastcall SetScaleL(int);
    int __fastcall GetScaleL(void);
    void __fastcall SetScaleX(int);
    int __fastcall GetScaleX(void);
    void __fastcall SetScaleP(int);
    int __fastcall GetScaleP(void);
    void __fastcall SetBoundX(int);
    int __fastcall GetBoundX(void);
    void __fastcall SetObjX(int);
    int __fastcall GetObjX(void);
    void __fastcall SetFontSize(int);
    int __fastcall GetFontSize(void);
    void __fastcall SetDelVis(bool b)
        {CheckBox1->Checked=b;}
    void __fastcall SetProVis(bool b)
        {CheckBox2->Checked=b;}
    bool __fastcall GetDelVis(void)
        {return CheckBox1->Checked;}
    bool __fastcall GetProVis(void)
        {return CheckBox2->Checked;}
    void __fastcall SetKmInPage(int n);
    int __fastcall GetKmInPage(void);
    void __fastcall SetMetSource(int);
    int __fastcall GetMetSource(void);
    void __fastcall SetProfilKind(int);
    int __fastcall GetProfilKind(void);    
public:		// User declarations
    __fastcall TDrwSetFrm(TComponent* Owner);
    __property int ScaleL={read=GetScaleL,write=SetScaleL};
    __property int ScaleX={read=GetScaleX,write=SetScaleX};
    __property int ScaleP={read=GetScaleP,write=SetScaleP};
    __property int BoundX={read=GetBoundX,write=SetBoundX};
    __property int ObjX={read=GetObjX,write=SetObjX};
    __property int KmInPage={read=GetKmInPage,write=SetKmInPage};
    __property bool DelVis={read=GetDelVis,write=SetDelVis};
    __property bool ProVis={read=GetProVis,write=SetProVis};
    __property int MetricsSource={read=GetMetSource,write=SetMetSource};
    __property int ProfilKind={read=GetProfilKind,write=SetProfilKind};    
    __property int FontSize={read=GetFontSize,write=SetFontSize};
};
//---------------------------------------------------------------------------
extern PACKAGE TDrwSetFrm *DrwSetFrm;
//---------------------------------------------------------------------------
#endif
