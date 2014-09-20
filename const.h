//---------------------------------------------------------------------------

#ifndef ConstH         
#define ConstH
//---------------------------------------------------------------------------
// Cобщения
// Данные перезагружены. Lparam содержит идентификатор дороги
#define CM_DATARELOAD WM_USER+1
// Объект будет удален Wparam содержит указатель на объект,
// Lparam - номер дороги
#define CM_REMOVEOBJ  WM_USER+2
// Добавлен объект
// Wparam содержит указатель на объект, Lparam - номер дороги
#define CM_INSERTOBJ WM_USER+3
// поля объекта были изменены
// Wparam содержит указатель на объект, Lparam - номер дороги
#define CM_UPDATEOBJ WM_USER+4
// Изменен флажок видимости класса объектов
// LParam - номер дороги
#define CM_CHANGEVIS WM_USER+5
// Изменен поле Selected у объекта
// WParam - содержит указатель на объект,
// LParam - номер дороги
#define CM_CHANGESEL WM_USER+6
// Снято выделение со всех объектов
//
// LParam - номер дороги
#define CM_SELECTOFF WM_USER+7
// Выделена группа объектов
//
// LParam - номер дороги
#define CM_SELECTGROUP WM_USER+8
// Показать объект
// WParam - указатель на объект
// LParam - номер дороги
#define CM_ACTIVATEOBJECT WM_USER+9
// Изменился источник назначения для операций копирования
// LParam - Указатель на источник
#define CM_CHANGECOPYDEST WM_USER+10
// Добавлена группа объетов
//
// Lparam - указатель на источник
#define CM_INSERTGROUP WM_USER+11
// Удалена группа объектов
//
// LParam - указатель на источник
#define CM_DELETEGROUP WM_USER+12
// Активирован объект
// WParam - указатель на объект
// LParam - источник данных
#define CM_ONACTIVATEOBJECT  WM_USER+13
// Активировано окно с планом дороги
// WParam - Указатель на TRoadFrm
#define CM_ONACTIVATEROADWIN WM_USER+14

// Для видео окна. Изменилась позиция видио
// LParam - источник данных
#define CM_CHANGEVIDEOPOSITION WM_USER+15
// Изменился статус проигрывателя (play pause)
// LParam - источник данных
#define CM_CHANGEVIDEOSTATUS WM_USER+16
// Изменился источник данных в окне видео
#define CM_CHANGEVIDEOSOURCE WM_USER+17
// Загружен новый источник данных
// LParam - источник данных
#define CM_OPENDATASOURCE WM_USER+18
// Закрыт источник данных
// Lparam - источник даннных
#define CM_CLOSEDATASOURCE WM_USER+19
//---------------------------------------------------------------------------
// Номера страниц
#define ROADMARKPAGE 4
#define DANGERPARTPAGE 8



//Коды объектов

#define MAXCODEID 128

// Обочина
#define ROADSIDECODE 29
#define SGNCODE 30

// Участок дороги по ширине
#define WIDTHCODE 45

// Разделительная полоса
#define DIVPARTCODE 46

// Дополнительная полоса
#define ADDPARTCODE 40

// Земляное полотно
#define ZEMPOLOTNOCODE 43

// Переезды
//#define RAILPASSCODE 16

//Автобусные остановки
#define BUSSTOPCODE 19

// Обочины
//#define OBJROADSIDECODE 18

//Населенные пункты
#define TOWNCODE 48

//Участки опасных уклонов
#define DANGERSLOPECODE 12

//Участки опасных поворотов
#define DANGERCURVECODE 52

//Участки с подсыпкой
#define DANGERPARTCODE 53

// Линии дороги (кромка бровка)
#define ROADMETRIC 51

// Точка измерения ширины
#define WIDTHMEASURECODE 64

#define ROADBOUNDCODE 61

// Мосты и трубы
#define ROADBRIDGECODE 18
#define ROADTUBECODE 42
#define ROADBARRIERCODE 16
#define ROADSIGNALCODE 17
#define ROADDRESSCODE 13
#define ROADMARKCODE 15
#define ROADATTACH 28
#define ROADCATEGORY 67

#define SIDEWALKCODE 59
#define RESTZONECODE 63
#define MOUNDHEIGHTCODE 70
#define ROADLAMPCODE 71
#define ROADBORDERCODE 72
#define ROADPLANCODE 66
#define TOWNCODE 48
#define ROADSURFACECODE 44
#define COMMUNICATIONCODE 20
#define VISMODECODE 73


//---------------------------------------------------------------------------
// Коды характиристик

//Наличие знака
#define SIGNEXCODE 1
enum TSignExist {seExist=2135088,seNotExist=2135089};

enum TLampKind {lkOnce=2385222,lkDouble=2385223};

