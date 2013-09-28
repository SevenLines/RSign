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
//***Функции интерфеса*******************************************************
//***************************************************************************

//---------------------------------------------------------------------------
// переход к следующему объкту на дороге
void __fastcall TfrmSetSigns::btnGoToNextClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString ObjectTitle = "";
        AnsiString ObjectPlace = "";

        //очистим список знаков, предлагаемых для установки
        this->ClearCurrentObjectSignsList();

        __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
        for(__int32 i = (this->CurrentRoadObject + 1); i < RoadObjectsCount; i++)
        {
            //IsFound = false;
            if(RoadObjectsList->Checked[0])// если отмечены примыкания
            {
                TRoadAttach *attach = dynamic_cast<TRoadAttach*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(attach)
                {
                    IsFound = true;
                    ObjectTitle = "примыкание";
                    ObjectPlace = AnsiString(attach->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckAttachSigns(attach);
                    this->CurrentActiveRoad->SetVideoPos(attach->L/100);
                }
            }

            if(RoadObjectsList->Checked[1])// если отмечены населённые пункты
            {
                TTown *town=dynamic_cast<TTown*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(town)
                {
                    IsFound = true;
                    ObjectTitle = "населённый пункт";
                    ObjectPlace = AnsiString(town->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckTownSigns(town);
                    this->CurrentActiveRoad->SetVideoPos(town->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[2])// если отмечены мосты
            {
                TRoadBridge *bridge=dynamic_cast<TRoadBridge*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(bridge)
                {
                    IsFound = true;
                    ObjectTitle = "мост";
                    ObjectPlace = AnsiString(bridge->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckBridgeSigns(bridge);
                    this->CurrentActiveRoad->SetVideoPos(bridge->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[3])// если отмечены автобусные остановки
            {
                TBusStop *busstop=dynamic_cast<TBusStop*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(busstop)
                {
                    IsFound = true;
                    ObjectTitle = "автобусная остановка";
                    ObjectPlace = AnsiString(busstop->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckBusStopSigns(busstop);
                    this->CurrentActiveRoad->SetVideoPos(busstop->L/100);
                }
            }

            if(RoadObjectsList->Checked[4])// если отмечены перезды
            {
                TRailCross *railcross=dynamic_cast<TRailCross*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(railcross)
                {
                    IsFound = true;
                    ObjectTitle = "переезд";
                    ObjectPlace = AnsiString(railcross->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckRailCrossSigns(railcross);
                    this->CurrentActiveRoad->SetVideoPos(railcross->L/100);
                }
            }

            if(IsFound)
            {
                // если нашли объект, то выходим из цикла и запоминаем номер объекта
                this->CurrentRoadObject = i;
                break;
            }
        }

        // выводим информацию об объекте
        this->ShowCurrentRoadObjectInfo(ObjectTitle, ObjectPlace);

        if(!IsFound)
        {
            // если пробежали весь цикл и не нашли ни один объект, задисэйблим кнопки Next и End
            this->CurrentRoadObject = RoadObjectsCount;
            this->ShowCurrentRoadObjectInfo("<< конец дороги >>", "<< конец дороги >>");
            this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MaxL/100);
        }
    }
}
//---------------------------------------------------------------------------
// переход в конец дороги
void __fastcall TfrmSetSigns::btnGoToEndClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        this->ShowCurrentRoadObjectInfo("<< конец дороги >>", "<< конец дороги >>");
        this->CurrentRoadObject = this->CurrentActiveRoad->EditedData->Objects->Count;
        this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MaxL/100);

        //очистим список знаков, предлагаемых для установки
        this->ClearCurrentObjectSignsList();
    }
}
//---------------------------------------------------------------------------
// переход в начало дороги
void __fastcall TfrmSetSigns::btnGoToBeginClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        this->ShowCurrentRoadObjectInfo("<< начало дороги >>", "<< начало дороги >>");
        this->CurrentRoadObject = -1;
        this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MinL/100);

        //очистим список знаков, предлагаемых для установки
        this->ClearCurrentObjectSignsList();
    }
}
//---------------------------------------------------------------------------
// переход к предыдущему объкту на дороге
void __fastcall TfrmSetSigns::btnGoToPrevClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        bool IsFound = false;
        AnsiString ObjectTitle = "";
        AnsiString ObjectPlace = "";

        //очистим список знаков, предлагаемых для установки
        this->ClearCurrentObjectSignsList();

        __int32 RoadObjectsCount = -1;
        for(__int32 i = (this->CurrentRoadObject - 1); i > RoadObjectsCount; i--)
        {
            //IsFound = false;
            if(RoadObjectsList->Checked[0])// если отмечены примыкания
            {
                TRoadAttach *attach = dynamic_cast<TRoadAttach*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(attach)
                {
                    IsFound = true;
                    ObjectTitle = "примыкание";
                    ObjectPlace = AnsiString(attach->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckAttachSigns(attach);
                    this->CurrentActiveRoad->SetVideoPos(attach->L/100);
                }
            }


            if(RoadObjectsList->Checked[1])// если отмечены населённые пункты
            {
                TTown *town = dynamic_cast<TTown*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(town)
                {
                    IsFound = true;
                    ObjectTitle = "населённый пункт";
                    ObjectPlace = AnsiString(town->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckTownSigns(town);
                    this->CurrentActiveRoad->SetVideoPos(town->LMin/100);
                }
            }
            
            if(RoadObjectsList->Checked[2])// если отмечены мосты
            {
                TRoadBridge *bridge=dynamic_cast<TRoadBridge*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(bridge)
                {
                    IsFound = true;
                    ObjectTitle = "мост";
                    ObjectPlace = AnsiString(bridge->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckBridgeSigns(bridge);
                    this->CurrentActiveRoad->SetVideoPos(bridge->LMin/100);
                }
            }

            if(RoadObjectsList->Checked[3])// если отмечены автобусные остановки
            {
                TBusStop *busstop=dynamic_cast<TBusStop*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(busstop)
                {
                    IsFound = true;
                    ObjectTitle = "автобусная остановка";
                    ObjectPlace = AnsiString(busstop->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckBusStopSigns(busstop);
                    this->CurrentActiveRoad->SetVideoPos(busstop->L/100);
                }
            }

            if(RoadObjectsList->Checked[4])// если отмечены перезды
            {
                TRailCross *railcross=dynamic_cast<TRailCross*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
                if(railcross)
                {
                    IsFound = true;
                    ObjectTitle = "переезд";
                    ObjectPlace = AnsiString(railcross->L);
                    // проверим знаки, если необходимо
                    if(AutoCheck->Checked)
                        this->CheckRailCrossSigns(railcross);
                    this->CurrentActiveRoad->SetVideoPos(railcross->L/100);
                }
            }

            if(IsFound)
            {
                // если нашли объект, то выходим из цикла и запоминаем номер объекта
                this->CurrentRoadObject = i;
                break;
            }
        }

        // выводим информацию об объекте
        this->ShowCurrentRoadObjectInfo(ObjectTitle, ObjectPlace);

        if(!IsFound)
        {
            // если пробежали весь цикл и не нашли ни один объект, задисэйблим кнопки Next и End
            this->CurrentRoadObject = RoadObjectsCount;
            this->ShowCurrentRoadObjectInfo("<< начало дороги >>", "<< начало дороги >>");
            this->CurrentActiveRoad->SetVideoPos(this->CurrentActiveRoad->MinL/100);
        }
    }
}

//---------------------------------------------------------------------------
// проверяем знаки для текущего объекта
void __fastcall TfrmSetSigns::btnCheckSignsClick(TObject *Sender)
{
    if(this->CheckCurrentActiveRoad())
    {
        if((this->CurrentRoadObject != -1) ||
           (this->CurrentRoadObject != this->CurrentActiveRoad->EditedData->Objects->Count))
        {
            // проверим, что это за объект

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
// расставляем знаки для текущего объекта
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
//***Вспомогательные функции*************************************************
//***************************************************************************

//---------------------------------------------------------------------------
bool __fastcall TfrmSetSigns::CheckCurrentActiveRoad()
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
void __fastcall TfrmSetSigns::SetCurrentActiveRoad(TRoadFrm *NewActiveRoad)
{
    this->CurrentActiveRoad = NewActiveRoad;
    this->CurrentRoadObject = -1;
    if(this->CurrentActiveRoad)
        lblCurrentRoadTitle->Caption = Trim(this->CurrentActiveRoad->RoadName);
    else
        lblCurrentRoadTitle->Caption = "<<дорога не выбрана>>";

    this->ShowCurrentRoadObjectInfo("","");
}

//---------------------------------------------------------------------------
// выводит информацию о текущем объекте
void __fastcall TfrmSetSigns::ShowCurrentRoadObjectInfo(AnsiString Title, AnsiString Place)
{
    lblCurrentRoadObjectTitle->Caption = Title;
    lblCurrentRoadObjectPlace->Caption = Place;
}
//---------------------------------------------------------------------------
// очистим список знаков, предложенных для расстановки
void __fastcall TfrmSetSigns::ClearCurrentObjectSignsList()
{
    for(__int32 i = 0; i < CurrentObjectSignsList->Count; i++)
        delete CurrentObjectSignsList->Items->Objects[i];

    CurrentObjectSignsList->Clear();
}

//***************************************************************************
//***Вспомогательные функции для проверки расстановки знаков*****************
//***************************************************************************

//---------------------------------------------------------------------------
// найти ближайший знак (вперёд)
TRoadSign* __fastcall TfrmSetSigns::FindNearestSignForward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
    for(__int32 i = ++ObjectIndex; i < RoadObjectsCount; i++)
    {
        // проверим расстояние от объекта
        __int32 distance = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L - this->CurrentActiveRoad->EditedData->Objects->Items[ObjectIndex]->L;
        if(abs(distance) > Radius)
            return NULL;

        TRoadSign *sign=dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
        if(sign)
        {
            // если знак удовлетворяет условия, то вернём его
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
// найти ближайший знак (назад)
TRoadSign* __fastcall TfrmSetSigns::FindNearestSignBackward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    __int32 RoadObjectsCount = -1;
    for(__int32 i = --ObjectIndex; i > RoadObjectsCount; i--)
    {
        // проверим расстояние от объекта
        __int32 distance = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L - this->CurrentActiveRoad->EditedData->Objects->Items[ObjectIndex]->L;
        if(abs(distance) > Radius)
            return NULL;

        TRoadSign *sign=dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
        if(sign)
        {
            // если знак удовлетворяет условия, то вернём его
            if((this->CurrentActiveRoad->Dict->GetShortTitle(sign->NumRoadSign) == SignName) &&
               (sign->Direction == SignDirection) &&
               (sign->Placement == SignPlacement))
                return sign;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
// найти ближайший знак в некотором "радиусе" вокруг объекта
TRoadSign* __fastcall TfrmSetSigns::FindNearestSign(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius)
{
    // пробегаем вперёд
    TRoadSign *Sign1 = this->FindNearestSignForward(ObjectIndex, SignName, SignDirection, SignPlacement, Radius);
    // пробегаем назад
    TRoadSign *Sign2 = this->FindNearestSignBackward(ObjectIndex, SignName, SignDirection, SignPlacement, Radius);
    // смотрим какой ближе
    if(Sign1 && !Sign2)
        return Sign1;
    if(!Sign1 && Sign2)
        return Sign2;
    if(Sign1 && Sign2)
    {
        //определим, какой знак ближе
        __int32 dist1 = abs(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]->L - Sign1->L);
        __int32 dist2 = abs(this->CurrentActiveRoad->EditedData->Objects->Items[this->CurrentRoadObject]->L - Sign2->L);
        if(dist1 < dist2)
            return Sign1;
        else
            return Sign2;
    }
    // если дошли до сюда, то знака нет
    return NULL;
}
//---------------------------------------------------------------------------
// найти знак внутри переденного участка(отрезка) дороги
TRoadSign* __fastcall TfrmSetSigns::FindSign(AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 L1, __int32 L2)
{
    __int32 RoadObjectsCount = this->CurrentActiveRoad->EditedData->Objects->Count;
    for (__int32 i = 0; i < RoadObjectsCount; i++)
    {
        //здесь перебираем все населённые пункты
        __int32 CurrentL = this->CurrentActiveRoad->EditedData->Objects->Items[i]->L;
        if((CurrentL >= L1) && (CurrentL <= L2))
        {
            TRoadSign *sign = dynamic_cast<TRoadSign*>(this->CurrentActiveRoad->EditedData->Objects->Items[i]);
            if(sign)
            {
                // если знак удовлетворяет условия, то вернём его
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
//***Функции проверки расстановки знаков*************************************
//***************************************************************************


/*
//---------------------------------------------------------------------------
// проверим/установим знаки для примыкания
AnsiString __fastcall TfrmSetSigns::SetAttachSigns(TRoadAttach *Attach, bool SetSign)
{
    AnsiString Description = "";
    TRoadSign *Sign;
    // проверим тип примыкания
    switch(Attach->Placement)
    {
        case apCross:// пересечение
            // ищем знак 2.3.1 (впереди, справа, в обратном направлении)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.1", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.1 по левой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.1 по левой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                        this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.1 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.1 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.1 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.1 по левой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.1 по левой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой", false);
            }

            // ищем знак 2.3.1 (сзади, справа, в прямом направлении)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.1", roDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.1 по правой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.1 по правой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                        this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.1 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.1 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.1 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.1 по правой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.1 по правой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой", false);
            }

            // ищем знак 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // всё нормально, знак 3.4 на месте
                }
                else
                {
                    // знак 3.4 есть, но его надо разместить на примыкании
                    Description += " знак 2.4 необходимо разместить на примыкании;";
                }
            }
            else
            {
                // нет знака 2.4 на примыкании
                Description += " нет знака 2.4 на примыкании;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L, 2000, "2.4", "", "Уступи дорогу", true);
            }

            // ищем знак 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // всё нормально, знак 3.4 на месте
                }
                else
                {
                    // знак 3.4 есть, но его надо разместить на примыкании
                    Description += " знак 2.4 необходимо разместить на примыкании;";
                }
            }
            else
            {
                // нет знака 2.4 на примыкании
                Description += " нет знака 2.4 на примыкании;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L, 2000, "2.4", "", "Уступи дорогу", true);
            }
            break;

        case apRight:// примыкание справа
            // ищем знак 2.3.3 (впереди, справа, в обратном направлении)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.3", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.3 по левой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.3 по левой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.3", "", "Примыкание слева", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.3 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.3 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.3 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.3 по левой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.3 по левой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.3", "", "Примыкание слева", false);
            }

            // ищем знак 2.3.2 (сзади, справа, в прямом направлении)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.2", roDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.2 по правой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.2 по правой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.2", "", "Примыкание справа", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.2 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.2 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.2 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.2 по правой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.2 по правой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.2", "", "Примыкание справа", false);
            }

            // ищем знак 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // всё нормально, знак 3.4 на месте
                }
                else
                {
                    // знак 3.4 есть, но его надо разместить на примыкании
                    Description += " знак 2.4 необходимо разместить на примыкании;";
                }
            }
            else
            {
                // нет знака 2.4 на примыкании
                Description += " нет знака 2.4 на примыкании;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L, 2000, "2.4", "", "Уступи дорогу", true);
            }
            break;

        case apLeft:// примыкание слева
            // ищем знак 2.3.2 (впереди, справа, в обратном направлении)
            Sign = this->FindNearestSignForward(this->CurrentRoadObject, "2.3.2", roUnDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.2 по левой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.2 по левой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.2", "", "Примыкание справа", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.2 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.2 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.2 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.2 по левой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.2 по левой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L + 15500, 200, "2.3.2", "", "Примыкание справа", false);
            }

            // ищем знак 2.3.3 (сзади, справа, в прямом направлении)
            Sign = this->FindNearestSignBackward(this->CurrentRoadObject, "2.3.3", roDirect, spRight, 30000);
            if(Sign)
            {
                // проверим расстояние до знака
                __int32 distance = abs(Sign->L - Attach->L)/100;
                if(distance > 300)
                {
                    // нет знака 2.3.3 по правой стороне дороги в допустимых пределах
                    Description += " нет знака 2.3.3 по правой стороне дороги в допустимых пределах;";
                    // добавляем знак, если надо
                    if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.3", "", "Примыкание слева", false);
                }
                else
                {
                    if(distance < 150)
                    {
                        // знак 2.3.3 есть, но возможно его надо переместить (слишком близко)
                        Description += " знак 2.3.3 есть, но возможно его надо переместить (слишком близко);";
                        // добавляем сообщение + пишем в знак
                    }
                    else
                    {
                        // знак 2.3.3 есть и расположен где надо
                    }
                }
            }
            else
            {
                // нет знака 2.3.3 по правой стороне дороги в допустимых пределах
                Description += " нет знака 2.3.3 по правой стороне дороги в допустимых пределах;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roDirect, spRight, Attach->L - 15500, 200, "2.3.3", "", "Примыкание слева", false);
            }

            // ищем знак 2.4 ()
            Sign = this->FindNearestSign(this->CurrentRoadObject, "2.4", roUnDirect, spRight, 500);
            if(Sign)
            {
                if(Sign->OnAttach)
                {
                    // всё нормально, знак 3.4 на месте
                }
                else
                {
                    // знак 3.4 есть, но его надо разместить на примыкании
                    Description += " знак 2.4 необходимо разместить на примыкании;";
                }
            }
            else
            {
                // нет знака 2.4 на примыкании
                Description += " нет знака 2.4 на примыкании;";
                // добавляем знак, если надо
                if(SetSign)
                    this->CurrentActiveRoad->Data->AddPrjSign(this->CurrentActiveRoad->Dict, roUnDirect, spRight, Attach->L, 2000, "2.4", "", "Уступи дорогу", true);
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
    SignsList->Add(new TSign("5.26", "Наименование объекта", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("5.26", "Наименование объекта", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

    SignsList->Add(new TSign("3.11", "Ограничение массы", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("3.11", "Ограничение массы", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

    SignsList->Add(new TSign("3.12", "Ограничение нагрузки на ось", "", roDirect, spRight, Bridge->LMin - 2000, Bridge->LMin + 200, 0, 0, false));
    SignsList->Add(new TSign("3.12", "Ограничение нагрузки на ось", "", roUnDirect, spRight, Bridge->LMax - 200, Bridge->LMax + 2000, 0, 0, false));

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
        {// нашли знак
        }
        else
        {// не нашли знак, добавим информацию в список занков объекта
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[прямое] ";
            else
                Description += "[обратное] ";

            if(((TSign*)SignsList->Items[i])->Name == "5.26")
            {
                Description += "отсутствует или расположен дальше 20 м. от моста";

                if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                    Place = Bridge->LMin;
                else
                    Place = Bridge->LMax;
            }

            if(((TSign*)SignsList->Items[i])->Name == "3.11" ||
               ((TSign*)SignsList->Items[i])->Name == "3.12")
            {
                Description += "отсутствует или расположен дальше 20 м. от моста";

                if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                    Place = Bridge->LMin;
                else
                    Place = Bridge->LMax;

                // здесь надо в Label запихать ограничение
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
        case apCross:// пересечение
            SignsList->Add(new TSign("2.4", "Уступите дорогу", "", roDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.4", "Уступите дорогу", "", roUnDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.1", "Пересечение со второстепенной дорогой", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.1", "Пересечение со второстепенной дорогой", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L + 15000, 300, false));
            break;
        case apRight:// примыкание справа
            SignsList->Add(new TSign("2.4", "Уступите дорогу", "", roDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.2", "Примыкание второстепенной дороги", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.3", "Примыкание второстепенной дороги", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L +15000, 300, false));
            break;
        case apLeft:// примыкание слева
            SignsList->Add(new TSign("2.4", "Уступите дорогу", "", roUnDirect, spRight, Attach->L - 500, Attach->L + 500, Attach->L, 2000, true));
            SignsList->Add(new TSign("2.3.3", "Примыкание второстепенной дороги", "", roDirect, spRight, Attach->L - 30000, Attach->L, Attach->L - 15000, 300, false));
            SignsList->Add(new TSign("2.3.2", "Примыкание второстепенной дороги", "", roUnDirect, spRight, Attach->L, Attach->L + 30000, Attach->L +15000, 300, false));
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
        {// нашли знак
        }
        else
        {// не нашли знак, добавим информацию в список занков объекта
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[прямое] ";
            else
                Description += "[обратное] ";

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
    // определим, какие знаки стоит искать 5.22(5.23) или 5.24(5.25)
    //if(MessageBox(NULL, "Действуют ли на территории данного населённого пункта требования, регулирующие порядок движения в населённых пунктах?", "Мастер расстановки занков", MB_YESNO) == IDYES)
    //{// 5.22-5.23
        SignsList->Add(new TSign("5.22", "Начало населённого пункта", "", roDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
        SignsList->Add(new TSign("5.23", "Конец населённого пункта", "", roDirect, spRight, Town->LMin - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.22", "Начало населённого пункта", "", roUnDirect, spRight, Town->LMax - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.23", "Конец населённого пункта", "", roUnDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
    //}
    //else
    //{
        SignsList->Add(new TSign("5.24", "Начало населённого пункта", "", roDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
        SignsList->Add(new TSign("5.25", "Конец населённого пункта", "", roDirect, spRight, Town->LMin - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.24", "Начало населённого пункта", "", roUnDirect, spRight, Town->LMax - 500, Town->LMax + 500, Town->LMax, 300, false));
        SignsList->Add(new TSign("5.25", "Конец населённого пункта", "", roUnDirect, spRight, Town->LMin - 500, Town->LMin + 500, Town->LMin, 300, false));
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
        {// нашли знак
        }
        else
        {// не нашли знак, добавим информацию в список занков объекта
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[прямое] ";
            else
                Description += "[обратное] ";

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
        SignsList->Add(new TSign("5.12", "Место остановки автобуса", "", roDirect, spRight, BusStop->L - 500, BusStop->L + 500, BusStop->L - 200, 300, false));
        SignsList->Add(new TSign("5.16.1", "Пешеходный переход", "", roDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
        SignsList->Add(new TSign("5.16.1", "Пешеходный переход", "", roUnDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
    }
    if(BusStop->Placement == opLeft)
    {
        SignsList->Add(new TSign("5.12", "Место остановки автобуса", "", roUnDirect, spRight, BusStop->L - 500, BusStop->L + 500, BusStop->L + 200, 300, false));
        SignsList->Add(new TSign("5.16.1", "Пешеходный переход", "", roDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
        SignsList->Add(new TSign("5.16.1", "Пешеходный переход", "", roUnDirect, spRight, BusStop->L - 200, BusStop->L + 200, BusStop->L, 300, false));
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
        {// нашли знак
        }
        else
        {// не нашли знак, добавим информацию в список занков объекта
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[прямое] ";
            else
                Description += "[обратное] ";

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

    // определим тип переезда
    if(RailCross->SignalKind == rcsMBlock || RailCross->SignalKind == rcsEBlock || RailCross->SignalKind == rcsABlock)
    {// со шлагбаумом
        // прямо
        SignsList->Add(new TSign("1.1", "Железнодорожный переезд со шлагбаумом", "", roDirect, spRight, RailCross->L - 30000, RailCross->L - 15000, RailCross->L - 30000 , 300, false));
        SignsList->Add(new TSign("1.1", "Железнодорожный переезд со шлагбаумом", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // обратно
        SignsList->Add(new TSign("1.1", "Железнодорожный переезд со шлагбаумом", "", roUnDirect, spRight, RailCross->L + 150000, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
        SignsList->Add(new TSign("1.1", "Железнодорожный переезд со шлагбаумом", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }
    else
    {// без шлагбаума
        // прямо
        SignsList->Add(new TSign("1.2", "Железнодорожный переезд без шлагбаума", "", roDirect, spRight, RailCross->L - 30000, RailCross->L - 15000, RailCross->L - 30000 , 300, false));
        SignsList->Add(new TSign("1.2", "Железнодорожный переезд без шлагбаума", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // обратно
        SignsList->Add(new TSign("1.2", "Железнодорожный переезд без шлагбаума", "", roUnDirect, spRight, RailCross->L + 150000, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
        SignsList->Add(new TSign("1.2", "Железнодорожный переезд без шлагбаума", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }

    if(RailCross->RailCount > 1)
    {// однопутная дорога
        // прямо
        SignsList->Add(new TSign("1.3.1", "Однопутная железная дорога", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // обратоно
        SignsList->Add(new TSign("1.3.1", "Однопутная железная дорога", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }
    else
    {// многопутная дорога
        // прямо
        SignsList->Add(new TSign("1.3.2", "Многопутная железная дорога", "", roDirect, spRight, RailCross->L - 15000, RailCross->L, RailCross->L - 5000 , 300, false));
        // обратоно
        SignsList->Add(new TSign("1.3.2", "Многопутная железная дорога", "", roUnDirect, spRight, RailCross->L, RailCross->L + 15000, RailCross->L + 5000 , 300, false));
    }

    // прямо
    // по правой стороне
    SignsList->Add(new TSign("1.4.1", "Приближение к железнодорожному переезду", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 30000 , 300, false));
    SignsList->Add(new TSign("1.4.2", "Приближение к железнодорожному переезду", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 17500 , 300, false));
    SignsList->Add(new TSign("1.4.3", "Приближение к железнодорожному переезду", "", roDirect, spRight, RailCross->L - 30000, RailCross->L, RailCross->L - 5000 , 300, false));
    // по левой стороне
    SignsList->Add(new TSign("1.4.4", "Приближение к железнодорожному переезду", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 30000 , 300, false));
    SignsList->Add(new TSign("1.4.5", "Приближение к железнодорожному переезду", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 17500 , 300, false));
    SignsList->Add(new TSign("1.4.6", "Приближение к железнодорожному переезду", "", roDirect, spLeft, RailCross->L - 30000, RailCross->L, RailCross->L - 5000 , 300, false));
    // обратно
    // по правой стороне
    SignsList->Add(new TSign("1.4.1", "Приближение к железнодорожному переезду", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
    SignsList->Add(new TSign("1.4.2", "Приближение к железнодорожному переезду", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 17500 , 300, false));
    SignsList->Add(new TSign("1.4.3", "Приближение к железнодорожному переезду", "", roUnDirect, spRight, RailCross->L, RailCross->L + 30000, RailCross->L + 5000 , 300, false));
    // по левой стороне
    SignsList->Add(new TSign("1.4.4", "Приближение к железнодорожному переезду", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 30000 , 300, false));
    SignsList->Add(new TSign("1.4.5", "Приближение к железнодорожному переезду", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 17500 , 300, false));
    SignsList->Add(new TSign("1.4.6", "Приближение к железнодорожному переезду", "", roUnDirect, spLeft, RailCross->L, RailCross->L + 30000, RailCross->L + 5000 , 300, false));


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
        {// нашли знак
        }
        else
        {// не нашли знак, добавим информацию в список занков объекта
            Description = "[" + ((TSign*)SignsList->Items[i])->Name + "] ";

            if(((TSign*)SignsList->Items[i])->Direction == roDirect)
                Description += "[прямое] ";
            else
                Description += "[обратное] ";

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
