//---------------------------------------------------------------------------

#ifndef PreViewH
#define PreViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "DrawMan.h"
//---------------------------------------------------------------------------
class TPreViewFrm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TComboBox *PageList;
    TComboBox *MsList;
    TScrollBox *ScrollBox1;
    TImage *Image1;
    TLabel *Label1;
    TLabel *Label2;
    TSpeedButton *SpeedButton1;
    void __fastcall PageListChange(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
    TDrawBitmap *BCont;
    int FStartKm,FEndKm,FKmPerPage;
    int FDeviceKind; // вид устройства 0 - тек принтер, 1 - растр картинка
public:		// User declarations
    __fastcall TPreViewFrm(TComponent* Owner);
    void __fastcall SetPageList(int skm,int ekm,int pkm,int devkind);
    void __fastcall MakeCurrentPage(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPreViewFrm *PreViewFrm;
//---------------------------------------------------------------------------
#endif
