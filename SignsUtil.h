//---------------------------------------------------------------------------

#ifndef SignsUtilH
#define SignsUtilH
#include "classes.hpp"
#include "Const.h"
//---------------------------------------------------------------------------
class TSign : public TObject
{
private:
    // направление
    // расположение
    // начало отрезка
    // конец отрезка
    // номер знака
public:
    __int32 MinL;// начало отрезка на котором знак должен находиться
    __int32 MaxL;// конец отрезка на котором знак должен находиться
    __int32 X;// месторасположение знака, если он не найден на отрезке
    __int32 Y;// расстояние от обчины/края дороги
    AnsiString Name;// наименование знака (напр. 2.3.1)
    AnsiString Description;// описание знака (напр. Примыкание второстепенной дороги)
    TRoadDirection Direction;// направление знака (напр.)
    TRoadSignPlacement Placement;// расположение знака (напр. )
    bool IsOnAttach;// true если знак расположен на примыкании
    AnsiString Label;// надпись на знаке
    //

    __fastcall TSign(AnsiString Name, AnsiString Description, AnsiString Label, TRoadDirection Direction, TRoadSignPlacement Placement, __int32 MinL, __int32 MaxL,  __int32 X, __int32 Y, bool IsOnAttach);
};
#endif
