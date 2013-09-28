//---------------------------------------------------------------------------

#ifndef SignDesignH
#define SignDesignH
#include "RoadObj.h"
#include "RoadDict.h"
#include "DataSour.h"

typedef bool __fastcall (__closure *TTestBreak)(TRoadObject*);
// ����� ��� �������� �������� ��������� ��������� ������
class TSignDesignData
{
int FCrossMaxLen;
int FMaxLenToAttachSignInSity;
int FMaxLenToAttachSign;
int FLenToAttachSignInSity;
int FLenToAttachSign;
int FSignOffset;
int FSignToSign;
int FSignToSignInSity;
int FAttachToSign;
int FSign24ToAttach;
int FTownToSign;
int FSignToBusStop;
int FMaxSignToBusStop;
int FMaxSignToBridge;
int FMaxSignToKm;
public:
__fastcall TSignDesignData(void)
    {
    FCrossMaxLen=500;
    FMaxLenToAttachSignInSity=10000;
    FMaxLenToAttachSign=30000;
    FLenToAttachSignInSity=7500;
    FLenToAttachSign=20000;
    FSignOffset=300;
    FSignToSign=5000;
    FSignToSignInSity=2500;
    FAttachToSign=1000;
    FSign24ToAttach=1000;
    FTownToSign=10000;
    FSignToBusStop=200;
    FMaxSignToBusStop=2000;
    FMaxSignToBridge=1000;
    FMaxSignToKm=10000;
    }
// ������ ��� ����������
// ������������ ���������� ����� ������������, ������������� � ������ �������
// ��� ������� ��� ��������� ������������ ������������
__property __int32 CrossMaxLen={read=FCrossMaxLen};
// ����������� ���������� ���������� �� ����� ����������� � ���������� ������
__property __int32 MaxLenToAttachSignInSity={read=FMaxLenToAttachSignInSity};
// ����������� ���������� ���������� �� ����� ����������� ��� ����������� ������
__property __int32 MaxLenToAttachSign={read=FMaxLenToAttachSign};
// ����������� ���������� �� ����� ����������� � ���������� ������
__property __int32 LenToAttachSignInSity={read=FLenToAttachSignInSity};
// ����������� ���������� �� ����� ����������� ��� ����������� ������
__property __int32 LenToAttachSign={read=FLenToAttachSign};
// ���������� �� ������ ������ �� �����
__property __int32 SignOffset={read=FSignOffset};
// ���������� ����� ������� ��� ������
__property __int32 SignToSign={read=FSignToSign};
// ��������� ����� ������� � ������
__property __int32 SignToSignInSity={read=FSignToSignInSity};
// ���������� ����� ����������� �� �����
__property __int32 AttachToSign={read=FAttachToSign};
// ���������� �� ����������� �� ����� "������ ������"
__property __int32 Sign24ToAttach={read=FSign24ToAttach};
// ����������� ���������� ���������� �� ������� ���. ������ �� �����
__property __int32 TownToSign={read=FTownToSign};
// ���������� �� ����� ���������� ��������� �� ����� ���������
__property __int32 SignToBusStop={read=FSignToBusStop};
// ������������ ���������� �� ����� �� ���������
__property __int32 MaxSignToBusStop={read=FMaxSignToBusStop};
// ������������ ���������� �� �������� � ��������� �� �������
__property __int32 MaxSignToBridge={read=FMaxSignToBridge};
// ������������ ���������� �� ������� � �������� �� �����
__property __int32 MaxSignToKm={read=FMaxSignToKm};
bool __fastcall IsBreakAttachObject(TRoadObject *obj)
{return dynamic_cast<TRoadAttach*>(obj)!=NULL;}

};

class TSignDesignRules
{
protected:
TAttachPlacement __fastcall GetAttachPlacement(TRoadAttach *At,TDtaSource *Data, int &SPos, int &EPos);
bool __fastcall IsInSity(TRoadObject *Obj,TDtaSource *Data);
virtual int __fastcall HandleAttach(TRoadAttach *At,TDtaSource *Data, TDictSource *Dict, bool doit=true);
int __fastcall AssistHandleTown(TTown *T,TDtaSource *Data,
    TDictSource *Dict,int Pos,TRoadDirection defdir,int defcode,int poscode,String scode, bool doit=true);
virtual int __fastcall HandleTown(TTown *T,TDtaSource *Data, TDictSource *Dict, bool doit=true);
virtual int __fastcall HandleBusStop(TBusStop *B,TDtaSource *Data, TDictSource *Dict, bool doit=true);
virtual int __fastcall HandleBridge(TRoadBridge *B,TDtaSource *Data, TDictSource *Dict, bool doit=true);
TRoadSign* __fastcall FindSign(TDtaSource *Data,int SCode,int Min,int Max, bool Napr,TRoadDirection dir, TRoadSignPlacement pl,TTestBreak breakfun,int &Pos);
void __fastcall SetSignPlacement(TDtaSource *Data,int sgntosgn,int SPos,int EPos,TRoadSign *Sgn);
int __fastcall FindSignX(TDtaSource *Data,TRoadDirection dir,int Pos);
public:
virtual bool __fastcall CanHandle(TRoadObject *Obj, TDtaSource *Data,TDictSource *Dict);
virtual int __fastcall HandleObject(TRoadObject *Obj, TDtaSource *Data, TDictSource *Dict, bool doit=true);
virtual int __fastcall TSignDesignRules::SetKmSign(TDtaSource *Data, TDictSource *Dict);
};

extern PACKAGE TSignDesignData SDesignData;
extern PACKAGE TSignDesignRules SDesignRules;
//---------------------------------------------------------------------------
#endif
