using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace UnityBuild
{
    public partial class InputBox : Form
    {
        public string Input
        {
            get { return this.TextBox_Input.Text; }
            set { this.TextBox_Input.Text = value; }
        }

        public InputBox()
        {
            this.InitializeComponent();
        }

        private void Button_OK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        public static DialogResult Show(string caption, string text, ref string input)
        {
            InputBox form = new InputBox();
            form.Text = caption;
            form.Label_Message.Text = text;
            form.Input = input;

            DialogResult result = form.ShowDialog();
            input = form.Input;
            return result;
        }
    }
}