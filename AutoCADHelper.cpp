#include <cstdio>
#include <iostream>
#include <algorithm>

#include "AutoCADHelper.h"
#include "MickMacros.h"

#pragma package(smart_init)


AutoCADSignBlockInfo::AutoCADSignBlockInfo(AnsiString _name,int _index)
{
   name = _name;
   index = _index;
}

int SignsCollection::GetIndexByName(AnsiString name)
{
   vector<AutoCADSignBlockInfo>::iterator i1 = signs.begin();
   while(i1!=signs.end()){
      if(i1->name == name){
         return i1->index;
      }
      i1++;
   }
   return -1;
}

AnsiString SignsCollection::GetNameByIndex(int index)
{
   vector<AutoCADSignBlockInfo>::iterator i1 = signs.begin();
   while(i1!=signs.end()){
      if(i1->index == index){
         return i1->name;
      }
      i1++;
   }
   return "";
}


void SignsCollection::Clear()
{
  signs.clear();
}


void SignsCollection::CheckExistingBlocks()
{
   static count,i;
   AnsiString str;
   if(Owner){
      Clear();
      try{
        if(Owner->ActiveDocument.IsBound()){
           count = Owner->BlocksCount;
           for(i=0;i<count;i++){
              str = Owner->Blocks[Variant(i)]->Name;
              /*if(str =="5.19.1_5.19.2"){
                 str = str;
              }*/
              signs.push_back(AutoCADSignBlockInfo(str,i));

           }
        }
      }catch(...){
        return;
      }
   }
}

void SignsCollection::AddBlock(AnsiString name, int i)
{
   signs.push_back(AutoCADSignBlockInfo(name,i));
}


int AutoCADHelper::GetTextWidth(AnsiString text, int Height)
{
    /*if(!cadActiveDocument) return -1;
    wchar_t fontName[256];
    short bold, italic, unuse;
    cadActiveDocument->ActiveTextStyle->GetFont(&fontName, &bold, &italic, &unuse, &unuse);
    BMP->Canvas->Font->Name = AnsiString(fontName);

    TFontStyles style;
    if(bold) style << fsBold;
    if(italic) style << fsItalic;
    BMP->Canvas->Font->Style = style;
    BMP->Canvas->Font->Height = Height;
                                        */
    return BMP->Canvas->TextWidth(text);
}

/**
* Create cadPoint
*/
Variant AutoCADHelper::cadPoint(double x, double y, double z)
{
   static bounds[2] = {0,2};
   Variant vArray;
   vArray = VarArrayCreate(bounds,1,varDouble);
   double *ptr = (double*)vArray.ArrayLock();
   ptr[0] = fInvertXAxe?-x:x;
   ptr[1] = fInvertYAxe?-y:y;
   ptr[2] = z;
   vArray.ArrayUnlock();
   return vArray; 
}


void AutoCADHelper::SplitString(AnsiString str, char delim, vector<AnsiString> &out, bool fRemoveEmpties)
{
    int strLenght = str.Length();
    int i,iLast = 1;
    for(i=2;i<=strLenght;i++){
      if(str[i]==delim){
         if ( !fRemoveEmpties || (fRemoveEmpties && i - iLast > 0 ) ) {
            out.push_back(str.SubString(iLast, i - iLast));
         }
         iLast = i + 1;
      }
    }
    if ( !fRemoveEmpties || (fRemoveEmpties && strLenght - iLast + 1 > 0) ) {
       out.push_back(str.SubString(iLast, strLenght - iLast + 1));
    }
}

Variant AutoCADHelper::cadPointArray(double *points, int Count,
                                    int coordCount)
{
   static j;
   static bounds[2] = {0};
   bounds[1] = Count*3-1;
   Variant vArray;
   vArray = VarArrayCreate(bounds,1,varDouble);
   double *_ptr = (double*)vArray.ArrayLock();
   switch(coordCount){
        case 1:
          for(j=0;j<Count;j++){
            _ptr[j*3] = fInvertXAxe?-points[j]:points[j];
          }
          break;
        case 2:
          for(j=0;j<Count;j++){
            _ptr[j*3] = fInvertXAxe?-points[2*j]:points[2*j];
            _ptr[j*3 + 1] = fInvertYAxe?-points[2*j+1]:points[2*j+1];
          }
          break;
        case 3:
          memcpy(_ptr,points,Count);
          break;
   }
   vArray.ArrayUnlock();

   return vArray;
}

Variant AutoCADHelper::cadArray(IDispatch **objects, int count)
{
   static j;
   static bounds[2] = {0};
   bounds[1] = count-1;
   Variant vArray;
   vArray = VarArrayCreate(bounds,1,varDispatch);
   IDispatch **_ptr = (IDispatch**)vArray.ArrayLock();

   try {
     for(j=0;j<count;j++){
        _ptr[j] = objects[j];
     }
   }catch(...) {}

   vArray.ArrayUnlock();
   return vArray;
}

Variant AutoCADHelper::cadArray(WideString *strings, int count)
{
   static j;
   static bounds[2] = {0};
   bounds[1] = count-1;
   Variant vArray;
   vArray = VarArrayCreate(bounds,1, varOleStr);
   for(j=0;j<count;j++){
      vArray.PutElement(Variant(strings[j]),j);
   }
   
   return vArray;
}

AcadLineTypePtr AutoCADHelper::getLineType(WideString name)
{
   try{
     return  cadActiveDocument->Linetypes->Item(Variant(name));
   }catch(...){
     return AcadLineTypePtr();
   }
}

AcadDocumentPtr AutoCADHelper::getActiveDocument()
{
   if(cadActiveDocument){
     AcadDocumentPtr doc =  cadActiveDocument->GetDefaultInterface();
     //return cadApplication->ActiveDocument;
     return doc;
   }else
     return AcadDocumentPtr();
}

AutoCADHelper::AutoCADHelper():fInvertYAxe(0),fInvertXAxe(0)
{
   gMakeBlockGap = 0.2;
   gMakeBlockTextHeight = 1.2;
   gMakeBlockTextOffsetX = 0.8;
   comboSignCount = 0;
   gMakeBlockTextEnable = true;
   cadActiveDocument = new TAcadDocument(0);
   cadApplication = 0;
   fApplicationRun = false;
   SignsCollection.Owner = this;
   gCopyTextObject = 0;
   gCopyText = 0;
   BMP = new Graphics::TBitmap();
}

AutoCADHelper::~AutoCADHelper()
{
   DeleteDocument(cadActiveDocument);
   delete BMP;
}

AcadApplication *AutoCADHelper::BindAutoCAD()
{
   if(FAILED(cadApplication.BindRunning())) return 0;

   if(cadApplication->Documents->Count>0 && cadApplication->ActiveDocument){
       SetActive(cadApplication->ActiveDocument);
   }

   return cadApplication;
}

AcadApplication * AutoCADHelper::RunAutoCAD(bool fVisible)
{
    if(FAILED(cadApplication.BindRunning())){
        if(FAILED(cadApplication.Bind(ProgIDToClassID("AutoCAD.Application")))){
           throw "can't run AutoCAD";
        }
    }
    cadApplication->Visible = fVisible;

    if(cadApplication->Documents->Count>0 && cadApplication->ActiveDocument){
       SetActive(cadApplication->ActiveDocument);
    }
    return cadApplication;

}

AcadApplicationPtr AutoCADHelper::getApplication()
{
   return cadApplication->Application;
}

TAcadDocument *AutoCADHelper::SetActive(AcadDocumentPtr docToConnect)
{
     cadActiveDocument->ConnectTo(docToConnect);
     return cadActiveDocument;
}

void AutoCADHelper::DeleteDocument(TAcadDocument *doc)
{
    doc->Disconnect();
}

AcadDocumentPtr AutoCADHelper::OpenDocument(AnsiString FileName,
                                           bool fSetActive, // set opened document as active document
                                           bool fReopen) // reopen document even if inside autocad documents list
{
  if(!cadApplication.IsBound()) return AcadDocumentPtr();

  int size = FileName.WideCharBufSize();
  wchar_t *str = new  wchar_t[size];
  FileName.WideChar(str,size);

  AcadDocumentPtr doc;  // used o iterate over documents;

  try{
    if(fReopen){
      // open existing document
      doc = cadApplication->Documents->Open(str,TNoParam(),TNoParam());
    }else{
      // trying to find is current document with name opened
      AcadDocuments *docs = cadApplication->Documents;
      int count = docs->Count;
      for(int i=0;i<count;i++){
         doc = docs->Item(Variant(i));
         if(!wcscmp(doc->FullName,str)){
            break;
         }
      }
      // if nothing find just open
      doc = cadApplication->Documents->Open(str,TNoParam(),TNoParam());
    }

  }__finally{
     delete[] str;
  }
  // if we should set opened document as active
  if(fSetActive && doc.IsBound()){
     SetActive(doc);
  }
  return doc;
}


AcadDocumentPtr AutoCADHelper::AddDocument(AnsiString _template)
{
   AcadDocumentPtr doc;
   if(cadApplication){
        doc = cadApplication->Documents->Add(Variant(_template));
        SetActive(doc);
   }
   return doc;
}

void __fastcall AutoCADHelper::ActiveDocumentBeginClose(TObject *sender)
{
   if(gOnActiveDocumentBeginClose) {
      gOnActiveDocumentBeginClose(sender);
   }
   if(sender == cadActiveDocument) {
      DeleteDocument(cadActiveDocument);
   }
}

void AutoCADHelper::ClearModelSpace()
{
  while(cadActiveDocument->ModelSpace->Count>0){
     cadActiveDocument->ModelSpace->Item(Variant(0))->Delete();
  }
}

AcadBlockPtr AutoCADHelper::getBlocks(int i)
{
   AcadBlockPtr block;
   if(cadActiveDocument){
     try{
         block = cadActiveDocument->Blocks->Item(Variant(i));
     }catch(...){
         cerr << "Ошибка при попытке получить доступ к " << i << "-му блоку"  << std::endl;
     }
   }
   return block;
}

