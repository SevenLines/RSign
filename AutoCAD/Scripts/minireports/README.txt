����� ������� ����� ����-�����, ���������� ������� ����� � ���� ����������
� ������ ������ (�������� ���).

� ����� ������� ����� � ����������� sql ���������� ������������ TSQL-���.
����� ��������� ��������� �����, ��� �������� ��������� ����� �������� �����
����� ��������������� ��������� ����� � sql-�������.

��� �������� ����-������ ���������� ��������� ���������:
	
	NumDataSource - ����� ��������� ������ �������� ������
	NumRoad - ����� ������ �������� ������
	RoadName - �������� ������ �������� ������
	DistrictName - �������� ������ �������� ������
	
��� ��������� ������������� ������ ����������� ����:
	
	/*$ParaName*/Param-Value/*$*/
	
��������, ���� �������� RoadName ���� "�������-���-����-���", ��:

	SELECT '/*$RoadName*/1234/*$*/'
	
���������� ��

	SELECT '�������-���-����-���'

�������� �������� ��� ������� ��������� ������� � ������� �����������, 
� ������ �������� "1234" ��������� ����������.

��������� �������� ��������� �� �����������, �.�. ��������� ����������� �������� ����������:

	SELECT '/*$DistrictName*//*$*/'

����� ��������� sqltotxt ����������� � ���� ���������� ������� ���� .credentials
� ������� � ���� ��������� �����������. ������ �����������:
#==== .credentials ====# << ��� ������ ������������ �� ����
UserID: sa
DataSource: .
InitialCatalog: RoadsDB_Direct
Password:
#==== .credentials ====# << ��� ������ ������������ �� ����
	
��������� sqltotxt:
https://github.com/SevenLines/sqltotxt.git


