#ifndef AutoCADHelperH
#define AutoCADHelperH 


#include "AutoCAD_OCX.h"
#include <string.h>
#include <Graphics.hpp>
#include <stdio.h>
#include <Dir.h>
#include <math.h>
#include <OleServer.hpp>
#include <Dialogs.hpp>
#include <vector>
#include <algorithm>


using namespace std;

class AutoCADHelper;
class AutoCADTable;

enum AutoCADTabelTextPosition {actpLeft = 0,actpMiddle = 1,
      actpRight = 2,actpTop = 4,actpCenter = 8,actpBottom=16};





struct AutoCADSignBlockInfo
{
  AnsiString name;
  int index;
  AutoCADSignBlockInfo(AnsiString _name,int index);
};

struct AutoCADPoint
{
   float x,y;
   AutoCADPoint(){x=0;y=0;}
   AutoCADPoint(float _x, float _y){x=_x;y=_y;}
};
const AutoCADPoint acpZero(0,0);

struct AutoCADPointGapGreater:binary_function<AutoCADPoint,AutoCADPoint,bool>{
   bool operator()(const AutoCADPoint& p1, const AutoCADPoint& p2){
      if(p1.x>p2.x){
         if(p1.y>p2.y){
            return true;
         }else{
           return false;
         }
      }else{
         return false;
      }
   }
};

class SignsCollection
{
private:   
   vector<AutoCADSignBlockInfo> signs;
public:
   AutoCADHelper *Owner;

   int GetIndexByName(AnsiString name);
   AnsiString GetNameByIndex(int index);
   void AddBlock(AnsiString name, int i);
   void Clear();
   void CheckExistingBlocks();
};

class AutoCADTable
{
private:
        AutoCADHelper *gOwner;
        int gRowsCount;
        float gRowHeight;
        float gHeaderWidth;
        float gTableWidth;
        float gRepeatInterval;
        float lEnd,gLetterWidth;
        float gFillGapsBegin;

        int *emptyMin;

        vector<AutoCADPoint> *gaps;


        bool gIsHI,*gFillGaps,gAutoShrink, fFirst;
        AutoCADPoint gLeftTop;
        float *RowslEnd, minS, minE;

        float iRowsFullHeight;


        void SetRowsCount(int value){
                gRowsCount = value;

                if(emptyMin) delete[] emptyMin;
                emptyMin = new int[value];

                iRowsFullHeight = gRowsCount*gRowHeight;
                if(RowslEnd) delete[] RowslEnd;
                RowslEnd = new float[value];
                SetFillGapsBegin(gFillGapsBegin);
                /*if(gFillGaps)
                  delete[] gFillGaps; */
                gFillGaps = new bool[value];
                if(gaps)
                  delete[] gaps;
                gaps = new vector<AutoCADPoint>[value];
        }

        void SetRowHeight(float value){
                gRowHeight = value;
                iRowsFullHeight = gRowsCount*gRowHeight;
        }

        void SetTableHeight(float value){
            iRowsFullHeight = value;
            if(gRowsCount!=0)
               gRowHeight = value/gRowsCount;
        }

        bool GetFillGaps(int index){return gFillGaps[index];}


        
        void SetHeaderWidth(float value){gHeaderWidth = value;};
        void SetTableWidth(float value){gTableWidth = value;};
        void SetLeftTop(AutoCADPoint value){gLeftTop = value;};
        
        void SetFillGaps(int index,bool value){
                if(gFillGaps){
                    if(index < 0){
                      for(int i=0;i<gRowsCount;i++){
                         gFillGaps[i] = value;
                      }
                    }else{
                       gFillGaps[index] = value;
                    }
                }
        };

        void SetFillGapsBegin(float value)
        {
            if(gFillGapsBegin!=value) gFillGapsBegin = value;
            for(int i=0;i<gRowsCount;i++){
               RowslEnd[i] = value;
               emptyMin[i] = value;
            }
        }

        void ResetLPos()
        {
          fFirst = true;
          for(int i=0;i<gRowsCount;i++){
               RowslEnd[i] = gFillGapsBegin;
          }
          minS = -1;
          minE = -1;          
        }        
public:
        inline float RowOffsetY(int i){return i*gRowHeight;}
        bool drawHeaders;
        int lessForVerticalLabels;

