//---------------------------------------------------------------------------

#ifndef DesignPatternH
#define DesignPatternH

#include "RoadObj.h"
#include "DataSour.h"

//---------------------------------------------------------------------------
class TDesignMetricsPattern
{
public:
virtual bool __fastcall Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict)
    {return false;}
};

class TDesignAttachVer1 : public TDesignMetricsPattern
{
protected:
int *CodesL;
int *CodesR;
int PtCount;
public:
virtual bool __fastcall Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict);
};

class TDesignAttachVer2: public TDesignAttachVer1
{
public:
virtual bool __fastcall Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict);
};


class TDesignAttachVer1_1 : public TDesignAttachVer1
{
public:
__fastcall TDesignAttachVer1_1(void);
};

class TDesignAttachVer1_2 : public TDesignAttachVer1
{
public:
__fastcall TDesignAttachVer1_2(void);
};

// Отличается от версии 1 тем что добавляет сигнальные столбики
class TDesignAttachVer2_1 : public TDesignAttachVer2
{
public:
__fastcall TDesignAttachVer2_1(void);
};

class TDesignAttachVer2_2 : public TDesignAttachVer2
{
public:
__fastcall TDesignAttachVer2_2(void);
};

class TDesignAttachVer3 : public TDesignMetricsPattern
{
public:
virtual bool __fastcall Design(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict);
};

const int DesignersCount=5;
extern PACKAGE TDesignMetricsPattern *Designers[5];
extern PACKAGE String DesignersName[5];

#endif
