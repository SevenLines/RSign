//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmSetting *FrmSetting;
//---------------------------------------------------------------------------
__fastcall TFrmSetting::TFrmSetting(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmSetting::FormActivate(TObject *Sender)
{
FOldCopyIndex=CopyIndex;
FOldRopMode=RopEnabled;
FOldVideoOffset=VideoOffset;
}
//---------------------------------------------------------------------------
void __fastcall TFrmSetting::Button2Click(TObject *Sender)
{
CopyIndex=FOldCopyIndex;
RopEnabled=FOldRopMode;
VideoOffset=FOldVideoOffset;
}
//---------------------------------------------------------------------------
