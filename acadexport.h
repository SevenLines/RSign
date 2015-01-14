//---------------------------------------------------------------------------

#ifndef acadexportH
#define acadexportH

#include "without_autocad.h"
#ifndef WITHOUT_AUTOCAD

#include "Metrics.h"
#include "Const.h"
#include "RoadObj.h"
#include "AutoCADHelper.h"
#include <map>
#include <vector>
#include <Math.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

#define M_ROWPOS(t) iTop##t, iBottom##t

#undef StrToInt

using namespace std;

class KromkaObjectGroup;
class TFAutoCADExport;

struct drect {
   long double x0,y0,x1,y1;
   drect(long double _x0,long double _y0,long double _x1,long double _y1) {
      x0=min(_x0,_x1); x1=max(_x0,_x1); y0=min(_y0,_y1); y1=max(_y0,_y1);
   }
};
bool operator<(const drect &a,const drect &b) {
   boolean t=(a.x1<b.x0|| !(b.x1<a.x0) && a.y1<b.y0); // Я думаю это правильно :) K.
   return t;
}

class TAcadExport {
   private:
      AnsiString strSignsAbsent;
      AnsiString strMarkAbsent;
      AnsiString strAutoCADDir;
      AnsiString strInfoTemplate;
      AnsiString strProjectBarrierPrefix;
      int iAutoSaveInterval;

      vector<TPoint> SignsPositions; // будем заносить сюда позиции знаков,
                                     // чтобы не было наложений

      WideString strSidewalksHatch;
      WideString strProfileHatch; 
      AutoCADHelper AutoCAD;
      AcadLineType* RoadMark1;

      AcadBlockReferencePtr SignSpot1,SignSpot1_m,SignSpot2;
      AcadBlockReferencePtr Tube;
      AcadText *tText;

      int maxTopCount;
      int maxBottomCount, maxBottomCountGraphic;
      int HeaderTextHeight;
      int RCenter;

      int iProfileHatchScale;
      int iSidewalsHatchScale;
      int iFillHatchScale;
      int iMinBarrierSegmentLength;


      int iStep;   //шаг в сантиметрах   

      AutoCADTable tableTop,tableBottom, tableGraphic;
      float ScaleY, ScaleYBlock;
      int SlopeMax,SlopeMin, SlopeCur, SlopeHeight, SlopeLastFase;
      int UnderTextYOffset;
      int UnderTextHeight;
      bool fAlreadyDrawSignSpot;
      bool fAlreadyDrawTube;
      bool fAuto6_13, fLeftValueOnly6_13;
      bool fFillProfile;
      bool fShowAttachmentComments;
      bool fDrawTable, fTopAddRowsWithoutData, fBottomAddRowsWithoutData, fGraphicAddRowsWithoutData;
      TRoad *curRoad;

      int M_ROWPOS(0),M_ROWPOS(Slopes),M_ROWPOS(Barriers),M_ROWPOS(MoundH),M_ROWPOS(Curves),
          M_ROWPOS(AxeCount),M_ROWPOS(Sidewalks),M_ROWPOS(RoadCover), M_ROWPOS(AddRow);

      int iProfileTop, iBottomArtifacts, iGraphic, iBottomSurface, iRulerHeight;
      int iStart, iEnd;

      int tabOffsetRoadMark;
      int tabOffsetBarrier;
      int tabHeight;
      int textOffset;
      int smallGridMarkHeight;
      float fTextSize;
      TPoint lPointBarrier;
      int NotExistColor;

      map<drect,TRoadObject*> rectmap;                // wrote by K.
      // Функция для размещения прямоугольников на плоскости без пересечений
      // r - исходное местоположение прямоугольника, dir -- направление смещения
      // прямоугольника если желаемое место занято (L R U D)
      // store=true, если надо запомнить расположение прямоугольника
      // obj - указатель на объект который будет нарисован там (можно NULL)
      // При успехе функция возвращает true и изменяет r
      // wrote by K.      
      bool __fastcall FindPlacement(drect &r,char dir,bool store,TRoadObject *obj);

      void ResetLastPoints();

   public:

      int profileHeight;
      int iMarkLinesBottom, iMarkLinesTop;
      int M_ROWPOS(Axe);


      void (__closure *OutInfoLog)(AnsiString );
      void (__closure *ProgressChanged)(int , AnsiString );

      __fastcall TAcadExport(void);
      __fastcall ~TAcadExport(void);
      bool __fastcall BeginDocument(TRoad *road);
      bool __fastcall BindToCurrentDocument(TRoad *road);
      bool __fastcall ExportTables(TFAutoCADExport *form);
      bool __fastcall DrawTables(bool fExportRuler);
      bool __fastcall FillGaps(int iRow);
      bool __fastcall AddDocument();
      bool __fastcall AddLayer(AnsiString name);
      bool __fastcall OpenDocument(AnsiString name);
      bool __fastcall BindActiveDocument();
      void __fastcall hideApplication();
      void __fastcall showApplication();      

      AnsiString RoadName;

      bool __fastcall ExportProfil(TExtPolyline *Poly);

