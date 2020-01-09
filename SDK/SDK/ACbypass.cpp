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
#include <TlHelp32.h>
typedef LONG	NTSTATUS;
#define NT_SUCCESS(Status)			((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS              ((NTSTATUS)0x00000000L) // ntsubauth
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)
typedef LONG KPRIORITY;
#define random(x) (rand()%x)
typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,
	SystemProcessorInformation,
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation, //5  
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemNextEventIdInformation,
	SystemEventIdsInformation,
	SystemCrashDumpInformation,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemPlugPlayBusInformation,
	SystemDockInformation,
	SystemPowerInformation2,
	SystemProcessorSpeedInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName,
	MemoryBasicVlmInformation
} MEMORY_INFORMATION_CLASS;

typedef enum _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	MaxThreadInfoClass
} THREADINFOCLASS;

typedef struct _VM_COUNTERS
{
	ULONG	PeakVirtualSize;
	ULONG	VirtualSize;
	ULONG	PageFaultCount;
	ULONG	PeakWorkingSetSize;
	ULONG	WorkingSetSize;
	ULONG	QuotaPeakPagedPoolUsage;
	ULONG	QuotaPagedPoolUsage;
	ULONG	QuotaPeakNonPagedPoolUsage;
	ULONG	QuotaNonPagedPoolUsage;
	ULONG	PagefileUsage;
	ULONG	PeakPagefileUsage;
} VM_COUNTERS, *PVM_COUNTERS;

typedef enum _THREAD_STATE
{
	StateInitialized,
	StateReady,
	StateRunning,
	StateStandby,
	StateTerminated,
	StateWait,
	StateTransition,
	StateUnknown
} THREAD_STATE;

