//---------------------------------------------------------------------------


#include "without_autocad.h"
#ifndef WITHOUT_AUTOCAD

#include <vcl.h>
#pragma hdrstop


#include "AutoCADPrintForm.h"
#include "AutoCADPrintThread.h"
#include <process.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAutoCADPrint *FAutoCADPrint;

void __fastcall TFAutoCADPrint::OnDocClose(TObject *Sender)
{
  lblActiveName->Caption = "";
}

//---------------------------------------------------------------------------
__fastcall TFAutoCADPrint::TFAutoCADPrint(TComponent* Owner)
        : TForm(Owner)
{
  vcTop = 42250;
  vcCenter = 0;
  vcBottom = -42250;
  vStep = 100000;
  sPos = 0;
  curState = 0;
  ePos = vStep;
  //SaveDialog1->InitialDir = ExtractFileDir(Application->ExeName) + "\\AutoCAD";
  strIniFileName = ChangeFileExt(Application->ExeName,".ini");

  Image1->Hint = "Выбери мышкой прямоугольник соответствующий\n\
видовому экрану в пространстве листа AutoCAD.\n\
Нажми 1: чтобы использовать ВИ для вывода верхней таблицы\n\
Нажми 2: чтобы использовать ВИ для вывода центральной таблицы\n\
Нажми 3: чтобы использовать ВИ для вывода нижней таблицы\n\
Нажми Delete: чтобы не использовать ВИ";

  Rects = new TList();

  TIniFile *ini = new TIniFile(strIniFileName);

  LoadIni(ini);
  delete ini;
  Width = 0;
  Application->HintHidePause = 10000;
}
//---------------------------------------------------------------------------

__fastcall TFAutoCADPrint::~TFAutoCADPrint()
{
   delete Rects;
}

void TFAutoCADPrint::CheckViewports()
{
   int count = helper->ActiveDocument->PaperSpace->Count;
   iSelected = -1;
   AcadEntityPtr e;
   AcadPViewportPtr pv;
   AcadPViewportPtr v;
   Variant center;
   _Left = _Right = _Top = _Bottom = 0;
   Rects->Clear();
   float left,right,top,bottom;
   float width,height;
   bool ffirst = true;
   for(int i=0;i<count;i++){
      e = helper->ActiveDocument->PaperSpace->Item(Variant(i));
      if(e->EntityType == acPViewport){
         if(ffirst){
           ffirst = false;
           continue;
         }
         pv = e;
         width = pv->Width/2;
         height = pv->Height/2;
         pv->get_Center(center);
         left = center.GetElement(0)-width;
         top = center.GetElement(1)-height;
         right = center.GetElement(0)+width;
         bottom = center.GetElement(1)+height;
         
         if(_Left>left) _Left = left;
         if(_Right<right) _Right = right;
         if(_Top>top) _Top = top;
         if(_Bottom<bottom) _Bottom = bottom;

         Rects->Add(new TRect(left,top,right,bottom));
      }
   }
   xOffset = -_Left;
   yOffset = -_Top;
   
   _Width = _Right - _Left;
   if(_Width) kWidth = (float)(Image1->Width)/_Width;
   _Height = _Bottom - _Top;
   if(_Height) kHeight = (float)Image1->Height/_Height;    
}

bool TFAutoCADPrint::BindViewports()
{
  bool ffirst = true;
  AcadEntityPtr e;
  vpTop.Unbind();
  vpCenter.Unbind();
  vpBottom.Unbind();
  text.Unbind();
  page.Unbind();
  page_max.Unbind();
  roadName.Unbind();

  if(!helper->ActiveDocument.IsBound()) return false;
  helper->ActiveDocument->Activate();

  bool finfo = chkInfo->Checked;   
  int cur = 0;
  int count = helper->ActiveDocument->PaperSpace->Count;
  for(int i=0;i<count;i++){
      e = helper->ActiveDocument->PaperSpace->Item(Variant(i));
      if(e->EntityType == acPViewport){
         if(ffirst){
           ffirst = false;
           continue;
         }
         if(cur==iTop){
           vpTop = e;
           // recalculate zoom positions for top vp
           float kTop = vStep/vpTop->Width;
           vcTop = iOffset+(vpTop->Height*kTop)/2;
         }
         if(cur==iCenter){
           vpCenter = e;
         }
         if(cur==iBottom){
           vpBottom = e;
           // recalculate zoom positions for bottom vp
           float kBottom = vStep/vpBottom->Width;
           vcBottom = -iOffset-(vpBottom->Height*kBottom)/2;                                                                  
         }
         cur++;
      }else if(finfo&&e->EntityType==acText){
         if(!wcscmp(e->Layer,L"@info")){
           text = e;
         }
         if(!wcscmp(e->Layer,L"@page")){
           page = e;
         }
         if(!wcscmp(e->Layer,L"@page_max")){
           page_max = e;
         }
         if(!wcscmp(e->Layer,L"@roadName")){
           roadName = e;
         }
      }
   }
   return true;


}

