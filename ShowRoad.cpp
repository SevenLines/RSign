//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ShowRoad.h"
#include "MainUnit.h"
#include "FileSour.h"
#include "ObjForm.h"
#include "DrawSetting.h"
#include "SettingFrm.h"
#include "SelNewSign.h"
#include "SelNewObj.h"
//#include "ShowVideo.h"
#include "PrnForm.h"
#include "bmpexport.h"
#include "MetaExport.h"
#include "DBDataSource.h"
#include "SignDesign.h"
#include "PolyForm.h"
#include "DesignPattern.h"
#include "Picture.h"
#include "BuildSlopes.h"
#include "BuildWidePart.h"
#include "RoadMark.h"
#include "acadexport.h"
#include <Registry.hpp>
#include <algorithm>

#include "VideoForm.h"
#include "ProgressFrm.h"
#include "AutoCADExportForm.h"
#include "AcadExportThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TRoadFrm *RoadFrm;
//---------------------------------------------------------------------------
__fastcall TRoadFrm::TRoadFrm(TComponent* Owner)
    : TForm(Owner)
{
FReadyForDrawing=false;
FInsertingObj=NULL;
FRoadId=0;
FViewId=0;
FPan1Vis=false;
FPan2Vis=false;
FPan3Vis=false;
FPan4Vis=false;
FEditedData=NULL;
FMetricData=NULL;
FVideoData=NULL;
FProfilData=NULL;
FCurveData=NULL;
FDictSour=NULL;
FDrawMan=NULL;
FDrawCont=NULL;
FOutMan=NULL;
FSlopesCont=NULL;
FVisCont=NULL;
FDressCont=NULL;
FVector=NULL;
HRuler=new TRuler(RulPanel);
HRuler->Parent=RulPanel;
HRuler->Kind=rkGorisontal;
HRuler->Align=alClient;

VRuler=new TRuler(VRulPanel);
VRuler->Parent=VRulPanel;
VRuler->Kind=rkVertical;
VRuler->Align=alClient;
FActiveObj=NULL;
FActiveSource=NULL;
FPartVisible=false;
FGridVisible=false;
FMoving=false;
FRectVisible=false;
FEditMetric=false;
FShowProfil=false;
FPlanKind=pkGorizontal;
FPlanDirect=pdDirect;
ZoomStatus=zsNone;
FKmInPage=1;
PBox->Parent->DoubleBuffered=true;
PrBox->Parent->DoubleBuffered=true;
PvBox->Parent->DoubleBuffered=true;
FDpsm=PixelsPerInch/2.54;
PlanPan->Brush->Style=bsClear;
PBox->ControlStyle=PBox->ControlStyle<<csOpaque;
PostActivateObj();

lPlace = opLeft;
lKind = skStolb;
frmSignalsInsert1 = new TfrmSignalsInsert(this);
}

void __fastcall TRoadFrm::CloseRoad(void)
{
FReadyForDrawing=false;
Caption="";
delete FDrawMan;
FDrawMan=NULL;
delete FOutMan;
FOutMan=NULL;
delete FDrawCont;
FDrawCont=NULL;
delete FSlopesCont;
FSlopesCont=NULL;
delete FVisCont;
FVisCont=NULL;
delete FDressCont;
FDressCont=NULL;
delete SelectRect;
SelectRect=NULL;
delete SelectObj;
SelectObj=NULL;
delete FInsertingObj;
FInsertingObj=NULL;
if (VisSet)
    {
    TForm *TmpForm=VisSet;
    VisSet->ReleaseData();
    TmpForm->Release();
    }
FVMinL=FVMaxL=FPMinL=FPMaxL=FMinX=FMaxX=0;
FEditedData=NULL;
FMetricData=NULL;
FVideoData=NULL;
FProfilData=NULL;
FCurveData=NULL;
}

void __fastcall TRoadFrm::SaveRegistry(void)
{
TRegistry *reg=new TRegistry();
reg->OpenKey("ViewParam",true);
reg->WriteInteger("BaseScaleX",BaseScaleX);
reg->WriteInteger("BaseScaleP",BaseScaleP);
reg->WriteInteger("BaseScaleL",BaseScaleL);
reg->WriteInteger("BoundX",FMaxX/100);
if (FMetricData)
    if (FMetricData->Road)
        reg->WriteInteger("ObjectMaxX",FMetricData->Road->XMax/100);
reg->WriteInteger("FontSize",FDrawMan->FontSize);
delete reg;
}

void __fastcall TRoadFrm::LoadRegistry(void)
{
TRegistry *reg=new TRegistry();
try
    {
    reg->OpenKey("ViewParam",false);
    int x=reg->ReadInteger("BaseScaleX");
    int l=reg->ReadInteger("BaseScaleL");
    int p=reg->ReadInteger("BaseScaleP");
    if (x&&l&&p)
        SetBaseScale(l,x,p);
    int fn=reg->ReadInteger("FontSize");
    if (fn)
        FDrawMan->FontSize=fn;
    int bx=reg->ReadInteger("BoundX");
    int obx=reg->ReadInteger("ObjectMaxX");
    if (bx&&obx)
        SetXBounds(bx*100,obx*100);
    }
catch (...)
    {}
delete reg;
}

void __fastcall TRoadFrm::Initialize(TDictSource *dict,TSharedObjSource *shared)
{
FDictSour=dict;
FShared=shared;
FDrawMan=new TDrawManager();
FDrawMan->BaseScaleL=4000;
FDrawMan->BaseScaleX=1000;
FDrawMan->BaseScaleP=1000;
FDrawMan->FontSize=12;
FDrawMan->Dict=FDictSour;
FDrawMan->Shared=Shared;
FDrawCont=new TDrawBitmap;
FOutMan=new TDrawManager();
FOutMan->SetDefaults(FDrawMan);
FSlopesCont=new TDrawBitmap;
FDressCont=new TDrawBitmap;
FVisCont=new TDrawBitmap;
SelectRect=new TSelectRect(PBox->Canvas);
SelectObj=new TSelectObj(PBox->Canvas,FDrawMan);
ShowPanels();
}

void __fastcall TRoadFrm::OpenView(__int32 RoadId,__int32 ViewId,TDictSource *dict,TSharedObjSource *shared)
{
FRoadId=RoadId;
FRoadName=DBDataModule->GetRoadName(FRoadId);
FDistrictName = DBDataModule->GetDistrName(FRoadId);
Caption=FRoadName;
try{
Caption += " ("+DBDataModule->GetDistrName(FRoadId) + ")";
}catch(...){}
FViewId=ViewId;
FViewName=DBDataModule->GetViewName(FViewId);
Initialize(dict,shared);
Application->CreateForm(__classid(TVisSetFrm), &VisSet);
VisSet->RoadFrm=this;
DBDataModule->LoadViewSources(FRoadId,FViewId);
VisSet->SetRoadId(FRoadId,FDictSour);
FindSources();
FDrawMan->VisSet=VisSet;
DBDataModule->ReleaseViewSources(FRoadId,FViewId);// Теперь источниками уже владеет дорога
DBDataModule->LoadVisible(FRoadId,FViewId,VisSet);
if (FMetricData)
    {
    FPMinX=FMinX;
    FPMaxX=FMaxX;
    FPMinL=FMinL;
    FPMaxL=FMaxL;
    FPartMinL=FMinL;
    FPartMaxL=FMaxL;
    BuildKmSet(FKmInPage);
    DBDataModule->LoadViewParam(this,FViewId);
    // Автоматическое построение линий --- Временно Необходимо убрать
//    BuildRoadLines();
    FReadyForDrawing=true;
    RefreshPlan();
    ScaleL(1.0);
    FDictSour->BuildPagesList(PageSet->Items);
    FCurPage=1;
    PageSet->ItemIndex=0;
    RefreshPlan();
    ShowAll();    
    }
LoadRegistry();
PostAction();
}

void __fastcall TRoadFrm::OpenRoad(__int32 RoadId,TDictSource *dict,TSharedObjSource *shared)
{
FRoadId=RoadId;
FRoadName=DBDataModule->GetRoadName(FRoadId);
Caption=FRoadName;
Initialize(dict,shared);
Application->CreateForm(__classid(TVisSetFrm), &VisSet);
VisSet->RoadFrm=this;
VisSet->SetRoadId(FRoadId,FDictSour);
FindSources();
FDrawMan->VisSet=VisSet;
if (FMetricData)
    {
    FPartMinL=FMinL;
    FPartMaxL=FMaxL;
    FRelativeNull=0;
    BuildKmSet(FKmInPage);
    // Автоматическое построение линий --- Временно Необходимо убрать
//    BuildRoadLines();
    FReadyForDrawing=true;
    FDictSour->BuildPagesList(PageSet->Items);
    PageSet->ItemIndex=0;
    FCurPage=1;
    RefreshPlan();
    ShowAll();
    }
LoadRegistry();
PostAction();
}

//---------------------------------------------------------------------------
void __fastcall TRoadFrm::OpenRoad(String Capt,TDtaSource* data,TDictSource* dict,TSharedObjSource *shared)
{
FRoadName=data->RoadName;
FRoadId=data->Id;
Caption=Capt;
Initialize(dict,shared);
if (data->Ready)
    {
    FMetricData=data;
    SetRoadBounds();
    FPartMinL=FMinL;
    FPartMaxL=FMaxL;
    BuildKmSet(FKmInPage);
    Application->CreateForm(__classid(TVisSetFrm), &VisSet);
    VisSet->RoadFrm=this;
    VisSet->SetRoadId(FRoadId,FDictSour);
    FDrawMan->VisSet=VisSet;
    VisSet->SetSourceVisible(data);
    // Автоматическое построение линий --- Временно Необходимо убрать
//    BuildRoadLines();
    FReadyForDrawing=true;
    LoadRegistry();
    FDictSour->BuildPagesList(PageSet->Items);
    PageSet->ItemIndex=0;
    FCurPage=1;
    RefreshPlan();
    ShowAll();
    }
else
    ShowMessage("Данные не готовы!");
PostAction();
}

void __fastcall TRoadFrm::SetRoadBounds(void)
{
if (FMetricData)
    {
    FMinX=FMetricData->Road->XMin;
    FMaxX=FMetricData->Road->XMax;
    if (FMinX>-10000)
        FMinX=-10000;
    if (FMaxX<10000)
        FMaxX=10000;
    FRoadMinL=FMetricData->Road->LMin;
    FRoadMaxL=FMetricData->Road->LMax;
    FMinL=FRoadMinL-FDrawMan->BaseScaleL;
    FMaxL=FRoadMaxL+FDrawMan->BaseScaleL;
    }
}

void __fastcall TRoadFrm::FindSources(void)
{
if (VisSet)
    {
    FEditedData=VisSet->EditedSource;
    FMetricData=VisSet->MetricSource;
    FProfilData=VisSet->ProfilSource;
    FVideoData=VisSet->VideoSource;
    FCurveData=VisSet->CurveSource;
    SetRoadBounds();
    }
}

void __fastcall TRoadFrm::SaveData(void)
{
TResManager *ResMan=MainForm->ResManager;
for (int i=0;i<ResMan->DataCount;i++)
    {
    TDtaSource *Dta=ResMan->Data[i];
    if (Dta->Id==RoadId)
        {
        TFileDataSource *FileData=dynamic_cast<TFileDataSource*>(Dta);
        if (FileData)
            FileData->Dump(Dict,true);
        TDBDataSource *DBData=dynamic_cast<TDBDataSource*>(Dta);
        if (DBData)
            DBData->Apply(Dict);
        }
    }
}

void __fastcall TRoadFrm::ReLoadData(void)
{
if (FEditMetric)
    ShowMessage("В режиме редактирования метрики эта операция невозможна");
else if (Application->MessageBox("Все изменения с момента последнего сохранения будут отменены. Продолжить?","Предупреждение",MB_YESNO)==ID_YES)
    {
    TResManager *ResMan=MainForm->ResManager;
    for (int i=0;i<ResMan->DataCount;i++)
        {
        TDtaSource *Dta=ResMan->Data[i];
        if (Dta->Id==RoadId)
            {
            int OldId=Dta->Id;
            int OldDClass=Dta->DataClass;
            Dta->Recreate(Dict);
            Dta->Load(OldId,OldDClass,Dict);
            MainForm->SendBroadCastMessage(CM_DATARELOAD,0,(int)Dta);
            }
        }
    }
}

void __fastcall TRoadFrm::ShowAll(void)
{
FPMinL=FMinL;
FPMaxL=FMaxL;
FPMinX=FMinX;
FPMaxX=FMaxX;
SetMarkerPos((FPMinL+FPMaxL)>>1);
ScaleL(1);
}

void __fastcall TRoadFrm::ScaleByRect(void)
{
int MinX,MaxX,MinY,MaxY;
if (SRectPos.x<CRectPos.x)
    {
    MinX=SRectPos.x;
    MaxX=CRectPos.x;
    }
else
    {
    MinX=CRectPos.x;
    MaxX=SRectPos.x;
    }
if (SRectPos.y<CRectPos.y)
    {
    MinY=SRectPos.y;
    MaxY=CRectPos.y;
    }
else
    {
    MinY=CRectPos.y;
    MaxY=SRectPos.y;
    }
FMetricData->Road->SetFrame(FPMinL,FPMaxL,FPMinX,FPMaxX,FPlanKind,FPlanDirect);
FMetricData->Road->SetOutBound(0,PBox->Width,0,PBox->Height);
if (((MaxX-MinX)<5) && ((MaxY-MinY)<5))
    {
    int DPX=(FPMaxX-FPMinX)>>2;
    int DPL=(FPMaxL-FPMinL)>>2;
    int CX,CL;
    FMetricData->Road->RConvertPoint((MinX+MaxX)>>1,(MinY+MaxY)>>1,CL,CX);
    FPMinX=CX-DPX;
    FPMaxX=CX+DPX;
    FPMinL=CL-DPL;
    FPMaxL=CL+DPL;
    }
else
    {
    if (FPlanKind==pkGorizontal)
        {
        FMetricData->Road->RConvertPoint(MinX,MinY,FPMinL,FPMinX);
        FMetricData->Road->RConvertPoint(MaxX,MaxY,FPMaxL,FPMaxX);
        }
    else
        {
        FMetricData->Road->RConvertPoint(MaxX,MaxY,FPMinL,FPMaxX);
        FMetricData->Road->RConvertPoint(MinX,MinY,FPMaxL,FPMinX);
        }
    if (FPMinL>FPMaxL)
        {
        __int32 t=FPMinL;
        FPMinL=FPMaxL;
        FPMaxL=t;
        }
    if (FPMinX>FPMaxX)
        {
        __int32 t=FPMinX;
        FPMinX=FPMaxX;
        FPMaxX=t;
        }
    }
SetMarkerPos((FPMinL+FPMaxL)>>1);
ShowScale();
InvalidateBoxes();
}

void __fastcall TRoadFrm::ScaleL(double K)
{
if ((FSclL/K>=100)||(K<=1))
    {
    __int32 DL=FPMaxL-FPMinL;
    __int32 CL=(FPMaxL+FPMinL)>>1;
    DL=(double)DL/K+0.5;
    if (DL>(FMaxL-FMinL))
        DL=FMaxL-FMinL;
    DL>>=1;
    FPMaxL=CL+DL;
    FPMinL=CL-DL;
    if (FPMinL<FMinL)
        {
        FPMaxL+=FMinL-FPMinL;
        FPMinL=FMinL;
        }
    if (FPMaxL>FMaxL)
        {
        FPMinL-=FPMaxL-FMaxL;
        FPMaxL=FMaxL;
        }
    ShowScale();
    InvalidateBoxes();
    }
}

void __fastcall TRoadFrm::PutPLMin(__int32 Pos,__int32 Max)
{
double d;
if (Max>0)
    d=(double)Pos/Max;
else
    d=0;
double DL=FPMaxL-FPMinL;
FPMinL=FMinL+(FMaxL-FMinL-DL)*d;
FPMaxL=FPMinL+DL;
if (FPMaxL>FMaxL)
    {
    FPMinL-=(FPMaxL-FMaxL);
    FPMaxL=FMaxL;
    }
KmSetText();
InvalidateBoxes();
}

void __fastcall TRoadFrm::PutPXMin(__int32 Pos,__int32 Max)
{
double d;
if (Max>0)
    d=(double)Pos/Max;
else
    d=0;
double DX=FPMaxX-FPMinX;
FPMinX=FMinX+(FMaxX-FMinX-DX)*d;
FPMaxX=FPMinX+DX;
if (FPMaxX>FMaxX)
    {
    FPMinX-=(FPMaxX-FMaxX);
    FPMaxX=FMaxX;
    }
InvalidateBoxes();
}

