#pragma once
#include "Cheat.h"

class CBaseEntity {
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
	template<class T>
	inline T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
public:
	int m_iHealth();
	int m_iMaxHealth();
	int m_shieldHealth();
	int m_shieldHealthMax();
	int m_iTeamNum();
	bool isAlive();
	DWORD64 m_iSignifierName();
	DWORD64 GetWeapon();
	int GetWeaponID();
	bool isSniper();
	bool isShotGunWeapon();
	bool isSingleShotWeapon();
	bool IsReloading();
	int m_ammoInStockpile();
	int m_wallClimbSetUp();
	float m_nextPrimaryAttackTime();
	int m_id();
	int ITEM_ID();
	int ITEM_NameID();
	void SetViewAngles(Vector p1);
	Vector GetViewAngles();
	Vector GetPunch();
	Vector m_localOrigin();
	Vector GetHeadPos();
	string GetPlayerName();
	void GetBoneMarx(Vector * pOutBoneArry);
	bool m_bleedoutState();
	Vector GetBonePosition(int bone);
	Vector GetEyePosition();
	Vector GetDynamic();
	bool IsAimLocalPlayerHead();
	bool IsAimLocalPlayerBody();
	bool IsAimLocalPlayer();
	bool IsVisible(int bone);
	int GetFlags();
	Vector GetVelocity();
	Vector GetvecAbsVelocity();
	Vector GetPredict(float dis, float BulletSpeed);
	Vector GetEyeAngles();
	Vector GetPredicted(Vector p0);
	bool m_bZooming();
	float GetDis();
	DWORD64 ModelNamePtr();
	float GetbulletSpeed();
	int GetWeaponShootType();
	bool GetShotStatus();
	int m_shotCount();
	void StartShot(bool bSwitch);
	int m_lastUCmdSimulationTicks();
};
class IHandleEntity
{
public:
	virtual ~IHandleEntity()
	{}

	virtual void SetRefEHandle() = 0;
	virtual void GetRefEHandle() const = 0;
};