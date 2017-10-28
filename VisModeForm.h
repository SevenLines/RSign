//---------------------------------------------------------------------------

#ifndef VisModeFormH
#define VisModeFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmVisMode : public TForm
{
__published:	// IDE-managed Components
    TEdit *edPartLen;
    TLabel *Label1;
    TUpDown *updPartLen;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *edStartPos;
    TEdit *edEndPos;
    TLabel *Label4;
    TEdit *edDraiverHeight;
    TUpDown *updDriverHeight;
    TLabel *Label5;
    TEdit *edMarkerHeight;
    TUpDown *updMarkerHeight;
    TButton *Button1;
    TButton *Button2;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmVisMode(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmVisMode *frmVisMode;
//---------------------------------------------------------------------------
#endif
