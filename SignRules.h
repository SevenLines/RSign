//---------------------------------------------------------------------------

#ifndef SignRulesH
#define SignRulesH
//---------------------------------------------------------------------------
class TDtaSource;
class TDictSource;
class TSignRules
{
private:
TDtaSource *Data;
TDictSource *Dict;

//���������� ��������� ����������
TRoadAttach* __fastcall FindNearestTRoadAttach(TRoadSign* curSign);
//���������� ��������� ���������� ���������
TBusStop* __fastcall FindNearestTBusStop(TRoadSign* curSign);
//���������� ��������� �������
TRailCross* __fastcall FindNearestTRailCross(TRoadSign* curSign);
//���������� ���� ������������ ����, ������������� ����� L1 � L2
TRoadSign* __fastcall FindSign(String signType, __int32 L1, __int32 L2);

//��������� ��������� �� ���� � ��������� ������
//bool __fastcall IsInTown(TRoadSign* curSign);
//��������� ��������� �� ������ � ��������� ������
bool __fastcall IsInTownDescreet(TDescreetRoadObject* curObj);
//��������� �������� �� ������� ������ �������
bool __fastcall CurrentRoadIsMain(TRoadAttach* curAttach);

public:
__fastcall TSignRules(void);
__fastcall ~TSignRules(void);
void __fastcall CheckExist(TDtaSource *data,TDictSource *dict);
void __fastcall AutoCheck(TDtaSource *data,TDictSource *dict);
//void __fastcall AddNewSigns(TDtaSource *data,TDictSource *dict);
};
#endif
