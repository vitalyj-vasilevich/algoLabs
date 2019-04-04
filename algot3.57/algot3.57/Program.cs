using System;
using System.IO;
using System.Text.RegularExpressions;

namespace algot3._57
{
    class Program
    {
        static void Main(string[] args)
        {
            int n, c, m, el, pos, i;
            int[] table;
            using (StreamReader sr = new StreamReader("input.txt"))
            {
                String[] input = Regex.Split(sr.ReadLine(), @"[ \r\n]+");
                m = Convert.ToInt32(input[0]);
                c = Convert.ToInt32(input[1]);
                n = Convert.ToInt32(input[2]);
                table = new int[m];
                for (int j = 0; j < m; j++)
                {
                    table[j] = -1;
                }
                for (int j = 0; j < n; ++j)
                {
                    el = Convert.ToInt32(sr.ReadLine());
                    i = 0;
                    pos = ((el % m) + c * i) % m;
                    while (table[pos] != -1 && table[pos] != el)
                    {
                        ++i;
                        pos = ((el % m) + c * i) % m;
                    }
                    table[pos] = el;
                }
            }
            using (StreamWriter sw = new StreamWriter("output.txt"))
            {
                for (int j = 0; j < m; ++j)
                {
                    sw.Write(table[j] + " ");
                }
            }
        }
    }
}
