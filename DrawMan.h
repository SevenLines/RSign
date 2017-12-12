//---------------------------------------------------------------------------
#ifndef DrawManH
#define DrawManH
#include "DataSour.h"
#include "VisSetForm.h"



//---------------------------------------------------------------------------

enum TContentStatus {csEmpty,csDrawing,csEnabled};
class TDrawContents
{
protected:
__int32 FL1,FL2,FCL,FX1,FX2,FPL1,FPL2;
__int32 FWidth,FHeight;
TContentStatus FStatus;
public:
__fastcall TDrawContents(void)
    {FStatus=csEmpty;}
//���������� DC ��� ���������
HDC virtual __fastcall GetContentDC(void) {return NULL;};
//������� DC ��� ���������
bool virtual __fastcall PrepareUpdating(void)
    {FStatus=csDrawing;return true;}
//����������� DC
void virtual __fastcall FinishUpdating(void)
    {FStatus=csEnabled;}
//������������� ������ ��������� � ��������
void virtual __fastcall SetSize(__int32 w,__int32 h)
    {FWidth=w;FHeight=h;}
//���������� ���������� ���������
void virtual __fastcall DrawTo(TCanvas*,int,int) {}
//�������� ��������� ������������� �������
void __fastcall SetParam(__int32 NL1, __int32 NL2,__int32 NCL,__int32 NX1,__int32 NX2,__int32 _FPL1,__int32 _FPL2)
    {FL1=NL1;FL2=NL2;FCL=NCL;FX1=NX1;FX2=NX2;FPL1=_FPL1;FPL2=_FPL2;}
//void __fastcall ConvertPoint(__int32 L,__int32 X,__int32 &PX,__int32 &PY);
//void __fastcall ConvertPoly(__int32 n, TRoadPoint *in, POINT *out);
//������� ������������ ����� ������ ��� ���������� �����������
__property __int32 L1={read=FL1};
__property __int32 L2={read=FL2};
//������� ������ ��������
__property __int32 PL1={read=FPL1};
__property __int32 PL2={read=FPL2};
__property __int32 CL={read=FCL};
__property __int32 X1={read=FX1};
__property __int32 X2={read=FX2};
__property __int32 Width={read=FWidth};
__property __int32 Height={read=FHeight};
__property HDC DC={read=GetContentDC};
__property TContentStatus Status={read=FStatus};
};

class TDrawBitmap : public TDrawContents
{
private:
HBITMAP FBitmap;
HDC Fdc;
void __fastcall FreeBitmap(void);
protected:
HDC virtual __fastcall GetContentDC(void)
    {if (FStatus==csDrawing) return Fdc;else return NULL;}
public:
void virtual __fastcall DrawTo(TCanvas*,int,int);
bool virtual __fastcall PrepareUpdating(void);
void virtual __fastcall FinishUpdating(void);
_fastcall TDrawBitmap(void) : TDrawContents()
    {FBitmap=NULL;Fdc=NULL;};
~TDrawBitmap(void)
    {FreeBitmap();}
__property HBITMAP Bitmap={read=FBitmap};
};

class TPrintContents : public TDrawContents
{
private:
    HDC FDc;
protected:
HDC virtual __fastcall GetContentDC(void)
    {if (FStatus==csDrawing) return Printer()->Canvas->Handle;else return NULL;}
public:
bool virtual __fastcall PrepareUpdating(void);
void virtual __fastcall FinishUpdating(void);
__fastcall TPrintContents(void) : TDrawContents()
    {FDc=NULL;}
};

class TMetaContents : public TDrawContents
{
private:
    HDC Fdc;
    String FFileName;
    int FDeviceDPI;
    void *FMetaFile;
    void __fastcall FreeMetaFile(void);
public:
    __fastcall TMetaContents(String name) : TDrawContents()
        {FFileName=name;FMetaFile=NULL;Fdc=NULL;}
    __fastcall ~TMetaContents(void)
        {FreeMetaFile();}
    HDC virtual __fastcall GetContentDC(void)
        {if (FStatus==csDrawing) return Fdc;else return NULL;}
    bool virtual __fastcall PrepareUpdating(void);
    void virtual __fastcall FinishUpdating(void);
};

