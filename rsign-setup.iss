; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppVersion GetDateTimeString('yyyymmdd', '', '');
#define MyAppName "RSign"
#define MyAppPublisher "ISTU"
#define MyAppExeName "RSign.exe"
#define MyDir "";

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{7518319D-13B7-4BA4-8F11-AAA6190EB8B5}

AppName={#MyAppName}
AppVersion="V{#MyAppVersion}"
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=".."
OutputBaseFilename=rsign-setup
Compression=lzma
SolidCompression=yes
UninstallDisplayIcon={app}\{#MyDir}RSign.ico

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#MyDir}RSign.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}GenRep.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}HTMLGenRep.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}LoginDB.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}Emfedit.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}GdiEdit.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}MoundHeights.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}RSign.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}GdiEdit.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyDir}PolyPat.ini"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#MyDir}RSign.ini"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#MyDir}README.md"; DestDir: "{app}"; Flags: ignoreversion
;Source: "{#MyDir}RSign.chm"; DestDir: "{app}"; Flags: ignoreversion

Source: "{#MyDir}ActiveX\*"; DestDir: "{app}\ActiveX\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}AutoCAD\*"; DestDir: "{app}\AutoCAD\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}Bitmap\*"; DestDir: "{app}\Bitmap\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}Data\*"; DestDir: "{app}\Data\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}DBFFiles\*"; DestDir: "{app}\DBFFiles\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}Help\*"; DestDir: "{app}\Help\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}Macroses\*"; DestDir: "{app}\Macroses\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}Query\*"; DestDir: "{app}\Query\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}VPatterns\*"; DestDir: "{app}\VPatterns\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}WMF\*"; DestDir: "{app}\WMF\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#MyDir}���������\*"; DestDir: "{app}\���������\"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{group}\������� RSign"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent