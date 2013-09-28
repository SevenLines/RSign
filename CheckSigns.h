//---------------------------------------------------------------------------

#ifndef CheckSignsH
#define CheckSignsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "ShowRoad.h"
//---------------------------------------------------------------------------
class TfrmCheckSigns : public TForm
{
__published:	// IDE-managed Components
    TButton *btnClose;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TLabel *Label1;
    TLabel *lblCurrentRoadTitle;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *lblCurrentSignTitle;
    TLabel *lblCurrentSignPlace;
    TGroupBox *GroupBox2;
    TLabel *lblCurrentSignDescription;
    TPanel *Panel2;
    TButton *btnGoToBegin;
    TButton *btnGoToPrev;
    TButton *btnGoToNext;
    TButton *btnGoToEnd;
    TPanel *Panel1;
    TButton *btnCheckSign;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox1;
    TCheckListBox *SignsList;
    TGroupBox *GroupBox3;
    TCheckBox *AutoCheck;
    TCheckBox *CheckOnlyKnownSigns;
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnGoToNextClick(TObject *Sender);
    void __fastcall btnGoToPrevClick(TObject *Sender);
    void __fastcall btnGoToEndClick(TObject *Sender);
    void __fastcall btnGoToBeginClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    TRoadFrm *CurrentActiveRoad;
    AnsiString CurrentRoadTitle;
    __int32 CurrentSign;
    TStringList *KnownSignsList;
    
    bool __fastcall CheckCurrentActiveRoad();
    void __fastcall SetCurrentActiveRoad(TRoadFrm *NewActiveRoad);
    void __fastcall ShowCurrentSignInfo(AnsiString Title, AnsiString Place);
    void __fastcall ShowCurrentSignDescription(AnsiString Description);
    //
    bool __fastcall IsKnownSign(TRoadSign *Sign);
    // функции проверки знаков
    //void __fastcall CheckSign231(__int32 SignIndex); 
public:		// User declarations
    __fastcall TfrmCheckSigns(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCheckSigns *frmCheckSigns;
//---------------------------------------------------------------------------
#endif
