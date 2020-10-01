using System;
using System.Buffers.Text;
using System.Collections;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;

namespace av
{
    public class StudentCard
    {
        public string Series { get; set; }
        public int Number { get; set; }
    }
    public class Student
    {
        public string Name { get; set; }
        public DateTime BirthDay { get; set; }
        public StudentCard card { get; set; }

        Student(string name, DateTime bd, StudentCard card)
        {
            Name = name;
            BirthDay = bd;
            this.card = card;
        }
    }

    

    class DateComparer : IComparer
    {
        public int Compare(object? x, object? y)
        {
            if ((x is Student) && (y is Student))
                return DateTime.Compare((x as Student).BirthDay, (x as Student).BirthDay);
            else
                throw new NotImplementedException("Only for student");
        }
    }

    class StudentCardComparer : IComparer
    {
        public int Compare(object? x, object? y)
        {
            StudentCard st1 = x as StudentCard;
            StudentCard st2 = y as StudentCard;
            if (st1.Series != st2.Series)
                return st1.Series.CompareTo(st2.Series);
            else
                return st1.Number.CompareTo(st2.Number);
        }
    }
}