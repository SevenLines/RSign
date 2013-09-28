//---------------------------------------------------------------------------
#ifndef FileSourH
#define FileSourH
//---------------------------------------------------------------------------
#include "DataSour.h"
//---------------------------------------------------------------------------
class TFileSharedObjSource : public TSharedObjSource
{
public:
__fastcall TFileSharedObjSource(void);
void virtual __fastcall Load(void);
};

class TFileDictSource : public TDictSource
{
public:
__fastcall TFileDictSource(void);
__fastcall TFileDictSource(__int32);
void virtual __fastcall Load(__int32);
};

class TFileDataSource : public TDtaSource
{
private:
String FFileName;
public:
__fastcall TFileDataSource(void);
__fastcall TFileDataSource(String filename,TDictSource *Dict,TRoadObjFactory *factory);
void virtual __fastcall Load(__int32 id_,__int32 dataclass_,TDictSource *Dict);
};
#endif
