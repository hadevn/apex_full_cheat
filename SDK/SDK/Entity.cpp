#include "Cheat.h"
#include "Offset.h"
#include "utils\StringCovert.h"
int CBaseEntity::m_iHealth()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_iHealth);
}

int CBaseEntity::m_iMaxHealth()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_iMaxHealth);
}
int CBaseEntity::m_shieldHealth()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_shieldHealth);
}
int CBaseEntity::m_shieldHealthMax()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_shieldHealthMax);
}
int CBaseEntity::m_iTeamNum()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_iTeamNum);
}
bool CBaseEntity::isAlive()
{
	if (!this)
		return false;
	bool result; // al
	if (*(DWORD*)((DWORD64)this + OFFSET::s_alivePtr) & 1)
		result = 0;
	else
		result = *(DWORD*)((DWORD64)this + OFFSET::m_lifeState) == 0; //DT_Player->m_lifeState : 0x718
	return result;

	//return *(int*)((DWORD64)this + OFFSET::m_lifeState) == 0;
}
DWORD64 CBaseEntity::m_iSignifierName()
{
	if (!this)
		return 0;
	return *(DWORD64*)((DWORD64)this + OFFSET::m_iSignifierName);
}
DWORD64 CBaseEntity::GetWeapon()//暂时用DWORD64
{
	if (!this)
		return 0;
	int weapid = CUtils::Read<DWORD>((DWORD64)G::LocalPlayer + OFFSET::m_latestPrimaryWeapons) & 0xFFFF;
	if (weapid != 0)
	{
		return (DWORD64)I::ClientEntList->GetClientEntity(weapid);
	}
	return 0;
}
//https://www.unknowncheats.me/forum/2399654-post1576.html
int CBaseEntity::GetWeaponID()//暂时用DWORD64
{
	if (!this)
		return -1;
	DWORD64 weapon = this->GetWeapon();
	if (!weapon)
		return -1;
	return *(int*)((DWORD64)weapon + OFFSET::m_weaponNameIndex);
}
bool CBaseEntity::isSniper()//暂时用DWORD64 
{
	if (!this)
		return false;
	switch (this->GetWeaponID())
	{
	case WEAPONID_长弓精准步枪:
	case WEAPONID_金狙:
	case WEAPONID_三重精准步枪:
	case WEAPONID_G7侦查枪:
	case WEAPONID_充能步枪:
		return true;
	default:
		return false;
		break;
	}
}
bool CBaseEntity::isShotGunWeapon()//暂时用DWORD64 
{
	if (!this)
		return false;
	switch (this->GetWeaponID())
	{
	case WEAPONID_和平捍卫者:
	case WEAPONID_獒犬霰弹:
	case WEAPONID_薯片枪:
	case WEAPONID_自动连喷:
		return true;
	default:
		return false;
		break;
	}
}
bool CBaseEntity::isSingleShotWeapon()//暂时用DWORD64 
{
	if (!this)
		return false;
	switch (this->GetWeaponID())
	{
	case WEAPONID_P2020手枪:
	case WEAPONID_G7侦查枪:
	case WEAPONID_小帮手:
	case WEAPONID_长弓精准步枪:
	case WEAPONID_连发突击步枪:
	case WEAPONID_三重精准步枪:
	case WEAPONID_和平捍卫者:
	case WEAPONID_金狙:
	case WEAPONID_獒犬霰弹:
	case WEAPONID_薯片枪:
		return true;
	default:
		return false;
		break;
	}
}
bool CBaseEntity::IsReloading()
{
	if (!this)
		return false;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return false;

	return *(bool*)(Weapon + OFFSET::m_bInReload);
}
int CBaseEntity::m_ammoInStockpile()
{
	if (!this)
		return -1;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return 0;

	return *(int*)(Weapon + OFFSET::m_ammoInClip);
}
int CBaseEntity::m_wallClimbSetUp()
{
	if (!this)
		return -1;
	return *(int*)(this + OFFSET::m_wallClimbSetUp);
}
float CBaseEntity::m_nextPrimaryAttackTime()
{
	if (!this)
		return 0.f;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return 0.f;

	return *(float*)(Weapon + OFFSET::m_nextPrimaryAttackTime);
}
int CBaseEntity::m_id()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + 8);
}
int CBaseEntity::ITEM_ID()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + 0x9C);
}
int CBaseEntity::ITEM_NameID()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_customScriptInt);
}
void CBaseEntity::SetViewAngles(Vector p1)
{
	if (!this)
		return;
	*(float*)((DWORD64)this + 0x2188) = p1.x;
	*(float*)((DWORD64)this + 0x218C) = p1.y;
	*(float*)((DWORD64)this + 0x2190) = p1.z;
}
Vector CBaseEntity::GetViewAngles()
{
	if (!this)
		return Vector(0, 0, 0);
	float x = *(float*)((DWORD64)this + 0x2188);
	float y = *(float*)((DWORD64)this + 0x218C);
	float z = *(float*)((DWORD64)this + 0x2190);
	return Vector(x, y, z);
		/*
	float x = *(float*)((DWORD64)this + 0x2150);
	float y = *(float*)((DWORD64)this + 0x2154);
	float z = *(float*)((DWORD64)this + 0x2158);
	return Vector(x,y,z);*/
}
Vector CBaseEntity::GetPunch()
{
	if (!this)
		return Vector(0, 0, 0);
	return *(Vector*)((DWORD64)this + OFFSET::s_shakePtr);
}
Vector CBaseEntity::m_localOrigin()
{
	if (!this)
		return Vector(0, 0, 0);
	/*
	Vector orgin;
	CUtils::ReadData((DWORD64)this + OFFSET::m_localOrigin, (void *)&orgin, sizeof(Vector));
	return orgin;*/
	return *(Vector*)((DWORD64)this + OFFSET::m_localOrigin);
}
Vector CBaseEntity::GetHeadPos()
{
	if (!this)
		return Vector(0, 0, 0);
	return GetBonePosition(BoneId::head);
	//Vector orgin;
	//CUtils::ReadData((DWORD64)this + 0xAC, (void *)&orgin, sizeof(Vector));
	//return orgin;
}
string CBaseEntity::GetPlayerName()
{
	if (!this)
		return "";
	int entityId = CUtils::Read<int>((DWORD64)this + OFFSET::s_entityID);		//ItemID0x9C		//这里的30和AOO 通过特征码定位手动更新
	DWORD64 namesList = CUtils::Read<DWORD64>(global::g_hGameImage + OFFSET::g_dwPlayerNameListPtr);
	char * name = CUtils::Read<char *>(namesList + entityId * 8 + OFFSET::s_playernamePtr);
	return Utf8ToAnsi(name);
}
void CBaseEntity::GetBoneMarx(Vector *pOutBoneArry)
{
	if (!this)
		return;
	FLOAT matrix[128][3][4];
	uintptr_t pBoneMatrix = CUtils::Read<DWORD64>((DWORD64)this + OFFSET::s_BoneMatrixPtr);
	if (pBoneMatrix)
	{
		CUtils::ReadData(pBoneMatrix, (char*)&matrix, sizeof(matrix));
	}

	for (int id = 0; id < 128; id++)
	{
		Vector bone_pos = Vector(matrix[id][0][3], matrix[id][1][3], matrix[id][2][3]) + this->m_localOrigin();
		pOutBoneArry[id] = bone_pos;
	}
}

