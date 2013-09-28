//---------------------------------------------------------------------------


#pragma hdrstop

#include "Document.h"
#include "MainUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TDocument::Show(void)
{
int res=(int)ShellExecute(MainForm->Handle,"open",FPath.c_str(),NULL,FPath.c_str(),SW_SHOWNORMAL);
if (res<=32)
    {
    String Error="����������� ������. ";
    switch (res)
        {
        case 0: Error="��� ��������� ��������� ������������ �������� �������. ";break;
        case ERROR_PATH_NOT_FOUND: Error="���� �� ������. ";break;
        case ERROR_FILE_NOT_FOUND: Error="���� �� ������. ";break;
        case ERROR_BAD_FORMAT: Error="�������� ������ �����. ";break;
        case SE_ERR_ACCESSDENIED: Error="������ � ����� ��������. ";break;
        case SE_ERR_ASSOCINCOMPLETE: Error="����������� ���������� �����. ";break;
        }
    ShowMessage(Error+FPath);
    }
}
