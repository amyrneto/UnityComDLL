using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
	private Camera cam;
	public GameObject tgtGameObject;
    // Start is called before the first frame update
    void Start()
    {
		cam = gameObject.GetComponent<Camera>();
		cam.transform.LookAt(tgtGameObject.transform.position);
	}
}
