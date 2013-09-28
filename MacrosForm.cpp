//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MacrosForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMacros *frmMacros;
//---------------------------------------------------------------------------
__fastcall TfrmMacros::TfrmMacros(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::FormCreate(TObject *Sender)
{
FMacrosList=new TObjList<TMacros>;
FGlobalVar=new TRoadObject;
LoadMacroses();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::FormDestroy(TObject *Sender)
{
SaveMacroses();
delete FMacrosList;
delete FGlobalVar;
FMacrosList=NULL;
}
//---------------------------------------------------------------------------
TMacros* __fastcall TfrmMacros::GetMacros(String Name)
{
TMacros *res=NULL;
for (int i=0;i<FMacrosList->Count;i++)
    if (FMacrosList->Items[i]->MacrosName==Name)
        {
        res=FMacrosList->Items[i];
        break;
        }
return res;
}
//---------------------------------------------------------------------------
TMacros* __fastcall TfrmMacros::GetMacros(int key)
{
TMacros *res=NULL;
for (int i=0;i<FMacrosList->Count;i++)
    if (FMacrosList->Items[i]->ShortCut==key)
        {
        res=FMacrosList->Items[i];
        break;
        }
return res;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::LoadMacroses(void)
{
String Folder=ExtractFilePath(Application->ExeName)+"Macroses\\";
TSearchRec sr;
if (!FindFirst(Folder+"*.mcr",faAnyFile,sr))
    {
    do
        {
        TMacros *Macros=new TMacros;
        Macros->LoadFromFile(Folder+sr.Name);
        FMacrosList->Add(Macros);
        listMacroses->Items->AddObject(Macros->MacrosName,Macros);
        }
    while (!FindNext(sr));
    FindClose(sr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::SaveMacroses(void)
{
String Folder=ExtractFilePath(Application->ExeName)+"Macroses";
if (!DirectoryExists(Folder))
    CreateDir(Folder);
for (int i=0;i<FMacrosList->Count;i++)
    FMacrosList->Items[i]->SaveToFile(Folder);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::ShowActiveMacros(void)
{
if (listMacroses->ItemIndex>=0)
    {
    TMacros* Macros=FMacrosList->Items[listMacroses->ItemIndex];
    editMacrosName->Text=Macros->MacrosName;
    HotKey->HotKey=Macros->ShortCut;
    memoMacrosText->Lines->Assign(Macros);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::btnAddMacroClick(TObject *Sender)
{
String macName=editMacrosName->Text.Trim();
if (macName!="")
    {
    if (!GetMacros(macName))
        {
        TMacros *Macros=new TMacros;
        Macros->MacrosName=macName;
        Macros->ShortCut=HotKey->HotKey;
        Macros->Assign(memoMacrosText->Lines);
        listMacroses->Items->AddObject(macName,Macros);
        FMacrosList->Add(Macros);
        }
    else
        ShowMessage("Макрос с таким именем уже есть");
    }
else
    ShowMessage("Необходимо ввести имя макроса");


}
//---------------------------------------------------------------------------
void __fastcall TfrmMacros::listMacrosesClick(TObject *Sender)
{
ShowActiveMacros();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMacros::btnDelMacroClick(TObject *Sender)
{
int ii=listMacroses->ItemIndex;
if (ii>=0)
    {
    TMacros* Macros=FMacrosList->Items[ii];
    delete Macros;
    FMacrosList->Items[ii]=NULL;
    FMacrosList->Delete(ii);
    listMacroses->Items->Delete(ii);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMacros::btnWriteMacroClick(TObject *Sender)
{
int ii=listMacroses->ItemIndex;
if (ii>=0)
    {
    TMacros *Macros=FMacrosList->Items[ii];
    String macName=editMacrosName->Text.Trim();
    TMacros *MR=GetMacros(macName);
    if ((MR==NULL)||(MR==Macros))
        {
        Macros->MacrosName=macName;
        Macros->ShortCut=HotKey->HotKey;
        Macros->Assign(memoMacrosText->Lines);
        listMacroses->Items->Strings[ii]=macName;
        }
    else
        ShowMessage("Макрос с таким именем уже есть");
    }
}
//---------------------------------------------------------------------------

