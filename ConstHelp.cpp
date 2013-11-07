//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConstHelp.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmConstHelp *frmConstHelp;
//---------------------------------------------------------------------------
__fastcall TfrmConstHelp::TfrmConstHelp(TComponent* Owner)
    : TForm(Owner)
{
FDict=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmConstHelp::SetDictionary(TDictSource *dict)
{
if (FDict)
    MainForm->ResManager->ReleaseDictSource(FDict->DictId);
FDict=dict;
if (FDict)
    MainForm->ResManager->UseDictSource(FDict);
listObjects->Clear();
listPropertys->Clear();
listValues->Clear();
if (FDict)
    {
    for (int i=0;i<FDict->ObjClasses->Count;i++)
        {
        TObjMetaClass *meta=FDict->ObjClasses->Items[i];
        if (meta)
            {
            TListItem  *Item=listObjects->Items->Add();
            Item->Caption=meta->OneTitle;
            Item->Data=(void*)meta;
            Item->SubItems->Add(meta->Id);
            }
        }
    }
}

void __fastcall TfrmConstHelp::listObjectsChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
if (FDict)
    {
    TObjMetaClass *meta=(TObjMetaClass*)Item->Data;
    if (meta)
        {
        listPropertys->Clear();
        listValues->Clear();
        for (int i=0;i<meta->PropCount;i++)
            {
            TPropClassesRec *Prop=FDict->PropClasses->Items[meta->PropIds[i]];
            if (Prop)
                {
                TListItem  *Item=listPropertys->Items->Add();
                Item->Caption=Prop->PropName;
                Item->Data=(void*)Prop;
                Item->SubItems->Add(Prop->Id);
                Item->SubItems->Add(Prop->ShortName);
                Item->SubItems->Add(Prop->ClassName);
                Item->SubItems->Add(TypesNames[Prop->Type]);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmConstHelp::listPropertysChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
if (FDict)
    {
    TPropClassesRec *Prop=(TPropClassesRec*)Item->Data;
    if (Prop)
        {
        listValues->Clear();
        for (int i=0;i<FDict->TextProps->Count;i++)
            {
            TTextPropRec* TRec=FDict->TextProps->Items[i];
            if (TRec->PropId==Prop->Id)
                {
                TListItem  *Item=listValues->Items->Add();
                Item->Caption=TRec->Text;
                Item->Data=(void*)TRec;
                Item->SubItems->Add(TRec->Id);
                Item->SubItems->Add(TRec->ShortText);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmConstHelp::FormClose(TObject *Sender,
      TCloseAction &Action)
{
SetDictionary(NULL);
}
//---------------------------------------------------------------------------

