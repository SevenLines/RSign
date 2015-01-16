//---------------------------------------------------------------------------

#ifndef VideoBarH
#define VideoBarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmVideoBar : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
virtual void __fastcall CreateParams(TCreateParams &Params);
public:		// User declarations
    __fastcall TfrmVideoBar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmVideoBar *frmVideoBar;
//---------------------------------------------------------------------------
#endif
