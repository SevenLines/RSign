namespace RoadImporter
{
    partial class FrmMoveToXML
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TVRoadObjects = new System.Windows.Forms.TreeView();
            this.BtnImport = new System.Windows.Forms.Button();
            this.XMLFldBrowserDlg = new System.Windows.Forms.FolderBrowserDialog();
            this.PBImport = new System.Windows.Forms.ProgressBar();
            this.LBLCurrentRoadObjectTitle = new System.Windows.Forms.Label();
            this.TXTDataSource = new System.Windows.Forms.TextBox();
            this.BTNSelectDataSource = new System.Windows.Forms.Button();
            this.TXTRoad = new System.Windows.Forms.TextBox();
            this.BTNSelectRoad = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // TVRoadObjects
            // 
            this.TVRoadObjects.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TVRoadObjects.CheckBoxes = true;
            this.TVRoadObjects.Location = new System.Drawing.Point(12, 64);
            this.TVRoadObjects.Name = "TVRoadObjects";
            this.TVRoadObjects.Size = new System.Drawing.Size(450, 275);
            this.TVRoadObjects.TabIndex = 0;
            this.TVRoadObjects.AfterCheck += new System.Windows.Forms.TreeViewEventHandler(this.TVRoadObjects_AfterCheck);
            // 
            // BtnImport
            // 
            this.BtnImport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnImport.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.BtnImport.Location = new System.Drawing.Point(356, 374);
            this.BtnImport.Name = "BtnImport";
            this.BtnImport.Size = new System.Drawing.Size(106, 23);
            this.BtnImport.TabIndex = 1;
            this.BtnImport.Text = "Выгрузить";
            this.BtnImport.UseVisualStyleBackColor = true;
            this.BtnImport.Click += new System.EventHandler(this.BtnImport_Click);
            // 
            // PBImport
            // 
            this.PBImport.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PBImport.Location = new System.Drawing.Point(15, 345);
            this.PBImport.Name = "PBImport";
            this.PBImport.Size = new System.Drawing.Size(447, 23);
            this.PBImport.TabIndex = 5;
            // 
            // LBLCurrentRoadObjectTitle
            // 
            this.LBLCurrentRoadObjectTitle.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LBLCurrentRoadObjectTitle.AutoSize = true;
            this.LBLCurrentRoadObjectTitle.Location = new System.Drawing.Point(12, 379);
            this.LBLCurrentRoadObjectTitle.Name = "LBLCurrentRoadObjectTitle";
            this.LBLCurrentRoadObjectTitle.Size = new System.Drawing.Size(0, 13);
            this.LBLCurrentRoadObjectTitle.TabIndex = 6;
            // 
            // TXTDataSource
            // 
            this.TXTDataSource.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TXTDataSource.Enabled = false;
            this.TXTDataSource.Location = new System.Drawing.Point(12, 37);
            this.TXTDataSource.Name = "TXTDataSource";
            this.TXTDataSource.Size = new System.Drawing.Size(408, 20);
            this.TXTDataSource.TabIndex = 11;
            // 
            // BTNSelectDataSource
            // 
            this.BTNSelectDataSource.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNSelectDataSource.Location = new System.Drawing.Point(426, 35);
            this.BTNSelectDataSource.Name = "BTNSelectDataSource";
            this.BTNSelectDataSource.Size = new System.Drawing.Size(36, 23);
            this.BTNSelectDataSource.TabIndex = 10;
            this.BTNSelectDataSource.Text = "...";
            this.BTNSelectDataSource.UseVisualStyleBackColor = true;
            this.BTNSelectDataSource.Click += new System.EventHandler(this.BTNSelectDataSource_Click);
            // 
            // TXTRoad
            // 
            this.TXTRoad.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TXTRoad.Enabled = false;
            this.TXTRoad.Location = new System.Drawing.Point(12, 12);
            this.TXTRoad.Name = "TXTRoad";
            this.TXTRoad.Size = new System.Drawing.Size(408, 20);
            this.TXTRoad.TabIndex = 9;
            // 
            // BTNSelectRoad
            // 
            this.BTNSelectRoad.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNSelectRoad.Location = new System.Drawing.Point(426, 10);
            this.BTNSelectRoad.Name = "BTNSelectRoad";
            this.BTNSelectRoad.Size = new System.Drawing.Size(36, 23);
            this.BTNSelectRoad.TabIndex = 8;
            this.BTNSelectRoad.Text = "...";
            this.BTNSelectRoad.UseVisualStyleBackColor = true;
            this.BTNSelectRoad.Click += new System.EventHandler(this.BTNSelectRoad_Click);
            // 
            // FrmMoveToXML
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 409);
            this.Controls.Add(this.TXTDataSource);
            this.Controls.Add(this.BTNSelectDataSource);
            this.Controls.Add(this.TXTRoad);
            this.Controls.Add(this.BTNSelectRoad);
            this.Controls.Add(this.LBLCurrentRoadObjectTitle);
            this.Controls.Add(this.PBImport);
            this.Controls.Add(this.BtnImport);
            this.Controls.Add(this.TVRoadObjects);
            this.Name = "FrmMoveToXML";
            this.Text = "Выгрузка в XML";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView TVRoadObjects;
        private System.Windows.Forms.Button BtnImport;
        private System.Windows.Forms.FolderBrowserDialog XMLFldBrowserDlg;
        private System.Windows.Forms.ProgressBar PBImport;
        private System.Windows.Forms.Label LBLCurrentRoadObjectTitle;
        private System.Windows.Forms.TextBox TXTDataSource;
        private System.Windows.Forms.Button BTNSelectDataSource;
        private System.Windows.Forms.TextBox TXTRoad;
        private System.Windows.Forms.Button BTNSelectRoad;
    }
}