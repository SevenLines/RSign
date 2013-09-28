//---------------------------------------------------------------------------
#pragma hdrstop

#include "VPattern.h"
#include <fstream.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TPatFigure::ReadInfo(TStringList* lst)
{
try {FSection=lst->Values["Section"].ToInt();} catch(...){FSection=0;}
}


void __fastcall TPatFigure::WriteInfo(TStringList* lst)
{
lst->Add("Section="+String(FSection));
}


void __fastcall TPatPageSize::ReadInfo(TStringList *lst)
{
TPatFigure::ReadInfo(lst);
try {FWidth=lst->Values["Width"].ToInt();} catch(...){FWidth=297;}
try {FHeight=lst->Values["Height"].ToInt();} catch(...){FHeight=210;}
try {FLeftOfs=lst->Values["LeftOfs"].ToInt();} catch(...){FLeftOfs=0;}
try {FRightOfs=lst->Values["RightOfs"].ToInt();} catch(...){FRightOfs=0;}
try {FTopOfs=lst->Values["TopOfs"].ToInt();} catch(...){FTopOfs=0;}
try {FBottomOfs=lst->Values["BottomOfs"].ToInt();} catch(...){FBottomOfs=0;}
}

void __fastcall TPatPageSize::Write(TStringList *lst)
{
lst->Add("Figure=PageSize");
WriteInfo(lst);
}

void __fastcall TPatPageSize::WriteInfo(TStringList *lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("Width="+String(FWidth));
lst->Add("Height="+String(FHeight));
lst->Add("LeftOfs="+String(FLeftOfs));
lst->Add("RightOfs="+String(FRightOfs));
lst->Add("TopOfs="+String(FTopOfs));
lst->Add("BottomOfs="+String(FBottomOfs));
}

