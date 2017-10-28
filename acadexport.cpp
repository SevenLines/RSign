//---------------------------------------------------------------------------



#pragma hdrstop

#include "without_autocad.h"
#ifndef WITHOUT_AUTOCAD

#include "acadexport.h"
#include "AcadExportThread.h"
#include <list.h>
#include "MickMacros.h"
#include "ProgressFrm.h"
#include "AcadExportObjects.h"
#include "AutoCADExportForm.h"
#include "AutoCADPrintForm.h"
#include "Helpers.h"

using namespace std;

#define M_RESETROWPOS(t) iTop##t=iBottom##t
//---------------------------------------------------------------------------

#pragma package(smart_init)


struct barrierPointAsc : binary_function<TPoint, TPoint, bool> {
    bool operator() (const TPoint &p1, const TPoint &p2) const {
        return p1.x < p2.x;
    }
};

void SetObjectColor(IAcadEntity *object, unsigned char R, unsigned char G, unsigned char B)
{
    AcadAcCmColor *color =  object->TrueColor;
    color->SetRGB(R, G, B);
    object->TrueColor = color;
}

__fastcall TAcadExport::TAcadExport(void) {
    ScaleY = 6;
    strAutoCADDir = ExtractFileDir(Application->ExeName) + "\\AutoCAD\\";

    AutoCAD.SignLabelParser =  Helpers::SignLabelParser;

    tabHeight = 2000;
    tabOffsetRoadMark = 15000;
    fTextSize = 0.25;
    textOffset = tabHeight * (1 - fTextSize) / 2;
    tabOffsetBarrier = tabOffsetRoadMark + tabHeight;

    tableTop.Owner = &AutoCAD;
    tableBottom.Owner = &AutoCAD;
    tableGraphic.Owner = &AutoCAD;


    tableTop.RepeatInterval = 100000;
    tableTop.RepeatInterval = 100000;

    tableBottom.HeaderWidth = 20000;
    tableBottom.RepeatInterval = 100000;

    tableGraphic.HeaderWidth = 20000;
    tableGraphic.RepeatInterval = 20000;

    tableTop.kBottomEmptyPadding = 0.2;
    tableBottom.kBottomEmptyPadding = 0.2;
    tableGraphic.kBottomEmptyPadding = 0.2;

    tableTop.kPadding = 0.90;
    tableBottom.kPadding = 0.90;
    tableGraphic.kPadding = 0.90;

    tableTop.AutoShrink = true;
    tableGraphic.AutoShrink = true;
    //tableTop.AutoShrinkOneLetterWidth = 2300;
    tableBottom.AutoShrink = true;
    //tableBottom.AutoShrinkOneLetterWidth = 2300;


    OutInfoLog = 0;
    fAuto6_13 = true;
}

void TAcadExport::ResetLastPoints()
{
    lPointBarrier = TPoint(0, tabOffsetBarrier);
    fAlreadyDrawSignSpot = false;
    fAlreadyDrawTube = false;
    fDrawTable = false;
    SlopeMax = 0, SlopeMin = 0, SlopeCur = 0, SlopeLastFase = 0;
}

__fastcall TAcadExport::~TAcadExport(void) {
}

AcadPolylinePtr TAcadExport::DrawPolyLine(vector<double> &points)
{
    AcadPolylinePtr pl;
    if (points.size() >= 4) {
        pl = AutoCAD.DrawPolyLine(points, 2);
    }
    return pl;
}

AcadPolylinePtr  TAcadExport::DrawPolyPoints(TExtPolyline *Poly, bool fUseCodes, bool fLockGaps,
        void(*lineEditFunction)(AcadPolylinePtr&, void* data), void* data)
{
    vector<double> points, range;
    vector<int> codes;
    AcadPolylinePtr pl;

    if (Poly->Count < 2) {
        return pl;
    }

    for (int i = 0; i < Poly->Count; ++i) {
        points.push_back(Poly->Points[i].x);
        points.push_back(-ScaleY * Poly->Points[i].y);
        codes.push_back(Poly->Codes[i].Visible());
    }

    int iLast = 0;
    if (fUseCodes) {
        if (Poly->Count >= 2 && codes[0]) {
            range.push_back(*points.begin());
            range.push_back(*(points.begin() + 1));
            range.push_back(*(points.end() - 2));
            range.push_back(*(points.end() - 1));
            pl = DrawPolyLine(range);
            if (lineEditFunction) {
                lineEditFunction(pl, data);
            }
        }
        for (int i = 1; i < codes.size(); i++) {
            if (!codes[i]) {
                if ( i - iLast > 1 ) {
                    range = vector<double>(
                                points.begin() + 2 * iLast,
                                points.begin() + 2 * i);
                    pl = DrawPolyLine(range);
                    if (lineEditFunction) {
                        lineEditFunction(pl, data);
                    }
                }
                iLast = i;
            }
        }
        if (codes[codes.size() - 1]) {
            range = vector<double>(
                        points.begin() + 2 * iLast,
                        points.end());
            if (codes[0]) {
                range.push_back(points[0]);
                range.push_back(points[1]);
            }
            pl = DrawPolyLine(range);
            if (lineEditFunction) {
                lineEditFunction(pl, data);
            }
        }
    } else {
        if (fLockGaps && Poly->Count > 2) {
            points.push_back(Poly->Points[0].x);
            points.push_back(-ScaleY * Poly->Points[0].y);
        }
        pl = DrawPolyLine(points);
        if (lineEditFunction) {
            lineEditFunction(pl, data);
        }
    }
    return pl;
}

bool __fastcall TAcadExport::BindToCurrentDocument(TRoad *road)
{
    curRoad = road;
    AutoCAD.RunAutoCAD();
    AutoCAD.BindToActiveDocument();
    return true;
}

void __fastcall TAcadExport::SetAutoCADVersion(AnsiString version)
{
    AutoCAD.setAutoCADVersion(version);
}

void TAcadExport::Print()
{
    FAutoCADPrint->helper = &AutoCAD;
    if (curRoad) {
        FAutoCADPrint->ePos = curRoad->LMax;
        FAutoCADPrint->sPos = curRoad->LMin;
    }
    FAutoCADPrint->ShowModal();
}

bool __fastcall TAcadExport::AddDocument()
{
    try {
        AutoCAD.ResetBlocksCollection();
        AutoCAD.AddDocument(strAutoCADDir + "SignsDef.dwt");
        AutoCAD.SendCommand(WideString("CLAYER 0\n"));
        AutoCAD.ActiveDocument->ActiveSpace = acModelSpace;
        AutoCAD.CheckExistingBlocks();
    } catch (...) {
        return false;
    }
    return true;
}

bool __fastcall TAcadExport::OpenDocument(AnsiString name)
{
    static length;
    length = name.Length();
    if (length > 2) {
        if (name[1] == '.' && (name[2] == '/') || (name[2] == '\\')) {
            name = ExtractFileDir(Application->ExeName) + name.SubString(2, length - 1);
        }
    } else {
        return false;
    }
    try {
        AutoCAD.ResetBlocksCollection();
        if (ExtractFileExt(name) == ".dwt") {
            AutoCAD.AddDocument(name);
        } else {
            AutoCAD.OpenDocument(name);
        }
        AutoCAD.SendCommand(WideString("CLAYER 0\n"));
        AutoCAD.ActiveDocument->ActiveSpace = acModelSpace;
        AutoCAD.CheckExistingBlocks();
        BUILDER_INFO("Успешно открыл документ и пересчитал блоки");
    } catch (...) {
        BUILDER_ERROR("Возникла непредвиденая ошибка при открытии документа!");
        return false;
    }
    return true;
}


bool __fastcall TAcadExport::BindActiveDocument()
{
    AutoCAD.ResetBlocksCollection();
    if ( AutoCAD.BindToActiveDocument() ) { // function return false on error
        AutoCAD.SendCommand(WideString("CLAYER 0\n"));
        AutoCAD.ActiveDocument->ActiveSpace = acModelSpace;
        AutoCAD.CheckExistingBlocks();
        return true;
    }
    return false;
}

void __fastcall TAcadExport::hideApplication()
{
    //AutoCAD.ActiveDocument->SendCommand(WideString("_.zoom _e\n"));
    AutoCAD.Application->Visible = 0;
}

void __fastcall TAcadExport::showApplication()
{
    //AutoCAD.ActiveDocument->SendCommand(WideString("_.zoom _e\n"));
    AutoCAD.Application->Visible = -1;
}

bool __fastcall TAcadExport::BeginDocument(TRoad *road) {
    try {
        curRoad = road;

        ResetLastPoints();
        rectmap.clear();

        AutoCAD.RunAutoCAD();
        AutoCAD.DisableAutoSave();
        /*iAutoSavefInterval = AutoCAD.Application->Preferences->OpenSave->AutoSaveInterval;
        AutoCAD.ActiveDocument->SendCommand(WideString("SAVETIME 0\n")); */

        strSignsAbsent = "";
        strMarkAbsent = "";

        /*разметка таблица*/
        tableTop.TableWidth = road->LMax;
        tableTop.FillGapsBegin = road->LMin;

        tableBottom.TableWidth = road->LMax;
        tableBottom.FillGapsBegin = road->LMin;

        tableGraphic.TableWidth = road->LMax;
        tableGraphic.FillGapsBegin = road->LMin;
        /**/

    } catch (...) {
        return false;
    }
    return true;
}

bool __fastcall TAcadExport::AddLayer(AnsiString l_name)
{
    IAcadLayers *layers = 0;
    try {
        layers = AutoCAD.ActiveDocument->get_Layers();
    } catch (...) {
        BUILDER_ERROR("Не смог получить доступ к слоям");
        return false;
    }
    if (!layers)
        return false;
    try {
        IAcadLayer * layer_ptr = layers->Add(WideString(l_name).c_bstr());
    } catch (...) {
        BUILDER_ERROR("Не удалось добавить слой " << l_name.c_str());
    }
    AutoCAD.SendCommand(WideString("CLAYER " + l_name + "\n"));

    return true;
}


bool __fastcall TAcadExport::DrawTables(bool fWithRuler)
{
    int i;

    if (!fDrawMap) { // режим карты отключен
        if (tableTop.RowsCount)tableTop.DrawTable();
        if (tableTop.drawHeaders) {
            tableTop.DrawHeaderText(iTopSidewalks, "Тротуары слева", HeaderTextHeight);
            tableTop.DrawHeaderText(iProfileTop, "Продольный профиль", HeaderTextHeight);
            tableTop.DrawHeaderText(iTopCurves, "Элементы дороги в плане", HeaderTextHeight);
            tableTop.DrawHeaderText(iTopSlopes, "Элементы дороги в\nпродольном профиле", HeaderTextHeight);
            tableTop.DrawHeaderText(iTopMoundH, "Высота насыпи слева", HeaderTextHeight);
            tableTop.DrawHeaderText(iTopBarriers, "Дорожные ограждение и\nнаправляющие устр-ва слева", HeaderTextHeight);
            tableTop.DrawHeaderText(iTop0, "осевая линия", HeaderTextHeight);
            for (i = 0; i < iTopAxeCount; i++) {
                tableTop.DrawHeaderText(iTopAxe - i, IntToStr(i + 1) + "-я от осевой", HeaderTextHeight);
            }
        }
        if (tableBottom.RowsCount) tableBottom.DrawTable();
        if (tableBottom.drawHeaders) {
            tableBottom.DrawHeaderText(iBottomSidewalks, "Тротуары справа", HeaderTextHeight);
            tableBottom.DrawHeaderText(iBottomSurface, "Тип покрытия", HeaderTextHeight);
            tableBottom.DrawHeaderText(iBottomMoundH, "Высота насыпи справа", HeaderTextHeight);
            tableBottom.DrawHeaderText(iBottomBarriers, "Дорожные ограждение и\nнаправляющие устр-ва справа", HeaderTextHeight);
            tableBottom.DrawHeaderText(iBottom0, "осевая линия", HeaderTextHeight);
            if (~iBottomArtifacts) {
                tableBottom.DrawHeaderText(iBottomArtifacts, "Искусственные сооружения СЛЕВА", HeaderTextHeight);
                tableBottom.DrawHeaderText(iBottomArtifacts + 1, "Искусственные сооружения СПРАВА", HeaderTextHeight);
            }
            tableBottom.DrawHeaderText(iBottomCurves, "Элементы дороги в плане", HeaderTextHeight);
            tableBottom.DrawHeaderText(iBottomSlopes, "Элементы дороги в\nпродольном профиле", HeaderTextHeight);

            for (i = 0; i < iBottomAxeCount; i++) {
                tableBottom.DrawHeaderText(iBottomAxe + i, IntToStr(i + 1) + "-я от осевой", HeaderTextHeight);
            }
        }

        if (tableGraphic.RowsCount) tableGraphic.DrawTable();
    }

    IAcadSummaryInfoPtr si = AutoCAD.ActiveDocument->SummaryInfo;
    si->set_Comments(WideString(IntToStr((int)tableTop.TableHeight + iRulerHeight)
                                + "\r\n" + IntToStr((int)tableBottom.TableHeight)
                                + "\r\n" + IntToStr((int) - tableBottom.LeftTop.y)
                                + "\r\n" + IntToStr((int)tableBottom.FillGapsBegin)
                                + "\r\n" + IntToStr((int)tableBottom.TableWidth)
                                + "\r\n" + IntToStr((int)iStep)
                                + "\r\n# высота верхней таблицы"
                                + "\r\n# высота нижней таблицы"
                                + "\r\n# растояние от центра до низа верхней таблицы"
                                + "\r\n# начало дороги"
                                + "\r\n# конец дороги"
                                + "\r\n# шаг"
                               ));
    si->set_Keywords(WideString(strInfoTemplate));

    TReplaceFlags rf;
    rf << rfReplaceAll;
    si->set_Title(WideString(StringReplace(RoadName, ".", " ", rf)));

    return true;
}

