using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TUIObject {
	// Classe contenant toutes les informations necessaires d'un tuiobject

	public GameObject TUI;
	public string TUIObjectName;
	public string portName;
	public string description;
	public string trafoType;
	public string trafoNo;
	public string constraintMin;
	public string constraintMax;

	public float received_value = 0f;
	public float value = 0f;
	public bool bool_value = false;
	public int TUIType;

	public bool nodeFound = false;

	public TUIObject () {
	}
}
