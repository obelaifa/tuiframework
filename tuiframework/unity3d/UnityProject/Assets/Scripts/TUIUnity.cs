using System;
using System.Collections.Generic;
using System.Net;
using System.Threading;
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

    // Integer Pointer welche an die C#/C++ API vom TUI-Framework übergeben werden
    private IntPtr tuiUnityInit;
    private IntPtr tuiUnityTest;

    // Der Thread wird benötigt damit die Verbindung zum TUI-Server die Anwendung nicht blockiert
    private Thread receiveThread ;
    

    public void Start()
    {
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
        TUIClientLibary.disconnectUnityWithTUIServer();
        receiveThread.Abort();
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
        TUIClientLibary.disconnectUnityWithTUIServer();
		receiveThread.Abort();
        Debug.Log("Disconnected");
    }

    public void Update()
    {
        lock (_locker)
        {
            
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
			(int)TUIClientLibary.TUITypes.AnalogChangedEvent,
            "LBR100",
            "value.A1",
			new TUIClientLibary.floatCallback(this.testChanged));
		TUIClientLibary.connectingParameters(tuiUnityTest,
			(int)TUIClientLibary.TUITypes.AnalogChangedEvent,
			"LBR100",
			"value.A2",
			new TUIClientLibary.floatCallback(this.testChanged));
		TUIClientLibary.connectingParameters(tuiUnityTest,
			(int)TUIClientLibary.TUITypes.AnalogChangedEvent,
			"LBR100",
			"value.A3",
			new TUIClientLibary.floatCallback(this.testChanged));

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

	private void testChanged (float value) {
		Debug.Log ("Yé soui le pèle Noël !");
		Debug.Log (value);
	}
}

