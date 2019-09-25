using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManagerScript : MonoBehaviour
{
	InputField memMapName;
	InputField memMapSize;
	//InputField dataInputField;

	PopulateDataGrid dataGridContent;

	// Start is called before the first frame update
	void Start()
	{
		memMapName = GameObject.Find("memNameInputField").GetComponent<InputField>();
		memMapSize = GameObject.Find("memSizeInputField").GetComponent<InputField>();
		//dataInputField = GameObject.Find("dataInputField").GetComponent<InputField>();
		dataGridContent = GameObject.Find("Content").GetComponent<PopulateDataGrid>();

		GameObject.Find("ButtonOpenMemMap").GetComponent<Button>().onClick.AddListener(OpenMemMap);
		GameObject.Find("ButtonWrite").GetComponent<Button>().onClick.AddListener(WriteMemMap);
		GameObject.Find("ButtonRead").GetComponent<Button>().onClick.AddListener(ReadMemMap);
		GameObject.Find("ButtonCloseMemMap").GetComponent<Button>().onClick.AddListener(CloseMemMap);
		//GameObject.Find("ButtonAddValue").GetComponent<Button>().onClick.AddListener(AddDataItem);
		GameObject.Find("ButtonClearData").GetComponent<Button>().onClick.AddListener(ClearData);
		GameObject.Find("ButtonGenerateData").GetComponent<Button>().onClick.AddListener(GenerateData);
	}

	public void OpenMemMap()
	{
		AcessDLL.OpenMemoryShare(memMapName.text, long.Parse(memMapSize.text));
	}

	public void WriteMemMap()
	{
		AcessDLL.WriteMemoryShare(memMapName.text, dataGridContent.fList);
	}

	public void ReadMemMap()
	{
		long size = AcessDLL.GetSize(memMapName.text);
		float[] f = new float[size];
		AcessDLL.ReadMemoryShare(memMapName.text, f);
		dataGridContent.PopulateData(f);
	}

	public void CloseMemMap()
	{
		AcessDLL.CloseAllMemoryShare();
	}

	public void ClearData()
	{
		dataGridContent.ClearData();
	}

	public void GenerateData()
	{
		long i;
		long size = long.Parse(memMapSize.text);
		float[] f = new float[size];
		for (i = 0; i < size; i++) {
			f[i] = Random.Range(0.0f, (float)i);
		}
		dataGridContent.PopulateData(f);
	}

}
