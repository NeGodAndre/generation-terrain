using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace LandscapeGenerator
{
    class ConversionTo
    {
        public static void BMP(List<List<float>> normalMap, string nameFile)
        {
            Bitmap bitmap = BitMap(normalMap);
            bitmap.Save(nameFile, ImageFormat.Bmp);
        }
        public static Bitmap BitMap(List<List<float>> normalMap)
        {
            Bitmap bitmap = new Bitmap(normalMap.Count, normalMap[0].Count, PixelFormat.Format24bppRgb);

            for (int i = 0; i < normalMap.Count; i++)
                for (int j = 0; j < normalMap[0].Count; j++)
                    bitmap.SetPixel(i, j, Color.FromArgb((int)(normalMap[i][j] * 255), (int)(normalMap[i][j] * 255), (int)(normalMap[i][j] * 255)));

            return bitmap;
        }
        public static void Obj(List<List<float>> map, string nameFile)
        {
            nameFile.Remove(nameFile.Length - 4);
            List<string> str = new List<string>();
            str.Add("#File create: " + DateTime.Now.ToString());

            str.Add("mtllib " + nameFile.Remove(nameFile.Length - 5) + ".mtl");

            for (int i = 0; i < map.Count; i++)
                for (int j = 0; j < map[0].Count; j++)
                    str.Add("v " + i.ToString() + " " + map[i][j].ToString() + " " + j.ToString());
            str.Add("\n");

            str.Add("g landscape");
            str.Add("usemtl landscape");
            for (int i = 0; i <= map.Count - 2; i++)
                for (int j = 1; j <= map[0].Count - 1; j++)
                {
                    str.Add("f " + (i * map.Count + j).ToString() + " " + (i * map.Count + j + 1).ToString() + " " + ((i + 1) * map.Count + j).ToString());
                    str.Add("f " + (i * map.Count + j + 1).ToString() + " " + ((i + 1) * map.Count + j + 1).ToString() + " " + ((i + 1) * map.Count + j).ToString());
                }

            using (StreamWriter sw = File.CreateText(nameFile.Remove(nameFile.Length - 5) + ".obj"))
            {
                for (int i = 0; i < str.Count; i++)
                    sw.WriteLine(str[i]);
            }

            str = new List<string>();
            str.Add("#File create: " + DateTime.Now.ToString());

            str.Add("newmtl landscape");

            str.Add("illum 2");
            str.Add("Kd 1.00 0.00 0.00");
            str.Add("Ka 0.00 0.00 0.00");
            str.Add("Tf 1.00 1.00 1.00");
            str.Add("Ni 1.00");

            str.Add("map_Ka grass.jpg");
            str.Add("map_Kd grass.jpg");
            str.Add("map_bump grassNormals.jpg");

            using (StreamWriter sw = File.CreateText(nameFile.Remove(nameFile.Length - 5) + ".mtl"))
            {
                for (int i = 0; i < str.Count; i++)
                    sw.WriteLine(str[i]);
            }
        }
    }
}
