DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3746/*$*/

-- точки промежутков
SELECT DISTINCT IDENTITY(int) as id, p
 INTO #t 
FROM (
	SELECT StartPos as p, NumPartType, NumDataSource 
	FROM ListRoadParts
	UNION
	SELECT EndPos, NumPartType, NumDataSource
	FROM ListRoadParts
) t
WHERE NumDataSource = @NumDataSource
	and NumPartType = 37

SELECT i1.p as l, i2.p as r
 INTO #intervals
FROM #t i1
 JOIN #t i2 ON i2.id - i1.id = 1

-- интервал -> значение
SELECT l, r, max(Value1) as v
 INTO #out
FROM #intervals i
 LEFT JOIN ListRoadParts lrp ON lrp.StartPos <= i.l and i.r <= lrp.EndPos
WHERE NumDataSource = @NumDataSource
	and NumPartType = 37
GROUP BY l, r

-- убираю повторы
SELECT cast(l*100 as int), cast(r*100 as int), v
FROM (
	SELECT isnull(l, (SELECT min(p) FROM #t)) as l, r, v
		FROM (
		SELECT l, max(r) as r, v
		FROM (
			SELECT max(o2.r) as l, o1.r, o1.v
			FROM #out o1
			 LEFT JOIN #out as o2 ON o1.v <> o2.v and o2.l < o1.l
			GROUP BY o1.r, o1.v
		) t
		GROUP BY l, v
	) t
) t
ORDER BY l

DROP TABLE #out
DROP TABLE #t 
DROP TABLE #intervals