//---------------------------------------------------------------------------
//  ������ ��� ������ � ������� � ��������� �����
//
//---------------------------------------------------------------------------
#ifndef MetricsH
#define MetricsH
//---------------------------------------------------------------------------
#include <fstream.h>
#include <windows.h>
#include <Types.hpp>
#include <Classes.hpp> 
#include "const.h"

// ����� ��� ������ � ������� �� ������

/* ��������� ����
������� ������ (Code[i]&1) ��������
    0 - ������� �� �������
    1 - ������� �������
3 ��������� ������� ((Code[i]>>1)&7) ��� ����������
    0 -- ������ � �����
    1 -- ���� ���������� � ������ � �����
    2 -- ������� ������ ����� �� i-2 ����� � i+1 � ������������ i-1 � i ������
4 ��������� ������� ((Code[i]>>4)&15)  �����������
    0 -- ��� �����������
    1 -- ������������� ���������� �� ������ ������
    2 -- ������������� ���������� �� ����� ������
    3 -- ������������� ���������� �� ������ ������
    4 -- ������������� ���������� �� ����� ������
    5 -- ������������� ���������� �� ������� ���� �����
    6 -- ������������� ���������� �� ������ ���� �����
    7 -- ������������� ���� �� ���������� �����
    8 -- ������������� ���� �� ��������� �����

���������� ������� ����� (0,0) (4 �������) (8-11)
���������� L
    0 -- 0 ������
    1 -- ������ �������
    2 -- ����� �������
    3 -- L ���������� �����
    4 -- L ��������� �����
    5 -- ������ ������� - ��������
    6 -- ����� ������� - ��������
���������� X (� �������������� ��� ����������� L) (12-15)
    0 -- ��� ������
    1 -- ������ ������
    2 -- ����� ������
    3 -- ������ ������
    4 -- ����� ������
    5 -- ������ ���� �����
    6 -- ����� ���� �����
    7 -- X ���� �����
    8 -- X ���� �����
��� ���������                          (16)
    0 -- �������������
    1 -- ��������
�������� ��������� 1 (DL ��� ����)     (17)
    0 -- ���
    1 -- ����
�������� ��������� 2 (DX ��� ����������)  (18)
    0 -- ���
    1 -- ����
��� ����������       (������� ��� ������� ������) 19
*/
struct TPointCode
{
private:
unsigned __int32 Val;
public:
__fastcall TPointCode(void)
    {Val=0;}
__fastcall TPointCode(int n)
    {Val=n;}
int operator()()
    {return Val;}
int Visible(void)
    {return Val&1;}
void SetVisible(int n)
    {Val=(Val&0xFFFFFFFE)|(n&1);}
int Connection(void)
    {return (Val>>1)&7;}
void SetConnection(int n)
    {Val=(Val&0xFFFFFFF1)|((n&7)<<1);}
int VisCon(void)
    {return Val&15;}
int Leep(void)
    {return (Val>>4)&15;}
void SetLeep(int n)
    {Val=(Val&0xFFFFFF0F)|((n&15)<<4);}
int LBase(void)
    {return (Val>>8)&15;}
int XBase(void)
    {return (Val>>12)&15;}
void SetXBase(int xb) {
    Val=(Val&0xFFFF0FFF)|((xb&15)<<12);}
bool Polar(void)
    {return (Val>>16)&1;}
bool BaseFixed1(void)
    {return (Val>>17)&1;}
bool BaseFixed2(void)
    {return (Val>>18)&1;}
int Sleek(void)
    {return (Val>>19)&1;}
void SetSleek(int n)
    { Val=(Val&0xFFF7FFFF)|((n&1)<<19);}
bool Undepended(void)
    {return (Leep()<7)&&(LBase()!=3)&&(LBase()!=4)&&(XBase()<7);}
bool DependPred(void)
    {return (Leep()==7)||(LBase()==3)||(XBase()==7);}
bool DependNext(void)
    {return (Leep()==8)||(LBase()==4)||(XBase()==8);}
void Set(int vis,int con,int leep)
    {Val=(Val&0xFFFFFF00)|((leep&15)<<4)|((con&7)<<1)|(vis&1);}
void SetBase(int lbase,int xbase,int polar,int fix1,int fix2)
    {Val=(Val&0xFFF800FF)|((lbase&15)<<8)|((xbase&15)<<12)|((polar&1)<<16)|((fix1&1)<<17)|((fix2&1)<<18);}
};