void __fastcall TRoadFrm::ShowScale(void)
{
if ((FPMaxL>FPMinL)&&(FPMaxX>FPMinX))
    {
    int pl,px;
    bool visv=true;
    bool vish=true;
    if ((FPMinX==FMinX)&&(FPMaxX==FMaxX))
        {
        if (FPlanKind==pkGorizontal)
            visv=false;
        else
            vish=false;
        }
    VScroll->Visible=visv;
    HScroll->Visible=vish;
    if (FPlanKind==pkGorizontal)
        {
        pl=PBox->Width,
        px=PBox->Height;
        }
    else
        {
        px=PBox->Width,
        pl=PBox->Height;
        }
    if (FPMaxL>FMaxL)
      FPMaxL=FMaxL;
    if (FPMinL<FMinL)
      FPMinL=FMinL;  
    double DPL=FPMaxL-FPMinL;
    double DPX=FPMaxX-FPMinX;
    double dl=(double)(FMaxL-FMinL)/DPL;
    double dx=(double)(FMaxX-FMinX)/DPX;
    __int32 scl=pl*(dl-1);
    __int32 scx=px*(dx-1);
    TNotifyEvent e1,e2;
    e1=HScroll->OnChange;
    e2=VScroll->OnChange;
    HScroll->OnChange=NULL;
    VScroll->OnChange=NULL;
    if (FPlanKind==pkGorizontal)
        {
        if (scl)
            {
            if (FPlanDirect==pdDirect)
                HScroll->SetParams((double)(FPMinL-FMinL)/(FMaxL-FMinL-DPL)*scl,0,scl);
            else
                HScroll->SetParams(scl-(double)(FPMinL-FMinL)/(FMaxL-FMinL-DPL)*scl,0,scl);
            }
        else
            HScroll->SetParams(0,0,0);
        if (scx)
            {
            if (FPlanDirect==pdDirect)
                VScroll->SetParams((double)(FPMinX-FMinX)/(FMaxX-FMinX-DPX)*scx,0,scx);
            else
                VScroll->SetParams(scx-(double)(FPMinX-FMinX)/(FMaxX-FMinX-DPX)*scx,0,scx);
            }
        else
            VScroll->SetParams(0,0,0);
        }
    else
        {
        if (scl)
            {
            if (FPlanDirect==pdDirect)
                VScroll->SetParams(scl-(double)(FPMinL-FMinL)/(FMaxL-FMinL-DPL)*scl,0,scl);
            else
                VScroll->SetParams((double)(FPMinL-FMinL)/(FMaxL-FMinL-DPL)*scl,0,scl);
            }
        else
            VScroll->SetParams(0,0,0);
        if (scx)
            {
            if (FPlanDirect==pdDirect)
                HScroll->SetParams((double)(FPMinX-FMinX)/(FMaxX-FMinX-DPX)*scx,0,scx);
            else
                HScroll->SetParams(scx-(double)(FPMinX-FMinX)/(FMaxX-FMinX-DPX)*scx,0,scx);
            }
        else
            HScroll->SetParams(0,0,0);
        }
    HScroll->OnChange=e1;
    VScroll->OnChange=e2;
    FSclL=(double)(FPMaxL-FPMinL)*FDpsm/pl+0.5;
    SclLVal->Text=String(FSclL);
    FSclX=(double)(FPMaxX-FPMinX)*FDpsm/px+0.5;
    SclXVal->Text=String(FSclX);
    FVMinL=FPMinL+(double)HIDEBOUND*FSclL/FDpsm;
    FVMaxL=FPMaxL-(double)HIDEBOUND*FSclL/FDpsm;
    KmSetText();
    }
}

void __fastcall TRoadFrm::ScaleX(double K)
{
if ((FSclX/K>=100)||(K<=1))
    {
    __int32 DX=FPMaxX-FPMinX;
    __int32 CX=(FPMaxX+FPMinX)>>1;
    DX=(double)DX/K+0.5;
    if (DX>(FMaxX-FMinX))
        DX=FMaxX-FMinX;
    DX>>=1;
    FPMaxX=CX+DX;
    FPMinX=CX-DX;
    if (FPMinX<FMinX)
        {
        FPMaxX+=FMinX-FPMinX;
        FPMinX=FMinX;
        }
    if (FPMaxX>FMaxX)
        {
        FPMinX-=FPMaxX-FMaxX;
        FPMaxX=FMaxX;
        }
    }
ShowScale();
InvalidateBoxes();
}

void __fastcall TRoadFrm::HideVideo(void)
{
frmVideoForm->CloseVideo();
frmVideoForm->Hide();
}

void __fastcall TRoadFrm::ShowVideo(int Direction,int id)
{
if (FVideoData) {
   if (Direction==1 && id>=0)
      FVideoData->DirVideoId=id;
   else if (id>=0)
      FVideoData->UnDirVideoId=id;
   frmVideoForm->InitVideo(FVideoData,Direction);
   frmVideoForm->Show();
   SynchronizeVideo();
   }
}

void __fastcall TRoadFrm::SetVideoPos(__int32 Pos)
{
int sign=frmVideoForm->Direction==1? 1: -1;
Pos-=sign*FrmSetting->VideoOffset*100;
__int32 DL=(FPMaxL-FPMinL)>>1;
FPMinL=Pos-DL;
FPMaxL=Pos+DL;
FMarkerL=Pos;
if (FPMaxL>FMaxL)
    {
    FPMinL-=(FPMaxL-FMaxL);
    FPMaxL=FMaxL;
    }
else if (FPMinL<FMinL)
  {
  FPMaxL+=FMinL-FPMinL;
  FPMinL=FMinL;
  }
ShowScale();
InvalidateBoxes();
}

void __fastcall TRoadFrm::BuildKmSet(__int32 Km)
{
int skm=FMinL/100000;
int ekm=(FMaxL+99999)/100000;
KmSet->Items->BeginUpdate();
KmSet->Items->Clear();
for (int i=skm;i<ekm;i+=Km)
    KmSet->Items->Add(String(i)+String("-")+String(min(i+Km,ekm))+String(" км"));
KmSet->Items->EndUpdate();
}

void __fastcall TRoadFrm::KmSetText(void)
{
int FVmnL=(FVMinL+5000)/10000;
int FVmxL=(FVMaxL+5000)/10000;
KmSet->Text=String((double)FVmnL/10)+"-"+String((double)FVmxL/10)+" км.";
}

void __fastcall TRoadFrm::PrintDialog(void)
{
if (Printer()==NULL)
    return;
int minkm=FMinL/100000;
int maxkm=(FMaxL+99999)/100000;
PrnParam->MinKm->Min=minkm;
PrnParam->MinKm->Max=maxkm;
PrnParam->MinKm->Position=FPMinL/100000;
PrnParam->MinKmM->Position=0;
PrnParam->MaxKm->Min=minkm;
PrnParam->MaxKm->Max=maxkm;
PrnParam->MaxKm->Position=(FPMaxL+99999)/100000;
PrnParam->MaxKmM->Position=0;
PrnParam->ScaleL->Text=FDrawMan->BaseScaleL;
PrnParam->ScaleLChange(PrnParam->ScaleL);
PrnParam->ScaleX->Text=FDrawMan->BaseScaleP;
if (FPlanKind==pkGorizontal)
    Printer()->Orientation=poLandscape;
else
    Printer()->Orientation=poPortrait;
if (PrnParam->ShowModal()==mrOk)
    {
    int skm=PrnParam->MinKm->Position*100000+PrnParam->MinKmM->Position*100;
    int ekm=PrnParam->MaxKm->Position*100000+PrnParam->MaxKmM->Position*100;
    int plen=PrnParam->PLen->Position*100000+PrnParam->PLenM->Position*100;
    int lms=PrnParam->ScaleL->Text.ToInt();
    int xms=PrnParam->ScaleX->Text.ToInt();
    int page=PrnParam->StartPage->Position;
    Print(skm,ekm,plen,lms,xms,page);
    }
}

String __fastcall PosToStr(int Pos)
{
String Res=String(Pos/1000);
int PosM=Pos%1000;
if (PosM)
    {
    Res+="+";
    Res+=String(PosM/100);
    PosM%=100;
    Res+=String(PosM/10);
    Res+=String(PosM%10);
    }
return Res;
}

void __fastcall TRoadFrm::PreparePattern(int minkm,int maxkm,int page)
{
    MainForm->Pattern->RepList->Clear();
    MainForm->Pattern->RepList->Add("RoadName="+String(FRoadName).Trim());
    MainForm->Pattern->RepList->Add("StartKm="+PosToStr(minkm));
    MainForm->Pattern->RepList->Add("EndKm="+PosToStr(maxkm));
    MainForm->Pattern->RepList->Add("PageNum="+String(page));
}

void __fastcall TRoadFrm::DrawFrames(TDrawManager *Man,TDrawContents *Cont,int dpi)
{
if (FReadyForDrawing)
    {
    TRect OutRect;
    void *dc=Cont->DC;
    int sx=GetDeviceCaps(dc,PHYSICALOFFSETX);
    int sy=GetDeviceCaps(dc,PHYSICALOFFSETY);
    if (MainForm->Pattern->GetProfilRect(OutRect))
        {
        OutRect.Top=(OutRect.Top*dpi)/254-sy;
        OutRect.Bottom=(OutRect.Bottom*dpi)/254-sy;
        OutRect.Left=(OutRect.Left*dpi)/254-sx;
        OutRect.Right=(OutRect.Right*dpi)/254-sx;
        Man->DrawProfil(Cont,&OutRect,FPlanKind,FPlanDirect);
        }
    if (MainForm->Pattern->GetCurvePlanRect(OutRect))
        {
        OutRect.Top=(OutRect.Top*dpi)/254-sy;
        OutRect.Bottom=(OutRect.Bottom*dpi)/254-sy;
        OutRect.Left=(OutRect.Left*dpi)/254-sx;
        OutRect.Right=(OutRect.Right*dpi)/254-sx;
        Man->DrawCurvesPlan(Cont,&OutRect,FPlanKind,FPlanDirect);
        }
    }
}

void __fastcall TRoadFrm::MakeBmpPage(TDrawContents* Cont,int minl,int maxl,int scll,int sclx, int dpi,int page)
{
int lpix=(double)(((maxl-minl)/scll)*dpi)/2.54;  // Размер в пикселях плана по длине
int xpix=(double)(((FMaxX-FMinX)/sclx)*dpi)/2.54; // Размер в пикселях плана по ширине
int hpix,vpix; // Размеры в пикселях по длине и высоте
if (FPlanKind==pkGorizontal)
    hpix=lpix,vpix=xpix;
else
    hpix=xpix,vpix=lpix;
int w,h; // Размер изображения в пикселях
int l,r,t,b; // Отступы
l=r=t=b=0;
if (MainForm->Pattern->GetPageSize(w,h))
    {
    if (MainForm->Pattern->GetPlanOffsets(l,r,t,b))
        {
        w-=l+r;
        h-=t+b;
        }
    w=(double)w*dpi/25.4+0.5;
    h=(double)h*dpi/25.4+0.5;
    l=(double)l*dpi/25.4+0.5;
    r=(double)r*dpi/25.4+0.5;
    t=(double)t*dpi/25.4+0.5;
    b=(double)b*dpi/25.4+0.5;
    }
else
    {
    w=hpix;
    h=vpix;
    }
int cx,cy; // Координаты центра плана в пикселях
if (MainForm->Pattern->GetPlanCenter(cx,cy))
    {
    cx=(cx*dpi)/254;
    cy=(cy*dpi)/254;
    }
else
    {
    cx=w/2;
    cy=h/2;
    }
// Рисуем план дороги
TRect OutRect(cx-hpix/2,cy-vpix/2,cx+hpix/2,cy+vpix/2);
Cont->SetParam(minl,maxl,FMinX,FMaxX);
Cont->SetSize(w,h);
Cont->PrepareUpdating();
FOutMan->SetDefaults(FDrawMan);
FOutMan->FillCont(Cont);
PreparePattern(minl/100,maxl/100,page);
MainForm->Pattern->DrawTo(FOutMan,Cont,(double)dpi/254,-l,-t,FPlanKind,FPlanDirect,FCurPage);
DrawMainPlan(FOutMan,Cont,scll,sclx,(double)dpi/2.54,&OutRect);
DrawFrames(FOutMan,Cont,dpi);
// Рисуем профиль
Cont->FinishUpdating();
}

void __fastcall TRoadFrm::MakePreViewPage(TDrawContents* Cont,int minl,int maxl,int scll,int sclx,int ms,int page)
{
if (Printer()==NULL)
    return;
HDC dc=Printer()->Handle;
int hsize=GetDeviceCaps(dc,HORZSIZE);
int vsize=GetDeviceCaps(dc,VERTSIZE);
int hpix=GetDeviceCaps(dc,HORZRES);
int vpix=GetDeviceCaps(dc,VERTRES);
int pdpi=GetDeviceCaps(dc,LOGPIXELSX);
int wdpi=GetDeviceCaps(Canvas->Handle,LOGPIXELSX);
int lpix=(double)(((maxl-minl)/scll)*wdpi*ms)/254;
int xpix=(double)(((FMaxX-FMinX)/sclx)*wdpi*ms)/254;
int cx=(double)hpix*wdpi*ms/(pdpi*200);
int cy=(double)(vpix*wdpi*ms)/(pdpi*200);
int w,h;
if (!MainForm->Pattern->GetPageSize(w,h))
    {
    w=hsize;
    h=vsize;
    }
Cont->SetParam(minl,maxl,FMinX,FMaxX);
Cont->SetSize((double)w*wdpi*ms/2540,(double)h*wdpi*ms/2540);
Cont->PrepareUpdating();
FOutMan->SetDefaults(FDrawMan);
FOutMan->FillCont(Cont);

for (int i=0;i<=MainForm->Pattern->MaxSection;i++)
    {
    MainForm->Pattern->Section=i;
    PreparePattern(minl/100,maxl/100,page);
    MainForm->Pattern->DrawTo(FOutMan,Cont,(double)wdpi*ms/25400,0,0,FPlanKind,FPlanDirect,FCurPage);
    if (MainForm->Pattern->GetPlanCenter(cx,cy))
        {
        cx=(cx*wdpi*ms)/25400;
        cy=(cy*wdpi*ms)/25400;
        RECT OutRect;
        if (FPlanKind==pkGorizontal)
           {
           OutRect.left=cx-lpix/2;
           OutRect.right=cx+lpix/2;
           OutRect.top=cy-xpix/2;
           OutRect.bottom=cy+xpix/2;
           }
        else
           {
           OutRect.left=cx-xpix/2;
           OutRect.right=cx+xpix/2;
           OutRect.top=cy-lpix/2;
           OutRect.bottom=cy+lpix/2;
           }
        DrawMainPlan(FOutMan,Cont,scll,sclx,(double)wdpi*ms/254,(TRect*)&OutRect);
        }
    DrawFrames(FOutMan,Cont,(wdpi*ms)/100);
    }
Cont->FinishUpdating();
}


void __fastcall TRoadFrm::Print(int minl,int maxl,int plen,int scll,int sclx,int page)
{
if (Printer()==NULL)
    return;
TPrintContents *prncont=new TPrintContents;
for (;minl<maxl;minl+=plen)
    {
    void *dc=Printer()->Handle;
    int hsize=GetDeviceCaps(dc,HORZRES);
    int vsize=GetDeviceCaps(dc,VERTRES);
    int hofs=GetDeviceCaps(dc,PHYSICALOFFSETX);
    int vofs=GetDeviceCaps(dc,PHYSICALOFFSETY);
    int pdpi=GetDeviceCaps(dc,LOGPIXELSX);


    int lpix=(double)((plen/scll)*pdpi)/2.54;
    int xpix=(double)(((FMaxX-FMinX)/sclx)*pdpi)/2.54;
    int hpix,vpix;
    if (FPlanKind==pkGorizontal)
        hpix=lpix,vpix=xpix;
    else
        hpix=xpix,vpix=lpix;
    int cx=hsize/2;
    int cy=vsize/2;
    if (MainForm->Pattern->GetPlanCenter(cx,cy))
        {
        cx=(cx*pdpi)/254;
        cy=(cy*pdpi)/254;
        }
    TRect OutRect(cx-hpix/2-hofs,cy-vpix/2-vofs,cx+hpix/2-hofs,cy+vpix/2-vofs);
    prncont->SetParam(minl,minl+plen,FMinX,FMaxX);
    prncont->PrepareUpdating();
    FOutMan->SetDefaults(FDrawMan);
    FOutMan->FillCont(prncont);
    PreparePattern(minl/100,(minl+plen)/100,page);
    page++;

    MainForm->Pattern->DrawTo(FOutMan,prncont,(double)pdpi/254,-hofs,-vofs,FPlanKind,FPlanDirect,FCurPage);
    DrawMainPlan(FOutMan,prncont,scll,sclx,(double)pdpi/2.54,&OutRect);
    DrawFrames(FOutMan,prncont,pdpi);
    prncont->FinishUpdating();
    }
delete prncont;
}

void __fastcall TRoadFrm::MetaExportDialog(void)
{
int minkm=FMinL/100000;
int maxkm=(FMaxL+99999)/100000;
MetaParam->MinKm->Min=minkm;
MetaParam->MinKm->Max=maxkm;
MetaParam->MinKm->Position=FPMinL/100000;
MetaParam->MaxKm->Min=minkm;
MetaParam->MaxKm->Max=maxkm;
MetaParam->MaxKm->Position=(FPMaxL+99999)/100000;
MetaParam->ScaleL->Text=FDrawMan->BaseScaleL;
MetaParam->ScaleLChange(PrnParam->ScaleL);
MetaParam->ScaleX->Text=FDrawMan->BaseScaleP;
if (MetaParam->ShowModal()==mrOk)
    {
    int skm=MetaParam->MinKm->Position*100000;
    int ekm=MetaParam->MaxKm->Position*100000;
    int plen=MetaParam->PLen->Position*100000;
    int lms=MetaParam->ScaleL->Text.ToInt();
    int xms=MetaParam->ScaleX->Text.ToInt();
    int dpi=BmpParam->Dpi->Text.ToInt();
    int page=MetaParam->StartPage->Position;
    MetaExport(MetaParam->FileName,skm,ekm,plen,lms,xms,dpi,page);
    }
}

void __fastcall TRoadFrm::MetaExport(String FName,int minl,int maxl,int plen,int scll,int sclx,int dpi,int page)
{
HDC dc=GetDC(0);
int devdpi=GetDeviceCaps(dc,LOGPIXELSX);
ReleaseDC(0,dc);
for (;minl<maxl;minl+=plen,page++)
    {
    TMetaContents *metacont=new TMetaContents(FName+String(page)+String(".emf"));
    MakeBmpPage(metacont,minl,minl+plen,scll,sclx,devdpi,page);
    delete metacont;
    }
}

void __fastcall TRoadFrm::AcadPrint(void){

   TAcadExport *aexp=new TAcadExport();
   int L1=MetricData->Road->LMin;
   int L2=MetricData->Road->LMax;
   int DX=1200;

   TRoad *R=new TRoad(MetricData->Road,L1,L2);
   R->SetBound(L1,L2,-DX,DX);
   R->SetFrame(L1,L2,-DX,DX,pkGorizontal,pdDirect);
   R->SetOutBound(L1,L2,-DX,DX);

   if(!aexp->BindToCurrentDocument(R)){
      ShowMessage("Невозможно начать работу с AutoCAD");
      return;
   }
   aexp->Print();

   delete aexp;
}