AcadBlockPtr AutoCADHelper::getBlocksByName(AnsiString BlockName)
{
   AcadBlockPtr block;
   if(cadActiveDocument){
     try{
         block = cadActiveDocument->Blocks->Item(Variant(BlockName));
     }catch(...){
         cerr << "Ошибка при попытке получить доступ к '" << BlockName.c_str() << "' блоку"  << std::endl;
     }
   }
   return block;
}

int AutoCADHelper::getBlocksCount()
{
   return cadActiveDocument->Blocks->Count;
}


AcadHatchPtr AutoCADHelper::FillAreaBase(AcadHatchPtr hatch,  IDispatch **LoopObjects,
                                   int LoopObjectsCount,
                                   int HatchColor,
                                   int hatchScale)
{
   WARNING_AND_RETURN_VALUE_ON_0(hatch.IsBound(), hatch);
   hatch->AppendOuterLoop(cadArray(LoopObjects,LoopObjectsCount));
   hatch->Evaluate();
   hatch->PatternScale = hatchScale;
   hatch->color = HatchColor;
   return hatch;
}                                   

AcadHatchPtr AutoCADHelper::FillArea(IDispatch **LoopObjects,
                                   int LoopObjectsCount,
                                   int HatchColor,
                                   WideString sHatchType,
                                   int hatchScale)
{
   AcadHatchPtr hatch;
   hatch = cadActiveDocument->ModelSpace->AddHatch(0,sHatchType,Variant(true));
   FillAreaBase(hatch, LoopObjects, LoopObjectsCount, HatchColor, hatchScale);
   return hatch;
}

AcadHatchPtr AutoCADHelper::FillAreaPS(IDispatch **LoopObjects,
                                   int LoopObjectsCount,
                                   int HatchColor,
                                   WideString sHatchType,
                                   int hatchScale)
{
   AcadHatchPtr hatch;
   hatch = cadActiveDocument->PaperSpace->AddHatch(0,sHatchType,Variant(true));
   FillAreaBase(hatch, LoopObjects, LoopObjectsCount, HatchColor, hatchScale);
   return hatch;
}

AcadBlockReferencePtr AutoCADHelper::DrawBlock(WideString BlockName,
                                        double x, double y,
                                        double rotation, double scale)
{
   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument, AcadBlockReferencePtr());
   AcadBlockReferencePtr refer = cadActiveDocument->ModelSpace->InsertBlock(cadPoint(x,y),
                  BlockName,scale,scale,scale,rotation);
   return refer;
}

bool AutoCADHelper::GetPropertyPoint(  AcadBlockReferencePtr ptrBlock,
                                       AnsiString PropertyName,
                                       AutoCADPoint &point)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;  

  Variant a;
  Variant vProperities;
  AnsiString PropertyNameX = PropertyName + " X";
  AnsiString PropertyNameY = PropertyName + " Y";
  AcadDynamicBlockReferencePropertyPtr prop;
  
  bool setX = false,setY = false;

  PropertyName = PropertyName.UpperCase();
  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (AcadDynamicBlockReferencePropertyPtr)(IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyNameX){
                 setX = true;
                 a = prop->get_Value();
                 point.x = a;
              }
              else if(str ==  PropertyNameY){
                 setY = true;
                 a = prop->get_Value();
                 point.y = a;
              }
              if(setX&&setY) return true;
           }
       }
     }
  }catch(...){
      std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
      << " of object " << ptrBlock->Name  << std::endl;
  }
  return false;
}

bool AutoCADHelper::GetSubPropertyPoint(AcadBlockPtr ptrBlock, AnsiString PropertyName, AutoCADPoint &out)
{
    WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

    int count ,i;
    AcadEntityPtr subBlock;    

    count  = ptrBlock->Count;
    for(i=0;i<count;i++){
       subBlock = ptrBlock->Item(Variant(i));
       if(subBlock->EntityType == 7){
          if(GetPropertyPoint( (AcadBlockReferencePtr) subBlock, PropertyName, out))
            return true;
       }
    }
    return false;
}

bool AutoCADHelper::GetSubPropertyDouble(AcadBlockPtr ptrBlock, AnsiString PropertyName, double &out)
{
    WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

    int count ,i;
    AcadEntityPtr subBlock;    

    count  = ptrBlock->Count;
    for(i=0;i<count;i++){
       subBlock = ptrBlock->Item(Variant(i));
       if(subBlock->EntityType == 7){
          if(GetPropertyDouble( (AcadBlockReferencePtr) subBlock, PropertyName, out))
            return true;
       }
    }
    return false;
}

void AutoCADHelper::SetAttribute(AcadBlockReferencePtr ptrBlock,
                                 AnsiString PropertyName,
                                 WideString value, int rot)
{
   WARNING_AND_RETURN_ON_0(ptrBlock.IsBound());

   int count;
   AnsiString str;   

   Variant vProperities;
   Variant a;
   AcadAttributeReferencePtr attribute;

   PropertyName = PropertyName.UpperCase();
   try{
     ptrBlock->GetAttributes(vProperities);
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              attribute = (IDispatch*)vProperities.GetElement(i);
              str = attribute->TagString;
              if(str ==  PropertyName){
                 attribute->set_TextString(value);
                 if(rot!=-1)attribute->Rotation = (double)rot/180*M_PI;
                 break;
              }
           }
       }
     }
   }catch(...){
         std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
                   << " of object " << ptrBlock->Name << std::endl;
   }
}

