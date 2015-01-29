DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3742/*$*/

SET NOCOUNT ON 
SELECT cast(Displacement*100 as int), 
100, 
'$b	tubeEx	style=vertical iLength:L='+cast(extent as varchar(10))
+ ' Position:' + dbo.pp_Km_mFormat(Displacement) 
+ ' DOut:' + TubeScheme
FROM ListTubes
WHERE NumDataSource = @NumDataSource
ORDER BY 1