typedef struct _CLIENT_ID
{
	HANDLE	UniqueProcess;
	HANDLE	UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef enum _KWAIT_REASON
{
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVertualMemory,
	WrPageOut,
	WrRendezvous,
	Spare2,
	Spare3,
	Spare4,
	Spare5,
	Spare6,
	WrKernel
} KWAIT_REASON;

typedef struct _SYSTEM_THREADS
{
	LARGE_INTEGER	KernelTime;
	LARGE_INTEGER	UserTime;
	LARGE_INTEGER	CreateTime;
	ULONG			WaitTime;
	PVOID			StartAddress;
	CLIENT_ID		ClientId;
	KPRIORITY		Priority;
	KPRIORITY		BasePriority;
	ULONG			ContextSwitchCount;
	THREAD_STATE	State;
	KWAIT_REASON	WaitReason;
} SYSTEM_THREADS, *PSYSTEM_THREADS;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT * Buffer;
#else // MIDL_PASS
	PWSTR  Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _SYSTEM_PROCESSES
{
	ULONG			NextEntryDelta;			//	构成结构序列的偏移量
	ULONG			ThreadCount;			//	线程数目
	ULONG			Reserved1[6];
	LARGE_INTEGER	CreateTime;				//	创建时间
	LARGE_INTEGER	UserTime;				//	用户模式(Ring 3)的CPU时间
	LARGE_INTEGER	KernelTime;				//	内核模式(Ring 0)的CPU时间
	UNICODE_STRING	ProcessName;			//	进程名称
	KPRIORITY		BasePriority;			//	进程优先权
	ULONG			ProcessId;				//	进程标识符
	ULONG			InheritedFromProcessId;	//	父进程的标识符
	ULONG			HandleCount;			//	句柄数目
	ULONG			Reserved2[2];
	VM_COUNTERS		VmCounters;				//	虚拟存储器的结构
	IO_COUNTERS		IoCounters;				//	IO计数结构
	SYSTEM_THREADS	Threads[1];				//	进程相关线程的结构数组
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;


typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG		ProcessId;
	UCHAR		ObjectTypeNumber;
	UCHAR		Flags;
	USHORT		Handle;
	PVOID		Object;
	ACCESS_MASK	GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;


typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
	ULONG						NumberOfHandles;
	SYSTEM_HANDLE_INFORMATION	Information[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef struct __SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize;
	ULONG HardFaultCount;
	ULONG NumberOfThreadsHighWatermark;
	ULONGLONG CycleTime;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	LONG BasePriority;
	ULONG UniqueProcessId;
	PVOID InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey;
	ULONG_PTR PeakVirtualSize;
	ULONG_PTR VirtualSize;
	ULONG PageFaultCount;
	ULONG_PTR PeakWorkingSetSize;
	ULONG_PTR WorkingSetSize;
	ULONG_PTR QuotaPeakPagedPoolUsage;
	ULONG_PTR QuotaPagedPoolUsage;
	ULONG_PTR QuotaPeakNonPagedPoolUsage;
	ULONG_PTR QuotaNonPagedPoolUsage;
	ULONG_PTR PagefileUsage;
	ULONG_PTR PeakPagefileUsage;
	ULONG_PTR PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
} S_SYSTEM_PROCESS_INFORMATION, *P_SYSTEM_PROCESS_INFORMATION;

typedef NTSTATUS(WINAPI *_NtQueryVirtualMemory)(HANDLE  ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
_NtQueryVirtualMemory Old_ZwQueryVirtualMemory = NULL;
NTSTATUS WINAPI MyZwQueryVirtualMemory(HANDLE  ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength)
{
	NTSTATUS nt = Old_ZwQueryVirtualMemory(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);

	if (NT_SUCCESS(nt))
	{
		if (ProcessHandle == GetCurrentProcess() || GetProcessId(ProcessHandle) == GetCurrentProcessId())
		{
			if (BaseAddress >= global::g_hInst && BaseAddress <= (global::g_hInst + global::g_dwModuleSize))
			{
				if (MemoryInformationClass == MemoryBasicInformation)
				{
					//DbgPrintA("MyZwQueryVirtualMemory->MemoryBasicInformation 0x%llX",BaseAddress);
					
					MEMORY_BASIC_INFORMATION64 *pmbi = (MEMORY_BASIC_INFORMATION64 *)MemoryInformation;
					pmbi->AllocationBase = 0;
					pmbi->RegionSize = global::g_dwModuleSize;
					pmbi->Protect = PAGE_NOACCESS;
					pmbi->Type = 0;
					pmbi->State = MEM_FREE; //0x10000;
				}
				if (MemoryInformationClass == MemorySectionName)
				{
					//DbgPrintA("MyZwQueryVirtualMemory->MemorySectionName");
					PUNICODE_STRING SectionName = (PUNICODE_STRING)MemoryInformation;
					if (SectionName)
					{
						//DbgPrintA("SectionName:%s", SectionName->Buffer);
						memset(SectionName->Buffer, 0, SectionName->MaximumLength);
					}
					return STATUS_UNSUCCESSFUL;
				}
			}
		}

	}
	return nt;
}

/*

typedef LONG(WINAPI *NtQueryInformationThreadProc)(
_In_       HANDLE ThreadHandle,
_In_       THREADINFOCLASS ThreadInformationClass,
_Inout_    PVOID ThreadInformation,
_In_       ULONG ThreadInformationLength,
_Out_opt_  PULONG ReturnLength
);
*/
typedef NTSTATUS(NTAPI *_ZwQueryInformationThread)(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, _In_ ULONG ThreadInformationLength, _Out_opt_ PULONG ReturnLength);
_ZwQueryInformationThread Old_ZwQueryInformationThread;
NTSTATUS NTAPI MyZwQueryInformationThread(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, _In_ ULONG ThreadInformationLength, _Out_opt_ PULONG ReturnLength)
{
	if (ThreadQuerySetWin32StartAddress == ThreadInformationClass)
	{
		if (ThreadInformation >= global::g_hInst && ThreadInformation <= (global::g_hInst + global::g_dwModuleSize))
		{
			ThreadInformation = NULL;
			//这可不行
			DbgPrintA("MyZwQueryInformationThread: 0x%llX", ThreadInformation);
			return STATUS_UNSUCCESSFUL;
		}
	}
	return Old_ZwQueryInformationThread(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength, ReturnLength);
}
typedef NTSTATUS(NTAPI *_ZwReadVirtualMemory)(IN HANDLE ProcessHandle, IN PVOID BaseAddress, OUT PVOID Buffer, IN ULONG NumberOfBytesToRead, OUT PULONG NumberOfBytesReaded OPTIONAL);
_ZwReadVirtualMemory Old_ZwReadVirtualMemory;
NTSTATUS NTAPI MyZwReadVirtualMemory(IN HANDLE ProcessHandle, IN PVOID BaseAddress, OUT PVOID Buffer, IN ULONG NumberOfBytesToRead, OUT PULONG NumberOfBytesReaded OPTIONAL)
{
	if (GetCurrentProcess() != ProcessHandle)
	{
		DWORD dwPID = GetProcessId(ProcessHandle);
		if (dwPID != GetCurrentProcessId())
		{
			return Old_ZwReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, NumberOfBytesToRead, NumberOfBytesReaded);
		}
	}

	if (BaseAddress >= global::g_hInst && BaseAddress <= (global::g_hInst + global::g_dwModuleSize))
	{
		DbgPrintA("MyZwReadVirtualMemory: 0x%llX", BaseAddress);
		return STATUS_UNSUCCESSFUL;
	}
	return Old_ZwReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, NumberOfBytesToRead, NumberOfBytesReaded);
}
typedef NTSTATUS(NTAPI *_ZwProtectVirtualMemory)(IN HANDLE ProcessHandle, IN PVOID* BaseAddress, IN SIZE_T* NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection);
_ZwProtectVirtualMemory Old_ZwProtectVirtualMemory;
NTSTATUS NTAPI MyZwProtectVirtualMemory(IN HANDLE ProcessHandle, IN PVOID* BaseAddress, IN SIZE_T* NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection)
{
	if ((void *)BaseAddress >= global::g_hInst && (void *)BaseAddress <= (global::g_hInst + global::g_dwModuleSize))
	{
		DbgPrintA("MyZwProtectVirtualMemory:%llX", BaseAddress);
		return STATUS_UNSUCCESSFUL;
	}
	return Old_ZwProtectVirtualMemory(ProcessHandle, BaseAddress, NumberOfBytesToProtect, NewAccessProtection, OldAccessProtection);
}

typedef NTSTATUS(NTAPI *_RtlGetNativeSystemInformation)(IN ULONG SystemInformationClass, IN PVOID NativeSystemInformation, IN ULONG InformationLength, OUT PULONG ReturnLength OPTIONAL);
_RtlGetNativeSystemInformation Old_RtlGetNativeSystemInformation;
NTSTATUS NTAPI MyRtlGetNativeSystemInformation(IN ULONG SystemInformationClass, IN PVOID NativeSystemInformation, IN ULONG InformationLength, OUT PULONG ReturnLength OPTIONAL)
{
	NTSTATUS nt = Old_RtlGetNativeSystemInformation(SystemInformationClass, NativeSystemInformation, InformationLength, ReturnLength);
	if (NT_SUCCESS(nt))
	{
		if (SystemInformationClass == SystemProcessInformation)
		{
			//DbgPrintX("SystemProcessInformation");


			P_SYSTEM_PROCESS_INFORMATION prev = P_SYSTEM_PROCESS_INFORMATION(NativeSystemInformation);
			P_SYSTEM_PROCESS_INFORMATION curr = P_SYSTEM_PROCESS_INFORMATION((PUCHAR)prev + prev->NextEntryOffset);

			while (prev->NextEntryOffset != NULL)
			{
				if ((!lstrcmpiW(curr->ImageName.Buffer, L"notepad.exe") || !lstrcmpiW(curr->ImageName.Buffer, L"client.exe") || !lstrcmpiW(curr->ImageName.Buffer, L"RemoteDll64.exe")) && curr->UniqueProcessId != GetCurrentProcessId())
				{
					//DbgPrintZ(L"SystemProcessInformation->curr->ImageName.Buffer = %s", curr->ImageName.Buffer);
					if (curr->NextEntryOffset == 0) {
						prev->NextEntryOffset = 0;
					}
					else {
						prev->NextEntryOffset += curr->NextEntryOffset;
					}
					curr = prev;
				}
				prev = curr;
				curr = P_SYSTEM_PROCESS_INFORMATION((PUCHAR)curr + curr->NextEntryOffset);
			}
		}

		if (SystemInformationClass == SystemModuleInformation)
		{
			DbgPrintA("SystemModuleInformation");


		}
	}

	return nt;
}
typedef BOOL(WINAPI *_IsBadReadPtr)(_In_opt_ CONST VOID *lp, _In_ UINT_PTR ucb);
_IsBadReadPtr Old_IsBadReadPtr;
BOOL WINAPI MyIsBadReadPtr(_In_opt_ CONST VOID *lp, _In_ UINT_PTR ucb)
{
	if (lp >= global::g_hInst && lp <= (global::g_hInst + global::g_dwModuleSize))
	{
		return 1;
	}
	return Old_IsBadReadPtr(lp, ucb);
}

typedef BOOL(WINAPI *_EnumProcessModulesEx)(HANDLE  hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded, DWORD dwFilterFlag);
_EnumProcessModulesEx Old_EnumProcessModulesEx;
BOOL WINAPI MyEnumProcessModulesEx(HANDLE  hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded, DWORD dwFilterFlag)
{
	BOOL bRet = Old_EnumProcessModulesEx(hProcess, lphModule, cb, lpcbNeeded, dwFilterFlag);
	if (bRet)
	{
		if (hProcess == GetCurrentProcess() || GetProcessId(hProcess) == GetCurrentProcessId())
		{
			DbgPrintA("MyEnumProcessModulesEx");
		}
	}
	return bRet;
}
/*
WINBASEAPI
SIZE_T
WINAPI
VirtualQuery(
	_In_opt_ LPCVOID lpAddress,
	_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,
	_In_ SIZE_T dwLength
);

*/
//static bool first = false;
typedef SIZE_T(WINAPI *_VirtualQuery)(_In_opt_ LPCVOID lpAddress,_Out_writes_bytes_to_(dwLength, return) PMEMORY_BASIC_INFORMATION lpBuffer,_In_ SIZE_T dwLength);
_VirtualQuery Old_VirtualQuery;
SIZE_T WINAPI MyVirtualQuery(HANDLE lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
//	DbgPrintA("EAC Memory Scaning: 0x%llX", lpAddress);
	SIZE_T shit = Old_VirtualQuery(lpAddress, lpBuffer, dwLength);
	if (lpAddress >= global::g_hInst && lpAddress <= (global::g_hInst + global::g_dwModuleSize))
	{
		//DbgPrintA("MyVirtualQuery: 0x%llX", lpAddress);
		lpBuffer->AllocationBase = 0;
		lpBuffer->RegionSize = global::g_dwModuleSize;
		lpBuffer->Protect = PAGE_NOACCESS;
		lpBuffer->Type = 0;
		lpBuffer->State = MEM_FREE;
		//dwLength = sizeof(lpBuffer);
	}
	return shit;
}
/*
typedef __int64(WINAPI *_RtlUserThreadStart)(PTHREAD_START_ROUTINE pfnStartAddr, PVOID pvParam);
_RtlUserThreadStart Old_RtlUserThreadStart;
typedef __int64(WINAPI *_BaseThreadInitThunk)(DWORD LdrReserved, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter);
//VOID BaseThreadInitThunk(DWORD LdrReserved, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
__int64 WINAPI MyRtlUserThreadStart(PTHREAD_START_ROUTINE pfnStartAddr, PVOID pvParam)
{
	if ((HANDLE)pfnStartAddr >= global::g_hInst && (HANDLE)pfnStartAddr <= (global::g_hInst + global::g_dwModuleSize))
	{
		//自己的不经过EAC的
		DbgPrintA("MyRtlUserThreadStart My Thread! 0x%11X", pfnStartAddr);
		static _BaseThreadInitThunk BaseThreadInitThunk = (_BaseThreadInitThunk)GetProcAddress(GetModuleHandleA("kernel32.dll"), XorString("BaseThreadInitThunk"));
		return BaseThreadInitThunk(0, pfnStartAddr, pvParam);
	}
	return Old_RtlUserThreadStart(pfnStartAddr, pvParam);
}*/
DWORD ThreadID;
/*
typedef BOOL(WINAPI *_Thread32Next)(HANDLE hSnapshot,LPTHREADENTRY32 lpte);
_Thread32Next Old_Thread32Next;
BOOL MyThread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte)
{
	BOOL Result = Old_Thread32Next(hSnapshot, lpte);
	if (lpte->th32ThreadID == ThreadID)
	{
		DbgPrintA("MyThread32Next EAC试图查询线程ID! %d", lpte->th32ThreadID);
		lpte->th32OwnerProcessID = 0;
		lpte->th32ThreadID = random(666);
	}
	return Result;
}*/
typedef HANDLE(WINAPI *_OpenThread)(_In_ DWORD dwDesiredAccess,_In_ BOOL bInheritHandle,_In_ DWORD dwThreadId);
_OpenThread Old_OpenThread;
HANDLE MyOpenThread(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwThreadId)
{
	DWORD threadID = dwThreadId;
	if (threadID == ThreadID)
	{
		DbgPrintA("MyOpenThread EAC试图打开线程! %d", dwThreadId);
		threadID = 0;
	}
		
	return Old_OpenThread(dwDesiredAccess, bInheritHandle, threadID);
}
void StartHook()
{
	HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
	HMODULE hKEDll = GetModuleHandleA("kernel32.dll");
	if (hNtDll != NULL)
	{
		_NtQueryVirtualMemory ZwQueryVirtualMemory = (_NtQueryVirtualMemory)GetProcAddress(hNtDll, XorString("NtQueryVirtualMemory"));
		_ZwReadVirtualMemory ZwReadVirtualMemory = (_ZwReadVirtualMemory)GetProcAddress(hNtDll, XorString("ZwReadVirtualMemory"));
		_ZwProtectVirtualMemory ZwProtectVirtualMemory = (_ZwProtectVirtualMemory)GetProcAddress(hNtDll, XorString("ZwProtectVirtualMemory"));
		_RtlGetNativeSystemInformation RtlGetNativeSystemInformation = (_RtlGetNativeSystemInformation)GetProcAddress(hNtDll, XorString("RtlGetNativeSystemInformation"));

		_VirtualQuery VirtualQuery = (_VirtualQuery)GetProcAddress(hKEDll, XorString("VirtualQuery"));
		//_IsBadReadPtr IsBadReadPtr = (_IsBadReadPtr)GetProcAddress(hKEDll, XorString("IsBadReadPtr"));

		_ZwQueryInformationThread ZwQueryInformationThread = (_ZwQueryInformationThread)GetProcAddress(hNtDll, XorString("ZwQueryInformationThread"));
		//_RtlUserThreadStart RtlUserThreadStart = (_RtlUserThreadStart)GetProcAddress(hNtDll, XorString("RtlUserThreadStart"));
		/*
		if (MH_CreateHookApi(L"kernel32.dll", XorString("Thread32Next"), &MyThread32Next, reinterpret_cast<void**>(&Old_Thread32Next)) != MH_OK)
		{
			DbgPrintA("失败Thread32Next");
			return;
		}*/
		if (MH_CreateHookApi(L"kernel32.dll", XorString("OpenThread"), &MyOpenThread, reinterpret_cast<void**>(&Old_OpenThread)) != MH_OK)
		{
			DbgPrintA("失败OpenThread");
			return;
		}
		if (MH_CreateHookApi(L"ntdll.dll", XorString("ZwQueryVirtualMemory"), &MyZwQueryVirtualMemory, reinterpret_cast<void**>(&Old_ZwQueryVirtualMemory)) != MH_OK)
		{
			DbgPrintA("失败ZwQueryVirtualMemory");
			return;
		}
		/*
		if (MH_CreateHookApi(L"ntdll.dll", XorString("RtlUserThreadStart"), &MyRtlUserThreadStart, reinterpret_cast<void**>(&Old_RtlUserThreadStart)) != MH_OK)
		{
			DbgPrintA("失败RtlUserThreadStart");
			return;
		}*/
		if (MH_CreateHookApi(L"ntdll.dll", XorString("ZwReadVirtualMemory"), &MyZwReadVirtualMemory, reinterpret_cast<void**>(&Old_ZwReadVirtualMemory)) != MH_OK)
		{
			DbgPrintA("失败ZwReadVirtualMemory");
			return;
		}
		if (MH_CreateHookApi(L"ntdll.dll", XorString("ZwProtectVirtualMemory"), &MyZwProtectVirtualMemory, reinterpret_cast<void**>(&Old_ZwProtectVirtualMemory)) != MH_OK)
		{
			DbgPrintA("失败ZwProtectVirtualMemory");
			return;
		}
		if (MH_CreateHookApi(L"ntdll.dll", XorString("ZwQueryInformationThread"), &MyZwQueryInformationThread, reinterpret_cast<void**>(&Old_ZwQueryInformationThread)) != MH_OK)
		{
			DbgPrintA("失败MyZwQueryInformationThread");
			return;
		}
		if (MH_CreateHookApi(L"ntdll.dll", XorString("RtlGetNativeSystemInformation"), &MyRtlGetNativeSystemInformation, reinterpret_cast<void**>(&Old_RtlGetNativeSystemInformation)) != MH_OK)
		{
			DbgPrintA("失败RtlGetNativeSystemInformation");
			return;
		}
		
		if (MH_CreateHookApi(L"kernel32.dll", XorString("IsBadReadPtr"), &MyIsBadReadPtr, reinterpret_cast<void**>(&Old_IsBadReadPtr)) != MH_OK)
		{
			DbgPrintA("失败IsBadReadPtr");
			return;
		}
		
		if (MH_CreateHookApi(L"kernel32.dll", XorString("VirtualQuery"), &MyVirtualQuery, reinterpret_cast<void**>(&Old_VirtualQuery)) != MH_OK)
		{
			DbgPrintA("失败VirtualQuery");
			return;
		}

		/*
		HMODULE hPsapi = LoadLibraryA("psapi.dll");
		
		_EnumProcessModulesEx EnumProcessModulesEx = (_EnumProcessModulesEx)GetProcAddress(hPsapi, "EnumProcessModulesEx");
		if (MH_CreateHookApi(L"psapi.dll", "EnumProcessModulesEx", &MyEnumProcessModulesEx, reinterpret_cast<void**>(&Old_EnumProcessModulesEx)) != MH_OK)
		{
			DbgPrintA("失败EnumProcessModulesEx");
			return;
		}*/

		MH_STATUS sts;
		/*
		if ((sts = MH_EnableHook(&Thread32Next)) != MH_OK)
		{
			DbgPrintA("Thread32Next 失败:%s", MH_StatusToString(sts));
			return;
		}*/
		if ((sts = MH_EnableHook(&OpenThread)) != MH_OK)
		{
			DbgPrintA("OpenThread 失败:%s", MH_StatusToString(sts));
			return;
		}
		if ((sts = MH_EnableHook(ZwQueryVirtualMemory)) != MH_OK)
		{
			DbgPrintA("ZwQueryVirtualMemory 失败:%s", MH_StatusToString(sts));
			return;
		}
		if ((sts = MH_EnableHook(ZwReadVirtualMemory)) != MH_OK)
		{
			DbgPrintA("ZwReadVirtualMemory 失败:%s", MH_StatusToString(sts));
			return;
		}
		if ((sts = MH_EnableHook(ZwProtectVirtualMemory)) != MH_OK)
		{
			DbgPrintA("ZwProtectVirtualMemory 失败:%s", MH_StatusToString(sts));
			return;
		}
		if ((sts = MH_EnableHook(RtlGetNativeSystemInformation)) != MH_OK)
		{
			DbgPrintA("RtlGetNativeSystemInformation 失败:%s", MH_StatusToString(sts));
			return;
		}
		
		if ((sts = MH_EnableHook(&IsBadReadPtr)) != MH_OK)
		{
			DbgPrintA("IsBadReadPtr 失败:%s", MH_StatusToString(sts));
			return;
		}
		
		if ((sts = MH_EnableHook(VirtualQuery)) != MH_OK)
		{
			DbgPrintA("VirtualQuery 失败:%s", MH_StatusToString(sts));
			return;
		}
		if ((sts = MH_EnableHook(ZwQueryInformationThread)) != MH_OK)
		{
			DbgPrintA("ZwQueryInformationThread 失败:%s", MH_StatusToString(sts));
			return;
		}
		/*
		if ((sts = MH_EnableHook(RtlUserThreadStart)) != MH_OK)
		{
			DbgPrintA("RtlUserThreadStart 失败:%s", MH_StatusToString(sts));
			return;
		}
		
		if ((sts = MH_EnableHook(EnumProcessModulesEx)) != MH_OK)
		{
			DbgPrintA("失败:%s", MH_StatusToString(sts));
			return;
		}*/
	}
}
void FuckEAC()
{
	StartHook();
}