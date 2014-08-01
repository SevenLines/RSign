DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- источник дороги << главное  поле

SELECT cast(StartPos*100 as int), case NumPlace when 257 then 50 else 150 end,
 '$b', 'barBarrierMetal', 'Length=' + cast( cast((EndPos - StartPos)*100 as int) as varchar),
case NumPlace when 257 then 'Flip=Отражение' else '' end
FROM ListBarriers
WHERE NumDataSource = @NumDataSource and GuidingStructuresCount = 0 and EndPos - StartPos>0