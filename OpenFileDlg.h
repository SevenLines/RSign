//---------------------------------------------------------------------------

#ifndef OpenFileDlgH
#define OpenFileDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TOpenRoadDialog : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
private:	// User declarations
public:		// User declarations
int RoadId;
String RoadName;
        __fastcall TOpenRoadDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpenRoadDialog *OpenRoadDialog;
//---------------------------------------------------------------------------
#endif
