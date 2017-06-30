using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonBoolean : MonoBehaviour {

	public GameObject buttonAudio;

	private bool value = false;

	 /**
	  * Called when there is a collision with the button. 
	  * Calls the function which sends a value to the server, with false as a parameter.
	  * Starts the button animation and sound.
	  * @param other Has to be there tobe a Unity default function.
	  */
	void OnTriggerEnter (Collider other) {
		Debug.Log (value);
		TUIUnity.buttonManip (value);

		buttonAudio.GetComponent<AudioSource> ().Play ();
		this.GetComponent<Animation> ().Play ();
	}
}
