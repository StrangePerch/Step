using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;
using System.Runtime.Serialization;


namespace av
{

    public delegate void VoidDelegate();

    class Program
    {

        static void Main()
        {
            Bill bill = new Bill(1,2,3,4);
            Bill.Full = true;


            XmlSerializer xml = new XmlSerializer(typeof(Bill));
            using (Stream fs = File.Create("File.txt"))
            {
                xml.Serialize(fs,bill);
            }
             
            bill.Print();
        }

    }
}
