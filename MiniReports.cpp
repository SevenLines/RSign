//---------------------------------------------------------------------------


#pragma hdrstop

#include "MiniReports.h"
#include <SysUtils.hpp>
#include <FileCtrl.hpp>
#include <windows.h>
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

void MiniReports::GenReport(AnsiString reportName, map<AnsiString, AnsiString> params)
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
	script.sprintf("%s -i \"%s\" -o \"%s\"",
	exe, inputDir, _lastOutputDir);

	if (params.size() > 0) {
		script += " -p";
		map<AnsiString, AnsiString>::iterator it;
		for(it = params.begin(); it!=params.end(); ++it) {
			script += " " + it->first + "=" + it->second;
		}
	}
	
	ShowMessage(script);
	
	delete openDialog;                
}

void MiniReports::LoadIni(TIniFile* ini)
{
	_lastOutputDir = ini->ReadString("MiniReports", "LastOutputDir", _applicationDir);
}

void MiniReports::SaveIni(TIniFile* ini)
{
	ini->WriteString("MiniReports", "LastOutputDir", _lastOutputDir);
}
