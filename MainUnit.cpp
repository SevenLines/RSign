//---------------------------------------------------------------------------
#include <vcl.h>
#include <htmlhelp.h>
#include <systdate.h>
#include <iostream>
#pragma hdrstop

#include "MickMacros.h"
#include "MainUnit.h"
#include "OpenRoad.h"
#include "OpenSource.h"
#include "ShowRoad.h"
#include "FileSour.h"
#include "DBDataSource.h"
//#include "ShowVideo.h"
#include "SetSigns.h"
#include "CheckSigns.h"
#include "SignsReports.h"
#include "SignsReports.h"
#include "VPatView.h"
#include "AddProject.h"
#include "SettingFrm.h"
#include "ShowSigns.h"
#include "DumpForm.h"
#include "CrvPlanForm.h"
#include "SaveViewForm.h"
#include "OpenViewForm.h"
#include "NewView.h"
#include "DesignPattern.h"
#include "MacrosForm.h"
#include "ConstHelp.h"
#include "MiniReports.h"
#include <iostream>

#include "without_autocad.h"
#include "AutoCADPrintForm.h"
#include "ItemSelectDialog.h"
#include "ConnectionFormUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
void *HelpLib=NULL;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
: TForm(Owner)
{
	PrepareMinireports();
}
__fastcall TMainForm::~TMainForm(void)
{
	if (HelpLib)
	FreeLibrary(HelpLib);
}

void __fastcall TMainForm::PrepareMinireports()
{
	vector<AnsiString> reports = MiniReportsSingleton.GetReports();
	ItemMiniReports->Clear();
	for(int i=0; i<reports.size(); ++i) {
		TMenuItem *item = new TMenuItem(this);
		item->Caption = reports[i];
		item->OnClick = ItemMiniReportsClick;
		ItemMiniReports->Add(item);
	}
}

void __fastcall TMainForm::ItemMiniReportsClick(TObject *Sender)
{
	if (FActiveRoad) {
		TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
		if (!item) return;
		std::map<AnsiString, AnsiString> params;
		params["NumRoad"] = FActiveRoad->RoadId;
        params["RoadName"] = FActiveRoad->RoadName;
        params["DistrictName"] = FActiveRoad->DistrictName;

        map<AnsiString, AnsiString> sources;
		for (int i=0,j=0;i<ResManager->DataCount;i++) {
			TDtaSource *Dta=MainForm->ResManager->Data[i];
			if (Dta && Dta->Id == FActiveRoad->RoadId) {
                sources[Dta->SourceName] = Dta->DataClass;
                break;
			}	
		}
        if (sources.size() > 1) {
            ItemSelectDialogForm->setOptions(sources, "Выбирете необходимый источник");
            if (ItemSelectDialogForm->ShowModal() != mrOk) return;
            params["NumDataSource"] = ItemSelectDialogForm->selectedItem();
        } else if (sources.size() > 0) {
            params["NumDataSource"] = sources.begin()->second;
        } else {
            ShowMessage("Не было найдено источников, честно говоря, вообще не понятно как вы дорогу открыли");
            return;
        }

        MiniReports::Credentials credentials(Connection->ConnectionString);
        //MiniReportsSingleton.SetCredentials();

		MiniReportsSingleton.GenReport(item->Caption, params, credentials);
	}
}

void __fastcall TMainForm::AppShortCut(TWMKey &Key, bool &Handled)
{
	int key=Key.CharCode;
	if (GetKeyState(18)&0x8000)  // Нажата ли кнопка alt
	key+=0x8000;
	else if (GetKeyState(17)&0x8000)   //нажата ли кнопка ctrl
	key+=0x4000;
	TMacros *Macros=frmMacros->GetMacros(key);
	if (Macros)
	{
		Macros->Execute();
		Handled=true;
	}
	else if (FActiveRoad)
	if (FActiveRoad->Active)
	FActiveRoad->RoadKeyPress(Key);
}


