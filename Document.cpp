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
    String Error="Неизвестная ошибка. ";
    switch (res)
        {
        case 0: Error="Для просмотра документа недостаточно ресурсов системы. ";break;
        case ERROR_PATH_NOT_FOUND: Error="Путь не найден. ";break;
        case ERROR_FILE_NOT_FOUND: Error="Файл не найден. ";break;
        case ERROR_BAD_FORMAT: Error="Неверный формат файла. ";break;
        case SE_ERR_ACCESSDENIED: Error="Доступ к файлу запрещен. ";break;
        case SE_ERR_ASSOCINCOMPLETE: Error="Неизвестное расширение файла. ";break;
        }
    ShowMessage(Error+FPath);
    }
}
