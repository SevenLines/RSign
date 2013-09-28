//---------------------------------------------------------------------------
#ifndef BaseSourH
#define BaseSourH
//---------------------------------------------------------------------------
// Файл содержит два класса обеспечивающих
// доступ к базе данных.
// Wrote By Martinenko O.
//---------------------------------------------------------------------------
#include "DataSour.h"
//---------------------------------------------------------------------------
class TFileDictSource : public TDictSource
{
public:
__fastcall TFileDictSource(void);
__fastcall TFileDictSource(__int32);
void virtual __fastcall Load(__int32 Id);
};

class TFileDataSource : public TDtaSource
{
public:
__fastcall TFileDataSource(void);
__fastcall TFileDataSource(__int32);
void virtual __fastcall Load(__int32 Id,__int32 dataclass,TDictSource*);
};

#endif