bool AutoCADHelper::GetPropertyDouble(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName, double &out)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;

  Variant vProperities;  
  AcadDynamicBlockReferencePropertyPtr prop;

  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyName){
                 vProperities = prop->get_Value();
                 out = vProperities;
                 return true;
              }
           }
       }
     }
  }catch(...){
       std::cerr << "Failed to get '" << PropertyName.c_str() << "'"
                 << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

bool AutoCADHelper::GetPropertyVariant(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName, Variant &out)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;

  Variant vProperities;
  AcadDynamicBlockReferencePropertyPtr prop;

  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyName){
                 vProperities = prop->get_Value();
                 out = vProperities;
                 return true;
              }
           }
       }
     }
  }catch(...){
      std::cerr << "Failed to get '" << PropertyName.c_str() << "'"
           << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

bool AutoCADHelper::SetPropertyPoint(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 AutoCADPoint value)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;

  Variant vProperities;
  Variant a;
  AnsiString PropertyNameX = PropertyName + " X";
  AnsiString PropertyNameY = PropertyName + " Y";
  AcadDynamicBlockReferencePropertyPtr prop;

  bool setX = false,setY = false;

  PropertyName = PropertyName.UpperCase();
  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (AcadDynamicBlockReferencePropertyPtr)(IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyNameX){
                 setX = true;
                 prop->set_Value(Variant(double(value.x)));
              }
              else if(str ==  PropertyNameY){
                 setY = true;
                 prop->set_Value(Variant(double(value.y)));
              }
              if(setX&&setY) return true;
           }
       }
     }
  }catch(...){
         std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
                   << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

bool AutoCADHelper::SetPropertyDouble(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                         double value)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;

  Variant vProperities;
  AcadDynamicBlockReferencePropertyPtr prop;

  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyName){
                 prop->set_Value(Variant(value));
                 return true;
              }
           }
       }
     }
  }catch(...){
         std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
                   << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

bool AutoCADHelper::SetPropertyListVariant(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 Variant value)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);

  int count;
  AnsiString str;

  Variant vProperities;
  AcadDynamicBlockReferencePropertyPtr prop;

  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyName){
                 prop->set_Value(value);
                 return true;
              }
           }
       }
     }
  }catch(...){
         std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
                   << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

bool AutoCADHelper::SetPropertyList(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 short value)
{
  WARNING_AND_RETURN_VALUE_ON_0(ptrBlock.IsBound(), false);  

  int count;
  AnsiString str;

  Variant vProperities;
  AcadDynamicBlockReferencePropertyPtr prop;

  try{
     vProperities = ptrBlock->GetDynamicBlockProperties();
     if(vProperities.IsArray()){
       count = vProperities.ArrayHighBound(1)+1;
       if(count>0){
           for(int i=0;i<count;i++){
              prop = (IDispatch*)vProperities.GetElement(i);
              str = prop->PropertyName;
              if(str ==  PropertyName){
                 prop->set_Value(Variant(value));
                 return true;
              }
           }
       }
     }
  }catch(...){
         std::cerr << "Failed to set property '" << PropertyName.c_str() << "'"
                   << " of object " << ptrBlock->Name << std::endl;
  }
  return false;
}

AcadLayoutPtr AutoCADHelper::AddPaperSpace(WideString name)
{
  try{
    return cadActiveDocument->Layouts->Add(name);
  }catch(...){
    std::cerr << "Failed to add PaperSpace '" << AnsiString(name).c_str() << "'" << std::endl;
  }
  return AcadLayoutPtr();
}

bool AutoCADHelper::SetupViewport(AcadLayoutPtr layout, double x, double y,
                                double width, double height)
{
   AcadPViewportPtr viewport;
   cadActiveDocument->set_ActiveSpace(acPaperSpace);
   cadActiveDocument->set_ActiveLayout(layout);
   try{
     viewport = cadActiveDocument->ActiveViewport;
     viewport->set_Center(cadPoint(x+width/2, y+ height/2));
     viewport->Width = width;
     viewport->Height = height;
   }catch(...){
      std::cerr << "Failed to setup ViewPort" << std::endl;
      return false;
   }
   return true;
}

void AutoCADHelper::CheckExistingBlocks()
{
   SignsCollection.CheckExistingBlocks();
}

bool AutoCADHelper::BindToActiveDocument()
{
   TAcadDocument *doc;
   try{
     doc = SetActive(cadApplication->ActiveDocument);
   }catch(...){
     std::cerr << "Не могу подключиться к активному документу T_T" << std::endl 
               << "Скорее всего AutoCAD не запущен, либо нету активных документов" << std::endl;
     return false;
   }
   return true;
}

void AutoCADHelper::SetBACKGROUNDPLOT_ZERO()
{
   SendCommand("BACKGROUNDPLOT 0\n");
}

void AutoCADHelper::SelectPaperSpace()
{
   cadActiveDocument->set_ActiveSpace(acPaperSpace); 
}

void AutoCADHelper::SendCommand(WideString command)
{
   cadActiveDocument->SendCommand(command);
}

AcadLayoutPtr AutoCADHelper::SetAsActiveLayout(Variant index)
{
   AcadLayoutPtr layout;
   try{
     layout = cadActiveDocument->Layouts->Item(index);
     cadActiveDocument->set_ActiveLayout(layout);
   }catch(...){
     std::cerr << "Failed to set layout with number '" << index << "' as active" << std::endl;
   }
   return layout;
}


bool AutoCADHelper::PrintActiveLayoutToFile(WideString FileName)
{
  try{
    cadActiveDocument->Plot->PlotToFile(FileName);
  }catch(...){
    std::cerr << "Failed to print active layout to file: "
              << AnsiString(FileName).c_str() << std::endl;
  }
  return true;
}

bool AutoCADHelper::PrintLayoutsToFile(WideString FileName, int* arrayofindexes, int count)
{
   WideString *names = new WideString[count];
   try{
     for(int i=0;i<count;i++){
        names[i] = WideString(cadActiveDocument->Layouts->Item(Variant(arrayofindexes[i]))->Name) + "12";
     }
     Variant array;
     Variant a1;
     array = cadArray(names,count);
     cadActiveDocument->Plot->SetLayoutsToPlot(a1);
     cadActiveDocument->Plot->PlotToFile(FileName);
   }catch(...){
      std::cerr << "Failed to print layouts to file: "
              << AnsiString(FileName).c_str() << std::endl;
      delete[] names;
      return false;
   }
   delete[] names;
   return true;
}

void AutoCADHelper::BeginMSpace(AcadPViewportPtr viewport)
{
     WARNING_AND_RETURN_ON_NULL( viewport.IsBound() );
     viewport->Display(True);
     AcadDocumentPtr doc = viewport->Document;
     doc->set_MSpace(True);
}

void AutoCADHelper::EndMSpace(AcadPViewportPtr viewport)
{
     WARNING_AND_RETURN_ON_NULL( viewport.IsBound() );
     AcadDocumentPtr doc = viewport->Document;
     doc->set_MSpace(False);
     viewport->Display(False);
}

bool AutoCADHelper::SetupActiveViewportZoomWindow(double x, double y,
                                double width, double height)
{
   AcadPViewportPtr viewport;
   cadActiveDocument->set_ActiveSpace(acPaperSpace);
   try{
     viewport = (IDispatch*)Variant((IDispatch*)cadActiveDocument
                  ->GetDefaultInterface()).OlePropertyGet("ActivePViewport");

     BeginMSpace(viewport);
       cadApplication->ZoomWindow(cadPoint(x,y),cadPoint(x+width,y+height));
     EndMSpace(viewport);

     cadApplication.ZoomExtents();
   }catch(...){
      std::cerr << "Failed to setup zoom window" << std::endl;
      return false;
   }
   return true;
}

bool AutoCADHelper::SetupActiveViewportZoomScale(double ZoomFactor)
{
   AcadPViewportPtr viewport;
   cadActiveDocument->set_ActiveSpace(acPaperSpace);
   try{
     viewport = (IDispatch*)Variant((IDispatch*)cadActiveDocument
                  ->GetDefaultInterface()).OlePropertyGet("ActivePViewport");

     BeginMSpace(viewport);
       cadApplication->ZoomScaled(ZoomFactor,acZoomScaledAbsolute);
     EndMSpace(viewport);

     cadApplication->ZoomExtents();
   }catch(...){
      std::cerr << "Failed to setup zoom window" << std::endl;   
      return false;
   }
   return true;
}

bool AutoCADHelper::SetupActiveViewportZoomCenter(double x, double y, double scale)
{
   AcadPViewportPtr viewport;
   cadActiveDocument->set_ActiveSpace(acPaperSpace);
   try{
     viewport = (IDispatch*)Variant((IDispatch*)cadActiveDocument
                  ->GetDefaultInterface()).OlePropertyGet("ActivePViewport");

     BeginMSpace(viewport);
       cadApplication->ZoomCenter(cadPoint(x,y),1);
     EndMSpace(viewport);

     cadApplication->ZoomExtents();
   }catch(...){
      std::cerr << "Failed to setup zoom window" << std::endl;   
      return false;
   }
   return true;
}

void AutoCADHelper::AddPaperSpace(AnsiString name, double x, double y,
                                        double width, double height)
{
   AcadPViewportPtr viewport;
   AcadLayoutPtr layout = cadActiveDocument->Layouts->Add(WideString(name));

   cadActiveDocument->set_ActiveSpace(acPaperSpace);
   cadActiveDocument->set_ActiveLayout(layout);

   SetupActiveViewportZoomWindow(x, y, width, height);
   
   cadActiveDocument->PurgeAll();
}

AcadTextPtr AutoCADHelper::DrawText(AnsiString str, double height, AcAlignment alignment,
                                  double x, double y, double rotation)
{
   AcadTextPtr text;
   text = cadActiveDocument->ModelSpace->AddText(WideString(str),cadPoint(x,y),height);
   text->Rotate(cadPoint(x,y),rotation);
   text->Alignment = alignment;
   text->set_TextAlignmentPoint(cadPoint(x,y));
   return text;
}

AcadTextPtr AutoCADHelper::DrawTextPS(AnsiString str, double height,
                                  double x, double y, double rotation)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadTextPtr());
   AcadTextPtr text;
   text = cadActiveDocument->PaperSpace->AddText(WideString(str),cadPoint(x,y),height);
   text->Rotate(cadPoint(x,y),rotation);
   return text;
}

AcadLinePtr AutoCADHelper::DrawLine(double x1, double y1, double x2, double y2)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadLinePtr());
   return cadActiveDocument->ModelSpace->AddLine(cadPoint(x1,y1),cadPoint(x2,y2));
}

AcadLinePtr AutoCADHelper::DrawLinePS(double x1, double y1, double x2, double y2)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadLinePtr());
   return cadActiveDocument->PaperSpace->AddLine(cadPoint(x1,y1),cadPoint(x2,y2));
}

AcadPolylinePtr AutoCADHelper::DrawPolyLine(double *array, int count, int coordCount)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadPolylinePtr());
   return cadActiveDocument->ModelSpace->AddPolyline(cadPointArray(array,count, coordCount));
}

AcadPolylinePtr AutoCADHelper::DrawPolyLinePS(double *array, int count, int coordCount)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadPolylinePtr());
   return cadActiveDocument->PaperSpace->AddPolyline(cadPointArray(array,count, coordCount));
}

AcadEllipsePtr AutoCADHelper::DrawEllipse(double centerX, double centerY, double MajorAxis,double MinorAxis)
{
//    WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadEllipsePtr());

    double temp;
    Variant majAx;

    if(MinorAxis<0)MinorAxis = -MinorAxis;
    if(MajorAxis<0)MajorAxis = -MajorAxis;

    if(MajorAxis<MinorAxis){
       majAx = cadPoint(0,-MinorAxis);
       temp = MajorAxis / MinorAxis;
    }else{
       majAx = cadPoint(MajorAxis);
       temp = MinorAxis / MajorAxis;
    }

    AcadEllipsePtr ellipse = cadActiveDocument->ModelSpace->AddEllipse(cadPoint(centerX,centerY),
                 majAx,Variant(temp));
    if(MajorAxis<MinorAxis){
       //ellipse->Rotate(cadPoint(centerX,centerY),M_PI_2);
    }
    return ellipse;
}

AcadPolylinePtr AutoCADHelper::DrawRect(double centerX, double centerY, double width, double height)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadPolylinePtr());

   double rect[10];
   double width2,height2;
   width2 = width*0.5;
   height2 = height*0.5;

   rect[0] = centerX - width2;
   rect[1] = centerY - height2;

   rect[2] = centerX + width2;
   rect[3] = centerY - height2;

   rect[4] = centerX + width2;
   rect[5] = centerY + height2;

   rect[6] = centerX - width2;
   rect[7] = centerY + height2;

   rect[8] = centerX - width2;
   rect[9] = centerY - height2;

   return DrawPolyLine(rect,5,2);
}

AcadPolylinePtr AutoCADHelper::DrawRectPS(double centerX, double centerY, double width, double height)
{
//    WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadPolylinePtr());
    double rect[10];
    double width2,height2;

    width2 = width*0.5;
    height2 = height*0.5;

    rect[0] = centerX - width2;
    rect[1] = centerY - height2;

    rect[2] = centerX + width2;
    rect[3] = centerY - height2;

    rect[4] = centerX + width2;
    rect[5] = centerY + height2;

    rect[6] = centerX - width2;
    rect[7] = centerY + height2;

    rect[8] = centerX - width2;
    rect[9] = centerY - height2;

    return DrawPolyLinePS(rect,5,2);
}

AcadArcPtr AutoCADHelper::DrawArc(double centerX, double centerY,
                                double radius, double sAngle, double eAngle)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadArcPtr());
   return cadActiveDocument->ModelSpace->AddArc(cadPoint(centerX,centerY),
                                                        radius,sAngle,eAngle);
}

AcadCirclePtr AutoCADHelper::DrawCircle(double centerX, double centerY, double radius)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadCirclePtr());
   return cadActiveDocument->ModelSpace->AddCircle(cadPoint(centerX,centerY),radius);
}

