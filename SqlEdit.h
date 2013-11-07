//---------------------------------------------------------------------------

#ifndef SqlEditH
#define SqlEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RoadDict.h"
//---------------------------------------------------------------------------
class TSqlEditFrm : public TForm
{
__published:	// IDE-managed Components
    TRadioGroup *RadioGroup1;
    TMemo *Memo1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall RadioGroup1Click(TObject *Sender);
private:	// User declarations
    String FSql[4];
    int FOldIndex;
public:		// User declarations
    bool __fastcall Execute(TObjMetaClass *);
    __fastcall TSqlEditFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSqlEditFrm *SqlEditFrm;
//---------------------------------------------------------------------------
#endif
