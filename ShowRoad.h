//---------------------------------------------------------------------------
#ifndef ShowRoadH
#define ShowRoadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "DrawMan.h"
#include "DataSour.h"
#include "Ruler.h"
#include "ListForm.h"
#include "VisSetForm.h"
#include "unSignalsInsert.h"
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
enum TZoomStatus {zsNone,zsWaitZoom,zsZoom,zsWaitPoint,zsWaitSecPoint,zsMovePoint,zsFocusRect};
#define MAXSEL 16
#define HIDEBOUND 4
#define KFLEEP 10 // ����������� ���������� ��� ������, ��� ������ ���������
#define SQRT2 1.4142135623730950488016887242097
#define SELBOUND 5
struct TSelectObj
{
bool Visible;
TCanvas *Canvas;
TDrawManager *Man;
int index;
TSelectObj(TCanvas *ACanvas, TDrawManager *AMan)
    {Canvas=ACanvas;Man=AMan;Visible=false;}
void __fastcall NewPicture(void)
    {
    if (Visible)
        {
        Visible=false;
        Draw();
        }
    }
void __fastcall Draw(void)
    {
    Man->DrawObjectMetric(Canvas->Handle,index);
    Visible=!Visible;
    }
void __fastcall operator()(void)
    {
    if (Visible)
        Draw();
    }
void __fastcall operator()(int Aindex)
    {index=Aindex;
     Draw();}
};

struct TSelectRect
{
bool Visible;
TCanvas *Canvas;
RECT rect;
TSelectRect(TCanvas *ACanvas)
    {Canvas=ACanvas;
     rect.left=0;rect.right=0;
     rect.top=0;rect.bottom=0;
     Visible=false;
    }
void __fastcall NewPicture()
    {
    if (Visible)
        {
        Visible=false;
        Draw();
        }
    }
void __fastcall Draw(void)
    {
    TPenMode pm=Canvas->Pen->Mode;
    Canvas->Pen->Mode=pmXor;
    Canvas->Pen->Color=clYellow;
    int oldwidth=Canvas->Pen->Width;
    Canvas->Pen->Width=2;
    Canvas->MoveTo(rect.left,rect.top);
    Canvas->LineTo(rect.right,rect.top);
    Canvas->LineTo(rect.right,rect.bottom);
    Canvas->LineTo(rect.left,rect.bottom);
    Canvas->LineTo(rect.left,rect.top);
    Canvas->Pen->Width=oldwidth;
    Canvas->Pen->Mode=pm;
    Visible=!Visible;
    }
void __fastcall operator()(void)
    {
    if (Visible)
        Draw();
    }
void __fastcall operator()(RECT Arect)
    {rect.left=Arect.left-SELBOUND;
     rect.right=Arect.right+SELBOUND;
     rect.top=Arect.top-SELBOUND;
     rect.bottom=Arect.bottom+SELBOUND;
     Draw();}
};

