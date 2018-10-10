namespace RoadImporter
{
    partial class FrmSelectRoad
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
            this.GRDRoads = new System.Windows.Forms.DataGridView();
            this.colNumRoad = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColTitle = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColDistrictTitle = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TXTNumRoadFilter = new System.Windows.Forms.TextBox();
            this.BTNOK = new System.Windows.Forms.Button();
            this.BTNCancel = new System.Windows.Forms.Button();
            this.TXTFullTitleFilter = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.GRDRoads)).BeginInit();
            this.SuspendLayout();
            // 
            // GRDRoads
            // 
            this.GRDRoads.AllowUserToAddRows = false;
            this.GRDRoads.AllowUserToDeleteRows = false;
            this.GRDRoads.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.GRDRoads.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GRDRoads.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colNumRoad,
            this.ColTitle,
            this.ColDistrictTitle});
            this.GRDRoads.Location = new System.Drawing.Point(12, 38);
            this.GRDRoads.Name = "GRDRoads";
            this.GRDRoads.ReadOnly = true;
            this.GRDRoads.RowHeadersVisible = false;
            this.GRDRoads.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.GRDRoads.Size = new System.Drawing.Size(572, 386);
            this.GRDRoads.TabIndex = 0;
            this.GRDRoads.DoubleClick += new System.EventHandler(this.GRDRoads_DoubleClick);
            // 
            // colNumRoad
            // 
            this.colNumRoad.DataPropertyName = "id_";
            this.colNumRoad.HeaderText = "Код";
            this.colNumRoad.Name = "colNumRoad";
            this.colNumRoad.ReadOnly = true;
            // 
            // ColTitle
            // 
            this.ColTitle.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColTitle.DataPropertyName = "FullTitle";
            this.ColTitle.HeaderText = "Наименование";
            this.ColTitle.Name = "ColTitle";
            this.ColTitle.ReadOnly = true;
            // 
            // ColDistrictTitle
            // 
            this.ColDistrictTitle.DataPropertyName = "DistrictTitle";
            this.ColDistrictTitle.HeaderText = "Район";
            this.ColDistrictTitle.Name = "ColDistrictTitle";
            this.ColDistrictTitle.ReadOnly = true;
            // 
            // TXTNumRoadFilter
            // 
            this.TXTNumRoadFilter.Location = new System.Drawing.Point(12, 12);
            this.TXTNumRoadFilter.Name = "TXTNumRoadFilter";
            this.TXTNumRoadFilter.Size = new System.Drawing.Size(100, 20);
            this.TXTNumRoadFilter.TabIndex = 1;
            this.TXTNumRoadFilter.TextChanged += new System.EventHandler(this.TXTNumRoadFilter_TextChanged);
            this.TXTNumRoadFilter.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TXTNumRoadFilter_KeyDown);
            // 
            // BTNOK
            // 
            this.BTNOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.BTNOK.Location = new System.Drawing.Point(428, 430);
            this.BTNOK.Name = "BTNOK";
            this.BTNOK.Size = new System.Drawing.Size(75, 23);
            this.BTNOK.TabIndex = 2;
            this.BTNOK.Text = "ОК";
            this.BTNOK.UseVisualStyleBackColor = true;
            // 
            // BTNCancel
            // 
            this.BTNCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.BTNCancel.Location = new System.Drawing.Point(509, 430);
            this.BTNCancel.Name = "BTNCancel";
            this.BTNCancel.Size = new System.Drawing.Size(75, 23);
            this.BTNCancel.TabIndex = 3;
            this.BTNCancel.Text = "Отмена";
            this.BTNCancel.UseVisualStyleBackColor = true;
            // 
            // TXTFullTitleFilter
            // 
            this.TXTFullTitleFilter.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TXTFullTitleFilter.Location = new System.Drawing.Point(118, 12);
            this.TXTFullTitleFilter.Name = "TXTFullTitleFilter";
            this.TXTFullTitleFilter.Size = new System.Drawing.Size(466, 20);
            this.TXTFullTitleFilter.TabIndex = 4;
            this.TXTFullTitleFilter.TextChanged += new System.EventHandler(this.TXTFullTitleFilter_TextChanged);
            // 
            // FrmSelectRoad
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(596, 458);
            this.Controls.Add(this.TXTFullTitleFilter);
            this.Controls.Add(this.BTNCancel);
            this.Controls.Add(this.BTNOK);
            this.Controls.Add(this.TXTNumRoadFilter);
            this.Controls.Add(this.GRDRoads);
            this.Name = "FrmSelectRoad";
            this.Text = "FrmSelectRoad";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmSelectRoad_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.GRDRoads)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView GRDRoads;
        private System.Windows.Forms.TextBox TXTNumRoadFilter;
        private System.Windows.Forms.Button BTNOK;
        private System.Windows.Forms.Button BTNCancel;
        private System.Windows.Forms.TextBox TXTFullTitleFilter;
        private System.Windows.Forms.DataGridViewTextBoxColumn colNumRoad;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColTitle;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColDistrictTitle;
    }
}