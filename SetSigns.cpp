//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetSigns.h"
#include "MainUnit.h"
#include "SignsUtil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSetSigns *frmSetSigns;
//---------------------------------------------------------------------------
__fastcall TfrmSetSigns::TfrmSetSigns(TComponent* Owner)
    : TForm(Owner)
{
}
//***************************************************************************
//***������� ���������*******************************************************
//***************************************************************************

//---------------------------------------------------------------------------
// ������� � ���������� ������ �� ������
void __fastcall TfrmSetSigns::btnGoToNextClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString ObjectTitle = "";
        AnsiString ObjectPlace = "";

        //������� ������ ������, ������������ ��� ���������
        this->ClearCurrentObjectSignsList();

        __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
        for(__int32 i = (this->CurrentRoadObject + 1); i < RoadObjectsCount; i++)
        {
            //IsFound = false;
            if(RoadObjectsList->Checked[0])// ���� �������� ����������
            {
                TRoadAttach *attach = dynamic_cast<TRoadAttach*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(attach)
                {
                    IsFound = true;
                    ObjectTitle = "����������";
                    ObjectPlace = AnsiString(attach->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckAttachSigns(attach);
                    this->CurrentActiveRoad->SetVideoPos(attach->L/100);
                }
            }

            if(RoadObjectsList->Checked[1])// ���� �������� ��������� ������
            {
                TTown *town=dynamic_cast<TTown*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(town)
                {
                    IsFound = true;
                    ObjectTitle = "��������� �����";
                    ObjectPlace = AnsiString(town->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckTownSigns(town);
                    this->CurrentActiveRoad->SetVideoPos(town->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[2])// ���� �������� �����
            {
                TRoadBridge *bridge=dynamic_cast<TRoadBridge*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(bridge)
                {
                    IsFound = true;
                    ObjectTitle = "����";
                    ObjectPlace = AnsiString(bridge->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckBridgeSigns(bridge);
                    this->CurrentActiveRoad->SetVideoPos(bridge->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[3])// ���� �������� ���������� ���������
            {
                TBusStop *busstop=dynamic_cast<TBusStop*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(busstop)
                {
                    IsFound = true;
                    ObjectTitle = "���������� ���������";
                    ObjectPlace = AnsiString(busstop->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckBusStopSigns(busstop);
                    this->CurrentActiveRoad->SetVideoPos(busstop->L/100);
                }
            }

            if(RoadObjectsList->Checked[4])// ���� �������� �������
            {
                TRailCross *railcross=dynamic_cast<TRailCross*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(railcross)
                {
                    IsFound = true;
                    ObjectTitle = "�������";
                    ObjectPlace = AnsiString(railcross->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckRailCrossSigns(railcross);
                    this->CurrentActiveRoad->SetVideoPos(railcross->L/100);
                }
            }

            if(IsFound)
            {
                // ���� ����� ������, �� ������� �� ����� � ���������� ����� �������
                this->CurrentRoadObject = i;
                break;
            }
        }

        // ������� ���������� �� �������
        this->ShowCurrentRoadObjectInfo(ObjectTitle, ObjectPlace);

        if(!IsFound)
        {
            // ���� ��������� ���� ���� � �� ����� �� ���� ������, ����������� ������ Next � End
            this->CurrentRoadObject = RoadObjectsCount;
            this->ShowCurrentRoadObjectInfo("<< ����� ������ >>", "<< ����� ������ >>");
            this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MaxL/100);
        }
    }
}
//---------------------------------------------------------------------------
// ������� � ����� ������
void __fastcall TfrmSetSigns::btnGoToEndClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        this->ShowCurrentRoadObjectInfo("<< ����� ������ >>", "<< ����� ������ >>");
        this->CurrentRoadObject = this->CurrentActiveRoad->EditedData->Objects->Count;
        this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MaxL/100);

        //������� ������ ������, ������������ ��� ���������
        this->ClearCurrentObjectSignsList();
    }
}
//---------------------------------------------------------------------------
// ������� � ������ ������
void __fastcall TfrmSetSigns::btnGoToBeginClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        this->ShowCurrentRoadObjectInfo("<< ������ ������ >>", "<< ������ ������ >>");
        this->CurrentRoadObject = -1;
        this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MinL/100);

        //������� ������ ������, ������������ ��� ���������
        this->ClearCurrentObjectSignsList();
    }
}
//---------------------------------------------------------------------------
// ������� � ����������� ������ �� ������
void __fastcall TfrmSetSigns::btnGoToPrevClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString ObjectTitle = "";
        AnsiString ObjectPlace = "";

        //������� ������ ������, ������������ ��� ���������
        this->ClearCurrentObjectSignsList();

        __int32 RoadObjectsCount = -1;
        for(__int32 i = (this->CurrentRoadObject - 1); i > RoadObjectsCount; i--)
        {
            //IsFound = false;
            if(RoadObjectsList->Checked[0])// ���� �������� ����������
            {
                TRoadAttach *attach = dynamic_cast<TRoadAttach*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(attach)
                {
                    IsFound = true;
                    ObjectTitle = "����������";
                    ObjectPlace = AnsiString(attach->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckAttachSigns(attach);
                    this->CurrentActiveRoad->SetVideoPos(attach->L/100);
                }
            }


            if(RoadObjectsList->Checked[1])// ���� �������� ��������� ������
            {
                TTown *town = dynamic_cast<TTown*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(town)
                {
                    IsFound = true;
                    ObjectTitle = "��������� �����";
                    ObjectPlace = AnsiString(town->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckTownSigns(town);
                    this->CurrentActiveRoad->SetVideoPos(town->LMin/100);
                }
            }
            
            if(RoadObjectsList->Checked[2])// ���� �������� �����
            {
                TRoadBridge *bridge=dynamic_cast<TRoadBridge*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(bridge)
                {
                    IsFound = true;
                    ObjectTitle = "����";
                    ObjectPlace = AnsiString(bridge->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckBridgeSigns(bridge);
                    this->CurrentActiveRoad->SetVideoPos(bridge->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[3])// ���� �������� ���������� ���������
            {
                TBusStop *busstop=dynamic_cast<TBusStop*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(busstop)
                {
                    IsFound = true;
                    ObjectTitle = "���������� ���������";
                    ObjectPlace = AnsiString(busstop->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckBusStopSigns(busstop);
                    this->CurrentActiveRoad->SetVideoPos(busstop->L/100);
                }
            }

            if(RoadObjectsList->Checked[4])// ���� �������� �������
            {
                TRailCross *railcross=dynamic_cast<TRailCross*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(railcross)
                {
                    IsFound = true;
                    ObjectTitle = "�������";
                    ObjectPlace = AnsiString(railcross->L);
                    // �������� �����, ���� ����������
                    if(AutoCheck->Checked)
                        this->CheckRailCrossSigns(railcross);
                    this->CurrentActiveRoad->SetVideoPos(railcross->L/100);
                }
            }

            if(IsFound)
            {
                // ���� ����� ������, �� ������� �� ����� � ���������� ����� �������
                this->CurrentRoadObject = i;
                break;
            }
        }

        // ������� ���������� �� �������
        this->ShowCurrentRoadObjectInfo(ObjectTitle, ObjectPlace);

        if(!IsFound)
        {
            // ���� ��������� ���� ���� � �� ����� �� ���� ������, ����������� ������ Next � End
            this->CurrentRoadObject = RoadObjectsCount;
            this->ShowCurrentRoadObjectInfo("<< ������ ������ >>", "<< ������ ������ >>");
            this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MinL/100);
        }
    }
}

//---------------------------------------------------------------------------
// ��������� ����� ��� �������� �������
void __fastcall TfrmSetSigns::btnCheckSignsClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        if((this->CurrentRoadObject != -1) ||
           (this->CurrentRoadObject != this->CurrentActiveRoad->EditedData->Objects->Count))
        {
            // ��������, ��� ��� �� ������

            TRoadAttach *attach = dynamic_cast<TRoadAttach*>(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]);
            if(attach)
                this->CheckAttachSigns(attach);

            TTown* town = dynamic_cast<TTown*>(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]);
            if(town)
                this->CheckTownSigns(town);

            TRoadBridge* bridge = dynamic_cast<TRoadBridge*>(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]);
            if(bridge)
                this->CheckBridgeSigns(bridge);

            TBusStop* busstop = dynamic_cast<TBusStop*>(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]);
            if(busstop)
                this->CheckBusStopSigns(busstop);

            TRailCross* railcross = dynamic_cast<TRailCross*>(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]);
            if(railcross)
                this->CheckRailCrossSigns(railcross);
        }

    }
}

