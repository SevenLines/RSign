//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "DataSour.h"
#include "SignRules.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TSignRules::TSignRules(void)
{
}
//---------------------------------------------------------------------------
__fastcall TSignRules::~TSignRules(void)
{
}
//---------------------------------------------------------------------------
//PUBLIC METHODS
//---------------------------------------------------------------------------
void __fastcall TSignRules::CheckExist(TDtaSource *data,TDictSource *dict)
{
Data=data;
Dict=dict;

bool isGood = false;

int n=0;
for (int i=0;i<Data->Objects->Count;i++){
  TRoadSign *s=dynamic_cast<TRoadSign*>(Data->Objects->Items[i]);
  if (s){
      //сначала неизвестно нужен знак или нет
      s->SetAutoTest(::stUnknown);
      if (s->NumRoadSign){
          //ShowMessage(Dict->TextProps->Items[s->MainPropId]->ShortText + " (" + String(s->L/100) + " м.)");
          String Code=Dict->GetShortTitle(s->NumRoadSign);
          //проверяем только пересечения и примыкания
          if((Code == "2.3.1") ||
           (Code == "2.3.2") ||
           (Code == "2.3.3"))
            {
//              ShowMessage(Dict->TextProps->Items[s->MainPropId]->ShortText + " (" + String(s->L/100) + " м.)");

              if(IsInTownDescreet(s)){//эти знаки в населённом пункте не ставятся
                s->SetAutoTest(stBad);
                s->SetAutoDescription("Знак находится на территории населённого пункта.");
                //ShowMessage(s->AutoDescription);
              }else{
                //находим ближайшие примыкание/перекрёсток на тойже стороне
                TRoadAttach* attach = FindNearestTRoadAttach(s);

                if(attach){
                  //проверяем расстояние между знаком и ближайшим примыканием/перекрёстком
                  __int32 distance = abs(s->L - attach->L)/100;
                  if(distance <= 300)
                    {
                      if(distance < 150)
                        {
                          s->SetAutoTest(stGood);
                          s->SetAutoDescription("Знак находится слишком близко от примыкания/перекрёстка. Возможно его необходимо перенести. (" + String(distance) + " м.)");
                          //ShowMessage(s->AutoDescription);
                        }
                      else
                        {
                          s->SetAutoTest(stGood);
                          s->SetAutoDescription("Знак находится на нужном месте. (" + String(distance) + " м.)");
                          //ShowMessage(s->AutoDescription);
                        }
                    }else{
                      s->SetAutoTest(stBad);
                      s->SetAutoDescription("Знак находится слишком далеко от примыкания/перекрёстка. (" + String(distance) + " м.)");
                      //ShowMessage(s->AutoDescription);
                    }
                }else{
                  s->SetAutoTest(stBad);
                  s->SetAutoDescription("Отсутствует примыкание/перекрёсток.");
                  //ShowMessage(s->AutoDescription);
                }
              }//конец IsInTownDescreet
              }

          //проверяем начало населённых пунктов
          if((Code == "5.22")||(Code == "5.24")){

            bool isGood = false;
            for (int i=0;i<Data->Objects->Count;i++){
              TTown *town=dynamic_cast<TTown*>(Data->Objects->Items[i]);
              if (town){
                //смотрим какое направление
                if(s->Direction == roDirect){//прямое
                  if(town->LMin == s->L){
                    isGood = true;
                  }
                }
                if(s->Direction == roUnDirect){//обратное
                  if(town->LMax == s->L){
                    isGood = true;
                  }
                }
              }
            }
            if(isGood){
              s->SetAutoTest(stGood);
              s->SetAutoDescription("Знак находится на нужном месте.");
              //ShowMessage(s->AutoDescription);
            }else{
              s->SetAutoTest(stBad);
              s->SetAutoDescription("Знак не совпадает с началом населённого пункта.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //проверяем конец населённых пунктов
          if((Code == "5.23") || (Code == "5.25")){

            isGood = false;
            for (int i=0;i<Data->Objects->Count;i++){
              TTown *town=dynamic_cast<TTown*>(Data->Objects->Items[i]);
              if (town){
                //смотрим какое направление
                if(s->Direction == roDirect){//прямое
                  if(town->LMax == s->L){
                    isGood = true;
                  }
                }
                if(s->Direction == roUnDirect){//обратное
                  if(town->LMin == s->L){
                    isGood = true;
                  }
                }
              }
            }
            if(isGood){
              s->SetAutoTest(stGood);
              s->SetAutoDescription("Знак находится на нужном месте.");
              //ShowMessage(s->AutoDescription);
            }else{
              s->SetAutoTest(stBad);
              s->SetAutoDescription("Знак не совпадает с концом населённого пункта.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //проверяем знак автобусной остановки
          if(Code == "5.12"){
            TBusStop* busStop = FindNearestTBusStop(s);
            if(busStop){//если автобусная остановка найдена
              __int32 distance = abs(s->L - busStop->L)/100;
              if(distance<10){//если в пределах 10 метров есть авт. остановка
                s->SetAutoTest(stGood);
                s->SetAutoDescription("Знак находится на нужном месте.");
                //ShowMessage(s->AutoDescription);
              }else{//если в пределах 10 метров нет авт. остановки
                s->SetAutoTest(stBad);
                s->SetAutoDescription("Автобусная остановка находится на растоянии больше 10 метров.");
                //ShowMessage(s->AutoDescription);
              }
            }else{//если автобусная остановка не найдена
              s->SetAutoTest(stBad);
              s->SetAutoDescription("Нет автобусной остановки.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //проверяем знак переезда (1.1 и 1.2) ->>
          if((Code == "1.2")||(Code == "1.1")){
            TRailCross* railCross = FindNearestTRailCross(s);
            if(railCross){//если переезд найден
              __int32 distance = abs(s->L - railCross->L)/100;
              if(distance <= 300){//
                if((Code == "1.2")&&
                  ((railCross->SignalKind == rcsSigns)||(railCross->SignalKind == rcsSound)||(railCross->SignalKind == rcsSemaphor))){
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("Знак находится на нужном месте.");
                  //ShowMessage(s->AutoDescription);
                }else if((Code == "1.1")&&
                  ((railCross->SignalKind == rcsMBlock)||(railCross->SignalKind == rcsEBlock)||(railCross->SignalKind == rcsABlock))){
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("Знак находится на нужном месте.");
                  //ShowMessage(s->AutoDescription);
                }else{
                  s->SetAutoTest(stBad);
                  s->SetAutoDescription("Не соответсятвие знака и наличия шлагбаума.");
                  //ShowMessage(s->AutoDescription);
                }
              }else{//если в пределах 300 метров нет переезда
                s->SetAutoTest(stBad);
                s->SetAutoDescription("Переезд находится на растоянии больше 300 метров.");
                //ShowMessage(s->AutoDescription);
              }
            }else{//если переезд не найден
              s->SetAutoTest(stBad);
              s->SetAutoDescription("Нет переезда.");
              //ShowMessage(s->AutoDescription);
            }
          }//проверяем знак переезда (1.1 и 1.2) <<-

          /*
          //проверяем знак переезда (1.4.1) ->>
          if(Dict->TextProps->Items[s->MainPropId]->ShortText == "1.4.1"){
            TRailCross* railCross = FindNearestTRailCross(s);
            if(railCross){//если переезд найден
              __int32 distance = abs(s->L - railCross->L)/100;
              if(distance <= 300){//если переезд в пределах 300 метров
                //знак должен быть расположен совместно со знаком 1.1 или 1.2
                //найдём его
                isGood = false;
                for (int i=0;i<Data->Objects->Count;i++){
                  TRoadSign *tmpSign=dynamic_cast<TRoadSign*>(Data->Objects->Items[i]);
                  if (tmpSign){
                    if(((Dict->TextProps->Items[tmpSign->MainPropId]->ShortText == "1.1")||
                      (Dict->TextProps->Items[tmpSign->MainPropId]->ShortText == "1.2"))&&
                      (tmpSign->L == s->L)){
                        isGood = true;
                      }
                  }
                }
                if(isGood){
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("Знак находится на нужном месте.");
                  ShowMessage(s->AutoDescription);
                }else{
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("Необходимо установить этот знак совместно со знаком 1.1 или 1.2.");
                  ShowMessage(s->AutoDescription);
                }

                //далее ищем знак 1.4.2 между переездом и знаком 1.4.1
                __int32 direct;
                direct = s->Direction;
                if(direct == roDirect){
                  tmpSign = FindSign("1.4.2", s->L, railCross->L);
                }
                if(direct == roUnDirect){
                  tmpSign = FindSign("1.4.2", railCross->L, s->L);
                }
                if(tmpSign){
                  if(tmpSign->Direction == direct){
                    tmpSign->SetAutoTest(stGood);
                    tmpSign->SetAutoDescription("Знак находится на нужном месте.");
                    ShowMessage(tmpSign->AutoDescription);
                  }
                //ищем знак 1.4.3 в зависимости от того, нашли мы 1.4.2 или нет
                  if(direct == roDirect){
                    tmpSign = FindSign("1.4.3", tmpSign->L, railCross->L);
                  }
                  if(direct == roUnDirect){
                    tmpSign = FindSign("1.4.3", railCross->L, tmpSign->L);
                  }
                }else{//если не найден знак 1.4.2
                  if(direct == roDirect){
                    tmpSign = FindSign("1.4.3", s->L, railCross->L);
                  }
                  if(direct == roUnDirect){
                    tmpSign = FindSign("1.4.3", railCross->L, s->L);
                  }
                }

                //далее ищем знак 1.4.3 между переездом и знаком 1.4.2
                if(tmpSign){
                  if(tmpSign->Direction == direct){
                    //знак должен быть расположен совместно со знаком 1.1 или 1.2
                    //найдём его
                    isGood = false;
                    for (int i=0;i<Data->Objects->Count;i++){
                      TRoadSign *tmpSign2=dynamic_cast<TRoadSign*>(Data->Objects->Items[i]);
                      if (tmpSign2){
                        if(((Dict->TextProps->Items[tmpSign2->MainPropId]->ShortText == "1.1")||
                          (Dict->TextProps->Items[tmpSign2->MainPropId]->ShortText == "1.2"))&&
                          (tmpSign2->L == tmpSign->L)){
                            isGood = true;
                          }
                      }
                    }
                    if(isGood){
                      tmpSign->SetAutoTest(stGood);
                      tmpSign->SetAutoDescription("Знак находится на нужном месте.");
                      ShowMessage(tmpSign->AutoDescription);
                    }else{
                      tmpSign->SetAutoTest(stGood);
                      tmpSign->SetAutoDescription("Необходимо установить этот знак совместно со знаком 1.1 или 1.2.");
                      ShowMessage(tmpSign->AutoDescription);
                    }
                  }
                }
              }else{//если переезд дальше чем в 300 метрах
                s->SetAutoTest(stBad);
                s->SetAutoDescription("Переезд находится на растоянии больше 300 метров.");
                ShowMessage(s->AutoDescription);
              }
            }else{//если переезд не найден
              s->SetAutoTest(stBad);
              s->SetAutoDescription("Нет переезда.");
              ShowMessage(s->AutoDescription);
            }
          }
          //проверяем знак переезда (1.4.1) <<-
          */
          //----------------------------------
        }
     }
  }
}
//---------------------------------------------------------------------------
//void __fastcall TSignRules::AddNewSigns(TDtaSource *data,TDictSource *dict)
//{
//Data=data;
//Dict=dict;
//}
//---------------------------------------------------------------------------
//пытаемся автоматически расставить знаки
void __fastcall TSignRules::AutoCheck(TDtaSource *data,TDictSource *dict){
  Data = data;
  Dict = dict;

  TRoadSign *tmpSign;//для проверки существования знака

  for (int i=0;i<data->Objects->Count;i++){

    //примыкания ->>
    TRoadAttach *attach = dynamic_cast<TRoadAttach*>(Data->Objects->Items[i]);
    if (attach){//если это примыкание
      if(!IsInTownDescreet(attach)){//если не в населённом пункте
        switch(attach->Placement){//проверяем тип примыкания
          case apRight://примыкание справа
            if(CurrentRoadIsMain(attach)){
              //добавляем три знака
              tmpSign = FindSign("2.3.2", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.2", "", "Примыкание справа",false);
              }
              tmpSign = FindSign("2.3.3", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.3", "", "Примыкание слева",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L, 2000, "2.4", "", "Уступи дорогу",true);
              }
            }else{
              //если текущая дорога не главная
            }
          break;
          case apLeft://примыкание слева
            if(CurrentRoadIsMain(attach)){
              //добавляем три знака
              tmpSign = FindSign("2.3.3", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.3", "", "Примыкание слева",false);
              }
              tmpSign = FindSign("2.3.2", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.2", "", "Примыкание справа",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L, 2000, "2.4", "", "Уступи дорогу",true);
              }
            }else{
              //если текущая дорога не главная
            }
          break;
          case apCross://пересечение
            if(CurrentRoadIsMain(attach)){
              //добавляем четыре знака
              tmpSign = FindSign("2.3.1", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой",false);
              }
              tmpSign = FindSign("2.3.1", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.1", "", "Пересечение со второстепенной дорогой",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L, 2000, "2.4", "", "Уступи дорогу",true);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L, 2000, "2.4", "", "Уступи дорогу",true);
              }
            }else{
              //если текущая дорога не главная
            }
          break;
        }
      }
    }
    //примыкания <<-
    /*
    //НП ->>
    TTown *town = dynamic_cast<TTown*>(Data->Objects->Items[i]);
    if (town){//если это мост
      tmpSign = FindSign("5.22", town->LMin - 200 , town->LMin + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.24", town->LMin - 200 , town->LMin + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roDirect, spRight, town->LMin, 200, "2.22", "", "Начало НП");
        }
      }
      tmpSign = FindSign("5.23", town->LMin - 200 , town->LMin + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.25", town->LMin - 200 , town->LMin + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roUnDirect, spLeft, town->LMin, 200, "2.24", "", "Конец НП");
        }
      }

      tmpSign = FindSign("5.23", town->LMax - 200 , town->LMax + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.25", town->LMax - 200 , town->LMax + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roUnDirect, spLeft, town->LMax, 200, "2.24", "", "Конец НП");
        }
      }

      tmpSign = FindSign("5.22", town->LMax - 200 , town->LMax + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.24", town->LMax - 200 , town->LMax + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roDirect, spRight, town->LMax, 200, "2.22", "", "Начало НП");
        }
      }
    }*/
    //НП <<-

    /*
    //мосты ->>
    TRoadBridge *bridge = dynamic_cast<TRoadBridge*>(Data->Objects->Items[i]);
    if (bridge){//если это мост
      //ставим знак сужения дороги, если он нужен

      //ставим знак "Ограничение массы", если нужно

      //ставим знак 5.26 "Наименование объекта", если нужно
    }
    //мосты <<-
    */

    //автобусная остановка ->>
    TBusStop *busStop = dynamic_cast<TBusStop*>(Data->Objects->Items[i]);
    if (busStop){//если это автобусная остановка
      //ставим знаки автобусной остановки 5.12
      tmpSign = FindSign("5.12", busStop->L - 200, busStop->L + 200);
      if(!tmpSign){
        Data->AddPrjSign(Dict, roDirect, spRight, busStop->L, 200, "5.12", "", "Автобусная остановка.",false);
      }
    }
    //автобусная остановка <<-
    /*
    //переезд ->>
    /**TRailCross *railCross = dynamic_cast<TRailCross*>(Data->Objects->Items[i]);
    if (railCross){//если это переезд
      //определяем его направление (прямое/обратное)
      //ставим знаки
      //проверяем, есть шлагбаум или нет
      //...
      tmpSign = FindSign("5.12", railCross->L - 200, railCross->L + 200);
      if(!tmpSign){

      }

    }*/
    //переезд <<-

  }
Data->AddFromBufer();
}
//---------------------------------------------------------------------------
//PRIVATE METHODS
//---------------------------------------------------------------------------
TRoadAttach* __fastcall TSignRules::FindNearestTRoadAttach(TRoadSign* curSign)
{
  __int32 curDistance = 999999;
  __int32 minDistance = 999999;
  __int32 attachType;//тип примыкания: пересечение или примыкание
  __int32 sideFactor;//сторона, на которой ищем примыкание
  TRoadAttach *nearestAttach;
  __int32 signL = curSign->L;

  //2.3.1 - пересечение
  //2.3.2 - примыкание справа
  //2.3.3 - примыкание слева
  //определиим что ищем, примыкание или пересечение
  String Code=Dict->GetShortTitle(curSign->NumRoadSign);
  if(Code == "2.3.1"){
    //пересечение
    attachType = apCross;
  }
  if(Code == "2.3.2"){
    if(curSign->Direction == roDirect){//прямое направление
      //
      attachType = apRight;//ищем справа
      sideFactor = 1;
     }
    if(curSign->Direction == roUnDirect){//обратное направление
      //
      attachType = apLeft;//ищем слева
      sideFactor = -1;
    }
  }

  if(Code == "2.3.3"){
    if(curSign->Direction == roDirect){//прямое направление
      //
      attachType = apLeft;//ищем слева
      sideFactor = 1;
    }
    if(curSign->Direction == roUnDirect){//обратное направление
      //
      attachType = apRight;//ищем справа
      sideFactor = -1;
    }
  }

  for (int i=0;i<Data->Objects->Count;i++)
    {
    TRoadAttach *s=dynamic_cast<TRoadAttach*>(Data->Objects->Items[i]);
    if (s){
      if(s->Placement == attachType){
          curDistance = sideFactor*(s->L - signL);
          if((curDistance < minDistance) && (curDistance >= 0))
            {
              minDistance = curDistance;
              nearestAttach = s;
            }
        }
      }
    }

  if(minDistance == 999999)
    {
      return NULL;
    }
  else
    {
      return nearestAttach;
    }
}
//---------------------------------------------------------------------------
TBusStop* __fastcall TSignRules::FindNearestTBusStop(TRoadSign* curSign){

  __int32 sideFactor = 1;
  __int32 curDistance = 999999;
  __int32 minDistance = 999999;
  TBusStop *nearestBusStop;

  __int32 signL = curSign->L;

  if(curSign->Direction == roUnDirect){//обратное направление
    sideFactor = -1;
  }

  for (int i=0;i<Data->Objects->Count;i++){
    TBusStop *busStop = dynamic_cast<TBusStop*>(Data->Objects->Items[i]);
    if (busStop){
      curDistance = sideFactor*(busStop->L - signL);
      if((curDistance < minDistance) && (curDistance >= 0)){
        minDistance = curDistance;
        nearestBusStop = busStop;
      }
    }
  }

  return nearestBusStop;
}
//---------------------------------------------------------------------------
TRailCross* __fastcall TSignRules::FindNearestTRailCross(TRoadSign* curSign){

  __int32 sideFactor = 1;
  __int32 curDistance = 999999;
  __int32 minDistance = 999999;
  TRailCross *nearestRailCross;

  __int32 signL = curSign->L;

  if(curSign->Direction == roUnDirect){//обратное направление
    sideFactor = -1;
  }

  for (int i=0;i<Data->Objects->Count;i++){
    TRailCross *railCross = dynamic_cast<TRailCross*>(Data->Objects->Items[i]);
    if (railCross){
      curDistance = sideFactor*(railCross->L - signL);
      if((curDistance < minDistance) && (curDistance >= 0)){
        minDistance = curDistance;
        nearestRailCross = railCross;
      }
    }
  }
  return nearestRailCross;
}
//---------------------------------------------------------------------------
bool __fastcall TSignRules::IsInTownDescreet(TDescreetRoadObject* curObj)
{
  for (int i=0;i<Data->Objects->Count;i++){
    //здесь перебираем все населённые пункты
    TTown *s=dynamic_cast<TTown*>(Data->Objects->Items[i]);
    if (s){
      if((s->LMin <= curObj->L)&&(s->LMax >= curObj->L)){
        return true;
      }else{
        return false;
      }
    }
  }
  return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSignRules::CurrentRoadIsMain(TRoadAttach* curAttach){
  return true;
}
//---------------------------------------------------------------------------
TRoadSign* __fastcall TSignRules::FindSign(String signType, __int32 L1, __int32 L2){
  for (int i=0;i<Data->Objects->Count;i++){
    //здесь перебираем все населённые пункты
    TRoadSign *roadSign=dynamic_cast<TRoadSign*>(Data->Objects->Items[i]);
    if (roadSign)
      if (roadSign->NumRoadSign)
      {
      String Code=Dict->GetShortTitle(roadSign->NumRoadSign);
      if((Code == signType)&&
        (roadSign->L >= L1)&&
        (roadSign->L <= L2)){
        return roadSign;
      }
    }
  }
  return NULL;
}
