using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CameraSwitcher : MonoBehaviour {
	public Camera[] cameras;
	public GameObject guitext;
	private int currentCam = 0;

	public void switchCam() {
		cameras [currentCam].gameObject.SetActive (false);
		currentCam += 1;
		currentCam %= cameras.Length;
		cameras [currentCam].gameObject.SetActive (true);

		guitext.GetComponent<Text>().text = "Camera " + (currentCam + 1).ToString ();
	}
}
