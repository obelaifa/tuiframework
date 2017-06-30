using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EmergencyStop : MonoBehaviour {

	private bool value = true;

	/**
	  * Called when there is a collision with a part of the robot (for the moment).
	  * Calls the function which sends a value to the server, with true as a parameter.
	  * @param other Has to be there tobe a Unity default function.
	  */
	void OnTriggerEnter (Collider other) {
		Debug.Log (value);
		TUIUnity.buttonManip (value);
	}
}
