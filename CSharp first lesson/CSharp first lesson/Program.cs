using System;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace av
{
    internal class Program
    {
        private static void Main()
        {
            //draw.Drawer.Setup();
            //Setup();

            //while (true)
            //{
            //    Loop_Body();
            //    if (Control()) return;
            //}
        }

        private static void Setup()
        {
            const int w = 50, h = 20; // Console Size
            const int wc = 1, hc = 1; // Buffer size = w * wc, h * h

            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Clear();
            Console.CursorSize = 10;
            Console.SetWindowSize(w, h);
            Console.SetBufferSize(w * wc, h * hc);
            Console.Title = "C# is awesome";
        }

        private static void Loop_Body()
        {
            while (true)
            {
                Drawer();
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Point
        {
            public int x;
            public int y;
        }

        [DllImport("user32.dll")]
        public static extern bool GetCursorPos(out Point lpPoint);

        private static void Drawer()
        {
            GetCursorPos(out var point);

            Console.SetCursorPosition(point.x / (1720 / (Console.BufferWidth - 2)), point.y / (1048 / (Console.BufferHeight - 2)));

            Console.WriteLine('■');
        }

        private static bool Control()
        {
            if (!Console.KeyAvailable) return false;
            var a = Console.ReadKey(true).Key;
            switch (a)
            {
                case ConsoleKey.UpArrow when Console.WindowTop > 0:
                    Console.SetWindowPosition(Console.WindowLeft, Console.WindowTop - 1);
                    break;
                case ConsoleKey.DownArrow when Console.WindowTop < Console.BufferHeight - Console.WindowHeight:
                    Console.SetWindowPosition(Console.WindowLeft, Console.WindowTop + 1);
                    break;
                case ConsoleKey.LeftArrow when Console.WindowLeft > 0:
                    Console.SetWindowPosition(Console.WindowLeft - 1, Console.WindowTop);
                    break;
                case ConsoleKey.RightArrow when Console.WindowLeft < Console.BufferWidth - Console.WindowWidth:
                    Console.SetWindowPosition(Console.WindowLeft + 1, Console.WindowTop);
                    break;
                case ConsoleKey.Escape:
                    return true;
            }

            return false;
        }
    }
}
