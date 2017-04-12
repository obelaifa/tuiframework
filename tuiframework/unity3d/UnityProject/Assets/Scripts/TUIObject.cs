﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TUIObject {

	public GameObject TUI;
	public string TUIObjectName;
	public string portName;
	public string description;
	public string trafoType;
	public string trafoNo;

	public float received_value = 0f;
	public float value = 0f;
	public bool bool_value = false;
	public int TUIType;

	public bool nodeFound = false;

	public TUIObject () {
	}
}
