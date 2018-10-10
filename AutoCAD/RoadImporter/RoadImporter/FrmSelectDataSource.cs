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
    public partial class FrmSelectDataSource : Form
    {
        public FrmSelectDataSource()
        {
            InitializeComponent();
            loadData(0);
        }

        public FrmSelectDataSource(DBProvider aDBProvider, int aNumRoad)
        {
            InitializeComponent();
            _DBProvider = aDBProvider;
            loadData(aNumRoad);
        }

        private void loadData(int aNumRoad)
        {
            GRDDataSources.AutoGenerateColumns = false;
            GRDDataSources.DataSource = getDBProvider().GetDataSources(aNumRoad);
        }

        private DBProvider _DBProvider;
        private DBProvider getDBProvider()
        {
            if (_DBProvider == null)
                _DBProvider = new DBProvider(Program.GetSettings().SQLConnection);
            return _DBProvider;
        }

        public int SelectedNumNumDataSource
        {
            get
            { 
                if (GRDDataSources.SelectedRows.Count == 0)
                    return 0;
                return (int)GRDDataSources.SelectedRows[0].Cells["ColNumDataSource"].Value;
            }
        }
        private void GRDDataSources_DoubleClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }
    }
}