void __fastcall TRoadFrm::AcadExport(void) {

   FAutoCADExport->SetRoadId(RoadId);
   FAutoCADExport->RoadName = FRoadName;
   if(FAutoCADExport->ShowModal()!=mrOk) return;

   if(!fBreakedLines && MessageDlg("Разорвать кромку бровки по примыканиям?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
        this->BreakRoadLines();
        fBreakedLines = true;
   }

   AcadExportThread *thread = new AcadExportThread(true);

   ProgressForm->windowBelow = this->Handle;
   thread->FAutoCADExport = FAutoCADExport;
   thread->ProgressForm = ProgressForm;
   thread->MetricData = MetricData;
   thread->Dict = Dict;
   thread->ProfilData = ProfilData;
   thread->CurveData = CurveData;
   if(!FDistrictName.IsEmpty()) {
        thread->RoadName = FRoadName+" ("+FDistrictName+")";
   } else {
        thread->RoadName = FRoadName;
   }

   thread->Resume();

}

void __fastcall TRoadFrm::BmpExportDialog(void)
{
int minkm=FMinL/100000;
int maxkm=(FMaxL+99999)/100000;
BmpParam->MinKm->Min=minkm;
BmpParam->MinKm->Max=maxkm;
BmpParam->MinKm->Position=FPMinL/100000;
BmpParam->MaxKm->Min=minkm;
BmpParam->MaxKm->Max=maxkm;
BmpParam->MaxKm->Position=(FPMaxL+99999)/100000;
BmpParam->ScaleL->Text=FDrawMan->BaseScaleL;
BmpParam->ScaleLChange(PrnParam->ScaleL);
BmpParam->ScaleX->Text=FDrawMan->BaseScaleP;
if (BmpParam->ShowModal()==mrOk)
    {
    int skm=BmpParam->MinKm->Position*100000;
    int ekm=BmpParam->MaxKm->Position*100000;
    int plen=BmpParam->PLen->Position*100000;
    int lms=BmpParam->ScaleL->Text.ToInt();
    int xms=BmpParam->ScaleX->Text.ToInt();
    int dpi=BmpParam->Dpi->Text.ToInt();
    int page=BmpParam->StartPage->Position;
    BmpExport(BmpParam->FileName,skm,ekm,plen,lms,xms,dpi,page);
    }
}

void __fastcall TRoadFrm::BmpExport(String FName,int minl,int maxl,int plen,int scll,int sclx,int dpi,int page)
{
TDrawBitmap *bitcont=new TDrawBitmap;
for (;minl<maxl;minl+=plen,page++)
    {
    MakeBmpPage(bitcont,minl,minl+plen,scll,sclx,dpi,page);
    if (!bitcont->Bitmap)
        {
        ShowMessage("Создание изображения по заданные параметрам требует слишком большого объема памяти");
        break;
        }
    Graphics::TBitmap *bmp=new Graphics::TBitmap;
    bmp->Handle=bitcont->Bitmap;
    bmp->SaveToFile(FName+String(page)+String(".bmp"));
    bmp->Handle=NULL;
    delete bmp;
    }
delete bitcont;
}



void __fastcall TRoadFrm::AlignPanels(void)
{
TAlign al;
if (FPlanKind==pkGorizontal)
    al=alTop;
else
    al=alLeft;

RulPanel->Parent=NULL;
VRulPanel->Parent=NULL;

if (FPlanKind==pkGorizontal)
    {
    Splitter1->Parent=CPanel;
    RulPanel->Parent=CPanel;
    Splitter4->Parent=PlanPan;
    VRulPanel->Parent=PlanPan;
    VScroll->Parent=PlanPan;
    HScroll->Parent=this;
    }
else
    {
    Splitter4->Parent=CPanel;
    VRulPanel->Parent=CPanel;
    Splitter1->Parent=PlanPan;
    RulPanel->Parent=PlanPan;
    VScroll->Parent=this;
    HScroll->Parent=PlanPan;
    }

Splitter2->Parent=NULL;
Splitter3->Parent=NULL;
Splitter5->Parent=NULL;

VisPan->Align=al;
ProPan->Align=al;
VisModePan->Align=al;

Splitter2->Align=al;
Splitter3->Align=al;
Splitter5->Align=al;

if (FPlanKind==pkGorizontal)
    {
    Splitter2->Height=6;
    Splitter3->Height=6;
    Splitter5->Height=6;
    }
else
    {
    Splitter2->Width=6;
    Splitter3->Width=6;
    Splitter5->Width=6;
    }
ShowPanels();
InvalidateBoxes();
}

void __fastcall TRoadFrm::ShowPanels(void)
{
TWinControl *VParent=VisPan->Parent;
TWinControl *PParent=ProPan->Parent;
TWinControl *QParent=VisModePan->Parent;

ProPan->Parent=NULL;
VisPan->Parent=NULL;
VisModePan->Parent=NULL;
Splitter2->Parent=NULL;
Splitter3->Parent=NULL;
Splitter5->Parent=NULL;


if (FPan1Vis)
    Splitter2->Parent=VParent;
Splitter2->Visible=FPan1Vis;

VisPan->Parent=VParent;
VisPan->Visible=FPan1Vis;

if (FPan2Vis)
    Splitter3->Parent=PParent;
Splitter3->Visible=FPan2Vis;
ProPan->Parent=PParent;
ProPan->Visible=FPan2Vis;

if (FPan4Vis)
   Splitter5->Parent=QParent;
Splitter5->Visible=FPan4Vis;
VisModePan->Parent=QParent;
VisModePan->Visible=FPan4Vis;

N11->Checked=FPan1Vis;
N21->Checked=FPan2Vis;
N10->Checked=FPan4Vis;
MainForm->N50->Checked=FPan2Vis;
MainForm->N74->Checked=FPan1Vis;
MainForm->N75->Checked=FPan4Vis;
}

//---------------------------------------------------------------------------
void __fastcall TRoadFrm::FormActivate(TObject *Sender)
{
MainForm->ActiveRoad=this;
}

//---------------------------------------------------------------------------
void __fastcall TRoadFrm::CalculateGridPos(bool CanMove)
{
FMinCanMove=FMaxCanMove=false;
if (FActiveObj)
    {
    TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject*>(FActiveObj);
    TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(FActiveObj);
    if (dobj)
        {
        int PY;
        if (FPlanKind==pkGorizontal)
            {
            FDrawMan->Road->ConvertPoint(dobj->L,0,FGridMinX,PY);
            FGridMaxX=PBox->Width*2;
            }
        else
            {
            FDrawMan->Road->ConvertPoint(dobj->L,0,PY,FGridMinX);
            FGridMaxX=PBox->Height*2;
            }
        FMinCanMove=CanMove;
        }
    else if (cobj)
        {
        int PY1;
        int PY2;
        int lmin=cobj->LMin;
        if (lmin<FVMinL)
            lmin=FVMinL;
        else
            FMinCanMove=CanMove;
        int lmax=cobj->LMax;
        if (lmax>FVMaxL)
            lmax=FVMaxL;
        else
            FMaxCanMove=CanMove;
        if (FPlanKind==pkGorizontal)
            {
            FDrawMan->Road->ConvertPoint(lmin,0,FGridMinX,PY1);
            FDrawMan->Road->ConvertPoint(lmax,0,FGridMaxX,PY2);
            }
        else
            {
            FDrawMan->Road->ConvertPoint(lmin,0,PY1,FGridMinX);
            FDrawMan->Road->ConvertPoint(lmax,0,PY2,FGridMaxX);
            }
        }
    }
if (FEditMetric)
    FMinCanMove=FMaxCanMove=false;
}

void __fastcall TRoadFrm::DrawMarkerPart(void)
{
if (FPartVisible)
    {
    FPartPainted=!FPartPainted;
    PBox->Canvas->Pen->Style=psDot;
    PBox->Canvas->Pen->Mode=pmXor;
    PBox->Canvas->Pen->Color=clRed;
    int X1,X2,Y1,Y2;
    FDrawMan->Road->ConvertPoint(FPartMinL,0,X1,Y1);
    FDrawMan->Road->ConvertPoint(FPartMaxL,0,X2,Y2);
    if (FPlanKind==pkGorizontal)
        {
        PBox->Canvas->MoveTo(X1,0);
        PBox->Canvas->LineTo(X1,PBox->Height);
        if (X1!=X2)
            {
            PBox->Canvas->MoveTo(X2,0);
            PBox->Canvas->LineTo(X2,PBox->Height);
            }
        }
    else
        {
        PBox->Canvas->MoveTo(0,Y1);
        PBox->Canvas->LineTo(PBox->Width,Y1);
        if (Y1!=Y2)
            {
            PBox->Canvas->MoveTo(0,Y2);
            PBox->Canvas->LineTo(PBox->Width,Y2);
            }
        }
    }
}

void __fastcall TRoadFrm::ClearMarkerPart(void)
{
if (FPartPainted)
    DrawMarkerPart();
}

void __fastcall TRoadFrm::DrawGrid(void)
{
if (FActiveObj)
    {
    FGridVisible=!FGridVisible;
    PBox->Canvas->Pen->Style=psDot;
    PBox->Canvas->Pen->Mode=pmXor;
    PBox->Canvas->Pen->Color=clYellow;
    if (FPlanKind==pkGorizontal)
        {
        PBox->Canvas->MoveTo(FGridMinX,0);
        PBox->Canvas->LineTo(FGridMinX,PBox->Height);
        if (FGridMaxX!=FGridMinX)
            {
            PBox->Canvas->MoveTo(FGridMaxX,0);
            PBox->Canvas->LineTo(FGridMaxX,PBox->Height);
            }
        }
    else
        {
        PBox->Canvas->MoveTo(0,FGridMinX);
        PBox->Canvas->LineTo(PBox->Width,FGridMinX);
        if (FGridMaxX!=FGridMinX)
            {
            PBox->Canvas->MoveTo(0,FGridMaxX);
            PBox->Canvas->LineTo(PBox->Width,FGridMaxX);
            }
        }
    PBox->Canvas->Pen->Mode=pmCopy;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRoadFrm::ClearGrid(void)
{
if (FGridVisible)
    {
    DrawGrid();
    }
}
//---------------------------------------------------------------------------
void __fastcall TRoadFrm::SetViewPosition(__int32 minl,__int32 maxl)
{
FPMinL=minl;
FPMaxL=maxl;
SetMarkerPos((FPMinL+FPMaxL)>>1);
ScaleL(1);
}

void __fastcall TRoadFrm::SetBaseScale(__int32 l,__int32 x,__int32 p)
{
FDrawMan->BaseScaleL=l;
FDrawMan->BaseScaleX=x;
FDrawMan->BaseScaleP=p;
}

void __fastcall TRoadFrm::ShowRoadPart(__int32 min,__int32 max)
{
int pix;
if (FPlanKind==pkGorizontal)
    pix=PBox->Width;
else
    pix=PBox->Height;
pix-=2*HIDEBOUND;
double ms=double(max-min)*FDpsm/(double)pix;
int move=(double)HIDEBOUND/FDpsm*ms;
FPMinL=min-move;
FPMaxL=max+move;
SetMarkerPos((FPMinL+FPMaxL)>>1);
ScaleL(1);
}

//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SetObjectActive(TRoadObject *Obj,TDtaSource *Src)
{
if (Obj)
    {
    FActiveObj=Obj;
    FActiveSource=Src;
    MainForm->SendBroadCastMessage(CM_ONACTIVATEOBJECT,(int)FActiveObj,(int)Src);
    PostActivateObj();
    PostAction();
    }
}

void __fastcall TRoadFrm::ActivateObject(TRoadObject *Obj,TDtaSource *Src)
{
if (Obj)
    {
    FActiveObj=Obj;
    FActiveSource=Src;
    TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject*>(FActiveObj);
    TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(FActiveObj);
    int L1,L2;
    if (dobj)
        L1=L2=dobj->L;
    else if (cobj)
        L1=cobj->LMin,L2=cobj->LMax;
    int pix;
    if (FPlanKind==pkGorizontal)
        pix=PBox->Width;
    else
        pix=PBox->Height;
    pix-=2*HIDEBOUND;
    int StdL=(pix/FDpsm)*FDrawMan->BaseScaleL;
    int StL=(pix/FDpsm)*FSclL;
    if ((L2-L1>StdL)||(L2-L1>StL)) // Масштабируем по размеру
        ShowRoadPart(L1,L2);
    else if (StL<StdL)  // Сохраняем текущий масштаб
        ShowRoadPart((L1+L2-StL)>>1,(L1+L2+StL)>>1);
    else
        ShowRoadPart((L1+L2-StdL)>>1,(L1+L2+StdL)>>1);
    ScaleL(1);
    MainForm->SendBroadCastMessage(CM_ONACTIVATEOBJECT,(int)FActiveObj,(int)Src);
    }
PostActivateObj();
PostAction();
}

void __fastcall TRoadFrm::UpdateLocalInfo(void)
{
TResManager *ResManager=MainForm->ResManager;
for (int i=0;i<ResManager->DataCount;i++)
    {
    TDtaSource *Dta=ResManager->Data[i];
    if (Dta->Id==RoadId)
        {
        for (int j=0;j<Dta->Objects->Count;j++)
            {
            TRoadObject *Obj=Dta->Objects->Items[j];
            Obj->DrwClassId=Dict->SelectDrwParam(Obj,FCurPage);
            }
        }
    }
}

void __fastcall TRoadFrm::RefreshPlan(void)
{
TResManager *ResManager=MainForm->ResManager;
for (int i=0;i<ResManager->DataCount;i++)
    {
    TDtaSource *Dta=ResManager->Data[i];
    if (Dta->Id==RoadId)
        Dta->SortByPlacement();
    }
FMetricData->BuildRoadMetrics();
for (int i=0;i<ResManager->DataCount;i++)
    {
    TDtaSource *Dta=ResManager->Data[i];
    if (Dta->Id==RoadId)
        Dta->CalcMetrics(FMetricData->Road);
    }
UpdateLocalInfo();
InvalidateBoxes();
}

void __fastcall TRoadFrm::UpdateActiveObject(bool leep)
{
if (FActiveObj)
    {
    TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject*>(FActiveObj);
    TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(FActiveObj);
    int DL=FDrawMan->BaseScaleL/20; // точки хватаются в пределах 0.5 мм.
    if (dobj)
        {
        __int32 L,X;
        if (FPlanKind==pkGorizontal)
            FDrawMan->Road->RConvertPoint(FGridMinX,0,L,X);
        else
            FDrawMan->Road->RConvertPoint(0,FGridMinX,L,X);
        if (leep)
            {
            TRoadObject *fobj=FDrawMan->FindNearestL(L,dobj,DL);
            TRoadSign *sobj=dynamic_cast<TRoadSign*>(fobj);
            TRoadSign *aobj=dynamic_cast<TRoadSign*>(FActiveObj);
            if (sobj&&aobj)
                if (sobj->Direction==aobj->Direction)
                    aobj->DX=sobj->DX;
             }
        dobj->L=L;
        MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)dobj,(int)FActiveSource);
        }
    else if (cobj)
        {
        __int32 L,X;
        if (FPlanKind==pkGorizontal)
            {
            if (FMinMov)
                FDrawMan->Road->RConvertPoint(FGridMinX,0,L,X);
            else
                FDrawMan->Road->RConvertPoint(FGridMaxX,0,L,X);
            }
        else
            {
            if (FMinMov)
                FDrawMan->Road->RConvertPoint(0,FGridMinX,L,X);
            else
                FDrawMan->Road->RConvertPoint(0,FGridMaxX,L,X);
            }
        if (leep)
            FDrawMan->FindNearestL(L,dobj,DL);
        if (FMinMov)
            {
            if (L<cobj->LMax)
                cobj->PutPosition(L,cobj->LMax);
            else
                cobj->PutPosition(cobj->LMax,L);
            }
        else
            {
            if (L>cobj->LMin)
                cobj->PutPosition(cobj->LMin,L);
            else
                cobj->PutPosition(L,cobj->LMin);
            }
        MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)cobj,(int)FActiveSource);
        }
    if ((FActiveObj->Poly)&&(FMetricData))
        FMetricData->Road->CalcPointsPos(FActiveObj->Poly,FActiveObj);
    FActiveSource->SortByPlacement();
    }
}
void __fastcall TRoadFrm::BuildPopMenu(void)
{
while (PopMenu->Items->Count)
  delete PopMenu->Items->Items[0];
for (int i=0;i<SelCount;i++)
   {
   TMenuItem* it=new TMenuItem(PopMenu);
   it->Tag=i;
   it->Caption=FDictSour->ObjClasses->Items[SelObjs[i]->DictId]->Title;
   it->OnClick=ShowMenu;
   PopMenu->Items->Add(it);
   }
}

void __fastcall TRoadFrm::ShowPopMenu(void)
{
POINT p;
GetCursorPos(&p);
int scrx;
scrx=GetDeviceCaps(Canvas->Handle,HORZRES);
HavePopup=true;;
if (p.x<scrx/2)
      {
      p.x=p.x+30;
      TrackPopupMenu(PopMenu->Items->Handle,TPM_RIGHTBUTTON|TPM_LEFTALIGN,p.x,p.y, 0 , Handle, NULL);
      }
else
     {
     p.x=p.x-30;
     TrackPopupMenu(PopMenu->Items->Handle,TPM_RIGHTBUTTON|TPM_RIGHTALIGN ,p.x,p.y, 0 , Handle, NULL);
     }
HavePopup=false;
}

