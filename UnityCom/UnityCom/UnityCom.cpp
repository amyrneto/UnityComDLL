// UnityCom.cpp : Define as funções exportadas para o aplicativo DLL.
//

#include "stdafx.h"
#include <tchar.h>
#include<string>

#include "UnityCom.h"

//#define BUF_SIZE 256
constexpr auto BUF_SIZE = 256;

extern "C"
{
	float UNITYCOM_API Add(float a, float b)
	{
		return a + b;
	}

	int UNITYCOM_API OpenMemoryShare()
	{
		//TCHAR name[] = TEXT("MyFileMappingObject");
		hMapFile = CreateFileMapping(
			INVALID_HANDLE_VALUE,    // use paging file
			NULL,                    // default security
			PAGE_READWRITE,          // read/write access
			0,                       // maximum object size (high-order DWORD)
			BUF_SIZE,                // maximum object size (low-order DWORD)
			szName);                 // name of mapping object

		if (hMapFile == NULL)
		{
			_tprintf(TEXT("Could not create file mapping object (%d).\n"),
				GetLastError());
			return 1;
		}
		pBuf = MapViewOfFile(hMapFile,   // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			BUF_SIZE);

		strBuf = reinterpret_cast<std::string *>(pBuf);

		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"),
				GetLastError());

			CloseHandle(hMapFile);

			return 1;
		}
		return 0;
	}

	std::string UNITYCOM_API ReadMemoryShare()
	//LPCTSTR UNITYCOM_API ReadMemoryShare()
	{
//#ifdef UNICODE
		//std::wstring w;
		//w = pBuf;
		//std::string str = std::string(w.begin(), w.end()); // magic here
//#else
		//s = pBuf;
//#endif
		strBuf = reinterpret_cast<std::string *>(pBuf);
		return *strBuf;
		//return pBuf;
	}

	void UNITYCOM_API WriteMemory(std::string msg)
	{
		param = new TCHAR[msg.size() + 1];
		param[msg.size()] = 0;
		//As much as we'd love to, we can't use memcpy() because
		//sizeof(TCHAR)==sizeof(char) may not be true:
		std::copy(msg.begin(), msg.end(), param);

		CopyMemory((PVOID)pBuf, param, (_tcslen(param) * sizeof(TCHAR)));
	}
	int UNITYCOM_API EndMemoryShare()
	{
		UnmapViewOfFile(pBuf);

		CloseHandle(hMapFile);
		return 0;
	}

}