void __fastcall TPatPlanesCenter::ReadInfo(TStringList *lst)
{
TPatFigure::ReadInfo(lst);
try {FX=lst->Values["X"].ToInt();} catch(...) {FX=0;}
try {FY=lst->Values["Y"].ToInt();} catch(...) {FY=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch(...){FWidth=2500;}
try {FHeight=lst->Values["Height"].ToInt();} catch(...){FHeight=1500;}
}
void __fastcall TPatPlanesCenter::WriteInfo(TStringList *lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("X="+String(FX));
lst->Add("Y="+String(FY));
lst->Add("Width="+String(FWidth));
lst->Add("Height="+String(FHeight));
}
void __fastcall TPatPlanesCenter::FillRect(TRect &r)
{
r.Top=FY-(FHeight>>1);
r.Bottom=FY+(FHeight>>1);
r.Left=FX-(FWidth>>1);
r.Right=FX+(FWidth>>1);
}

void __fastcall TPatPlanCenter::Write(TStringList *lst)
{
lst->Add("Figure=PlanCenter");
WriteInfo(lst);
}

void __fastcall TPatCurvePlanCenter::Write(TStringList *lst)
{
lst->Add("Figure=CurvePlanCenter");
WriteInfo(lst);
}

void __fastcall TPatProfilCenter::Write(TStringList *lst)
{
lst->Add("Figure=ProfilCenter");
WriteInfo(lst);
}


void __fastcall TPatLabel::MakeReplace(char *Str,char *Res)
{
if (!FRepList)
    {
    strcpy(Res,Str);
    return;
    }
char *Pres=Res;
char Name[32];
char *pname=Name;
char IntVal[32];
char *pintval=IntVal;

char *Pstr=Str;
int status=0;
while (*Pstr)
    {
    if (*Pstr=='$')
        {
        if (status)
            {
            *pname=0;
            String RVal;
            if ((status==2)&&(pintval!=IntVal))
                {
                *pintval=0;
                RVal=String(RepList->Values[Name].ToInt()+String(IntVal).ToInt());
                pintval=IntVal;
                }
            else
                RVal=RepList->Values[Name];
            if (RVal!="")
                {
                strcpy(Pres,RVal.c_str());
                Pres+=RVal.Length();
                }
            pname=Name;
            status=0;
            }
        else
            status=1;
        }
    else if ((*Pstr=='+')&&(status==1))
        {
        status++;
        }
    else if (status==0)
        *(Pres++)=*Pstr;
    else if (status==1)
        *(pname++)=*Pstr;
    else
        *(pintval++)=*Pstr;
    Pstr++;
    }
*Pres=0;
}

void __fastcall TPatLabel::ReadInfo(TStringList* lst)
{
TPatFigure::ReadInfo(lst);
try {FColor=lst->Values["Color"].ToInt();} catch(...) {FColor=0;}
try {FSize=lst->Values["Size"].ToInt();} catch(...) {FSize=12;}
try {FBold=lst->Values["Bold"].ToInt();} catch(...) {FBold=0;}
try {FItalic=lst->Values["Italic"].ToInt();} catch(...) {FItalic=0;}
try {FUnderline=lst->Values["Underline"].ToInt();} catch(...) {FUnderline=0;}
try {FFormat=lst->Values["Format"].ToInt();} catch (...) {FFormat=0;}
try {FName=lst->Values["FontName"];} catch(...) {FName="Arial";}
try {FText=lst->Values["Text"];} catch(...) {FText="Введи текст";}
try {FCaption=lst->Values["Caption"];} catch(...) {FCaption="Неизвестный заголовок";}
}

void __fastcall TPatLabel::WriteInfo(TStringList* lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("Color="+String(FColor));
lst->Add("Size="+String(FSize));
lst->Add("Bold="+String((int)FBold));
lst->Add("Italic="+String((int)FItalic));
lst->Add("Underline="+String((int)FUnderline));
lst->Add("Format="+String(FFormat));
lst->Add("FontName="+FName);
lst->Add("Text="+FText);
lst->Add("Caption="+FCaption);
}

void* __fastcall TPatLabel::CreateFont(double K)
{
LOGFONT fn;
GetObject(GetStockObject(SYSTEM_FONT),sizeof(LOGFONT),&fn);
fn.lfWidth=0;
fn.lfItalic=FItalic;
fn.lfUnderline=FUnderline;
fn.lfWeight=FW_NORMAL+FBold*(FW_BOLD-FW_NORMAL);
fn.lfHeight=(double)FSize*K;
fn.lfEscapement=FAngle;
strcpy(fn.lfFaceName,FName.c_str());
return CreateFontIndirect(&fn);
}

void __fastcall TPatLabel::SetParam(TFont* fnt)
{
LOGFONT fn;
GetObject(fnt->Handle,sizeof(LOGFONT),&fn);
FItalic=fn.lfItalic;
FUnderline=fn.lfUnderline;
FBold=fn.lfWeight>=FW_BOLD;
FName=fn.lfFaceName;
FSize=-fn.lfHeight;
}

TFont* __fastcall TPatLabel::GetFont(void)
{
TFont *fnt=new TFont;
fnt->Handle=CreateFont(-1);
return fnt;
}


void __fastcall TPatLabelRect::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
char OutText[1024];
HDC dc=Cont->DC;
RECT R;
R.left=FP1.x*K+cx;
R.top=FP1.y*K+cy;
R.right=FP2.x*K+cx;
R.bottom=FP2.y*K+cy;
// FSize/72 -- размер в дюймах. FSize/72*254 -- размер в 0.1 мм.
SelectObject(dc,CreateFont(K*254/72));
int oldcolor=SetTextColor(dc,FColor);
MakeReplace(FText.c_str(),OutText);
DrawText(dc,OutText,strlen(OutText),&R,FFormat);
SetTextColor(dc,oldcolor);
DeleteObject(SelectObject(dc,GetStockObject(SYSTEM_FONT)));
}

void __fastcall TPatLabelRect::ReadInfo(TStringList *lst)
{
TPatLabel::ReadInfo(lst);
FAngle=0;
try {FP1.x=lst->Values["X1"].ToInt();} catch(...) {FP1.x=0;}
try {FP1.y=lst->Values["Y1"].ToInt();} catch(...) {FP1.y=0;}
try {FP2.x=lst->Values["X2"].ToInt();} catch(...) {FP2.x=0;}
try {FP2.y=lst->Values["Y2"].ToInt();} catch(...) {FP2.y=0;}
}

