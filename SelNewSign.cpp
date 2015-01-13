//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelNewSign.h"
#include "RoadObj.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddSignFrm *AddSignFrm;
//---------------------------------------------------------------------------
__fastcall TAddSignFrm::TAddSignFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool __fastcall TAddSignFrm::Execute(TDictSource* Dict,int NumCode,int variation)
{
FDict=Dict;
FDrawMan->Dict=FDict;
FDrawMan->Shared=MainForm->Shared;
ListTypes->Items->Clear();
for (int i=SGNCODE+1;i<SGNCODE+9;i++)
        ListTypes->Items->Add(Dict->ObjClasses->Items[i]->Title);
ListTypes->ItemIndex=FOldClass;
Panel3->Visible=false;
FNumCode=NumCode;
FSignClass=FOldClass;
if (FNumCode)
    {
    String S=FDict->GetShortTitle(NumCode);
    GOSTCode->Text=S;
    int pos=S.Pos(".");
    if (pos)
        {
        try
            {int ClassNum=S.SubString(1,pos-1).Trim().ToInt();
             if ((ClassNum>0)&&(ClassNum<8))
                {
                 FSignClass=ClassNum;
                 ListTypes->ItemIndex=ClassNum-1;
                 SetListKinds();
                 for (int i=0;i<ListKinds->Items->Count;i++)
                    {
                    TTextPropRec *TRec=dynamic_cast<TTextPropRec*>(ListKinds->Items->Objects[i]);
                    if (TRec)
                        if (TRec->Id==NumCode)
                            {
                            ListKinds->ItemIndex=i;
                            SetVariantList();
                            if (variation)
                                {
                                String strvar=String(variation);
                                for (int j=0;j<VariantList->Items->Count;j++)
                                    {
                                    if (VariantList->Items->Strings[j]==strvar)
                                        {
                                        VariantList->ItemIndex=j;
                                        break;
                                        }
                                    }
                                }
                            break;
                            }
                    }
                }
            }
        catch (...) {}
        }
    }
return ShowModal()==mrOk;
}

String __fastcall TAddSignFrm::GetCode(void)
{
if (ListKinds->ItemIndex>=0)
        return ((TTextPropRec*)(ListKinds->Items->Objects[ListKinds->ItemIndex]))->ShortText;
return "";
}

void __fastcall TAddSignFrm::TestAddEnabled(void)
{
Button1->Enabled=(ListKinds->ItemIndex>=0)&&(ListTypes->ItemIndex>=0);
}

void __fastcall TAddSignFrm::ListTypesClick(TObject *Sender)
{
FSignClass=ListTypes->ItemIndex+1;
SetListKinds();
TestAddEnabled();
}

