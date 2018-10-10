using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RoadImporter
{
    class Settings
    {
        public Settings(string aSQLConnection, int aNumRoad, int aNumDataSource)
        {
            SQLConnection = aSQLConnection;
            NumRoad = aNumRoad;
            NumDataSource = aNumDataSource;
        }
        
        public string SQLConnection { get; set; }
        public int NumRoad { get; set; }
        public int NumDataSource { get; set; }
    }
}