void __fastcall TPatLabelRect::Write(TStringList *lst)
{
lst->Add("Figure=LabelRect");
WriteInfo(lst);
}

void __fastcall TPatLabelRect::WriteInfo(TStringList *lst)
{
TPatLabel::WriteInfo(lst);
lst->Add("X1="+String(FP1.x));
lst->Add("Y1="+String(FP1.y));
lst->Add("X2="+String(FP2.x));
lst->Add("Y2="+String(FP2.y));
}

void __fastcall TPatLabelAngle::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
HDC dc=Cont->DC;
char OutText[1024];
SelectObject(dc,CreateFont(K*254/72));
int x=FP.x*K;
int y=FP.y*K;
int oldcolor=SetTextColor(dc,FColor);
int oldalign=SetTextAlign(dc,FFormat);
MakeReplace(FText.c_str(),OutText);
TextOut(dc,x,y,OutText,strlen(OutText));
SetTextColor(dc,oldcolor);
SetTextAlign(dc,oldalign);
DeleteObject(SelectObject(dc,GetStockObject(SYSTEM_FONT)));
}

void __fastcall TPatLabelAngle::Write(TStringList* lst)
{
lst->Add("Figure=LabelAngle");
WriteInfo(lst);
}

void __fastcall TPatLabelAngle::WriteInfo(TStringList* lst)
{
TPatLabel::WriteInfo(lst);
lst->Add("Angle="+String(FAngle));
lst->Add("X="+String(FP.x));
lst->Add("Y="+String(FP.y));
}

void __fastcall TPatLabelAngle::ReadInfo(TStringList* lst)
{
TPatLabel::ReadInfo(lst);
try {FAngle=lst->Values["Angle"].ToInt();} catch(...) {FAngle=0;}
try {FP.x=lst->Values["X"].ToInt();} catch(...) {FP.x=0;}
try {FP.y=lst->Values["Y"].ToInt();} catch(...) {FP.y=0;}
}

void __fastcall TPatLine::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
HDC dc=Cont->DC;
SelectObject(dc,CreatePen(PS_SOLID,FWidth*K+0.5,FColor));
MoveToEx(dc,cx+FP1.x*K+0.5,cy+FP1.y*K+0.5,NULL);
LineTo(dc,cx+FP2.x*K+0.5,cy+FP2.y*K+0.5);
DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
}
void __fastcall TPatLine::ReadInfo(TStringList* lst)
{
TPatFigure::ReadInfo(lst);
try {FColor=lst->Values["Color"].ToInt();} catch(...) {FColor=0;}
try {FWidth=lst->Values["Width"].ToInt();} catch(...) {FWidth=1;}
try {FP1.x=lst->Values["X1"].ToInt();} catch(...) {FP1.x=0;}
try {FP1.y=lst->Values["Y1"].ToInt();} catch(...) {FP1.y=0;}
try {FP2.x=lst->Values["X2"].ToInt();} catch(...) {FP2.x=0;}
try {FP2.y=lst->Values["Y2"].ToInt();} catch(...) {FP2.y=0;}
}

void __fastcall TPatLine::Write(TStringList* lst)
{
lst->Add("Figure=Line");
WriteInfo(lst);
}

void __fastcall TPatLine::WriteInfo(TStringList* lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("Color="+String(FColor));
lst->Add("Width="+String(FWidth));
lst->Add("X1="+String(FP1.x));
lst->Add("Y1="+String(FP1.y));
lst->Add("X2="+String(FP2.x));
lst->Add("Y2="+String(FP2.y));
}

void __fastcall TPatRectangle::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
HDC dc=Cont->DC;
SelectObject(dc,CreatePen(PS_SOLID,FPenWidth*K+0.5,FPenColor));
SelectObject(dc,CreateSolidBrush(FBrushColor));
Rectangle(dc,cx+FP1.x*K+0.5,cy+FP1.y*K+0.5,cx+FP2.x*K+0.5,cy+FP2.y*K+0.5);
DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
DeleteObject(SelectObject(dc,GetStockObject(NULL_BRUSH)));
}

