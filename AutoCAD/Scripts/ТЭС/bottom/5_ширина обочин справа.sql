DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- источник дороги << главное  поле

DECLARE @NumRoad int
DECLARE @l int, @r int, @max_ob_v float
DECLARE @mul int

SELECT @l = -1, @r = -1 -- явные границы участка слева и справа
SELECT @mul = 100 -- множитель границ т.е если значение 100 то границы будут увиличены в 100 раз
SELECT @max_ob_v = 5 -- максимальная ширина обочины, как правило сильно большие значению означают наличие моста

SELECT @r = case when @r <= 0 or @r - @l < 0 then 99999999 else @r end
SELECT @l = case when @l < 0 or @r - @l < 0 then -99999999 else @l end

SELECT	cast(dbo.pp_GetMaxValue(@l,StartPos)*@mul as int) as 'обочины слева',
		cast(dbo.pp_GetMinValue(@r,EndPos)*@mul as int) as r,
		case when Width > @max_ob_v then 0 else cast(Width as float) end as v
FROM ListRoadSides
WHERE NumDataSource = @NumDataSource and NumPlace = 258
	and ((StartPos >= @l and EndPos <= @r) or (StartPos <= @l and EndPos <= @r and EndPos >= @l) or (StartPos >= @l and StartPos <= @r and EndPos >= @r))
ORDER BY 1

