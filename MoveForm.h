//---------------------------------------------------------------------------

#ifndef MoveFormH
#define MoveFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <SysUtils.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TmoveDialog : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TEdit *edLength;
   TRadioGroup *rgKind;
   TCheckBox *cbVideo;
   TCheckBox *cbGeometry;
   TButton *Button1;
   TButton *Button2;
private:	// User declarations
   bool GetmoveVideo(void) {return cbVideo->Checked;}
   bool GetmoveGeometry(void) {return cbGeometry->Checked;}
   bool GetmoveAllObjects(void) {return rgKind->ItemIndex==2;}
   bool GetmoveSelected(void) {return rgKind->ItemIndex==1;}
   int GetLength(void) {return StrToInt(edLength->Text.c_str());}
public:		// User declarations
   __fastcall TmoveDialog(TComponent* Owner);
   __property int Length={read=GetLength};
   __property bool moveVideo={read=GetmoveVideo};
   __property bool moveGeometry={read=GetmoveGeometry};
   __property bool moveAllObjects={read=GetmoveAllObjects};
   __property bool moveSelected={read=GetmoveSelected};
};
//---------------------------------------------------------------------------
extern PACKAGE TmoveDialog *moveDialog;
//---------------------------------------------------------------------------
#endif
