//---------------------------------------------------------------------------

#ifndef SignsReportsH
#define SignsReportsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include "MainUnit.h"
#include <CheckLst.hpp>
#include "ShowRoad.h"
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TfrmSignsReports : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label2;
    TButton *btnMake;
    TButton *btnClose;
    TEdit *txtStartPosition;
    TEdit *txtEndPosition;
    TEdit *txtFileName;
    TLabel *Label3;
    TButton *btnOpenReportFile;
    TOpenDialog *OpenDialog;
    TCheckListBox *ReportsList;
    TGroupBox *GroupBox3;
    TLabel *Label4;
    TLabel *Label5;
    TComboBox *DesignSourceList;
    TComboBox *ExistSourceList;
    TLabel *Label6;
    TEdit *txtFilePath;
    TGroupBox *GroupBox4;
    TCheckListBox *TitulList;
    TLabel *Label7;
    TEdit *txtRoadDistr;
    TLabel *Label8;
    TEdit *txtDepDistr;
    TLabel *Label9;
    TEdit *txtDepCheef;
    TRadioGroup *groupFormat;
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnOpenReportFileClick(TObject *Sender);
    void __fastcall btnMakeClick(TObject *Sender);
    void __fastcall txtStartPositionExit(TObject *Sender);
    void __fastcall txtEndPositionExit(TObject *Sender);
    void __fastcall ReportsListClickCheck(TObject *Sender);
private:	// User declarations
    TRoadFrm *FRoadFrm;
    TDtaSource *FDesignSource;
    TDtaSource *FExistSource;
    void __fastcall SetComboListItem(TComboBox *CBox,TDtaSource *Dta);
    String __fastcall FormatPlacement(int l);
    String __fastcall FormatSignPlacement(TRoadSign *sgn);
    void __fastcall TestEnabled(void);
    // вспомогательные функции
    bool __fastcall DeleteFileDialog(String Path,String FName);
    void __fastcall DeleteTempDBFFile(TADOCommand *DbfCommand, String DBFPath,String DBFName);
    void __fastcall DeleteTempDBFFiles(TADOCommand *DbfCommand, AnsiString DBFFolderPath);
    // функции формирования отчётов
    void __fastcall MakeHeaderFile(TADOCommand *DbfCommand,__int32 SectionBegin, __int32 SectionEnd);
    void __fastcall MakeTitulSheet(TADOCommand *DbfCommand,__int32 SectionBegin, __int32 SectionEnd);
    void __fastcall MakeRoadSignRegister(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd);// СВОДНАЯ ВЕДОМОСТЬ ДОРОЖНЫХ ЗНАКОВ
    void __fastcall MakeNewRoadSignRegister(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd);
    void __fastcall MakeRoadSignSpecification(TADOCommand *DbfCommand, __int32 SectionBegin, __int32 SectionEnd);
    void __fastcall MakeRoadSignPlacement(TADOCommand *DbfCommand, __int32 MinL, __int32 MaxL); // ВЕДОМОСТЬ УСТАНОВКИ ПРОЕКТНЫХ ЗНАКОВ
    void __fastcall MakeRoadMarkRegister(TADOCommand *DbfCommand, __int32 MinL, __int32 MaxL); // Разметка    
    //Вспомогательная функция для третьего отчета
    void __fastcall AssistSpec(TADOCommand *DbfCommand,TRoadSign *sign,int action);
    // Функции для склонения прилагательных (названий районов)
    String __fastcall Get_T(String S);
    String __fastcall Get_I(String S);
public:		// User declarations
    __fastcall TfrmSignsReports(TComponent* Owner);
    bool __fastcall Execute(TRoadFrm *);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSignsReports *frmSignsReports;
//---------------------------------------------------------------------------
#endif
