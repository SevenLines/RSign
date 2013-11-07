//---------------------------------------------------------------------------

#ifndef EditGeomParamsH
#define EditGeomParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
//---------------------------------------------------------------------------
class TfrmEditGeomData : public TForm
{
__published:	// IDE-managed Components
    TDBGridEh *DBGGeomParams;
    TEdit *txtStartPos;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *txtEndPos;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *txtRadius;
    TComboBox *cbType;
    TButton *cmdChange;
    TButton *Button3;
    TButton *Button4;
    TDataSource *DataSource;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall cmdChangeClick(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall DBGGeomParamsDblClick(TObject *Sender);
private:	// User declarations
    TADOConnection *FConnection;
public:		// User declarations
    __fastcall TfrmEditGeomData(TComponent* Owner);
    void __fastcall UpdateTXTControls(TObject *Sender);
    __property TADOConnection *Connection={read=FConnection,write=FConnection};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditGeomData *frmEditGeomData;
//---------------------------------------------------------------------------
#endif
