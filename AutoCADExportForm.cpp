//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop


#include "AutoCADExportForm.h"
#include "AddRowsDescription.h"
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFAutoCADExport *FAutoCADExport;


AnsiString removeExtension(AnsiString &str)
{
  AnsiString result = str;
  int i=result.Length();
  bool hasExt = false;
  while(i!=1&&!(hasExt = (result[i]=='.'))) {
    i--;
  }

  if(hasExt) {
    return str.SubString(1,i-1);
  } else {
    return str;
  }
}

//---------------------------------------------------------------------------
__fastcall TFAutoCADExport::TFAutoCADExport(TComponent* Owner)
: TForm(Owner)
{
  LoadTemplates();
  fIniLoading = false;
  strIniFileName = ChangeFileExt(Application->ExeName,".ini");
  SetupTEdits();
  TIniFile *ini = new TIniFile(strIniFileName);
  LoadIni(ini, true);
  delete ini;
}
//---------------------------------------------------------------------------

#define ONLYNUMBERS(editName) SetWindowLong(editName->Handle, GWL_STYLE, GetWindowLong(editName->Handle, GWL_STYLE) | ES_NUMBER);

void TFAutoCADExport::SetupTEdits()
{
 ONLYNUMBERS(edtUnderTextHeight)
 ONLYNUMBERS(edtUnderTextYOffset)
 ONLYNUMBERS(edtNotExistsColor)
 ONLYNUMBERS(edtStep)
 ONLYNUMBERS(edtStart)
 ONLYNUMBERS(edtEnd)
 ONLYNUMBERS(edtScaleY)
 ONLYNUMBERS(edtScaleYBlock)   
 ONLYNUMBERS(edtAutoShrinkOneLetterWidth)
 ONLYNUMBERS(edtUseVerticalTextIfLess)
 ONLYNUMBERS(edtSmallGridMarkHeight)
 ONLYNUMBERS(edtRCenter)
 ONLYNUMBERS(edtHeaderWidth)
 ONLYNUMBERS(edtHeaderTextHeight)
 ONLYNUMBERS(edtRowHeight)
}

int TFAutoCADExport::getIndexOfItemInComboBox(TComboBox *combo, AnsiString value, bool fAddIfNotExist)
{
  int index = combo->Items->IndexOf(value);
  if(!~index&&fAddIfNotExist) {
    combo->AddItem(value, (TObject*)1);
    return combo->Items->IndexOf(value);
  }
  return index;
}