//---------------------------------------------------------------------------
// ����������� ����� ��� �������� �������
void __fastcall TfrmSetSigns::btnSetSignsClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        if((this->CurrentRoadObject != -1) ||
           (this->CurrentRoadObject != this->CurrentActiveRoad->EditedData->Objects->Count))
        {
            for(__int32 i = 0; i < CurrentObjectSignsList->Count; i++)
            {
                if(CurrentObjectSignsList->Checked[i])
                {
                    TSign *sign = (TSign*)CurrentObjectSignsList->Items->Objects[i];
                    if(sign)
                    this->CurrentActiveRoad->EditedData->AddPrjSign(
                        this->CurrentActiveRoad->Dict,
                        sign->Direction,
                        sign->Placement,
                        sign->X,
                        sign->Y,
                        sign->Name,
                        sign->Label,
                        sign->Description,
                        TSignAttach(sign->IsOnAttach));
                }
            }
        }

    }

    this->CurrentActiveRoad->EditedData->AddFromBufer();
}

//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::btnCloseClick(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::FormShow(TObject *Sender)
{
    this->SetCurrentActiveRoad(MainForm->ActiveRoad);
}

//***************************************************************************
//***��������������� �������*************************************************
//***************************************************************************

//---------------------------------------------------------------------------
bool __fastcall TfrmSetSigns::CheckCurrentActiveRoad()
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
void __fastcall TfrmSetSigns::SetCurrentActiveRoad(TRoadFrm *NewActiveRoad)
{
    this->CurrentActiveRoad = NewActiveRoad;
    this->CurrentRoadObject = -1;
    if(this->CurrentActiveRoad)
        lblCurrentRoadTitle->Caption = Trim(this->CurrentActiveRoad->RoadName);
    else
        lblCurrentRoadTitle->Caption = "<<������ �� �������>>";

    this->ShowCurrentRoadObjectInfo("","");
}

