//---------------------------------------------------------------------------

#ifndef ConnectionFormUnitH
#define ConnectionFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
class TConnectionForm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grpUserInfo;
    TEdit *edtUserID;
    TEdit *edtPassword;
    TLabel *lblUserID;
    TLabel *lblPassword;
    TPanel *Panel1;
    TComboBox *cmbDataSource;
    TPanel *Panel2;
    TComboBox *cmbInitialCatalog;
    TPanel *Panel3;
    TButton *btnCancel;
    TEdit *edtProvider;
    TCheckBox *chkAsLocalUser;
    TPanel *Panel4;
    TButton *btnConnect;
    TButton *btnTest;
    TButton *btnConnectToSever;
    TLabel *lblSuccess;
    void __fastcall btnTestClick(TObject *Sender);
    void __fastcall chkAsLocalUserClick(TObject *Sender);
    void __fastcall btnConnectToSeverClick(TObject *Sender);
    void __fastcall btnConnectClick(TObject *Sender);
private:	// User declarations
    TADOConnection *mConnection;
    TADOConnection *mInitConnection;
    WideString getConnectionString();
    WideString getConnectionString(bool withoutDataBase);
    WideString getConnectionItem(WideString key, WideString value, WideString def="");
    void setInitConnection(TADOConnection *connection);
    void setConnectionString(WideString connectionString);

public:		// User declarations
    __fastcall TConnectionForm(TComponent* Owner);
    void loadIni(TIniFile *ini);
    void saveIni(TIniFile *ini);

    bool testConnection(bool checkDatabaseList=false);
    void fillSchemasList(TADOConnection *connection);
    bool connect();

    void updateInterface();

    __property TADOConnection* Connection={write=setInitConnection};
    __property WideString ConnectionString={read=getConnectionString,write=setConnectionString};
  
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
#endif
