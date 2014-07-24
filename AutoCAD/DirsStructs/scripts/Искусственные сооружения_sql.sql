DECLARE @NumDataSource int
SELECT @NumDataSource = 3742
SET NOCOUNT ON 
SELECT cast(Displacement*100 as int), 
100, 
'$b	tubeEx	style=vertical iLength:L='+cast(extent as varchar(10))
+ ' Position:' + dbo.pp_Km_mFormat(Displacement) 
+ ' DOut:' + TubeScheme
FROM ListTubes
WHERE NumDataSource = @NumDataSource
ORDER BY 1

SELECT cast(StartPos*100 as int),
case NumPlace when 257 then '50' else '150' end,
'$b	barBarrierMetal	Length=' + cast(cast((EndPos-StartPos)*100 as int) as varchar(10)) + ' ' + 
case NumPlace when 257 then 'Flip<1' else '' end
FROM ListBarriers
WHERE NumDataSource = @NumDataSource and NumTypeGuidingStructure = 0
ORDER BY 1

SELECT cast(Displacement*100 as int),
case NumPlace when 257 then '50' else '150' end,
'$b	lamp	style=Одиночный'
FROM ListRoadLamps
WHERE NumDataSource = @NumDataSource