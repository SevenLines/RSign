//---------------------------------------------------------------------------

#ifndef MiniReportsH
#define MiniReportsH
//---------------------------------------------------------------------------

#include <vector>
#include <map>
#include <system.hpp>
#include <IniFiles.hpp>
#include <Menus.hpp>
using namespace std;

class MiniReports
{
public:
  struct Credentials {
    AnsiString UserId;
    AnsiString Password;
    AnsiString DataSource;
    AnsiString InitialCatalog;

    Credentials(AnsiString connectionString = "");
    void FromConnectionString(AnsiString connectionString);
  };

private:
    AnsiString _directory;
    AnsiString _sqltotxt;
    AnsiString _sql2docx;    
    AnsiString _applicationDir;
    AnsiString _lastOutputDir;

public:
    MiniReports();
    ~MiniReports();

    AnsiString ScriptsDirectory();
    void setApplicationDir(AnsiString ApplicationDir);
    vector<AnsiString> GetReports();
    vector<AnsiString> GetDocXReports();
    void GenReport(AnsiString reportName, map<AnsiString, AnsiString> &params, Credentials &credentials);
    void GenDocxReport(AnsiString reportName, map<AnsiString, AnsiString> &params, Credentials &credentials);
    void UpdateDocxReport(AnsiString reportName, map<AnsiString, AnsiString> &params, Credentials &credentials);
    void RoadToFromXML(map<AnsiString, AnsiString> &params, AnsiString connectionString, AnsiString method);  
    void ExecuteScript(AnsiString appPath, AnsiString script, Credentials &credentials);

    void LoadIni(TIniFile* ini);
    void SaveIni(TIniFile* ini);
};

MiniReports MiniReportsSingleton;

#endif
