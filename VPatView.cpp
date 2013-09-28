//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VPatView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define TOPSPACE 18
#define ITEMSPACE 8
#define CAPTIONSPACE 4
#define LEFTSPACE 8
#define RIGHTSPACE 8

TVPatFrm *VPatFrm;
//---------------------------------------------------------------------------
__fastcall TVPatFrm::TVPatFrm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVPatFrm::FormCreate(TObject *Sender)
{
FOldPatName="";
WorkPat=new TDrawPattern;
String Folder=Application->ExeName;
int Pos=Folder.LastDelimiter("\\");
if (Pos)
    {
    Folder.Delete(Pos+1,64);
    Folder=Folder+"VPatterns\\*.vp";
    TSearchRec sr;
    if (!FindFirst(Folder,faAnyFile,sr))
        {
        do
            {
            int p=sr.Name.LastDelimiter(".");
            ListBox1->Items->Add(sr.Name.SubString(1,p-1));
            }
        while (!FindNext(sr));
        FindClose(sr);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TVPatFrm::FormDestroy(TObject *Sender)
{
delete WorkPat;
}
//---------------------------------------------------------------------------
void __fastcall TVPatFrm::ListBox1DblClick(TObject *Sender)
{
if (ListBox1->ItemIndex>=0)
    Edit1->Text=ListBox1->Items->Strings[ListBox1->ItemIndex];
}
//---------------------------------------------------------------------------

String __fastcall TVPatFrm::GetPatFileName(String s)
{
if (s=="")
    return "";
String Folder=Application->ExeName;
int Pos=Folder.LastDelimiter("\\");
if (Pos)
    {
    Folder.Delete(Pos+1,64);
    Folder+=String("VPatterns\\")+s+String(".vp");
    return Folder;
    }
return "";
}

String __fastcall TVPatFrm::GetCurPatFileName(void)
{
return GetPatFileName(Edit1->Text);
}

void __fastcall TVPatFrm::SetCurPatFileName(String Name)
{
String FileN=Name.SubString(Name.LastDelimiter("\\")+1,1000);
FOldPatName=FileN.SubString(1,FileN.LastDelimiter(".")-1);
Edit1->Text=FOldPatName;
}


void __fastcall TVPatFrm::ShowPattern(TDrawPattern *pat)
{
while (GroupBox2->ControlCount)
    delete GroupBox2->Controls[GroupBox2->ControlCount-1];
int h=TOPSPACE;
for (int i=0;i<pat->Figures->Count;i++)
    {
    TPatFigure *fig=pat->Figures->Items[i];
    TPatLabel *lab=dynamic_cast<TPatLabel*>(fig);
    if (lab)
        {
        TLabel *label=new TLabel(GroupBox2);
        TEdit *edit=new TEdit(GroupBox2);
        label->Top=h;
        label->Left=LEFTSPACE;
        label->Caption=lab->Caption;
        label->Parent=GroupBox2;
        h+=label->Height+CAPTIONSPACE;
        edit->Top=h;
        edit->Left=LEFTSPACE;
        edit->Width=GroupBox2->Width-LEFTSPACE-RIGHTSPACE;
        edit->Anchors=edit->Anchors<<akRight;
        edit->Text=lab->Text;
        edit->Parent=GroupBox2;
        edit->Tag=(int)lab;
        edit->OnChange=EditChange;
        h+=edit->Height+ITEMSPACE;
        }
    }
Button3->Enabled=false;
}

void __fastcall TVPatFrm::EditChange(TObject *Sender)
{
Button3->Enabled=true;
}

void __fastcall TVPatFrm::Edit1Change(TObject *Sender)
{
Button1->Enabled=Edit1->Text!="";
}
//---------------------------------------------------------------------------

void __fastcall TVPatFrm::ListBox1Click(TObject *Sender)
{
if (ListBox1->ItemIndex>=0)
    {
    String s=GetPatFileName(ListBox1->Items->Strings[ListBox1->ItemIndex]);
    if (s!="")
        WorkPat->LoadFromFile(s);
    ShowPattern(WorkPat);
    }
}
//---------------------------------------------------------------------------

void __fastcall TVPatFrm::Button3Click(TObject *Sender)
{
for (int i=0;i<GroupBox2->ControlCount;i++)
    {
    TEdit *edit=dynamic_cast<TEdit*>(GroupBox2->Controls[i]);
    if (edit)
        if (edit->Tag)
            {
            TPatLabel *lab=(TPatLabel*)(edit->Tag);
            lab->Text=edit->Text;
            }
    }
String s=GetPatFileName(ListBox1->Items->Strings[ListBox1->ItemIndex]);
if (s!="")
    WorkPat->SaveToFile(s);
Button3->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TVPatFrm::FormShow(TObject *Sender)
{
Edit1->Text=FOldPatName;
}
//---------------------------------------------------------------------------

void __fastcall TVPatFrm::Button1Click(TObject *Sender)
{
FOldPatName=Edit1->Text;
}
//---------------------------------------------------------------------------

