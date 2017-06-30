using System;
using System.Runtime.InteropServices;

/**
* Die Klasse stellt die Funktionen vom TUI über deren C++ API über DLL-Import bereit.
*/
public class TUIClientLibary
{
   /**
   * Verbindet sich mit dem TUI-Server
   * @param recievePort EmpfängerPort des Clients
   * @param senderPort SenderPort des Clients
   * @param serverIPPort IP und Port des Servers im Format serverIP:Port
   * @param tuiInit Instanz von TUIInit
   * @return true falls Verbindung erfolgreich
   */
    [DllImport("TUIUnityClient.dll") ]
    public static extern bool connectUnityWithTUIServer(int recievePort, int senderPort, string serverIPPort, IntPtr tuiInit);

    /**
    * Verbindet sich mit dem TUI-Server
    * @param recievePort EmpfängerPort des Clients
    * @param senderPort SenderPort des Clients
    * @param serverIPPort IP und Port des Servers im Format serverIP:Port
    * @param tuiInit Instanz von TUIInit
    * @return true falls Verbindung erfolgreich
    */
    [DllImport("TUIUnityClient.dll")]
	public static extern bool disconnectUnityWithTUIServer();

    /**
    * Erstellt eine TUIInit-Instanz.
    * @return IntPtr zur TUIInit-Instanz
    */
    [DllImport("TUIUnityClient")]
    public static extern IntPtr createTUIInitInstance();

    /**
    * Setzt die TUI C#-Instanz als Member für TUIInit Instanz
    * @param tuiInitInstance Die TUIInit-Instanz.
    * @param tuiCSharpInstance Die TUI C#-Instanz
    */
    [DllImport("TUIUnityClient")]
    public static extern void setTUIInitParameter(IntPtr tuiInitInstance, IntPtr tuiCSharpInstance);

    /**
    * Erstellt eine TUI C#-Instanz.
    * @return IntPtr zur TUI C#-Instanz
    */
    [DllImport("TUIUnityClient")]
    public static extern IntPtr createTUICsharpInstance();

	/**
    * Übergibt die Channel-Parameter zur Verbindung auf dem TUI-Server.
    * @param instance Die TUI C#-Instanz.
    * @param TUIType ID des TUITypes.
    * @param objectName Name des TUI-Object-Types.
    * @param channelName Name des Channels.
    * @param Callback für Boolean-Werte und Float-Werte.
    */
	[DllImport("TUIUnityClient", EntryPoint = "connectingParametersAll")]
	public static extern void connectingParametersAll(IntPtr instance, floatCallback call, boolCallback callb);

	[DllImport("TUIUnityClient")]
	public static extern void sendUnityEvent (IntPtr instance, string tuiObject, string portName, string serializedPayload);

    /**
    * Delegat für das Callback für Integer-Werte
    * @param value integer-Werte.
    */
    public delegate void integerCallback(int value);

    /**
    * Delegat für das Callback für Float-Werte
    * @param value Float-Werte.
    */
	public delegate void floatCallback (string TUIObjectName, string portName, string description, float value, string trafoType, string trafoNo, string constraintMin, string constraintMax);

    /**
    * ### Nicht implementiert bisher ###
    * Delegat für das Callback für Byte-Werte
    * @param value Byte-Werte.
    */
    public delegate void byteCallback(byte value);

    /**
    * Delegat für das Callback für bool-Werte
    * @param value bool-Werte.
    */
	public delegate void boolCallback(string TUIObjectName, string portName, string description, bool value, string trafoType, string trafoNo, string constraintMin, string constraintMax);

    /**
    * ### Nicht implementiert bisher ###
    * Delegat für das Callback für String-Werte
    * @param value String-Werte.
    */
    public delegate void stringCallback(string value);

    /**
    * Enumeration zum mappen der TUI-Type IDs
    */
    public enum TUITypes
    {
        DigitalChangedEvent = 11,
        AnalogChangedEvent = 12,
        IntegerChangedEvent = 13,
        TrackerChangedEvent = 14,
        Matrix4ChangedEvent = 15,
        HapticChangedEvent = 16,
        KinectEvent = 18,
        GestureEvent = 19,
        Vector3dEvent = 20,
        MouseEvent = 21,
        VectorList3dEvent = 22,
        Vector4Event = 23,
        PackedVector4Event = 24,
        Matrix4Event = 25,
        PackedMatrix4Event = 26
    }

}