      bool __fastcall ExportRoadMetric(TExtPolyline *Poly,TMetricsKind kind, bool fEnd = false);
      bool __fastcall ExportAttach(TExtPolyline *Poly,TRoadAttach *a, bool fEnd = false);
      bool __fastcall ExportSign(TExtPolyline *Poly,TRoadSign *s, bool fEnd = false);
      // Функция передает знаки разбитые по группам
      bool __fastcall ExportSigns(TExtPolyline* Poly, TRoadSign** signs, int count, bool fEnd = false);
      bool __fastcall ExportRoadMark(TExtPolyline *Poly,TRoadMark *m,int line,String code, bool fEnd = false);
      bool __fastcall ExportTube(TExtPolyline *Poly,TRoadTube* t, bool fEnd = false);
      bool __fastcall ExportBridge(TExtPolyline *Poly,TRoadBridge *b, bool fEnd = false);
      bool __fastcall ExportBarrier(TExtPolyline *Poly,TRoadBarrier *b,bool exist, bool fEnd = false);
      bool __fastcall ExportSignal(TExtPolyline *Poly,TRoadSignal *s,bool exist, bool fEnd = false);
      bool __fastcall ExportCurve(TDangerCurve *c, bool fEnd = false);
      bool __fastcall ExportSlope(TDangerSlope *s, int fase = 1, bool fEnd = false);
      bool __fastcall ExportBusStop(TExtPolyline *Poly,TBusStop *s, bool fEnd = false);
      bool __fastcall ExportLighting(TExtPolyline *Poly,TRoadLighting *s, bool exist, bool fEnd = false);
//      bool __fastcall ExportEmbankment(...)
      bool __fastcall ExportMoundHeight(TMoundHeight *m, int fase = 0, bool fEnd = false);
      bool __fastcall ExportRestZone(TExtPolyline *Poly,TSquareRoadSideObject_Kromka *r, bool fEnd = false);
      bool __fastcall ExportSidewalk(KromkaObjectGroup *sidewalksGroup, bool fEnd=false);
      bool __fastcall ExportBorder(TExtPolyline *Poly,TLinearRoadSideObject *o,bool exist, bool fEnd = false);
      bool __fastcall ExportRoadCover(TExtPolyline *p, TRoadPart *t, bool fEnd = false);
      bool __fastcall ExportCommunication(TExtPolyline *p, TCommunication *t, bool fEnd = false);
      bool __fastcall ExportTrafficLight(TExtPolyline *p, vector<TTrafficLight*> &t, bool fEnd = false );
      //bool __fastcall ExportCityObjects(TExtPolyline *p, TTrafficLight *t, bool fEnd = false );

      bool __fastcall ExportTown(TExtPolyline *p, TTown *t, bool fEnd = false);
      bool __fastcall ExportPlan(TExtPolyline *p, TLinearRoadSideObject *t, int kind, bool fEnd=false);
      int __fastcall ExportAddRows(AnsiString path, AutoCADTable *table, bool check = false);
      int __fastcall ExportGraphic(AnsiString path, bool check);
      int __fastcall ExportGraphicPath(AnsiString path, bool check);

      int __fastcall ExportTopAddRows(AnsiString DirPath, bool check = false);
      int __fastcall ExportBottomAddRows(AnsiString DirPath, bool check = false);


      void ExportAddRowLine( AutoCADTable *table, int iRow, int iPos, int iEnd,  AnsiString str);


      void __fastcall DrawGrid(int step);
      AcadBlockReferencePtr DrawBlockOnLine(String blockName, TPoint p1, TPoint p2, String lengthPropName, double scale=1);

      AcadPolylinePtr DrawPolyPoints(TExtPolyline *Poly, bool fUseCodes = true, bool fLockGaps = false,
                        void(*lineEditFunction)(AcadPolylinePtr&, void* data)=0, void* data=0);
                        
      AcadPolylinePtr DrawPolyLine(vector<double> &points);

      void __fastcall DrawTextUnderLine(TPoint p1, TPoint p2, AnsiString text);

      void __fastcall DrawTextOverPoly(TExtPolyline *Poly, AnsiString text,
              AnsiString(__closure *textControlFunction)(AnsiString text, TPoint pStart, TPoint pEnd, TPoint centerPoint, float angle)=0);

      TPoint __fastcall GetCenterOnPolyline(TExtPolyline *p, int minx, int maxx, float* out_angle=0,
                                        int* width_of_sector=0, TPoint* pointStart=0, TPoint* pointEnd=0);

      AnsiString RoadMarkTextDraw(AnsiString text, TPoint pStart, TPoint pEnd, TPoint centerPoint, float angle);

      AcadPolylinePtr DrawRoadMark(TExtPolyline *Poly, AnsiString name,
                                 int iRow, int line, AutoCADTable *table, bool dontDrawPolyLine=false);

      float GetAngle(TPoint &p1, TPoint &p2, float *length = 0);
      AcadBlockReferencePtr DrawBorder(vector<TPoint> &points, AnsiString blockname, bool fExist);
      AcadBlockReferencePtr DrawBarrier(vector<TPoint> &points, AnsiString blockname, bool fFlip, bool fExist, bool fOpenLeft = false,int *fLastVisible = 0);
      int findSignSuperposition(TPoint pos, int radius);

      void DrawSign(
          AnsiString Name,
          AnsiString label,
          AutoCADPoint pos,
          int xoffset,
          int yoffset,
          double rotation,
          double rotationHandle,
          double scale,
          bool fOnAttachment,
          AcadBlockReferencePtr &signspot,
          bool fUnderRoad
      );

      void ExportRuler(int iStart, int iEnd, bool fEnd);

      void __fastcall TAcadExport::SetLayerOrder(AnsiString LayerName, AnsiString order);
      void SetAttributes(AcadBlockReferencePtr block, AnsiString labels);
      void Print();
      // столбы освещения
      void __fastcall EndDocument();
};
//---------------------------------------------------------------------------

#endif // WITHOUT_AUTOCAD

#endif

