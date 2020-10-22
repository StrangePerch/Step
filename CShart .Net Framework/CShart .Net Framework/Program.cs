using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml;

namespace CSharp.Net_Framework
{
    class Program
    {
        static void Main(string[] args)
        {   
            DllImportExample.MessageBox(IntPtr.Zero, "text","caption",1);
        }

        static void ReadNode(XmlNode node)
        {
            Console.WriteLine($"Type = {node.NodeType}, Name = {node.Name}, Value = {node.Value}");

            if (node.Attributes != null)
            {
                foreach (XmlAttribute attribute in node.Attributes)
                {
                    Console.WriteLine($"Type = {attribute.NodeType}, Name = {attribute.Name}, Value = {attribute.Value}");
                }
            }

            if (node.HasChildNodes)
            {
                foreach (XmlNode child in node.ChildNodes)
                {
                    ReadNode(child);
                }
            }

        }
    }
}
