SET NOCOUNT ON 

DECLARE @NumRoad int, @NumDataSource int

SELECT @NumRoad = 492, @NumDataSource = $(NumDataSource) --(3746,2568)

SELECT @NumRoad=NumRoad
FROM ListDataSources
WHERE id_ = @NumDataSource

CREATE TABLE #Positions (id_ int identity(1,1), Pos numeric(10,2))

INSERT INTO #Positions (Pos)
SELECT StartPos
FROM ListRoadSides 
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
UNION
SELECT EndPos 
FROM ListRoadSides 
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
UNION
SELECT StartPos
FROM ListRoadParts 
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
	and NumPartType = 14
UNION	
SELECT EndPos	
FROM ListRoadParts 	
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
	and NumPartType = 14
UNION
SELECT StartPos
FROM ListRoadParts 
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
	and NumPartType = 13
UNION	
SELECT EndPos	
FROM ListRoadParts 	
WHERE NumRoad = @NumRoad
	and NumDataSource = @NumDataSource
	and NumPartType = 13
ORDER BY 1	

SELECT P.Pos StartPos, P1.Pos EndPos	
 INTO #Parts	
FROM #Positions P	
JOIN #Positions P1 ON P.id_ + 1  = P1.id_	


SELECT P.StartPos, P.EndPos, LRP.Value2 RoadWidth,
	ISNULL(S.SideWidth, 0) SideWidth,
	rtrim(CSF.Fulltitle) Surface,
	(P.EndPos - P.StartPos) * LRP.Value2 Area,
	ISNULL(100.0*
		(select sum(DP2.ParamVal)
		from av_Defect_Registry D2
		join av_defregparams DP2 ON DP2.DefReg_id = D2.id_
					and DP2.Param_id = 30
		where D2.NumRoad = @NumRoad
			and D2.NumDataSource = @NumDataSource
			and D2.Defect_id = 2
			and D2.StartPos between P.StartPos and P.EndPos)/((P.EndPos - P.StartPos) * LRP.Value2),
	0) DefPerc2,
	ISNULL(100.0*
		(select sum(case DP1.Param_id when 30 then DP1.ParamVal when 31 then DP1.ParamVal * (D1.EndPos - D1.StartPos) else 0 end)
		from av_Defect_Registry D1
		join av_defregparams DP1 ON DP1.DefReg_id = D1.id_
					and DP1.Param_id = 30
		where D1.NumRoad = @NumRoad
			and D1.NumDataSource = @NumDataSource
			and D1.StartPos between P.StartPos and P.EndPos)/((P.EndPos - P.StartPos) * LRP.Value2),
	0) DefPerc
  INTO #Surface
FROM #Parts P
LEFT JOIN ListRoadParts SF ON SF.NumRoad = @NumRoad
			and SF.NumDataSource = @NumDataSource
			and SF.NumPartType = 13
			and (P.StartPos >= SF.StartPos and P.StartPos < SF.EndPos)
LEFT JOIN Classifier CSF ON CSF.id_ = SF.Reference
LEFT JOIN ListRoadParts LRP ON LRP.NumRoad = @NumRoad
			and LRP.NumDataSource = @NumDataSource
			and LRP.NumPartType = 14
			and (P.StartPos >= LRP.StartPos and P.StartPos < LRP.EndPos)
LEFT JOIN (select L.StartPos, L.EndPos, sum(C.RowWidth) SideWidth
	from ListRoadSides L
	join CharactRoadSides C ON C.NumRoadSide = L.id_
	where L.NumRoad = @NumRoad
		and L.NumDataSource = @NumDataSource
		and C.NumTypeStrengthening in (93, 88)
	group by L.StartPos, L.EndPos) S ON (P.StartPos >= S.StartPos and P.StartPos < S.EndPos)


SELECT cast(T.StartPos*100 as int) [Начало], cast(T.EndPos*100 as int)[Конец], cast(T.RoadWidth + T.SideWidth as decimal(6,1))
FROM #Surface T
ORDER BY T.StartPos



DROP TABLE #Positions
DROP TABLE #Parts
DROP TABLE #Surface

