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
      //������� ���������� ����� ���� ��� ���
      s->SetAutoTest(::stUnknown);
      if (s->NumRoadSign){
          //ShowMessage(Dict->TextProps->Items[s->MainPropId]->ShortText + " (" + String(s->L/100) + " �.)");
          String Code=Dict->GetShortTitle(s->NumRoadSign);
          //��������� ������ ����������� � ����������
          if((Code == "2.3.1") ||
           (Code == "2.3.2") ||
           (Code == "2.3.3"))
            {
//              ShowMessage(Dict->TextProps->Items[s->MainPropId]->ShortText + " (" + String(s->L/100) + " �.)");

              if(IsInTownDescreet(s)){//��� ����� � ��������� ������ �� ��������
                s->SetAutoTest(stBad);
                s->SetAutoDescription("���� ��������� �� ���������� ���������� ������.");
                //ShowMessage(s->AutoDescription);
              }else{
                //������� ��������� ����������/���������� �� ����� �������
                TRoadAttach* attach = FindNearestTRoadAttach(s);

                if(attach){
                  //��������� ���������� ����� ������ � ��������� �����������/�����������
                  __int32 distance = abs(s->L - attach->L)/100;
                  if(distance <= 300)
                    {
                      if(distance < 150)
                        {
                          s->SetAutoTest(stGood);
                          s->SetAutoDescription("���� ��������� ������� ������ �� ����������/����������. �������� ��� ���������� ���������. (" + String(distance) + " �.)");
                          //ShowMessage(s->AutoDescription);
                        }
                      else
                        {
                          s->SetAutoTest(stGood);
                          s->SetAutoDescription("���� ��������� �� ������ �����. (" + String(distance) + " �.)");
                          //ShowMessage(s->AutoDescription);
                        }
                    }else{
                      s->SetAutoTest(stBad);
                      s->SetAutoDescription("���� ��������� ������� ������ �� ����������/����������. (" + String(distance) + " �.)");
                      //ShowMessage(s->AutoDescription);
                    }
                }else{
                  s->SetAutoTest(stBad);
                  s->SetAutoDescription("����������� ����������/����������.");
                  //ShowMessage(s->AutoDescription);
                }
              }//����� IsInTownDescreet
              }

          //��������� ������ ��������� �������
          if((Code == "5.22")||(Code == "5.24")){

            bool isGood = false;
            for (int i=0;i<Data->Objects->Count;i++){
              TTown *town=dynamic_cast<TTown*>(Data->Objects->Items[i]);
              if (town){
                //������� ����� �����������
                if(s->Direction == roDirect){//������
                  if(town->LMin == s->L){
                    isGood = true;
                  }
                }
                if(s->Direction == roUnDirect){//��������
                  if(town->LMax == s->L){
                    isGood = true;
                  }
                }
              }
            }
            if(isGood){
              s->SetAutoTest(stGood);
              s->SetAutoDescription("���� ��������� �� ������ �����.");
              //ShowMessage(s->AutoDescription);
            }else{
              s->SetAutoTest(stBad);
              s->SetAutoDescription("���� �� ��������� � ������� ���������� ������.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //��������� ����� ��������� �������
          if((Code == "5.23") || (Code == "5.25")){

            isGood = false;
            for (int i=0;i<Data->Objects->Count;i++){
              TTown *town=dynamic_cast<TTown*>(Data->Objects->Items[i]);
              if (town){
                //������� ����� �����������
                if(s->Direction == roDirect){//������
                  if(town->LMax == s->L){
                    isGood = true;
                  }
                }
                if(s->Direction == roUnDirect){//��������
                  if(town->LMin == s->L){
                    isGood = true;
                  }
                }
              }
            }
            if(isGood){
              s->SetAutoTest(stGood);
              s->SetAutoDescription("���� ��������� �� ������ �����.");
              //ShowMessage(s->AutoDescription);
            }else{
              s->SetAutoTest(stBad);
              s->SetAutoDescription("���� �� ��������� � ������ ���������� ������.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //��������� ���� ���������� ���������
          if(Code == "5.12"){
            TBusStop* busStop = FindNearestTBusStop(s);
            if(busStop){//���� ���������� ��������� �������
              __int32 distance = abs(s->L - busStop->L)/100;
              if(distance<10){//���� � �������� 10 ������ ���� ���. ���������
                s->SetAutoTest(stGood);
                s->SetAutoDescription("���� ��������� �� ������ �����.");
                //ShowMessage(s->AutoDescription);
              }else{//���� � �������� 10 ������ ��� ���. ���������
                s->SetAutoTest(stBad);
                s->SetAutoDescription("���������� ��������� ��������� �� ��������� ������ 10 ������.");
                //ShowMessage(s->AutoDescription);
              }
            }else{//���� ���������� ��������� �� �������
              s->SetAutoTest(stBad);
              s->SetAutoDescription("��� ���������� ���������.");
              //ShowMessage(s->AutoDescription);
            }
          }

          //��������� ���� �������� (1.1 � 1.2) ->>
          if((Code == "1.2")||(Code == "1.1")){
            TRailCross* railCross = FindNearestTRailCross(s);
            if(railCross){//���� ������� ������
              __int32 distance = abs(s->L - railCross->L)/100;
              if(distance <= 300){//
                if((Code == "1.2")&&
                  ((railCross->SignalKind == rcsSigns)||(railCross->SignalKind == rcsSound)||(railCross->SignalKind == rcsSemaphor))){
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("���� ��������� �� ������ �����.");
                  //ShowMessage(s->AutoDescription);
                }else if((Code == "1.1")&&
                  ((railCross->SignalKind == rcsMBlock)||(railCross->SignalKind == rcsEBlock)||(railCross->SignalKind == rcsABlock))){
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("���� ��������� �� ������ �����.");
                  //ShowMessage(s->AutoDescription);
                }else{
                  s->SetAutoTest(stBad);
                  s->SetAutoDescription("�� ������������� ����� � ������� ���������.");
                  //ShowMessage(s->AutoDescription);
                }
              }else{//���� � �������� 300 ������ ��� ��������
                s->SetAutoTest(stBad);
                s->SetAutoDescription("������� ��������� �� ��������� ������ 300 ������.");
                //ShowMessage(s->AutoDescription);
              }
            }else{//���� ������� �� ������
              s->SetAutoTest(stBad);
              s->SetAutoDescription("��� ��������.");
              //ShowMessage(s->AutoDescription);
            }
          }//��������� ���� �������� (1.1 � 1.2) <<-

          /*
          //��������� ���� �������� (1.4.1) ->>
          if(Dict->TextProps->Items[s->MainPropId]->ShortText == "1.4.1"){
            TRailCross* railCross = FindNearestTRailCross(s);
            if(railCross){//���� ������� ������
              __int32 distance = abs(s->L - railCross->L)/100;
              if(distance <= 300){//���� ������� � �������� 300 ������
                //���� ������ ���� ���������� ��������� �� ������ 1.1 ��� 1.2
                //����� ���
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
                  s->SetAutoDescription("���� ��������� �� ������ �����.");
                  ShowMessage(s->AutoDescription);
                }else{
                  s->SetAutoTest(stGood);
                  s->SetAutoDescription("���������� ���������� ���� ���� ��������� �� ������ 1.1 ��� 1.2.");
                  ShowMessage(s->AutoDescription);
                }

                //����� ���� ���� 1.4.2 ����� ��������� � ������ 1.4.1
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
                    tmpSign->SetAutoDescription("���� ��������� �� ������ �����.");
                    ShowMessage(tmpSign->AutoDescription);
                  }
                //���� ���� 1.4.3 � ����������� �� ����, ����� �� 1.4.2 ��� ���
                  if(direct == roDirect){
                    tmpSign = FindSign("1.4.3", tmpSign->L, railCross->L);
                  }
                  if(direct == roUnDirect){
                    tmpSign = FindSign("1.4.3", railCross->L, tmpSign->L);
                  }
                }else{//���� �� ������ ���� 1.4.2
                  if(direct == roDirect){
                    tmpSign = FindSign("1.4.3", s->L, railCross->L);
                  }
                  if(direct == roUnDirect){
                    tmpSign = FindSign("1.4.3", railCross->L, s->L);
                  }
                }

                //����� ���� ���� 1.4.3 ����� ��������� � ������ 1.4.2
                if(tmpSign){
                  if(tmpSign->Direction == direct){
                    //���� ������ ���� ���������� ��������� �� ������ 1.1 ��� 1.2
                    //����� ���
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
                      tmpSign->SetAutoDescription("���� ��������� �� ������ �����.");
                      ShowMessage(tmpSign->AutoDescription);
                    }else{
                      tmpSign->SetAutoTest(stGood);
                      tmpSign->SetAutoDescription("���������� ���������� ���� ���� ��������� �� ������ 1.1 ��� 1.2.");
                      ShowMessage(tmpSign->AutoDescription);
                    }
                  }
                }
              }else{//���� ������� ������ ��� � 300 ������
                s->SetAutoTest(stBad);
                s->SetAutoDescription("������� ��������� �� ��������� ������ 300 ������.");
                ShowMessage(s->AutoDescription);
              }
            }else{//���� ������� �� ������
              s->SetAutoTest(stBad);
              s->SetAutoDescription("��� ��������.");
              ShowMessage(s->AutoDescription);
            }
          }
          //��������� ���� �������� (1.4.1) <<-
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
//�������� ������������� ���������� �����
void __fastcall TSignRules::AutoCheck(TDtaSource *data,TDictSource *dict){
  Data = data;
  Dict = dict;

  TRoadSign *tmpSign;//��� �������� ������������� �����

  for (int i=0;i<data->Objects->Count;i++){

    //���������� ->>
    TRoadAttach *attach = dynamic_cast<TRoadAttach*>(Data->Objects->Items[i]);
    if (attach){//���� ��� ����������
      if(!IsInTownDescreet(attach)){//���� �� � ��������� ������
        switch(attach->Placement){//��������� ��� ����������
          case apRight://���������� ������
            if(CurrentRoadIsMain(attach)){
              //��������� ��� �����
              tmpSign = FindSign("2.3.2", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.2", "", "���������� ������",false);
              }
              tmpSign = FindSign("2.3.3", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.3", "", "���������� �����",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L, 2000, "2.4", "", "������ ������",true);
              }
            }else{
              //���� ������� ������ �� �������
            }
          break;
          case apLeft://���������� �����
            if(CurrentRoadIsMain(attach)){
              //��������� ��� �����
              tmpSign = FindSign("2.3.3", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.3", "", "���������� �����",false);
              }
              tmpSign = FindSign("2.3.2", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.2", "", "���������� ������",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L, 2000, "2.4", "", "������ ������",true);
              }
            }else{
              //���� ������� ������ �� �������
            }
          break;
          case apCross://�����������
            if(CurrentRoadIsMain(attach)){
              //��������� ������ �����
              tmpSign = FindSign("2.3.1", attach->L - 30000, attach->L);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L - 15500, 200, "2.3.1", "", "����������� �� �������������� �������",false);
              }
              tmpSign = FindSign("2.3.1", attach->L, attach->L + 30000);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L + 15500, 200, "2.3.1", "", "����������� �� �������������� �������",false);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roDirect, spRight, attach->L, 2000, "2.4", "", "������ ������",true);
              }
              tmpSign = FindSign("2.4", attach->L - 500, attach->L + 500);
              if(!tmpSign){
                Data->AddPrjSign(Dict, roUnDirect, spRight, attach->L, 2000, "2.4", "", "������ ������",true);
              }
            }else{
              //���� ������� ������ �� �������
            }
          break;
        }
      }
    }
    //���������� <<-
    /*
    //�� ->>
    TTown *town = dynamic_cast<TTown*>(Data->Objects->Items[i]);
    if (town){//���� ��� ����
      tmpSign = FindSign("5.22", town->LMin - 200 , town->LMin + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.24", town->LMin - 200 , town->LMin + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roDirect, spRight, town->LMin, 200, "2.22", "", "������ ��");
        }
      }
      tmpSign = FindSign("5.23", town->LMin - 200 , town->LMin + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.25", town->LMin - 200 , town->LMin + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roUnDirect, spLeft, town->LMin, 200, "2.24", "", "����� ��");
        }
      }

      tmpSign = FindSign("5.23", town->LMax - 200 , town->LMax + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.25", town->LMax - 200 , town->LMax + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roUnDirect, spLeft, town->LMax, 200, "2.24", "", "����� ��");
        }
      }

      tmpSign = FindSign("5.22", town->LMax - 200 , town->LMax + 200);
      if(!tmpSign){
        tmpSign = FindSign("5.24", town->LMax - 200 , town->LMax + 200);
        if(!tmpSign){
          Data->AddPrjSign(Dict, roDirect, spRight, town->LMax, 200, "2.22", "", "������ ��");
        }
      }
    }*/
    //�� <<-

    /*
    //����� ->>
    TRoadBridge *bridge = dynamic_cast<TRoadBridge*>(Data->Objects->Items[i]);
    if (bridge){//���� ��� ����
      //������ ���� ������� ������, ���� �� �����

      //������ ���� "����������� �����", ���� �����

      //������ ���� 5.26 "������������ �������", ���� �����
    }
    //����� <<-
    */

    //���������� ��������� ->>
    TBusStop *busStop = dynamic_cast<TBusStop*>(Data->Objects->Items[i]);
    if (busStop){//���� ��� ���������� ���������
      //������ ����� ���������� ��������� 5.12
      tmpSign = FindSign("5.12", busStop->L - 200, busStop->L + 200);
      if(!tmpSign){
        Data->AddPrjSign(Dict, roDirect, spRight, busStop->L, 200, "5.12", "", "���������� ���������.",false);
      }
    }
    //���������� ��������� <<-
    /*
    //������� ->>
    /**TRailCross *railCross = dynamic_cast<TRailCross*>(Data->Objects->Items[i]);
    if (railCross){//���� ��� �������
      //���������� ��� ����������� (������/��������)
      //������ �����
      //���������, ���� �������� ��� ���
      //...
      tmpSign = FindSign("5.12", railCross->L - 200, railCross->L + 200);
      if(!tmpSign){

      }

    }*/
    //������� <<-

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
  __int32 attachType;//��� ����������: ����������� ��� ����������
  __int32 sideFactor;//�������, �� ������� ���� ����������
  TRoadAttach *nearestAttach;
  __int32 signL = curSign->L;

  //2.3.1 - �����������
  //2.3.2 - ���������� ������
  //2.3.3 - ���������� �����
  //���������� ��� ����, ���������� ��� �����������
  String Code=Dict->GetShortTitle(curSign->NumRoadSign);
  if(Code == "2.3.1"){
    //�����������
    attachType = apCross;
  }
  if(Code == "2.3.2"){
    if(curSign->Direction == roDirect){//������ �����������
      //
      attachType = apRight;//���� ������
      sideFactor = 1;
     }
    if(curSign->Direction == roUnDirect){//�������� �����������
      //
      attachType = apLeft;//���� �����
      sideFactor = -1;
    }
  }

  if(Code == "2.3.3"){
    if(curSign->Direction == roDirect){//������ �����������
      //
      attachType = apLeft;//���� �����
      sideFactor = 1;
    }
    if(curSign->Direction == roUnDirect){//�������� �����������
      //
      attachType = apRight;//���� ������
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

  if(curSign->Direction == roUnDirect){//�������� �����������
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

  if(curSign->Direction == roUnDirect){//�������� �����������
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
    //����� ���������� ��� ��������� ������
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
    //����� ���������� ��� ��������� ������
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
