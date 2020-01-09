#pragma once
#include "Cheat.h"
#include "render.h"
#include "math\Vector2D.hpp"
typedef struct
{
	wstring text;
	FLOAT FontSize;
	FLOAT X;
	FLOAT Y;
	UINT32 Color;
	UINT Flags;
}DRAWSTRING, *PDRAWSTRING;

class Draw {
public:
	void DrawString(float fontSize, const Vector2D &vec, ImU32 col, bool bCenter, bool stroke, const char *pText, ...);
	void DrawBox(const Vector2D &vecStart, const Vector2D &vecEnd, ImU32 col, float thickness);
	void DrawFilledBox(const Vector2D &vecStart, const Vector2D &vecEnd, ImU32 col);
	void DrawLine(const Vector2D &vecStart, const Vector2D &vecEnd, ImU32 col, float thickness = 1.0f);
	void DrawCircle(const Vector2D &vecCenter, float radius, ImU32 col, int num_seg, float thickness);
};