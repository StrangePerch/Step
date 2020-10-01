using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Step_CSharp_main
{
    class Program
    {
        static void Main(string[] args)
        {
            Vector a = new Vector(1, 2, 7, 8);
            Vector b = new Vector(new Point(5,5), new Point(10,10) );
        }
    }
}
