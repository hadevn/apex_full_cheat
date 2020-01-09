#include "Common.h"
#include "NetVars.h"
#include "math\Vector.hpp"
#include "math\Vector4D.hpp"
#include <memory>
#include "MinHook\include\MinHook.h"
#include "SDK.h"
#include "Offset.h"
#include "math\QAngle.hpp"
#include "ActorMgr.h"
#include "hooks.h"
using CreateInterfaceFn = uintptr_t(__fastcall *)(const char *, uintptr_t);
namespace Interfaces
{
	CreateInterfaceFn GetInterfaceFactory()
	{
		// Get base address of game module.
		uintptr_t BaseAddress = (uintptr_t)GetModuleHandleA(NULL);

		if (!BaseAddress)
			return CreateInterfaceFn{};

		// Game->GetCreateInterface( )
		return (CreateInterfaceFn)(CUtils::Read<CreateInterfaceFn>(BaseAddress + OFFSET::uCreateInterface));
	}
	void getInterfaces()
	{
		CreateInterfaceFn CreateInterface = GetInterfaceFactory();
		I::Engine = CUtils::Read<IVEngineClient*>(global::g_hGameImage + OFFSET::uEngineClient);
		I::Globals = (IGlobalVarsBase*)OFFSET::uGolbals;
		I::ClientEntList = (IClientEntityList*)CreateInterface("VClientEntityList003", NULL);
		I::EngineTrace = (IEngineTrace*)CreateInterface("EngineTraceClient004", NULL);
		DbgPrintA("I::Engine: 0x%08X I::Globals: 0x%08X I::ClientEntList: 0x%08X I::EngineTrace: 0x%08X", I::Engine, I::Globals, I::ClientEntList, I::EngineTrace);

	}
}
extern _PeekMessageW Old_PeekMessageW;
void InstallCreatMoveHook()
{
	//to do silent Aim
	BYTE bData[0x22] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x89, 0x44, 0x24, 0x28, 0xF3, 0x0F, 0x10, 0x44, 0x24, 0x28, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,0x90, 0x90, };
	DWORD64 dwAddr = global::g_hGameImage + OFFSET::SilentAimAddr;
	DWORD myLocalView;
	VirtualProtect((void*)dwAddr, 0x22, PAGE_EXECUTE_READWRITE, &myLocalView);
	memcpy((void*)dwAddr, bData, sizeof(bData));
	//Install Hook:

	MH_STATUS st;
	DWORD64 cm = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, XorString("48 8B C4 56 41 56 48 81 ?? ?? ?? ?? ?? 48 89 58 ??"));
	_CreateMove tmpCreateMove = (_CreateMove)(cm);
	DbgPrintA("CREATEMOVE ：0x%llX",tmpCreateMove);
	//VirtualProtect((void*)tmpCreateMove, 0x20, PAGE_EXECUTE_READWRITE, &myLocalView);
	if ((st = MH_CreateHook(tmpCreateMove, &Hooks::MyCreateMove, reinterpret_cast<void **>(&OLD_CreateMove))) != MH_OK)
	{
		DbgPrintA("失败原因：%s", MH_StatusToString(st));
		return;
	}
	if ((st = MH_EnableHook(tmpCreateMove)) != MH_OK)
	{
		DbgPrintA("enable失败");
	}

}
void InitHook()
{
	Hooks::InitDX11Hook();
}
DWORD GetModuleSize(DWORD64 base)
{
	IMAGE_DOS_HEADER dos_header = { 0 };
	IMAGE_NT_HEADERS nt_headers = { 0 };
	if (!base)return -1;
	dos_header = *(IMAGE_DOS_HEADER*)base;
	nt_headers = *(IMAGE_NT_HEADERS*)(base + dos_header.e_lfanew);
	return nt_headers.OptionalHeader.SizeOfImage;
}


