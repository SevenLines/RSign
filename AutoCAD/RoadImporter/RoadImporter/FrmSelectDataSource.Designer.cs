namespace RoadImporter
{
    partial class FrmSelectDataSource
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
            this.GRDDataSources = new System.Windows.Forms.DataGridView();
            this.ColNumDataSource = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColTitle = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.BTNCancel = new System.Windows.Forms.Button();
            this.BTNOK = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.GRDDataSources)).BeginInit();
            this.SuspendLayout();
            // 
            // GRDDataSources
            // 
            this.GRDDataSources.AllowUserToAddRows = false;
            this.GRDDataSources.AllowUserToDeleteRows = false;
            this.GRDDataSources.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.GRDDataSources.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GRDDataSources.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColNumDataSource,
            this.ColTitle});
            this.GRDDataSources.Location = new System.Drawing.Point(12, 12);
            this.GRDDataSources.Name = "GRDDataSources";
            this.GRDDataSources.ReadOnly = true;
            this.GRDDataSources.RowHeadersVisible = false;
            this.GRDDataSources.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.GRDDataSources.Size = new System.Drawing.Size(555, 269);
            this.GRDDataSources.TabIndex = 0;
            this.GRDDataSources.DoubleClick += new System.EventHandler(this.GRDDataSources_DoubleClick);
            // 
            // ColNumDataSource
            // 
            this.ColNumDataSource.DataPropertyName = "id_";
            this.ColNumDataSource.HeaderText = "Код";
            this.ColNumDataSource.Name = "ColNumDataSource";
            this.ColNumDataSource.ReadOnly = true;
            // 
            // ColTitle
            // 
            this.ColTitle.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColTitle.DataPropertyName = "FullTitle";
            this.ColTitle.HeaderText = "Наименование";
            this.ColTitle.Name = "ColTitle";
            this.ColTitle.ReadOnly = true;
            // 
            // BTNCancel
            // 
            this.BTNCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.BTNCancel.Location = new System.Drawing.Point(492, 289);
            this.BTNCancel.Name = "BTNCancel";
            this.BTNCancel.Size = new System.Drawing.Size(75, 23);
            this.BTNCancel.TabIndex = 5;
            this.BTNCancel.Text = "Отмена";
            this.BTNCancel.UseVisualStyleBackColor = true;
            // 
            // BTNOK
            // 
            this.BTNOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.BTNOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.BTNOK.Location = new System.Drawing.Point(411, 289);
            this.BTNOK.Name = "BTNOK";
            this.BTNOK.Size = new System.Drawing.Size(75, 23);
            this.BTNOK.TabIndex = 4;
            this.BTNOK.Text = "ОК";
            this.BTNOK.UseVisualStyleBackColor = true;
            // 
            // FrmSelectDataSource
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(579, 324);
            this.Controls.Add(this.BTNCancel);
            this.Controls.Add(this.BTNOK);
            this.Controls.Add(this.GRDDataSources);
            this.Name = "FrmSelectDataSource";
            this.Text = "FrmSelectDataSource";
            ((System.ComponentModel.ISupportInitialize)(this.GRDDataSources)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView GRDDataSources;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColNumDataSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColTitle;
        private System.Windows.Forms.Button BTNCancel;
        private System.Windows.Forms.Button BTNOK;
    }
}