AcadCirclePtr AutoCADHelper::DrawCirclePS(double centerX, double centerY, double radius)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadCirclePtr());
   return cadActiveDocument->PaperSpace->AddCircle(cadPoint(centerX,centerY),radius);
}

void AutoCADHelper::Regen()
{
//   WARNING_AND_RETURN_ON_0(cadActiveDocument);
   cadActiveDocument->Regen(acAllViewports);
}

AcadLineTypePtr AutoCADHelper::LoadLineType(WideString LineTypeName,
                                          WideString FileName,
                                          WideString ShapeFileName)
{
//   WARNING_AND_RETURN_VALUE_ON_0(cadActiveDocument.IsBound(), AcadLineTypePtr());
   try{
       if(!ShapeFileName.IsEmpty()){
          cadActiveDocument->LoadShapeFile(ShapeFileName);
       }
       cadActiveDocument->Linetypes->Load(LineTypeName, FileName);
       return cadActiveDocument->Linetypes->Item(Variant(LineTypeName));
   }catch(...){
       std::cerr << "failed to get linetype '" << AnsiString(LineTypeName).c_str() << "'";
   }
   return AcadLineTypePtr();
}

WideString AutoCADHelper::GetSignName(AnsiString signName)
{
   int i,length,count;
   length = signName.Length();
   count = 0;
   for(i=1;i<=length;i++){
      if(signName[i] == '.'){
         if(count == 2){
            return signName.SubString(1,i-1);
         }
         count++;
      }
   }
   return signName;
}


void AutoCADHelper::SetSignLabels(AcadBlockReferencePtr block, WideString str)
{
  if(str.IsEmpty()) return;
  vector<AnsiString> labels;
  SplitString(AnsiString(str), '\\', labels);
  for (int i = 0; i < labels.size(); ++i) {
     SetAttribute(block,"LABEL"+(i==0?AnsiString(""):IntToStr(i)),labels[i]);
  }
}

void AutoCADHelper::ResetBlocksCollection()
{
   SignsCollection.Clear();
}

bool AutoCADHelper::IsLarger(AnsiString name)
{
  return false;
}


AcadBlockPtr AutoCADHelper::MakeCombineBlock(WideString block1, WideString label1,
                                             WideString block2, WideString label2,
                                             WideString block3, WideString label3,
                                             WideString block4, WideString label4)
{
    int subBlocksCount;
    int i, blockIndex;
    bool ffind, fHaveNoLabels;
    int count;
    double maxWidth,maxWidth2,width, block3Width, height,height2, fullHeight, TopOffset;
    float offset,scale;
    const float GlobalScale = 1.5; 
    Variant tVar;

    AutoCADPoint p1(0,0), p2(0,0), pTop;

    p1.x = p1.y = 0;
    p2.x = p2.y = 0;
    pTop.x = 0;
    fullHeight = 0;
    AcadBlock * newBlock = 0;

    count = (block1.IsEmpty()?0:1) + (block2.IsEmpty()?0:1)
             + (block3.IsEmpty()?0:1) + (block4.IsEmpty()?0:1);
    if(count<2) return newBlock;

    maxWidth = maxWidth2 = 0;

    AcadBlockPtr *block = new AcadBlockPtr[count];
    AutoCADPoint *blockspos = new AutoCADPoint[count];

    AcadBlockReferencePtr subBlock;
    AcadEntityPtr entity;
    WideString newBlockName;

    bool fCheckLostBlock = false;

    for(int i=0;i<count;i++){
       switch(i){
          case 0:
            try{
                block[0] = cadActiveDocument->Blocks->Item(Variant(block1));
            }catch(...){
                fCheckLostBlock = true;
                if(!strLostBlocks.Pos(block1)){
                  strLostBlocks+="\n"+block1;
                }
            }
            newBlockName+=block1+ ((i==count-1)?"":"_");
          break;
          case 1:
          
            try{
                block[1] = cadActiveDocument->Blocks->Item(Variant(block2));
            }catch(...){
                fCheckLostBlock = true;
                if(!strLostBlocks.Pos(block2)){
                  strLostBlocks+="\n"+block2;
                }
            }

            newBlockName+=block2 + ((i==count-1)?"":"_");
          break;
          case 2:
          
            try{
             block[2] = cadActiveDocument->Blocks->Item(Variant(block3));
            }catch(...){
                fCheckLostBlock = true;
                if(!strLostBlocks.Pos(block3)){
                  strLostBlocks+="\n"+block3;
                }
            }

            newBlockName+=block3 + ((i==count-1)?"":"_");
          break;
          case 3:
            try{
                block[3] = cadActiveDocument->Blocks->Item(Variant(block4));
            }catch(...){
                fCheckLostBlock = true;
                if(!strLostBlocks.Pos(block4)){
                  strLostBlocks+="\n"+block4;
                }
            }
            newBlockName+=block4 + ((i==count-1)?"":"_");
          break;
       }
    }

    if(fCheckLostBlock) return newBlock;

    fHaveNoLabels = label1.IsEmpty()&&label2.IsEmpty()&&label3.IsEmpty()&&label4.IsEmpty();

    if((blockIndex=SignsCollection.GetIndexByName(newBlockName))!=-1&&fHaveNoLabels){
       return BlocksByName[newBlockName];
    }

    if(!fHaveNoLabels){
      newBlockName+="#"+IntToStr(comboSignCount++);
    }
    

    blockspos[0] = p1;
    subBlocksCount = block[0]->Count;
    ffind = false;
    for(i=0;i<subBlocksCount;i++){
       entity = block[0]->Item(Variant(i));
       if(entity->EntityType == 7){
          subBlock=entity;
          if(GetPropertyDouble(subBlock,"Height",height)){
              if(GetPropertyDouble(subBlock,"Width",width)){
                scale = subBlock->XScaleFactor;
                height*=scale;
                width*=scale;                
                maxWidth = width>maxWidth?width:maxWidth;
                ffind = true;
                break;
              }
          }
       }
    }

    if(!ffind) return newBlock;

    TopOffset = height/2;
    fullHeight+=height;

    ffind = false;
    subBlocksCount = block[1]->Count;
    for(i=0;i<subBlocksCount;i++){
       entity = block[1]->Item(Variant(i));
       if(entity->EntityType == 7){
          subBlock = entity;
          if(GetPropertyDouble(entity,"Height",height2)){
            if(GetPropertyDouble(entity,"Width",width)){
                scale = subBlock->XScaleFactor;
                height2*=scale;
                width*=scale;
                maxWidth = width>maxWidth?width:maxWidth;               
                ffind = true;
                break;
            }
          }
       }
    }
    if(!ffind) return newBlock;

    fullHeight+=height2;

    p2.y = (p1.y - height/2 - height2/2-gMakeBlockGap);
    p1 = p2;
    height = height2;
    blockspos[1] = p2;

    if(count>2){
        ffind = false;
        subBlocksCount = block[2]->Count;
        for(i=0;i<subBlocksCount;i++){
           entity = block[2]->Item(Variant(i));
           if(entity->EntityType == 7){
              subBlock = entity;
              if(GetPropertyDouble(entity,"Height",height2)){
                if(GetPropertyDouble(entity,"Width",block3Width)){
                    scale = subBlock->XScaleFactor;
                    height2*=scale;
                    block3Width*=scale;
                    maxWidth = block3Width>maxWidth?block3Width:maxWidth;
                    ffind = true;
                    break;
                }
              }
           }
        }
        if(!ffind) return newBlock;
        fullHeight+=height2;

        p2.y = (p1.y - height/2 - height2/2-gMakeBlockGap);
        p1 = p2;
        height = height2;
        blockspos[2] = p2;

        if(count > 3){
          ffind = false;
          subBlocksCount = block[3]->Count;
          for(i=0;i<subBlocksCount;i++){
             entity = block[3]->Item(Variant(i));
             if(entity->EntityType == acBlockReference){
                subBlock = entity;
                if(GetPropertyDouble(entity,"Height",height2)){
                  if(GetPropertyDouble(entity,"Width",block3Width)){
                      scale = subBlock->XScaleFactor;
                      height2*=scale;
                      block3Width*=scale;
                      maxWidth = block3Width>maxWidth?block3Width:maxWidth;
                      ffind = true;
                      break;
                  }
                }
             }
          }
          if(!ffind) return newBlock;
          fullHeight+=height2;

          p2.y = (p1.y - height/2 - height2/2-gMakeBlockGap);
          p1 = p2;
          height = height2;
          blockspos[3] = p2;
        }
    }

    offset =  TopOffset - (fullHeight)/2;

    newBlock = cadActiveDocument->Blocks->Add(cadPoint(0,offset),WideString(newBlockName));
    subBlock = newBlock->InsertBlock(cadPoint(blockspos[0].x,blockspos[0].y),
        WideString(block1),1,1,1,0,TNoParam());
    if(!label1.IsEmpty())
       SetSignLabels(subBlock,SignLabelParser(block1, label1));
    subBlock = newBlock->InsertBlock(cadPoint(blockspos[1].x,blockspos[1].y),
        WideString(block2),1,1,1,0,TNoParam());
    if(!label2.IsEmpty())
       SetSignLabels(subBlock,SignLabelParser(block1,label2));
    if(count>2){
        subBlock = newBlock->InsertBlock(cadPoint(blockspos[2].x,blockspos[2].y),
                WideString(block3),1,1,1,0,TNoParam());
        if(!label3.IsEmpty())
           SetSignLabels(subBlock,SignLabelParser(block1,label3));
        if(count>3){
          subBlock = newBlock->InsertBlock(cadPoint(blockspos[3].x,blockspos[3].y),
                WideString(block4),1,1,1,0,TNoParam());
          if(!label4.IsEmpty())
             SetSignLabels(subBlock,SignLabelParser(block1,label4));
        }
    }
    
    delete[] block;
    delete[] blockspos;

    try{
       SignsCollection.AddBlock(newBlock->Name,cadActiveDocument->Blocks->Count-1);
    }catch(...){
       ShowMessage("Error ON:\nSignsCollection.AddBlock(newBlock);");
    }
    return newBlock;
}

