//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ObjForm.h"
#include "MainUnit.h"
#include "Mask.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


// Минимальное расстояние от левого края группы до подписи
#define LEFTSP 15
#define RIGHTSP 15
// Расстояние от подписи до елемента редактирования
#define TABSP 5
// Расстояние от верха до первого элемента
#define TOPSP 25
// Расстояние между элементами по вертикали
#define VERTSP 5
// Расстояние по вертикали от начала элемента до подписи
#define VCSP 3

TObjFrm *ObjFrm;

int OldX=0;
int OldY=0;


//---------------------------------------------------------------------------
__fastcall TObjFrm::TObjFrm(TComponent* Owner)
    : TForm(Owner)
{
Dict=NULL;
Data=NULL;
ModalRes=NULL;
}

void __fastcall TObjFrm::WndProc(TMessage &Mes)
{
if ((Mes.Msg==CM_DATARELOAD)||(Mes.Msg==CM_DELETEGROUP))
    {
    if (Data)
        if (Mes.LParam==(int)Data)
            {
            Close();
            }
    return;
    }
else if (Mes.Msg==CM_CLOSEDATASOURCE)
    {
    if ((int)Data==Mes.LParam)
        Close();
    return;
    }
else if (Mes.Msg==CM_REMOVEOBJ)
    {
    if (Obj==(TRoadObject*)Mes.WParam)
        {
        Close();
        }
    return;
    }
else if (Mes.Msg==CM_UPDATEOBJ)
    {
    if (Obj==(TRoadObject*)Mes.WParam)
        {
        Obj->UpdateCard(this);
        }                          
    return;
    }
TForm::WndProc(Mes);
}

//---------------------------------------------------------------------------
TGroupBox* __fastcall TObjFrm::SelectGroup(int n)
{
switch (n)
    {
    case 1: return CGroup;
    case 2: return ChrGroup;
    case 3: return PlaceGroup;
    }
return NULL;
}
void __fastcall TObjFrm::AlignGroup(int n)
{
Constraints->MinHeight=0;
Constraints->MaxHeight=0;
TGroupBox *g=SelectGroup(n);
int maxwid=0;
for (int i=0;i<g->ControlCount;i++)
    {
    TLabel *l=dynamic_cast<TLabel*>(g->Controls[i]);
    if (l)
        if (maxwid<l->Width)
            maxwid=l->Width;
    }
for (int i=0;i<g->ControlCount;i++)
    {
    TLabel *l=dynamic_cast<TLabel*>(g->Controls[i]);
    if (l)
        l->Left=LEFTSP+maxwid-l->Width;
    else
        {
        TControl *c=dynamic_cast<TControl*>(g->Controls[i]);
        if (c)
            {
            c->Left=LEFTSP+maxwid+TABSP;
            c->Width=g->Width-LEFTSP-maxwid-TABSP-RIGHTSP;
            }
        }
    }
Height=CGroup->Height+ChrGroup->Height+PlaceGroup->Height+70;
Button1->Top=TabSheet1->ClientHeight-5-Button1->Height;
Button2->Top=TabSheet1->ClientHeight-5-Button2->Height;
Button3->Top=TabSheet2->ClientHeight-5-Button3->Height;
Button4->Top=TabSheet2->ClientHeight-5-Button4->Height;
DocListBox->Width=TabSheet2->ClientWidth-2*DocListBox->Left;
DocListBox->Height=CGroup->Height;//+ChrGroup->Height+PlaceGroup->Height;
Constraints->MinHeight=Height;
Constraints->MaxHeight=Height;
}

void __fastcall TObjFrm::AddRef(TControl* ctrl,int id)
{
if (id>=CompList->Count)
        CompList->Count=id+1;
CompList->Items[id]=ctrl;
}

void __fastcall TObjFrm::AddMask(int gr,int id,String Title,String Mask,String Val)
{
TGroupBox *g=SelectGroup(gr);
int h=g->Height;
TLabel *l=new TLabel(this);
l->Parent=g;
l->AutoSize=true;
l->Caption=Title;
l->Top=h+VCSP;
TMaskEdit *m=new TMaskEdit(this);
m->Parent=g;
m->Top=h;
m->EditMask=Mask;
m->Text=Val;
m->OnChange=ElemChange;
m->Anchors=m->Anchors<<akRight;
g->Height=h+m->Height+VERTSP;
AddRef(m,id);
}

void __fastcall TObjFrm::AddText(int gr,int id,String Title,String Val,bool enable)
{
TGroupBox *g=SelectGroup(gr);
int h=g->Height;
TLabel *l=new TLabel(this);
l->Parent=g;
l->AutoSize=true;
l->Caption=Title;
l->Top=h+VCSP;
TEdit *m=new TEdit(this);
m->Parent=g;
m->Top=h;
m->Text=Val;
m->Anchors=m->Anchors<<akRight;
m->OnChange=ElemChange;
m->Enabled=enable;

g->Height=h+m->Height+VERTSP;
AlignGroup(gr);
AddRef(m,id);
}

void __fastcall TObjFrm::AddCombo(int gr,int id,String Title,int vid,bool enable)
{
TGroupBox *g=SelectGroup(gr);
int h=g->Height;
TLabel *l=new TLabel(this);
l->Parent=g;
l->AutoSize=true;
l->Caption=Title;
l->Top=h+VCSP;
TComboBox *c=new TComboBox(this);
c->Parent=g;
c->Style=csDropDownList;
c->Top=h;
c->Tag=id;
Dict->TextPropByClasses(c->Items,id);
for (int i=0;i<c->Items->Count;i++)
    {
    TTextPropRec *rec=(TTextPropRec*)c->Items->Objects[i];
    if (rec->Id==vid)
        {
        c->ItemIndex=i;
        break;
        }
    }
c->Anchors=c->Anchors<<akRight;
c->OnChange=ElemChange;
c->Enabled=enable;
g->Height=h+c->Height+VERTSP;
AlignGroup(gr);
AddRef(c,id);
}