        __property int RowsCount = {read = gRowsCount, write = SetRowsCount};
        __property float RowHeight = {read = gRowHeight, write = SetRowHeight};
        __property float HeaderWidth = {read = gHeaderWidth, write = SetHeaderWidth};
        __property float TableHeight = {read = iRowsFullHeight, write = SetTableHeight};
        __property float TableWidth = {read = gTableWidth, write = SetTableWidth};
        __property AutoCADPoint LeftTop = {read = gLeftTop, write = SetLeftTop};
        __property bool IsHeaderInclude = {read = gIsHI, write = gIsHI};
        __property float RepeatInterval = {read = gRepeatInterval, write = gRepeatInterval};
        __property AutoCADHelper *Owner = {read = gOwner, write = gOwner};
        __property bool FillGaps[int i] = {read = GetFillGaps, write = SetFillGaps};
        __property bool AutoShrink = {read = gAutoShrink, write = gAutoShrink};
        __property float AutoShrinkOneLetterWidth = {read = gLetterWidth, write = gLetterWidth};
        __property float FillGapsBegin = {read = gFillGapsBegin, write = SetFillGapsBegin};

        /* ТЕКСТ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadText *DrawText(int row, float offset, AnsiString str,
                                float kProp = 0.34);
        void DrawTextInBorders(int row, float offBeg,
                                    float offEnd,AnsiString str,
                                    bool fWithBorders = true,float kProp = 0.43);
        AcadText *DrawHeaderText(int row,AnsiString str, float kProp = 0.34);
        AcadText *DrawVerticalText(AnsiString txt, int iRow, float Pos, float kyPos = 0.5,
                                        bool fRight = true, float kProp = 0.2);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /* REPEAT -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        void DrawRepeatTextInterval(int iRow, AnsiString str,
                                float sPos, float ePos,
                                AnsiString (*func)(float _min, float _max) = 0,
                                float step = 0,
                                bool fWithBorders = true, float kProp = 0.43);

        void DrawRepeatEmptyInterval(int iRow,
                                float sPos, float ePos, float step = 0,
                                bool fWithBorders = true, bool fInc = false);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /* GEOMETRY -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadLine *DrawBorder(int offset,int iRow=-1);
        void DrawSnakeBorder(int iRow, float *xOffsets, int count);
        void DrawSnakeBorder2(int iRow, float sPos, float ePos);
        void DrawEmpty(int Row, float offsetBegin, float offsetEnd,
                        bool fWithBorders = false, bool fInc = false);
        AcadBlockReferencePtr DrawBlock(WideString BlockName, int iRow, float Pos, float yOffset=0.5);
        AcadLine *DrawLine(int iRow, float sPos, float ePos);
        AcadLine *DrawLine(int iRow, float sPos, float yk1/* 0<=yk1<=1 */, float ePos, float yk2);
        AcadLine *DrawFull(int offsetBegin, int OffsetEnd);
        void FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch, float scale = 75, int color = 0);
        void FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch, float scale, long colorR, long colorG, long colorB);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /* TABLE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        void DrawTable();
        void FillLastGaps(float step, int iRow=-1);
        AutoCADTable(AutoCADHelper *Owner = 0, float TableWidth = 0, int RowsCount = 0,
                     float RowHeight = 2000, AutoCADPoint LeftTop = acpZero,
                     float HeaderWidth = 0);
        ~AutoCADTable();
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /* SPECIFIC -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadEllipse *DrawLeftArcEllipse(int iRow, float sPos, float ePos);
        AcadEllipse *DrawRightArcEllipse(int iRow, float sPos, float ePos);
        void DrawRepeatTextIntervalSpec(int iRow, AnsiString str,
                                float sPos, float ePos,
                                AnsiString (*func)(float _min, float _max) = 0,
                                float step = 0,
                                bool fWithBorders = true, float kProp = 0.43);
        void DrawRepeatTextIntervalSpec2(int iRow, AnsiString str,
                                float sPos, float ePos, bool fTop, float step = 0,
                                bool fWithBorders = true, float kProp = 0.43);

        void DrawRepeatTextIntervalSpec3(int iRow,float sPos, float ePos,
                                float sHeight, float eHeight,
                                float step,float kProp=0.18);

        void DrawTextInBordersSpec(int row, float offBeg,
                                    float offEnd,AnsiString str,
                                    bool fWithBorders = true,float kProp = 0.52);
        void DrawRepeatVerticalTextInterval(int iRow,float sPos, float ePos,
                                float step = 0,float kyPos = 0.75,
                                bool fWithBorders = true, float kProp = 0.43);
        void DrawTextInBordersSpec2(int row, float offBeg,
                                    float offEnd,AnsiString str, bool fTop,
                                    bool fWithBorders = true,float kProp = 0.43);
        float DrawTextInBordersSpec3(int iRow, AnsiString text, float Pos, float yPos,
                                  AcAlignment align,float width =0, float kProp = 0.43);
        void DrawEmpty2(int Row, float offsetBegin, float offsetEnd,
                        bool fWithBorders = false, bool fInc = false);
        void DrawRepeatEmptyInterval2(int iRow,
                                float sPos, float ePos, float step = 0,
                                bool fWithBorders = true, bool fInc = false);
        float kBottomEmptyPadding;
        float kPadding;
        float MinViewFontSize;
        AnsiString EmptyFill;
        int EmptyFillScale;                                                  
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
};

class AutoCADHelper
{

private:
        IAcadApplicationDisp cadApplication;
        TAcadDocument *cadActiveDocument;
        bool fApplicationRun, fInvertYAxe, fInvertXAxe;
        TNotifyEvent gOnActiveDocumentBeginClose;

        Graphics::TBitmap *BMP;
        
        bool gMakeBlockTextEnable;
        float gMakeBlockGap;
        double gMakeBlockTextHeight;
        double gMakeBlockTextOffsetX;

        AcadText *gCopyTextObject;
        bool gCopyText;

        int comboSignCount;

        SignsCollection SignsCollection;
        
        AcadApplication *getApplication();
        AcadBlockPtr getBlocks(int i);
        AcadBlockPtr getBlocksByName(AnsiString BlockName);
        AcadLineType *getLineType(WideString name);
        AcadDocument *getActiveDocument();
        void SetSignAttribute(AcadBlockReferencePtr block, WideString value);
        WideString GetSignName(AnsiString signName);
        int getBlocksCount();
        void __fastcall ActiveDocumentBeginClose(TObject *sender);

        void set_OnActiveDocumentBeginClose(TNotifyEvent value){
           gOnActiveDocumentBeginClose = value;
           if(cadActiveDocument){
              cadActiveDocument->OnBeginClose = ActiveDocumentBeginClose;
           }
        }

public:
        AutoCADHelper();
        ~AutoCADHelper();

        AnsiString strLostBlocks;
        AnsiString (*SignLabelParser)(AnsiString , AnsiString );



        Variant cadPoint(double x = 0, double y = 0, double z = 0);
        Variant cadPointArray(double *points, int Count/*кол-во точек, а не координат в массиве*/,
                                    int coordCount = 2/*кол-во координат у точки*/);
        Variant cadArray(IDispatch **objects, int count);
        Variant cadArray( WideString *strings, int count);        

        /*ПРИЛОЖЕНИЕ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadApplication *RunAutoCAD(bool fVisible=true);
        AcadApplication *BindAutoCAD();
        void ResetBlocksCollection();
        bool IsLarger(AnsiString name);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*ДОКУМЕНТЫ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        TAcadDocument *CreateDocumentFromInterface(IAcadDocument* doc = 0, bool setAsActive = true); // create document
        void DeleteDocument(TAcadDocument** doc); // delete document

        IAcadDocument *AddDocument(AnsiString _template="acadiso.dwt");
        TAcadDocument *BindToActiveDocument();
        IAcadDocument *OpenDocument(AnsiString FileName,
                                    bool fSetActive = false,
                                    bool fReopen = false);
        void SendCommand(WideString command);
        void SelectPaperSpace();/*переключиться на PAPERSPACE*/
        void CheckExistingBlocks();
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*РИСОВАНИЕ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        /* %func_name%PS - рисование в пространстве листа;
           для выбора активного листа использовать SetAsActiveLayout*/

        AcadPolyline *DrawPolyLine(double *array, int count, int coordCount = 2);
        AcadPolyline *DrawPolyLinePS(double *array, int count, int coordCount = 2);

        AcadPolyline *DrawRect(double centerX, double centerY, double width, double height);
        AcadPolyline *DrawRectPS(double centerX, double centerY, double width, double height);

        AcadCircle *DrawCircle(double centerX, double centerY, double radius);
        AcadCircle *DrawCirclePS(double centerX, double centerY, double radius);

        AcadLine *DrawLine(double x1, double y1, double x2, double y2);
        AcadLine *DrawLinePS(double x1, double y1, double x2, double y2);

        AcadText *DrawText(AnsiString str, double height,
                        double x = 0, double y = 0, double rotation = 0);
        AcadText *DrawTextPS(AnsiString str, double height,
                        double x = 0, double y = 0, double rotation = 0);
        AcadArc *DrawArc(double centerX, double centerY, double radius, double sAngle, double eAngle);
        AcadEllipse *DrawEllipse(double centerX, double centerY, double MajorAxis,double MinorAxis);

        AcadHatch *FillArea(IDispatch **LoopObjects, int LoopObjectsCount,
                         int HatchColor = 0, WideString sHatchType = "SOLID", int hatchScale = 75);
        AcadHatch *FillAreaPS(IDispatch **LoopObjects, int LoopObjectsCount,
                         int HatchColor = 0, WideString sHatchType = "SOLID", int hatchScale = 75);
        void DrawRepeatTextInterval(WideString str, float sPosX, float ePosX,
                                         float sPosY, float ePosY, float TextHeight,
                                         float step = 100000);
        int GetTextWidth(AnsiString text, int Height);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*БЛОКИ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        //void LoadBlocksFromFile(AnsiString FileName, AnsiString BlockName="");
        void SetAttribute(AcadBlockReferencePtr block, AnsiString PropertyName,
                                 WideString value, int rot = -1);
                                 
        bool SetPropertyPoint(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 AutoCADPoint value);
        bool SetPropertyDouble(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 double value);
        bool SetPropertyList(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 short value);
        bool SetPropertyListVariant(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName,
                                 Variant value);

        bool GetPropertyPoint(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName, AutoCADPoint &out);
        bool GetSubPropertyPoint(AcadBlockPtr ptrBlock, AnsiString PropertyName, AutoCADPoint &out);
        bool GetPropertyDouble(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName, double &out);
        bool GetSubPropertyDouble(AcadBlockPtr ptrBlock, AnsiString PropertyName, double &out);
        bool GetPropertyVariant(AcadBlockReferencePtr ptrBlock, AnsiString PropertyName, Variant &out);

        AcadBlockReferencePtr DrawBlock(WideString BlockName,
                              double x = 0, double y = 0,
                              double rotation = 0, double scale = 1);
        AcadBlockPtr MakeCombineBlock(WideString block1, WideString label1,
                                      WideString block2, WideString label2="",
                                      WideString block3="", WideString label3="",
                                      WideString block4="", WideString label4="");
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*PAPERSPACE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        void AddPaperSpace(AnsiString name, double x, double y,
                                        double width, double height);
        AcadLayout *AddPaperSpace(WideString name);
        bool SetupViewport(AcadLayout *layout, double x, double y,
                                        double width, double height);

        bool SetupActiveViewportZoomWindow(double x, double y,
                   double width, double height);/*настроить вид видового экрана*/
        bool SetupActiveViewportZoomScale(double ZoomFactor);
        bool SetupActiveViewportZoomCenter(double x, double y,double scale);

        bool PrintActiveLayoutToFile(WideString FileName);
        bool PrintLayoutsToFile(WideString FileName, int* arrayofindexes, int count);
        AcadLayout *SetAsActiveLayout(Variant index); /*выбрать активный Layout*/
        void SetBACKGROUNDPLOT_ZERO();/*надо вызвать перед 2 и более вызовами
                                        PrintActiveLayoutToFile */
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*ТИПЫ ЛИНИЙ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadLineTypePtr LoadLineType(WideString LineTypeName,
                                   WideString FileName = "acadiso.lin",
                                   WideString ShapeFileName = "");
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*MODELSPACE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        void Regen();        
        void ClearModelSpace();
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        __property AcadApplication *Application = {read = getApplication};
        __property AcadDocument *ActiveDocument = {read = getActiveDocument};
        __property AcadBlockPtr Blocks[int] = {read = getBlocks};
        __property AcadBlockPtr BlocksByName[AnsiString] = {read = getBlocksByName};
        __property bool InvertYAxe = {read = fInvertYAxe, write = fInvertYAxe};
        __property bool InvertXAxe = {read = fInvertXAxe, write = fInvertXAxe};
        __property int BlocksCount = {read = getBlocksCount};
        __property AcadLineType *LineType[WideString str] = {read = getLineType};
        __property float MakeBlockGap = {read = gMakeBlockGap, write = gMakeBlockGap};
        __property bool MakeBlockTextEnable  = {read = gMakeBlockTextEnable,
                                                        write = gMakeBlockTextEnable};
        __property double MakeBlockTextHeight = {read = gMakeBlockTextHeight,
                                                write = gMakeBlockTextHeight};
        __property double MakeBlockTextOffsetX = {read = gMakeBlockTextOffsetX,
                                                 write = gMakeBlockTextOffsetX};
        __property bool CopyText = {read = gCopyText, write = gCopyText};
        __property AcadText* CopyTextObject = {read = gCopyTextObject,
                                               write= gCopyTextObject};

        __property TNotifyEvent OnActiveDocumentBeginClose = {read = gOnActiveDocumentBeginClose,
                                                write = set_OnActiveDocumentBeginClose};
};


#endif
