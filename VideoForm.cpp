//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VideoForm.h"
#include "MainUnit.h"
#include "VideoBar.h"

#include <math.h>"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MediaPlayer_OCX"
#pragma resource "*.dfm"

// Команды для очереди команд


TfrmVideoForm *frmVideoForm;

//---------------------------------------------------------------------------
__fastcall TfrmVideoForm::TfrmVideoForm(TComponent* Owner)
    : TForm(Owner)
{
frmVideoBar->Align=alBottom;
frmVideoBar->Left=0;
frmVideoBar->Width=Panel4->ClientWidth;
frmVideoBar->Height=40;
frmVideoBar->Top=CalcFormHeight(ClientWidth)-40;
frmVideoBar->Parent=this;
frmVideoBar->Show();
Timer->Interval=1000;
Timer->Enabled=false;
FData=NULL;
FNumRoad=0;
FDirection=0;
CreateEdits();
Panel3->Left=(frmVideoBar->Width-Panel3->Width)/2;
Panel3->Top=cmdPlay->Height+1;
Panel3->Parent=frmVideoBar;
ScrollBar->Left=cmdPlay->Width*COLBUT;
ScrollBar->Width=frmVideoBar->Width-2*cmdPlay->Width*COLBUT;
ScrollBar->Top=0;
ScrollBar->Height=cmdPlay->Height;
ScrollBar->Parent=frmVideoBar;
for (int i=0;i<ROWBUT;i++)
    for (int j=0;j<COLBUT;j++) {
        DirBut[i][j]=new TSpeedButton(Panel1);
        DirBut[i][j]->Visible=true;
        DirBut[i][j]->Enabled=true;
        DirBut[i][j]->Width=cmdPlay->Width;
        DirBut[i][j]->Height=cmdPlay->Height;
        DirBut[i][j]->Top=cmdPlay->Top+(i)*cmdPlay->Height+1;
        DirBut[i][j]->Left=Panel1->ClientWidth-(j+1)*cmdPlay->Width;
        DirBut[i][j]->Anchors.Clear();
        DirBut[i][j]->Anchors<<akRight<<akTop;
        DirBut[i][j]->GroupIndex=2;
        DirBut[i][j]->OnClick=butVideoClick;
        DirBut[i][j]->AllowAllUp=false;
        DirBut[i][j]->Parent=frmVideoBar;
        UnDirBut[i][j]=new TSpeedButton(Panel1);
        UnDirBut[i][j]->Visible=true;
        UnDirBut[i][j]->Enabled=true;
        UnDirBut[i][j]->Width=cmdPlay->Width;
        UnDirBut[i][j]->Height=cmdPlay->Height;
        UnDirBut[i][j]->Top=cmdPlay->Top+(i)*cmdPlay->Height+1;
        UnDirBut[i][j]->Left=j*cmdPlay->Width;
        UnDirBut[i][j]->Anchors.Clear();
        UnDirBut[i][j]->Anchors<<akLeft<<akTop;
        UnDirBut[i][j]->GroupIndex=2;
        UnDirBut[i][j]->OnClick=butVideoClick;
        UnDirBut[i][j]->AllowAllUp=false;
        UnDirBut[i][j]->Parent=frmVideoBar;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::CreateEdits(void)                     
{
for (int i=0;i<VIDEOEDITCOUNT;i++)
    {
    FEdits[i]=new TEdit(Panel1);
    FEdits[i]->Visible=false;
    FEdits[i]->Parent=Panel1;
    FEdits[i]->Enabled=i==0;
    FLabels[i]=new TLabel(Panel1);
    FLabels[i]->Visible=false;
    FLabels[i]->AutoSize=true;
    FLabels[i]->Parent=Panel1;
    FLabels[i]->Caption=PopMenu->Items->Items[i]->Caption;
    VParams[i]=i==0;
    }
FEdits[8]->Width=150;
FEdits[0]->OnKeyPress=PosEditKeyPress;
FEdits[0]->OnExit=PosEditExit;
}

int __fastcall TfrmVideoForm::CalcFormHeight(int wd)
{
if (MPlayer->ImageSourceWidth)
    return Height-ClientHeight+Panel1->Height+(MPlayer->ImageSourceHeight*wd)/MPlayer->ImageSourceWidth;
else
    return Height-ClientHeight+Panel1->Height+(2*wd)/3;
}

int __fastcall TfrmVideoForm::CalcBarTop(int wd)
{
if (MPlayer->ImageSourceWidth)
    return (MPlayer->ImageSourceHeight*wd)/MPlayer->ImageSourceWidth;
else
    return (2*wd)/3;
}

void __fastcall TfrmVideoForm::AlignButtons(void) {
  for (int i=0;i<ROWBUT;i++)
     for (int j=0;j<COLBUT;j++) {
        DirBut[i][j]->Visible=false;
        UnDirBut[i][j]->Visible=false;
     }
  int height=2;
  if (Data) {
     int maxrow=0;
     int dmaxcol=0,umaxcol=0;
     for (int i=0;i<Data->DirVideoTime->Count;i++) {
        maxrow=max(maxrow,Data->DirVideoTime->Items[i]->Row);
        dmaxcol=max(dmaxcol,Data->DirVideoTime->Items[i]->Col);
     }
     for (int i=0;i<Data->UnDirVideoTime->Count;i++) {
        maxrow=max(maxrow,Data->UnDirVideoTime->Items[i]->Row);
        umaxcol=max(umaxcol,Data->UnDirVideoTime->Items[i]->Col);
     }
     maxrow=max(2,min(maxrow,ROWBUT));
     dmaxcol=min(dmaxcol,COLBUT);
     umaxcol=min(umaxcol,COLBUT);
     height+=maxrow*cmdPlay->Height;
     frmVideoBar->Height=height;
     frmVideoBar->Top=CalcBarTop(Width)-height;
     for (int i=0;i<Data->DirVideoTime->Count;i++) {
        TVideoTime *T=Data->DirVideoTime->Items[i];
        if (T->Row>0 && T->Row<=ROWBUT && T->Col>0 && T->Col<=COLBUT) {
            DirBut[T->Row-1][T->Col-1]->Tag=i+1;
            DirBut[T->Row-1][T->Col-1]->Visible=true;
            if (T->Icon>0 && T->Icon<=ImgDirection->Count)
               ImgDirection->GetBitmap(T->Icon-1,DirBut[T->Row-1][T->Col-1]->Glyph);
            if (T->Id==Data->DirVideoId && Direction==1)
               DirBut[T->Row-1][T->Col-1]->Down=true;
        }
     }
     for (int i=0;i<Data->UnDirVideoTime->Count;i++) {
        TVideoTime *T=Data->UnDirVideoTime->Items[i];
        if (T->Row>0 && T->Row<=ROWBUT && T->Col>0 && T->Col<=COLBUT) {
            UnDirBut[T->Row-1][T->Col-1]->Tag=-(i+1);
            UnDirBut[T->Row-1][T->Col-1]->Visible=true;
            if (T->Icon>0 && T->Icon<=ImgDirection->Count)
               ImgDirection->GetBitmap(T->Icon-1,UnDirBut[T->Row-1][T->Col-1]->Glyph);
            if (T->Id==Data->UnDirVideoId && Direction==2)
               UnDirBut[T->Row-1][T->Col-1]->Down=true;
        }
     }
  }
}

void __fastcall TfrmVideoForm::AlignEdits(void)
{
int top=4;
int space=2;
int lbleft=10;
int edleft=20;
int maxwid=0;
for (int i=0;i<VIDEOEDITCOUNT;i++)
    if (VParams[i])
        if (FLabels[i]->Width>maxwid)
            maxwid=FLabels[i]->Width;

for (int i=0;i<VIDEOEDITCOUNT;i++)
    {
    if (VParams[i])
        {
        FLabels[i]->Left=lbleft;
        FLabels[i]->Top=top;
        FEdits[i]->Left=edleft+maxwid;
        FEdits[i]->Top=top;
        top+=FEdits[i]->Height+space;
        }
    FEdits[i]->Visible=VParams[i];
    FLabels[i]->Visible=VParams[i];
    }
Panel1->Height=top+space;
Height=CalcFormHeight(Width);
}

void __fastcall TfrmVideoForm::SetMenu(void)
{
for (int i=0;i<PopMenu->Items->Count;i++)
    {
    TMenuItem *it=PopMenu->Items->Items[i];
    if (it->Tag>=0)
        it->Checked=VParams[it->Tag];
    }
}

void __fastcall TfrmVideoForm::SetInterval(int val)
{
Timer->Interval=val;
}

int __fastcall TfrmVideoForm::GetInterval(void)
{
return Timer->Interval;
}

void __fastcall TfrmVideoForm::InitVideo(TDtaSource *data,int Dir)
{
CloseVideo();
FData=data;
FNumRoad=FData->Id;
FDirection=Dir;
FCurHighIndex=-1;
FStatus=0;
SetMenu();
Caption=FData->RoadName;
AlignButtons();
//MPlayer->DisplayMode=1; //Это что-то непонятное
}

void __fastcall TfrmVideoForm::CloseVideo(void)
{
FData=0;
StopVideo();
FNumRoad=0;
FDirection=0;
AlignButtons();
}

void __fastcall TfrmVideoForm::PostChangeStatus(void)
{
switch (FStatus)
    {
    case 0:cmdStop->Down=true;break;
    case 1:cmdPause->Down=true;break;
    case 2:cmdPlay->Down=true;break;
    }
}

void __fastcall TfrmVideoForm::SetVideoPosition(unsigned long pos)
{
MPlayer->CurrentPosition=(double)pos/1000;
//Caption=IntToStr(MPlayer->OpenState)+" "+IntToStr(MPlayer->PlayState);
//MPlayer->CurrentPosition=pos/40;
}

int __fastcall TfrmVideoForm::GetVideoPosition(void)
{
return MPlayer->CurrentPosition*1000;
}

void __fastcall TfrmVideoForm::CalculateTimeVal(void)
{
int CurTime=GetVideoPosition();
if ((FData)&&(FPosIndex>=0))
    {
    bool dir;
    TVideoTime *VT=0;
    if (Direction==1) {
        if (FData->DirVideoId>=0)
            VT=FData->DirVideoTime->Items[FData->DirVideoId];
        }
    else {
        if (FData->UnDirVideoId>=0)
           VT=FData->UnDirVideoTime->Items[FData->UnDirVideoId];
    }
 if (VT) {
    TVideoTimeVal *Values=VT->Values;
    int n=VT->Count-1;
    __int32 *L=VT->L;
    bool ArrayDec;
    int fndindex=FPosIndex-1;
    while (fndindex>=0)  // Ищем сзади от массива время неравное текущему в том же high
        {
        if (Values[fndindex].HighIndex==Values[FPosIndex].HighIndex)
            {if (Values[fndindex].Time!=Values[FPosIndex].Time)
              {ArrayDec=Values[fndindex].Time>Values[FPosIndex].Time;goto complete;}
            }
        else
            break;
        fndindex--;
        }
    fndindex=FPosIndex+1;
    while (fndindex<=n)   // Если не нашли то ищем впереди массива время неравное текущему в том же high
        {
        if (Values[fndindex].HighIndex==Values[FPosIndex].HighIndex)
            {
            if (Values[fndindex].Time!=Values[FPosIndex].Time)
                ArrayDec=Values[FPosIndex].Time>Values[fndindex].Time;
            }
        else
            break;
        fndindex++;
        }
    complete:
    Values[n].Time<Values[0].Time;
    bool TimeInc=CurTime>Values[FPosIndex].Time;
    if (TimeInc^ArrayDec) // Надо искать впереди время больше текущего и массив возрастает или если время меньше текущего и массив убывает
        {
        if (ArrayDec)     // Массив убывает
            while (FPosIndex<n)
                {
                if ((CurTime>=Values[FPosIndex+1].Time)||(FCurHighIndex!=Values[FPosIndex].HighIndex))
                    break;
                FPosIndex++;
                }
        else
            while (FPosIndex<n)
                {
                if ((CurTime<=Values[FPosIndex+1].Time)||(FCurHighIndex!=Values[FPosIndex].HighIndex))
                    break;
                FPosIndex++;
                }
        if (FPosIndex==n)
            FPosition=L[n];
        else
            {
            FPosition=L[FPosIndex];
            int dt=Values[FPosIndex+1].Time-Values[FPosIndex].Time;
            if (dt)
                FPosition+=((L[FPosIndex+1]-L[FPosIndex])*(CurTime-Values[FPosIndex].Time))/dt;
            }
        }
    else // Надо искать сзади
        {
        if (ArrayDec)
            while (FPosIndex>0)
                {
                if ((CurTime<=Values[FPosIndex-1].Time)||(FCurHighIndex!=Values[FPosIndex].HighIndex))
                    break;
                FPosIndex--;
                }
        else
            while (FPosIndex>0)
                {
                if ((CurTime>=Values[FPosIndex-1].Time)||(FCurHighIndex!=Values[FPosIndex].HighIndex))
                    break;
                FPosIndex--;
                }

        if (FPosIndex==0)
            FPosition=L[0];
        else
            {
            FPosition=L[FPosIndex];
            int dt=Values[FPosIndex-1].Time-Values[FPosIndex].Time;
            if (dt)
                FPosition+=((L[FPosIndex-1]-L[FPosIndex])*(CurTime-Values[FPosIndex].Time))/dt;
            }
        }
    if (FCurHighIndex!=Values[FPosIndex].HighIndex)
        {
        SetHighAndPosition(Values[FPosIndex]);
        CurTime=GetVideoPosition();
        }
    }
   }
if (VParams[1])
    FEdits[1]->Text=CurTime/40;
if (VParams[9])
    FEdits[9]->Text=(double)CurTime/1000;
}

String __fastcall TfrmVideoForm::FindFile(String S)
{
String Res="";
S=S.Trim();
if (FileExists(S))
    Res=S;
else if (S!="")
    {
    char *sym=S.c_str();
    while (*sym=='\\')
        sym++;
    while ((*sym>0)&&(*sym!='\\'))
        sym++;
    if (*sym)
        sym++;
    int i;
    for (i=0;i<MainForm->VideoServers->Count;i++)
        if (FileExists(MainForm->VideoServers->Strings[i]+"\\"+String(sym)))
            {
            Res=MainForm->VideoServers->Strings[i]+"\\"+String(sym);
            break;
            }
    if (i==MainForm->VideoServers->Count)
        {
        MainForm->OpenVideo->Title="Укажите местоположение файла "+ExtractFileName(S);
        if (MainForm->OpenVideo->Execute())
            {
            Res=MainForm->OpenVideo->FileName;
            }
        }
    }
return Res;
}

void __fastcall TfrmVideoForm::SetHighAndPosition(TVideoTimeVal &VT)
{
String FileName=FindFile(FData->VideoHighList->Items[VT.HighIndex]->FileName);
if (FileName!="")
    FData->VideoHighList->Items[VT.HighIndex]->FileName=FileName;
MPlayer->FileName=FileName;
SetVideoPosition(VT.Time);
FCurHighIndex=VT.HighIndex;
CStartMode=5; CPlayPos=VT.Time; // Дебильный способ справиться с ошибкой
PlayVideo();
}

void __fastcall TfrmVideoForm::SetPosition(int newpos)
{
    TVideoTimeVal Val;
    FPosIndex=0;
    if (Direction==1) {
        if (FData->DirVideoId>=0)
            FPosIndex=FData->DirVideoTime->Items[FData->DirVideoId]->GetMesValue(newpos,Val);
    } else {
        if (FData->UnDirVideoId>=0)
            FPosIndex=FData->UnDirVideoTime->Items[FData->UnDirVideoId]->GetMesValue(newpos,Val);
    }
    TVideoHigh *VH=FData->VideoHighList->Items[Val.HighIndex];
    if (Val.HighIndex!=FCurHighIndex)
        {
        FCurHighIndex=Val.HighIndex;
        MPlayer->AutoStart=false;
        String FileName=FindFile(VH->FileName);
        if (FileName!="")  {
            VH->FileName=FileName;
        }
        MPlayer->FileName=FileName;
        StartMode=5; // Дебильный способ справиться с ошибкой  при открытии файла. Дается 5 попыток
        AlignEdits();
        }
    SetVideoPosition(Val.Time);
//    SetVideoPosition(Val.Time);
    FPosition=newpos;
    SetGeometry();
    if (VParams[1])
        FEdits[1]->Text=Val.Time/40;
    if (VParams[9])
        FEdits[9]->Text=(double)Val.Time/1000;
    ScrollBar->OnChange=NULL;
    ScrollBar->SetParams(newpos/100,FData->Road->LMin/100,FData->Road->LMax/100);
    ScrollBar->OnChange=ScrollBarChange;

}

void __fastcall TfrmVideoForm::SetGeometry(void)
{
if (Data)
    {
    TGeometryVal Val;
    FData->Road->Geometry.GetMesValue(FPosition,Val);

    if (VParams[0])
        FEdits[0]->Text=(double)FPosition/100;
    if (VParams[1])
        {
/*        if (FCurHighIndex>=0)
            {
            TVideoHigh *VH=FData->VideoHighList->Items[FCurHighIndex];
            if (Direction==1)
                FEdits[1]->Text=(FPosition-VH->L[0])/100;
            else
                FEdits[1]->Text=(VH->L[VH->Count-1]-FPosition)/100;
            }
*/            
        }
    if (VParams[2])
        {
        TVideoTime *VT=0;
        if (Direction==1) {
            if (FData->DirVideoId>=0)
                VT=FData->DirVideoTime->Items[FData->DirVideoId];
        } else {
            if (FData->UnDirVideoId>=0)
                VT=FData->UnDirVideoTime->Items[FData->UnDirVideoId];
        }
        if (VT) {
        TVideoTimeVal *Values=VT->Values;
        int n=VT->Count-1;
        __int32 *L=VT->L;
        if ((FPosIndex>0)&&(FPosIndex<n))
            {
            int DL=L[FPosIndex+1]-L[FPosIndex-1];
            int DT=Values[FPosIndex+1].Time-Values[FPosIndex-1].Time;
            if (DT)
                FEdits[2]->Text=String(fabs(double((DL*360)/(DT))/10))+"км.ч";
            else
                FEdits[2]->Text="";
            }
        }
      }
    if (VParams[3])
        FEdits[3]->Text=String(Val.LongSlope);
    if (VParams[4])
        FEdits[4]->Text=String(Val.LeftSlope);
    if (VParams[5])
        FEdits[5]->Text=String(Val.RightSlope);
    if (VParams[6])
        FEdits[6]->Text=String(Val.DirectRad);
    if (VParams[7])
        FEdits[7]->Text=String(Val.UnDirectRad);
    if (VParams[8])
        {
        String S="";
        TRoadObject *Obj=FData->FindRoadPart(DANGERCURVECODE,FPosition);
        if (Obj)
            {
            TDangerCurve *Crv=dynamic_cast<TDangerCurve*>(Obj);
            if (Crv)
                {
                switch (Crv->Kind)
                    {
                    case ckLine: S="Прямая вставка";break;
                    case ckRightCurve: S="Переходная кривая правого поворота"; break;
                    case ckCircle: S="Круговая кривая";break;
                    case ckLeftCurve: S="Переходная кривая левого поворота"; break;
                    }
                }
            }
        FEdits[8]->Text=S;
        }
    }
}

void __fastcall TfrmVideoForm::PlayVideo(void)
{
MPlayer->Play();
FEdits[0]->Enabled=false;
ScrollBar->OnChange=NULL;
Timer->Enabled=true;
}

void __fastcall TfrmVideoForm::PauseVideo(void)
{
MPlayer->Pause();
Timer->Enabled=false;
FEdits[0]->Enabled=true;
ScrollBar->OnChange=ScrollBarChange;
CalculateTimeVal();
}

void __fastcall TfrmVideoForm::StopVideo(void)
{
MPlayer->Stop();
Timer->Enabled=false;
FEdits[0]->Enabled=true;
ScrollBar->OnChange=ScrollBarChange;
CalculateTimeVal();
}

void __fastcall TfrmVideoForm::WndProc(TMessage &Mes)
{
if (Mes.Msg==WM_MOUSEWHEEL)
    {
    int delta=(signed __int16)(Mes.WParamHi);
    if (Direction==1)
        SetPosition(FPosition+(delta*10)/12);
    else
        SetPosition(FPosition-(delta*10)/12);
    MainForm->SendBroadCastMessage(CM_CHANGEVIDEOPOSITION,0,(int)FData);
    return;
    }
TForm::WndProc(Mes);
}
void __fastcall TfrmVideoForm::TimerTimer(TObject *Sender)
{
CalculateTimeVal();
SetGeometry();
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOPOSITION,0,(int)FData);
}
//---------------------------------------------------------------------------


void __fastcall TfrmVideoForm::MPlayerPlayStateChange(TObject *Sender,
      long OldState, long NewState)
{
FStatus=NewState;
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOSTATUS,0,(int)FData);
PostChangeStatus();
// Дебильный способ справиться с ошибкой
if (FStatus==0 && StartMode)
   MPlayer->Play(),--StartMode;
else if (FStatus==0 && CStartMode)
   MPlayer->Play(),--CStartMode;
else if (FStatus==2 && StartMode)
   StartMode=0,MPlayer->Pause();
else if (FStatus==2 && CStartMode)
   CStartMode=0,SetVideoPosition(CPlayPos),PlayVideo();
}
//---------------------------------------------------------------------------


