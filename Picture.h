//---------------------------------------------------------------------------

#ifndef PictureH
#define PictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPictureForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image;
private:	// User declarations
public:		// User declarations
    __fastcall TPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPictureForm *PictureForm;
//---------------------------------------------------------------------------
#endif
