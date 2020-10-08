using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;

namespace av
{
    class Program
    {
        static void Main()
        {

            Group group = new Group();

            group.Sort(new SurnameComparer());

            foreach (var variable in group.GetPoints())
            {
                Console.WriteLine(variable);
            }


            //const int size = 100000000;

            //using (new OperationTimer.OperationTimer("Array"))
            //{
            //    ArrayList array = new ArrayList();
            //    for (int i = 0; i < size; i++)
            //    {
            //        array.Add(1);
            //        int x = (int)array[i];
            //    }

            //    array = null;
            //}

            //using (new OperationTimer.OperationTimer("List"))
            //{
            //    List<int> list = new List<int>();
            //    for (int i = 0; i < size; i++)
            //    {
            //        list.Add(1);
            //        int x = list[i];
            //    }

            //    list = null;
            //}


        }

        static void PrintTable(Hashtable group)
        {
            foreach (Student student in group.Keys)
            {
                Console.WriteLine(student);
                if (student != null)
                    foreach (var item in ((@group[student] as ArrayList)!))
                    {
                        Console.Write(item + " ");
                    }

                Console.WriteLine();
            }
        }

        static void AddMark(Hashtable group, string name, int mark)
        {
            foreach (Student? student in group.Keys)
            {
                if (student?.Name == name)
                    (group[student] as ArrayList)?.Add(mark);
            }
        }
    }
}
