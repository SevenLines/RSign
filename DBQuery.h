#ifndef DBQueryH
#define DBQueryH

const char ListMetricsLoad[]="select * from ELEM_ListMetrics where NumRoad=$NumRoad$ and \
    NumDataSource=$NumSource$ order by NumLine";
const char MetricsLoad[]="select cast(L*100+0.5 as integer) as L, cast(X*100+0.5 as integer) as X,\
    NumLine, Code, NumPoint, LeepPar, BasePar1, BasePar2 from ELEM_Metrics where NumRoad=$NumRoad$\
    and NumDataSource=$NumSource$ order by NumLine,NumPoint";
const char MetricsDelete[]="delete from ELEM_Metrics where NumLine=$NumLine$";
const char ListMetricsDelete[]="delete from ELEM_ListMetrics where NumLine=$NumLine$";
const char ListMetricsSave[]="update ELEM_ListMetrics SET LCount=$PolyCount$ where NumLine=$NumLine$";
const char ListMetricsAppend[]="insert into ELEM_ListMetrics (NumRoad,LCount,NumDataSource)\
     VALUES ($NumRoad$, $PolyCount$, $NumSource$) select @@IDENTITY as 'Identity'";
const char MetricsAppend[]="insert into ELEM_Metrics (NumRoad, NumLine, NumPoint, L, X, Code,LeepPar,BasePar1,BasePar2,NumDataSource)\
    VALUES ($NumRoad$,$NumLine$,$PolyNum$,$PolyL$/100.0,$PolyX$/100.0,$PolyCode$,$PolyLeep$,$PolyBase1$,$PolyBase2$,$NumSource$)";
const char DocumentLoad[]="select RD.doc_id as DocId,RD.doc_name as Name, RD.doc_path as Path, RS.s_path as Driver, RD.doc_object as ObjId, RD.doc_celement as DictId from RDocuments RD left join RServers RS on RD.doc_serv=RS.s_id where doc_road=$NumRoad$ and NumDataSource=$NumSource$";
const char ProfilLoad[]="select NumRoad,cast(Displacement*100+0.5 as integer) as L,cast(X_pr*100+0.5 as integer) as X,cast(Y_pr*100+0.5 as integer) as Y,cast(Z*100+0.5 as integer) as Z,LongSlope, LeftSlope, RightSlope, RightRadius, LeftRadius from RoadGeometry where NumRoad=$NumRoad$\
    and NumDataSource=$NumSource$ order by L";
const char BlobProfilLoad[]="select NumRoad,Displacement as L,X_pr as X,Y_pr as Y,Z,LongSlope, LeftSlope, RightSlope, RightRadius, LeftRadius from RoadGeometryBlob where NumRoad=$NumRoad$\
    and NumDataSource=$NumSource$";    
const char ProfilCount[]="select count(*) as c from RoadGeometry where NumRoad=$NumRoad$ and NumDataSource=$NumSource$";

const char HighDistinct[]="select distinct id_high, direction from vi_points where id_road=$NumRoad$ and NumDataSource=$NumSource$";

const char HighLoad[]="select id_high,cast(PosOfSVPD*100 as integer) as PosOfSVPD,\
    cast(PosOfInv*100 as integer) as PosOfInv,Direction from vi_points where id_road=$NumRoad$ and NumDataSource=$NumSource$ order by PosOfInv";
#endif