bool __fastcall TAcadExport::ExportTables(TFAutoCADExport *form)
{
    fAuto6_13 = form->ExportAuto6_13;
    fLeftValueOnly6_13 = form->ExportLeftValueOnly6_13;

    RCenter = form->RCenter;
    int iTopAddRowsCount = 0;
    int iBottomAddRowsCount = 0;
    iTopAxeCount = iBottomAxeCount = 0;
    iRulerHeight = form->ExportRuler ? form->RowHeight : 0;

    M_RESETROWPOS(AxeCount) = 0;

    M_RESETROWPOS(RoadCover) = M_RESETROWPOS(0) = M_RESETROWPOS(Slopes) =
                                   M_RESETROWPOS(Curves) = M_RESETROWPOS(Barriers) = M_RESETROWPOS(MoundH) =
                                           M_RESETROWPOS(Axe) = M_RESETROWPOS(Sidewalks) = M_RESETROWPOS(AddRow) = -1;

    iBottomArtifacts = iProfileTop = iGraphic = -1 ;

    tableTop.drawHeaders = form->ExportMakeHeader;
    tableBottom.drawHeaders = form->ExportMakeHeader;

    int count = 0, i;

    HeaderTextHeight = form->HeaderTextHeight;
    strInfoTemplate = form->EditInfoTemplate;
    strProjectBarrierPrefix = form->EditProjectBarrierPrefix;

    tableTop.RowHeight = form->RowHeight;
    tableTop.HeaderWidth = form->ExportMakeHeader ? form->HeaderWidth : 0;
    tableTop.AutoShrinkOneLetterWidth = form->AutoShrinkOneLetterWidth;



    tableBottom.AutoShrinkOneLetterWidth = form->AutoShrinkOneLetterWidth;
    tableBottom.RowHeight = form->RowHeight;
    tableBottom.HeaderWidth = form->ExportMakeHeader ? form->HeaderWidth : 0;



    tableGraphic.AutoShrinkOneLetterWidth = form->AutoShrinkOneLetterWidth;
    tableGraphic.RowHeight = form->GrphRowHeight;
    tableGraphic.HeaderWidth = form->ExportMakeHeader ? form->HeaderWidth : 0;


    fBottomAddRowsWithoutData = fTopAddRowsWithoutData = form->ExportTopAddRowsWithoutData;
    fShowAttachmentComments = form->ExportShowAttachmentComments;
    fDrawMap = form->ExportDrawMap;

    iMinBarrierSegmentLength = form->MinBarrierSegmentLength;
    iProfileHatchScale = form->ProfileHatchScale;
    iSidewalsHatchScale = form->SidewalksHatchScale;
    iFillHatchScale = form->TableHatchScale;
    strSidewalksHatch = form->EditSidewalksHatch;
    strProfileHatch = form->EditProfileHatch;
    tableTop.EmptyFill = form->EditTableHatch;
    tableTop.EmptyFillScale = iFillHatchScale;
    tableBottom.EmptyFill = form->EditTableHatch;
    tableBottom.EmptyFillScale = iFillHatchScale;
    tableGraphic.EmptyFill = form->EditTableHatch;
    tableGraphic.EmptyFillScale = iFillHatchScale;
    fFillProfile = !strProfileHatch.IsEmpty();

    iStart = form->ExportSection ? 100 * form->Start : -1;
    iEnd = form->ExportSection ? 100 * form->End : -1;

    if (~iStart) {
        tableBottom.FillGapsBegin = iStart;
        tableTop.FillGapsBegin = iStart;
    }

    UnderTextYOffset = form->UnderTextYOffset;
    UnderTextHeight = form->UnderTextHeight;
    UnderTextYOffset = UnderTextHeight * 0.75;

    AutoCAD.strLostBlocks = "";
    lessForVerticalLabels = form->UseVerticalTextIfLess;

    tableTop.lessForVerticalLabels = lessForVerticalLabels * 100;
    tableBottom.lessForVerticalLabels = lessForVerticalLabels * 100;
    tableGraphic.lessForVerticalLabels = lessForVerticalLabels * 100;

    smallGridMarkHeight = form->SmallGridMarkHeight;

    ScaleY = (float)form->ScaleY / 100;
    ScaleYBlock = (float)form->ScaleYBlock / 100;
    if (ScaleYBlock <= 0) ScaleYBlock = ScaleY;

    profileHeight = form->RowHeight;

    NotExistColor = form->NotExistsColor;

    iTopAddRowsCount = ExportTopAddRows(form->EditTopAddRows, true);
    form->setTopAddRowsCount(iTopAddRowsCount);

    count += (~(iTopSidewalks = form->getTopRow("тротуары"))) ? 1 : 0;
    count += (~(iTopMoundH = form->getTopRow("высоты насыпи"))) ? 1 : 0;
    count += (~(iTopBarriers = form->getTopRow("дорожные ограждения и направляющие устр-ва"))) ? 1 : 0;
    count += (~(iTop0 = form->getTopRow("разметка осевая"))) ? 1 : 0;
    count += (~(iTopAxe = form->getTopRow("разметка от осевой"))) ? 1 : 0;

    if (~iTopAxe) {
        iTopAxeCount = iMarkLinesTop ? iMarkLinesTop : form->TableRowLinesTop;
        count += iTopAxeCount - 1;
        iTopAxe += iTopAxeCount - 1;
    }
    count += (~(iProfileTop = form->getTopRow("продольный профиль"))) ? 1 : 0;
    count += (~(iTopCurves = form->getTopRow("кривые в плане"))) ? 1 : 0;
    count += (~(iTopSlopes = form->getTopRow("продольные уклоны"))) ? 1 : 0;
    count += (~(iTopRoadCover = form->getTopRow("тип покрытия"))) ? 1 : 0;
    count += (~(iTopAddRow = form->getTopRow("дополнительные строки"))) ? iTopAddRowsCount : 0;

    tableTop.RowsCount = count;

    tableTop.LeftTop = AutoCADPoint(0, tableTop.TableHeight + form->RCenter + iRulerHeight);

    tableTop.FillGaps[-1] = false;
    if (iTopMoundH >= 0)tableTop.FillGaps[iTopMoundH] = false;
    if (iTopBarriers >= 0)tableTop.FillGaps[iTopBarriers] = true;
    if (iTop0 >= 0)tableTop.FillGaps[iTop0] = true;
    if (iTopCurves >= 0)tableTop.FillGaps[iTopCurves] = false;
    if (iTopSlopes >= 0)tableTop.FillGaps[iTopSlopes] = false;
    if (iTopSidewalks >= 0)tableTop.FillGaps[iTopSidewalks] = true;

    for (i = 0; i < iTopAxeCount; i++) {
        tableTop.FillGaps[iTopAxe - i] = true;
    }

    if (!~iTopAddRow) {
        for (i = iTopAddRow; i < iTopAddRow + iTopAddRowsCount; i++) {
            tableTop.FillGaps[i] = true;
        }
    }

    count = 0;

    iBottomAddRowsCount = ExportBottomAddRows(form->EditTopAddRows, true);
    form->setBottomAddRowsCount(iBottomAddRowsCount);

    count += (~(iBottomSidewalks = form->getBottomRow("тротуары"))) ? 1 : 0;
    count += (~(iBottomMoundH = form->getBottomRow("высоты насыпи"))) ? 1 : 0;
    count += (~(iBottomBarriers = form->getBottomRow("дорожные ограждения и направляющие устр-ва"))) ? 1 : 0;
    count += (~(iBottom0 = form->getBottomRow("разметка осевая"))) ? 1 : 0;
    count += (~(iBottomAxe = form->getBottomRow("разметка от осевой"))) ? 1 : 0;

    if (~iBottomAxe) {
        iBottomAxeCount = iMarkLinesBottom ? iMarkLinesBottom : form->TableRowLinesBottom;
        count += iBottomAxeCount - 1;
    }
    count += (~(iBottomCurves = form->getBottomRow("кривые в плане"))) ? 1 : 0;
    count += (~(iBottomSurface = form->getBottomRow("тип покрытия"))) ? 1 : 0;
    count += (~(iBottomSlopes = form->getBottomRow("продольные уклоны"))) ? 1 : 0;
    count += (~(iBottomArtifacts = form->getBottomRow("искусственные сооружения"))) ? 2 : 0; //две строки на искусс.сооруж.
    count += (~(iBottomAddRow = form->getBottomRow("дополнительные строки"))) ? iBottomAddRowsCount : 0;
    tableBottom.RowsCount  = count;

    tableBottom.RowsCount = maxBottomCountGraphic = tableBottom.RowsCount;
    /*if(form->ExportGraphic) {
    tableBottom.RowsCount = maxBottomCountGraphic + ExportGraphic(form->EditTopAddRows,true);
    }else{
    tableBottom.RowsCount = maxBottomCountGraphic;
    }*/

    tableBottom.FillGaps[-1] = false;
    if (iBottomMoundH >= 0)tableBottom.FillGaps[iBottomMoundH] = false;
    if (iBottomBarriers >= 0)tableBottom.FillGaps[iBottomBarriers] = true;
    if (iBottom0 >= 0)tableBottom.FillGaps[iBottom0] = true;
    if (iBottomCurves >= 0)tableBottom.FillGaps[iBottomCurves] = false;
    if (iBottomSlopes >= 0)tableBottom.FillGaps[iBottomSlopes] = false;
    if (iBottomSidewalks >= 0)tableBottom.FillGaps[iBottomSidewalks] = true;


    tableBottom.LeftTop = AutoCADPoint(0, -form->RCenter);


    for (i = 0; i < iBottomAxeCount; i++) {
        tableBottom.FillGaps[iBottomAxe + i] = true;
    }

    for (i = iBottomAddRow; i < iBottomAddRowsCount + iBottomAddRow; i++) {
        tableBottom.FillGaps[i] = true;
    }

    tableGraphic.RowsCount =  ExportGraphic(form->EditTopAddRows, true);
    tableGraphic.LeftTop = AutoCADPoint(0, -form->RCenter - tableBottom.TableHeight);

    iStep = form->Step;
    return true;
}

bool __fastcall TAcadExport::FindPlacement(drect &r, char dir, bool store, TRoadObject *obj) {
    map<drect, TRoadObject*>::iterator it = rectmap.find(r);
    while (it != rectmap.end()) {
        if (dir == 'L') {
            long double dx = r.x1 - it->first.x0 + 1;
            r.x1 -= dx;
            r.x0 -= dx;
        }
        else if (dir == 'R') {
            long double dx = it->first.x1 - r.x0 + 1;
            r.x1 += dx;
            r.x0 += dx;
        }
        else if (dir == 'D') {
            long double dy = r.y1 - it->first.y0 + 1;
            r.y1 -= dy;
            r.y0 -= dy;
        }
        else if (dir == 'U') {
            drect t = it->first;
            long double dy = it->first.y1 - r.y0 + 1;
            r.y1 += dy;
            r.y0 += dy;
        } else
            return false;
        it = rectmap.find(r);
    }
    if (store)
        rectmap[r] = obj;
    return true;
}


void __fastcall TAcadExport::SetLayerOrder(AnsiString LayerName, AnsiString order)
{
    AutoCAD.ActiveDocument->SendCommand(WideString("(setq ss (ssget \"x\" (list (cons 8 \"" + LayerName + "\"))))\n"));
    AutoCAD.ActiveDocument->SendCommand(WideString("(command \"_draworder\" ss \"\" \"" + order + "\")\n"));
}

void __fastcall TAcadExport::EndDocument(AnsiString savePath) {
    rectmap.clear();
    //AutoCAD.ActiveDocument->SendCommand(WideString("SAVETIME " + IntToStr(iAutoSaveInterval) + "\n"));
    //AutoCAD.Application->ZoomAll();
    SetLayerOrder("RoadMark", "_back");
    SetLayerOrder("Borders", "_back");
    SetLayerOrder("RoadSidewalks", "_back");
    SetLayerOrder("RoadPlan", "_back");
    SetLayerOrder("RoadTrafficLights", "_front");
    SetLayerOrder("RoadMetrics", "_back");
    SetLayerOrder("RoadSurface", "_back");
    SetLayerOrder("RoadTown", "_back");


    AutoCAD.ActiveDocument->SendCommand(WideString("_.zoom _e\n"));

    AnsiString strMessage = "";
    if (!strSignsAbsent.IsEmpty() || !AutoCAD.strLostBlocks.IsEmpty()) {
        strMessage += "-=-=-=-=-=-=-=-=-\nСледующие знаки отсутствуют:" + strSignsAbsent;
        strMessage += AutoCAD.strLostBlocks;
        strMessage += "\n-=-=-=-=-=-=-=-=-\n";
    }
    if (!strMarkAbsent.IsEmpty()) {
        strMessage += "-=-=-=-=-=-=-=-=-\nНе определены типы линий для:" + strMarkAbsent + "\nсмотри табл. Classifier\nClass_id = 55";
        strMessage += "\n-=-=-=-=-=-=-=-=-\n";
    }
    if (!strMessage.IsEmpty()) ShowMessage(strMessage);

    if (fAlreadyDrawSignSpot) {
        SignSpot1->Delete();
        SignSpot1_m->Delete();
        SignSpot2->Delete();
    }
    if (fAlreadyDrawTube) {
        Tube->Delete();
    }
    AutoCAD.EnableAutoSave();
    
    if (savePath != "") {
       AutoCAD.ActiveDocument->SaveAs(WideString(savePath));
    } 
}

bool _fastcall TAcadExport::ExportProfil(TExtPolyline *Poly) {
    if (fDrawMap) return true; // в редиме карты ничего не рисуем

    int i, count;
    double *points;
    double maxDegree = (float)2.0f / 180.0f * 3.14f;

    count = Poly->Count;
    points = new double[(Poly->Count + 1) * 2];

    TPoint p1, p2, p3;

    list<TPoint> pts;
    int step = 50;
    for (i = 0; i < count; i += step) {
        points[2 * i] = Poly->Points[i].x;
        points[2 * i + 1] = Poly->Points[i].y + tableTop.LeftTop.y - tableTop.RowOffsetY(iProfileTop); // - tableTop.RowHeight;
        pts.push_back(TPoint(points[2 * i], points[2 * i + 1]));
    }

    points[2 * count] = Poly->Points[0].x;
    points[2 * count + 1] = Poly->Points[0].y;

    float angle;
    int size = pts.size();

    list<TPoint>::iterator it1, it2, it3, it;

    delete[] points;

    size = pts.size();
    points = new double[size * 2 + 4];
    for (i = 0, it = pts.begin(); it != pts.end(); ++it, ++i) {
        points[2 * i] = it->x;
        points[2 * i + 1] = it->y;
    }
    points[size * 2] = points[size * 2 - 2];
    points[size * 2 + 1] = tableTop.LeftTop.y - tableTop.RowOffsetY(iProfileTop) - tableTop.RowHeight;
    points[size * 2 + 2] = points[0];
    points[size * 2 + 3] = points[size * 2 + 1];

    AcadPolylinePtr plines[1];

    plines[0] = AutoCAD.DrawPolyLine(&points[0], size + 2, 2);

    if (fFillProfile) {
        AcadHatchPtr hatch;
        hatch = AutoCAD.FillArea((IDispatch**)plines, 1, 0, strProfileHatch);
        hatch->PatternScale = iProfileHatchScale;
    }

    delete[] points;
    return plines[0];
}

bool __fastcall TAcadExport::ExportRoadMetric(TExtPolyline *Poly, TMetricsKind kind, bool fEnd) {
    //if (kind==mkBrovka)
    //   Poly->Count
    //   Poly->Points[i].X -- координата по ширине
    //   Poly->Points[i].L -- координата по длине
    //   Poly->Codes[i]&1  Код видимости до i-той точки 1 - видимый, 0 - невидимый
    //   Координаты целые в сантиметрах!
    if (fEnd) {
        if (smallGridMarkHeight != 0 && !fDrawMap) {
            int step = 10000;
            for (int i = (curRoad->LMin / step) * step; i < curRoad->LMax; i += step) {
                AcadLinePtr line = AutoCAD.DrawLine(i, -smallGridMarkHeight / 2, i, smallGridMarkHeight / 2);
                line->color = 8;
                line->set_Lineweight(acLnWt030);
            }
        }
        return true;
    }
    switch (kind) {
    case mkBrovka:
        DrawPolyPoints(Poly);
        break;
    case mkKromka:
        DrawPolyPoints(Poly);
        break;
    case mkDivPart:
        DrawPolyPoints(Poly, false, false);
        break;
    case mkSafeZone:
        DrawPolyPoints(Poly, false, true);
        break;
    default:
        BUILDER_INFO("Неизвестный тип метрики: " << kind);
        DrawPolyPoints(Poly);
    }

    return true;
}


bool __fastcall TAcadExport::ExportAttach(TExtPolyline *Poly, TRoadAttach *a, bool fEnd) {

    if (fEnd) {
        return true;
    }

    // ищем минимальную и максимальную точку по Y у примыкания
    int maxY = abs(Poly->Points[0].y);
    int minY = abs(Poly->Points[0].y);
    int iLast, i;
    TPoint pMax = Poly->Points[0], pMin = Poly->Points[0];
    for (i = 1; i < Poly->Count; ++i) {
        if (abs(Poly->Points[i].y) > maxY ) {
            maxY = abs(Poly->Points[i].y);
            pMax = Poly->Points[i];
        }
        if (abs(Poly->Points[i].y) < minY ) {
            minY = abs(Poly->Points[i].y);
            pMin = Poly->Points[i];
        }
    }

    // вывод комментария
    if (fShowAttachmentComments) {
        vector<AnsiString> strings;
        AnsiString str = a->Comment;
        str = StringReplace(str, "\\n", "\n", TReplaceFlags() << rfReplaceAll);
        for (iLast = 1, i = 1; i < str.Length(); ++i) {
            if (str[i] == '\n') {
                strings.push_back(str.SubString(iLast, i - iLast));
                iLast = i + 1;
            }
        }
        strings.push_back(str.SubString(iLast, i - iLast + 1));

        for (i = 1; i <= strings.size(); ++i) {
            if (pMax.y > 0) {
                if (!strings[i - 1].IsEmpty()) {
                    AutoCAD.DrawText(strings[i - 1],
                                     UnderTextHeight,
                                     acAlignmentTopCenter,
                                     a->L,
                                     -ScaleY * (pMax.y) - i * UnderTextYOffset - (i - 1)*UnderTextHeight);
                }
            } else {
                if (!strings[i - 1].IsEmpty()) {
                    AutoCAD.DrawText(strings[i - 1], UnderTextHeight, acAlignmentBottomCenter ,
                                     a->L, -ScaleY * (pMax.y) + (strings.size() - i)*UnderTextYOffset + (strings.size() - i + 1)*UnderTextHeight);
                }
            }
        }
    }


    // вывод названия примыкания

    if (a->Name != "") {
        AutoCAD.DrawText(a->Name,
                         UnderTextHeight,
                         acAlignmentMiddleLeft,
                         pMin.x + (pMax.x - pMin.x) / 2,
                         -ScaleY * (pMin.y + (pMax.y - pMin.y) / 2),
                         Helpers::GetAngle2(pMin, pMax, ScaleY)
                        );
    }

    DrawPolyPoints(Poly);

    return true;
}

