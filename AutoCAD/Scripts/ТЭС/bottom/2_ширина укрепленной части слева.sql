DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- �������� ������ << �������  ����

DECLARE @NumRoad int
DECLARE @l int, @r int, @max_ob_v float
DECLARE @mul int

SELECT @l = -1, @r = -1 -- ����� ������� ������� ����� � ������
SELECT @mul = 100 -- ��������� ������ �.� ���� �������� 100 �� ������� ����� ��������� � 100 ���
SELECT @max_ob_v = 5 -- ������������ ������ �������, ��� ������� ������ ������� �������� �������� ������� �����

SELECT @r = case when @r <= 0 or @r - @l < 0 then 99999999 else @r end
SELECT @l = case when @l < 0 or @r - @l < 0 then -99999999 else @l end

SELECT	cast(dbo.pp_GetMaxValue(@l,StartPos)*@mul as int) as '����. �����',
		cast(dbo.pp_GetMinValue(@r,EndPos)*@mul as int) as r,
		sum(RowWidth) as v
FROM ListRoadSides l
 LEFT JOIN CharactRoadSides c ON c.NumRoadSide = l.id_
WHERE l.NumDataSource = @NumDataSource
	and c.NumTypeStrengthening in (93, 88) and l.NumPlace = 257
	and ((StartPos >= @l and EndPos <= @r) or (StartPos <= @l and EndPos <= @r and EndPos >= @l) or (StartPos >= @l and StartPos <= @r and EndPos >= @r))
GROUP BY StartPos, EndPos
ORDER BY StartPos