void TFAutoCADExport::SaveIni(TIniFile *ini)
{
 ini->WriteBool("AutoCAD","ExportAttachmetns",chkAttachments->Checked);
 ini->WriteBool("AutoCAD","ExportTable",chkTable->Checked);
 ini->WriteBool("AutoCAD","ExportBridges",chkBridges->Checked);
 ini->WriteBool("AutoCAD","ExportBusstops",chkBusstops->Checked);
 ini->WriteBool("AutoCAD","ExportMark",chkMark->Checked);
 ini->WriteBool("AutoCAD","ExportRoadMetrics",chkRoadMetrics->Checked);
 ini->WriteBool("AutoCAD","ExportRoadSideObjects",chkRoadSideObjects->Checked);
 ini->WriteBool("AutoCAD","ExportRoadSigns",chkRoadSigns->Checked);
 ini->WriteBool("AutoCAD","ExportSignal",chkSignal->Checked);
 ini->WriteBool("AutoCAD","ExportSignalExistToo",chkSignalExistToo->Checked);
 ini->WriteBool("AutoCAD","ExportTubes",chkTubes->Checked);
 ini->WriteBool("AutoCAD","ExportSlopes",chkSlope->Checked);
 ini->WriteBool("AutoCAD","ExportCurves",chkCurves->Checked);
 ini->WriteBool("AutoCAD","ExportMoundHeights",chkMoundHeights->Checked);
 ini->WriteBool("AutoCAD","ExportAuto6_13",chkAuto6_13->Checked);
 ini->WriteBool("AutoCAD","LeftValueOnly6_13",chkLeftValueOnly6_13->Checked);
 ini->WriteBool("AutoCAD","ExportLamps",chkLamps->Checked);
 ini->WriteBool("AutoCAD","ExportSidewalks",chkSidewalks->Checked);
 ini->WriteBool("AutoCAD","ExportBorders",chkBorders->Checked);
 ini->WriteBool("AutoCAD","ExportPlan",chkPlan->Checked);
 ini->WriteBool("AutoCAD","ExportSurface",chkSurface->Checked);
 ini->WriteBool("AutoCAD","ExportTown",chkTown->Checked);
 ini->WriteBool("AutoCAD","ExportConditionAsExisting",chkConditionAsExisting->Checked);
 ini->WriteBool("AutoCAD","ExportTrafficLights",chkTrafficLights->Checked);
 ini->WriteBool("AutoCAD","ExportCityObjects",chkCityObjects->Checked);
 ini->WriteBool("AutoCAD","ExportProfile",chkProfile->Checked);
 ini->WriteBool("AutoCAD","ExportDefects",chkDefects->Checked);
 ini->WriteBool("AutoCAD","ExportCommunications",chkCommunications->Checked);
 ini->WriteBool("AutoCAD","MakeHeaders",chkMakeHeader->Checked);
 ini->WriteBool("AutoCAD","ExportAddRowsWithoutData",chkTopAddRowsWithoutData->Checked);
 ini->WriteBool("AutoCAD","HideAutoCAD", chkHideAutoCAD->Checked);
 ini->WriteBool("AutoCAD","ShowAttachmentComments", chkShowAttachmentComments->Checked);
 ini->WriteBool("AutoCAD","DrawMap", chkDrawMap->Checked);   
 ini->WriteInteger("AutoCAD","ExportTo",rgOut->ItemIndex);
 ini->WriteInteger("AutoCAD","NotExistsColor",NotExistsColor);

 ini->WriteBool("AutoCAD","chkSection",chkSection->Checked);
 ini->WriteBool("AutoCAD","chkGridStep",chkGridStep->Checked );

 ini->WriteInteger("AutoCAD","LinesTop",edtLinesTop->Value);
 ini->WriteInteger("AutoCAD","LinesBottom",edtLinesBottom->Value);
 ini->WriteInteger("AutoCAD","AutoShrinkOneLetterWidth",AutoShrinkOneLetterWidth);
 ini->WriteInteger("AutoCAD","UseVerticalTextIfLess",UseVerticalTextIfLess);

 ini->WriteInteger("AutoCAD","RCenter",RCenter);
 ini->WriteInteger("AutoCAD","RowHeight",RowHeight);
 ini->WriteInteger("AutoCAD","GrphRowHeight",GrphRowHeight);
 ini->WriteInteger("AutoCAD", "MinBarrierSegmentLength", MinBarrierSegmentLength);

 ini->WriteInteger("AutoCAD","UnderTextYOffset",UnderTextYOffset);
 ini->WriteInteger("AutoCAD","UnderTextHeight",UnderTextHeight);
 ini->WriteInteger("AutoCAD","HeaderWidth",HeaderWidth);

 ini->WriteInteger("AutoCAD","SmallGridMarkHeight",SmallGridMarkHeight);

 ini->WriteInteger("AutoCAD", "iStart", Start);
 ini->WriteInteger("AutoCAD", "iEnd", End);
 ini->WriteInteger("AutoCAD", "Step", Step);
 ini->WriteInteger("AutoCAD", "GridStep", GridStep);
 ini->WriteInteger("AutoCAD", "LineWidth", LineWidth);

 ini->WriteString("AutoCAD","EditTopAddRows",edtTopAddRows->Text);

 ini->WriteString("AutoCAD","ExportFile",edtPath->Text);
 ini->WriteString("AutoCAD","Version",cmbAutoCADVersion->Text);

 ini->WriteInteger("AutoCAD","iCurrentDataSet",cbCurList->ItemIndex);
 ini->WriteInteger("AutoCAD","iProjectDataSet",cbPrjList->ItemIndex);

 ini->WriteString("AutoCAD","ProfileHatch",edtProfileHatch->Text);
 ini->WriteString("AutoCAD","InfoTemplate",edtInfoTemplate->Text);
 ini->WriteString("AutoCAD","SidewalksHatch",edtSidewalksHatch->Text);
 ini->WriteString("AutoCAD","ProjectBarrierPrefix",edtProjectBarrierPrefix->Text);


 ini->WriteString("AutoCAD","TableHatch",edtTableHatch->Text);
 ini->WriteInteger("AutoCAD", "HeaderTextHeight", HeaderTextHeight);
 ini->WriteInteger("AutoCAD","ScaleY",ScaleY);
 ini->WriteInteger("AutoCAD","ScaleYBlock",ScaleYBlock);   

 try{ini->WriteInteger("AutoCAD", "SidewalksHatchScale", StrToInt(edtSidewalksHatchScale->Text.c_str()));}catch(...){}
 try{ini->WriteInteger("AutoCAD", "ProfileHatchScale", StrToInt(edtProfileHatchScale->Text.c_str()));}catch(...){}
 try{ini->WriteInteger("AutoCAD", "TableHatchScale", StrToInt(edtTableHatchScale->Text.c_str()));}catch(...){}

 ini->WriteBool("AutoCAD","chkGraphic",ExportGraphic);
 ini->WriteBool("AutoCAD","chkRuler",chkRuler->Checked);

 SaveRowsInfoToIni(listTopRows, ini);
 SaveRowsInfoToIni(listBottomRows, ini);
}

