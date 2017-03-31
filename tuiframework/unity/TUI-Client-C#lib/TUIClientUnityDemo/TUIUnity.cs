using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TUICSharp_Lib;

namespace TUIClientUnityDemo
{
    public class TUIUnity
    {
        int xValue;
        int yValue;
        public TUIUnity(IntPtr tuiUnityTest)
        {
            // Verbindet sich mit den Ports
            TUIClientLibary.connectingParameters(tuiUnityTest, 
                (int)TUIClientLibary.TUITypes.IntegerChangedEvent,
                "TUIMouse1", 
                "DeltaX", 
                new TUIClientLibary.integerCallback(this.getXValue));

            TUIClientLibary.connectingParameters(tuiUnityTest, 
                (int)TUIClientLibary.TUITypes.IntegerChangedEvent,
                "TUIMouse1", 
                "DeltaY", 
                new TUIClientLibary.integerCallback(this.getYValue));

            TUIClientLibary.connectingParameters(tuiUnityTest,
                (int)TUIClientLibary.TUITypes.DigitalChangedEvent,
                "TUIMouse1",
                "LeftButton",
                new TUIClientLibary.boolCallback(this.getleftMouse));

            TUIClientLibary.connectingParameters(tuiUnityTest,
                (int)TUIClientLibary.TUITypes.DigitalChangedEvent,
                "TUIMouse1",
                "RightButton",
                new TUIClientLibary.boolCallback(this.getrightMouse));
        }

        public void getXValue(int value)
        {
           // xValue = value;
            System.Console.WriteLine("XValues 1234 " + value);
        }

        public void getYValue(int value)
        {
            //yValue = value;
            System.Console.WriteLine("YValues "+ value);
        }

        public void getleftMouse(bool value)
        {
            System.Console.WriteLine("Left Mouse " + value);
        }

        public void getrightMouse(bool value)
        {
            System.Console.WriteLine("Right Mouse " + value);
        }

        // Experimentel funktioniert bisher nicht
        public void getMouseData(IntPtr value)
        {
            string result = "";
            TUIClientLibary.getMouseData(value, result);
            System.Console.WriteLine("Left Mouse " + result);
        }
    }

}
