//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PolyForm.h"
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPolyFrm *PolyFrm;
//---------------------------------------------------------------------------
__fastcall TPolyFrm::TPolyFrm(TComponent* Owner)
    : TForm(Owner)
{
   ParamCode=0;
   FPatterns=new TStringList;
   LoadPatterns();
   BuildMenu();
}
//---------------------------------------------------------------------------
__fastcall TPolyFrm::~TPolyFrm(void)
{
   for (int i=0;i<FPatterns->Count;i++)
      delete (TPolyline*)FPatterns->Objects[i];
   delete FPatterns;
}
//---------------------------------------------------------------------------

bool __fastcall nextint(char *&s,__int32 &res) {
   res=0;
   int sign=1;
   while ((*s<'0' || *s>'9') && *s && *s!='-')
      s++;
   if (*s) {
      for (;*s>='0' && *s<='9' || *s=='-';s++)
         if (*s=='-')
            sign*=-1;
         else
            res=res*10+*s-'0';
      res*=sign;
      return true;
      }
   return false;
}

void __fastcall TPolyFrm::LoadPatterns(void) {
   String FName=ExtractFilePath(Application->ExeName)+"\polypat.ini";
   TIniFile *ini=new TIniFile(FName);
   int count=ini->ReadInteger("Lines","Count",0);
   for (int i=0;i<count;i++) {
      String sname="Line"+IntToStr(i);
      String caption=ini->ReadString(sname,"Caption","empty");
      String code=ini->ReadString(sname,"Code","");
      String lpar=ini->ReadString(sname,"LeepPar","");
      String bpar1=ini->ReadString(sname,"Base1Par","");
      String bpar2=ini->ReadString(sname,"Base2Par","");
      int size=ini->ReadInteger(sname,"Size",0);
      if (size) {
         char *pcod=code.c_str();
         char *plpar=lpar.c_str();
         char *pbpar1=bpar1.c_str();
         char *pbpar2=bpar2.c_str();
         __int32 c,l,p1,p2,i=0;
         TPolyline *poly=new TPolyline(size);
         while (nextint(pcod,c) && nextint(plpar,l) && nextint(pbpar1,p1) && nextint(pbpar2,p2) && i<size) {
            poly->Points[i].Code=c;
            poly->Points[i].LeepPar=l;
            poly->Points[i].BasePar1=p1;
            poly->Points[i].BasePar2=p2;
            i++;
         }
         FPatterns->AddObject(caption,(TObject*)poly);
         }
   }
}
//---------------------------------------------------------------------------
void __fastcall TPolyFrm::SavePatterns(void) {
   String FName=ExtractFilePath(Application->ExeName)+"\polypat.ini";
   TIniFile *ini=new TIniFile(FName);
   ini->WriteInteger("Lines","Count",FPatterns->Count);
   for (int i=0;i<FPatterns->Count;i++) {
      TPolyline *poly=(TPolyline*)FPatterns->Objects[i];
      if (poly && poly->Count) {
         String sname="Line"+IntToStr(i);
         ini->WriteString(sname,"Caption",FPatterns->Strings[i]);
         ini->WriteInteger(sname,"Size",poly->Count);
         String code,lpar,bpar1,bpar2;
         code=IntToStr(poly->Points[0].Code());
         lpar=IntToStr(poly->Points[0].LeepPar);
         bpar1=IntToStr(poly->Points[0].BasePar1);
         bpar2=IntToStr(poly->Points[0].BasePar2);
         for (int j=1;j<poly->Count;j++) {
            code+=","+IntToStr(poly->Points[j].Code());
            lpar+=","+IntToStr(poly->Points[j].LeepPar);
            bpar1+=","+IntToStr(poly->Points[j].BasePar1);
            bpar2+=","+IntToStr(poly->Points[j].BasePar2);
         }
         ini->WriteString(sname,"Code",code);
         ini->WriteString(sname,"LeepPar",lpar);
         ini->WriteString(sname,"Base1Par",bpar1);
         ini->WriteString(sname,"Base2Par",bpar2);
      }
   }
   ini->UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TPolyFrm::BuildMenu(void) {
while (PatMenu->Items->Count>1)
   delete PatMenu->Items->Items[1];
for (int i=0;i<FPatterns->Count;i++) {
   TMenuItem* it=new TMenuItem(PatMenu);
   it->Tag=i;
   it->Caption=FPatterns->Strings[i];
   it->OnClick=CopyPointFromPattern;
   PatMenu->Items->Add(it);
   }
}


void __fastcall TPolyFrm::CopyPointFromPattern(TObject *Sender) {
   TMenuItem *it=dynamic_cast<TMenuItem*>(Sender);
   if (it && FPoly) {
      TPolyline *p=(TPolyline*)FPatterns->Objects[it->Tag];
      FPoly->CopyPoints(p);
      FRefRoad->CalcPointsPos(FPoly,FRefObj);
      BuildList();
      SetActivePoint(-1,true);
      FVector=FRefForm->BuildPoly(true);
      FRefForm->PBox->Invalidate();
   }
}


//---------------------------------------------------------------------------
void __fastcall TPolyFrm::ShowForm(TRoadFrm *frm,TRoad *road,TPolyline *poly,TExtPolyline *vec,TRoadObject *obj)
{
FRefForm=frm;
FRefRoad=road;
FRefObj=obj;
FPoly=poly;
FVector=vec;
BuildList();
Show();
}

String __fastcall TPolyFrm::GetPointInfo(int Num)
{
String Res=String(Num)+":";
TPointCode Code=(*FPoly)[Num].Code;
switch (Code.Connection())
    {
    case 0: Res+="Прямая ";break;
    case 1: Res+="Дуга   ";break;
    case 2: Res+="Безье  ";break;
    }
return Res;
}

void __fastcall TPolyFrm::BuildList(void)
{
PolyList->Items->BeginUpdate();
PolyList->Items->Clear();
if (FPoly)
    {
    int n=FPoly->Count;
    for (int i=0;i<n;i++)
        PolyList->Items->Add(GetPointInfo(i));
    for (int i=0;i<n;i++)
        PolyList->Checked[i]=(*FPoly)[i].Code.Visible();
    }
PolyList->Items->EndUpdate();
PolyList->MultiSelect=true;
GroupBox2->Visible=false;
}

void __fastcall TPolyFrm::BuildProp(int Num)
{
TRoadPoint P=(*FPoly)[Num];
Visible->Checked=P.Code.Visible();
Connection->ItemIndex=P.Code.Connection();
Leep->ItemIndex=P.Code.Leep();
LeepPar->Text=P.LeepPar;
LBase->ItemIndex=P.Code.LBase();
XBase->ItemIndex=P.Code.XBase();
Polar->ItemIndex=P.Code.Polar();
BasePar1->Text=P.BasePar1;
BasePar2->Text=P.BasePar2;
BaseFixed1->Checked=P.Code.BaseFixed1();
BaseFixed2->Checked=P.Code.BaseFixed2();
}

void __fastcall TPolyFrm::UpdatePoly(TExtPolyline *vec)
{
FVector=vec;
BuildList();
}

void __fastcall TPolyFrm::UpdatePoint(int Num)
{
if (Num==PolyList->ItemIndex)
    BuildProp(Num);
String S=GetPointInfo(Num);
if (S!=PolyList->Items->Strings[Num])
    PolyList->Items->Strings[Num]=S;
}

void __fastcall TPolyFrm::SetActivePoint(int n,bool exclusive)
{
if (exclusive)
    PolyList->ClearSelection();
if (n>=0)
    {
    BuildProp(n);
    PolyList->ItemIndex=n;
    PolyList->Selected[n]=true;
    }
GroupBox2->Visible=n>=0;
}

TPointCode __fastcall TPolyFrm::GetCode(void)
{
TPointCode Code;
Code.Set(Visible->Checked,Connection->ItemIndex,Leep->ItemIndex);
Code.SetBase(LBase->ItemIndex,XBase->ItemIndex,Polar->ItemIndex,BaseFixed1->Checked,BaseFixed2->Checked);
return Code;
}

void __fastcall TPolyFrm::CopySelectedPoints(void)
{
int n=0;
for (int i=0;i<FPoly->Count;i++)
    if (PolyList->Selected[i])
        n++;
FBuffer->Count=n;
n=0;
for (int i=0;i<FPoly->Count;i++)
    if (PolyList->Selected[i])
        FBuffer->Points[n++]=FPoly->Points[i];
}
void __fastcall TPolyFrm::RemoveSelectedPoints(void)
{
int n=0;
for (int i=0;i<FPoly->Count;i++)
    if (PolyList->Selected[i])
        n++;
    else
        FPoly->Points[i-n]=FPoly->Points[i];
FPoly->Count=FPoly->Count-n;
PolyList->DeleteSelected();
}
void __fastcall TPolyFrm::CutSelectedPoints(void)
{
CopySelectedPoints();
RemoveSelectedPoints();
}
void __fastcall TPolyFrm::SelectAllPoints(void)
{
PolyList->SelectAll();
}

void __fastcall TPolyFrm::RefreshSelection(void)
{
for (int i=0;i<PolyList->Items->Count;i++)
    if (PolyList->Selected[i])
        FVector->Flags[i]|=1;
    else
        FVector->Flags[i]&=0xFFFFFFFE;
}

void __fastcall TPolyFrm::SelectPoint(int n)
{
if ((n>=0)&&(n<PolyList->Items->Count))
    PolyList->Selected[n]=true;
}

void __fastcall TPolyFrm::PastePoints(void)
{
int n=FPoly->Count;
int m=FBuffer->Count;
int p=PolyList->ItemIndex;
if (p<0)
    p=0;
FPoly->Count=n+m;
for (int i=n-1;i>=p;i--)
    FPoly->Points[i+m]=FPoly->Points[i];
for (int i=0;i<m;i++)
    FPoly->Points[i+p]=FBuffer->Points[i];
}
void __fastcall TPolyFrm::AddPoints(void)
{
int n=FPoly->Count;
FPoly->Count=FPoly->Count+FBuffer->Count;
for (int i=0;i<FBuffer->Count;i++)
    FPoly->Points[i+n]=FBuffer->Points[i];
}

void __fastcall TPolyFrm::ReplaceSelectedToWidePart(void)
{
int firstsel=-1;
bool *NewPt=new bool [FPoly->Count];
int n=0;// Номер точки для записи
for (int i=0;i<FPoly->Count;i++)
    {
    int endsel=-1;
    if (PolyList->Selected[i])
        {
        if (firstsel==-1)
            firstsel=i;
        if (i==FPoly->Count-1)
            endsel=i;
        }
    else if (firstsel!=-1)
        endsel=i-1;
    if (endsel!=-1)
        {
        if (endsel>firstsel) // если выбрано несколько точек
            {
            double S1=0,S2=0,S3=0;
            double L1=0,L2=0,L3=0;
            double X2=0,X3=0;
            if (firstsel>0)
                {
                X2=FPoly->Points[firstsel-1].X;
                L2=fabs(FPoly->Points[firstsel].L-FPoly->Points[firstsel-1].L);
                S2=(FPoly->Points[firstsel].X+X2)*L2/2;
                }
            if (endsel<FPoly->Count-1)
                {
                X3=FPoly->Points[endsel+1].X;
                L3=fabs(FPoly->Points[endsel+1].L-FPoly->Points[endsel].L);
                S3=(FPoly->Points[endsel].X+X3)*L3/2;
                }
            for (int j=firstsel;j<endsel;j++)
                S1+=(FPoly->Points[j+1].X+FPoly->Points[j].X)*fabs(FPoly->Points[j+1].L-FPoly->Points[j].L)/2;
            L1=fabs(FPoly->Points[endsel].L-FPoly->Points[firstsel].L);
            // До соединения площадь равна S1+S2+S3.
            // После соединения площадь равна H*L1+(X2+H)*L2/2 + (X3+H)*L3/2
            // Отсюда H=(S1+S2+S3-X2*L2/2-X3*L3/2)/(L1+L2/2+L3/2)
            double H=(S1+S2+S3-X2*L2/2-X3*L3/2)/(L1+L2/2+L3/2);
            FPoly->Points[n]=FPoly->Points[firstsel];
            FPoly->Points[n].X=H;
            NewPt[n]=true;
            n++;
            FPoly->Points[n]=FPoly->Points[endsel];
            FPoly->Points[n].X=H;
            NewPt[n]=true;
            n++;
            }
        else  // Если выбрана одна точка
            {
            FPoly->Points[n]=FPoly->Points[firstsel];
            NewPt[n]=false;
            n++;
            }
        firstsel=-1;
        }
// Запись точек                   // Если точка не выбрана то ее надо записать
    if (!PolyList->Selected[i])
        {
        FPoly->Points[n]=FPoly->Points[i];
        NewPt[n]=false;
        n++;
        }
    }
FPoly->Count=n;
// Пересчитываем параметры для измененных точек
for (int i=0;i<n;i++)
    if (NewPt[i])
        FRefForm->SetPoint(FPoly->Points[i],i);
delete[] NewPt;
}

void __fastcall TPolyFrm::PolyListClick(TObject *Sender)
{
int n=PolyList->ItemIndex;
if (n>=0)
    {
    TRoadPoint P=(*FPoly)[n];
    if (P.Code.Visible()!=PolyList->Checked[n])
        {
        P.Code.SetVisible(PolyList->Checked[n]);
        FRefForm->SetPoint(P,n);
        }
    BuildProp(n);
    RefreshSelection();
    if (FRefForm->ActivePoint!=n)
        {
        FRefForm->ActivePoint=n;
        FRefForm->PBox->Invalidate();
        }
    }
GroupBox2->Visible=PolyList->ItemIndex>=0;
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::Button1Click(TObject *Sender)
{
int n=PolyList->ItemIndex;
if (n>=0)
    {
    TRoadPoint P=(*FPoly)[n];
    P.Code=GetCode();
    P.LeepPar=LeepPar->Text.ToInt();
    FRefForm->SetPoint(P,n);
    PolyList->Items->Strings[n]=GetPointInfo(n);
    PolyList->Checked[n]=P.Code.Visible();
    BuildProp(n);
    FRefForm->PBox->Invalidate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::Button2Click(TObject *Sender)
{
int n=PolyList->ItemIndex;
if (n>=0)
    {
    TRoadPoint P=(*FPoly)[n];
    P.Code=GetCode();
    P.LeepPar=LeepPar->Text.ToInt();
    P.BasePar1=BasePar1->Text.ToInt();
    P.BasePar2=BasePar2->Text.ToInt();
     (*FPoly)[n]=P;
    FRefRoad->CalcPointPos(FPoly,n,FRefObj);
    FRefForm->SetPoint((*FPoly)[n],n);
    PolyList->Items->Strings[n]=GetPointInfo(n);
    PolyList->Checked[n]=P.Code.Visible();
    BuildProp(n);
    FRefForm->PBox->Invalidate();
    }
}
//---------------------------------------------------------------------------



void __fastcall TPolyFrm::FormCreate(TObject *Sender)
{
FBuffer=new TPolyline;
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::FormDestroy(TObject *Sender)
{
delete FBuffer;    
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::btnSelectAllClick(TObject *Sender)
{
SelectAllPoints();
RefreshSelection();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::btnEraseClick(TObject *Sender)
{
RemoveSelectedPoints();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
}
//---------------------------------------------------------------------------




void __fastcall TPolyFrm::btnAddClick(TObject *Sender)
{
AddPoints();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
BuildList();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::btnPasteClick(TObject *Sender)
{
PastePoints();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
BuildList();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::btnCopyClick(TObject *Sender)
{
CopySelectedPoints();
}
//---------------------------------------------------------------------------


void __fastcall TPolyFrm::btnCutClick(TObject *Sender)
{
CutSelectedPoints();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::SpeedButton1Click(TObject *Sender)
{
ReplaceSelectedToWidePart();
BuildList();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::SpeedButton2Click(TObject *Sender)
{
FPoly->ChangeOrientation();
FVector=FRefForm->BuildPoly(true);
FRefForm->PBox->Invalidate();
BuildList();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
if (FRefForm)
    {
    FRefForm->StopEditPoly();
    FRefForm->PBox->Invalidate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::btnSaveParClick(TObject *Sender)
{
   ParamCode=GetCode();
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::SpeedButton3Click(TObject *Sender)
{
POINT p;
GetCursorPos(&p);
PatMenu->Popup(p.x,p.y);
}
//---------------------------------------------------------------------------

void __fastcall TPolyFrm::N1Click(TObject *Sender)
{
if (FPoly && FPoly->Count) {
   TPolyline *p=new TPolyline();
   p->CopyPoints(FPoly);
   FPatterns->AddObject("Polyline"+IntToStr(FPatterns->Count+1),(TObject*)p);
   SavePatterns();
   BuildMenu();
   }
}
//---------------------------------------------------------------------------

