#ifndef AutoCADExportHelper_H
#define AutoCADExportHelper_H

#include <Classes.hpp>
#include <Controls.hpp>
#include <CheckLst.hpp>
#include <IniFiles.hpp>
#include <vector>

using namespace std;

struct AutoCADTableRow
{
   AnsiString name;
   int iRow;
   bool fChecked;

   AnsiString toString();
};

class AutoCADTableRows
{

public:
   AutoCADTableRows();
   ~AutoCADTableRows();
   void saveToIni(TIniFile *ini, AnsiString Section, AnsiString Indent);
   void loadFromIni(TIniFile *ini, AnsiString Section, AnsiString Indent);
   vector<AutoCADTableRow> list;
};

class AutoCADTableRowsBinder : public AutoCADTableRows
{
public:
        AutoCADTableRowsBinder(TCheckListBox * lst = 0);
        ~AutoCADTableRowsBinder();
        void saveToIni(TIniFile *ini, AnsiString Section, AnsiString Indent);
        void loadFromIni(TIniFile *ini, AnsiString Section, AnsiString Indent);
private:
        TCheckListBox* listBox;
        
};


#endif
