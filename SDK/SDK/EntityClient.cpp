#include "Cheat.h"
#include "EntityClient.h"
struct VMatrixW2S
{
	float m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};
int IVEngineClient::GetLocalPlayerID()
{
	//GetLocalPlayer: 35 index
	if (!this) return 1;
	typedef int(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 36)(this);
}
bool IVEngineClient::IsConnected(void)
{
	if (!this) return false;
	//IsConnected 44 idx of IVEngineClient
	return GetVFunc<bool(__fastcall*)(void*)>(this, 44)(this);
}

bool IVEngineClient::IsInGame(void)
{
	typedef bool(__thiscall* OriginalFn)(void*);
	return GetVFunc< OriginalFn >(this, 45)(this);
}
VMatrixW2S getViewMatrix()
{
	uintptr_t view_render = *(uintptr_t *)((uintptr_t)GetModuleHandle(nullptr) + 0xD4138F0);
	if (!view_render)
		return VMatrixW2S{};

	uintptr_t pview_matrix = CUtils::Read<uintptr_t>(view_render + 0x1A93D0);
	if (pview_matrix != 0) {
		return *(VMatrixW2S*)((uintptr_t)pview_matrix);
	}
	return VMatrixW2S{};
}
bool ScreenTransform(const Vector& point, Vector2D& screen) // tots not pasted
{
	float w;
	const VMatrixW2S& worldToScreen = getViewMatrix();
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	//screen.z = 0.0f;

	bool behind = false;

	if (w < 0.001f)
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool IVEngineClient::W2S(const Vector& origin, Vector2D& screen)
{
	if (!ScreenTransform(origin, screen))
	{
		//int ScreenWidth, ScreenHeight;
		RECT rctA;
		::GetWindowRect(GetForegroundWindow(), &rctA);
		int ScreenWidth = rctA.right - rctA.left;
		int ScreenHeight = rctA.bottom - rctA.top;
		//I::Engine->GetScreenSize(ScreenWidth, ScreenHeight);
		float x = ScreenWidth / 2;
		float y = ScreenHeight / 2;
		x += 0.5 * screen.x * ScreenWidth + 0.5;
		y -= 0.5 * screen.y * ScreenHeight + 0.5;
		screen.x = x;
		screen.y = y;
		return true;
	}
	return false;
}
