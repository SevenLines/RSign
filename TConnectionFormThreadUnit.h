//---------------------------------------------------------------------------

#ifndef TConnectionFormThreadUnitH
#define TConnectionFormThreadUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <vector>

using namespace std;
//---------------------------------------------------------------------------
enum ConnectionFormActions {cfaGetSchemasList, cfaOpenAsync};

class TConnectionFormThread : public TThread
{
private:
    vector<AnsiString> schemasList;
    void getSchemasList();
    void openAsync();
protected:
    void __fastcall Execute();
public:
    __fastcall TConnectionFormThread(bool CreateSuspended);
    TADOConnection* Connection;
    ConnectionFormActions action;


    vector<AnsiString> SchemasList();
    AnsiString Message;



};
//---------------------------------------------------------------------------
#endif
