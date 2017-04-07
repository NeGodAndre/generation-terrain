namespace Shell
{
    partial class Form2
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
            this.label1 = new System.Windows.Forms.Label();
            this.waySkyBoxTextBox = new System.Windows.Forms.TextBox();
            this.waySkyBox = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.harshnessTextBox = new System.Windows.Forms.TextBox();
            this.resolutionСomboBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.rapidityTextBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.heightFactorTextBox = new System.Windows.Forms.TextBox();
            this.saveButton = new System.Windows.Forms.Button();
            this.defaultButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Путь к SkyBox";
            // 
            // waySkyBoxTextBox
            // 
            this.waySkyBoxTextBox.Location = new System.Drawing.Point(88, 6);
            this.waySkyBoxTextBox.Name = "waySkyBoxTextBox";
            this.waySkyBoxTextBox.Size = new System.Drawing.Size(460, 20);
            this.waySkyBoxTextBox.TabIndex = 1;
            // 
            // waySkyBox
            // 
            this.waySkyBox.Location = new System.Drawing.Point(554, 4);
            this.waySkyBox.Name = "waySkyBox";
            this.waySkyBox.Size = new System.Drawing.Size(25, 23);
            this.waySkyBox.TabIndex = 2;
            this.waySkyBox.Text = "...";
            this.waySkyBox.UseVisualStyleBackColor = true;
            this.waySkyBox.Click += new System.EventHandler(this.waySkyBox_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(176, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Разрешение окна визуализатора";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(148, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Резкость поворота камеры";
            // 
            // harshnessTextBox
            // 
            this.harshnessTextBox.Location = new System.Drawing.Point(166, 86);
            this.harshnessTextBox.Name = "harshnessTextBox";
            this.harshnessTextBox.Size = new System.Drawing.Size(100, 20);
            this.harshnessTextBox.TabIndex = 5;
            // 
            // resolutionСomboBox
            // 
            this.resolutionСomboBox.DisplayMember = "1";
            this.resolutionСomboBox.FormattingEnabled = true;
            this.resolutionСomboBox.Items.AddRange(new object[] {
            "640 x 480",
            "800 x 600",
            "1024 x 768",
            "1152 x 864",
            "1280 x 720",
            "1280 x 1024",
            "1920 x 1080"});
            this.resolutionСomboBox.Location = new System.Drawing.Point(194, 41);
            this.resolutionСomboBox.Name = "resolutionСomboBox";
            this.resolutionСomboBox.Size = new System.Drawing.Size(157, 21);
            this.resolutionСomboBox.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 115);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(133, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Быстрота передвижения";
            // 
            // rapidityTextBox
            // 
            this.rapidityTextBox.Location = new System.Drawing.Point(166, 112);
            this.rapidityTextBox.Name = "rapidityTextBox";
            this.rapidityTextBox.Size = new System.Drawing.Size(100, 20);
            this.rapidityTextBox.TabIndex = 8;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(321, 89);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(148, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Параметр маштабирования";
            // 
            // heightFactorTextBox
            // 
            this.heightFactorTextBox.Location = new System.Drawing.Point(472, 86);
            this.heightFactorTextBox.Name = "heightFactorTextBox";
            this.heightFactorTextBox.Size = new System.Drawing.Size(107, 20);
            this.heightFactorTextBox.TabIndex = 10;
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(15, 171);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(100, 23);
            this.saveButton.TabIndex = 11;
            this.saveButton.Text = "сохранить";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // defaultButton
            // 
            this.defaultButton.Location = new System.Drawing.Point(479, 171);
            this.defaultButton.Name = "defaultButton";
            this.defaultButton.Size = new System.Drawing.Size(100, 23);
            this.defaultButton.TabIndex = 12;
            this.defaultButton.Text = "По умолчанию";
            this.defaultButton.UseVisualStyleBackColor = true;
            this.defaultButton.Click += new System.EventHandler(this.defaultButton_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 205);
            this.Controls.Add(this.defaultButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.heightFactorTextBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.rapidityTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.resolutionСomboBox);
            this.Controls.Add(this.harshnessTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.waySkyBox);
            this.Controls.Add(this.waySkyBoxTextBox);
            this.Controls.Add(this.label1);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox waySkyBoxTextBox;
        private System.Windows.Forms.Button waySkyBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox harshnessTextBox;
        private System.Windows.Forms.ComboBox resolutionСomboBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox rapidityTextBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox heightFactorTextBox;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button defaultButton;
    }
}