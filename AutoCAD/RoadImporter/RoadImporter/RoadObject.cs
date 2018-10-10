using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;


namespace RoadImporter
{
    public class RoadObject 
    {
        public int Id { get; set; }
        public string FullTitle { get; set; }
        public string TableName { get; set; }
        public string TableCondition { get; set; }
        public bool IsFake { get; set; }
        public int ObjectType { get; set; }

        public RoadObject(DataRow aRow)
        { 
            Id = DBAdapter.IsNULL(aRow["id_"], 0);
            FullTitle = DBAdapter.IsNULL(aRow["FullTitle"], "").Trim();
            TableName = DBAdapter.IsNULL(aRow["TableName"], "").Trim();
            TableCondition = DBAdapter.IsNULL(aRow["Condition"], "").Trim();
            IsFake = DBAdapter.IsNULL(aRow["FakeObject"], false);
            ObjectType = DBAdapter.IsNULL(aRow["ObjectType"], 0);
        }

        public RoadObject(int aId, string aFullTitle, string aTableName)
        {
            Id = aId;
            FullTitle = aFullTitle;
            TableName = aTableName;
            IsFake = false;
            ObjectType = 0;
        }

        private List<RoadObject> _Children = new List<RoadObject>();
        public List<RoadObject> Children 
        { 
            get { return _Children; } 
        }

        public void AddChild(RoadObject aRoadObject)
        {
            Children.Add(aRoadObject);
        }

        public RoadObject GetById(int aId)
        {
            if (Id == aId)
                return this;

            foreach (RoadObject child in Children)
            {
                RoadObject recChild = child.GetById(aId);
                if (recChild != null)
                    return recChild;
            }
            return null;
        }

        public RoadObject GetByXMLName(string aXMLName)
        {
            if (XMLName == aXMLName)
                return this;

            foreach (RoadObject child in Children)
            {
                RoadObject recChild = child.GetByXMLName(aXMLName);
                if (recChild != null)
                    return recChild;
            }
            return null;
        }

        private DataSet _DataSet;
        public DataSet DataSet
        { 
            get
            {
                if (_DataSet == null)
                    throw new Exception("Данные не загружены");
                return _DataSet;
            }
        }
        public void SetDataSet(DataSet aDataSet)
        {
            this._DataSet = aDataSet;
            if (this._DataSet == null)
                return;
            if (this._DataSet.Tables.Count > 0)
            {
                this._DataSet.Tables[0].TableName = this.TableName;
                if (this.TableName == "ListRoadSides")
                {
                    if (this._DataSet.Tables.Count != 2)
                        throw new Exception("В объекте с обочинами неверное количество таблиц данных");
                    this._DataSet.Tables[1].TableName = "CharactRoadSides";
                }
                if (this.TableName == "ELEM_VideoInfo")
                { 
                    if (this._DataSet.Tables.Count != 3)
                        throw new Exception("В объекте с данными видео неверное количество таблиц данных");
                    this._DataSet.Tables[1].TableName = "vi_Points";
                    this._DataSet.Tables[2].TableName = "v_high";
                }
            }
        }
        public DataTable FirstTable
        { 
            get
            {
                return this.DataSet.Tables[0];
            }
        }

        public bool CanUpload
        { 
            get 
            {
                if (this.IsFake)
                    return false;
                return (!string.IsNullOrEmpty(this.TableName));
            }
        }

        public string XMLName
        {
            get
            {
                return string.Format("{0}_{1}.xml", this.FullTitle, this.Id);
            }
        }

        public string GetSelectStatement(int aNumRoad, int aNumDataSource)
        {
            if (TableName == "ListRoadSides")
                return getListRoadSidesSelectStatement(aNumRoad, aNumDataSource);

            if (TableName == "ELEM_VideoInfo")
                return getVideoSelectStatement(aNumRoad, aNumDataSource);

            string whereCondition = string.Format("NumRoad = {0}", aNumRoad);

            if (TableName == "ListDataSources")
                whereCondition += string.Format(" and id_ = {0}", aNumDataSource);
            else
                whereCondition += string.Format(" and NumDataSource = {0}", aNumDataSource);
            
            if (!string.IsNullOrEmpty(this.TableCondition))
                whereCondition += string.Format(" and {0}", this.TableCondition);

            string retVal = string.Format(
                "SELECT * FROM {0} WHERE {1}", 
                this.TableName,
                whereCondition 
            );

            return retVal;
        }

