//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "GdiEForm.h"
#include "FileSour.h"
#include "DBDataSource.h"
#include "PenForm.h"
#include "ProcForm.h"
#include "BrForm.h"
#include "SqlEdit.h"
#include "VisCondE.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
Manager=new TResManager;
Shared=NULL;
Factory=new TRoadObjFactory;
MovedIndex=-1;
MovedTextIndex=-1;
FDrawMan=new TDrawManager();
FRoad=new TRoad(0,0);
FDrawMan->Road=FRoad;
CurrentDrw=new TDrwClassesRec;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Click(TObject *Sender)
{
Dict=Manager->AddFileDictSource(0);
Shared=new TFileSharedObjSource;
Shared->Load();
ShowObjTree(ObjTree,Dict);
ShowObjTree(VisObjTree,Dict);
ShowPropList(Dict);
BuildPagesList(Dict);
ShowGdiList();
ShowVisList(NULL);
FDrawMan->Dict=Dict;
FDrawMan->Shared=Shared;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowGdiList(void)
{
GDIPens->Items->Clear();
GDIBrushs->Items->Clear();
GDIPens->Items->AddObject("",(TObject*)(-BLACK_PEN-256));
GDIPens->Items->AddObject("пустое перо",(TObject*)(-NULL_PEN-256));
GDIPens->Items->AddObject("белое перо",(TObject*)(-WHITE_PEN-256));
GDIBrushs->Items->AddObject("",(TObject*)(-BLACK_BRUSH-256));
GDIBrushs->Items->AddObject("",(TObject*)(-DKGRAY_BRUSH-256));
GDIBrushs->Items->AddObject("",(TObject*)(-GRAY_BRUSH-256));
GDIBrushs->Items->AddObject("",(TObject*)(-LTGRAY_BRUSH-256));
GDIBrushs->Items->AddObject("пустая кисть",(TObject*)(-NULL_BRUSH-256));
GDIBrushs->Items->AddObject("белая кисть",(TObject*)(-WHITE_BRUSH-256));
for (int i=0;i<Shared->GorzGDIObjects->Count;i++)
        {
        void *obj=Shared->GorzGDIObjects->Items[i];
        if (obj)
                {
                int t=GetObjectType(obj);
                if (t==OBJ_EXTPEN)
                        GDIPens->Items->AddObject("",(TObject*)i);
                else if (t==OBJ_BRUSH)
                        GDIBrushs->Items->AddObject("",(TObject*)i);
                }
        }
}


void __fastcall TMainForm::BuildPagesList(TDictSource *Dict)
{
PagesList->Clear();
CurPage->Items->Clear();
for (int i=0;i<Dict->DrwPages->Count;i++)
    {
    TDrwPageRec *Rec=Dict->DrwPages->Items[i];
    PagesList->Items->AddObject(Rec->ShortName,Rec);
    CurPage->Items->AddObject(Rec->ShortName,Rec);
    }
CurPage->ItemIndex=0;
}

int __fastcall TMainForm::PageIndex(void)
{
int Res=0;
if (CurPage->ItemIndex>=0)
    {
    TDrwPageRec *Rec=dynamic_cast<TDrwPageRec*>(CurPage->Items->Objects[CurPage->ItemIndex]);
    if (Rec)
        Res=Rec->Id;
    }
return Res;
}

int __fastcall TMainForm::PageFlags(void)
{
int Res=0;
for (int i=0;i<PagesList->Count;i++)
    {
    TDrwPageRec *Rec=dynamic_cast<TDrwPageRec*>(PagesList->Items->Objects[i]);
    if ((Rec)&&PagesList->Checked[i])
        Res|=Rec->Id;
    }
return Res;
}

void __fastcall TMainForm::ShowPagesFlag(TDrwClassesRec *Rec)
{
int n=Rec->PagesSet;
for (int i=0;i<PagesList->Items->Count;i++)
    {
    bool flag=false;
    TDrwPageRec *Rec=dynamic_cast<TDrwPageRec*>(PagesList->Items->Objects[i]);
    if (Rec)
        if (Rec->Id&n)
            flag=true;
    PagesList->Checked[i]=flag;
    }
}

void __fastcall TMainForm::ShowVisList(TObjMetaClass *Meta)
{
VisList->Clear();
int n=Dict->DrwParams->Count;
bool *Pres=new bool [n];
for (int i=0;i<n;i++)
    Pres[i]=false;
if (Meta)
    for (int i=0;i<Dict->DrwClasses->Count;i++)
        {
        TDrwClassesRec *Rec=Dict->DrwClasses->Items[i];
        if (Rec)
            if (Rec->ObjClassId==Meta->Id)
                for (int j=0;j<MAXDRWPARAM;j++)
                    Pres[Rec->DrwParamId[j]]=true;
        }
for (int i=0;i<n;i++)
    if (Pres[i])
        {
        TDrwParamRec *Par=Dict->DrwParams->Items[i];
        if (Par)
            VisList->Items->AddObject("",(TObject*)Par);
        }
delete[] Pres;
}

void __fastcall TMainForm::ShowObjTree(TTreeView* tr,TDictSource *Dict)
{
tr->Items->Clear();
Dict->BuildClassesTree(tr,NULL);
}


void __fastcall TMainForm::ShowPropList(TDictSource *Dict)
{
PropList->Items->BeginUpdate();
ProperList->Items->BeginUpdate();
PropList->Items->Clear();
ProperList->Items->Clear();
for (int i=0;i<Dict->PropClasses->Count;i++)
        {
        if (Dict->PropClasses->Items[i])
                {
                PropList->Items->AddObject(Dict->PropClasses->Items[i]->PropName,(TObject*)Dict->PropClasses->Items[i]);
                ProperList->Items->AddObject(Dict->PropClasses->Items[i]->PropName,(TObject*)Dict->PropClasses->Items[i]);
                }
        }
ProperList->Items->Add("");
PropList->Items->EndUpdate();
ProperList->Items->EndUpdate();
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
TIniFile *ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
Connection->ConnectionString=ini->ReadString("Connection","String",Connection->ConnectionString);
delete ini;
for (int i=0;i<CLASSESCOUNT;i++)
        ClassList->Items->Add(ClassesNames[i]);
ClassList->ItemIndex=0;
for (int i=0;i<TYPESCOUNT;i++)
        PropType->Items->Add(TypesNames[i]);
PropType->ItemIndex=0;
}
//---------------------------------------------------------------------------

int __fastcall TMainForm::GetClassNameIndex(String s)
{
int res=-1;
for (int i=0;i<CLASSESCOUNT;i++)
        if (String(ClassesNames[i])==s)
                {res=i;break;}
return res;
}

void __fastcall TMainForm::DeleteFromCharList(int n)
{
if (MainChar->ItemIndex==n+1)
        MainChar->ItemIndex=-1;
MainChar->Items->Delete(n+1);
CharList->Items->Delete(n);
}

void __fastcall TMainForm::AddToCharList(TPropClassesRec* r)
{
MainChar->Items->AddObject(r->PropName,(TObject*)r);
CharList->Items->AddObject(r->PropName,(TObject*)r);
}


void __fastcall TMainForm::PropListDblClick(TObject *Sender)
{
if (PropList->ItemIndex>=0)
        {
        int i;
        String s=PropList->Items->Strings[PropList->ItemIndex];
        for (i=0;i<CharList->Items->Count;i++)
                if (CharList->Items->Strings[i]==s)
                        break;
        if (i<CharList->Items->Count)
                DeleteFromCharList(i);
        else
                AddToCharList((TPropClassesRec*)PropList->Items->Objects[PropList->ItemIndex]);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
if (ObjTree->Selected!=NULL)
    {
    TObjMetaClass *r=(TObjMetaClass*)ObjTree->Selected->Data;
    if (r)
        {
        String cname;
        if (ClassList->ItemIndex>=0)
            cname=ClassesNames[ClassList->ItemIndex];
        else
            cname="";
        r->SetParams(MainTable->Text,ObjFlags->Text.ToInt(),cname);
        r->ClearPropeties();
        for (int i=0;i<CharList->Items->Count;i++)
            {
            int flag=PR_NECESSARY|PR_PUBLISHED;
            if (CharList->Checked[i])
                flag|=PR_READONLY;
            r->AddProperty(flag,((TPropClassesRec*)CharList->Items->Objects[i])->Id);
            }
        if (MainChar->ItemIndex>0)
            r->SetMainProp(((TPropClassesRec*)MainChar->Items->Objects[MainChar->ItemIndex])->Id);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N3Click(TObject *Sender)
{
String path=ExtractFilePath(Application->ExeName);
SortByViewOrder();
Shared->Dump(path);
Dict->Dump(path);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GDIPensDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
((TListBox *)Control)->Canvas->FillRect(Rect);
HDC dc = ((TListBox *)Control)->Canvas->Handle;
void *oldbr=SelectObject(dc,GetStockObject(WHITE_BRUSH));
void *oldpn=SelectObject(dc,GetStockObject(NULL_PEN));
//Rectangle(dc,Rect.Left+24,Rect.Top,Rect.Right-24,Rect.Bottom);
int pi=int(GDIPens->Items->Objects[Index]);
if (pi<0)
    SelectObject(dc,GetStockObject(-pi-256));
else
    {
    void *obj=Shared->GorzGDIObjects->Items[pi];
    if (obj)
        SelectObject(dc,obj);
    }
SetBkMode(dc,TRANSPARENT);
MoveToEx(dc,Rect.Left+24,(Rect.Top+Rect.Bottom)>>1,NULL);
LineTo(dc,Rect.Right-24,(Rect.Top+Rect.Bottom)>>1);
SelectObject(dc,oldbr);
SelectObject(dc,oldpn);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GDIBrushsDrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
HDC dc = ((TListBox *)Control)->Canvas->Handle;
((TListBox *)Control)->Canvas->FillRect(Rect);
void *oldbr=SelectObject(dc,GetStockObject(WHITE_BRUSH));
void *oldpn=SelectObject(dc,GetStockObject(NULL_PEN));
int bi=int(GDIBrushs->Items->Objects[Index]);
if (bi<0)
    SelectObject(dc,GetStockObject(-bi-256));
else
    {
    void *obj=Shared->GorzGDIObjects->Items[bi];
    if (obj)
        SelectObject(dc,obj);
    }
SetBkMode(dc,TRANSPARENT);
SelectObject(dc,GetStockObject(BLACK_PEN));
Rectangle(dc,Rect.Left+24,Rect.Top+1,Rect.Right-24,Rect.Bottom-1);
SelectObject(dc,oldbr);
SelectObject(dc,oldpn);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProperListClick(TObject *Sender)
{
if (ProperList->ItemIndex>=0)
        {
        if (ProperList->ItemIndex<ProperList->Items->Count-1)
                {
                TPropClassesRec *Rec=(TPropClassesRec*)ProperList->Items->Objects[ProperList->ItemIndex];
                if (Rec)
                        {
                        PropName->Text=Rec->PropName;
                        PropShort->Text=Rec->ShortName;
                        PropClass->Text=Rec->ClassName;
                        PropField->Text=Rec->FieldName;
                        PropType->ItemIndex=Rec->Type;
                        ValList->Visible=Rec->Type==prEnum;
                        if (ValList->Visible)
                            {
                            ValList->Items->BeginUpdate();
                            ValList->Items->Clear();
                            Dict->TextPropByClasses(ValList->Items,Rec->Id);
                            ValList->Items->EndUpdate();
                            }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
if (ProperList->ItemIndex>=0)
        {
        if (ProperList->ItemIndex<ProperList->Items->Count-1)
                {
                TPropClassesRec *Rec=(TPropClassesRec*)ProperList->Items->Objects[ProperList->ItemIndex];
                if (Rec)
                        {
                        Rec->SetValue(PropName->Text,PropShort->Text,PropClass->Text,PropField->Text,TPropClassesType(PropType->ItemIndex));
                        SortTextByViewOrder(Rec->Id);
                        }
                }
        else
                {
                int n=Dict->PropClasses->FirstFree(1);
                TPropClassesRec *Rec=new TPropClassesRec(n);
                Rec->SetValue(PropName->Text,PropShort->Text,PropClass->Text,PropField->Text,TPropClassesType(PropType->ItemIndex));
                if (n>=Dict->PropClasses->Count)
                        Dict->PropClasses->Count=n+1;
                Dict->PropClasses->Items[n]=Rec;
                ProperList->Items->Objects[ProperList->ItemIndex]=(TObject*)Rec;
                ProperList->Items->Add("");
                }
        ProperList->Items->Strings[ProperList->ItemIndex]=PropName->Text;
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SortTextByViewOrder(int id)
{
int n=ValList->Items->Count;
if (n>0)
    {
    TTextPropRec **index=new TTextPropRec* [n];
    for (int i=0;i<n;i++)
        index[i]=(TTextPropRec*)ValList->Items->Objects[i];
    Dict->ChangePropOrder(id,n,index);
    delete[] index;
    }
}

void __fastcall TMainForm::SortByViewOrder(void)
{
__int32 *newnum=new __int32 [Dict->PropClasses->Count];
for (int i=0;i<ProperList->Items->Count;i++)
    {
    TPropClassesRec *Rec=(TPropClassesRec*)ProperList->Items->Objects[i];
    if (Rec)
        newnum[Rec->Id]=i+1;
    }
Dict->ChangePropClasses(0,Dict->PropClasses->Count-1,newnum);
delete[] newnum;
}

void __fastcall TMainForm::ClassListChange(TObject *Sender)
{
ClassList->Hint=Factory->GetClassInfo(ClassList->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MoveStringList(TStrings *Lst,int newindex,int &oldindex)
{
if ((newindex>=0)&&(oldindex>=0)&&(oldindex!=newindex))
    {
    if (newindex>oldindex)
        {
        Lst->InsertObject(newindex+1,Lst->Strings[oldindex],Lst->Objects[oldindex]);
        Lst->Delete(oldindex);
        }
    else
        {
        Lst->InsertObject(newindex,Lst->Strings[oldindex],Lst->Objects[oldindex]);
        Lst->Delete(oldindex+1);
        }
    oldindex=newindex;
    }
}


void __fastcall TMainForm::ProperListMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
int newindex=ProperList->ItemAtPos(Point(X,Y),true);
MoveStringList(ProperList->Items,newindex,MovedIndex);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ProperListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
MovedIndex=ProperList->ItemAtPos(Point(X,Y),true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProperListMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
MovedIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisListDrawItem(TWinControl *Control, int Index,
      TRect &Rect, TOwnerDrawState State)
{
TRect MRect;
HDC dc = ((TListBox *)Control)->Canvas->Handle;
((TListBox *)Control)->Canvas->FillRect(Rect);
void *oldbr=SelectObject(dc,GetStockObject(WHITE_BRUSH));
void *oldpn=SelectObject(dc,GetStockObject(NULL_PEN));
Rectangle(dc,Rect.Left+24,Rect.Top,Rect.Right-24,Rect.Bottom);
SelectObject(dc,oldbr);
SelectObject(dc,oldpn);
TDrwParamRec *Rec=(TDrwParamRec*)VisList->Items->Objects[Index];
if (Rec)
      {
      TDrawContents *Cont=new TDrawBitmap();
      int w=Rect.Right-Rect.Left-48;
      int h=Rect.Bottom-Rect.Top-4;
      Cont->SetSize(w,h);
      Cont->SetParam(0,1,0,1);
      SetBkMode(dc,TRANSPARENT);
      TExtPolyline * Poly;
      if (Rec->ProcId==1)
        {
        Poly=new TExtPolyline(4,1);
        (*Poly)[0].x=0;
        (*Poly)[0].y=2;
        (*Poly)[1].x=w;
        (*Poly)[1].y=2;
        (*Poly)[2].x=w;
        (*Poly)[2].y=h-2;
        (*Poly)[3].x=0;
        (*Poly)[3].y=h-2;
        }
      else if (Rec->ProcId==4)
        {
        Poly=new TExtPolyline(4,1);
        Poly->Codes[0]=0;
        Poly->Codes[2]=0;
        (*Poly)[2].x=w-12;
        (*Poly)[2].y=6;
        (*Poly)[3].x=12;
        (*Poly)[3].y=6;
        (*Poly)[0].x=12;
        (*Poly)[0].y=h-6;
        (*Poly)[1].x=w-12;
        (*Poly)[1].y=h-6;
        }
      else if (Rec->ProcId==3)
        {
        Poly=new TExtPolyline(1,0);
        (*Poly)[0].x=w>>1;
        (*Poly)[0].y=h>>1;
        TDrwParamRec3 *R=(TDrwParamRec3*)Rec;
        MRect.Top=0;
        MRect.Bottom=h;
        int dw=(R->Height*h/R->Width)>>1;
        MRect.Left=(w>>1)-dw;
        MRect.Right=(w>>1)+dw;
        }
      else
        {
        Poly=new TExtPolyline(2,1);
        Poly->Codes[0]=0;
        (*Poly)[0].x=0;
        (*Poly)[0].y=h>>1;
        (*Poly)[1].x=w;
        (*Poly)[1].y=h>>1;
        }
      FDrawMan->BaseScaleL=2000;
      FDrawMan->BaseScaleX=500;
      Cont->PrepareUpdating();
      if (Rec->ProcId==3)
          FDrawMan->CallDrawFunc(Cont,Poly,Rec,&MRect,2000,500,pkGorizontal,pdDirect,PixelsPerInch/2.54,true);
      else
        FDrawMan->CallDrawFunc(Cont,Poly,Rec,&MRect,1000,200,pkGorizontal,pdDirect,PixelsPerInch/2.54,true);
      delete Poly;
      Cont->FinishUpdating();
      Cont->DrawTo(VisList->Canvas,Rect.Left+24,Rect.Top+2);
      delete Cont;
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CopyDrwParam(TDrwClassesRec *NewRec)
{
if (NewRec)
    {
    TStringList *lst=new TStringList;
    NewRec->Dump(lst);
    CurrentDrw->LoadDump(lst);
    delete lst;
    UpDown1->Position=CurrentDrw->Priority;
    ShowPagesFlag(NewRec);
    ShowObject();
    }
}

void __fastcall TMainForm::CopyDrwParam(TObjMetaClass *Meta,TTextPropRec *Rec)
{
if (Meta)
        {
        int drwpar=0;
        int recid=0;
        if (Rec)
                recid=Rec->Id;
        drwpar=Dict->SelectDrwParam(Meta->Id,recid,PageIndex());
        if (drwpar>0)
                {
                TStringList *lst=new TStringList;
                Dict->DrwClasses->Items[drwpar]->Dump(lst);
                CurrentDrw->LoadDump(lst);
                delete lst;
                }
        else
                {
                CurrentDrw->SetDrwParam(0,0,0,0);
                CurrentDrw->SetClassId(Meta->Id,recid);
                }
        ShowPagesFlag(CurrentDrw);                
        UpDown1->Position=CurrentDrw->Priority;
        ShowObject();
        }
}

void __fastcall TMainForm::ShowObject(void)
{
Check1->Checked=CurrentDrw->DrwParamId[0]>0;
Check2->Checked=CurrentDrw->DrwParamId[1]>0;
Check3->Checked=CurrentDrw->DrwParamId[2]>0;
Check4->Checked=CurrentDrw->DrwParamId[3]>0;
if (CurrentDrw->ObjClassId>0)
    {
    TObjMetaClass *Rec=dynamic_cast<TObjMetaClass*>(Dict->ObjClasses->Items[CurrentDrw->ObjClassId]);
    if (Rec)
        {
        TRect R;
        R.Top=0;
        R.Left=0;
        R.Bottom=VisBox->Height-1;
        R.Right=VisBox->Width-1;
        TExtPolyline *p=Factory->GetDefaultMetric(Rec->ClassName,R);
        if (p)
          {      
          if (CurrentDrw->DrwParamId[0]>0)
            {
            TDrawContents *Cont=new TDrawBitmap();
            Cont->SetSize(R.Right,R.Bottom);
            Cont->SetParam(0,1,0,1);
            FDrawMan->BaseScaleL=2000;
            FDrawMan->BaseScaleX=500;
            Cont->PrepareUpdating();
            for (int i=0;i<MAXDRWPARAM;i++)
                if (CurrentDrw->DrwParamId[i]>0)
                {
                TRect MRect;
                TDrwParamRec *Drw=Dict->DrwParams->Items[CurrentDrw->DrwParamId[i]];
                TDrwParamRec3 *Drw3=dynamic_cast<TDrwParamRec3*>(Drw);
                if (Drw3)
                        {
                        int pw=(Drw3->Width*PixelsPerInch)/254;
                        int ph=(Drw3->Height*PixelsPerInch)/254;
                        MRect.Left=(*p)[0].x-(pw>>1);
                        MRect.Right=(*p)[0].x+(pw>>1);
                        MRect.Top=(*p)[0].y-(ph>>1);
                        MRect.Bottom=(*p)[0].y+(ph>>1);
                        FDrawMan->CallDrawFunc(Cont,p,Drw,&MRect,2000,500,pkGorizontal,pdDirect,PixelsPerInch/2.54,i==0);
                        }
                else
                    FDrawMan->CallDrawFunc(Cont,p,Drw,&MRect,1000,200,pkGorizontal,pdDirect,PixelsPerInch/2.54,i==0);
                }
            Cont->FinishUpdating();
            Cont->DrawTo(VisBox->Canvas,0,0);
            delete Cont;
            if (ShowGrid->Checked)
                {
                VisBox->Canvas->Pen->Mode=pmXor;
                VisBox->Canvas->Pen->Color=clWhite;
                VisBox->Canvas->Pen->Style=psDot;
                switch (p->Count)
                    {
                    case 1:{
                        VisBox->Canvas->MoveTo((*p)[0].x-10,(*p)[0].y);
                        VisBox->Canvas->LineTo((*p)[0].x+10,(*p)[0].y);
                        VisBox->Canvas->MoveTo((*p)[0].x,(*p)[0].y-10);
                        VisBox->Canvas->LineTo((*p)[0].x,(*p)[0].y+10);
                        } break;
                    case 2:{
                        VisBox->Canvas->MoveTo((*p)[0].x,(*p)[0].y);
                        VisBox->Canvas->LineTo((*p)[1].x,(*p)[1].y);
                        } break;
                    case 4:{
                        VisBox->Canvas->MoveTo((*p)[3].x,(*p)[3].y);
                        for (int i=0;i<4;i++)
                            VisBox->Canvas->LineTo((*p)[i].x,(*p)[i].y);
                        }
                    }
                VisBox->Canvas->Pen->Mode=pmCopy;
                }
             }   
          delete p;
          }
        }
    }
Button3->Enabled=CurrentDrw->DrwParamId[0]>0;
}

void __fastcall TMainForm::ShowProc(void)
{
int pos=0;
if (Radio1->Checked)
        pos=CurrentDrw->DrwParamId[0];
else if (Radio2->Checked)
        pos=CurrentDrw->DrwParamId[1];
else if (Radio3->Checked)
        pos=CurrentDrw->DrwParamId[2];
else if (Radio4->Checked)
        pos=CurrentDrw->DrwParamId[3];
if (pos<0)
        pos=0;
int index=-1;
for (int i=0;i<VisList->Items->Count;i++)
    {
    TDrwParamRec *Rec=(TDrwParamRec*)VisList->Items->Objects[i];
    if (Rec)
        if (Rec->Id==pos)
            {
            index=i;
            break;
            }
    }
VisList->ItemIndex=index;
}

void __fastcall TMainForm::VisPropListClick(TObject *Sender)
{
if ((VisPropList->ItemIndex>=0)&&(VisObjTree->Selected!=NULL))
        {
        TObjMetaClass *Meta=(TObjMetaClass*)VisObjTree->Selected->Data;
        TObject *Data=(TTextPropRec*)VisPropList->Items->Objects[VisPropList->ItemIndex];
        TTextPropRec *Rec=dynamic_cast<TTextPropRec*>(Data);
        if (Rec)   // Если есть отображаемая характеристика и ссылка на ее значение
            CopyDrwParam(Meta,Rec);
        else
            {
            TDrwClassesRec *Drw=dynamic_cast<TDrwClassesRec*>(Data);
            if (Drw)
                CopyDrwParam(Drw);
            else
                CurrentDrw->SetClassId(0,0);
            }
        }
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisBoxPaint(TObject *Sender)
{
ShowObject();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Radio1Click(TObject *Sender)
{
ShowProc();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisListDblClick(TObject *Sender)
{
if (VisList->ItemIndex>=0)
        {
        TDrwClassesRec *Drw=(TDrwClassesRec *)VisList->Items->Objects[VisList->ItemIndex];
        if (Drw)
            {
            int id=Drw->Id;
            if (Radio1->Checked)
                {
                CurrentDrw->SetDrwParam(0,id);
                Check1->Checked=true;
                }
            else if (Radio2->Checked)
                {
                CurrentDrw->SetDrwParam(1,id);
                Check2->Checked=true;
                }
            else if (Radio3->Checked)
                {
                CurrentDrw->SetDrwParam(2,id);
                Check3->Checked=true;
                }
            else if (Radio4->Checked)
                {
                CurrentDrw->SetDrwParam(3,id);
                Check4->Checked=true;
                }
            }
        VisBox->Invalidate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender)
{
Connection->Connected=true;
Dict=Manager->AddDictSource(0,Connection);
Shared=new TDBSharedObjSource(Connection);
ShowObjTree(ObjTree,Dict);
ShowObjTree(VisObjTree,Dict);
ShowPropList(Dict);
BuildPagesList(Dict);
ShowGdiList();
ShowVisList(NULL);
FDrawMan->Dict=Dict;
FDrawMan->Shared=Shared;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender)
{
SortByViewOrder();
if (Shared)
    {
    TDBSharedObjSource *dbs=dynamic_cast<TDBSharedObjSource*>(Shared);
    if (dbs)
        {
        dbs->Save();
        }
    else
        {
        Connection->Connected=true;
        if (Connection->Connected)
            {
            TDBSharedObjSource *dbs=new TDBSharedObjSource();
            dbs->Connection=Connection;
            dbs->CopyList(Shared);
            dbs->Save();
            delete dbs;
            }
        else
            ShowMessage("Соединение не установлено. Операция отменена");
        }
    }
if (Dict)
    {
    TDBDictSource *dbd=dynamic_cast<TDBDictSource*>(Dict);
    if (dbd)
        dbd->Save();
    else
        {
        Connection->Connected=true;
        if (Connection->Connected)
            {
            TDBDictSource *dbd=new TDBDictSource();
            dbd->Connection=Connection;
            dbd->CopyList(Dict);
            dbd->Save();
            delete dbd;
            }
        else
            ShowMessage("Соединение не установлено. Операция отменена");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::P4Click(TObject *Sender)
{
if (GDIPens->ItemIndex>=0)
    {
    void *Pen=Shared->GorzGDIObjects->Items[int(GDIPens->Items->Objects[GDIPens->ItemIndex])];
    if (Pen)
        {
        EXTLOGPEN ps;
        GetObject(Pen,sizeof(EXTLOGPEN),&ps);
        PenEdit->Color=ps.elpColor;
        PenEdit->Width=ps.elpWidth;
        PenEdit->Style=ps.elpPenStyle;
        if (PenEdit->ShowModal()==mrOk)
            {
            DeleteObject(Pen);
            LOGBRUSH lb;
            lb.lbStyle=BS_SOLID;
            lb.lbColor=PenEdit->Color;
            lb.lbHatch=0;
            Pen=ExtCreatePen(PS_GEOMETRIC|PenEdit->Style,PenEdit->Width,&lb,0,NULL);
            Shared->GorzGDIObjects->Items[int(GDIPens->Items->Objects[GDIPens->ItemIndex])]=Pen;
            GDIPens->Invalidate();
            VisList->Invalidate();
            VisBox->Invalidate();
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::P1Click(TObject *Sender)
{
if (PenEdit->ShowModal()==mrOk)
        {
        int n=Shared->GorzGDIObjects->FirstFree(1);
        if (n>=Shared->GorzGDIObjects->Count)
                {
                Shared->GorzGDIObjects->Count=n+1;
                Shared->VertGDIObjects->Count=n+1;
                }
        LOGBRUSH lb;
        lb.lbStyle=BS_SOLID;
        lb.lbColor=PenEdit->Color;
        lb.lbHatch=0;
        void *GPen=ExtCreatePen(PS_GEOMETRIC|PenEdit->Style,PenEdit->Width,&lb,0,NULL);
        void *VPen=ExtCreatePen(PS_GEOMETRIC|PenEdit->Style,PenEdit->Width,&lb,0,NULL);
        Shared->GorzGDIObjects->Items[n]=GPen;
        Shared->VertGDIObjects->Items[n]=VPen;
        GDIPens->Items->AddObject("",(TObject*)n);
        GDIPens->Invalidate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::P5Click(TObject *Sender)
{
if (GDIBrushs->ItemIndex>=0)
        {
        void *Bru=Shared->GorzGDIObjects->Items[int(GDIBrushs->Items->Objects[GDIBrushs->ItemIndex])];
        if (Bru)
                {
                LOGBRUSH ps;
                GetObject(Bru,sizeof(LOGBRUSH),&ps);
                BrushEdit->ColorDialog1->Color=TColor(ps.lbColor);
                if (ps.lbStyle==BS_HATCHED)
                        BrushEdit->ComboBox1->ItemIndex=ps.lbHatch+1;
                else
                        BrushEdit->ComboBox1->ItemIndex=0;
                if (BrushEdit->ShowModal())
                        {
                        DeleteObject(Bru);
                        if (BrushEdit->ComboBox1->ItemIndex)
                                Bru=CreateHatchBrush(BrushEdit->ComboBox1->ItemIndex-1,BrushEdit->ColorDialog1->Color);
                        else
                                Bru=CreateSolidBrush(BrushEdit->ColorDialog1->Color);
                        Shared->GorzGDIObjects->Items[int(GDIBrushs->Items->Objects[GDIBrushs->ItemIndex])]=Bru;
                        GDIBrushs->Invalidate();
                        VisList->Invalidate();
                        VisBox->Invalidate();
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::P2Click(TObject *Sender)
{
if (BrushEdit->ShowModal()==mrOk)
        {
        int n=Shared->GorzGDIObjects->FirstFree(1);
        if (n>=Shared->GorzGDIObjects->Count)
                {
                Shared->GorzGDIObjects->Count=n+1;
                Shared->VertGDIObjects->Count=n+1;
                }
        void *GBru,*VBru;
        if (BrushEdit->ComboBox1->ItemIndex)
                {
                GBru=CreateHatchBrush(BrushEdit->ComboBox1->ItemIndex-1,BrushEdit->ColorDialog1->Color);
                VBru=CreateHatchBrush(BrushEdit->ComboBox1->ItemIndex-1,BrushEdit->ColorDialog1->Color);
                }
        else
                {
                GBru=CreateSolidBrush(BrushEdit->ColorDialog1->Color);
                VBru=CreateSolidBrush(BrushEdit->ColorDialog1->Color);
                }
        Shared->GorzGDIObjects->Items[n]=GBru;
        Shared->VertGDIObjects->Items[n]=VBru;        
        GDIBrushs->Items->AddObject("",(TObject*)n);
        GDIBrushs->Invalidate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GDIPensDblClick(TObject *Sender)
{
if ((GDIPens->ItemIndex>=0)&&(VisList->ItemIndex>=0))
        {
        TDrwParamRec *Par=(TDrwParamRec*)VisList->Items->Objects[VisList->ItemIndex];
        if (Par)
            {
            int n=int(GDIPens->Items->Objects[GDIPens->ItemIndex]);
            if (n<0)
                Par->SetPenId(n+256);
            else
                Par->SetPenId(n);
            }
        VisList->Invalidate();
        VisBox->Invalidate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GDIBrushsDblClick(TObject *Sender)
{
if ((GDIBrushs->ItemIndex>=0)&&(VisList->ItemIndex>=0))
        {
        TDrwParamRec *Pr=(TDrwParamRec*)VisList->Items->Objects[VisList->ItemIndex];
        TDrwParamRecB *Par=dynamic_cast<TDrwParamRecB*>(Pr);
        if (Par)
            {
            int n=int(GDIBrushs->Items->Objects[GDIBrushs->ItemIndex]);
            if (n<0)
                Par->SetBrushId(n+256);
            else
                Par->SetBrushId(n);
            }
        VisList->Invalidate();
        VisBox->Invalidate();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisListClick(TObject *Sender)
{
if (VisList->ItemIndex>=0)
        {
        TDrwParamRec *Pr=(TDrwParamRec*)VisList->Items->Objects[VisList->ItemIndex];
        if (Pr)
                {
                __int32 penid=Pr->PenId;
                for (int i=0;i<GDIPens->Count;i++)
                        if (GDIPens->Items->Objects[i]==(TObject*)penid)
                                {
                                GDIPens->ItemIndex=i;
                                break;
                                }
                TDrwParamRecB *Par=dynamic_cast<TDrwParamRecB*>(Pr);
                if (Par)
                        {
                        __int32 brushid=Par->BrushId;
                        for (int i=0;i<GDIBrushs->Count;i++)
                                if (GDIBrushs->Items->Objects[i]==(TObject*)brushid)
                                        {
                                        GDIBrushs->ItemIndex=i;
                                        break;
                                        }
                        }
                }
        }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::P3Click(TObject *Sender)
{
if (ProcEdit->ShowModal()==mrOk)
        {
        ProcEdit->Id=Dict->DrwParams->FirstFree(1);
        TDrwParamRec *Pr=ProcEdit->GetParams();
        VisList->Items->AddObject("",(TObject*)Pr);
        if (Dict->DrwParams->Count<=Pr->Id)
                Dict->DrwParams->Count=Pr->Id+1;
        Dict->DrwParams->Items[Pr->Id]=Pr;
        VisList->Invalidate();
        VisBox->Invalidate();
        }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::P6Click(TObject *Sender)
{
if (VisList->ItemIndex>=0)
        {
        TDrwParamRec *Pr=(TDrwParamRec*)VisList->Items->Objects[VisList->ItemIndex];
        ProcEdit->SetParams(Pr);
        if (ProcEdit->ShowModal()==mrOk)
                {
                TDrwParamRec *NewPr=ProcEdit->GetParams();
                VisList->Items->Objects[VisList->ItemIndex]=(TObject*)NewPr;
                Dict->DrwParams->Items[Pr->Id]=NewPr;
                VisList->Invalidate();
                VisBox->Invalidate();
                delete Pr;                
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Check1Click(TObject *Sender)
{
if (Check1->Checked)
        Radio1->Checked=true;
else
        CurrentDrw->SetDrwParam(0,0);
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Check2Click(TObject *Sender)
{
if (Check2->Checked)
        Radio2->Checked=true;
else
        CurrentDrw->SetDrwParam(1,0);
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Check3Click(TObject *Sender)
{
if (Check3->Checked)
        Radio3->Checked=true;
else
        CurrentDrw->SetDrwParam(2,0);
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Check4Click(TObject *Sender)
{
if (Check4->Checked)
        Radio4->Checked=true;
else
        CurrentDrw->SetDrwParam(3,0);
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button3Click(TObject *Sender)
{
if ((VisPropList->ItemIndex>=0)&&(VisObjTree->Selected!=NULL))
        {
        TObjMetaClass *Meta=(TObjMetaClass*)VisObjTree->Selected->Data;
        TObject *Data=VisPropList->Items->Objects[VisPropList->ItemIndex];
        TTextPropRec *Rec=dynamic_cast<TTextPropRec*>(Data);
        TDrwClassesRec *Drw=dynamic_cast<TDrwClassesRec*>(Data);
        if (Meta)
            {
            if (Drw)  // Выбрана строка с условием
                {
                Drw->SetDrwParam(CurrentDrw->DrwParamId[0],CurrentDrw->DrwParamId[1],CurrentDrw->DrwParamId[2],CurrentDrw->DrwParamId[3]);
                Drw->SetPriority(CurrentDrw->Priority);
                Drw->SetPagesSet(PageFlags());
                }
            else
                {
                int recid=0;
                if (Rec)
                        recid=Rec->Id;
                int drwpar=Dict->SelectDrwParam(Meta->Id,recid,PageIndex());
                bool needadd=true;
                if (drwpar>0)
                    {
                    TDrwClassesRec * Drw=Dict->DrwClasses->Items[drwpar];
                    if (Drw)
                        if ((Drw->PropValueId==recid)||(recid==0))
                            {
                            Drw->SetDrwParam(CurrentDrw->DrwParamId[0],CurrentDrw->DrwParamId[1],CurrentDrw->DrwParamId[2],CurrentDrw->DrwParamId[3]);
                            Drw->SetPriority(CurrentDrw->Priority);
                            Drw->SetPagesSet(PageFlags());
                            Drw->Condition="";
                            needadd=false;
                            }
                    }
                if (needadd)        // Надо добавить параметры
                    {
                    int id=Dict->DrwClasses->FirstFree(1);
                    TDrwClassesRec *NewRec=new TDrwClassesRec(id,Meta->Id,recid,CurrentDrw);
                    NewRec->SetPagesSet(PageFlags());
                    if (Dict->DrwClasses->Count<=id)
                        Dict->DrwClasses->Count=id+1;
                    Dict->DrwClasses->Items[id]=NewRec;
                    }
                }
            }
        }
VisBox->Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button4Click(TObject *Sender)
{
if (ObjTree->Selected!=NULL)
        {
        TObjMetaClass *r=(TObjMetaClass*)ObjTree->Selected->Data;
        if (r)
            SqlEditFrm->Execute(r);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit1Change(TObject *Sender)
{
try
    {
    CurrentDrw->SetPriority(Edit1->Text.ToInt());
    }
catch (...)
    {}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
delete CurrentDrw;
TIniFile *ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
ini->WriteString("Connection","String",Connection->ConnectionString);
delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ObjTreeChange(TObject *Sender, TTreeNode *Node)
{
if (ObjTree->Selected!=NULL)
    {
    TObjMetaClass *r=(TObjMetaClass*)(ObjTree->Selected->Data);
    if (r)
        {
        ObjName->Text=r->OneTitle;
        MainTable->Text=r->TableName;
        ObjFlags->Text=String(r->Flags);
        ClassList->ItemIndex=GetClassNameIndex(r->ClassName);
        CharList->Items->BeginUpdate();
        MainChar->Items->BeginUpdate();
        CharList->Items->Clear();
        MainChar->Items->Clear();
        MainChar->Items->Add("");
        for (int i=0;i<r->PropCount;i++)
            {
            TPropClassesRec *rec=Dict->PropClasses->Items[r->PropIds[i]];
            if (rec)
                {
                CharList->Items->AddObject(rec->PropName,(TObject*)rec);
                CharList->Checked[CharList->Items->Count-1]=r->PropFlags[i]&PR_READONLY;
                MainChar->Items->AddObject(rec->PropName,(TObject*)rec);
                if (rec->Id==r->MainPropId)
                    MainChar->ItemIndex=MainChar->Items->Count-1;
                }
            }
            CharList->Items->EndUpdate();
            MainChar->Items->EndUpdate();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisObjTreeChange(TObject *Sender,
      TTreeNode *Node)
{
if (VisObjTree->Selected!=NULL)
    {
    VisPropList->Items->Clear();
    TObjMetaClass *Rec=(TObjMetaClass*)VisObjTree->Selected->Data;
    if (Rec)
        {
        if (Rec->MainPropId>0)
            Dict->TextPropByClasses(VisPropList->Items,Rec->MainPropId);
        int DrwNum=Dict->SelectDrwParam(Rec->Id,0,PageIndex());
        if (DrwNum)
            VisPropList->Items->AddObject("По умолчанию",Dict->DrwClasses->Items[DrwNum]);
        else
            VisPropList->Items->Add("По умолчанию");
        for (int i=0;i<Dict->DrwClasses->Count;i++)
            {
            TDrwClassesRec *Drw=Dict->DrwClasses->Items[i];
            if (Drw)
                {
                if (Drw->ObjClassId==Rec->Id)
                    if (Drw->Condition!="")
                    VisPropList->Items->AddObject(Drw->Condition,Drw);
                }
            }
        }
    ShowVisList(Rec);
    VisPropList->ItemIndex=0;
    VisPropListClick(NULL);
    }
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VisBoxDblClick(TObject *Sender)
{
ShowProc();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N7Click(TObject *Sender)
{
int n=Dict->DrwParams->Count;
bool *used=new bool[n];
for (int i=0;i<n;i++)
    used[i]=false;
int m=Dict->DrwClasses->Count;
for (int i=0;i<m;i++)
    {
    TDrwClassesRec *Rec=Dict->DrwClasses->Items[i];
    if (Rec)
        for (int j=0;j<MAXDRWPARAM;j++)
            used[Rec->DrwParamId[j]]=true;
    }
for (int i=1;i<n;i++)
    if (!used[i])
        {
        TDrwParamRec *DrwPar=Dict->DrwParams->Items[i];
        if (DrwPar)
            {
            delete DrwPar;
            Dict->DrwParams->Items[i]=NULL;
            }
        }
delete[] used;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ShowGridClick(TObject *Sender)
{
VisBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ValListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
MovedTextIndex=ValList->ItemAtPos(Point(X,Y),true);    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ValListMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
int newindex=ValList->ItemAtPos(Point(X,Y),true);
MoveStringList(ValList->Items,newindex,MovedTextIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ValListMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
MovedTextIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N8Click(TObject *Sender)
{
if (VisObjTree->Selected!=NULL)
    {
    TObjMetaClass *Meta=(TObjMetaClass*)VisObjTree->Selected->Data;
    if (Meta)
        {
        VisCondEdit->SetObjClass(Meta,Dict);
        if (VisCondEdit->ShowModal()==mrOk)
            {
            int id=Dict->DrwClasses->FirstFree(1);
            TDrwClassesRec *NewRec=new TDrwClassesRec(id,Meta->Id,0,CurrentDrw);
            NewRec->Condition=VisCondEdit->Condition;
            if (Dict->DrwClasses->Count<=id)
                Dict->DrwClasses->Count=id+1;
            Dict->DrwClasses->Items[id]=NewRec;
            VisPropList->Items->AddObject(VisCondEdit->Condition,NewRec);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N9Click(TObject *Sender)
{
if (VisObjTree->Selected!=NULL)
    {
    TObjMetaClass *Meta=(TObjMetaClass*)VisObjTree->Selected->Data;
    if (Meta)
        {
        if (VisPropList->ItemIndex>=0)
            {
            TObject *Data=VisPropList->Items->Objects[VisPropList->ItemIndex];
            TDrwClassesRec *Drw=dynamic_cast<TDrwClassesRec*>(Data);
            if (Drw)
                {
                VisCondEdit->SetObjClass(Meta,Dict);
                VisCondEdit->Condition=Drw->Condition;
                if (VisCondEdit->ShowModal()==mrOk)
                    {
                    VisPropList->Items->Strings[VisPropList->ItemIndex]=VisCondEdit->Condition;
                    Drw->Condition=VisCondEdit->Condition;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