void AutoCADHelper::DrawRepeatTextInterval(WideString str, float sPosX, float ePosX,
                                 float PosY, float TextHeight, float step)
{
   if(sPosX<0) sPosX = 0;
   if(ePosX<0||ePosX == sPosX) return;

   int iMax = (int)(ePosX/step)+1;
   int iMin = (int)(sPosX/step)+1;

   if(iMin!=iMax){
     // draw repeat text
     // draw head
     if(sPosX<iMin*step){
         DrawText(str, TextHeight, acAlignmentMiddle, sPosX + (iMin*step-sPosX)/2, PosY);
     }
     // draw body
     for(int i=iMin;i<iMax-1;i++){
         DrawText(str, TextHeight, acAlignmentMiddle, i*step + step/2, PosY);
     }
     // draw tail
     if(ePosX>(iMax-1)*step){
        DrawText(str, TextHeight, acAlignmentMiddle, (iMax-1)*step + (ePosX-(iMax-1)*step)/2, PosY);
     }
   }else{
     // draw text only once
     DrawText(str, TextHeight, acAlignmentMiddle, sPosX + (ePosX - sPosX)/2, PosY);
   }
}

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

AutoCADTable::~AutoCADTable()
{
    if(emptyMin) delete[] emptyMin;
    emptyMin = 0;
}


AutoCADTable::AutoCADTable(AutoCADHelper *Owner, float _TableWidth, int _RowsCount,
                                float _RowHeight, AutoCADPoint _LeftTop, float _HeaderWidth)
{
  gOwner = Owner;
  emptyMin = 0;
  gFillGapsBegin = 0;
  MinViewFontSize = 0;    
  gaps = 0;  
  gFillGaps = 0;
  LeftTop = _LeftTop;
  RowslEnd = 0;
  RowsCount = _RowsCount;
  FillGaps[-1] = true;
  RowHeight = _RowHeight;
  HeaderWidth = _HeaderWidth;
  TableWidth = _TableWidth;
  gRepeatInterval = 0;
  gIsHI = false;

  kPadding = 0.9;
}

void OrderGaps(AutoCADPoint p1,AutoCADPoint p2)
{
   if(p1.x>p2.x){}
}

void AutoCADTable::FillLastGaps(float step, int iRow)
{
   AutoCADPointGapGreater great;
  // stable_sort(gaps[iRow].begin(),gaps[iRow].end(),great);
   if(iRow==-1){
     for(int i=0;i<RowsCount;i++){
        if(gFillGaps[i]) DrawRepeatEmptyInterval(i,RowslEnd[i],TableWidth,step,true);
     }
   }else{
     DrawRepeatEmptyInterval(iRow,RowslEnd[iRow],TableWidth,step,true);
   }
}

void AutoCADTable::DrawSnakeBorder(int iRow, float *xOffsets, int count)
{
   int iTemp,i,odd;
   double yTop,yBottom,yPos,*points;

   yTop = gLeftTop.y - RowOffsetY(iRow);
   yBottom = gLeftTop.y - RowOffsetY(iRow+1);

   points = new double[count*4];

   for(i=0;i<count;i++){
      odd = i%2;
      iTemp = i*4;
      points[iTemp] = points[iTemp + 2] = xOffsets[i]<0?0:xOffsets[i];
      points[iTemp+1] = odd?yTop:yBottom;
      points[iTemp+3] = odd?yBottom:yTop;
   }

   gOwner->DrawPolyLine(points,count*2,2);

   delete[] points;
}

void AutoCADTable::DrawSnakeBorder(int iRow, float sPos, float ePos)
{
   float pos[2] = {sPos, ePos};
   DrawSnakeBorder(iRow,pos,2);
}

void AutoCADTable::DrawTable()
{
   int count;
   double *points = 0;

    /*ROWS */
   if(gRowsCount%2==0){
     count = (7+(gRowsCount/2-1)*4);
     points = new double[count*2+2 + (gHeaderWidth>0?4:0)];

     double xPosLeft = -(gIsHI?0:gHeaderWidth);
     double xPos = xPosLeft;
     double yPos = gLeftTop.y;

     points[0] = gLeftTop.x + gTableWidth;
     points[1] = gLeftTop.y - iRowsFullHeight;

     points[2] = gLeftTop.x + gTableWidth;
     points[3] = gLeftTop.y;

     for(int i=2;i<count;i++){
        points[i*2] = xPos + gLeftTop.x;
        if(i%2==1){
           yPos-=gRowHeight;
           if(xPos==gTableWidth){
             xPos = xPosLeft;
           }else{
             xPos = gTableWidth;
           }
        }
        points[i*2+1] = yPos;
     }

     points[count*2] =  points[4];
     points[count*2+1] = points[5];

     if(gHeaderWidth){
        points[count*2+2] = gLeftTop.x+(gIsHI?gHeaderWidth:0);
        points[count*2+3] = gLeftTop.y;

        points[count*2+4] = gLeftTop.x+(gIsHI?gHeaderWidth:0);
        points[count*2+5] = gLeftTop.y - iRowsFullHeight;
     }
     
     gOwner->DrawPolyLine(points, count+1+(gHeaderWidth>0?2:0), 2);
   
     delete[] points;
   }else{
     count = (7+(gRowsCount/2)*4);
     points = new double[count*2+2 + (gHeaderWidth>0?4:0)];

     double xPosLeft = -(gIsHI?0:gHeaderWidth);
     double xPos = xPosLeft;
     double yPos = gLeftTop.y - iRowsFullHeight;

     points[0] = gLeftTop.x + xPosLeft;
     points[1] = yPos;

     points[2] = gLeftTop.x + xPosLeft;
     points[3] = gLeftTop.y;

     points[4] = gLeftTop.x + gTableWidth;
     points[5] = gLeftTop.y;

     points[6] = gLeftTop.x + gTableWidth;
     points[7] = yPos;

     for(int i=4;i<count;i++){
        points[i*2] = xPos + gLeftTop.x;
        if(i%2==1){
           yPos+=gRowHeight;
           if(xPos==gTableWidth){
             xPos = xPosLeft;
           }else{
             xPos = gTableWidth;
           }
        }
        points[i*2+1] = yPos;
     }

     points[count*2] =  points[4];
     points[count*2+1] = points[5];

     if(gHeaderWidth){
        points[count*2+2] = gLeftTop.x+(gIsHI?gHeaderWidth:0);
        points[count*2+3] = gLeftTop.y;

        points[count*2+4] = gLeftTop.x+(gIsHI?gHeaderWidth:0);
        points[count*2+5] = gLeftTop.y - iRowsFullHeight;
     }
     
     gOwner->DrawPolyLine(points, count+1+(gHeaderWidth>0?2:0), 2);
   
     delete[] points;
   }

}

AcadLinePtr AutoCADTable::DrawBorder(int offset, int iRow)
{
   if(offset>TableWidth) return AcadLinePtr();
   int iS = iRow==-1?gLeftTop.y:gLeftTop.y-iRow*gRowHeight;
   int iE = iRow==-1?gLeftTop.y-iRowsFullHeight:gLeftTop.y-(iRow+1)*gRowHeight;
   
   return gOwner->DrawLine(gLeftTop.x + offset, iS, gLeftTop.x +offset,iE);
}

AcadHatchPtr AutoCADTable::FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch,
                                float scale, int color)
{
    double dblPL[10];

    dblPL[0] = offsetBegin;
    dblPL[1] = gLeftTop.y - RowOffsetY(iRow);

    dblPL[2] = offsetEnd;
    dblPL[3] = gLeftTop.y - RowOffsetY(iRow);

    dblPL[4] = offsetEnd;
    dblPL[5] = gLeftTop.y - RowOffsetY(iRow+1);

    dblPL[6] = offsetBegin;
    dblPL[7] = gLeftTop.y - RowOffsetY(iRow+1);

    dblPL[8] = offsetBegin;
    dblPL[9] = gLeftTop.y - RowOffsetY(iRow);

    AcadPolylinePtr pl[1];
    pl[0] = gOwner->DrawPolyLine(dblPL, 5, 2);

    AcadHatchPtr hatch = gOwner->FillArea((IDispatch**)pl, 1, 0, strHatch);
    
    AcadAcCmColor *_color =  hatch->TrueColor;
    _color->set_ColorIndex(color);
    hatch->set_TrueColor(_color);

    hatch->PatternScale = scale;

    return hatch;
}

AcadHatchPtr AutoCADTable::FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch,
                                float scale, long colorR, long colorG, long colorB)
{
    AcadHatchPtr hatch = FillArea(iRow, offsetBegin, offsetEnd, strHatch, scale, 0);
    
    AcadAcCmColor *color =  hatch->TrueColor;
    color->SetRGB(colorR, colorG, colorB);
    hatch->set_TrueColor(color);

    return hatch;    
}

void AutoCADTable::DrawEmpty(int iRow, float offsetBegin, float offsetEnd,
                             bool fWithBorders, bool fWithoutFill, bool fInc )
{
   if(offsetBegin<0) offsetBegin = 0;
   if(offsetEnd<0) offsetEnd = 0;
   if(EmptyFill.IsEmpty() || fWithoutFill) {  // draw cross line if EmptyFIll is not set, or forced fWithoutFill
      DrawLine(iRow,offsetBegin,fInc?0:1,offsetEnd,fInc?1:0);
   } else {
      FillArea(iRow, offsetBegin, offsetEnd, EmptyFill, EmptyFillScale);
   }
   if(fWithBorders){
      DrawSnakeBorder(iRow, offsetBegin, offsetEnd);
   }
}


