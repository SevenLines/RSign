DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- источник дороги << главное  поле

SELECT Displacement*100, case NumPlace when 257 then 50 else 150 end, '$b', 'lamp','style=Одиночный'
FROM ListRoadLamps
WHERE NumDataSource = @NumDataSource