class TExtRect
{
public:
    RECT Rect;
    int SelfIndex;
    int SortedIndex;
    int RoadL; // ���������� ����� �������� �������������� � �������� �����������
    int RoadX;
__fastcall TExtRect(void)
    {SelfIndex=-1;}
__fastcall TExtRect(int index,RECT &r)
    {Rect=r;SelfIndex=index;}
int __fastcall Dimention(int n)
    {
    switch (n)
        {
        case 0: return Rect.left;
        case 1: return Rect.right;
        case 2: return Rect.top;
        case 3: return Rect.bottom;
        }
    return 0;
    }
};

// ������ ���������� ����������
class TIntervalList
{
private:
};

class TRectsManager
{
private:
int FDirection; //��� ����������� �������������� : �� ������ ���� ��� ����� ����� ��� ������ ������ � �.�
int FCount;
int FMemCount;
void __fastcall FindSignPlacement(int param,RECT &r);
public :
__fastcall TRectsManager(void);
__fastcall ~TRectsManager(void);
void __fastcall Clear(void);
void __fastcall NewSession(int n,int dir);
TExtRect *Rects; // ������ ��������������� ���������������. ��� ���� ���������� ������
TExtRect **SortedRects; // ������ ������ �� �������������� ������������� �� ����������� ������� 1
//TExtRect **SortedRects2; // ������ ������ �� �������������� ������������� �� ����������� ������� 2
void __fastcall PutRect(int index,RECT &r); // ��������� ������ ���������� ������������� � ������
//��������� ������� ����������� ���������� ��� ��������������. version- ����� ���������
void __fastcall FindPlacement(int version,int param,int index,RECT &r);
//��������� ��������� ������������ �� ������������� � ������� ����������������
bool __fastcall TestRect(RECT &r);
__property int Count={read=FCount};
};