AcadTextPtr AutoCADTable::DrawText(int row, float offset,
                                 AnsiString str, float kProp)
{
   kProp = kProp>1?1:kProp;
   float xOffset = gLeftTop.x + offset;
   float yOffset = gLeftTop.y-(RowOffsetY(row) + gRowHeight*0.5);
   AcadTextPtr text = gOwner->DrawText(WideString(str),
                                       kProp*gRowHeight,
                                       acAlignmentMiddleLeft,
                                       xOffset,
                                       yOffset);
   return text;
}


void AutoCADTable::DrawHeaderText(int row,AnsiString str, float kProp)
{
   DrawTextInBorders(row,gIsHI?0:-gHeaderWidth,
                         gIsHI?gHeaderWidth:0,WideString(str),false, kProp);
}


void AutoCADTable::DrawRepeatEmptyInterval(int iRow,
                                float sPos, float ePos, float step,
                                bool fWithBorders, bool fWithoutFill, bool fInc)
{
   if(emptyMin) {
      if ( emptyMin[iRow] > ePos ) {
         return;
      }
      if ( emptyMin[iRow] > sPos ) {
         sPos = emptyMin[iRow];
         if (sPos > ePos) {
            return;
         }
      }
   }

   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos){
      if(fWithBorders){
         DrawBorder(sPos,iRow);
      }
      return;
   }

   int iMin = (int)(sPos/step) + 1;
   int iMax = (int)(ePos/step) + 1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   float *pos = new float[count];
   pos[0] = sPos;   

   if(iMin!=iMax){
     if(sPos<iMin*step){
         DrawEmpty(iRow,sPos,iMin*step,false,fWithoutFill, fInc);
         pos[counter++] = iMin*step;
     }
     for(int i=iMin;i<iMax-1;i++){
         DrawEmpty(iRow,i*step,(i+1)*step,false,fWithoutFill, fInc);
         pos[counter++] = (i+1)*step;
     }
     if(ePos>(iMax-1)*step){
        DrawEmpty(iRow,(iMax-1)*step,ePos,false,fWithoutFill, fInc);
        pos[counter++] = ePos;
     }
     if(fWithBorders)DrawSnakeBorder(iRow,pos,counter);
   }else{
     DrawEmpty(iRow, sPos, ePos, false, fWithoutFill, fInc);
     if(fWithBorders)DrawSnakeBorder(iRow,sPos,ePos);
   }
   delete[] pos;
}


void AutoCADTable::DrawRepeatTextInterval(int iRow, AnsiString str,
                                float sPos, float ePos,
                                AnsiString (*func)(float, float),
                                float step, bool fWithBorders, float kProp)
{
   if(iRow<0) return;

   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   AnsiString tStr;

   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos) return;

   int iMax = (int)(ePos/step)+1;
   int iMin = (int)(sPos/step)+1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   float *pos = new float[count];
   pos[0] = sPos;


   if(gFillGaps[iRow]&&RowslEnd[iRow]<=sPos){
     DrawRepeatEmptyInterval(iRow,RowslEnd[iRow],sPos,step,true);
   }

   emptyMin[iRow] = max(max(emptyMin[iRow], sPos),ePos);

   float min,max;

   if(iMin!=iMax){
     if(sPos<iMin*step){
         if(func){
             min = sPos;
             max = iMin*step;
             if(!str.IsEmpty()){
                tStr = str+"\n"+func(min,max);
             }else{
                tStr=func(min,max);
             }
             DrawTextInBorders(iRow,min,max,tStr,false,kProp);
         }else{
             if(!str.IsEmpty())DrawTextInBorders(iRow,sPos,iMin*step,str,false,kProp);
         }
         pos[counter++] = iMin*step;
     }
     for(int i=iMin;i<iMax-1;i++){
         if(func){
           min = i*step;
           max = (i+1)*step;
           if(!str.IsEmpty()){
              tStr = str+"\n"+func(min,max);
           }else{
              tStr=func(min,max);
           }
           DrawTextInBorders(iRow,min,max,tStr,false,kProp);
         }else{
           if(!str.IsEmpty())DrawTextInBorders(iRow,i*step,(i+1)*step,str,false,kProp);
         }
         pos[counter++] = (i+1)*step;
     }
     if(ePos>(iMax-1)*step){
        if(func){
           min = (iMax-1)*step;
           max = ePos;
           if(!str.IsEmpty()){
              tStr = str+"\n"+func(min,max);
           }else{
              tStr=func(min,max);
           }
           DrawTextInBorders(iRow,min,max,tStr,false,kProp);
        }else{
           if(!str.IsEmpty())DrawTextInBorders(iRow,(iMax-1)*step,ePos,str,false,kProp);
        }
        pos[counter++] = ePos;
     }
     if(fWithBorders) DrawSnakeBorder(iRow,pos,counter);

   }else{
     if(func){
        min = sPos;
        max = ePos;
        if(!str.IsEmpty()){
           tStr = str+"\n"+func(min,max);
        }else{
           tStr=func(min,max);
        }
        DrawTextInBorders(iRow,min,max,tStr,false,kProp);
     }else{
        if(!str.IsEmpty())DrawTextInBorders(iRow,sPos,ePos,str,false,kProp);
     }
     if(gFillGaps[iRow]&&fWithBorders)DrawSnakeBorder(iRow,sPos,ePos);
   }

   RowslEnd[iRow] = ePos;
   delete[] pos;
}




void AutoCADTable::DrawRepeatTextIntervalSpec2(int iRow, AnsiString str,
                                float sPos, float ePos,bool fTop,
                                float step, bool fWithBorders, float kProp)
{

   if(iRow<0) return;

   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   AnsiString tStr;

   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos) return;

   int iMax = (int)(ePos/step)+1;
   int iMin = (int)(sPos/step)+1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   float *pos = new float[count];
   pos[0] = sPos;


   if(gFillGaps[iRow]&&RowslEnd[iRow]<=sPos){
     DrawRepeatEmptyInterval(iRow,RowslEnd[iRow],sPos,step,true);
   }

   emptyMin[iRow] = max(max(emptyMin[iRow], sPos),ePos);
   float min,max;
   if(iMin!=iMax){
     if(sPos<iMin*step){
         if(!str.IsEmpty())DrawTextInBordersSpec2(iRow,sPos,iMin*step,str,fTop,false,kProp);
         pos[counter++] = iMin*step;
     }
     for(int i=iMin;i<iMax-1;i++){
         if(!str.IsEmpty())DrawTextInBordersSpec2(iRow,i*step,(i+1)*step,str,fTop,false,kProp);
         pos[counter++] = (i+1)*step;
     }
     if(ePos>(iMax-1)*step){
        if(!str.IsEmpty())DrawTextInBordersSpec2(iRow,(iMax-1)*step,ePos,str,fTop,false,kProp);
        pos[counter++] = ePos;
     }
     if(fWithBorders) DrawSnakeBorder(iRow,pos,counter);

   }else{
     if(!str.IsEmpty())DrawTextInBordersSpec2(iRow,sPos,ePos,str,fTop,false,kProp);
     if(gFillGaps[iRow]&&fWithBorders)DrawSnakeBorder(iRow,sPos,ePos);
   }

   RowslEnd[iRow] = ePos;
   delete[] pos;
}


