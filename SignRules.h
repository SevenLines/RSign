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

//возвращает блажайшее примыкание
TRoadAttach* __fastcall FindNearestTRoadAttach(TRoadSign* curSign);
//возвращает блажайшую автобусную остановку
TBusStop* __fastcall FindNearestTBusStop(TRoadSign* curSign);
//возвращает блажайший переезд
TRailCross* __fastcall FindNearestTRailCross(TRoadSign* curSign);
//возвращает знак определённого типа, расположенный между L1 и L2
TRoadSign* __fastcall FindSign(String signType, __int32 L1, __int32 L2);

//проверяет находится ли знак в населённом пункте
//bool __fastcall IsInTown(TRoadSign* curSign);
//проверяет находится ли объект в населённом пункте
bool __fastcall IsInTownDescreet(TDescreetRoadObject* curObj);
//проверяет является ли текущая дорога главной
bool __fastcall CurrentRoadIsMain(TRoadAttach* curAttach);

public:
__fastcall TSignRules(void);
__fastcall ~TSignRules(void);
void __fastcall CheckExist(TDtaSource *data,TDictSource *dict);
void __fastcall AutoCheck(TDtaSource *data,TDictSource *dict);
//void __fastcall AddNewSigns(TDtaSource *data,TDictSource *dict);
};
#endif
