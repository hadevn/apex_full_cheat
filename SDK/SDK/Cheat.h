#pragma once
template <typename T>
T GetVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}
#pragma once
#include "xorstr.hpp"
#include "Vars.h"
#include "Common.h"
#include "NetVars.h"
#include "MinHook\include\MinHook.h"
#include "math\Vector.hpp"
#include "math\Vector4D.hpp"
#include "dxgi.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "imgui\imgui.h"
#include "Offset.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <d3d11.h>

#include "Entity.h"
#include "Misc.h"
#include "EntityClient.h"
#include "GlobalVar.h"
#include "IClientEntityList.h"
#include "SDK.h"
#include "ActorMgr.h"

class CCheats
{
public:
	CCheats();
	~CCheats();

public:
	void DrawBone(ACTOR_INFO *pAI);
	void ESP();
	void Process();
	void DrawHighlight(ACTOR_INFO *pAI,bool bIsVisible);
	//void BulletTrace(CBaseEntity * entity, Color color);
public:
	CActorMgr *GetActor() { return m_pActor; }
private:
	CActorMgr *m_pActor;
	RECT m_rc;
};


CCheats *GetCheat();
void InitItemName();