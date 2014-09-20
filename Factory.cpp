//---------------------------------------------------------------------------


#pragma hdrstop

#include "Factory.h"
#pragma package(smart_init)
#include "RoadObj.h"
//---------------------------------------------------------------------------
TRoadObject* __fastcall TRoadObjFactory::CreateRoadObj(String ClassName,__int32 id,__int32 code)
{
if (ClassName==ClassesNames[0])
        return new TRoadObject(id,code);
else if (ClassName==ClassesNames[1])
        return new TDescreetRoadObject(id,code);
else if (ClassName==ClassesNames[2])
        return new TDescreetDirRoadObject(id,code);
else if (ClassName==ClassesNames[3])
        return new TDescreetSideRoadObject(id,code);
else if (ClassName==ClassesNames[4])
        return new TContRoadObject(id,code);
else if (ClassName==ClassesNames[5])
        return new TBusStop(id,code);
else if (ClassName==ClassesNames[6])
        return new TRoadSideObject(id,code);
else if (ClassName==ClassesNames[7])
        return new TLinearRoadSideObject(id,code);
else if (ClassName==ClassesNames[8])
        return new TSquareRoadSideObject(id,code);
else if (ClassName==ClassesNames[9])
        return new TRoadPart(id,code);
else if (ClassName==ClassesNames[10])
        return new TRoadBridge(id,code);
else if (ClassName==ClassesNames[11])
        return new TDangerPart(id,code);
else if (ClassName==ClassesNames[12])
        return new TDangerSlope(id,code);
else if (ClassName==ClassesNames[13])
        return new TDangerCurve(id,code);
else if (ClassName==ClassesNames[14])
        return new TRoadBridge(id,code);
else if (ClassName==ClassesNames[15])
        return new TSquareAttachObject(id,code);
else if (ClassName==ClassesNames[16])
        return new TTown(id,code);
else if (ClassName==ClassesNames[17])
        return new TRoadAttach(id,code);
else if (ClassName==ClassesNames[18])
        return new TCommRoadObject(id,code);
else if (ClassName==ClassesNames[19])
        return new TRailCross(id,code);
else if (ClassName==ClassesNames[20])
        return new TRoadSign(id,code);
else if (ClassName==ClassesNames[21])
        return new TRoadBarrier(id,code);
else if (ClassName==ClassesNames[22])
        return new TRoadMark(id,code);
else if (ClassName==ClassesNames[23])
        return new TRoadOut(id,code);
else if (ClassName==ClassesNames[24])
        return new TRoadTube(id,code);
else if (ClassName==ClassesNames[25])
        return new TCommunication(id,code);
else if (ClassName==ClassesNames[26])
        return new TObochina(id,code);
else if (ClassName==ClassesNames[27])
        return new TSquareCenterObject(id,code);
else if (ClassName==ClassesNames[28])
        return new TRoadObstacle(id,code);
else if (ClassName==ClassesNames[29])
        return new TCarePart(id,code);
else if (ClassName==ClassesNames[30])
        return new TDTP(id,code);
else if (ClassName==ClassesNames[31])
        return new TBandRoadPart(id,code);
else if (ClassName==ClassesNames[32])
        return new TRoadSignal(id,code);
else if (ClassName==ClassesNames[33])
        return new TDrainageObject(id,code);
else if (ClassName==ClassesNames[34])
        return new TZemPolotno(id,code);
else if (ClassName==ClassesNames[35])
        return new TRoadDress(id,code);
else if (ClassName==ClassesNames[36])
        return new TRoadDefect(id,code);
else if (ClassName==ClassesNames[37])
        return new TRoadDescription(id,code);
else if (ClassName==ClassesNames[38])
        return new TRoadWidthMeasure(id,code);
else if (ClassName==ClassesNames[39])
        return new TSquareRoadSideObject_Kromka(id,code);
else if (ClassName==ClassesNames[40])
        return new TLinearCenterRoadObject(id,code);
else if (ClassName==ClassesNames[41])
        return new TRoadCategory(id,code);
else if (ClassName==ClassesNames[42])
        return new TRoadLighting(id,code);
else if (ClassName==ClassesNames[43])
        return new TMoundHeight(id,code);
else if (ClassName==ClassesNames[44])
        return new TDivRoadPart(id,code);
else if (ClassName==ClassesNames[45])
        return new TDangerVisMode(id,code);
else if (ClassName==ClassesNames[46])
        return new TDressLayer(id,code);
else if (ClassName==ClassesNames[47])
        return new TDescreetCenterRoadObject(id,code);
else if (ClassName==ClassesNames[48])
        return new TMapObject(id,code);
else if (ClassName==ClassesNames[49])
        return new TTrafficLight(id,code);
return NULL;
}