void __fastcall TPatRectangle::ReadInfo(TStringList* lst)
{
TPatFigure::ReadInfo(lst);
try {FPenColor=lst->Values["PenColor"].ToInt();} catch(...) {FPenColor=0;}
try {FPenWidth=lst->Values["PenWidth"].ToInt();} catch(...) {FPenColor=0;}
try {FBrushColor=lst->Values["BrushColor"].ToInt();} catch(...) {FBrushColor=1;}
try {FP1.x=lst->Values["X1"].ToInt();} catch(...) {FP1.x=0;}
try {FP1.y=lst->Values["Y1"].ToInt();} catch(...) {FP1.y=0;}
try {FP2.x=lst->Values["X2"].ToInt();} catch(...) {FP2.x=0;}
try {FP2.y=lst->Values["Y2"].ToInt();} catch(...) {FP2.y=0;}
}

void __fastcall TPatRectangle::Write(TStringList* lst)
{
lst->Add("Figure=Rectangle");
WriteInfo(lst);
}

void __fastcall TPatRectangle::WriteInfo(TStringList* lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("PenColor="+String(FPenColor));
lst->Add("PenWidth="+String(FPenWidth));
lst->Add("BrushColor="+String(FBrushColor));
lst->Add("X1="+String(FP1.x));
lst->Add("Y1="+String(FP1.y));
lst->Add("X2="+String(FP2.x));
lst->Add("Y2="+String(FP2.y));
}

void __fastcall TPatGrid::ReadInfo(TStringList* lst)
{
TPatFigure::ReadInfo(lst);
try {FPenColor=lst->Values["PenColor"].ToInt();} catch(...) {FPenColor=0;}
try {FPenWidth=lst->Values["PenWidth"].ToInt();} catch(...) {FPenColor=0;}
try {FBorder=lst->Values["Border"].ToInt();} catch(...) {FBorder=0;}
try {FVSpace=lst->Values["VSpace"].ToInt();} catch(...) {FVSpace=100;}
try {FHSpace=lst->Values["HSpace"].ToInt();} catch(...) {FHSpace=100;}
try {FP1.x=lst->Values["X1"].ToInt();} catch(...) {FP1.x=0;}
try {FP1.y=lst->Values["Y1"].ToInt();} catch(...) {FP1.y=0;}
try {FP2.x=lst->Values["X2"].ToInt();} catch(...) {FP2.x=0;}
try {FP2.y=lst->Values["Y2"].ToInt();} catch(...) {FP2.y=0;}
}

void __fastcall TPatGrid::Write(TStringList* lst)
{
lst->Add("Figure=Grid");
WriteInfo(lst);
}

void __fastcall TPatGrid::WriteInfo(TStringList* lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("PenColor="+String(FPenColor));
lst->Add("PenWidth="+String(FPenWidth));
lst->Add("Border="+String((int)FBorder));
lst->Add("VSpace="+String(FVSpace));
lst->Add("HSpace="+String(FHSpace));
lst->Add("X1="+String(FP1.x));
lst->Add("Y1="+String(FP1.y));
lst->Add("X2="+String(FP2.x));
lst->Add("Y2="+String(FP2.y));
}

void __fastcall TPatGrid::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
HDC dc=Cont->DC;
SelectObject(dc,CreatePen(PS_SOLID,FPenWidth*K+0.5,FPenColor));
SelectObject(dc,GetStockObject(NULL_BRUSH));
POINT p1,p2;
p1.x=cx+FP1.x*K+0.5;
p2.x=cx+FP2.x*K+0.5;
p1.y=cy+FP1.y*K+0.5;
p2.y=cy+FP2.y*K+0.5;
int t;
int i=1;
t=cx+(FP1.x+FHSpace)*K+0.5;
while (t<p2.x)
    {
    MoveToEx(dc,t,p1.y,NULL);
    LineTo(dc,t,p2.y);
    i++;
    t=cx+(FP1.x+FHSpace*i)*K+0.5;
    }
i=1;
t=cy+(FP1.y+FVSpace)*K+0.5;
while (t<p2.y)
    {
    MoveToEx(dc,p1.x,t,NULL);
    LineTo(dc,p2.x,t);
    i++;
    t=cy+(FP1.y+FVSpace*i)*K+0.5;
    }