void __fastcall TRoadFrm::ShowMenu(TObject *Send)
{
TMenuItem* it=(TMenuItem*)Send;
if (it)
    {
    FActiveObj=SelObjs[it->Tag];
    FActiveSource=SelSrc[it->Tag];
    }
else
    {
    FActiveObj=SelObjs[0];
    FActiveSource=SelSrc[0];
    }
CalculateGridPos(false);
DrawGrid();
if (FActiveObj)
    {
    if (MainForm->PropertyByClick)
        {
        TObjFrm *Frm;
        Application->CreateForm(__classid(TObjFrm), &Frm);
        Frm->BuildForm(FDictSour,FActiveSource,FActiveObj);
        Frm->Show();
        }
    if (MainForm->SelectByClick)
        {
        FActiveObj->Selected=true;
        MainForm->SendBroadCastMessage(CM_CHANGESEL,(int)FActiveObj,(int)FActiveSource);
        }
    MainForm->SendBroadCastMessage(CM_ONACTIVATEOBJECT,(int)FActiveObj,(int)FActiveSource);
    }
PostActivateObj();
}

void __fastcall TRoadFrm::InvalidateBoxes(void)
{
FVMinL=FPMinL+(double)HIDEBOUND*FSclL/FDpsm;
FVMaxL=FPMaxL-(double)HIDEBOUND*FSclL/FDpsm;
NeedRepDraw=NeedRepDress=NeedRepSlopes=NeedRepVis=true;
if ((FVMinL<FVMaxL)&&(FMinX<FMaxX))
    {
    PrepareDrawCont();
    PrepareSlopesCont();
    PrepareVisCont();
    }
PBox->Invalidate();
PrBox->Invalidate();
PvBox->Invalidate();
PvisBox->Invalidate();
}

void __fastcall TRoadFrm::DrawFocusRect(void)
{
TRect r;
if (CRectPos.x<SRectPos.x)
    {
    r.Left=CRectPos.x;
    r.Right=SRectPos.x;
    }
else
    {
    r.Left=SRectPos.x;
    r.Right=CRectPos.x;
    }
if (CRectPos.y<SRectPos.y)
    {
    r.Top=CRectPos.y;
    r.Bottom=SRectPos.y;
    }
else
    {
    r.Top=SRectPos.y;
    r.Bottom=CRectPos.y;
    }
PBox->Canvas->DrawFocusRect(r);
}

TExtPolyline* __fastcall TRoadFrm::BuildPoly(bool re)
{
if (!re && FVector!=0 && FPoly!=0) {
      int n=FPoly->Count<FVector->Count?FPoly->Count:FVector->Count;
      FDrawMan->Road->ConvertPoly(n,FPoly->Points,FVector->Points);

} else {
   delete FVector;
   FVector=NULL;
   if (FPoly)
       {
       int n=FPoly->Count;
       FVector=new TExtPolyline(n);
       FDrawMan->Road->ConvertPoly(n,FPoly->Points,FVector->Points);
       for (int i=0;i<n;i++)
           {
           FVector->Codes[i]=FPoly->Points[i].Code.VisCon();
           FVector->Flags[i]=0;
           }
       FActivePoint=-1;
       }
   }
   if (FVector==0 && FEditMetric)
      StopEditPoly();
return FVector;
}

#define RECTSIZE 3
#define ARECTSIZE 4

void __fastcall TRoadFrm::DrawPoly(void)
{
if ((FVector)&&(FPoly))
    {
    int n=FPoly->Count;
    void *dc=PBox->Canvas->Handle;
    void *pen1=CreatePen(PS_SOLID,2,clBlue);
    void *pen2=CreatePen(PS_DOT,1,clBlue);
    FVector->DrawPoly(dc,pen1,pen2);
    SelectObject(dc,pen1);
    POINT *p=FVector->Points;
    for (int i=0;i<n;i++)
        if (FVector->Flags[i]&1)
            {
            Rectangle(dc,p[i].x-ARECTSIZE,p[i].y-ARECTSIZE,p[i].x+ARECTSIZE,p[i].y+ARECTSIZE);
            }
        else
            Rectangle(dc,p[i].x-RECTSIZE,p[i].y-RECTSIZE,p[i].x+RECTSIZE,p[i].y+RECTSIZE);
    SelectObject(dc,GetStockObject(BLACK_PEN));
    DeleteObject(pen1);
    DeleteObject(pen2);
    }
}

int __fastcall TRoadFrm::FindActivePoint(int X,int Y)
{
int fp=-1;
if ((FVector)&&(FPoly))
    {
    double MaxLen=RECTSIZE+1;
    int mlen=MaxLen;
    int n=FPoly->Count;
    POINT *p=FVector->Points;
    if (FActivePoint>=0)
        {
        int dx=p[FActivePoint].x-X;
        int dy=p[FActivePoint].y-Y;
        if ((abs(dx)<mlen)&&(abs(dy)<mlen))
            return FActivePoint;
        }
    for (int i=0;i<n;i++)
        {
        int dx=p[i].x-X;
        int dy=p[i].y-Y;
        if ((abs(dx)<mlen)&&(abs(dy)<mlen))
            {
            double d=sqrt(dx*dx+dy*dy);
            if (d<MaxLen)
                MaxLen=d,fp=i;
            }
        }
    }
return fp;
}

void __fastcall TRoadFrm::DeleteActivePoint(void)
{
if (FPoly)
    if (FActivePoint>=0)
        {
        FPoly->DeletePoint(FActivePoint);
        BuildPoly(true);
        PolyFrm->UpdatePoly(FVector);
        PBox->Invalidate();
        }
}

void __fastcall TRoadFrm::SetActivePointCode(int Kind,int Code)
{
if (FEditMetric)
    if (FPoly)
        if (FActivePoint>=0)
            {
            switch (Kind)
                {
                case 0:(*FPoly)[FActivePoint].Code.SetVisible(Code);break;
                case 1:(*FPoly)[FActivePoint].Code.SetConnection(Code);break;
                case 2:(*FPoly)[FActivePoint].Code.SetLeep(Code);break;
                }
            FMetricData->Road->CalcPointPos(FPoly,FActivePoint,FActiveObj);
            int X,Y;
            FDrawMan->Road->ConvertPoint((*FPoly)[FActivePoint].L,(*FPoly)[FActivePoint].X,X,Y);
            (*FVector)[FActivePoint].x=X;
            (*FVector)[FActivePoint].y=Y;
            FVector->Codes[FActivePoint]=(*FPoly)[FActivePoint].Code.VisCon();
            PBox->Invalidate();
            }
}

void __fastcall TRoadFrm::SetPoint(TRoadPoint P,int index)
{
(*FPoly)[index]=P;
int ind1,ind2;
FMetricData->Road->SetPointPos(FPoly,index,FActiveObj,ind1,ind2);
bool contin;
do
    {
    contin=ind1!=ind2;
    __int32 CX,CY;
    FMetricData->Road->ConvertPoint((*FPoly)[ind1].L,(*FPoly)[ind1].X,CX,CY);
    (*FVector)[ind1].x=CX;
    (*FVector)[ind1].y=CY;
    FVector->Codes[ind1]=(*FPoly)[ind1].Code.VisCon();
    ind1=(ind1+1)%FPoly->Count;
    }
while (contin);
}

void __fastcall TRoadFrm::InsertPoint(TRoadPoint P,int index)
{
FPoly->InsertPoint(P,index);
int ind1,ind2;
FMetricData->Road->SetPointPos(FPoly,index,FActiveObj,ind1,ind2);
BuildPoly(true);
PolyFrm->UpdatePoly(FVector);
PBox->Invalidate();
}

void __fastcall TRoadFrm::InsertPoint(void)
{
if (FPoly)
    if ((FActivePoint>=0)||(FPoly->Count==0))
        {
        TRoadPoint pt;
        pt.Code=1;
        if (FActivePoint<FPoly->Count-1)  // После точки есть еще одна
            {
            pt.L=((*FPoly)[FActivePoint].L+(*FPoly)[FActivePoint+1].L)/2;
            pt.X=((*FPoly)[FActivePoint].X+(*FPoly)[FActivePoint+1].X)/2;
            }
        else if ((FActivePoint==FPoly->Count-1)&&(FPoly->Count>0))
            {
            int DL=FSclL;
            int DX=0;
            if (FPoly->Count>1)
                {
                DL=((*FPoly)[FActivePoint].L-(*FPoly)[FActivePoint-1].L)/2;
                DX=((*FPoly)[FActivePoint].X-(*FPoly)[FActivePoint-1].X)/2;
                }
            pt.L=(*FPoly)[FActivePoint].L+DL;
            pt.X=(*FPoly)[FActivePoint].X+DX;
            }
        else
            {
            pt.L=(FVMinL+FVMaxL)/2;
            pt.X=0;
            }
        InsertPoint(pt,FActivePoint+1);
        }
}

void __fastcall TRoadFrm::StartEditPoly(void)
{
if (FActiveObj)
    {
    if (FActiveObj->Poly)
        {
        FPoly=FActiveObj->Poly;
        }
    else
        {
        FPoly=new TPolyline(0,0);
        FActiveObj->Poly=FPoly;
        FActiveSource->PolyList->Add(FPoly);
        }
    FEditMetric=true;
    BuildPoly(true);
    PolyFrm->ShowForm(this,FMetricData->Road,FPoly,FVector,FActiveObj);
    }
}

void __fastcall TRoadFrm::StopEditPoly(void)
{
FPoly=NULL;
FEditMetric=false;
if (FActiveObj)
    FActiveObj->PostEditPoly();
InvalidateBoxes();
PolyFrm->Hide();
}


void __fastcall TRoadFrm::PrepareDressCont(void)
{
if (NeedRepDress)
    {
    int w,h;
    if (FPlanKind==pkGorizontal)
      w=PBox->Width,h=PvBox->Height;
    else
      w=PvBox->Width,h=PBox->Height;

    FDressCont->SetSize(w,h);
    FDressCont->SetParam(FVMinL,FVMaxL,FPMinX,FPMaxX);
    FDressCont->PrepareUpdating();
    FDrawMan->FillCont(FDressCont);
    TRect r(0,0,w,h);
    if (FPlanKind==pkGorizontal)
        {
        r.left+=HIDEBOUND;
        r.right-=HIDEBOUND;
        }
    else
        {
        r.top+=HIDEBOUND;
        r.bottom-=HIDEBOUND;
        }
    FDrawMan->DrawCurvesPlan(FDressCont,&r,FPlanKind,FPlanDirect);
//    FDrawMan->DrawRazrez(FDressCont,&r,(FVMinL+FVMaxL)>>1);
    FDressCont->FinishUpdating();
    NeedRepDress=false;
    }
}

void __fastcall TRoadFrm::PrepareSlopesCont(void)
{
if (NeedRepSlopes&&FReadyForDrawing)
    {
    int w,h;
    if (FPlanKind==pkGorizontal)
      w=PBox->Width,h=PrBox->Height;
    else
      w=PrBox->Width,h=PBox->Height;

    FSlopesCont->SetSize(w,h);
    FSlopesCont->SetParam(FVMinL,FVMaxL,FPMinX,FPMaxX);
    FSlopesCont->PrepareUpdating();
    FDrawMan->FillCont(FSlopesCont);
    TRect r(0,0,w,h);
    if (FPlanKind==pkGorizontal)
        {
        r.left+=HIDEBOUND;
        r.right-=HIDEBOUND;
        }
    else
        {
        r.top+=HIDEBOUND;
        r.bottom-=HIDEBOUND;
        }
    FDrawMan->DrawProfil(FSlopesCont,&r,FPlanKind,FPlanDirect);
    FSlopesCont->FinishUpdating();
    NeedRepSlopes=false;
    }
}

void __fastcall TRoadFrm::PrepareVisCont(void) {
if (NeedRepVis&&FReadyForDrawing) {
    int w,h;
    if (FPlanKind==pkGorizontal)
      w=PBox->Width,h=PvisBox->Height;
    else
      w=PvisBox->Width,h=PBox->Height;
    FVisCont->SetSize(w,h);
    FVisCont->SetParam(FVMinL,FVMaxL,FPMinX,FPMaxX);
    FVisCont->PrepareUpdating();
    FDrawMan->FillCont(FVisCont);
    TRect r(0,0,w,h);
    if (FPlanKind==pkGorizontal)
        {
        r.left+=HIDEBOUND;
        r.right-=HIDEBOUND;
        }
    else
        {
        r.top+=HIDEBOUND;
        r.bottom-=HIDEBOUND;
        }
    FDrawMan->DrawVisibleMode(FVisCont,&r,FPlanKind,FPlanDirect);
    FVisCont->FinishUpdating();
    NeedRepVis=false;
}
}

void __fastcall TRoadFrm::DrawMainPlan(TDrawManager* Man,TDrawContents *Cont,double scll,double sclx,double dpsm,TRect *r)
{
if (FReadyForDrawing)
    {
    bool mask[MAXCODEID];
    for (int i=0;i<MAXCODEID;i++)
        mask[i]=true;
    mask[DANGERSLOPECODE]=false;
    mask[DANGERCURVECODE]=false;
    mask[ROADDRESSCODE]=false;
    mask[VISMODECODE]=false;
    Man->DrawByCodes(MAXCODEID,mask,Cont,scll,sclx,dpsm,r,FPlanKind,FPlanDirect);
    }
}

void __fastcall TRoadFrm::PrepareDrawCont(void)
{
if (NeedRepDraw&&FReadyForDrawing)
    {
    FDrawCont->SetSize(PBox->Width,PBox->Height);
    FDrawCont->SetParam(FVMinL,FVMaxL,FPMinX,FPMaxX);
    RECT r;
    r.left=0;
    r.top=0;
    r.right=PBox->Width;
    r.bottom=PBox->Height;
    if (FPlanKind==pkGorizontal)
        {
        r.left+=HIDEBOUND;
        r.right-=HIDEBOUND;
        }
    else
        {
        r.top+=HIDEBOUND;
        r.bottom-=HIDEBOUND;
        }
    FDrawCont->PrepareUpdating();
    FDrawMan->FillCont(FDrawCont);

    DrawMainPlan(FDrawMan,FDrawCont,FSclL,FSclX,FDpsm,(TRect*)&r);
    FDrawCont->FinishUpdating();
    if (FEditMetric) {
        BuildPoly(false);
    }
    NeedRepDraw=false;
    }
}

void __fastcall TRoadFrm::SynchronizeVideo(void)
{
if (frmVideoForm->Visible)
    if (frmVideoForm->NumRoad==FVideoData->Id)
        if (frmVideoForm->Status!=2)
            {
            int sign=frmVideoForm->Direction==1? 1: -1;
            frmVideoForm->Position=FMarkerL+sign*FrmSetting->VideoOffset*100;
            }
}

void __fastcall TRoadFrm::SetMarkerPos(__int32 newl)
{
FMarkerL=newl;
if (FMarkerL<FMetricData->Road->LMin)
    FMarkerL=FMetricData->Road->LMin;
else if (FMarkerL>FMetricData->Road->LMax)
    FMarkerL=FMetricData->Road->LMax;
SynchronizeVideo();
PBox->Invalidate();
}

void __fastcall TRoadFrm::DrawMarker(TPaintBox *pb,int dl)
{
int x,y;
FDrawMan->Road->ConvertPoint(FMarkerL,0,x,y);
pb->Canvas->Pen->Style=psDot;
pb->Canvas->Pen->Color=clYellow;
if (FPlanKind==pkGorizontal)
    {
    pb->Canvas->MoveTo(x+dl,0);
    pb->Canvas->LineTo(x+dl,pb->Height-1);
    }
else
    {
    pb->Canvas->MoveTo(0,y+dl);
    pb->Canvas->LineTo(pb->Width-1,y+dl);
    }
}

void __fastcall TRoadFrm::PaintRoad(TObject *Sender)
{
PrepareDrawCont();

                           //  Отображаем картинку из памяти на экран
FDrawCont->DrawTo(PBox->Canvas,0,0);
                           //  Рамка выделения теперь отсутствует
SelectRect->NewPicture();
SelectObj->NewPicture();
FDrawMan->DrawSelected(PBox->Canvas->Handle);
                           //  Отображаем желтую линию маркера позиции
DrawMarker(PBox,0);

                            //
FGridVisible=false;
FPartPainted=false;
CalculateGridPos(FMinCanMove||FMaxCanMove);
DrawGrid();
DrawMarkerPart();
CPVisible=false;  // Точка не видна
if (FPlanKind==pkGorizontal)
    {
    TPoint P;
    P.x=P.y=0;
    TPoint Q=PBox->ClientToScreen(P);
    P=HRuler->ScreenToClient(Q);
    int PX1,PY1;
    FDrawMan->Road->ConvertPoint(FPMinL,0,PX1,PY1);
    int PX2,PY2;
    FDrawMan->Road->ConvertPoint(FPMaxL,0,PX2,PY2);
    bool dir=FPlanDirect==pdDirect;
    if (dir)
            HRuler->SetMinMax(dir,(double)(FPMinL-FRelativeNull)/100,(double)(FPMaxL-FRelativeNull)/100,P.x+PX1,PX2-PX1);
    else
            HRuler->SetMinMax(dir,(double)(FPMinL-FRelativeNull)/100,(double)(FPMaxL-FRelativeNull)/100,HRuler->Width-P.x-PX1,PX1-PX2);
    VRuler->SetMinMax(dir,(double)FPMinX/100,(double)FPMaxX/100,0,PBox->Height);
    }
else
    {
    TPoint P;
    P.x=P.y=0;
    TPoint Q=PBox->ClientToScreen(P);
    P=HRuler->ScreenToClient(Q);
    int PX1,PY1;
    FDrawMan->Road->ConvertPoint((int)(FPMinL/100)*100,0,PX1,PY1);
    int PX2,PY2;
    FDrawMan->Road->ConvertPoint((int)(FPMaxL/100)*100,0,PX2,PY2);
    bool dir=FPlanDirect==pdDirect;
    if (dir)
        VRuler->SetMinMax(!dir,(double)(FPMinL-FRelativeNull)/100,(double)(FPMaxL-FRelativeNull)/100,VRuler->Height-PY1-P.y,PY1-PY2);
    else
        VRuler->SetMinMax(!dir,(double)(FPMinL-FRelativeNull)/100,(double)(FPMaxL-FRelativeNull)/100,P.y+PY1,PY2-PY1);
    HRuler->SetMinMax(dir,(double)FPMinX/100,(double)FPMaxX/100,0,PBox->Width);
    }
if (FEditMetric)
    DrawPoly();
PostAction();
}


