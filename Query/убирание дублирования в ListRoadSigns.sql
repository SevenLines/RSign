SELECT LD.FullTitle District,LR.FullTitle Road,LDS.FullTitle DataSource,t1.*
FROM ListRoadSigns t1
 LEFT JOIN ListRoadSigns t2 ON t1.NumRoad=t2.NumRoad and t1.NumDataSource=t2.NumDataSource and t1.Displacement=t2.Displacement and
				t1.NumRoadSign=t2.NumRoadSign and t1.NumPlace=t2.NumPlace and t1.NumMoveDirection=t2.NumMoveDirection and
				t1.SideDistance=t2.SideDistance and t1.id_ < t2.id_
 LEFT JOIN ListRoads LR ON LR.id_=t1.NumRoad
 LEFT JOIN ListDataSources LDS ON LDS.id_=t1.NumDataSource
 LEFT JOIN ListDistricts LD ON LD.id_=LR.NumDistrict
WHERE t2.id_ is not Null 
ORDER BY 1,2,3