//---------------------------------------------------------------------------
// ������� ���������� � ������� �������
void __fastcall TfrmSetSigns::ShowCurrentRoadObjectInfo(AnsiString Title, AnsiString Place)
{
    lblCurrentRoadObjectTitle->Caption = Title;
    lblCurrentRoadObjectPlace->Caption = Place;
}
//---------------------------------------------------------------------------
// ������� ������ ������, ������������ ��� �����������
void __fastcall TfrmSetSigns::ClearCurrentObjectSignsList()
{
    for(__int32 i = 0; i < CurrentObjectSignsList->Count; i++)
        delete CurrentObjectSignsList->Items->Objects[i];

    CurrentObjectSignsList->Clear();
}

//***************************************************************************
//***��������������� ������� ��� �������� ����������� ������*****************
//***************************************************************************

//---------------------------------------------------------------------------
// ����� ��������� ���� (�����)
TRoadSign* __fastcall TfrmSetSigns::FindNearestSignForward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
    for(__int32 i = ++ObjectIndex; i < RoadObjectsCount; i++)
    {
        // �������� ���������� �� �������
        __int32 distance = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L - this->CurrentActiveRoad->EditedData->Objects->Items[ObjectIndex]->L;
        if(abs(distance) > Radius)
            return NULL;

        TRoadSign *sign=dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
        if(sign)
        {
            // ���� ���� ������������� �������, �� ����� ���
            //AnsiString SName = this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign);
            if((this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign) == SignName) &&
               (sign->Direction == SignDirection) &&
               (sign->Placement == SignPlacement))
                return sign;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
// ����� ��������� ���� (�����)
TRoadSign* __fastcall TfrmSetSigns::FindNearestSignBackward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    __int32 RoadObjectsCount = -1;
    for(__int32 i = --ObjectIndex; i > RoadObjectsCount; i--)
    {
        // �������� ���������� �� �������
        __int32 distance = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L - this->CurrentActiveRoad->EditedData->Objects->Items[ObjectIndex]->L;
        if(abs(distance) > Radius)
            return NULL;

        TRoadSign *sign=dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
        if(sign)
        {
            // ���� ���� ������������� �������, �� ����� ���
            if((this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign) == SignName) &&
               (sign->Direction == SignDirection) &&
               (sign->Placement == SignPlacement))
                return sign;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
// ����� ��������� ���� � ��������� "�������" ������ �������
TRoadSign* __fastcall TfrmSetSigns::FindNearestSign(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    // ��������� �����
    TRoadSign *Sign1 = this->FindNearestSignForward(ObjectIndex, SignName, SignDirection, SignPlacement, Radius);
    // ��������� �����
    TRoadSign *Sign2 = this->FindNearestSignBackward(ObjectIndex, SignName, SignDirection, SignPlacement, Radius);
    // ������� ����� �����
    if(Sign1 && !Sign2)
        return Sign1;
    if(!Sign1 && Sign2)
        return Sign2;
    if(Sign1 && Sign2)
    {
        //���������, ����� ���� �����
        __int32 dist1 = abs(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]->L - Sign1->L);
        __int32 dist2 = abs(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]->L - Sign2->L);
        if(dist1 < dist2)
            return Sign1;
        else
            return Sign2;
    }
    // ���� ����� �� ����, �� ����� ���
    return NULL;
}
//---------------------------------------------------------------------------
// ����� ���� ������ ����������� �������(�������) ������
TRoadSign* __fastcall TfrmSetSigns::FindSign(AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 L1, __int32 L2)
{
    __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
    for (__int32 i = 0; i < RoadObjectsCount; i++)
    {
        //����� ���������� ��� ��������� ������
        __int32 CurrentL = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L;
        if((CurrentL >= L1) && (CurrentL <= L2))
        {
            TRoadSign *sign = dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
            if(sign)
            {
                // ���� ���� ������������� �������, �� ����� ���
                if((this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign) == SignName) &&
                    (sign->Direction == SignDirection) &&
                    (sign->Placement == SignPlacement))
                    return sign;
            }
        }
    }
    return NULL;
}

