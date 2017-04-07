using System;
using System.Collections.Generic;

namespace LandscapeGenerator
{
    class DiamondSquare
    {
        private bool isIsland;
        private int width;
        private int length;
        private List<List<float>> map;
        private Random rand;
        private float parameterRoughness;


        public DiamondSquare(int width, int length, float parameterRoughness, bool isIsland = false)
        {
            this.width = width;
            this.length = length;
            this.isIsland = isIsland;
            this.parameterRoughness = parameterRoughness;

            rand = new Random();
            SetMapSize();
        }


        public void SetWidthMap(int width)
        {
            this.width = width;

            SetMapSize();
        }
        public void SetLenght(int length)
        {
            this.length = length;

            SetMapSize();
        }
        public void SetParameterRoughness(float parameterRoughness)
        {
            this.parameterRoughness = parameterRoughness;
        }
        public void SetIsIsland(bool isIsland)
        {
            this.isIsland = isIsland;
        }

        private void SetMapSize()
        {
            map = new List<List<float>>();
            for (int i = 0; i < length; i++)
            {
                map.Add(new List<float>());
                for (int j = 0; j < width; j++)
                    map[i].Add(0);
            }
        }

        public bool IsIsland() { return isIsland; }
        public int GetWidth() { return width; }
        public int GetLength() { return length; }
        public float GetParameterRoughness() { return parameterRoughness; }

        private void Square(int up, int down, int left, int right)
        {         
            map[(up + down) / 2][(right + left) / 2] = (map[up][left] + map[down][left] + map[up][right] + map[down][right]) / 4.0f + rand.Next(-(int)parameterRoughness * (down - up), + (int)parameterRoughness * (down - up)) + rand.Next(-(int)parameterRoughness * (right - left), + (int)parameterRoughness * (right - left));
        }

        private void Diamond(int up, int down, int left, int right)
        {
            int u = up < 0 ? (isIsland ? 0 : map.Count + up) : up;
            int d = down >= map.Count ? (isIsland ? 0 : down - map.Count) : down;
            int l = left < 0 ? (isIsland ? 0 : map[0].Count + left) : left;
            int r = right >= map[0].Count ? (isIsland ? 0 : right - map[0].Count) : right;

            //if (up < 0 || left < 0 || down >= map.Count || right >= map[0].Count)
            //    return;

            map[(up + down) / 2][(right + left) / 2] = (map[u][(l + r) / 2] + map[d][(l + r) / 2] + map[(u + d) / 2][l] + map[(u + d) / 2][r]) / 4 + rand.Next(-(int)parameterRoughness * Math.Abs(r - l), (int)parameterRoughness * Math.Abs(r - l)) + rand.Next(-(int)parameterRoughness * Math.Abs(d - u), (int)parameterRoughness * Math.Abs(d - u));
        }

        public List<List<float>> MapCreation(float minHeight, float maxHeight)
        {
            SetMapSize();

            map[0][0] = rand.Next((int)minHeight, (int)maxHeight);
            map[0][map[0].Count - 1] = rand.Next((int)minHeight, (int)maxHeight);
            map[map.Count - 1][0] = rand.Next((int)minHeight, (int)maxHeight);
            map[map.Count - 1][map[0].Count - 1] = rand.Next((int)minHeight, (int)maxHeight);

            Genetator();

            return map;
        }

        private void Genetator()
        {
            for (int n = 1; n <= map.Count-1 && n <= map[0].Count-1; n *= 2)
            {
                for (int up = 0; up < map.Count-1 && map.Count / n != 1;)
                {
                    int down = up + (map[0].Count - 1) / n;
                    for (int left = 0; left < map[0].Count-1 && map[0].Count/n != 1;)
                    {
                        int right = left + (map[0].Count-1) / n;

                        Square(up, down, left, right);
                        
                        left = right;
                    }
                    up = down;
                }
                    for (int up = 0; up < map.Count - 1 && map.Count / n != 1;)
                    {
                        int down = up + (map.Count - 1) / n;
                        for (int left = 0; left < map[0].Count - 1 && map[0].Count / n != 1;)
                        {
                            int right = left + (map[0].Count - 1) / n;


                            int lgthUD2 = Math.Abs(up - down) / 2;
                            int lghtLR2 = Math.Abs(left - right) / 2;

                            Diamond(up - lgthUD2, up + lgthUD2, left, right);
                            Diamond(up, down, left - lghtLR2, left + lghtLR2);
                            Diamond(up, down, right - lghtLR2, right + lghtLR2);
                            Diamond(up + lgthUD2, down + lgthUD2, left, right);

                            left = right;
                        }
                        up = down;
                    }
            }
        }

        public List<List<float>> returnMap() { return map; }
    }
}