        private string getListRoadSidesSelectStatement(int aNumRoad, int aNumDataSource)
        {
            string retVal = string.Format(
                @"SELECT * 
                FROM ListRoadSides 
                WHERE NumRoad = {0} and NumDataSource = {1};
                SELECT CRS.* 
                FROM CharactRoadSides CRS 
                WHERE CRS.NumRoadSide in (select id_ from ListRoadSides where NumRoad = {0} and NumDataSource = {1});",
                aNumRoad,
                aNumDataSource
            );

            return retVal;
        }

        private string getVideoSelectStatement(int aNumRoad, int aNumDataSource)
        {
            string retVal = string.Format(
                @"SELECT * 
                FROM ELEM_VideoInfo
                WHERE NumRoad = {0} and NumDataSource = {1};
                SELECT *
                FROM vi_Points
                WHERE id_road = {0} and NumDataSource = {1};
                SELECT *
                FROM v_high
                WHERE id_high in (select id_high from vi_Points WHERE id_road = {0} and NumDataSource = {1});",
                aNumRoad,
                aNumDataSource
            );
            return retVal;        
        }

        public string GetDeleteStatement(int aNumRoad, int aNumDataSource)
        {
            if (TableName == "ELEM_VideoInfo")
                return getVideoDeleteStatement(aNumRoad, aNumDataSource);

            string retVal = string.Format(
                "DELETE FROM {0} WHERE NumRoad = {1} and NumDataSource = {2}",
                this.TableName,
                aNumRoad,
                aNumDataSource
            );
            if (!string.IsNullOrEmpty(this.TableCondition))
                retVal += string.Format(" and {0}", this.TableCondition);

            return retVal;
        }

        private string getVideoDeleteStatement(int aNumRoad, int aNumDataSource)
        {
            string retVal = string.Format(
                @"SELECT DISTINCT id_high 
                    INTO #id_high 
                FROM vi_Points
                WHERE id_road = {0} and NumDataSource = {1};

                DELETE FROM ELEM_VideoInfo WHERE NumRoad = {0} and NumDataSource = {1};
                DELETE FROM vi_Points WHERE id_high in (select id_high from #id_high);
                DELETE FROM v_high WHERE id_high in (select id_high from #id_high);",
                aNumRoad,
                aNumDataSource
            );
            return retVal;
        }

        public string GetInsertStatement(DataTable aDataTable)
        {
            string colNames = "";
            string colValues = "";
            foreach (DataColumn col in aDataTable.Columns)
            {
                if (col.ColumnName == "id_")
                    continue;

                colNames += (colNames == "" ? "" : ",") + "[" + col.ColumnName + "]";
                colValues += (colValues == "" ? "" : ",") +  "@" + col.ColumnName;
            }
            string retVal = string.Format(
                @"INSERT INTO {0} ({1}) VALUES ({2});
                SELECT SCOPE_IDENTITY();",
                aDataTable.TableName, 
                colNames, 
                colValues
            );

            return retVal;
        }

        public void FillInsertStatementPararmeters(SqlParameterCollection aParams, DataRow aRow, int aNumRoad, int aNumDataSource)
        {

            foreach (DataColumn col in aRow.Table.Columns)
            {
                if (col.ColumnName == "id_")
                    continue;

                object value = aRow[col.ColumnName] == null ? DBNull.Value : aRow[col.ColumnName];
                
                string colNameUpperCase = col.ColumnName.ToUpper();
                if (colNameUpperCase == "NUMROAD" || colNameUpperCase == "ID_ROAD")
                    value = aNumRoad;
                if (colNameUpperCase == "NUMDATASOURCE")
                    value = aNumDataSource;

                aParams.Add("@" + col.ColumnName, DBProvider.TypeToSqlDbType(col.DataType)).Value = value;
            }
        }

    }
}