void __fastcall TRoadFrm::SetXBounds(__int32 boundx,__int32 objx)
{
FMaxX=boundx;
FMinX=-boundx;
if (FPMinX<FMinX)
    FPMinX=FMinX;
if (FPMaxX>FMaxX)
    FPMaxX=FMaxX;
TRoad *R=FMetricData->Road;
FMetricData->SetRoadBound(R->LMin,R->LMax,-objx,objx);
}

void __fastcall TRoadFrm::ShowParam(void)
{
DrwSetFrm->ScaleL=FDrawMan->BaseScaleL;
DrwSetFrm->ScaleX=FDrawMan->BaseScaleX;
DrwSetFrm->ScaleP=FDrawMan->BaseScaleP;
DrwSetFrm->FontSize=FDrawMan->FontSize;
DrwSetFrm->BoundX=FMaxX/100;
DrwSetFrm->DelVis=FDrawMan->DelVis;
DrwSetFrm->ProVis=FDrawMan->ProVis;
DrwSetFrm->ObjX=FMetricData->Road->XMax/100;
DrwSetFrm->KmInPage=FKmInPage;
DrwSetFrm->MetricsSource=FMetricData->MetricsSource;
DrwSetFrm->ProfilKind=FProfilData->ProfilKind;
if (DrwSetFrm->ShowModal()==mrOk)
    {
    FDrawMan->DelVis=DrwSetFrm->DelVis;
    FDrawMan->ProVis=DrwSetFrm->ProVis;
    FDrawMan->BaseScaleL=DrwSetFrm->ScaleL;
    FDrawMan->BaseScaleX=DrwSetFrm->ScaleX;
    FDrawMan->BaseScaleP=DrwSetFrm->ScaleP;
    FDrawMan->FontSize=DrwSetFrm->FontSize;
    FMetricData->MetricsSource=DrwSetFrm->MetricsSource;
    FProfilData->ProfilKind=DrwSetFrm->ProfilKind;
    SetXBounds(DrwSetFrm->BoundX*100,DrwSetFrm->ObjX*100);
    FKmInPage=DrwSetFrm->KmInPage;
    BuildKmSet(FKmInPage);
    RefreshPlan();
    ShowScale();
    SaveRegistry();
    InvalidateBoxes();
    }
}

void __fastcall TRoadFrm::AddNewObject(int DictId)
{
if (FEditedData)
    if (!FEditedData->ReadOnly)
        {
        if ((DictId>=0)&&(DictId<Dict->ObjClasses->Count))
            {
            TObjMetaClass *Meta=(TObjMetaClass*)Dict->ObjClasses->Items[DictId];
            if (Meta)
                AddNewObject(Meta);
            }
    }
}

void __fastcall TRoadFrm::AddNewObject(TObjMetaClass *Meta)
{
if (Meta)
    {
    delete FInsertingObj;
    FInsertingObj=NULL;
    FInsertingObj=MainForm->Factory->CreateRoadObj(Meta->ClassName,0,Meta->Id);
    if (FInsertingObj)
        ZoomStatus=zsWaitPoint;
    }
}

void __fastcall TRoadFrm::AddNewObject(void)
{
if (FEditedData)
    if (!FEditedData->ReadOnly)
        if (AddObjFrm->Execute(Dict))
            if (AddObjFrm->MetaClass)
                AddNewObject(AddObjFrm->MetaClass);
}

void __fastcall TRoadFrm::AddNewSign(String Code,int Variation=0)
{
delete FInsertingObj;
FInsertingObj=NULL;
if (FEditedData)
    if (!FEditedData->ReadOnly)
        {
          TRoadSign *NewSign=FEditedData->CreateManSign(FDictSour,roDirect,spRight,0,0,Code,"","");

           if (NewSign) {
           NewSign->ViewKind=Variation;
           MainForm->SignPanel->AddButton(Dict,Code.Trim());
           FInsertingObj=NewSign;
           ZoomStatus=zsWaitPoint;
           }
        }
}

void __fastcall TRoadFrm::MoveActiveObject(void)
{
CalculateGridPos(true);
}

void __fastcall TRoadFrm::EditActiveMarkParams(void)
{
if (FActiveObj)
    if (FEditedData==FActiveSource)
        {
        TRoadMark *mark=dynamic_cast<TRoadMark*>(FActiveObj);
        if (mark)
            if (frmMarkParam->Execute(Dict,mark))
                {
                mark->DrwClassId=Dict->SelectDrwParam(mark,FCurPage);
                MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)mark,(int)FActiveSource);
                }
        }
}

bool __fastcall TRoadFrm::IsInTown(int L) {
   for (int i=0;i<MainForm->ResManager->DataCount;i++) {
      TDtaSource *d=MainForm->ResManager->Data[i];
      if (d->Id==RoadId) {
         int ind1,ind2;
         int count=d->BinarySearch(0,L,ind1,ind2);
         if (count) {
            for (;ind1<=ind2;ind1++) {
                TTown *T=dynamic_cast<TTown*>(d->Objects->Items[ind1]);
                if (T && T->DictId==TOWNCODE && T->LMax>=L)
                  return true;
            }
         }
      }
   }
   return false;
}

void __fastcall TRoadFrm::ContinueMarkLine(void)
{
if (FActiveObj)
    if (FEditedData==FActiveSource)
        {
        TRoadMark *mark=dynamic_cast<TRoadMark*>(FActiveObj);
        if (mark)
            {
            TObjMetaClass *Meta=(TObjMetaClass*)Dict->ObjClasses->Items[ROADMARKCODE];
            TRoadMark *mnew=dynamic_cast<TRoadMark*>(MainForm->Factory->CreateRoadObj(Meta->ClassName,0,Meta->Id));
            if (mnew)
                {
                int L=mark->LMax;
                bool intown=IsInTown(L);
                // Ищем ближайшее и предыдущее примыкание слева и справа
                TRoadAttach *NL=0,*NR=0,*PL=0,*PR=0;
                int roadmaxl=1<<30;
                for (int i=0;i<MainForm->ResManager->DataCount;i++) {
                  TDtaSource *d=MainForm->ResManager->Data[i];
                  if (d->Id==RoadId) {
                     for (int i=0;i<d->Objects->Count;i++) {
                        TContRoadObject *CO=dynamic_cast<TContRoadObject*>(d->Objects->Items[i]);
                        if (CO && CO->DictId==ROADBOUNDCODE)
                           roadmaxl=CO->LMax;
                        TRoadAttach *A=dynamic_cast<TRoadAttach*>(d->Objects->Items[i]);
                        if (A && A->DictId==ROADATTACH) {
                           if (A->L<=L && A->Placement==opLeft) {
                              if (PL==0 || PL->L<A->L)
                                 PL=A;
                           } else if (A->L<=L) {
                              if (PR==0 || PR->L<A->L)
                                 PR=A;
                           } else if (A->Placement==opLeft) {
                              if (NL==0 || NL->L>A->L)
                                 NL=A;
                           } else {
                              if (NR==0 || NR->L>A->L)
                                 NR=A;
                           }
                        }
                     }
                  }
                }
                mnew->SetDirection(mark->Direction);
                mnew->L=L;
                mnew->SetK(mark->K);
                mnew->SetOffset(mark->Offset);
                mnew->SetLMax(mnew->L+10000);
                mnew->SetKind(mark->Kind);
               int minl=1<<30,maxl=1<<30,minr=1<<30,maxr=1<<30;
               if (NL && NL->Poly)
                  minl=min(NL->Poly->Points[0].L,NL->Poly->Points[NL->Poly->Count-1].L),
                  maxl=max(NL->Poly->Points[0].L,NL->Poly->Points[NL->Poly->Count-1].L);
               if (NR && NR->Poly)
                  minr=min(NR->Poly->Points[0].L,NR->Poly->Points[NR->Poly->Count-1].L),
                  maxr=max(NR->Poly->Points[0].L,NR->Poly->Points[NR->Poly->Count-1].L);
                  minl=((minl+99)/100)*100;
                  minr=((minr+99)/100)*100;
                  maxl=((maxl)/100)*100;
                  maxr=((maxr)/100)*100;

// Особые случаи
                if (mark->Kind==ma1||mark->Kind==ma3) {// сплошная
                  int minv=min(minl,minr);
                  if (minv<L+500) {  // Дальше перекресток, рисуем 1.7
                     mnew->SetKind(ma7);
                     if (min(maxl,maxr)>=max(minl,minr))
                        mnew->SetLMax(max(maxl,maxr));
                     else
                        mnew->SetLMax(min(maxl,maxr));
                  }  else {
                     mnew->SetKind(ma6);
                     mnew->SetLMax(L+(intown ? 5000: 10000));
                  }
                } else if (mark->Kind==ma2_1||mark->Kind==ma2_2) {
                  if (mark->Direction==roUnDirect && minl<L+500)
                     mnew->SetKind(ma7),mnew->SetLMax(maxl);
                  else if (mark->Direction==roDirect && minr<L+500)
                     mnew->SetKind(ma7),mnew->SetLMax(maxr);
                  else
                     mnew->SetKind(ma4);
                } else if (mark->Kind==ma4 || mark->Kind==ma10) {
                  mnew->SetKind(ma2_1);
                  if (mark->Direction==roUnDirect)
                     mnew->SetLMax(minl);
                  else
                     mnew->SetLMax(minr);
                } else if (mark->Kind==ma5) {
                  mnew->SetKind(ma6);
                  mnew->SetLMax(L+(intown?5000:10000));
                } else if (mark->Kind==ma6) {
                  TRoadMark *pr=0;
                  int i;
                  for (i=0;i<FActiveSource->Objects->Count;i++) {
                       pr=dynamic_cast<TRoadMark*>(FActiveSource->Objects->Items[i]);
                       if (pr && pr->K==mark->K && pr->Offset==mark->Offset && abs(pr->LMax-mark->L)<200)
                        break;
                  }
                  if (i<FActiveSource->Objects->Count && pr->Kind==ma1) {
                     mnew->SetKind(ma5);
                     mnew->SetLMax(min(minl,minr)-(IsInTown(min(minl,minr))?7000:14000));
                  } else {
                     mnew->SetKind(ma1);
                     mnew->SetLMax(min(minl,minr));
                  }
                } else if (mark->Kind==ma7||mark->Kind==ma13) {
                  if (mark->K==0 && mark->Offset==0) {
                     mnew->SetKind(ma1);
                     if (intown) {
                        if (min(minl,minr)<=L+15000)
                           mnew->SetLMax(min(minl,minr));
                        else
                           mnew->SetLMax(L+2000);
                     } else {
                        if (min(minl,minr)<=L+29000)
                           mnew->SetLMax(min(minl,minr));
                        else
                           mnew->SetLMax(L+4000);
                     }
                  } else {
                     mnew->SetKind(ma2_1);
                     mnew->SetLMax(mark->Direction==roDirect?minr:minl);
                  }
                } else if ((mark->Kind==ma11l || mark->Kind==ma11r) && mark->Kind==0 && mark->Offset==0) {
                                  TRoadMark *pr=0;
                  int i;
                  for (i=0;i<FActiveSource->Objects->Count;i++) {
                       pr=dynamic_cast<TRoadMark*>(FActiveSource->Objects->Items[i]);
                       if (pr && pr->K==mark->K && pr->Offset==mark->Offset && abs(pr->LMax-mark->L)<200)
                        break;
                  }
                  if (i<FActiveSource->Objects->Count && pr->Kind==ma1) {
                     mnew->SetKind(ma6);
                     mnew->SetLMax(L+(intown ? 5000: 10000));
                  } else {
                     mnew->SetKind(ma1);
                     mnew->SetLMax(min(minl,minr));
                  }
                }
                if (mnew->LMax>roadmaxl)
                  mnew->SetLMax(roadmaxl);
                if (frmMarkParam->Execute(Dict,mnew))
                    {
                    mnew->DrwClassId=Dict->SelectDrwParam(mnew,FCurPage);
                    FEditedData->Objects->Add(mnew);
                    FEditedData->SortByPlacement();
                    MainForm->SendBroadCastMessage(CM_INSERTOBJ,(int)mnew,(int)FEditedData);
                    SetObjectActive(mnew,FEditedData);
                    }
                }
            }
        }
}

void __fastcall TRoadFrm::NewMarkLine(void)
{
bool inspat=false;
if (FActiveObj)
    if (FEditedData==FActiveSource)
        {
        TRoadMark *mark=dynamic_cast<TRoadMark*>(FActiveObj);
        if (mark)
            {
            TObjMetaClass *Meta=(TObjMetaClass*)Dict->ObjClasses->Items[ROADMARKCODE];
            TRoadMark *mnew=dynamic_cast<TRoadMark*>(MainForm->Factory->CreateRoadObj(Meta->ClassName,0,Meta->Id));
            if (mnew)
                {
                mnew->SetDirection(mark->Direction);
                mnew->L=mark->L;
                mnew->SetLMax(mark->LMax);
                mnew->SetKind(mark->Kind);
                mnew->SetK(mark->K);
                mnew->SetOffset(mark->Offset);
                if (frmMarkParam->Execute(Dict,mnew))
                    {
                    mnew->DrwClassId=Dict->SelectDrwParam(mnew,FCurPage);
                    FEditedData->Objects->Add(mnew);
                    FEditedData->SortByPlacement();
                    MainForm->SendBroadCastMessage(CM_INSERTOBJ,(int)mnew,(int)FEditedData);
                    SetObjectActive(mnew,FEditedData);
                    }
                else
                    delete mnew;
                inspat=true;
                }
            }
        }
if (!inspat)
    AddNewObject(ROADMARKCODE);
}

void __fastcall TRoadFrm::ChangeActiveSignCode(void)
{
if (FActiveObj)
    if (FEditedData==FActiveSource)
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FActiveObj);
        if (sign)
            if (AddSignFrm->Execute(Dict,sign->NumRoadSign,sign->ViewKind));
                {
                sign->SetDictId(SGNCODE+AddSignFrm->SignClass);
                sign->NumRoadSign=AddSignFrm->NumCode;
                sign->ViewKind=AddSignFrm->Variation;
                sign->DrwClassId=Dict->SelectDrwParam(sign,FCurPage);
                InvalidateBoxes();
                }
        }
}

void __fastcall TRoadFrm::AddNewSign(void)
{
if (FEditedData)
    if (!FEditedData->ReadOnly)
        {
        if (FEditMetric)
            InsertPoint();
        else if (AddSignFrm->Execute(Dict,0,0))
            AddNewSign(AddSignFrm->Code.Trim(),AddSignFrm->Variation);
        }
}

void __fastcall TRoadFrm::DeleteActiveObject(bool NeedRemove)
{
if (FActiveObj)
    if (!FActiveSource->ReadOnly)
        {
        TRoadObject *s=dynamic_cast<TRoadObject*>(FActiveObj);
        if (s)
            {
            if (NeedRemove)
                {
                if (FEditedData)
                    FEditedData->SetMarker(0);
                FActiveSource->SetMarker(0);
                s->MarkTagByTree(1);
                if (FEditedData)
                    FActiveSource->DeleteMarkedObjects(1,CM_REMOVEOBJ);
                FActiveObj=NULL;
                FActiveSource=NULL;
                }
            else
                {
                FActiveSource->DeleteObjectEx(s);
                if (FEditedData)
                    FEditedData->DeleteObject(s);
                }
            InvalidateBoxes();
            PostActivateObj();
            }
        }
}

void __fastcall TRoadFrm::CalculateRoadMarkLength(void)
{
TDtaSource *src;
if (FEditedData)
    src=FEditedData;
else if (FMetricData)
    src=FMetricData;
else
    src=FActiveSource;
if (src)
    src->CalculateRoadMarkLength(2000);
}

void __fastcall TRoadFrm::BuildRoadLines(void)
{
if (FMetricData)
    {
    FMetricData->BuildRoadMetrics(0);
    FMetricData->BuildRoadLines(Dict);
    FMetricData->BuildRoadMetrics();
    MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)FMetricData);
    }
}

void __fastcall TRoadFrm::BreakRoadLines(void) {
   if (FMetricData) {
      FMetricData->BreakRoadLines();
   }
}


void __fastcall TRoadFrm::BuildWidePartsDialog(void)
{
frmWidePartDialog->Dict=Dict;
frmWidePartDialog->StartPos=FRoadMinL/100;
frmWidePartDialog->EndPos=FRoadMaxL/100;
if (frmWidePartDialog->ShowModal()==mrOk)
    {
    if (frmWidePartDialog->BuildParts||frmWidePartDialog->BuildLeftSides||frmWidePartDialog->BuildRightSides)
        {
        int sp=frmWidePartDialog->StartPos*100;
        int ep=frmWidePartDialog->EndPos*100;
        FMetricData->BuildRoadMetrics(1);
        if (frmWidePartDialog->BuildParts)
            FMetricData->BuildWidePart(sp,ep,frmWidePartDialog->PartMaxDev,frmWidePartDialog->PartRoundVal,FDictSour);
        if (frmWidePartDialog->BuildLeftSides)
            FMetricData->BuildRoadSides(sp,ep,rsLeft,frmWidePartDialog->SideMaxDev,frmWidePartDialog->SideRoundVal,frmWidePartDialog->SideKind,FDictSour);
        if (frmWidePartDialog->BuildRightSides)
            FMetricData->BuildRoadSides(sp,ep,rsRight,frmWidePartDialog->SideMaxDev,frmWidePartDialog->SideRoundVal,frmWidePartDialog->SideKind,FDictSour);
        FMetricData->BuildRoadMetrics();
        MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)FMetricData);
        }
    }
}