void TFAutoCADPrint::DrawViewports()
{
   TRect rct;

   AnsiString str;
   Image1->Canvas->Font->Size = 8;
   Image1->Canvas->Brush->Color = clWhite;
   Image1->Canvas->FillRect(TRect(0,0,Image1->Width,Image1->Height));
   for(int i=0;i<Rects->Count;i++){
     TRect *rect = (TRect*)Rects->Items[i];
     Image1->Canvas->Pen->Color = i==iSelected?clRed:clBlack;
     rct=TRect((rect->Left+xOffset)*kWidth,
               (-rect->Top-yOffset+_Height)*kHeight,
               (rect->Right+xOffset)*kWidth,
               (-rect->Bottom-yOffset+_Height)*kHeight);

     Image1->Canvas->Rectangle(rct);
     str = AnsiString(i==iTop?"1":"") + AnsiString(i==iCenter?"2":"") + AnsiString(i==iBottom?"3":"");
     if(!str.IsEmpty()){
       DrawText(Image1->Canvas->Handle,str.c_str(),str.Length(),&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
     }     
   }
}

void TFAutoCADPrint::SaveIni(TIniFile *ini)
{
   ReadValues();
   ini->WriteFloat("AutoCAD","PViewportTopCenterY",vcTop);
   ini->WriteFloat("AutoCAD","PViewportMiddleCenterY",vcCenter);
   ini->WriteFloat("AutoCAD","PViewportBottomCenterY",vcBottom);
   ini->WriteFloat("AutoCAD","PScaleStep",vStep);
   ini->WriteInteger("AutoCAD","iTop",iTop);
   ini->WriteInteger("AutoCAD","iCenter",iCenter);
   ini->WriteInteger("AutoCAD","iBottom",iBottom);
   ini->WriteInteger("AutoCAD","PBegin",sPos);
   ini->WriteInteger("AutoCAD","PEnd",ePos);
   ini->WriteInteger("AutoCAD","PrintPageNumBegin",iPage);
   ini->WriteBool("AutoCAD","POnlySelectedInterval",chkOnly->Checked);
   //ini->WriteBool("AutoCAD","Synchronize",chkSynchronize->Checked);
   ini->WriteBool("AutoCAD","ShowMetricsInfo",chkInfo->Checked);
   ini->WriteString("AutoCAD","PatternString",edtPattern->Text);
   ini->WriteString("AutoCAD", "PDFBinder",edtPDFBinder->Text );
}

void TFAutoCADPrint::LoadIni(TIniFile *ini)
{
   edtTopCenter->Text = vcTop = ini->ReadFloat("AutoCAD","PViewportTopCenterY",44000);
   edtMiddleCenter->Text = vcCenter = ini->ReadFloat("AutoCAD","PViewportMiddleCenterY",0);
   edtBottomCenter->Text = vcBottom = ini->ReadFloat("AutoCAD","PViewportBottomCenterY",-42250);
   edtStart->Text = sPos = ini->ReadInteger("AutoCAD","PBegin",0);
   edtStep->Text = vStep = ini->ReadFloat("AutoCAD","PScaleStep",100000);
   edtEnd->Text = ePos = ini->ReadInteger("AutoCAD","PEnd",vStep);

   edtPattern->Text = ini->ReadString("AutoCAD","PatternString","%i-%i км.");
   chkInfo->Checked = ini->ReadBool("AutoCAD","ShowMetricsInfo",true);
   chkOnly->Checked = ini->ReadBool("AutoCAD","POnlySelectedInterval",false);
//   chkSynchronize->Checked = ini->ReadBool("AutoCAD","Synchronize",false);
   edtPage->Text = ini->ReadInteger("AutoCAD","PrintPageNumBegin",3);   
   iTop =  ini->ReadInteger("AutoCAD","iTop",-1);
   iCenter =  ini->ReadInteger("AutoCAD","iCenter",-1);
   iBottom =  ini->ReadInteger("AutoCAD","iBottom",-1);

   edtPDFBinder->Text = ini->ReadString("AutoCAD", "PDFBinder",
                         ".\\AutoCAD\\PDFBinder\\pdfbinder.exe" );

   TShiftState ss;
   edtEndKeyDown(0,VK_RETURN,ss);
}

void __fastcall TFAutoCADPrint::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key){
     case VK_ESCAPE:
       if(iSelected>=0){
          iSelected = -1;
          DrawViewports();
       }else{
          ModalResult = mrCancel;
       }
     break;
     case '1':
       if(Panel1->Focused()&&iSelected>=0){
         iTop = iSelected;
         if(iCenter==iTop) iCenter = -1;
         if(iBottom==iTop) iBottom = -1;         
         iSelected = -1;
         DrawViewports();
       }
     break;
     case '2':
       if(Panel1->Focused()&&iSelected>=0){
         iCenter = iSelected;
         if(iTop==iCenter) iTop = -1;
         if(iBottom==iCenter) iBottom = -1;           
         iSelected = -1;
         DrawViewports();
       }
     break;
     case '3':
       if(Panel1->Focused()&&iSelected>=0){
         iBottom = iSelected;
         if(iTop==iBottom) iTop = -1;
         if(iCenter==iBottom) iCenter = -1;
         iSelected = -1;
         DrawViewports();
       }
     break;
     case VK_DELETE:
       if(Panel1->Focused()&&iSelected>=0){
         if(iSelected==iBottom) iBottom = -1;
         if(iTop==iSelected) iTop = -1;
         if(iCenter==iSelected) iCenter = -1;
         iSelected = -1;
         DrawViewports();
       }
     break;
  }
}
//---------------------------------------------------------------------------
void TFAutoCADPrint::ReadValues()
{
     float v;
     int v2;
     if(TryStrToFloat(edtTopCenter->Text,v)){
         vcTop = v;
      }else{
         edtTopCenter->Text = vcTop;
      }

      if(TryStrToFloat(edtMiddleCenter->Text,v)){
         vcCenter = v;
      }else{
         edtMiddleCenter->Text = vcCenter;
      }

      if(TryStrToFloat(edtBottomCenter->Text,v)){
         vcBottom = v;
      }else{
         edtBottomCenter->Text = vcBottom;
      }

      if(TryStrToFloat(edtStep->Text,v)){
         vStep = v;
      }else{
         edtStep->Text = vStep;
      }

      if(TryStrToFloat(edtStart->Text,v)){
         sPos = v;
      }else{
         edtStart->Text = sPos;
      }

      if(TryStrToInt(edtPage->Text,v2)){
        iPage = v2;
      }else{
        edtPage->Text = v2;
      }

      if(TryStrToFloat(edtEnd->Text,v)){
         ePos = v;
      }else{
         edtEnd->Text = ePos;
      }

}

