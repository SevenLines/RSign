//---------------------------------------------------------------------------

#ifndef SignsUtilH
#define SignsUtilH
#include "classes.hpp"
#include "Const.h"
//---------------------------------------------------------------------------
class TSign : public TObject
{
private:
    // �����������
    // ������������
    // ������ �������
    // ����� �������
    // ����� �����
public:
    __int32 MinL;// ������ ������� �� ������� ���� ������ ����������
    __int32 MaxL;// ����� ������� �� ������� ���� ������ ����������
    __int32 X;// ����������������� �����, ���� �� �� ������ �� �������
    __int32 Y;// ���������� �� ������/���� ������
    AnsiString Name;// ������������ ����� (����. 2.3.1)
    AnsiString Description;// �������� ����� (����. ���������� �������������� ������)
    TRoadDirection Direction;// ����������� ����� (����.)
    TRoadSignPlacement Placement;// ������������ ����� (����. )
    bool IsOnAttach;// true ���� ���� ���������� �� ����������
    AnsiString Label;// ������� �� �����
    //

    __fastcall TSign(AnsiString Name, AnsiString Description, AnsiString Label, TRoadDirection Direction, TRoadSignPlacement Placement, __int32 MinL, __int32 MaxL,  __int32 X, __int32 Y, bool IsOnAttach);
};
#endif