void __fastcall TRoadFrm::WidthMeasureDialog(void)
{
if (FMetricData)
    FMetricData->BuildWidthMeasure(10000,FDictSour);
}


void __fastcall TRoadFrm::LongSlopesPartDialog(void)
{
if (FProfilData)
    {
    frmBuildSlopes->ProfilMinLen=FProfilData->ProfilMinLen;
    frmBuildSlopes->ProfilMaxDev=FProfilData->ProfilMaxDev;
    frmBuildSlopes->ProfilVal1=FProfilData->ProfilVal1;
    frmBuildSlopes->ProfilVal2=FProfilData->ProfilVal2;
    frmBuildSlopes->StartPos=FRoadMinL/100;
    frmBuildSlopes->EndPos=(FRoadMaxL+99)/100;
    if (frmBuildSlopes->ShowModal()==mrOk)
        {
        FProfilData->ProfilMinLen=frmBuildSlopes->ProfilMinLen;
        FProfilData->ProfilMaxDev=frmBuildSlopes->ProfilMaxDev;
        FProfilData->ProfilVal1=frmBuildSlopes->ProfilVal1;
        FProfilData->ProfilVal2=frmBuildSlopes->ProfilVal2;
        int sp=frmBuildSlopes->StartPos*100;
        int ep=frmBuildSlopes->EndPos*100;
        FProfilData->BuildLongSlopesPart(Dict,sp,ep);
        InvalidateBoxes();
        }
    }
}

void __fastcall TRoadFrm::NextObject(void)
{
if (FActiveObj)
    {
    int index=-1;
    TRoadObject *next=FActiveSource->FindNext(FActiveObj->DictId,FActiveObj->L+1,100000000000,index);
    if (next)
        {
        if (MainForm->PropertyByClick)
            {
            TObjFrm *Frm;
            Application->CreateForm(__classid(TObjFrm), &Frm);
            Frm->BuildForm(FDictSour,FActiveSource,next);
            Frm->Show();
            }
        ActivateObject(next,FActiveSource);
        }
    }
}

void __fastcall TRoadFrm::PredObject(void)
{
if (FActiveObj)
    {
    int index=-1;
    TRoadObject *pred=FActiveSource->FindPred(FActiveObj->DictId,0,FActiveObj->L-1,index);
    if (pred)
        {
        if (MainForm->PropertyByClick)
            {
            TObjFrm *Frm;
            Application->CreateForm(__classid(TObjFrm), &Frm);
            Frm->BuildForm(FDictSour,FActiveSource,pred);
            Frm->Show();
            }
        ActivateObject(pred,FActiveSource);
        }
    }
}

void __fastcall TRoadFrm::SetAllSigns(void)
{
if (FEditedData)
    if (!FEditedData->ReadOnly)
        if ((Application->MessageBox("Вы действительно хотите добавить объекты в автоматическом режиме","Предупреждение",MB_YESNO)==IDYES))
            {
            int n=FEditedData->Objects->Count;
            for (int i=0;i<n;i++)
                {
                TRoadObject *Obj=FEditedData->Objects->Items[i];
                SDesignRules.HandleObject(Obj,FEditedData,FDictSour);
                }
            int c=FEditedData->Buffer->Count;
            FEditedData->AddFromBufer();
            ShowMessage("Операция завершена. Добавлено знаков : "+String(c));
            MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)FEditedData);
            }
}

void __fastcall TRoadFrm::SetDirector(void) {
if (FEditedData)
    if (!FEditedData->ReadOnly)
        if ((Application->MessageBox("Вы действительно хотите добавить сигнальные столбики в автоматичеком режиме","Предупреждение",MB_YESNO)==IDYES)) {
           for (int i=0;i<FEditedData->Objects->Count;i++) {
               if (FEditedData->Objects->Items[i]->DictId==ROADTUBECODE) {
                  TRoadTube *t=dynamic_cast<TRoadTube*>(FEditedData->Objects->Items[i]);
                  if (t && t->Placement==tuCross) {
                     TObjMetaClass *Meta=Dict->ObjClasses->Items[ROADSIGNALCODE];
                     TRoadObject *obj=FEditedData->Factory->CreateRoadObj(Meta->ClassName,0,ROADSIGNALCODE);
                     TRoadSignal *d=dynamic_cast<TRoadSignal*>(obj);
                     if (d) {
                        d->Count=7;
                        d->DX=-35;
                        d->MetricsKind=mkBrovka;
                        d->PutPosition(t->L-3000,t->L+3000);
                        d->Placement=opRight;
                        d->Kind=skStolb;
                        d->DrwClassId=Dict->SelectDrwParam(d,1);
                        FEditedData->Buffer->Add(d);
                     } else
                        delete obj;
                     obj=FEditedData->Factory->CreateRoadObj(Meta->ClassName,0,ROADSIGNALCODE);
                     d=dynamic_cast<TRoadSignal*>(obj);
                     if (d) {
                        d->Count=7;
                        d->DX=-35;
                        d->MetricsKind=mkBrovka;
                        d->PutPosition(t->L-3000,t->L+3000);
                        d->Placement=opLeft;
                        d->Kind=skStolb;
                        d->DrwClassId=Dict->SelectDrwParam(d,1);
                        FEditedData->Buffer->Add(d);
                     } else
                        delete obj;
                  }
               }
           }
        FEditedData->AddFromBufer();
        }
}

void __fastcall TRoadFrm::SetKmSigns(void)
{
if (FEditedData)
    if (!FEditedData->ReadOnly)
        if ((Application->MessageBox("Вы действительно хотите изменить все километровые отметки","Предупреждение",MB_YESNO)==IDYES))
            {
            SDesignRules.SetKmSign(FEditedData,FDictSour);
            int c=FEditedData->Buffer->Count;
            FEditedData->AddFromBufer();
            ShowMessage("Операция завершена. Добавлено знаков : "+String(c));
            MainForm->SendBroadCastMessage(CM_INSERTGROUP,0,(int)FEditedData);
            }
}

void __fastcall TRoadFrm::QuickDesign(void)
{
if (FActiveObj)
    if (FEditedData)
        if (!FEditedData->ReadOnly)
            {
            SDesignRules.HandleObject(FActiveObj,FEditedData,FDictSour);
            FEditedData->AddFromBufer();
            InvalidateBoxes();
            PostActivateObj();
            }
}

void __fastcall TRoadFrm::DesignAttach(void)
{
Designers[MainForm->CurAttachDesigner]->Design(FActiveObj,FActiveSource,Dict);
if (FActiveObj&&FMetricData)
    {
    if (FActiveObj->Poly)
        {
        FMetricData->Road->CalcPointsPos(FActiveObj->Poly,FActiveObj);
        FActiveObj->PostEditPoly();
        }
    }
}

void __fastcall TRoadFrm::DesignAttachMark(void)
{
if (FEditedData) {
   MarkDesigners[0]->Design(FActiveObj,FEditedData,Dict);
   if (FActiveObj&&FMetricData)
      {
      if (FActiveObj->Poly)
         {
         FMetricData->Road->CalcPointsPos(FActiveObj->Poly,FActiveObj);
         FActiveObj->PostEditPoly();
         }
      }
   }
}

void __fastcall TRoadFrm::HandlePutPoint(int X,int Y,bool Leep)
{
if (FInsertingObj)
    {
    int CL,CX;
    FMetricData->Road->SetFrame(FPMinL,FPMaxL,FPMinX,FPMaxX,FPlanKind,FPlanDirect);
    FMetricData->Road->SetOutBound(0,PBox->Width,0,PBox->Height);
    FMetricData->Road->RConvertPoint(X,Y,CL,CX);
    if (Leep)
        FDrawMan->FindNearestL(CL,NULL,max(FDrawMan->BaseScaleL,FSclL)/KFLEEP);
    TRoadDirection dr;
    if (CX<0)
        dr=roUnDirect,CX=-(CX-FMetricData->Road->LeftLine.FindX(CL));
    else
        dr=roDirect,CX-=FMetricData->Road->RightLine.FindX(CL);
    TRoadSign *s=dynamic_cast<TRoadSign*>(FInsertingObj);
    if (s)
        {
        int SelCount=FDrawMan->SelectByXY(X,Y,SelObjs,SelSrc,DrwIndexes,MAXSEL);
        TRoadSign *tempSign = 0;
        for (int i=0;i<SelCount;i++) {
            if (0==(tempSign = dynamic_cast<TRoadSign*>(SelObjs[i]))) {
                break;
            }
        }
        if(tempSign) {
           s->L = tempSign->L;
           s->SetDX(tempSign->DX);
        }else{
           s->L=CL;
           s->SetDX(CX);
        }
        s->SetDirection(dr);
        }
    else
        {
        TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject*>(FInsertingObj);
        if (dobj)
            dobj->L=CL;
        else
            {
            TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(FInsertingObj);
            if (cobj)
                {
                if (ZoomStatus==zsWaitPoint)
                    {
                    cobj->PutPosition(CL,CL+1000);
                    ZoomStatus=zsWaitSecPoint;
                    }
                else if (ZoomStatus==zsWaitSecPoint)
                    {
                    if (CL<cobj->LMin)
                        cobj->PutPosition(CL,cobj->LMin);
                    else
                        cobj->PutPosition(cobj->LMin,CL);
                    ZoomStatus=zsNone;
                    }
                }
            }
        }
        if (ZoomStatus!=zsWaitSecPoint)
            {
            TRoadMark *InsertingMark=dynamic_cast<TRoadMark*>(FInsertingObj);
            int MResult=0;
            if (InsertingMark)
                {
                MResult=frmMarkParam->Execute(Dict,InsertingMark);
                }
            else
                {
                TObjFrm *Frm;
                Application->CreateForm(__classid(TObjFrm), &Frm);


                TRoadSignal *rs = dynamic_cast<TRoadSignal*>(FInsertingObj);
                if(rs){
                  rs->Placement = lPlace;
                  rs->Kind = lKind;
                  if((!frmSignalsInsert1->chkAuto->Checked)||GetKeyState(VK_CONTROL)&0x0100){
                    frmSignalsInsert1->RoadSignal = rs;
                    frmSignalsInsert1->ShowModal();
                  }
                }

                Frm->BuildForm(FDictSour,FEditedData,FInsertingObj);
                Frm->ModalRes=&MResult;
                Frm->Changed=true;
                Frm->ShowModal();

                if(rs){
                  lPlace = rs->Placement;
                  lKind = rs->Kind;
                }
                }
            if (MResult==mrOk)
                {
                FInsertingObj->DrwClassId=Dict->SelectDrwParam(FInsertingObj,FCurPage);
                FEditedData->Objects->Add(FInsertingObj);
                FEditedData->SortByPlacement();
                MainForm->SendBroadCastMessage(CM_INSERTOBJ,(int)FInsertingObj,(int)FEditedData);
                SetObjectActive(FInsertingObj,FEditedData);
                MainForm->SendBroadCastMessage(CM_INSERTOBJ,(int)FInsertingObj,(int)FEditedData);
                FInsertingObj=NULL;
                }
            else
                {
                delete FInsertingObj;
                FInsertingObj=NULL;
                }
            }

//    FDataSour->AddManSign(FDictSour,dr,spRight,CL,CX,AddSignFrm->Code.Trim(),"","");

        InvalidateBoxes();
    }
if (ZoomStatus!=zsWaitSecPoint)
    ZoomStatus=zsNone;
}

void __fastcall TRoadFrm::EchoCursorPosition(int X,int Y)
{
int CL,CX;
FMetricData->Road->SetFrame(FPMinL,FPMaxL,FPMinX,FPMaxX,FPlanKind,FPlanDirect);
FMetricData->Road->SetOutBound(0,PBox->Width,0,PBox->Height);
FMetricData->Road->RConvertPoint(X,Y,CL,CX);
StatusBar->Panels->Items[0]->Text=String("L=")+String((CL+50)/100)+String("; X=")+String((double)CX/100);
TGeometryVal G;
FProfilData->Road->Geometry.GetMesValue(CL,G);
StatusBar->Panels->Items[1]->Text=String(G.LeftSlope);
StatusBar->Panels->Items[2]->Text=String(G.RightSlope);
StatusBar->Panels->Items[3]->Text=String(G.LongSlope);
}

String __fastcall TRoadFrm::GetObjName(TRoadObject *obj)
{
if (obj)
    return Dict->ObjClasses->Items[obj->DictId]->Title;
return "";
}

void __fastcall TRoadFrm::ShowStatus(void)
{
enum TZoomStatus {zsNone,zsWaitZoom,zsZoom,zsWaitPoint,zsWaitSecPoint};
String Str="";
switch (ZoomStatus)
    {
    case zsWaitZoom: Str+="Выделите участок для просмотра"; break;
    case zsZoom:     Str+="Выделите участок для просмотра"; break;
    case zsWaitPoint:
        {
        if (dynamic_cast<TDescreetRoadObject*>(FInsertingObj))
            Str+="Укажите положение объекта : "+GetObjName(FInsertingObj);
        else if (FInsertingObj)
            Str+="Укажите начало объекта : "+GetObjName(FInsertingObj);
        } break;
    case zsWaitSecPoint:
            Str+="Укажите конец объекта : "+GetObjName(FInsertingObj);break;
    case zsNone: {if (FActiveObj)
                Str+="Выбран объект : "+GetObjName(FActiveObj);
            } break;
    }
StatusBar->Panels->Items[5]->Text=Str;
}

void __fastcall TRoadFrm::PostAction(void)
{
bool b;
b=FSclL>144;
SpeedButton1->Enabled=b;
SpeedButton6->Enabled=b;
MainForm->N33->Enabled=b;
SpeedButton6->Down=b&&(ZoomStatus!=zsNone);

b=(FMinL==FPMinL)&&(FMaxL==FPMaxL);
SpeedButton2->Enabled=!b;
SpeedButton3->Enabled=!b;
MainForm->N34->Enabled=!b;
MainForm->N35->Enabled=!b;

b=(FMinX==FPMinX)&&(FMaxX==FPMaxX);
SpeedButton7->Enabled=!b;
b=FActiveObj!=NULL;
bool c;
if (FActiveSource)
    c=!FActiveSource->ReadOnly;
else
    c=false;
SpeedButton11->Enabled=b;
SpeedButton12->Enabled=b;
MainForm->N17->Enabled=b&&c;
MainForm->N25->Enabled=b&&c;
MainForm->PrevObjBut->Enabled=b;
MainForm->NextObjBut->Enabled=b;
if (b)
    SpeedButton12->Down=FActiveObj->Selected;
else
    SpeedButton12->Down=false;
if (FEditedData)
    {
    SpeedButton15->Enabled=!FEditedData->ReadOnly;
    SpeedButton15->Down=MainForm->ResManager->CopyDestination==FEditedData;
    }
else
    SpeedButton15->Enabled=false;
SpeedButton13->Enabled=(MainForm->ResManager->CopyDestination!=NULL);
if (FEditedData)
    {
    SpeedButton14->Enabled=(!FEditedData->ReadOnly)&&b;
    }
else
    {
    SpeedButton14->Enabled=false;
    }
SpeedButton14->Down=FEditMetric;
SpeedButton16->Down=FShowProfil;
c=false;
if (FActiveObj)
    if (dynamic_cast<TRoadAttach*>(FActiveObj))
        c=true;

MainForm->AttDesignBut->Enabled=c;
MainForm->RMDesignBut->Enabled=c;
// Видео
bool v_en=frmVideoForm->Visible&&(frmVideoForm->Data==FVideoData);
SpeedButton18->Down=v_en&&(frmVideoForm->Direction==1);
SpeedButton19->Down=v_en&&(frmVideoForm->Direction==2);
SpeedButton20->Down=FPartVisible;
ShowStatus();
}

void __fastcall TRoadFrm::PostChangeFocus(void)
{
MainForm->N3->Enabled=true;
MainForm->N6->Enabled=true;
MainForm->N19->Enabled=true;
MainForm->N5->Enabled=true;
MainForm->N59->Enabled=true;
MainForm->N71->Enabled=true;
if (FEditedData)
    {
    MainForm->N16->Enabled=!FEditedData->ReadOnly;
    MainForm->N32->Enabled=!FEditedData->ReadOnly;
    MainForm->N41->Enabled=!FEditedData->ReadOnly;
    MainForm->N43->Enabled=!FEditedData->ReadOnly;
    MainForm->N45->Enabled=!FEditedData->ReadOnly;
    MainForm->N46->Enabled=!FEditedData->ReadOnly;
    MainForm->AddDangBut->Enabled=!FEditedData->ReadOnly;
    MainForm->AddSignBut->Enabled=!FEditedData->ReadOnly;
    }
else
    {
    MainForm->N16->Enabled=false;
    MainForm->N32->Enabled=false;
    MainForm->N41->Enabled=false;
    MainForm->N43->Enabled=false;
    MainForm->N45->Enabled=false;
    MainForm->N46->Enabled=false;
    MainForm->AddDangBut->Enabled=false;
    MainForm->AddSignBut->Enabled=false;
    }
MainForm->N37->Enabled=true;
MainForm->N38->Enabled=true;
MainForm->N14->Enabled=true;
MainForm->N70->Enabled=true;
for (int i=MainForm->N13->Count-1;i>=0;i--) {
   if (MainForm->N13->Items[i]->Tag>=100 && MainForm->N13->Items[i]->Tag<200)
      delete MainForm->N13->Items[i];
}
if (FVideoData)
    {
    MainForm->N18->Enabled=FVideoData->HaveDirVideo; // Видео
    MainForm->N47->Enabled=FVideoData->HaveUnDirVideo; // Видео
    SpeedButton18->Enabled=FVideoData->HaveDirVideo;
    SpeedButton19->Enabled=FVideoData->HaveUnDirVideo;
    for (int i=0;i<FVideoData->DirVideoTime->Count;i++) {
      TMenuItem *m=new TMenuItem(MainForm->N13);
      m->Tag=FVideoData->DirVideoTime->Items[i]->Id+100;
      m->Caption=FVideoData->DirVideoTime->Items[i]->Description;
      MainForm->N13->Add(m);
      m->OnClick=MainForm->N18->OnClick;
    }
    for (int i=0;i<FVideoData->UnDirVideoTime->Count;i++) {
      TMenuItem *m=new TMenuItem(MainForm->N13);
      m->Tag=FVideoData->UnDirVideoTime->Items[i]->Id+100;
      m->Caption=FVideoData->UnDirVideoTime->Items[i]->Description;
      MainForm->N13->Add(m);
      m->OnClick=MainForm->N47->OnClick;
    }
    }
else
    {
    MainForm->N18->Enabled=false; // Видео
    MainForm->N47->Enabled=false; // Видео
    SpeedButton18->Enabled=false;
    SpeedButton19->Enabled=false;
    }
MainForm->N39->Enabled=true;
MainForm->N26->Enabled=true;
MainForm->N48->Enabled=true;
MainForm->N49->Enabled=true;
MainForm->N50->Enabled=true;
MainForm->N50->Checked=FPan2Vis;
MainForm->N74->Enabled=true;
MainForm->N74->Checked=FPan1Vis;
MainForm->N75->Enabled=true;
MainForm->N75->Checked=FPan4Vis;
MainForm->N21->Enabled=true;
MainForm->N22->Enabled=true;
MainForm->N24->Enabled=true;
TDtaSource *cd=MainForm->ResManager->CopyDestination;
MainForm->N26->Enabled=(cd!=NULL)&&(cd!=FEditedData);
}

