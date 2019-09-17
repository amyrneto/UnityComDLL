// UnityCom.cpp : Define as funções exportadas para o aplicativo DLL.
//

// Isso aqui já está funcionando:
//		- Dicionário de memory maps:
//			- nome, handle
//			- nome, buffer
//			- nome, array size
//		- tamanho do buffer parametrizado: quantidade de floats no array
// @todo: refazer a conexão com Unity:
//		- ler/escrever arrays de float no mapa de memoria

#include "stdafx.h"

//typedef std::basic_string<TCHAR> tstring;
#include "UnityCom.h"

extern "C"
{
	float UNITYCOM_API Add(float a, float b)
	{
		return a + b;
	}

	bool UNITYCOM_API IsOpen(char memMapName[NAME_SIZE])
	{
		HANDLE hMapFile= mMapHandleArray.at(memMapName);
		if (hMapFile != NULL) {
			return true;
		}
		return false;
	}

	int UNITYCOM_API OpenMemoryShare(char memMapName[NAME_SIZE], long _bufSize)
	{
		if (_bufSize > MAX_ARRAY_SIZE) {
			printf("Array too large!");
			return -1;
		}
		hMap::iterator itMemMapHandArray;
		HANDLE hMapFile;
		LPVOID pBuf;
		bool exist = false;
		itMemMapHandArray = mMapHandleArray.find(memMapName);
		if (itMemMapHandArray != mMapHandleArray.end()) {
			if (mMapHandleArray.at(memMapName) != NULL) {
				hMapFile = mMapHandleArray.at(memMapName);
				pBuf = mMapBufferArray.at(memMapName);
				printf("Mem name already mapped. (%d)", mMapHandleArray.size());
				return mMapHandleArray.size();
			}
			else {
				exist = true;
			}
		}

		TCHAR szName[NAME_SIZE];
		swprintf(szName, NAME_SIZE, L"%hs", memMapName);
		hMapFile = CreateFileMapping(
			INVALID_HANDLE_VALUE,    // use paging file
			NULL,                    // default security
			PAGE_READWRITE,          // read/write access
			0,                       // maximum object size (high-order DWORD)
			_bufSize*(sizeof(float)), // maximum object size (low-order DWORD)
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
			_bufSize*(sizeof(float)));

		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"),
				GetLastError());

			CloseHandle(hMapFile);

			return 1;
		}

		// Add new handler, buffer and array size;
		if (exist) {
			mMapHandleArray.at(memMapName) = hMapFile;
			mMapBufferArray.at(memMapName) = pBuf;
			aSize.at(memMapName) = _bufSize;
		}
		else {
			mMapHandleArray.insert(std::pair<char*, HANDLE>(memMapName, hMapFile));
			mMapBufferArray.insert(std::pair<char*, LPVOID>(memMapName, pBuf));
			aSize.insert(std::pair<char*, long>(memMapName, _bufSize));
		}
		return 0;
	}

	bool UNITYCOM_API ReadMemoryShare(char memMapName[NAME_SIZE], float *val)
	{
		hMap::iterator itMemMapHandArray;
		itMemMapHandArray = mMapHandleArray.find(memMapName);
		if (itMemMapHandArray == mMapHandleArray.end()) {
			printf("Mapa de memória inexistente!");
			return false;
		}

		LPVOID pBuf = mMapBufferArray.at(memMapName);
		long length = aSize.at(memMapName) * sizeof(float);

		CopyMemory(val, (LPVOID)pBuf, length);
		return true;
	}

	bool UNITYCOM_API WriteMemoryShare(char memMapName[NAME_SIZE], float *val)
	{
		hMap::iterator itMemMApHandArray;
		itMemMApHandArray = mMapHandleArray.find(memMapName);
		if (itMemMApHandArray == mMapHandleArray.end()) {
			printf("Mapa de memória inexistente!");
			return false;
		}

		LPVOID pBuf = mMapBufferArray.at(memMapName);
		long length = aSize.at(memMapName) * sizeof(float);
				
		CopyMemory((LPVOID)pBuf, val, length);
		return true;
	}

	bool UNITYCOM_API CloseAllMemoryShare()
	{
		bufMap::iterator itMemMapBufferArray;
		for (itMemMapBufferArray = mMapBufferArray.begin(); itMemMapBufferArray != mMapBufferArray.end(); ++itMemMapBufferArray) {
			LPVOID pBuf = itMemMapBufferArray->second;
			UnmapViewOfFile(pBuf);
			mMapBufferArray.erase(itMemMapBufferArray);
		}

		hMap::iterator itMemMapHandArray;
		for (itMemMapHandArray = mMapHandleArray.begin(); itMemMapHandArray != mMapHandleArray.end(); ++itMemMapHandArray) {
			HANDLE hMapFile = itMemMapHandArray->second;
			CloseHandle(hMapFile);
			mMapHandleArray.erase(itMemMapHandArray);
		}
		return true;
	}

	bool UNITYCOM_API CloseMemoryShare(char memMapName[NAME_SIZE])
	{
		hMap::iterator itMemMApHandArray;
		itMemMApHandArray = mMapHandleArray.find(memMapName);
		if (itMemMApHandArray == mMapHandleArray.end()) {
			printf("Mapa de memória inexistente!");
			return false;
		}

		LPVOID pBuf = mMapBufferArray.at(memMapName);
		HANDLE hMapFile = mMapHandleArray.at(memMapName);

		UnmapViewOfFile(pBuf);
		CloseHandle(hMapFile);
		return true;
	}

}
