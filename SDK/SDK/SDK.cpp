#include "Cheat.h"
#include "Color.h"
IVEngineClient*	I::Engine;
IGlobalVarsBase* I::Globals;
IClientEntityList* I::ClientEntList;
IEngineTrace* I::EngineTrace;
CBaseEntity* G::LocalPlayer;
CUserCmd* G::UserCmd;
CMiscellaneous*	E::Misc = new CMiscellaneous();
CRageBot* E::RageBot = new CRageBot();
GColor* G::gc;
bool G::PressedKeys[256] = {};
bool G::SendPacket = true;

//ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;
void IEngineTrace::ClipRayToEntity(Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace)
{
	if (!this) return;
	typedef int(__fastcall* OriginalFn)(void*, Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace);
	GetVFunc<OriginalFn>(this, 3)(this, ray, fMask, pEnt, pTrace);
}

void IEngineTrace::TraceRay(Ray_t &ray, unsigned int fMask,trace_t *pTrace)
{
	if (!this) return;
	typedef int(__fastcall* OriginalFn)(void*, Ray_t &ray, unsigned int fMask,trace_t *pTrace);
	GetVFunc<OriginalFn>(this, 4)(this, ray, fMask, pTrace);
}

void IEngineTrace::fnTraceRay(Ray_t *ray, Vector form, Vector to)
{
	if (!this) return;

	typedef int(__fastcall* OriginalFn)(void*, Ray_t *ray, Vector form, Vector to);
	GetVFunc<OriginalFn>(this, 6)(this, ray, form, to);
}
