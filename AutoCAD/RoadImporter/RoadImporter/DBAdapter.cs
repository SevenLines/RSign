using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;


namespace RoadImporter
{
    public class DBAdapterBase
    {
        protected SqlConnection _SqlConn;
        
        private string _ConnectionString;

        public DBAdapterBase(string aConnectionString, bool aAutoConnect = true)
        {
            _ConnectionString = aConnectionString;
            if (aAutoConnect)
                Connect();
        }

        public void Dispose()
        {
            Disconnect();
        }

        public bool Connect()
        {
            _SqlConn = new SqlConnection();
            _SqlConn.ConnectionString = _ConnectionString;
            _SqlConn.Open();

            return true;
        }

        public void Disconnect()
        {
            _SqlConn.Close();
        }

        public bool canRunQuery()
        {
            if (_SqlConn.State == ConnectionState.Open)
                return true;

            if ((_SqlConn.State == ConnectionState.Broken || _SqlConn.State == ConnectionState.Closed)
                    && _SqlConn.State != ConnectionState.Broken)
            {
                _SqlConn.Open();
                return (_SqlConn.State == ConnectionState.Open);
            }

            while (_SqlConn.State == ConnectionState.Executing || _SqlConn.State == ConnectionState.Fetching)
                System.Threading.Thread.Sleep(1000);
            return true;
        }

        #region NullHelpers
        public static string IsNULL(Object aTableValue, string aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (string)aTableValue;
            return aNULLValue;
        }

        public static Guid IsNULL(Object aTableValue, Guid aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (Guid)aTableValue;
            return aNULLValue;
        }

        public static DateTime IsNULL(Object aTableValue, DateTime aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (DateTime)aTableValue;
            return aNULLValue;
        }

        public static DateTime? IsNULL(Object aTableValue, DateTime? aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (DateTime?)aTableValue;
            return aNULLValue;
        }

        public static float IsNULL(Object aTableValue, float aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (float)Convert.ToDecimal(aTableValue);
            return aNULLValue;
        }

        public static double IsNULL(Object aTableValue, double aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (double)Convert.ToDecimal(aTableValue);
            return aNULLValue;
        }

        public static int IsNULL(Object aTableValue, int aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (int)aTableValue;
            return (int)aNULLValue;
        }

        public static long IsNULL(Object aTableValue, long aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (long)aTableValue;
            return aNULLValue;
        }

        public static short IsNULL(Object aTableValue, short aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (short)aTableValue;
            return aNULLValue;
        }

        public static bool IsNULL(Object aTableValue, bool aNULLValue)
        {
            if (aTableValue != DBNull.Value)
                return (bool)aTableValue;
            return aNULLValue;
        }

        public static Object NULLIF(Object aValue, DateTime aNULLValue)
        {
            if (aValue is DateTime)
            {
                if ((DateTime)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }

        public static Object NULLIF(Object aValue, int? aNULLValue)
        {
            if (aValue == null && aNULLValue == null)
                return DBNull.Value;
            if (aValue is int)
            {
                if ((int)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }

        public static Object NULLIF(Object aValue, bool aNULLValue)
        {
            if (aValue is bool)
            {
                if ((bool)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }

        public static Object NULLIF(Object aValue, string aNULLValue)
        {
            if (aValue is string)
            {
                if ((string)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }

        public static Object NULLIF(Object aValue, float aNULLValue)
        {
            if (aValue is float)
            {
                if ((float)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }

        public static Object NULLIF(Object aValue, Guid aNULLValue)
        {
            if (aValue is Guid)
            {
                if ((Guid)aValue == aNULLValue)
                    return DBNull.Value;
            }
            return aValue;
        }
        #endregion
    }

    public class DBAdapter : DBAdapterBase
    {
        public DBAdapter(string aConnectionString, bool aAutoConnect = true) : base(aConnectionString, aAutoConnect) { }

        public DataTable GetListRoadObjects()
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            SqlCommand cmd = new SqlCommand(
                @"SELECT RO.* 
                FROM dbo.ListRoadObjects RO
                ORDER BY RO.Parent, RO.FullTitle", 
                _SqlConn
            );
            cmd.CommandType = CommandType.Text;

            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataTable resData = new DataTable();
            da.Fill(resData);
            return resData;
        }

        public DataSet GetDataSet(string aSQL)
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            SqlCommand cmd = new SqlCommand(aSQL, _SqlConn);
            cmd.CommandType = CommandType.Text;

            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataSet resData = new DataSet();
            da.Fill(resData);
            return resData;
        }

        public object ExecuteScalarCommand(SqlCommand aCommand)
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            aCommand.Connection = _SqlConn;
            return aCommand.ExecuteScalar();
        }

        public object ExecuteCommand(SqlCommand aCommand)
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            aCommand.Connection = _SqlConn;
            aCommand.ExecuteNonQuery();

            return true;
        }

        public DataTable GetRoads(int? aNumRoad = null)
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            SqlCommand cmd = new SqlCommand(
                @"SELECT R.*, rtrim(D.FullTitle) DistrictTitle
                FROM ListRoads R 
                LEFT JOIN ListDistricts D ON D.id_ = R.NumDistrict
                WHERE (R.id_ <> 0) and (@NumRoad is NULL or R.id_ = @NumRoad) 
                ORDER BY D.FullTitle, R.FullTitle", 
                _SqlConn
            );
            cmd.CommandType = CommandType.Text;

            cmd.Parameters.Add("@NumRoad", SqlDbType.Int).Value = NULLIF(aNumRoad, (int?)null);

            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataTable resData = new DataTable();
            da.Fill(resData);
            return resData;

        }

        public DataTable GetDataSources(int? aNumRoad, int? aNumDataSource)
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            SqlCommand cmd = new SqlCommand(
                @"SELECT DS.* 
                FROM ListDataSources DS 
                WHERE (@NumRoad is NULL or DS.NumRoad = @NumRoad)and(@NumDataSource is NULL or DS.id_ = @NumDataSource)
                ORDER BY DS.FullTitle", 
                _SqlConn
            );
            cmd.CommandType = CommandType.Text;

            cmd.Parameters.Add("@NumRoad", SqlDbType.Int).Value = NULLIF(aNumRoad, (int?)null);
            cmd.Parameters.Add("@NumDataSource", SqlDbType.Int).Value = NULLIF(aNumDataSource, (int?)null);

            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataTable resData = new DataTable();
            da.Fill(resData);
            return resData;

        }

        public int GetMaxVideoId()
        {
            if (!canRunQuery())
                throw new Exception("No Database access");

            SqlCommand cmd = new SqlCommand(
                @"SELECT max(id_high) id_high FROM v_high",
                _SqlConn
            );
            cmd.CommandType = CommandType.Text;

            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataTable resData = new DataTable();
            da.Fill(resData);
            if (resData.Rows.Count == 0)
                return 0;
            return IsNULL(resData.Rows[0][0], 0);
        }
    }

}
