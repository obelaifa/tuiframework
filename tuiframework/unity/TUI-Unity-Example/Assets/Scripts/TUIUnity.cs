using System;
using System.Collections.Generic;
using System.Net;
using System.Threading;
using TUIClientUnity_Lib;
using UnityEngine;
using UnityEngine.UI;

public class TUIUnity : MonoBehaviour
{
    // Unity Game Objects die mit dem Skript verbunden sind
    public GameObject cube;
    public InputField IP;
    public InputField serverPort;
    public InputField clientReceiverPort;
    public InputField clientSenderPort;

    // Locker um Thread-Safe zu gewährleisten
    private static readonly object _locker = new object();

    // Queues für die X und Y-Werte, müssen Static sein da sonst Exceptions geworfen werden
    private static Queue<float> XValues;
    private static Queue<float> YValues;

    private static bool mouseLeft;
    private static bool mouseRight;

    // Integer Pointer welche an die C#/C++ API vom TUI-Framework übergeben werden
    private IntPtr tuiUnityInit;
    private IntPtr tuiUnityTest;

    // Der Thread wird benötigt damit die Verbindung zum TUI-Server die Anwendung nicht blockiert
    private Thread receiveThread ;
    

    public void Start()
    {
        // Initalisiert ein paar Werte für die Buttons

        mouseLeft = false;
        mouseRight = false;
        XValues = new Queue<float>();
        YValues = new Queue<float>();

        // Erstellt eine TUI C#-Instanz und speichert diese als IntPtr
        tuiUnityTest = TUIClientLibary.createTUICsharpInstance();

        // Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
        connecting();

        // Erstellt eine TUIInit-Instanz und speichert diese als IntPtr
        tuiUnityInit = TUIClientLibary.createTUIInitInstance();

        // Setzt TUI C#-Instanz als Member für TUIInit-Instanz
        TUIClientLibary.setTUIInitParameter(tuiUnityInit, tuiUnityTest);

    }

    /**
    * Soll bei Beendigung der Anwendung im Unity-Editor die Verbindung zum TUI-Server schließen.
    * Bisher aber nicht funktionsfähig da im TUI-Framework die Disconnect-Funktion bugged ist.
    */
    void OnApplicationQuit()
    {
        receiveThread.Abort();
        TUIClientLibary.disconnectUnityWithTUIServer();
        Debug.Log("Disconnected");
    }

    /**
    * Thread-Funktion welche die Verbindung zum TUI-Server aufbaut.
    */
    private void ReceiveData()
    {
        int rPort = int.Parse(clientReceiverPort.text);
        int sPort = int.Parse(clientSenderPort.text);
        string serverIP =IP.text +":"+serverPort.text;
 
        // Aufruf der API-Funktion zum Verbinden mit dem TUI-Server.
        TUIClientLibary.connectUnityWithTUIServer(rPort, sPort, serverIP, tuiUnityInit);

        Debug.Log("Thread finished");
    }

    /**
    * Wird ausgeführt sobald auf den Connect-Button im Interface gedrückt wird.
    */
    public void buttomClick()
    {
        // Überprüft ob die IP und Port des Servers valide sind und startet den Thread falls true.
        if (validateIP(IP.text, serverPort.text))
        {   
            receiveThread = new Thread(new ThreadStart(ReceiveData));
            receiveThread.Start();
            Debug.Log("Connected");
        }
        else
        {

        }
    }

    /**
    * Soll die Verbindung zum TUI-Server schließen bei Button-Click.
    * Bisher aber nicht funktionsfähig da im TUI-Framework die Disconnect-Funktion bugged ist.
    */
    public void closeConnection()
    {
        receiveThread.Abort();
        TUIClientLibary.disconnectUnityWithTUIServer();
        Debug.Log("Disconnected");
    }

    public void Update()
    {
        lock (_locker)
        {
            // Es wird überprüft ob Daten für Delta-X in der Queue vorhanden sind.
            if (XValues.Count > 0)
            {
                try
                {
                    Debug.Log("moved X");
                    // Starten eines kritischen Bereichs, erforderlich für Thread-safe Operationen
                    // Lässt den Würfel rotieren
                    cube.transform.Rotate(0, XValues.Dequeue(), 0, Space.World);
                }
                catch (Exception e)
                {
                    Debug.LogError("Error Output " + e);
                }
            }

            // Es wird überprüft ob Daten für Delta-Y in der Queue vorhanden sind.
            if (YValues.Count > 0)
            {
                try
                {
                    Debug.Log("moved Y");
                    // Starten des Kritischen Bereichs, wird für Thread-safe benötigt.
                
                        // Lässt den Würfel rotieren.
                        cube.transform.Rotate(YValues.Dequeue(), 0 , 0, Space.World);
               
                }
                catch (Exception e)
                {
                    Debug.LogError("Error Output " + e);
                }
            }

            if (mouseLeft)
            {

                cube.GetComponent<Renderer>().material.color = Color.white;
            }

            if (mouseRight)
            {

                cube.GetComponent<Renderer>().material.color = Color.black;
            }
        }


            
    }