void __fastcall TMainForm::ReadIni(TIniFile *ini)
{
    ConnectionForm->loadIni(ini);

	String connectionString = ini->ReadString("Connection","ConnectionString", "");
    if (connectionString!=Connection->ConnectionString && !connectionString.IsEmpty())  {
        Connection->Close();
        int pass = connectionString.Pos("Password");
        // if password not present in current connection string, use password from connection form
        if (pass == 0) {
            String password = ini->ReadString("ConnectionForm", "Password", "");
            if (!password.IsEmpty()) {
                int userIdPos = connectionString.Pos("User ID");
                if (!userIdPos) userIdPos = connectionString.Pos("UserID");
                
                if (userIdPos) {
                    connectionString.Insert("Password=" + password + ";", userIdPos);
                }
            }
        }
  	    Connection->ConnectionString = connectionString;
        Connection->Open();
        ConnectionForm->Connection = Connection;
    }

	Left=ini->ReadInteger("MainForm","Left",Left);
	Top=ini->ReadInteger("MainForm","Top",Top);
	String PatName=ini->ReadString("PrintPattern","Name","").Trim();
	ini->ReadSectionValues("Cheefs",CheefList);
	VideoServers->CommaText=ini->ReadString("Video","Servers","");
	if (PatName!="")
	    if (Pattern->LoadFromFile(PatName))
	        VPatFrm->FileName=PatName;

}

void __fastcall TMainForm::WriteIni(TIniFile *ini)
{
	ini->WriteString("Connection","ConnectionString",Connection->ConnectionString);
	ini->WriteInteger("MainForm","Left",Left);
	ini->WriteInteger("MainForm","Top",Top);
	ini->WriteString("PrintPattern","Name",VPatFrm->FileName);
	ini->WriteString("Video","Servers",VideoServers->CommaText);
    ConnectionForm->saveIni(ini);
}

void __fastcall TMainForm::LoadIni(void)
{
	TIniFile *ini=new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
	ReadIni(ini);
	OpenRoadDialog->LoadIni(ini);
	MiniReportsSingleton.LoadIni(ini);
	delete ini;
}

void __fastcall TMainForm::SaveIni(void)
{
	String FName=ChangeFileExt(Application->ExeName,".ini");
	if ((!FileIsReadOnly(FName))||(!FileExists(FName))) {
		TIniFile *ini=new TIniFile(FName);
		WriteIni(ini);
		OpenRoadDialog->SaveIni(ini);
		MiniReportsSingleton.SaveIni(ini);
		delete ini;
	}
}

void __fastcall TMainForm::SetActiveRoad(TRoadFrm *R)
{
	//N61->Enabled=!(Connection->Connected);
	if (R!=FActiveRoad)
	{
		FActiveRoad=R;
		if (FActiveRoad)
		    FActiveRoad->PostChangeFocus();
		else
		{
			N3->Enabled=false;
			N5->Enabled=false;
			N6->Enabled=false;
			N19->Enabled=false;
			N14->Enabled=false;
			N16->Enabled=false;
			N17->Enabled=false;
			N18->Enabled=false;
			N47->Enabled=false;
			N21->Enabled=false;
			N22->Enabled=false;
			N24->Enabled=false;
			N25->Enabled=false;
			N26->Enabled=false;
			N32->Enabled=false;
			N33->Enabled=false;
			N34->Enabled=false;
			N35->Enabled=false;
			N37->Enabled=false;
			N38->Enabled=false;
			N39->Enabled=false;
			N41->Enabled=false;
			N43->Enabled=false;
			N45->Enabled=false;
			N46->Enabled=false;
			N48->Enabled=false;
			N49->Enabled=false;
			N50->Enabled=false;
			N50->Checked=false;
			N74->Enabled=false;
			N74->Checked=false;
			N75->Enabled=false;
			N75->Checked=false;
			N81->Enabled=false;
			N81->Checked=false;
			N59->Enabled=false;
			PrevObjBut->Enabled=false;
			NextObjBut->Enabled=false;
			AutoDesignBut->Enabled=false;
			AddDangBut->Enabled=false;
			AddSignBut->Enabled=false;
			AttDesignBut->Enabled=false;
			RMDesignBut->Enabled=false;
			ShowDocBut->Enabled=false;
			N63->Enabled=false;
			N70->Enabled=false;
			ItemMiniReports->Enabled=false;
			N71->Enabled=false;
			N76->Enabled=false;
		}
		SendBroadCastMessage(CM_ONACTIVATEROADWIN,(int)R,0);
	}
}

void __fastcall TMainForm::SendBroadCastMessage(int Command,int Wpar,int Lpar)
{
	for (int i=0;i<Application->ComponentCount;i++)
	{
		TCustomForm *Frm=dynamic_cast<TCustomForm*>(Application->Components[i]);
		if (Frm)
		    SendMessage(Frm->Handle,Command,Wpar,Lpar);
	}
}

