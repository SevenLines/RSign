//---------------------------------------------------------------------------

#ifndef AutoCADPrintFormH
#define AutoCADPrintFormH
//---------------------------------------------------------------------------

#include "without_autocad.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#ifndef WITHOUT_AUTOCAD

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "AutoCADHelper.h"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
#include <list>

enum AutoCADPrintOutputStyle{posFile = 0, posDevice};

template <class T> void ClearList(TList *list)
{
  for (int i=0;i<list->Count;i++){
     delete (T*)list->Items[i];
  }
  list->Clear();
}


//---------------------------------------------------------------------------
class TFAutoCADPrint : public TForm
{
__published:	// IDE-managed Components
        TButton *cmdPrint;
        TLabel *Label1;
        TEdit *edtTopCenter;
        TEdit *edtMiddleCenter;
        TEdit *edtBottomCenter;
        TLabel *Label2;
        TSaveDialog *SaveDialog1;
        TEdit *edtStep;
        TLabel *Label3;
        TEdit *edtStart;
        TLabel *Label4;
        TEdit *edtEnd;
        TLabel *Label5;
        TButton *Button3;
        TEdit *edtPos;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TTrackBar *tbPos;
        TEdit *edtPos2;
        TCheckBox *chkOnly;
        TImage *Image1;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *Panel1;
        TGroupBox *GroupBox2;
        TPanel *pnlBottom;
        TPanel *pnlTop;
        TCheckBox *chkInfo;
        TEdit *edtPattern;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *edtPage;
        TLabel *Label13;
        TLabel *Label14;
        TOpenDialog *OpenDialog1;
        TPanel *Panel2;
        TButton *Button2;
        TLabel *lblActiveName;
        TButton *Button12;
        TPanel *Panel3;
        TEdit *edtPDFBinder;
        TLabel *Label16;
        TOpenDialog *OpenDialog2;
        TButton *Button8;
    TButton *Button9;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall cmdPrintClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall tbPosChange(TObject *Sender);
        void __fastcall edtEndKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall edtStepEnter(TObject *Sender);
        void __fastcall edtPosKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall edtPosChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
private:
        AutoCADHelper AutoCAD;
        bool ffirst1;
        AcadTextPtr text;
        AcadTextPtr roadName;
        AcadTextPtr page;

        AnsiString strRoadName;
        AnsiString strIniFileName;

        void SaveIni(TIniFile *ini);
        void LoadIni(TIniFile *ini);
        void CheckViewports();
        void DrawViewports();
        bool BindViewports();
        void ReadValues();
        float kHeight,kWidth;
        float _Height,_Width;
        float xOffset,yOffset;
        float _Left,_Right,_Top,_Bottom;
        int iOffset;
        TList *Rects;
        int curState,iPage;
        void __fastcall OnDocClose(TObject *Sender);
public:		// User declarations
       AcadPViewportPtr vpTop;
       AcadPViewportPtr vpCenter;
       AcadPViewportPtr vpBottom;
       int iTop,iCenter,iBottom,iSelected;

       enum PrintType {ptDWG, ptPDF};

       void Print(PrintType printType = ptPDF);
       
       bool BeginPrint();
       bool PauseLastFramePrint(std::list<AnsiString> &fileNames);
       bool SetFrame(int position, int width);
       bool EndPrint();

       AutoCADHelper *helper;
       float vcTop,vcCenter,vcBottom, vStep, sPos, ePos;
       AcadDocumentPtr lastDoc;
       AnsiString FileName;
       AutoCADPrintOutputStyle OutputStyle;
        __fastcall TFAutoCADPrint(TComponent* Owner);
        __fastcall ~TFAutoCADPrint();
};
//---------------------------------------------------------------------------
extern PACKAGE TFAutoCADPrint *FAutoCADPrint;
//---------------------------------------------------------------------------

#endif // WITHOUT_AUTOCAD

#endif
