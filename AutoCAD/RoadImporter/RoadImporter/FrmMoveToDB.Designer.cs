namespace RoadImporter
{
    partial class FrmMoveToDB
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
            this.XMLFldBrowserDlg = new System.Windows.Forms.FolderBrowserDialog();
            this.BtnChooseDir = new System.Windows.Forms.Button();
            this.BtnImport = new System.Windows.Forms.Button();
            this.TxtXMLPath = new System.Windows.Forms.TextBox();
            this.CHKDeleteData = new System.Windows.Forms.CheckBox();
            this.TXTRoad = new System.Windows.Forms.TextBox();
            this.BTNSelectRoad = new System.Windows.Forms.Button();
            this.TXTDataSource = new System.Windows.Forms.TextBox();
            this.BTNSelectDataSource = new System.Windows.Forms.Button();
            this.lblXMLPath = new System.Windows.Forms.Label();
            this.LBLCurrentRoadObjectTitle = new System.Windows.Forms.Label();
            this.PBImport = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // BtnChooseDir
            // 
            this.BtnChooseDir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnChooseDir.Location = new System.Drawing.Point(392, 23);
            this.BtnChooseDir.Name = "BtnChooseDir";
            this.BtnChooseDir.Size = new System.Drawing.Size(36, 24);
            this.BtnChooseDir.TabIndex = 0;
            this.BtnChooseDir.Text = "...";
            this.BtnChooseDir.UseVisualStyleBackColor = true;
            this.BtnChooseDir.Click += new System.EventHandler(this.BtnChooseDir_Click);
            // 
            // BtnImport
            // 
            this.BtnImport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BtnImport.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.BtnImport.Location = new System.Drawing.Point(333, 260);
            this.BtnImport.Name = "BtnImport";
            this.BtnImport.Size = new System.Drawing.Size(95, 23);
            this.BtnImport.TabIndex = 2;
            this.BtnImport.Text = "Загрузить";
            this.BtnImport.UseVisualStyleBackColor = true;
            this.BtnImport.Click += new System.EventHandler(this.BtnImport_Click);
            // 
            // TxtXMLPath
            // 
            this.TxtXMLPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TxtXMLPath.Enabled = false;
            this.TxtXMLPath.Location = new System.Drawing.Point(12, 26);
            this.TxtXMLPath.Name = "TxtXMLPath";
            this.TxtXMLPath.Size = new System.Drawing.Size(377, 20);
            this.TxtXMLPath.TabIndex = 1;
            // 
            // CHKDeleteData
            // 
            this.CHKDeleteData.AutoSize = true;
            this.CHKDeleteData.Location = new System.Drawing.Point(12, 146);
            this.CHKDeleteData.Name = "CHKDeleteData";
            this.CHKDeleteData.Size = new System.Drawing.Size(156, 17);
            this.CHKDeleteData.TabIndex = 3;
            this.CHKDeleteData.Text = "Очистить перед вставкой";
            this.CHKDeleteData.UseVisualStyleBackColor = true;
            // 
            // TXTRoad
            // 
            this.TXTRoad.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TXTRoad.Enabled = false;
            this.TXTRoad.Location = new System.Drawing.Point(12, 83);
            this.TXTRoad.Name = "TXTRoad";
            this.TXTRoad.Size = new System.Drawing.Size(377, 20);
            this.TXTRoad.TabIndex = 5;
            // 
            // BTNSelectRoad
            // 
            this.BTNSelectRoad.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNSelectRoad.Location = new System.Drawing.Point(392, 81);
            this.BTNSelectRoad.Name = "BTNSelectRoad";
            this.BTNSelectRoad.Size = new System.Drawing.Size(36, 23);
            this.BTNSelectRoad.TabIndex = 4;
            this.BTNSelectRoad.Text = "...";
            this.BTNSelectRoad.UseVisualStyleBackColor = true;
            this.BTNSelectRoad.Click += new System.EventHandler(this.BTNSelectRoad_Click);
            // 
            // TXTDataSource
            // 
            this.TXTDataSource.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TXTDataSource.Enabled = false;
            this.TXTDataSource.Location = new System.Drawing.Point(12, 108);
            this.TXTDataSource.Name = "TXTDataSource";
            this.TXTDataSource.Size = new System.Drawing.Size(377, 20);
            this.TXTDataSource.TabIndex = 7;
            // 
            // BTNSelectDataSource
            // 
            this.BTNSelectDataSource.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNSelectDataSource.Location = new System.Drawing.Point(392, 106);
            this.BTNSelectDataSource.Name = "BTNSelectDataSource";
            this.BTNSelectDataSource.Size = new System.Drawing.Size(36, 23);
            this.BTNSelectDataSource.TabIndex = 6;
            this.BTNSelectDataSource.Text = "...";
            this.BTNSelectDataSource.UseVisualStyleBackColor = true;
            this.BTNSelectDataSource.Click += new System.EventHandler(this.BTNSelectDataSource_Click);
            // 
            // lblXMLPath
            // 
            this.lblXMLPath.AutoSize = true;
            this.lblXMLPath.Location = new System.Drawing.Point(9, 9);
            this.lblXMLPath.Name = "lblXMLPath";
            this.lblXMLPath.Size = new System.Drawing.Size(65, 13);
            this.lblXMLPath.TabIndex = 8;
            this.lblXMLPath.Text = "Путь к XML";
            // 
            // LBLCurrentRoadObjectTitle
            // 
            this.LBLCurrentRoadObjectTitle.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LBLCurrentRoadObjectTitle.AutoSize = true;
            this.LBLCurrentRoadObjectTitle.Location = new System.Drawing.Point(9, 250);
            this.LBLCurrentRoadObjectTitle.Name = "LBLCurrentRoadObjectTitle";
            this.LBLCurrentRoadObjectTitle.Size = new System.Drawing.Size(0, 13);
            this.LBLCurrentRoadObjectTitle.TabIndex = 10;
            // 
            // PBImport
            // 
            this.PBImport.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PBImport.Location = new System.Drawing.Point(12, 216);
            this.PBImport.Name = "PBImport";
            this.PBImport.Size = new System.Drawing.Size(416, 23);
            this.PBImport.TabIndex = 9;
            // 
            // FrmMoveToDB
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(440, 295);
            this.Controls.Add(this.LBLCurrentRoadObjectTitle);
            this.Controls.Add(this.PBImport);
            this.Controls.Add(this.lblXMLPath);
            this.Controls.Add(this.TXTDataSource);
            this.Controls.Add(this.BTNSelectDataSource);
            this.Controls.Add(this.TXTRoad);
            this.Controls.Add(this.BTNSelectRoad);
            this.Controls.Add(this.CHKDeleteData);
            this.Controls.Add(this.BtnImport);
            this.Controls.Add(this.TxtXMLPath);
            this.Controls.Add(this.BtnChooseDir);
            this.Name = "FrmMoveToDB";
            this.Text = "Загрузить в БД";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.FolderBrowserDialog XMLFldBrowserDlg;
        private System.Windows.Forms.Button BtnChooseDir;
        private System.Windows.Forms.Button BtnImport;
        private System.Windows.Forms.TextBox TxtXMLPath;
        private System.Windows.Forms.CheckBox CHKDeleteData;
        private System.Windows.Forms.TextBox TXTRoad;
        private System.Windows.Forms.Button BTNSelectRoad;
        private System.Windows.Forms.TextBox TXTDataSource;
        private System.Windows.Forms.Button BTNSelectDataSource;
        private System.Windows.Forms.Label lblXMLPath;
        private System.Windows.Forms.Label LBLCurrentRoadObjectTitle;
        private System.Windows.Forms.ProgressBar PBImport;
    }
}