class TPolyline;

struct TRoadPoint
{
public:
__fastcall TRoadPoint(void)
    {L=X=0;Code=1;LeepPar=BasePar1=BasePar2=0;}
__fastcall TRoadPoint(__int32 l,__int32 x)
    {L=l;X=x;Code=1;LeepPar=BasePar1=BasePar2=0;}
__fastcall TRoadPoint(__int32 l,__int32 x,__int32 code)
    {L=l;X=x;Code=1;Code=code;LeepPar=BasePar1=BasePar2=0;}
__fastcall TRoadPoint(__int32 l,__int32 x,__int32 code,__int32 lpar,__int32 bpar1,__int32 bpar2)
    {L=l;X=x;Code=1;Code=code;LeepPar=lpar;BasePar1=bpar1;BasePar2=bpar2;}
__int32 LeepPar; // �������� ��� ����������� � ����������� �� ����
__int32 BasePar1; // ��������� ��� ������� ����������� �����
__int32 BasePar2;
__int32 L; // ���������� �� ������ ������ �� ���
__int32 X; // ���������� �� ������ ����� ������
TPointCode Code; // ��� ����������
// ����� ��������� ���������� ����� � ���� ���������� �� ����� Base ��� ����� angle
void __fastcall LeepToLine(__int32 BaseL,__int32 BaseX,double angle);
bool __fastcall LeepToPolyline(__int32 BaseL,__int32 BaseX,__int32 shift,double angle, TPolyline *Poly);
// ����� ������� ����� ����������� ���� ������ ��������� �� ����� Base1 Base2 ��� ������ angle1, angle2
bool __fastcall CrossPoint(__int32 BaseL1,__int32 BaseX1,__int32 BaseL2,__int32 BaseX2,double angle1,double angle2);
};

// ��������� �� ������� ����� � �� ����� ����������
// ������������ ��� ���������� ������������ �������
// ������������ ������ ������ ������� �����
struct TExtPolyline
{
private:
void __fastcall CopyExtPolyline(TExtPolyline *Source);
public:
__int32 DirectionVal;
__int32 Count;     //���������� �����
__int32 FCapacity; //���������� ����� ������ � ������
POINT *Points;
TPointCode *Codes;
__int32 *Flags; // ������ ��� �������� ���������� � ������
__fastcall TExtPolyline(void);
__fastcall TExtPolyline(int n);
__fastcall TExtPolyline(int n,int defcode);
__fastcall TExtPolyline(TExtPolyline*);
__fastcall TExtPolyline(TExtPolyline*,double offset);
// ������� ����� �������, ������� �������� �� ���������
__fastcall TExtPolyline(TExtPolyline*,int ofsx,int ofsy);
__fastcall ~TExtPolyline(void);
void __fastcall ReSize(int n);
POINT &operator[](int n)
    {return Points[n];}
void __fastcall DisSelect(void);
void __fastcall Select(int n);
void __fastcall DrawBezierSeg(void *dc,int n);
void __fastcall DrawArcSeg(void *dc,int n);
// ������� ��� ����������� ������� ����� ���������
void __fastcall PolyDraw(void *dc, void *pen,TRect& VR);
// ������� ��� ����������� ��������� pen1 - ���� ��� ��������� ������� �����
// pen2 ��� ��������� �����
void __fastcall DrawPoly(void *dc,void *pen1,void *pen2);
// ������� ��� ������������ �������, ������������ ����������
// pen, brush ����� ���� NULL
void __fastcall DrawTo(void *dc,void *pen,void *brush);
// ������� ������� ���� �� ���������
void __fastcall CreatePath(void *dc);
// ������� ������� ����� �� ���������, ��������� � �������� � ����������� ���������� �� ���
double __fastcall LenTo(POINT Cur,POINT &Ret,int &index);
};

