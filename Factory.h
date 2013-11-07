//---------------------------------------------------------------------------

#ifndef FactoryH
#define FactoryH

#include <Classes.hpp>
#include "Metrics.h"
//---------------------------------------------------------------------------
class TDictSource;
class TRoadObject;
class TCharacter;

class TRoadObjFactory
{
private:
TDictSource *FDict;
public:
__fastcall TRoadObjFactory(void) {}
TRoadObject* __fastcall CreateRoadObj(String ClassName,__int32 id,__int32 code);
String __fastcall GetClassInfo(String ClassName);
TExtPolyline* __fastcall GetDefaultMetric(String ClassName,TRect &r);
TCharacter * __fastcall CreateCharacter(__int32 CharCode,String CharName,String CharVal);
TCharacter * __fastcall CreateCharacter(__int32 CharCode,String CharVal);
__property TDictSource* Dict={read=FDict,write=FDict};
};


#endif
