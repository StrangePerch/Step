using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.AccessControl;

namespace draw
{
    public static class Drawer
    {
        private static Point pos;
        private static int size;
        public static void Setup()
        {
            int w, h;
            Console.Clear();
            Console.Write("W = ");
            w = int.Parse(Console.ReadLine() ?? string.Empty);
            Console.Clear();
            Console.Write("H = ");
            h = int.Parse(Console.ReadLine() ?? string.Empty);
                
            if (w > 210) w = 210;
            if (h > 61) h = 61;

            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Clear();
            Console.CursorSize = 100;
            Console.SetWindowSize(w, h);
            Console.SetBufferSize(w, h);
            Console.Title = "Drawer";

            Loop();
        }

        private static void Loop()
        {
            while (true)
            {
                GetCursorPos(out var point);

                pos.x = point.x / (1720 / (Console.BufferWidth - 2));
                pos.y = point.y / (1000 / (Console.BufferHeight - 2));
                //pos.x = point.x / 8;
                //pos.y = point.y / 17;

               if (pos.y >= Console.BufferHeight) pos.y = Console.BufferHeight - 1;
                if (pos.x >= Console.BufferWidth) pos.x = Console.BufferWidth - 1;

                Console.SetCursorPosition(pos.x, pos.y);

                Draw();
            }
        }

        private static void Draw()
        {
            if (!Console.KeyAvailable) return;
            var read = Console.ReadKey(true);
            char str = read.KeyChar;
            var a = read.Key;

            if (size < 1) size = 1;



            switch (a)
            {
                case ConsoleKey.OemMinus:
                    size--;
                    break;
                case ConsoleKey.Subtract:
                    size--;
                    break;
                case ConsoleKey.OemPlus:
                    size++;
                    break;
                case ConsoleKey.Add:
                    size++;
                    break;
                case ConsoleKey.Tab:
                    string colorin;
                    Console.SetCursorPosition(0, 0);
                    colorin = Console.ReadLine();
                    Console.SetCursorPosition(0, 0);
                    for (int i = 0; i < colorin.Length; i++)
                    {
                        Console.Write(' ');
                    }

                    ConsoleColor.TryParse(colorin, true, out ConsoleColor color);
                    Console.ForegroundColor = color;
                    break;
                case ConsoleKey.Backspace:
                    Brush(' ');
                    break;
                case ConsoleKey.Delete:
                    Console.Clear();
                    break;
                case ConsoleKey.Spacebar:
                    Brush('■');
                    break;
                default:
                    Brush(str);
                    break;
            }

            while (Console.KeyAvailable)
            {
                Console.ReadKey(false);
            }
        }

        private static void Brush(char toDraw)
        {
            for (int i = -size / 2; i < size / 2.0; i++)
            {
                var y = pos.y + i;
                if (y < Console.BufferHeight && y >= 0 && y != Console.BufferHeight - 1)
                {
                    Console.SetCursorPosition(pos.x - size / 2, y);
                }
                for (int j = -size / 2; j < size / 2.0; j++)
                {
                    var x = pos.x + j;
                    if (x < Console.BufferWidth && x >= 0 && x != Console.BufferWidth - 1)
                    {
                        Console.Write(toDraw);
                    }
                }
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
    }
}