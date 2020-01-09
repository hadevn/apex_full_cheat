#include "Common.h"
#include "ActorMgr.h"
#include "utils\StringCovert.h"
#include "SDK.h"


CActorMgr::CActorMgr()
{
}


CActorMgr::~CActorMgr()
{
}
//	»ñÈ¡¹Ç÷À×ø±ê
/*
void CActorMgr::GetBone(DWORD64 dwEntry, Vector &EntityPos, Vector *pOutBoneArry)
{
FLOAT matrix[128][3][4];
uintptr_t pBoneMatrix = CUtils::Read<DWORD64>(dwEntry + OFFSET::s_BoneMatrixPtr);
if (pBoneMatrix)
{
CUtils::ReadData(pBoneMatrix, (char*)&matrix, sizeof(matrix));
}

for (int id = 0; id < 128; id++)
{
Vector bone_pos = Vector(matrix[id][0][3], matrix[id][1][3], matrix[id][2][3]) + EntityPos;
pOutBoneArry[id] = bone_pos;
}
}*/
int CActorMgr::GetItemTpye(int id)
{
	if (id >= 0 && id <=38)
		return ITEM_WEAPONS;
	if (id >= 39 && id <= 42)
		return ITEM_AMMO;
	if (id >= 43 && id <= 48)
		return ITEM_HEALING;

	if (id >= 49 && id <= 64)
		return ITEM_SHIELD;
	if (id >= 65 && id <= 67)
		return ITEM_GRENADES;
	if (id >= 68 && id <= 77)
		return ITEM_SCOPES;
	if (id >= 78 && id <= 103)
		return ITEM_ATTACHMENTS;

	return 0;
}



