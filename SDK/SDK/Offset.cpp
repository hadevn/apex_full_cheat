#include "Cheat.h"
#include "hooks.h"

uint64_t OFFSET::g_AutoShotAddr = 0;
uint64_t OFFSET::g_SendPacket = 0;
uint64_t OFFSET::g_GameSpeedHack = 0;
uint64_t OFFSET::uNetVarPtr = 0;
uint64_t OFFSET::uDX11Base = 0;// 0x25DA8398;
uint64_t OFFSET::g_dwPlayerNameListPtr = 0;
uint64_t OFFSET::g_dwWorldToScreenEP;
uint64_t OFFSET::uEngineClient = 0;
uint64_t OFFSET::uGolbals = 0;
uint64_t OFFSET::uCreateInterface = 0;
uint64_t OFFSET::g_dwInGamePtr = 0;				//x	
uint64_t OFFSET::m_iHealth = 0;
uint64_t OFFSET::m_iMaxHealth = 0;
uint64_t OFFSET::m_shieldHealth = 0;
uint64_t OFFSET::m_shieldHealthMax = 0;
uint64_t OFFSET::m_iSignifierName = 0;
uint64_t OFFSET::m_iTeamNum = 0;
uint64_t OFFSET::m_localOrigin = 0;
uint64_t OFFSET::m_vecAbsVelocity = 0;
uint64_t OFFSET::m_customScriptInt = 0;			//这里不能确定 应该是 这个是通过这个ID取武器名字
uint64_t OFFSET::m_latestPrimaryWeapons = 0;
uint64_t OFFSET::m_nextPrimaryAttackTime = 0;
uint64_t OFFSET::m_lifeState = 0;
uint64_t OFFSET::m_shotCount = 0;
uint64_t OFFSET::m_vecVelocity = 0;
uint64_t OFFSET::m_bInReload = 0;
uint64_t OFFSET::m_ammoInClip = 0;
uint64_t OFFSET::m_wallClimbSetUp = 0;
uint64_t OFFSET::m_angEyeAngles = 0;
uint64_t OFFSET::CopyPointEP = 0;
uint64_t OFFSET::GetChecksumEP = 0;
uint64_t OFFSET::SilentAimAddr = 0;
uint64_t OFFSET::m_localAngles = 0;
uint64_t OFFSET::vecViewOffset_Pitch = 0;
uint64_t OFFSET::vecViewOffset_Yaw = 0;
uint64_t OFFSET::vecViewOffset_Roll = 0;
uint64_t OFFSET::m_bZooming = 0;
uint64_t OFFSET::s_entityID = 0;
uint64_t OFFSET::s_playernamePtr = 0xA00;		//这里手动更新	在g_dwPlayerNameListPtr特征码下面的CALL里,或者写CALL
uint64_t OFFSET::s_alivePtr = 0;				//这里F6 41 ?? 01 74 03 32 C0 C3 或者 搜索isAlive
uint64_t OFFSET::s_BoneMatrixPtr = 0;			//这里用特征码搜索48 8B 86 ?? ?? ?? ?? 4B 8D 0C 76 48 03 C9 0F 10 04 C8
uint64_t OFFSET::s_bulletSpeed = 0;				//这里48 8B FE 48 8B 05 ?? ?? ?? ?? F3 0F 59 B3 ?? ?? ?? ??   或者FireWeaponBolt_Script
uint64_t OFFSET::s_weaponSpread = 0;			//这里F3 0F 5C D1 F3 0F 59 D0 F3 0F 58 D1 F3 0F 58 93 或者GetSpread
uint64_t OFFSET::s_shakePtr = 0;				//这里E8 ? ? ? ? F2 0F 10 93 ? ? ? ? 0F 28 D8 
uint64_t OFFSET::m_fFlags = 0;
uint64_t OFFSET::m_bleedoutState = 0;
uint64_t OFFSET::m_weaponNameIndex = 0;
uint64_t OFFSET::m_lastUCmdSimulationTicks = 0;
uint64_t OFFSET::D3D_igo64 = 0;
void OffsetsManger::InstallOffset()
{
	//SEProtectStartMutation();
	uint64_t uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "4C 8B 1D ?? ?? ?? ?? 4D 85 DB 74 19");
	OFFSET::uNetVarPtr = uFindPos + *(uint32_t *)(uFindPos + 3) + 7 - global::g_hGameImage;
	DbgPrintA("uNetVarPtr:%08X", OFFSET::uNetVarPtr);

	if (OFFSET::uNetVarPtr != 0)
	{
		CNetVars::Get().Initialize();
		//CNetVars::Get().DumpNetvars();
		DbgPrintA("%04X", CNetVars::Get().GetOffset("DT_Player", "m_iHealth"));
		OFFSET::m_iHealth = CNetVars::Get().GetOffset("DT_Player", "m_iHealth");
		OFFSET::m_iMaxHealth = CNetVars::Get().GetOffset("DT_Player", "m_iMaxHealth");
		OFFSET::m_shieldHealth = CNetVars::Get().GetOffset("DT_Player", "m_shieldHealth");
		OFFSET::m_shieldHealthMax = CNetVars::Get().GetOffset("DT_Player", "m_shieldHealthMax");
		OFFSET::m_iSignifierName = CNetVars::Get().GetOffset("DT_BaseEntity", "m_iSignifierName");
		OFFSET::m_iTeamNum = CNetVars::Get().GetOffset("DT_BaseEntity", "m_iTeamNum");
		OFFSET::m_vecAbsVelocity = CNetVars::Get().GetOffset("DT_Player", "m_vecAbsVelocity");
		OFFSET::m_localOrigin = OFFSET::m_vecAbsVelocity + 0xC;
		OFFSET::m_customScriptInt = CNetVars::Get().GetOffset("DT_PropSurvival", "m_customScriptInt");
		OFFSET::m_latestPrimaryWeapons = CNetVars::Get().GetOffset("DT_Player", "m_latestPrimaryWeapons");
		OFFSET::m_lifeState = CNetVars::Get().GetOffset("DT_Player", "m_lifeState");
		OFFSET::m_shotCount = CNetVars::Get().GetOffset("DT_WeaponX", "m_shotCount");
		OFFSET::m_fFlags = CNetVars::Get().GetOffset("DT_Player", "m_fFlags");
		OFFSET::m_wallClimbSetUp = CNetVars::Get().GetOffset("DT_Player", "m_wallClimbSetUp");
		//OFFSET::vecViewOffset_Pitch = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.x");
		//OFFSET::vecViewOffset_Yaw = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.y");
		//OFFSET::vecViewOffset_Roll = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.z");
		OFFSET::m_angEyeAngles = CNetVars::Get().GetOffset("DT_Player", "m_angEyeAngles.x"); //0x00000018 = X[24] 0x0000001C = Y[28]  
		OFFSET::vecViewOffset_Pitch = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.x");
		OFFSET::vecViewOffset_Yaw = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.y");
		OFFSET::vecViewOffset_Roll = CNetVars::Get().GetOffset("DT_Player", "m_vecViewOffset.z");
		OFFSET::m_vecVelocity = CNetVars::Get().GetOffset("DT_Player", "m_vecVelocity");
		OFFSET::m_ammoInClip = CNetVars::Get().GetOffset("DT_WeaponX", "m_ammoInClip");
		OFFSET::m_bInReload = CNetVars::Get().GetOffset("DT_WeaponX", "m_bInReload");
		OFFSET::m_nextPrimaryAttackTime = CNetVars::Get().GetOffset("DT_WeaponX", "m_nextPrimaryAttackTime");
		OFFSET::m_bleedoutState = CNetVars::Get().GetOffset("DT_Player", "m_bleedoutState");
		OFFSET::m_localAngles = CNetVars::Get().GetOffset("DT_Player", "m_localAngles");
		OFFSET::m_bZooming = CNetVars::Get().GetOffset("DT_Player", "m_bZooming");
		OFFSET::m_weaponNameIndex = CNetVars::Get().GetOffset("DT_WeaponX", "m_weaponNameIndex");
		OFFSET::m_lastUCmdSimulationTicks = CNetVars::Get().GetOffset("DT_Player", "m_lastUCmdSimulationTicks");

		DbgPrintA("m_iHealth:%08X", OFFSET::m_iHealth);
		DbgPrintA("m_iMaxHealth:%08X", OFFSET::m_iMaxHealth);
		DbgPrintA("m_shieldHealth:%08X", OFFSET::m_shieldHealth);
		DbgPrintA("m_shieldHealthMax:%08X", OFFSET::m_shieldHealthMax);
		DbgPrintA("m_iSignifierName:%08X", OFFSET::m_iSignifierName);
		DbgPrintA("m_iTeamNum:%08X", OFFSET::m_iTeamNum);
		DbgPrintA("m_vecAbsVelocity:%08X", OFFSET::m_vecAbsVelocity);
		DbgPrintA("m_localOrigin:%08X", OFFSET::m_localOrigin);
		DbgPrintA("m_customScriptInt:%08X", OFFSET::m_customScriptInt);
		DbgPrintA("m_latestPrimaryWeapons:%08X", OFFSET::m_latestPrimaryWeapons);
		DbgPrintA("m_lifeState:%08X", OFFSET::m_lifeState);
		DbgPrintA("m_shotCount:%08X", OFFSET::m_shotCount);
		DbgPrintA("m_localAngles:%08X", OFFSET::m_localAngles);
		DbgPrintA("vecViewOffset: %08X %08X %08X", OFFSET::vecViewOffset_Pitch, OFFSET::vecViewOffset_Yaw,OFFSET::vecViewOffset_Roll);
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//g_dwPlayerNameListPtr//4C 39 05 ? ? ? ? 74 0D 8B 51 ? E8 ? ? ? ? 48 85 C0
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "4C 39 05 ?? ?? ?? ?? 74 0D 8B 51 ?? E8 ?? ?? ?? ?? 48 85 C0");
	OFFSET::g_dwPlayerNameListPtr = uFindPos + *(uint32_t*)(uFindPos + 3) + 7 - global::g_hGameImage;
	DbgPrintA("g_dwPlayerNameListPtr:%08X", OFFSET::g_dwPlayerNameListPtr);
	//s_entityID
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "4C 39 05 ?? ?? ?? ?? 74 0D 8B 51 ?? E8 ?? ?? ?? ?? 48 85 C0");
	OFFSET::s_entityID = *(byte*)(uFindPos + 11);
	DbgPrintA("s_entityID:%08X", OFFSET::s_entityID);

	//s_alivePtr
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "F6 41 ?? 01 74 03 32 C0 C3");
	OFFSET::s_alivePtr = *(byte*)(uFindPos + 2);
	DbgPrintA("s_alivePtr:%08X", OFFSET::s_alivePtr);

	//s_BoneMatrixPtr
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8B 87 ?? ?? ?? ?? 48 8D 14 5B 48 03 D2 48 8D 4F 10");
	OFFSET::s_BoneMatrixPtr = *(uint32_t*)(uFindPos + 3);
	DbgPrintA("s_BoneMatrixPtr:%08X", OFFSET::s_BoneMatrixPtr);

	//s_bulletSpeed
	//uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8B FE 48 8B 05 ?? ?? ?? ?? F3 0F 59 B3 ?? ?? ?? ??");
	//OFFSET::s_bulletSpeed = *(uint32_t*)(uFindPos + 14);
	OFFSET::s_bulletSpeed = 0x1CB8;
	DbgPrintA("s_bulletSpeed:%08X", OFFSET::s_bulletSpeed);

	//s_weaponSpread	
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "F3 0F 5C D1 F3 0F 59 D0 F3 0F 58 D1 F3 0F 58 93");
	OFFSET::s_weaponSpread = *(uint32_t*)(uFindPos + 16);
	DbgPrintA("s_weaponSpread:%08X", OFFSET::s_weaponSpread);

	//s_shakePtr
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "E8 ? ? ? ? F2 0F 10 93 ? ? ? ? 0F 28 D8 ");
	OFFSET::s_shakePtr = *(uint32_t*)(uFindPos + 9);
	DbgPrintA("s_shakePtr:%08X", OFFSET::s_shakePtr);

	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//uDX11Base
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8B 0D ?? ?? ?? ?? 45 33 C0 8B D3 48 8B 01 FF 50 40");

	OFFSET::uDX11Base = uFindPos + *(uint32_t *)(uFindPos + 3) + 7 - global::g_hGameImage;

	if (OFFSET::uDX11Base != 0)
	{
		DbgPrintA("uDX11Base:%llX", OFFSET::uDX11Base);
	}
	//g_pEngineClient: *(CEngineClient**)FindPattern("48 8B 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 48 8B B4 24 ? ? ? ?", 3, 7);
	//如果错了请修正
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D0 FF 93 ? ? ? ? 48 8B ? ? ? ? ? ? ");
	OFFSET::uEngineClient = uFindPos + *(uint32_t *)(uFindPos + 15) + 19 - global::g_hGameImage;
	DbgPrintA("uEngineClient2:%llX", OFFSET::uEngineClient);

	//g_dwWorldToScreenEP
	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "E8 ? ? ? ? 84 c0 0F ? ? ? ? ? 48 8b 0d ? ? ? ? 4c");
	OFFSET::g_dwWorldToScreenEP = (uFindPos + 5) - (/*0x100000000  % */*(uint32_t *)(uFindPos + 1)) - global::g_hGameImage;
	DbgPrintA("g_dwWorldToScreenEP:%llX", OFFSET::g_dwWorldToScreenEP);

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8B 05 ? ? ? ? F3 0F 10 50 ? 74 38");
	OFFSET::uGolbals = (uint64_t)((*(DWORD64*)(uFindPos + 7 + *(DWORD*)(uFindPos + 3))) + 0x4);
	DbgPrintA("uGolbals:%llX", OFFSET::uGolbals);

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "0F 84 92 00 00 00 33 D2 48 8D 0D ?? ?? ?? ?? FF 15") + 15;
	OFFSET::uCreateInterface = uFindPos + *(uint32_t *)(uFindPos + 2) + 6 - global::g_hGameImage;
	DbgPrintA("uCreateInterface:%llX", OFFSET::uCreateInterface);

	//uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8D 05 ?? ?? ?? ?? 33 ED 48 8B F8");
	//OFFSET::g_dwInGamePtr = uFindPos + *(uint32_t *)(uFindPos + 3) + 7 - global::g_hGameImage;
	//DbgPrintA("g_dwInGamePtr:%llX", OFFSET::g_dwInGamePtr);

	//uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 89 5C 24 ?? 55 48 8B EC 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8B D9");
	//OFFSET::CopyPointEP = uFindPos - global::g_hGameImage;
	//DbgPrintA("CopyPointEP:%llX", OFFSET::CopyPointEP);

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 89 5C 24 ?? 55 48 8B EC 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8B D9");
	OFFSET::GetChecksumEP = uFindPos - global::g_hGameImage;
	DbgPrintA("GetChecksumEP:%llX", OFFSET::GetChecksumEP);

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "F2 0F 11 4C 24 ?? E8 ?? ?? ?? ?? 84 C0") - 0x22;
	OFFSET::SilentAimAddr = uFindPos - global::g_hGameImage;
	DbgPrintA("SilentAimAddr:%llX", OFFSET::SilentAimAddr);

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 8D 05 ?? ?? ?? ?? 48 89 05 ?? ?? ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? 48 8B 15 ?? ?? ?? ??");
	OFFSET::g_dwInGamePtr = uFindPos + *(uint32_t *)(uFindPos + 3) + 7 - global::g_hGameImage;
	DbgPrintA("g_dwInGamePtr:%llX", OFFSET::g_dwInGamePtr);


	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "83 F0 01 83 E8 04 23 C1 89 05 ?? ?? ?? ?? 8B 0D ?? ?? ?? ??") + 8;
	OFFSET::g_AutoShotAddr = uFindPos + *(uint32_t *)(uFindPos + 2) + 6 - global::g_hGameImage;
	DbgPrintA("g_AutoShotAddr:%llX", OFFSET::g_AutoShotAddr);

	/*uintptr_t igo64_address = (uintptr_t)GetModuleHandleA(XorString("igo64.dll"));
	uFindPos = (uint64_t)CUtils::PatternScan((void *)igo64_address, "48 8B 05 ? ? ? ? 44 8B C7 8B D6 48 8B CB FF D0 89 84 24 ? ? ? ? EB 07 8B 84 24 ? ? ? ? 85 C0 78 68 89 6C 24 30 48 8B 03 45 33 C0 48 8D 54 24 ? 48 8B CB FF 50 58 8B F8 85 C0 78 0B");
	OFFSET::D3D_igo64 = *(uint32_t*)(uFindPos + 2);
	DbgPrintA("D3D_igo64:%08X", OFFSET::D3D_igo64);*/

	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "0F 2E C8 7A 02 74 26");
	OFFSET::g_GameSpeedHack = (uFindPos + 7) + *(uint32_t *)(uFindPos + 11) + 8 - global::g_hGameImage;
	DbgPrintA("g_GameSpeedHack:%llX", OFFSET::g_GameSpeedHack);


	uFindPos = (uint64_t)CUtils::PatternScan((void *)global::g_hGameImage, "48 89 AC 24 ?? ?? ?? ?? 48 89 BC 24 ?? ?? ?? ?? 40 B7 01");
	OFFSET::g_SendPacket = uFindPos + 0x12 - global::g_hGameImage;
	DbgPrintA("g_SendPacket:%llX", OFFSET::g_SendPacket);
	DWORD dwAddr;
	VirtualProtect((void*)(OFFSET::g_SendPacket + global::g_hGameImage), 0x1, PAGE_EXECUTE_READWRITE, &dwAddr);
	//----------------------------------------------------------------------------------------------------------
	//CopyPoint = (_CopyPoint)(global::g_hGameImage + OFFSET::CopyPointEP);
	//DbgPrintA("CopyPoint:%llX", CopyPoint);
	GetChecksum = (_GetChecksum)(global::g_hGameImage + OFFSET::GetChecksumEP);
	//SEProtectEnd();
}