//---------------------------------------------------------------------------

#ifndef acadexportH
#define acadexportH
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

#define M_ROWPOS(t) iTop##t, iBottom##t

using namespace std;

#include "AutoCADPrintForm.h"
#include "AutoCADExportForm.h"

struct drect {
   long double x0,y0,x1,y1;
   drect(long double _x0,long double _y0,long double _x1,long double _y1) {
      x0=min(_x0,_x1); x1=max(_x0,_x1); y0=min(_y0,_y1); y1=max(_y0,_y1);
   }
};
bool operator<(const drect &a,const drect &b) {
   boolean t=(a.x1<b.x0|| !(b.x1<a.x0) && a.y1<b.y0); // � ����� ��� ��������� :) K.
   return t;
}

class TAcadExport {
   private:
      AnsiString strSignsAbsent;
      AnsiString strMarkAbsent;
      AnsiString strAutoCADDir;
      AnsiString strInfoTemplate;

      vector<TPoint> SignsPositions; // ����� �������� ���� ������� ������,
                                     // ����� �� ���� ���������

      WideString strSidewalksHatch;
      WideString strProfileHatch; 
      AutoCADHelper AutoCAD;
      AcadLineType* RoadMark1;

      AcadBlockReferencePtr SignSpot1,SignSpot2;
      AcadBlockReferencePtr Tube;
      AcadText *tText;

      int maxTopCount;
      int maxBottomCount, maxBottomCountGraphic;
      int HeaderTextHeight;
      int RCenter;

      int iProfileHatchScale;
      int iSidewalsHatchScale;
      int iFillHatchScale;


      int iStep;   //��� � �����������   

      AutoCADTable tableTop,tableBottom, tableGraphic;
      float ScaleY;
      int SlopeMax,SlopeMin, SlopeCur, SlopeHeight, SlopeLastFase;
      int UnderTextYOffset;
      int UnderTextHeight;
      bool fAlreadyDrawSignSpot;
      bool fAlreadyDrawTube;
      bool fAuto6_13, fLeftValueOnly6_13;
      bool fFillProfile;
      bool fDrawTable, fTopAddRowsWithoutData, fBottomAddRowsWithoutData, fGraphicAddRowsWithoutData;
      TRoad *curRoad;

      int M_ROWPOS(0),M_ROWPOS(Slopes),M_ROWPOS(Barriers),M_ROWPOS(MoundH),M_ROWPOS(Curves),
          M_ROWPOS(AxeCount),M_ROWPOS(Sidewalks),M_ROWPOS(RoadCover), M_ROWPOS(AddRow);

      int iProfileTop, iBottomArtifacts, iGraphic, iBottomSurface;
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
      // ������� ��� ���������� ��������������� �� ��������� ��� �����������
      // r - �������� �������������� ��������������, dir -- ����������� ��������
      // �������������� ���� �������� ����� ������ (L R U D)
      // store=true, ���� ���� ��������� ������������ ��������������
      // obj - ��������� �� ������ ������� ����� ��������� ��� (����� NULL)
      // ��� ������ ������� ���������� true � �������� r
      // wrote by K.      
      bool __fastcall FindPlacement(drect &r,char dir,bool store,TRoadObject *obj);

      void ResetLastPoints();

   public:

      int profileHeight;
      int iMarkLinesBottom, iMarkLinesTop;
      int M_ROWPOS(Axe);


      void (__closure *OutInfoLog)(AnsiString &);

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

      AnsiString RoadName;

      bool __fastcall ExportProfil(TExtPolyline *Poly);

      bool __fastcall ExportRoadMetric(TExtPolyline *Poly,TMetricsKind kind, bool fEnd = false);
      bool __fastcall ExportAttach(TExtPolyline *Poly,TRoadAttach *a, bool fEnd = false);
      bool __fastcall ExportSign(TExtPolyline *Poly,TRoadSign *s, bool fEnd = false);
      // ������� �������� ����� �������� �� �������
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
      bool __fastcall ExportSidewalk(TExtPolyline *Poly,TSquareRoadSideObject_Kromka *s,bool exist, bool fEnd = false);
      bool __fastcall ExportBorder(TExtPolyline *Poly,TLinearRoadSideObject *o,bool exist, bool fEnd = false);
      bool __fastcall ExportRoadCover(TExtPolyline *p, TRoadPart *t, bool fEnd = false);
      bool __fastcall ExportCommunication(TExtPolyline *p, TCommunication *t, bool fEnd = false);

      bool __fastcall ExportTown(TExtPolyline *p, TTown *t, bool fEnd = false);
      bool __fastcall ExportPlan(TExtPolyline *p, TLinearRoadSideObject *t, int kind, bool fEnd=false);
      int __fastcall ExportAddRows(AnsiString path, AutoCADTable *table, bool check = false);
      int __fastcall ExportGraphic(AnsiString path, bool check);
      int __fastcall ExportGraphicPath(AnsiString path, bool check);

      int __fastcall ExportTopAddRows(AnsiString DirPath, bool check = false);
      int __fastcall ExportBottomAddRows(AnsiString DirPath, bool check = false);


      void ExportAddRowLine( AutoCADTable *table, int iRow, int iPos, int iEnd,  AnsiString str);


      void __fastcall DrawGrid(int step);

      AcadPolylinePtr DrawPolyPoints(TExtPolyline *Poly, bool fUseCodes = true, bool fLockGaps = false);
      AcadPolylinePtr DrawRoadMark(TExtPolyline *Poly, AnsiString name,
                                 int iRow, int line, AutoCADTable *table);
      float GetAngle(TPoint &p1, TPoint &p2, float *length = 0);
      AcadBlockReferencePtr DrawBorder(vector<TPoint> &points, AnsiString blockname, bool fExist);
      AcadBlockReferencePtr DrawBarrier(vector<TPoint> &points, AnsiString blockname, bool fFlip, bool fExist, bool fOpenLeft = false,int *fLastVisible = 0);
      int findSignSuperposition(TPoint pos, int radius);
      void DrawSign(AnsiString Name,  AnsiString label, AutoCADPoint pos,
                    double xoffset, double yoffset, double rotation, double rotationHandle,
                    double scale, bool fOnAttachment = False);

      void ExportRuler(int iStart, int iEnd, bool fEnd);

      void SetAttributes(AcadBlockReferencePtr block, AnsiString labels);
      void Print();
      // ������ ���������
      void __fastcall EndDocument();
};
//---------------------------------------------------------------------------
#endif