void __fastcall TMainForm::PostBroadCastMessage(int Command,int Wpar,int Lpar)
{
	for (int i=0;i<Application->ComponentCount;i++)
	{
		TCustomForm *Frm=dynamic_cast<TCustomForm*>(Application->Components[i]);
		if (Frm)
		    PostMessage(Frm->Handle,Command,Wpar,Lpar);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::WndProc(TMessage &Mes)
{
	TForm::WndProc(Mes);
}

TRoadFrm* __fastcall TMainForm::FindRoad(__int32 id,__int32 dataclass)
{
	for (int i=0;i<Application->ComponentCount;i++)
	{
		TRoadFrm *Frm = dynamic_cast<TRoadFrm*>(Application->Components[i]);
		if (Frm)
		    if ((Frm->RoadId==id)&&(Frm->VisSet->SourceVisible(dataclass)))
		        return Frm;
	}
	return NULL;
}

void __fastcall TMainForm::SetVideoPos(__int32 pos)
{
	if (FActiveRoad)
	FActiveRoad->SetVideoPos(pos);
}

bool __fastcall TMainForm::OpenRoadById(__int32 id,__int32 dataclass,bool OpenCopy)
{
	TRoadFrm *frm=FindRoad(id,dataclass);
	bool res(false);
	if (OpenCopy||!frm)
	{
		if (!Shared)
		{
			Shared=new TDBSharedObjSource(Connection);
			Shared->Load();
		}

		//    int SourType=DBDataModule->GetSourceType(dataclass);
		TDictSource *Dict=ResManager->AddDictSource(0,Connection);
		TDtaSource *Data;
		String Capt=DBDataModule->GetRoadName(id).Trim()+String(" : ")+DBDataModule->GetSourceName(dataclass).Trim();
		Data=ResManager->AddDataSource(Capt,id,dataclass,0,Connection,Factory);
		if (Data)
		{
			Application->CreateForm(__classid(TRoadFrm), &frm);
			frm->OpenRoad(Capt,Data,Dict,Shared);
			frm->Show();
			ResManager->ReleaseDataSource(Data); // Теперь источником владеет окно
			res=true;
		}
	}
	return res;
}

bool __fastcall TMainForm::CloseRoad(__int32 id,__int32 dataclass)
{
	TRoadFrm *Frm=FindRoad(id,dataclass);
	if (Frm)
	    Frm->Close();
	return true;
}

bool __fastcall TMainForm::ActivateRoad(__int32 id,__int32 dataclass)
{
	bool res(false);
	TRoadFrm *Frm=FindRoad(id,dataclass);
	if (Frm)
	{
		Frm->Show();
		res=true;
	}
	return res;
}

bool __fastcall TMainForm::IsRoadOpen(__int32 id,__int32 dataclass)
{
	bool res(false);
	if (FindRoad(id,dataclass))
	res=true;
	return res;
}

bool __fastcall TMainForm::ShowRoadObject(__int32 RoadId,__int32 dataclass,__int32 ObjId)
{
	bool res(false);
	TRoadFrm *Frm=FindRoad(RoadId,dataclass);
	if (Frm)
	{
		for (int i=0;i<ResManager->DataCount;i++)
		{
			TDtaSource *Dta=ResManager->Data[i];
			if ((Dta->Id==RoadId)&&(Dta->DataClass==dataclass))
			{
				TRoadObject *Obj=Dta->FindObject(ObjId);
				if (Obj)
				{
					Frm->ActivateObject(Obj,Dta);
					res=true;
				}
			}
		}
	}
	return res;
}

bool __fastcall TMainForm::ShowRoadPart(__int32 RoadId,__int32 dataclass,__int32 StartPos,__int32 EndPos)
{
	bool res(false);
	TRoadFrm *Frm=FindRoad(RoadId,dataclass);
	if (Frm)
	{
		Frm->ShowRoadPart(StartPos*100,EndPos*100);
		res=true;
	}
	return res;
}

void __fastcall TMainForm::OpenRoad(TObject *Sender)
{
	if (OpenRoadDialog->ShowModal()==mrOk)
	{
		OpenSourceDialog->RoadId=OpenRoadDialog->RoadId;
		if (OpenSourceDialog->ShowModal()==mrOk)
		{
			BUILDER_INFO( "Открываю источник: "
			<< OpenRoadDialog->RoadName.Trim().c_str()
			<< " [id:" << OpenRoadDialog->RoadId << "]"
			<< " источник: " << OpenSourceDialog->DataSource );
			OpenRoadById(OpenRoadDialog->RoadId,OpenSourceDialog->DataSource,true);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	Application->OnShortCut=AppShortCut;
	Shared=NULL;
	HaveInit=false;
	ResManager=new TResManager;
	Factory=new TRoadObjFactory;
	Pattern=new TDrawPattern;
	DBDataModule=new TDBDataModule(Connection);
	VideoServers=new TStringList;
	CheefList=new TStringList;
	Left=0;
	Top=0;
	FActiveRoad=(TRoadFrm*)1;
	SetActiveRoad(NULL);
	SignPanel=new TSignPanel(this);
	SignPanel->Left=AddSignBut->Left+AddSignBut->Width;
	SignPanel->Top=0;
	SignPanel->SetSigns(10,BtnPropMode->Width);
	SignPanel->Parent=this;
	FCurAttachDesigner=0;
	for (int i=0;i<DesignersCount;i++)
	{
		TMenuItem* it=new TMenuItem(DesignersList);
		it->Tag=i;
		it->Caption=DesignersName[i];
		it->OnClick=SetDesigner;
		it->RadioItem=true;
		DesignersList->Items->Add(it);
	}
}

void __fastcall TMainForm::SetDesigner(TObject *Send)
{
	TMenuItem *it=dynamic_cast<TMenuItem*>(Send);
	if (it)
	{
		FCurAttachDesigner=it->Tag;
		it->Checked=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	while (_Module.GetLockCount()>0)
	_Module.Unlock();
	SaveIni();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N14Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		ActiveRoad->ShowParam();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N17Click(TObject *Sender)
{
	if (FActiveRoad)
	FActiveRoad->DeleteActiveObject(false);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N19Click(TObject *Sender)
{
	if (FActiveRoad)
	if (ResManager->DataCount)
	{
		DumpDialog->DataSrcList->Items->Clear();
		for (int i=0;i<ResManager->DataCount;i++)
		{
			TDtaSource *Dta=ResManager->Data[i];
			DumpDialog->DataSrcList->Items->AddObject(Dta->RoadName+" : "+Dta->SourceName,Dta);
		}
		DumpDialog->SetCurrentData(ResManager->Data[0]);
		DumpDialog->CurrentDict=FActiveRoad->Dict;
		DumpDialog->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N20Click(TObject *Sender)
{
	if (OpenDump->Execute())
	{
		if (Shared==NULL)
		{
			Shared=new TFileSharedObjSource;
			Shared->Load();
		}
		TRoadFrm *frm;
		Application->CreateForm(__classid(TRoadFrm), &frm);
		TDictSource *Dict=ResManager->AddFileDictSource(0);
		TDtaSource *Data=ResManager->AddFileDataSource(OpenDump->FileName,0,Factory);
		String Capt=Data->RoadName.Trim()+String(" : ")+Data->SourceName.Trim();
		frm->OpenRoad(Capt,Data,Dict,Shared);
		ResManager->ReleaseDataSource(Data); // Теперь источником владеет окно    
		frm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N16Click(TObject *Sender)
{
	if  (FActiveRoad)
	    FActiveRoad->AddNewSign();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N3Click(TObject *Sender)
{
	if (ActiveRoad)
	    ActiveRoad->SaveData();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N21Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		FActiveRoad->BmpExportDialog();

		/*    if (BmpParam->ShowModal()==mrOk)
		{
		int skm=BmpParam->MinKm->Position*100000;
		int ekm=BmpParam->MaxKm->Position*100000;
		int plen=BmpParam->PLen->Position*100000;
		int lms=BmpParam->ScaleL->Text.ToInt();
		int xms=BmpParam->ScaleX->Text.ToInt();
		int dpi=BmpParam->Dpi->Text.ToInt();
		FActiveRoad->BmpExport(BmpParam->Edit1->Text,skm,ekm,plen,lms,xms,dpi);
		}
*/        
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N22Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->PrintDialog();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N24Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		frmSignsReports->Execute(FActiveRoad);
	}
	else
	ShowMessage("Не выбрана дорога. Для продолжения выберите дорогу.");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N31Click(TObject *Sender)
{
	if (VPatFrm->ShowModal()==mrOk)
	{
		Pattern->LoadFromFile(VPatFrm->FileName);
	}
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::N32Click(TObject *Sender)
{
	if  (FActiveRoad)
	    FActiveRoad->AddNewObject();
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::N41Click(TObject *Sender)
{
	if (FActiveRoad)
	if (FActiveRoad->EditedData)
	{
		if (ActiveRoad->EditedData->ReadOnly)
		ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
		else
		frmSetSigns->Show();
	}
	else
	ShowMessage("Не выбрана дорога. Для продолжения выберите дорогу.");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N39Click(TObject *Sender)
{
	if (ActiveRoad)
	{
		ActiveRoad->VisSet->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N33Click(TObject *Sender)
{
	if (ActiveRoad)
	{
		ActiveRoad->ScaleL(SQRT2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N34Click(TObject *Sender)
{
	if (ActiveRoad)
	{
		ActiveRoad->ScaleL(1/SQRT2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N35Click(TObject *Sender)
{
	if (ActiveRoad)
	{
		ActiveRoad->ShowAll();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N38Click(TObject *Sender)
{
	if (ActiveRoad)
	    ActiveRoad->ChangeOrientation();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N37Click(TObject *Sender)
{
	if (ActiveRoad)
	    ActiveRoad->ChangeDirection();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N42Click(TObject *Sender)
{
	typedef void (*HelpFunc)(void*,char*,int,void*);
	HelpFunc HtHelp;
	if (!HelpLib)
	    HelpLib=LoadLibrary("hhctrl.ocx");
	if (HelpLib)
	{
		HtHelp=(HelpFunc)GetProcAddress(HelpLib,"HtmlHelpA");
		if (HtHelp)
		    HtHelp(Handle,HelpFile.c_str(),HH_DISPLAY_TOPIC,NULL);
		else
		    ShowMessage("Не удается найти функцию отображения справки. Возможно библиотека hhctrl.ocx изменена или испорчена.");
	}
	else
	ShowMessage("Не удается найти библиотеку hhctrl.ocx.");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N43Click(TObject *Sender)
{
	if (this->ActiveRoad)
	    frmCheckSigns->Show();
	else
	    ShowMessage("Не выбрана дорога. Для продолжения выберите дорогу.");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender)
{
	if (ActiveRoad)
	    ActiveRoad->ReLoadData();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N6Click(TObject *Sender)
{
	if (ActiveRoad)
	    OpenRoadById(ActiveRoad->RoadId,0,true);
}
//---------------------------------------------------------------------------

int __fastcall TMainForm::AddProject(__int32 RoadNum)
{
	int res=-1;
	AddProjectForm->RoadName->Text=DBDataModule->GetRoadName(RoadNum);
	if (AddProjectForm->ShowModal()==mrOk)
	{
		res=DBDataModule->AddProject(RoadNum,AddProjectForm->ProjName->Text,AddProjectForm->OrgName->KeyValue,
		AddProjectForm->ExecName->Text,AddProjectForm->ExamName->Text);
	}
	return res;
}

void __fastcall TMainForm::N27Click(TObject *Sender)
{
	if (OpenRoadDialog->ShowModal()==mrOk)
	{
		int NumSource=AddProject(OpenRoadDialog->RoadId);
		if (NumSource>=0)
		{
			OpenRoadById(OpenRoadDialog->RoadId,NumSource,true);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N25Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->DeleteActiveObject(true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N26Click(TObject *Sender)
{
	if (ActiveRoad)
	    if (ActiveRoad->EditedData)
	        ActiveRoad->EditedData->CopySelectedObjects(ActiveRoad->Dict);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N28Click(TObject *Sender)
{
	FrmSetting->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PrevObjButClick(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->PredObject();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NextObjButClick(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->NextObject();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AutoDesignButClick(TObject *Sender)
{
	if (FActiveRoad)
      if (FActiveRoad->EditedData)
      {
          if (FActiveRoad->EditedData->ReadOnly)
          ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
          else
          FActiveRoad->QuickDesign();
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N46Click(TObject *Sender)
{
	if (FActiveRoad)
      if (FActiveRoad->EditedData)
      {
          if (ActiveRoad->EditedData->ReadOnly)
            ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
          else
            FActiveRoad->SetAllSigns();
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
	if (!HaveInit)
	{
		LoadIni();
		HaveInit=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N45Click(TObject *Sender)
{
	if (FActiveRoad)
      if (FActiveRoad->EditedData)
      {
          if (ActiveRoad->EditedData->ReadOnly)
            ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
          else
            FActiveRoad->SetKmSigns();
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddSignButClick(TObject *Sender)
{
	if (FActiveRoad)
      if (FActiveRoad->EditedData)
      {
          if (ActiveRoad->EditedData->ReadOnly)
              ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
          else
              FActiveRoad->AddNewSign();
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddDangButClick(TObject *Sender)
{
	if (FActiveRoad)
      if (FActiveRoad->EditedData)
      {
          if (ActiveRoad->EditedData->ReadOnly)
            ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
          else
            FActiveRoad->AddNewObject(DANGERPARTCODE);
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N18Click(TObject *Sender)
{
	if (FActiveRoad) {
		TMenuItem *m=dynamic_cast<TMenuItem*>(Sender);
		if (m) {
			if (m->Tag>=100 && m->Tag<200)
			    FActiveRoad->ShowVideo(1,m->Tag-100);
			else
			    FActiveRoad->ShowVideo(1,-1);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N47Click(TObject *Sender)
{
	if (FActiveRoad) {
		TMenuItem *m=dynamic_cast<TMenuItem*>(Sender);
		if (m) {
			if (m->Tag>=100 && m->Tag<200)
			    FActiveRoad->ShowVideo(2,m->Tag-100);
			else
			    FActiveRoad->ShowVideo(2,-1);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N12Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->BuildRoadLines();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AttDesignButClick(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->DesignAttach();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N48Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->MetaExportDialog();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N49Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		SignForm->PageIndex=FActiveRoad->CurPage;
		SignForm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N50Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->ShowProfil();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N51Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->ShowDress();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N52Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->LongSlopesPartDialog();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N54Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		frmCrvPlan->Initialize(FActiveRoad->CurveData,FActiveRoad->Dict);
		frmCrvPlan->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListObjectClick(TObject *Sender)
{
	TMenuItem *It=dynamic_cast<TMenuItem*>(Sender);
	if (It)
	{
		TListFrm *Frm=ResManager->GetListFrm(It->Tag);
		if (Frm)
		    Frm->Show();
	}
}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete Shared;
	delete ResManager;
	delete Factory;
	delete Pattern;
	delete DBDataModule;
	delete VideoServers;
	delete CheefList;
	Shared=NULL;
	ResManager=NULL;
	Factory=NULL;
	Pattern=NULL;
	DBDataModule=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N59Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		SaveViewFrm->RoadId=FActiveRoad->RoadId;
		if (SaveViewFrm->ShowModal()==mrOk)
		{
			DBDataModule->SaveView(FActiveRoad,SaveViewFrm->ViewId,SaveViewFrm->ViewName);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N58Click(TObject *Sender)
{
	if (OpenRoadDialog->ShowModal()==mrOk)
	{
		OpenViewFrm->RoadId=OpenRoadDialog->RoadId;
		if (OpenViewFrm->ShowModal()==mrOk)
		{
			BUILDER_INFO( "Открываю вид: "
			<< OpenRoadDialog->RoadName.Trim().c_str()
			<< " [id:" << OpenRoadDialog->RoadId << "]"
			<< " вид: " << OpenViewFrm->ViewId );
			try {
				if (!Shared)
				{
					Shared=new TDBSharedObjSource(Connection);
					Shared->Load();
				}
				TDictSource *Dict=ResManager->AddDictSource(0,Connection);
				TRoadFrm *frm;
				Application->CreateForm(__classid(TRoadFrm), &frm);
				frm->OpenView(OpenViewFrm->RoadId,OpenViewFrm->ViewId,Dict,Shared);
				frm->Show();
			}  catch(...) {
				std::cerr << "ошибка при открытии дороги" << std::endl;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N57Click(TObject *Sender)
{
	if (OpenRoadDialog->ShowModal()==mrOk)
	{
		int RoadId=OpenRoadDialog->RoadId;
		NewViewDialog->RoadId=RoadId;
		if (NewViewDialog->ShowModal()==mrOk)
		{
			if (!Shared)
			{
				Shared=new TDBSharedObjSource(Connection);
				Shared->Load();
			}
			TDictSource *Dict=ResManager->AddDictSource(0,Connection);
			TRoadFrm *frm;
			Application->CreateForm(__classid(TRoadFrm), &frm);
			TDtaSource **Datas=new TDtaSource* [NewViewDialog->SourcesCount];
			for (int i=0;i<NewViewDialog->SourcesCount;i++)
			{
				__int32 Num=NewViewDialog->DataSource[i];
				String Capt=DBDataModule->GetRoadName(RoadId).Trim()+String(" : ")+DBDataModule->GetSourceName(Num).Trim();
				Datas[i]=ResManager->AddDataSource(Capt,RoadId,Num,0,Connection,Factory);
			}
			frm->OpenRoad(RoadId,Dict,Shared);
			for (int i=0;i<NewViewDialog->SourcesCount;i++)
			{
				frm->VisSet->SetSourceVisible(Datas[i],true);
				ResManager->ReleaseDataSource(Datas[i]);
			}
			delete Datas;
			frm->Show();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N61Click(TObject *Sender)
{
    if (FActiveRoad) {
    	ShowMessage("Перед установкой подключения необходимо закрыть все открытые дороги");
        return;
    }

    ConnectionForm->Connection = Connection;
    ConnectionForm->ShowModal();

	/*if (FActiveRoad)
	ShowMessage("Перед установкой подключения необходимо закрыть все открытые дороги");
	else
	{
		HINSTANCE dll;
		typedef int (*ConnectFunc)(char*, LPCSTR, LPCSTR);
		ConnectFunc LoginDB;
		char str[1024];
		dll = LoadLibrary(".\\LoginDB.dll");
		LoginDB = (ConnectFunc)GetProcAddress(dll, "_LogDB");
		Connection->Connected=false;
		if (LoginDB(str,(LPCSTR)"(local)",(LPCSTR)"RoadsDB") == 1)
		{
			Connection->ConnectionString = str;
			Connection->LoginPrompt=true;
			Connection->Open();
			if (Connection->Connected)
			    Connection->LoginPrompt=false;
		}
		FreeLibrary(dll);
	} */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N63Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->MoveActiveObject();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N64Click(TObject *Sender)
{
	frmMacros->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N66Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		frmConstHelp->SetDictionary(ActiveRoad->Dict);
		frmConstHelp->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N67Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		FActiveRoad->BuildWidePartsDialog();
		//    FActiveRoad->BuildWidePart(0.2);
		//    FActiveRoad->BuildRoadSides(0.4,94);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N68Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		FActiveRoad->WidthMeasureDialog();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N69Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		FActiveRoad->CalculateRoadMarkLength();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N70Click(TObject *Sender)
{
#ifndef WITHOUT_AUTOCAD
	if (FActiveRoad)
	    FActiveRoad->AcadExport();
#endif    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N71Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->BreakRoadLines();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N72Click(TObject *Sender)
{
#ifndef WITHOUT_AUTOCAD
	if (FActiveRoad){
		TWindowState state = FActiveRoad->WindowState;
		FActiveRoad->WindowState = wsMinimized;
		FActiveRoad->AcadPrint();
		FActiveRoad->WindowState = state;
	}else{
		FAutoCADPrint->ShowModal();
	}
#endif
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N73Click(TObject *Sender)
{
	if (FActiveRoad)
	if (FActiveRoad->EditedData)
	{
		if (ActiveRoad->EditedData->ReadOnly)
		    ShowMessage("Эта функция доступна только для слоя проектируемых данных.");
		else
		    FActiveRoad->SetDirector();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N74Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->ShowMapPlan();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N75Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->ShowVisPlan();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RMDesignButClick(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->DesignAttachMark();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N76Click(TObject *Sender)
{
	if (FActiveRoad)
	{
		FActiveRoad->MoveObjects();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N80Click(TObject *Sender)
{
	ShellExecute(0, 0, "RSign.log", 0, 0 , SW_SHOW );   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N81Click(TObject *Sender)
{
	if (FActiveRoad)
	    FActiveRoad->ShowDressLayers();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TMainForm::N83Click(TObject *Sender)
{
TMenuItem *it=(TMenuItem*)Sender;
if (FActiveRoad)
   FActiveRoad->ConnectToBaseLine(it->Tag);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N85Click(TObject *Sender)
{
if (FActiveRoad)
   FActiveRoad->MoveMetricToProp();
}
//---------------------------------------------------------------------------

