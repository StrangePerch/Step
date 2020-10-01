using System;

namespace Step_CSharp_main
{

    public class Point
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
    public class Vector
    {
        public Point A { get; set; }
        public Point B { get; set; }

        public int X { get; set; }

        public int Y { get; set; }

        public Vector(Point a, Point b)
        {
            A = b;
            B = b;
            X = Math.Abs(a.X - b.X);
            Y = Math.Abs(a.Y - b.Y);
        }

        public Vector(int x, int y)
        {
            X = x;
            Y = y;
        }

        public Vector(int x1, int y1, int x2, int y2)
        {
            X = Math.Abs(x1 - x2);
            Y = Math.Abs(y1 - y2);
            A = new Point(x1,y1);
            B = new Point(x2,y2);
        }

    }
}