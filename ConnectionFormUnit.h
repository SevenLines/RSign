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
#include "TConnectionFormThreadUnit.h"

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
    TTimer *TimerComboInitialCatalog;
    void __fastcall btnTestClick(TObject *Sender);
    void __fastcall chkAsLocalUserClick(TObject *Sender);
    void __fastcall btnConnectToSeverClick(TObject *Sender);
    void __fastcall btnConnectClick(TObject *Sender);
    void __fastcall TimerComboInitialCatalogTimer(TObject *Sender);
private:	// User declarations
    TADOConnection *mConnection;
    TADOConnection *mInitConnection;
    TConnectionFormThread *thread;
    bool fTryToConnect;
    bool fCheckDatabaseList;
    WideString getConnectionString();
    WideString getConnectionString(bool withoutDataBase);
    WideString getConnectionItem(WideString key, WideString value, WideString def="");
    void setInitConnection(TADOConnection *connection);
    void setConnectionString(WideString connectionString);

public:		// User declarations
    __fastcall TConnectionForm(TComponent* Owner);
    void loadIni(TIniFile *ini);
    void saveIni(TIniFile *ini);

    bool testConnection(bool checkDatabaseList=false, bool async=true);
    void fillSchemasList(TADOConnection *connection);
    void __fastcall ThreadOnTerminate(TObject *object);
    void __fastcall ConnectComplete(TADOConnection* Connection,
        const _di_Error Error, TEventStatus &EventStatus);

    void toggleConnectButtons(bool enable=true);
    void toggleComboInitialCatalog(bool enable=true);

    bool connect();

    void updateInterface();

    __property TADOConnection* Connection={write=setInitConnection};
    __property WideString ConnectionString={read=getConnectionString,write=setConnectionString};
  
};
//---------------------------------------------------------------------------
extern PACKAGE TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
#endif
