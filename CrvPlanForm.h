//---------------------------------------------------------------------------

#ifndef CrvPlanFormH
#define CrvPlanFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "DataSour.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TCurveParam : public TObject
{
public:
int L[4];
int Rad;
TCurveKind Direction;
TDangerCurve *InCrv;
TDangerCurve *CrcCrv;
TDangerCurve *OutCrv;
TCurveParam(TDangerCurve *in,TDangerCurve *crc,TDangerCurve *out);
bool Correct(void)
    {return L[0]&&L[1]&&L[2]&&L[3];}
void WriteInGrid(TStringGrid *Grid,int Index);
};

class TfrmCrvPlan : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TLabel *Label8;
    TLabel *Label18;
    TLabel *Label19;
    TSpeedButton *btSetCpPos;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TLabel *Label20;
    TSpeedButton *AutoCalcRad;
    TEdit *Edit_L1;
    TEdit *Edit_L2;
    TEdit *Edit_L3;
    TEdit *Edit_L4;
    TEdit *Edit_Rad;
    TGroupBox *GroupBox2;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *Edit_MinR;
    TGroupBox *GroupBox3;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TEdit *Edit_Crcl_Rad;
    TEdit *Edit_Crcl_DMax;
    TEdit *Edit_Crcl_DMid;
    TGroupBox *GroupBox4;
    TLabel *Label13;
    TLabel *Label14;
    TEdit *Edit_DMax;
    TEdit *Edit_In_DMid;
    TGroupBox *GroupBox5;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TEdit *Edit_Out_DMax;
    TEdit *Edit_Out_DMid;
    TComboBox *Combo_Dir;
    TEdit *Edit_Pos;
    TComboBox *ComboPartType;
    TComboBox *SelTrack;
    TTrackBar *Track;
    TBitBtn *BitBtn2;
    TUpDown *UpDownPos;
    TBitBtn *BitBtn3;
    TBitBtn *btnAdd;
    TBitBtn *btnSave;
    TBitBtn *btnDelete;
    TBitBtn *BitBtn1;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton8;
    TSpeedButton *SpeedButton9;
    TStringGrid *Grid;
    TSplitter *Splitter1;
    TPaintBox *PBox;
    TGroupBox *GroupBox6;
    TLabel *Label21;
    TLabel *Label22;
    TEdit *Edit_W1;
    TEdit *Edit_W2;
    TSpeedButton *AutoCalcInOut;
    TEdit *Edit_In_Rad;
    TEdit *Edit_Out_Rad;
    TLabel *Label23;
    TLabel *Label24;
    TEdit *Edit_CrIn_Rad;
    TEdit *Edit_CrOut_Rad;
    void __fastcall btSetCpPosClick(TObject *Sender);
    void __fastcall AutoCalcRadClick(TObject *Sender);
    void __fastcall SpeedButtonClick(TObject *Sender);
    void __fastcall SelTrackChange(TObject *Sender);
    void __fastcall TrackChange(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall BitBtn3Click(TObject *Sender);
    void __fastcall EditExit(TObject *Sender);
    void __fastcall EditKeyPress(TObject *Sender, char &Key);
    void __fastcall VideoClick(TObject *Sender);
    void __fastcall GridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall btnDeleteClick(TObject *Sender);
    void __fastcall GridClick(TObject *Sender);
    void __fastcall Edit_PosExit(TObject *Sender);
    void __fastcall Edit_PosKeyPress(TObject *Sender, char &Key);
    void __fastcall btnSaveClick(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall PBoxPaint(TObject *Sender);
    void __fastcall Edit_RadExit(TObject *Sender);
    void __fastcall Edit_RadKeyPress(TObject *Sender, char &Key);
    void __fastcall Edit_BndExit(TObject *Sender);
    void __fastcall Edit_BndKeyPress(TObject *Sender, char &Key);
    void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
    TDtaSource *FData;
    TDictSource *FDict;
    int CurvesCount;
    int EditIndex;
    TDangerCurve *FCrvIn;
    TDangerCurve *FCrvOut;
    TDangerCurve *FCrvCrcl;
    __int32 *ArrayPos;
    __int32 *ArrayRad;
    double *ArrayAngle;
    double *ArrayX;
    double *ArrayY;
    __int32 CrclStart;
    __int32 CrclEnd;
    __int32 InStart;
    __int32 OutEnd;
    __int32 ArraySize;
// Границы участка поворота
    __int32 Bounds[4];
// Границы участка окна
    __int32 WndBounds[2];
    __int32 Radius;
    bool FHasCurves;
    int FCpPosition;
    TDangerCurve* __fastcall UpdateCurve(TDangerCurve *Crv,__int32 L1,__int32 L2,TCurveKind knd);
    void __fastcall Sinchronize(void);
    void __fastcall FindCurveAt(__int32 Pos);
    void __fastcall GetBounds(void);
    void __fastcall GetWndBounds(void);
    void __fastcall TestBounds(void);
    void __fastcall EditCurves(void);
    void __fastcall GetCurves(void);
    double __fastcall CalcMidleRad(int lb, int ub);
    void __fastcall CalcCircleRad(void);
    void __fastcall GetRadiusData(void);
    void __fastcall SetTrack(int mn,int mx,int pos);
    void __fastcall SetTrackParam(void);
    int __fastcall GetCircleRad(int beg,int end);    
//    void __fastcall GetCircleParams(double*);
//    void __fastcall GetInCurveParams(double*,double);
//    void __fastcall GetOutCurveParams(double*,double);
    double __fastcall GetMaxDevLen(int* InBnd,int Rad);
    void __fastcall CalcExternBounds(void);
    void __fastcall CalcCircleBounds(void);
    void __fastcall CalcInOutBounds(void);
    void __fastcall AddTableItem(TDangerCurve*,TDangerCurve*,TDangerCurve*);
    void __fastcall ShowTable(void);
    void __fastcall ClearTable(void);
    void __fastcall DrawCurve(void);
public:		// User declarations
    __fastcall TfrmCrvPlan(TComponent* Owner);
    void __fastcall Initialize(TDtaSource *data,TDictSource *dict);
    void __fastcall SetViewPos(__int32 Pos);
    void __fastcall CalcParams(void);
    TDangerCurve* __fastcall GetCurve(__int32 Pos);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCrvPlan *frmCrvPlan;
//---------------------------------------------------------------------------
#endif
