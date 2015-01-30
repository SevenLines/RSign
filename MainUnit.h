//---------------------------------------------------------------------------
//  Внимание!!! для успешеой работы необходимо установить настройку компилятора
//  treate enums as int   AddTerminateProc
//---------------------------------------------------------------------------
#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "ShowRoad.h"
#include "VPattern.h"
#include "SignPanel.h"
#include <Menus.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <map>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
  TADOConnection *Connection;
  TMenuItem *N13;
  TMenuItem *N14;
  TMenuItem *N15;
  TMenuItem *N16;
  TMenuItem *N17;
  TMenuItem *N18;
  TMenuItem *N19;
  TMenuItem *N20;
  TOpenDialog *OpenDump;
    TMenuItem *N21;
    TMenuItem *N22;
    TMenuItem *N23;
    TMenuItem *N24;
    TMenuItem *N29;
    TMenuItem *N30;
    TMenuItem *N31;
    TMenuItem *N32;
    TMenuItem *N33;
    TMenuItem *N34;
    TMenuItem *N35;
    TMenuItem *N36;
    TMenuItem *N37;
    TMenuItem *N38;
    TMenuItem *N39;
    TMenuItem *N40;
    TMenuItem *N41;
    TMenuItem *N42;
    TMenuItem *N43;
    TMenuItem *N25;
    TMenuItem *N26;
    TMenuItem *N27;
    TSpeedButton *BtnPropMode;
    TSpeedButton *BtnSelectMode;
    TMenuItem *N28;
    TMenuItem *N44;
    TSpeedButton *NextObjBut;
    TSpeedButton *PrevObjBut;
    TSpeedButton *AutoDesignBut;
    TMenuItem *N45;
    TMenuItem *N46;
    TSpeedButton *AddDangBut;
    TSpeedButton *AddSignBut;
    TMenuItem *N47;
    TMenuItem *N11;
    TMenuItem *N12;
    TSpeedButton *AttDesignBut;
    TSpeedButton *ShowDocBut;
    TMenuItem *N48;
    TMenuItem *N49;
    TMenuItem *N50;
    TMenuItem *N51;
    TMenuItem *N52;
    TMenuItem *N53;
    TMenuItem *N54;
    TMenuItem *N56;
  TMenuItem *N55;
  TMenuItem *N57;
  TMenuItem *N58;
  TMenuItem *N59;
    TMenuItem *N60;
    TMenuItem *MenuItemConnect;
    TMenuItem *N62;
    TPopupMenu *DesignersList;
    TMenuItem *N63;
    TMenuItem *N64;
    TMenuItem *N65;
    TMenuItem *N66;
    TMenuItem *N67;
    TMenuItem *N68;
    TOpenDialog *OpenVideo;
    TMenuItem *N69;
   TMenuItem *N70;
   TMenuItem *N71;
        TMenuItem *N72;
   TMenuItem *N73;
   TMenuItem *N74;
   TMenuItem *N75;
   TSpeedButton *RMDesignBut;
   TMenuItem *N76;
   TMenuItem *N77;
   TMenuItem *N78;
   TMenuItem *N79;
    TMenuItem *N80;
        TMenuItem *N81;
    TMenuItem *ItemMiniReports;
    TMenuItem *N82;
    TMenuItem *N83;
    TMenuItem *N84;
    TMenuItem *N85;
    TMenuItem *ItemDocxReport;
    TMenuItem *N61;
  void __fastcall OpenRoad(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall N14Click(TObject *Sender);
  void __fastcall N17Click(TObject *Sender);
  void __fastcall N19Click(TObject *Sender);
  void __fastcall N20Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
  void __fastcall N3Click(TObject *Sender);
    void __fastcall N21Click(TObject *Sender);
    void __fastcall N22Click(TObject *Sender);
    void __fastcall N24Click(TObject *Sender);
    void __fastcall N31Click(TObject *Sender);
    void __fastcall N32Click(TObject *Sender);
    void __fastcall N41Click(TObject *Sender);
    void __fastcall N39Click(TObject *Sender);
    void __fastcall N33Click(TObject *Sender);
    void __fastcall N34Click(TObject *Sender);
    void __fastcall N35Click(TObject *Sender);
    void __fastcall N38Click(TObject *Sender);
    void __fastcall N37Click(TObject *Sender);
    void __fastcall N42Click(TObject *Sender);
    void __fastcall N43Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N6Click(TObject *Sender);
    void __fastcall N27Click(TObject *Sender);
    void __fastcall N25Click(TObject *Sender);
    void __fastcall N26Click(TObject *Sender);
    void __fastcall N28Click(TObject *Sender);
    void __fastcall PrevObjButClick(TObject *Sender);
    void __fastcall NextObjButClick(TObject *Sender);
    void __fastcall AutoDesignButClick(TObject *Sender);
    void __fastcall N46Click(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall N45Click(TObject *Sender);
    void __fastcall AddSignButClick(TObject *Sender);
    void __fastcall AddDangButClick(TObject *Sender);
    void __fastcall N18Click(TObject *Sender);
    void __fastcall N47Click(TObject *Sender);
    void __fastcall N12Click(TObject *Sender);
    void __fastcall AttDesignButClick(TObject *Sender);
    void __fastcall N48Click(TObject *Sender);
    void __fastcall N49Click(TObject *Sender);
    void __fastcall N50Click(TObject *Sender);
    void __fastcall N51Click(TObject *Sender);
    void __fastcall N52Click(TObject *Sender);
    void __fastcall N54Click(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall N59Click(TObject *Sender);
  void __fastcall N58Click(TObject *Sender);
  void __fastcall N57Click(TObject *Sender);
    void __fastcall MenuItemConnectClick(TObject *Sender);
    void __fastcall N63Click(TObject *Sender);
    void __fastcall N64Click(TObject *Sender);
    void __fastcall N66Click(TObject *Sender);
    void __fastcall N67Click(TObject *Sender);
    void __fastcall N68Click(TObject *Sender);
    void __fastcall N69Click(TObject *Sender);
   void __fastcall N70Click(TObject *Sender);
   void __fastcall N71Click(TObject *Sender);
        void __fastcall N72Click(TObject *Sender);
   void __fastcall N73Click(TObject *Sender);
   void __fastcall N74Click(TObject *Sender);
   void __fastcall N75Click(TObject *Sender);
   void __fastcall RMDesignButClick(TObject *Sender);
   void __fastcall N76Click(TObject *Sender);
    void __fastcall N80Click(TObject *Sender);
        void __fastcall N81Click(TObject *Sender);
    void __fastcall ItemMiniReportsClick(TObject *Sender);
    void __fastcall N83Click(TObject *Sender);
    void __fastcall N85Click(TObject *Sender);
    void __fastcall ItemDocxReportClick(TObject *Sender);


private:	// User declarations
    void __fastcall AppShortCut(TWMKey &Key, bool &Handled);
    TRoadFrm *FActiveRoad;
    int FCurAttachDesigner;
    bool HaveInit;

    unsigned long gdiplusToken;

    TRect lastRoadWindowPosition;
    TRect lastVideoWindowPosition;
    bool blockShowRoadSizeEventProcessor;

    void ShowRoadFormGeometryChange(TRect windowRect);
    void VideoFormGeometryChange(TRect windowRect);

    virtual void __fastcall WndProc(TMessage&);

    TRoadFrm* __fastcall FindRoad(__int32 id,__int32 dataclass);

    void __fastcall SetActiveRoad(TRoadFrm *);

    int __fastcall AddProject(__int32 RoadId);

    bool __fastcall GetPropertyByClick(void)
        {return BtnPropMode->Down;}

    bool __fastcall GetSelectByClick(void)
        {return BtnSelectMode->Down;}

    void __fastcall SetDesigner(TObject *Send);
           
public:		// User declarations
    TSignPanel *SignPanel;
    TResManager *ResManager;
    TSharedObjSource *Shared;
    TRoadObjFactory *Factory;
    TDrawPattern *Pattern;
    TStringList *VideoServers;
    TStringList *CheefList;
    __fastcall TMainForm(TComponent* Owner);
    __fastcall ~TMainForm(void);
    __property TRoadFrm *ActiveRoad={read=FActiveRoad,write=SetActiveRoad};
    void __fastcall ListObjectClick(TObject *Sender);    
    void __fastcall SetVideoPos(__int32 pos);
    bool __fastcall OpenRoadById(__int32 id,__int32 dataclass,bool OpenCopy);
    bool __fastcall CloseRoad(__int32 id,__int32 dataclass);
    bool __fastcall ActivateRoad(__int32 id,__int32 dataclass);
    bool __fastcall IsRoadOpen(__int32 id,__int32 dataclass);
    bool __fastcall ShowRoadObject(__int32 RoadId,__int32 dataclass,__int32 ObjId);
    bool __fastcall ShowRoadPart(__int32 RoadId,__int32 dataclass,__int32 StartPos,__int32 EndPos);
    void __fastcall ReadIni(TIniFile*);
    void __fastcall WriteIni(TIniFile*);
    void __fastcall LoadIni(void);
    void __fastcall SaveIni(void);
    void __fastcall SendBroadCastMessage(int Command,int Wpar,int Lpar);
    void __fastcall PostBroadCastMessage(int Command,int Wpar,int Lpar);
    bool GetActiveRoadParamsForMiniReport(std::map<AnsiString, AnsiString> &params);

    void __fastcall PrepareShowRoadSize(TRoadFrm* frm);

    void __fastcall PrepareMinireports();
    int __fastcall SetupConnection();

    __property bool PropertyByClick={read=GetPropertyByClick};
    __property bool SelectByClick={read=GetSelectByClick};
    __property int CurAttachDesigner={read=FCurAttachDesigner};
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
