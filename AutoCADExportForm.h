//---------------------------------------------------------------------------

#ifndef AutoCADExportFormH
#define AutoCADExportFormH

//---------------------------------------------------------------------------s
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
#include <CheckLst.hpp>
#include "MainUnit.h"
#include <CheckLst.hpp>
#include "CSPIN.h"

#undef StrToInt

//#ifndef WITHOUT_AUTOCAD

#define MPROPERTY1(name)  __property bool Export##name = {read = get_Export##name};\
                          bool get_Export##name(){return chk##name->Checked;}

#define MPROPERTY2(name)  __property bool TableRow##name = {read = get_TableRow##name};\
                          bool get_TableRow##name(){return chk##name->Checked;}

#define MPROPERTY3(name)  __property int name = {read = get_##name};\
                          int get_##name()              \
                          {                                     \
                              static int last = 0;                 \
                              static cur;                            \
                              if(TryStrToInt(edt##name->Text.c_str(),cur)){  \
                                 last = cur;                          \
                                 return cur;                         \
                              }else{                                 \
                                  return last;                       \
                              }                                      \
                          }


#define MPROPERTY4(name)  __property int TableRow##name = {read = get_TableRow##name, write = set_TableRow##name};\
                          int get_TableRow##name(){return edt##name->Value;} \
                          void set_TableRow##name(int value){edt##name->Value = value;}

#define MPROPERTY5(name) __property WideString Edit##name = {read = get_Edit##name, write = set_Edit##name}; \
                          WideString get_Edit##name(){return edt##name->Text;} \
                          void set_Edit##name(WideString value){edt##name->Text = value;}

#define MPROPERTY6(name)  __property int name = {read = get_##name};\
                          int get_##name()              \
                          {                                     \
                              static cur;                            \
                              if(TryStrToInt(edt##name->Text.c_str(),cur)){  \
                                 return cur;                         \
                              }else{                                 \
                                  return -1;                       \
                              }                                      \
                          }


//---------------------------------------------------------------------------
class TFAutoCADExport : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox1;
   TGroupBox *GroupBox4;
   TComboBox *cbCurList;
   TComboBox *cbPrjList;
   TLabel *Label7;
   TLabel *Label8;
        TOpenDialog *OpenDialog2;
        TSaveDialog *SaveDialog1;
        TPanel *pnlLeft;
        TGroupBox *GroupBox10;
        TButton *Button6;
        TComboBox *edtPath;
        TLabel *Label28;
    TGroupBox *GroupBox6;
    TEdit *edtTopAddRows;
    TButton *btnTopAddRows;
    TComboBox *cmbRoad;
    TPanel *Panel3;
    TPanel *Panel2;
    TCheckBox *chkLamps;
    TCheckBox *chkSidewalks;
    TCheckBox *chkBorders;
    TCheckBox *chkMoundHeights;
    TCheckBox *chkCurves;
    TCheckBox *chkSlope;
    TCheckBox *chkRoadSideObjects;
    TCheckBox *chkBusstops;
    TCheckBox *chkSignal;
    TCheckBox *chkBridges;
    TCheckBox *chkMark;
    TCheckBox *chkTubes;
    TCheckBox *chkRoadSigns;
    TCheckBox *chkAttachments;
    TCheckBox *chkRoadMetrics;
    TCheckBox *chkTable;
    TCheckBox *chkSignalExistToo;
    TCheckBox *chkAll;
    TPanel *Panel1;
    TCheckBox *chkTown;
    TCheckBox *chkCommunications;
    TCheckBox *chkPlan;
    TCheckBox *chkProfile;
    TCheckBox *chkSurface;
    TCheckBox *chkAllPlan;
    TGroupBox *GroupBox9;
    TLabel *Label22;
    TEdit *edtGridStep;
    TCheckBox *chkGridStep;
    TPanel *Panel4;
    TPageControl *PageControl1;
    TTabSheet *TabSheet2;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label20;
    TLabel *Label9;
    TEdit *edtUnderTextHeight;
    TEdit *edtUnderTextYOffset;
    TCheckBox *chkAuto6_13;
    TCheckBox *chkLeftValueOnly6_13;
    TEdit *edtStep;
    TEdit *edtInfoTemplate;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox2;
    TLabel *Label4;
    TCSpinEdit *edtLinesBottom;
    TCheckListBox *listBottomRows;
    TGroupBox *GroupBox3;
    TLabel *Label3;
    TCSpinEdit *edtLinesTop;
    TCheckBox *chkRuler;
    TCheckListBox *listTopRows;
    TCheckBox *chkTopAddRowsWithoutData;
    TCheckBox *chkGraphic;
    TTabSheet *TabSheet3;
    TLabel *Label27;
    TLabel *Label2;
    TLabel *Label1;
    TLabel *Label12;
    TLabel *Label11;
    TLabel *Label21;
    TLabel *Label23;
    TGroupBox *GroupBox7;
    TLabel *Label10;
    TLabel *Label13;
    TCheckBox *chkMakeHeader;
    TEdit *edtHeaderWidth;
    TEdit *edtHeaderTextHeight;
    TEdit *edtRowHeight;
    TEdit *edtGrphRowHeight;
    TEdit *edtRCenter;
    TGroupBox *GroupBox13;
    TGroupBox *GroupBox12;
    TComboBox *edtTableHatch;
    TEdit *edtTableHatchScale;
    TGroupBox *GroupBox8;
    TComboBox *edtProfileHatch;
    TEdit *edtProfileHatchScale;
    TGroupBox *GroupBox11;
    TComboBox *edtSidewalksHatch;
    TEdit *edtSidewalksHatchScale;
    TEdit *edtNotExistsColor;
    TEdit *edtScaleY;
    TEdit *edtAutoShrinkOneLetterWidth;
    TGroupBox *GroupBox5;
    TLabel *Label14;
    TLabel *Label17;
    TLabel *Label15;
    TEdit *edtStart;
    TCheckBox *chkSection;
    TEdit *edtEnd;
    TPanel *Panel5;
    TButton *Button1;
    TButton *btnOk;
    TPanel *Panel6;
    TComboBox *cbIni;
    TRadioGroup *rgOut;
    TButton *Button3;
    TEdit *edtSmallGridMarkHeight;
    TLabel *Label26;
    TEdit *edtUseVerticalTextIfLess;
    TLabel *Label24;
    TButton *btnShowInfo;
    TEdit *edtMinBarrierSegmentLength;
    TLabel *Label16;
    TCheckBox *chkHideAutoCAD;
    TCheckBox *chkTrafficLights;
    TCheckBox *chkCityObjects;
    TCheckBox *chkShowAttachmentComments;
    TEdit *edtProjectBarrierPrefix;
    TLabel *Label18;
    TEdit *edtLineWidth;
    TLabel *Label19;
    TLabel *Label25;
    TEdit *edtScaleYBlock;
    TLabel *Label29;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall chkAllClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
   void __fastcall cbCurListChange(TObject *Sender);
   void __fastcall cbPrjListChange(TObject *Sender);
        void __fastcall btnTopAddRowsClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall listBottomRowsDragOver(TObject *Sender,
          TObject *Source, int X, int Y, TDragState State, bool &Accept);
        void __fastcall edtBottomAddRowsClick(TObject *Sender);
        void __fastcall edtTopAddRowsDblClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall cbIniChange(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall edtTopAddRowsChange(TObject *Sender);
        void __fastcall edtStartChange(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
    void __fastcall btnShowInfoClick(TObject *Sender);
private:	// User declarations
        AnsiString strIniFileName;
        void SaveIni(TIniFile *ini);
        void LoadIni(TIniFile *ini);
        int iCur,iPrj;
        int topAddRowsCount;
        int bottomAddRowsCount;
        bool fIniLoading;
        WideString get_EditTopAddRows();
        void set_EditTopAddRows(WideString value);        

public:		// User declarations
        __fastcall TFAutoCADExport(TComponent* Owner);
        void __fastcall SetRoadId(int rid);
        AnsiString RoadName;
        AnsiString RoadDistrict;

        int getExportTo(){return rgOut->ItemIndex;}
        AnsiString getFileName(){return ExtractFileDir(Application->ExeName)+"\\AutoCAD\\"+edtPath->Text;}

        MPROPERTY1(RoadMetrics);
        MPROPERTY1(Attachments);
        MPROPERTY1(RoadSigns);
        MPROPERTY1(Mark);
        MPROPERTY1(Tubes);
        MPROPERTY1(Bridges);
        MPROPERTY1(Signal);
        MPROPERTY1(SignalExistToo);
        MPROPERTY1(Busstops);
        MPROPERTY1(RoadSideObjects);
        MPROPERTY1(Slope);
        MPROPERTY1(Table);
        MPROPERTY1(Curves);
        MPROPERTY1(Lamps);
        MPROPERTY1(TrafficLights);
        MPROPERTY1(CityObjects);
        MPROPERTY1(MoundHeights);
        MPROPERTY1(Auto6_13);
        MPROPERTY1(LeftValueOnly6_13);
        MPROPERTY1(Sidewalks);
        MPROPERTY1(Borders);
        MPROPERTY1(Profile);
        MPROPERTY1(Plan);
        MPROPERTY1(Communications);
        MPROPERTY1(Town);
        MPROPERTY1(Surface);
        MPROPERTY1(MakeHeader);
        MPROPERTY1(HideAutoCAD);
        MPROPERTY1(ShowAttachmentComments);
        MPROPERTY1(TopAddRowsWithoutData);
        MPROPERTY1(GridStep);
        MPROPERTY1(Ruler);
        MPROPERTY1(Section);
        MPROPERTY1(Graphic);

        __property bool ExportAddRows = {read = get_ExportAddRows};\
        bool get_ExportAddRows(){
             return getTopRow("дополнительные строки")!=-1 && getBottomRow("дополнительные строки")!=-1 && !edtTopAddRows->Text.IsEmpty();
        }

        MPROPERTY3(RCenter);
        MPROPERTY3(NotExistsColor);
        MPROPERTY3(UnderTextYOffset);
        MPROPERTY3(AutoShrinkOneLetterWidth);
        MPROPERTY3(UnderTextHeight);
        MPROPERTY3(RowHeight);
        MPROPERTY3(MinBarrierSegmentLength)
        MPROPERTY3(GrphRowHeight);
        MPROPERTY3(HeaderWidth);
        MPROPERTY3(HeaderTextHeight);
        MPROPERTY3(UseVerticalTextIfLess);
        MPROPERTY3(SmallGridMarkHeight);
        MPROPERTY3(SidewalksHatchScale);
        MPROPERTY3(ProfileHatchScale);
        MPROPERTY3(TableHatchScale);

        MPROPERTY4(LinesTop);
        MPROPERTY4(LinesBottom);

        MPROPERTY5(SidewalksHatch);
        MPROPERTY5(ProfileHatch);
        MPROPERTY5(TableHatch);
        MPROPERTY5(InfoTemplate);
        MPROPERTY5(ProjectBarrierPrefix);

        MPROPERTY6(Start);
        MPROPERTY6(End);
        MPROPERTY6(Step);
        MPROPERTY6(GridStep);
        MPROPERTY6(ScaleY);
        MPROPERTY6(ScaleYBlock);        
        MPROPERTY6(LineWidth);

        __property int ExportTo = {read  = getExportTo};
        __property AnsiString FileName = {read = getFileName};
        __property WideString EditTopAddRows = {read = get_EditTopAddRows, write = set_EditTopAddRows};

        int getIndexOfItemInComboBox(TComboBox *combo, AnsiString value, bool fAddIfNotExist);

        int getTopRow(AnsiString rowName);
        int getBottomRow(AnsiString rowName);

        int setBottomAddRowsCount(int count);   /* это чтобы правильно пересчитывать позицию строк*/
        int setTopAddRowsCount(int count);      /* с учетом дополнительных строк надо вызвать по крайне мере*/
                                                /* один раз перед getTopRow и getBottomRow соответственно */
                                                /* с правильно пересчитанным значением count
                                                   функцией Export%Bottom|Top%AddRows(form->Edit%Bottom|Top%AddRows,true)
                                                   PS: дада... facepalm */

        int getRow(TCheckListBox *lb, AnsiString &rowName);
        void SaveRowsInfoToIni(TCheckListBox *list, TIniFile *ini);
        void LoadRowsInfoFromIni(TCheckListBox *list, TIniFile *ini);
        int countOfUnchecksBefore(TCheckListBox *list, int iRow);
        void SetupTEdits();

        void fillComboRoad();
        void locateRoadNameComboRoad();
        
        void __fastcall LoadSetupsInis();
        void __fastcall LoadTemplates();
        int __fastcall CountOfExports(); // returns count of selected items for export

};
//---------------------------------------------------------------------------
extern PACKAGE TFAutoCADExport *FAutoCADExport;
//---------------------------------------------------------------------------
//#endif  // WITHOUT_AUTOCAD

#endif

