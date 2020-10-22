using System;
using System.Buffers.Text;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;

namespace av
{
    [Serializable]
    class StudentCard
    {
        public string Series { get; set; }
        public int Number { get; set; }

        public override string ToString()
        {
            return $"Student Card: {Series} {Number}";
        }
    }

    [Serializable]
    class Student : ICloneable, IComparable
    {
        public string Name { get; set; }

        public string Surname { get; set; }
        public DateTime BirthDay { get; set; }

        public StudentCard StudentCard { get; set; }

        public object Clone()
        {
            Student temp = (Student)this.MemberwiseClone();
            temp.StudentCard = new StudentCard
            {
                Series = this.StudentCard.Series,
                Number = this.StudentCard.Number
            };
            return temp;
        }

        public void Exam(string date)
        {
            Console.WriteLine($"Student {Name} has exam at {date}");
        }

        public int CompareTo(object obj)
        {
            return Name.CompareTo((obj as Student).Name);
        }
        public override string ToString()
        {
            return $"Name: {Name}, Surname: {Surname}, BirthDay: {BirthDay.ToShortDateString()}, {StudentCard} ";
        }
    }
    class Teacher
    {
        public delegate void ExamDelegate(string date);

        SortedList<string, ExamDelegate> list = new SortedList<string, ExamDelegate>();

        public event ExamDelegate ExamEvent
        {
            add
            {
                if (value.Target is Student)
                    list.Add((value.Target as Student).Name, value);
                else
                    list.Add("Unknown", value);
            }

            remove => list.Remove((value.Target as Student).Name);
        }

        public void SetExam(string date)
        {
            foreach (var variable in list.Values)
            {
                variable(date);
            }
        }
    }

    class Group
    {
        public Point2D<int>[] Points =
        {
            new Point2D<int>(10, 10),
            new Point2D<int>(5, 3),
            new Point2D<int>(1, 2),
            new Point2D<int>(7, 6),
            new Point2D<int>(0, 0),
            new Point2D<int>(-5, -7)
        };

        public IEnumerable<Point2D<int>> GetPoints()
        {
            for (int i = 0; i < Points.Length; i++)
            {
                yield return Points[i];
            }
        }

        public Student[] Students =
        {
            new Student
            {
                Name = "Tatyana",
                Surname = "Smirnova",
                BirthDay = new DateTime(1980, 12, 16),
                StudentCard = new StudentCard
                {
                    Series = "AA",
                    Number = 123456
                }
            },
            new Student
            {
                Name = "Ivan",
                Surname = "Komarov",
                BirthDay = new DateTime(1983, 10, 11),
                StudentCard = new StudentCard
                {
                    Series = "AB",
                    Number = 651234
                }
            },
            new Student
            {
                Name = "Olga",
                Surname = "Kucher",
                BirthDay = new DateTime(1983, 12, 20),
                StudentCard = new StudentCard
                {
                    Series = "AA",
                    Number = 651234
                }
            },
            new Student
            {
                Name = "Nikolay",
                Surname = "Tovstochub",
                BirthDay = new DateTime(1980, 5, 25),
                StudentCard = new StudentCard
                {
                    Series = "CA",
                    Number = 123456
                }
            },
        };

        public IEnumerator<Student> GetEnumerator()
        {
            for (int i = 0; i < Students.Length; i++)
            {
                yield return Students[i];
            }
        }

        public void Sort()
        {
            Array.Sort(Students);
        }

        public void Sort(IComparer<Student> comparer)
        {
            Array.Sort(Students, comparer);
        }
    }

    class DateComparer : IComparer<Student>
    {
        public int Compare(Student x, Student y)
        {
            return DateTime.Compare(x.BirthDay, y.BirthDay);
        }
    }

    class SurnameComparer : IComparer<Student>
    {
        public int Compare(Student x, Student y)
        {
            return x.Surname.CompareTo(y.Surname);
        }
    }

    class StudentCardComparer : IComparer<Student>
    {
        public int Compare(Student x, Student y)
        {
            StudentCard st1 = x.StudentCard;
            StudentCard st2 = y.StudentCard;
            if (st1.Series != st2.Series)
                return st1.Series.CompareTo(st2.Series);
            else
                return st1.Number.CompareTo(st2.Number);
        }
    }

    static class Func
    {
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

        static List<Student> getStudents()
        {
            List<Student> students = new List<Student>
            {
                new Student
                {
                    Name = "Tatyana",
                    Surname = "Ivanova",
                    BirthDay = new DateTime(1980, 12, 16),
                    StudentCard = new StudentCard
                    {
                        Series = "AA",
                        Number = 123456
                    }
                },
                new Student
                {
                    Name = "Ivan",
                    Surname = "Smirnoff",
                    BirthDay = new DateTime(1983, 3, 11),
                    StudentCard = new StudentCard
                    {
                        Series = "AB",
                        Number = 651234
                    }
                },
                new Student
                {
                    Name = "Olga",
                    Surname = "Freymut",
                    BirthDay = new DateTime(1985, 12, 20),
                    StudentCard = new StudentCard
                    {
                        Series = "AA",
                        Number = 651234
                    }
                },
                new Student
                {
                    Name = "Nikolay",
                    Surname = "Drozdov",
                    BirthDay = new DateTime(1980, 5, 25),
                    StudentCard = new StudentCard
                    {
                        Series = "CA",
                        Number = 123456
                    }
                }
            };
            return students;
        }
    }
}