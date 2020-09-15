using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace av
{
    class Program
    {
        static void Main(string[] args)
        {

            setup();

            while(true)
            {
                loop_body();
            }

        }

       static void setup()
        {
            const int w = 50, h = 20; // Console Size
            const int wc = 2, hc = 2; // Buffer size = w * wc, h * hc

            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.Clear();
            Console.CursorSize = 10;
            Console.SetWindowSize(w, h);
            Console.SetBufferSize(w * wc, h * hc);
            Console.Title = "C# is awesome";

            Console.WriteLine("Hello World of C#");
        }

        static void loop_body()
        {
            
        }
        
        static void move()
        {
            ConsoleKey a = Console.ReadKey(true).Key;
            if (a == ConsoleKey.UpArrow && Console.WindowTop > 0)
                Console.SetWindowPosition(Console.WindowLeft, Console.WindowTop - 1);
            if (a == ConsoleKey.DownArrow && Console.WindowTop < Console.BufferHeight - Console.WindowHeight)
                Console.SetWindowPosition(Console.WindowLeft, Console.WindowTop + 1);
            if (a == ConsoleKey.LeftArrow && Console.WindowLeft > 0)
                Console.SetWindowPosition(Console.WindowLeft - 1, Console.WindowTop);
            if (a == ConsoleKey.RightArrow && Console.WindowLeft < Console.BufferWidth - Console.WindowWidth)
                Console.SetWindowPosition(Console.WindowLeft + 1, Console.WindowTop);
        }
    }
}
