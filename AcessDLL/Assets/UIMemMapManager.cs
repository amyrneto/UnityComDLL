using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIMemMapManager : MonoBehaviour
{
	private Button btnOpenMemMap;
	private Button btnCloseMemMap;
	private InputField memMapNameInputField;
	private InputField memMapSizeInputField;

	public FluidContainerScript fluidContainer;

	public string memMapName;
	public int particleCount;
	private long bufSize;

	// Start is called before the first frame update
	void Start()
    {
		fluidContainer = GameObject.Find("FluidContainer").GetComponent<FluidContainerScript>();
		btnOpenMemMap = GameObject.Find("ButtonOpenMemMap").GetComponent<Button>();
		btnCloseMemMap = GameObject.Find("ButtonCloseMemMap").GetComponent<Button>();
		btnOpenMemMap.onClick.AddListener(OpenSharedMemory);
		btnCloseMemMap.onClick.AddListener(CloseSharedMemory);
		memMapNameInputField = GameObject.Find("memNameInputField").GetComponent<InputField>();
		memMapSizeInputField = GameObject.Find("memSizeInputField").GetComponent<InputField>();
		memMapName = memMapNameInputField.text;
		particleCount = int.Parse(memMapSizeInputField.text);
	}

	public void OpenSharedMemory()
	{
		Debug.Log("Open!");
		memMapName = memMapNameInputField.text;
		particleCount = int.Parse(memMapSizeInputField.text);
		bufSize = particleCount * 3; // for x, y and z coordinates.
		int r = AcessDLL.OpenMemoryShare(memMapName, bufSize);
		fluidContainer.StartFluidSimulation(particleCount);
	}

	public void CloseSharedMemory()
	{
		Debug.Log("Close");
		fluidContainer.StopFluidSimulation();
		AcessDLL.CloseAllMemoryShare();
	}
}
