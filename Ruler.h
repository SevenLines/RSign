//---------------------------------------------------------------------------
#ifndef RulerH
#define RulerH
// Класс для отображения линейки
//---------------------------------------------------------------------------
enum TRulerKind {rkGorisontal=1,rkVertical=2};
class TRuler : public TGraphicControl
{
private:
bool FDir; // Направление рисования
TRulerKind FKind;
TFont *FFont;
double FMin,FMax; // Границы линейки в координатах дороги
int FDrwStart;
int FDrwLen;
double FMarker;
bool FMarkerVisible;
void __fastcall SetKind(TRulerKind k);
virtual void __fastcall Paint(void);
void __fastcall DrawMarker(void);
void __fastcall SetMarker(double pos);
void __fastcall SetFont(TFont *font);
public:
__fastcall TRuler(TComponent *Owner)
    : TGraphicControl(Owner)
    {FFont=new TFont;
     FMarkerVisible=false;
     ControlStyle=ControlStyle<<csOpaque;
    }
__fastcall ~TRuler(void)
    {delete FFont;}
void __fastcall SetMinMax(bool d,double min,double max,int ds,int dl);
void __fastcall HideMarker(void);
__property Font={read=FFont,write=SetFont};
__property bool Dir={read=FDir};
__property double Min={read=FMin};
__property double Max={read=FMax};
__property double Marker={read=FMarker,write=SetMarker};
__property bool MarkerVisible={read=FMarkerVisible};
__property TRulerKind Kind={read=FKind,write=SetKind};
};

#endif
