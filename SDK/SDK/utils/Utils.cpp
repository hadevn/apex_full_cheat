#include "Utils.h"
#include <assert.h>

namespace CUtils {
	void DBG(char *format, ...)
	{	
		std::string temp;
		va_list marker = { 0 };
		va_start(marker, format);
		size_t num_of_chars = _vscprintf(format, marker);
		if (num_of_chars > temp.capacity())
		{
			temp.reserve(num_of_chars + 1);
		}
		vsprintf_s(const_cast<char*>(temp.c_str()), num_of_chars + 1, format, marker);
		OutputDebugString(temp.c_str());			
	}
	float RandomFloat(float min, float max)
	{
		assert(max > min);

		float random = ((float)rand()) / (float)RAND_MAX;
		float range = max - min;

		return (random*range) + min;
	}
	uint8_t* PatternScan(void* module, const char* signature)
	{
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector < int > {};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern)+strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)module + dosHeader->e_lfanew);

		auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<uint8_t*>(module);

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scanBytes[i];
			}
		}
		return nullptr;
	}


	void ReadData(const DWORD64 dwPtr, void *pData, int size)
	{
		if (!IsBadReadPtr((void*)dwPtr, size))
			memcpy(pData, (void*)dwPtr, size);
	}


	void split(const string& src, const string& separator, vector<string>& dest)
	{
		string str = src;
		string substring;
		string::size_type start = 0, index;
		do
		{
			index = str.find_first_of(separator, start);
			if (index != string::npos)
			{
				substring = str.substr(start, index - start);
				dest.push_back(substring);
				start = str.find_first_not_of(separator, index);
				if (start == string::npos) return;
			}
		} while (index != string::npos);

		//the last token
		substring = str.substr(start);
		dest.push_back(substring);
	}
}



