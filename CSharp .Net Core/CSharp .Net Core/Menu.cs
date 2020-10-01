using System;

namespace av
{
    public class Menu
    {
        private readonly string[] _variants;
        public int X { get; }
        public int Y { get; }

        private int _choice;

        public Menu(string[] a, int x, int y)
        {
            _variants = a;
            this.X = x;
            this.Y = y;
            this._choice = 0;
        }

        private void Print()
        {
            Console.BackgroundColor = ConsoleColor.Black;
            for (var i = 0; i < _variants.Length; i++)
            {
                Console.SetCursorPosition(X, Y + i);
                Console.BackgroundColor = i == _choice ? ConsoleColor.White : ConsoleColor.Black;
                Console.Write(_variants[i]);
            }
            Console.BackgroundColor = ConsoleColor.Black;
        }
        public int Enter()
        {
            Print();
            while (true)
            {
                ConsoleKeyInfo key;
                if (Console.KeyAvailable)
                {
                    key = Console.ReadKey(true);
                    switch (key.Key)
                    {
                        case ConsoleKey.Enter:
                        case ConsoleKey.RightArrow:
                            return _choice;
                        case ConsoleKey.UpArrow when _choice > 0:
                            _choice--;
                            break;
                        case ConsoleKey.UpArrow:
                            _choice = _variants.Length - 1;
                            break;
                        case ConsoleKey.DownArrow when _choice < _variants.Length - 1:
                            _choice++;
                            break;
                        case ConsoleKey.DownArrow:
                            _choice = 0;
                            break;
                    }
                    Print();
                }
            }
        }
    }
}