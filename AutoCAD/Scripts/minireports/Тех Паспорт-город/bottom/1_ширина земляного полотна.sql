DECLARE @NumRoad int, @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- источник дороги << главное  поле
SELECT @NumRoad = /*$NumRoad*/3749/*$*/ -- источник дороги << главное  поле

DECLARE @RoadStart int, @RoadEnd int

SELECT @RoadStart = round(StartPos, 0), @RoadEnd = round(EndPos, 0)
FROM ListRoadParts
WHERE NumPartType = 33
    and NumRoad = @NumRoad
    and NumDataSource = @NumDataSource

SELECT convert(int, round(StartPos, 0)) StartPos, convert(int, round(EndPos, 0)) EndPos,
    Reference NumTCategory, 
    (case Reference 
        when 193 then 6
        when 194 then 4.5
    else NULL
    end) RoadWidth
 INTO #TCategory 
FROM ListRoadParts
WHERE NumPartType = 1 and NumRoad = @NumRoad and NumDataSource = 0


SELECT convert(int, round(LRP.StartPos, 0)) StartPos, convert(int, round(LRP.EndPos, 0)) EndPos, 
    LRP.Reference Surf, rtrim(C.FullTitle) SurfTitle
 INTO #Surf
FROM ListRoadParts LRP
JOIN Classifier C ON C.id_ = LRP.Reference
WHERE LRP.NumPartType = 13
    and LRP.NumRoad = @NumRoad
    and LRP.NumDataSource = @NumDataSource


SELECT convert(int, round(StartPos, 0)) StartPos, convert(int, round(EndPos, 0)) EndPos, 
    round(Value2, 1) Width
 INTO #RoadWidth
FROM ListRoadParts
WHERE NumPartType = 14
    and NumRoad = @NumRoad
    and NumDataSource = @NumDataSource
    

SELECT convert(int, round(S.StartPos, 0)) StartPos, convert(int, round(S.EndPos, 0)) EndPos,
    S.NumPlace, S.Width 
  INTO #Sides
FROM ListRoadSides S
WHERE S.NumRoad = @NumRoad
    and S.NumDataSource = @NumDataSource

CREATE TABLE #Points (id_ int identity(1,1), Point int)

INSERT INTO #Points (Point)
SELECT @RoadStart Point UNION SELECT @RoadEnd UNION
SELECT StartPos FROM #TCategory UNION
SELECT EndPos FROM #TCategory UNION
SELECT StartPos FROM #Surf UNION
SELECT EndPos FROM #Surf UNION
SELECT StartPos FROM #RoadWidth UNION
SELECT EndPos FROM #RoadWidth UNION
SELECT StartPos FROM #Sides UNION
SELECT EndPos FROM #Sides

ORDER BY 1

DELETE FROM #Points WHERE Point < @RoadStart or Point > @RoadEnd


SELECT P.StartPos * 100, P.EndPos * 100,
    cast(W.Width + SL.Width + SR.Width as float) [Зем. полотно]
FROM 
(
  SELECT L.Point StartPos, R.Point EndPos
  FROM #Points L
  JOIN #Points R ON L.id_ = R.id_ - 1
) P
LEFT JOIN #TCategory C ON P.StartPos >= C.StartPos
            and P.StartPos < C.EndPos
LEFT JOIN #Surf S ON P.StartPos >= S.StartPos
            and P.StartPos < S.EndPos
LEFT JOIN #RoadWidth W ON P.StartPos >= W.StartPos
            and P.StartPos < W.EndPos
LEFT JOIN #Sides SL ON P.StartPos >= SL.StartPos
            and P.StartPos < SL.EndPos
            and SL.NumPlace = 257
LEFT JOIN #Sides SR ON P.StartPos >= SR.StartPos
            and P.StartPos < SR.EndPos
            and SR.NumPlace = 258
WHERE W.Width + SL.Width + SR.Width is not NULL
ORDER BY 1, 2

DROP TABLE #TCategory 
DROP TABLE #Surf
DROP TABLE #RoadWidth
DROP TABLE #Sides
DROP TABLE #Points