void AutoCADTable::DrawRepeatTextIntervalMoundHeight(int iRow,float sPos, float ePos,
                                float sHeight, float eHeight,
                                float step,float kProp)
{
   if(iRow<0) return;

   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   AnsiString str;

   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos) return;
   emptyMin[iRow] = max(max(emptyMin[iRow], sPos),ePos);
   int curHeight;
   float k,temp,temp2,xoffset;
   float width  = ePos-sPos;

   int iMax = (int)(ePos/step)+1;
   int iMin = (int)(sPos/step)+1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   xoffset = kProp*gRowHeight*0.1;
   float *pos = new float[count];
   pos[0] = sPos;
   float min,max;
   float subKProp = 0.75;


   if(iMin!=iMax){
     if(sPos<iMin*step&&int(sPos)%(int)step == 0){
         if((int)sHeight%100==0){
            str.sprintf("%i м",(int)sHeight/100);
         }else{
            if((int)sHeight%10==0){
              str.sprintf("%.1f м",(float)sHeight/100.0f);
            }else{
              str.sprintf("%.2f м",(float)sHeight/100.0f);
            }
         }
         temp2 = DrawTextInBordersMoundHeight(iRow,str,sPos+xoffset,0.875,acAlignmentMiddleLeft,step/2,kProp);
         DrawTextInBordersMoundHeight(iRow,(int)sPos%int(step)/100,sPos+xoffset,0.625,acAlignmentMiddleLeft,0,(!temp2?kProp*subKProp:temp2*subKProp));
         pos[counter++] = iMin*step;
     }

     temp = iMin*step;
     k = ((temp-sPos)/width);
     curHeight = sHeight +  (eHeight-sHeight)*k;

     if((int)curHeight%100==0){
        str.sprintf("%i м",curHeight/100);
     }else{
        if((int)curHeight%10==0){
          str.sprintf("%.1f м",(float)curHeight/100.0f);
        }else{
          str.sprintf("%.2f м",(float)curHeight/100.0f);
        }
     }


     temp2 = DrawTextInBordersMoundHeight(iRow,str,temp-xoffset,0.875,acAlignmentMiddleRight,temp - sPos,kProp);
     DrawTextInBordersMoundHeight(iRow,1000,temp-xoffset,0.625,acAlignmentMiddleRight,0,(!temp2?kProp*subKProp:temp2*subKProp));

     for(int i=iMin;i<iMax-1;i++){
         temp = i*step;
         k = ((temp-sPos)/width);
         curHeight = sHeight +  (eHeight-sHeight)*k;
         if((int)curHeight%100==0){
            str.sprintf("%i м",curHeight/100);
         }else{
            if((int)curHeight%10==0){
              str.sprintf("%.1f м",(float)curHeight/100.0f);
            }else{
              str.sprintf("%.2f м",(float)curHeight/100.0f);
            }
         }
         temp2 = DrawTextInBordersMoundHeight(iRow,str,temp+xoffset,0.875,acAlignmentMiddleLeft,step/2,kProp);
         DrawTextInBordersMoundHeight(iRow,0,temp+xoffset,0.625,acAlignmentMiddleLeft,0,(!temp2?kProp*subKProp:temp2*subKProp));

         temp += step;
         k = (temp-sPos)/width;
         curHeight = sHeight +  (eHeight-sHeight)*k;
         if((int)curHeight%100==0){
            str.sprintf("%i м",curHeight/100);
         }else{
            if((int)curHeight%10==0){
              str.sprintf("%.1f м",(float)curHeight/100.0f);
            }else{
              str.sprintf("%.2f м",(float)curHeight/100.0f);
            }
         }
         temp2 = DrawTextInBordersMoundHeight(iRow,str,temp-xoffset,0.875,acAlignmentMiddleRight,step/2,kProp);
         DrawTextInBordersMoundHeight(iRow,1000,temp-xoffset,0.625,acAlignmentMiddleRight,0,(!temp2?kProp*subKProp:temp2*subKProp));

         pos[counter++] = (i+1)*step;
     }
     if(ePos>(iMax-1)*step){
        temp = ePos - (iMax-1)*step;
        k = (float)((iMax-1)*step-sPos)/width;
        curHeight = sHeight +  (eHeight-sHeight)*k;
        if((int)curHeight%100==0){
           str.sprintf("%i м",curHeight/100);
        }else{
           if((int)curHeight%10==0){
             str.sprintf("%.1f м",(float)curHeight/100.0f);
           }else{
             str.sprintf("%.2f м",(float)curHeight/100.0f);
           }
        }
        temp2 = DrawTextInBordersMoundHeight(iRow,str,(iMax-1)*step+xoffset,0.875,acAlignmentMiddleLeft,temp/2,kProp);
        DrawTextInBordersMoundHeight(iRow,0,(iMax-1)*step+xoffset,0.625,acAlignmentMiddleLeft,0,(!temp2?kProp*subKProp:temp2*subKProp));

        if((int)eHeight%100==0){
           str.sprintf("%i м",(int)eHeight/100);
        }else{
           if((int)eHeight%10==0){
             str.sprintf("%.1f м",(float)eHeight/100.0f);
           }else{
             str.sprintf("%.2f м",(float)eHeight/100.0f);
           }
        }

        temp2 = DrawTextInBordersMoundHeight(iRow,str,ePos-xoffset,0.875,acAlignmentMiddleRight,temp/2,kProp);
        DrawTextInBordersMoundHeight(iRow,(int)ePos%int(step)/100,ePos-xoffset,0.625,acAlignmentMiddleRight,0,(!temp2?kProp*subKProp:temp2*subKProp));

        pos[counter++] = ePos;
     }
     DrawSnakeBorder(iRow,pos,counter);

   }else{
     if(sPos==iMin*step){

        if((int)sHeight%100==0){
           str.sprintf("%i м",(int)sHeight/100);
        }else{
           if((int)sHeight%10==0){
             str.sprintf("%.1f м",(float)sHeight/100.0f);
           }else{
             str.sprintf("%.2f м",(float)sHeight/100.0f);
           }
        }
        temp2 = DrawTextInBordersMoundHeight(iRow,str,sPos+xoffset,0.875,acAlignmentMiddleLeft,width,kProp);
        DrawTextInBordersMoundHeight(iRow,(int)sPos%int(step)/100,sPos+xoffset,0.625,acAlignmentMiddleLeft,0,(!temp2?kProp*subKProp:temp2*subKProp));
     }

     if((int)eHeight%100==0){
        str.sprintf("%i м",(int)eHeight/100);
     }else{
        if((int)eHeight%10==0){
          str.sprintf("%.1f м",(float)eHeight/100.0f);
        }else{
          str.sprintf("%.2f м",(float)eHeight/100.0f);
        }
     }

     temp2 = DrawTextInBordersMoundHeight(iRow,str,ePos-xoffset,0.875,acAlignmentMiddleRight,width,kProp);
     DrawTextInBordersMoundHeight(iRow,(int)ePos%int(step)/100,ePos-xoffset,0.625,acAlignmentMiddleRight,0,(!temp2?kProp*subKProp:temp2*subKProp));
     DrawSnakeBorder(iRow,sPos,ePos);
   }

   RowslEnd[iRow] = ePos;
   delete[] pos;
}

void AutoCADTable::DrawRepeatVerticalTextInterval(int iRow,
                                float sPos, float ePos,float kyPos,
                                float step, bool fWithBorders, float kProp)
{
   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   AnsiString tStr;
   emptyMin[iRow] = max(max(emptyMin[iRow], sPos),ePos);
   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos) return;

   int iMax = (int)(ePos/step)+1;

   int temp;
   int iMin = (int)(sPos/step)+1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   float *pos = new float[count];
   pos[0] = sPos;
   float min,max;

   if(iMin!=iMax){
     if(sPos<iMin*step){
         if(int(sPos)%int(step) == 0){
             DrawVerticalText(0,iRow,sPos,1-kyPos,true,kProp);
         }
         temp = iMin*step;
         DrawVerticalText(1000,iRow,temp,kyPos,false,kProp);
         pos[counter++] = iMin*step;
     }
     for(int i=iMin;i<iMax-1;i++){
         temp = i*step;
         DrawVerticalText(0,iRow,temp,1-kyPos,true,kProp);
         temp = (i+1)*step;
         DrawVerticalText(1000,iRow,temp,kyPos,false,kProp);
     }
     if(ePos>(iMax-1)*step){
        temp = (iMax-1)*step;
        DrawVerticalText(0,iRow,temp,1-kyPos,true,kProp);
        pos[counter++] = ePos;
        DrawVerticalText(int(ePos)%int(step)/100,iRow,ePos,kyPos,false,kProp);
     }
     if(fWithBorders) DrawSnakeBorder(iRow,pos,counter);

   }else{
     if(int(sPos)%int(step) == 0){
         DrawVerticalText(0,iRow,sPos,1-kyPos,true,kProp);
     }
     if(int(ePos)%int(step)==0){
       DrawVerticalText(1000,iRow,ePos,1-kyPos,true,kProp);
     }else{
       DrawVerticalText(int(ePos)%int(step)/100,iRow,ePos,kyPos,false,kProp);
     }

     if(fWithBorders)DrawSnakeBorder(iRow,sPos,ePos);
   }

   RowslEnd[iRow] = ePos;
   delete[] pos;
}


AcadBlockReferencePtr AutoCADTable::DrawBlock(WideString BlockName, int iRow, float Pos, float yOffset)
{
   return gOwner->DrawBlock(BlockName,gLeftTop.x+Pos,gLeftTop.y-RowOffsetY(iRow) - gRowHeight*yOffset);
}

AcadLinePtr AutoCADTable::DrawLine(int iRow, float sPos, float ePos)
{
   if(iRow==-1 || !gOwner) return AcadLinePtr();
   float y = gLeftTop.y - RowOffsetY(iRow) - gRowHeight/2;
   return gOwner->DrawLine(gLeftTop.x+sPos,y,gLeftTop.x+ePos,y);
}

AcadLinePtr AutoCADTable::DrawLine(int iRow, float sPos,
                                 float yk1, float ePos, float yk2)
{
   if(iRow==-1 || !gOwner) return AcadLinePtr();
   yk1 = gLeftTop.y - RowOffsetY(iRow) - gRowHeight*(1-yk1);
   yk2 = gLeftTop.y - RowOffsetY(iRow) - gRowHeight*(1-yk2);
   return gOwner->DrawLine(gLeftTop.x+sPos,yk1,gLeftTop.x+ePos,yk2);
}

AcadEllipsePtr AutoCADTable::DrawRightArcEllipse(int iRow, float sPos, float ePos)
{
    return gOwner->DrawEllipse(sPos,gLeftTop.y - RowOffsetY(iRow+1),abs((int)(ePos-sPos)),gRowHeight/2);
}

AcadEllipsePtr AutoCADTable::DrawLeftArcEllipse(int iRow, float sPos, float ePos)
{
    return gOwner->DrawEllipse(sPos,gLeftTop.y - RowOffsetY(iRow),abs((int)(ePos-sPos)),gRowHeight/2);
}

AcadTextPtr AutoCADTable::DrawVerticalText(AnsiString txt, int iRow, float Pos,
                                         float kyPos,bool fRight, float kProp)
{
   float xOffset = gLeftTop.x + Pos;
   float _Height;
   float yOffset = gLeftTop.y- RowOffsetY(iRow)-gRowHeight*(1-kyPos);

   // if kProp less then 10 then we use height according to row height
   if(kProp>10)
     _Height = kProp;
   else
     _Height = gRowHeight*kProp;

   AcadTextPtr text;
   if(fRight){
     text = gOwner->DrawText(txt,_Height,acAlignmentTopCenter, xOffset + 0.35*_Height,yOffset,M_PI_2);
   } else {
     text = gOwner->DrawText(txt,_Height,acAlignmentBottomCenter, xOffset,yOffset,M_PI_2);
   }
   return text;
}

// returns the rest of words started from index
AnsiString GetRestOfStringAfter(int index, vector<AnsiString> words, AnsiString delimiter = " ")
{
   AnsiString str;
   for(int i=index;i<words.size(); ++i ) {
      if (i!=index) str += delimiter;
      str += words[i];
   }
   return str;
}

// returns the rest of words started from index
AnsiString GetRestOfStringBefore(int index, vector<AnsiString> words, AnsiString delimiter = " ")
{
   AnsiString str;
   for(int i=index;i>=0; --i ) {
      str += words[i];
      if (i!=index) str += delimiter;
   }
   return str;
}

