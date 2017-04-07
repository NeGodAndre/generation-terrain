using System;
using System.ComponentModel;
using System.Windows.Forms;

using LandscapeGenerator;
using System.Diagnostics;

namespace Shell
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 0;
            lg = new LandscapeGenerator.LandscapeGenerator();
            lg = new LandscapeGenerator.LandscapeGenerator(Convert.ToInt32(width.Text), Convert.ToInt32(lenght.Text), (float)Convert.ToDouble(minHeight.Text), (float)Convert.ToDouble(maxHeight.Text), indexToFloat(comboBox1.SelectedIndex), indexToSlope(comboBox2.SelectedIndex), true);
            lg.setLenght(0);
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        LandscapeGenerator.LandscapeGenerator lg;

        private void button1_Click(object sender, EventArgs e)
        {
           // lg = new LandscapeGenerator.LandscapeGenerator(Convert.ToInt32(width.Text), Convert.ToInt32(lenght.Text), (float)Convert.ToDouble(minHeight.Text), (float)Convert.ToDouble(maxHeight.Text), indexToFloat(comboBox1.SelectedIndex), true);

            lg.setMaxHeight((float)Convert.ToDouble(maxHeight.Text));
            lg.setMinHeight((float)Convert.ToDouble(minHeight.Text));
            lg.setLenght(Convert.ToInt32(lenght.Text));
            lg.setWidth(Convert.ToInt32(width.Text));
            lg.setParameterRoughness(indexToFloat(comboBox1.SelectedIndex));
            lg.setSlope(indexToSlope(comboBox2.SelectedIndex));

            //1f, true);
            lg.Generator();

            pictureBox1.Image = lg.ToBitMap();
            lg.ToBMP("heightmap.bmp");

            /*dataGridView1.ColumnCount = Convert.ToInt32(textBox4.Text);
            dataGridView1.RowCount = Convert.ToInt32(textBox3.Text);
            for (int i = 0; i < dataGridView1.ColumnCount; i++)
                for (int j = 0; j < dataGridView1.RowCount; j++)
                    dataGridView1[i, j].Value = lg.normalMap[i][j].ToString();*/
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process prc = new Process(); 
            prc.StartInfo.FileName = @"C:\Users\Andrey\Documents\generation-terrain\diplom\bin\x64\Release\visualization.exe"; 
            prc.Start(); 
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(lg != null)
            //lg.ToBMP("heightmap.bmp");
            lg.ToObj("1");
            //saveFileDialog1.o
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            lg.ToObj("1");
           // lg.ToBMP("heightmap.bmp");
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void настройкиToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private bool SaveFileAs()
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "heightmap (*.bmp)|*.bmp|All files (*.*)|*.*";
            saveFileDialog.FileName = "heightmap";
            saveFileDialog.DefaultExt = "heightmap";
            saveFileDialog.AddExtension = true;

            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                lg.ToBMP(saveFileDialog.FileName);
                return true;
            }
            return false;
        }

        private float indexToFloat(int index)
        {
            switch (index)
            {
                case 0:
                    return 1f;
                case 1:
                    return 2f;
                case 2:
                    return 4f;
                default:
                    return 1f;
            }
        }
        private float indexToSlope(int index)
        {
            switch (index)
            {
                case 0:
                    return 1f;
                case 1:
                    return 2f;
                case 2:
                    return 3f;
                default:
                    return 1f;
            }
        }

        private void saveAsBMPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (lg != null)
                if (lg.getLength() != 0 && lg.getWidth() != 0)
                {
                    SaveFileDialog saveFileDialog = new SaveFileDialog();
                    saveFileDialog.Filter = "heightmap (*.bmp)|*.bmp|All files (*.*)|*.*";
                    saveFileDialog.FileName = "heightmap";
                    saveFileDialog.DefaultExt = "heightmap";
                    saveFileDialog.AddExtension = true;

                    if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
                        lg.ToBMP(saveFileDialog.FileName);
                }
                else
                    MessageBox.Show("Карта не создана");
            else
                MessageBox.Show("Карта не создана");
        }

        private void saveAsObjToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (lg != null)
                if (lg.getLength() != 0 && lg.getWidth() != 0)
                {
                    SaveFileDialog saveFileDialog = new SaveFileDialog();
                    saveFileDialog.Filter = "map (*.obj)|*.obj|All files (*.*)|*.*";
                    saveFileDialog.FileName = "heightmap";
                    saveFileDialog.DefaultExt = "heightmap";
                    saveFileDialog.AddExtension = true;

                    if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
                        lg.ToObj(saveFileDialog.FileName);
                }
                else
                    MessageBox.Show("Карта не создана");
            else
                MessageBox.Show("Карта не создана");
        }

        private void settingsRendererToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.ShowDialog();
        }
    }
}