void TFAutoCADExport::LoadIni(TIniFile *ini, bool firstTime)
{
 fIniLoading = true;
 chkAttachments->Checked = ini->ReadBool("AutoCAD","ExportAttachmetns",true);
 chkTable->Checked = ini->ReadBool("AutoCAD","ExportTable",true);
 chkBridges->Checked = ini->ReadBool("AutoCAD","ExportBridges",true);
 chkBusstops->Checked = ini->ReadBool("AutoCAD","ExportBusstops",true);
 chkMark->Checked = ini->ReadBool("AutoCAD","ExportMark",true);
 chkRoadMetrics->Checked = ini->ReadBool("AutoCAD","ExportRoadMetrics",true);
 chkRoadSideObjects->Checked = ini->ReadBool("AutoCAD","ExportRoadSideObjects",true);
 chkRoadSigns->Checked = ini->ReadBool("AutoCAD","ExportRoadSigns",true);
 chkSignal->Checked = ini->ReadBool("AutoCAD","ExportSignal",true);
 chkDefects->Checked = ini->ReadBool("AutoCAD","ExportDefects",false);
 chkSignalExistToo->Checked = ini->ReadBool("AutoCAD","ExportSignalExistToo",false);
 chkTubes->Checked = ini->ReadBool("AutoCAD","ExportTubes",true);
 chkSlope->Checked = ini->ReadBool("AutoCAD","ExportSlopes",true);
 chkMoundHeights->Checked = ini->ReadBool("AutoCAD","ExportMoundHeights",true);
 chkCurves->Checked = ini->ReadBool("AutoCAD","ExportCurves",true);
 chkAuto6_13->Checked = ini->ReadBool("AutoCAD","ExportAuto6_13",false);
 chkLeftValueOnly6_13->Checked =  ini->ReadBool("AutoCAD","LeftValueOnly6_13",true);
 chkLamps->Checked = ini->ReadBool("AutoCAD","ExportLamps",true);
 chkSidewalks->Checked = ini->ReadBool("AutoCAD","ExportSidewalks",true);
 chkBorders->Checked = ini->ReadBool("AutoCAD","ExportBorders",true);
 chkTrafficLights->Checked = ini->ReadBool("AutoCAD","ExportTrafficLights", false);
 chkCityObjects->Checked = ini->ReadBool("AutoCAD","ExportCityObjects", false);
 rgOut->ItemIndex = ini->ReadInteger("AutoCAD","ExportTo",0);
 edtNotExistsColor->Text = ini->ReadInteger("AutoCAD","NotExistsColor",1);
 chkSection->Checked = ini->ReadBool("AutoCAD","chkSection",false);
 chkPlan->Checked = ini->ReadBool("AutoCAD","ExportPlan",false);
 chkCommunications->Checked = ini->ReadBool("AutoCAD","ExportCommunications",false);
 chkProfile->Checked = ini->ReadBool("AutoCAD", "chkProfile", false);
 chkSurface->Checked = ini->ReadBool("AutoCAD", "ExportSurface", false);
 chkTown->Checked = ini->ReadBool("AutoCAD","ExportTown",false);
 chkConditionAsExisting->Checked = ini->ReadBool("AutoCAD","ExportConditionAsExisting",false);
 chkProfile->Checked = ini->ReadBool("AutoCAD","ExportProfile",false);
 chkMakeHeader->Checked = ini->ReadBool("AutoCAD","MakeHeaders",true);
 chkTopAddRowsWithoutData->Checked = ini->ReadBool("AutoCAD","ExportAddRowsWithoutData",false);
 chkHideAutoCAD->Checked = ini->ReadBool("AutoCAD","HideAutoCAD", true);
 chkShowAttachmentComments->Checked = ini->ReadBool("AutoCAD", "ShowAttachmentComments", true);
 edtTopAddRows->Text = ini->ReadString("AutoCAD","EditTopAddRows","");
 chkGraphic->Checked = ini->ReadBool("AutoCAD","chkGraphic",false);
 chkGridStep->Checked = ini->ReadBool("AutoCAD","chkGridStep",false);
 chkRuler->Checked = ini->ReadBool("AutoCAD","chkRuler",false);
 chkDrawMap->Checked = ini->ReadBool("AutoCAD","DrawMap", false);

 edtStep->Text = ini->ReadInteger("AutoCAD","Step",100000);

 edtRCenter->Text = ini->ReadInteger("AutoCAD","RCenter",33500);
 edtRowHeight->Text = ini->ReadInteger("AutoCAD","RowHeight",3000);
 edtUnderTextHeight->Text =  ini->ReadInteger("AutoCAD","UnderTextHeight",350);
 edtUnderTextYOffset->Text =  ini->ReadInteger("AutoCAD","UnderTextYOffset",300);
 edtHeaderWidth->Text = ini->ReadInteger("AutoCAD","HeaderWidth",20000);
 edtScaleY->Text = ini->ReadInteger("AutoCAD","ScaleY",600);
 edtScaleYBlock->Text = ini->ReadInteger("AutoCAD","ScaleYBlock",0);   
 edtStart->Text = ini->ReadInteger("AutoCAD","iStart",-1);
 edtEnd->Text = ini->ReadInteger("AutoCAD","iEnd",-1);

 edtLineWidth->Text = ini->ReadInteger("AutoCAD","LineWidth",0);
 edtAutoShrinkOneLetterWidth->Text = ini->ReadInteger("AutoCAD","AutoShrinkOneLetterWidth",2300);
 edtUseVerticalTextIfLess->Text = ini->ReadInteger("AutoCAD","UseVerticalTextIfLess",50);
 edtGridStep->Text = ini->ReadInteger("AutoCAD", "GridStep", 10000);
 edtMinBarrierSegmentLength->Text = ini->ReadInteger("AutoCAD", "MinBarrierSegmentLength", 2000);
 edtSmallGridMarkHeight->Text = ini->ReadInteger("AutoCAD","SmallGridMarkHeight",0);

 edtGrphRowHeight->Text = ini->ReadInteger("AutoCAD","GrphRowHeight",4000);

 edtLinesTop->Value = ini->ReadInteger("AutoCAD", "LinesTop", 1);
 edtLinesBottom->Value = ini->ReadInteger("AutoCAD", "LinesBottom", 1);   
 edtInfoTemplate->Text = ini->ReadString("AutoCAD","InfoTemplate","%i км");
 edtSidewalksHatch->ItemIndex = getIndexOfItemInComboBox(edtSidewalksHatch,
  ini->ReadString("AutoCAD","SidewalksHatch","AR-HBONE"), true);
 edtProfileHatch->ItemIndex = getIndexOfItemInComboBox(edtProfileHatch,
  ini->ReadString("AutoCAD","ProfileHatch","ANSI31"), true);
 edtTableHatch->ItemIndex = getIndexOfItemInComboBox(edtTableHatch,
  ini->ReadString("AutoCAD","TableHatch","ANSI31"), true);
 edtSidewalksHatchScale->Text = ini->ReadInteger("AutoCAD", "SidewalksHatchScale", 75);
 edtProfileHatchScale->Text = ini->ReadInteger("AutoCAD", "ProfileHatchScale", 75);
 edtTableHatchScale->Text = ini->ReadInteger("AutoCAD", "TableHatchScale", 75);
 edtProjectBarrierPrefix->Text = ini->ReadString("AutoCAD","ProjectBarrierPrefix","");

 iCur = ini->ReadInteger("AutoCAD","iCurrentDataSet",-1);
 iPrj = ini->ReadInteger("AutoCAD","iProjectDataSet",-1);

 edtHeaderTextHeight->Text = ini->ReadInteger("AutoCAD", "HeaderTextHeight", 450);

 edtPath->ItemIndex = edtPath->Items->IndexOf(ini->ReadString("AutoCAD","ExportFile",""));

 LoadRowsInfoFromIni(listTopRows, ini);
 LoadRowsInfoFromIni(listBottomRows, ini);
 fIniLoading = false;

 if (firstTime) {
  cmbAutoCADVersion->ItemIndex = cmbAutoCADVersion->Items->IndexOf(ini->ReadString("AutoCAD","Version","Default"));
}
}
void __fastcall TFAutoCADExport::FormClose(TObject *Sender,
  TCloseAction &Action)
{
  TIniFile *ini = new TIniFile(strIniFileName);
  SaveIni(ini);
  delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::FormKeyDown(TObject *Sender, WORD &Key,
  TShiftState Shift)
{
  switch(Key){
   case VK_RETURN:
   btnOk->Click();
   break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::SetRoadId(int rid) {

  cbCurList->Items->Clear();
  cbPrjList->Items->Clear();
  int cind=0,pind=0;
  cbCurList->Items->AddObject("Ќе выводить",0);
  cbPrjList->Items->AddObject("Ќе выводить",0);
  for (int i=0,j=0;i<MainForm->ResManager->DataCount;i++)
  {
    TDtaSource *Dta=MainForm->ResManager->Data[i];
    if (Dta && Dta->Id==rid) {
      cbCurList->Items->AddObject(Dta->SourceName,Dta);
      cbPrjList->Items->AddObject(Dta->SourceName,Dta);
      j++;
      if (Dta->ReadOnly)
       cind=j;
     else
       pind=j;
   }
 }
 iCur = iCur==-1?cind:iCur<cbCurList->Items->Count?iCur:cind;
 iPrj = iPrj==-1?pind:iPrj<cbPrjList->Items->Count?iPrj:pind;
 cbCurList->ItemIndex=iCur;
 cbPrjList->ItemIndex=iPrj;
}


void __fastcall TFAutoCADExport::chkAllClick(TObject *Sender)
{
 TCheckBox *xBox = dynamic_cast<TCheckBox*>(Sender);
 TCheckBox *checkBox;
 if(!xBox) return;
 bool fCheck = xBox->Checked;

 TWinControl *parent = xBox->Parent;
 for(int i=0;i<parent->ControlCount;i++) {
  if(parent->Controls[i]!=xBox) {
   checkBox = dynamic_cast<TCheckBox*>(parent->Controls[i]);
   if(checkBox) {
    checkBox->Checked = fCheck;
  }
}
}

if(xBox==chkAllPlan) {
 chkGraphic->Checked = fCheck;
}
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::Button2Click(TObject *Sender)
{
  static AnsiString name,temp;
  OpenDialog1->InitialDir = ExtractFileDir(edtPath->Text);
  if(!OpenDialog1->Execute()) return;
  name = OpenDialog1->FileName;
  temp=ExtractFileDir(Application->ExeName);
  if(name.Pos(temp)==1){
   name = "."+name.SubString(temp.Length()+1,name.Length() - temp.Length());
 }
 edtPath->Text = name;
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::Button3Click(TObject *Sender)
{
  pnlLeft->Visible = !pnlLeft->Visible;
  if(pnlLeft->Visible)
   Button3->Caption = "<<";
 else
   Button3->Caption = ">>";
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::cbCurListChange(TObject *Sender)
{
 iCur = cbCurList->ItemIndex;
}
//---------------------------------------------------------------------------

int TFAutoCADExport::setBottomAddRowsCount(int count)
{
  bottomAddRowsCount = count;
}

int TFAutoCADExport::setTopAddRowsCount(int count)
{
  topAddRowsCount = count;
}


void __fastcall TFAutoCADExport::cbPrjListChange(TObject *Sender)
{
  iPrj = cbPrjList->ItemIndex;   
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADExport::btnTopAddRowsClick(TObject *Sender)
{
  TButton *btn = dynamic_cast<TButton*>(Sender);
  if(!btn) return;

  TEdit *edt;
  AnsiString str;

  if (btn == btnTopAddRows){
   edt = edtTopAddRows;
 }else{
   return;
 }
 str = edt->Text;
 if(SelectDirectory("¬ыберете директорию содержащую файлы с данными дл€ строк","",str)) {
   edt->Text = str;
 }
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::Button5Click(TObject *Sender)
{
  if(!OpenDialog2->Execute()) return;
  TIniFile *ini = new TIniFile(OpenDialog2->FileName);
  LoadIni(ini);
  delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADExport::Button6Click(TObject *Sender)
{
  AnsiString newName;
  if((int)cbIni->Items->Objects[cbIni->ItemIndex]==1) {
   newName = removeExtension(cbIni->Text);
 }
  /*if(!RoadName.IsEmpty()) {
     newName+=" " + RoadName;
  }  */
 if(newName.IsEmpty()) {
   newName="новый";
 }
 if(InputQuery("—оздание нового набора настроек", "¬ведите им€ дл€ нового набора:", newName)) {
  TIniFile *ini = new TIniFile(ExtractFileDir(Application->ExeName)+"\\AutoCAD\\"+newName+".ini");
  SaveIni(ini);
  delete ini;
}
int index = cbIni->ItemIndex;
LoadSetupsInis();
cbIni->ItemIndex = index;
}
//---------------------------------------------------------------------------
int TFAutoCADExport::getRow(TCheckListBox *lb, AnsiString &rowName)
{
 int enl = 0;
 int iRowMark =  lb->Items->IndexOf("разметка от осевой");
 int iRowMark2 =  lb->Items->IndexOf("искусственные сооружени€");
 int iAddRows =  lb->Items->IndexOf("дополнительные строки");
 int iRow = lb->Items->IndexOf(rowName);
 if(!~iRow) return -1;
 if(~iRowMark&&iRow>iRowMark&&lb->Checked[iRowMark])
  enl=(lb==listTopRows)?edtLinesTop->Value-1: enl=(lb==listBottomRows)?edtLinesBottom->Value-1:0;
   if(~iRowMark2&&iRow>iRowMark2&&lb->Checked[iRowMark2]) enl+=1; //на искусственные сооружени€ две строчки
   if (!lb->Checked[iRow]) return -1;
   if(lb == listTopRows) {
    if(iRow>iAddRows&&lb->Checked[iAddRows]) {
     return topAddRowsCount - 1 + iRow+enl-countOfUnchecksBefore(lb, iRow);
   }
 } else if(lb == listBottomRows) {
  if(iRow>iAddRows&&lb->Checked[iAddRows]) {
   return bottomAddRowsCount - 1 + iRow+enl-countOfUnchecksBefore(lb, iRow);
 }
}
return iRow+enl-countOfUnchecksBefore(lb, iRow);
}

AnsiString TFAutoCADExport::getAutoCADVersion()
{
 return cmbAutoCADVersion->Text;
}

int TFAutoCADExport::countOfUnchecksBefore(TCheckListBox *list, int iRow)
{
 int c = 0;
 iRow--;     
 while(iRow>=0) {
  if(!list->Checked[iRow]) {
    c++;
  }
  iRow--;
}
return c;
}

int TFAutoCADExport::getTopRow(AnsiString rowName)
{
 return getRow(listTopRows, rowName);
}

int TFAutoCADExport::getBottomRow(AnsiString rowName)
{
 return getRow(listBottomRows, rowName);
}

void TFAutoCADExport::SaveRowsInfoToIni(TCheckListBox *list, TIniFile *ini)
{
 AnsiString str = "";
 for(int i=0;i<list->Count;i++) {
  str += list->Items->Strings[i]+"="+IntToStr(list->Checked[i])+";";
}
ini->WriteString("AutoCAD", list->Name, str);
}

void TFAutoCADExport::LoadRowsInfoFromIni(TCheckListBox *list, TIniFile *ini)
{
 AnsiString str;
 str = ini->ReadString("AutoCAD", list->Name, "");
 int iLast = 0;
 int iCur = 0;
 int iRow;
 AnsiString curString;
 bool fChecked;
 for(int i=2;i<str.Length();i++) {
  if(str[i]=='=') {
   curString = str.SubString(iLast+1,i-iLast-1);
   fChecked = str[i+1]=='1';
   iRow = list->Items->IndexOf(curString);
   if(~iRow) {
     list->Checked[iRow] = fChecked; 
     list->Items->Move(iRow, iCur);
   }
   i+=2;
   iLast = i;
   iCur++;
 }
}

}

void TFAutoCADExport::fillComboRoad()
{
  TSearchRec sr;
  cmbRoad->Clear();
  cmbRoad->ItemIndex = -1;
  AnsiString roadName = StringReplace(RoadName, "\"", "", TReplaceFlags() << rfReplaceAll);
  if(!FindFirst(edtTopAddRows->Text + "\\" + roadName + "\\*.*", faDirectory, sr)) {
   do {
    if (sr.Attr&faDirectory&& sr.Name!="." && sr.Name!="..") {
     cmbRoad->AddItem(roadName + "\\" + sr.Name, 0);
   }
 }while (!FindNext(sr));
}
if(!FindFirst(edtTopAddRows->Text + "\\*.*", faDirectory, sr)) {
 do {
  if (sr.Attr&faDirectory&& sr.Name!="." && sr.Name!="..") {
   cmbRoad->AddItem(sr.Name, 0);
 }
}while (!FindNext(sr));
}
FindClose(sr);
locateRoadNameComboRoad();
}

void TFAutoCADExport::locateRoadNameComboRoad()
{
  TReplaceFlags Flags;
  Flags << rfReplaceAll;
  AnsiString name;
  AnsiString roadName = RoadName;
  AnsiString districtName = RoadDistrict;

  // пытаемс€ найти папку с именем как у дороги
  roadName = StringReplace(roadName, " ", "",Flags);
  roadName = StringReplace(roadName, "-", "",Flags);
  roadName = StringReplace(roadName, "_", "",Flags);
  roadName = StringReplace(roadName, ".", "",Flags);
  roadName = StringReplace(roadName, "\"", "",Flags);

  cmbRoad->ItemIndex = -1;
  for(int i=0;i<cmbRoad->Items->Count;i++) {
   name = cmbRoad->Items->Strings[i];
   name = StringReplace(name, " ", "",Flags);
   name = StringReplace(name, "-", "",Flags);
   name = StringReplace(name, "_", "",Flags);
   name = StringReplace(name, ".", "",Flags);
   name = StringReplace(name, "\"", "",Flags);
   if(name.Pos(roadName) ) {
    cmbRoad->ItemIndex = i;
    return;
  }
}

  // пытаемс€ найти папку с именем как у района
districtName = StringReplace(districtName, " ", "",Flags);
districtName = StringReplace(districtName, "-", "",Flags);
districtName = StringReplace(districtName, "_", "",Flags);
districtName = StringReplace(districtName, ".", "",Flags);
districtName = StringReplace(districtName, "\"", "",Flags);

for(int i=0;i<cmbRoad->Items->Count;i++) {
 name = cmbRoad->Items->Strings[i];
 name = StringReplace(name, " ", "",Flags);
 name = StringReplace(name, "-", "",Flags);
 name = StringReplace(name, "_", "",Flags);
 name = StringReplace(name, ".", "",Flags);
 name = StringReplace(name, "\"", "",Flags);
 if(name.Pos(districtName) ) {
  cmbRoad->ItemIndex = i;
  return;
}
}

}


void __fastcall TFAutoCADExport::listBottomRowsDragOver(TObject *Sender,
  TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  if(Source == Sender) {
    Accept = true;
    TCheckListBox *lb = static_cast<TCheckListBox*>(Sender);
    if(!lb) return;
    int curItem = lb->ItemIndex;
    int newItem = lb->ItemAtPos(TPoint(X,Y), true);
    if(~newItem&&~curItem&&(newItem!=curItem)) {
     lb->Items->Move(curItem,newItem);
     lb->ItemIndex = newItem;
   }
 }
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::edtBottomAddRowsClick(TObject *Sender)
{
 static TEdit* lastEdit = 0;
 TEdit *edit = dynamic_cast<TEdit*>(Sender);
 if(edit&&lastEdit!=edit) {
  edit->SelectAll();

}
lastEdit = edit;
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::edtTopAddRowsDblClick(TObject *Sender)
{
 TEdit *edit = dynamic_cast<TEdit*>(Sender);
 if(edit) {
  edit->SelectAll();
}
}

WideString TFAutoCADExport::get_EditTopAddRows()
{
 return edtTopAddRows->Text +"\\"+ cmbRoad->Text;
}
void TFAutoCADExport::set_EditTopAddRows(WideString value)
{
  edtTopAddRows->Text = value;
}


void __fastcall TFAutoCADExport::LoadSetupsInis()
{
  TSearchRec rec;
  int iAttributes=0;
  cbIni->Clear();
  cbIni->AddItem(" -- последний -- ", 0);
  if(!FindFirst(ExtractFileDir(Application->ExeName)+"\\AutoCAD\\*.ini",0,rec)) {
    do {
      cbIni->AddItem(ExtractFileName(rec.Name), (TObject*)1);
    }
    while(!FindNext(rec));
    FindClose(rec);
  }
  cbIni->AddItem("...",(TObject*)2);
  cbIni->ItemIndex = 0;
}

void __fastcall TFAutoCADExport::LoadTemplates()
{
  TSearchRec rec;
  int iAttributes=0;

  if(!FindFirst(ExtractFileDir(Application->ExeName)+"\\AutoCAD\\*.dwt",0,rec)) {
    do {
      if(!~edtPath->Items->IndexOf(ExtractFileName(rec.Name))) {
       edtPath->AddItem(ExtractFileName(rec.Name), (TObject*)1);
     }
   }
   while(!FindNext(rec));
   FindClose(rec);
 }
  //cbIni->AddItem("...",(TObject*)2);
  //cbIni->ItemIndex = 0;
}

void __fastcall TFAutoCADExport::FormShow(TObject *Sender)
{
  LoadSetupsInis();
  LoadTemplates();
  fillComboRoad();
  locateRoadNameComboRoad();
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::cbIniChange(TObject *Sender)
{
 static lastItem = 0;
 int type = (int)cbIni->Items->Objects[cbIni->ItemIndex];
 TIniFile *ini=0;

 switch (type) {
   case 0:
   ini = new TIniFile(strIniFileName);
   break;

   case 1:
   ini = new TIniFile(ExtractFileDir(Application->ExeName)+"\\AutoCAD\\"+cbIni->Items->Strings[cbIni->ItemIndex]);
   break;

   case 2:
   if(OpenDialog2->Execute()) {
     ini = new TIniFile(OpenDialog1->FileName);
   } else {
     cbIni->ItemIndex = lastItem;
   }
   break;
 }

 if(ini) {
  LoadIni(ini);
  delete ini;
}
lastItem = cbIni->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::btnOkClick(TObject *Sender)
{
   bottomAddRowsCount = 0;
   topAddRowsCount = 0; /*это на вс€кий пожарный: обнулим кол-во дополнительных строк*/        
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::edtTopAddRowsChange(TObject *Sender)
{
  fillComboRoad();        
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADExport::edtStartChange(TObject *Sender)
{
 if(fIniLoading) return;
 TEdit *edit = dynamic_cast<TEdit*>(Sender);
 if(!edit->Text.IsEmpty() && edit->Text != -1) {
  chkSection->Checked = true;
}else{
  chkSection->Checked = false;
}
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADExport::Button4Click(TObject *Sender)
{
 chkSection->Checked = false;
 edtStart->Text = "-1";
 edtEnd->Text = "-1";
}
//---------------------------------------------------------------------------
int __fastcall TFAutoCADExport::CountOfExports()
{
  int count = 0;

  count += ExportRoadMetrics;
  count += ExportAttachments;
  count += ExportRoadSigns;
  count += ExportMark;
  count += ExportTubes;
  count += ExportBridges;
  count += ExportSignal;
  count += ExportBusstops;
  count += ExportRoadSideObjects;
  count += ExportSlope;
  count += ExportCurves;
  count += ExportMoundHeights;
  count += ExportDefects;

  count += ExportLamps;
  count += ExportSidewalks;
  count += ExportBorders;
  count += ExportTrafficLights;
  count += ExportCityObjects;    

  count += ExportProfile;
  count += ExportSurface;
  count += ExportCommunications;
  count += ExportTown;
  count += ExportPlan;

  count += ExportGraphic;
  count += ExportAddRows;

    //count += ExportRuler;
    //count += ExportTable;

  return count;
}
//---------------------------------------------------------------------------




void __fastcall TFAutoCADExport::btnShowInfoClick(TObject *Sender)
{
  FAddRowDescription->Show();    
}
//---------------------------------------------------------------------------

