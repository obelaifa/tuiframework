using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class OutputText : MonoBehaviour {

	public GameObject outText;

	public void printOut (string myText) {
		outText.GetComponentInChildren<Text>().text = myText;
		outText.GetComponent<Animation> ().Play ();
	}
}