String __fastcall TRoadObjFactory::GetClassInfo(String ClassName)
{
if (ClassName==ClassesNames[0])
        return RoadObjectInfo;
else if (ClassName==ClassesNames[1])
        return DescreetRoadObjectInfo;
else if (ClassName==ClassesNames[2])
        return DescreetDirRoadObjectInfo;
else if (ClassName==ClassesNames[3])
        return DescreetSideRoadObjectInfo;
else if (ClassName==ClassesNames[4])
        return ContRoadObjectInfo;
else if (ClassName==ClassesNames[5])
        return BusStopInfo;
else if (ClassName==ClassesNames[6])
        return LinearRoadSideObjectInfo;
else if (ClassName==ClassesNames[7])
        return SquareRoadSideObjectInfo;
else if (ClassName==ClassesNames[8])
        return RoadSideObjectInfo;
else if (ClassName==ClassesNames[9])
        return RoadPartInfo;
else if (ClassName==ClassesNames[10])
        return RoadBridgeInfo;
else if (ClassName==ClassesNames[11])
        return DangerPartInfo;
else if (ClassName==ClassesNames[12])
        return DangerSlopeInfo;
else if (ClassName==ClassesNames[13])
        return DangerCurveInfo;
else if (ClassName==ClassesNames[14])
        return RoadBridgeInfo;
else if (ClassName==ClassesNames[15])
        return SquareAttachObjectInfo;
else if (ClassName==ClassesNames[16])
        return TownInfo;
else if (ClassName==ClassesNames[17])
        return RoadAttachInfo;
else if (ClassName==ClassesNames[18])
        return CommRoadObjectInfo;
else if (ClassName==ClassesNames[19])
        return RailCrossInfo;
else if (ClassName==ClassesNames[20])
        return RoadSignInfo;
else if (ClassName==ClassesNames[21])
        return RoadBarrierInfo;
else if (ClassName==ClassesNames[22])
        return RoadMarkInfo;
else if (ClassName==ClassesNames[23])
        return RoadOutInfo;
else if (ClassName==ClassesNames[24])
        return RoadTubeInfo;
else if (ClassName==ClassesNames[25])
        return CommunicationInfo;
else if (ClassName==ClassesNames[26])
        return ObochinaInfo;
else if (ClassName==ClassesNames[27])
        return SquareCenterObjectInfo;
else if (ClassName==ClassesNames[28])
        return RoadObstacleInfo;
else if (ClassName==ClassesNames[29])
        return CarePartInfo;
else if (ClassName==ClassesNames[30])
        return DTPInfo;
else if (ClassName==ClassesNames[31])
        return BandRoadPartInfo;
else if (ClassName==ClassesNames[32])
        return RoadSignalInfo;
else if (ClassName==ClassesNames[33])
        return DrainageObjectInfo;
else if (ClassName==ClassesNames[34])
        return ZemPolotnoInfo;
else if (ClassName==ClassesNames[35])
        return RoadDressInfo;
else if (ClassName==ClassesNames[36])
        return RoadDefectInfo;
else if (ClassName==ClassesNames[37])
        return RoadDescriptionInfo;
else if (ClassName==ClassesNames[38])
        return RoadWidthMeasureInfo;
else if (ClassName==ClassesNames[39])
        return SquareRoadSide_KromkaInfo;
else if (ClassName==ClassesNames[40])
        return LinearCenterObjectInfo;
else if (ClassName==ClassesNames[41])
        return RoadCategoryInfo;
else if (ClassName==ClassesNames[42])
        return RoadLightingInfo;
else if (ClassName==ClassesNames[43])
        return MoundHeightInfo;
else if (ClassName==ClassesNames[44])
        return DivRoadPartInfo;
else if (ClassName==ClassesNames[45])
        return DangerVisModeInfo;
else if (ClassName==ClassesNames[46])
        return DressLayerInfo;
else if (ClassName==ClassesNames[47])
        return DescreetCenterRoadObjectInfo;
else if (ClassName==ClassesNames[48])
        return MapObjectInfo;
else if (ClassName==ClassesNames[49])
        return TrafficLightInfo;
return "";
}

TExtPolyline* __fastcall TRoadObjFactory::GetDefaultMetric(String ClassName,TRect &r)
{
TRoadObject *ro=CreateRoadObj(ClassName,0,0);
TExtPolyline *Poly=NULL;
if (ro)
switch (ro->GetLocal())
    {
    case locDescreet:
        {Poly=new TExtPolyline(1,0);
         (*Poly)[0].x=(r.Left+r.Right)>>1;
         (*Poly)[0].y=(r.Top+r.Bottom)>>1;
         }break;
    case locLinear:
        {
        Poly=new TExtPolyline(2,1);
        Poly->Codes[0]=0;
        int w=(r.Right-r.Left)>>2;
        int c=(r.Right+r.Left)>>1;
        (*Poly)[0].x=c-w;
        (*Poly)[1].x=c+w;
        (*Poly)[0].y=(*Poly)[1].y=(r.Top+r.Bottom)>>1;
        }break;
    case locSquare:
        {
        Poly=new TExtPolyline(4,1);
        int w=(r.Right-r.Left)>>2;
        int c=(r.Right+r.Left)>>1;
        (*Poly)[0].x=(*Poly)[3].x=c-w;
        (*Poly)[1].x=(*Poly)[2].x=c+w;
        w=(r.Bottom-r.Top)>>2;
        c=(r.Bottom+r.Top)>>1;
        (*Poly)[0].y=(*Poly)[1].y=c+w;
        (*Poly)[2].y=(*Poly)[3].y=c-w;
        }break;
    }
return Poly;
}