class TDrawManager
{
private:
__int32 FBaseScaleL;    //������� ����������� �������� �� ����� ������
__int32 FBaseScaleX;    //������� ����������� �������� �� ������ ������
__int32 FBaseScaleP;    //������� ����������� �������� �� ������ ������
__int32 FFontSize;      //������ ������ � ������� ��� ������ ��������
__int32 FVisModeLength;    //����� ������� ����������� ��������� (��)
__int32 FVisModeVisLength; //������������ ����������� ���������  (�)
__int32 FVisModeMinStep;   //�������� ���������� ����������� ��������� (�)
bool FDelVis;
bool FProVis;
//TDtaSource *FSource;
TVisSetFrm *FVisSet;
TDictSource *FDict;
TSharedObjSource *FShared;
__int32 FSclL;
__int32 FSclX;
TPlanKind FPlanKind;
TPlanDirect FPlanDirect;
double FDpsm;
int FSensetive;
// ��� �������� ��� �����������.
// ������ � �������� ��������� ��� �������� �� ���������
int FVisModeBorder;

__int32 ObjCount;
TRoadObject **Objs; //������ ���������� �� ������������ ��������
TDtaSource **Sources;
TRectsManager RectsMan;
TRectsManager SignsMan;
//RECT *Rects;
TExtPolyline **Polys;
void __fastcall FreeHash(void);
// ������ ���� �����������. ����������� ������� ��������
// codes ������ ���� �������� ��� �����������.
// ������������ ������� � ������ < codes Mask ��������� ������� ������ ����
void __fastcall SelectObjects(int codes,bool *Mask,__int32 L1,__int32 L2);
// ������ ����. ���������� �������� �� �����
void __fastcall SortObjects(void);
// ������ � ��������� ���� ����� ����� ������������ ������
void __fastcall FindSignsPlacement(TDrawContents *Cont);
// ������ ����. ���������� �������
void __fastcall PrepareMetric(TDrawContents *Cont,RECT *OutRect);
// � �������, ����������� � ���� flag=1 ���� ���������� �� ��������� �������
// flag=2 ���� ������ ���������
void __fastcall DrawObjects(TDrawContents *Cont,int flag);

//int __fastcall CutBy(__int32 n,TRoadPoint *Sour,POINT *Dest,TDrawContents *Drw);
void __fastcall DrawRoad(int codes,bool *Mask,TDrawContents *Cont,RECT *OutRect);
void* __fastcall GetPen(TDrwParamRec *par,bool &needdel);
void* __fastcall GetGdiObj(int ObjId);
//void __fastcall DrawOneDash(TDrawContents *Cont,__int32 n,POINT *p,int shift,int width,__int32 penid,__int32 brushid);
void __fastcall DrawPolygon(TDrawContents *Cont,TExtPolyline*,int PenId,int BrushId);
void __fastcall DrawFigure(TDrawContents *Cont,POINT pt,double dirx,double diry,int kind,int size,int orsize,int penid,int brushid);
//POINT * __fastcall BuildEqvi(POINT *Sour,int count,double shift,double Ex,int &n);
void __fastcall DrawLabel(TDrawContents *Cont,TPlanLabel *l);
void __fastcall DrawSignLabel(TDrawContents *Cont,int dir,RECT *r,String Caption);
/*
// ������� ������� ���������� �����
// 0 - ��� �������� 3 - 90 �� �� ������� �������
// 2 - 180 ��. 1 - 90 �� ������ ������� �������
int __fastcall GetSignDirection(TRoadSign *sign,TPlanKind pk,TPlanDirect pd);
*/
void __fastcall CalcRect(TExtPolyline*,RECT *r);
// ������� �����������
/* 1 */ void __fastcall DrawArea(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec1 *par);
/* 2 */ void __fastcall DrawLine(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec2 *par);
// ��������� ���������� ��������� � �������� ����������� �� ����� � ����������� �� ��������
// (4 ��������). ����� ����� ��������� ���������� �������������� ������ (���� 5 ���=true)
void __fastcall CalcMetaRect(POINT *p,TDrwParamRec3 *par,RECT*,int,bool);
/* 3 */
void __fastcall DrawMetafile(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec3 *par,RECT*);
// ��� ������� ��� ��������� ���������� ���� �� �������� � �� ������������
void __fastcall DrawTrafficLight(TTrafficLight *light,TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec3 *par,RECT*);
void __fastcall DrawSign(TDrawContents *Cont,int count,__int32 *ObjNum,int flag);
void __fastcall DrawSignImage(TDrawContents *Cont,int ObjNum);
void __fastcall DrawSignBackColor(TDrawContents *Cont,int ObjNum);
void __fastcall DrawSignLines(TDrawContents *Cont,int ObjNum);
void __fastcall DrawSignLabels(TDrawContents *Cont,int ObjNum);
/* 4  */
void __fastcall DrawBridge(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec4 *par);
/* 5 */
void __fastcall DrawDash(TDrawContents *Cont,__int32 n,TExtPolyline *Poly,TDrwParamRec5 *par);
/* 6 */
void __fastcall DrawFigureLine(TDrawContents *Cont,int count,TExtPolyline *Poly,TDrwParamRec6 *par);
/* 7 */
void __fastcall DrawCurvesLine(TDrawContents *Cont,__int32 n,TExtPolyline *Poly,TDrwParamRec7 *par);
/* 8 */
void __fastcall DrawBordersLine(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec8 *par);

// ��������� ��� ����������� ������� �� �������
void __fastcall DrawProfilLine(TDrawContents *Cont,TRect *ProfRect,__int32 L1,__int32 L2,int dir);

// ������� ����� ��� ������� ����������� ������� � �.�.
void* __fastcall CreateLabelFont(int dpi);

public:
TRoad *Road;

__fastcall TDrawManager(void);
__fastcall TDrawManager(TVisSetFrm *NSetFrm,TDictSource* NDict,TSharedObjSource *NShared);
__fastcall ~TDrawManager(void);
void __fastcall SetDefaults(TDrawManager *Source);
void __fastcall FillCont(TDrawContents *Cont);
RECT* __fastcall GetRect(int n);
virtual void __fastcall DrawVisibleMode(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd);
virtual void __fastcall DrawDressLayers(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd);
virtual void __fastcall GetVisModeParam(TRect *OutRect,TPlanKind pk,TPlanDirect pd,int X,int Y,int &dir,int &len);
virtual void __fastcall DrawCurvesPlan(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd);
virtual void __fastcall DrawProfil(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd);
virtual void __fastcall DrawRazrez(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd,__int32 L);
void virtual __fastcall DrawObjectMetric(HDC dc,int index);
void virtual __fastcall DrawSelected(HDC dc);
void virtual __fastcall DrawAll(TDrawContents* Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd);
void virtual __fastcall DrawByCodes(int max,bool *vis,TDrawContents* Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd);
void virtual __fastcall DrawByCode(__int32 Code,TDrawContents* Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd);
void virtual __fastcall StopDrawing(void);
int virtual __fastcall SelectByXY(__int32 X,__int32 Y,TRoadObject** Array,TDtaSource **Src,int *Indexes,int max);
// ������� ������� ����� ��������� � L, �� ������ ��� �� ���������� DL
// �� ���� ��������, ����� obj. � ������ ������ �������� ����� � ���������� true
// ��� ���� ������������ �������� �������� ���� �� ���� ��� obj
TRoadObject* __fastcall FindNearestL(__int32 &L,TRoadObject *obj,__int32 DL);
// ������� ������� ����� ��������� � L,X �� ������ ��� �� ���������� DL
// �� ���� ��������, ����� obj. � ������ ������ �������� ����� � ���������� true
TRoadObject* __fastcall FindNearestLX(__int32 &L,__int32 &X, TRoadObject *obj,__int32 DL);
// ������� �������� ���������� �������� �����, ���, ����� ��� ���������
// � ������� ���������� � ������� FindNearestL
void Round_Int(int &L) {
  if (L>0) L=((L+50)/100)*100;
  else L=((L-50)/100)*100;
}
bool __fastcall LeepPoint(int& PX,int &PY,TRoadObject *obj,__int32 DL,bool round=false);
void __fastcall CallDrawFunc(TDrawContents *Cont,TExtPolyline*,TDrwParamRec *par,TRect *r,__int32 fl,__int32 fx,TPlanKind pk,TPlanDirect pd,double dpsm,bool clear);
void __fastcall CallDrawFunc(TDrawContents *Cont,TExtPolyline*,TDrwParamRec *par,TRect *r,bool clear);
//void __fastcall CallDrawFunc(TDrawContents *Cont,TExtPolyline*,TDrwParamRec *par,TRect *r,double dpcm,bool clear);
//__property TDtaSource *Source={read=FSource,write=FSource};
__property TVisSetFrm *VisSet={read=FVisSet,write=FVisSet};
__property TDictSource *Dict={read=FDict,write=FDict};
__property TSharedObjSource *Shared={read=FShared,write=FShared};
__property __int32 Sensetive={read=FSensetive,write=FSensetive};
__property __int32 BaseScaleL={read=FBaseScaleL,write=FBaseScaleL};
__property __int32 BaseScaleX={read=FBaseScaleX,write=FBaseScaleX};
__property __int32 BaseScaleP={read=FBaseScaleP,write=FBaseScaleP};
__property __int32 FontSize={read=FFontSize,write=FFontSize};
__property bool DelVis={read=FDelVis,write=FDelVis};
__property bool ProVis={read=FProVis,write=FProVis};

__property __int32 VisModeLength={read=FVisModeLength,write=FVisModeLength};
__property __int32 VisModeVisLength={read=FVisModeVisLength,write=FVisModeVisLength};
__property __int32 VisModeMinStep={read=FVisModeMinStep,write=FVisModeMinStep};

};

#endif
