//---------------------------------------------------------------------------

#ifndef AttachFormH
#define AttachFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmAttachParams : public TForm
{
__published:	// IDE-managed Components
   TEdit *edAngle;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TEdit *edLength;
   TLabel *Label4;
   TEdit *edBegWidth;
   TEdit *edEndWidth;
   TButton *Button1;
   TButton *Button2;
private:	// User declarations
public:		// User declarations
   __fastcall TfrmAttachParams(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAttachParams *frmAttachParams;
//---------------------------------------------------------------------------
#endif
