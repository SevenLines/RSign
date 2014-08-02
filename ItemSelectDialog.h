//---------------------------------------------------------------------------

#ifndef ItemSelectDialogH
#define ItemSelectDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <map>

using namespace std;
//---------------------------------------------------------------------------
class TItemSelectDialogForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TPanel *Panel2;
    TComboBox *cmbOptions;
    TLabel *lblMessage;
private:	// User declarations
    map<AnsiString, AnsiString> params;
public:		// User declarations
    __fastcall TItemSelectDialogForm(TComponent* Owner);
    void setOptions(map<AnsiString, AnsiString> &items, AnsiString message="");
    AnsiString selectedItem();
};
//---------------------------------------------------------------------------
extern PACKAGE TItemSelectDialogForm *ItemSelectDialogForm;
//---------------------------------------------------------------------------
#endif
