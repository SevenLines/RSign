DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- источник дороги << главное  поле

DECLARE @NumRoad int
DECLARE @l int, @r int, @max_ob_v float
DECLARE @mul int

SELECT @l = -1, @r = -1 -- явные границы участка слева и справа
SELECT @mul = 100 -- множитель границ т.е если значение 100 то границы будут увиличены в 100 раз
SELECT @max_ob_v = 5 -- максимальная ширина обочины, как правило сильно большие значению означают наличие моста

SELECT @r = case when @r <= 0 or @r - @l < 0 then 99999999 else @r end
SELECT @l = case when @l < 0 or @r - @l < 0 then -99999999 else @l end

SELECT @NumRoad = NumRoad
FROM ListDataSources
WHERE id_ = @NumDataSource

SELECT IDENTITY(int) as id, pos
 INTO #t1
FROM (
	SELECT DISTINCT pos
	FROM (
		SELECT StartPos as pos, NumPartType, NumDataSource, NumRoad
		FROM ListRoadParts
		UNION
		SELECT EndPos, NumPartType, NumDataSource, NumRoad
		FROM ListRoadParts
	) t
	WHERE (NumPartType in (13,14) and NumDataSource = @NumDataSource ) 
			or (NumPartType = 1 and NumDataSource = 0 and NumRoad = @NumRoad)
) t

SELECT t1.pos as l, t1_.pos as r
 INTO #intervals2
FROM #t1 t1
 LEFT JOIN #t1 t1_ ON t1_.id - t1.id = 1

SELECT cast(l as int)*@mul as 'проезжая ext', cast(r as int)*@mul as r, cast(w as varchar(10))+'('+cast(rs as varchar(10))+')-'+rtrim(surf) as info
FROM (
	SELECT l, r, cast(p.Value2 as float) as w, c.FullTitle surf
		, round(cast(case cat.Reference when 188 then 3.75*4 
				when 189 then p.Value2 / 3.75
				when 190 then p.Value2 / 3.75
				when 191 then p.Value2 / 3.75
				when 192 then p.Value2 / 3.5
				when 193 then p.Value2 / 3
				when 194 then 1
				else p.Value2 / 3 end as float),0) as rs
	FROM #intervals2 i
	 LEFT JOIN ListRoadParts p ON p.StartPos <= i.l and i.r <= p.EndPos and isnull(p.NumPartType,14) = 14
	 LEFT JOIN ListRoadParts cat ON cat.StartPos <= i.l and i.r <= cat.EndPos and isnull(cat.NumPartType,1) = 1
	 LEFT JOIN ListRoadParts s ON s.StartPos <= i.l and i.r <= s.EndPos and isnull(s.NumPartType,13) = 13
	 LEFT JOIN Classifier c ON c.id_ = s.Reference
	WHERE	s.NumDataSource = @NumDataSource 
			and p.NumDataSource = @NumDataSource 
			and cat.NumRoad = @NumRoad and cat.NumDataSource = 0
) t
ORDER BY l

DROP TABLE #t1
DROP TABLE #intervals2
