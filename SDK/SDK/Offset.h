#pragma once
#include "singleton.hpp"
class OffsetsManger :public Singleton<OffsetsManger> {
public:
	void InstallOffset();
};
namespace OFFSET
{
	extern uint64_t D3D_igo64;
	extern uint64_t m_lastUCmdSimulationTicks;
	extern uint64_t m_weaponNameIndex;
	extern uint64_t g_AutoShotAddr;
	extern uint64_t m_bZooming;
	extern uint64_t m_localAngles;
	extern uint64_t g_SendPacket;
	extern uint64_t g_GameSpeedHack;
	extern uint64_t vecViewOffset_Pitch;
	extern uint64_t vecViewOffset_Yaw;
	extern uint64_t vecViewOffset_Roll;
	extern uint64_t uNetVarPtr;
	extern uint64_t g_dwPlayerNameListPtr;
	extern uint64_t uDX11Base;
	extern uint64_t uEngineClient;
	extern uint64_t g_dwWorldToScreenEP;
	extern uint64_t g_dwInGamePtr;
	extern uint64_t uGolbals;
	extern uint64_t uCreateInterface;
	extern uint64_t CopyPointEP;
	extern uint64_t GetChecksumEP;
	extern uint64_t SilentAimAddr;
	extern uint64_t m_bInReload;
	extern uint64_t m_ammoInClip;
	extern uint64_t m_angEyeAngles;
	extern uint64_t m_iHealth;
	extern uint64_t m_iMaxHealth;
	extern uint64_t m_shieldHealth;
	extern uint64_t m_shieldHealthMax;
	extern uint64_t m_iSignifierName;
	extern uint64_t m_iTeamNum;
	extern uint64_t m_localOrigin;
	extern uint64_t m_iHealth;
	extern uint64_t m_iMaxHealth;
	extern uint64_t m_shieldHealth;
	extern uint64_t m_shieldHealthMax;
	extern uint64_t m_iSignifierName;
	extern uint64_t m_iTeamNum;
	extern uint64_t m_localOrigin;
	extern uint64_t uGolbals;
	extern uint64_t m_vecAbsVelocity;
	extern uint64_t m_customScriptInt;
	extern uint64_t m_latestPrimaryWeapons;
	extern uint64_t m_nextPrimaryAttackTime;
	extern uint64_t m_lifeState;
	extern uint64_t m_shotCount;
	extern uint64_t m_fFlags;
	extern uint64_t m_vecVelocity;
	extern uint64_t m_wallClimbSetUp;
	extern uint64_t m_bleedoutState;
	extern uint64_t s_entityID;
	extern uint64_t s_playernamePtr;
	extern uint64_t s_alivePtr;
	extern uint64_t s_BoneMatrixPtr;
	extern uint64_t s_bulletSpeed;
	extern uint64_t s_weaponSpread;
	extern uint64_t s_shakePtr;
}
