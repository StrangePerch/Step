using System;
using System.IO;
using System.Runtime;

namespace CSharp.Net_Framework
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

        public static Point operator -(Point p)
        {
            p.X = -p.X;
            p.Y = -p.Y;
            return p;
        }
    }


    [Author("Sasha", "2020-05-20")]
    public class Vector
    {
        public Point? A { get; set; }
        public Point? B { get; set; }

        private int x;
                     
        private int y;
        [ValueFromFile("x.ini")]
        public int X
        {
            get
            {
                foreach (var obj in typeof(Vector).GetProperty("X.ini").GetCustomAttributes(true))
                {
                    if (!(obj is ValueFromFileAttribute)) continue;
                    return x = int.Parse((obj as ValueFromFileAttribute).GetValue());
                }
                return x;
            }
            set => x = value;
        }
        [ValueFromFile("y.ini")]
        public int Y
        {
            get
            {
                foreach (var obj in typeof(Vector).GetProperty("Y.ini").GetCustomAttributes(true))
                {
                    if (!(obj is ValueFromFileAttribute)) continue;
                    return y = int.Parse((obj as ValueFromFileAttribute).GetValue());
                }
                return y;
            }
            set => y = value;
        }

        public Vector(Point a, Point b)
        {
            A = a;
            B = b;
            x = Math.Abs(a.X - b.X);
            y = Math.Abs(a.Y - b.Y);
        }

        public Vector(int x, int y)
        {
            A = null;
            B = null;
            this.x = x;
            this.y = y;
        }

        public Vector(int x1, int y1, int x2, int y2)
        {
            x = Math.Abs(x1 - x2);
            y = Math.Abs(y1 - y2);
            A = new Point(x1, y1);
            B = new Point(x2, y2);
        }

        public static Vector operator -(Vector v)
        {
            if (v.A != null && v.B != null)
            {
                v.A = -v.A;
                v.B = -v.B;
            }
            v.x = -v.x;
            v.y = -v.y;
            return v;
        }

        public static Vector operator +(Vector lhs, Vector rhs)
        {
            if (lhs.A != null && rhs.A != null && lhs.B != null && rhs.B != null)
            {
                Point a = new Point(lhs.A.X + rhs.A.X, lhs.A.Y + rhs.A.Y);
                Point b = new Point(lhs.B.X + rhs.B.X, lhs.B.Y + rhs.B.Y);
                return new Vector(a, b);
            }
            else
            {
                return new Vector(lhs.x + rhs.x, lhs.y + rhs.y);
            }
        }

        public static bool operator ==(Vector lhs, Vector rhs)
        {
            return rhs.A != null && lhs.B != null && lhs.A != null &&
                   lhs.A.X - lhs.B.X == rhs.A.X - rhs.A.Y && lhs.A.Y - lhs.B.Y == rhs.A.Y - rhs.A.Y;
        }

        public static bool operator !=(Vector lhs, Vector rhs)
        {
            return !(lhs == rhs);
        }

        [Author("Ivan", "2020-05-20")]
        public double Length()
        {
            return Math.Sqrt(Math.Pow(x, 2) + Math.Pow(y, 2));
        }

        public static bool operator >(Vector lhs, Vector rhs)
        {
            return lhs.Length() > rhs.Length();
        }
        public static bool operator <(Vector lhs, Vector rhs)
        {
            return lhs.Length() < rhs.Length();
        }

        public static bool operator <=(Vector lhs, Vector rhs)
        {
            return lhs == rhs || lhs.Length() < rhs.Length();
        }

        public static bool operator >=(Vector lhs, Vector rhs)
        {
            return lhs == rhs || lhs.Length() > rhs.Length();
        }

        public static bool operator true(Vector v)
        {
            return v.x != 0 || v.y != 0;
        }

        public static bool operator false(Vector v)
        {
            return v.x == 0 && v.y == 0;
        }
    }

    class MultiVector
    {
        private readonly Vector[] _vectors;

        public int Length()
        {
            return _vectors.Length;
        }

        public MultiVector(int size)
        {
            this._vectors = new Vector[size];
            Random rand = new Random(DateTime.Now.Second);
            for (int i = 0; i < size; i++)
            {
                _vectors[i] = new Vector(rand.Next(-10, 10), rand.Next(-10, 10), rand.Next(-10, 10), rand.Next(-10, 10));
            }
        }

        public Vector this[int ind]
        {
            get => _vectors[ind];

            set => _vectors[ind] = value;
        }

        public Vector this[int ind, int ind2]
        {
            get => _vectors[ind2];

            set => _vectors[ind2] = value;
        }
    }
}