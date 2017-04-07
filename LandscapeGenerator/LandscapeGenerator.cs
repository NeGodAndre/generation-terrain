using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;

namespace LandscapeGenerator
{
    public class LandscapeGenerator
    {
        private int workWidth;
        private int workLength;

        private int width;
        private int length;
        private float minHeight;
        private float maxHeight;
        private bool isIsland;
        private float parameterRoughness;

        private float slope;

        private DiamondSquare diamondSquare = null;
        private Perlin perlin = null;

        private List<List<float>> normalMap;//времено
        private List<List<float>> map;

        public int getWidth() { return width; }
        public int getLength() { return length; }
        public float getMinHeight() { return minHeight; }
        public float getMaxHeight() { return maxHeight; }
        public float getParameterRoughness() { return parameterRoughness; }
        public bool IsIsland() { return isIsland; }
        public float getSlope() { return slope; }

        public void setWidth(int width) { this.width = width; }
        public void setLenght(int length) { this.length = length; }
        public void setMinHeight(float minHeight) { this.minHeight = minHeight; }
        public void setMaxHeight(float maxHeight) { this.maxHeight = maxHeight; }
        public void setParameterRoughness(float parameterRoughness) { this.parameterRoughness = parameterRoughness; }
        public void setIsland(bool isIsland) { this.isIsland = isIsland; }
        public void setSlope(float slope) { this.slope = slope; }

        public LandscapeGenerator()
        {
            this.width = 0;
            this.length = 0;
            this.minHeight = 0f;
            this.maxHeight = 0f;
            this.isIsland = false;
            this.parameterRoughness = 1f;
            this.slope = 1f;

            diamondSquare = new DiamondSquare(width, length, parameterRoughness);
            perlin = new Perlin(width, length);
        }

        public LandscapeGenerator(int width, int length, float minHeight, float maxHeight, float parameterRoughness, float sloap, bool isIsland)
        {
            this.width = width;
            this.length = length;
            this.minHeight = minHeight;
            this.maxHeight = maxHeight;
            this.isIsland = isIsland;
            this.parameterRoughness = parameterRoughness;
            this.slope = sloap;

            workWidth = workLength = DeterminationSideMap(width, length);

            diamondSquare = new DiamondSquare(workWidth, workLength, parameterRoughness, isIsland);
            perlin = new Perlin(width, length);
        }

        
        public void Generator()
        {
            List<List<float>> buf;
            buf = diamondSquare.MapCreation(minHeight, maxHeight);
            List<List<float>> buf1;
            buf1 = diamondSquare.MapCreation(minHeight, maxHeight);
            List<List<float>> buf2;
            buf2 = diamondSquare.MapCreation(minHeight, maxHeight);
            for (int i = 0; i < workLength; i++)
                for (int j = 0; j < workWidth; j++)
                    buf[i][j] += buf1[i][j] + buf2[i][j];

            buf = ReturnMap(buf);
            buf = Filter(buf, 3);
            normalMap = Normalization(buf);
            /*/normalMap = ReturnMap(normalMap);
            float min = normalMap[0][0];
            for (int i = 0; i < normalMap.Count; i++)
            {
                float bufMin = normalMap[i].Min();
                if (bufMin < min)
                    min = bufMin;
            }
            normalMap = ReturnMap(normalMap);*/
            map = new List<List<float>>();
            for (int i = 0; i < normalMap.Count; i++)
            {
                map.Add(new List<float>());
                for (int j = 0; j < normalMap[0].Count; j++)
                    map[i].Add((normalMap[i][j]) * (maxHeight - minHeight));
            }

        }

        private List<List<float>> Normalization(List<List<float>> map)
        {
            List<List<float>> bufMap = new List<List<float>>(map.Count);
            for (int i = 0; i < map.Count; i++)
            {
                bufMap.Add(new List<float>());
                for (int j = 0; j < map[0].Count; j++)
                    bufMap[i].Add(0);
            }

            float max = map[0][0];
            float min = map[0][0];
            for (int i = 0; i < map.Count; i++)
            {
                float bufMax = map[i].Max();
                if (bufMax > max)
                    max = bufMax;
                float bufMin = map[i].Min();
                if (bufMin < min)
                    min = bufMin;
            }

            for (int i = 0; i < map.Count; i++)
                for (int j = 0; j < map[0].Count; j++)
                    bufMap[i][j] = (map[i][j] - min) / (max - min);

            for (int i = 0; i < bufMap.Count; i++)
                for (int j = 0; j < bufMap[i].Count; j++)
                    bufMap[i][j] = (float)Math.Pow(bufMap[i][j], slope);

            return bufMap;
        }

        private int DeterminationSide(int side)
        {
            int i;
            for (i = 0; !(Math.Pow(2, i) < side && side < Math.Pow(2, i+1)); i++) ;
            return (int)Math.Pow(2, i + 1) + 1;
        }
        private int DeterminationSideMap(int sideWidth, int sideLangth)
        {
            int bufW = DeterminationSide(sideWidth);
            int bufL = DeterminationSide(sideLangth);

            return (bufL > bufW) ? bufL : bufW;
        }
        private List<List<float>> ReturnMap(List<List<float>> workMap)
        {
            List<List<float>> returnMap = new List<List<float>>();

            for (int i = 0; i < length; i++)
            {
                returnMap.Add(new List<float>());
                for (int j = 0; j < width; j++)
                    returnMap[i].Add(0);
            }

            int left = workLength / 2 - length / 2 > 0 ? workLength / 2 - length / 2 : 0;
            int top = workWidth / 2 - width / 2 > 0 ? workWidth / 2 - width / 2 : 0;

            for (int i = 0; i < returnMap.Count; i++)
                for (int j = 0; j < returnMap[0].Count; j++)
                {
                    returnMap[i][j] = workMap[left + i][top + j];
                }

            return returnMap;
        }

        private List<List<float>> Filter(List<List<float>> map, int sizeCore)
        {
            List<List<float>> newMap = new List<List<float>>();

            for (int i = 0; i < map.Count; i++)
            {
                newMap.Add(new List<float>());

                for (int j = 0; j < map[0].Count; j++)
                {
                    List<float> buf = new List<float>();

                    for (int ki = i - 1; ki <= i + 1; ki++)
                        for (int kj = j - 1; kj <= j + 1; kj++)
                        {
                            int kii = ki < 0 ? 0 : ki >= map.Count ? map.Count - 1 : ki;
                            int kjj = kj < 0 ? 0 : kj >= map[0].Count ? map[0].Count - 1 : kj; 

                            buf.Add(map[kii][kjj]);
                        }
                    buf.Sort();
                    newMap[i].Add(buf[buf.Count / sizeCore + 1]);
                }
            }

            return newMap;
        }

        public List<List<float>> getMash()
        {
            return map;
        }
        public Bitmap ToBitMap()
        {
            return ConversionTo.BitMap(normalMap);
        }
        public void ToBMP(string fileName)
        {
            ConversionTo.BMP(normalMap, fileName);
        }
        public void ToObj(string fileName)
        {
            ConversionTo.Obj(map, fileName);
        }
    }
}