bool __fastcall TAcadExport::ExportSigns(TExtPolyline* Poly,  TRoadSign** signs, int count, bool fEnd) {
    if (fEnd) {
        return true;
    }

    if (~iStart) {
        if (Poly->Points[0].x < iStart) return true;
    }
    if (~iEnd) {
        if (Poly->Points[0].x > iEnd) return true;
    }
    if (count == 0) {
        return true;
    }

    double scale = ScaleYBlock * 50;
    int signSpotOffset = 19;

    /// создавать новый объект signspot сильно нарпяжно, так что создадим его один раз
    /// а потом будем все время копировать
    if (!fAlreadyDrawSignSpot) {
        SignsPositions.clear(); // так как процедура совершается, как правило в
        // начале, то почистим список позиций знаков
        SignSpot1 = AutoCAD.DrawBlock("signspot", 0, 0, 0, scale);
        if (!AutoCAD.SetPropertyPoint(SignSpot1, "pHand", AutoCADPoint(0, 0)))
            return false;

        SignSpot1_m = AutoCAD.DrawBlock("signspot_m", 0, 0, 0, scale);
        if (!AutoCAD.SetPropertyPoint(SignSpot1_m, "pHand", AutoCADPoint(0, 0)))
            return false;

        SignSpot2 = AutoCAD.DrawBlock("signspot2", 0, 0, 0, scale);
        if (!AutoCAD.SetPropertyPoint(SignSpot2, "pHand", AutoCADPoint(0, 0)))
            return false;

        fAlreadyDrawSignSpot = true;
    }

    // парные знаки
    AnsiString signsPair[][2] = {
        {"5.19.1", "5.19.2"},
        {"5.16", "5.16"},
        {"5.17", "5.17"},
        {"5.21", "5.22"}
    };
    int signsPairCount = sizeof(signsPair) / sizeof(signsPair[0]);
    vector<TRoadSign*> direct;
    vector<TRoadSign*> undirect;
    vector<TRoadSign*> onRoad;
    vector<TRoadSign*> onAttachment;

    if (count >= 2) {
        // разбиваем на группы: знаки на примыканиях и знаки на главной дороге
        for (int i = 0; i < count; ++i) {
            TRoadSign *s = signs[i];
            if (s->OnAttach && s->OnAttach != saRoad) {
                onAttachment.push_back(s);
            } else {
                onRoad.push_back(s);
            }
        }

        if (onAttachment.size() == 0 || onRoad.size() == 0) {
            // все знаки либо на примыканиях, либо на главной дороге
            // можно ничего не делать
            bool fAllOnRoad = onRoad.size() > 0;
            // разбиваем на группы по направлениям
            if (onRoad.size() > 0) {
                for (int i = 0; i < onRoad.size(); ++i) {
                    TRoadSign* s = onRoad[i];
                    switch (s->Direction) {
                    case roUnDirect:
                        undirect.push_back(s);
                        break;
                    default:
                        direct.push_back(s);
                    }
                }
            } else {
                for (int i = 0; i < onAttachment.size(); ++i) {
                    TRoadSign* s = onAttachment[i];
                    switch (s->OnAttach) {
                    case saOut:
                        switch (s->Direction) {
                        case roUnDirect:
                            direct.push_back(s);
                            break;
                        default:
                            undirect.push_back(s);
                        }
                        break;
                    default:
                        switch (s->Direction) {
                        case roUnDirect:
                            undirect.push_back(s);
                            break;
                        default:
                            direct.push_back(s);
                        }
                    }
                }
            }
            // ищем парные знаки и переносим их из обратного в прямое направление
            bool wasPair = false;
            for (int i = 0; i < direct.size(); ++i) {
                TRoadSign* s = direct[i];
                for (int j = 0; j < signsPairCount; ++j) {
                    if (s->OldTitle == signsPair[j][0]) {
                        for (int k = 0; k < undirect.size(); ++k) {
                            TRoadSign* s2 = undirect[k];
                            if (s2->OldTitle == signsPair[j][1]) {
                                direct.push_back(s2);
                                undirect.erase(undirect.begin() + k);
                                --k;
                                wasPair = true;
                            }
                        }
                    } else if (s->OldTitle == signsPair[j][1]) {
                        for (int k = 0; k < undirect.size(); ++k) {
                            TRoadSign* s2 = undirect[k];
                            if (s2->OldTitle == signsPair[j][0]) {
                                direct.push_back(s2);
                                undirect.erase(undirect.begin() + k);
                                --k;
                                wasPair = true;
                            }
                        }
                    }
                }
            }
            if (wasPair && direct.size() == 2 && undirect.size() == 1) {
                // комбинация парные знаки и один в противоположном направленнии
                // подклеиваем пару к противоположному направлению
                undirect.push_back(direct[0]);
                undirect.push_back(direct[1]);
                direct.clear();
                sort(undirect.begin(), undirect.end(), Helpers::compareSigns);
                signs = undirect.begin();
            } else if (direct.size() == 0 || undirect.size() == 0) {
                // если все знаки в одном нарпавлении
                if (direct.size() > 0) {
                    sort(direct.begin(), direct.end(), Helpers::compareSigns);
                    signs = direct.begin();
                }
                if (undirect.size() > 0) {
                    sort(undirect.begin(), undirect.end(), Helpers::compareSigns);
                    signs = undirect.begin();
                }
            } else {
                // остальные случаи сводим к предыдущим двум
                ExportSigns(Poly, direct.begin(), direct.size(), fEnd);
                ExportSigns(Poly, undirect.begin(), undirect.size(), fEnd);
                return true;
            }
        } else {
            // выводим каждую группу отдельно
            ExportSigns(Poly, onAttachment.begin(), onAttachment.size(), fEnd);
            ExportSigns(Poly, onRoad.begin(), onRoad.size(), fEnd);
            return true;
        }
    }

    double yoffset = 20;
    bool ffind, fOnAttachment = false;
    int i;
    AnsiString strings[4];
    AcadBlockPtr block;
    AcadBlockReferencePtr signspot = SignSpot1;
    double rotation = 0, rotationHandle = 0;

    switch (signs[0]->OnAttach) {
    case saIn:
    case saOut:
        signSpotOffset = 10;
        break;
    }

    if (true) {
        // настраиваем корректный поворот знаков
        switch (signs[0]->Direction) {
        case roDirect:
            switch (signs[0]->Placement) {
            case spRight:
                switch (signs[0]->OnAttach) {
                case saIn:
                    rotationHandle = -M_PI / 2;
                    rotation = M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                case saOut:
                    rotationHandle = -M_PI / 2;
                    rotation = -M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                default:
                    rotationHandle = -M_PI / 2;
                    signspot = SignSpot1;
                }
                break;
            case spBetween:
            case spUp:
            case spLeft:
                switch (signs[0]->OnAttach) {
                case saIn:
                    rotationHandle = M_PI / 2;
                    rotation = M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                case saOut:
                    rotationHandle = M_PI / 2;
                    rotation = -M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                default:
                    rotationHandle = M_PI / 2;
                    rotation = 0;
                    signspot = SignSpot1_m;
                }
                break;
            default:
                BUILDER_ERROR("Не могу определить угол поворота знака " << signs[0]->OldTitle.c_str() << " на позиции " << Poly->Points[0].x);
            }
            break;
        case roUnDirect:
            switch (signs[0]->Placement) {
            case spRight:
                switch (signs[0]->OnAttach) {
                case saIn:
                    rotationHandle = M_PI / 2;
                    rotation = M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                case saOut:
                    rotationHandle = M_PI / 2;
                    rotation = -M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                default:
                    rotationHandle = M_PI / 2;
                    signspot = SignSpot1;
                }
                break;
            case spBetween:
            case spUp:
            case spLeft:
                switch (signs[0]->OnAttach) {
                case saIn:
                    rotationHandle = -M_PI / 2;
                    rotation = M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                case saOut:
                    rotationHandle = -M_PI / 2;
                    rotation = -M_PI / 2;
                    signspot = SignSpot2;
                    fOnAttachment = true;
                    break;
                default:
                    rotationHandle = -M_PI / 2;
                    rotation = 0;
                    signspot = SignSpot1_m;
                }
                break;
            default:
                BUILDER_ERROR("Не могу определить угол поворота знака " << signs[0]->OldTitle.c_str() << " на позиции " << Poly->Points[0].x);
            }
            break;
        }



        switch (signs[0]->Placement) {
        case spBetween:
        case spUp:
            switch (signs[0]->OnAttach) {
            case saIn:
            case saOut:
                break;
            default:
                rotationHandle *= -1;
                if (signs[0]->Placement == spUp) {
                    signspot = SignSpot2;
                    rotationHandle -= M_PI / 2;
                    rotation += M_PI / 2;
                    signSpotOffset = 9;
                } else {
                    signspot = SignSpot1;
                }
                break;
            }
        }
    }

    if (fDrawMap) {
        if (Poly->Count == 2) {
            double angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[1], ScaleY);

            rotationHandle += angle;
            //rotation += angle;

            switch (signs[0]->Direction) {
            case roUnDirect:
                //rotation += M_PI;
                switch (signs[0]->Placement) {
                case spRight:
                    rotationHandle += M_PI;
                    break;
                }
                break;
            case roDirect:
                switch (signs[0]->Placement) {
                case spLeft:
                    rotationHandle -= M_PI;
                    break;
                }
                break;
            }

            switch (signs[0]->OnAttach) {
            case saIn:
                //rotation -= M_PI_2;
                rotationHandle -= M_PI_2;
                break;
            case saOut:
                switch (signs[0]->Direction) {
                case roUnDirect:
                    //rotation += M_PI_2;
                    //rotationHandle += M_PI_2;
                    break;
                }

                break;
            }

            switch (signs[0]->Placement) {
            case spUp:
                //rotationHandle -= M_PI_2;
                break;
            }
        }
    }

    AnsiString sEmpty = "";

    try {
        if (count == 1) {
            try {
                DrawSign(
                    signs[0]->OldTitle + (signs[0]->ViewKind == 0 ? sEmpty : AnsiString("." + IntToStr(signs[0]->ViewKind))),
                    signs[0]->Label,
                    AutoCADPoint(Poly->Points[0].x, -ScaleY * Poly->Points[0].y),
                    signs[0]->L,
                    signSpotOffset,
                    0,
                    rotation,
                    rotationHandle,
                    scale,
                    fOnAttachment,
                    signspot,
                    signs[0]->Placement == spUp);
            } catch (...) {
                if (!strSignsAbsent.Pos(signs[0]->OldTitle))strSignsAbsent += "\n" + signs[0]->OldTitle;
            }
        } else {
            vector<WideString> blockNames;
            vector<WideString> labels;
            for (int i = 0; i < count; ++i) {
                blockNames.push_back(signs[i]->OldTitle + (signs[i]->ViewKind == 0 ? sEmpty : AnsiString("." + IntToStr(signs[i]->ViewKind))));
                labels.push_back(signs[i]->Label);
            }
            block = AutoCAD.MakeCombineBlock(blockNames, labels);
            if (block.IsBound()) {
                DrawSign(block->Name,
                         "",
                         AutoCADPoint(Poly->Points[0].x, -ScaleY * Poly->Points[0].y),
                         signs[0]->L,
                         signSpotOffset,
                         0,
                         rotation,
                         rotationHandle,
                         scale,
                         fOnAttachment,
                         signspot,
                         signs[0]->Placement == spUp);
            }
        }
    } catch (...) {
        BUILDER_ERROR("Ошибка вывода знака: " << signs[0]->OldTitle.c_str() << " на позиции " << Poly->Points[0].x );
        return false;
    }
    return true;
}

// возвращает кол-во знаков лежащих
// около позиции pos, в пределах radius
int TAcadExport::findSignSuperposition(TPoint pos, int radius)
{
    int counter = 0;
    for (vector<TPoint>::iterator it = SignsPositions.begin(); it != SignsPositions.end(); ++it) {
        TPoint temp = *it - pos;
        if (abs(temp.x) < radius && abs(temp.y) < radius )
            counter++;

    }
    return counter;
}

/// name - нзвание знака
/// label - надпись на знаке
/// pos - положение знака
/// xoffset - cдвиг знака относительно pos.x
/// yoffset - cдвиг знака относительно pos.y
/// rotation - поворот знака
/// rotationHandle - поворот сноски, знак будет крепиться к сноске
/// scale - масштабирование
/// fOnAttachment - знак находится на примыкании (то есть на въезде или выезде),
///                 поставить True если на примыкании
void TAcadExport::DrawSign(
    AnsiString Name,
    AnsiString label,
    AutoCADPoint pos,
    int LPos,
    int xoffset,
    int yoffset,
    double rotation,
    double rotationHandle,
    double scale,
    bool fOnAttachment,
    AcadBlockReferencePtr &signspot,
    bool fUnderRoad
)
{
    static AcadBlockReferencePtr block;
    static AutoCADPoint newPos;
    static int _pos;
    static int txOffset, tyOffset;
    xoffset *= scale;
    yoffset *= scale;

    if (fDrawMap) {
        _pos = LPos / 100;
    } else {
        if (Name == "6.13") {
            int sPos;
            sPos = label.Pos("-");
            sPos = sPos == 0 ? label.Length() + 1 : sPos;
            if (fAuto6_13) {
                if (TryStrToInt(label.SubString(1, sPos - 1), sPos)) {
                    pos.x = sPos * 100000;
                } else {
                    pos.x = RoundTo((float)pos.x / 100000, 0) * 100000;
                }
                _pos = 0;
            } else {
                _pos = (int)LPos % 100000 / 100;
            }
            if (fLeftValueOnly6_13) {
                label = label.SubString(1, sPos - 1);
            }
        } else {
            _pos = (int)LPos % 100000 / 100;
        }
    }

    txOffset = xoffset;
    tyOffset = yoffset;

    IAcadSelectionSet *set = AutoCAD.ActiveDocument->ActiveSelectionSet;
    set->Clear();

    // копируем сноску
    block = signspot->Copy();
    AutoCAD.SetAttribute(block, "LABEL", AnsiString(_pos));
    // поворачиваем сноску
    block->set_Rotation(rotationHandle);

    // чтобы за край не уходили
    float posOffset = 0.25 * ScaleY;
    if (!fUnderRoad && !fDrawMap) {
        int framePos = (LPos / 100) % (iStep / 100);
        if (framePos <= 30 * posOffset) {
            tyOffset += (rotationHandle == -M_PI / 2) ? 3000 * posOffset : -3000 * posOffset;
        } else if ( (iStep / 100) - framePos <= 30 * posOffset ) {
            tyOffset += (rotationHandle == -M_PI / 2) ? -3000 * posOffset : 3000 * posOffset;
        }
    }

    //if (fUnderRoad || fOnAttachment) {
    //    tyOffset += 500 * posOffset;
    //}
    // чтобы не было наложений, наложенные знаки сдивгаем вправо
    int countOfSignsNearCurrent;
    countOfSignsNearCurrent = findSignSuperposition(TPoint(pos.x, pos.y) , 1000 * posOffset);
    if ( countOfSignsNearCurrent > 0 ) {
        if (fOnAttachment) {
            txOffset -= 1000 * countOfSignsNearCurrent * posOffset;
        } else {
            tyOffset += 1000 * countOfSignsNearCurrent * posOffset;
        }
    }

    // запомним положение знака
    SignsPositions.push_back(TPoint(pos.x, pos.y) );

    // поставим сноску и сдвинем ее хвостик
    //AutoCAD.SetPropertyDouble(block,"Length",1200);
    block->set_InsertionPoint(AutoCAD.cadPoint(int(pos.x), int(pos.y)));
    AutoCAD.SetPropertyPoint(block, "pHand", AutoCADPoint(txOffset, tyOffset));

    // собственно рисуем знак
    //block = AutoCAD.DrawBlock(Name,int(newPos.x),int(newPos.y),rotation,scale);
    block = AutoCAD.DrawBlock(Name, int(txOffset), int(tyOffset), rotation, scale);
    // поворачиваем блок относительно центра
    block->Rotate(AutoCAD.cadPoint(0, 0), rotationHandle);
    block->Move(AutoCAD.cadPoint(0, 0), AutoCAD.cadPoint(int(pos.x), int(pos.y)));
    if (block.IsBound()) {
        SetAttributes(block, Helpers::SignLabelParser(Name, label));
        if (Name.Pos("6.10.1") || Name.Pos("6.10.2") || Name.Pos("6.9.1") || Name.Pos("6.9.2")) {
            block->color = 5; /*синий цвет знакам*/
        }
    }

}

void TAcadExport::SetAttributes(AcadBlockReferencePtr block, AnsiString labels)
{
    int count = 1, last = 0, i;
    int length = labels.Length();

    for (i = 1; i <= length; i++) {
        if (labels[i] == '\\') {
            switch (count) {
            case 1:
                AutoCAD.SetAttribute(block, "LABEL", labels.SubString(last + 1, (i - last - 1)).UpperCase());
                break;
            case 2:
                AutoCAD.SetAttribute(block, "LABEL1", labels.SubString(last + 1, (i - last - 1)).UpperCase());
                break;

            case 3:
                AutoCAD.SetAttribute(block, "LABEL1", labels.SubString(last + 1, (i - last - 1)).UpperCase());
                break;
            }
            count++;
            last = i;
            if (count == 3)
                break;
        }
    }
    switch (count) {
    case 1:
        AutoCAD.SetAttribute(block, "LABEL", labels.SubString(last + 1, (length - last)).UpperCase());
        break;

    case 2:
        AutoCAD.SetAttribute(block, "LABEL1", labels.SubString(last + 1, (length - last)).UpperCase());
        break;

    case 3:
        AutoCAD.SetAttribute(block, "LABEL2", labels.SubString(last + 1, (length - last)).UpperCase());
        break;
    }
}



bool __fastcall TAcadExport::ExportSign(TExtPolyline *Poly, TRoadSign *s, bool fEnd) {
    if (fEnd) {
        return true;
    }
    return true;
}


TPoint __fastcall TAcadExport::GetCenterOnPolyline(
    TExtPolyline *p, int minx, int maxx, float* out_angle, int *width_of_sector, TPoint* pointStart, TPoint* pointEnd)
{
    float length, k;
    int i1 = 0,
        i2 = p->Count - 1;
    TPoint pEnd, pStart, pOffset;
    std::vector<TPoint> Points;
    for (int i = 0; i < p->Count; ++i) {
        int j = i;

        if (p->Points[0].x > p->Points[p->Count - 1].x) {
            j = p->Count - j - 1;
        }
        Points.push_back(p->Points[j]);
    }

    if (Points[i1].x < minx && minx != maxx) {
        i1 = -1;
        for (int i = 1; i < Points.size(); ++i) {
            if (Points[i].x > minx) {
                i1 = i - 1;
                break;
            }
        }
        if (i1 == -1) {
            return TPoint(-1, -1);
        }
    }

    if (Points[i2].x > maxx && minx != maxx) {
        i2 = -1;
        for (int i = Points.size() - 2; i >= 0; --i) {
            if (Points[i].x < maxx) {
                i2 = i + 1;
                break;
            }
        }
        if (i2 == -1) {
            return TPoint(-1, -1);
        }
    }

    pStart = Points[i1];
    pEnd = Points[i2];

    if (pStart.x < minx && minx != maxx) {
        k = 1;
        pOffset.x = Points[i1 + 1].x - Points[i1].x;
        pOffset.y = Points[i1 + 1].y - Points[i1].y;
        k = (float) (minx - pStart.x) / pOffset.x;
        pStart.x += pOffset.x * k + 1;
        pStart.y += pOffset.y * k;
    }

    if (pEnd.x > maxx && minx != maxx) {
        k = 1;
        pOffset.x = Points[i2].x - Points[i2 - 1].x;
        pOffset.y = Points[i2].y - Points[i2 - 1].y;
        k = (float) (pEnd.x - maxx) / pOffset.x;
        pEnd.x -= pOffset.x * k - 1;
        pEnd.y -= pOffset.y * k;
    }

    int centerX = (pEnd.x + pStart.x) / 2;

    for (int i = i1; i < i2; ++i) {
        TPoint p1 = Points[i];
        TPoint p2 = Points[i + 1];
        if (i == i1) p1 = pStart;
        if (i == i2 - 1) p2 = pEnd;
        if (p1.x < centerX && centerX < p2.x) {
            k = 1;
            if (out_angle) {
                *out_angle = Helpers::GetAngle2(p1, p2, ScaleY);
            }
            if (width_of_sector) {
                *width_of_sector = pEnd.x - pStart.x;
            }
            if (pointStart) {
                *pointStart = pStart;
            }
            if (pointEnd) {
                *pointEnd = pEnd;
            }
            k = (float) (centerX - p1.x) / (p2.x - p1.x);
            return TPoint(p1.x + (p2.x - p1.x) * k, p1.y + (p2.y - p1.y) * k);
        }
    }
    return TPoint(-1, -1);
}

