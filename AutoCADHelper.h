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
        float lEnd;
        float gLetterWidth; // avg width of letter if height of text equals to the row height
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
        AcadTextPtr DrawText(int row, float offset, AnsiString str,
                                float kProp = 0.34);
        void DrawTextInBorders(int row, float offBeg,
                                    float offEnd,AnsiString str,
                                    bool fWithBorders = true,float kProp = 0.43);
        void DrawHeaderText(int row,AnsiString str, float kProp = 0.34);
        AcadTextPtr DrawVerticalText(AnsiString txt, int iRow, float Pos, float kyPos = 0.5,
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
                                bool fWithBorders=true, bool fWithoutFill = false, bool fInc = false);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /* GEOMETRY -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        AcadLinePtr DrawBorder(int offset,int iRow=-1);
        void DrawSnakeBorder(int iRow, float *xOffsets, int count);
        void DrawSnakeBorder(int iRow, float sPos, float ePos);

        void DrawEmpty(int Row, float offsetBegin, float offsetEnd,
                        bool fWithBorders, bool fWithoutFill, bool fInc);

        AcadBlockReferencePtr DrawBlock(WideString BlockName, int iRow, float Pos, float yOffset=0.5);
        AcadLinePtr DrawLine(int iRow, float sPos, float ePos);
        AcadLinePtr DrawLine(int iRow, float sPos, float yk1/* 0<=yk1<=1 */, float ePos, float yk2);
        AcadLinePtr DrawFull(int offsetBegin, int OffsetEnd);
        AcadHatchPtr FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch, float scale = 75, int color = 0);
        AcadHatchPtr FillArea(int iRow, float offsetBegin, float offsetEnd, AnsiString strHatch, float scale, long colorR, long colorG, long colorB);
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
        AcadEllipsePtr DrawLeftArcEllipse(int iRow, float sPos, float ePos);
        AcadEllipsePtr DrawRightArcEllipse(int iRow, float sPos, float ePos);

         // for drawing road mark and barriers text
        struct LineInfo { AnsiString Text; int Height; float kOffset; };
        void SplitTextForRoadMark(AnsiString str, int RectHeight, int RectWidth, vector<LineInfo> &lines);        
        void DrawRepeatTextIntervalRoadMark(int iRow, AnsiString str,
                                float sPos, float ePos,
                                AnsiString (*func)(float _min, float _max) = 0,
                                float step = 0,
                                bool fWithBorders = true, float kProp = 0.43);
        void DrawTextInBordersRoadMark(int row, float offBeg,
                                    float offEnd,AnsiString str,
                                    bool fWithBorders = true,float kProp = 0.52);
        // -=-=-=-=-=-=-=-=-=-=-

        // for drawing mound heights text
        void DrawRepeatTextIntervalMoundHeight(int iRow,float sPos, float ePos,
                                float sHeight, float eHeight,
                                float step,float kProp=0.18);
        float DrawTextInBordersMoundHeight(int iRow, AnsiString text, float Pos, float yPos,
                                  AcAlignment align,float width =0, float kProp = 0.43);

        void DrawRepeatTextIntervalSpec2(int iRow, AnsiString str,
                                float sPos, float ePos, bool fTop, float step = 0,
                                bool fWithBorders = true, float kProp = 0.43);
        // -=-=-=-=-=-=-=-=-=-=-


        void DrawRepeatVerticalTextInterval(int iRow,float sPos, float ePos,
                                float step = 0,float kyPos = 0.75,
                                bool fWithBorders = true, float kProp = 0.43);
        void DrawTextInBordersSpec2(int row, float offBeg,
                                    float offEnd,AnsiString str, bool fTop,
                                    bool fWithBorders = true,float kProp = 0.43);



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
        
        AcadApplicationPtr getApplication();

        AcadBlockPtr getBlocks(int i);
        AcadBlockPtr getBlocksByName(AnsiString BlockName);
        AcadLineTypePtr getLineType(WideString name);
        AcadDocumentPtr getActiveDocument();


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
        TAcadDocument *SetActive(AcadDocumentPtr docToConnect); // create document
        void DeleteDocument(TAcadDocument *doc); // delete document

        AcadDocumentPtr AddDocument(AnsiString _template="acadiso.dwt");
        bool BindToActiveDocument();
        AcadDocumentPtr OpenDocument(AnsiString FileName,
                                    bool fSetActive = false,
                                    bool fReopen = false);
        void SendCommand(WideString command);
        void SelectPaperSpace();/*переключиться на PAPERSPACE*/
        void CheckExistingBlocks();
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*РИСОВАНИЕ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        /* %func_name%PS - рисование в пространстве листа;
           для выбора активного листа использовать SetAsActiveLayout*/

        AcadPolylinePtr DrawPolyLine(double *array, int count, int coordCount = 2);
        AcadPolylinePtr DrawPolyLinePS(double *array, int count, int coordCount = 2);

        AcadPolylinePtr DrawRect(double centerX, double centerY, double width, double height);
        AcadPolylinePtr DrawRectPS(double centerX, double centerY, double width, double height);

        AcadCirclePtr DrawCircle(double centerX, double centerY, double radius);
        AcadCirclePtr DrawCirclePS(double centerX, double centerY, double radius);

        AcadLinePtr DrawLine(double x1, double y1, double x2, double y2);
        AcadLinePtr DrawLinePS(double x1, double y1, double x2, double y2);

        AcadTextPtr DrawText(AnsiString str, double height, AcAlignment alignment, double x, double y, double rotation = 0);
        AcadTextPtr DrawTextPS(AnsiString str, double height,
                        double x = 0, double y = 0, double rotation = 0);
        AcadArcPtr DrawArc(double centerX, double centerY, double radius, double sAngle, double eAngle);
        AcadEllipsePtr DrawEllipse(double centerX, double centerY, double MajorAxis,double MinorAxis);

        AcadHatchPtr FillArea(IDispatch **LoopObjects, int LoopObjectsCount,
                         int HatchColor = 0, WideString sHatchType = "SOLID", int hatchScale = 75);
        AcadHatchPtr FillAreaPS(IDispatch **LoopObjects, int LoopObjectsCount,
                         int HatchColor = 0, WideString sHatchType = "SOLID", int hatchScale = 75);
        AcadHatchPtr FillAreaBase(AcadHatchPtr hatch, IDispatch **LoopObjects, int LoopObjectsCount,
                         int HatchColor = 0, int hatchScale = 75);
                         
        void DrawRepeatTextInterval(WideString str, float sPosX, float ePosX,
                                         float PosY, float TextHeight,
                                         float step = 100000);
        int GetTextWidth(AnsiString text, int Height);
        /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

        /*БЛОКИ -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
        /**
         * set atribute with name PropertyName of block, with value,
         * set rot to -1 if u don't want to rotate object
        */
        void SetSignLabels(AcadBlockReferencePtr block, WideString value);
        void SplitString(AnsiString str, char delim, vector<AnsiString> &out, bool fRemoveEmpties = true);
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
        AcadLayoutPtr AddPaperSpace(WideString name);
        bool SetupViewport(AcadLayoutPtr layout, double x, double y,
                                        double width, double height);

        void BeginMSpace(AcadPViewportPtr viewport);
        void EndMSpace(AcadPViewportPtr viewport);                               
        bool SetupActiveViewportZoomWindow(double x, double y,
                   double width, double height);/*настроить вид видового экрана*/
        bool SetupActiveViewportZoomScale(double ZoomFactor);
        bool SetupActiveViewportZoomCenter(double x, double y,double scale);

        bool PrintActiveLayoutToFile(WideString FileName);
        bool PrintLayoutsToFile(WideString FileName, int* arrayofindexes, int count);
        AcadLayoutPtr SetAsActiveLayout(Variant index); /*выбрать активный Layout*/
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
        __property AcadDocumentPtr ActiveDocument = {read = getActiveDocument};
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
