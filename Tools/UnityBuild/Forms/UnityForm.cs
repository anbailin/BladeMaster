using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using Extensibility;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.CommandBars;
using System.Resources;
using System.Reflection;
using System.Globalization;
using System.Diagnostics;
using System.Data;
using Microsoft.VisualStudio.VCProjectEngine;

namespace UnityBuild
{
    public partial class UnityForm : Form
    {
        private UnityManager UnityManager;
        private DataTable Cpps;

        public UnityForm(VCProject project)
        {
            this.UnityManager = new UnityManager(project);

            this.Cpps = new DataTable();
            this.Cpps.Columns.Add("Cpp");
            this.Cpps.Columns.Add("VirtualPath");
            this.Cpps.Columns.Add("Unity");
            this.Cpps.Columns.Add("Condition");
            this.Cpps.Columns.Add("Size", typeof(long));

            this.InitializeComponent();
        }

        private void UnityForm_Load(object sender, EventArgs e)
        {
            this.UnityManager.LoadUnities();
            this.UnityManager.LoadCpps();

            this.UpdateCpps();
            this.DataGridView.DataSource = this.Cpps;

            this.TextBox_UnityFilter.Text = this.UnityManager.Filter.Name;
            this.TextBox_UnityFolder.Text = this.UnityManager.Filter.Path;

            this.Label_Status.Text = "";
            this.TextBox_Prefix.Text = this.UnityManager.Project.Name + UnityFilter.DefaultName;
        }

        private void Button_OK_Click(object sender, EventArgs e)
        {
            this.Apply();
            this.Close();
        }

        private void Button_Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Button_Apply_Click(object sender, EventArgs e)
        {
            this.Apply();
        }

        private void Button_ApplySettings_Click(object sender, EventArgs e)
        {
            if (this.TextBox_UnityFilter.Text.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                Utils.ShowWarning("Illegal character in Unity Filter.");
                return;
            }

            if (this.TextBox_UnityFolder.Text.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                Utils.ShowWarning("Illegal character in Unity Folder.");
                return;
            }

            this.UnityManager.Filter.Name = this.TextBox_UnityFilter.Text;
            this.UnityManager.Filter.Path = this.TextBox_UnityFolder.Text;
            this.UnityManager.Filter.SaveSettings();

            this.UnityManager.LoadUnities();
            this.UnityManager.LoadCpps();
            this.UpdateCpps();
        }

        private void Button_AutoUnity_Click(object sender, EventArgs e)
        {
            if (this.DataGridView.Rows.Count == 0)
            {
                Utils.ShowWarning("No cpp files.");
                return;
            }

            if (this.TextBox_Prefix.Text.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                Utils.ShowWarning("Illegal character in Unity Prefix.");
                return;
            }

            if (this.TextBox_Prefix.Text.Trim() == "")
            {
                Utils.ShowWarning("Unity Prefix can not be empty.");
                return;
            }

            this.AutoUnity();
        }

        private void ContextMenuStrip_Opening(object sender, CancelEventArgs e)
        {
            if (this.DataGridView.SelectedRows.Count == 0)
            {
                e.Cancel = true;
                return;
            }
        }

        private void ToolStripMenuItem_SetUnity_Click(object sender, EventArgs e)
        {
            if (this.DataGridView.SelectedRows.Count == 0) return;

            string unity = this.DataGridView.SelectedRows[0].Cells[2].Value as string;
            if (InputBox.Show("Set Unity", "Unity Name:", ref unity) == DialogResult.OK)
            {
                foreach (DataGridViewRow row in this.DataGridView.SelectedRows)
                {
                    (row.DataBoundItem as DataRowView).Row[2] = unity;
                }
            }
        }

        private void ToolStripMenuItem_SetCondition_Click(object sender, EventArgs e)
        {
            if (this.DataGridView.SelectedRows.Count == 0) return;

            string condition = this.DataGridView.SelectedRows[0].Cells[3].Value as string;
            if (InputBox.Show("Set Condition", "Condition:", ref condition) == DialogResult.OK)
            {
                foreach (DataGridViewRow row in this.DataGridView.SelectedRows)
                {
                    (row.DataBoundItem as DataRowView).Row[3] = condition;
                }
            }
        }

        private void DataGridView_SelectionChanged(object sender, EventArgs e)
        {
            if (this.DataGridView.SelectedRows.Count > 0)
            {
                long size = 0;
                foreach (DataGridViewRow row in this.DataGridView.SelectedRows)
                {
                    size += (long)(row.DataBoundItem as DataRowView).Row[4];
                }
                size = (size + 1024) / 1024;
                this.Label_Status.Text = string.Format("{0} cpps selected, {1} KB.", this.DataGridView.SelectedRows.Count, size);
            }
            else
            {
                this.Label_Status.Text = "";
            }
        }

        private void UpdateCpps()
        {
            this.DataGridView.SuspendLayout();
            this.Cpps.Rows.Clear();

            foreach (Cpp cpp in this.UnityManager.Cpps.Values)
            {
                this.Cpps.Rows.Add(cpp.Name, cpp.VirtualPath, cpp.UnityName, cpp.Condition, cpp.Size);
            }

            this.DataGridView.ResumeLayout();
        }

        private void Apply()
        {
            this.UnityManager.Filter.Name = this.TextBox_UnityFilter.Text;
            this.UnityManager.Filter.Path = this.TextBox_UnityFolder.Text;
            this.UnityManager.Filter.SaveSettings();

            this.UnityManager.Unities = new Dictionary<string, Unity>();

            foreach (DataRow row in this.Cpps.Rows)
            {
                string unityname = row[2] as string;

                if (!String.IsNullOrEmpty(unityname))
                {
                    unityname.Trim();

                    Unity unity = null;
                    if (!this.UnityManager.Unities.TryGetValue(unityname, out unity))
                    {
                        unity = new Unity(unityname);
                        this.UnityManager.Unities.Add(unityname, unity);
                    }

                    Cpp cpp = new Cpp(row[0] as string);

                    cpp.Condition = row[3] as string;
                    if (cpp.Condition != null) cpp.Condition.Trim();

                    unity.Cpps.Add(cpp.Name, cpp);
                }
            }

            this.UnityManager.SaveUnities();
        }

        private void AutoUnity()
        {
            long max_size = (long)this.NumericUpDown_Size.Value * 1024;
            int max_files = (int)this.NumericUpDown_Files.Value;

            int unity_index = 1;
            int unity_files = 0;
            long unity_size = 0;

            foreach (DataGridViewRow row in this.DataGridView.Rows)
            {
                long cpp_size = (long)(row.DataBoundItem as DataRowView).Row[4];

                if (unity_size > 0 && (unity_size + cpp_size > max_size || unity_files > max_files))
                {
                    unity_index++;
                    unity_size = 0;
                    unity_files = 0;
                }

                (row.DataBoundItem as DataRowView).Row[2] = this.TextBox_Prefix.Text + unity_index.ToString();

                unity_size += cpp_size;
                unity_files++;
            }
        }
    }
}