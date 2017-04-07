namespace Shell
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.очиститьToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsBMPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsObjToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.настройкиToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.настройкиПрограммыToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsRendererToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.инфоToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.maxHeight = new System.Windows.Forms.TextBox();
            this.minHeight = new System.Windows.Forms.TextBox();
            this.width = new System.Windows.Forms.TextBox();
            this.lenght = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Максимальная высота";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Минимальная высота";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Ширина карты";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 108);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Длина карты";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.настройкиToolStripMenuItem,
            this.инфоToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(537, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.очиститьToolStripMenuItem,
            this.saveAsBMPToolStripMenuItem,
            this.saveAsObjToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(48, 20);
            this.toolStripMenuItem1.Text = "Файл";
            // 
            // очиститьToolStripMenuItem
            // 
            this.очиститьToolStripMenuItem.Name = "очиститьToolStripMenuItem";
            this.очиститьToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
            this.очиститьToolStripMenuItem.Text = "Очистить";
            // 
            // saveAsBMPToolStripMenuItem
            // 
            this.saveAsBMPToolStripMenuItem.Name = "saveAsBMPToolStripMenuItem";
            this.saveAsBMPToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
            this.saveAsBMPToolStripMenuItem.Text = "Сохранить как BMP";
            this.saveAsBMPToolStripMenuItem.Click += new System.EventHandler(this.saveAsBMPToolStripMenuItem_Click);
            // 
            // saveAsObjToolStripMenuItem
            // 
            this.saveAsObjToolStripMenuItem.Name = "saveAsObjToolStripMenuItem";
            this.saveAsObjToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
            this.saveAsObjToolStripMenuItem.Text = "Сохранить как Obj ";
            this.saveAsObjToolStripMenuItem.Click += new System.EventHandler(this.saveAsObjToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(181, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // настройкиToolStripMenuItem
            // 
            this.настройкиToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.настройкиПрограммыToolStripMenuItem,
            this.settingsRendererToolStripMenuItem});
            this.настройкиToolStripMenuItem.Name = "настройкиToolStripMenuItem";
            this.настройкиToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
            this.настройкиToolStripMenuItem.Text = "Настройки";
            this.настройкиToolStripMenuItem.Click += new System.EventHandler(this.настройкиToolStripMenuItem_Click);
            // 
            // настройкиПрограммыToolStripMenuItem
            // 
            this.настройкиПрограммыToolStripMenuItem.Name = "настройкиПрограммыToolStripMenuItem";
            this.настройкиПрограммыToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.настройкиПрограммыToolStripMenuItem.Text = "Настройки программы";
            // 
            // settingsRendererToolStripMenuItem
            // 
            this.settingsRendererToolStripMenuItem.Name = "settingsRendererToolStripMenuItem";
            this.settingsRendererToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.settingsRendererToolStripMenuItem.Text = "Настройки визуализатора";
            this.settingsRendererToolStripMenuItem.Click += new System.EventHandler(this.settingsRendererToolStripMenuItem_Click);
            // 
            // инфоToolStripMenuItem
            // 
            this.инфоToolStripMenuItem.Name = "инфоToolStripMenuItem";
            this.инфоToolStripMenuItem.Size = new System.Drawing.Size(94, 20);
            this.инфоToolStripMenuItem.Text = "О программе";
            // 
            // maxHeight
            // 
            this.maxHeight.Location = new System.Drawing.Point(142, 27);
            this.maxHeight.Name = "maxHeight";
            this.maxHeight.Size = new System.Drawing.Size(100, 20);
            this.maxHeight.TabIndex = 5;
            this.maxHeight.Text = "255";
            // 
            // minHeight
            // 
            this.minHeight.Location = new System.Drawing.Point(142, 53);
            this.minHeight.Name = "minHeight";
            this.minHeight.Size = new System.Drawing.Size(100, 20);
            this.minHeight.TabIndex = 6;
            this.minHeight.Text = "0";
            // 
            // width
            // 
            this.width.Location = new System.Drawing.Point(142, 79);
            this.width.Name = "width";
            this.width.Size = new System.Drawing.Size(100, 20);
            this.width.TabIndex = 7;
            this.width.Text = "129";
            // 
            // lenght
            // 
            this.lenght.Location = new System.Drawing.Point(142, 105);
            this.lenght.Name = "lenght";
            this.lenght.Size = new System.Drawing.Size(100, 20);
            this.lenght.TabIndex = 8;
            this.lenght.Text = "129";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(15, 281);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(77, 23);
            this.button1.TabIndex = 10;
            this.button1.Text = "Генерация";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pictureBox1);
            this.groupBox1.Location = new System.Drawing.Point(248, 30);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(280, 280);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Предпросмотр";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(6, 19);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(268, 255);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(547, 30);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(415, 282);
            this.dataGridView1.TabIndex = 12;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(142, 281);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(100, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "Просмотр";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(15, 334);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 13;
            this.button3.Text = "сохранение";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 134);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(83, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Вид местности";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Степ",
            "Одна гора",
            "Гористая местность"});
            this.comboBox1.Location = new System.Drawing.Point(121, 131);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 161);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(74, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Крутизна гор";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "Пологие",
            "Нормальные",
            "Крутые"});
            this.comboBox2.Location = new System.Drawing.Point(121, 158);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 21);
            this.comboBox2.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(537, 320);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.lenght);
            this.Controls.Add(this.width);
            this.Controls.Add(this.minHeight);
            this.Controls.Add(this.maxHeight);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Shell";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.TextBox maxHeight;
        private System.Windows.Forms.TextBox minHeight;
        private System.Windows.Forms.TextBox width;
        private System.Windows.Forms.TextBox lenght;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem настройкиToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem настройкиПрограммыToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem settingsRendererToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem инфоToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem очиститьToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsBMPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsObjToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBox2;
    }
}

