//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("GdiEForm.cpp", MainForm);
USEFORM("ObjForm.cpp", ObjFrm);
USEFORM("PenForm.cpp", PenEdit);
USEFORM("BrForm.cpp", BrushEdit);
USEFORM("ProcForm.cpp", ProcEdit);
USEFORM("SqlEdit.cpp", SqlEditFrm);
USEFORM("SettingFrm.cpp", FrmSetting);
USEFORM("VisCondE.cpp", VisCondEdit);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
       Application->CreateForm(__classid(TPenEdit), &PenEdit);
       Application->CreateForm(__classid(TBrushEdit), &BrushEdit);
       Application->CreateForm(__classid(TProcEdit), &ProcEdit);
       Application->CreateForm(__classid(TSqlEditFrm), &SqlEditFrm);
       Application->CreateForm(__classid(TVisCondEdit), &VisCondEdit);
       Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
