chcp 65001

SET hide_feedback= SET NOCOUNT ON 
SET NumDataSource=%1
SET Organization=

:: create structure
mkdir "top"
pushd "top"
	copy NUL "1_Границы зон обслуживания и наименование дорожных организаций.txt" 
popd

mkdir "bottom"
pushd "bottom"
	if not exist "1_Ширина земляного полотна.txt" copy NUL "1_Ширина земляного полотна.txt" 
	if not exist "2_Ширина проезжей части.txt" copy NUL "2_Ширина проезжей части.txt" 
	if not exist "3_Ширина обочин слева.txt" copy NUL "3_Ширина обочин слева.txt" 
	if not exist "4_Ширина обочин справа.txt" copy NUL "4_Ширина обочин справа.txt" 
	if not exist "5_Конструкция дорожной одежды.txt" copy NUL "5_Конструкция дорожной одежды.txt" 
	if not exist "9_Исскуственный сооружения слева.txt" copy NUL "9_Исскуственный сооружения слева.txt" 
	if not exist "10_Исскуственный сооружения справа.txt" copy NUL "10_Исскуственный сооружения справа.txt" 
	if not exist "11_Снегозаносимые участки слева.txt" copy NUL "11_Снегозаносимые участки слева.txt" 
	if not exist "12_Снегозаносимые участки справа.txt" copy NUL "12_Снегозаносимые участки справа.txt" 
	if not exist "13_Грунт земляного полотна.txt" copy NUL "13_Грунт земляного полотна.txt" 
	if not exist "18_Состояние прокрытия проезжей части.txt" copy NUL "18_Состояние прокрытия проезжей части.txt" 
popd

popd

:: fill data
SET scripts_dir=d:\_DISTR\_ASUDOR\RSign\AutoCAD\DirsStructs\scripts\
SET sqlcmd=sqlcmd -h-1 -d RoadsDB_Direct -v NumDataSource=%NumDataSource% -v Organization=%Organization%

%sqlcmd% -i "%scripts_dir%Наименование организации.sql" -o "top\1_Границы зон обслуживания и наименование дорожных организаций.txt"

%sqlcmd% -i "%scripts_dir%Ширина земляного полотна.sql" -o "bottom\1_Ширина земляного полотна.txt"
%sqlcmd% -i "%scripts_dir%Ширина проезжей части.sql" -o "bottom\2_Ширина проезжей части.txt"
%sqlcmd% -i "%scripts_dir%Обочины слева.sql" -o "bottom\3_Ширина обочин слева.txt"
%sqlcmd% -i "%scripts_dir%Обочины справа.sql" -o "bottom\4_Ширина обочин справа.txt"
%sqlcmd% -i "%scripts_dir%Дорожная одежда.sql" -o "bottom\5_Конструкция дорожной одежды.txt"