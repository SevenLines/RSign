using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RoadImporter
{
    public partial class FrmMoveToDB : Form
    {
        private DBProvider _DBProvider;
        private DBProvider getDBProvider()
        {
            if (_DBProvider == null)
                _DBProvider = new DBProvider(Program.GetSettings().SQLConnection);
            return _DBProvider;
        }
        private int? _NumRoad;
        public int NumRoad
        {
            get
            {
                if (_NumRoad == null)
                    _NumRoad = Program.GetSettings().NumRoad;
                return (int)_NumRoad;
            }
            set
            {
                _NumRoad = value;
                NumDataSource = 0;
            }
        }
        
        private int? _NumDataSource;
        public int NumDataSource
        {
            get
            {
                if (_NumDataSource == null)
                    _NumDataSource = Program.GetSettings().NumDataSource;
                return (int)_NumDataSource;
            }
            set
            {
                _NumDataSource = value;
                TXTDataSource.Text = getDBProvider().GetRoadDataSourceTitle(value);
                TXTRoad.Text = getDBProvider().GetRoadTitle(NumRoad, value);
            }
        }

        private List<RoadObject> _RoadObjecs;

        public FrmMoveToDB()
        {
            InitializeComponent();
            int nds = NumDataSource;
            NumRoad = NumRoad;
            NumDataSource = nds;
        }

        private List<RoadObject> LoadXMLs(string aPath)
        {
            RoadObject rootObject = getDBProvider().GetRoadObjects();
            XMLProvider xmlProvider = new XMLProvider(aPath, false);
            return xmlProvider.GetRoadObjects(rootObject);
        }

        private void Import(List<RoadObject> aRoadObjects, int aNumRoad, int aNumDataSource, bool aNeedToDelete)
        {
            PBImport.Minimum = 0;
            PBImport.Maximum = aRoadObjects.Count;
            PBImport.Step = 1;
            foreach (RoadObject rObject in aRoadObjects)
            {
                if (rObject.Id == -1)
                    continue;

                LBLCurrentRoadObjectTitle.Text = rObject.FullTitle;
                LBLCurrentRoadObjectTitle.Update();

                if (aNeedToDelete)
                    getDBProvider().DeleteInDB(rObject, aNumRoad, aNumDataSource);
                getDBProvider().UploadToDB(rObject, aNumRoad, aNumDataSource);
                PBImport.PerformStep();
            }
            LBLCurrentRoadObjectTitle.Text = "";
            PBImport.Value = 0;
        }

        private void BtnChooseDir_Click(object sender, EventArgs e)
        {
            if (XMLFldBrowserDlg.ShowDialog() != DialogResult.OK)
                return;

            TxtXMLPath.Text = XMLFldBrowserDlg.SelectedPath;
            _RoadObjecs = new List<RoadObject>();
            _RoadObjecs = LoadXMLs(XMLFldBrowserDlg.SelectedPath);

            RoadObject ndsRoadObject = null;
            foreach (RoadObject rObject in _RoadObjecs)
            {
                if (rObject.Id == -1)
                {
                    ndsRoadObject = rObject;
                    break;
                }
            }

            if (ndsRoadObject != null && ndsRoadObject.FirstTable.Rows.Count > 0)
            {
                DataRow row = ndsRoadObject.FirstTable.Rows[0];
                NumRoad = DBAdapter.IsNULL(row["NumRoad"], 0);
                int nds = DBAdapter.IsNULL(row["id_"], 0);
                if (getDBProvider().IsRoadDataSourceExists(NumRoad, nds))
                    NumDataSource = nds;
                else
                {
                    if (MessageBox.Show(
                        string.Format(
                            "Источник данных для дороги '{0}' с кодом '{1}' не найден, создать новый?",
                            NumRoad,
                            nds
                        ),
                        "Создание нового источника данных",
                        MessageBoxButtons.YesNo,
                        MessageBoxIcon.Question) == DialogResult.No
                    )
                        return;

                    NumDataSource = getDBProvider().CreateNumDataSource(ndsRoadObject, NumRoad);

                }
            }
        }

        private void BtnImport_Click(object sender, EventArgs e)
        {
            if (_RoadObjecs == null)
                throw new Exception("Не указаны объекты для загрузки");
            Import(_RoadObjecs, NumRoad, NumDataSource, CHKDeleteData.Checked);
        }

        private void BTNSelectRoad_Click(object sender, EventArgs e)
        {
            FrmSelectRoad frm = new FrmSelectRoad(getDBProvider());
            if (frm.ShowDialog() != DialogResult.OK)
                return;

            NumRoad = frm.SelectedNumRoad;
        }

        private void BTNSelectDataSource_Click(object sender, EventArgs e)
        {
            FrmSelectDataSource frm = new FrmSelectDataSource(getDBProvider(), NumRoad);
            if (frm.ShowDialog() != DialogResult.OK)
                return;

            NumDataSource = frm.SelectedNumNumDataSource;
        }
    }
}
