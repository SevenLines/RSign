//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ErrorObjectDlg.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TErrorObjectDialog *ErrorObjectDialog;
//---------------------------------------------------------------------------
__fastcall TErrorObjectDialog::TErrorObjectDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TErrorObjectDialog::NewSession(void)
{
checkApplyToAll->Checked=false;
FLastAction=0;
}
bool __fastcall TErrorObjectDialog::Execute(TRoadObject *obj,TDtaSource *src,String Message,String ObjName)
{
FObj=obj;
FSrc=src;
if (FLastAction&&(checkApplyToAll->Checked))
    {
    if (FLastAction==2)
        DeleteObject();
    else if (FLastAction==3)
        MarkObject();
    return FLastAction>1;
    }
else
    {
    checkApplyToAll->Checked=false;
    labelMessage->Caption=Message;
    labelObjName->Caption=ObjName;
    TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(obj);
    String Pos;
    if (cobj)
        {
        Pos=String(cobj->LMin/100)+"-"+String(cobj->LMax/100);
        }
    else
        Pos=String(cobj->LMin/100);
    labelPosition->Caption=Pos;
    return ShowModal()==mrOk;
    }
}

void __fastcall TErrorObjectDialog::DeleteObject(void)
{
FSrc->DeleteObject(FObj);
}

void __fastcall TErrorObjectDialog::MarkObject(void)
{
FObj->Selected=true;
MainForm->SendBroadCastMessage(CM_CHANGESEL,(int)FObj,(int)FSrc);
}

void __fastcall TErrorObjectDialog::btnCancelClick(TObject *Sender)
{
FLastAction==1;
}
//---------------------------------------------------------------------------
void __fastcall TErrorObjectDialog::btnDeleteClick(TObject *Sender)
{
FLastAction=2;
DeleteObject();
}
//---------------------------------------------------------------------------
void __fastcall TErrorObjectDialog::btnMarkClick(TObject *Sender)
{
FLastAction=3;
MarkObject();
}
//---------------------------------------------------------------------------