void __fastcall TRoadFrm::PostActivateObj(void)
{
if (FEditedData)
    {
    if ((!FActiveObj)||FEditedData->ReadOnly)
        MainForm->AutoDesignBut->Enabled=false;
    else
        MainForm->AutoDesignBut->Enabled=SDesignRules.CanHandle(FActiveObj,FEditedData,Dict);
    }
else
    MainForm->AutoDesignBut->Enabled=false;
if (FEditMetric)
    {
    FEditMetric=false;
    if (FActiveObj)
        if (FActiveObj->Poly==FPoly)
            {
            FEditMetric=true;
            PolyFrm->UpdatePoly(FVector);
            }
    PostAction();
    }
if (FActiveObj)
    {
    TRoadSign *s=dynamic_cast<TRoadSign*>(FActiveObj);
    TRoadMark *m=dynamic_cast<TRoadMark*>(FActiveObj);
    bool b=FActiveSource==FEditedData;
    ObjMenu_Move->Visible=b;
    MainForm->N63->Enabled=b;
    ObjMenu_Delete->Visible=b;
    ObjMenu_Sign->Visible=b&&s;
    ObjMenu_Mark->Visible=b&&m;
    ObjMenu_ContinueMark->Visible=b&&m;
    if (FActiveObj->Poly && FActiveObj->Poly->Count>=2)
       StatusBar->Panels->Items[4]->Text="L="+FloatToStr((double)((int)(FActiveObj->Poly->Length()+0.5))/100);
    else {
      TContRoadObject *cro=dynamic_cast<TContRoadObject*>(FActiveObj);
      if (cro)
         StatusBar->Panels->Items[4]->Text="L="+FloatToStr((double)(cro->LMax-cro->LMin)/100);
      else
         StatusBar->Panels->Items[4]->Text="";
      }
    }
else
    {
    StatusBar->Panels->Items[4]->Text="";
    MainForm->N63->Enabled=false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TRoadFrm::SpeedButton1Click(TObject *Sender)
{
ScaleL(SQRT2);
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton2Click(TObject *Sender)
{
ScaleL(1/SQRT2);
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ShowEntRoad(TObject *Sender)
{
ShowAll();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::HScrollChange(TObject *Sender)
{
if (FPlanKind==pkGorizontal)
    {
    if (FPlanDirect==pdDirect)
        PutPLMin(HScroll->Position,HScroll->Max);
    else
        PutPLMin(HScroll->Max-HScroll->Position,HScroll->Max);
    SetMarkerPos((FPMinL+FPMaxL)>>1);
    }
else
    {
    if (FPlanDirect==pdDirect)
        PutPXMin(HScroll->Position,HScroll->Max);
    else
        PutPXMin(HScroll->Max-HScroll->Position,HScroll->Max);
    }
}
//---------------------------------------------------------------------------
void __fastcall TRoadFrm::VScrollChange(TObject *Sender)
{
if (FPlanKind==pkGorizontal)
    {
    if (FPlanDirect==pdDirect)
            PutPXMin(VScroll->Position,VScroll->Max);
    else
            PutPXMin(VScroll->Max-VScroll->Position,VScroll->Max);
    }
else
    {
    if (FPlanDirect==pdDirect)
        PutPLMin(VScroll->Max-VScroll->Position,VScroll->Max);
    else
        PutPLMin(VScroll->Position,VScroll->Max);
    SetMarkerPos((FPMinL+FPMaxL)>>1);
    }
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N11Click(TObject *Sender)
{
   ShowMapPlan();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ShowMapPlan(void) {
FPan1Vis=!FPan1Vis;
ShowPanels();
InvalidateBoxes();
}

void __fastcall TRoadFrm::ShowProfil(void)
{
FPan2Vis=!FPan2Vis;
ShowPanels();
InvalidateBoxes();
}

void __fastcall TRoadFrm::ShowVisPlan(void)
{
FPan4Vis=!FPan4Vis;
ShowPanels();
InvalidateBoxes();
}

void __fastcall TRoadFrm::ShowDress(void)
{
FPan3Vis=!FPan3Vis;
ShowPanels();
InvalidateBoxes();
}

void __fastcall TRoadFrm::N21Click(TObject *Sender)
{
ShowProfil();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton4Click(TObject *Sender)
{
double DL;
if (FPlanKind==pkGorizontal)
    DL=(FPMaxX-FPMinX)/(double)PBox->Height*PBox->Width;
else
    DL=(FPMaxX-FPMinX)/(double)PBox->Width*PBox->Height;
__int32 CL=(FPMaxL+FPMinL)>>1;
DL/=2;
FPMaxL=CL+DL;
FPMinL=CL-DL;
ShowScale();
InvalidateBoxes();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::MoveCurrentPoint(int X,int Y)
{
if (CPVisible)
    DrawCurrentPoint();
CP.x=X;
CP.y=Y;
DrawCurrentPoint();
}

void __fastcall TRoadFrm::DrawCurrentPoint(void)
{
CPVisible=!CPVisible;
TPenMode oldmode=PBox->Canvas->Pen->Mode;
PBox->Canvas->Pen->Mode=pmXor;
TBrushStyle oldstyle=PBox->Canvas->Brush->Style;
PBox->Canvas->Brush->Style=bsClear;
PBox->Canvas->Pen->Color=clYellow;
int oldwidth=PBox->Canvas->Pen->Width;
PBox->Canvas->Pen->Width=2;
PBox->Canvas->Ellipse(CP.x-4,CP.y-4,CP.x+4,CP.y+4);
PBox->Canvas->Pen->Mode=oldmode;
PBox->Canvas->Brush->Style=oldstyle;
PBox->Canvas->Pen->Width=oldwidth;
}

void __fastcall TRoadFrm::PBoxMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if (FPlanKind==pkGorizontal)
    {
    int CL,CX;
    FMetricData->Road->SetFrame(FPMinL,FPMaxL,FPMinX,FPMaxX,FPlanKind,FPlanDirect);
    FMetricData->Road->SetOutBound(0,PBox->Width,0,PBox->Height);
    FMetricData->Road->RConvertPoint(X,Y,CL,CX);
    HRuler->Marker=(CL-FRelativeNull)/100;
    VRuler->Marker=CX/100;
    }
else
    {
    int CL,CX;
    FMetricData->Road->SetFrame(FPMinL,FPMaxL,FPMinX,FPMaxX,FPlanKind,FPlanDirect);
    FMetricData->Road->SetOutBound(0,PBox->Width,0,PBox->Height);
    FMetricData->Road->RConvertPoint(X,Y,CL,CX);
    HRuler->Marker=CX/100;
    VRuler->Marker=(CL-FRelativeNull)/100;
    }
if ((ZoomStatus==zsWaitPoint)||((ZoomStatus==zsWaitSecPoint)))
    {
    if (Shift.Contains(ssShift))
        FDrawMan->LeepPoint(X,Y,FActiveObj,max(FDrawMan->BaseScaleL,FSclL)/KFLEEP);
    MoveCurrentPoint(X,Y);
    }
else if (ZoomStatus==zsZoom)
    {
    DrawFocusRect();
    CRectPos.x=X;
    CRectPos.y=Y;
    DrawFocusRect();
    }
else if (ZoomStatus==zsFocusRect)
    {
    DrawFocusRect();
    if (Shift.Contains(ssShift))
        {
        CRectPos.x=X;
        CRectPos.y=Y;
        DrawFocusRect();
        }
    else
        ZoomStatus=zsNone;
    }
else if (ZoomStatus==zsMovePoint)
    {
    int CX=X+FMovePtDX;
    int CY=Y+FMovePtDY;
//    if (Shift.Contains(ssShift))
//            FDrawMan->LeepPoint(CX,CY,FActiveObj,max(FDrawMan->BaseScaleL,FSclL)/KFLEEP);
    TRoadPoint P=(*FPoly)[FActivePoint];
    FDrawMan->Road->RConvertPoint(CX,CY,P.L,P.X);
    if (Shift.Contains(ssShift))
        FDrawMan->FindNearestL(P.L,FActiveObj,max(FDrawMan->BaseScaleL,FSclL)/KFLEEP);
    SetPoint(P,FActivePoint);
    PolyFrm->UpdatePoint(FActivePoint);
    PBox->Invalidate();
    }
else
    {
    if(GetKeyState('L')&0x0100&&fMishaWantMorePoints){
       int tx,ty;
       int index;
       TRoadPoint P;
       FDrawMan->Road->RConvertPoint(X,Y,P.L,P.X);
       tx = P.L - lPointAddingPoint.L;
       ty = P.X - lPointAddingPoint.X;
       float r = sqrt(tx*tx+ty*ty);
       if(r>300){
         lPointAddingPoint.L = P.L;
         lPointAddingPoint.X = P.X;
         lPointAddingPoint.Code=1;
         InsertPoint(lPointAddingPoint,FPoly->Count);
       }
    }
    
    PBox->Cursor=crDefault;
    if (FGridVisible)
        {
        int Val;
        if (FMoving&&Shift.Contains(ssShift))
            FDrawMan->LeepPoint(X,Y,FActiveObj,max(FDrawMan->BaseScaleL,FSclL)/KFLEEP);
        if (FPlanKind==pkGorizontal)
            Val=X;
        else
            Val=Y;
        if (FMoving)
            {
            ClearGrid();
            if (FMinMov)
                FGridMinX=Val;
            else
                FGridMaxX=Val;
            DrawGrid();
            }
        else
            {
            if (((abs(FGridMinX-Val)<2)&&(FMinCanMove))||((abs(FGridMaxX-Val)<2)&&(FMaxCanMove)))
                {
                if (FPlanKind==pkGorizontal)
                    PBox->Cursor=crHSplit;
                else
                    PBox->Cursor=crVSplit;
                }
            }
        }
    }
PostAction();
EchoCursorPosition(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PBoxMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
fMishaWantMorePoints = false;
if (ZoomStatus==zsZoom)
    {
    DrawFocusRect();
    CRectPos.x=X;
    CRectPos.y=Y;
    ZoomStatus=zsWaitZoom;
    ScaleByRect();
    ZoomStatus=zsNone;
    }
else if ((ZoomStatus==zsWaitPoint)||(ZoomStatus==zsWaitSecPoint))
    {
    if (Button==mbLeft)
        HandlePutPoint(X,Y,Shift.Contains(ssShift));
    else
        ZoomStatus=zsNone;
    if (CPVisible)
        DrawCurrentPoint();
    }
else if (FMoving)
    {
    UpdateActiveObject(Shift.Contains(ssShift));
    FMoving=false;
    FMinCanMove=FMaxCanMove=false;
    InvalidateBoxes();
    }
else if (ZoomStatus==zsMovePoint)
    {
    ZoomStatus=zsNone;
    PBox->Invalidate();
    }
else if (FEditMetric)
    {
    int ap=FindActivePoint(X,Y);
    POINT CurP;
    CurP.x=X;
    CurP.y=Y;
    if (Shift.Contains(ssShift))   // Добавление выделения
        {
        bool SelComplete=false;
        if (ZoomStatus==zsFocusRect)
            {
            ZoomStatus=zsNone;
            DrawFocusRect();
            CRectPos.x=X;
            CRectPos.y=Y;
            int MinX=min(CRectPos.x,SRectPos.x);
            int MaxX=max(CRectPos.x,SRectPos.x);
            int MinY=min(CRectPos.y,SRectPos.y);
            int MaxY=max(CRectPos.y,SRectPos.y);
            if ((MaxX-MinX>1)||(MaxY-MinY>1))  // Выделение в рамке
                {
                SelComplete=true;
                for (int i=0;i<FVector->Count;i++)
                    if ((FVector->Points[i].x<=MaxX)&&(FVector->Points[i].x>=MinX)&&
                            (FVector->Points[i].y<=MaxY)&&(FVector->Points[i].y>=MinY))
                        {
                        FVector->Select(i);
                        PolyFrm->SelectPoint(i);
                        }
                PBox->Invalidate();
                }
            }
        if (!SelComplete)
            {
            if (ap>=0)
                {
                FVector->Select(ap);
                PolyFrm->SelectPoint(ap);
                FActivePoint=ap;
                PolyFrm->SetActivePoint(FActivePoint,false);
                PBox->Invalidate();
                }
            }
        }
    else if (Shift.Contains(ssAlt))  // Добавляем точку в хвост вектора
        {
        TRoadPoint P;
        FDrawMan->Road->RConvertPoint(CurP.x,CurP.y,P.L,P.X);
        P.Code=PolyFrm->ParamCode;
        InsertPoint(P,FPoly->Count);
        }
    else if (Shift.Contains(ssCtrl)) // Добавляем точку в середину вектора
        {
        POINT RetP;
        int index;
        int l=FVector->LenTo(CurP,RetP,index);
        if (l<2)
            {
            TRoadPoint P;
            FDrawMan->Road->RConvertPoint(RetP.x,RetP.y,P.L,P.X);
            P.Code=PolyFrm->ParamCode;
            InsertPoint(P,index+1);
            }
        }
    else                              //Выбор активной точки
        {
        FVector->DisSelect();
        FVector->Select(ap);
        FActivePoint=ap;
        PolyFrm->SetActivePoint(FActivePoint,true);
        PBox->Invalidate();
        }
    }
else if (FShowProfil)
    {
    TRoadPoint P;
    FDrawMan->Road->RConvertPoint(X,Y,P.L,P.X);
    TDrawContents *Cont=new TDrawBitmap;
    int w=PictureForm->ClientWidth;
    int h=PictureForm->ClientHeight;
    Cont->SetSize(w,h);
    Cont->PrepareUpdating();
    FDrawMan->FillCont(Cont);
    FDrawMan->DrawRazrez(Cont,&TRect(0,0,w,h),FPlanKind,FPlanDirect,P.L);
    Cont->FinishUpdating();
    PictureForm->Image->Picture->Bitmap->Width=w;
    PictureForm->Image->Picture->Bitmap->Height=h;
    Cont->DrawTo(PictureForm->Image->Canvas,0,0);
    PictureForm->Image->Invalidate();
    delete Cont;
    FShowProfil=false;
    PictureForm->Caption="Поперечный профиль. "+FRoadName.Trim()+String(" : ")+String(P.L/100);
    PictureForm->Show();
    }
else if (Button==mbLeft)
    {
    ClearGrid();
    SelCount=FDrawMan->SelectByXY(X,Y,SelObjs,SelSrc,DrwIndexes,MAXSEL);
    if (SelCount>1)
        {
        BuildPopMenu();
        ShowPopMenu();
        }
    else if (SelCount==1)
        ShowMenu(NULL);
    else
        {
        FActiveObj=NULL;
        FActiveSource=NULL;
        PostActivateObj();
        }
    }
else if (Button==mbRight)
    {
    CP.x=X;
    CP.y=Y;
    TPoint P=PBox->ClientToScreen(TPoint(X,Y));
    Popup->Popup(P.x,P.y);
    }
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PBoxMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if ((Button==mbRight)&&(!FEditMetric))
    {
    SelCount=FDrawMan->SelectByXY(X,Y,SelObjs,SelSrc,DrwIndexes,MAXSEL);
    int i;
    for (i=0;i<SelCount;i++)
        if (SelObjs[i]==FActiveObj)
            break;
    if (i<SelCount)
        {
        POINT p;
        GetCursorPos(&p);
        ObjMenu->Popup(p.x,p.y);
        }
    }
else if (ZoomStatus==zsWaitZoom)
    {
    ZoomStatus=zsZoom;
    SRectPos.x=X;
    SRectPos.y=Y;
    CRectPos.x=X;
    CRectPos.y=Y;
    DrawFocusRect();
    }
else if (FEditMetric)
    {
    if (Shift.Contains(ssShift))
        {
        ZoomStatus=zsFocusRect;
        SRectPos.x=X;
        SRectPos.y=Y;
        CRectPos.x=X;
        CRectPos.y=Y;
        DrawFocusRect();
        }
    else
        {

        if(GetKeyState('L')&0x0100){
           fMishaWantMorePoints = true;
           FDrawMan->Road->RConvertPoint(X,Y,lPointAddingPoint.L,
                                             lPointAddingPoint.X);
           lPointAddingPoint.Code=0;
           InsertPoint(lPointAddingPoint,FPoly->Count);
        }

        int ap=FindActivePoint(X,Y);
        if ((ap==FActivePoint)&&(ap>=0))
            {
            ZoomStatus=zsMovePoint;
            FMovePtDX=(*FVector)[ap].x-X;
            FMovePtDY=(*FVector)[ap].y-Y;
            }
        }
    }
else if (FShowProfil)  // Чтобы ничего не делала в этом случае
    {
    }
else if ((FGridVisible)&&(FActiveSource==FEditedData)&&(FActiveSource))
    {
    int Val;
    if (FPlanKind==pkGorizontal)
        Val=X;
    else
        Val=Y;
    if ((abs(FGridMinX-Val)<2)&&(FMinCanMove))
        {
        FMoving=true;
        FMinMov=true;
        }
    if ((abs(FGridMaxX-Val)<2)&&(FMaxCanMove))
        {
        FMoving=true;
        FMinMov=false;
        }
    }
if (HScroll->Visible)
        HScroll->SetFocus();
else
        VScroll->SetFocus();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ChangeOrientation(void)
{
if (FPlanKind==pkGorizontal)
    FPlanKind=pkVertical;
else
    FPlanKind=pkGorizontal;
AlignPanels();
ShowScale();
InvalidateBoxes();
}

void __fastcall TRoadFrm::SpeedButton5Click(TObject *Sender)
{
ChangeOrientation();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton6Click(TObject *Sender)
{
if (SpeedButton6->Down)
    ZoomStatus=zsWaitZoom;
else
    {
    if (ZoomStatus==zsZoom)
        DrawFocusRect();
    ZoomStatus=zsNone;
    }
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
if (FViewId)
    DBDataModule->SaveView(this,FViewId,FViewName);
Release();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N31Click(TObject *Sender)
{
VisSet->Show();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SclXValKeyPress(TObject *Sender, char &Key)
{
try
    {
    if (Key==13)
        {
        __int32 X=SclXVal->Text.ToInt();
        ScaleX((double)FSclX/X);
        }
    }
catch (...)
    {}
if (((Key<'0')||(Key>'9'))&&(Key!=8))
    Key=0;
PostAction();
}
//---------------------------------------------------------------------------



void __fastcall TRoadFrm::SclLValKeyPress(TObject *Sender, char &Key)
{
try
    {
    if (Key==13)
        {
        __int32 L=SclLVal->Text.ToInt();
        ScaleL((double)FSclL/L);
        }
    }
catch (...)
    {}
if (((Key<'0')||(Key>'9'))&&(Key!=8))
    Key=0;
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton7Click(TObject *Sender)
{
FPMinX=FMinX;
FPMaxX=FMaxX;
ShowScale();
InvalidateBoxes();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::FormResize(TObject *Sender)
{
ShowScale();
InvalidateBoxes();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::WndProc(TMessage &Mes)
{
if (Mes.Msg==CM_ONACTIVATEROADWIN)
    {
    if (Mes.WParam!=(int)this)
        {
        FActiveObj=NULL;
        FActiveSource=NULL;
        PostActivateObj();
        InvalidateBoxes();
        }
    return;
    }
else if (Mes.Msg==CM_CHANGEVIS)
    {
    if (VisSet->SourceVisible((TDtaSource*)Mes.LParam))
        InvalidateBoxes();
    return;
    }
else if ((Mes.Msg==CM_DATARELOAD)||(Mes.Msg==CM_DELETEGROUP))
    {
    if (VisSet->SourceVisible((TDtaSource*)Mes.LParam))
        {
        FActiveObj=NULL;
        FActiveSource=NULL;
        PostActivateObj();
        InvalidateBoxes();
        }
    return;
    }
else if (Mes.Msg==CM_OPENDATASOURCE)
    {
    if (VisSet)
        if (FRoadId==((TDtaSource*)Mes.LParam)->Id)
            VisSet->SetRoadId(FRoadId,FDictSour);
    }
else if (Mes.Msg==CM_REMOVEOBJ)
    {
    if ((int)FActiveObj==Mes.WParam)
        {
        FActiveObj=NULL;
        FActiveSource=NULL;
        PostActivateObj();
        }
    InvalidateBoxes();        
    return;
    }
else if ((Mes.Msg==CM_INSERTOBJ)||(Mes.Msg==CM_UPDATEOBJ)||(Mes.Msg==CM_INSERTGROUP))
    {
    if (VisSet->SourceVisible((TDtaSource*)Mes.LParam))
        {
        InvalidateBoxes();
        PostActivateObj();
        }
    return;
    }
else if ((Mes.Msg==CM_CHANGESEL)||(Mes.Msg==CM_SELECTOFF)||((Mes.Msg==CM_SELECTGROUP)))
    {
    if (VisSet->SourceVisible((TDtaSource*)Mes.LParam))
        PBox->Invalidate();
    return;
    }
else if (Mes.Msg==CM_ACTIVATEOBJECT)
    {
    if (VisSet->SourceVisible((TDtaSource*)Mes.LParam))
        ActivateObject((TRoadObject*)Mes.WParam,(TDtaSource*)Mes.LParam);
    return;
    }
else if (Mes.Msg==CM_ONACTIVATEOBJECT)
    {
    if ((int)(FActiveObj)!=Mes.WParam)
        {
        FActiveObj=NULL;
        FActiveSource=NULL;
        PostActivateObj();
        PBox->Invalidate();
        }
    return;
    }
else if (Mes.Msg==CM_CHANGECOPYDEST)
    {
    PostAction();
    return;
    }
else if (Mes.Msg==CM_CHANGEVIDEOSOURCE)
    {
    PostAction();
    return;
    }
else if (Mes.Msg==WM_MOUSEWHEEL)
    {
    int key=Mes.WParamLo;
    int delta=(signed __int16)(Mes.WParamHi);
    if (key&4)  // Очень странно константа определена по-другому
        {
        delta/=120;
        bool sign=0;
        if (delta<0)
            delta=-delta,sign=true;
        double d=1;
        for (;delta>0;delta--)
            d*=SQRT2;
        if (sign)
            d=1/d;
        ScaleL(d);
        }
    else
        {
        SetMarkerPos(FMarkerL+(delta*FSclL)/120);
        int DL=(FPMaxL-FPMinL)>>1;
        FPMaxL=FMarkerL+DL;
        FPMinL=FMarkerL-DL;
        ScaleL(1);
        }
    return;
    }
else if (Mes.Msg==WM_COMMAND)
    {
    if (PopMenu->DispatchCommand((__int16)Mes.WParam))
       return;
    }
else if ((Mes.Msg==WM_MENUSELECT)&&(HavePopup))
    {
        if (PopMenu->Handle==(void*)Mes.LParam)
                {
                TMenuItem *it=PopMenu->FindItem(Mes.WParamLo,fkCommand);
                if (it)
                        {
                        (*SelectRect)();
                        (*SelectObj)();
                        FActiveObj=SelObjs[it->Tag];
                        FActiveSource=SelSrc[it->Tag];
                        CalculateGridPos(false);
                        (*SelectRect)(*FDrawMan->GetRect(DrwIndexes[it->Tag]));
                        (*SelectObj)(DrwIndexes[it->Tag]);
                        }
                else
                        {
                        (*SelectRect)();
                        (*SelectObj)();
                        FActiveObj=NULL;
                        FActiveSource=NULL;
                        }
                PostActivateObj();
                }
          else  if (!Mes.LParam)
                {
                (*SelectRect)();
                (*SelectObj)();
                FActiveObj=NULL;
                FActiveSource=NULL;
                PostActivateObj();
                }
     }
else if (Mes.Msg==CM_CHANGEVIDEOPOSITION)
    {
    if (Mes.LParam==(int)FVideoData)
        SetVideoPos(frmVideoForm->Position);
    }
TForm::WndProc(Mes);
}

void __fastcall TRoadFrm::PrBoxPaint(TObject *Sender)
{
PrepareSlopesCont();
if (FPlanKind==pkGorizontal)
        FSlopesCont->DrawTo(PrBox->Canvas,PBox->Left,0);
else
        FSlopesCont->DrawTo(PrBox->Canvas,0,PBox->Top);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PvBoxPaint(TObject *Sender)
{
PrepareDressCont();
if (FPlanKind==pkGorizontal)
        FDressCont->DrawTo(PvBox->Canvas,PBox->Left,0);
else
        FDressCont->DrawTo(PvBox->Canvas,0,PBox->Top);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SplitterMoved(TObject *Sender)
{
InvalidateBoxes();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ChangeDirection(void)
{
if (FPlanDirect==pdDirect)
    FPlanDirect=pdUndirect;
else
    FPlanDirect=pdDirect;
AlignPanels();
ShowScale();
InvalidateBoxes();
}

void __fastcall TRoadFrm::SpeedButton8Click(TObject *Sender)
{
ChangeDirection();
PostAction();
}
//---------------------------------------------------------------------------


void __fastcall TRoadFrm::SclLValSelect(TObject *Sender)
{
__int32 L=SclLVal->Text.ToInt();
ScaleL((double)FSclL/L);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ShowActiveObject(void)
{
if (FActiveObj)
    {
      TObjFrm *Frm;
      Application->CreateForm(__classid(TObjFrm), &Frm);

      Frm->BuildForm(FDictSour,FActiveSource,FActiveObj);
      Frm->Show();
    }
}

void __fastcall TRoadFrm::SpeedButton11Click(TObject *Sender)
{
ShowActiveObject();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton9Click(TObject *Sender)
{
SaveData();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton10Click(TObject *Sender)
{
ReLoadData();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton12Click(TObject *Sender)
{
if (FActiveObj)
    {
    FActiveObj->Selected=SpeedButton12->Down;
    MainForm->SendBroadCastMessage(CM_CHANGESEL,(int)FActiveObj,(int)FActiveSource);
    }
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton15Click(TObject *Sender)
{
TDtaSource *CDta=NULL;
if (SpeedButton15->Down)
    if (FEditedData)
        if (!FEditedData->ReadOnly)
            CDta=FEditedData;
MainForm->ResManager->CopyDestination=CDta;
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::KmSetChange(TObject *Sender)
{
__int32 mn=FMinL/100000;
ShowRoadPart((mn+KmSet->ItemIndex*FKmInPage)*100000,(mn+(KmSet->ItemIndex+1)*FKmInPage)*100000);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton13Click(TObject *Sender)
{
if (VisSet)
    {
    for (int i=0;i<VisSet->DataList->Count;i++)
        {
        TDtaSource *Dta=VisSet->DataList->Items[i];
        if (Dta!=MainForm->ResManager->CopyDestination)
            Dta->CopySelectedObjects(Dict);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton14Click(TObject *Sender)
{
FShowProfil=false;
if (SpeedButton14->Down)
    StartEditPoly();
else
    StopEditPoly();
PostAction();
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::RoadKeyPress(TWMKey &Key)
{
switch (Key.CharCode)                      //WM_KEYDOWN
    {
    case 13:
        {
        ShowActiveObject();
        PostAction();
        } break;
    case 46:
        {if (FEditMetric)
            DeleteActivePoint();
         else
            DeleteActiveObject(GetKeyState(VK_SHIFT)>>7);/*МИША: замена VK_LSHIFT на VK_SHIFT*/
        } break;
    case 45:
        {
        if (FEditMetric)
            InsertPoint();
         else if (GetKeyState(VK_SHIFT)>>7)  /*МИША: замена VK_LSHIFT на VK_SHIFT*/
            AddNewObject();
         else if (FCurPage==ROADMARKPAGE) // Страница с разметкой
            NewMarkLine();
         else if (FCurPage==DANGERPARTPAGE)
            AddNewObject(DANGERPARTCODE);
         else
            AddNewSign();
        } break;
    case 187: SetActivePointCode(0,1);break;
    case 189: SetActivePointCode(0,0);break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6': SetActivePointCode(2,Key.CharCode-'0'); break;
    case '7':
    case '8':
    case '9': SetActivePointCode(1,Key.CharCode-'7');break;
    case 'Q': SetActivePointCode(2,12); break;
    case 'W': SetActivePointCode(2,13); break;
    case 'E': SetActivePointCode(2,14); break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton16Click(TObject *Sender)
{
FShowProfil=!FShowProfil;
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton17Click(TObject *Sender)
{
RefreshPlan();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton18Click(TObject *Sender)
{
if (SpeedButton18->Down)
    ShowVideo(1,-1);
else
    HideVideo();
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOSOURCE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton19Click(TObject *Sender)
{
if (SpeedButton19->Down)
    ShowVideo(2,-1);
else
    HideVideo();
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOSOURCE,0,0);
}
//---------------------------------------------------------------------------


void __fastcall TRoadFrm::FormDestroy(TObject *Sender)
{
if (frmVideoForm->Data==FVideoData)
    {
    HideVideo();
    }
if (FEditMetric)
   StopEditPoly();
MainForm->ActiveRoad=NULL;
CloseRoad();
MainForm->ResManager->ReleaseDictSource(FDictSour->DictId);
if(frmSignalsInsert1) delete frmSignalsInsert1;
}
//---------------------------------------------------------------------------



void __fastcall TRoadFrm::ObjMenu_EditClick(TObject *Sender)
{
ShowActiveObject();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ObjMenu_MoveClick(TObject *Sender)
{
MoveActiveObject();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ObjMenu_DeleteClick(TObject *Sender)
{
DeleteActiveObject(true);
PostAction();
}
//---------------------------------------------------------------------------


void __fastcall TRoadFrm::ObjMenu_SignClick(TObject *Sender)
{
ChangeActiveSignCode();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N4Click(TObject *Sender)
{
int CL,CX;
FMetricData->Road->RConvertPoint(CP.x,CP.y,CL,CX);
FRelativeNull=CL;
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N5Click(TObject *Sender)
{
FRelativeNull=0;
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N7Click(TObject *Sender)
{
int CL,CX;
FMetricData->Road->RConvertPoint(CP.x,CP.y,CL,CX);
FPartMinL=CL;
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N8Click(TObject *Sender)
{
int CL,CX;
FMetricData->Road->RConvertPoint(CP.x,CP.y,CL,CX);
FPartMaxL=CL;
PBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::SpeedButton20Click(TObject *Sender)
{
FPartVisible=!FPartVisible;
PBox->Invalidate();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PageSetChange(TObject *Sender)
{
if (PageSet->ItemIndex>=0)
    {
    TDrwPageRec *Rec=dynamic_cast<TDrwPageRec *>(PageSet->Items->Objects[PageSet->ItemIndex]);
    if (Rec)
        {
        FCurPage=Rec->Id;
        RefreshPlan();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ObjMenu_MarkClick(TObject *Sender)
{
EditActiveMarkParams();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::ObjMenu_ContinueMarkClick(TObject *Sender)
{
ContinueMarkLine();
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N9Click(TObject *Sender)
{
ShowParam();
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key){
     case 191:
        if(SpeedButton14->Enabled){
           SpeedButton14->Down = !SpeedButton14->Down;
           SpeedButton14->Click();
        }
     break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::N10Click(TObject *Sender)
{
ShowVisPlan();   
}
//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PvisBoxPaint(TObject *Sender)
{
PrepareVisCont();
int dl;
if (FPlanKind==pkGorizontal) {
        FVisCont->DrawTo(PvisBox->Canvas,PBox->Left,0);
        dl=PBox->Left;
} else {
        FVisCont->DrawTo(PvisBox->Canvas,0,PBox->Top);
        dl=PBox->Top;
}
DrawMarker(PvisBox,dl);
}

//---------------------------------------------------------------------------

void __fastcall TRoadFrm::PvisBoxMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (VisSet->MetricSource) {
       TRoadPoint P;
       if (FPlanKind==pkGorizontal)
          FDrawMan->Road->RConvertPoint(X-PBox->Left,Y,P.L,P.X);
       else
          FDrawMan->Road->RConvertPoint(X,Y-PBox->Top,P.L,P.X);
       int dir,len;
       TRect orect(PvisBox->Left,PvisBox->Top,PvisBox->Left+PvisBox->Width,PvisBox->Top+PvisBox->Height);
       FDrawMan->GetVisModeParam(&orect,PlanKind,PlanDirect,X,Y,dir,len);
       if (!(((GetKeyState('A')&0x0100) && dir==roDirect) || ((GetKeyState('Z')&0x0100) && dir==roUnDirect)))
         return;       
       int ind=-1;
       P.L=(int)(P.L/FDrawMan->VisModeLength)*FDrawMan->VisModeLength;
       TDangerVisMode *A=dynamic_cast<TDangerVisMode*>(VisSet->MetricSource->FindNext(VISMODECODE,P.L,P.L+FDrawMan->VisModeLength-1,ind));
       while (A && A->Direction!=dir) {
          ind++;
          A=dynamic_cast<TDangerVisMode*>(VisSet->MetricSource->FindNext(VISMODECODE,P.L,P.L+FDrawMan->VisModeLength-1,ind));
       }
       if (A) {
         if (len>0) {
            A->Length=len;
            MainForm->SendBroadCastMessage(CM_UPDATEOBJ,(int)A,(int)VisSet->MetricSource);
         } else {
            VisSet->MetricSource->DeleteObject(A);
            MainForm->SendBroadCastMessage(CM_REMOVEOBJ,(int)A,(int)VisSet->MetricSource);            
         }
       } else {
            if (len>0) {
               A=(TDangerVisMode*)MainForm->Factory->CreateRoadObj("TDangerVisMode",0,VISMODECODE);
               A->Length=len;
               int lmin=(P.L/FDrawMan->VisModeLength)*FDrawMan->VisModeLength;
               A->PutPosition(lmin,lmin+FDrawMan->VisModeLength);
               A->Direction=(TRoadDirection)dir;
               A->DrwClassId=Dict->SelectDrwParam(A,FCurPage);
               VisSet->MetricSource->AddRoadObject(A);
               MainForm->SendBroadCastMessage(CM_INSERTOBJ,(int)A,(int)VisSet->MetricSource);
            }
       }
    }


    
}
//---------------------------------------------------------------------------

