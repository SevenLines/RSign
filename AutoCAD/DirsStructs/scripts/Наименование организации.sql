SET NOCOUNT ON 
SELECT cast(StartPos * 100 as int), cast(EndPos * 100 as int), '$(Organization)'
FROM ListRoadParts
WHERE NumDataSource = $(NumDataSource) and NumPartType = 33

