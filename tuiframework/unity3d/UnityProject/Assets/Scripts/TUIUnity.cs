using System;
using System.Collections.Generic;
using System.Net;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

public class TUIUnity : MonoBehaviour {
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
	private bool threadStarted = false;

	private static Vector3 movement;
	private float d = 0f;

    public void Start() {
        // Erstellt eine TUI C#-Instanz und speichert diese als IntPtr
        tuiUnityTest = TUIClientLibary.createTUICsharpInstance();

        // Erstellt eine TUIInit-Instanz und speichert diese als IntPtr
        tuiUnityInit = TUIClientLibary.createTUIInitInstance();

        // Setzt TUI C#-Instanz als Member für TUIInit-Instanz
        TUIClientLibary.setTUIInitParameter(tuiUnityInit, tuiUnityTest);
    }

    /**
    * Soll bei Beendigung der Anwendung im Unity-Editor die Verbindung zum TUI-Server schließen.
    * Bisher aber nicht funktionsfähig da im TUI-Framework die Disconnect-Funktion bugged ist.
    */
    void OnApplicationQuit() {
		if (threadStarted) {
			TUIClientLibary.disconnectUnityWithTUIServer ();
			receiveThread.Abort ();
		}
        Debug.Log("Disconnected");
    }

    /**
    * Thread-Funktion welche die Verbindung zum TUI-Server aufbaut.
    */
    private void ReceiveData() {
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
    public void buttomClick() {
        // Überprüft ob die IP und Port des Servers valide sind und startet den Thread falls true.
        if (validateIP(IP.text, serverPort.text)) {   
            receiveThread = new Thread(new ThreadStart(ReceiveData));
            receiveThread.Start();
			threadStarted = true;
            Debug.Log("Connected");
        }
        else {

        }
    }

    /**
    * Soll die Verbindung zum TUI-Server schließen bei Button-Click.
    * Bisher aber nicht funktionsfähig da im TUI-Framework die Disconnect-Funktion bugged ist.
    */
    public void closeConnection() {
		if (threadStarted) {
			TUIClientLibary.disconnectUnityWithTUIServer ();
			receiveThread.Abort ();
		}
        Debug.Log("Disconnected");
    }

	/**
	 * Appelle la fonction de recherche de node une fois par tuiobject de la map.
	 * Procede ensuite aux transformations si la valeur reçue est suffisamment differente de la valeur precedente,
	 * et si l'on a trouve un gameobject correspondant au tuiobject.
	 */
    public void FixedUpdate() {
        lock (_locker) {
			foreach (var tuiObject in tuiOjectMap) {

				if (!tuiObject.Value.nodeFound) {
					tuiObject.Value.TUI = findNode (tuiObject.Value.TUIObjectName, tuiObject.Value.description);
					tuiObject.Value.nodeFound = true; //permet d'appeler une seule fois la fonction findNode
				}

				d = tuiObject.Value.received_value - tuiObject.Value.value;
				tuiObject.Value.value = tuiObject.Value.received_value;

				if (d <= 0.05f && d >= -0.05f)
					continue;

				if (tuiObject.Value.TUIType == 12) //pour les analog
					TUIClientLibary.sendUnityEvent (tuiUnityTest, tuiObject.Value.TUIObjectName, tuiObject.Value.portName, tuiObject.Value.received_value.ToString ());
				else if (tuiObject.Value.TUIType == 13) //pour les digital
					TUIClientLibary.sendUnityEvent (tuiUnityTest, tuiObject.Value.TUIObjectName, tuiObject.Value.portName + "Out", System.Convert.ToInt16(tuiObject.Value.bool_value).ToString());
				//on est oblige de convertir le booleen en int correspondant, sinon ça marche pas
				if (tuiObject.Value.TUI == null)
					continue;

				if (tuiObject.Value.trafoNo.CompareTo("1") == 0)
					movement.Set (d, 0f, 0f);
				else if (tuiObject.Value.trafoNo.CompareTo("2") == 0)
					movement.Set (0f, d, 0f);
				else if (tuiObject.Value.trafoNo.CompareTo("3") == 0)
					movement.Set (0f, 0f, d);

				if (tuiObject.Value.trafoType.CompareTo ("rot") == 0)
					tuiObject.Value.TUI.transform.Rotate (movement);
				else if (tuiObject.Value.trafoType.CompareTo ("trans") == 0)
					tuiObject.Value.TUI.transform.Translate (movement/1000f); //les translate sont en metre, on divise donc le vector par 1000f
			}
        } 
    }

    /**
    * Verbindet die Parameter.
    * 
    */
    public void connecting() {
		// Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
		TUIClientLibary.connectingParametersAll (tuiUnityTest, new TUIClientLibary.floatCallback(this.floatCallback), new TUIClientLibary.boolCallback(this.boolCalback));
    }

    /**
    * Validiert die IP adresse und den Port
    * @param IP Die IP-Adresse des TUI-Servers
    * @param port Der Port des TUI-Servers
    * @return true falls valide
    */
    private bool validateIP(string IP, string port) {
        IPAddress address;
        int portValid;

        // Überprüft ob die IP valide ist
        if (!IPAddress.TryParse(IP, out address)) {
            return false;
        }
        // Überprüft ob der Port eine Zahl ist
        if (!int.TryParse(port, out portValid)) {
            return false;
        }
        return true;
    }

	/**
	 * Recoit les informations des ports analog de TUI, creer ou met à jour les informations dans la map
	 */
	private void floatCallback (string TUIObjectName, string portName, string description, float value, string trafoType, string trafoNo) {
		try {
			lock (_locker) {
				string key = TUIObjectName + " " + portName;
				if (!tuiOjectMap.ContainsKey(key)) {
					tuiOjectMap.Add(key, new TUIObject());
					tuiOjectMap [key].TUIObjectName = TUIObjectName;
					tuiOjectMap [key].portName = portName;
					tuiOjectMap [key].description = description;
					tuiOjectMap [key].TUIType = 12;
					tuiOjectMap [key].trafoType = trafoType;
					tuiOjectMap [key].trafoNo = trafoNo;
				}
				tuiOjectMap [key].received_value = value;
			}
		}
		catch (Exception e) {
			Debug.LogError(e.ToString());
		}
	}

	/**
	 * Recoit les informations des ports digital de TUI, creer ou met à jour les informations dans la map
	 */
	private void boolCalback (string TUIObjectName, string portName, string description, bool value) {
		try {
			lock (_locker) {
				string key = TUIObjectName + " " + portName;
				if (!tuiOjectMap.ContainsKey(key)) {
					tuiOjectMap.Add(key, new TUIObject());
					tuiOjectMap [key].TUIObjectName = TUIObjectName;
					tuiOjectMap [key].portName = portName;
					tuiOjectMap [key].description = description;
					tuiOjectMap [key].TUIType = 13;
				}
				if (tuiOjectMap [key].bool_value != value) {
					tuiOjectMap [key].bool_value = value;
					tuiOjectMap [key].received_value += 1;	//permet de ne pas changer la condition de sortie dans la fonction Fixed Update
					tuiOjectMap [key].received_value %= 10;	//on pourrait même mettre un %2 mais bon, ça marche comme ça et 10 c'est rond
				}
			}
		}
		catch (Exception e) {
			Debug.LogError (e.ToString());
		}
	}

	/**
	 * Fonction recursive qui recherche le gameobject description, sous l'instance TUIObjectName.
	 * Les nodes que l'on veut bouger portant tous les memes noms, cette fonction est obligatoire.
	 * Au pire, même s'il ne porte pas les mêmes noms, ça marche quand même. (mais normalement dans le futur si)
	 * 
	 * Sortie : null si l'on n'a pas trouve, le bon gameobject sinon
	 */
	private GameObject findNode(string TUIOjectName, string description) {
		GameObject node = GameObject.Find (TUIOjectName);

		if (node != null)
			foreach (Transform child in node.transform) {	//node.transform renvoi la liste des enfants d'un gameobject, mais des enfants d'un seul niveau
				if (child.name.CompareTo (description) == 0)
					return child.gameObject;				//si on n'a trouver le node, on le retourne
				node = findNode (child.name, description);	//on appelle a nouveau pour l'enfant
			}

		if (node != null) {
			if (node.name.CompareTo (description) != 0)
				node = null;
		}

		return node;
	}
}


