using System;
using System.IO;

namespace algoTask
{
    class Program
    {
        public static int Max(int a, int b)
        {
            return a > b ? a : b;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            short n;
            int[] weights = new int[10];
            using (StreamReader sr = new StreamReader("input.txt"))
            {
                n = Convert.ToInt16(sr.ReadLine());
                String input = sr.ReadToEnd();
                weights = new int[n];
                String[] nums = input.Split(' ');
                for (int i = 0; i < n; ++i)
                {
                    weights[i] = Convert.ToInt32(nums[i]);
                }
            }
            if (n == 2) using (StreamWriter sw = new StreamWriter("output.txt")) { sw.Write(-1); return; } 
            if (n == 1) using (StreamWriter sw = new StreamWriter("output.txt")) { sw.Write(weights[0]); return; }
            if(n == 3 || n == 4) using (StreamWriter sw = new StreamWriter("output.txt")) { sw.Write(weights[n - 1] + weights[0]); return; }
            int[] results = new int[n];
            results[0] = weights[0];
            results[1] = -1;
            results[2] = weights[0] + weights[2];
            for (int i = 3; i < n; ++i)
            {
                results[i] = Max(results[i - 2], results[i - 3]) + weights[i];
            }
            using (StreamWriter sw = new StreamWriter("output.txt")) { sw.Write(results[n - 1]); return; }
        }
    }
}