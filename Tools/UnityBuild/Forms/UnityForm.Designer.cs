namespace UnityBuild
{
    partial class UnityForm
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.Button_OK = new System.Windows.Forms.Button();
            this.Button_Cancel = new System.Windows.Forms.Button();
            this.Button_Apply = new System.Windows.Forms.Button();
            this.DataGridView = new System.Windows.Forms.DataGridView();
            this.Column_Cpp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_VirtualPath = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Unity = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Condition = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column_Size = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ContextMenuStrip_Cpp = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ToolStripMenuItem_SetUnity = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem_SetCondition = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.TextBox_UnityFolder = new System.Windows.Forms.TextBox();
            this.TextBox_UnityFilter = new System.Windows.Forms.TextBox();
            this.Button_ApplySettings = new System.Windows.Forms.Button();
            this.Label_Status = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.TextBox_Prefix = new System.Windows.Forms.TextBox();
            this.NumericUpDown_Size = new System.Windows.Forms.NumericUpDown();
            this.NumericUpDown_Files = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Button_AutoUnity = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.DataGridView)).BeginInit();
            this.ContextMenuStrip_Cpp.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDown_Size)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDown_Files)).BeginInit();
            this.SuspendLayout();
            // 
            // Button_OK
            // 
            this.Button_OK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_OK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Button_OK.Location = new System.Drawing.Point(543, 490);
            this.Button_OK.Name = "Button_OK";
            this.Button_OK.Size = new System.Drawing.Size(75, 21);
            this.Button_OK.TabIndex = 4;
            this.Button_OK.Text = "OK";
            this.Button_OK.UseVisualStyleBackColor = true;
            this.Button_OK.Click += new System.EventHandler(this.Button_OK_Click);
            // 
            // Button_Cancel
            // 
            this.Button_Cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Button_Cancel.Location = new System.Drawing.Point(624, 490);
            this.Button_Cancel.Name = "Button_Cancel";
            this.Button_Cancel.Size = new System.Drawing.Size(75, 21);
            this.Button_Cancel.TabIndex = 5;
            this.Button_Cancel.Text = "Cancel";
            this.Button_Cancel.UseVisualStyleBackColor = true;
            this.Button_Cancel.Click += new System.EventHandler(this.Button_Cancel_Click);
            // 
            // Button_Apply
            // 
            this.Button_Apply.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_Apply.Location = new System.Drawing.Point(705, 490);
            this.Button_Apply.Name = "Button_Apply";
            this.Button_Apply.Size = new System.Drawing.Size(75, 21);
            this.Button_Apply.TabIndex = 6;
            this.Button_Apply.Text = "Apply";
            this.Button_Apply.UseVisualStyleBackColor = true;
            this.Button_Apply.Click += new System.EventHandler(this.Button_Apply_Click);
            // 
            // DataGridView
            // 
            this.DataGridView.AllowUserToAddRows = false;
            this.DataGridView.AllowUserToDeleteRows = false;
            this.DataGridView.AllowUserToResizeRows = false;
            this.DataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.DataGridView.BackgroundColor = System.Drawing.SystemColors.Window;
            this.DataGridView.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.DataGridView.ClipboardCopyMode = System.Windows.Forms.DataGridViewClipboardCopyMode.Disable;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("NSimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DataGridView.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.DataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column_Cpp,
            this.Column_VirtualPath,
            this.Column_Unity,
            this.Column_Condition,
            this.Column_Size});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.DataGridView.DefaultCellStyle = dataGridViewCellStyle2;
            this.DataGridView.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.DataGridView.Location = new System.Drawing.Point(12, 116);
            this.DataGridView.Name = "DataGridView";
            this.DataGridView.RowHeadersVisible = false;
            this.DataGridView.RowHeadersWidth = 30;
            this.DataGridView.RowTemplate.ContextMenuStrip = this.ContextMenuStrip_Cpp;
            this.DataGridView.RowTemplate.DefaultCellStyle.Font = new System.Drawing.Font("NSimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DataGridView.RowTemplate.Height = 18;
            this.DataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.DataGridView.Size = new System.Drawing.Size(768, 314);
            this.DataGridView.TabIndex = 7;
            this.DataGridView.SelectionChanged += new System.EventHandler(this.DataGridView_SelectionChanged);
            // 
            // Column_Cpp
            // 
            this.Column_Cpp.DataPropertyName = "Cpp";
            this.Column_Cpp.HeaderText = "Cpp";
            this.Column_Cpp.Name = "Column_Cpp";
            this.Column_Cpp.ReadOnly = true;
            this.Column_Cpp.Width = 266;
            // 
            // Column_VirtualPath
            // 
            this.Column_VirtualPath.DataPropertyName = "VirtualPath";
            this.Column_VirtualPath.HeaderText = "Virtual Path";
            this.Column_VirtualPath.Name = "Column_VirtualPath";
            this.Column_VirtualPath.ReadOnly = true;
            this.Column_VirtualPath.Width = 200;
            // 
            // Column_Unity
            // 
            this.Column_Unity.DataPropertyName = "Unity";
            this.Column_Unity.HeaderText = "Unity";
            this.Column_Unity.Name = "Column_Unity";
            this.Column_Unity.Width = 150;
            // 
            // Column_Condition
            // 
            this.Column_Condition.DataPropertyName = "Condition";
            this.Column_Condition.HeaderText = "Condition";
            this.Column_Condition.Name = "Column_Condition";
            // 
            // Column_Size
            // 
            this.Column_Size.DataPropertyName = "Size";
            this.Column_Size.HeaderText = "Size";
            this.Column_Size.Name = "Column_Size";
            this.Column_Size.ReadOnly = true;
            this.Column_Size.Width = 50;
            // 
            // ContextMenuStrip_Cpp
            // 
            this.ContextMenuStrip_Cpp.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem_SetUnity,
            this.ToolStripMenuItem_SetCondition});
            this.ContextMenuStrip_Cpp.Name = "ContextMenuStrip";
            this.ContextMenuStrip_Cpp.Size = new System.Drawing.Size(155, 48);
            this.ContextMenuStrip_Cpp.Opening += new System.ComponentModel.CancelEventHandler(this.ContextMenuStrip_Opening);
            // 
            // ToolStripMenuItem_SetUnity
            // 
            this.ToolStripMenuItem_SetUnity.Name = "ToolStripMenuItem_SetUnity";
            this.ToolStripMenuItem_SetUnity.Size = new System.Drawing.Size(154, 22);
            this.ToolStripMenuItem_SetUnity.Text = "Set Unity";
            this.ToolStripMenuItem_SetUnity.Click += new System.EventHandler(this.ToolStripMenuItem_SetUnity_Click);
            // 
            // ToolStripMenuItem_SetCondition
            // 
            this.ToolStripMenuItem_SetCondition.Name = "ToolStripMenuItem_SetCondition";
            this.ToolStripMenuItem_SetCondition.Size = new System.Drawing.Size(154, 22);
            this.ToolStripMenuItem_SetCondition.Text = "Set Condition";
            this.ToolStripMenuItem_SetCondition.Click += new System.EventHandler(this.ToolStripMenuItem_SetCondition_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.TextBox_UnityFolder);
            this.groupBox1.Controls.Add(this.TextBox_UnityFilter);
            this.groupBox1.Controls.Add(this.Button_ApplySettings);
            this.groupBox1.Location = new System.Drawing.Point(12, 11);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(768, 99);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Settings";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Unity Folder:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Unity Filter:";
            // 
            // TextBox_UnityFolder
            // 
            this.TextBox_UnityFolder.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TextBox_UnityFolder.Location = new System.Drawing.Point(95, 42);
            this.TextBox_UnityFolder.Name = "TextBox_UnityFolder";
            this.TextBox_UnityFolder.Size = new System.Drawing.Size(667, 21);
            this.TextBox_UnityFolder.TabIndex = 0;
            // 
            // TextBox_UnityFilter
            // 
            this.TextBox_UnityFilter.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TextBox_UnityFilter.Location = new System.Drawing.Point(95, 18);
            this.TextBox_UnityFilter.Name = "TextBox_UnityFilter";
            this.TextBox_UnityFilter.Size = new System.Drawing.Size(667, 21);
            this.TextBox_UnityFilter.TabIndex = 0;
            // 
            // Button_ApplySettings
            // 
            this.Button_ApplySettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_ApplySettings.AutoSize = true;
            this.Button_ApplySettings.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Button_ApplySettings.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Button_ApplySettings.Location = new System.Drawing.Point(663, 71);
            this.Button_ApplySettings.Name = "Button_ApplySettings";
            this.Button_ApplySettings.Size = new System.Drawing.Size(99, 22);
            this.Button_ApplySettings.TabIndex = 4;
            this.Button_ApplySettings.Text = "Apply Settings";
            this.Button_ApplySettings.UseVisualStyleBackColor = true;
            this.Button_ApplySettings.Click += new System.EventHandler(this.Button_ApplySettings_Click);
            // 
            // Label_Status
            // 
            this.Label_Status.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Label_Status.AutoSize = true;
            this.Label_Status.Location = new System.Drawing.Point(9, 495);
            this.Label_Status.Name = "Label_Status";
            this.Label_Status.Size = new System.Drawing.Size(0, 12);
            this.Label_Status.TabIndex = 9;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.TextBox_Prefix);
            this.groupBox2.Controls.Add(this.NumericUpDown_Size);
            this.groupBox2.Controls.Add(this.NumericUpDown_Files);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.Button_AutoUnity);
            this.groupBox2.Location = new System.Drawing.Point(12, 436);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(768, 49);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Auto Unity";
            // 
            // TextBox_Prefix
            // 
            this.TextBox_Prefix.Location = new System.Drawing.Point(402, 19);
            this.TextBox_Prefix.Name = "TextBox_Prefix";
            this.TextBox_Prefix.Size = new System.Drawing.Size(200, 21);
            this.TextBox_Prefix.TabIndex = 5;
            // 
            // NumericUpDown_Size
            // 
            this.NumericUpDown_Size.Location = new System.Drawing.Point(88, 20);
            this.NumericUpDown_Size.Maximum = new decimal(new int[] {
            10240,
            0,
            0,
            0});
            this.NumericUpDown_Size.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDown_Size.Name = "NumericUpDown_Size";
            this.NumericUpDown_Size.Size = new System.Drawing.Size(100, 21);
            this.NumericUpDown_Size.TabIndex = 4;
            this.NumericUpDown_Size.Value = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            // 
            // NumericUpDown_Files
            // 
            this.NumericUpDown_Files.Location = new System.Drawing.Point(254, 20);
            this.NumericUpDown_Files.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.NumericUpDown_Files.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.NumericUpDown_Files.Name = "NumericUpDown_Files";
            this.NumericUpDown_Files.Size = new System.Drawing.Size(100, 21);
            this.NumericUpDown_Files.TabIndex = 3;
            this.NumericUpDown_Files.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(360, 22);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "Prefix:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(194, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "Max Files:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(89, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "Max Size (KB):";
            // 
            // Button_AutoUnity
            // 
            this.Button_AutoUnity.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_AutoUnity.Location = new System.Drawing.Point(687, 18);
            this.Button_AutoUnity.Name = "Button_AutoUnity";
            this.Button_AutoUnity.Size = new System.Drawing.Size(75, 21);
            this.Button_AutoUnity.TabIndex = 0;
            this.Button_AutoUnity.Text = "Auto Unity";
            this.Button_AutoUnity.UseVisualStyleBackColor = true;
            this.Button_AutoUnity.Click += new System.EventHandler(this.Button_AutoUnity_Click);
            // 
            // UnityForm
            // 
            this.AcceptButton = this.Button_OK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.Button_Cancel;
            this.ClientSize = new System.Drawing.Size(792, 522);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.Label_Status);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.DataGridView);
            this.Controls.Add(this.Button_Apply);
            this.Controls.Add(this.Button_Cancel);
            this.Controls.Add(this.Button_OK);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(500, 300);
            this.Name = "UnityForm";
            this.ShowIcon = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Unity Build";
            this.Load += new System.EventHandler(this.UnityForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DataGridView)).EndInit();
            this.ContextMenuStrip_Cpp.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDown_Size)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NumericUpDown_Files)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Button_OK;
        private System.Windows.Forms.Button Button_Cancel;
        private System.Windows.Forms.Button Button_Apply;
        private System.Windows.Forms.DataGridView DataGridView;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox TextBox_UnityFolder;
        private System.Windows.Forms.TextBox TextBox_UnityFilter;
        private System.Windows.Forms.Button Button_ApplySettings;
        private System.Windows.Forms.ContextMenuStrip ContextMenuStrip_Cpp;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_SetUnity;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_SetCondition;
        private System.Windows.Forms.Label Label_Status;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button Button_AutoUnity;
        private System.Windows.Forms.NumericUpDown NumericUpDown_Size;
        private System.Windows.Forms.NumericUpDown NumericUpDown_Files;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox TextBox_Prefix;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Cpp;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_VirtualPath;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Unity;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Condition;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column_Size;
    }
}