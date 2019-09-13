// UnityCom.cpp : Define as funções exportadas para o aplicativo DLL.
//

#include "stdafx.h"

//typedef std::basic_string<TCHAR> tstring;
#include "UnityCom.h"


//#define BUF_SIZE 256
constexpr auto BUF_SIZE = 1024;

extern "C"
{
	float UNITYCOM_API Add(float a, float b)
	{
		return a + b;
	}

	int UNITYCOM_API OpenMemoryShare()
	{
		//tstring s(_T("some string"));
		//std::vector<TCHAR> buffer(name.begin(), name.end());
		//buffer.push_back(_T('\0'));
		//TCHAR* szName = &buffer[0];
		// string is now addressed by szName, no need to do memory management
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

		//strBuf = reinterpret_cast<std::string *>(pBuf);

		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"),
				GetLastError());

			CloseHandle(hMapFile);

			return 1;
		}
		return 0;
	}

	float UNITYCOM_API ReadMemoryShare()
	{
		float* r;
		r = reinterpret_cast<float *>(pBuf);
		//strBuf = reinterpret_cast<std::string *>(pBuf);
		return *r;
		//return pBuf;
	}

	void UNITYCOM_API WriteMemoryShare(float val)
	{
		CopyMemory((LPVOID)pBuf, &val, (sizeof(float)));
	}

	int UNITYCOM_API EndMemoryShare()
	{
		UnmapViewOfFile(pBuf);
		CloseHandle(hMapFile);
		return 0;
	}

}
