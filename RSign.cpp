//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <atl\atlmod.h>
#include "RoadViewImpl.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include "without_autocad.h"

USEFORM("MainUnit.cpp", MainForm);
USEFORM("ShowRoad.cpp", RoadFrm);
USEFORM("ListForm.cpp", ListFrm);
USEFORM("ObjForm.cpp", ObjFrm);
USEFORM("DrawSetting.cpp", DrwSetFrm);
USEFORM("OpenRoad.cpp", OpenRoadDialog);
USEFORM("SelNewSign.cpp", AddSignFrm);
USEFORM("bmpexport.cpp", BmpParam);
USEFORM("PrnForm.cpp", PrnParam);
USEFORM("VPatView.cpp", VPatFrm);
USEFORM("SelNewObj.cpp", AddObjFrm);
USEFORM("PreView.cpp", PreViewFrm);
USEFORM("SetSigns.cpp", frmSetSigns);
USEFORM("CheckSigns.cpp", frmCheckSigns);
USEFORM("SignsReports.cpp", frmSignsReports);
USEFORM("OpenSource.cpp", OpenSourceDialog);
USEFORM("AddProject.cpp", AddProjectForm);
USEFORM("SettingFrm.cpp", FrmSetting);
USEFORM("PolyForm.cpp", PolyFrm);
USEFORM("MetaExport.cpp", MetaParam);
USEFORM("ShowSigns.cpp", SignForm);
USEFORM("Picture.cpp", PictureForm);
USEFORM("VideoForm.cpp", frmVideoForm);
USEFORM("DumpForm.cpp", DumpDialog);
USEFORM("ProgressFrm.cpp", ProgressForm);
USEFORM("CrvPlanForm.cpp", frmCrvPlan);
USEFORM("VisSetForm.cpp", VisSetFrm);
USEFORM("SaveViewForm.cpp", SaveViewFrm);
USEFORM("OpenViewForm.cpp", OpenViewFrm);
USEFORM("NewView.cpp", NewViewDialog);
USEFORM("MacrosForm.cpp", frmMacros);
USEFORM("ConstHelp.cpp", frmConstHelp);
USEFORM("BuildSlopes.cpp", frmBuildSlopes);
USEFORM("BuildWidePart.cpp", frmWidePartDialog);
USEFORM("RoadMark.cpp", frmMarkParam);
USEFORM("ErrorObjectDlg.cpp", ErrorObjectDialog);
USEFORM("AutoCADPrintForm.cpp", FAutoCADPrint);
USEFORM("AutoCADExportForm.cpp", FAutoCADExport);
USEFORM("unSignalsInsert.cpp", frmSignalsInsert);
USEFORM("AttachForm.cpp", frmAttachParams);
USEFORM("MoveForm.cpp", moveDialog);
USEFORM("AddRowsDescription.cpp", FAddRowDescription);
USEFORM("ItemSelectDialog.cpp", ItemSelectDialogForm);
USEFORM("ConnectionFormUnit.cpp", ConnectionForm);
//---------------------------------------------------------------------------
#ifndef WITHOUT_AUTOCAD
USEFORM("AutoCADPrintForm.cpp", FAutoCADPrint);
#endif
USEFORM("AutoCADExportForm.cpp", FAutoCADExport);
USEFORM("unSignalsInsert.cpp", frmSignalsInsert);
USEFORM("AttachForm.cpp", frmAttachParams);
USEFORM("MoveForm.cpp", moveDialog);
USEFORM("AddRowsDescription.cpp", FAddRowDescription);
//---------------------------------------------------------------------------
TComModule _ProjectModule(0 /*InitATLServer*/);
TComModule &_Module = _ProjectModule;


// The ATL Object map holds an array of _ATL_OBJMAP_ENTRY structures that
// described the objects of your OLE server. The MAP is handed to your
// project's CComModule-derived _Module object via the Init method.
//
BEGIN_OBJECT_MAP(ObjectMap)
  OBJECT_ENTRY(CLSID_RoadView, TRoadViewImpl)