class TRoadFrm : public TForm
{
__published:    // IDE-managed Components
    TPopupMenu *Popup;
    TMenuItem *N11;
    TMenuItem *N21;
    TMenuItem *N31;
    TScrollBar *HScroll;
    TMenuItem *N1;
    TPanel *CPanel;
    TPanel *ToolPan;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TEdit *SclXVal;
    TPanel *RulPanel;
    TSplitter *Splitter1;
    TPanel *ARulPan;
    TPanel *VisPan;
    TSplitter *Splitter2;
    TPanel *AVisPan;
    TSplitter *Splitter3;
    TPanel *ProPan;
    TPanel *PlanPan;
    TPaintBox *PBox;
    TPanel *VRulPanel;
    TSplitter *Splitter4;
    TScrollBar *VScroll;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TPopupMenu *PopMenu;
    TPaintBox *PrBox;
    TPaintBox *PvBox;
    TSpeedButton *SpeedButton8;
    TComboBox *SclLVal;
    TSpeedButton *SpeedButton9;
    TSpeedButton *SpeedButton10;
    TSpeedButton *SpeedButton11;
    TSpeedButton *SpeedButton12;
    TSpeedButton *SpeedButton15;
    TComboBox *KmSet;
    TSpeedButton *SpeedButton13;
    TStatusBar *StatusBar;
    TSpeedButton *SpeedButton14;
    TSpeedButton *SpeedButton16;
    TSpeedButton *SpeedButton17;
    TSpeedButton *SpeedButton18;
    TSpeedButton *SpeedButton19;
    TPopupMenu *ObjMenu;
    TMenuItem *ObjMenu_Edit;
    TMenuItem *ObjMenu_Delete;
    TMenuItem *ObjMenu_Move;
    TMenuItem *ObjMenu_Sign;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TSpeedButton *SpeedButton20;
    TComboBox *PageSet;
    TMenuItem *ObjMenu_Mark;
    TMenuItem *ObjMenu_ContinueMark;
   TMenuItem *N9;
   TPanel *AVisModePan;
   TPanel *VisModePan;
   TSplitter *Splitter5;
   TMenuItem *N10;
   TPaintBox *PvisBox;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall PaintRoad(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall ShowEntRoad(TObject *Sender);
    void __fastcall HScrollChange(TObject *Sender);
    void __fastcall N11Click(TObject *Sender);
    void __fastcall N21Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall PBoxMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall PBoxMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall PBoxMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall VScrollChange(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall SpeedButton6Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall N31Click(TObject *Sender);
    void __fastcall SclXValKeyPress(TObject *Sender, char &Key);

    void __fastcall SclLValKeyPress(TObject *Sender, char &Key);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
  void __fastcall PrBoxPaint(TObject *Sender);
  void __fastcall PvBoxPaint(TObject *Sender);
  void __fastcall SplitterMoved(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
    void __fastcall SclLValSelect(TObject *Sender);
    void __fastcall SpeedButton11Click(TObject *Sender);
    void __fastcall SpeedButton9Click(TObject *Sender);
    void __fastcall SpeedButton10Click(TObject *Sender);
    void __fastcall SpeedButton12Click(TObject *Sender);
    void __fastcall SpeedButton15Click(TObject *Sender);
    void __fastcall KmSetChange(TObject *Sender);
    void __fastcall SpeedButton13Click(TObject *Sender);
    void __fastcall SpeedButton14Click(TObject *Sender);
    void __fastcall SpeedButton16Click(TObject *Sender);
    void __fastcall SpeedButton17Click(TObject *Sender);
    void __fastcall SpeedButton18Click(TObject *Sender);
    void __fastcall SpeedButton19Click(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ObjMenu_EditClick(TObject *Sender);
    void __fastcall ObjMenu_MoveClick(TObject *Sender);
    void __fastcall ObjMenu_DeleteClick(TObject *Sender);
    void __fastcall ObjMenu_SignClick(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N7Click(TObject *Sender);
    void __fastcall N8Click(TObject *Sender);
    void __fastcall SpeedButton20Click(TObject *Sender);
    void __fastcall PageSetChange(TObject *Sender);
    void __fastcall ObjMenu_MarkClick(TObject *Sender);
    void __fastcall ObjMenu_ContinueMarkClick(TObject *Sender);
   void __fastcall N9Click(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall N10Click(TObject *Sender);
   void __fastcall PvisBoxPaint(TObject *Sender);
   void __fastcall PvisBoxMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:        // User declarations
       /* ���� */
       TObjPlacement lPlace;
	    TRoadSignalKind lKind;
	    TfrmSignalsInsert *frmSignalsInsert1;
	    bool fMishaWantMorePoints;
	    TRoadPoint lPointAddingPoint;
       int AutoPointFreq;
       bool fBreakedLines;
       /* ���� */

    bool FReadyForDrawing;
    bool FRectVisible; //true e��� ������������ �����
    TZoomStatus ZoomStatus;//

    void __fastcall HandlePutPoint(int X,int Y,bool Leep);

    bool CPVisible;
    POINT CP;        // ����� ��� �������
    void __fastcall MoveCurrentPoint(int X,int Y);
    void __fastcall DrawCurrentPoint(void);

    POINT SRectPos; // ��������� ����� �����
    POINT CRectPos; // ����������� ����� �����
    void __fastcall DrawFocusRect(void);
    void __fastcall ScaleByRect(void);

    TPlanKind FPlanKind;
    TPlanDirect FPlanDirect;
    bool FGridVisible; //true ���� ������������ ������������
    bool FMoving;      //true ���� ����������� ������������
    bool FMinMov;      //true ���� ������������ ������� ������������
    bool FMinCanMove;  //true ���� ����� ���������� ������� ������������
    bool FMaxCanMove;  //true ���� ����� ���������� ������� ������������
    bool FEditMetric;  //true ���� �������������� �������
    bool FShowProfil;  //true ���� ������� ������ ����� ��� ����������� �������
    TPolyline *FPoly;  //��������� ��� ��������������
    TExtPolyline *FVector;   //������ �� ����� � ����������� ������
    int FActivePoint;  //����� �������� �����
    int FMovePtDX;     // �������� �� ������� �� �������� �����
    int FMovePtDY;     //
    int FGridMinX,FGridMaxX;
    bool FPartVisible; // true, ���� ������� ������ ������������
    bool FPartPainted; // true, ���� ������� ����������
    int FPartMinL,FPartMaxL; // ���������� �������
    int SelCount;
    // ��������� ������� � �� ��������� ������
    TRoadObject *SelObjs[MAXSEL];
    TDtaSource *SelSrc[MAXSEL];
    int DrwIndexes[MAXSEL];
    TRoadObject *FActiveObj; // ��������� ������.
    TDtaSource *FActiveSource; // �������� ������ � ������� ����� �������� ������
    TRoadObject *FInsertingObj; // ����������� ������

    TSelectRect *SelectRect;//PBox->Canvas);
    TSelectObj *SelectObj;
    __int32 FViewId; //������������� ���� � ��� ���
    String FViewName;
    __int32 FCurPage; // ������������� ������� ��������

    String FRoadName;
    String FDistrictName;
    __int32 FRoadId;
    //������� ���� ������
    __int32 FMinL,FMaxL,FMinX,FMaxX;
    // ������� ����� ������
    __int32 FRoadMinL,FRoadMaxL;
    //������� ������ � ����
    __int32 FPMinL,FPMaxL,FPMinX,FPMaxX;
    //������� ������� ����� ������ � ����
    __int32 FVMinL,FVMaxL;
    //��������� �������
    __int32 FMarkerL;
    //
    __int32 FRelativeNull;

    __int32 FSclX;  // ����������� �������� �� ������
    __int32 FSclL;  // ����������� �������� �� �����
    __int32 FKmInPage; //���������� ���������� �� ����������� �����
    double FDpsm;   // �������� � ����������
    bool NeedRepDraw,NeedRepDress,NeedRepSlopes,NeedRepVis;
    TDrawManager *FDrawMan;
    __int32 __fastcall GetBaseScaleL(void)
        {return FDrawMan->BaseScaleL;}
    __int32 __fastcall GetBaseScaleX(void)
        {return FDrawMan->BaseScaleX;}
    __int32 __fastcall GetBaseScaleP(void)
        {return FDrawMan->BaseScaleP;}
    __int32 __fastcall GetPlanFontSize(void)
        {return FDrawMan->FontSize;}
    void __fastcall SetPlanFontSize(__int32 x)
        {FDrawMan->FontSize=x;}
// ������� ��� ������ ���������� � ������
    void __fastcall SaveRegistry(void);
    void __fastcall LoadRegistry(void);
    TDrawContents *FDrawCont;

    TDrawManager *FOutMan;  // �������� ������ ��� ����� ������

    TDrawContents *FSlopesCont;
    TDrawContents *FDressCont;
    TDrawContents *FVisCont;

//    TDtaSource *FDataSour;
// �������� ������ ��� �������� ��������������
    TDtaSource *FEditedData;
// �������� ������ � ������� �������� �������� ����������� ���������� (������ ������ � ��.)
    TDtaSource *FMetricData;
// �������� ������ � �����
    TDtaSource *FVideoData;
// �������� ������ � �������� (���������� � ����������)
    TDtaSource *FProfilData;
// �������� ������ � ������
    TDtaSource *FCurveData;
    TDictSource *FDictSour;
    TSharedObjSource *FShared;
    // ��������� ��� �������� ��������� �������
    bool FPan1Vis,FPan2Vis,FPan3Vis,FPan4Vis;
    void __fastcall AlignPanels(void);
    void __fastcall ShowPanels(void);
    void __fastcall ShowScale(void);
    void __fastcall DrawGrid(void);
    void __fastcall DrawMarkerPart(void);
    void __fastcall ClearMarkerPart(void);
    void __fastcall DrawMarker(TPaintBox *pb,int dl);
    void __fastcall ClearGrid(void);
    void __fastcall CalculateGridPos(bool CanMove);
// leep=true ���� ������ ������ ������������ � ������������ ��������
    void __fastcall UpdateActiveObject(bool leep);
    void __fastcall BuildPopMenu(void);
    void __fastcall ShowPopMenu(void);
    void __fastcall ShowMenu(TObject *Send);


    void __fastcall WndProc(TMessage&);
    bool HavePopup;
    void __fastcall EchoCursorPosition(int X,int Y);
    void __fastcall ShowStatus(void);
    void __fastcall PostAction(void);
    void __fastcall PostActivateObj(void);
    void __fastcall DrawPoly(void);
    int __fastcall  FindActivePoint(int X,int Y);
    void __fastcall PrepareDrawCont(void);
    void __fastcall PrepareSlopesCont(void);
    void __fastcall PrepareDressCont(void);
    void __fastcall PrepareVisCont(void);
// ������� ��� ���������� ��������� ���������� �� ��������
// ���� ��������� ���������� ��� ������������� ��������� �����������
    void __fastcall UpdateLocalInfo(void);
    void __fastcall DrawMainPlan(TDrawManager* Man,TDrawContents *Cont,double scll,double sclx,double dpsm,TRect *r);
    void __fastcall DrawFrames(TDrawManager* Man,TDrawContents *Cont,int dpi);
    void __fastcall Initialize(TDictSource *dict,TSharedObjSource *shared);
    void __fastcall SetRoadBounds(void);
public:         // User declarations
    void __fastcall RoadKeyPress(TWMKey &Key);
    void __fastcall PostChangeFocus(void);
    String __fastcall GetObjName(TRoadObject *obj);
    TRuler *HRuler;
    TRuler *VRuler;
    TVisSetFrm *VisSet;
    __fastcall TRoadFrm(TComponent* Owner);
    //��������� ������ � �������� ������ � ���������������
    void __fastcall OpenRoad(String Capt,TDtaSource*,TDictSource*,TSharedObjSource *);
    void __fastcall OpenView(__int32 RoadId,__int32 ViewId,TDictSource *dict,TSharedObjSource *shared);
    void __fastcall OpenRoad(__int32 RoadId,TDictSource *dict,TSharedObjSource *shared);
    void __fastcall FindSources(void);
    void __fastcall SaveData(void);
    void __fastcall ReLoadData(void);
    void __fastcall CloseRoad(void);
    void __fastcall ShowAll(void);
    void __fastcall ScaleL(double K);
    void __fastcall ScaleX(double K);
    void __fastcall ChangeOrientation(void);
    void __fastcall ChangeDirection(void);
// true ���� ��������� ��������������� ����� �����������
    TExtPolyline* __fastcall BuildPoly(bool re);    
    void __fastcall PutPLMin(__int32 Pos,__int32 Max);
    void __fastcall PutPXMin(__int32 Pos,__int32 Max);
    void __fastcall SetViewPosition(__int32 minl,__int32 maxl);
    void __fastcall SetMarkerPos(__int32 newl);
    void __fastcall SetBaseScale(__int32 l,__int32 x,__int32 p);
    void __fastcall SetXBounds(__int32 boundx,__int32 objx);
    void __fastcall ShowParam(void);
    void __fastcall DeleteActiveObject(bool NeedRemove);
    void __fastcall ShowRoadPart(__int32 min,__int32 max);
    void __fastcall SetObjectActive(TRoadObject *Obj,TDtaSource *Src);    
    void __fastcall ActivateObject(TRoadObject*,TDtaSource *Src);
    void __fastcall AddNewSign(String,int);
    void __fastcall AddNewSign(void);
    void __fastcall ChangeActiveSignCode(void);
    void __fastcall EditActiveMarkParams(void);// ����������� ����� ������ ��������, ��������� �������
    void __fastcall ContinueMarkLine(void);   // ������� ����� ������ ��������, ��������� �������
    void __fastcall NewMarkLine(void);        // ������� ����� ������ ��������. ���� �������� ��������, �� �� ����� �����������
    void __fastcall MoveActiveObject(void);
    void __fastcall AddNewObject(void);
    void __fastcall AddNewObject(int DictId);
    void __fastcall AddNewObject(TObjMetaClass *Meta);
    void __fastcall ShowActiveObject(void);
    void __fastcall LongSlopesPartDialog(void);
    void __fastcall BuildWidePartsDialog(void);    
    void __fastcall BuildRoadLines(void);
    void __fastcall CalculateRoadMarkLength(void);
    // ������ ����� � ������ ����������� ������ ������ � ����������� � �������� ������� ��� ���������
    void __fastcall BreakRoadLines(void);
    // ������ ������� �� ������ � �������� ����� � ������
    void __fastcall WidthMeasureDialog(void);        
    // ���� ��������� ������ ���� �� ����, ��� � �������
    void __fastcall NextObject(void);
    // ���� ���������� ������ ���� �� ����, ��� � �������
    void __fastcall PredObject(void);

    void __fastcall StartEditPoly(void);
    void __fastcall StopEditPoly(void);
    void __fastcall DeleteActivePoint(void);
    void __fastcall InsertPoint(void);
    void __fastcall InsertPoint(TRoadPoint P,int index);
    void __fastcall SetPoint(TRoadPoint P,int index);
    void __fastcall SetActivePointCode(int Kind,int Code);
    void __fastcall RefreshPlan(void);

    void __fastcall ShowProfil(void);
    void __fastcall ShowDress(void);
    void __fastcall ShowVisPlan(void);
    void __fastcall ShowMapPlan(void);    

// ���������� ���� �� �����
    void __fastcall SynchronizeVideo(void);
    void __fastcall ShowVideo(int Direction,int id);
    void __fastcall HideVideo(void);
    void __fastcall SetVideoPos(__int32 Pos);
    void __fastcall SetAllSigns(void);
    void __fastcall SetDirector(void);
    void __fastcall QuickDesign(void);
    void __fastcall SetKmSigns(void);
    void __fastcall DesignAttach(void);
    bool __fastcall IsInTown(int L);
    void __fastcall DesignAttachMark(void);    
    void __fastcall BuildKmSet(__int32 Km);
    void __fastcall KmSetText(void);
    void __fastcall MetaExportDialog(void);
    void __fastcall MetaExport(String FName,int minl,int maxl,int plen,int scll,int sclx,int dpi,int page);
    void __fastcall BmpExportDialog(void);
    void __fastcall BmpExport(String FName,int minl,int maxl,int plen,int scll,int sclx,int dpi,int page);
    void __fastcall AcadExport(void);
    void __fastcall AcadPrint(void);
    void __fastcall PreparePattern(int minkm,int maxkm,int page);
    void __fastcall MakeBmpPage(TDrawContents* Cont,int minl,int maxl,int scll,int sclx, int dpi,int page);
    void __fastcall MakePreViewPage(TDrawContents *Cont,int minl,int maxl,int scll,int sclx,int ms,int page);
    void __fastcall Print(int minl,int maxl,int plen,int scll,int sclx,int page);
    bool inline AbortAutoCADExport();
    void __fastcall PrintDialog(void);
    // �������������� �����
    void __fastcall InvalidateBoxes(void);
    __property TDtaSource* VideoData={read=FVideoData};
    __property TDtaSource* EditedData={read=FEditedData};
    __property TDtaSource* ProfilData={read=FProfilData};    
    __property TDtaSource* MetricData={read=FMetricData};    
    __property TDtaSource* CurveData={read=FCurveData};
    __property TDictSource* Dict={read=FDictSour};
    __property TSharedObjSource *Shared={read=FShared};
    __property __int32 CurPage={read=FCurPage};
    __property __int32 RoadMinL={read=FRoadMinL};
    __property __int32 RoadMaxL={read=FRoadMaxL};
    __property __int32 MinL={read=FMinL};
    __property __int32 MaxL={read=FMaxL};
    __property __int32 MinX={read=FMinX};
    __property __int32 MaxX={read=FMaxX};
    __property __int32 PMinL={read=FPMinL};
    __property __int32 PMaxL={read=FPMaxL};
    __property __int32 PMinX={read=FPMinX};
    __property __int32 PMaxX={read=FPMaxX};
    __property __int32 BaseScaleL={read=GetBaseScaleL};
    __property __int32 BaseScaleX={read=GetBaseScaleX};
    __property __int32 BaseScaleP={read=GetBaseScaleP};
    __property __int32 PlanFontSize={read=GetPlanFontSize,write=SetPlanFontSize};
    __property TPlanKind PlanKind={read=FPlanKind};
    __property TPlanDirect PlanDirect={read=FPlanDirect};
    __property __int32 MarkerL={read=FMarkerL};
    __property String RoadName={read=FRoadName};
    __property int ActivePoint={read=FActivePoint,write=FActivePoint};
    __property int RoadId={read=FRoadId};
    __property TRoadObject *ActiveObj={read=FActiveObj};
    __property TRoadObject *InsertingObj={read=FInsertingObj};
};
//---------------------------------------------------------------------------
extern PACKAGE TRoadFrm *RoadFrm;
//---------------------------------------------------------------------------
#endif
