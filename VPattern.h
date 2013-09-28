//---------------------------------------------------------------------------

#ifndef VPatternH
#define VPatternH
#include <Classes.hpp>
#include "Lists.h"
#include "Metrics.h"
#include "DrawMan.h"


class TPatFigure
{
protected:
TPlanKind FPlanKind;
TPlanDirect FPlanDirect;
int FSection;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd)  {}
virtual void __fastcall Write(TStringList*) {}
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
__property int Section={read=FSection};
};

class TPatPlanesCenter: public TPatFigure
{
protected:
int FX,FY,FWidth,FHeight;
public:
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall FillRect(TRect &r);
__property int X={read=FX};
__property int Y={read=FY};
__property int Width={read=FWidth};
__property int Height={read=FHeight};
};

class TPatPlanCenter : public TPatPlanesCenter
{
public:
virtual void __fastcall Write(TStringList*);
};

class TPatCurvePlanCenter : public TPatPlanesCenter
{
public:
virtual void __fastcall Write(TStringList*);
};

class TPatProfilCenter : public TPatPlanesCenter
{
public:
virtual void __fastcall Write(TStringList*);
};

class TPatPageSize : public TPatFigure
{
protected:
int FWidth,FHeight;
int FLeftOfs,FRightOfs,FTopOfs,FBottomOfs;
public:
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
__property int Width={read=FWidth};
__property int Height={read=FHeight};
__property int LeftOfs={read=FLeftOfs};
__property int RightOfs={read=FRightOfs};
__property int TopOfs={read=FTopOfs};
__property int BottomOfs={read=FBottomOfs};
};

class TPatLabel : public TPatFigure
{
protected:
int FSize;
int FColor;
int FFormat;
int FAngle;
bool FBold;
bool FItalic;
bool FUnderline;
String FName;
String FText;
String FCaption;

TStringList *FRepList;
void* __fastcall CreateFont(double);
void __fastcall MakeReplace(char*,char*);
public:
__fastcall TPatLabel(void)
    {FRepList=NULL;}
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
void __fastcall SetParam(TFont*);
TFont* __fastcall GetFont(void);
__property String Text={read=FText,write=FText};
__property String Caption={read=FCaption};
__property TStringList* RepList={read=FRepList,write=FRepList};
};

class TPatLabelRect : public TPatLabel
{
POINT FP1,FP2;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatLabelAngle : public TPatLabel
{
POINT FP;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatLine : public TPatFigure
{
private:
POINT FP1,FP2;
int FWidth;
int FColor;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatRectangle : public TPatFigure
{
private:
POINT FP1,FP2;
int FPenColor;
int FPenWidth;
int FBrushColor;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatGrid : public TPatFigure
{
private:
POINT FP1,FP2;
int FPenColor;
int FPenWidth;
int FVSpace;
int FHSpace;
bool FBorder;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatKmSign : public TPatFigure
{
private:
POINT FP;
int FPenColor;
int FPenWidth;
int FBrushColor;
int FSize;
public:
virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
virtual void __fastcall ReadInfo(TStringList*);
virtual void __fastcall WriteInfo(TStringList*);
virtual void __fastcall Write(TStringList*);
};

class TPatRoadObject : public TPatFigure
{
private:
    TExtPolyline *FPoly;
    int FObjCode;
    int FObjChr;
public:
    __fastcall TPatRoadObject(void): TPatFigure()
        {FPoly=new TExtPolyline(16);}
    __fastcall ~TPatRoadObject(void)
        {delete FPoly;}
    virtual void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
    virtual void __fastcall ReadInfo(TStringList*);
    virtual void __fastcall WriteInfo(TStringList*);
    virtual void __fastcall Write(TStringList*);
};

class TDrawPattern
{
private:
TObjList<TPatFigure> *FFigures;
TStringList *FRepList;
TPatPlanCenter *FPlanCenter;
TPatCurvePlanCenter *FCurvePlanCenter;
TPatProfilCenter *FProfilCenter;
TPatPageSize *FPageSize;
int FSection;
int FMaxSection;
void __fastcall SetSection(int);
public:
__fastcall TDrawPattern(void);
__fastcall ~TDrawPattern(void);
bool __fastcall LoadFromFile(String FileName);
void __fastcall SaveToFile(String FileName);
void __fastcall DrawTo(TDrawManager *Man,TDrawContents *Cont,double K,int cx,int cy,TPlanKind pk,TPlanDirect pd,__int32 PageInd);
void __fastcall Clear(void);
bool __fastcall GetPlanCenter(int &x,int &y);
bool __fastcall GetProfilRect(TRect &r);
bool __fastcall GetCurvePlanRect(TRect &r);
bool __fastcall GetPlanSize(int &x,int &y);
bool __fastcall GetPlanOffsets(int &l,int &r,int &t,int &b);
bool __fastcall GetPageSize(int &x,int &y);
__property TObjList<TPatFigure>* Figures={read=FFigures};
__property TStringList *RepList={read=FRepList};
__property int Section={read=FSection,write=SetSection};
__property int MaxSection={read=FMaxSection};
};
//---------------------------------------------------------------------------
#endif