if (FBorder)
    Rectangle(dc,cx+FP1.x*K+0.5,cy+FP1.y*K+0.5,cx+FP2.x*K+0.5,cy+FP2.y*K+0.5);
DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
}

void __fastcall TPatKmSign::ReadInfo(TStringList* lst)
{
TPatFigure::ReadInfo(lst);
try {FPenColor=lst->Values["PenColor"].ToInt();} catch(...) {FPenColor=0;}
try {FPenWidth=lst->Values["PenWidth"].ToInt();} catch(...) {FPenColor=0;}
try {FBrushColor=lst->Values["BrushColor"].ToInt();} catch(...) {FBrushColor=clRed;}
try {FSize=lst->Values["Size"].ToInt();} catch(...) {FSize=10;}
try {FP.x=lst->Values["X"].ToInt();} catch(...) {FP.x=0;}
try {FP.y=lst->Values["Y"].ToInt();} catch(...) {FP.y=0;}
}

void __fastcall TPatKmSign::Write(TStringList* lst)
{
lst->Add("Figure=KmSign");
WriteInfo(lst);
}

void __fastcall TPatKmSign::WriteInfo(TStringList* lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("PenColor="+String(FPenColor));
lst->Add("PenWidth="+String(FPenWidth));
lst->Add("BrushColor="+String(FBrushColor));
lst->Add("Size="+String(FSize));
lst->Add("X="+String(FP.x));
lst->Add("Y="+String(FP.y));
}

void __fastcall TPatKmSign::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
HDC dc=Cont->DC;
SelectObject(dc,CreateSolidBrush(FBrushColor));
SelectObject(dc,GetStockObject(NULL_PEN));
POINT p;
int sz;
p.x=cx+FP.x*K+0.5;
p.y=cy+FP.y*K+0.5;
sz=(FSize*K)/2+0.5;
Pie(dc,p.x-sz,p.y-sz,p.x+sz,p.y+sz,p.x,p.y+sz,p.x,p.y-sz);
DeleteObject(SelectObject(dc,GetStockObject(NULL_BRUSH)));
SelectObject(dc,CreatePen(PS_SOLID,FPenWidth*K+0.5,FPenColor));
Ellipse(dc,p.x-sz,p.y-sz,p.x+sz,p.y+sz);
DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
}

void __fastcall TPatRoadObject::ReadInfo(TStringList *lst)
{
TPatFigure::ReadInfo(lst);
try {FObjCode=lst->Values["ObjCode"].ToInt();} catch(...) {FObjCode=0;}
try {FObjChr=lst->Values["ObjChr"].ToInt();} catch(...) {FObjChr=0;}
String PStr=lst->Values["Points"];
char *str=PStr.c_str();
int ind=0;
int x,y,c,s=0;
if (str)
    {
    while (*str)
        {
        switch (s)
            {
            case 0:
                {
                if (*str=='{')
                    {
                    x=y=0;
                    c=0;
                    s=1;
                    }
                } break;
            case 1:
            case 2:
            case 3:
                {
                if (*str=='}')
                    {
                    FPoly->Points[ind].x=x;
                    FPoly->Points[ind].y=y;
                    FPoly->Codes[ind]=c;
                    ind++;
                    s=0;
                    }
                else if (*str==';')
                    s++;
                else if ((*str>='0')&&(*str<='9'))
                    {
                    if (s==1)
                        x=x*10+*str-'0';
                    else if (s==2)
                        y=y*10+*str-'0';
                    else if (s==3)
                        c=c*10+*str-'0';
                    }
                } break;
            }
        str++;
        }
    }
FPoly->Count=ind;
}

void __fastcall TPatRoadObject::Write(TStringList *lst)
{
lst->Add("Figure=RoadObject");
WriteInfo(lst);
}

void __fastcall TPatRoadObject::WriteInfo(TStringList *lst)
{
TPatFigure::WriteInfo(lst);
lst->Add("ObjCode="+String(FObjCode));
lst->Add("ObjChr="+String(FObjChr));
String Met="";
for (int i=0;i<FPoly->Count;i++)
    {
    int x=FPoly->Points[i].x;
    int y=FPoly->Points[i].y;
    int c=FPoly->Codes[i]();
    Met+=String("{")+String(x)+String(",")+String(y)+String(",")+String(c)+String("}");
    }
lst->Add("Points="+Met);
}