bool CBaseEntity::m_bleedoutState()
{
	if (!this)
		return false;
	return *(bool*)((DWORD64)this + OFFSET::m_bleedoutState);
}
Vector CBaseEntity::GetBonePosition(int bone)
{
	if (!this)
		return Vector(0, 0, 0);
	FLOAT matrix[128][3][4];
	uintptr_t pBoneMatrix = CUtils::Read<DWORD64>((DWORD64)this + OFFSET::s_BoneMatrixPtr);
	if (pBoneMatrix)
	{
		CUtils::ReadData(pBoneMatrix, (char*)&matrix, sizeof(matrix));
	}

	for (int id = 0; id < 128; id++)
	{
		Vector bone_pos = Vector(matrix[id][0][3], matrix[id][1][3], matrix[id][2][3]) + this->m_localOrigin();
		if (id == bone)
			return bone_pos;
	}
	return Vector(0, 0, 0);
}
Vector CBaseEntity::GetEyePosition()
{
	return *(Vector*)((DWORD64)this + 0x1B68);
	/*
	if (!this)
		return Vector(0, 0, 0);
	Vector origin = this->m_localOrigin();
	Vector offset = *(Vector*)((DWORD64)this + 0x1B64);
	DbgPrintA("offset: %f %f %f ", offset.x, offset.y, offset.z);
	return(origin + offset);
	*/
}

Vector CBaseEntity::GetDynamic()
{
	return *(Vector*)((DWORD64)this + 0x2178);
}
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, // NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY, // NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS, // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType()
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};


class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};


