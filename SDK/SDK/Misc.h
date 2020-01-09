#pragma once
#include "Cheat.h"

enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};
enum AA_Pitch
{
	AA_Pitch_DOWN = 0,
//	AA_Pitch_Zero,
//	AA_Pitch_UP,
//	AA_Pitch_Mix,
	AA_Pitch_Lisp
};
enum AA_YAW
{
	AA_Yaw_Backward,
	AA_Yaw_SideWayL,
	AA_Yaw_SideWayR,
	AA_Yaw_FastSpin,
	AA_Yaw_SlowSpin,
	AA_Yaw_Jitter,
	AA_Yaw_MixJitter,
	AA_Yaw_Rand,
	AA_YAW_LispFake
};
static void inline SinCos(float radians, float *sine, float *cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}
static void AngleVectors(const Vector &angles, Vector *forward)
{
	float sp, sy, cp, cy;
	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}
static void VectorAngles(const Vector& forward, Vector &angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;
		if (angles[1] > 90) angles[1] -= 180;
		else if (angles[1] < 90) angles[1] += 180;
		else if (angles[1] == 90) angles[1] = 0;
	}
	angles[2] = 0.0f;
	
}
static float GetFov(const Vector& viewAngle, const Vector& aimAngle)
{
	Vector ang, aim;
	AngleVectors(viewAngle, &aim);
	AngleVectors(aimAngle, &ang);
	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}
static Vector CalcAngle(Vector src, Vector dst)
{
	Vector angles;
	Vector delta = src - dst;
	VectorAngles(delta, angles);
	delta.Normalize();
	return angles;
}

class CMiscellaneous
{
public:
	void Bunnyhop();
	void AutoStrafe();
};
class CRageBot
{
public:
	void DropTarget();
	void Rage();
	void FindTarget();
	void Aimbot();
	void AntiAim();
	CBaseEntity* m_ent;
	CBaseEntity* m_BastFovTarget;
	Vector m_BestPoint;
	bool aimboting;
	bool shoting;
	bool zooming;
	bool reseting;
	bool goAntiAim;
	int m_besthitbox;
//	int m_tickcount_backup;
};