void __fastcall TAcadExport::DrawTextUnderLine(TPoint p1, TPoint p2, AnsiString text)
{
    TPoint centerPoint;
    float kUnderTextHeight = 1;
    float angle = Helpers::GetAngle2(p1, p2, ScaleY);
    centerPoint.x = (p1.x + p2.x) / 2;
    centerPoint.y = (p1.y + p2.y) / 2;
    AutoCAD.DrawText(text, kUnderTextHeight * UnderTextHeight, acAlignmentBottomCenter,  centerPoint.x, -ScaleY * centerPoint.y, angle);
}

void __fastcall TAcadExport::DrawTextOverPoly(TExtPolyline *Poly, AnsiString text,
        AnsiString(__closure *textControlFunction)(AnsiString text, TPoint pStart, TPoint pEnd, TPoint centerPoint, float angle, void* data), void* data)
{
    float angle;
    int width_of_sector;
    float kUnderTextHeight = 1;

    int ilastStepPoint = 0;
    
    TPoint centerPoint, pStart, pEnd;

    if (!fDrawMap) {
        int xLeft = Poly->Points[0].x;
        int xRight = Poly->Points[Poly->Count - 1].x;
        if (xLeft > xRight) {
            Helpers::swap(xLeft, xRight);
        }

        int iMin = xLeft / iStep;
        if (iMin < (float) xLeft / iStep) {
            iMin++;
        }

        int iMax = xRight / iStep;
        for (int k = iMin; k <= iMax + 1; ++k) {
            int leftPos = (k - 1) * iStep;
            leftPos = max(leftPos, xLeft);

            int rightPos = k * iStep;
            rightPos = min(rightPos, xRight);

            centerPoint = GetCenterOnPolyline(
                Poly, 
                leftPos, 
                rightPos, 
                &angle, &width_of_sector, &pStart, &pEnd
            );
            if (centerPoint.x != -1) {
                AnsiString str = textControlFunction ? 
                                 textControlFunction(text, pStart, pEnd, centerPoint, angle, data) : 
                                 text;
                if (!str.IsEmpty()) {
                    AutoCAD.DrawText(
                        str,
                        kUnderTextHeight * UnderTextHeight,
                        acAlignmentBottomCenter,
                        centerPoint.x,
                        -ScaleY * centerPoint.y,
                        angle
                    );
                }
            }
        }
    } else {
        centerPoint = GetCenterOnPolyline(Poly, -1, -1, &angle, &width_of_sector, &pStart, &pEnd);
        if (centerPoint.x != -1) {
            AnsiString str = text;
            if (textControlFunction) {
                str = textControlFunction(text, pStart, pEnd, centerPoint, angle, data);
            }
            if (!str.IsEmpty()) {
                AutoCAD.DrawText(
                    str,
                    kUnderTextHeight * UnderTextHeight,
                    acAlignmentBottomCenter,
                    centerPoint.x,
                    -ScaleY * centerPoint.y,
                    angle
                );
            }
        }
    }

   
}

AnsiString TAcadExport::RoadMarkTextDraw(AnsiString text, TPoint pStart, TPoint pEnd, TPoint centerPoint, float angle, void* data)
{
    AnsiString str = text;
    float kUnderTextHeight = 1, kEdgeLines = 0.5;
    TRoadMark* m = (TRoadMark*)data;

    int start, end;
    if (fDrawMap && m) {
        start = m->LMin / 100;
        end = m->LMax / 100;
    } else {
        start = (pStart.x / 100) % 1000;
        end = (pEnd.x / 100) % 1000;
    }
    end = end == 0 ? 1000 : end;
    int length = end - start;

    if (length >= 10) {
        str.sprintf("%s(%d)", text, length);
        if (length < 20) {
            kUnderTextHeight *= (float)length / 20;
        }
    } else {
        kUnderTextHeight = 0.6;
    }
    float kPositionMarksHeight = kUnderTextHeight * 0.75;
    float scale = ScaleYBlock / 4;

    AutoCAD.DrawText(str,
                     kUnderTextHeight * UnderTextHeight * scale,
                     centerPoint.y > 0 ? acAlignmentBottomCenter : acAlignmentTopCenter,
                     centerPoint.x,
                     -ScaleY * centerPoint.y + (centerPoint.y > 0 ? scale : -scale) * UnderTextYOffset * kEdgeLines,
                     angle);

    if (length >= 15 && start != 0 && start != 1000 && start != iStep / 100) {
        AutoCAD.DrawText(IntToStr(start),
                         kPositionMarksHeight * UnderTextHeight * ScaleYBlock / 3.5,
                         centerPoint.y > 0 ? acAlignmentTopLeft : acAlignmentTopRight,
                         pStart.x + 100 * scale,
                         -ScaleY * pStart.y + (centerPoint.y > 0 ? scale : -scale) * UnderTextYOffset * kEdgeLines,
                         M_PI_2 + angle);
    }
    /*if (length >= 15 && end != 0 && end != 1000 && start != iStep / 100) {
        AutoCAD.DrawText(IntToStr(end),
                         kPositionMarksHeight * UnderTextHeight,
                         acAlignmentMiddleLeft,
                         pEnd.x,
                         -ScaleY*pEnd.y + UnderTextYOffset * kEdgeLines,
                         angle + M_PI_2);
    }*/
    return "";
}

// Миша, взять код разметки можно так
// TPlanLabel *l=m->GetText(0);
// String s=l->Caption;
// после окончания обработки надо удалять l
// delete l;
// line это номер линии (0 - осевая 1,2 - номера справа -1,-2 - слева
// 100 - разметка не на линиях
AcadPolylinePtr TAcadExport::DrawRoadMark(TRoadMark *m, TExtPolyline *Poly, AnsiString name,
        int iRow, int line, AutoCADTable *table, bool dontDrawPolyLine)
{
    AcadPolylinePtr pl;
    float Min, Max, angle;
    int iMaxY, MaxY;
    int count = Poly->Count;
    float kEdgeLines = 0.5;

    if (fDrawMap) table = NULL; // в режиме карты в таблице ничего не рисуем

    if (count > 1) { // are there any points to draw?
        if (!dontDrawPolyLine) {
            pl = DrawPolyPoints(Poly, false);
        }

        if (Poly->Points[0].x > Poly->Points[count - 1].x) {
            Min = Poly->Points[count - 1].x;
            Max = Poly->Points[0].x;
        } else {
            Max = Poly->Points[count - 1].x;
            Min = Poly->Points[0].x;
        }
        if (abs(Poly->Points[0].y) > abs(Poly->Points[count - 1].y)) {
            iMaxY = 0;
        } else {
            iMaxY = count - 1;
        }

        if (iRow != -1 || fDrawMap) { // if we draw road mark on common road
            int yOffset;
            // fill rows in tables
            if (table && line != 0) { // if we draw lines over central
                table->DrawRepeatTextIntervalRoadMark(iRow, name, Min, Max, Helpers::StringConvert, iStep, 0.25);
            } else { // if we draw central line
                tableTop.DrawRepeatTextIntervalRoadMark(iTop0, name, Min, Max, Helpers::StringConvert, iStep, 0.25);
                tableBottom.DrawRepeatTextIntervalRoadMark(iBottom0, name, Min, Max, Helpers::StringConvert, iStep, 0.25);
            }
            if ( line >= 0 ) {
                yOffset = -ScaleY * (Poly->Points[(Poly->Count) / 2 - (Poly->Count % 2 ? 0 : 1)].y) + UnderTextYOffset;
            } else {
                yOffset = -ScaleY * (Poly->Points[(Poly->Count) / 2 - (Poly->Count % 2 ? 0 : 1)].y) - UnderTextYOffset;
            }

            AnsiString label_under_mark = name;

            float kUnderTextHeight = ScaleY / 3.5;
            if (Max - Min < 750) {
                kUnderTextHeight = 0.6 * ScaleY / 3.5;
            }
            DrawTextOverPoly(Poly, label_under_mark, RoadMarkTextDraw, m);

        } else { // if we draw road mark on attachments
            AcadTextPtr text;
            // we should recalculate angle of text, to draw it properly
            if (iMaxY > 0) {
                angle = Helpers::GetAngle2(Poly->Points[iMaxY], Poly->Points[iMaxY - 1], ScaleY);
                Max = Poly->Points[iMaxY].x + (Poly->Points[iMaxY - 1].x - Poly->Points[iMaxY].x) / 2;
                MaxY = Poly->Points[iMaxY].y + (Poly->Points[iMaxY - 1].y - Poly->Points[iMaxY].y) / 2;
            } else {
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[1], ScaleY);
                Max = Poly->Points[0].x + (Poly->Points[1].x - Poly->Points[0].x) / 2;
                MaxY = Poly->Points[0].y + (Poly->Points[1].y - Poly->Points[0].y) / 2;
            }

            if (Poly->Points[iMaxY].y > 0) {
                Max -= 0.5 * UnderTextYOffset;
            } else {
                Max += 0.5 * UnderTextYOffset;
            }
            DrawTextOverPoly(Poly, name, RoadMarkTextDraw, m);
        }
        if (Max - Min >= 1000) {
            AcadLinePtr line = AutoCAD.DrawLine(Poly->Points[0].x, -ScaleY * (Poly->Points[0].y) - UnderTextYOffset * kEdgeLines,
                                                Poly->Points[0].x, -ScaleY * (Poly->Points[0].y) + UnderTextYOffset * kEdgeLines);
            line->Rotate(AutoCAD.cadPoint(Poly->Points[0].x, -ScaleY * Poly->Points[0].y, 0),
                         Helpers::GetAngle2(Poly->Points[0], Poly->Points[1], ScaleY));

            line = AutoCAD.DrawLine(Poly->Points[Poly->Count - 1].x, -ScaleY * (Poly->Points[Poly->Count - 1].y) - UnderTextYOffset * kEdgeLines,
                                    Poly->Points[Poly->Count - 1].x, -ScaleY * (Poly->Points[Poly->Count - 1].y) + UnderTextYOffset * kEdgeLines);
            line->Rotate(AutoCAD.cadPoint(Poly->Points[Poly->Count - 1].x, -ScaleY * Poly->Points[Poly->Count - 1].y, 0),
                         Helpers::GetAngle2(Poly->Points[Poly->Count - 2], Poly->Points[Poly->Count - 1], ScaleY));
        }
    }

    return pl;
}



AcadBlockReferencePtr TAcadExport::DrawBlockOnLine(String blockName, TPoint p1, TPoint p2, String lengthPropName, double scale)
{
    float yoffset = -ScaleY * (p2.y - p1.y);
    float xoffset = p2.x - p1.x;
    float angle = xoffset != 0 ? atan(yoffset / xoffset) : yoffset < 0 ? -M_PI_2 : M_PI_2;
    if (xoffset < 0)angle += M_PI;
    float length = sqrt(yoffset * yoffset + xoffset * xoffset);
    AcadBlockReferencePtr block = AutoCAD.DrawBlock(blockName, p1.x, -ScaleY * p1.y, angle, scale);
    if (block.IsBound()) {
        vector<AnsiString> props;
        Utils::split(lengthPropName, " ,", props);
        for (int i = 0; i < props.size(); ++i) {
            try {
                AutoCAD.SetPropertyDouble(block, props[i], length);
            } catch (...) {
                BUILDER_ERROR("Не смог изменить свойство "
                              << props[i].c_str()
                              << " блока "
                              << blockName.c_str()
                              << " на промежутке "
                              << "[" << p1.x << "; " << p1.y << "]"
                              << "[" << p2.x << "; " << p2.y << "]");
            }
        }
    }
    return block;
}

