using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using TUICSharp_Lib;

namespace TUIClientUnityDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            int rPort = 8998;
            int sPort = 8999;
            string serverIP = "127.0.0.1:7999";

            // Erstellt eine TUI C#-Instanz und speichert diese als IntPtr
            IntPtr tuiUnityTest = TUIClientLibary.createTUICsharpInstance();

            // Erstellt eine TUIInit-Instanz und speichert diese als IntPtr
            IntPtr tuiUnityInit = TUIClientLibary.createTUIInitInstance();

            // Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
            TUIUnity tuiUnity = new TUIUnity(tuiUnityTest);

            // Setzt TUI C#-Instanz als Member für TUIInit-Instanz
            TUIClientLibary.setTUIInitParameter(tuiUnityInit, tuiUnityTest);

            // Verbindet sich mit dem TUI-server
            Console.Write(TUIClientLibary.connectUnityWithTUIServer(rPort,sPort,serverIP, tuiUnityInit));
        }
    }
}
