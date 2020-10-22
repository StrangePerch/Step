using System;
using System.IO;

namespace CSharp.Net_Framework
{

    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    class AuthorAttribute : Attribute
    {
        string name = "Sasha";
        DateTime date = DateTime.Now;

        public AuthorAttribute()
        {

        }

        public AuthorAttribute(string n, string d)
        {
            name = n;
            date = Convert.ToDateTime(d);
        }

        public override string ToString()
        {
            return $"Author: {name}, Date: {date}";
        }
    }

    [AttributeUsage(AttributeTargets.Property)]
    public class ValueFromFileAttribute : Attribute
    {
        private string filename;

        public string GetValue()
        {
            return File.ReadAllText(filename);
        }
        public ValueFromFileAttribute(string fn)
        {
            filename = fn;
        }
    }
}