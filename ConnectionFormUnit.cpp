//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectionFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConnectionForm *ConnectionForm;
//---------------------------------------------------------------------------
__fastcall TConnectionForm::TConnectionForm(TComponent* Owner)
    : TForm(Owner)
{
    mConnection = new TADOConnection(this);
}
//---------------------------------------------------------------------------
void TConnectionForm::loadIni(TIniFile *ini)
{
    cmbInitialCatalog->Text = ini->ReadString("ConnectionForm", "Initial Catalog", "");
    cmbDataSource->Text = ini->ReadString("ConnectionForm", "DataSource", "");
    edtUserID->Text = ini->ReadString("ConnectionForm", "UserID", "");
    edtPassword->Text = ini->ReadString("ConnectionForm", "Password", "");
    edtProvider->Text = ini->ReadString("ConnectionForm", "Provider", "SQLOLEDB.1");
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
    ini->WriteBool("ConnectionForm", "AsLocalUser", chkAsLocalUser->Checked);
}
//---------------------------------------------------------------------------
void TConnectionForm::fillSchemasList(TADOConnection *connection)
{
    if (connection->Connected) {
        WideString lastDataBaseName = cmbInitialCatalog->Text;
        int selectedIndex = -1;
        
        TADODataSet* response = new TADODataSet(0);

        OleVariant ErrorParam;
        ErrorParam.VType = VT_ERROR;
        //EmptyParam.VError = DISP_E_PARAMNOTFOUND;
        connection->OpenSchema(siCatalogs, OleVariant(), ErrorParam, response);

        cmbInitialCatalog->Clear();
        response->Open();
        response->First();
        int recordNum = 0;
        while(!response->Eof) {
            AnsiString dbName = response->FieldByName("CATALOG_NAME")->AsString;
            if (dbName == lastDataBaseName) {
                selectedIndex = recordNum;
            }
            ++recordNum;
            cmbInitialCatalog->AddItem(dbName, 0);
            response->Next();
        }
        response->Close();

        delete response;

        cmbInitialCatalog->ItemIndex = selectedIndex;
    }
}
//---------------------------------------------------------------------------
bool TConnectionForm::testConnection(bool checkDatabaseList)
{
    mConnection->Close();
    lblSuccess->Color = clRed;
    Application->ProcessMessages();
    Sleep(100);
    mConnection->ConnectionString = getConnectionString(checkDatabaseList);
    try {
        mConnection->LoginPrompt = false;
        mConnection->Open();
    } catch (Exception* e) {
        ShowMessage(e->Message);
    }
    lblSuccess->Color = mConnection->Connected ? clGreen : clRed;

    if (mConnection->Connected  && checkDatabaseList) {
        fillSchemasList(mConnection);
    }

    return mConnection->Connected;

}
//---------------------------------------------------------------------------
bool TConnectionForm::connect()
{
    if (!testConnection()) {
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
    if (connection) {
        bool userID_is_Set = false;
        for(char* tok = strtok(AnsiString(connection->ConnectionString).c_str(), ";"); tok; tok = strtok(NULL, ";"))  {
            AnsiString str = AnsiString(tok);
            if (str.Pos("Initial Catalog=")) {
                cmbInitialCatalog->Text = str.Delete(1, strlen("Initial Catalog="));
            }
            if (str.Pos("User Id=")) {
                userID_is_Set = true;
                edtUserID->Text = str.Delete(1, strlen("UserId="));
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

    updateInterface();
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
    out += getConnectionItem("Provider", edtProvider->Text, "SQLOLEDB.1");
    if (!withoutDataBase) {
        out += getConnectionItem("Initial Catalog", cmbInitialCatalog->Text, "");
    }
    out += getConnectionItem("Data Source", cmbDataSource->Text, "(local)");
    if (!chkAsLocalUser->Checked) {
        out += getConnectionItem("User ID", edtUserID->Text, "");
        out += getConnectionItem("Password", edtPassword->Text, "");
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
}
void __fastcall TConnectionForm::btnConnectToSeverClick(TObject *Sender)
{
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