void __fastcall TPatRoadObject::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,int PageInd)
{
TExtPolyline *NewPoly=new TExtPolyline(16);
int n=FPoly->Count;
NewPoly->Count=n;
POINT *SP=FPoly->Points;
POINT *NP=NewPoly->Points;
int *SCod=(int*)FPoly->Codes;
int *NCod=(int*)NewPoly->Codes;
for (int i=0;i<n;i++)
    {
    NP[i].x=cx+SP[i].x*K+0.5;
    NP[i].y=cy+SP[i].y*K+0.5;
    NCod[i]=SCod[i];
    }
int drwpar=Man->Dict->SelectDrwParam(FObjCode,FObjChr,PageInd);
TDrwClassesRec *ClRec=Man->Dict->DrwClasses->Items[drwpar];
TObjList<TDrwParamRec> *DrPar=Man->Dict->DrwParams;

if (ClRec)
    {
    double dpsm=(double)GetDeviceCaps(Cont->DC,LOGPIXELSX)/2.54;
    for (int k=0;k<MAXDRWPARAM;k++)
        {
        TDrwParamRec *Rec=DrPar->Items[ClRec->DrwParamId[k]];
        if (Rec)
            {
            Man->CallDrawFunc(Cont,NewPoly,Rec,&TRect(0,0,0,0),Man->BaseScaleL,Man->BaseScaleX/((K*100)/dpsm),pk,pd,dpsm,false);
            }
        }
    }
delete NewPoly;
}

__fastcall TDrawPattern::TDrawPattern(void)
{
FFigures=new TObjList<TPatFigure>;
FRepList=new TStringList;
FPlanCenter=NULL;
FPageSize=NULL;
FCurvePlanCenter=NULL;
FProfilCenter=NULL;
}

__fastcall TDrawPattern::~TDrawPattern(void)
{
delete FFigures;
delete FRepList;
}

bool __fastcall TDrawPattern::LoadFromFile(String FileName)
{
bool Res=false;
char c[1024];
Clear();
ifstream in(FileName.c_str());
if (in.is_open())
    {
    Res=true;
    TStringList *Text=new TStringList;
    while (!in.eof())
        {
        in.getline(c,1024);
        Text->CommaText=c;
        String FKind=Text->Values["Figure"];
        if (FKind=="PageSize")
            {
            TPatPageSize *ps=new TPatPageSize;
            ps->ReadInfo(Text);
            FPageSize=ps;
            FFigures->Add(ps);          // Заносим эти объекты в список, для упрощения записи их в файл
            }
        else if (FKind=="PlanCenter")
            {
            TPatPlanCenter *pc=new TPatPlanCenter;
            pc->ReadInfo(Text);
            FFigures->Add(pc);
            }
        else if (FKind=="CurvePlanCenter")
            {
            TPatCurvePlanCenter *pc=new TPatCurvePlanCenter;
            pc->ReadInfo(Text);
            FFigures->Add(pc);
            }
        else if (FKind=="ProfilCenter")
            {
            TPatProfilCenter *pc=new TPatProfilCenter;
            pc->ReadInfo(Text);
            FFigures->Add(pc);
            }
        else if (FKind=="Line")
            {
            TPatLine *ln=new TPatLine;
            ln->ReadInfo(Text);
            FFigures->Add(ln);
            }
        else if (FKind=="Rectangle")
            {
            TPatRectangle *rc=new TPatRectangle;
            rc->ReadInfo(Text);
            FFigures->Add(rc);
            }
        else if (FKind=="Grid")
            {
            TPatGrid *rc=new TPatGrid;
            rc->ReadInfo(Text);
            FFigures->Add(rc);
            }
        else if (FKind=="KmSign")
            {
            TPatKmSign *rc=new TPatKmSign;
            rc->ReadInfo(Text);
            FFigures->Add(rc);
            }
        else if (FKind=="LabelRect")
            {
            TPatLabelRect *lr=new TPatLabelRect;
            lr->ReadInfo(Text);
            FFigures->Add(lr);
            }
        else if (FKind=="LabelAngle")
            {
            TPatLabelAngle *la=new TPatLabelAngle;
            la->ReadInfo(Text);
            FFigures->Add(la);
            }
        else if (FKind=="RoadObject")
            {
            TPatRoadObject *la=new TPatRoadObject;
            la->ReadInfo(Text);
            FFigures->Add(la);
            }
        }
    delete Text;
    }
FMaxSection=0;
for (int i=0;i<FFigures->Count;i++)
    if (FMaxSection<FFigures->Items[i]->Section)
        FMaxSection=FFigures->Items[i]->Section;
SetSection(0);
return Res;
}

