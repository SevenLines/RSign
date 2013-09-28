//---------------------------------------------------------------------------


#pragma hdrstop

#include "Macroses.h"
#include <Dialogs.hpp>
#include "MainUnit.h"
#include "MacrosForm.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


#define OPCOUNT 7
const char Operators[OPCOUNT][CONSTLEN]={"REM","LABEL","GOTO","IF","SET","RUN","DIM"};

// Функции для оператора RUN
#define FUNCOUNT 10
const char Functions[FUNCOUNT][CONSTLEN]={"Message","Move_Object","Add_Sign","Next_Obj","Prev_Obj","Repaint","Get_Obj_Count","Get_Object","Get_Position","Set_Position"};

void __fastcall TMacros::LoadFromFile(String fname)
{
FMacrosName=ExtractFileName(fname);
int pos=FMacrosName.LastDelimiter(".");
if (pos)
    FMacrosName=FMacrosName.SubString(1,pos-1);
TStringList::LoadFromFile(fname);
if (Count)
    {
    String LastString=Strings[Count-1];
    pos=LastString.Pos("ShortCut=");
    if (pos)
        {
        try
            {FShortCut=LastString.SubString(pos+9,6).Trim().ToInt();}
        catch (...)
            {}
        Delete(Count-1);
        }
    }
}

void __fastcall TMacros::SaveToFile(String Path)
{
String fname=Path+"\\"+FMacrosName+".mcr";
Add("ShortCut="+String(FShortCut));
TStringList::SaveToFile(fname);
Delete(Count-1);
}

int __fastcall TMacros::GetOperator(String Command,String &Param,const char Pat[][CONSTLEN],int PatCount)
{
int i;
for (i=0;i<PatCount;i++)
    if (Command.Pos(Pat[i])==1)
        break;
if (i<PatCount)
    {
    Param=Command.SubString(String(Pat[i]).Length()+2,2048).Trim();
    }
else
    i=-1;
return i;
}

void __fastcall TMacros::SetValue(String VarName,String Value)
{
if (VarName.Pos("AOBJ.")==1)
    {
    if (MainForm->ActiveRoad)
        {
        TRoadObject *aobj=MainForm->ActiveRoad->ActiveObj;
        if (aobj)
            {
            aobj->PutProperty(VarName.SubString(6,32),Value);
            }
        }
    }
else if (VarName.Pos("INSOBJ.")==1)
    {
    if (MainForm->ActiveRoad)
        {
        TRoadObject *aobj=MainForm->ActiveRoad->InsertingObj;
        if (aobj)
            {
            aobj->PutProperty(VarName.SubString(8,32),Value);
            }
        }
    }
else if (VarName.Pos("LOCAL.")==1)
    {
    FLocalVar->PutProperty(VarName.SubString(7,32),Value);
    }
else if (VarName.Pos("GLOBAL.")==1)
    {
    frmMacros->GlobalVar->PutProperty(VarName.SubString(8,32),Value);
    }
else
    {
    int p=VarName.Pos(".");
    if (p)
        {
        int n=FLocalObjects->IndexOf(VarName.SubString(1,p-1));
        if (n>=0)
            {
            TRoadObject *obj=(TRoadObject*)FLocalObjects->Objects[n];
            obj->PutProperty(VarName.SubString(p+1,32),Value);
            }
        }
    }
}

String __fastcall TMacros::GetValue(String VarName)
{
String Res=0;
if (VarName.Pos("AOBJ.")==1)
    {
    if (MainForm->ActiveRoad)
        {
        TRoadObject *aobj=MainForm->ActiveRoad->ActiveObj;
        if (aobj)
            Res=aobj->GetPropValue(VarName.SubString(6,32));
        }
    }
else if (VarName.Pos("INSOBJ.")==1)
    {
    if (MainForm->ActiveRoad)
        {
        TRoadObject *aobj=MainForm->ActiveRoad->InsertingObj;
        if (aobj)
            Res=aobj->GetPropValue(VarName.SubString(8,32));
        }
    }
else if (VarName.Pos("LOCAL.")==1)
    {
    Res=FLocalVar->GetPropValue(VarName.SubString(7,32));
    }
else if (VarName.Pos("GLOBAL.")==1)
    {
    Res=frmMacros->GlobalVar->GetPropValue(VarName.SubString(8,32));
    }
else
    {
    int p=VarName.Pos(".");
    if (p)
        {
        int n=FLocalObjects->IndexOf(VarName.SubString(1,p-1));
        if (n>=0)
            {
            TRoadObject *obj=(TRoadObject*)FLocalObjects->Objects[n];
            Res=obj->GetPropValue(VarName.SubString(p+1,32));
            }
        }
    }
return Res;
}

