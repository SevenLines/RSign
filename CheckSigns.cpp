//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckSigns.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCheckSigns *frmCheckSigns;
//---------------------------------------------------------------------------
__fastcall TfrmCheckSigns::TfrmCheckSigns(TComponent* Owner)
    : TForm(Owner)
{
}

//***************************************************************************
//***������� ���������*******************************************************
//***************************************************************************

//---------------------------------------------------------------------------
void __fastcall TfrmCheckSigns::FormShow(TObject *Sender)
{
    this->SetCurrentActiveRoad(MainForm->ActiveRoad);

    // ������� � ������ ��� �����, ������� ����� ������������
    KnownSignsList = new TStringList();
    //***
    KnownSignsList->Add("1.1");
    KnownSignsList->Add("1.2");
    KnownSignsList->Add("1.3.1");
    KnownSignsList->Add("1.3.2");
    KnownSignsList->Add("1.4.1");
    KnownSignsList->Add("1.4.2");
    KnownSignsList->Add("1.4.3");
    KnownSignsList->Add("1.4.4");
    KnownSignsList->Add("1.4.5");
    KnownSignsList->Add("1.4.6");
    //***
    KnownSignsList->Add("2.3.1");
    KnownSignsList->Add("2.3.2");
    KnownSignsList->Add("2.3.3");
    KnownSignsList->Add("2.4");
    //***
    KnownSignsList->Add("3.11");
    KnownSignsList->Add("3.12");
    //***
    //***
    KnownSignsList->Add("5.22");
    KnownSignsList->Add("5.23");
    KnownSignsList->Add("5.24");
    KnownSignsList->Add("5.25");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCheckSigns::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    delete KnownSignsList;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCheckSigns::btnCloseClick(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
// ������� � ���������� ����� �� ������
void __fastcall TfrmCheckSigns::btnGoToNextClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString SignTitle = "";
        AnsiString SignPlace = "";
        AnsiString SignDescription = "";

        __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
        for(__int32 i = (this->CurrentSign + 1); i < RoadObjectsCount; i++)
        {
            //IsFound = false;
            TRoadSign *sign = dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
            if(sign)
            {
                //AnsiString SignName = this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign);
                SignTitle  = this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign);
                if(SignTitle.Length() > 0)
                {
                    switch(SignTitle[1])
                    {
                        case '1':
                            if(SignsList->Checked[0])// ���������������
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '2':
                            if(SignsList->Checked[1])// ����������
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '3':
                            if(SignsList->Checked[2])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '4':
                            if(SignsList->Checked[3])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '5':
                            if(SignsList->Checked[4])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '6':
                            if(SignsList->Checked[5])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '7':
                            if(SignsList->Checked[6])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }


            if(IsFound)
            {
                // ���� ����� ����, �� ������� �� ����� � ���������� ����� �����
                this->CurrentSign = i;
                SignPlace = sign->L;

                this->CurrentActiveRoad->SetVideoPos(sign->L/100);
                break;
            }
        }

        // ������� ���������� �� �����
        this->ShowCurrentSignInfo(SignTitle, SignPlace);
        this->ShowCurrentSignDescription(SignDescription);

        if(!IsFound)
        {
            // ���� ��������� ���� ���� � �� ����� �� ���� ������, ����������� ������ Next � End
            this->CurrentSign = RoadObjectsCount;
            this->ShowCurrentSignInfo("<< ����� ������ >>", "<< ����� ������ >>");
            this->ShowCurrentSignDescription("");
        }
    }
}
//---------------------------------------------------------------------------
// ������� � ����������� ����� �� ������
void __fastcall TfrmCheckSigns::btnGoToPrevClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString SignTitle = "";
        AnsiString SignPlace = "";
        AnsiString SignDescription = "";

        __int32 RoadObjectsCount = -1;
        for(__int32 i = (this->CurrentSign - 1); i > RoadObjectsCount; i--)
        {
            TRoadSign* sign = dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
            if(sign)
            {
                //AnsiString SignName = this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign);
                SignTitle  = this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign);
                if(SignTitle.Length() > 0)
                {
                    switch(SignTitle[1])
                    {
                        case '1':
                            if(SignsList->Checked[0])// ���������������
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '2':
                            if(SignsList->Checked[1])// ����������
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '3':
                            if(SignsList->Checked[2])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '4':
                            if(SignsList->Checked[3])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '5':
                            if(SignsList->Checked[4])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '6':
                            if(SignsList->Checked[5])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '7':
                            if(SignsList->Checked[6])//
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }


            if(IsFound)
            {
                // ���� ����� ����, �� ������� �� ����� � ���������� ����� �����
                this->CurrentSign = i;
                SignPlace = sign->L;

                this->CurrentActiveRoad->SetVideoPos(sign->L/100);
                break;
            }
        }

        // ������� ���������� �� �����
        this->ShowCurrentSignInfo(SignTitle, SignPlace);
        this->ShowCurrentSignDescription(SignDescription);

        if(!IsFound)
        {
            // ���� ��������� ���� ���� � �� ����� �� ���� ������, ����������� ������ Next � End
            this->CurrentSign = RoadObjectsCount;
            this->ShowCurrentSignInfo("<< ������ ������ >>", "<< ������ ������ >>");
            this->ShowCurrentSignDescription("");
        }
    }
}
//---------------------------------------------------------------------------
// ��������� � ����� ������
void __fastcall TfrmCheckSigns::btnGoToEndClick(TObject *Sender)
{
    this->ShowCurrentSignInfo("<< ����� ������ >>", "<< ����� ������ >>");
    if(this->CheckCurrentActiveRoad())
        this->CurrentSign = this->CurrentActiveRoad->EditedData->Objects->Count;
}
//---------------------------------------------------------------------------
// ��������� � ������ ������
void __fastcall TfrmCheckSigns::btnGoToBeginClick(TObject *Sender)
{
    this->ShowCurrentSignInfo("<< ������ ������ >>", "<< ������ ������ >>");
    this->CurrentSign = -1;
}
//---------------------------------------------------------------------------

