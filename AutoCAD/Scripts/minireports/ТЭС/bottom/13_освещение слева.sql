DECLARE @NumDataSource int
SELECT @NumDataSource = /*$NumDataSource*/3749/*$*/ -- �������� ������ << �������  ����

SELECT Displacement*100, case NumPlace when 257 then 50 else 150 end, '$b', 'lamp','style=���������'
FROM ListRoadLamps
WHERE NumDataSource = @NumDataSource
