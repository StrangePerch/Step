using System;
using System.Runtime.InteropServices;

namespace CSharp.Net_Framework
{
    public class DllImportExample
    {
        [DllImport("User32.dll")]
        public static extern int MessageBox(IntPtr h, string w, string c, int t);
    }
}