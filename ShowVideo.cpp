//---------------------------------------------------------------------------
#include <vcl.h>
#include "Math.hpp"
#include <dir.h>
#pragma hdrstop

#include "ShowVideo.h"
#include "MainUnit.h"
#include "GeomControls.h"
#include "EditGeomParams.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmShowVideo *frmShowVideo;
bool FindFirst(TADODataSet, AnsiString);
AnsiString Replace(AnsiString, AnsiString, AnsiString);
bool FirstTime;
//---------------------------------------------------------------------------
__fastcall TfrmShowVideo::TfrmShowVideo(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::cmdPlayClick(TObject *Sender)
{
    if(txtDistRoadChanged)
    {
        this->StartPos = Replace(txtDistRoad->Text,",",".").ToInt();
        if(!this->InitVideo()) return;
        txtDistRoadChanged = false;
    }
    Timer1->Interval = 500;
    MPlayer->Play();
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::cmdPauseClick(TObject *Sender)
{
    MPlayer->Pause();
    if(MPlayer->Mode == mpPlaying)
    {
        Timer1->Interval = 500;
    }
    else
    {
        Timer1->Interval = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowVideo::cmdStopClick(TObject *Sender)
{
    Timer1->Interval = 0;
    MPlayer->Stop();
}
//---------------------------------------------------------------------------

bool FindFirst(TADODataSet *DS, AnsiString Filter)
{
    bool RValue = false;
    DS->Filtered = false;
    DS->Filter = Filter;
    DS->Filtered = true;
    if(DS->RecordCount > 0)
    {
        RValue = true;
        TBookmark SavePlace;
        SavePlace = DS->GetBookmark();
        DS->Filtered = false;
        DS->GotoBookmark(SavePlace);
        DS->FreeBookmark(SavePlace);
    }
    else
    {
        DS->Filtered = false;
    }
    return RValue;
}

bool TfrmShowVideo::InitVideo()
{
    if(frmShowVideo->ID_Road!=0)//если указана дорога
    {
        DSRepers->Active = false;
        DSRepers->CommandText = "select * from ListRoads where id_ = " + AnsiString(ID_Road);
        DSRepers->Active = true;
        RoadStartPos = DSRepers->FieldByName("StartPos")->AsFloat;
        RoadEndPos = DSRepers->FieldByName("EndPos")->AsFloat;
        AnsiString MyCaption = DSRepers->FieldByName("FullTitle")->AsString.Trim();
        ScrollBar1->Min = 0;
        ScrollBar1->Max = RoadEndPos - RoadStartPos;
        AnsiString Orders = "";
        AnsiString Znak = "";
        if(Direction == 1)
        {
            Orders = " order by PosOfInv";
            Znak = ">=";
            MyCaption += " (прямо)";
        }
        else
        {
            Orders = " order by PosOfInv desc";
            Znak = "<=";
            MyCaption += " (обратно)";
        }
        Caption = MyCaption;
        DSRepers->Active = false;
        DSRepers->CommandText = "select * from vi_points where id_road = " + AnsiString(ID_Road) + " and NumDataSource = "+ AnsiString(DataSource) +" and direction = " + AnsiString(Direction) + Orders;
        DSRepers->Active = true;
        this->txtDistRoad->Text = AnsiString(StartPos);
        txtDistRoadChanged = false;
        if(FindFirst(DSRepers, "posOfInv " + Znak + AnsiString(StartPos)))
        {
            ID_High = DSRepers->FieldByName("id_high")->AsInteger;
            AnsiString FileName = GetPathToVideo();
            if(!FileExists(FileName))
            {
                ShowMessage("Ошибка!!!\nФайл по указанному пути не найден\n"+ FileName);
                this->Hide();
                return false;
            }
            MPlayer->FileName = FileName;
            MPlayer->Open();
            MPlayer->TimeFormat = tfMilliseconds;
            int s = MPlayer->Length;
            MPlayer->DisplayRect = Panel1->ClientRect;
//это для продольных и поперечных уклонов и радиусов
            DSGeomParams->Active = false;
            DSGeomParams->CommandText = "if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[RoadGeometry]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)\
                                            Begin\
                                                select * from RoadGeometry where NumRoad = " + AnsiString(ID_Road) + " and NumDataSource = " + AnsiString(DataSource) + " order by Displacement\
                                            End\
                                            Else\
                                            Begin\
                                                	create table #t_s_t (a int) select * from #t_s_t drop table #t_s_t \
                                            End";

            DSGeomParams->Active = true;
//
//это для обработанных данных
            DSGeomConers->Active = false;
            DSGeomConers->CommandText = "select lrp.id_, lrp.NumPartType, lrp.NumRoad, lrp.Reference, lrp.StartPos, lrp.EndPos, lrp.Value2, lrp.NumDataSource, c.FullTitle \
                                            from ListRoadParts lrp \
                                            join Classifier c on lrp.Reference = c.id_ \
                                            where NumPartType = 34 and \
                                            NumRoad = " + AnsiString(ID_Road) + " and NumDataSource = " + AnsiString(DataSource) + " order by StartPos";
            DSGeomConers->Active = true;
//
            SetVideoPosition();
        }
        else
        {
            ShowMessage("Для указанного участка ничего не найдено");
            this->Hide();
            return false;
        }
    }
    else
    {
        ShowMessage("Дорога не указана");
        this->Hide();
        return false;
    }
    this->Show();
    return true;
}

AnsiString TfrmShowVideo::GetPathToVideo()
{
    DSTemp->Active = false;
    DSTemp->CommandText = "select rtrim(pathToVideo) as pathToVideo from v_high where id_high = " + AnsiString(ID_High);
    DSTemp->Active = true;
    return DSTemp->FieldByName("pathToVideo")->AsString; 
}

bool TfrmShowVideo::SetVideoPosition()
{
    DSDistTime->Active = false;
    DSDistTime->CommandText = "select * from v_TimeDist where id_high = " + AnsiString(ID_High) + " order by Times";
    DSDistTime->Active = true;
    double LastPosOfSVPD = DSRepers->FieldByName("PosOfSVPD")->AsFloat;
    double LastPosOfInv  = DSRepers->FieldByName("PosOfInv")->AsFloat;
    LastReperPosOfInv = LastPosOfInv;
    LastReperPosOfSVPD = LastPosOfSVPD;
    DSRepers->Prior();
    double StartPosOfSVPD;
    if(!DSRepers->Bof)
    {
        FirstReperPosOfInv = DSRepers->FieldByName("PosOfInv")->AsFloat;
        FirstReperPosOfSVPD = DSRepers->FieldByName("PosOfSVPD")->AsFloat;
        Koff = (LastReperPosOfInv - FirstReperPosOfInv)/(LastReperPosOfSVPD - FirstReperPosOfSVPD);
        StartPosOfSVPD = (StartPos - FirstReperPosOfInv)/Koff + FirstReperPosOfSVPD;
    }
    else
    {
        FirstReperPosOfInv = StartPos - 20;
        FirstReperPosOfSVPD = StartPos - LastReperPosOfInv + LastReperPosOfSVPD - 20;
        Koff = 1;
        StartPosOfSVPD = (StartPos - LastReperPosOfInv)/Koff + LastReperPosOfSVPD;
    }
//    double StartPosOfSVPD = (StartPos - FirstReperPosOfInv)/Koff + FirstReperPosOfSVPD;
    DSRepers->Next();
    if(FindFirst(DSDistTime, "Distance > " + Replace(AnsiString(StartPosOfSVPD), ",", ".")))
    {
        DSDistTime->Prior();
        MPlayer->Position = DSDistTime->FieldByName("Times")->AsFloat*1000;
        FirstTime = true;
//        cmdPlayClick(NULL);
    }

}

AnsiString Replace(AnsiString str, AnsiString FindStr, AnsiString ReplaceStr)
{
    int PosOfComma = str.Pos(FindStr);
    while(PosOfComma!=0)
    {
        str = str.SubString(0, PosOfComma - 1) + ReplaceStr + str.SubString(PosOfComma + 1, str.Length());
        PosOfComma = str.Pos(FindStr);
    }
    return str;
}


void __fastcall TfrmShowVideo::Timer1Timer(TObject *Sender)
{
    double CurrVideoTime = MPlayer->Position;
    CurrVideoTime = double(CurrVideoTime) / 1000.00;
    if(FindFirst(DSDistTime, "Times > " + Replace(AnsiString(CurrVideoTime), ",", ".")))
    {
        double NextSVPDDist = DSDistTime->FieldByName("Distance")->AsFloat;
        double NextSVPDTime = DSDistTime->FieldByName("Times")->AsFloat;
        DSDistTime->Prior();
        double PrevSVPDDist = DSDistTime->FieldByName("Distance")->AsFloat;
        double PrevSVPDTime = DSDistTime->FieldByName("Times")->AsFloat;
        double CurrPosOfSVPD = DSDistTime->FieldByName("Distance")->AsFloat;
        txtHighDist->Text = AnsiString(RoundTo(DSDistTime->FieldByName("Distance")->AsFloat,-2));
        txtSpeed->Text = AnsiString(RoundTo((NextSVPDDist - PrevSVPDDist)*3.6/(NextSVPDTime - PrevSVPDTime),-2));

        if(CurrPosOfSVPD < FirstReperPosOfSVPD || CurrPosOfSVPD >= LastReperPosOfSVPD)
        {
            DSRepers->Next();
            if(!DSRepers->Eof)
            {
                if(ID_High == DSRepers->FieldByName("id_high")->AsInteger)
                {
                    FirstReperPosOfSVPD = LastReperPosOfSVPD;
                    FirstReperPosOfInv = LastReperPosOfInv;
                    LastReperPosOfSVPD = DSRepers->FieldByName("posOfSVPD")->AsFloat;
                    LastReperPosOfInv = DSRepers->FieldByName("posOfInv")->AsFloat;
                    Koff = (LastReperPosOfInv - FirstReperPosOfInv)/(LastReperPosOfSVPD - FirstReperPosOfSVPD);
                }
                else
                {
                    ID_High = DSRepers->FieldByName("id_high")->AsInteger;
                    cmdStopClick(NULL);
                    FirstReperPosOfInv = DSRepers->FieldByName("posOfInv")->AsFloat;
                    FirstReperPosOfSVPD = DSRepers->FieldByName("posOfSVPD")->AsFloat;
                    DSRepers->Next();
                    LastReperPosOfInv = DSRepers->FieldByName("posOfInv")->AsFloat;
                    LastReperPosOfSVPD = DSRepers->FieldByName("posOfSVPD")->AsFloat;

                    AnsiString FileName = GetPathToVideo();
                    if(!FileExists(FileName))
                    {
                        ShowMessage("Ошибка!!!\nФайл по указанному пути не найден\n"+ FileName);
                        return;
                    }
                    MPlayer->FileName = FileName;
                    MPlayer->Open();
                    MPlayer->TimeFormat = tfMilliseconds;
                    MPlayer->DisplayRect = Panel1->ClientRect;

                    DSDistTime->Active = false;
                    DSDistTime->CommandText = "select * from v_TimeDist where id_high = " + AnsiString(ID_High) + " order by Times";
                    DSDistTime->Active = true;

                    if(FindFirst(DSDistTime, "Distance > " + Replace(AnsiString(FirstReperPosOfSVPD), ",", ".")))
                    {
//                       DSDistTime->Prior();
                        MPlayer->StartPos = DSDistTime->FieldByName("Times")->AsFloat*1000;
                        cmdPlayClick(NULL);
                    }
                    else
                    {
                        ShowMessage("Ошибка");
                    }
                    return;
                }
            }
            else
            {
                cmdStopClick(NULL);
            }
        }
        double CurrPos = RoundTo((CurrPosOfSVPD - FirstReperPosOfSVPD) * Koff + FirstReperPosOfInv,-2);
        txtDistRoad->Text = CurrPos;
        ScrollBar1->Position = (int)CurrPos - RoadStartPos;
        MainForm->SetVideoPos(CurrPos);
//это для уклонов
        if(DSGeomParams->RecordCount == 0 || \
            !(FindFirst(DSGeomParams, "Displacement >= " + AnsiString((int)CurrPos))) )
        {
            for(int i = 0; i < ssSizeOfDasData; i++)
            {
                if(GeomControls[i].ssVisible)
                {
                    TComponent* GeomComponent = this->FindComponent("txt" + GeomControls[i].ssName);
                    if(GeomComponent)
                        ((TEdit*)GeomComponent)->Text = "Нет данных";
                }
            }
        }
        else
        {
            for(int i = 0; i < ssSizeOfDasData; i++)
            {
                if(GeomControls[i].ssVisible)
                {
                    TComponent* GeomComponent = this->FindComponent("txt" + GeomControls[i].ssName);
                    if(GeomComponent)
                    {
                        if(!GeomControls[i].ssField.IsEmpty() && DSGeomParams->FieldList->Find(GeomControls[i].ssField)!=NULL)
                            ((TEdit*)GeomComponent)->Text = DSGeomParams->FieldByName(GeomControls[i].ssField)->AsString;
                        else
                            ((TEdit*)GeomComponent)->Text = "Нет данных";
                    }

                }
            }
        }
//
//это для поворотов
        if(DSGeomConers->RecordCount == 0 || \
            !(FindFirst(DSGeomConers, "StartPos <= "+AnsiString((int)CurrPos)+" and EndPos > "+AnsiString((int)CurrPos))) )
        {
            for(int i = ssSizeOfDasData; i < ssSizeOf; i++)
            {
                if(GeomControls[i].ssVisible)
                {
                    TComponent* GeomComponent = this->FindComponent("txt" + GeomControls[i].ssName);
                    if(GeomComponent)
                        ((TEdit*)GeomComponent)->Text = "Нет данных";
                }
            }
        }
        else
        {
            for(int i = ssSizeOfDasData; i < ssSizeOf; i++)
            {
                if(GeomControls[i].ssVisible)
                {
                    TComponent* GeomComponent = this->FindComponent("txt" + GeomControls[i].ssName);
                    if(GeomComponent)
                    {
                        if(!GeomControls[i].ssField.IsEmpty() && DSGeomConers->FieldList->Find(GeomControls[i].ssField)!=NULL)
                            ((TEdit*)GeomComponent)->Text = DSGeomConers->FieldByName(GeomControls[i].ssField)->AsString;
                        else
                            ((TEdit*)GeomComponent)->Text = "Нет данных";
                    }

                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::txtDistRoadChange(TObject *Sender)
{
    if(MPlayer->Mode != mpPlaying)
    {
        txtDistRoadChanged = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::ScrollBar1Change(TObject *Sender)
{
    if(MPlayer->Mode != mpPlaying)
    {
        txtDistRoad->Text = ScrollBar1->Position + RoadStartPos;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::FormHide(TObject *Sender)
{
    Timer1->Interval = 0;
    if(frmEditGeomData->Showing) frmEditGeomData->Hide();    
}
//---------------------------------------------------------------------------



void __fastcall TfrmShowVideo::Panel1Resize(TObject *Sender)
{
    MPlayer->DisplayRect = Panel1->ClientRect;
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::N1Click(TObject *Sender)
{
    if(frmGeomControls->ShowModal() == mrOk)
    {
        int iForSize = 0;
        SetFormSize(Label3->Top + 30 + 19 * ssSizeOf + 30, this->Width);        
        for(int i = 0; i < ssSizeOf; i++)
        {
            DeleteGeoControl(GeomControls[i].ssName);
            if(GeomControls[i].ssVisible)
            {
                CreateGeoControl(GeomControls[i].ssName, GeomControls[i].ssCaption, Label3->Left, Label3->Top + 30 + 19 * iForSize);
                iForSize++;
            }
        }
        SetFormSize(Label3->Top + 30 + 19 * iForSize + 30, this->Width);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowVideo::OptionsGeoControls(TObject *Sender)
{
//
/*LongSlope - среднее значение продольного уклона (к прямому напр.)
RightLongSlope - значение продольного уклона в пр.
LeftLongSlope - значение продольного уклона в обр.
RightSlope - значение поперчного уклона в пр.
LeftSlope  - значение поперчного уклона в обр.
*/
    ssSizeOf = 11;
    GeomControls = new Geom_Controls[ssSizeOf];

    GeomControls[0].ssCaption = "Усредненный продольный уклон (прив. к пр.)";
    GeomControls[0].ssName = "ProdSlope";
    GeomControls[0].ssVisible = false;
    GeomControls[0].ssField = "LongSlope";

    GeomControls[1].ssCaption = "Продольный уклон (прямой заезд)";
    GeomControls[1].ssName = "ProdSlope_F";
    GeomControls[1].ssVisible = false;
    GeomControls[1].ssField = "RightLongSlope";
    //

    GeomControls[2].ssCaption = "Продольный уклон (обратный заезд)";
    GeomControls[2].ssName = "ProdSlope_R";
    GeomControls[2].ssVisible = false;
    GeomControls[2].ssField = "LeftLongSlope";

    GeomControls[3].ssCaption = "Поперечный уклон (прямой заезд)";
    GeomControls[3].ssName = "PopSlope_F";
    GeomControls[3].ssVisible = false;
    GeomControls[3].ssField = "RightSlope";
    //rigthSlope

    GeomControls[4].ssCaption = "Поперечный уклон (обратный заезд)";
    GeomControls[4].ssName = "PopSlope_R";
    GeomControls[4].ssVisible = false;
    GeomControls[4].ssField = "LeftSlope";
    //leftslope

    GeomControls[5].ssCaption = "Радиус поворота (прямой заезд)";
    GeomControls[5].ssName = "Radius_F";
    GeomControls[5].ssVisible = false;
    GeomControls[5].ssField = "RightRadius";

    GeomControls[6].ssCaption = "Радиус поворота (обратный заезд)";
    GeomControls[6].ssName = "Radius_R";
    GeomControls[6].ssVisible = false;
    GeomControls[6].ssField = "LeftRadius";

    this->ssSizeOfDasData = 7;

    GeomControls[7].ssCaption = "Начало участка";
    GeomControls[7].ssName = "lcStartPos";
    GeomControls[7].ssVisible = false;
    GeomControls[7].ssField = "StartPos";

    GeomControls[8].ssCaption = "Конец участка";
    GeomControls[8].ssName = "EndPos";
    GeomControls[8].ssVisible = false;
    GeomControls[8].ssField = "EndPos";

    GeomControls[9].ssCaption = "Тип участка";
    GeomControls[9].ssName = "Type";
    GeomControls[9].ssVisible = false;
    GeomControls[9].ssField = "FullTitle";

    GeomControls[10].ssCaption = "Радиус поворота";
    GeomControls[10].ssName = "Radius";
    GeomControls[10].ssVisible = false;
    GeomControls[10].ssField = "Value2";

    this->ssSizeOfConers = 4;

    SetFormSize(Label3->Top + 30 + 19 * ssSizeOf + 30, this->Width);

    int iForSize = 0;
    for(int i = 0; i < ssSizeOf; i++)
    {
        DeleteGeoControl(GeomControls[i].ssName);
        if(GeomControls[i].ssVisible)
        {
            CreateGeoControl(GeomControls[i].ssName, GeomControls[i].ssCaption, Label3->Left, Label3->Top + 30 + 19 * iForSize);
            iForSize++;
        }
    }
    SetFormSize(Label3->Top + 30 + 19 * iForSize + 30, this->Width);
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::CreateGeoControl(AnsiString ControlName, AnsiString ControlCaption, int ControlX, int ControlY)
{
//
    TLabel* NewLabel = new TLabel(this);
    NewLabel->Visible = true;
    NewLabel->Parent = this;
    NewLabel->Left = ControlX;
    NewLabel->Top = ControlY;
    NewLabel->Name = "lbl" + ControlName;
    NewLabel->Caption = ControlCaption;
    NewLabel->Anchors = Label1->Anchors;

    TEdit* NewEdit = new TEdit(this);
    NewEdit->Visible = true;
    NewEdit->Parent = this;
    NewEdit->Left = 206;
    NewEdit->Top = ControlY;
    NewEdit->Name = "txt" + ControlName;
    NewEdit->Width = 229;
    NewEdit->Height = 21;
    NewEdit->Anchors = Label1->Anchors;
    NewEdit->Font = txtSpeed->Font;
    NewEdit->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowVideo::DeleteGeoControl(AnsiString ControlName)
{
//
    TComponent* GeomComponent = this->FindComponent("lbl" + ControlName);
    if(GeomComponent) delete GeomComponent;
    GeomComponent = this->FindComponent("txt" + ControlName);
    if(GeomComponent) delete GeomComponent;
}

//---------------------------------------------------------------------------
void __fastcall TfrmShowVideo::FormCreate(TObject *Sender)
{
    OptionsGeoControls(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::SetFormSize(int frmHeight, int frmWidth)
{
//
    TAnchors* TA = new TAnchors[ControlCount];
    for(int i = 0; i < this->ControlCount; i++)
    {
        TA[i] = Controls[i]->Anchors;
        Controls[i]->Anchors.Clear();
        Controls[i]->Anchors << akTop << akLeft;
    }
    this->Height = frmHeight;
    this->Width = frmWidth;
    for(int i = 0; i < this->ControlCount; i++)
    {
        Controls[i]->Anchors.Clear();
        Controls[i]->Anchors = TA[i];
    }
    delete[] TA;
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    delete this->GeomControls;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmShowVideo::mnuEditGeomParamsClick(TObject *Sender)
{
    frmEditGeomData->Show();    
}
//---------------------------------------------------------------------------


void __fastcall TfrmShowVideo::DSGeomConersAfterScroll(TDataSet *DataSet)
{
    if(frmEditGeomData->Showing)
    {
        frmEditGeomData->UpdateTXTControls(NULL);
    }
}
//---------------------------------------------------------------------------

