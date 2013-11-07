//---------------------------------------------------------------------------
#pragma hdrstop
#include "SignsUtil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TSign::TSign(AnsiString Name, AnsiString Description, AnsiString Label, TRoadDirection Direction, TRoadSignPlacement Placement, __int32 MinL, __int32 MaxL,  __int32 X, __int32 Y, bool IsOnAttach)
{
    this->Name = Name;
    this->Description = Description;
    this->Label = Label;
    this->Direction = Direction;
    this->Placement = Placement;
    this->MinL = MinL;
    this->MaxL = MaxL;
    this->X = X;
    this->Y = Y;
    this->IsOnAttach = IsOnAttach; 
}