// ����� ��������� (������ �� �����).
// ��� ���������� ���������� ���������� ���������� �����
// (����� ���������� �������������) � ������� ��������
// Count. ����� ����� � ������ ����� ����� ���������� �
// ������� �������� Points. ��������� ����� �� 0 �� Count-1.
// ��������� Count � 0 �� ����������� ������. ��� ������������
// ������ ���� ������� FreePoints();

// ��� ����������� ���������� ����� �����
#define INCCAPVALUE 16

class TPolyline
{
private:
__int32 FCapacity; //���������� ����� ������ � ������
__int32 FCount;    //����� ����� � �������
__int32 FId;       //������������� ���������
TRoadPoint *FPoints; // ������ �����
void __fastcall SetCount(int); //��������� ����� �����
public:
__fastcall TPolyline(void);
__fastcall TPolyline(__int32 NCount);
__fastcall TPolyline(__int32 NCount,__int32 id);
__fastcall TPolyline(TPolyline*,__int32 id);
__fastcall ~TPolyline(void);
void __fastcall SetId(int id)
    {FId=id;}
TRoadPoint& __fastcall operator[](int n)
    {return FPoints[n];}

void __fastcall CopyPoints(TPolyline*);    
void __fastcall DeletePoint(int num);
// ��������� ����� � ������� n (����� n-1)
void __fastcall InsertPoint(TRoadPoint& pt,int n);
// ��������� ���������� L ���������
void __fastcall Move(int len);
void __fastcall LoadFromStream(TMemoryStream *Mem);
void __fastcall SaveToStream(TMemoryStream *Mem);
double __fastcall Length(void);
// ������� ������� ������ ����������� ��������� � �������� �� a �� b � �������
// ����� ����������� � p. ������������� ����� ����� ����� ������� ����������� �����
// ��� 0 ���� �� ������������
int __fastcall CrossLine(TRoadPoint &a,TRoadPoint &b,TRoadPoint &p);

// ������� ������� ����� �� ���������, ��������� � �������� � ����������� ���������� �� ���
// index - ����� ����� ������ �������, �� ������� ����� ��������
double __fastcall LenTo(TRoadPoint &Cur,TRoadPoint &Ret,int &index);

// ������� ������ ������� ��������� �� ������ ���������. len - ���������� �� ����� ���
// ����������� ������� �����
void __fastcall ExpandToSimplePoly(TPolyline *Poly, double len);

// ��������� ���������  Addded � ����� �������. ���� ���� ������, �� ������� ������� ��
// �� ����������� ������� � ������
void __fastcall AddPoly(TPolyline * Added);
// �������� ��� ������� � ������� ���������� X ����� 0 �� ��������������� ������� Ref
void __fastcall ReplaceNullPart(TPolyline *Ref);
// ������� �� ������ � ����� ����� ������� � X=0;
void __fastcall Trim(void);
// ��������� ����� ������� � ����� ��������� (L1>=L ��������� �����)
// b=false, ���� ������������� ������� ������ ���� 0
// b=true, ���� ������������� ������� ������ ������������������
void __fastcall AddLine(bool b,int L1, int L2, int X);
// �������, ����������� ��� �������� ���� ���������
int __fastcall SumGetXNext(int L,int &n);
int __fastcall SumGetXPred(int L,int &n);

// ������� ��� ��������� ����������� �������
void __fastcall ChangeOrientation(void);

// ����������� ���������� X
void __fastcall MulDiv(int Mul,int Div);
void __fastcall AddX(int DX);
//
// ����������� ���� ��������� � ����������� X1*K1+X2*K2
//
void __fastcall Sum(TPolyline *Fir,TPolyline *Sec,int K1,int K2);
// ����������� ��������� � �������� �� ���� ������������.
// ��������������, ��� L[i+1]>=L[i];
void __fastcall CopyAndCut(TPolyline* Poly,__int32 L1,__int32 L2);

// ��������� ������ ������ � ������� ������� � ��������� defln
void __fastcall MakeSimplePart(TPolyline *P,int defln);

// �� ������ ���� ___/\/\/\-  ������ ������ ����  ___|-----
void __fastcall MakeWidePart(TPolyline *Pl,int Par1,int RoundVal);
// �� ������ ���� ___|------  ������ ������ ����  ___/-----
// DL ������������ ����� ����������� �������
void __fastcall MakeMiddlePart(int DL);
// ������� ��� ����������� ��������� �� ����� �� �������� � �������������� �����
// pen1 ���� ��� ����� pen2 --- ��� ��������
void __fastcall Dump(ofstream&);
void __fastcall LoadDump(ifstream&);
bool __fastcall GetMinMax(int &Min,int &Max);
bool __fastcall GetMinMaxVal(int &Min,int &Max);
//������� ����� ����������� ������������ ������ � ����������
__int32 __fastcall FindX(__int32 L1);
// ��� ��������� � �������� ���������� ���������� L ���� ������� �� ������� �������� ��������
// ���������� ����� i - ������� �� i �� i+1 �����. ���� �� ������ �� -1
__int32 __fastcall FindSeg(__int32 L);
void __fastcall FreePoints(void); // ������������ ������
// ��������� �������� L,X � BasePar1,BasePar2;
void __fastcall FastSetParam(void);
__property __int32 Count={read=FCount,write=SetCount};
__property __int32 Capacity={read=FCapacity};
__property __int32 Id={read=FId};
__property TRoadPoint *Points={read=FPoints};
};

