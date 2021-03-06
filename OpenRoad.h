//---------------------------------------------------------------------------
#ifndef OpenRoadH
#define OpenRoadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
// ����� ��� ����������� ������ �����. ����������� ��� ��������� ����
// � ������ ������ ������ ������������� ��� � ������������� ������
// � ���������� mrOk
class TOpenRoadDialog : public TForm
{
__published:	// IDE-managed Components
   TDBGrid *DBGrid1;
   TADODataSet *ListRoads_DataSet;
   TDataSource *ListRoads_DataSource;
    TPanel *Panel1;
    TPanel *Panel2;
    TDBText *DBText1;
    TButton *Button1;
    TButton *Button2;
    TPanel *Panel3;
    TADODataSet *SubTitul_DataSet;
    TPanel *Panel4;
    TEdit *txtIDFilter;
    TEdit *txtFilter;
    TPanel *Panel5;
    TButton *Button3;
    TComboBox *cbGroup;
    TComboBox *cbDist;
   void __fastcall Button1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
   void __fastcall DBGrid1DblClick(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SetFilter(TObject *Sender);
    void __fastcall ListRoads_DataSetAfterScroll(TDataSet *DataSet);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall cbGroupChange(TObject *Sender);
private:	// User declarations
    String FRoadName;
    int lastGroupId;
    __int32 FRoadId;
    __int32 Mode;   // ������ 0 - ��� ������, 1 - ��������� 
    void __fastcall SetFilter(void);
public:		// User declarations
    void LoadIni(TIniFile *ini);
    void SaveIni(TIniFile *ini);    
    __fastcall TOpenRoadDialog(TComponent* Owner);
    __property __int32 RoadId={read=FRoadId};
    __property String RoadName={read=FRoadName};
};
//---------------------------------------------------------------------------
extern PACKAGE TOpenRoadDialog *OpenRoadDialog;
//---------------------------------------------------------------------------
#endif
