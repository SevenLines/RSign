//---------------------------------------------------------------------------

#ifndef BuildSlopesH
#define BuildSlopesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmBuildSlopes : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox6;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit2;
    TUpDown *ProfMinLen;
    TEdit *Edit3;
    TUpDown *ProfMaxDev;
    TGroupBox *GroupBox7;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *Edit4;
    TEdit *Edit5;
    TUpDown *ProfVal1;
    TUpDown *ProfVal2;
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label6;
    TEdit *edtStartPos;
    TEdit *edtEndPos;
private:	// User declarations
    void __fastcall SetProfilMinLen(int);
    int __fastcall GetProfilMinLen(void);
    void __fastcall SetProfilMaxDev(int);
    int __fastcall GetProfilMaxDev(void);
    void __fastcall SetProfilVal1(int);
    int __fastcall GetProfilVal1(void);
    void __fastcall SetProfilVal2(int);
    int __fastcall GetProfilVal2(void);
    void __fastcall SetStartPos(int);
    int __fastcall GetStartPos(void);
    void __fastcall SetEndPos(int);
    int __fastcall GetEndPos(void);
public:		// User declarations
    __fastcall TfrmBuildSlopes(TComponent* Owner);
    __property int ProfilMinLen={read=GetProfilMinLen,write=SetProfilMinLen};
    __property int ProfilMaxDev={read=GetProfilMaxDev,write=SetProfilMaxDev};
    __property int ProfilVal1={read=GetProfilVal1,write=SetProfilVal1};
    __property int ProfilVal2={read=GetProfilVal2,write=SetProfilVal2};
    __property int StartPos={read=GetStartPos,write=SetStartPos};
    __property int EndPos={read=GetEndPos,write=SetEndPos};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBuildSlopes *frmBuildSlopes;
//---------------------------------------------------------------------------
#endif
