#pragma once
#include <windows.h>
#include <mutex>
#include <vector>

using namespace std;

namespace CUtils {
	void DBG(char *format, ...);
	uint8_t* PatternScan(void* module, const char* signature);

	template<class T>
	T Read(const DWORD64 dwPtr)
	{
		if (!IsBadReadPtr((void*)dwPtr, sizeof(T)))
			return *(T*)dwPtr;
		return 0;
	}

	template<class T>
	bool Write(DWORD64 dwPtr, const T value)
	{
		if (!IsBadReadPtr((void*)dwPtr, sizeof(T)))
		{
			memcpy((void *)dwPtr, value, sizeof(T));
			return true;
		}
		return false;
	}
	float RandomFloat(float min, float max);
	void ReadData(const DWORD64 dwPtr, void *pData, int size);
	void split(const string& src, const string& separator, vector<string>& dest);
}



