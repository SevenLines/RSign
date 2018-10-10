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
    public partial class FrmSelectRoad : Form
    {
        public FrmSelectRoad()
        {
            InitializeComponent();
            loadData();
        }

        public FrmSelectRoad(DBProvider aDBProvider)
        {
            InitializeComponent();
            _DBProvider = aDBProvider;
            loadData();
        }

        private DBProvider _DBProvider;
        private DBProvider getDBProvider()
        {
            if (_DBProvider == null)
                _DBProvider = new DBProvider(Program.GetSettings().SQLConnection);
            return _DBProvider;
        }

        public int SelectedNumRoad 
        {
            get
            {
                if (GRDRoads.SelectedRows.Count == 0)
                    return 0;
                return (int)GRDRoads.SelectedRows[0].Cells["colNumRoad"].Value;
            }
        }

        private void loadData()
        {
            GRDRoads.AutoGenerateColumns = false;
            GRDRoads.DataSource = getDBProvider().GetRoads();
        }

        private void applyFilter()
        {
            string filter = "";
            if (!string.IsNullOrEmpty(TXTNumRoadFilter.Text))
                filter = string.Format("id_ = '{0}'", TXTNumRoadFilter.Text); 
            if (!string.IsNullOrEmpty(TXTFullTitleFilter.Text))
                filter = (filter == "" ? "" : " and ") + string.Format("FullTitle like '{0}%'", TXTFullTitleFilter.Text);
            (GRDRoads.DataSource as DataTable).DefaultView.RowFilter = filter;
        }
        private void GRDRoads_DoubleClick(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
        }

        private void TXTNumRoadFilter_TextChanged(object sender, EventArgs e)
        {
            applyFilter();
        }

        private void TXTFullTitleFilter_TextChanged(object sender, EventArgs e)
        {
            applyFilter();
        }

        private void TXTNumRoadFilter_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                this.DialogResult = DialogResult.OK;
        }

        private void FrmSelectRoad_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (DialogResult == DialogResult.OK && SelectedNumRoad == 0)
                e.Cancel = true;
        }


    }
}
