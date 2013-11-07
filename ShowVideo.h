//---------------------------------------------------------------------------

#ifndef ShowVideoH
#define ShowVideoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
struct Geom_Controls
{
    AnsiString ssName;
    AnsiString ssField;
    AnsiString ssCaption;
    bool ssVisible;
};
struct DSGeoms
{
    TADODataSet* ssDS;
    int ssCountOfChild;
    Geom_Controls* ArrOfGeom;
    bool ssActive;
    AnsiString ssName;
};

class TfrmShowVideo : public TForm
{
__published:	// IDE-managed Components
    TMediaPlayer *MPlayer;
    TPanel *Panel1;
    TBitBtn *cmdPlay;
    TBitBtn *cmdPause;
    TBitBtn *cmdStop;
    TScrollBar *ScrollBar1;
    TADODataSet *DSRepers;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *txtSpeed;
    TEdit *txtDistRoad;
    TEdit *txtHighDist;
    TTimer *Timer1;
    TADODataSet *DSDistTime;
    TADODataSet *DSTemp;
    TPopupMenu *PopupMenu1;
    TMenuItem *N1;
    TADODataSet *DSGeomParams;
    TADODataSet *DSGeomConers;
    TMenuItem *mnuEditGeomParams;
    void __fastcall cmdPlayClick(TObject *Sender);
    void __fastcall cmdPauseClick(TObject *Sender);
    void __fastcall cmdStopClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall txtDistRoadChange(TObject *Sender);
    void __fastcall ScrollBar1Change(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall Panel1Resize(TObject *Sender);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall mnuEditGeomParamsClick(TObject *Sender);
    void __fastcall DSGeomConersAfterScroll(TDataSet *DataSet);
private:	// User declarations
    double Koff;//коэффицент, на который нужно умножить расстояние от начала заезда
    int ID_High;
    double FirstReperPosOfInv;//первый репер
    double FirstReperPosOfSVPD;
    double LastReperPosOfInv;
    double LastReperPosOfSVPD;
    double RoadStartPos;//начало дороги из нашей базы
    double RoadEndPos;//конец дороги из нашей базы
    bool txtDistRoadChanged;//показывает менял ли юзер позицию от начала дороги
    AnsiString GetPathToVideo();
    bool SetVideoPosition();
    void __fastcall OptionsGeoControls(TObject *Sender);
    void __fastcall CreateGeoControl(AnsiString ControlName, AnsiString ControlCaption, int ControlX, int ControlY);
    void __fastcall DeleteGeoControl(AnsiString ControlName);
    void __fastcall SetFormSize(int frmHeight, int frmWidth);
public:		// User declarations
    bool InitVideo();
    int ID_Road;
    int Direction; //1 - прямое, 2 - обратное
    int DataSource;
    double StartPos;
    double EndPos;
    __fastcall TfrmShowVideo(TComponent* Owner);
    Geom_Controls* GeomControls;
    int ssSizeOf;
    int ssSizeOfDasData;
    int ssSizeOfConers;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmShowVideo *frmShowVideo;
//---------------------------------------------------------------------------
#endif