// Направление расположения объекта (прямое - обратное)
//#define DIRCODE 3
enum TRoadDirection {roDirect=246,roUnDirect=247};

//#define ROADSIDECODE 5
enum TRoadSide {rsLeft=257,rsRight=258};

// Расположение примыкания
//#define ATCODE 6
enum TAttachPlacement {apLeft=257,apRight=258,apCross=261};

enum TCommunicationPlacement {cpLeft=257,cpRight=258,cpCross=261,cpCross2=262};
enum TGroundPlacement {gpOver=263,gpUnder=264};
enum TCommunicationKind {ckComm1=164,ckComm2=165,ckComm3=166,ckComm4=167,ckComm5=168,ckComm6=169,ckComm7=170};

enum TTubePlacement {tuRoad=0,tuLeft=257,tuRight=258,tuCross=262};

// Тех. категория дороги
//#define RCLCODE 7
enum TRoadClass {rc1a=188,rc1=189,rc1b=190,rc2=191,rc3=192,rc4=193,rc5=194,rcnone=0};
enum TRoadSurface {rs233=233,rs234=234,rs235=235,rs236=236,rs237=237,rs238=238};

enum TAttachWildness {awDefault=0,awWild=2385038,awCulture=2385039,awNeedCulture=2385040};


// Расположение знака : слева, справа, на разделительной полосе, над дорогой
//#define PLSGNCODE 8
enum TRoadSignPlacement {spLeft=257,spRight=258,spBetween=259,spUp=260};

enum TRoadSignalKind {skStolb=181,skTumba1=182,skTumba2=183,skOstrov=184};

enum TBarrierConstruction {br112=112,br113=113,br114=114,br115=115,br116=116,br117=117,br118=118,brm=1959537};

enum TLayer {lab=2385237,lcb=2385238};


// характеристика имени примыкания (текстовое)
//#define ATNAMECODE 9

// Направление расположения дорожного объекта (не знака)
//#define OBPLCODE 10
enum TObjPlacement {opLeft=257,opRight=258,opBetween=259};

//Вид препятствия для моста
//#define OBSTACLEKINDCODE 11
enum TObstacleKind {ok95=95,ok96=96,ok97=97,ok98=98,ok99=99,ok100=100,ok101=101,ok102=102,ok103=103};

//Имя препятствия для моста (строка)
//#define OBSTACLENAMECODE 12

//Схема моста (строка)
//#define BRIDGESHEMECODE 13

// Необходимость знака
//#define SIGNNESCODE 15
enum TSignTest {stGood=2135090,stBad=2135091,stUnknown=0};

// К чему относится знак
enum TSignAttach {saRoad=2117086,saOut=2117087,saIn=2117088};

enum TDrainageKind {dkLotok1=119,dkLotok2=120,dkKuvet1=121,dkKuvet2=122,dkDrainage1=123,
                    dkDrainage2=124,dkDrainage3=125,dkDrainage4=126,dkDrainage5=127,dkDrainage6=128};

enum TPermiss {tpYes=2385041,tpNo=2385042};

enum TCurveKind {ckLine=2385043,ckRightCurve=2385044,ckCircle=2385045,ckLeftCurve=2385089};

#define SIGNGOSTCODE 21
#define MARKKINDCODE 43
#define SIDESTRENGTHCODE 41
//#define SIGNGOSTCODE1 21
//#define SIGNGOSTCODE2 22
//#define SIGNGOSTCODE3 23
//#define SIGNGOSTCODE4 24
//#define SIGNGOSTCODE5 25
//#define SIGNGOSTCODE6 26
//#define SIGNGOSTCODE7 27

enum TBridgeKind {};
enum TBridgeConstruction {};
enum TBridgeMaterial {};

//Вид пересекаемого пути (для переезда)
//#define RAILTYPECODE 26


//Вид переездной сигнализации
//#define RAILCROSSSIGNALCODE 27
enum TRailKind {rtp1=2135092,rtp2=2135093,rtp3=2135094,rtp4=2135095};
enum TRailCrossSignal {rcsSigns=2135096,rcsMBlock=2135097,rcsEBlock=2135098,rcsABlock=2135099,rcsSound=2135100,rcsSemaphor=2135101};

enum TMetricsKind {mkKromka=2384959,mkBrovka=2384960,mkDivPart=2385157,mkKromkaLine=2385234,mkBrovkaLine=2385235,mkBoundLine=2385247};

