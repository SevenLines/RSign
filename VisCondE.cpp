//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VisCondE.h"
#include "DataSour.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVisCondEdit *VisCondEdit;
//---------------------------------------------------------------------------
__fastcall TVisCondEdit::TVisCondEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVisCondEdit::SetObjClass(TObjMetaClass *obj,TDictSource *dict)
{
FObjClass=obj;
FDict=dict;
ObjCaption->Caption=FObjClass->Title;
PropList->Items->BeginUpdate();
ValList->Items->BeginUpdate();
PropList->Items->Clear();
ValList->Items->Clear();
for (int i=0;i<FObjClass->PropCount;i++)
    {
    int num=FObjClass->PropIds[i];
    PropList->Items->AddObject(FDict->PropClasses->Items[num]->PropName+"("+String(num)+")",(TObject*)num);
    }
PropList->Items->EndUpdate();
ValList->Items->EndUpdate();
}

void __fastcall TVisCondEdit::FormHide(TObject *Sender)
{
FDict=NULL;
FObjClass=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TVisCondEdit::PropListClick(TObject *Sender)
{
if (PropList->ItemIndex>=0)
    {
    int num=(int)PropList->Items->Objects[PropList->ItemIndex];
    FDict->TextPropByClasses(ValList->Items,num);
    }
}
//---------------------------------------------------------------------------
void __fastcall TVisCondEdit::PropListDblClick(TObject *Sender)
{
if (PropList->ItemIndex>=0)
    {
    int num=(int)PropList->Items->Objects[PropList->ItemIndex];
    TPropClassesRec *PRec=FDict->PropClasses->Items[num];
    int pos=CondEdit->SelStart+1;
    String T=CondEdit->Text.Delete(pos,CondEdit->SelLength);
    T.Insert(PRec->ClassName,pos);
    CondEdit->Text=T;
    CondEdit->SelStart=pos-1;
    CondEdit->SelLength=PRec->ClassName.Length();
    }
}
//---------------------------------------------------------------------------
void __fastcall TVisCondEdit::ValListDblClick(TObject *Sender)
{
if (ValList->ItemIndex>=0)
    {
    TTextPropRec *R=(TTextPropRec*)ValList->Items->Objects[ValList->ItemIndex];
    int pos=CondEdit->SelStart+1;
    String T=CondEdit->Text.Delete(pos,CondEdit->SelLength);
    String S=String(R->Id);
    T.Insert(S,pos+1);
    CondEdit->Text=T;
    CondEdit->SelStart=pos-1;
    CondEdit->SelLength=S.Length();
    }
}
//---------------------------------------------------------------------------
