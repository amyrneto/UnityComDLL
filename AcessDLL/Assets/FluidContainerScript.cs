using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FluidContainerScript : MonoBehaviour
{
	//AcessDLL memMap;
	public string memMapName;
	public long bufSize;

	[SerializeField]
	private float[] dataStream;
	Vector3 start, end;
	public ParticleSystem psFluid;

    // Start is called before the first frame update
    void Start()
    {
		psFluid = GetComponent<ParticleSystem>();
		AcessDLL.OpenMemoryShare(memMapName, bufSize);
		dataStream = new float[bufSize];
		AcessDLL.ReadMemoryShare(memMapName, dataStream);
	}

	// Update is called once per frame
	void Update()
    {
		AcessDLL.ReadMemoryShare(memMapName, dataStream);
		//Debug.Log(dataStream.Length);
		for (int i=0; i<dataStream.Length; i+=3) {
			float x = dataStream[i];
			float y = dataStream[i+1];
			float z = dataStream[i+2];
			start = new Vector3(x, y, z);
			end = new Vector3(x + 0.01f, y, z);
			Debug.DrawLine(start, end);
			end = start;
		}
	}
}
