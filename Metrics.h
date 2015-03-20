//---------------------------------------------------------------------------
//  Модуль для работы с точками и векторами точек
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

// Класс для работы с точками на дороге

/* Структура кода
Младший разряд (Code[i]&1) Видимсть
    0 - участок не видимый
    1 - участок видимый
3 следующих разряда ((Code[i]>>1)&7) Вид Соединения
    0 -- Прямая к точке
    1 -- Дуга окружности и прямая к точке
    2 -- Участок кривой безье от i-2 точки к i+1 с контрольными i-1 и i точкой
4 следующих разряда ((Code[i]>>4)&15)  Ограничения
    0 -- Нет ограничений
    1 -- фиксированное расстояние от правой бровки
    2 -- фиксированное расстояние от левой бровки
    3 -- фиксированное расстояние от правой кромки
    4 -- фиксированное расстояние от левой кромки
    5 -- фиксированное расстояние от правого края плана
    6 -- фиксированное расстояние от левого края плана
    7 -- фиксированный угол от предудущей точки
    8 -- фиксированный угол от следующей точки

Вычисление базовой точки (0,0) (4 разряда) (8-11)
Вычисление L
    0 -- 0 дороги
    1 -- Начало объекта
    2 -- Конец объекта
    3 -- L предудущей точки
    4 -- L следующей точки
    5 -- Начало объекта - родителя
    6 -- Конец объекта - родителя
Вычисление X (с использованием уже вычисленной L) (12-15)
    0 -- Ось дороги
    1 -- Правая бровка
    2 -- Левая бровка
    3 -- Правая кромка
    4 -- Левая кромка
    5 -- Правый край плана
    6 -- Левый край плана
    7 -- X пред точки
    8 -- X след точки
Вид координат                          (16)
    0 -- прямоугольные
    1 -- полярные
Фиксация параметра 1 (DL или угол)     (17)
    0 -- нет
    1 -- есть
Фиксация параметра 2 (DX или расстояние)  (18)
    0 -- нет
    1 -- есть
Вид соединения       (Отрезок или гладкая кривая) 19
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
__int32 LeepPar; // Параметр для ограничения в зависимости от кода
__int32 BasePar1; // Параметры для расчета привязанных точек
__int32 BasePar2;
__int32 L; // Расстояние от начала дороги по оси
__int32 X; // Расстояние от осевой линии дороги
TPointCode Code; // Код соединения
// Метод позволяет установить точку к лучу выходящему из точки Base под углом angle
void __fastcall LeepToLine(__int32 BaseL,__int32 BaseX,double angle);
bool __fastcall LeepToPolyline(__int32 BaseL,__int32 BaseX,__int32 shift,double angle, TPolyline *Poly);
// Метод находит точку пересечения двух прямых выходящих из точек Base1 Base2 под углами angle1, angle2
bool __fastcall CrossPoint(__int32 BaseL1,__int32 BaseX1,__int32 BaseL2,__int32 BaseX2,double angle1,double angle2);
};

// структура из массива точек и их кодов соединений
// используется для расширения возможностей графики
// Используются первые четыре разряда кодов
struct TExtPolyline
{
private:
void __fastcall CopyExtPolyline(TExtPolyline *Source);
public:
__int32 DirectionVal;
__int32 Count;     //Количество точек
__int32 FCapacity; //Выделенный объем памяти в точках
POINT *Points;
TPointCode *Codes;
__int32 *Flags; // Флажки для хранения информации о точках
__fastcall TExtPolyline(void);
__fastcall TExtPolyline(int n);
__fastcall TExtPolyline(int n,int defcode);
__fastcall TExtPolyline(TExtPolyline*);
__fastcall TExtPolyline(TExtPolyline*,double offset);
// Создает новую полинию, копируя исходную со смещенеим
__fastcall TExtPolyline(TExtPolyline*,int ofsx,int ofsy);
__fastcall ~TExtPolyline(void);
void __fastcall ReSize(int n);
POINT &operator[](int n)
    {return Points[n];}
void __fastcall DisSelect(void);
void __fastcall Select(int n);
void __fastcall DrawBezierSeg(void *dc,int n);
void __fastcall DrawArcSeg(void *dc,int n);
// Функция для отображения видимой части полилинии
void __fastcall PolyDraw(void *dc, void *pen,TRect& VR);
// Функция для отображения полилинии pen1 - перо для рисования видимых линий
// pen2 для невидимых линий
void __fastcall DrawPoly(void *dc,void *pen1,void *pen2);
// Функция для закрашивания области, ограниченной полилинией
// pen, brush могут быть NULL
void __fastcall DrawTo(void *dc,void *pen,void *brush);
// Функция создает путь из полилинии
void __fastcall CreatePath(void *dc);
// Функция находит точку на полилинии, ближайшую к заданной и возвращаяет расстояние до нее
double __fastcall LenTo(POINT Cur,POINT &Ret,int &index);
};

// Класс полилиния (вектор из точек).
// Для заполнения необходимо установить количество точек
// (очень желательно окончательное) с помощью свойства
// Count. После этого к каждой точке можно обращаться с
// помощью свойства Points. Нумерация точек от 0 до Count-1.
// Установка Count в 0 не освобождает памяти. Для освобождения
// памяти надо вызвать FreePoints();

// Это минимальное приращение числа точек
#define INCCAPVALUE 16

class TPolyline
{
private:
__int32 FCapacity; //Выделенный объем памяти в точках
__int32 FCount;    //Число точек в векторе
__int32 FId;       //Идентификатор полилинии
TRoadPoint *FPoints; // Массив точек
void __fastcall SetCount(int); //Установка числа точек
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
// Вставляет точку в позицию n (после n-1)
void __fastcall InsertPoint(TRoadPoint& pt,int n);
// Переносит координату L полилинии
void __fastcall Move(int len);
void __fastcall LoadFromStream(TMemoryStream *Mem);
void __fastcall SaveToStream(TMemoryStream *Mem);
double __fastcall Length(void);
// Функция находит первое пересечение полилинии с отрезком от a до b и заносит
// точку пересечения в p. Возввращается номер точки перед которой вставляется новая
// или 0 если не пересекается
int __fastcall CrossLine(TRoadPoint &a,TRoadPoint &b,TRoadPoint &p);

// Функция находит точку на полилинии, ближайшую к заданной и возвращаяет расстояние до нее
// index - номер точки начала отрезка, на которой лежит проекция
double __fastcall LenTo(TRoadPoint &Cur,TRoadPoint &Ret,int &index);

// Функция строит простую полилинию по данной полилинии. len - расстояние до точек для
// приближения кривыми Безье
void __fastcall ExpandToSimplePoly(TPolyline *Poly, double len);

// добавляет полилинию  Addded в конец текущей. Если есть разрыв, то метрика берется из
// то добавляется участок с нулями
void __fastcall AddPoly(TPolyline * Added);
// Заменяет все участки в которых координата X равна 0 на соответствующий участок Ref
void __fastcall ReplaceNullPart(TPolyline *Ref);
// Удаляет из начала и конца линии участки с X=0;
void __fastcall Trim(void);
// Добавляет новый отрезок в конец полилинии (L1>=L последней точки)
// b=false, если отсутствующие участки должны быть 0
// b=true, если отсутствующие участки должны аппроксимироваться
void __fastcall AddLine(bool b,int L1, int L2, int X);
// функции, применяемые для сложения двух полилиний
int __fastcall SumGetXNext(int L,int &n);
int __fastcall SumGetXPred(int L,int &n);

// Функция для изменения направления вектора
void __fastcall ChangeOrientation(void);

// Преобразует координату X
void __fastcall MulDiv(int Mul,int Div);
void __fastcall AddX(int DX);
//
// копирование двух полилиний с соединением X1*K1+X2*K2
//
void __fastcall Sum(TPolyline *Fir,TPolyline *Sec,int K1,int K2);
// копирование полилинии с обрезкой по двум направлениям.
// предполагается, что L[i+1]>=L[i];
void __fastcall CopyAndCut(TPolyline* Poly,__int32 L1,__int32 L2);

// округляет ширину полосы в меньшую сторону с точностью defln
void __fastcall MakeSimplePart(TPolyline *P,int defln);

// Из полосы вида ___/\/\/\-  делает полосу вида  ___|-----
void __fastcall MakeWidePart(TPolyline *Pl,int Par1,int RoundVal);
// Из полосы вида ___|------  делает полосу вида  ___/-----
// DL максимальная длина переходного участка
void __fastcall MakeMiddlePart(int DL);
// Функция для отображения полилинии из точек на контекст с использованием кодов
// pen1 перо для линии pen2 --- для пропуска
void __fastcall Dump(ofstream&);
void __fastcall LoadDump(ifstream&);
bool __fastcall GetMinMax(int &Min,int &Max);
bool __fastcall GetMinMaxVal(int &Min,int &Max);
//Находим точку пересечения вертикальной прямой с полилинией
__int32 __fastcall FindX(__int32 L1);
// Для полилинии с условием неубывания координаты L ищет отрезок на который попадает параметр
// Возвращает номер i - отрезок от i до i+1 точки. Если не найден то -1
__int32 __fastcall FindSeg(__int32 L);
void __fastcall FreePoints(void); // Освобождение памяти
// Процедура копирует L,X в BasePar1,BasePar2;
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
