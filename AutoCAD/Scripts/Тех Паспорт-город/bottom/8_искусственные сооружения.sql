DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3766/*$*/

SET NOCOUNT ON 
SELECT cast(Displacement*100 as int), 
100, 
'$b','tubeEx', 'style=vertical iLength:L='+cast(extent as varchar(10))
+ ' Position:' + dbo.pp_Km_mFormat(Displacement) 
+ ' DOut:' + TubeScheme
FROM ListTubes
WHERE NumDataSource = 3766
UNION
SELECT cast(StartPos*100 as int), case NumPlace when 257 then 50 else 150 end,
 '$b', 'barBarrierMetal', 'Length=' + cast( cast((EndPos - StartPos)*100 as int) as varchar) + 
case NumPlace when 257 then 'Flip=отражение' else '' end
FROM ListBarriers
WHERE NumDataSource = @NumDataSource and GuidingStructuresCount = 0 and EndPos - StartPos>0
ORDER BY 1