using System;
using System.Collections.Specialized;

namespace CSharp_first_lesson
{
    public class Base
    {
        private int somedata;

        public Base(int sd)
        {
            somedata = sd;
        }

        public void Print()
        {
            Console.WriteLine($"Somedata = {somedata}");
        }
    }

    class Inh1 : Base
    {
        private string moredata;

        Inh1(int sd, string md) : base(sd)
        {
            moredata = md;
        }


        public new void Print()
        {
            base.Print();
            Console.WriteLine($"More data = {moredata}");
        }
    }


    class Inh2 : Base
    {

        private double moredata;

        Inh2(int sd, double md) : base(sd)
        {
            moredata = md;
        }

        public new void Print()
        {
            base.Print();
            Console.WriteLine($"More data = {moredata}");
        }
    }
}