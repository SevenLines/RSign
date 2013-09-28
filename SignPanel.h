//---------------------------------------------------------------------------

#ifndef SignPanelH
#define SignPanelH
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "DataSour.h"
//---------------------------------------------------------------------------
class TSignPanel : public TPanel
{
private:
int FCount;
int FSize;
int FActCount;
TStringList *Codes;
TSpeedButton **Buttons;
void __fastcall ButtonClick(TObject *Sender);
void __fastcall DrawBitmap(TDictSource *Dict,Graphics::TBitmap *bmp,String Code);
public:
__fastcall TSignPanel(TComponent *Owner);
__fastcall ~TSignPanel();
void __fastcall SetSigns(int count,int size);
void __fastcall AddButton(TDictSource *Dict,String SignCode);
};

#endif