typedef bool(*ShouldHitFunc_t)(IHandleEntity* pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter
{
public:
	// It does have a base, but we'll never network anything below here..
	CTraceFilterSimple(const IHandleEntity* passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
	virtual bool ShouldHitEntity(IHandleEntity* pHandleEntity, int contentsMask);

	virtual void SetPassEntity(const IHandleEntity* pPassEntity)
	{
		m_pPassEnt = pPassEntity;
	}

	virtual void SetCollisionGroup(int iCollisionGroup)
	{
		m_collisionGroup = iCollisionGroup;
	}

	const IHandleEntity* GetPassEntity(void)
	{
		return m_pPassEnt;
	}

private:
	const IHandleEntity* m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
};
/*
bool CBaseEntity::IsAimLocalPlayerHead()
{

	;
}

bool CBaseEntity::IsAimLocalPlayerBody()
{

;
}

bool CBaseEntity::IsAimLocalPlayer()
{
	if (!this)
		return false;
	Vector src3D, dst3D, forward;
	trace_t tr;
	ZeroMemory(&tr, sizeof(tr));
	Ray_t ray;
	ZeroMemory(&ray, sizeof(ray));
	AngleVectors(this->GetEyeAngles(), &forward);
	src3D = this->GetBonePosition(10) - Vector(0, 0, 0);
	dst3D = src3D + (forward * 4000.f);
	ray.Init(src3D, dst3D);
	I::EngineTrace->TraceRay(ray, 0x640400B, nullptr, &tr);
	if (tr.m_pEnt == G::LocalPlayer)
		return true;
	return false;
}
*/
bool CBaseEntity::IsVisible(int bone)
{
	if (!this)
		return false;

	Ray_t ray;
//	ZeroMemory(&ray, sizeof(ray));
	ray.Init(G::LocalPlayer->GetBonePosition(10), this->GetBonePosition(bone));
/*
	typedef INT64(__fastcall* pfnfunc)(Ray_t *a1, Vector&a, Vector &b);
	auto func1 = (pfnfunc)(global::g_hGameImage + 0x211cb0);
	func1(&ray, G::LocalPlayer->GetEyePosition(), this->GetBonePosition(bone));*/
	trace_t tr;
	ZeroMemory(&tr, sizeof(tr));
	bool m_visible = false;
	
	//I::EngineTrace->ClipRayToEntity(ray, 0x640400B, nullptr, &tr);
	I::EngineTrace->TraceRay(ray, 0x640400B, &tr);
	if (&tr == NULL)
		return false;

	return tr.m_pEnt == this || tr.fraction > 0.97f;

}
int CBaseEntity::GetFlags()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_fFlags);
}
Vector CBaseEntity::GetVelocity()
{
	if (!this)
		return Vector(0, 0, 0);
	return *(Vector*)((DWORD64)this + OFFSET::m_vecVelocity);
}

Vector CBaseEntity::GetvecAbsVelocity()
{
	if (!this)
		return Vector(0, 0, 0);
	return *(Vector*)((DWORD64)this + OFFSET::m_vecAbsVelocity);
}

Vector ExtrapolateTick(Vector p0, Vector v0)
{
	return p0 + (v0 * I::Globals->interval_per_tick);
}
Vector CBaseEntity::GetPredict(float dis,float BulletSpeed)
{
	if (!this)
		return Vector(0, 0, 0);
	Vector predict(0, 0, 0);
	float bulletTime = dis / BulletSpeed;
	predict.x = this->GetvecAbsVelocity().x * bulletTime;
	predict.y = this->GetvecAbsVelocity().y * bulletTime;
	predict.z = (375.f * 0.5f * (bulletTime * bulletTime)); //375.f 750.f 
	return  predict;

}
Vector CBaseEntity::GetEyeAngles()
{
	if (!this)
		return Vector(0,0,0);
	return *(Vector*)((DWORD64)this + OFFSET::m_localAngles);
}
Vector CBaseEntity::GetPredicted(Vector p0)
{
	return ExtrapolateTick(p0, this->GetVelocity());
}
bool CBaseEntity::m_bZooming()
{
	if (!this)
		return false;
	return *(bool*)((DWORD64)this + OFFSET::m_bZooming);
}
float CBaseEntity::GetDis()
{
	if (!this)
		return 0.f;
	return (this->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length();
}

DWORD64 CBaseEntity::ModelNamePtr()
{
	if (!this)
		return -1;
	return *(DWORD64*)((DWORD64)this + 0x40);
}
float CBaseEntity::GetbulletSpeed()
{
	if (!this)
		return 0.f;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return 0.f;
	return *(float*)(Weapon + OFFSET::s_bulletSpeed);
}

int CBaseEntity::GetWeaponShootType()
{
	if (!this)
		return -1;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return 0;
	return *(int*)(Weapon + OFFSET::m_customScriptInt);
}
bool CBaseEntity::GetShotStatus()
{
	if (!this)
		return false;
	return *(DWORD64*)(global::g_hGameImage + OFFSET::g_AutoShotAddr) == 5;
}
int CBaseEntity::m_shotCount()
{
	if (!this)
		return 0;
	DWORD64 Weapon = G::LocalPlayer->GetWeapon();
	if (!Weapon)
		return 0;
	return *(int*)((DWORD64)Weapon + OFFSET::m_shotCount);
}
void CBaseEntity::StartShot(bool bSwitch)
{
	if (!this)
		return;
	if ( bSwitch)
		*(DWORD64*)(global::g_hGameImage + OFFSET::g_AutoShotAddr) = 5;	//等于5是按下
	else
		*(DWORD64*)(global::g_hGameImage + OFFSET::g_AutoShotAddr) = 4;	
}
int CBaseEntity::m_lastUCmdSimulationTicks()
{
	if (!this)
		return -1;
	return *(int*)((DWORD64)this + OFFSET::m_lastUCmdSimulationTicks);
}

