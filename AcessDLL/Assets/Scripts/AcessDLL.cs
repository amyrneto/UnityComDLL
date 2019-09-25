using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices;
using System.IO;
using System.Reflection;

public static class AcessDLL
{
	//private const string UNITYCOM = "..\\UnityCom\\Release\\UnityCom.dll";
	private const string UNITYCOM = "..\\UnityCom\\x64\\Release\\UnityCom";
	[DllImport(UNITYCOM, EntryPoint = "Add")]
	public static extern float Add(float a, float b);

	[DllImport(UNITYCOM, EntryPoint = "IsOpen")]
	public static extern bool IsOpen(char[] memMapName);

	[DllImport(UNITYCOM, EntryPoint = "OpenMemoryShare")]
	public static extern int OpenMemoryShare(string memMapName, long bufSize);

	[DllImport(UNITYCOM, EntryPoint = "WriteMemoryShare")]
	public static extern bool WriteMemoryShare(string memMapName, float[] val, long offset = 0, long length = -1);

	[DllImport(UNITYCOM, EntryPoint = "ReadMemoryShare")]
	public static extern bool ReadMemoryShare(string memMapName, float[] val, long offset = 0, long length = -1);

	[DllImport(UNITYCOM, EntryPoint = "GetSize")]
	public static extern long GetSize(string memMapName);

	[DllImport(UNITYCOM, EntryPoint = "CloseAllMemoryShare")]
	public static extern bool CloseAllMemoryShare();

	[DllImport(UNITYCOM, EntryPoint = "CloseMemoryShare")]
	public static extern bool CloseMemoryShare(string memMapName);
}