bool __fastcall TAcadExport::ExportRoadMark(TExtPolyline *Poly, TRoadMark *m, int line, String code, bool fEnd) {
    bool ffind;
    float x, y, height, rot, length, yoffset, xoffset, angle, Min, Max;
    int iRow, i;
    AutoCADTable *table, *table2;
    AcadPolylinePtr pl[1];
    TPoint p;
    float R1_2_1BorderHeight2 = 434 / 2;
    AnsiString str;

    int count;

    AcadHatchPtr hatch;
    AcadTextPtr text;
    AcadPolylinePtr pl1;
    AcadBlockReferencePtr block;
    AcadAcCmColorPtr color;
    int lastUnderTextYOffset;

    try {
        if (fEnd) {
            if (iTop0 != -1)tableTop.FillLastGaps(iStep, iTop0);
            if (iBottom0 != -1)tableBottom.FillLastGaps(iStep, iBottom0);
            for (i = 0; i < iTopAxeCount; i++) {
                tableTop.FillLastGaps(iStep, iTopAxe - i);
            }
            for (i = 0; i < iBottomAxeCount; i++) {
                tableBottom.FillLastGaps(iStep, iBottomAxe + i);
            }
            return true;
        }


        table2 = 0;
        iRow = -1;

        if (line >= -10 && line < 0) {
            if (iTopAxeCount >= abs(line)) {
                table = &tableTop;
                iRow = iTopAxe + line + 1;
            }
        } else if (line > 0 && line <= 10) {
            if (iBottomAxeCount >= abs(line)) {
                table = &tableBottom;
                iRow = iBottomAxe + line - 1;
            }
        } else if (line == 0) {
            table = 0; /*вывод возможен в две таблицы сразу*/
            iRow = 0;
        }

        ffind = false;
        count = Poly->Count;

        if (count > 1) {

            if (Poly->Points[0].x > Poly->Points[count - 1].x) {
                Min = Poly->Points[count - 1].x;
                Max = Poly->Points[0].x;
            } else {
                Max = Poly->Points[count - 1].x;
                Min = Poly->Points[0].x;
            }

            if (~iStart) {
                if (Max < iStart) return true;
            }
            if (~iEnd) {
                if (Min > iEnd) return true;
            }

            switch (m->Kind) {
            case ma1: /*сплошная*/
                DrawRoadMark(m, Poly, "1.1", iRow, line, table);
                break;
            case ma1_park: /*сплошная на парковке*/
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.1_park", Poly->Points[i + 1], Poly->Points[i], "Length", ScaleYBlock / 4);
                }
                break;

            case ma2_1:/*Край проезжей части (сплошная) */
                DrawRoadMark(m, Poly, "1.2", iRow, line, table);
                break;

            case ma2_2:/*Краевая линия (прерывистая)  */
                pl1 = DrawRoadMark(m, Poly, "1.2", iRow, line, table);
                try {
                    if (pl1) pl1->set_Linetype(WideString("linedash_1"));
                } catch (...) {}
                break;

            case ma3: /*двойная сплошная*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY, &length);
                DrawRoadMark(m, Poly, "1.3", iRow, line, table, true);
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.3", Poly->Points[i], Poly->Points[i + 1], "Length");
                }
                break;

            case ma4:/*Обозначение мест, где запрещена остановка*/
                /*pl1 = DrawPolyPoints(Poly);

                color = pl1->TrueColor;
                color->SetRGB(255,180,0);
                pl1->TrueColor = color;

                if(table&&line){
                    table->DrawRepeatTextIntervalRoadMark(iRow,"1.4",Min,Max,StringConvert,iStep,0.25);
                }else{
                    tableTop.DrawRepeatTextIntervalRoadMark(iTop0,"1.4",Min,Max,StringConvert,iStep,0.25);
                    tableBottom.DrawRepeatTextIntervalRoadMark(iBottom0,"1.4",Min,Max,StringConvert,iStep,0.25);
                } */

                pl1 = DrawRoadMark(m, Poly, "1.4", iRow, line, table);
                if (pl1.IsBound()) {
                    color = pl1->TrueColor;
                    pl1->set_Lineweight(acLnWt040);
                    color->SetRGB(255, 180, 0);
                    pl1->TrueColor = color;
                }

                //DrawTextOverPoly(Poly, "1.4", RoadMarkTextDraw);
                break;

            case ma5: /*Прерывистая линия*/
                pl1 = DrawRoadMark(m, Poly, "1.5", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Linetype(WideString("linedash_1"));
                    pl1->set_LinetypeScale(0.5);
                }
                break;

            case ma6: /*Приближение к сплошной линии*/
                pl1 = DrawRoadMark(m, Poly, "1.6", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Linetype(WideString("linedash_2"));
                    pl1->set_LinetypeScale(0.5);
                }
                break;

            case ma7:  /*Обозначение полос движения на перекрестке*/
                pl1 = DrawRoadMark(m, Poly, "1.7", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Linetype(WideString("linedash_3"));
                    pl1->set_LinetypeScale(0.33);
                }
                break;

            case ma8: /*Обозначение границы между полосой разгона и основной полосой*/
                pl1 = DrawRoadMark(m, Poly, "1.8", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Linetype(WideString("linedash_1"));
                    pl1->set_LinetypeScale(0.2);
                }
                break;

            case ma9: /*Обозначение границ реверсивных полос движения*/
                BUILDER_ERROR("Разметка 1.9 не реализована");
                break;

            case ma10:  /*Обозначение мест, где запрещена стоянка*/
                pl1 = DrawRoadMark(m, Poly, "1.10", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Linetype(WideString("linedash_1"));
                    pl1->set_LinetypeScale(0.33);
                    color = pl1->TrueColor;
                    pl1->set_Lineweight(acLnWt040);
                    color->SetRGB(255, 180, 0);
                    pl1->TrueColor = color;
                }
                break;

            case ma11l:  /*Движение с одной стороны (прерывистая слева)*/
            case ma11r:  /*Движение с одной стороны (прерывистая справа)*/
                for (int i = 0; i < count - 1; i++) {
                    block = DrawBlockOnLine("r_1.11", Poly->Points[i], Poly->Points[i + 1], "Length");
                    int px =  Poly->Points[i + 1].x - Poly->Points[i].x;
                    int py =  Poly->Points[i + 1].y - Poly->Points[i].y;
                    length = sqrt(px * px + py * py * ScaleY * ScaleY);
                    if (block.IsBound() ) {
                        float lengthScale = 0.1;
                        AutoCAD.SetPropertyDouble(block, "Length", length / lengthScale);
                        block->set_XScaleFactor(lengthScale);
                        if ((m->Kind == ma11r && m->Direction == roDirect) || (m->Kind == ma11l && m->Direction == roUnDirect)) {
                            AutoCAD.SetPropertyList(block, "Flip", 1);
                        }
                    }
                }
                DrawTextOverPoly(Poly, "1.11", RoadMarkTextDraw);
                break;

            case ma12:  /*Стоп линия*/
                /*for(int i=0;i<count-1;i++){
                    DrawBlockOnLine("r_1.12", Poly->Points[i], Poly->Points[i+1], "Length");
                } */
                pl1 = DrawRoadMark(m, Poly, "1.12", iRow, line, table);
                if (pl1.IsBound()) {
                    pl1->set_Lineweight(acLnWt040);
                }
                break;

            case ma13: /*Обозначение места, где водитель обязан уступить дорогу*/
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.13", Poly->Points[i], Poly->Points[i + 1], "Length");
                }
                break;

            case ma14_1:
            case ma14_2:/*пешеход*/
            case ma14_3:
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.14.1", Poly->Points[i], Poly->Points[i + 1], "Width", ScaleYBlock / 4);
                }
                break;
            case ma14_1e:
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.14.1_e", Poly->Points[i], Poly->Points[i + 1], "Width", ScaleYBlock / 4);
                }
                break;
            case ma14_2e:
                for (int i = 0; i < count - 1; i++) {
                    DrawBlockOnLine("r_1.14.2_e", Poly->Points[i], Poly->Points[i + 1], "Width", ScaleYBlock / 4);
                }
                break;

            case ma15: /*Обозначение переезда для велосипедистов*/
                BUILDER_ERROR("Разметка 1.15 не реализована");
                //tableBottom.DrawRepeatTextInterval(0,"1.15",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma16_1: /*Обозначение островков, разделяющих потоки  противоположенных направлений*/
            case ma16_2: /*Обозначение островков, разделяющих потоки  одного направления*/
            case ma16_3: /*Обозначение островков в местах слияния транспортных потоков*/

                switch (m->Kind) {
                case  ma16_1: str = "1.16.1"; break;
                case  ma16_2: str = "1.16.2"; break;
                case  ma16_3: str = "1.16.3"; break;
                }
                p.y = 0;
                p.x = 0;
                for (i = 0; i < Poly->Count; i++) {
                    p.x += Poly->Points[i].x;
                    p.y += Poly->Points[i].y;
                }

                p.y *= -ScaleY;
                p.x /= Poly->Count;
                p.y /= Poly->Count;

                //text = AutoCAD.DrawText(str,UnderTextHeight,acAlignmentMiddleCenter, p.x,p.y);
                pl[0] = DrawPolyPoints(Poly, false, true);
                hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, L"ANSI31");
                hatch->PatternScale = 50;
                pl[0]->Delete();

                block = AutoCAD.DrawBlock("r_label", p.x, p.y, 0, ScaleYBlock / 4);
                if (block.IsBound()) {
                    AutoCAD.SetAttribute(block, "Label", str);
                }

                //tableBottom.DrawRepeatTextInterval(0,"1.16",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma17: /*Обозначение остановок маршрутных транспортных средств*/
            {
                float scale = ScaleYBlock / 4;
                block = DrawBlockOnLine("r_1.17", Poly->Points[0], Poly->Points[count - 1], "Length Length2", scale);

                // чтобы выводить разметку так чтобы правая ножка не отрывалась от общего контура
                // в случае изменения размеров блока разметки, надо поменять значение 582 на значение шага повторения
                float blockDefaultLength = 582 * scale;
                float length = Helpers::GetLength(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                int realLength = ((int)length / (int)blockDefaultLength) * blockDefaultLength;
                AutoCAD.SetPropertyDouble(block, "Length",  realLength);
                AutoCAD.SetPropertyDouble(block, "Length2", realLength);

            }
                //tableBottom.DrawRepeatTextInterval(0,"1.17",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
            break;

            case ma18l: /*Направление движения(налево)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.18_3", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                AutoCAD.SetPropertyList(block, "Flip", 1);
                break;
            case ma18p: /*Направление движения(прямо)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.18_1", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                break;
            case ma18pl: /*Направление движения(прямо,налево)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.18_2", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                AutoCAD.SetPropertyList(block, "Flip", 1);
                break;
            case ma18pr: /*Направление движения(прямо,направо)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.18_2", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                break;
            case ma18prl: /*Направление движения(прямо,направо,налево)*/
                BUILDER_ERROR("Разметка 1.8prl не реализована");
                break;

            case ma18r: /*Направление движения(направо)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.18_3", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                break;
            case ma18rl: /*Направление движения(направо,налево)*/
                BUILDER_ERROR("Разметка 1.8rl не реализована");
                //tableBottom.DrawRepeatTextInterval(0,"1.18",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma19_1:  /*Направление перестроения(направо)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.19", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                break;
            case ma19_2:  /*Направление перестроения(налево)*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.19", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                AutoCAD.SetPropertyList(block, "Flip", 1);
                //tableBottom.DrawRepeatTextInterval(0,"1.19",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma20: /*Приближение к поперечной линии 1.13*/
                angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[count - 1], ScaleY);
                block = AutoCAD.DrawBlock("r_1.20", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 4);
                break;

            case ma21: /*Приближение к поперечной линии 1.12*/
                //tableBottom.DrawRepeatTextInterval(0,"1.21",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                BUILDER_ERROR("Разметка 1.21 не реализована");
                break;

            case ma22:  /*Обозначение номера дороги*/
                BUILDER_ERROR("Разметка 1.22 не реализована");
                //tableBottom.DrawRepeatTextInterval(0,"1.22",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma23:  /*Обозначение полосы движения только для маршрутных транспортных средств*/
                block = AutoCAD.DrawBlock("r_1.23",
                                          Poly->Points[0].x,
                                          -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI,
                                          ScaleYBlock / 4);
                //tableBottom.DrawRepeatTextInterval(0,"1.23",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;

            case ma24_1: /*Дублирование предупреждающих дорожных знаков*/
                block = AutoCAD.DrawBlock("r_1.24.1", Poly->Points[0].x, -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI);//ma24_2_20km
                break;
             case ma24_1_children: /*Дублирование предупреждающих дорожных знаков*/
                block = AutoCAD.DrawBlock("r_1.24.1_children", Poly->Points[0].x, -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI);//ma24_2_20km
                break;
            case ma24_2_20km: /*Дублирование ограничения в 20км*/
                block = AutoCAD.DrawBlock("r_1.24.2_20km", Poly->Points[0].x, -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI);
                break;
            case ma24_2: /*Дублирование ограничения в 40км*/
                block = AutoCAD.DrawBlock("r_1.24.2_40km", Poly->Points[0].x, -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI);
                break;
            case ma24_3: /*Дублирование дорожного знака Инвалиды*/
                BUILDER_ERROR("Разметка 1.24 на позиции " << Poly->Points[0].x << " не реализована");
                //tableBottom.DrawRepeatTextInterval(0,"1.24",Poly->Points[0].x,Poly->Points[count-1].x,StringConvert,100000,0.25);
                break;
            case ma24_4: /*Дублирование дорожного знака Инвалиды*/
                block = AutoCAD.DrawBlock("r_1.24_4", Poly->Points[0].x, -ScaleY * Poly->Points[0].y,
                                          m->Direction == roDirect ? 0 : M_PI);
                break;
            case ma25:  /*Обозначение искусственных неровностей*/
                x = Poly->Points[0].x;
                y = Poly->Points[0].y;
                height = ScaleY * (Poly->Points[count - 1].y - y);
                if (height < 0) {
                    rot = M_PI / 2;
                    height = -height;
                } else {
                    rot = -M_PI / 2;
                }
                block = AutoCAD.DrawBlock("r_1.25", x, -ScaleY * y, rot, ScaleYBlock / 4);
                AutoCAD.SetPropertyDouble(block, "Width", height);
                break;
            default:
                BUILDER_ERROR("Разметка с id=" << m->Kind << " не реализована (id смотри в таблице Classifier)");
            }
        }
    } catch (...) {
        BUILDER_ERROR( ("Ошибка вывода разметки " + IntToStr((int)m->Kind) + " на позиции " + IntToStr(Poly->Points[0].x)).c_str() );
        return false;
    }
    return true;
}

bool __fastcall TAcadExport::ExportTube(TExtPolyline *Poly, TRoadTube* t, bool fEnd) {
    float xLength, yLength, edge, Length;
    AcadBlockReferencePtr block;
    int min, max, miny, maxy;
    TPoint pS, pE, pT;

    if (fEnd) {
        return true;
    }

    if (Poly->Points[0].y > Poly->Points[1].y) {
        pE = Poly->Points[1];
        pS = Poly->Points[0];
    } else {
        pE = Poly->Points[0];
        pS = Poly->Points[1];
    }

    if (Poly->Points[0].x < Poly->Points[1].x) {
        min = Poly->Points[0].x;
        max = Poly->Points[1].x;
    } else {
        min = Poly->Points[1].x;
        max = Poly->Points[0].x;
    }


    if (~iStart) {
        if (max < iStart) return true;
    }
    if (~iEnd) {
        if (min > iEnd) return true;
    }

    edge = Helpers::GetAngle2(pS, pE, ScaleY, &Length);
    if (!fAlreadyDrawTube) {
        Tube = AutoCAD.DrawBlock("tube");
        fAlreadyDrawTube = true;
    }
    block = Tube->Copy();
    block->set_InsertionPoint(AutoCAD.cadPoint(pS.x, -ScaleY * pS.y));
    block->Rotation = edge;
    AutoCAD.SetPropertyDouble(block, "Length", Length);
    if (Length > 2000 ) {
        AutoCAD.SetAttribute(block, "LABEL", "т:" + IntToStr((pS.x / 100) % 1000));
    }
    return true;
}

bool __fastcall TAcadExport::ExportBridge(TExtPolyline *Poly, TRoadBridge *b, bool fEnd) {
    static float yMin, yMax, xMin, xMax, width, length;
    static AcadBlockReferencePtr block;
    if (fEnd) {
        return true;
    }
    yMin = Poly->Points[0].y;
    yMax = Poly->Points[2].y;
    xMin = Poly->Points[0].x;
    xMax = Poly->Points[2].x;
    width = yMax - yMin;
    if (width < 0) width = - width;
    length = xMax - xMin;
    if (length < 0) length = - length;
    block = AutoCAD.DrawBlock("bridge", xMin < xMax ? xMin : xMax, -ScaleY * (yMin > yMax ? yMin : yMax));
    AutoCAD.SetPropertyDouble(block, "Width", ScaleY * width);
    AutoCAD.SetPropertyDouble(block, "Length", length);
    return true;
}


AcadBlockReferencePtr TAcadExport::DrawBarrier(vector<TPoint> &points, AnsiString blockname, bool fFlip, bool fExist, bool fOpenLeft, int *fLastVisible)
{

    float yoffset, xoffset, angle, length;
    TPoint pMax, pMin;
    AcadBlockReferencePtr block;

    int count = points.size();

    for (int i = 0; i < count - 1; i++) {
        pMin  = points[i];
        pMin.y *= -ScaleY;

        pMax  = points[i + 1];
        pMax.y *= -ScaleY;

        yoffset = (pMax.y - pMin.y);
        xoffset = pMax.x - pMin.x;
        angle = xoffset != 0 ? atan(yoffset / xoffset) : yoffset < 0 ? -M_PI_2 : M_PI_2;
        if (xoffset < 0)angle += M_PI;
        length = sqrt(yoffset * yoffset + xoffset * xoffset);

        block.Unbind();
        block = AutoCAD.DrawBlock(blockname, pMin.x, pMin.y, angle);

        if (block.IsBound()) {
            if (!fExist) block->color = NotExistColor;
            AutoCAD.SetPropertyDouble(block, "Length", length);
            AutoCAD.SetPropertyList(block, "Flip", fFlip);
            if (i > 0) {
                if (i < count - 2) {
                    AutoCAD.SetPropertyListVariant(block, "visible", "none");
                } else {
                    if (fLastVisible) *fLastVisible = 2;
                    AutoCAD.SetPropertyListVariant(block, "visible", "right");
                }
            } else {
                if (fOpenLeft) {
                    if (count > 2) {
                        AutoCAD.SetPropertyListVariant(block, "visible", "none");
                    } else {
                        if (fLastVisible) *fLastVisible = 2;
                        AutoCAD.SetPropertyListVariant(block, "visible", "right");
                    }
                } else {
                    if (count > 2) {
                        AutoCAD.SetPropertyListVariant(block, "visible", "left");
                    } else {
                        if (fLastVisible) *fLastVisible = 0;
                        AutoCAD.SetPropertyListVariant(block, "visible", "both");
                    }
                }
            }
        }
    }
    return block;
}


void StyleDrawBarrierMetal(AcadPolylinePtr& pl, void* data)
{
    BarrierDrawStyleParameters* params = (BarrierDrawStyleParameters*)data;
    pl->set_Lineweight(params->lineWeight);
    pl->set_LinetypeScale(params->lineTypeScale);
    pl->set_Linetype(WideString("barrier-circle"));
    if (!params->exist)
        pl->color = params->NotExistColor;
}

void StyleDrawBarrierUndefined(AcadPolylinePtr& pl, void* data)
{
    BarrierDrawStyleParameters* params = (BarrierDrawStyleParameters*)data;
    pl->set_Lineweight(params->lineWeight);
    pl->set_LinetypeScale(params->lineTypeScale);
    pl->set_Linetype(WideString("barrier-square"));
    if (!params->exist)
        pl->color = params->NotExistColor;
}

void StyleDrawBarrierCivil(AcadPolylinePtr& pl, void* data)
{
    BarrierDrawStyleParameters* params = (BarrierDrawStyleParameters*)data;
    pl->set_Lineweight(acLnWt070);
    pl->set_LinetypeScale(params->lineTypeScale * 6);
    pl->set_Linetype(WideString("perila"));
    pl->color = 20;
}

void StyleDrawBarrierNewJersey(AcadPolylinePtr& pl, void* data)
{
    BarrierDrawStyleParameters* params = (BarrierDrawStyleParameters*)data;
    pl->set_Lineweight(params->lineWeight);
    pl->set_LinetypeScale(params->lineTypeScale);
    pl->set_Linetype(WideString("barrier-square"));
    if (!params->exist)
        pl->color = params->NotExistColor;
}

