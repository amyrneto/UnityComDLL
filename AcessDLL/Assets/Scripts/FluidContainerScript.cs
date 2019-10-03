using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FluidContainerScript : MonoBehaviour
{
	//AcessDLL memMap;
	public string memMapName;
	public int particleCount;

	[SerializeField]
	private float[] dataStream;
	private long bufSize;
	private ParticleSystem psFluid;
	private bool isSimulating = false;
    // Start is called before the first frame update
    void Start()
    {
		psFluid = GetComponent<ParticleSystem>();
	}

	public void StartFluidSimulation(int _particleCount)
	{
		particleCount = _particleCount;
		psFluid.Emit(particleCount);
		bufSize = particleCount * 3; // for x, y and z coordinates.
		dataStream = new float[bufSize];
		isSimulating = true;
	}

	public void StopFluidSimulation()
	{
		particleCount = 0;
		psFluid.Clear();
		bufSize = 0; // for x, y and z coordinates.
		dataStream = new float[bufSize];
		isSimulating = false;
	}

	// Update is called once per frame
	void Update()
	{
		if (isSimulating) {
			ParticleSystem.Particle[] fluidParticles = new ParticleSystem.Particle[particleCount];
			bool r = AcessDLL.ReadMemoryShare(memMapName, dataStream);
			psFluid.GetParticles(fluidParticles);
			//Debug.Log(fluidParticles.Length);
			//Debug.Log(dataStream.Length);

			int particleIndex = 0;
			for (int i = 0; i < dataStream.Length; i += 3) {
				Vector3 newPos = new Vector3(dataStream[i], dataStream[i + 1], dataStream[i + 2]);
				//fluidParticles[particleIndex].color = colors[ii];
				fluidParticles[particleIndex].position = newPos;
				//Debug.DrawLine(newPos, new Vector3(newPos.x + 0.1f, newPos.y, newPos.z));
				particleIndex++;
			}
			psFluid.SetParticles(fluidParticles, fluidParticles.Length);
		}
	}
}
