#ifndef AutoCADExportHelper_CPP
#define AutoCADExportHelper_CPP

#include  "AutoCADExportHelper.h"


AnsiString AutoCADTableRow::toString()
{
  return name+"|"+IntToStr(iRow)+"|"+IntToStr(fChecked)+";";
}



AutoCADTableRows::AutoCADTableRows()
{

}


AutoCADTableRows::~AutoCADTableRows()
{

}


void AutoCADTableRows::saveToIni(TIniFile *ini, AnsiString Section, AnsiString Indent)
{
   AnsiString str = "";
   for(int i=0;i<list.size();i++) {
       str += list[i].toString();
   }
   ini->WriteString(Section, Indent, str);
}

void AutoCADTableRows::loadFromIni(TIniFile *ini, AnsiString Section, AnsiString Indent)
{
    AnsiString str = ini->ReadString(Section, Indent, "");
    
}


void AutoCADTableRowsBinder::saveToIni(TIniFile *ini, AnsiString Section, AnsiString Indent)
{

}

void AutoCADTableRowsBinder::loadFromIni(TIniFile *ini, AnsiString Section, AnsiString Indent)
{
}


AutoCADTableRowsBinder::AutoCADTableRowsBinder(TCheckListBox *lst)
{
        listBox = lst;                                                                        
}

AutoCADTableRowsBinder::~AutoCADTableRowsBinder()
{
}

#endif
 