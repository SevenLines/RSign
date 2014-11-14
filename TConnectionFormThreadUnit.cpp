//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TConnectionFormThreadUnit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TConnectionFormThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TConnectionFormThread::TConnectionFormThread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void TConnectionFormThread::openAsync()
{
    Message = "";
    try {
        Connection->LoginPrompt = false;
        Connection->Open();
    } catch (Exception* e) {
        Message = e->Message;
    }
}
//---------------------------------------------------------------------------
void TConnectionFormThread::getSchemasList()
{
    if (Connection->Connected) {
        //WideString lastDataBaseName = cmbInitialCatalog->Text;
        int selectedIndex = -1;
        
        TADODataSet* response = new TADODataSet(0);

        OleVariant ErrorParam;
        ErrorParam.VType = VT_ERROR;
        schemasList.clear();
        //EmptyParam.VError = DISP_E_PARAMNOTFOUND;
        Connection->OpenSchema(siCatalogs, OleVariant(), ErrorParam, response);

        schemasList.clear();
        //cmbInitialCatalog->Clear();
        response->Open();
        response->First();
        int recordNum = 0;
        while(!response->Eof) {
            AnsiString dbName = response->FieldByName("CATALOG_NAME")->AsString;
            /*if (dbName == lastDataBaseName) {
                selectedIndex = recordNum;
            }*/
            schemasList.push_back(dbName);
            ++recordNum;
            //cmbInitialCatalog->AddItem(dbName, 0);
            response->Next();
        }
        response->Close();

        delete response;

        //cmbInitialCatalog->ItemIndex = selectedIndex;
    }
}

vector<AnsiString> TConnectionFormThread::SchemasList()
{
    return schemasList;
}
//---------------------------------------------------------------------------
void __fastcall TConnectionFormThread::Execute()
{
    //---- Place thread code here ----
    switch(action) {
    case cfaGetSchemasList:
        getSchemasList();
        break;
    case cfaOpenAsync:
        openAsync();
        break;
    }
}
//---------------------------------------------------------------------------
