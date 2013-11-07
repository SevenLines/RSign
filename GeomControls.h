//---------------------------------------------------------------------------

#ifndef GeomControlsH
#define GeomControlsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ShowVideo.h"
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TfrmGeomControls : public TForm
{
__published:	// IDE-managed Components
    TCheckListBox *clbCeomControls;
    TButton *Button1;
    TButton *Button2;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmGeomControls(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGeomControls *frmGeomControls;
//---------------------------------------------------------------------------
#endif
