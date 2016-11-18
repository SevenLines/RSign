//---------------------------------------------------------------------------


#pragma hdrstop

#include "MiniReports.h"
#include <SysUtils.hpp>
#include <FileCtrl.hpp>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Dialogs.hpp>


//---------------------------------------------------------------------------

#pragma package(smart_init)

MiniReports::Credentials::Credentials(AnsiString connectionString)
{
    UserId = "";
    Password = "";
    DataSource = "";
    InitialCatalog = "";
    if (connectionString!="") {
         FromConnectionString(connectionString);
    }
}

void MiniReports::Credentials::FromConnectionString(AnsiString s)
{
  for(char* tok = strtok(s.c_str(), ";"); tok; tok = strtok(NULL, ";"))  {
    AnsiString str = AnsiString(tok);
    if (str.Pos("Initial Catalog=")) {
        InitialCatalog = str.Delete(1, strlen("Initial Catalog="));
    }
    if (str.Pos("UserId=") || str.Pos("User ID=") || str.Pos("UserID=")) {
        int eqPos = str.Pos("=");
        UserId = str.Delete(1, eqPos);
    }
    if (str.Pos("Password=")) {
        Password = str.Delete(1, strlen("Password="));
    }
    if (str.Pos("Data Source=")) {
        str = str.Delete(1, strlen("Data Source="));
        DataSource = str=="(local)" ? AnsiString(".") : str;
    }
  }
}

MiniReports::MiniReports() :
_directory("AutoCAD\\Scripts\\")
,_sqltotxt("sqltotxt.exe")
,_sql2docx("sql2docx.exe")
{
	_applicationDir = GetCurrentDir();
}

void MiniReports::setApplicationDir(AnsiString ApplicationDir)
{
	_applicationDir = ApplicationDir;
}

MiniReports::~MiniReports()
{

}

AnsiString MiniReports::ScriptsDirectory()
{
	return _applicationDir + "\\" + _directory;
}

vector<AnsiString> MiniReports::GetReports()
{
	AnsiString reportsDir = ScriptsDirectory() + "minireports\\*";

	TSearchRec sr;
	vector<AnsiString> dirs;
	int iAttributes = faDirectory;
	if (FindFirst(reportsDir, iAttributes, sr) == 0)
	{
		do
		{
			if ((sr.Attr & iAttributes) == iAttributes)
			{
				if (sr.Name != "." && sr.Name != "..") {
					dirs.push_back(sr.Name);
				}
			}
		} while (FindNext(sr) == 0);
		FindClose(sr);
	}
	return dirs;
}

vector<AnsiString> MiniReports::GetDocXReports()
{
	AnsiString reportsDir = ScriptsDirectory() + "docx\\*.docx";

	TSearchRec sr;
	vector<AnsiString> dirs;
	int iAttributes = 0;
	if (FindFirst(reportsDir, iAttributes, sr) == 0)
	{
		do
		{
            if (sr.Name != "." && sr.Name != "..") {
                dirs.push_back(sr.Name);
            }
		} while (FindNext(sr) == 0);
		FindClose(sr);
	}
	return dirs;
}

void MiniReports::GenDocxReport(AnsiString reportName, map<AnsiString, AnsiString> &params,
         Credentials &credentials)
{
    AnsiString docxReportPath = ScriptsDirectory() + "docx\\" + reportName;
    TSaveDialog *saveDialog = new TSaveDialog(NULL);

    TReplaceFlags flags;
    flags << rfReplaceAll;

    saveDialog->Title = "Выберите файл куда сохранится результат";
    saveDialog->FileName = StringReplace(params["RoadName"], "\"", "", flags);
    saveDialog->FileName = StringReplace(saveDialog->FileName, "/", "", flags);
    saveDialog->FileName = StringReplace(saveDialog->FileName, "\\", "", flags);
	saveDialog->Filter = "docx | *.docx";
    saveDialog->DefaultExt = ".docx";
	if(!saveDialog->Execute()) {
       delete saveDialog;
       return;
    }

    AnsiString exe = ScriptsDirectory() + "sql2docx.exe";
    AnsiString script;
	script.sprintf("\"%s\" -i \"%s\" -o \"%s\"",
					exe,
                    docxReportPath,
                    saveDialog->FileName);

    if (params.size() > 0) {
		script += " -p";
		map<AnsiString, AnsiString>::iterator it;
		for(it = params.begin(); it!=params.end(); ++it) {
			script += " " + it->first + "=\"" + it->second + "\"";
		}
	}
   // script += " -q";

    ExecuteScript(exe, script, credentials);

    delete saveDialog; 
}

