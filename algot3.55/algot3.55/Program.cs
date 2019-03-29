using System;
using System.IO;
using System.Text.RegularExpressions;

namespace algot3._55
{
    class Program
    {
        static void Main(string[] args)
        {
            int n;
            int[] nums;
            using (StreamReader sr = new StreamReader("input.txt"))
            {
                n = Convert.ToInt32(sr.ReadLine());
                String[] input = Regex.Split(sr.ReadToEnd(), @"[ \r\n]+");
                nums = new int[n + 1];
                for (int i = 1; i < n + 1; ++i)
                {
                    nums[i] = Convert.ToInt32(input[i - 1]);
                }
            }
            bool isHeap = true;
            if (n == 2) isHeap = nums[2] < nums[1] ? false : true;
            if (n == 4)
            {
                if (nums[2] < nums[1] || nums[3] < nums[1] || nums[2] > nums[4]) isHeap = false;
            }
            for (int i = 1; 2 * i < n; ++i)
            {
                if (nums[i] > nums[2 * i] || nums[i] > nums[2 * i + 1])
                {
                    isHeap = false;
                    break;
                }
            }
            Console.WriteLine(isHeap);
            using (StreamWriter sw = new StreamWriter("output.txt"))
            {
                sw.Write(isHeap ? "Yes" : "No");
            }
        }
    }
}
