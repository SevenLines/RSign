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
//***Функции интерфеса*******************************************************
//***************************************************************************

//---------------------------------------------------------------------------
void __fastcall TfrmCheckSigns::FormShow(TObject *Sender)
{
    this->SetCurrentActiveRoad(MainForm->ActiveRoad);

    // добавим в список все знаки, которые будем обрабатывать
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
// переход к следующему знаку на дороге
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
                            if(SignsList->Checked[0])// предупреждающие
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '2':
                            if(SignsList->Checked[1])// приоритета
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
                // если нашли знак, то выходим из цикла и запоминаем номер знака
                this->CurrentSign = i;
                SignPlace = sign->L;

                this->CurrentActiveRoad->SetVideoPos(sign->L/100);
                break;
            }
        }

        // выводим информацию об знаке
        this->ShowCurrentSignInfo(SignTitle, SignPlace);
        this->ShowCurrentSignDescription(SignDescription);

        if(!IsFound)
        {
            // если пробежали весь цикл и не нашли ни один объект, задисэйблим кнопки Next и End
            this->CurrentSign = RoadObjectsCount;
            this->ShowCurrentSignInfo("<< конец дороги >>", "<< конец дороги >>");
            this->ShowCurrentSignDescription("");
        }
    }
}
//---------------------------------------------------------------------------
// переход к предыдущему знаку на дороге
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
                            if(SignsList->Checked[0])// предупреждающие
                            {
                                IsFound = this->IsKnownSign(sign);
                            }
                            break;
                        case '2':
                            if(SignsList->Checked[1])// приоритета
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
                // если нашли знак, то выходим из цикла и запоминаем номер знака
                this->CurrentSign = i;
                SignPlace = sign->L;

                this->CurrentActiveRoad->SetVideoPos(sign->L/100);
                break;
            }
        }

        // выводим информацию об знаке
        this->ShowCurrentSignInfo(SignTitle, SignPlace);
        this->ShowCurrentSignDescription(SignDescription);

        if(!IsFound)
        {
            // если пробежали весь цикл и не нашли ни один объект, задисэйблим кнопки Next и End
            this->CurrentSign = RoadObjectsCount;
            this->ShowCurrentSignInfo("<< начало дороги >>", "<< начало дороги >>");
            this->ShowCurrentSignDescription("");
        }
    }
}
//---------------------------------------------------------------------------
// переходим в конец дороги
void __fastcall TfrmCheckSigns::btnGoToEndClick(TObject *Sender)
{
    this->ShowCurrentSignInfo("<< конец дороги >>", "<< конец дороги >>");
    if(this->CheckCurrentActiveRoad())
        this->CurrentSign = this->CurrentActiveRoad->EditedData->Objects->Count;
}
//---------------------------------------------------------------------------
// переходим в начало дороги
void __fastcall TfrmCheckSigns::btnGoToBeginClick(TObject *Sender)
{
    this->ShowCurrentSignInfo("<< начало дороги >>", "<< начало дороги >>");
    this->CurrentSign = -1;
}
//---------------------------------------------------------------------------

//***************************************************************************
//***Вспомогательные функции*************************************************
//***************************************************************************

//---------------------------------------------------------------------------
bool __fastcall TfrmCheckSigns::CheckCurrentActiveRoad()
{
    if(MainForm->ActiveRoad)
    {// если есть выбранная дорога
        if(MainForm->ActiveRoad == this->CurrentActiveRoad)
        {// если дорога не поменялась
            return true;
        }
        else
        {// если дорога сменилась
            if(MessageBox(NULL, "Сменилась текущая дорога. Сменить текущую дорогу?", "Мастер расстановки занков", MB_YESNO) == IDYES)
            {// меняем текущую дорогу
                SetCurrentActiveRoad(MainForm->ActiveRoad);
                return true;
            }
            else
            {// оставляем текущую дорогу
                ShowMessage("Для продолжения сделайте текущую дорогу активной.");
                return false;
            }
        }
    }
    else
    {// если нет выбранной дороги
        ShowMessage("Дальнейшая расстановка знаков невозможна, т.к. не выбрана ни одна дорога. Для продолжения выберите дорогу.");
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
        lblCurrentRoadTitle->Caption = "<<дорога не выбрана>>";

    //this->ShowCurrentSignInfo("", "");
    this->ShowCurrentSignInfo("<< начало дороги >>", "<< начало дороги >>");
}
//---------------------------------------------------------------------------
// выводит информацию о текущем знаке
void __fastcall TfrmCheckSigns::ShowCurrentSignInfo(AnsiString Title, AnsiString Place)
{
    lblCurrentSignTitle->Caption = Title;
    lblCurrentSignPlace->Caption = Place;
}
//---------------------------------------------------------------------------
// выводит описание ситуации по текущему знаку
void __fastcall TfrmCheckSigns::ShowCurrentSignDescription(AnsiString Description)
{
    lblCurrentSignDescription->Caption = Description;
}
//---------------------------------------------------------------------------

//***************************************************************************
//***Вспомогательные функции для проверки расстановки знаков*****************
//***************************************************************************

//---------------------------------------------------------------------------
// возвращает true, если можем проверить этот знак
bool __fastcall TfrmCheckSigns::IsKnownSign(TRoadSign *Sign)
{
    if(Sign)
    {
        AnsiString SignName = this->CurrentActiveRoad->Dict->GetShortTitle(Sign->NumRoadSign);;
         __int32 i;
        if(KnownSignsList->Find(SignName, i))
            return true;
        /*
        // предупреждающие знаки
        if(SignName == "1.1")// Железнодорожный переезд со шлагбаумом
            return true;

        if(SignName == "1.1")// Железнодорожный переезд со шлагбаумом
            return true;

        // знаки приоритета
        if(SignName == "2.3.1")// пересечение со второстепенной дорогой
            return true;

        // запрещающие знаки
        */
    }
    return false;
}

//***************************************************************************
//***Функции проверки расстановки знаков*************************************
//***************************************************************************
