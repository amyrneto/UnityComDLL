#pragma once
#ifdef UNITYCOM_EXPORTS
#define UNITYCOM_API __declspec(dllexport)
#else
#define UNITYCOM_API __declspec(dllimport)
#endif // UNITYCOM_EXPORTS
#include "stdafx.h"

#include <tchar.h>
#include <string>
#include <vector>

extern "C"
{
	//std::string mmapName;
	//TCHAR szMsg[256] = TEXT("Message from first process, Amyr.");
	TCHAR szName[256] = TEXT("mMapUnity");
	//TCHAR *param;
	HANDLE hMapFile;
	//LPCTSTR pBuf;
	LPVOID pBuf;
	std::string *strBuf;

	float UNITYCOM_API Add(float a, float b);
	int UNITYCOM_API OpenMemoryShare();
	float UNITYCOM_API ReadMemoryShare();
	void UNITYCOM_API WriteMemoryShare(float val);
	int UNITYCOM_API EndMemoryShare();
}