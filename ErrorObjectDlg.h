//---------------------------------------------------------------------------

#ifndef ErrorObjectDlgH
#define ErrorObjectDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RoadObj.h"
#include "DataSour.h"
//---------------------------------------------------------------------------
class TErrorObjectDialog : public TForm
{
__published:	// IDE-managed Components
    TLabel *labelMessage;
    TLabel *Label1;
    TLabel *Label2;
    TButton *btnCancel;
    TButton *btnDelete;
    TButton *btnMark;
    TCheckBox *checkApplyToAll;
    TLabel *labelObjName;
    TLabel *labelPosition;
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnDeleteClick(TObject *Sender);
    void __fastcall btnMarkClick(TObject *Sender);
private:	// User declarations
    int FLastAction;
    TRoadObject *FObj;
    TDtaSource *FSrc;
    void __fastcall DeleteObject(void);
    void __fastcall MarkObject(void);
public:		// User declarations
    __fastcall TErrorObjectDialog(TComponent* Owner);
    void __fastcall NewSession(void);
    bool __fastcall Execute(TRoadObject *obj,TDtaSource *src,String Message,String ObjName);
};
//---------------------------------------------------------------------------
extern PACKAGE TErrorObjectDialog *ErrorObjectDialog;
//---------------------------------------------------------------------------
#endif
