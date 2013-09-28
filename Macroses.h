//---------------------------------------------------------------------------

#ifndef MacrosesH
#define MacrosesH
#include <classes.hpp>
#include "RoadObj.h"

#define CONSTLEN 16
//---------------------------------------------------------------------------
class TMacros : public TStringList
{
private:
TRoadObject *FLocalVar;
TStringList *FLocalObjects;
int FShortCut;
String FMacrosName;
void __fastcall SetShortCut(int x)
    {FShortCut=x;}
void __fastcall SetMacrosName(String s)
    {FMacrosName=s;}
//----- Функции для интерпретации
int __fastcall GetOperator(String Command,String &Param,const char Pat[][CONSTLEN],int PatCount);
void __fastcall Operator_Set(String Param);
void __fastcall Operator_Run(String Param);
void __fastcall Operator_Dim(String Param);
void __fastcall Operator_Goto(String Param,int &CP);
void __fastcall Operator_If(String Param,int &CP);
String __fastcall Calculate(char **str);
String __fastcall GetValue(String VarName);
void __fastcall SetValue(String VarName,String Value);
int __fastcall FindLabel(String Label);
public:
__fastcall TMacros(void) : TStringList()
    {FLocalVar=NULL;
     FLocalObjects=new TStringList;
    }
__fastcall ~TMacros(void)
    {delete FLocalVar;
     delete FLocalObjects;
    }
bool __fastcall Execute(void);
virtual void __fastcall LoadFromFile(String fname);
virtual void __fastcall SaveToFile(String path);
__property int ShortCut={read=FShortCut,write=SetShortCut};
__property String MacrosName={read=FMacrosName,write=SetMacrosName};
};
#endif
