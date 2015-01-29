SELECT	cast(StartPos * 100 as int), cast(EndPos *100 as int), cast(Value2 as float)
FROM ListRoadParts l
WHERE NumDataSource = /*$NumDataSource*/3766/*$*/ and NumPartType = 14