using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace RoadImporter
{
    public class DBProvider
    {
        public DBProvider(string aSQLConnection)
        {
            _ConnectionString = aSQLConnection;
        }

        private string _ConnectionString;

        private DBAdapter _DBAdapter;
        public DBAdapter GetDBAdapter()
        {
            if (_DBAdapter == null)
                _DBAdapter = new DBAdapter(_ConnectionString);
            return _DBAdapter;
        }

        public RoadObject GetRoadObjects()
        {
            RoadObject retVal = null;
            DataTable dtRoadObjects = GetDBAdapter().GetListRoadObjects();
            foreach (DataRow row in dtRoadObjects.Rows)
            {
                int parentID = DBAdapter.IsNULL(row["Parent"], 0);
                RoadObject newChild = new RoadObject(row);

                if (parentID == 0)
                {
                    retVal = newChild;
                }
                else
                {
                    if (retVal == null)
                        throw new Exception("Не найден корневой дорожный объект");

                    RoadObject parent = retVal.GetById(parentID);
                    if (parent != null)
                        parent.AddChild(newChild);
                }
            }

            if (retVal == null)
                throw new Exception("Не найден корневой дорожный объект");

            retVal.AddChild(new RoadObject(-1, "Источник данных", "ListDataSources"));
            retVal.AddChild(new RoadObject(-2, "Привязка видео", "ELEM_VideoInfo"));

            return retVal;
        }

        public DataSet LoadFromDB(RoadObject aRoadObject, int aNumRoad, int aNumDataSource)
        {
            if (!aRoadObject.CanUpload)
                return null;
            return GetDBAdapter().GetDataSet(aRoadObject.GetSelectStatement(aNumRoad, aNumDataSource));
        }

        public void DeleteInDB(RoadObject aRoadObject, int aNumRoad, int aNumDataSource)
        {
            if (!aRoadObject.CanUpload)
                return;

            SqlCommand cmd = new SqlCommand(aRoadObject.GetDeleteStatement(aNumRoad, aNumDataSource));
            GetDBAdapter().ExecuteCommand(cmd);
        }

        public void UploadToDB(RoadObject aRoadObject, int aNumRoad, int aNumDataSource)
        {
            if (!aRoadObject.CanUpload)
                return;

            switch(aRoadObject.TableName)
            {
                case "ListRoadSides": 
                    UploadRoadSidesToDB(aRoadObject, aNumRoad, aNumDataSource);
                    break;
                case "ELEM_VideoInfo":
                    UploadVideoInfoToDB(aRoadObject, aNumRoad, aNumDataSource);
                    break;
                default:
                    DataTable dt = aRoadObject.FirstTable;
                    foreach (DataRow row in dt.Rows)
                        InsertRowIntoDB(aRoadObject, row, aNumRoad, aNumDataSource);
                    break;

            }
        }

        public void UploadRoadSidesToDB(RoadObject aSidesRoadObject, int aNumRoad, int aNumDataSource)
        {
            if (aSidesRoadObject.DataSet.Tables.Count != 2)
                throw new Exception("В объекте с обочинами неверное количество таблиц данных");

            DataTable dt = aSidesRoadObject.FirstTable;
            Dictionary<int, int> numRoadSidesDict = new Dictionary<int, int>();
            foreach (DataRow row in dt.Rows)
            {
                int numRoadSide = InsertRowIntoDB(aSidesRoadObject, row, aNumRoad, aNumDataSource);
                numRoadSidesDict.Add(DBAdapter.IsNULL(row["id_"], 0), numRoadSide);
            }

            DataTable charactDT = aSidesRoadObject.DataSet.Tables[1];
            foreach (DataRow row in charactDT.Rows)
            {
                SqlCommand cmd = new SqlCommand(aSidesRoadObject.GetInsertStatement(row.Table));
                aSidesRoadObject.FillInsertStatementPararmeters(cmd.Parameters, row, aNumRoad, aNumDataSource);
                cmd.Parameters["@NumRoadSide"].Value = numRoadSidesDict[DBAdapter.IsNULL(row["NumRoadSide"], 0)];
                GetDBAdapter().ExecuteScalarCommand(cmd);
            }
        }

        public void UploadVideoInfoToDB(RoadObject aVideoRoadObject, int aNumRoad, int aNumDataSource)
        {
            if (aVideoRoadObject.DataSet.Tables.Count != 3)
                throw new Exception("В объекте с данными видео неверное количество таблиц данных");

            Dictionary<int, int> idHighDict = new Dictionary<int, int>();
            DataTable dtELEM_VideoInfo = aVideoRoadObject.DataSet.Tables[0];
            DataTable dtviPoints = aVideoRoadObject.DataSet.Tables[1];
            DataTable dtvHigh = aVideoRoadObject.DataSet.Tables[2];

            foreach (DataRow row in dtvHigh.Rows)
            {
                int idHighOld = DBAdapter.IsNULL(row["id_high"], 0);
                if (!idHighDict.ContainsKey(idHighOld))
                {
                    int idHighNew = GetDBAdapter().GetMaxVideoId() + 1;
                    idHighDict.Add(idHighOld, idHighNew);
                }
                row["id_high"] = idHighDict[idHighOld];
                InsertRowIntoDB(aVideoRoadObject, row, aNumRoad, aNumDataSource);
            }

            foreach (DataRow row in dtviPoints.Rows)
            {
                int idHighOld = DBAdapter.IsNULL(row["id_high"], 0);
                row["id_high"] = idHighDict[idHighOld];
                InsertRowIntoDB(aVideoRoadObject, row, aNumRoad, aNumDataSource);
            }

            foreach (DataRow row in dtELEM_VideoInfo.Rows)
            {
                byte[] bytesFileIDs = (byte[])row["FileID_Array"];
                for (int i = 0; i < bytesFileIDs.Count(); i += 4)
                {
                    Int32 idHighOld = BitConverter.ToInt32(bytesFileIDs, i);
                    byte[] bytesFileID = BitConverter.GetBytes(idHighDict[idHighOld]);
                    for (int j = 0; j < 4; j++)
                        bytesFileIDs[i + j] = bytesFileID[j];
                }
                row["FileID_Array"] = bytesFileIDs;
                InsertRowIntoDB(aVideoRoadObject, row, aNumRoad, aNumDataSource);
            }
            
        }

        public int InsertRowIntoDB(RoadObject aRoadObject, DataRow aRow, int aNumRoad, int aNumDataSource)
        {
            SqlCommand cmd = new SqlCommand(aRoadObject.GetInsertStatement(aRow.Table));
            aRoadObject.FillInsertStatementPararmeters(cmd.Parameters, aRow, aNumRoad, aNumDataSource);
            
            object executeResult = GetDBAdapter().ExecuteScalarCommand(cmd);

            if (executeResult == DBNull.Value)
                return 0;
            return Convert.ToInt32(executeResult);
        }

        public string GetRoadTitle(int aNumRoad, int aNumDataSource)
        {
            string retVal = "";

            DataTable dtRoad = GetDBAdapter().GetRoads(aNumRoad);
            if (dtRoad.Rows.Count != 0)
                retVal = string.Format("{0}({1})_{2}", 
                    DBAdapter.IsNULL(dtRoad.Rows[0]["FullTitle"], "").Trim(),
                    DBAdapter.IsNULL(dtRoad.Rows[0]["DistrictTitle"], "").Trim(),
                    aNumDataSource
                );

            return retVal;
        }

        public string GetRoadDataSourceTitle(int aNumDataSource)
        {
            string retVal = "";
            DataTable dtDataSources = GetDBAdapter().GetDataSources(null, aNumDataSource);
            if (dtDataSources.Rows.Count != 0)
                retVal = DBAdapter.IsNULL(dtDataSources.Rows[0]["FullTitle"], "").Trim();

            return retVal;
        }

        public bool IsRoadDataSourceExists(int aNumRoad, int aNumDataSource)
        {
            DataTable dtDataSources = GetDBAdapter().GetDataSources(aNumRoad, aNumDataSource);
            return (dtDataSources.Rows.Count != 0);
        }

        public static SqlDbType TypeToSqlDbType(Type aType)
        {
            Dictionary<Type, SqlDbType> typeMap = new Dictionary<Type, SqlDbType>();

            typeMap[typeof(string)] = SqlDbType.VarChar;
            typeMap[typeof(char[])] = SqlDbType.VarChar;
            typeMap[typeof(int)] = SqlDbType.Int;
            typeMap[typeof(Int32)] = SqlDbType.Int;
            typeMap[typeof(Int16)] = SqlDbType.SmallInt;
            typeMap[typeof(Int64)] = SqlDbType.BigInt;
            typeMap[typeof(Byte[])] = SqlDbType.VarBinary;
            typeMap[typeof(Boolean)] = SqlDbType.Bit;
            typeMap[typeof(DateTime)] = SqlDbType.SmallDateTime;
            typeMap[typeof(DateTimeOffset)] = SqlDbType.DateTimeOffset;
            typeMap[typeof(Decimal)] = SqlDbType.Decimal;
            typeMap[typeof(Double)] = SqlDbType.Float;
            typeMap[typeof(Decimal)] = SqlDbType.Money;
            typeMap[typeof(Byte)] = SqlDbType.TinyInt;
            typeMap[typeof(TimeSpan)] = SqlDbType.Time;

            return typeMap[(aType)];
        }

        public DataTable GetRoads()
        {
            return GetDBAdapter().GetRoads();
        }

        public DataTable GetDataSources(int aNumRoad)
        {
            return GetDBAdapter().GetDataSources(aNumRoad, null);
        }

        public int CreateNumDataSource(RoadObject aNDSRoadObject, int aNumRoad)
        {
            if (aNDSRoadObject.Id != -1)
                throw new Exception("Для создания источника передан неверный объект");

            if (aNDSRoadObject.FirstTable.Rows.Count == 0)
                throw new Exception("Для создания источника передан объект без данных");

            return InsertRowIntoDB(aNDSRoadObject, aNDSRoadObject.FirstTable.Rows[0], aNumRoad, 0);
        }
    }
}
