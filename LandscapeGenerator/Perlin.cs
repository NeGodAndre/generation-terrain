using System;
using System.Collections.Generic;

namespace LandscapeGenerator
{
    class Perlin
    {
        private int width;
        private int length;
        private List<List<float>> map;
        Perlin2D perlin2D;

        public Perlin(int width, int length)
        {
            perlin2D = new Perlin2D(DateTime.Now.GetHashCode());

            this.width = width;
            this.length = length;

            SetMapSize();
        }

        public int GetWidth() { return width; }
        public int GetLength() { return length; }

        public List<List<float>> MapCreation()
        {
            for (int i = 0; i < map.Count; i++)
                for (int j = 0; j < map[i].Count; j++)
                    map[i][j] = perlin2D.Noise(i+0.3f, j+0.1f);
            return map;
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

        public List<List<float>> returnMap() { return map; }
    }
}