void MiniReports::UpdateDocxReport(AnsiString reportName, map<AnsiString, AnsiString> &params,
         Credentials &credentials)
{
    AnsiString docxReportPath = ScriptsDirectory() + "docx\\" + reportName;
    TOpenDialog *openDialog = new TSaveDialog(NULL);

    TReplaceFlags flags;
    flags << rfReplaceAll;

    openDialog->Title = "Выберите файл для обновления";
    openDialog->FileName = "";
	openDialog->Filter = "docx | *.docx";
    openDialog->DefaultExt = ".docx";
	if(!openDialog->Execute()) {
       delete openDialog;
       return;
    }

    AnsiString exe = ScriptsDirectory() + "sql2docx.exe";
    AnsiString script;
	script.sprintf("\"%s\" -i \"%s\" -o \"%s\"",
					exe,
                    openDialog->FileName,
                    openDialog->FileName);

    if (params.size() > 0) {
		script += " -p";
		map<AnsiString, AnsiString>::iterator it;
		for(it = params.begin(); it!=params.end(); ++it) {
			script += " " + it->first + "=\"" + it->second + "\"";
		}
	}
    script += " -u -q";

    ExecuteScript(exe, script, credentials);

    delete openDialog; 
}

void MiniReports::GenReport(AnsiString reportName, map<AnsiString, AnsiString> &params,
         Credentials &credentials)
{
	AnsiString exe = ScriptsDirectory() + _sqltotxt;
	AnsiString inputDir = ScriptsDirectory() + "\\minireports\\" + reportName;

	TOpenDialog *openDialog = new TOpenDialog(NULL);
	openDialog->InitialDir = _lastOutputDir;
	openDialog->FileName = "this path is fine";
	openDialog->Options << ofNoValidate;
	openDialog->Filter = "Folder | *.";
	if(!openDialog->Execute()) {
       delete openDialog;
       return;
    }

	_lastOutputDir = ExcludeTrailingPathDelimiter(ExtractFileDir(openDialog->FileName));

    AnsiString outputPath = _lastOutputDir;
    if (params.count("RoadName")) {
        outputPath += "\\" + StringReplace(params["RoadName"], "\"", "", TReplaceFlags() << rfReplaceAll);
    }
    if (params.count("DistrictName")) {
        outputPath += "\\" + StringReplace(params["DistrictName"], "\"", "", TReplaceFlags() << rfReplaceAll);
    }
    
	AnsiString script;
	script.sprintf("\"%s\" -i \"%s\" -o \"%s\"",
					exe,
                    ExcludeTrailingPathDelimiter(inputDir),
                    outputPath);

	if (params.size() > 0) {
		script += " -p";
		map<AnsiString, AnsiString>::iterator it;
		for(it = params.begin(); it!=params.end(); ++it) {
			script += " " + it->first + "=\"" + it->second + "\"";
		}
	}

    ExecuteScript(exe, script, credentials);
	
	delete openDialog;                
}

void MiniReports::ExecuteScript(AnsiString appPath, AnsiString script, Credentials &credentials)
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	memset(&si, sizeof(si), 0);
	si.cb = sizeof(STARTUPINFO);
	memset(&pi, sizeof(pi), 0);

    AnsiString credentialsPath = ScriptsDirectory() + ".credentials";
    FILE* credentialsFile = fopen(credentialsPath.c_str(), "r");
    AnsiString output = "";
    while(!feof(credentialsFile)) {
        char s[256];
        fgets(s, 256, credentialsFile);
        /*if (AnsiString(s).Pos("UserID") || AnsiString(s).Pos("Password") ) {
            output += AnsiString(s);
        }*/
    }
    fclose(credentialsFile);
    credentialsFile = fopen(credentialsPath.c_str(), "w");
    output += "UserID: " + credentials.UserId + "\n";
    output += "Password: " + credentials.Password + "\n";
    output += "DataSource: " + credentials.DataSource + "\n";
    output += "InitialCatalog: " + credentials.InitialCatalog + "\n";
    fprintf(credentialsFile, output.c_str());
    fclose(credentialsFile);

    script += " -c \"" + credentialsPath + "\"";
    AnsiString bat = ScriptsDirectory() + "last_mini_report.bat";
    FILE *file = fopen( bat.c_str(), "w");
    fprintf(file, "chcp 1251\n");
    fprintf(file, script.c_str());
    fclose(file);

    WinExec( bat.c_str(), SW_SHOW );
    /*
    AnsiString batch = "/C " + bat;

	if( CreateProcessA( "cmd",   // No module name (use command line)
        batch.c_str(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) {
        WaitForSingleObject( pi.hProcess, INFINITE );
	    CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    } else {
		DWORD dw = GetLastError();
        ShowMessage(dw);
	} */
}

void MiniReports::LoadIni(TIniFile* ini)
{
	_lastOutputDir = ini->ReadString("MiniReports", "LastOutputDir", _applicationDir);
}

void MiniReports::SaveIni(TIniFile* ini)
{
	ini->WriteString("MiniReports", "LastOutputDir", _lastOutputDir);
}
