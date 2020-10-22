using System;
using System.Linq;
using System.Runtime.CompilerServices;

namespace av
{
    static class StrExtension
    {
        public static string DeleteSpace(this string str)
        {
            return str.Replace(" ", "");
        }
    }

    static class ArrayExtension
    {
        public static int[] MultBy(this int[] arr, int mult)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] *= mult;
            }

            return arr;
        }

        public static int[] Print(this int[] arr)
        {
            foreach (var variable in arr)
            {
               Console.Write(variable);

               if(variable != arr.Last()) Console.Write(',');
               Console.Write(' ');
            }

            return arr;
        }
    }
}