void __fastcall TfrmVideoForm::FormCanResize(TObject *Sender,
      int &NewWidth, int &NewHeight, bool &Resize)
{
if ((MPlayer->ImageSourceHeight!=0)&&(MPlayer->ImageSourceWidth!=0))
    NewHeight=CalcFormHeight(NewWidth);
Panel3->Left=(frmVideoBar->Width-Panel3->Width)/2;
frmVideoBar->Top=CalcBarTop(NewWidth)-frmVideoBar->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
StopVideo();
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOSOURCE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::cmdPlayClick(TObject *Sender)
{
if (cmdPlay->Down)
    PlayVideo();
else
    PauseVideo();
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::cmdStopClick(TObject *Sender)
{
if (cmdStop->Down)
    StopVideo();
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::cmdPauseClick(TObject *Sender)
{
if (cmdPause->Down)
    PauseVideo();
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::FormShow(TObject *Sender)
{
PostChangeStatus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::N1Click(TObject *Sender)
{
TMenuItem *it=dynamic_cast<TMenuItem*>(Sender);
if (it)
    {
    VParams[it->Tag]=!VParams[it->Tag];
    SetMenu();
    AlignEdits();
    SetGeometry();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::PosEditExit(TObject *Sender)
{
TEdit *Ed=dynamic_cast<TEdit*>(Sender);
if (Ed)
    {
    double pos=Ed->Text.ToDouble();
    SetPosition(pos*100);
    MainForm->SendBroadCastMessage(CM_CHANGEVIDEOPOSITION,0,(int)FData);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::PosEditKeyPress(TObject *Sender, char &Key)
{if (Key==13)
    PosEditExit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::ScrollBarChange(TObject *Sender)
{
SetPosition(ScrollBar->Position*100);
MainForm->SendBroadCastMessage(CM_CHANGEVIDEOPOSITION,0,(int)FData);
}
//---------------------------------------------------------------------------


void __fastcall TfrmVideoForm::FormResize(TObject *Sender)
{
    if (OnFormGeometryChange) {
        OnFormGeometryChange(TRect(Left, Top, Left + Width, Top + Height));
    }
    Panel3->Left=(frmVideoBar->Width-Panel3->Width)/2;
    frmVideoBar->Top=CalcBarTop(Width)-frmVideoBar->Height;
}
//---------------------------------------------------------------------------
void TfrmVideoForm::RecalculatePosition(TWMMove message)
{
    if (OnFormGeometryChange) {
        OnFormGeometryChange(TRect(Left, Top, Left + Width, Top + Height));
    }
}

void __fastcall TfrmVideoForm::butVideoClick(TObject *Sender)
{
    TSpeedButton *sb=(TSpeedButton*)Sender;
    if (sb->Tag>0) {
       Data->DirVideoId=sb->Tag-1;
       InitVideo(Data,1);
       SetPosition(Position);
       //ShowVideo();
    }
    else if (sb->Tag<0) {
       Data->UnDirVideoId=-sb->Tag-1;
       InitVideo(Data,2);
       SetPosition(Position);
       //ShowVideo();
    }
}
void __fastcall TfrmVideoForm::MPlayerMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
frmVideoBar->Visible=Y>frmVideoBar->Top;
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::Panel4MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
frmVideoBar->Visible=Y>frmVideoBar->Top;
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::Panel4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
frmVideoBar->Visible=Y>frmVideoBar->Top;
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::MPlayerMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
frmVideoBar->Visible=Y>frmVideoBar->Top;
}
//---------------------------------------------------------------------------

void __fastcall TfrmVideoForm::ItemSetTopMostClick(TObject *Sender)
{
    /*ItemSetTopMost->Checked = !ItemSetTopMost->Checked;
    this->FormStyle = ItemSetTopMost->Checked ? fsStayOnTop : fsNormal;
    PostChangeStatus(); */
}
//---------------------------------------------------------------------------

