//---------------------------------------------------------------------------

#ifndef VPatViewH
#define VPatViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "VPattern.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TVPatFrm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox2;
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TEdit *Edit1;
    TListBox *ListBox1;
    TPanel *Panel2;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ListBox1DblClick(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
    TDrawPattern *WorkPat;
    String __fastcall GetPatFileName(String);
    String __fastcall GetCurPatFileName(void);
    void __fastcall SetCurPatFileName(String Name);
    void __fastcall EditChange(TObject *Sender);
    String FOldPatName;
public:		// User declarations
    void __fastcall ShowPattern(TDrawPattern*);
    __fastcall TVPatFrm(TComponent* Owner);
    __property String FileName={read=GetCurPatFileName,write=SetCurPatFileName};
};
//---------------------------------------------------------------------------
extern PACKAGE TVPatFrm *VPatFrm;
//---------------------------------------------------------------------------
#endif
