using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.Linq;
using System.IO;

namespace RoadImporter
{
    public partial class FrmMoveToXML : Form
    {
        private DBProvider _DBProvider;
        private DBProvider getDBProvider()
        { 
            if (_DBProvider == null)
                _DBProvider = new DBProvider(Program.GetSettings().SQLConnection);
            return _DBProvider;
        }
        private int? _NumRoad;
        private int NumRoad
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
        private int NumDataSource
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

        public FrmMoveToXML()
        {
            InitializeComponent();
            TVRoadObjects.Nodes.Add(createTreeNode(getDBProvider().GetRoadObjects()));
            int nds = NumDataSource;
            NumRoad = NumRoad;
            NumDataSource = nds;
        }

        private void TVRoadObjects_AfterCheck(object sender, TreeViewEventArgs e)
        {
            checkNodes(e.Node, e.Node.Checked);
        }

        private TreeNode createTreeNode(RoadObject aRootRoadObject)
        {
            TreeNode node = new TreeNode(aRootRoadObject.FullTitle);
            node.Tag = aRootRoadObject;
            foreach (RoadObject child in aRootRoadObject.Children)
                node.Nodes.Add(createTreeNode(child));
            return node;
        }

        private void checkNodes(TreeNode aNode, bool aChecked)
        {
            foreach (TreeNode child in aNode.Nodes)
            {
                child.Checked = aChecked;
                checkNodes(child, aChecked);
            }
        }

        private void fillCheckedRoadObjects(TreeNodeCollection aParentNodes, List<RoadObject> aRoadObjects)
        {
            foreach(TreeNode node in aParentNodes)
            {
                RoadObject rObject = (RoadObject)node.Tag;
                if (node.Checked || rObject.Id == -1)
                    aRoadObjects.Add(rObject);
                fillCheckedRoadObjects(node.Nodes, aRoadObjects);
            }
        }

        private void Import(string aPath, List<RoadObject> aRoadObjects)
        {
            string folderName = getDBProvider().GetRoadTitle(NumRoad, NumDataSource);
            XMLProvider xmlProvider = new XMLProvider(Path.Combine(aPath, folderName), true);
            PBImport.Minimum = 0;
            PBImport.Maximum = aRoadObjects.Count();
            PBImport.Step = 1;
            foreach (RoadObject rObject in aRoadObjects)
            {
                LBLCurrentRoadObjectTitle.Text = rObject.FullTitle;
                LBLCurrentRoadObjectTitle.Update();
                rObject.SetDataSet(getDBProvider().LoadFromDB(rObject, NumRoad, NumDataSource));
                xmlProvider.Import(rObject);
                PBImport.PerformStep();
            }
            LBLCurrentRoadObjectTitle.Text = "";
            PBImport.Value = 0;
        }

        private void BtnImport_Click(object sender, EventArgs e)
        {
            if (XMLFldBrowserDlg.ShowDialog() != DialogResult.OK)
                return;

            List<RoadObject> roadObjects = new List<RoadObject>();
            fillCheckedRoadObjects(this.TVRoadObjects.Nodes, roadObjects);
            Import(XMLFldBrowserDlg.SelectedPath, roadObjects);
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
