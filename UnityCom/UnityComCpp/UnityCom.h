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
#include <map>

constexpr auto MEGA_BYTES = 1024 * 1024;	// 50 MB
constexpr auto MAX_BUF_SIZE = 50 * MEGA_BYTES;	// 50 MB
constexpr auto MAX_ARRAY_SIZE = MAX_BUF_SIZE / sizeof(float);	// 50 MB
constexpr auto NAME_SIZE = 256;
typedef std::map<std::string, HANDLE> hMap;
typedef std::map<std::string, LPVOID> bufMap;
typedef std::map<std::string, long> arrSize;


extern "C"
{
	hMap mMapHandleArray;
	bufMap mMapBufferArray;
	arrSize aSize;

	float UNITYCOM_API Add(float a, float b);
	bool UNITYCOM_API IsOpen(char memMapName[NAME_SIZE]);
	int UNITYCOM_API OpenMemoryShare(char memMapName[NAME_SIZE], long bufSize = 1024);
	bool UNITYCOM_API ReadMemoryShare(char memMapName[NAME_SIZE], float *val);
	bool UNITYCOM_API WriteMemoryShare(char memMapName[NAME_SIZE], float *val);
	bool UNITYCOM_API CloseAllMemoryShare();
	bool UNITYCOM_API CloseMemoryShare(char memMapName[NAME_SIZE]);
}
