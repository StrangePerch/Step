using System;
using System.Runtime.Serialization;

namespace av
{
    public class Bill : ISerializable
    {
        public int DayCost;
        public int Days;
        public int DelayPenalty;
        public int Delay;
        public static bool Full;

        private int _WithoutPenalty;
        private int _Penalty;
        private int _WithPenalty;

        public int WithoutPenalty
        {
            get
            {
                if (_WithoutPenalty == 0) _WithoutPenalty = DayCost * Days;
                return _WithoutPenalty;
            }
        }

        private int Penalty
        {
            get
            {
                if (_Penalty == 0) _Penalty = DelayPenalty * Delay;
                return _Penalty;
            }
        }
        public int WithPenalty
        {
            get
            {
                if (_WithPenalty == 0)
                    _WithPenalty = WithoutPenalty + Penalty;
                return _WithPenalty;
            }
        }

        public Bill()
        {

        }
        public Bill(int DayCost, int Days, int DelayPenalty, int Delay)
        {
            this.DayCost = DayCost;
            this.Delay = Delay;
            this.Days = Days;
            this.DelayPenalty = DelayPenalty;
        }

        public Bill(SerializationInfo info, StreamingContext context)
        {
            DayCost = info.GetInt32("DayCost");
            Days = info.GetInt32("Days");
            DelayPenalty = info.GetInt32("Penalty");
            Delay = info.GetInt32("Delay");
            if (Full)
            {
                _WithPenalty = info.GetInt32("WithPenalty");
                _WithoutPenalty = info.GetInt32("WithoutPenalty");
                _Penalty = info.GetInt32("Penalty");
            }
        }

        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("DayCost", DayCost);
            info.AddValue("Days", Days);
            info.AddValue("DelayPenalty", DelayPenalty);
            info.AddValue("Delay", Delay);
            if (Full)
            {
                info.AddValue("WithoutPenalty", WithoutPenalty);
                info.AddValue("WithPenalty", WithPenalty);
                info.AddValue("Penalty", WithPenalty);
            }
        }

        public void Print()
        {
            Console.WriteLine($"DayCost = {DayCost}, " +
                              $"Days = {Days}, " +
                              $"DelayPenalty = {DelayPenalty}, " +
                              $"Delay = {Delay}, " +
                              $"Penalty = {Penalty}, " +
                              $"WithPenalty = {WithPenalty}, " +
                              $"WithoutPenalty = {WithoutPenalty}");
        }
    }
}