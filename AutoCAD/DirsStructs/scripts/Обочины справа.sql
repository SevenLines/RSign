SET NOCOUNT ON 
DECLARE @NumRoad int, @NumDataSource int

SELECT  @NumDataSource = $(NumDataSource) --(3746,2568)

SELECT cast(T.StartPos*100 as int) [Начало], cast(T.EndPos*100 as int) [Конец], cast(T.RW1 as decimal(6,1))
FROM (
SELECT L.StartPos, L.EndPos, rtrim(CS.Fulltitle) Place, 
	max(case when C.NumTypeStrengthening in (93, 88) then C.RowWidth else 0 end) RW1,
	max(case when C.NumTypeStrengthening = 94 then C.RowWidth else 0 end) RW2,
	max(case when C.NumTypeStrengthening = 1077522 then C.RowWidth else 0 end) RW3,
	max(case when C.NumTypeStrengthening not in (93, 88, 94, 1077522) then C.RowWidth else 0 end) RW4
FROM ListRoadSides L
JOIN CharactRoadSides C ON C.NumRoadSide = L.id_
JOIN Classifier CS ON CS.id_ = L.NumPlace
WHERE NumDataSource = @NumDataSource and L.NumPlace = 258
GROUP BY L.StartPos, L.EndPos, CS.Fulltitle
) T
ORDER BY T.StartPos, T.Place