//***************************************************************************
//***������� �������� ����������� ������*************************************
//***************************************************************************


/*
//---------------------------------------------------------------------------
// ��������/��������� ����� ��� ����������
AnsiString __fastcall TfrmSetSigns::SetAttachSigns(TRoadAttach *Attach, bool SetSign)
{
    AnsiString Description = "";
    TRoadSign *Sign;
    // �������� ��� ����������
    switch(Attach->Placement)
    {
        case apCross:// �����������
            // ���� ���� 2.3.1 (�������, ������, � �������� �����������)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.1", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.1 �� ����� ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.1 �� ����� ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                        this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.1", "", "����������� �� �������������� �������", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.1 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.1 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.1 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.1 �� ����� ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.1 �� ����� ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.1", "", "����������� �� �������������� �������", false);
            }

            // ���� ���� 2.3.1 (�����, ������, � ������ �����������)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.1", roDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.1 �� ������ ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.1 �� ������ ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                        this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.1", "", "����������� �� �������������� �������", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.1 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.1 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.1 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.1 �� ������ ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.1 �� ������ ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.1", "", "����������� �� �������������� �������", false);
            }

            // ���� ���� 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // �� ���������, ���� 3.4 �� �����
                }
                else
                {
                    // ���� 3.4 ����, �� ��� ���� ���������� �� ����������
                    Description += " ���� 2.4 ���������� ���������� �� ����������;";
                }
            }
            else
            {
                // ��� ����� 2.4 �� ����������
                Description += " ��� ����� 2.4 �� ����������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L, 2000, "2.4", "", "������ ������", true);
            }

            // ���� ���� 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // �� ���������, ���� 3.4 �� �����
                }
                else
                {
                    // ���� 3.4 ����, �� ��� ���� ���������� �� ����������
                    Description += " ���� 2.4 ���������� ���������� �� ����������;";
                }
            }
            else
            {
                // ��� ����� 2.4 �� ����������
                Description += " ��� ����� 2.4 �� ����������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L, 2000, "2.4", "", "������ ������", true);
            }
            break;

        case apRight:// ���������� ������
            // ���� ���� 2.3.3 (�������, ������, � �������� �����������)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.3", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.3 �� ����� ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.3 �� ����� ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.3", "", "���������� �����", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.3 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.3 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.3 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.3 �� ����� ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.3 �� ����� ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.3", "", "���������� �����", false);
            }

            // ���� ���� 2.3.2 (�����, ������, � ������ �����������)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.2", roDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.2 �� ������ ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.2 �� ������ ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.2", "", "���������� ������", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.2 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.2 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.2 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.2 �� ������ ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.2 �� ������ ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.2", "", "���������� ������", false);
            }

            // ���� ���� 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // �� ���������, ���� 3.4 �� �����
                }
                else
                {
                    // ���� 3.4 ����, �� ��� ���� ���������� �� ����������
                    Description += " ���� 2.4 ���������� ���������� �� ����������;";
                }
            }
            else
            {
                // ��� ����� 2.4 �� ����������
                Description += " ��� ����� 2.4 �� ����������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L, 2000, "2.4", "", "������ ������", true);
            }
            break;

        case apLeft:// ���������� �����
            // ���� ���� 2.3.2 (�������, ������, � �������� �����������)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.2", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.2 �� ����� ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.2 �� ����� ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.2", "", "���������� ������", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.2 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.2 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.2 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.2 �� ����� ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.2 �� ����� ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.2", "", "���������� ������", false);
            }

            // ���� ���� 2.3.3 (�����, ������, � ������ �����������)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.3", roDirect, spRight, 30000);
            if(Sign)
            {
                // �������� ���������� �� �����
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // ��� ����� 2.3.3 �� ������ ������� ������ � ���������� ��������
                    Description += " ��� ����� 2.3.3 �� ������ ������� ������ � ���������� ��������;";
                    // ��������� ����, ���� ����
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.3", "", "���������� �����", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // ���� 2.3.3 ����, �� �������� ��� ���� ����������� (������� ������)
                        Description += " ���� 2.3.3 ����, �� �������� ��� ���� ����������� (������� ������);";
                        // ��������� ��������� + ����� � ����
                    }
                    else
                    {
                        // ���� 2.3.3 ���� � ���������� ��� ����
                    }
                }
            }
            else
            {
                // ��� ����� 2.3.3 �� ������ ������� ������ � ���������� ��������
                Description += " ��� ����� 2.3.3 �� ������ ������� ������ � ���������� ��������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.3", "", "���������� �����", false);
            }

            // ���� ���� 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roUnDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // �� ���������, ���� 3.4 �� �����
                }
                else
                {
                    // ���� 3.4 ����, �� ��� ���� ���������� �� ����������
                    Description += " ���� 2.4 ���������� ���������� �� ����������;";
                }
            }
            else
            {
                // ��� ����� 2.4 �� ����������
                Description += " ��� ����� 2.4 �� ����������;";
                // ��������� ����, ���� ����
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L, 2000, "2.4", "", "������ ������", true);
            }
            break;
        default:

            break;
    }

    return Description;
    //this->ShowCurrentRoadObjectDescription(Description);
}
*/
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::CheckBridgeSigns(TRoadBridge* Bridge)
{
    TList* SignsList = new TList;
    SignsList->Add(new TSign("5.26", "������������ �������", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("5.26", "������������ �������", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

    SignsList->Add(new TSign("3.11", "����������� �����", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("3.11", "����������� �����", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

    SignsList->Add(new TSign("3.12", "����������� �������� �� ���", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("3.12", "����������� �������� �� ���", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

    //AnsiString Description;
    //TRoadSign *Sign;

    CurrentObjectSignsList->Clear();
    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        AnsiString Description = "";
        AnsiString Label = "";
        __int32 Place = 0;

        TRoadSign *Sign = this->FindSign(
            ((TSign*)SignsList->Items[i])->Name,
            ((TSign*)SignsList->Items[i])->Direction,
            ((TSign*)SignsList->Items[i])->Placement,
            ((TSign*)SignsList->Items[i])->MinL,
            ((TSign*)SignsList->Items[i])->MaxL);
        if(Sign)
        {// ����� ����
        }
        else
        {// �� ����� ����, ������� ���������� � ������ ������ �������
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[������] ";
            else
                Description += "[��������] ";

            if(((TSign*)SignsList->Items[i])->Name == "5.26")
            {
                Description += "����������� ��� ���������� ������ 20 �. �� �����";

                if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                    Place = Bridge->LMin;
                else
                    Place = Bridge->LMax;
            }

            if(((TSign*)SignsList->Items[i])->Name == "3.11" ||
               ((TSign*)SignsList->Items[i])->Name == "3.12")
            {
                Description += "����������� ��� ���������� ������ 20 �. �� �����";

                if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                    Place = Bridge->LMin;
                else
                    Place = Bridge->LMax;

                // ����� ���� � Label �������� �����������
            }

            CurrentObjectSignsList->AddItem(Description, new TSign(
                ((TSign*)SignsList->Items[i])->Name,
                ((TSign*)SignsList->Items[i])->Description,
                Label,
                ((TSign*)SignsList->Items[i])->Direction,
                ((TSign*)SignsList->Items[i])->Placement,
                0,
                0,
                Place,
                300,
                false));
        }
    }

    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        TSign *s = (TSign*)SignsList->Items[i];
        delete s;
        SignsList->Items[i] = 0;
    }
    delete SignsList;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::CheckAttachSigns(TRoadAttach* Attach)
{
    TList* SignsList = new TList;
    switch(Attach->Placement)
    {
        case apCross:// �����������
            SignsList->Add(new TSign("2.4", "�������� ������", "", roDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.4", "�������� ������", "", roUnDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.1", "����������� �� �������������� �������", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.1", "����������� �� �������������� �������", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L + 15000, 300, false));
            break;
        case apRight:// ���������� ������
            SignsList->Add(new TSign("2.4", "�������� ������", "", roDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.2", "���������� �������������� ������", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.3", "���������� �������������� ������", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L +15000, 300, false));
            break;
        case apLeft:// ���������� �����
            SignsList->Add(new TSign("2.4", "�������� ������", "", roUnDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.3", "���������� �������������� ������", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.2", "���������� �������������� ������", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L +15000, 300, false));
            break;
    }

    CurrentObjectSignsList->Clear();
    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        AnsiString Description = "";
        AnsiString Label = "";
        //__int32 Place = 0;

        TRoadSign *Sign = this->FindSign(
            ((TSign*)SignsList->Items[i])->Name,
            ((TSign*)SignsList->Items[i])->Direction,
            ((TSign*)SignsList->Items[i])->Placement,
            ((TSign*)SignsList->Items[i])->MinL,
            ((TSign*)SignsList->Items[i])->MaxL);
        if(Sign)
        {// ����� ����
        }
        else
        {// �� ����� ����, ������� ���������� � ������ ������ �������
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[������] ";
            else
                Description += "[��������] ";

            CurrentObjectSignsList->AddItem(Description, new TSign(
                ((TSign*)SignsList->Items[i])->Name,
                ((TSign*)SignsList->Items[i])->Description,
                ((TSign*)SignsList->Items[i])->Label,
                ((TSign*)SignsList->Items[i])->Direction,
                ((TSign*)SignsList->Items[i])->Placement,
                0,
                0,
                ((TSign*)SignsList->Items[i])->X,
                ((TSign*)SignsList->Items[i])->Y,
                ((TSign*)SignsList->Items[i])->IsOnAttach));
            
        }
    }

    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        TSign *s = (TSign*)SignsList->Items[i];
        delete s;
        SignsList->Items[i] = 0;
    }
    delete SignsList;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::CheckTownSigns(TTown* Town)
{
    TList* SignsList = new TList;
    // ���������, ����� ����� ����� ������ 5.22(5.23) ��� 5.24(5.25)
    //if(MessageBox(NULL, "��������� �� �� ���������� ������� ���������� ������ ����������, ������������ ������� �������� � ��������� �������?", "������ ����������� ������", MB_YESNO) == IDYES)
    //{// 5.22-5.23
        SignsList->Add(new TSign("5.22", "������ ���������� ������", "", roDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
        SignsList->Add(new TSign("5.23", "����� ���������� ������", "", roDirect, spRight, Town->LMin - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.22", "������ ���������� ������", "", roUnDirect, spRight, Town->LMax - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.23", "����� ���������� ������", "", roUnDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
    //}
    //else
    //{
        SignsList->Add(new TSign("5.24", "������ ���������� ������", "", roDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
        SignsList->Add(new TSign("5.25", "����� ���������� ������", "", roDirect, spRight, Town->LMin - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.24", "������ ���������� ������", "", roUnDirect, spRight, Town->LMax - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.25", "����� ���������� ������", "", roUnDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
    //}

    CurrentObjectSignsList->Clear();
    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        AnsiString Description = "";
        AnsiString Label = "";
        //__int32 Place = 0;

        TRoadSign *Sign = this->FindSign(
            ((TSign*)SignsList->Items[i])->Name,
            ((TSign*)SignsList->Items[i])->Direction,
            ((TSign*)SignsList->Items[i])->Placement,
            ((TSign*)SignsList->Items[i])->MinL,
            ((TSign*)SignsList->Items[i])->MaxL);
        if(Sign)
        {// ����� ����
        }
        else
        {// �� ����� ����, ������� ���������� � ������ ������ �������
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[������] ";
            else
                Description += "[��������] ";

            CurrentObjectSignsList->AddItem(Description, new TSign(
                ((TSign*)SignsList->Items[i])->Name,
                ((TSign*)SignsList->Items[i])->Description,
                ((TSign*)SignsList->Items[i])->Label,
                ((TSign*)SignsList->Items[i])->Direction,
                ((TSign*)SignsList->Items[i])->Placement,
                0,
                0,
                ((TSign*)SignsList->Items[i])->X,
                ((TSign*)SignsList->Items[i])->Y,
                ((TSign*)SignsList->Items[i])->IsOnAttach));
        }
    }

    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        TSign *s = (TSign*)SignsList->Items[i];
        delete s;
        SignsList->Items[i] = 0;
    }
    delete SignsList;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::CheckBusStopSigns(TBusStop *BusStop)
{
    TList* SignsList = new TList;

    if(BusStop->Placement == opRight)
    {
        SignsList->Add(new TSign("5.12", "����� ��������� ��������", "", roDirect, spRight, BusStop->L - 500, BusStop->L + 500, BusStop->L - 200, 300, false));
        SignsList->Add(new TSign("5.16.1", "���������� �������", "", roDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
        SignsList->Add(new TSign("5.16.1", "���������� �������", "", roUnDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
    }
    if(BusStop->Placement == opLeft)
    {
        SignsList->Add(new TSign("5.12", "����� ��������� ��������", "", roUnDirect, spRight, BusStop->L - 500, BusStop->L + 500, BusStop->L + 200, 300, false));
        SignsList->Add(new TSign("5.16.1", "���������� �������", "", roDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
        SignsList->Add(new TSign("5.16.1", "���������� �������", "", roUnDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
    }

    CurrentObjectSignsList->Clear();
    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        AnsiString Description = "";
        AnsiString Label = "";
        //__int32 Place = 0;

        TRoadSign *Sign = this->FindSign(
            ((TSign*)SignsList->Items[i])->Name,
            ((TSign*)SignsList->Items[i])->Direction,
            ((TSign*)SignsList->Items[i])->Placement,
            ((TSign*)SignsList->Items[i])->MinL,
            ((TSign*)SignsList->Items[i])->MaxL);

        if(Sign)
        {// ����� ����
        }
        else
        {// �� ����� ����, ������� ���������� � ������ ������ �������
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[������] ";
            else
                Description += "[��������] ";

            CurrentObjectSignsList->AddItem(Description, new TSign(
                ((TSign*)SignsList->Items[i])->Name,
                ((TSign*)SignsList->Items[i])->Description,
                ((TSign*)SignsList->Items[i])->Label,
                ((TSign*)SignsList->Items[i])->Direction,
                ((TSign*)SignsList->Items[i])->Placement,
                0,
                0,
                ((TSign*)SignsList->Items[i])->X,
                ((TSign*)SignsList->Items[i])->Y,
                ((TSign*)SignsList->Items[i])->IsOnAttach));
        }
    }

    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        TSign *s = (TSign*)SignsList->Items[i];
        delete s;
        SignsList->Items[i] = 0;
    }
    delete SignsList;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetSigns::CheckRailCrossSigns(TRailCross* RailCross)
{
    TList* SignsList = new TList;

    // ��������� ��� ��������
    if(RailCross->SignalKind == rcsMBlock || RailCross->SignalKind == rcsEBlock || RailCross->SignalKind == rcsABlock)
    {// �� ����������
        // �����
        SignsList->Add(new TSign("1.1", "��������������� ������� �� ����������", "", roDirect, spRight, RailCross->L - 30000, RailCross->L - 15000, RailCross->L - 30000 , 300, false));
        SignsList->Add(new TSign("1.1", "��������������� ������� �� ����������", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // �������
        SignsList->Add(new TSign("1.1", "��������������� ������� �� ����������", "", roUnDirect, spRight, RailCross->L + 150000, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
        SignsList->Add(new TSign("1.1", "��������������� ������� �� ����������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }
    else
    {// ��� ���������
        // �����
        SignsList->Add(new TSign("1.2", "��������������� ������� ��� ���������", "", roDirect, spRight, RailCross->L - 30000, RailCross->L - 15000, RailCross->L - 30000 , 300, false));
        SignsList->Add(new TSign("1.2", "��������������� ������� ��� ���������", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // �������
        SignsList->Add(new TSign("1.2", "��������������� ������� ��� ���������", "", roUnDirect, spRight, RailCross->L + 150000, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
        SignsList->Add(new TSign("1.2", "��������������� ������� ��� ���������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }

    if(RailCross->RailCount > 1)
    {// ���������� ������
        // �����
        SignsList->Add(new TSign("1.3.1", "���������� �������� ������", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // ��������
        SignsList->Add(new TSign("1.3.1", "���������� �������� ������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }
    else
    {// ����������� ������
        // �����
        SignsList->Add(new TSign("1.3.2", "����������� �������� ������", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // ��������
        SignsList->Add(new TSign("1.3.2", "����������� �������� ������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }

    // �����
    // �� ������ �������
    SignsList->Add(new TSign("1.4.1", "����������� � ���������������� ��������", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 30000 , 300, false));
    SignsList->Add(new TSign("1.4.2", "����������� � ���������������� ��������", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 17500 , 300, false));
    SignsList->Add(new TSign("1.4.3", "����������� � ���������������� ��������", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 5000 , 300, false));
    // �� ����� �������
    SignsList->Add(new TSign("1.4.4", "����������� � ���������������� ��������", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 30000 , 300, false));
    SignsList->Add(new TSign("1.4.5", "����������� � ���������������� ��������", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 17500 , 300, false));
    SignsList->Add(new TSign("1.4.6", "����������� � ���������������� ��������", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 5000 , 300, false));
    // �������
    // �� ������ �������
    SignsList->Add(new TSign("1.4.1", "����������� � ���������������� ��������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
    SignsList->Add(new TSign("1.4.2", "����������� � ���������������� ��������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 17500 , 300, false));
    SignsList->Add(new TSign("1.4.3", "����������� � ���������������� ��������", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 5000 , 300, false));
    // �� ����� �������
    SignsList->Add(new TSign("1.4.4", "����������� � ���������������� ��������", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
    SignsList->Add(new TSign("1.4.5", "����������� � ���������������� ��������", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 17500 , 300, false));
    SignsList->Add(new TSign("1.4.6", "����������� � ���������������� ��������", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 5000 , 300, false));


    CurrentObjectSignsList->Clear();
    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        AnsiString Description = "";
        AnsiString Label = "";
        //__int32 Place = 0;

        TRoadSign *Sign = this->FindSign(
            ((TSign*)SignsList->Items[i])->Name,
            ((TSign*)SignsList->Items[i])->Direction,
            ((TSign*)SignsList->Items[i])->Placement,
            ((TSign*)SignsList->Items[i])->MinL,
            ((TSign*)SignsList->Items[i])->MaxL);

        if(Sign)
        {// ����� ����
        }
        else
        {// �� ����� ����, ������� ���������� � ������ ������ �������
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[������] ";
            else
                Description += "[��������] ";

            CurrentObjectSignsList->AddItem(Description, new TSign(
                ((TSign*)SignsList->Items[i])->Name,
                ((TSign*)SignsList->Items[i])->Description,
                ((TSign*)SignsList->Items[i])->Label,
                ((TSign*)SignsList->Items[i])->Direction,
                ((TSign*)SignsList->Items[i])->Placement,
                0,
                0,
                ((TSign*)SignsList->Items[i])->X,
                ((TSign*)SignsList->Items[i])->Y,
                ((TSign*)SignsList->Items[i])->IsOnAttach));
        }
    }

    for(__int32 i = 0; i < SignsList->Count; i++)
    {
        TSign *s = (TSign*)SignsList->Items[i];
        delete s;
        SignsList->Items[i] = 0;
    }
    delete SignsList;
}
//---------------------------------------------------------------------------