END_OBJECT_MAP()
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // redirect output to the file
//    std::ofstream out("RSign.log", std::ios_base::out | std::ios_base::app );
    std::ofstream out("RSign.log", std::ios_base::app);
    // save old values
    std::streambuf *stdCerr = std::cerr.rdbuf();
    std::streambuf *stdCout = std::cout.rdbuf();

    // redirect
    std::cout.rdbuf(out.rdbuf());
    std::cerr.rdbuf(out.rdbuf());
    
    std::cout << std::endl << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
    std::cout << "[" << Now().DateTimeString().c_str() << "] Начало сеанса RSign" << std::endl;
    
    try
    {
       Application->Initialize();
       Application->Title = "RSign";
       Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TVPatFrm), &VPatFrm);
         Application->CreateForm(__classid(TDrwSetFrm), &DrwSetFrm);
         Application->CreateForm(__classid(TOpenRoadDialog), &OpenRoadDialog);
         Application->CreateForm(__classid(TAddSignFrm), &AddSignFrm);
         Application->CreateForm(__classid(TBmpParam), &BmpParam);
         Application->CreateForm(__classid(TPrnParam), &PrnParam);
         Application->CreateForm(__classid(TAddObjFrm), &AddObjFrm);
         Application->CreateForm(__classid(TPreViewFrm), &PreViewFrm);
         Application->CreateForm(__classid(TfrmSetSigns), &frmSetSigns);
         Application->CreateForm(__classid(TfrmCheckSigns), &frmCheckSigns);
         Application->CreateForm(__classid(TfrmSignsReports), &frmSignsReports);
         Application->CreateForm(__classid(TOpenSourceDialog), &OpenSourceDialog);
         Application->CreateForm(__classid(TAddProjectForm), &AddProjectForm);
         Application->CreateForm(__classid(TFrmSetting), &FrmSetting);
         Application->CreateForm(__classid(TPolyFrm), &PolyFrm);
         Application->CreateForm(__classid(TMetaParam), &MetaParam);
         Application->CreateForm(__classid(TSignForm), &SignForm);
         Application->CreateForm(__classid(TPictureForm), &PictureForm);
         Application->CreateForm(__classid(TDumpDialog), &DumpDialog);
         Application->CreateForm(__classid(TProgressForm), &ProgressForm);
         Application->CreateForm(__classid(TfrmCrvPlan), &frmCrvPlan);
         Application->CreateForm(__classid(TfrmVideoForm), &frmVideoForm);
         Application->CreateForm(__classid(TSaveViewFrm), &SaveViewFrm);
         Application->CreateForm(__classid(TOpenViewFrm), &OpenViewFrm);
         Application->CreateForm(__classid(TNewViewDialog), &NewViewDialog);
         Application->CreateForm(__classid(TSaveViewFrm), &SaveViewFrm);
         Application->CreateForm(__classid(TOpenViewFrm), &OpenViewFrm);
         Application->CreateForm(__classid(TNewViewDialog), &NewViewDialog);
         Application->CreateForm(__classid(TfrmMacros), &frmMacros);
         Application->CreateForm(__classid(TfrmConstHelp), &frmConstHelp);
         Application->CreateForm(__classid(TfrmConstHelp), &frmConstHelp);
         Application->CreateForm(__classid(TfrmMacros), &frmMacros);
         Application->CreateForm(__classid(TfrmConstHelp), &frmConstHelp);
         Application->CreateForm(__classid(TfrmBuildSlopes), &frmBuildSlopes);
         Application->CreateForm(__classid(TfrmWidePartDialog), &frmWidePartDialog);
         Application->CreateForm(__classid(TfrmMarkParam), &frmMarkParam);
         Application->CreateForm(__classid(TErrorObjectDialog), &ErrorObjectDialog);
         Application->CreateForm(__classid(TFAutoCADPrint), &FAutoCADPrint);
         Application->CreateForm(__classid(TFAutoCADPrint), &FAutoCADPrint);
         Application->CreateForm(__classid(TFAutoCADExport), &FAutoCADExport);
         Application->CreateForm(__classid(TfrmSignalsInsert), &frmSignalsInsert);
         Application->CreateForm(__classid(TfrmAttachParams), &frmAttachParams);
         Application->CreateForm(__classid(TfrmAttachParams), &frmAttachParams);
         Application->CreateForm(__classid(TmoveDialog), &moveDialog);
         Application->CreateForm(__classid(TmoveDialog), &moveDialog);
         Application->CreateForm(__classid(TFAddRowDescription), &FAddRowDescription);
         Application->CreateForm(__classid(TFAddRowDescription), &FAddRowDescription);
         Application->CreateForm(__classid(TConnectionForm), &ConnectionForm);
         Application->CreateForm(__classid(TConnectionForm), &ConnectionForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    // restore buffers
    std::cout << "[" << Now().DateTimeString().c_str() << "] Завершение сеанса" << std::endl;
    std::cout.rdbuf(stdCout);
    std::cerr.rdbuf(stdCerr);
    // close file
    out.close();
    return 0;
}
//---------------------------------------------------------------------------
