namespace MyOfficeX.COM
{
    partial class MyOfficeX
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.myRichEditControl1 = new RichEditConrol.MyRichEditControl();
            this.SuspendLayout();
            // 
            // myRichEditControl1
            // 
            this.myRichEditControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.myRichEditControl1.Location = new System.Drawing.Point(0, 0);
            this.myRichEditControl1.Name = "myRichEditControl1";
            this.myRichEditControl1.Size = new System.Drawing.Size(502, 334);
            this.myRichEditControl1.TabIndex = 0;
            // 
            // MyOfficeX
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.myRichEditControl1);
            this.Name = "MyOfficeX";
            this.Size = new System.Drawing.Size(502, 334);
            this.ResumeLayout(false);

        }

        #endregion

        private RichEditConrol.MyRichEditControl myRichEditControl1;
    }
}
