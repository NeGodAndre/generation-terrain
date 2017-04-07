using System;
using System.IO;
using System.Windows.Forms;

namespace Shell
{
    public partial class Form2 : Form
    {
        private struct ForFile
        {
            public int width;
            public int height;
            public int heightFactor;
            public float harshness;
            public float rapidity;
        }
        ForFile forFile;

        public Form2()
        {
            InitializeComponent();
            resolutionСomboBox.SelectedIndex = 0;
        }

        private void waySkyBox_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "SkyBox";
            openFileDialog.Filter = "SkyBox (*.dds)|*.dds|All files (*.*)|*.*";

            if(openFileDialog.ShowDialog() == DialogResult.OK && openFileDialog.FileName != "")
            {
                this.waySkyBoxTextBox.Text = openFileDialog.FileName;
            }
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            forFile.heightFactor = int.Parse(heightFactorTextBox.Text);
            forFile.rapidity = float.Parse(rapidityTextBox.Text);
            forFile.harshness = float.Parse(harshnessTextBox.Text);
            resolutionToInts(resolutionСomboBox.SelectedIndex, ref forFile.height, ref forFile.width);

            writeToFile();
        }

        private void defaultButton_Click(object sender, EventArgs e)
        {

        }

        private void resolutionToInts(int index, ref int height, ref int width)
        {
            switch (index)
            {
                case 0:
                    height = 640;
                    width = 480;
                    break;
                case 1:
                    height = 800;
                    width = 600;
                    break;
                case 2:
                    height = 1024;
                    width = 768;
                    break;
                case 3:
                    height = 1152;
                    width = 864;
                    break;
                case 4:
                    height = 1280;
                    width = 720;
                    break;
                case 5:
                    height = 1280;
                    width = 1024;
                    break;
                case 6:
                    height = 1920;
                    width = 1080;
                    break;
                default:
                    height = 640;
                    width = 480;
                    break;
            }
        }
        private void writeToFile()
        {
            StreamWriter file = new StreamWriter("renderSetting");
            file.Write("width" + file.NewLine);
            file.Write(forFile.width.ToString() + file.NewLine);
            file.Write("height" + file.NewLine);
            file.Write(forFile.height.ToString() + file.NewLine);
            file.Write("heightFactor" + file.NewLine);
            file.Write(forFile.heightFactor.ToString() + file.NewLine);
            file.Write("rapidity" + file.NewLine);
            file.Write(forFile.rapidity.ToString() + file.NewLine);
            file.Write("harshness" + file.NewLine);
            file.Write(forFile.harshness.ToString() + file.NewLine);
            file.Close();
        }
        private void readToFile()
        {
            StreamReader file = new StreamReader("renderSetting");
            
        }
    }
}