//	功能函数调用
typedef struct
{
	DWORD64 dwEP;
	void *pParam;
}CALL_MYFUNCTION, *PCALL_MYFUNCTION;
typedef DWORD(*_Function)(VOID *p);


//	远程函数线程
void WINAPI MyFunctionThread(PCALL_MYFUNCTION pCMF)
{
	if (pCMF != NULL && pCMF->dwEP != NULL)
	{
		_Function Function = (_Function)pCMF->dwEP;
		Function(pCMF->pParam);
	}
}

HANDLE MyCreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, LPDWORD lpThreadId)
{
	HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
	if (hNtDll != NULL)
	{
		DWORD dwImageSize = GetModuleSize((DWORD64)hNtDll);
		DbgPrintA("dwImageSize:%d", dwImageSize);
		BYTE *pMemoryData = (BYTE *)hNtDll + dwImageSize - 0x400;

		if (pMemoryData != NULL)
		{
			DWORD dwProtect;
			VirtualProtect(pMemoryData, 0x100, PAGE_EXECUTE_READWRITE, &dwProtect);
			CALL_MYFUNCTION *pCMF = (CALL_MYFUNCTION *)VirtualAlloc(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			pCMF->dwEP = (DWORD64)(lpStartAddress);
			pCMF->pParam = lpParameter;
			memcpy((LPVOID)pMemoryData, (LPVOID)MyFunctionThread, 0x100);
			HANDLE hHandle = CreateRemoteThread(GetCurrentProcess(), NULL, 0, (LPTHREAD_START_ROUTINE)pMemoryData, pCMF, NULL, lpThreadId);
			return hHandle;
		}
	}
	return 0;
}

extern void FuckEAC();
extern DWORD ThreadID;
void WINAPI InitGame(VOID *p)
{
	//bool installhook = false;
	while (TRUE)
	{
		/*
		if (GetModuleHandle("ntdll.dll") != NULL && GetModuleHandle("kernel32.dll") != NULL && !installhook)
		{
			MH_Initialize();
			FuckEAC();
			installhook = true;
		}*/
		global::g_hGameWnd = FindWindowA(XorString("Respawn001"), NULL);
		if (global::g_hGameWnd != NULL) {
			break;
		}
		Sleep(100);
	}
	Sleep(10000);
	OffsetsManger::Get().InstallOffset();
	DbgPrintA("InstallOffset Success!");
	Interfaces::getInterfaces();
	InitHook();
}
/*
LPVOID LM_CreateFakeThread(LPVOID Thread)
{
	DWORD ThreadAdresi = 0x40000; //your fake adress xD
	DWORD Old;
	VirtualProtect((LPVOID)ThreadAdresi, 0x1000, PAGE_EXECUTE_READWRITE, &Old);
	CONTEXT ctx;
	HANDLE tHand = CreateRemoteThread(GetCurrentProcess(), 0, 0, (LPTHREAD_START_ROUTINE)ThreadAdresi, 0, 0, 0);
	SuspendThread(tHand);
	ctx.ContextFlags = CONTEXT_INTEGER;
	GetThreadContext(tHand, &ctx);
	ctx.Eax = (DWORD)Thread;
	ctx.ContextFlags = CONTEXT_INTEGER;
	SetThreadContext(tHand, &ctx);
	ResumeThread(tHand);
	return (LPVOID)ctx.Eax;
}
*/
BOOL WINAPI DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID lpReserved)
{

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);	
		global::g_hInst = hModule;
		global::g_hGameImage = (DWORD64)GetModuleHandleA(NULL);
		global::g_dwModuleSize = GetModuleSize((DWORD64)hModule);
		MH_Initialize();
		FuckEAC();
		MyCreateThread((LPTHREAD_START_ROUTINE)InitGame, NULL, &ThreadID);
		DbgPrintA("Apex注入成功! g_hGameImage: 08%08X", global::g_hGameImage);
	}
	break;
	case DLL_PROCESS_DETACH:
	{

		return TRUE;
	}
	break;
	}

	return TRUE;
}