void __fastcall TObjFrm::AddCheckBox(int gr,int id,String Title,int Val,bool enable)
{
TGroupBox *g=SelectGroup(gr);
int h=g->Height;
TLabel *l=new TLabel(this);
l->Parent=g;
l->AutoSize=true;
l->Caption=Title;
l->Top=h+VCSP;
TCheckBox *c=new TCheckBox(this);
c->Parent=g;
c->Top=h;
c->Checked=Val;
c->Anchors=c->Anchors<<akRight;
c->OnClick=ElemChange;
c->Enabled=enable;

g->Height=h+c->Height+VERTSP;
AlignGroup(gr);
AddRef(c,id);
}

String __fastcall TObjFrm::GetAsString(int n)
{
String res="";
if (CompList->Items[n])
    {
    TCustomEdit *m=dynamic_cast<TCustomEdit*>((TObject*)CompList->Items[n]);
    if (m)
        res=m->Text;
    else
        res=String(GetAsInt(n));
    }
return res;
}

int __fastcall TObjFrm::GetAsInt(int n)
{
int res=0;
if (CompList->Items[n])
    {
    TComboBox *c=dynamic_cast<TComboBox*>((TObject*)CompList->Items[n]);
    if (c)
        {
        if (c->ItemIndex>=0)
            res=((TTextPropRec*)c->Items->Objects[c->ItemIndex])->Id;
        }
    else
        {
        TCheckBox *ch=dynamic_cast<TCheckBox*>((TObject*)CompList->Items[n]);
        if (ch)
              res=ch->Checked;
        }
    }
return res;
}

void __fastcall TObjFrm::SetAsString(int n,String val)
{
if (CompList->Items[n])
    {
    TCustomEdit *m=dynamic_cast<TCustomEdit*>((TObject*)CompList->Items[n]);
    if (m)
        m->Text=val;
    else
        {
        try {SetAsInt(n,val.ToInt());}
        catch (...)
            {}
        }
    }
}

void __fastcall TObjFrm::SetAsInt(int n,int val)
{
if (CompList->Items[n])
    {
    TComboBox *c=dynamic_cast<TComboBox*>((TObject*)CompList->Items[n]);
    if (c)
        {
        for (int i=0;i<c->Items->Count;i++)
            {
            TTextPropRec *rec=(TTextPropRec*)c->Items->Objects[i];
            if (rec->Id==val)
                {
                c->ItemIndex=i;
                break;
                }
            }
        }
    else
        {
        TCheckBox *ch=dynamic_cast<TCheckBox*>((TObject*)CompList->Items[n]);
        ch->Checked=val;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TObjFrm::FormDeactivate(TObject *Sender)
{
if (AutoClose->Down)
    {
    Close();
    }
}

void __fastcall TObjFrm::SetChanged(bool b)
{
FChanged=b;
Button1->Enabled=FChanged;
}

//---------------------------------------------------------------------------
void __fastcall TObjFrm::BuildForm(TDictSource *dict,TDtaSource* data,TRoadObject *obj)
{
Data=data;
Dict=dict;
Obj=obj;
Caption=Dict->ObjClasses->Items[Obj->DictId]->Title;
Obj->BuildCard(this);
Data->GetDocuments(DocListBox->Items,Obj->Id,Obj->DictId);
Button3->Enabled=DocListBox->Items->Count>0;
DocListBox->ItemIndex=0;
SetChanged(false);
}

void __fastcall TObjFrm::ClearGroup(TWinControl *wnd)
{
while (wnd->ControlCount)
    delete wnd->Controls[0];
wnd->Height=TOPSP;
}

void __fastcall TObjFrm::ClearGroups(void)
{
ClearGroup(CGroup);
ClearGroup(ChrGroup);
ClearGroup(PlaceGroup);
SetChanged(false);
}

void __fastcall TObjFrm::FormCreate(TObject *Sender)
{
CompList=new TList;
CGroup->Height=TOPSP;
ChrGroup->Height=TOPSP;
PlaceGroup->Height=TOPSP;
if (OldX)
    Left=OldX;
if (OldY)
    Top=OldY;
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
OldX=Left;
OldY=Top;
delete CompList;
CompList=NULL;
Release();
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::ElemChange(TObject *Sender)
{
SetChanged(true);
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::Button2Click(TObject *Sender)
{
if (FChanged)
    {
    Obj->UpdateCard(this);
    SetChanged(false);
    }
else
    {
    if (ModalRes)
        *ModalRes=mrCancel;
    Close();
    Release();
    }
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::Button1Click(TObject *Sender)
{
if (FChanged)
    {
    Obj->SaveCard(this);
    Data->SortByPlacement();
    Data->BuildRoadMetrics();
    MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)Obj,(int)Data);
    }
if (ModalRes)
    *ModalRes=mrOk;
Close();
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::Button3Click(TObject *Sender)
{
if (DocListBox->ItemIndex>=0)
    {
    TDocument *doc=dynamic_cast<TDocument*>(DocListBox->Items->Objects[DocListBox->ItemIndex]);
    if (doc)
        doc->Show();    
    }
}
//---------------------------------------------------------------------------

void __fastcall TObjFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   switch(Key){
     case VK_RETURN:
       Button1->Click();
     break;
     case VK_ESCAPE:
       Button2->Click();
     break;
   } 
}
//---------------------------------------------------------------------------