//---------------------------------------------------------------------------
void __fastcall TFAutoCADPrint::cmdPrintClick(TObject *Sender)
{
    if(!helper) return;
    ReadValues();
    try{
        SaveDialog1->FileName = AutoCAD.ActiveDocument->SummaryInfo->Title;
    }catch(...){}
    if(!SaveDialog1->Execute()){
      return;
    }else{
      FileName = SaveDialog1->FileName;
    }

    Print();

    TIniFile *ini = new TIniFile(strIniFileName);
    SaveIni(ini);
    delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADPrint::Button7Click(TObject *Sender)
{
    tbPos->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button3Click(TObject *Sender)
{
      tbPos->Position++;        
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::tbPosChange(TObject *Sender)
{
  static last = -1;
  int v;

  if(TryStrToInt(edtStep->Text,v)){
    edtPos->Text = tbPos->Position*v;
    v = tbPos->Position;
    if(last!=v){
      if(!helper) return;
      AnsiString str;
      int iMin = tbPos->Position;
      
      ReadValues();

      int km = (iMin*vStep)/100000;
      int meters = (int(iMin*vStep)/100)%1000;
      try{
        str.sprintf(edtPattern->Text.c_str(),km,meters);
      }catch(...){return;}

      if(!BindViewports()) return;
      
      helper->SelectPaperSpace();
      helper->Application->ZoomAll();

      if(text.IsBound()) text->set_TextString(WideString(str));
      if(roadName.IsBound()) roadName->set_TextString(WideString(strRoadName));

      int j = tbPos->Position;
      int minPos = tbPos->Min;
      int diff = tbPos->Max - tbPos->Min;

      if(page.IsBound())
         page->set_TextString(WideString(iPage+j-minPos));
      if(page_max.IsBound())
         page_max->set_TextString(WideString(iPage+diff));

      SetFrame(j*vStep, vStep);
    }
    last = v;
  }
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADPrint::edtEndKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  int v1,v2;
  switch(Key){
     case VK_RETURN:
      if(TryStrToInt(edtStep->Text,v2)){
        if(TryStrToInt(edtStart->Text,v1)){
           tbPos->Min = v1/v2;
        }
        if(TryStrToInt(edtEnd->Text,v1)){
           tbPos->Max = v1/v2;/*+(v1%v2==0?0:1);*/
        }
      }
     break;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADPrint::edtStepEnter(TObject *Sender)
{
  TEdit *edt  = dynamic_cast<TEdit*>(Sender);
  if(edt){
    edt->SelectAll();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::edtPosKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  int v1,v2;
  switch(Key){
      if(TryStrToInt(edtPos->Text,v1)){
        if(TryStrToInt(edtStep->Text,v2)){
           tbPos->Position = v1/v2;
        }
      }
  }
}
//---------------------------------------------------------------------------

bool TFAutoCADPrint::BeginPrint()
{
     return false;
}

bool TFAutoCADPrint::PauseLastFramePrint(std::list<AnsiString> &fileNames)
{
   if ( MessageDlg("Объединить все pdf в один файл?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
        AnsiString argvs = "\"" + ExtractFileName(FileName)+".pdf" + "\"";
        for( list<AnsiString>::iterator it = fileNames.begin(); it!=fileNames.end(); ++it ) {
           argvs += " ";
           argvs += "\"" + ExtractFileName(*it) + ".pdf" + "\"";
        }

        AnsiString execDir = ExtractFileDir(Application->ExeName);
        AnsiString pdfBinderDir = StringReplace(edtPDFBinder->Text,
                    ".\\", ExtractFileDir(Application->ExeName) + "\\", TReplaceFlags());    //execDir + "\\AutoCAD\\PDFBinder\\pdfbinder.exe";
        AnsiString cmndLine = "chcp 1251\n" + pdfBinderDir +" "+ argvs;

        AnsiString batName =  ExtractFileDir(FileName) + "\\pdf для " +
                         ExtractFileName(FileName) + ".bat";

        FILE *file = fopen( batName.c_str(), "w");
        fprintf(file, cmndLine.c_str());
        fclose(file);

        if(FileExists(pdfBinderDir) ) {
          WinExec( batName.c_str(), SW_SHOW );
        }
        return true;
   }
   return false;
}

bool TFAutoCADPrint::SetFrame(int position, int width)
{
     AcadPViewportPtr viewport;
     int yCenter;
     for(int i=0;i<3;i++){
       switch(i){
          case 0: viewport = vpBottom; yCenter = vcBottom; break;
          case 1: viewport = vpCenter; yCenter = vcCenter; break;
          case 2: viewport = vpTop; yCenter = vcTop; break;
          default: continue;
       }
       if ( viewport.IsBound() ) {
            viewport->Display(-1); // -1 is true :D, that is not my idea
            helper->ActiveDocument->MSpace = true;
            helper->ActiveDocument->ActivePViewport = viewport;
            helper->Application->ZoomWindow(helper->cadPoint(position,yCenter),
                                             helper->cadPoint(position+width,yCenter));

       }
       Application->ProcessMessages();
    }
    helper->ActiveDocument->MSpace = false;
}

bool TFAutoCADPrint::EndPrint()
{
     return false;
}

void TFAutoCADPrint::Print(PrintType printType)
{
      ProgressForm->showCancel = 1;
      AnsiString str;
      AnsiString pattern = edtPattern->Text;
      float iMax,iMin;
      float step = (vStep/100000);

      if(!chkOnly->Checked){
        iMin = tbPos->Min;
        iMax = tbPos->Max;
      }else{
        iMin = tbPos->Position;
        iMax = tbPos->Position;
      }

      ProgressForm->Caption = "Печать из AutoCAD";
      ProgressForm->Position = 0;
      ProgressForm->Note = "Пробую подключиться к AutoCAD";
      ProgressForm->SetMinMax(tbPos->Min, tbPos->Max);


      if(!BindViewports())
        return; 

        str.sprintf(pattern.c_str(),0,1);
        
        std::list<AnsiString> fileNames;
        int iiPage=0;

        AutoCADPrintOutputStyle osPrint = FAutoCADPrint->OutputStyle;
        
        switch(osPrint){
          case 0: helper->ActiveDocument->SetVariable(WideString("BACKGROUNDPLOT"),Variant(0)); break;
          default: return;
        }

        helper->SelectPaperSpace();
        helper->Application->ZoomAll();

        if(roadName.IsBound()) {
           roadName->set_TextString(WideString(strRoadName));
        }
        ProgressForm->Show();

        for(int j=iMin;j<=iMax;j++){
          int km = int(tbPos->Min + j);
          int meters = vStep;
          ProgressForm->Note = str.sprintf("%.d/%.d", tbPos->Position - tbPos->Min, tbPos->Max-tbPos->Min-1);
          ProgressForm->Position = j;

          try{
            tbPos->Position = j;
            // last frame printing:
            if ( j == tbPos->Max) {
               if (!chkOnly->Checked) {
                  ShowMessage("Это пауза в течении которой вы можете успеть\n"
                           "отредактировать текущую страницу в AutoCAD");
                  AnsiString temp;// = FileName+" ["+IntToStr(j/)+"+"+IntToStr(meters)+"]";
                  temp.sprintf("%s[%0.4i+%0.3i]",
                                FileName.c_str(),
                                int(j * vStep) / 100000,
                                int(j * vStep) % 100000 / 100 );
                  // save fileName for PauseLastFramePrint function, which is used to concat pdfs to one
                  fileNames.push_back(temp);
                  // save result
                  switch(printType) {
                    case ptDWG:
                      helper->ActiveDocument->SaveAs(WideString(temp));
                      break;
                    case ptPDF:
                      helper->ActiveDocument->Plot->PlotToFile(WideString(temp));
                      PauseLastFramePrint(fileNames);
                      break;
                  }
                  break;
               }
            }
            AnsiString temp;// = FileName+" ["+IntToStr(j/)+"+"+IntToStr(meters)+"]";
            temp.sprintf("%s[%0.4i+%0.3i]",
                     FileName.c_str(),
                     int(j * vStep) / 100000,
                     int(j * vStep) % 100000 / 100 );
            // save fileName for PauseLastFramePrint function, which is used to concat pdfs to one
            fileNames.push_back(temp);
            // save result
            switch(printType) {
              case ptDWG:
                helper->ActiveDocument->SaveAs(WideString(temp));
                break;
              case ptPDF:
                helper->ActiveDocument->Plot->PlotToFile(WideString(temp));
                break;
            }
          }catch(...){
             TMsgDlgButtons buttons;
                 buttons << mbRetry << mbYes << mbAbort;
                 int value = MessageDlg("Произошел сбой при печати!\nПопробывать перепечатать текущий лист и продолжить печать(Retry).\nПродолжить печать(Ignore).\nПрекратить печать(Abort).",mtWarning,buttons,0);
                 switch(value){
                    case mrRetry:
                      j--;
                    break;
                    case mrIgnore:
                      //continue;
                    break;
                    case mrAbort:
                      j = iMax;
                    break;
                 }
          }
          ProgressForm->Position = j-iMin;
          Application->ProcessMessages();
          if(GetKeyState(VK_ESCAPE)&0x0100||ProgressForm->Terminated) {
            ProgressForm->Hide();
            return;
          }
        }
        ProgressForm->Hide();
}


void __fastcall TFAutoCADPrint::Button2Click(TObject *Sender)
{
  helper = 0;

  if(AutoCAD.BindAutoCAD()){
    if(!AutoCAD.ActiveDocument){
       if(!ffirst1)ShowMessage("Не возможно подключиться к активному документу.\n\
Убедитесь что открыт хотя бы один документ.");
       helper = &AutoCAD; 
       return;
    }
  }else{
    if(!ffirst1)ShowMessage("Не возможно подключиться к AutoCAD.\nУбедитесь что он запущен.");
    return;
  }
  helper = &AutoCAD;

  helper->OnActiveDocumentBeginClose = OnDocClose;

  edtStart->Text = sPos;
  edtEnd->Text = ePos;

  TShiftState ts;
  //edtEndKeyDown(0,VK_RETURN,ts);
  if(helper->ActiveDocument.IsBound()){
      lblActiveName->Caption = AnsiString(helper->ActiveDocument->Name)
      + "["+AnsiString(helper->ActiveDocument->Path) +"]";
  }

  int topTableHeight = 0, bottomTableHeight=0, yOffset = 0, Start = 0, End = 0, Step = 100000;
  IAcadSummaryInfoPtr si = AutoCAD.ActiveDocument->SummaryInfo;
  AnsiString gTemplate = si->Keywords;
  if(gTemplate.IsEmpty()) gTemplate = "%i км";
  strRoadName = si->Title;
  AnsiString comments = si->Comments;
  if(sscanf(comments.c_str(), "%i\r\n%i\r\n%i\r\n%i\r\n%i\r\n%i",
                &topTableHeight, &bottomTableHeight, &yOffset, &Start, &End, &Step)) {
     iOffset = yOffset;
     edtTopCenter->Text = yOffset + topTableHeight/2;
     edtBottomCenter->Text = -yOffset - bottomTableHeight/2;
     edtStart->Text = Start;
     edtEnd->Text = End;
     edtStep->Text = Step;
     edtPattern->Text = gTemplate;
  }
  lblActiveName->Hint = lblActiveName->Caption;
  CheckViewports();
  DrawViewports();

  int v1,v2;
  if(TryStrToInt(edtStep->Text,v2)){
    if(TryStrToInt(edtStart->Text,v1)){
       if(v1/v2>tbPos->Max) tbPos->Max = v1/v2;
       tbPos->Min = v1/v2;               
    }
    if(TryStrToInt(edtEnd->Text,v1)){
       tbPos->Max = v1/v2;/*+(v1%v2==0?0:1);*/
    }
  }
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADPrint::edtPosChange(TObject *Sender)
{
  int v1,v2;
  if(TryStrToInt(edtPos->Text,v1)){
    if(TryStrToInt(edtStep->Text,v2)){
       tbPos->Position = v1/v2;
       edtPos2->Text = v1+v2;
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADPrint::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  helper = 0;
  TIniFile *ini = new TIniFile(strIniFileName);
  SaveIni(ini);
  delete ini;
  ClearList<TRect>(Rects);
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button4Click(TObject *Sender)
{
  if(!helper) return;
  Variant var,var2;

  try{
    var = helper->cadPoint(0,StrToFloat(edtTopCenter->Text));
    helper->ActiveDocument->ActiveSpace = acModelSpace;
    var2 = helper->ActiveDocument->Utility->GetPoint(var);
  }catch(...){
    return;
  }
  if(var2.IsArray()){
    edtTopCenter->Text = var2.GetElement(1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button5Click(TObject *Sender)
{
  if(!helper) return;
  Variant var,var2;


  try{
    var = helper->cadPoint(0,StrToFloat(edtMiddleCenter->Text));
    helper->ActiveDocument->ActiveSpace = acModelSpace;
    var2 = helper->ActiveDocument->Utility->GetPoint(var);
  }catch(...){
    return;
  }
  if(var2.IsArray()){
    edtMiddleCenter->Text = var2.GetElement(1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button6Click(TObject *Sender)
{
  if(!helper) return;
  Variant var,var2;

  try{
    var = helper->cadPoint(0,StrToFloat(edtBottomCenter->Text));
    helper->ActiveDocument->ActiveSpace = acModelSpace;
    var2 = helper->ActiveDocument->Utility->GetPoint(var);
  }catch(...){
    return;
  }
  if(var2.IsArray()){
    edtBottomCenter->Text = var2.GetElement(1);
  }    
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Panel1->SetFocus();
  switch(curState){
     float x,y;
     TRect *rect;
     if(!kHeight||!kWidth) return;
     x = (float)X/kWidth + xOffset;
     y = -(float)Y/kHeight + yOffset+_Height;
     for(int i=0;i<Rects->Count;i++){
        rect = (TRect*)Rects->Items[i];
        if(rect->Left<=x&&rect->Right>=x&&
           rect->Top<=y&&rect->Bottom>=y){
             iSelected = i;
             DrawViewports();
             return;
           }
     }
  }        
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button8Click(TObject *Sender)
{
 /* if(pnlTop->Visible) ClientHeight = GroupBox2->Height;
  else ClientHeight = pnlTop->Height + pnlBottom->Height + GroupBox2->Height;
  pnlTop->Visible = !pnlTop->Visible;

  pnlBottom->Visible = pnlTop->Visible;  */
  
  OpenDialog2->FileName = StringReplace(edtPDFBinder->Text,
         ".\\", ExtractFileDir(Application->ExeName) + "\\", TReplaceFlags());
  if(!OpenDialog2->Execute()) return;
  edtPDFBinder->Text = StringReplace(OpenDialog2->FileName,
         ExtractFileDir(Application->ExeName), ".\\", TReplaceFlags());

}
//---------------------------------------------------------------------------


void __fastcall TFAutoCADPrint::FormShow(TObject *Sender)
{
  ffirst1 = true;
  Button2->Click();
  ffirst1 = false;        
}
//---------------------------------------------------------------------------

void __fastcall TFAutoCADPrint::Button9Click(TObject *Sender)
{
    ffirst1 = true;
    Button2->Click();
    ffirst1 = false;    
    if(!helper) return;

    ReadValues();

    SaveDialog1->FileName = AutoCAD.ActiveDocument->SummaryInfo->Title;
    if(!SaveDialog1->Execute()){
      return;
    }else{
      FileName = ChangeFileExt(SaveDialog1->FileName,"");
    }

    AnsiString path = ExtractFilePath(FileName) + ChangeFileExt(ExtractFileName(FileName), "");
    AnsiString baseName = path + "_base";
    AnsiString tempName = path + "_temp";

    // создаем базовый файл
    AutoCAD.ActiveDocument->SaveAs( WideString(baseName) );
    baseName = AutoCAD.ActiveDocument->FullName;
    
    // save a copy
    AutoCAD.ActiveDocument->SaveAs( WideString(tempName) );
    tempName = AutoCAD.ActiveDocument->FullName;

    AutoCAD.ActiveDocument->ActiveSpace = acModelSpace;
    // удаляем все объекты из текущего файла
    AutoCAD.ActiveDocument->SendCommand(WideString("_ai_selall\n").c_bstr());
    Sleep(100);
    AutoCAD.ActiveDocument->SendCommand(WideString("_.erase\n").c_bstr());
    Sleep(100);
    AutoCAD.ActiveDocument->PurgeAll();

    // добавляем ссылку на базовый файл
    AutoCAD.ActiveDocument->ModelSpace->AttachExternalReference(
          WideString(baseName),
          WideString("xRef1"),
          AutoCAD.cadPoint(),
          1,1,1,0, VARIANT_FALSE
    );
    // исправялем ошибки файлов (необходимо) + уменшаем размер файла
    helper->ActiveDocument->SendCommand(WideString("_.audit _y\n"));

    // печатаем
    Print(ptDWG);

    // удаляем временный файл
    remove(tempName.c_str());

    helper->ActiveDocument->Close();

    TIniFile *ini = new TIniFile(strIniFileName);
    SaveIni(ini);
    delete ini;
}
//---------------------------------------------------------------------------



void __fastcall TFAutoCADPrint::Button12Click(TObject *Sender)
{
  pnlTop->Visible = !pnlTop->Visible;
  Button12->Caption =  pnlTop->Visible?"<--":"-->";
}
//---------------------------------------------------------------------------

#endif // WITHOUT_AUTOCAD
