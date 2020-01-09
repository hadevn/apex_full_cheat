#pragma once
#include "Cheat.h"

class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class C_BaseEntity;
class IClientThinkable;
class IClientAlphaProperty;



class IClientEntityList {
public:
	virtual int unknowFun1() = 0;
	virtual int unknowFun2() = 0;
	virtual int unknowFun3() = 0;
	virtual int unknowFun4() = 0;
	virtual IClientEntity* GetClientEntity(int entNum) = 0;
	virtual void* GetClientEntityFromHandle(void* hEnt) = 0;
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int unknowFun5() = 0;
	virtual int GetHighestEntityIndex();
	virtual void SetMaxEntities(int maxEnts) = 0;
	virtual int GetMaxEntities() = 0;
};