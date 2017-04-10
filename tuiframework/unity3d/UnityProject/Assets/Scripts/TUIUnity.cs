using System;
using System.Collections.Generic;
using System.Net;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

public class TUIUnity : MonoBehaviour
{
    // Unity Game Objects die mit dem Skript verbunden sind
    public InputField IP;
    public InputField serverPort;
    public InputField clientReceiverPort;
    public InputField clientSenderPort;

	private static Dictionary<string, TUIObject>  tuiOjectMap = new Dictionary<string, TUIObject>();

    // Locker um Thread-Safe zu gewährleisten
    private static readonly object _locker = new object();

    // Integer Pointer welche an die C#/C++ API vom TUI-Framework übergeben werden
    private IntPtr tuiUnityInit;
    private IntPtr tuiUnityTest;

    // Der Thread wird benötigt damit die Verbindung zum TUI-Server die Anwendung nicht blockiert
    private Thread receiveThread ;

	private static Vector3 movement;
	private float d = 0f;

    public void Start()
    {
        // Erstellt eine TUI C#-Instanz und speichert diese als IntPtr
        tuiUnityTest = TUIClientLibary.createTUICsharpInstance();

        // Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
        //connecting();

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
        //TUIClientLibary.disconnectUnityWithTUIServer();
        //receiveThread.Abort();

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

	public void connected() {
		// Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
		connecting();
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

    public void FixedUpdate()
    {
        lock (_locker)
        {
			foreach (var tuiObject in tuiOjectMap) {
				tuiObject.Value.TUI = GameObject.Find (tuiObject.Value.description);
				if (tuiObject.Value.TUI == null)
					continue;
				d = tuiObject.Value.received_value - tuiObject.Value.value;
				tuiObject.Value.value = tuiObject.Value.received_value;
				movement.Set (0f, 0f, d);

				tuiObject.Value.TUI.transform.Rotate (movement);
			}
			Debug.Log ("Transform done");
        } 
    }

    /**
    * Verbindet die Parameter.
    */
    public void connecting()
    {
		TUIClientLibary.connectingParametersAll (tuiUnityTest, new TUIClientLibary.floatCallback(this.floatCallback));
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

	private void floatCallback (string TUIObjectName, string description, float value) {
		Debug.Log (TUIObjectName);
		Debug.Log (description);
		Debug.Log (value);

		try
		{
			lock (_locker)
			{
				if (!tuiOjectMap.ContainsKey(TUIObjectName + " " + description)) {
					tuiOjectMap.Add(TUIObjectName + " " + description, new TUIObject());
					tuiOjectMap [TUIObjectName + " " + description].description = description;
				}
				tuiOjectMap [TUIObjectName + " " + description].received_value = value;
			}
		}
		catch (Exception e)
		{
			Debug.LogError(e.ToString());
		}
	}
}

