//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SignsReports.h"
#include "ComObj.hpp"
#include "DbDataSource.h"


typedef int (*ReportFunction)(LPCSTR, LPCSTR, LPCSTR, bool, int);
const char GroupsName[8][48]={"Ошибочные коды","Предупреждающие знаки","Знаки приоритета","Запрещающие знаки","Предписывающие знаки","Информационно-указательные знаки","Знаки сервиса","Знаки дополнительной информации"};
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSignsReports *frmSignsReports;
//---------------------------------------------------------------------------
__fastcall TfrmSignsReports::TfrmSignsReports(TComponent* Owner)
    : TForm(Owner)
{
txtFilePath->Text=ExtractFilePath(Application->ExeName);
OpenDialog->InitialDir = txtFilePath->Text;
txtFileName->Text="SignRep.rtf";
}

//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::SetComboListItem(TComboBox *CBox,TDtaSource *Dta)
{
if (CBox->Items->Count>=0)
    {
    int index=0;
    for (int i=0;i<CBox->Items->Count;i++)
        if (Dta==CBox->Items->Objects[i])
            {index=i;break;}
    CBox->ItemIndex=index;
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::TestEnabled(void)
{
bool en=false;
for (int i=0;i<ReportsList->Items->Count;i++)
    if (ReportsList->Checked[i])
        {en=true;break;}
for (int i=0;i<TitulList->Items->Count;i++)
    if (TitulList->Checked[i])
        {en=true;break;}
btnMake->Enabled=en;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSignsReports::FormatPlacement(int l)
{
String Res=String(l/100000)+" + ";
l=(l%100000)/100;
String S=String(l);
while (S.Length()<3)
    S="0"+S;
return Res+S;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSignsReports::FormatSignPlacement(TRoadSign *sign)
{
String Res="";
switch (sign->Placement)
    {
    case spLeft: Res+=sign->Direction==roDirect? "Слева": "Справа"; break;
    case spRight: Res+=sign->Direction==roDirect? "Справа": "Слева"; break;
    case spBetween: Res+="На разделительной полосе";break;
    case spUp: Res+="Над проезжей частью";break;
    }
if ((sign->OnAttach==saOut)||(sign->OnAttach==saIn))
    Res+=", на примыкании ("+String(int(sign->DX/100+0.5))+"м.)";
return Res;
}


bool __fastcall TfrmSignsReports::Execute(TRoadFrm *frm)
{
FRoadFrm=frm;
ExistSourceList->Items->Clear();
DesignSourceList->Items->Clear();
for (int i=0;i<MainForm->ResManager->DataCount;i++)
    {
    TDtaSource *Dta=MainForm->ResManager->Data[i];
    if (Dta)
        if (Dta->Id==FRoadFrm->RoadId)
            {
            ExistSourceList->Items->AddObject(Dta->SourceName,Dta);
            DesignSourceList->Items->AddObject(Dta->SourceName,Dta);
            txtRoadDistr->Text=DBDataModule->GetDistrName(FRoadFrm->RoadId);
            String S=DBDataModule->GetInspectName(FRoadFrm->RoadId).Trim();
            int n=S.Pos(" ");
            if (n)
                txtDepDistr->Text=S.SubString(1,n-1);
            else
                txtDepDistr->Text=S;       
            txtDepCheef->Text=MainForm->CheefList->Values[txtDepDistr->Text];
            }
    }
SetComboListItem(ExistSourceList,FRoadFrm->MetricData);
SetComboListItem(DesignSourceList,FRoadFrm->EditedData);
TestEnabled();
return ShowModal()==mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::btnCloseClick(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::FormShow(TObject *Sender)
{
    txtStartPosition->Text = AnsiString(FRoadFrm->RoadMinL/100);
    txtEndPosition->Text = AnsiString(FRoadFrm->RoadMaxL/100);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::btnOpenReportFileClick(TObject *Sender)
{
OpenDialog->FileName=txtFilePath->Text+"\\"+txtFileName->Text;
OpenDialog->InitialDir=txtFilePath->Text;
if (OpenDialog->Execute())
    {
    txtFilePath->Text=ExtractFilePath(OpenDialog->FileName);
    txtFileName->Text=ExtractFileName(OpenDialog->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::btnMakeClick(TObject *Sender)
{
    __int32 MinL = txtStartPosition->Text.ToInt();
    __int32 MaxL = txtEndPosition->Text.ToInt();

//*** создадм объекты и подключимся к DBF-ным файлкам
    TADOConnection *DbfConnection;
    TADOCommand *DbfCommand;
    AnsiString DBFFolderPath = ExtractFilePath(Application->ExeName) + "DBFFiles";
    ChDir(DBFFolderPath);

    try
    {
        DbfConnection = new TADOConnection(NULL);
        DbfCommand = new TADOCommand(NULL);
        DbfConnection->ConnectionString = "Driver={Microsoft Visual FoxPro Driver};UID=;SourceDB=" + DBFFolderPath + ";SourceType=DBF;Exclusive=No;Collate=MACHINE;OLE DB Services = 0";
        DbfConnection->LoginPrompt = false;
        DbfConnection->Connected = true;
        DbfCommand->Connection = DbfConnection;
    }
    catch(EOleException &OleError)
    {
        ShowMessage("Возникла ошибка при открытии DBF файлов. Код ошибки: " + AnsiString(OleError.ErrorCode) + ". Сообщение: " + OleError.Message + ".");
        return;
    }

    DeleteTempDBFFiles(DbfCommand, DBFFolderPath);

    String TemplateFile;
    String ReportFile;
    String OutFile;
    FDesignSource=NULL;
    if (DesignSourceList->ItemIndex>=0)
        FDesignSource=dynamic_cast<TDtaSource*>(DesignSourceList->Items->Objects[DesignSourceList->ItemIndex]);
    FExistSource=NULL;
    if (ExistSourceList->ItemIndex>=0)
        FExistSource=dynamic_cast<TDtaSource*>(ExistSourceList->Items->Objects[ExistSourceList->ItemIndex]);
    MakeHeaderFile(DbfCommand,MinL*100,MaxL*100);
    try
        {
        String DllName;
        String RepExt;
        if (groupFormat->ItemIndex==0)
            {
            DllName="GenRep.dll";
            RepExt=".rtf";
            }
        else
            {
            DllName="HTMLGenRep.dll";
            RepExt=".htm";
            }

        AnsiString DllPath = ExtractFilePath(Application->ExeName) + DllName;
        HINSTANCE RepDll=LoadLibrary(DllPath.c_str());
        if (RepDll)
            {
            ReportFunction GenRep=(ReportFunction)GetProcAddress(RepDll,"GenRep");
            for (int i=0;i<ReportsList->Items->Count;i++)
                if (ReportsList->Checked[i])
                    {
                    switch (i)
                        {
                        case 0: MakeRoadSignRegister(DbfCommand,MinL,MaxL);break;
                        case 1: MakeNewRoadSignRegister(DbfCommand, MinL, MaxL);break;
                        case 2: MakeRoadSignSpecification(DbfCommand, MinL, MaxL);break;
                        case 3: MakeRoadSignPlacement(DbfCommand, MinL, MaxL);break;
                        case 4: MakeRoadMarkRegister(DbfCommand,MinL,MaxL);break;
                        }
                    TemplateFile="\\ReportTemplate"+String(i+1)+RepExt;
                    ReportFile="\\Report"+String(i+1)+".dbf";
                    OutFile=txtFileName->Text;
                    int pos=OutFile.Pos(".");
                    if (pos)
                        OutFile.Delete(pos,1000);
                    OutFile+=String(i+1)+RepExt;
                    if (DeleteFileDialog(txtFilePath->Text,OutFile))
                        {
                        try
                            {
                            String WorkPath=ExtractFilePath(Application->ExeName) + "DBFFiles";
                            DbfConnection->Connected = false;
                            GenRep(String(WorkPath+TemplateFile).c_str(), WorkPath.c_str(), String(txtFilePath->Text+OutFile).c_str(), true , 1);
                            DbfConnection->Connected = true;
                            }
                        catch (...)
                            {
                            ShowMessage("Во время формирования произошла ошибка. Обратитесь к разработчикам.");
                            }
                        }
                    DeleteFile(DBFFolderPath + ReportFile);
                    }
            for (int i=0;i<TitulList->Items->Count;i++)
                {
                if (TitulList->Checked[i])
                    {
                    TemplateFile="\\TitulTemplate"+String(i+1)+RepExt;
                    OutFile=txtFileName->Text;
                    int pos=OutFile.Pos(".");
                    if (pos)
                        OutFile.Delete(pos,1000);
                    OutFile+=String(i+1)+"_t"+RepExt;
                    try
                        {
                        String WorkPath=ExtractFilePath(Application->ExeName) + "DBFFiles";
                        DbfConnection->Connected = false;
                        GenRep(String(WorkPath+TemplateFile).c_str(), WorkPath.c_str(), String(txtFilePath->Text+OutFile).c_str(), true , 1);
                        DbfConnection->Connected = true;
                        }
                    catch (...)
                        {
                        ShowMessage("Во время формирования произошла ошибка. Обратитесь к разработчикам.");
                        }
                    }
                }
            FreeLibrary(RepDll);
            }
        else
            ShowMessage("Не найдена библиотека"+DllName);
        }
    catch(...)
        {
        ShowMessage("Ошибка при формировании отчета");
        }
    DbfConnection->Connected = false;
    delete DbfCommand;
    delete DbfConnection;
}
//---------------------------------------------------------------------------
// удалим временные DBF файлы, если они есть
void __fastcall TfrmSignsReports::DeleteTempDBFFile(TADOCommand *DbfCommand, String DBFPath,String DBFName)
{
TSearchRec sr;
if(FindFirst(DBFPath+"\\"+DBFName+".dbf", 0, sr) == 0)
    {
    DbfCommand->CommandText = "drop table "+DBFName;
    DbfCommand->Execute();
    }
}

bool __fastcall TfrmSignsReports::DeleteFileDialog(String Path,String FName)
{
bool Res=true;
TSearchRec sr;
if (FindFirst(Path+FName, 0, sr) == 0)
    {
    if (Application->MessageBox(String("Файл с именем "+FName+" уже существует. Вы хотите переписать его?").c_str(),"Предупреждение",MB_YESNO)==ID_YES)
        {
        if (!DeleteFile(Path+FName))
            {
            ShowMessage("Файл "+FName+" не может быть удален. Возможно файл занят другим приложением");
            Res=false;
            }
        }
    else
        Res=false;
    }

return Res;
}

void __fastcall TfrmSignsReports::DeleteTempDBFFiles(TADOCommand *DbfCommand, String DBFPath)
{
DeleteTempDBFFile(DbfCommand,DBFPath,"rep_temp");
DeleteTempDBFFile(DbfCommand,DBFPath,"report1");
DeleteTempDBFFile(DbfCommand,DBFPath,"report2");
DeleteTempDBFFile(DbfCommand,DBFPath,"report3");
DeleteTempDBFFile(DbfCommand,DBFPath,"report4");
DeleteTempDBFFile(DbfCommand,DBFPath,"report5_h");
DeleteTempDBFFile(DbfCommand,DBFPath,"report5_s");
DeleteTempDBFFile(DbfCommand,DBFPath,"report5");
DeleteTempDBFFile(DbfCommand,DBFPath,"rep_str");
}

String __fastcall TfrmSignsReports::Get_I(String S)
{
String Res=S.Trim();
int n=Res.Length()-1;
if ((Res.Pos("ий")==n)||(Res.Pos("ая")==n))
    {
    Res=Res.Delete(n,2);
    Res+="ого";
    }
return Res;
}
String __fastcall TfrmSignsReports::Get_T(String S)
{
String Res=S.Trim();
int n=Res.Length()-1;
if ((Res.Pos("ий")==n)||(Res.Pos("ая")==n))
    {
    Res[n]='и';
    Res[n+1]='м';
    }
return Res;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::MakeHeaderFile(TADOCommand *DbfCommand, __int32 MinL, __int32 MaxL)
{
    DbfCommand->CommandText = "create table rep_str (title char(100), begin char(100), end char(100), roaddist char (100), roaddist_i char (100), depdist char (100), depdist_i char (100), depdist_t char (100),depcheef char (100))";
    DbfCommand->Execute();
    DbfCommand->CommandText = "insert into rep_str (title, begin, end, roaddist, roaddist_i, depdist,depdist_i,depdist_t,depcheef) values ('" +
        FRoadFrm->RoadName+ "','"+FormatPlacement(MinL)+ "', '" + FormatPlacement(MaxL) +"','"+
        txtRoadDistr->Text+"','"+Get_I(txtRoadDistr->Text)+"','"+txtDepDistr->Text+"','"+Get_I(txtDepDistr->Text)+"','"+
        Get_T(txtDepDistr->Text)+"','"+txtDepCheef->Text+"')";
    DbfCommand->Execute();
}
//---------------------------------------------------------------------------
// СВОДНАЯ ВЕДОМОСТЬ ДОРОЖНЫХ ЗНАКОВ ->>
void __fastcall TfrmSignsReports::MakeRoadSignRegister(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd)
{
    // создадим файл для временных данных
    DbfCommand->CommandText = "create table rep_temp (\
        name char(100), number char(100), signgroup char(100), groupnum char(100),exist int,notexist int)";
    DbfCommand->Execute();
            // Записываем существующие знаки
    int n=FExistSource->Objects->Count;
    for (int i=0;i<n;i++)
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FExistSource->Objects->Items[i]);
        if (sign)
            if((sign->L/100 >= SectionBegin) && (sign->L/100 <= SectionEnd))
                {
                AnsiString SignName = FRoadFrm->Dict->GetTitle(sign->NumRoadSign);
                AnsiString SignNumber = FRoadFrm->Dict->GetShortTitle(sign->NumRoadSign);
                if (SignNumber=="")
                    ShowMessage("Неверно указан код знака "+String(sign->L));
                else
                    {
                    int numgroup=SignNumber[1]-'0';
                    if ((numgroup>7) || (numgroup<1))
                        numgroup=0;
                    DbfCommand->CommandText = "insert into rep_temp (name, number, signgroup, groupnum,\
                        exist, notexist) values ('" + SignName + "' , '" + SignNumber + "', '" +
                        GroupsName[numgroup] + "', '" + String(numgroup) + "', 1,0)";
                    DbfCommand->Execute();
                    }
                }
        }
            // Записываем проектные знаки
    n = FDesignSource->Objects->Count;
    for (int i=0;i<n;i++)
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FDesignSource->Objects->Items[i]);
        if (sign)
            if((sign->L/100 >= SectionBegin) && (sign->L/100 <= SectionEnd))
                {
                AnsiString SignName = FRoadFrm->Dict->GetTitle(sign->NumRoadSign);
                AnsiString SignNumber = FRoadFrm->Dict->GetShortTitle(sign->NumRoadSign);
                int numgroup=SignNumber[1]-'0';
                if ((numgroup>7) || (numgroup<1))
                    numgroup=0;
                DbfCommand->CommandText = "insert into rep_temp (name, number, signgroup, groupnum,\
                    exist, notexist) values ('" + SignName + "' , '" + SignNumber + "', '" +
                    GroupsName[numgroup] + "', '" + String(numgroup) + "', 0,1)";
                DbfCommand->Execute();
                }
        }


    // создадим и заполним данными итоговую таблицу
    DbfCommand->CommandText = "create table report1 (\
        signgroup char(100),name char(100),number char(100),exist int,notexist int, add char(10), remove char(10))";
    DbfCommand->Execute();

    TADODataSet* DbfDataSet = new TADODataSet(NULL);
    DbfDataSet->Connection = DbfCommand->Connection;//DbfConnection;

    DbfDataSet->CommandType = cmdText;
    DbfDataSet->CommandText = "select name, number, signgroup, groupnum, sum(exist) exist, sum(notexist) notexist from rep_temp group by name, number, signgroup, groupnum order by groupnum, number";
    DbfDataSet->Active = true;

    while(!DbfDataSet->Eof)
    {
        AnsiString AddSign = "";
        AnsiString RemoveSign = "";
        __int32 OldSigns = DbfDataSet->FieldByName("exist")->AsInteger;
        __int32 NewSigns = DbfDataSet->FieldByName("notexist")->AsInteger;
        if(OldSigns > NewSigns)
            RemoveSign = (OldSigns - NewSigns);
        else
            if(OldSigns < NewSigns)
                AddSign = (NewSigns - OldSigns);

    DbfCommand->CommandText = "insert into report1 (signgroup, name, number, exist, notexist, add, remove) values ('" + DbfDataSet->FieldByName("signgroup")->AsString + "', '" + DbfDataSet->FieldByName("name")->AsString + "', '" + DbfDataSet->FieldByName("number")->AsString + "', " + DbfDataSet->FieldByName("exist")->AsString + ", " + DbfDataSet->FieldByName("notexist")->AsString + ", '" + AddSign + "', '" + RemoveSign + "')";
    DbfCommand->Execute();
    DbfDataSet->Next();
    }

    delete DbfDataSet;
}// СВОДНАЯ ВЕДОМОСТЬ ДОРОЖНЫХ ЗНАКОВ <<-

//*************************************************************
// ВЕДОМОСТЬ УСТАНОВКИ ПРОЕКТНЫХ ЗНАКОВ ->>


struct SignClassRec
    {int Num;int Code;int Count;};
int comparefunc(const void *Var1,const void* Var2)
{
if (((SignClassRec*)Var1)->Code<((SignClassRec*)Var2)->Code)
    return -1;
else
if (((SignClassRec*)Var1)->Code>((SignClassRec*)Var2)->Code)
    return 1;
return 0;
}

void __fastcall TfrmSignsReports::MakeTitulSheet(TADOCommand *DbfCommand,__int32 SectionBegin, __int32 SectionEnd)
{

}

void __fastcall TfrmSignsReports::MakeNewRoadSignRegister(TADOCommand *DbfCommand, __int32 LMin, __int32 LMax)
{
struct SignClassRec SgnClass[500];
int ClassCount=0;

    DbfCommand->CommandText="create table report2 (sgngroup char(50),code char(20),name char(50), scount int)";
    DbfCommand->Execute();
    int n=FDesignSource->Objects->Count;
    for (int i=0;i<n;i++)
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FDesignSource->Objects->Items[i]);
        if (sign)
            if((sign->L/100 >= LMin) && (sign->L/100 <= LMax))
                {
                int j;
                for (j=0;j<ClassCount;j++)
                    if (SgnClass[j].Num==sign->NumRoadSign)
                        break;
                if (j<ClassCount)
                    SgnClass[j].Count++;
                else
                    {
                    SgnClass[ClassCount].Num=sign->NumRoadSign;
                    SgnClass[ClassCount].Count=1;
                    String S=FRoadFrm->Dict->GetShortTitle(sign->NumRoadSign);
                    char *c=S.c_str();
                    int p=0;
                    int cd[4]={0,0,0,0};
                    while (*c&&(p<3))
                        {
                        if ((*c>='0')&&(*c<='9'))
                            cd[p]=cd[p]*10+*c-'0';
                        else if (*c=='.')
                            p++;
                        c++;
                        }
                    SgnClass[ClassCount].Code=(cd[0]<<16)+(cd[1]<<8)+cd[2];
                    ClassCount++;
                    }
                }
        }
qsort(SgnClass,ClassCount,sizeof(SignClassRec),comparefunc);
for (int i=0;i<ClassCount;i++)
    {
    int numgroup=SgnClass[i].Code>>16;
    if ((numgroup>7) || (numgroup<1))
       numgroup=0;
    DbfCommand->CommandText="insert into report2 (sgngroup,code, name, scount) values ('"+
        String(GroupsName[numgroup])+"','"+FRoadFrm->Dict->GetShortTitle(SgnClass[i].Num)+"','"+
        FRoadFrm->Dict->GetTitle(SgnClass[i].Num)+"',"+String(SgnClass[i].Count)+")";
    DbfCommand->Execute();
    }
}
//*************************************************************
// ВЕДОМОСТЬ УСТАНОВКИ/УДАЛЕНИЯ ДОРОЖНЫХ ЗНАКОВ <<
void __fastcall TfrmSignsReports::AssistSpec(TADOCommand *DbfCommand,TRoadSign *sign,int action)
{
String Act=action?"УСТАНОВИТЬ" : "УДАЛИТЬ";
DbfCommand->CommandText = "insert into report3 (name,number,place,action) values ('"+
FRoadFrm->Dict->GetTitle(sign->NumRoadSign)+"','"+FRoadFrm->Dict->GetShortTitle(sign->NumRoadSign)+"','"+
FormatPlacement(sign->L)+"','"+Act+"')";
DbfCommand->Execute();
}

void __fastcall TfrmSignsReports::MakeRoadSignPlacement(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd)
{
DbfCommand->CommandText = "create table report4 (name char(100), number char(16), place char(16), comment char(100))";
DbfCommand->Execute();
for (int i=0;i<FDesignSource->Objects->Count;i++)
    {
    TRoadSign *sign=dynamic_cast<TRoadSign*>(FExistSource->Objects->Items[i]);
    if (sign)
        {
        String Plc;
        DbfCommand->CommandText="insert into report4 (name,number,place,comment) values ('"+
            FRoadFrm->Dict->GetTitle(sign->NumRoadSign)+"','"+
            FRoadFrm->Dict->GetShortTitle(sign->NumRoadSign)+"','"+
            FormatPlacement(sign->L)+"','"+
            FormatSignPlacement(sign)+"')";
        DbfCommand->Execute();
        }
    }
}

void __fastcall TfrmSignsReports::MakeRoadSignSpecification(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd)
{
    DbfCommand->CommandText = "create table report3 (name char(100), number char(16), place char(16), action char (16))";
    DbfCommand->Execute();
    int n=FExistSource->Objects->Count;
    for (int i=0;i<n;i++)  // Пометим все знаки
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FExistSource->Objects->Items[i]);
        if (sign)
            sign->Tag=1;
        }
    int m=FDesignSource->Objects->Count;
    for (int i=0;i<m;i++)
        {
        TRoadSign *sign=dynamic_cast<TRoadSign*>(FDesignSource->Objects->Items[i]);
        if (sign)
            {// Перемещение в пределах 10 метров считаем несущественным
            sign->Tag=1;
            int ind1,ind2;
            if (FExistSource->BinarySearch(sign->L-1000,sign->L+1000,ind1,ind2))
                {
                while (ind1<=ind2)
                    {
                    TRoadSign *exsign=dynamic_cast<TRoadSign*>(FExistSource->Objects->Items[ind1]);
                    if (exsign)
                        if ((exsign->Tag)&&(exsign->NumRoadSign==sign->NumRoadSign)&&(exsign->Direction==sign->Direction)&&(exsign->Placement==sign->Placement))
                            {
                            exsign->Tag=0;
                            sign->Tag=0;
                            break;
                            }
                    ind1++;
                    }
                }
            }
        }
    int i=0;
    int j=0;
    TRoadSign *dessign=NULL;
    TRoadSign *exsign=NULL;
    while ((i<n)&&(j<m))
        {
        while ((i<n)&&(!exsign))
            {
            exsign=dynamic_cast<TRoadSign*>(FExistSource->Objects->Items[i]);
            if (exsign)
                if (exsign->Tag==0)  // Непомеченные знаки пропускаем
                    exsign=NULL;
            i++;
            }
        while ((j<m)&&(!dessign))
            {
            dessign=dynamic_cast<TRoadSign*>(FDesignSource->Objects->Items[j]);
            if (dessign)
                if (dessign->Tag==0)
                    dessign=NULL;
            j++;
            }
        if (exsign)
            {
            if (dessign)
                {
                if (exsign->L<dessign->L)
                    {
                    AssistSpec(DbfCommand,exsign,0);
                    exsign->Tag=0;
                    exsign=NULL;
                    }
                else
                    {
                    AssistSpec(DbfCommand,dessign,1);
                    dessign->Tag=0;
                    dessign=NULL;
                    }
                }
            else
                {
                AssistSpec(DbfCommand,exsign,0);
                exsign->Tag=0;
                exsign=NULL;
                }
            }
        else if (dessign)
            {
            AssistSpec(DbfCommand,dessign,1);
            dessign->Tag=0;
            dessign=NULL;
            }
        }
}

void __fastcall TfrmSignsReports::MakeRoadMarkRegister(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd)
{
int ShTitlesCount=0;
String ShTitles[32];
int  ShIndexes[32];
typedef int IntArray32[32];
IntArray32 *MarkLens;
bool Measure[32];
for (int i=0;i<FDesignSource->Objects->Count;i++)
    {
    TRoadMark *mark=dynamic_cast<TRoadMark*>(FDesignSource->Objects->Items[i]);
    if (mark)
        {
        String ShTitl=FRoadFrm->Dict->GetShortTitle(mark->Kind);
        int j;
        for (j=0;j<ShTitlesCount;j++)
            if (ShTitl==ShTitles[j])
                break;
        if (j==ShTitlesCount)
            {
            ShTitles[ShTitlesCount]=FRoadFrm->Dict->GetShortTitle(mark->Kind);
            ShIndexes[ShTitlesCount]=FRoadFrm->Dict->GetPropValIndex(mark->Kind);
            ShTitlesCount++;
            }
        }
    }
// Сортируем заголовки
for (int i=0;i<ShTitlesCount-1;i++)
    for (int j=i+1;j<ShTitlesCount;j++)
        if (ShIndexes[i]>ShIndexes[j])
        {
        String t=ShTitles[i];
        ShTitles[i]=ShTitles[j];
        ShTitles[j]=t;
        int tmp=ShIndexes[i];
        ShIndexes[i]=ShIndexes[j];
        ShIndexes[j]=tmp;
        }
String Cm="create table report5_h (";
for (int i=0;i<31;i++)
    {
    Cm+="val"+String(i)+" char(16),";
    }
Cm+="val31 char(16))";
DbfCommand->CommandText=Cm;
DbfCommand->Execute();
Cm="insert into report5_h (";
for (int i=0;i<ShTitlesCount;i++)
    {
    if (i)
        Cm+=",";
    Cm+="val"+String(i);
    }
Cm+=") values (";
for (int i=0;i<ShTitlesCount;i++)
    {
    if (i)
        Cm+=",";
    char *p=ShTitles[i].c_str();
    int k=0;
    int n=0;
    while (*p)
        {
        if (*p=='.')
            k++;
        else if (k==1)
            n=n*10+*p-'0';
        p++;
        }
    Measure[i]=(n==16)||((n<25)&&(n>=18));
    String Ed;
    if (Measure[i])
        Ed="(шт)";
    else
        Ed="(м)";
    Cm+="'"+ShTitles[i]+" "+Ed+"'";
    }
Cm+=")";
DbfCommand->CommandText=Cm;
DbfCommand->Execute();
int rowsstart=(SectionBegin/1000);
int rowscount=(SectionEnd+999)/1000-rowsstart;
MarkLens=new IntArray32 [rowscount];
int SumLength[32];
for (int i=0;i<32;i++)
    {
    SumLength[i]=0;
    for (int j=0;j<rowscount;j++)
        MarkLens[j][i]=0;
    }
for (int i=0;i<FDesignSource->Objects->Count;i++)
    {
    TRoadMark *mark=dynamic_cast<TRoadMark*>(FDesignSource->Objects->Items[i]);
    if (mark)
        {
        String ShTitl=FRoadFrm->Dict->GetShortTitle(mark->Kind);
        int j;
        for (j=0;j<ShTitlesCount;j++)
            if (ShTitl==ShTitles[j])
                break;
        if (Measure[j])
            {
            SumLength[j]++;
            if (mark->Direction==roUnDirect)
                MarkLens[(mark->LMax/100000)-rowsstart][j]++;
            else
                MarkLens[(mark->LMin/100000)-rowsstart][j]++;
            }
        else
            {
            int MarkDL=mark->LMax-mark->LMin;
            int LPos=mark->LMin;
            int PartPos=mark->LMin/100000;
            int MarkLen=(mark->Length+50)/100; //Длина Разметки в метрах
            int SumLen=0;         // Для хранения суммы записанных длин по участкам
            if (LPos<mark->LMax)
                while (LPos<mark->LMax)
                    {
                    int PartEnd=(PartPos+1)*100000;
                    if (PartEnd>mark->LMax)   // Пишем последний участок
                        {
                        MarkLens[PartPos-rowsstart][j]+=MarkLen-SumLen;
                        PartEnd=mark->LMax;
                        }
                    else
                        {
                        int WLen=(double)MarkLen*(PartEnd-LPos)/MarkDL;
                        MarkLens[PartPos-rowsstart][j]+=WLen;
                        SumLen+=WLen;
                        }
                    PartPos++;
                    LPos=PartPos*100000;
                    }
            else
                MarkLens[PartPos-rowsstart][j]+=MarkLen;
            SumLength[j]+=MarkLen;
            }
        }
    }
Cm="create table report5 (";
for (int i=0;i<32;i++)
    Cm+="val"+String(i)+" int,";
Cm+="pos char(12))";
DbfCommand->CommandText=Cm;
DbfCommand->Execute();
for (int j=0;j<rowscount;j++)
    {
    Cm="insert into report5 (";
    for (int i=0;i<ShTitlesCount;i++)
        Cm+="val"+String(i)+",";
    Cm+="pos) values (";
    for (int i=0;i<ShTitlesCount;i++)
        Cm+=String(MarkLens[j][i])+",";
    Cm+="'"+String(j+rowsstart)+"-"+String(j+rowsstart+1)+"')";
    DbfCommand->CommandText=Cm;
    DbfCommand->Execute();
    }
// Выводим строку итого

Cm="create table report5_s (";
for (int i=0;i<31;i++)
    Cm+="val"+String(i)+" int,";
Cm+="val31 int)";
DbfCommand->CommandText=Cm;
DbfCommand->Execute();


Cm="insert into report5_s (";
for (int i=0;i<ShTitlesCount;i++)
    {
    if (i)
        Cm+=",";
    Cm+="val"+String(i);
    }
Cm+=") values (";
for (int i=0;i<ShTitlesCount;i++)
    {
    if (i)
        Cm+=",";
    Cm+=String(SumLength[i]);
    }
Cm+=")";
DbfCommand->CommandText=Cm;
DbfCommand->Execute();
delete MarkLens;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSignsReports::txtStartPositionExit(TObject *Sender)
{
    if((txtStartPosition->Text.ToInt() < FRoadFrm->MinL/100) ||
       (txtStartPosition->Text.ToInt() > FRoadFrm->MaxL/100))
        txtStartPosition->Text = FRoadFrm->MinL/100;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSignsReports::txtEndPositionExit(TObject *Sender)
{
    if((txtEndPosition->Text.ToInt() < FRoadFrm->MinL/100) ||
       (txtEndPosition->Text.ToInt() > FRoadFrm->MaxL/100))
        txtEndPosition->Text = FRoadFrm->MaxL/100;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSignsReports::ReportsListClickCheck(TObject *Sender)
{
TestEnabled();
}
//---------------------------------------------------------------------------

