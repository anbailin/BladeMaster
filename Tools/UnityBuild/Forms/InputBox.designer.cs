namespace UnityBuild
{
    partial class InputBox
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
            this.Button_OK = new System.Windows.Forms.Button();
            this.Button_Cancel = new System.Windows.Forms.Button();
            this.Label_Message = new System.Windows.Forms.Label();
            this.TextBox_Input = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // Button_OK
            // 
            this.Button_OK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_OK.Location = new System.Drawing.Point(326, 56);
            this.Button_OK.Name = "Button_OK";
            this.Button_OK.Size = new System.Drawing.Size(75, 21);
            this.Button_OK.TabIndex = 2;
            this.Button_OK.Text = "OK";
            this.Button_OK.UseVisualStyleBackColor = true;
            this.Button_OK.Click += new System.EventHandler(this.Button_OK_Click);
            // 
            // Button_Cancel
            // 
            this.Button_Cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Button_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Button_Cancel.Location = new System.Drawing.Point(407, 56);
            this.Button_Cancel.Name = "Button_Cancel";
            this.Button_Cancel.Size = new System.Drawing.Size(75, 21);
            this.Button_Cancel.TabIndex = 3;
            this.Button_Cancel.Text = "Cancel";
            this.Button_Cancel.UseVisualStyleBackColor = true;
            // 
            // Label_Message
            // 
            this.Label_Message.AutoSize = true;
            this.Label_Message.Location = new System.Drawing.Point(12, 10);
            this.Label_Message.Name = "Label_Message";
            this.Label_Message.Size = new System.Drawing.Size(53, 12);
            this.Label_Message.TabIndex = 0;
            this.Label_Message.Text = "message:";
            // 
            // TextBox_Input
            // 
            this.TextBox_Input.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.TextBox_Input.Location = new System.Drawing.Point(12, 25);
            this.TextBox_Input.Name = "TextBox_Input";
            this.TextBox_Input.Size = new System.Drawing.Size(470, 21);
            this.TextBox_Input.TabIndex = 1;
            // 
            // InputBox
            // 
            this.AcceptButton = this.Button_OK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.Button_Cancel;
            this.ClientSize = new System.Drawing.Size(494, 88);
            this.Controls.Add(this.TextBox_Input);
            this.Controls.Add(this.Label_Message);
            this.Controls.Add(this.Button_Cancel);
            this.Controls.Add(this.Button_OK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "InputBox";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Button_OK;
        private System.Windows.Forms.Button Button_Cancel;
        private System.Windows.Forms.Label Label_Message;
        private System.Windows.Forms.TextBox TextBox_Input;
    }
}