void AutoCADTable::SplitTextForRoadMark(AnsiString str, int RectHeight, int RectWidth, vector<LineInfo> &lines)
{
#define GETK(str) (float)RectWidth / (str.Length()* LetterWidth)

    int width, minLinesCount;
    int LetterWidth = gLetterWidth / 4;
    int LetterHeight;
    int linesCount;
    float kOffset, k, kTitle, k0 = 0, k1 = 0, k2 = 0;
    vector<AnsiString> strs;

    // for each subline check is it possible to increase size of letters
    linesCount = 1; // at least we have one line

    kTitle = k = GETK(str); //(float)RectWidth / (); // get relation between RectWidth and text width
    LetterHeight = kTitle * RectHeight;  // recalculate LetterHeight

    // check is text box wide enough
    if (k <= 0.5) {
       AnsiString rest;
       // let's split string on words
       vector<AnsiString> words;
       gOwner->SplitString(str, ' ', words); // split line with spaces

       // try to split string on two lines
       linesCount = 2;
       rest = GetRestOfStringAfter(1, words);
       kTitle = GETK( words[0] );
       k0 = std::min<float>( kTitle, GETK( rest ) ) / linesCount;
       k0 = std::min<float> ( k0, 1.0 / linesCount);
       // is it use?
       if ( kTitle > k && words.size() > 2 ) {
         // try to split string on three lines
         linesCount = 3;
         rest = GetRestOfStringAfter(2, words);
         k1 = std::min<float>( std::min<float>( GETK(words[0]), GETK(words[1]) ), GETK(rest) ) / linesCount;
         k1 = std::min<float> ( k1, 1.0 / linesCount);
         // is it use?
         if ( k1 > 1.3*k0) { // that cause overall text size is more important then size of just one header
           strs.push_back(words[0]);
           strs.push_back(words[1]);
           strs.push_back(GetRestOfStringAfter(2, words));
           k = k1;
           kTitle = std::min<float> ( (GETK( words[0] )) / 3, 1.0 / 3);
         } else {
           strs.push_back(words[0]);
           strs.push_back(GetRestOfStringAfter(1, words));
           k = k0;
           kTitle = std::min<float> ( (GETK( words[0] )) / 2, 1.0 / 2);
         }
       } else { // if spliting only spoils result revert to one line
         strs.push_back(str);
         kTitle = k;
       }
    } else { // perfect solution, no dividig is needed
       strs.push_back(str); // otherwise just push string to lines array
       kTitle = k;
    }

    // loop over string lines
    kOffset =  1.0 / ( strs.size() + 1);
    for (int i=0;i<strs.size() ;++i) {
       LineInfo li;

       if (i == 0) { // fot title or first substring we have special case
          if ( strs.size() > 1 ) { // move title a bit higher
            li.kOffset = kOffset - kTitle*0.1;
          }  else {
            li.kOffset = kOffset;
          }
          li.Height = min( RectHeight, kTitle * RectHeight);
       } else { // if not title
          li.Height = min( RectHeight, k * RectHeight);
          li.kOffset = (i+1)*kOffset + kTitle*0.1;
       }

       li.Text = strs[i];
       // push lineInfo to array
       lines.push_back(li);
    }
#undef GETK
}


void AutoCADTable::DrawTextInBordersRoadMark(int row, float offBeg,
                            float offEnd,AnsiString str,
                            bool fWithBorders ,float kProp)
{
  if (RowslEnd[row] > offBeg) offBeg = RowslEnd[row];
  if(offEnd <= offBeg) return;

  float xOffset, yOffset;
  float width = fabs(offEnd-offBeg);

  vector<LineInfo> strings;
  SplitTextForRoadMark(str, gRowHeight, offEnd - offBeg, strings);

  xOffset = gLeftTop.x + offBeg + width/2;
  yOffset = gLeftTop.y - RowOffsetY(row);

  for(int i=0;i<strings.size();i++){
     gOwner->DrawText(strings[i].Text,
        kProp*strings[i].Height,
        acAlignmentMiddle,
        xOffset,
        yOffset - strings[i].kOffset * gRowHeight);
  }

  if(fWithBorders){
      DrawSnakeBorder(row,offBeg,offEnd);
  }
}

void AutoCADTable::DrawRepeatTextIntervalRoadMark(int iRow, AnsiString str,
                                float sPos, float ePos,
                                AnsiString (*func)(float, float),
                                float step, bool fWithBorders, float kProp)
{
#define DRAWTEXT(min, max)  \
        if(func){ \
           AnsiString tStr; \
           if(!str.IsEmpty()){ \
              tStr = str+func(min,max); \
           }else{ \
              tStr=func(min,max); \
           } \
           DrawTextInBordersRoadMark(iRow,min,max,tStr,false,kProp); \
        }else{ \
           if(!str.IsEmpty())DrawTextInBordersRoadMark(iRow,min,max,str,false,kProp); \
        }     

   if(iRow<0) return;
   if(step==0){
     if(gRepeatInterval!=0)
       step=gRepeatInterval;
     else
       return;
   }

   if(sPos<0) sPos = 0;
   if(ePos<0||ePos == sPos) return;
   
   if(sPos>ePos){
      int temp =  sPos;
      sPos = ePos;
      ePos = temp;
   }

   int iMax = (int)(ePos/step)+1;
   int iMin = (int)(sPos/step)+1;

   int count = abs(iMax - iMin)+2;
   int counter = 1;
   float *pos = new float[count];
   pos[0] = sPos;

   if(gFillGaps[iRow]&&RowslEnd[iRow]<=sPos){
     DrawRepeatEmptyInterval(iRow,RowslEnd[iRow],sPos,step,true);
   }
   emptyMin[iRow] = max(max(emptyMin[iRow], sPos),ePos);

   float min,max;
   if(iMin!=iMax){
     if(sPos<iMin*step){
        min = sPos;
        max = iMin*step;
        DRAWTEXT(min, max);
        pos[counter++] = max; 
     }
     for(int i=iMin;i<iMax-1;i++){
        min = i*step;
        max = (i+1)*step;
        DRAWTEXT(min, max);
        pos[counter++] = max; 
     }
     if(ePos>(iMax-1)*step){
        min = (iMax-1)*step;
        max = ePos;
        DRAWTEXT(min, max);
        pos[counter++] = max; 
     }
     if(fWithBorders) DrawSnakeBorder(iRow,pos,counter);
   }else{
     DRAWTEXT(sPos, ePos);
     if(gFillGaps[iRow]&&fWithBorders)DrawSnakeBorder(iRow,sPos,ePos);
   }
   delete[] pos;
   RowslEnd[iRow] = ePos;
   
#undef DRAWTEXT
}


void AutoCADTable::DrawTextInBorders(int row, float offBeg,
                            float offEnd,AnsiString str,
                            bool fWithBorders ,float kProp)
{
  if(row<0 || offEnd == offBeg) return;

  int count = 1;
  int strLenght = str.Length();

  vector<AnsiString> strings;
  gOwner->SplitString(str, '\n', strings);
  count = strings.size();

  float Height = gRowHeight/(float)count;

  float xOffset = gLeftTop.x + offBeg + (offEnd - offBeg)/2;
  float yOffset = gLeftTop.y- RowOffsetY(row)+Height/2;

  if(kProp<=1) { /*если в пропорциях от высоты строки*/
    for(int i=0;i<count;i++){     
       yOffset-=Height;
       gOwner->DrawText(strings[i],kProp*Height,acAlignmentMiddle, xOffset,yOffset);
    }
  } else {  /*иначе абсолютное значение*/
    for(int i=0;i<count;i++){
       yOffset-=Height;
       gOwner->DrawText(strings[i],kProp, acAlignmentMiddle, xOffset,yOffset);
    }
  }

  if(fWithBorders){
      DrawSnakeBorder(row,offBeg,offEnd);
  }
}

void AutoCADTable::DrawTextInBordersSpec2(int row, float offBeg,
                            float offEnd,AnsiString str, bool fTop,
                            bool fWithBorders,float kProp)
{
   AcadTextPtr text;
   AcAlignment align;
   float width  = (float)abs(int(offEnd - offBeg))/2;
   float xOffset = gLeftTop.x + offBeg + width*1.5;
   float yOffset;
   float scale;

   scale = (float)width/(float)(str.Length()*(gLetterWidth*kProp));

   if(scale>=1)
     scale = kProp;
   else{
      scale = (float)abs(int(offEnd-offBeg))/(float)(str.Length()*gLetterWidth);
      scale *= kPadding;
      if(scale>kProp)scale = kProp;
   }

   yOffset = gLeftTop.y- RowOffsetY(row+1)+ 0.5*gRowHeight + gRowHeight*kBottomEmptyPadding*0.5;
   if(fTop){
     align = acAlignmentBottomCenter;
     scale*=(0.5-kBottomEmptyPadding/2);
   }else{
     align = acAlignmentTopCenter;
     scale*=(kBottomEmptyPadding/2+0.5);
   }

   text = gOwner->DrawText(str,scale*gRowHeight,align, xOffset,yOffset);
}




float AutoCADTable::DrawTextInBordersMoundHeight(int iRow, AnsiString text,
                         float Pos, float yPos, AcAlignment align, float width, float kProp)
{
   AcadTextPtr aText;
   bool fwas = false;
   float scale;
   if(yPos>1) yPos = 1;
   float xOffset = gLeftTop.x+Pos;
   float yOffset = gLeftTop.y-RowOffsetY(iRow)-gRowHeight*(1-yPos);

   if(width>0){
     scale = (float)width/(float)(text.Length()*(gLetterWidth*kProp));

     if(scale>=1)
       scale = kProp;
     else{
        fwas = true;
        scale = width/(float)(text.Length()*gLetterWidth);
        if(scale>kProp)scale = kProp;
     }
   }else{
      scale = kProp;
   }

   aText = gOwner->DrawText(text,scale*gRowHeight,align,xOffset,yOffset);

   return fwas?scale:0;
}

