#pragma once

#include "Cheat.h"
#include <string>
#include "math\Vector2D.hpp"
using namespace std;
typedef HRESULT(__stdcall *tD3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef __int64(__fastcall *_CreateMove)(CInput *pInput, int sequence_number, float input_sample_frametime, bool active);
extern _CreateMove OLD_CreateMove;
typedef __int64(__thiscall *_GetChecksum)(void *pThis);
extern _GetChecksum GetChecksum;
//typedef int(__fastcall *_CopyPoint)(DWORD64* a1);
//extern _CopyPoint CopyPoint;
typedef BOOL(WINAPI *_PeekMessageW)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
namespace Hooks
{
	extern __int64 __fastcall MyCreateMove(CInput * pInput, int sequence_number, float input_sample_frametime, bool active);
	extern HRESULT PresentHooked(IDXGISwapChain * pSwapChain, UINT SyncInterval, UINT flags);
	extern LRESULT hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	extern void InitDX11Hook();
	extern BOOL WINAPI MyPeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
}
class CFixMove
{
public:
	void Start();
	void End();
private:
	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;
};