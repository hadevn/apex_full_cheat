#pragma once
#include "utils/Utils.h"
#include <windows.h>
#include "Offset.h"
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

typedef struct
{
	char szCN[0x100];
	char szEN[0x100];
	char szTexture[0x100];

}ITEM_NAME, *PITEM_NAME;

extern std::map<int, ITEM_NAME> g_ItemHash;

template<class T>


#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )

T read(const DWORD64 dwPtr)
{
	if (!IsBadReadPtr((void*)dwPtr, sizeof(T)))
		return *(T*)dwPtr;
	return 0;
}

void readMem(DWORD64 dwPtr, void *pData, int size);


#define ReadDword64(X) read<DWORD64>(X)
#define ReadInt(X) read<UINT32>(X)
#define ReadByte(X) read<BYTE>(X)
#define ReadBool(X) read<bool>(X)
#define ReadWord(X) read<WORD>(X)
#define ReadDword(X) read<DWORD>(X)
#define ReadFloat(X) read<FLOAT>(X)
#define ReadDouble(X) read<DOUBLE>(X)

namespace global
{
	extern HINSTANCE g_hInst;
	extern DWORD64 g_hGameImage;
	extern HWND g_hGameWnd;
	extern DWORD64 g_dwModuleSize;
}

#define DbgPrintA CUtils::DBG
//#define VMProtectDecryptStringA Xor

#define IN_ATTACK				(1 << 0)
#define IN_JUMP					(1 << 1)
#define IN_DUCK					(1 << 2)
#define IN_FORWARD				(1 << 3)
#define IN_BACK					(1 << 4)
#define IN_USE					(1 << 5)
#define IN_CANCEL				(1 << 6)
#define IN_LEFT					(1 << 7)
#define IN_RIGHT				(1 << 8)
#define IN_MOVELEFT				(1 << 9)
#define IN_MOVERIGHT			(1 << 10)
#define IN_ATTACK2				(1 << 11)
#define IN_RUN					(1 << 12)
#define IN_RELOAD				(1 << 13)
#define IN_ALT1					(1 << 14)
#define IN_ALT2					(1 << 15)
#define IN_SCORE				(1 << 16)
#define IN_SPEED				(1 << 17)
#define IN_WALK					(1 << 18)
#define IN_ZOOM					(1 << 19)
#define IN_WEAPON1				(1 << 20)
#define IN_WEAPON2				(1 << 21)
#define IN_BULLRUSH				(1 << 22)

#define	FL_ONGROUND				(1 << 0)
#define FL_DUCKING				(1 << 1)
#define	FL_WATERJUMP			(1 << 3)
#define FL_ONTRAIN				(1 << 4)
#define FL_INRAIN				(1 << 5)
#define FL_FROZEN				(1 << 6)
#define FL_ATCONTROLS			(1 << 7)
#define	FL_CLIENT				(1 << 8)
#define FL_FAKECLIENT			(1 << 9)
#define	FL_INWATER				(1 << 10)

#define HIDEHUD_SCOPE			(1 << 11)

extern HWND g_hGameWnd;



wstring MBytesToWString(const char* lpcszString);
string WStringToMBytes(const wchar_t* lpwcszWString);
wstring UTF8ToWString(const char* lpcszString);
string WStringToUTF8(const wchar_t* lpwcszWString);
string readString(const DWORD64 dwPtr);