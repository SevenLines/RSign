//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RoadMark.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMarkParam *frmMarkParam;
String CenterFilter="1.1 1.3 1.5 1.6 1.7 1.11";
String BorderFilter="1.2.1 1.2.2 1.7";
//---------------------------------------------------------------------------
__fastcall TfrmMarkParam::TfrmMarkParam(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMarkParam::BuildKindList(void)
{
FDict->TextPropByClasses(ListKinds->Items,MARKKINDCODE);
if (comboKind->ItemIndex>0)
    {
    String Filter;
    if (comboKind->ItemIndex==1)
        Filter=CenterFilter;
    else
        Filter=BorderFilter;
    ListKinds->Items->BeginUpdate();
    for (int i=ListKinds->Items->Count-1;i>=0;i--)
        {
        TTextPropRec *prec=(TTextPropRec*)ListKinds->Items->Objects[i];
        if (Filter.Pos(prec->ShortText)==0)
            ListKinds->Items->Delete(i);
        }
    ListKinds->Items->EndUpdate();
    }
if (FObj)
    for (int i=0;i<ListKinds->Items->Count;i++)
        {
        TTextPropRec *prec=(TTextPropRec*)ListKinds->Items->Objects[i];
        if (prec->Id==FObj->Kind)
            {
            ListKinds->ItemIndex=i;
            break;
            }
        }
}

bool __fastcall TfrmMarkParam::Execute(TDictSource *dict,TRoadMark *obj)
{
FDrawMan->Shared=MainForm->Shared;
FDict=dict;
FObj=obj;
if (FObj)
    {
    editStart->Text=FObj->L/100;
    editEnd->Text=FObj->LMax/100;
    if (obj->Direction==roUnDirect)
        comboDirection->ItemIndex=1;
    else
        comboDirection->ItemIndex=0;
    updK->Position=obj->K;
    updX->Position=obj->Offset;
    }
BuildKindList();
return ShowModal()==mrOk;
}

void __fastcall TfrmMarkParam::FormCreate(TObject *Sender)
{
FDrawMan=new TDrawManager();
FDrawMan->Road=new TRoad(0,0);;
FDrawMan->BaseScaleL=2000;
FDrawMan->BaseScaleX=500;
FDrawMan->Dict=FDict;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMarkParam::FormDestroy(TObject *Sender)
{
delete FDrawMan->Road;
FDrawMan->Road=NULL;
delete FDrawMan;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMarkParam::comboKindChange(TObject *Sender)
{
switch (comboKind->ItemIndex)
    {
    case 1:
        {
        comboDirection->ItemIndex=0;
        updK->Position=0;
        updX->Position=0;
        break;
        }
    case 2:
        {
        comboDirection->ItemIndex=1;
        updK->Position=1000;
        updX->Position=-20;
        break;
        }
    case 3:
        {
        comboDirection->ItemIndex=0;
        updK->Position=1000;
        updX->Position=-20;
        break;
        }
    }
BuildKindList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMarkParam::ListKindsDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
HDC dc = ((TListBox *)Control)->Canvas->Handle;
((TListBox *)Control)->Canvas->FillRect(Rect);
TTextPropRec *prec=(TTextPropRec*)ListKinds->Items->Objects[Index];
int pid=prec->Id;
int drwcls=FDict->SelectDrwParam(ROADMARKCODE,pid,1);

String s=prec->ShortText;
DrawText(dc,s.c_str(),s.Length(),&TRect(Rect.left,Rect.top+2,Rect.right-64,Rect.bottom-2),DT_WORDBREAK);

if (drwcls>0)
      {
      TDrwClassesRec *Cls=FDict->DrwClasses->Items[drwcls];
      TDrawContents *Cont=new TDrawBitmap();
      int w=Rect.Right-Rect.Left-64;
      int h=Rect.Bottom-Rect.Top-4;
      Cont->SetSize(w,h);
      Cont->SetParam(0,1,0,1);
      SetBkMode(dc,TRANSPARENT);
      TExtPolyline Poly(2,0);
      Poly[0].x=2;
      Poly[0].y=h>>1;
      Poly[1].x=w-2;
      Poly[1].y=h>>1;
      Poly.Codes[1]=1;
      Cont->PrepareUpdating();
      for (int i=0;i<MAXDRWPARAM;i++)
          if (Cls->DrwParamId[i]>0)
            {
            TDrwParamRec *Rec=FDict->DrwParams->Items[Cls->DrwParamId[i]];
            TRect MRect;
            FDrawMan->CallDrawFunc(Cont,&Poly,Rec,&MRect,2000,500,pkGorizontal,pdDirect,PixelsPerInch/2.54,i==0);
            }
       Cont->FinishUpdating();
       Cont->DrawTo(((TListBox *)Control)->Canvas,Rect.Left+62,Rect.Top+2);
       delete Cont;
      }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMarkParam::Button1Click(TObject *Sender)
{
if (FObj)
    {
    int startl=editStart->Text.ToInt()*100;
    int endl=editEnd->Text.ToInt()*100;
    if (startl<endl)
        {
        if (ListKinds->ItemIndex>=0)
            {
            FObj->SetL(startl);
            FObj->SetLMax(endl);
            FObj->SetDirection(comboDirection->ItemIndex==1 ? roUnDirect: roDirect);
            FObj->SetK(updK->Position);
            FObj->SetOffset(updX->Position);
            TTextPropRec *prec=(TTextPropRec*)ListKinds->Items->Objects[ListKinds->ItemIndex];
            FObj->SetKind(TMarkKind(prec->Id));
            ModalResult=mrOk;
            }
        else
            ShowMessage("�� ������ ��� ��������");
        }
    else
        ShowMessage("��������� ����� ����� ������ ������");
    }
}
//---------------------------------------------------------------------------

