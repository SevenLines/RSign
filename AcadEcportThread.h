//---------------------------------------------------------------------------

#ifndef AcadEcportThreadH
#define AcadEcportThreadH

#include "acadexport.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class AcadExport : public TThread
{            
private:
protected:
        void __fastcall Execute();
public:
        __fastcall AcadExport(bool CreateSuspended);
        TRoad *R;
};
//---------------------------------------------------------------------------
#endif
