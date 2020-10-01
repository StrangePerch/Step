using System;
using System.Collections.Generic;

namespace CSharp_first_lesson
{

    public class Rocket
    {
        public enum EFuelType
        {
            SolidFuel,
            LiquidFuel,
            Ion
        }

        private string Name { get; set; }

        private EFuelType FT { get; set; }

        private static List <string> SpaceMap { get; }

        public static string lastPlace
        {
            get => lastPlace;
            set { 
                  SpaceMap.Add(value);
                  lastPlace = value;
                }

        }

        private string StartLocation { get; set; }
        private string Destination { get; set; }

        public string FuelType
        {
            set
            {
                Enum.TryParse(value, out EFuelType temp);
                FT = temp;
            }
        }

        
        private int at; //ThrustersAmount
        static Rocket()
        {
            Console.WriteLine("Rocket created");
        }

        void Start()
        {
            Console.WriteLine($"Rocket launched from {StartLocation} to {Destination}");
            lastPlace = Destination;
        }
        

        Rocket()
        {

        }
        Rocket(string name, EFuelType ft, int at)
        {
            this.Name = name;
            this.FT = ft;
            this.at = at;
        }
    }
}