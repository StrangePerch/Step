using System;

namespace av
{
    public class Point2D<T>
    {
        public T X { get; set; }
        public T Y { get; set; }

        public Point2D(T x, T y)
        {
            X = x;
            Y = y;
        }

        public Point2D()
        {
            X = default(T);
            Y = default(T);
        }

        public override string ToString()
        {
            return $"X = {X}, Y = {Y}";
        }
    }

    public class Point3D : Point2D<int>
    {
        public int Z { get; set; }

        Point3D(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public override string ToString()
        {
            return base.ToString() + $", Z = {Z}";
        }
    }
}