using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Common;

namespace RoadImporter
{
    class ImporterSettings
    {
        public ImporterSettings(string[] aCommandLineParams)
        {
            if (aCommandLineParams.Count() != 4)
                throw new Exception("Количество параметров должно быть 4: Строка подключения, КодДороги, КодИсточникаДанных, Операция (ToXML/ToDB)");

            SQLConnection = getConnectionString(aCommandLineParams[0]);
            int number = 0;
            if (int.TryParse(aCommandLineParams[1], out number))
                NumRoad = number;

            if (int.TryParse(aCommandLineParams[2], out number))
                NumDataSource = number;

            Operation = getOperationFromString(aCommandLineParams[3]);
        }

        public ImporterSettings(string aSQLConnection, int aNumRoad, int aNumDataSource, string aOperation)
        {
            SQLConnection = getConnectionString(aSQLConnection);
            NumRoad = aNumRoad;
            NumDataSource = aNumDataSource;
            Operation = getOperationFromString(aOperation);
        }

        private ImporterOperation getOperationFromString(string aStringOperation)
        {
            if (aStringOperation == "ToXML")
                return ImporterOperation.ToXML;
            else
                return ImporterOperation.ToDB;
        }

        private string getConnectionString(string aConnectionString)
        {
            DbConnectionStringBuilder csBuilder = new DbConnectionStringBuilder();
            csBuilder.ConnectionString = aConnectionString;
            csBuilder.Remove("Provider");
            csBuilder.Remove("Use Procedure for Prepare");
            csBuilder.Remove("Auto Translate");
            csBuilder.Remove("Use Encryption for Data");
            csBuilder.Remove("Tag with column collation when possible");
            
            return csBuilder.ConnectionString;
        }

        public string SQLConnection { get; set; }
        public int NumRoad { get; set; }
        public int NumDataSource { get; set; }
        public ImporterOperation Operation { get; set; }
    }

    enum ImporterOperation
    { 
        ToDB,
        ToXML
    }
}