bool __fastcall TAcadExport::ExportBarrier(TExtPolyline *Poly, TRoadBarrier *b, bool exist, bool fEnd) {
    static dir, counter = 0;
    static AnsiString str;

    static AcadBlockReferencePtr lBlockLeft, lBlockRight, block;
    static float lEndRight = -1, lEndLeft = -1;
    static lPropLeft = -1, lPropRight = -1, curProp;
    static bool fOpenLeft;


    if (fEnd) {
        if (!fDrawMap) {
            if (~iTopBarriers)tableTop.FillLastGaps(iStep, iTopBarriers);
            if (~iBottomBarriers)tableBottom.FillLastGaps(iStep, iBottomBarriers);
        }
        return true;
    }

    dir = b->Placement == opLeft ? 1 : -1;

    lPointBarrier.x = Poly->Points[Poly->Count - 1].x;

    vector<TPoint> points;
    for (int i = 0; i < Poly->Count; i++) {
        points.push_back(Poly->Points[i]);
    }
    if (iMinBarrierSegmentLength != -1)
        Utils::optimize(points, iMinBarrierSegmentLength);

    sort(points.begin(), points.end(), barrierPointAsc());

    bool temp;

    float Min, Max, yoffset, xoffset, angle, length;
    TPoint pMin, pMax;
    bool inversed;
    if (points.front().x > points.back().x) {
        Min = points.back().x;
        pMin = points.back();
        pMax = points.front();
        Max = points.front().x;
        inversed = true;
    } else {
        Max = points.back().x;
        pMax = points.back();
        pMin = points.front();
        Min = points.front().x;
        inversed = false;
    }

    if (~iStart) {
        if (Max < iStart) return true;
    }
    if (~iEnd) {
        if (Min > iEnd) return true;
    }

    curProp = 0;

    fOpenLeft = false;
    int lastStep;

    switch (b->Placement) {
    case opLeft:
        if ( abs(int(pMin.x - lEndLeft)) < 200) {
            switch (lPropLeft) {
            case 0:
                curProp = 2;
                if (lBlockLeft.IsBound()) {
                    fOpenLeft = true;
                    AutoCAD.SetPropertyListVariant(lBlockLeft, "visible", "left");
                }
                break;

            case 1:
            case 3:
                curProp = 2;
                break;

            case 2:
                curProp = 2;
                if (lBlockLeft.IsBound()) {
                    fOpenLeft = true;
                    AutoCAD.SetPropertyListVariant(lBlockLeft, "visible", "none");
                }
                break;
            }
        }
        lEndLeft = pMax.x;
        break;
    case opRight:
        if ( abs(int(pMin.x - lEndRight)) < 200) {
            switch (lPropLeft) {
            case 0:
                curProp = 2;
                if (lBlockRight.IsBound()) {
                    fOpenLeft = true;
                    AutoCAD.SetPropertyListVariant(lBlockRight, "visible", "left");
                }
                break;

            case 1:
            case 3:
                curProp = 2;
                break;

            case 2:
                curProp = 2;
                if (lBlockRight.IsBound()) {
                    fOpenLeft = true;
                    AutoCAD.SetPropertyListVariant(lBlockRight, "visible", "none");
                }
                break;
            }
        }
        lEndRight = pMax.x;
        break;
    }

    AnsiString barrierName = "";
    AcadPolylinePtr pl;
    AcadCirclePtr circle;
    vector<AcadPolylinePtr> lines;
    float k = ScaleY / 3.5;
    int lineTypeScale = 20 * k;
    int endsRadius = 100 * k;
    int lineWeight = acLnWt040;

    BarrierDrawStyleParameters params;
    params.lineWeight = lineWeight;
    params.lineTypeScale = lineTypeScale;
    params.NotExistColor = NotExistColor;
    params.exist = exist;

    switch (b->Construction) {
    case br112:
        str = "ДО (У3)"; //str = "Барьерное одностороннее"
        barrierName = "barBarrierMetal";
        //block = DrawBarrier(points, barrierName, dir<0?0:1, exist, fOpenLeft, &curProp);
        DrawPolyPoints(Poly, true, false, StyleDrawBarrierMetal, &params);
        circle = AutoCAD.DrawCircle(pMin.x, pMin.y * -ScaleY, endsRadius);
        circle->set_Lineweight(lineWeight);
        if (!exist) circle->color = NotExistColor;

        circle = AutoCAD.DrawCircle(pMax.x, pMax.y * -ScaleY, endsRadius);
        circle->set_Lineweight(lineWeight);
        if (!exist) circle->color = NotExistColor;
        break;

    case br113:
        str = "ДО (У3)"; //str = "Барьерное двухстороннее";
        barrierName = "barBarrierMetalDuo";
        block = DrawBarrier(points, barrierName, dir < 0 ? 0 : 1, exist, fOpenLeft, &curProp);
        break;

    case br114:
        str = "Тросовое";
        break;

    case br115:
    case br118:
        str = "ДО (У3)"; //str = "Парапеты"; "По типу Нью-Джерси";
        barrierName = "barNewJersey";
        DrawPolyPoints(Poly, true, false, StyleDrawBarrierNewJersey, &params);

        pl = AutoCAD.DrawRect(pMin.x, pMin.y * -ScaleY, endsRadius, endsRadius);
        pl->set_Lineweight(lineWeight);
        if (!exist) pl->color = NotExistColor;

        pl = AutoCAD.DrawRect(pMax.x, pMax.y * -ScaleY, endsRadius, endsRadius);
        pl->set_Lineweight(lineWeight);
        if (!exist) pl->color = NotExistColor;

        // рисование сноски на разметку 2.5 на ограждении
        lastStep = -9999;
        for (int i = 0; i < points.size(); i++) {
            int step = points[i].x / iStep;
            if (step != lastStep
                    || (i == points.size() - 1 && abs(points.front().x - points.back().x) > 10000)) {
                block = AutoCAD.DrawBlock("r_label", points[i].x, points[i].y * -ScaleY, 0, ScaleYBlock / 4);
                if (block.IsBound()) {
                    AutoCAD.SetAttribute(block, "Label", "2.5");
                }
            }
            lastStep = step;
        }

        break;

    case br116:
        str = "Сетки";
        break;

    case br117:
        str = "Перила";
        barrierName = "barCivil";
        params.lineTypeScale = lineTypeScale * 2;
        DrawPolyPoints(Poly, true, false, StyleDrawBarrierCivil, &params);
        break;

    case brm:
        str = "ДО (У3)"; //str = "Металлическое";
        barrierName = "barBarrierMetal";
        block = DrawBarrier(points, barrierName, dir < 0 ? 0 : 1, exist, fOpenLeft, &curProp);
        break;

    default:
        str = "ДО (У3)"; // нестандартное
        DrawPolyPoints(Poly, true, false, StyleDrawBarrierUndefined, &params);
        pl = AutoCAD.DrawRect(pMin.x, pMin.y * -ScaleY, endsRadius, endsRadius);
        pl->set_Lineweight(lineWeight);
        if (!exist) pl->color = NotExistColor;

        pl = AutoCAD.DrawRect(pMax.x, pMax.y * -ScaleY, endsRadius, endsRadius);
        pl->set_Lineweight(lineWeight);
        if (!exist) pl->color = NotExistColor;
        break;
    }

    if (block.IsBound()) {
        switch (curProp) {
        case 0:
            break;
        case 1:
            AutoCAD.SetPropertyListVariant(block, "visible", "left");
            break;
        case 2:
            AutoCAD.SetPropertyListVariant(block, "visible", "right");
            break;
        case 3:
            AutoCAD.SetPropertyListVariant(block, "visible", "none");
            break;
        }
    }

    for (int i = 0; i < lines.size(); ++i) {
        lines[i].Release();
    }

    if (strProjectBarrierPrefix.Length()) {
        str = AnsiString(exist ? "" : strProjectBarrierPrefix.c_str()) + " " + str; //"ДО (У3)";
    }

    if (!fDrawMap) {
        switch (b->Placement) {
        case opLeft:
            if (block.IsBound()) lBlockLeft = block;
            lPropLeft = curProp;
            tableTop.DrawRepeatTextIntervalRoadMark(iTopBarriers, str, Poly->Points[0].x, lPointBarrier.x, Helpers::StringConvert, iStep, true, 0.43);
            break;
        case opRight:
            if (block.IsBound()) lBlockRight = block;
            lPropRight = curProp;
            tableBottom.DrawRepeatTextIntervalRoadMark(iBottomBarriers, str, Poly->Points[0].x, lPointBarrier.x, Helpers::StringConvert, iStep, true, 0.43);
            break;
        }
    }

    return true;

}

bool __fastcall TAcadExport::ExportSignal(TExtPolyline *Poly, TRoadSignal *s, bool exist, bool fEnd) {
    static AnsiString str;

    if (fEnd) {
        if (!fDrawMap) {
            if (~iTopBarriers)tableTop.FillLastGaps(iStep, iTopBarriers);
            if (~iBottomBarriers)tableBottom.FillLastGaps(iStep, iBottomBarriers);
        }
        return true;
    }

    if (~iStart) {
        if (s->LMax < iStart) return true;
    }
    if (~iEnd) {
        if (s->LMin > iEnd) return true;
    }

    float scale = ((float)ScaleY / 2) * 100;

    AcadBlockReferencePtr block;

    int count = Poly->Count;
    try {
        if (s->Count == 1) {
            if (!fDrawMap) {
                switch (s->Placement) {
                case opLeft:
                    tableTop.DrawRepeatTextIntervalRoadMark(iTopBarriers, "1", s->LMin, s->LMin + 100, Helpers::StringConvert, iStep, true, 0.43);
                    break;
                case opRight:
                    tableBottom.DrawRepeatTextIntervalRoadMark(iBottomBarriers, "1", s->LMin, s->LMin + 100, Helpers::StringConvert, iStep, true, 0.43);
                    break;
                }
            }
            block = AutoCAD.DrawBlock("signalpost", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, 0, scale);
            if (!exist) block->color = NotExistColor;
        } else if (s->Count > 1 && count > 1) {

            float *length = new float[count];
            float tx, ty, step, curL, k;
            int iEnd, iStart;
            int i;
            int iCur = 1;

            length[0] = 0;
            for (i = 0; i < count - 1; i++) {
                tx = Poly->Points[i + 1].x - Poly->Points[i].x;
                ty = Poly->Points[i + 1].y - Poly->Points[i].y;
                length[iCur++] = length[iCur - 1] + sqrt(tx * tx + ty * ty);
                if (!Poly->Codes[i].Visible()) {
                    iEnd = i;
                }
            }
            step = length[iCur - 1] / (s->Count - 1);

            std::vector<int> signalsPos(s->Count);
            signalsPos.push_back(s->LMin);

            iCur = 1;
            curL = 0;
            for (i = 0; i < s->Count - 2; i++) {
                curL += step;
                while (curL > length[iCur]) {
                    iCur++;
                    if (iCur > count) {
                        break;
                    }
                }

                k = 1 - (length[iCur] - curL) / (length[iCur] - length[iCur - 1]);
                tx = Poly->Points[iCur].x - Poly->Points[iCur - 1].x;
                ty = -ScaleY * (Poly->Points[iCur].y - Poly->Points[iCur - 1].y);
                signalsPos.push_back(Poly->Points[iCur - 1].x + k * tx);
                block = AutoCAD.DrawBlock("signalpost", signalsPos.back(), -ScaleY * Poly->Points[iCur - 1].y + k * ty, 0, scale);
                if (!exist) block->color = NotExistColor;
            }
            signalsPos.push_back(s->LMax);

            if (!fDrawMap) {
                switch (s->Placement) {
                case opLeft:
                    tableTop.DrawRepeatTextIntervalRoadMark(iTopBarriers, "", s->LMin, s->LMax, Helpers::StringConvertSignals, iStep, true, 0.43, (void*)&signalsPos);
                    break;
                case opRight:
                    tableBottom.DrawRepeatTextIntervalRoadMark(iBottomBarriers, "", s->LMin, s->LMax, Helpers::StringConvertSignals, iStep, true, 0.43, (void*)&signalsPos);
                    break;
                }
            }

            block = AutoCAD.DrawBlock("signalpost", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, 0, scale);
            if (!exist) block->color = NotExistColor;
            block = AutoCAD.DrawBlock("signalpost", Poly->Points[count - 1].x, -ScaleY * Poly->Points[count - 1].y, 0, scale);
            if (!exist) block->color = NotExistColor;
            delete[] length;
        }
    } catch (...) {
        BUILDER_ERROR( ("Ошибка вывода столбиков на промежутке [" + IntToStr(s->LMin) + "; " + IntToStr(s->LMax) + "]").c_str() );
        return false;
    }
    return true;
}

bool __fastcall TAcadExport::ExportMoundHeight(TMoundHeight *m, int fase, bool fEnd) {
    AnsiString str;
    static bool ffirstL, ffirstR;
    static lRightHeight, lLeftHeight, lRightL, lLeftL;

    if (fEnd) {
        return true;
    }

    if (fDrawMap) return true;

    if (fase) {
        switch (m->Placement) {
        case rsLeft:
            if (ffirstL) {
                ffirstL = false;
            } else {
                if ( !((~iStart && m->L < iStart) || (~iEnd && lLeftL > iEnd)) ) {
                    if (lLeftHeight > m->Height) {
                        tableTop.DrawLine(iTopMoundH, lLeftL, 0.5, m->L, 0.1);
                    } else if (lLeftHeight < m->Height) {
                        tableTop.DrawLine(iTopMoundH, lLeftL, 0.1, m->L, 0.5);
                    } else {
                        tableTop.DrawLine(iTopMoundH, lLeftL, 0.5, m->L, 0.5);
                    }
                    tableTop.DrawRepeatTextIntervalMoundHeight(iTopMoundH, lLeftL, m->L, lLeftHeight, m->Height, iStep);
                }
            }
            lLeftHeight = m->Height;
            lLeftL = m->L;
            break;

        case rsRight:
            if (ffirstR) {
                ffirstR = false;
            } else {
                if ( !((~iStart && m->L < iStart) || (~iEnd && lRightL > iEnd)) ) {
                    if (lRightHeight > m->Height) {
                        tableBottom.DrawLine(iBottomMoundH, lRightL, 0.5, m->L, 0.1);
                    } else if (lRightHeight < m->Height) {
                        tableBottom.DrawLine(iBottomMoundH, lRightL, 0.1, m->L, 0.5);
                    } else {
                        tableBottom.DrawLine(iBottomMoundH, lRightL, 0.5, m->L, 0.5);
                    }
                    tableBottom.DrawRepeatTextIntervalMoundHeight(iBottomMoundH, lRightL, m->L, lRightHeight, m->Height, iStep);
                }
            }
            lRightHeight = m->Height;
            lRightL = m->L;
            break;
        }
    } else {
        ffirstL = ffirstR = true;
    }
    return true;
}


bool __fastcall TAcadExport::ExportCurve(TDangerCurve *c, bool fEnd) {
    if (fEnd) {
        return true;
    }

    if (fDrawMap) return true;

    int tLessForVerticalLabels = lessForVerticalLabels;

    lessForVerticalLabels = 0;
    tableBottom.lessForVerticalLabels = 0;
    tableTop.lessForVerticalLabels = 0;

    static TCurveKind lKind = -1;
    float length = c->LMax - c->LMin;

    if (~iStart) {
        if (c->LMax < iStart) return true;
    }
    if (~iEnd) {
        if (c->LMin > iEnd) return true;
    }

    AcadEllipsePtr ellipse;
    AcadBlockReferencePtr block;

    try {
        switch (c->Kind) {
        case ckCircle:
            if (iTopCurves >= 0) {
                block = tableTop.DrawBlock("pArc", iTopCurves, c->LMin);
                AutoCAD.SetPropertyDouble(block, "Length", length);
                if (c->Radius < 0) {
                    c->Radius = -c->Radius;
                    AutoCAD.SetPropertyList(block, "Flip", 1);
                }
            }
            if (iBottomCurves >= 0) {
                block = tableBottom.DrawBlock("pArc", iBottomCurves, c->LMin);
                AutoCAD.SetPropertyDouble(block, "Length", length);
                if (c->Radius < 0) {
                    c->Radius = -c->Radius;
                    AutoCAD.SetPropertyList(block, "Flip", 1);
                }
            }
            tableTop.DrawRepeatTextIntervalRoadMark(iTopCurves, "R=" + IntToStr((int)c->Radius), c->LMin, c->LMax, 0, iStep, false, 0.33);
            tableBottom.DrawRepeatTextIntervalRoadMark(iBottomCurves, "R=" + IntToStr((int)c->Radius), c->LMin, c->LMax, 0, iStep, false, 0.33);
            break;

        case ckLeftCurve:
            if (lKind == ckLine) {
                if (iTopCurves >= 0) {
                    ellipse = tableTop.DrawLeftArcEllipse(iTopCurves, c->LMin, c->LMax);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = 0;
                        ellipse->EndAngle = M_PI_2;
                    } else {
                        ellipse->StartAngle = M_PI * 1.5;
                        ellipse->EndAngle = M_PI * 2;
                    }
                    tableTop.DrawLine(iTopCurves, c->LMin, 0.25, c->LMin, 0.75);
                    tableTop.DrawVerticalText(c->LMin % iStep / 100, iTopCurves, c->LMin, 0.75, true, 0.15);
                }
                if (iBottomCurves >= 0) {
                    ellipse = tableBottom.DrawLeftArcEllipse(iBottomCurves, c->LMin, c->LMax);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = 0;
                        ellipse->EndAngle = M_PI_2;
                    } else {
                        ellipse->StartAngle = M_PI * 1.5;
                        ellipse->EndAngle = M_PI * 2;
                    }
                    tableBottom.DrawLine(iBottomCurves, c->LMin, 0.25, c->LMin, 0.75);
                    tableBottom.DrawVerticalText(c->LMin % iStep / 100, iBottomCurves, c->LMin, 0.75, true, 0.15);
                }
            } else if (lKind == ckCircle) {
                if (iTopCurves >= 0) {
                    ellipse = tableTop.DrawLeftArcEllipse(iTopCurves, c->LMax, c->LMin);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = M_PI * 1.5;
                        ellipse->EndAngle = M_PI * 2;
                    } else {
                        ellipse->StartAngle = M_PI;
                        ellipse->EndAngle = M_PI * 1.5;
                    }
                    tableTop.DrawLine(iTopCurves, c->LMax, 0.25, c->LMax, 0.75);
                    tableTop.DrawVerticalText(c->LMax % iStep / 100, iTopCurves, c->LMax, 0.75, false, 0.15);
                }
                if (iBottomCurves >= 0) {
                    ellipse = tableBottom.DrawLeftArcEllipse(iBottomCurves, c->LMax, c->LMin);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = M_PI * 1.5;
                        ellipse->EndAngle = M_PI * 2;
                    } else {
                        ellipse->StartAngle = M_PI;
                        ellipse->EndAngle = M_PI * 1.5;
                    }
                    tableBottom.DrawLine(iBottomCurves, c->LMax, 0.25, c->LMax, 0.75);
                    tableBottom.DrawVerticalText(c->LMax % iStep / 100, iBottomCurves, c->LMax, 0.75, false, 0.15);
                }
            }

            break;

        case ckRightCurve:

            if (lKind == ckLine) {
                if (iTopCurves >= 0) {
                    ellipse = tableTop.DrawRightArcEllipse(iTopCurves, c->LMin, c->LMax);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = M_PI_2;
                        ellipse->EndAngle = M_PI;
                    } else {
                        ellipse->StartAngle = 0;
                        ellipse->EndAngle = M_PI_2;
                    }
                    tableTop.DrawLine(iTopCurves, c->LMin, 0.25, c->LMin, 0.75);
                    tableTop.DrawVerticalText(c->LMin % iStep / 100, iTopCurves, c->LMin, 0.75, true, 0.15);
                }
                if (iBottomCurves >= 0) {
                    ellipse = tableBottom.DrawRightArcEllipse(iBottomCurves, c->LMin, c->LMax);
                    if (abs(c->LMin - c->LMax) < tableBottom.RowHeight / 2) {
                        ellipse->StartAngle = M_PI_2;
                        ellipse->EndAngle = M_PI;
                    } else {
                        ellipse->StartAngle = 0;
                        ellipse->EndAngle = M_PI_2;
                    }
                    tableBottom.DrawLine(iBottomCurves, c->LMin, 0.25, c->LMin, 0.75);
                    tableBottom.DrawVerticalText(c->LMin % iStep / 100, iBottomCurves, c->LMin, 0.75, true, 0.15);
                }
            } else if (lKind == ckCircle) {
                if (iTopCurves >= 0) {
                    ellipse = tableTop.DrawRightArcEllipse(iTopCurves, c->LMax, c->LMin);
                    if (abs(c->LMin - c->LMax) < tableTop.RowHeight / 2) {
                        ellipse->StartAngle = M_PI;
                        ellipse->EndAngle = M_PI * 1.5;
                    } else {
                        ellipse->StartAngle = M_PI_2;
                        ellipse->EndAngle = M_PI;
                    }
                    tableTop.DrawLine(iTopCurves, c->LMax, 0.25, c->LMax, 0.75);
                    tableTop.DrawVerticalText(c->LMax % iStep / 100, iTopCurves, c->LMax, 0.75, false, 0.15);
                }
                if (iBottomCurves >= 0) {
                    ellipse = tableBottom.DrawRightArcEllipse(iBottomCurves, c->LMax, c->LMin);
                    if (abs(c->LMin - c->LMax) < tableBottom.RowHeight / 2) {
                        ellipse->StartAngle = M_PI;
                        ellipse->EndAngle = M_PI * 1.5;
                    } else {
                        ellipse->StartAngle = M_PI_2;
                        ellipse->EndAngle = M_PI;
                    }
                    tableBottom.DrawLine(iBottomCurves, c->LMax, 0.25, c->LMax, 0.75);
                    tableBottom.DrawVerticalText(c->LMax % iStep / 100, iBottomCurves, c->LMax, 0.75, false, 0.15);
                }
            }

            break;

        case ckLine:
            tableTop.DrawLine(iTopCurves, c->LMin, c->LMax);
            tableBottom.DrawLine(iBottomCurves, c->LMin, c->LMax);
            break;
        }
    } catch (...) {
        BUILDER_ERROR( ("Ошибка вывода кривой в плане на промежутке [" + IntToStr(c->LMin) + "; " + IntToStr(c->LMax) + "]").c_str() );
        return false;
    }
    lKind = c->Kind;

    lessForVerticalLabels = tLessForVerticalLabels;
    tableBottom.lessForVerticalLabels = tLessForVerticalLabels * 100;
    tableTop.lessForVerticalLabels = tableBottom.lessForVerticalLabels;

    return true;
}

