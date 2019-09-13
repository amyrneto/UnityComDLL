#pragma once
#ifdef UNITYCOM_EXPORTS
#define UNITYCOM_API __declspec(dllexport)
#else
#define UNITYCOM_API __declspec(dllimport)
#endif // UNITYCOM_EXPORTS

extern "C"
{
	TCHAR szName[256] = TEXT("MyFileMappingObject");
	TCHAR szMsg[256] = TEXT("Message from first process, Amyr.");
	TCHAR *param;
	HANDLE hMapFile;
	//LPCTSTR pBuf;
	LPVOID pBuf;
	std::string *strBuf;

	float UNITYCOM_API Add(float a, float b);
	int UNITYCOM_API OpenMemoryShare();
	std::string UNITYCOM_API ReadMemoryShare();
	//LPCTSTR UNITYCOM_API ReadMemoryShare();
	void UNITYCOM_API WriteMemory(std::string msg);
	int UNITYCOM_API EndMemoryShare();




}