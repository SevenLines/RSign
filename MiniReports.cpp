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

MiniReports::MiniReports() :
_directory("AutoCAD\\Scripts\\")
,_sqltotxt("sqltotxt.exe")
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
	AnsiString reportsDir = ScriptsDirectory() + "*";

	TSearchRec sr;
	vector<AnsiString> dirs;
	int iAttributes = faDirectory;
	if (FindFirst(reportsDir, iAttributes, sr) == 0)
	{
		do
		{
			if ((sr.Attr & iAttributes) == sr.Attr)
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

void MiniReports::GenReport(AnsiString reportName, map<AnsiString, AnsiString> params, Credentials &credentials)
{
	AnsiString exe = ScriptsDirectory() + _sqltotxt;
	AnsiString inputDir = ScriptsDirectory() + reportName;

	TOpenDialog *openDialog = new TOpenDialog(NULL);
	openDialog->InitialDir = _lastOutputDir;
	openDialog->FileName = "this path is fine";
	openDialog->Options << ofNoValidate;
	openDialog->Filter = "Folder | *.";
	if(!openDialog->Execute()) return;

	_lastOutputDir = ExtractFileDir(openDialog->FileName);
	AnsiString script;
	script.sprintf("\"%s\" -i \"%s\" -o \"%s\"",
					exe, inputDir, _lastOutputDir);

	if (params.size() > 0) {
		script += " -p";
		map<AnsiString, AnsiString>::iterator it;
		for(it = params.begin(); it!=params.end(); ++it) {
			script += " " + it->first + "=" + it->second;
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
    /*File credentialsFile = fopen(credentialsPath.c_str(), "w");
    fprintf(credentialsFile, "UserID: %s\n", credentials.UserID);
    fprintf(credentialsFile, "Password: %s\n", credentials.Password);
    fprintf(credentialsFile, "DataSource: %s\n", credentials.DataSource);
    fprintf(credentialsFile, "InitialCatalog: %s\n", credentials.InitialCatalog);
    fclose(credentialsFile);*/

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
