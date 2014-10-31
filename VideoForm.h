//---------------------------------------------------------------------------

#ifndef VideoFormH
#define VideoFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include "DataSour.h"
#include <Buttons.hpp>
#include "ActiveX\\MediaPlayer_OCX.h"
#include <OleCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#define VIDEOEDITCOUNT 10

class TfrmVideoForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TTimer *Timer;
    TSMediaPlayer *MPlayer;
    TPanel *Panel2;
    TScrollBar *ScrollBar;
    TPanel *Panel3;
    TSpeedButton *cmdPlay;
    TSpeedButton *cmdPause;
    TSpeedButton *cmdStop;
    TPopupMenu *PopMenu;
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
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall MPlayerPlayStateChange(TObject *Sender, long OldState,
          long NewState);
    void __fastcall FormCanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall cmdPlayClick(TObject *Sender);
    void __fastcall cmdStopClick(TObject *Sender);
    void __fastcall cmdPauseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall PosEditExit(TObject *Sender);
    void __fastcall PosEditKeyPress(TObject *Sender, char &Key);
    void __fastcall ScrollBarChange(TObject *Sender);
private:	// User declarations
    TDtaSource *FData;

    int StartMode,CStartMode,CPlayPos;  // Дебильный способ справиться с ошибкой в MediaPlayere
    int FNumRoad;
    int FPosIndex;
    int FPosition;
    int FStatus;
    int FDirection;
    int FCurHighIndex;
    void __fastcall SetPosition(int);
    void __fastcall SetInterval(int);
    int __fastcall GetInterval(void);
    void __fastcall WndProc(TMessage &Mes);
    void __fastcall SetGeometry(void);

    void __fastcall PostChangeStatus(void);
    void __fastcall SetVideoPosition(unsigned long pos);
    int __fastcall  GetVideoPosition(void);
    void __fastcall CalculateTimeVal(void);
    void __fastcall SetHighAndPosition(TVideoTimeVal &VT);

    bool VParams[VIDEOEDITCOUNT];
    TEdit* FEdits[VIDEOEDITCOUNT];
    TLabel * FLabels[VIDEOEDITCOUNT];
    void __fastcall CreateEdits(void);
    void __fastcall AlignEdits(void);
    void __fastcall SetMenu(void);
    int __fastcall CalcFormHeight(int wd);
    String __fastcall FindFile(String S);
public:		// User declarations
    __fastcall TfrmVideoForm(TComponent* Owner);
    void __fastcall InitVideo(TDtaSource *data,int Dir);
    void __fastcall CloseVideo(void);
    void __fastcall PlayVideo(void);
    void __fastcall StopVideo(void);
    void __fastcall PauseVideo(void);
    __property int Status={read=FStatus};
    __property int Position={read=FPosition,write=SetPosition};
    __property int Interval={read=GetInterval,write=SetInterval};
    __property int Direction={read=FDirection};
    __property int NumRoad={read=FNumRoad};
    __property TDtaSource* Data={read=FData};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmVideoForm *frmVideoForm;
//---------------------------------------------------------------------------
#endif