//***************************************************************************
//***��������������� �������*************************************************
//***************************************************************************

//---------------------------------------------------------------------------
bool __fastcall TfrmCheckSigns::CheckCurrentActiveRoad()
{
    if(MainForm->ActiveRoad)
    {// ���� ���� ��������� ������
        if(MainForm->ActiveRoad == this->CurrentActiveRoad)
        {// ���� ������ �� ����������
            return true;
        }
        else
        {// ���� ������ ���������
            if(MessageBox(NULL, "��������� ������� ������. ������� ������� ������?", "������ ����������� ������", MB_YESNO) == IDYES)
            {// ������ ������� ������
                SetCurrentActiveRoad(MainForm->ActiveRoad);
                return true;
            }
            else
            {// ��������� ������� ������
                ShowMessage("��� ����������� �������� ������� ������ ��������.");
                return false;
            }
        }
    }
    else
    {// ���� ��� ��������� ������
        ShowMessage("���������� ����������� ������ ����������, �.�. �� ������� �� ���� ������. ��� ����������� �������� ������.");
        return false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCheckSigns::SetCurrentActiveRoad(TRoadFrm *NewActiveRoad)
{
    this->CurrentActiveRoad = NewActiveRoad;
    this->CurrentSign = -1;
    if(this->CurrentActiveRoad)
        lblCurrentRoadTitle->Caption = Trim(this->CurrentActiveRoad->RoadName);
    else
        lblCurrentRoadTitle->Caption = "<<������ �� �������>>";

    //this->ShowCurrentSignInfo("", "");
    this->ShowCurrentSignInfo("<< ������ ������ >>", "<< ������ ������ >>");
}
//---------------------------------------------------------------------------
// ������� ���������� � ������� �����
void __fastcall TfrmCheckSigns::ShowCurrentSignInfo(AnsiString Title, AnsiString Place)
{
    lblCurrentSignTitle->Caption = Title;
    lblCurrentSignPlace->Caption = Place;
}
//---------------------------------------------------------------------------
// ������� �������� �������� �� �������� �����
void __fastcall TfrmCheckSigns::ShowCurrentSignDescription(AnsiString Description)
{
    lblCurrentSignDescription->Caption = Description;
}
//---------------------------------------------------------------------------

//***************************************************************************
//***��������������� ������� ��� �������� ����������� ������*****************
//***************************************************************************

//---------------------------------------------------------------------------
// ���������� true, ���� ����� ��������� ���� ����
bool __fastcall TfrmCheckSigns::IsKnownSign(TRoadSign *Sign)
{
    if(Sign)
    {
        AnsiString SignName = this->CurrentActiveRoad->Dict->GetShortTitle(Sign->NumRoadSign);;
         __int32 i;
        if(KnownSignsList->Find(SignName, i))
            return true;
        /*
        // ��������������� �����
        if(SignName == "1.1")// ��������������� ������� �� ����������
            return true;

        if(SignName == "1.1")// ��������������� ������� �� ����������
            return true;

        // ����� ����������
        if(SignName == "2.3.1")// ����������� �� �������������� �������
            return true;

        // ����������� �����
        */
    }
    return false;
}

//***************************************************************************
//***������� �������� ����������� ������*************************************
//***************************************************************************