enum TMarkKind {ma1=2384961,ma2_1=2385125,ma2_2=2384962,ma3=2384963,ma4=2384964,ma5=2384965,
    ma6=2384966,ma7=2384967,ma8=2384968,ma9=2384969,ma10=2384970,ma11l=2384971,ma11r=2385126,
    ma12=2384972,ma13=2384973,ma14_1=2384974,ma14_2=2384975,ma14_3=2384976,ma15=2384977,
    ma16_1=2384978,ma16_2=2384979,ma16_3=2384980,ma17=2384981,ma18p=2384982,
    ma18r=2384983,ma18l=2384984,ma18pr=2384985,ma18pl=2384986,ma18rl=2385131,ma18prl=2384987,
    ma19_1=2384988,ma19_2=2384989,ma20=2384990,ma21=2384991,ma22=2384992,ma23=2384993,
    ma24_1=2385127,ma24_2=2385128,ma24_3=2385129,ma25=2385130};

enum TTrafficLightsPlacement {tlpOpora=2385257,tlpConsol=2385258,tlpRast=2385259};
enum TTrafficLightsKind {tlkT=2385251,tlkTr=2385252,tlkTl=2385253,tlkTrl=2385254,tlkP=2385255,trlkTR=2385257};

#define MLLongLinesCount 16
const TMarkKind MLLongLines[MLLongLinesCount]={ma1,ma2_1,ma2_2,ma3,ma4,ma5,ma6,ma7,ma8,ma9,ma10,ma11l,ma11r,ma12,ma13,ma17};
#define MLCrossLinesCount 5
const TMarkKind MLCrossLines[MLCrossLinesCount]={ma14_1,ma14_2,ma14_3,ma15,ma25};
#define MLIslandsCount 3
const TMarkKind MLIslands[MLIslandsCount]={ma16_1,ma16_2,ma16_3};
#define MLArrowsCount 16
const TMarkKind MLArrows[MLArrowsCount]={ma18p,ma18l,ma18r,ma18pl,ma18pr,ma18rl,ma18prl,ma19_1,ma19_2,ma20,ma21,ma22,ma23,ma24_1,ma24_2,ma24_3};

class SetOfInt
{
private:
int Count;
int *Array;
public:
    __fastcall SetOfInt(int *array,int count)
        {Array=array;Count=count;}
bool __fastcall Elem(int x)
    {
    for (int i=0;i<Count;i++)
        if (Array[i]==x)
            return true;
    return false;
    }
};

extern  SetOfInt MarkLongLines;
extern  SetOfInt MarkCrossLines;
extern  SetOfInt MarkIslands;
extern  SetOfInt MarkArrows;


enum TLayerKind {};
enum TDressMaterial {};
/*  Дефекты
  1 - ступенька при сопр пр. части и обочины
  2 - Выбоины покрытия
  12 - Застой воды у кромки проезжей части и обочины
  56 - Ямы
  17 - Заросшие кюветы
  67 - Трещины
  83 - Участки обочин разрушенные
  84 - Участки одиночных трещин
  85 - Участки с сеткой трещин
  88 - Участки дорог разрушенные
  89 - Участки дорог с массовыми нарушениями покрытия
*/
enum TDefectKind {dk1=1+33554432,dk2=2+33554432,dk3=3+33554432,dk12=12+33554432,
    dk16=16+33554432,dk17=17+33554432,
    dk56=56+33554432,dk67=67+33554432,dk83=83+33554432,dk84=84+33554432,
    dk85=85+33554432,dk88=88+33554432,dk89=89+33554432,dk94=94+33554432,
    dk95=95+33554432,dk96=95+33554432};
// Число путей
//#define RAILWAYCOUNT 29

//Название автобусной остановки
//#define BUSSTOPNAMECODE 31

//Виды укреплений обочин
//#define ROADSIDESTRENGTHCODE 32

//Название населенного пункта
//#define TOWNNAMECODE 33

enum TScaleKind {skByX=0,skByL=1};

enum TDangPartKind {dpNoVal=0,dpUnKnown=1,dpBusStop=2,dpCurve=3,dpSlope=4,dpAttach=5};

class TLoadableConstants
{
private:
int FPGMBusStopWidth;
int FPGMBusStopLength;
int FPGMAttachWidth[6];
int FPGMAttachLength[6];
int FPGMRoadWidth[6];
int GetPgmAttachWidth(int n)
    { return (n>=0)&&(n<6) ? FPGMAttachWidth[n] : FPGMAttachWidth[5];}
int GetPgmAttachLength(int n)
    { return (n>=0)&&(n<6) ? FPGMAttachLength[n] : FPGMAttachLength[5];}
int GetPgmRoadWidth(int n)
    { return (n>=0)&&(n<6) ? FPGMRoadWidth[n] : FPGMRoadWidth[5];}
public:
__property int PGMBusStopWidth={read=FPGMBusStopWidth};
__property int PGMBusStopLength={read=FPGMBusStopLength};
__property int PGMAttachWidth[int]={read=GetPgmAttachWidth};
__property int PGMAttachLength[int]={read=GetPgmAttachLength};
__property int PGMRoadWidth[int]={read=GetPgmRoadWidth};
};



#endif
