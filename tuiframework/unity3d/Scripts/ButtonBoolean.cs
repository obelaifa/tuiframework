using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonBoolean : MonoBehaviour {

	public GameObject buttonAudio;

	private bool value = true;

	void OnTriggerEnter (Collider other) {
		Debug.Log ("Colliding");
		TUIUnity.buttonManip (value);
		value = !value;

		buttonAudio.GetComponent<AudioSource> ().Play ();
		this.GetComponent<Animation> ().Play ();
	}
}
