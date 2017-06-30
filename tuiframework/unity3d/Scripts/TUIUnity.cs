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
	public OutputText outText;

	private static Dictionary<string, TUIObject>  tuiOjectMap = new Dictionary<string, TUIObject>();

    // Locker um Thread-Safe zu gewährleisten
    private static readonly object _locker = new object();

    // Integer Pointer welche an die C#/C++ API vom TUI-Framework übergeben werden
    private IntPtr tuiUnityInit;
    private static IntPtr tuiUnityTest;

    // Der Thread wird benötigt damit die Verbindung zum TUI-Server die Anwendung nicht blockiert
    private Thread receiveThread ;
	private static bool threadStarted = false;

	// Movement vector and coefficient
	private static Vector3 movement;
	private float d = 0f;

	/**
	 * Function called when there is a collision with the robot or with the button
	 * Send the Boolean value to TUI server using the port "Button_result" of the TUIObject "ButtonTest"
	 * @param value Value sent to the server
	 */
	public static void buttonManip (bool value) {
		if (threadStarted)
			TUIClientLibary.sendUnityEvent (tuiUnityTest, "ButtonTest", "Button_result", System.Convert.ToInt16(value).ToString());
	}

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
			threadStarted = false;
			Debug.Log ("Disconnected");
			outText.printOut ("Disconnected");
		}
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

        Debug.Log ("Thread finished");
    }

    /**
    * Wird ausgeführt sobald auf den Connect-Button im Interface gedrückt wird.
    */
    public void buttomClick() {
        // Überprüft ob die IP und Port des Servers valide sind und startet den Thread falls true.
        if (validateIP(IP.text, serverPort.text)) {   
            receiveThread = new Thread(new ThreadStart(ReceiveData));
            receiveThread.Start();
			receiveThread.IsBackground = true;
			threadStarted = true;
            Debug.Log("Connected");
			outText.printOut ("Connected");
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
			threadStarted = false;
			Debug.Log ("Disconnected");
			outText.printOut ("Disconnected");
		}
    }

	/**
	 * Call first the research function, one time per object in the map if it has not already been found.
	 * Then proceed to the transformations if the received value is different enough from the previous value,
	 * and if we have found a gameobject to move.
	 */
    public void FixedUpdate() {
        lock (_locker) {
			foreach (var tuiObject in tuiOjectMap) {
				if (!tuiObject.Value.nodeFound) {
					tuiObject.Value.TUI = findNode (tuiObject.Value.TUIObjectName, tuiObject.Value.description);
					tuiObject.Value.nodeFound = true; //allow to call only once the findNode function
				}

				d = tuiObject.Value.received_value - tuiObject.Value.value;
				tuiObject.Value.value = tuiObject.Value.received_value;

				if (d <= 0.05f && d >= -0.05f)
					continue;


				if (tuiObject.Value.TUIType == (int)TUIClientLibary.TUITypes.AnalogChangedEvent) //for the analogs
					TUIClientLibary.sendUnityEvent (tuiUnityTest, tuiObject.Value.TUIObjectName, tuiObject.Value.portName, tuiObject.Value.received_value.ToString ());
				else if (tuiObject.Value.TUIType == (int)TUIClientLibary.TUITypes.DigitalChangedEvent) //for the digitals
					TUIClientLibary.sendUnityEvent (tuiUnityTest, tuiObject.Value.TUIObjectName, tuiObject.Value.portName, System.Convert.ToInt16(tuiObject.Value.bool_value).ToString());
				//We have to convert the Boolean to the corresponding int, otherwise it doesn't work

				if (tuiObject.Value.TUI == null)
					continue;

				if (tuiObject.Value.trafoNo.CompareTo ("1") == 0)
					movement.Set (-d, 0f, 0f);
				else if (tuiObject.Value.trafoNo.CompareTo("2") == 0)
					movement.Set (0f, d, 0f);
				else if (tuiObject.Value.trafoNo.CompareTo("3") == 0)
					movement.Set (0f, 0f, d);

				if (tuiObject.Value.trafoType.CompareTo ("rot") == 0)
					tuiObject.Value.TUI.transform.Rotate ((-1) * movement);
				else if (tuiObject.Value.trafoType.CompareTo ("trans") == 0)
					tuiObject.Value.TUI.transform.Translate (movement/1000f); //translate function works with meters, we divide then the vector by 1000f
			}
        } 
    }

    /**
    * Verbindet die Parameter.
    * 
    */
    public void connecting() {
		// Erstellt eine Unity C#-Instanz und übergibt diesen die TUI C#-Instanz
		TUIClientLibary.connectingParametersAll (tuiUnityTest, new TUIClientLibary.floatCallback(this.floatCallback), new TUIClientLibary.boolCallback(this.boolCallback));
		outText.printOut ("Connection proceeded");
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
	 * Receive the analog port information of TUI, creates or updates the information in the map (for float)
	 * @param TUIObjectName Instance name
	 * @param portName Port name
	 * @param description Node name
	 * @param value Float value
	 * @param trafoType Type of transformation (translation or rotation)
	 * @param trafoNo Transformation number: 1 <=> x-axis ; 2 <=> y-axis ; 3 <=> z-axis
	 * @param constraintMin Value of the minimum constraint
	 * @param constraintMax Value of the maximum constraint
	 */
	private void floatCallback (string TUIObjectName, string portName, string description, float value, string trafoType, string trafoNo, string constraintMin, string constraintMax) {
		try {
			lock (_locker) {
				string key = TUIObjectName + " " + portName; //creation of a specific key
				if (!tuiOjectMap.ContainsKey(key)) {
					tuiOjectMap.Add(key, new TUIObject());
					tuiOjectMap [key].TUIObjectName = TUIObjectName;
					tuiOjectMap [key].portName = portName;
					tuiOjectMap [key].description = description;
					tuiOjectMap [key].TUIType = (int)TUIClientLibary.TUITypes.AnalogChangedEvent;
					tuiOjectMap [key].trafoType = trafoType;
					tuiOjectMap [key].trafoNo = trafoNo;
					tuiOjectMap [key].constraintMin = constraintMin;
					tuiOjectMap [key].constraintMax = constraintMax;
				}
				tuiOjectMap [key].received_value = value;
			}
		}
		catch (Exception e) {
			Debug.LogError(e.ToString());
		}
	}

	/**
	 * Receive the digital port information of TUI, creates or updates the information in the map (for Boolean)
	 * @param TUIObjectName Instance name
	 * @param portName Port name
	 * @param description Node name
	 * @param value Boolean value
	 * @param trafoType Type of transformation (translation or rotation)
	 * @param trafoNo Transformation number: 1 <=> x-axis ; 2 <=> y-axis ; 3 <=> z-axis
	 * @param constraintMin Value of the minimum constraint
	 * @param constraintMax Value of the maximum constraint
	 */
	private void boolCallback (string TUIObjectName, string portName, string description, bool value, string trafoType, string trafoNo, string constraintMin, string constraintMax) {
		try {
			lock (_locker) {
				string key = TUIObjectName + " " + portName;
				if (!tuiOjectMap.ContainsKey(key)) {
					tuiOjectMap.Add(key, new TUIObject());
					tuiOjectMap [key].TUIObjectName = TUIObjectName;
					tuiOjectMap [key].portName = portName;
					tuiOjectMap [key].description = description;
					tuiOjectMap [key].TUIType = (int)TUIClientLibary.TUITypes.DigitalChangedEvent;
					tuiOjectMap [key].trafoType = trafoType;
					tuiOjectMap [key].trafoNo = trafoNo;
					tuiOjectMap [key].constraintMin = constraintMin;
					tuiOjectMap [key].constraintMax = constraintMax;
				}
				if (tuiOjectMap [key].bool_value != value) {
					tuiOjectMap [key].bool_value = value;
					tuiOjectMap [key].received_value += 1;	//Allow to keep the out condition in the FixedUpdate fucntion for the boolean values
					tuiOjectMap [key].received_value %= 10; //Avoid too big received_value
				}
			}
		}
		catch (Exception e) {
			Debug.LogError (e.ToString());
		}
	}

	/**
	 * Recursive function which researchs the gameObject named description under the instance TUIObjectName
	 * The nodes that we want to move,  can have the same name, this function is necessary 
	 * 
	 * @param return null if the gameobject has not been found, the right GameObject otherwise
	 */
	private GameObject findNode(string TUIOjectName, string description) {
		GameObject node = GameObject.Find (TUIOjectName);

		if (node != null)
			foreach (Transform child in node.transform) {	//node.transform sends back the children list of a gameObject, but only the first "level" children
				if (child.name.CompareTo (description) == 0)
					return child.gameObject;				//If we found the node, we return it
				node = findNode (child.name, description);	//otherwise we call it again for the child
			}

		if (node != null) {
			if (node.name.CompareTo (description) != 0)
				node = null;
		}

		return node;
	}
}