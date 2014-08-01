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
private:
    AnsiString _directory;
    AnsiString _sqltotxt;
    AnsiString _applicationDir;
    AnsiString _lastOutputDir;

public:
    MiniReports();
    ~MiniReports();

    AnsiString ScriptsDirectory();
    void setApplicationDir(AnsiString ApplicationDir);
    vector<AnsiString> GetReports();
    void GenReport(AnsiString reportName, map<AnsiString, AnsiString> params);

    void LoadIni(TIniFile* ini);
    void SaveIni(TIniFile* ini);
};

MiniReports MiniReportsSingleton;

#endif
