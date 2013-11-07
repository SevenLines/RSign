//---------------------------------------------------------------------------

#ifndef DumpFormH
#define DumpFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "DataSour.h"
//---------------------------------------------------------------------------
class TDumpDialog : public TForm
{
__published:	// IDE-managed Components
    TEdit *FileName;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *FilePath;
    TButton *Button1;
    TCheckBox *SaveGeom;
    TButton *Button2;
    TButton *Button3;
    TSaveDialog *SvDialog;
    TLabel *Label3;
    TComboBox *DataSrcList;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall DataSrcListChange(TObject *Sender);
private:	// User declarations
    TDictSource *FCurrentDict;
public:		// User declarations
    __fastcall TDumpDialog(TComponent* Owner);
    __property TDictSource* CurrentDict={read=FCurrentDict,write=FCurrentDict};
    void __fastcall SetCurrentData(TDtaSource* data);
};
//---------------------------------------------------------------------------
extern PACKAGE TDumpDialog *DumpDialog;
//---------------------------------------------------------------------------
#endif