String __fastcall TMacros::Calculate(char **pstr)
{
String res=0;
char *str=*pstr;
char lexval[128];
char *plex=lexval;
int s=0;
while ((*str)&&(s>=0))
    {
    if (s==0)
        {
        if ((*str<='9')&&(*str>='0'))
            *(plex++)=*str,s=1;
        else if (*str=='"')
            s=4;
        else if ((*str<='Z')&&(*str>='A'))
            *(plex++)=*str,s=2;
        else if ((*str!=' ')&&(*str!='(')&&(*str!=')'))
            *(plex++)=*str,s=3;
        }
    else if (s==4)
        {
        if (*str=='"')
            s=-s;
        else
            *(plex++)=*str;
        }
    else if ((*str!=' ')&&(*str!='(')&&(*str!=')'))
        *(plex++)=*str;
    else
        s=-s;
    str++;
    }
*plex=0;
if (s>0) s=-s;
if ((s==-1)||(s==-4))
    res=String(lexval);
else if (s==-2)
    res=GetValue(lexval);
else
    {
    String p1=Calculate(&str);
    String p2=Calculate(&str);
    String op=String(lexval);
    if (op=="+")
        res=String(p1.ToDouble()+p2.ToDouble());
    else if (op=="*")
        res=String(p1.ToDouble()*p2.ToDouble());
    else if (op=="-")
        res=String(p1.ToDouble()-p2.ToDouble());
    else if (op=="/")
        res=String(p1.ToDouble()/p2.ToDouble());
    else if (op=="#")
        res=p1+p2;
    else if (op=="<")
        res=String((int)(p1.ToDouble()<p2.ToDouble()));
    else if (op==">")
        res=String((int)(p1.ToDouble()>p2.ToDouble()));
    else if (op=="=")
        res=String((int)(p1.ToDouble()==p2.ToDouble()));
    else if (op=="<=")
        res=String((int)(p1.ToDouble()<=p2.ToDouble()));
    else if (op==">=")
        res=String((int)(p1.ToDouble()>=p2.ToDouble()));
    else if (op=="<>")
        res=String((int)(p1.ToDouble()!=p2.ToDouble()));
    else if (op=="&")
        res=String((int)(p1.ToInt()&&p2.ToInt()));
    else if (op=="|")
        res=String((int)(p1.ToInt()||p2.ToInt()));
    }
*pstr=str;
return res;
}

void __fastcall TMacros::Operator_Set(String Param)
{
int pos=Param.Pos(" ");
if (pos)
    {
    char *s=Param.c_str();
    s+=pos;
    SetValue(Param.SubString(1,pos-1),Calculate(&s));
    }
}

void __fastcall TMacros::Operator_Run(String Param)
{
if (Param!="")
    {
    String FunPar;
    int funnum=GetOperator(Param,FunPar,Functions,FUNCOUNT);
    switch (funnum)
        {
        case 0: ShowMessage(FunPar);break;
        case 1: if (MainForm->ActiveRoad)
                    MainForm->ActiveRoad->MoveActiveObject();  break;
        case 2: if (MainForm->ActiveRoad)
                    {
                    if (Param=="")
                        MainForm->ActiveRoad->AddNewSign();
                    else
                        MainForm->ActiveRoad->AddNewSign(FunPar,0);
                    }break;
        case 3: {if (MainForm->ActiveRoad)
                    MainForm->ActiveRoad->NextObject();
                }break;
        case 4: {if (MainForm->ActiveRoad)
                    MainForm->ActiveRoad->PredObject();
                } break;
        case 5: {if (MainForm->ActiveRoad)
                    MainForm->ActiveRoad->RefreshPlan();
                } break;
        case 6: {if (MainForm->ActiveRoad)
                    {
                    if (MainForm->ActiveRoad->EditedData)
                        SetValue(FunPar,MainForm->ActiveRoad->EditedData->Objects->Count);
                    else
                        SetValue(FunPar,0);
                    }
                } break;
        case 8: {if (MainForm->ActiveRoad)
                    SetValue(FunPar,String(MainForm->ActiveRoad->MarkerL));
                 else
                    SetValue(FunPar,0);
                 } break;
        case 9: {if (MainForm->ActiveRoad)
                    {
                    int pos=GetValue(FunPar).ToInt();
                    MainForm->ActiveRoad->SetVideoPos(pos);
                    MainForm->ActiveRoad->SetMarkerPos(pos);
                    }
                } break;
        default : ShowMessage("Неизвестная функция");break;
        }
    }
}

int __fastcall TMacros::FindLabel(String Label)
{
int res=-1;
for (int i=0;i<Count;i++)
    {
    String Command=Strings[i].Trim();
    if (Command!="")
        {
        String Param;
        int opnum=GetOperator(Command,Param,Operators,OPCOUNT);
        if (opnum==1)
            {
            if (Param==Label)
                {
                res=i;
                break;
                }
            }
        }
    }
return res;
}

void __fastcall TMacros::Operator_Goto(String Param,int &CP)
{
int NewP=FindLabel(Param);
if (NewP>=0)
    CP=NewP;
else
    {
    ShowMessage("Метка "+Param+" не найдена");
    CP++;
    }
}

void __fastcall TMacros::Operator_If(String Param,int &CP)
{
char *par=Param.c_str();
String Val=Calculate(&par);
if (Val!="0")
    {
    Operator_Goto(String(par).Trim(),CP);
    }
else
    CP++;
}

void __fastcall TMacros::Operator_Dim(String Param)
{
int n=FLocalObjects->IndexOf(Param);
if (n<0)
    FLocalObjects->Add(Param);
}

bool __fastcall TMacros::Execute(void)
{
int CPos=0;
delete FLocalVar;
FLocalVar=new TRoadObject;
FLocalObjects->Clear();
while ((CPos>=0)&&(CPos<Count))
    {
    String Command=Strings[CPos].Trim();
    if (Command!="")
        {
        String Param;
        int opnum=GetOperator(Command,Param,Operators,OPCOUNT);
        if (opnum<0)
            ShowMessage("Неизвестный оператор "+Command);
        else if (opnum==2)
            Operator_Goto(Param,CPos);
        else if (opnum==3)
            Operator_If(Param,CPos);
        else if (opnum==4)
            Operator_Set(Param);
        else if (opnum==5)
            Operator_Run(Param);
        else if (opnum==6)
            Operator_Dim(Param);
        if ((opnum!=2)&&(opnum!=3))
            CPos++;
        }
    else
        CPos++;
    }
FLocalObjects->Clear();
delete FLocalVar;
FLocalVar=NULL;
return true;
}
