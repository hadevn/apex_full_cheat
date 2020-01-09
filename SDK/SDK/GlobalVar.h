#pragma once
#include "Cheat.h"
class IGlobalVarsBase
{
public:
	float realtime; //0x0000
	int32_t framecount; //0x0004
	float absoluteframetime; //0x0008
	float curtime; //0x000C
	float frametime; //0x0010
	int32_t tickcount; //0x0014
	float Unk1; //0x0018
	float interval_per_tick; //0x001C
	float interpolation_amount; //0x0020
	int32_t simTicksThisFrame; //0x0024
	int32_t network_protocol; //0x0028
}; //Size: 0x002C