bool __fastcall TAcadExport::ExportSlope(TDangerSlope *s, int fase, bool fEnd) {
    if (fEnd) {
        return true;
    }

    if (fDrawMap) return true;

    if (~iStart) {
        if (s->LMax < iStart) return true;
    }
    if (~iEnd) {
        if (s->LMin > iEnd) return true;
    }

    if (s->Promille > 0) {
        if (iTopSlopes >= 0) {
            tableTop.DrawRepeatEmptyInterval(iTopSlopes, s->LMin, s->LMax, iStep, true, true, true);
            tableTop.DrawRepeatVerticalTextInterval(iTopSlopes, s->LMin, s->LMax, 0.33, iStep, false, 0.15);
        }
        if (iBottomSlopes >= 0) {
            tableBottom.DrawRepeatEmptyInterval(iBottomSlopes, s->LMin, s->LMax, iStep, true, true, true);
            tableBottom.DrawRepeatVerticalTextInterval(iBottomSlopes, s->LMin, s->LMax, 0.33, iStep, false, 0.15);
        }
        if (iTopSlopes >= 0)tableTop.DrawRepeatTextIntervalSpec2(iTopSlopes, "l=" + IntToStr(abs(s->Promille)) + "‰", s->LMin, s->LMax, false, iStep);
        if (iBottomSlopes >= 0)tableBottom.DrawRepeatTextIntervalSpec2(iBottomSlopes, "l=" + IntToStr(abs(s->Promille)) + "‰", s->LMin, s->LMax, false, iStep);
    } else if (s->Promille < 0) {
        if (iTopSlopes >= 0) {
            tableTop.DrawRepeatEmptyInterval(iTopSlopes, s->LMin, s->LMax, iStep, true, true, false);
            tableTop.DrawRepeatVerticalTextInterval(iTopSlopes, s->LMin, s->LMax, 0.66, iStep, false, 0.15);
        }
        if (iBottomSlopes >= 0) {
            tableBottom.DrawRepeatEmptyInterval(iBottomSlopes, s->LMin, s->LMax, iStep, true, true, false);
            tableBottom.DrawRepeatVerticalTextInterval(iBottomSlopes, s->LMin, s->LMax, 0.66, iStep, false, 0.15);
        }
        if (iTopSlopes >= 0)tableTop.DrawRepeatTextIntervalSpec2(iTopSlopes, "l=" + IntToStr(abs(s->Promille)) + "‰", s->LMin, s->LMax, true, iStep);
        if (iBottomSlopes >= 0)tableBottom.DrawRepeatTextIntervalSpec2(iBottomSlopes, "l=" + IntToStr(abs(s->Promille)) + "‰", s->LMin, s->LMax, true, iStep);
    } else {
        if (iTopSlopes >= 0) {
            tableTop.DrawLine(iTopSlopes, s->LMin, tableTop.kBottomEmptyPadding, s->LMax, tableTop.kBottomEmptyPadding);
            tableTop.DrawRepeatVerticalTextInterval(iTopSlopes, s->LMin, s->LMax, 0.66, iStep, false, 0.15);
        }
        if (iBottomSlopes >= 0) {
            tableBottom.DrawLine(iBottomSlopes, s->LMin, tableBottom.kBottomEmptyPadding, s->LMax, tableBottom.kBottomEmptyPadding);
            tableBottom.DrawRepeatVerticalTextInterval(iBottomSlopes, s->LMin, s->LMax, 0.66, iStep, false, 0.15);
        }
    }
    return true;
}

bool __fastcall TAcadExport::ExportBusStop(TExtPolyline *Poly, TBusStop *s, bool fEnd) {
    static float rotation;
    if (fEnd) {
        return true;
    }

    if (~iStart) {
        if (Poly->Points[0].x < iStart) return true;
    }
    if (~iEnd) {
        if (Poly->Points[0].x > iEnd) return true;
    }

    rotation = s->GetPlacement() == spLeft ? M_PI : 0;
    AutoCAD.DrawBlock("busstop", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, rotation, ScaleY / 2);
    return true;
}

bool __fastcall TAcadExport::ExportDescreetRoadObject(TExtPolyline *Poly, TDescreetRoadObject *s, bool fEnd) {
    static float rotation;
    if (fEnd) {
        return true;
    }

    if (~iStart) {
        if (Poly->Points[0].x < iStart) return true;
    }
    if (~iEnd) {
        if (Poly->Points[0].x > iEnd) return true;
    }

    String blockName = "";   
    switch(s->DrwClassId) {
        case  517: // решетка ливневой канализации
            blockName = "drainage";
        break;
        case  516: // люк смотрового колодца
            blockName = "well";
        break;
        case  518: // урна
            blockName = "can";
        break;
        case  519: // скамья
            blockName = "bench";
        break;
    }
    if (blockName != "") {
        AutoCAD.DrawBlock(blockName, Poly->Points[0].x, -ScaleY * Poly->Points[0].y, rotation, ScaleY / 2);
    }
    return true;
}

bool __fastcall TAcadExport::ExportRestZone(TExtPolyline *Poly, TSquareRoadSideObject_Kromka *r, bool fEnd) {
    if (fEnd) {
        return true;
    }
    DrawPolyPoints(Poly);
    return true;
}

bool __fastcall TAcadExport::ExportSidewalk(KromkaObjectGroup *sidewalksGroup, bool fEnd) {

    if (fEnd) {
        if (!fDrawMap) {
            if (~iTopSidewalks)tableTop.FillLastGaps(iStep, iTopSidewalks);
            if (~iBottomSidewalks)tableBottom.FillLastGaps(iStep, iBottomSidewalks);
        }
        return true;
    }

    if (sidewalksGroup->objects.size()) {
        for (int j = 0; j < sidewalksGroup->objects.size(); ++j) {
            TSquareRoadSideObject_Kromka* s = sidewalksGroup->objects[j].obj;

            if (~iStart) {
                if (s->LMax < iStart) continue;
            }
            if (~iEnd) {
                if (s->LMin > iEnd) continue;
            }

            TExtPolyline *Poly = s->PrepareMetric(sidewalksGroup->road());

            AcadPolylinePtr pl[1];
            pl[0] = DrawPolyPoints(Poly, false, true);
            AcadHatchPtr hatch = AutoCAD.FillArea((IDispatch**)pl, 1, !sidewalksGroup->objects[j].exist ? NotExistColor : 0, strSidewalksHatch);
            if (hatch) hatch->PatternScale = iSidewalsHatchScale;

            delete Poly;
        }

        AnsiString str = "а/б";
        if (!fDrawMap) {
            switch (sidewalksGroup->objects[0].obj->Placement) {
            case spLeft:
                tableTop.DrawRepeatTextIntervalRoadMark(iTopSidewalks, str,
                                                        sidewalksGroup->min(), sidewalksGroup->max(), Helpers::StringConvert, iStep, true, 0.43);
                break;
            case spRight:
                tableBottom.DrawRepeatTextIntervalRoadMark(iBottomSidewalks, str,
                        sidewalksGroup->min(), sidewalksGroup->max(), Helpers::StringConvert, iStep, true, 0.43);
                break;
            }
        }

    }
    return true;
}

AcadBlockReferencePtr TAcadExport::DrawBorder(vector<TPoint> &points, AnsiString blockname, bool fExist)
{
    int count = points.size();
    float yoffset, xoffset, angle, length;
    TPoint pMax, pMin;
    AcadBlockReferencePtr block;
    for (int i = 0; i < count - 1; i++) {
        pMin  = points[i];
        pMin.y *= -ScaleY;

        pMax  = points[i + 1];
        pMax.y *= -ScaleY;

        yoffset = (pMax.y - pMin.y);
        xoffset = pMax.x - pMin.x;
        angle = xoffset != 0 ? atan(yoffset / xoffset) : yoffset < 0 ? -M_PI_2 : M_PI_2;
        if (xoffset < 0)angle += M_PI;
        length = sqrt(yoffset * yoffset + xoffset * xoffset);

        block = AutoCAD.DrawBlock(blockname, pMin.x, pMin.y, angle);

        if (block.IsBound()) {
            if (!fExist) block->color = NotExistColor;
            AutoCAD.SetPropertyDouble(block, "Length", length);
        }
    }
    return block;
}

void StyleBorderBgLine(AcadPolylinePtr& line, void* data)
{
    BorderDrawStyleParams *params = (BorderDrawStyleParams*)data;
    line->set_Lineweight(50);
    if (!params->exist) {
        line->color = params->NotExistColor;
    }
}

void StyleBorderFgLine(AcadPolylinePtr& line, void* data)
{
    line->set_Lineweight(30);
    line->set_Linetype(WideString("linedash_1"));
    AcadAcCmColorPtr color;
    color = line->TrueColor;
    color->SetRGB(255, 255, 255);
    line->TrueColor = color;
}

bool __fastcall TAcadExport::ExportBorder(TExtPolyline *Poly, TLinearRoadSideObject *o, bool exist, bool fEnd) {
    if (fEnd) return true;

    if (~iStart) {
        if (o->LMax < iStart) return true;
    }
    if (~iEnd) {
        if (o->LMin > iEnd) return true;
    }
    BorderDrawStyleParams params;
    params.exist = exist;
    params.NotExistColor = NotExistColor;
    DrawPolyPoints(Poly, true, false, StyleBorderBgLine, &params);
    DrawPolyPoints(Poly, true, false, StyleBorderFgLine, &params);
    return true;
}

bool __fastcall TAcadExport::ExportLighting(TExtPolyline *Poly, TRoadLighting *s, bool exist, bool fEnd) {
    if (fEnd) {
        return true;
    }

    if (~iStart) {
        if (Poly->Points[0].x < iStart) return true;
    }
    if (~iEnd) {
        if (Poly->Points[0].x > iEnd) return true;
    }

    AcadBlockReferencePtr block;

    double angle;
    if (Poly->Count == 2) {
        angle = Helpers::GetAngle2(Poly->Points[0], Poly->Points[1], ScaleY);
    } else {
        if (s->Placement == rsRight) {
            angle = M_PI;
        } else {
            angle = 0;
        }
    }

    block = AutoCAD.DrawBlock("lamp", Poly->Points[0].x, -ScaleY * Poly->Points[0].y, angle, ScaleYBlock / 2);
    if (block.IsBound()) {
        switch (s->Kind) {
        case lkOnce:
            AutoCAD.SetPropertyList(block, "Style", 0);
            break;

        case lkDouble:
            AutoCAD.SetPropertyList(block, "Style", 1);
            break;
        }
        if (!exist) {
            block->color = NotExistColor;
        }
    } else {
        return false;
    }

    return true;
}


void TAcadExport::ExportAddRowLine( AutoCADTable *table, int iRow,
                                    int iPos, int iEnd, AnsiString str)
{
    if (fDrawMap) return;

    AnsiString style = str.SubString(1, 2);
    AnsiString params;
    AnsiString sTemp;
    if (style == "$c") { //заливка
        params = str.SubString(3, str.Length() - 2).Trim();
        char hatchName[255];
        float scale;
        int color = 0;
        sscanf(params.c_str(), "%s\t%f\t%i", hatchName, &scale, &color);
        table->FillArea(iRow, iPos, iEnd, hatchName, iFillHatchScale, color);
        table->DrawBorder(iPos, iRow);
        table->DrawBorder(iEnd, iRow);
    } else if (style == "$b") { //блок
        params = str.SubString(3, str.Length() - 2).Trim();
        AnsiString blockName;

        TStringList *paramsValues = new TStringList();
        ExtractStrings(TSysCharSet() << '\t' << ' ',
                       TSysCharSet() << ' ' << '\t',
                       params.c_str(), paramsValues);
        if (paramsValues->Count == 0) {
            return;
        }
        table->FillGaps[iRow] = false;

        blockName = paramsValues->Strings[0]; // первый параметр - имя блока
        paramsValues->Delete(0);
        AcadBlockReferencePtr block = table->DrawBlock(blockName, iRow, iPos, (float)iEnd / 100);

        if (paramsValues->Count > 0) {
            if (block.IsBound()) {
                for (int i = 0; i < paramsValues->Count; i++) {
                    AnsiString param = paramsValues->Strings[i];
                    int suffixPos;
                    AnsiString name, value;

                    if ( suffixPos = param.Pos(':')) {
                        name = param.SubString(1, suffixPos - 1);
                        value = param.SubString(suffixPos + 1,  param.Length() - suffixPos);
                        AutoCAD.SetAttribute(block, name, value);
                    } else if (suffixPos = param.Pos('=')) {
                        name = param.SubString(1, suffixPos - 1);
                        value = param.SubString(suffixPos + 1,  param.Length() - suffixPos);
                        double dValue;
                        if (TryStrToFloat(value, dValue)) {
                            AutoCAD.SetPropertyDouble(block, name, dValue);
                        }
                    } else if (suffixPos = param.Pos('<')) {
                        int iValue;
                        name = param.SubString(1, suffixPos - 1);
                        value = param.SubString(suffixPos + 1,  param.Length() - suffixPos);
                        if (TryStrToInt(value, iValue)) {
                            AutoCAD.SetPropertyList(block, name, iValue);
                        } else {
                            AutoCAD.SetPropertyListVariant(block, name, value);
                        }
                    }
                }
            }
        }
        delete paramsValues;
    } else { // просто текст
        table->FillGaps[iRow] = true;
        table->DrawRepeatTextIntervalRoadMark(iRow, str, iPos, iEnd, 0, iStep, true);
    }
}

struct ExportAddRowsOptions {
    ExportAddRowsOptions()
        : offset(0)
    {}

    /**
    * try to update options with the values from line
    * values form (assigning value without spaces):
    * offset=value1 option2=value2 ...
    */
    static void FromLine(AnsiString line, ExportAddRowsOptions &options) {
        int pos;
        int result;
        AnsiString subString;
        // trying to find offset option
        if ( pos = line.Pos("offset") ) {
            subString = line.SubString(pos, line.Length() - pos + 1);
            result = sscanf(subString.c_str(), "offset=%d", &options.offset);
        }
        if ( pos = line.Pos("lineStyle") ) {
            char lineStyle[64];
            subString = line.SubString(pos, line.Length() - pos + 1);
            result = sscanf(subString.c_str(), "lineStyle=%s", &lineStyle);
            options.lineStyle = lineStyle;
        }
    }

    int offset; // offset of output rows
    AnsiString lineStyle;
};

int __fastcall TAcadExport::ExportAddRows(AnsiString path, AutoCADTable *table, bool check)
{
    if (fDrawMap) return 0;

    int iRow = -1;
    int iCount;
    int ePos, sPos;
    char sEPos[32], sSPos[32];
    AnsiString sIRow;
    char str[512] = {0};
    char value2[128] = {0};

    ExportAddRowsOptions exportAddRowOptions;

    AnsiString str2;
    AnsiString value;
    str2 = ChangeFileExt(ExtractFileName(path), "");

    int startCount = table == &tableTop ? iTopAddRow : iBottomAddRow;
    AnsiString LayerName = table == &tableTop ? "Top" : "Bottom";

    if (!sscanf(str2.c_str(), "%i_%s", &iRow, &str)) return -1;
    sIRow = IntToStr(iRow);
    iCount = sIRow.Length();
    strcpy(str, str2.SubString(iCount + 2, str2.Length() - iCount).c_str());
    if (iRow < 0) iRow = -iRow;



    if (!check) {
        ifstream file(path.c_str());
        AnsiString line;
        string s;
        int count;

        if (file.is_open()) {
            AddLayer(str);
            if (table->IsHeaderInclude) {
                table->DrawHeaderText(startCount + iRow - 1, str, HeaderTextHeight);
            }

            if (OutInfoLog) OutInfoLog("Вывожу \"" + AnsiString(str) + "\"");

            int linesCount = 0;
            int currentLine = 0;
            while (getline(file, s)) {
                linesCount++;
            }
            file.clear();
            file.seekg(0, ios::beg);
            int iTableRow = startCount + iRow - 1;
            table->FillGaps[iTableRow] = false;

            while (getline(file, s))  {
                // выходим если нажали отмену
                if (ProgressForm->Thread) {
                    AcadExportThread *thread = dynamic_cast<AcadExportThread*>(ProgressForm->Thread);
                    if ( thread->IsTerminated) {
                        return -1;
                    }
                }

                s.erase(s.find_last_not_of(" \n\r\t") + 1);

                line = s.c_str();
                if (s.length() <= 0)
                    continue;

                if (line[1] == '#') { // if comment
                    // remove comment symbol, and trim string
                    line[1] = ' ';
                    line.Trim();
                    // try to execute special option commands
                    ExportAddRowsOptions::FromLine(line, exportAddRowOptions);
                } else if (s.length() > 0) {
                    try {
                        vector<AnsiString> words;
                        Utils::split(line, " \t", words, 3);

                        count = strlen(sSPos) + 1 + strlen(sEPos) + 1;
                        if (!TryStrToInt(words[0], sPos)) {
                            OutInfoLog("Неправильный формат данных: " + str2 + " - " + line);
                            continue;
                        }
                        if (!TryStrToInt(words[1], ePos)) {
                            OutInfoLog("Ошибка вывода: " + str2 + " - " + line);
                            continue;
                        }
                        sPos += exportAddRowOptions.offset;
                        ePos += exportAddRowOptions.offset;

                        line = words[2];

                        ExportAddRowLine(table, iTableRow, sPos, ePos, line.Trim());
                    } catch (...) {
                        OutInfoLog("Ошибка вывода: " + str2 + " - " + line);
                    }
                }
                currentLine++;
                if (ProgressChanged) {
                    ProgressChanged((float) currentLine / linesCount * 100, "");
                }
            }
            file.close();
            if (table->FillGaps[iTableRow]) {
               table->FillLastGaps(iStep, iTableRow);
            }
        }
    }
    return iRow;
}

