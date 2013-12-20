//---------------------------------------------------------------------------

#ifndef AddRowsDescriptionH
#define AddRowsDescriptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFAddRowDescription : public TForm
{
__published:	// IDE-managed Components
    TRichEdit *RichEdit1;
    TButton *Button1;
private:	// User declarations
public:		// User declarations
    __fastcall TFAddRowDescription(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAddRowDescription *FAddRowDescription;
//---------------------------------------------------------------------------
#endif