enum THorzAlign {aLeft=TA_LEFT,aRight=TA_RIGHT,aCenter=TA_CENTER};
enum TVertAlign {aTop=TA_TOP,aBottom=TA_BOTTOM,aBaseline=TA_BASELINE};
enum TOrientation {oAway=0,oOrto=1};

class TPlanLabel
{
private:
int FKind;
int FSize;
int FColor;
String FCaption;
THorzAlign FHorzAlign;
TVertAlign FVertAlign;
TOrientation FOrientation;
POINT FPos;
__int32 FDx;
__int32 FDy;
TScaleKind FScaleKind;
public:
__fastcall TPlanLabel(int kind,String caption)
        {FKind=kind;FCaption=caption;FColor=0;}
void __fastcall SetMetric(int x,int y,__int32 dx,__int32 dy)
        {FPos.x=x;FPos.y=y;FDx=dx;FDy=dy;}
void __fastcall SetAlign(THorzAlign horz,TVertAlign vert,TOrientation orient,TScaleKind scale)
        {FHorzAlign=horz;FVertAlign=vert;FOrientation=orient;FScaleKind=scale;}
void __fastcall SetSize(int newsize)
    {FSize=newsize;}
void __fastcall SetColor(__int32 newcol)
    {FColor=newcol;}
__property int Kind={read=FKind};
__property String Caption={read=FCaption};
__property THorzAlign HorzAlign={read=FHorzAlign};
__property TVertAlign VertAlign={read=FVertAlign};
__property TOrientation Orientation={read=FOrientation};
__property POINT Pos={read=FPos};
__property __int32 Dx={read=FDx};
__property __int32 Dy={read=FDy};
__property TScaleKind ScaleKind={read=FScaleKind};
__property __int32 Size={read=FSize};
__property __int32 Color={read=FColor};
};


#endif
