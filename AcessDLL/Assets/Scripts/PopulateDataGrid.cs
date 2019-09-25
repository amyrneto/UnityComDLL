using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PopulateDataGrid : MonoBehaviour
{
	public GameObject prefab;
	public float[] fList;

	public void PopulateData(float[] _data)
	{
		//ClearData();
		fList = _data;
		for(int i=0; i<_data.Length; i++) {
			AddDataItem(fList[i].ToString());
		}
	}

	public void AddDataItem(string _str)
	{
		GameObject newObj;
		newObj = (GameObject)Instantiate(prefab, transform);
		newObj.GetComponent<Text>().text = _str;
	}

	public void ClearData()
	{
		Transform[] chList = gameObject.GetComponentsInChildren<Transform>();
		fList = new float[chList.Length];
		foreach (Transform t in chList) {
			Destroy(t.gameObject);
		}
	}
}
