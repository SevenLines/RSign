//---------------------------------------------------------------------------

#ifndef SetSignsH
#define SetSignsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ShowRoad.h"
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSetSigns : public TForm
{
__published:	// IDE-managed Components
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox1;
    TCheckListBox *RoadObjectsList;
    TLabel *Label1;
    TLabel *lblCurrentRoadTitle;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *lblCurrentRoadObjectTitle;
    TLabel *lblCurrentRoadObjectPlace;
    TPanel *Panel2;
    TButton *btnGoToBegin;
    TButton *btnGoToPrev;
    TButton *btnGoToNext;
    TButton *btnGoToEnd;
    TPanel *Panel1;
    TButton *btnClose;
    TGroupBox *GroupBox3;
    TCheckBox *AutoCheck;
    TButton *btnSetSigns;
    TButton *btnCheckSigns;
    TPageControl *PageControl1;
    TGroupBox *GroupBox4;
    TCheckListBox *CurrentObjectSignsList;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnGoToNextClick(TObject *Sender);
    void __fastcall btnGoToEndClick(TObject *Sender);
    void __fastcall btnGoToBeginClick(TObject *Sender);
    void __fastcall btnGoToPrevClick(TObject *Sender);
    void __fastcall btnCheckSignsClick(TObject *Sender);
    void __fastcall btnSetSignsClick(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
private:	// User declarations
    __int32 CurrentRoadObject;
    TRoadFrm *CurrentActiveRoad;
    AnsiString CurrentRoadTitle;

    // Вспомогательные функции
    bool __fastcall CheckCurrentActiveRoad();
    void __fastcall SetCurrentActiveRoad(TRoadFrm *NewActiveRoad);
    void __fastcall ShowCurrentRoadObjectInfo(AnsiString Title, AnsiString Place);
    void __fastcall ClearCurrentObjectSignsList();
    // Функции проверки расстановки знаков
    void __fastcall CheckBridgeSigns(TRoadBridge* Bridge);
    void __fastcall CheckAttachSigns(TRoadAttach* Attach);
    void __fastcall CheckTownSigns(TTown* Town);
    void __fastcall CheckBusStopSigns(TBusStop* BusStop);
    void __fastcall CheckRailCrossSigns(TRailCross* RailCross);

    // Вспомогательные функции проверки расстановки знаков
    TRoadSign* __fastcall FindNearestSignForward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius);
    TRoadSign* __fastcall FindNearestSignBackward(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius);
    TRoadSign* __fastcall FindNearestSign(__int32 ObjectIndex, AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 Radius);
    TRoadSign* __fastcall FindSign(AnsiString SignName, TRoadDirection SignDirection, TRoadSignPlacement SignPlacement, __int32 L1, __int32 L2);
public:		// User declarations
    __fastcall TfrmSetSigns(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetSigns *frmSetSigns;
//---------------------------------------------------------------------------
#endif
