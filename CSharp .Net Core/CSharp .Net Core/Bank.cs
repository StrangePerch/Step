using System;
using System.CodeDom.Compiler;
using System.Collections;
using System.Data;
using System.IO.Pipes;

namespace av
{
    public class Bank
    {
        private System.Collections.SortedList _accounts;

        public Bank()
        {
            _accounts = new SortedList();
        }

        public void Login(int ind)
        {
           Account ac = _accounts.GetByIndex(ind) as Account;
           ac.Login();
        }

        private readonly string[] _menuVariants = { "OpenAccount", "CloseAccount", "EXIT" };
        public void MainMenu()
        {
            while (true)
            {
                Console.BackgroundColor = ConsoleColor.Black;
                Console.Clear();
                Menu menu = new Menu(_menuVariants, 0, 0);
                switch (menu.Enter())
                {
                    case 0:
                        OpenAccount();
                        break;
                    case 1:
                        CloseAccount();
                        break;
                    case 2:
                        return;
                }
            }
        }

        public string[] ToString()
        {
            string[] temp = new string[_accounts.Count + 1];
            temp[0] = "EXIT";
            for (int i = 0; i < _accounts.Count; i++)
            {
                temp[i + 1] = _accounts.GetKey(i).ToString();
            }
            return temp;
        }

        private void OpenAccount()
        {
            Random rand = new Random();
            int num;
            Console.Clear();
            do
            { 
                num = rand.Next(100000000, 999999999);
                Console.Write("Generating num");
            } while (_accounts.ContainsKey(num));

            Console.Clear();
            int code = rand.Next(1000, 9999);
            Console.Write($"Num = {num}, code = {code}");
            _accounts.Add(num, new Account(num,code));
            Console.Read();
        }

        private void CloseAccount()
        {
            
            string[] str = ToString();
            if (str.Length <= 0) return;
            while (true)
            {
                Console.Clear();
                Menu menu = new Menu(str!, 0, 0);
                int choice = menu.Enter();
                if (choice == 0) return;
                else
                {
                    _accounts.RemoveAt(choice - 1);
                    return;
                }
            }
        }
    }

    public class ATM
    {
        private Bank bank;

        public ATM(Bank bank)
        {
            this.bank = bank;
        }

        
        public void MainMenu()
        {
            string[] str = bank.ToString();
            if (str.Length <= 0) return;
            while (true)
            {
                Console.Clear();
                Menu menu = new Menu(str!, 0, 0);
                int choice = menu.Enter();
                if (choice == 0) return;
                else
                {
                    bank.Login(choice - 1);
                    return;
                }
            }
        }
    }

    public class Account
    {
        private int num;
        private int code;
        private int money = 0;

        public Account(int num, int code)
        {
            this.num = num;
            this.code = code;
        }

        public void Login()
        {
            while (Console.KeyAvailable) Console.ReadKey(true);
            for (int i = 0; i < 3; i++)
            {
                Console.BackgroundColor = ConsoleColor.Black;
                    Console.Clear();
                Console.Write("Code = ");
                string str = Console.ReadLine();
                   while (str.Length <= 0) str = Console.ReadLine();
                int c;
                c = int.Parse(str);
                if (c == code) MainMenu();
            }
        }

        private readonly string[] _menuVariants = { "TakeMoney", "PutMoney", "CheckMoney", "EXIT" };
        public void MainMenu()
        {
            while (true)
            {
                Console.BackgroundColor = ConsoleColor.Black;
                Console.Clear();
                Menu menu = new Menu(_menuVariants, 0, 0);
                switch (menu.Enter())
                {
                    case 0:
                        TakeMoney();
                        break;
                    case 1:
                        PutMoney();
                        break;
                    case 2:
                        Console.Clear();
                        Console.Write($"Money: {money}");
                        break;
                    case 3:
                        return;
                }
            }
        }

        private void TakeMoney()
        {
            Console.Clear();
            while (true)
            {
                Console.Write("Take: $");
                int temp;
                temp = int.Parse(Console.ReadLine());
                if (temp > money)
                {
                    Console.Clear();
                    Console.WriteLine($"Too Much you have only {money}");
                }
                else
                {
                    money -= temp;
                    return;
                }
            }
        }

        private void PutMoney()
        {
            Console.Clear();
            Console.Write("Put: $");
            int temp;
            temp = int.Parse(Console.ReadLine());
            money += temp;
        }
        public override string ToString()
        {
            return num.ToString();
        }
    }


    public class App
    {
        private readonly string[] _menuVariants = {"ATM", "BANK", "EXIT" };

        private readonly Bank _bank;
        private readonly ATM _atm;

        public App()
        {
            this._bank = new Bank();
            this._atm = new ATM(_bank);
        }

        public void MainMenu()
        {
            while (true)
            {
                Console.BackgroundColor = ConsoleColor.Black;
                Console.Clear();
                Menu menu = new Menu(_menuVariants, 0, 0);
                switch (menu.Enter())
                {
                    case 0:
                        _atm.MainMenu();
                        break;
                    case 1:
                        _bank.MainMenu();
                        break;
                    case 2: return;
                }
            }

        }
    }
}