void __fastcall TAddSignFrm::SetListKinds(void)
{
if (ListTypes->ItemIndex>=0)
    {
    ListKinds->Items->BeginUpdate();
    ListKinds->Items->Clear();
    FDict->TextPropByClasses(ListKinds->Items,SIGNGOSTCODE+ListTypes->ItemIndex);
    FOldClass=ListTypes->ItemIndex;
    ListKinds->Items->EndUpdate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::ListKindsClick(TObject *Sender)
{
if (ListKinds->ItemIndex>=0)
    {
    GOSTCode->Text=GetCode();
    FNumCode=((TTextPropRec*)(ListKinds->Items->Objects[ListKinds->ItemIndex]))->Id;
    SetVariantList();
    TestAddEnabled();
    }
}
//---------------------------------------------------------------------------

int __fastcall TAddSignFrm::GetValue(char *s)
{
int Val=0;
while (*s)
    {
    if ((*s<='9')&&(*s>='0'))
        Val=Val*10+*s-'0';
    else if ((*s!='=')&&(*s!=' '))
        break;
    s++;
    }
return Val;
}

void __fastcall TAddSignFrm::SetVariantList(void)
{
DrwVariantList->ClearList();
VariantList->Items->BeginUpdate();
VariantList->Items->Clear();
if (ListKinds->ItemIndex>=0)
    {
    TTextPropRec* TRec=(TTextPropRec*)ListKinds->Items->Objects[ListKinds->ItemIndex];
    TObjList<TDrwClassesRec> *Lst=FDict->DrwClasses;
    int n=Lst->Count;
    for (int i=0;i<n;i++)
        {
        TDrwClassesRec *Drw=Lst->Items[i];
        if (Drw)
          if (Drw->Condition!="")
            {
            int p=Drw->Condition.Pos("NumRoadSign");
            if (p)
                {
                int numrs=GetValue(Drw->Condition.c_str()+p+11);
                if (numrs==TRec->Id)
                    {
                    p=Drw->Condition.Pos("ViewKind");
                    if (p)
                        {
                        int numkn=GetValue(Drw->Condition.c_str()+p+8);
                        DrwVariantList->Add(Drw);
                        VariantList->Items->Add(String(numkn));
                        }
                    }
                }
            }
        }
    }
VariantList->Items->EndUpdate();
FVariation=0;
Panel3->Visible=VariantList->Items->Count;
}

void __fastcall TAddSignFrm::ListKindsDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
HDC dc = ((TListBox *)Control)->Canvas->Handle;
((TListBox *)Control)->Canvas->FillRect(Rect);
String s=ListKinds->Items->Strings[Index];
DrawText(dc,s.c_str(),s.Length(),&TRect(Rect.left,Rect.top+2,Rect.right-64,Rect.bottom-2),DT_WORDBREAK);

int pid=((TTextPropRec*)(ListKinds->Items->Objects[Index]))->Id;
int drwcls=FDict->SelectDrwParam(SGNCODE+1+ListTypes->ItemIndex,pid,1);

if (drwcls>0)
      {
      TDrwClassesRec *Cls=FDict->DrwClasses->Items[drwcls];
      if (Cls->DrwParamId[0]>0)
        {
          TDrwParamRec *Rec=FDict->DrwParams->Items[Cls->DrwParamId[0]];
          TDrawContents *Cont=new TDrawBitmap();
          int w=60;
          int h=Rect.Bottom-Rect.Top-4;
          Cont->SetSize(w,h);
          Cont->SetParam(0,1,0,0,1);
          SetBkMode(dc,TRANSPARENT);

          TRect MRect;
          TExtPolyline Poly(1,1);
          Poly[0].x=w>>1;
          Poly[0].y=h>>1;

          Cont->PrepareUpdating();
          FDrawMan->CallDrawFunc(Cont,&Poly,Rec,&MRect,2000,800,pkGorizontal,pdDirect,PixelsPerInch/2.54,true);
          Cont->FinishUpdating();
          Cont->DrawTo(((TListBox *)Control)->Canvas,Rect.Right-64,Rect.Top+2);
          delete Cont;
          }
      }
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::FormCreate(TObject *Sender)
{
FOldClass=0;
FDrawMan=new TDrawManager();
FDrawMan->Road=new TRoad(0,0);;
FDrawMan->BaseScaleL=2000;
FDrawMan->BaseScaleX=500;
FDrawMan->Dict=FDict;
FDrawMan->Shared=MainForm->Shared;
DrwVariantList=new TObjList<TDrwClassesRec>;
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::FormDestroy(TObject *Sender)
{
DrwVariantList->ClearList();
delete DrwVariantList;
delete FDrawMan->Road;
FDrawMan->Road=NULL;
delete FDrawMan;
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::FormShow(TObject *Sender)
{
TestAddEnabled();    
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::VariantListDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
HDC dc = ((TListBox *)Control)->Canvas->Handle;
((TListBox *)Control)->Canvas->FillRect(Rect);
String s=VariantList->Items->Strings[Index];
DrawText(dc,s.c_str(),s.Length(),&TRect(Rect.left,Rect.top+2,Rect.right-64,Rect.bottom-2),DT_WORDBREAK);
TDrwClassesRec *Drw=dynamic_cast<TDrwClassesRec*>(DrwVariantList->Items[Index]);
if (Drw->DrwParamId[0]>0)
    {
    TDrwParamRec3 *Rec=dynamic_cast<TDrwParamRec3*>(FDict->DrwParams->Items[Drw->DrwParamId[0]]);
    TDrawContents *Cont=new TDrawBitmap();
    int h=Rect.Bottom-Rect.Top-4;
    int w=Rect.Right-Rect.Left-12;
    Cont->SetSize(w,h);
    Cont->SetParam(0,1,0,0,1);
    SetBkMode(dc,TRANSPARENT);
    TRect MRect;
    TExtPolyline Poly(1,1);
    Poly[0].x=w>>1;
    Poly[0].y=h>>1;
    Cont->PrepareUpdating();
    FDrawMan->CallDrawFunc(Cont,&Poly,Rec,&MRect,2000,800,pkGorizontal,pdDirect,PixelsPerInch/2.54,true);
    Cont->FinishUpdating();
    Cont->DrawTo(((TListBox *)Control)->Canvas,Rect.Right-w-2,Rect.Top+2);
    delete Cont;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::VariantListMeasureItem(TWinControl *Control,
      int Index, int &Height)
{
TListBox *Lst=dynamic_cast<TListBox*>(Control);
TDrwClassesRec *Drw=dynamic_cast<TDrwClassesRec*>(Lst->Items->Objects[Index]);
Height=32;
if (Drw)
    if (Drw->DrwParamId[0]>0)
    {
    TDrwParamRec3 *Rec=dynamic_cast<TDrwParamRec3*>(FDict->DrwParams->Items[Drw->DrwParamId[0]]);
    Height=(32*Rec->Height)/120;
    if (Height<32)
        Height=32;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::VariantListClick(TObject *Sender)
{
if (VariantList->ItemIndex>=0)
    FVariation=VariantList->Items->Strings[VariantList->ItemIndex].ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::Splitter1Moved(TObject *Sender)
{
ListKinds->Invalidate();
VariantList->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::FormResize(TObject *Sender)
{
ListKinds->Invalidate();
VariantList->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TAddSignFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   switch(Key){
     case VK_RETURN:
       Button1->Click();
     break;
     case VK_ESCAPE:
     case VK_END:
       Button2->Click();
     break;
   }
}
//---------------------------------------------------------------------------