void CActorMgr::Update()
{
	//SEProtectStartMutation();

	m_List.clear();
	bool found = false;
	for (int x = 1; x < I::ClientEntList->GetHighestEntityIndex(); x++)
	{
		CBaseEntity* Entity = (CBaseEntity*)I::ClientEntList->GetClientEntity(x);
		if (!Entity)
			continue;
		DWORD64 m_iSignifierName = Entity->m_iSignifierName();

		if (!m_iSignifierName)
			continue;

		char szName[64] = { 0 };
		CUtils::ReadData(m_iSignifierName, szName, sizeof(szName));

		ACTOR_INFO AI;
		AI.dwPtr = (DWORD64)Entity;
		if (strcmp(szName, "player") == 0)	// Crashes
		{
			AI.type = TYPE_PLAYER;
			AI.isAlive = Entity->isAlive();
			AI.id = Entity->m_id();	//ID
			AI.health = Entity->m_iHealth();
			AI.maxhealth = Entity->m_iMaxHealth();
			AI.shieldhealth = Entity->m_shieldHealth();
			AI.shieldhealthmax = Entity->m_shieldHealthMax();
			AI.teamid = Entity->m_iTeamNum();
			AI.name = Entity->GetPlayerName();
			AI.orgin = Entity->m_localOrigin();
			AI.head = Entity->GetHeadPos();
			if (G::LocalPlayer)
			{
				if (AI.teamid != G::LocalPlayer->m_iTeamNum())
				{
					float distance = ((Entity->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length()) * 0.01905f;
					if (distance <= Vars.Rage.AntiAim.MinDis)
						found = true;
				}

			}
			char szModelName[80] = { 0 };
			CUtils::ReadData(Entity->ModelNamePtr() + 0x4, szModelName, sizeof(szModelName));

			if (strstr(szModelName, "bloodhound"))		//Ñ°ÑªÁÔÈ®
			{
				AI.modeltype = TYPE_MODEL1;
			}
			else if (strstr(szModelName, "gibraltar"))		//Ö±²¼ÂÞÍÓ
			{
				AI.modeltype = TYPE_MODEL2;
			}
			else if (strstr(szModelName, "support"))			//ÃüÂö
			{
				AI.modeltype = TYPE_MODEL3;
			}
			else if (strstr(szModelName, "pathfinder"))		//Ì½Â·Õß
			{
				AI.modeltype = TYPE_MODEL4;
			}
			else if (strstr(szModelName, "donglixiaozi"))	//¶¯Á¦Ð¡×Ó(´ýÌí¼Ó)
			{
				AI.modeltype = TYPE_MODEL5;
			}
			else if (strstr(szModelName, "wraith"))			//¶ñÁé
			{
				AI.modeltype = TYPE_MODEL6;
			}
			else if (strstr(szModelName, "bangalore"))		//°à¼ÓÂÞ¶û
			{
				AI.modeltype = TYPE_MODEL7;
			}
			else if (strstr(szModelName, "caustic"))			//ÇÖÊ´
			{
				AI.modeltype = TYPE_MODEL8;
			}
			else if (strstr(szModelName, "holo"))			//»ÃÏó
			{
				AI.modeltype = TYPE_MODEL9;
			}
			else
			{
				AI.modeltype = TYPE_MODEL2;
			}
			m_List.Push(AI);
		}

		else if (strcmp(szName, "prop_survival") == 0)
		{
			AI.type = TYPE_ITEM;
			AI.id = Entity->ITEM_ID();
			AI.nameid = Entity->ITEM_NameID();
			AI.orgin = Entity->m_localOrigin();
			AI.itemtpye = GetItemTpye(Entity->ITEM_NameID());
			m_List.Push(AI);
		}

		else if (strcmp(szName, "prop_script") == 0)	// NPC
		{
			AI.type = 000;

			//AI.isAlive = Entity->isAlive();
			AI.id = Entity->m_id();	//ID

			Vector ent = Entity->m_localOrigin();
			Vector loc = G::LocalPlayer->m_localOrigin();
			float distance = ((Entity->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length()) * 0.01905f;
			//DbgPrintA("a7");

			/*
			if (distance < 20)
			{
				//DbgPrintA("ACTOR:index:%d dis:%f coord:%f,%f,%f->%f,%f,%f", x, distance, loc.x, loc.y, loc.z, ent.x, ent.y, ent.z);
			}
		*/

			AI.health = Entity->m_iHealth();
			AI.maxhealth = Entity->m_iMaxHealth();
			AI.shieldhealth = Entity->m_shieldHealth();
			AI.shieldhealthmax = Entity->m_shieldHealthMax();
			AI.teamid = Entity->m_iTeamNum();
			AI.name = "NPCaaaa";
			AI.orgin = Entity->m_localOrigin();
			AI.head = Entity->GetHeadPos();

			char szModelName[80] = { 0 };
			CUtils::ReadData(Entity->ModelNamePtr() + 0x4, szModelName, sizeof(szModelName));

			if (strstr(szModelName, "bloodhound"))		//Ñ°ÑªÁÔÈ®
			{
				AI.modeltype = TYPE_MODEL1;
			}
			else if (strstr(szModelName, "gibraltar"))		//Ö±²¼ÂÞÍÓ
			{
				AI.modeltype = TYPE_MODEL2;
			}
			else if (strstr(szModelName, "support"))			//ÃüÂö
			{
				AI.modeltype = TYPE_MODEL3;
			}
			else if (strstr(szModelName, "pathfinder"))		//Ì½Â·Õß
			{
				AI.modeltype = TYPE_MODEL4;
			}
			else if (strstr(szModelName, "donglixiaozi"))	//¶¯Á¦Ð¡×Ó(´ýÌí¼Ó)
			{
				AI.modeltype = TYPE_MODEL5;
			}
			else if (strstr(szModelName, "wraith"))			//¶ñÁé
			{
				AI.modeltype = TYPE_MODEL6;
			}
			else if (strstr(szModelName, "bangalore"))		//°à¼ÓÂÞ¶û
			{
				AI.modeltype = TYPE_MODEL7;
			}
			else if (strstr(szModelName, "caustic"))			//ÇÖÊ´
			{
				AI.modeltype = TYPE_MODEL8;
			}
			else if (strstr(szModelName, "holo"))			//»ÃÏó
			{
				AI.modeltype = TYPE_MODEL9;
			}
			else
			{
				AI.modeltype = TYPE_MODEL9;
			}

			m_List.Push(AI);
		}
		else if ((strcmp(szName, "prop_dynamic") == 0))//prop_dynamic
		{
			float distance = ((Entity->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length()) * 0.01905f;

			//if (distance < 20 && distance != 0 )
			{
				AI.type = 00;

				AI.isAlive = 1;
				AI.id = Entity->m_id();	//ID

				AI.health = 100;
				AI.maxhealth = 100;
				AI.shieldhealth = 100;
				AI.shieldhealthmax = 100;
				AI.teamid = 0;
				AI.name = "°Ð×Ó";
				AI.orgin = Entity->m_localOrigin();
				AI.head = Entity->GetHeadPos();
				m_List.Push(AI);
			}
		}

	}
	E::RageBot->goAntiAim = found;
	//SEProtectEnd();

}

ACTOR_INFO * CActorMgr::GetLocalPlayer()
{
	DWORD64 LocalPtr = (DWORD64)I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayerID());
	for (int i = 0; i < m_List.GetCount(); i++)
	{
		ACTOR_INFO *pAI = m_List.GetData(i);
		if (pAI != NULL && pAI->dwPtr == LocalPtr)
			return pAI;
	}
	return NULL;
}

DWORD64 CActorMgr::GetWeaponPtr()
{
	int weapid = CUtils::Read<DWORD>((DWORD64)G::LocalPlayer + OFFSET::m_latestPrimaryWeapons) & 0xFFFF;
	if (weapid != 0)
	{
		return (DWORD64)I::ClientEntList->GetClientEntity(weapid);
	}
	return 0;
}

