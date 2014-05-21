SET NOCOUNT ON 
DECLARE @NumRoad int, @NumDataSource int

SELECT @NumRoad = 492, @NumDataSource = $(NumDataSource) --(3746,2568,2061)

SELECT @NumRoad = NumRoad
FROM ListDataSources
WHERE id_ = @NumDataSource

SELECT cast(T.StartPos*100 as int) [Начало], cast(T.EndPos*100 as int) [Конец],
	ISNULL(MP_M1, '') + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MP_H1)), '') + ', ' +
	ISNULL(MP_M2, '')  + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MP_H2)), '') + ', ' +
	ISNULL(MP_M3, '')  + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MP_H3)), '') + ', ' +

	ISNULL(MO_M1, '')  + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MO_H1)), '')
	/*ISNULL(MO_M2, '')  + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MO_H2)), ''),
	ISNULL(MO_M3, '') + ' ' + 
	ISNULL(convert(varchar(10), convert(int, MO_H3)), ''),

	ISNULL(MD_M1, ''),
	ISNULL(convert(varchar(10), convert(int, MD_H1)), ''),
	ISNULL(MD_M2, ''),
	ISNULL(convert(varchar(10), convert(int, MD_H2)), ''),

	RoadConstruction*/
FROM (
SELECT StartPos, EndPos,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 1 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MP_M1,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 1 then RD.Height else NULL end) MP_H1,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 2 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MP_M2,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 2 then RD.Height else NULL end) MP_H2,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 3 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MP_M3,
	max(case when RD.NumTypeRDLayer = 254 and RD.LayerNumber = 3 then RD.Height else NULL end) MP_H3,

	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 1 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MO_M1,
	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 1 then RD.Height else NULL end) MO_H1,
	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 2 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MO_M2,
	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 2 then RD.Height else NULL end) MO_H2,
	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 3 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MO_M3,
	max(case when RD.NumTypeRDLayer = 255 and RD.LayerNumber = 3 then RD.Height else NULL end) MO_H3,

	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 1 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MD_M1,
	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 1 then RD.Height else NULL end) MD_H1,
	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 2 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MD_M2,
	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 2 then RD.Height else NULL end) MD_H2,
	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 3 then rtrim(ISNULL(M.FullTitle, RD.NumMaterial)) else NULL end) MD_M3,
	max(case when RD.NumTypeRDLayer = 256 and RD.LayerNumber = 3 then RD.Height else NULL end) MD_H3,
	max(rtrim(Cst.FullTitle)) RoadConstruction
FROM CharactRoadDressing RD
LEFT JOIN ListMaterials M ON M.id_ = RD.NumMaterial
LEFT JOIN Classifier Cst ON Cst.id_ = RD.NumRDConstruction
WHERE RD.NumRoad = @NumRoad
	and RD.NumDataSource = @NumDataSource
GROUP BY RD.StartPos, RD.EndPos
) T
ORDER BY T.StartPos


--select * from CharactRoadDressing RD where RD.NumDataSource = 2061 and RD.NumTypeRDLayer = 254 and RD.LayerNumber = 2 

--update RD set NumMaterial = 2297 from CharactRoadDressing RD where RD.NumDataSource = 2061 and RD.NumTypeRDLayer = 254 and RD.LayerNumber = 2 