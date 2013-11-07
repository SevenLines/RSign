//---------------------------------------------------------------------------

#ifndef BuildWidePartH
#define BuildWidePartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "DataSour.h"
//---------------------------------------------------------------------------
class TfrmWidePartDialog : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TCheckBox *checkPart;
    TLabel *Label1;
    TEdit *editPartMaxDev;
    TLabel *Label2;
    TEdit *editPartRoundVal;
    TGroupBox *GroupBox2;
    TCheckBox *checkLeftSide;
    TCheckBox *checkRightSide;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *editSideMaxDev;
    TEdit *editSideRountVal;
    TLabel *Label5;
    TComboBox *comboSideKind;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *editStartPos;
    TEdit *editEndPos;
    TButton *Button1;
    TButton *Button2;
    TUpDown *updPartMaxDev;
    TUpDown *updPartRoundVal;
    TUpDown *updSideMaxDev;
    TUpDown *updSideRoundVal;
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    TDictSource *FDict;
    int __fastcall GetPartMaxDev(void)
        {return updPartMaxDev->Position;}
    int __fastcall GetPartRoundVal(void)
        {return updPartRoundVal->Position;}
    int __fastcall GetSideMaxDev(void)
        {return updSideMaxDev->Position;}
    int __fastcall GetSideRoundVal(void)
        {return updSideRoundVal->Position;}
    int __fastcall GetStartPos(void)
        {return editStartPos->Text.ToInt();}
    void __fastcall SetStartPos(int v)
        {editStartPos->Text=String(v);}
    int __fastcall GetEndPos(void)
        {return editEndPos->Text.ToInt();}
    void __fastcall SetEndPos(int v)
        {editEndPos->Text=String(v);}
    int __fastcall GetSideKind(void)
        {return ((TTextPropRec*)comboSideKind->Items->Objects[comboSideKind->ItemIndex])->Id;}
    bool __fastcall GetBuildParts(void)
        {return checkPart->Checked;}
    bool __fastcall GetBuildLeftSides(void)
        {return checkLeftSide->Checked;}
    bool __fastcall GetBuildRightSides(void)
        {return checkRightSide->Checked;}
public:		// User declarations
    __fastcall TfrmWidePartDialog(TComponent* Owner);
    __property TDictSource *Dict={read=FDict,write=FDict};
    __property int PartMaxDev={read=GetPartMaxDev};
    __property int PartRoundVal={read=GetPartRoundVal};
    __property int SideMaxDev={read=GetSideMaxDev};
    __property int SideRoundVal={read=GetSideRoundVal};
    __property int StartPos={read=GetStartPos,write=SetStartPos};
    __property int EndPos={read=GetEndPos,write=SetEndPos};
    __property int SideKind={read=GetSideKind};
    __property bool BuildParts={read=GetBuildParts};
    __property bool BuildLeftSides={read=GetBuildLeftSides};
    __property bool BuildRightSides={read=GetBuildRightSides};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWidePartDialog *frmWidePartDialog;
//---------------------------------------------------------------------------
#endif
