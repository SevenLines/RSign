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
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#define VIDEOEDITCOUNT 10
#define ROWBUT 2
#define COLBUT 5

class TfrmVideoForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TTimer *Timer;
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
    TImageList *ImgDirection;
    TPanel *Panel4;
    TSMediaPlayer *MPlayer;
    TScrollBar *ScrollBar;
    TPanel *Panel3;
    TSpeedButton *cmdPlay;
    TSpeedButton *cmdPause;
    TSpeedButton *cmdStop;
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
    void __fastcall FormResize(TObject *Sender);
    void __fastcall MPlayerMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Panel4MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Panel4MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall MPlayerMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
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
    TSpeedButton* DirBut[ROWBUT][COLBUT],*UnDirBut[ROWBUT][COLBUT];
    void __fastcall CreateEdits(void);
    void __fastcall AlignEdits(void);
    void __fastcall AlignButtons(void);
    void __fastcall SetMenu(void);
    int __fastcall CalcFormHeight(int wd);
    int __fastcall CalcBarTop(int wd);
    String __fastcall FindFile(String S);
    void __fastcall butVideoClick(TObject *Sender);    
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

    void (__closure *OnFormGeometryChange)(TRect);
    void RecalculatePosition(TWMMove message);

BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_MOVE, TWMMove, RecalculatePosition)
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmVideoForm *frmVideoForm;
//---------------------------------------------------------------------------
#endif

