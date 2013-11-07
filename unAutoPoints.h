//---------------------------------------------------------------------------

#ifndef unAutoPointsH
#define unAutoPointsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TFAutoPoints : public TForm
{
__published:	// IDE-managed Components
   TCSpinEdit *edtFreq;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   
   void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall FormShow(TObject *Sender);
private:	// User declarations
   void ReadIni(TIniFile *ini);
   void WriteIni(TIniFile *ini);
   int getAutoPointsFreq();
public:		// User declarations
   __fastcall TFAutoPoints(TComponent* Owner);
   __property int AutoPointsFreq = {read = getAutoPointsFreq};
};
//---------------------------------------------------------------------------
extern PACKAGE TFAutoPoints *FAutoPoints;
//---------------------------------------------------------------------------
#endif
