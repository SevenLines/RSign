--select * from ListRoadSigns where NumDataSource=1650
-- �������� ������ � ������� ������� �������, ����� ������� �� ������� ������
update ListRoadSigns set NumPlace=258 where 
	NumDataSource=1776 and NumPlace=257 and NumMoveDirection=247

-- �������� ������ � ������� ������� �����, ����� ������� �� ������� ������
--update ListRoadSigns set NumPlace=258, NumMoveDirection=247
--	where NumDataSource=1969 and NumPlace=257 and NumMoveDirection=246

--select * from ListRoadSigns where NumDataSource=1561 and NumMoveDirection=247 and NumPlace<>257

--select * from ListRoadSides where NumDataSource=1649
-- select * from Classifier where id_=246