    /**
    * Diese Funktion wird ausgeführt sobald die Maus in X-Richtung verschoben wird.
    * @param value Der Wert in welcher die Maus in X-Richtung verschoben wurde.
    */
    public void getMouseXValue(int value)
    {
            try
            {
                //Debug.Log("XValues " + value);
                // Startet einen kritischen Bereich.
                lock(_locker)
                {
                    // Fügt den Wert zur Instanzübergreifenden Queue hinzu.
                    XValues.Enqueue(value);
                }
            }
            catch (Exception e)
            {
                Debug.LogError("Error X-Input: " + e.ToString());
        }
    }

    /**
    * Diese Funktion wird ausgeführt sobald die Maus in Y-Richtung verschoben wird.
    * @param value Der Wert in welcher die Maus in Y-Richtung verschoben wurde.
    */
    public void getMouseYValue(int value)
    {
        try
        {
            //Debug.Log("YValues " + value);
            // Startet einen kritischen Bereich.
            lock (_locker)
            {
                // Fügt den Wert zur Instanzübergreifenden Queue hinzu.
                YValues.Enqueue(value);
            }
        }
        catch (Exception e)
        {
            Debug.LogError("Error Y-Input: " + e.ToString());
        }
    }

    /**
* Diese Funktion wird ausgeführt sobald die linke Maustaste gedrückt wurde.
* @param value true falls linke Maustaste gedrückt wurde.
*/
    public void getMouseLeft(bool value)
    {
        try
        {
            //Debug.Log("YValues " + value);
            // Startet einen kritischen Bereich.
            lock (_locker)
            {
                Debug.Log("Left Mouse " + value);
                mouseLeft = value;
            }
        }
        catch (Exception e)
        {
            Debug.LogError("Error Y-Input: " + e.ToString());
        }
    }

    /**
    * Diese Funktion wird ausgeführt sobald die rechte Maustaste gedrückt wird.
    * @param value true falls rechte Maustaste gedrückt wurde.
    */
    public void getMouseRight(bool value)
    {
        try
        {
            //Debug.Log("YValues " + value);
            // Startet einen kritischen Bereich.
            lock (_locker)
            {
                Debug.Log("Right Mouse " + value);
                mouseRight = value;
            }
        }
        catch (Exception e)
        {
            Debug.LogError("Error Y-Input: " + e.ToString());
        }
    }


    /**
    * Verbindet die Parameter.
    */
    public void connecting()
    {
        // Aufruf der C#/C++ API. Übergibt die C#-TUIinstanz, Clientname, Portname und die Funktion zu TUI.
        // Die Namen müssen exakt übereinstimmen mit der TUI-Server Konfiguration.

        // Verbindet die Parameter für die Bewegungen der Maus in X-Richtung.
        TUIClientLibary.connectingParameters(tuiUnityTest,
            (int)TUIClientLibary.TUITypes.IntegerChangedEvent,
            "TUIUnity",
            "DeltaX",
            new TUIClientLibary.integerCallback(this.getMouseXValue));

        // Verbindet die Parameter für die Bewegungen der Maus in Y-Richtung.
        TUIClientLibary.connectingParameters(tuiUnityTest,
            (int)TUIClientLibary.TUITypes.IntegerChangedEvent,
            "TUIUnity",
            "DeltaY",
            new TUIClientLibary.integerCallback(this.getMouseYValue));

        // Verbindet die Parameter für das drücken der linken Maustaste
        TUIClientLibary.connectingParameters(tuiUnityTest,
            (int)TUIClientLibary.TUITypes.DigitalChangedEvent,
            "TUIUnity",
            "leftMouse",
            new TUIClientLibary.boolCallback(this.getMouseLeft));

        // Verbindet die Parameter für das drücken der rechten Maustaste
        TUIClientLibary.connectingParameters(tuiUnityTest,
            (int)TUIClientLibary.TUITypes.DigitalChangedEvent,
            "TUIUnity",
            "rightMouse",
            new TUIClientLibary.boolCallback(this.getMouseRight));

    }

    /**
    * Validiert die IP adresse und den Port
    * @param IP Die IP-Adresse des TUI-Servers
    * @param port Der Port des TUI-Servers
    * @return true falls valide
    */
    private bool validateIP(string IP, string port)
    {
        IPAddress address;
        int portValid;

        // Überprüft ob die IP valide ist
        if (!IPAddress.TryParse(IP, out address))
        {
            return false;
        }
        // Überprüft ob der Port eine Zahl ist
        if (!int.TryParse(port, out portValid))
        {
            return false;
        }

        return true;
    }
}