void __fastcall TDrawPattern::SaveToFile(String FileName)
{
ofstream out(FileName.c_str());
if (out.is_open())
    {
    TStringList *Text=new TStringList;
    for (int i=0;i<FFigures->Count;i++)
        {
        FFigures->Items[i]->Write(Text);
        out<<Text->CommaText.c_str()<<"\n";
        Text->Clear();
        }
    delete Text;
    }
}

void __fastcall TDrawPattern::SetSection(int newsec)
{
FSection=newsec;
FPageSize=NULL;
FPlanCenter=NULL;
FCurvePlanCenter=NULL;
FProfilCenter=NULL;
for (int i=0;i<FFigures->Count;i++)
    {
    if (FFigures->Items[i]->Section==FSection)
        {
        TPatPageSize *ps=dynamic_cast<TPatPageSize*>(FFigures->Items[i]);
        if (ps)
            FPageSize=ps;
        TPatPlanCenter *pc=dynamic_cast<TPatPlanCenter*>(FFigures->Items[i]);
        if (pc)
            FPlanCenter=pc;
        TPatCurvePlanCenter *pcpc=dynamic_cast<TPatCurvePlanCenter*>(FFigures->Items[i]);
        if (pcpc)
            FCurvePlanCenter=pcpc;
        TPatProfilCenter *ppc=dynamic_cast<TPatProfilCenter*>(FFigures->Items[i]);
        if (ppc)
            FProfilCenter=ppc;
        }

    }
}


void __fastcall TDrawPattern::DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)
{
for (int i=0;i<FFigures->Count;i++)
    {
    if (FFigures->Items[i]->Section==FSection)
        {
        TPatLabel *lab=dynamic_cast<TPatLabel*>(FFigures->Items[i]);
        if (lab)
            lab->RepList=RepList;
        FFigures->Items[i]->DrawTo(Man,Cont,K,cx,cy,pk,pd,PageInd);
        }
    }
}

void __fastcall TDrawPattern::Clear(void)
{
FPlanCenter=NULL;
FPageSize=NULL;
FCurvePlanCenter=NULL;
FProfilCenter=NULL;
FFigures->Clear();
}

bool __fastcall TDrawPattern::GetPlanCenter(int &x,int &y)
{
if (FPlanCenter)
    {
    x=FPlanCenter->X;
    y=FPlanCenter->Y;
    return true;
    }
return false;
}

bool __fastcall TDrawPattern::GetPlanSize(int &x,int &y)
{
if (FPlanCenter)
    {
    x=FPlanCenter->Width;
    y=FPlanCenter->Height;
    return true;
    }
return false;
}

bool __fastcall TDrawPattern::GetCurvePlanRect(TRect &r)
{
if (FCurvePlanCenter)
    {
    FCurvePlanCenter->FillRect(r);
    return true;
    }
return false;
}

bool __fastcall TDrawPattern::GetProfilRect(TRect &r)
{
if (FProfilCenter)
    {
    FProfilCenter->FillRect(r);
    return true;
    }
return false;
}

bool __fastcall TDrawPattern::GetPlanOffsets(int &l,int &r,int &t,int &b)
{
if (FPageSize)
    {
    l=FPageSize->LeftOfs;
    r=FPageSize->RightOfs;
    t=FPageSize->TopOfs;
    b=FPageSize->BottomOfs;
    return true;
    }
return false;
}

bool __fastcall TDrawPattern::GetPageSize(int &x,int &y)
{
if (FPageSize)
    {
    x=FPageSize->Width;
    y=FPageSize->Height;
    return true;
    }
return false;
}
