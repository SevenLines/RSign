//---------------------------------------------------------------------------

#ifndef SettingFrmH
#define SettingFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmSetting : public TForm
{
__published:	// IDE-managed Components
    TRadioGroup *RadioCopy;
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox1;
    TCheckBox *RopMode;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TEdit *Edit1;
    TUpDown *updownVideoOffset;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
    int FOldCopyIndex;
    int FOldVideoOffset;
    bool FOldRopMode;
    int __fastcall GetVideoOffset(void)
        {return updownVideoOffset->Position;}
    void __fastcall SetVideoOffset(int x)
        {updownVideoOffset->Position=x;}
    int __fastcall GetCopyIndex(void)
        {return RadioCopy->ItemIndex;}
    void __fastcall SetCopyIndex(int ind)
        {RadioCopy->ItemIndex=ind;}
    bool __fastcall GetRopEnabled(void)
        {return RopMode->Checked;}
    void __fastcall SetRopEnabled(bool mode)
        {RopMode->Checked=mode;}
public:		// User declarations
    __fastcall TFrmSetting(TComponent* Owner);
    __property int CopyIndex={read=GetCopyIndex,write=SetCopyIndex};
    __property bool RopEnabled={read=GetRopEnabled,write=SetRopEnabled};
    __property int VideoOffset={read=GetVideoOffset,write=SetVideoOffset};
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSetting *FrmSetting;
//---------------------------------------------------------------------------
#endif
