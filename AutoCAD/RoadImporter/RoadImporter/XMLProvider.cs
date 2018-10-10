using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.IO;

namespace RoadImporter
{
    class XMLProvider
    {
        private string _Path;

        public XMLProvider(string aPath, bool aNeedToClear)
        {
            if (string.IsNullOrEmpty(aPath))
                throw new Exception("Не указана директория для выгрузки");
            if (!Directory.Exists(aPath))
                Directory.CreateDirectory(aPath);

            _Path = aPath;

            if (aNeedToClear)
                ClearDirectory();
        }

        public void Import(RoadObject aRoadObject)
        {
            if (!aRoadObject.CanUpload)
                return;
            aRoadObject.DataSet.WriteXml(Path.Combine(_Path, aRoadObject.XMLName), XmlWriteMode.WriteSchema);
        }

        public void Export(RoadObject aRoadObject, string aXMLPath)
        {
            if (!aRoadObject.CanUpload)
                return;
            DataSet ds = new DataSet();
            ds.ReadXml(aXMLPath);
            aRoadObject.SetDataSet(ds);
        }

        public void ClearDirectory()
        {
            DirectoryInfo di = new DirectoryInfo(_Path);

            foreach (FileInfo file in di.GetFiles())
                file.Delete();
            foreach (DirectoryInfo dir in di.GetDirectories())
                dir.Delete(true);
        }

        public List<RoadObject> GetRoadObjects(RoadObject aRootObject)
        {
            List<RoadObject> retList = new List<RoadObject>();

            DirectoryInfo di = new DirectoryInfo(_Path);

            foreach (FileInfo file in di.GetFiles())
            {
                RoadObject rObject = aRootObject.GetByXMLName(file.Name);
                if (rObject == null)
                    continue;
                Export(rObject, file.FullName);
                retList.Add(rObject);
            }

            return retList;
        }
    }
}
