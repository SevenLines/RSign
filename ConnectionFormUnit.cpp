//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectionFormUnit.h"
#include <algorithms>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
__fastcall TConnectionForm::TConnectionForm(TComponent* Owner)
    : TForm(Owner)
{
    mConnection = new TADOConnection(this);
    fTryToConnect = false;
    fCheckDatabaseList = false;
}
//---------------------------------------------------------------------------
void TConnectionForm::loadIni(TIniFile *ini)
{
    cmbInitialCatalog->Text = ini->ReadString("ConnectionForm", "Initial Catalog", "");
    cmbDataSource->Text = ini->ReadString("ConnectionForm", "DataSource", "");
    edtUserID->Text = ini->ReadString("ConnectionForm", "UserID", "");
    edtPassword->Text = ini->ReadString("ConnectionForm", "Password", "");
    edtProvider->Text = ini->ReadString("ConnectionForm", "Provider", "SQLOLEDB.1");
    FillServerList(ini->ReadString("ConnectionForm", "Servers", ""));
    chkAsLocalUser->Checked = ini->ReadBool("ConnectionForm", "AsLocalUser", false);

    updateInterface();   
}
//---------------------------------------------------------------------------
void TConnectionForm::saveIni(TIniFile *ini)
{
    ini->WriteString("ConnectionForm", "Initial Catalog", cmbInitialCatalog->Text);
    ini->WriteString("ConnectionForm", "DataSource", cmbDataSource->Text);
    ini->WriteString("ConnectionForm", "UserID", edtUserID->Text);
    ini->WriteString("ConnectionForm", "Password", edtPassword->Text);
    ini->WriteString("ConnectionForm", "Provider", edtProvider->Text);
    ini->WriteString("ConnectionForm", "Servers", getServersListString());
    ini->WriteBool("ConnectionForm", "AsLocalUser", chkAsLocalUser->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TConnectionForm::ThreadOnTerminate(TObject *object)
{
    TConnectionFormThread* thread = dynamic_cast<TConnectionFormThread*>(object);
    if (thread && thread == this->thread) {
        AnsiString lastDataBaseName;
        int selectedIndex;
        vector<AnsiString> lst;

        switch(thread->action) {
        case cfaGetSchemasList:
            lst = thread->SchemasList();
            lastDataBaseName = cmbInitialCatalog->Text;
            cmbInitialCatalog->Clear();
            cmbInitialCatalog->Text = "";
            //selectedIndex = -1;
            for (int i=0;i<lst.size();++i) {
                cmbInitialCatalog->AddItem(lst[i], 0);
                //if (lst[i] == lastDataBaseName) {
                    //selectedIndex = i;
                //}
            }
            //cmbInitialCatalog->ItemIndex = selectedIndex;
            break;
        }

        this->thread = 0;
        cmbInitialCatalog->Enabled = true;
        toggleComboInitialCatalog(true);
    }

}

void __fastcall TConnectionForm::ConnectComplete(TADOConnection* Connection,
        const _di_Error Error, TEventStatus &EventStatus)
{
    fTryToConnect = false;
    toggleComboInitialCatalog(true);
    lblSuccess->Color = Connection->Connected ? clGreen : clRed;
    if (Connection->Connected && fCheckDatabaseList) {
        updateServerList(cmbDataSource->Text);
        fillSchemasList(Connection);
    }
    //mConnection->Errors
}
//---------------------------------------------------------------------------
void TConnectionForm::fillSchemasList(TADOConnection *connection)
{
    TConnectionFormThread *thread = new TConnectionFormThread(true);
    thread->OnTerminate = ThreadOnTerminate;
    thread->action = cfaGetSchemasList;
    toggleComboInitialCatalog(false);

    this->thread = thread;
    thread->Connection = connection;
    thread->Resume();
}
//---------------------------------------------------------------------------
bool TConnectionForm::testConnection(bool checkDatabaseList, bool async)
{

    lblSuccess->Color = clRed;
    Application->ProcessMessages();
    Sleep(100);

    mConnection->Close();
    mConnection->ConnectionString = getConnectionString(checkDatabaseList);

    fTryToConnect = true;
    fCheckDatabaseList = checkDatabaseList && async;


    mConnection->ConnectOptions = async ? coAsyncConnect : coConnectUnspecified;
    mConnection->OnConnectComplete = ConnectComplete;
    mConnection->LoginPrompt = false;
    toggleComboInitialCatalog(false);
    try {
        mConnection->Open();
    } catch (Exception* e) {
        ShowMessage(e->Message);
    }

    return mConnection->Connected;

}
//---------------------------------------------------------------------------
bool TConnectionForm::connect()
{
    if (!testConnection(false, false)) {
        ShowMessage("Не могу подсоединится!");
        return false;
    }
    if (mInitConnection) {
        try {
            mInitConnection->Close();
            mInitConnection->ConnectionString = ConnectionString;
            mInitConnection->Open();
        } catch (Exception* e) {
            ShowMessage(e->Message);
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
void TConnectionForm::setInitConnection(TADOConnection *connection)
{
    mInitConnection = connection;
    updateInterface();
    if (connection) {
        bool userID_is_Set = false;
        for(char* tok = strtok(AnsiString(connection->ConnectionString).c_str(), ";"); tok; tok = strtok(NULL, ";"))  {
            AnsiString str = AnsiString(tok);
            if (str.Pos("Initial Catalog=")) {
                cmbInitialCatalog->Text = str.Delete(1, strlen("Initial Catalog="));
            }
            if (str.Pos("User ID=")) {
                userID_is_Set = true;
                edtUserID->Text = str.Delete(1, strlen("User ID="));
            }
            if (str.Pos("Provider=")) {
                edtProvider->Text = str.Delete(1, strlen("Provider="));
            }
            if (str.Pos("Data Source=")) {
                cmbDataSource->Text = str.Delete(1, strlen("Data Source="));
            }
        }
        chkAsLocalUser->Checked = !userID_is_Set;
        if (connection->Connected) {
            fillSchemasList(connection);
        }
    }

}
//---------------------------------------------------------------------------
WideString TConnectionForm::getConnectionItem(WideString key, WideString value, WideString def)
{
    return key + "=" + (value.IsEmpty() ? def : value) + ";";
}
//---------------------------------------------------------------------------
WideString TConnectionForm::getConnectionString(bool withoutDataBase)
{
    WideString out;
    out += getConnectionItem("Provider", edtProvider->Text.Trim(), "SQLOLEDB.1");
    if (!withoutDataBase) {
        out += getConnectionItem("Initial Catalog", cmbInitialCatalog->Text.Trim(), "");
    }
    out += getConnectionItem("Data Source", cmbDataSource->Text.Trim(), "(local)");
    if (!chkAsLocalUser->Checked) {
        out += getConnectionItem("User ID", edtUserID->Text.Trim(), "");
        out += getConnectionItem("Password", edtPassword->Text.Trim(), "");
    } else {
        out += getConnectionItem("Integrated Security", "", "SSPI");
    }
    return out;
}
//---------------------------------------------------------------------------
WideString TConnectionForm::getConnectionString()
{
    return getConnectionString(false);
}
//---------------------------------------------------------------------------
void TConnectionForm::setConnectionString(WideString connectionString)
{
    mConnection->ConnectionString = connectionString;
}
void __fastcall TConnectionForm::btnTestClick(TObject *Sender)
{
    testConnection();    
}
//---------------------------------------------------------------------------


void __fastcall TConnectionForm::chkAsLocalUserClick(TObject *Sender)
{
    updateInterface();
}
//---------------------------------------------------------------------------
void TConnectionForm::updateInterface()
{
    edtUserID->Enabled = !chkAsLocalUser->Checked;
    edtPassword->Enabled = !chkAsLocalUser->Checked;
    lblUserID->Enabled = !chkAsLocalUser->Checked;
    lblPassword->Enabled = !chkAsLocalUser->Checked;
    lblSuccess->Color = (mInitConnection && mInitConnection->Connected) ? clGreen : clRed;
    toggleComboInitialCatalog(true);
}
//---------------------------------------------------------------------------
AnsiString TConnectionForm::getServersListString()
{
    AnsiString out;
    for (int i=0;i<serversList.size();++i) {
        out += serversList[i]+";";
    }
    return out;
}
//---------------------------------------------------------------------------
void TConnectionForm::FillServerList(AnsiString ServersString)
{
    for(char* tok = strtok(ServersString.c_str(), ";"); tok; tok = strtok(NULL, ";"))  {
        serversList.push_back(tok);
    }
    sort(serversList.begin(), serversList.end());
    for (int  i=0;i<serversList.size();++i) {
        cmbDataSource->AddItem(serversList[i], 0);
    }
}
//---------------------------------------------------------------------------
void TConnectionForm::updateServerList(AnsiString serverName)
{
    if(find(serversList.begin(), serversList.end(), serverName) == serversList.end() ) {
        cmbDataSource->AddItem(serverName, 0);
        serversList.push_back(serverName);
        sort(serversList.begin(), serversList.end());
    }
}
//---------------------------------------------------------------------------
void __fastcall TConnectionForm::btnConnectToSeverClick(TObject *Sender)
{
    if (fTryToConnect) {
        mConnection->Cancel();
        return;
    }
    
    if (thread) {
        toggleComboInitialCatalog(true);
        thread = 0;
        return;
    }

    testConnection(true);
}
//---------------------------------------------------------------------------
void __fastcall TConnectionForm::btnConnectClick(TObject *Sender)
{
    if (connect()) {
        ModalResult = mrOk;
    }
}
//---------------------------------------------------------------------------

void __fastcall TConnectionForm::TimerComboInitialCatalogTimer(
      TObject *Sender)
{
    static int index = 0;
    ++index;
    AnsiString message[] = {
        "Пробую подключиться, подождите",
        "> Пробую подключиться, подождите .",
        ">> Пробую подключиться, подождите ..",
        ">>> Пробую подключиться, подождите ..."
    };
    cmbInitialCatalog->Text = message[index%4];
    if (index > 3)
        index = 0;
}
//---------------------------------------------------------------------------
void TConnectionForm::toggleConnectButtons(bool enable)
{
    btnConnect->Enabled = enable;
    btnTest->Enabled = enable;
    btnConnectToSever->Enabled = enable;
}
//---------------------------------------------------------------------------
void TConnectionForm::restoreComboItemPosition(AnsiString itemText, TComboBox *cmb)
{
    int selectedIndex = -1;
    for (int i=0;i<cmb->Items->Count;++i) {
        if (cmb->Items->Strings[i] == itemText) {
            selectedIndex = i;
        }
    }
    cmb->ItemIndex = selectedIndex;
}
//---------------------------------------------------------------------------
void TConnectionForm::toggleComboInitialCatalog(bool enable)
{
    static AnsiString lastComboValue;

    if (enable == false) {
        lastComboValue = cmbInitialCatalog->Text;
    } else {
        restoreComboItemPosition(lastComboValue, cmbInitialCatalog);
    }

    cmbInitialCatalog->Enabled = enable;
    cmbDataSource->Enabled = enable;

    chkAsLocalUser->Enabled = enable;
    TimerComboInitialCatalog->Enabled = !enable;
    toggleConnectButtons(enable);
}


void __fastcall TConnectionForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_ESCAPE) {
        ModalResult = mrCancel;
    }    
}
//---------------------------------------------------------------------------