int __fastcall TAcadExport::ExportGraphicPath(AnsiString path, bool check)
{
    if (fDrawMap) return 0;

    int iRow = -1;
    int iCount, i;
    int ePos, sPos;
    char sEPos[32], sSPos[32];
    AnsiString sIRow;
    char str[512] = {0};
    char value2[128] = {0};
    ExportAddRowsOptions exportAddRowOptions;

    AnsiString str2;
    str2 = ChangeFileExt(ExtractFileName(path), "");

    AnsiString value;

    if (!sscanf(str2.c_str(), "%i_%s", &iRow, &str)) return -1;
    sIRow = IntToStr(iRow);
    iCount = sIRow.Length();
    strcpy(str, str2.SubString(iCount + 2, str2.Length() - iCount).c_str());
    if (iRow < 0) iRow = -iRow;
    if (!check) {
        ifstream file(path.c_str());
        string s;
        int count, linesCount;
        float iValue;
        float lValue = -1, curValue;
        if (file.is_open()) {
            AddLayer("Graphic" + IntToStr(iRow));

            lValue = curValue = 0;
            vector<double> pointsArray;
            bool fWas = false;

            int linesCount = 0;
            int currentLine = 0;
            while (getline(file, s)) {
                linesCount++;
            }
            file.clear();
            file.seekg(0, ios::beg);

            while (getline(file, s))  {
                AnsiString line = s.c_str();
                if (line[1] == '#') { // if comment
                    // remove comment symbol, and trim string
                    line[1] = ' ';
                    line.Trim();
                    // try to execute special option commands
                    ExportAddRowsOptions::FromLine(line, exportAddRowOptions);
                } else if (s.length() > 0) {
                    lValue = curValue;

                    if (sscanf(s.c_str(), "%i %i %f", &sPos, &ePos, &iValue) == 3) {
                        curValue = iValue > 1 ? (float)iValue / 100.0f : iValue;
                        pointsArray.push_back(sPos);
                        pointsArray.push_back(tableGraphic.LeftTop.y - tableGraphic.RowHeight * (iRow - 1) - (1 - lValue)*tableGraphic.RowHeight);
                        pointsArray.push_back(sPos);
                        pointsArray.push_back(tableGraphic.LeftTop.y - tableGraphic.RowHeight * (iRow - 1) - (1 - curValue)*tableGraphic.RowHeight);
                        fWas = true;
                    }
                    lValue = curValue;
                }
                currentLine++;
                if (ProgressChanged) {
                    ProgressChanged((float) currentLine / linesCount * 100, "");
                }
            }
            if (fWas) {
                pointsArray.push_back(ePos);
                pointsArray.push_back(tableGraphic.LeftTop.y - tableGraphic.RowHeight * (iRow - 1) - (1 - lValue)*tableGraphic.RowHeight);
                pointsArray.push_back(ePos);
                pointsArray.push_back(tableGraphic.LeftTop.y - tableGraphic.RowHeight * (iRow - 1) - (1 - curValue)*tableGraphic.RowHeight);
            }

            file.close();
            if (pointsArray.size()) {
                AcadPolylinePtr pl = DrawPolyLine(pointsArray);
                if (exportAddRowOptions.lineStyle != "") {
                   pl->set_Linetype(WideString(exportAddRowOptions.lineStyle));
                }
            }
        }
    }
    return iRow;
}

int __fastcall TAcadExport::ExportGraphic(AnsiString DirPath, bool check)
{

    TSearchRec rec;
    int value = -1;
    int max = 0;
    if (!FindFirst(DirPath + "\\graphic\\*.*", 0, rec)) {
        do {
            if ((value = ExportGraphicPath(DirPath + "\\graphic\\" + rec.Name, check)) > 0) {
                if (max < value)max = value;
            }
        } while (!FindNext(rec));
    }
    FindClose(rec);
    return max;
}


int __fastcall TAcadExport::ExportTopAddRows(AnsiString DirPath, bool check)
{
    if (!check && fTopAddRowsWithoutData) return 0;
    TSearchRec rec;
    int value = -1;
    int max = 0;
    if (!FindFirst(DirPath + "\\top\\*.*", 0, rec)) {
        do {
            // выходим если нажали отмену
            if (ProgressForm->Thread) {
                AcadExportThread *thread = dynamic_cast<AcadExportThread*>(ProgressForm->Thread);
                if ( thread->IsTerminated) {
                    return -1;
                }
            }
            if ((value = ExportAddRows(DirPath + "\\top\\" + rec.Name, &tableTop, check)) > 0) {
                // выходим если кто-то нажал отмену
                if (value == -1) {
                    return -1;
                }

                if (max < value)max = value;
            }
        } while (!FindNext(rec));
    }
    FindClose(rec);
    return max;
}

int __fastcall TAcadExport::ExportBottomAddRows(AnsiString DirPath, bool check)
{
    if (!check && fBottomAddRowsWithoutData) return 0;
    TSearchRec rec;
    int value = -1;
    int max = 0;
    if (!FindFirst(DirPath + "\\bottom\\*.*", 0, rec)) {
        do {
            if ((value = ExportAddRows(DirPath + "\\bottom\\" + rec.Name, &tableBottom, check)) > 0) {
                if (max < value)max = value;
            }
        } while (!FindNext(rec));
    }
    FindClose(rec);
    return max;
}

void __fastcall TAcadExport::DrawGrid(int step)
{
    for (int i = 0; i < curRoad->LMax; i += step) {
        AutoCAD.DrawLine(i, -RCenter - tableBottom.TableHeight, i, RCenter + tableTop.TableHeight);
        AutoCAD.DrawText(IntToStr((i / 100) % 1000), 3 * UnderTextHeight, 0,
                         i + UnderTextYOffset, RCenter - UnderTextYOffset - 3 * UnderTextHeight);
    }

}

void TAcadExport::ExportRuler(int iStart, int iEnd, bool fEnd)
{
    if (fEnd) {
        return;
    }

    iStart = iStart / 100000;
    iEnd = iEnd / 100000 + 1;

    for (int i = iStart; i < iEnd; i++) {
        AutoCAD.SetAttribute(AutoCAD.DrawBlock("Ruler", i * 100000, tableTop.LeftTop.y - tableTop.TableHeight), "START", IntToStr(i));
    }
}

bool __fastcall TAcadExport::ExportRoadCover(TExtPolyline *p, TRoadPart *t, bool fEnd)
{
    if (fEnd) return true;
    AcadPolylinePtr pl[1];
    
    AnsiString strParams;
    AnsiString name;
    AnsiString hatchFill = "SOLID";
    unsigned char Color[3] = {0, 0, 0};
    int idSurface = t->GetPropValue("Surface").ToInt();

    switch (idSurface) {
    case 233:    //Цементобетон
        Color[0] = Color[1] = Color[2] = 240;
        strParams = "$c\tANGLE\t15\t251"; // заливка тип масштаб цвет
        name = "цементобетон";
        hatchFill = "ANGLE";
        break;

    case 234:   // Асфальтобетон
        Color[0] = 196;
        Color[1] = 220;
        Color[2] = 220;
        strParams = "$c\tSOLID\t15\t161"; // заливка тип масштаб цвет
        name = "асфальтобетон";
        break;

    case 235:   // щебень укреп
        Color[0] = 244;
        Color[1] = 200;
        Color[2] = 128;
        strParams = "$c\tGRAVEL\t15\t43"; // заливка тип масштаб цвет
        hatchFill = "GRAVEL";
        name = "щебень (гравий)";
        break;

    case 236:  // щебень
        Color[0] = 220;
        Color[1] = 220;
        Color[2] = 180;
        strParams = "$c\tGRAVEL\t15\t43"; // заливка тип масштаб цвет
        hatchFill = "GRAVEL";
        name = "щебеночное (гравийное)";
        break;

    case 237:  // грунтовое
        Color[0] = 196;
        Color[1] = 220;
        Color[2] = 220;
        strParams = "$c\tGRAVEL\t15\t161"; // заливка тип масштаб цвет
        hatchFill = "GRAVEL";
        name = "грунтовое";
        break;

    case 238:
        Color[0] = 220;
        Color[1] = 220;
        Color[2] = 180;
        strParams = "$c\tSOLID\t15\t254"; // заливка тип масштаб цвет
        name = "прочее";
        break;
    }

    pl[0] = DrawPolyPoints(p, false, true);
    AcadHatchPtr hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, WideString(hatchFill));
    pl[0]->Erase();
    AcadAcCmColor *color =  hatch->TrueColor;

    color->SetRGB(Color[0], Color[1], Color[2]);
    hatch->TrueColor = color;

    if (~iBottomSurface) {
        ExportAddRowLine(&tableBottom, iBottomSurface, t->LMin, t->LMax, strParams);
        ExportAddRowLine(&tableBottom, iBottomSurface, t->LMin, t->LMax, name);
    }
    return true;
}

bool __fastcall TAcadExport::ExportTown(TExtPolyline *p, TTown *t, bool fEnd)
{
    if (fEnd) return true;
    AcadPolylinePtr pl[1];
    pl[0] = DrawPolyPoints(p, false, true);
    AcadHatchPtr hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, L"SOLID");
    pl[0]->Erase();
    AcadAcCmColor *color =  hatch->TrueColor;
    color->SetRGB(225, 225, 225);
    hatch->TrueColor = color;
    return true;
}

bool __fastcall TAcadExport::ExportPlan(TExtPolyline *p, TLinearRoadSideObject *t, int kind, bool fEnd)
{
    if (fEnd) {
        return true;
    }   // 2385239
    if (kind >= 2385228 && kind <= 2385239) {  /*рисуем площадные объекты*/
        AcadPolylinePtr pl[1];
        int scale = 50;
        int rotate = 0;
        bool fErasePolyline = true;
        pl[0] = DrawPolyPoints(p, false, true);
        AnsiString fillType = "";
        unsigned char Color[3];

        switch (kind) {
        case 2385228:  //Берег
            fillType = "";
            Color[0] = 185;
            Color[1] = 255;
            Color[2] = 255;
            scale = 400;
            break;

        case 2385229:  //Болото
            fillType = "DASH";
            Color[0] = 202;
            Color[1] = 227;
            Color[2] = 174;
            scale = 200;
            break;

        case 2385230:  //Лес
            fillType = "GRASS";
            Color[0] = 208;
            Color[1] = 255;
            Color[2] = 208;
            scale = 150;
            rotate = 180;
            break;

        case 2385231:  //Кустарник
            fillType = "GRASS";
            Color[0] = 208;
            Color[1] = 255;
            Color[2] = 208;
            scale = 100;
            break;

        case 2385232:  //Пашня
            fillType = "";
            Color[0] = 240;
            Color[1] = 240;
            Color[2] = 240;
            //fErasePolyline = false;
            break;

        case 2385233:  //Луг
            fillType = "";
            Color[0] = 208;
            Color[1] = 255;
            Color[2] = 208;
            break;
        case 2385239: // газон
            fillType = "";
            Color[0] = 64;
            Color[1] = 255;
            Color[2] = 0;
            break;
        }


        AcadHatchPtr hatch;
        hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, "SOLID");
        SetObjectColor(hatch, Color[0], Color[1], Color[2]);
        if (!fillType.IsEmpty()) {
            hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, fillType);
            SetObjectColor(hatch, 0, 0, 0);
            hatch->PatternScale = scale;
            if (rotate) {
                hatch->set_PatternAngle((float)rotate / 180 * M_PI);
            }
        }
        if (fErasePolyline) pl[0]->Erase();

    } else if (kind == 2385108 || kind == 2385224 || // Линия застройки
               kind == 2385225 || kind == 2385248 || // Забор деревянный, Забор металлический
               kind == 2385249 || kind == 2385250) { // Квартал жилой, Квартал нежилой,  Квартал
        AcadPolylinePtr pl;
        unsigned char Color[3];

        if (kind == 2385108) { // Линия застройки
            Color[0] = 255, Color[1] = 0, Color[2] = 255;
        } else if (kind == 2385224 || kind == 2385225) { // Забор деревянный, Забор металлический
            Color[0] = 134, Color[1] = 94, Color[2] = 94;
        } else if (kind == 2385248 || kind == 2385249 || kind == 2385250) { // Квартал жилой, Квартал нежилой,  Квартал
            Color[0] = 94, Color[1] = 132, Color[2] = 112;
        }

        pl = DrawPolyPoints(p, false, false);
        if (pl) {
           SetObjectColor(pl, Color[0], Color[1], Color[2]);
        }
    }
    return true;
}

bool __fastcall TAcadExport::ExportCommunication(TExtPolyline *p, TCommunication *t, bool fEnd )
{
    if (fEnd) return true;
    AcadPolylinePtr pl;
    switch (t->CommKind) {
    case 2385262: // трамвайные пути
        pl = DrawPolyPoints(p);
        /*for(int i=0;i<p->Count-1;i++){
            DrawBlockOnLine("train-lines", p->Points[i], p->Points[i+1], "Length VerticalLineLength");
        }*/
        if (pl.IsBound()) {
            pl->set_Linetype(WideString("trainpath"));
            pl->set_LinetypeScale(ScaleY / 0.2);
        }
        break;
    default:
        pl = DrawPolyPoints(p);
        pl->set_Linetype(WideString("linedash_1"));
        pl->set_Lineweight(acLnWt030);
    }
    return true;
}

bool __fastcall TAcadExport::ExportTrafficLight(TExtPolyline *p, vector<TTrafficLight*> &trafficLights, bool fEnd )
{
    if (fEnd) return true;
    static float rotation;
    if (fEnd) {
        return true;
    }

    if (~iStart) {
        if (p->Points[0].x < iStart) return true;
    }
    if (~iEnd) {
        if (p->Points[0].x > iEnd) return true;
    }

    for (int i = 0; i < trafficLights.size(); ++i) {
        TTrafficLight* t = trafficLights[i];
        rotation = -(float)t->Direction / 180.0 * M_PI;
        AnsiString blockKind = "";
        switch (t->Kind) {
        case tlkT: blockKind = "T"; break;
        case tlkTl: blockKind = "T_l"; break;
        case tlkTr: blockKind = "T_r"; break;
        case tlkTrl: blockKind = "T_rl"; break;
        case tlkP: blockKind = "TP"; break;
        case trlkTR: blockKind = "TR"; break;  //2385256
        }

        float scale = ScaleYBlock / 2;
        AcadBlockReferencePtr block
            = AutoCAD.DrawBlock("light", p->Points[0].x, -ScaleY * p->Points[0].y, rotation, scale);
        if (block.IsBound()) {
            AutoCAD.SetPropertyListVariant(block, "Type", blockKind);
            /*if(!exist) {
                block->color = NotExistColor;
            } */
        } else {
            return false;
        }
    }

    return true;
}

bool __fastcall TAcadExport::ExportDefect(TExtPolyline *p, TRoadDefect *d, bool fEnd) 
{
    if (fEnd) {
        return true;
    }

    switch(d->Kind) {
        //дефекты в виде участков дорог
        case dk12:
        case dk83:
        case dk84:
        case dk88:
        case dk89:
        case dk85:
        // case dk3: // гребенка не нужна
        case dk95:
        // case dk16: // колейность не нужна
        // Выбоины ямы заплаты
        case dk2: 
        case dk56: 
        case dk94: 
        {
            AcadPolylinePtr pl[1];
            int scale = 25 * (float)ScaleY / 0.8;
            int rotate = 0;
            bool fErasePolyline = true;
            pl[0] = DrawPolyPoints(p, false, true);
            AnsiString fillType = "";
            unsigned char Color[3];

            AcadHatchPtr hatch;
            String hatchFill = "ANSI37";
            switch (d->Kind) {
                case dk2: 
                case dk56: 
                case dk94: 
                    hatchFill = "SOLID";
                break;
            }
            hatch = AutoCAD.FillArea((IDispatch**)pl, 1, 0, hatchFill);
            hatch->PatternScale = scale;
            SetObjectColor(hatch, 255, 0, 0);
            SetObjectColor(pl[0], 255, 0, 0);
            }
            break;
        case dk67: {
            AcadPolylinePtr pl[1];
            pl[0] = DrawPolyPoints(p, false, false);
            SetObjectColor(pl[0], 255, 0, 0);
        }
    }
    

    return true;
}


#endif // WITHOUT_AUTOCAD

