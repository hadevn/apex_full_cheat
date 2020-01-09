#include "Cheat.h"
#include <string.h>
#include "math\Vector2D.hpp"
#include "D3dDraw.h"
extern BONEIDBYMODEL *GetBoneID(int ModelType);
//CCheats* CheatEngine = GetCheat();
void CMiscellaneous::Bunnyhop()
{
	//SEProtectStartMutation();
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	
	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
		G::UserCmd->buttons |= IN_JUMP;

	}
	else if (G::UserCmd->buttons & IN_JUMP)
	{


		if (G::LocalPlayer->GetFlags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			G::UserCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
	//SEProtectEnd();
}

void CMiscellaneous::AutoStrafe()
{
	if (G::LocalPlayer->GetFlags() & FL_ONGROUND)
		return;
	static bool bFick = false;
	G::UserCmd->sidemove = bFick ? -450.f : 450.f;
	bFick = !bFick;
}
void CRageBot::DropTarget()
{
	if (m_ent)
	{
		if (!m_ent->isAlive() || m_ent->m_bleedoutState())
		{
			m_ent = NULL;
			return;
		}
		float distance = (m_ent->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length() * 0.01905f;	//¾àÀë
		float fov = GetFov(G::LocalPlayer->GetViewAngles(), CalcAngle(G::LocalPlayer->GetEyePosition(), m_ent->GetBonePosition(10)));
		if (fov > Vars.Rage.FOV)
			m_ent = NULL;
		else if (distance > Vars.Rage.MaxDis)
			m_ent = NULL;
		
		if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
		{
			return;
		}
		else if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
		{
			return;
		}
		else if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
		{
			return;
		}else if(Vars.Rage.VisualCheck)
			m_ent = NULL;
	}
	else
	{
		m_ent = NULL;
	}
}
void CRageBot::Rage()
{
	//SEProtectStartMutation();
	
	if (!GetCheat())
		return;
	DropTarget();
//	G::UserCmd->tick_count = G::LocalPlayer->m_lastUCmdSimulationTicks();

	if (!GetCheat()->GetActor()->GetWeaponPtr())
	{
		return;
	}
	if (shoting && Vars.Rage.AutoShot && Vars.RageMode)
		G::UserCmd->buttons &= ~IN_ATTACK;
	if (G::LocalPlayer->IsReloading() || G::LocalPlayer->m_ammoInStockpile() == 0 || G::LocalPlayer->GetbulletSpeed() < 300.f)	//×¢ÊÍ²âÊÔ zheli mei wenti
	{
		return;
	}
	if (!Vars.Rage.Hitboxs[0] && !Vars.Rage.Hitboxs[2] && !Vars.Rage.Hitboxs[1])
		return;
	if (Vars.Rage.EnableAimBotKey && !G::PressedKeys[Vars.Rage.AimBotKey])
	{
		return;
	}
	/*
	if (Vars.Rage.Silent && !Vars.Rage.EnableAimBotKey && !(G::UserCmd->buttons & IN_ATTACK))
	{
		return;
	}*/
	if (Vars.Rage.Legit.EnableLegit)
	{
		if (Vars.Rage.Legit.StopAfterXshot != 0)
		{
			if (G::LocalPlayer->m_shotCount() > Vars.Rage.Legit.StopAfterXshot)
				return;
		}
	}
	if (!m_ent)
	{
		shoting = false;
		bool tmp = true;
		if (Vars.Rage.OneShot && Vars.RageMode)
		{
			if (G::UserCmd->buttons & IN_ATTACK)
				tmp = false;
		}
		if(tmp)
			FindTarget();
	}
	else
		Aimbot();
	//SEProtectEnd();
}



int GetModelType(CBaseEntity* Entity)
{

	char str[80] = { 0 };
	CUtils::ReadData(Entity->ModelNamePtr() + 0x4, str, sizeof(str));

	if (strstr(str, "bloodhound"))		//Ñ°ÑªÁÔÈ®
	{
		return TYPE_MODEL1;
	}
	else if (strstr(str, "gibraltar"))		//Ö±²¼ÂÞÍÓ
	{
		return TYPE_MODEL2;
	}
	else if (strstr(str, "support"))			//ÃüÂö
	{
		return TYPE_MODEL3;
	}
	else if (strstr(str, "pathfinder"))		//Ì½Â·Õß
	{
		return TYPE_MODEL4;
	}
	else if (strstr(str, "stim"))	//¶¯Á¦Ð¡×Ó(´ýÌí¼Ó)
	{
		return TYPE_MODEL5;
	}
	else if (strstr(str, "wraith"))			//¶ñÁé
	{
		return TYPE_MODEL6;
	}
	else if (strstr(str, "bangalore"))		//°à¼ÓÂÞ¶û
	{
		return TYPE_MODEL7;
	}
	else if (strstr(str, "caustic"))			//ÇÖÊ´
	{
		return TYPE_MODEL8;
	}
	else if (strstr(str, "holo"))			//»ÃÏó
	{
		return TYPE_MODEL9;
	}
	else
	{
		return TYPE_MODEL3;
	}
}
void CRageBot::FindTarget()
{
	//SEProtectStartMutation();
	if (!GetCheat())
		return;

	float bestFov = Vars.Rage.FOV;

	float bestDistance = 9999999.0f;
	float AntiAimFov = 180.f;
	int bestHp = 100;
	//ÓÅ»¯Ò»ÏÂFPS

	m_besthitbox = 0;
	/*
	if (m_ent)
	{
		if (!m_ent->isAlive())
		{
			m_ent = NULL;
			return;
		}

		float distance = (m_ent->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length() * 0.01905f;	//¾àÀë
		float fov = GetFov(G::LocalPlayer->GetViewAngles(), CalcAngle(G::LocalPlayer->GetEyePosition(), m_ent->GetBonePosition(10)));
		if (fov > Vars.Rage.FOV)
			m_ent = NULL;
		else if (distance > Vars.Rage.MaxDis)
			m_ent = NULL;
		else if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
		{
			m_besthitbox = 10;
			//m_BestPoint = m_ent->GetBonePosition(10);
			return;
		}
		else if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
		{
			m_besthitbox = 9;
			//m_BestPoint = m_ent->GetBonePosition(9);
			return;
		}
		else if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
		{
			m_besthitbox = 5;
			//m_BestPoint = m_ent->GetBonePosition(5);
			return;
		}
		else
			m_ent = NULL;
	}
	else
	{
		m_ent = NULL;
	}*/
	for (int i = 1; i < I::ClientEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* player = (CBaseEntity*)I::ClientEntList->GetClientEntity(i);

		if (!player)
			continue;

		DWORD64 m_iSignifierName = player->m_iSignifierName();

		if (!m_iSignifierName)
			continue;

		char szName[64] = { 0 };
		CUtils::ReadData(m_iSignifierName, szName, sizeof(szName));

		if (strcmp(szName, "player") == 0)
		{
			if (!player
				|| player == G::LocalPlayer
				|| !player->isAlive()
				|| player->m_iTeamNum() == G::LocalPlayer->m_iTeamNum()
				|| player->m_bleedoutState())
			{
				
				continue;
			}
			Vector eVecTarget = player->GetBonePosition(10);

		//	Vector pVecTarget = G::LocalPlayer->GetEyePosition();
	
			Vector viewAngles = G::LocalPlayer->GetViewAngles();
			Vector ent = player->m_localOrigin();
			Vector loc = G::LocalPlayer->m_localOrigin();

			float distance = ((player->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length()) * 0.01905f;
		
			if (distance > Vars.Rage.MaxDis)
				continue;

			float fov = GetFov(viewAngles, CalcAngle(G::LocalPlayer->GetEyePosition(), eVecTarget));

			int hp = player->m_iHealth();
			if (fov < bestFov)
			{
				AntiAimFov = fov;
				m_BastFovTarget = player;
			}

			if (fov > bestFov)
				continue;
			if (Vars.Rage.TargetMethod == 1 && distance > bestDistance)
				continue;
			if (Vars.Rage.TargetMethod == 2 && hp > bestHp)
				continue;

			bool found = false;
			
			if (Vars.Rage.Hitboxs[0]  && player->IsVisible(10)) //head	//×¢ÊÍ²âÊÔ
			{
				found = true;
				m_BestPoint = player->GetBonePosition(10);
				m_besthitbox = 10;
			}
			else if (Vars.Rage.Hitboxs[1] && player->IsVisible(9)) //Neck
			{
				found = true;
				m_BestPoint = player->GetBonePosition(9);
				m_besthitbox = 9;
			}
			else if (Vars.Rage.Hitboxs[2] && player->IsVisible(5)) //abdomen
			{
				found = true;
				m_BestPoint = player->GetBonePosition(5);
				m_besthitbox = 5;
			}
			else if (!Vars.Rage.VisualCheck)
			{
				found = true;
				m_BestPoint = player->GetBonePosition(10);
				m_besthitbox = 10;
			}
			if (found)
			{
				bestFov = fov;
				bestDistance = distance;
				bestHp = hp;
				m_ent = player;
			}
		}
	}
	//SEProtectEnd();
}
Vector Smooth(Vector pOriginal, Vector angDestination, float fSmoothness)
{
	Vector angSmooth;
	angDestination.Clamp();
	pOriginal.Clamp();
	angSmooth.Init();
	angSmooth.x = angDestination.x - pOriginal.x;
	angSmooth.y = angDestination.y - pOriginal.y;
	angSmooth.Clamp();
	angSmooth.x = pOriginal.x + angSmooth.x / 100 * fSmoothness;
	angSmooth.y = pOriginal.y + angSmooth.y / 100 * fSmoothness;
	angSmooth.Clamp();
	return angSmooth;
}
void CRageBot::Aimbot()
{
	//SEProtectStartMutation();
	if (!m_ent)
		return;
	if (!m_ent->isAlive() || m_ent->m_bleedoutState())
	{
		return;
	}

	if (Vars.Rage.BaimShotGun && G::LocalPlayer->isShotGunWeapon())
	{
		if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
			m_BestPoint = m_ent->GetBonePosition(9);
		else if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
			m_BestPoint = m_ent->GetBonePosition(5);
		else if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
			m_BestPoint = m_ent->GetBonePosition(10);
		else if(!Vars.Rage.VisualCheck)
			m_BestPoint = m_ent->GetBonePosition(10);
		else return;
	}
	else
	{
		if ((Vars.Rage.Legit.EnableLegit && Vars.Rage.Legit.BaimAfterXshot > 0 && G::LocalPlayer->m_shotCount() > Vars.Rage.Legit.BaimAfterXshot) || (Vars.Rage.Legit.EnableLegit && m_ent->m_iHealth() <= Vars.Rage.Legit.BaimLowHP))
		{
			if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
				m_BestPoint = m_ent->GetBonePosition(5);
			else if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
				m_BestPoint = m_ent->GetBonePosition(9);
			else if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
				m_BestPoint = m_ent->GetBonePosition(10);
			else if (!Vars.Rage.VisualCheck)
				m_BestPoint = m_ent->GetBonePosition(10);
			else return;
		}
		else
		{
			if (GetModelType(m_ent) == TYPE_MODEL4)
			{
				if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
					m_BestPoint = m_ent->GetBonePosition(9);
				else if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
					m_BestPoint = m_ent->GetBonePosition(5);
				else if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
					m_BestPoint = m_ent->GetBonePosition(10);
				else if (!Vars.Rage.VisualCheck)
					m_BestPoint = m_ent->GetBonePosition(9);
				else return;
			}
			else
			{
				if (Vars.Rage.Hitboxs[0] && m_ent->IsVisible(10)) //head
					m_BestPoint = m_ent->GetBonePosition(10);
				else if (Vars.Rage.Hitboxs[1] && m_ent->IsVisible(9)) //Neck
					m_BestPoint = m_ent->GetBonePosition(9);
				else if (Vars.Rage.Hitboxs[2] && m_ent->IsVisible(5)) //abdomen
					m_BestPoint = m_ent->GetBonePosition(5);
				else if (!Vars.Rage.VisualCheck)
					m_BestPoint = m_ent->GetBonePosition(10);
				else return;
			}

		}
	}
	float next_shot = G::LocalPlayer->m_nextPrimaryAttackTime() - I::Globals->curtime;
	float distance = (m_ent->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length() * 0.01905f;	//¾àÀë
//	if(Vars.Rage.ExtrapolateTick)
//		m_BestPoint = m_ent->GetPredicted(m_BestPoint);
	if (Vars.Rage.Predict)
		m_BestPoint += m_ent->GetPredict(m_ent->GetDis(), G::LocalPlayer->GetbulletSpeed());
	Vector aim_angle = CalcAngle(G::LocalPlayer->GetEyePosition(), m_BestPoint);
	aim_angle -= G::LocalPlayer->GetPunch() * 1.f;
	Vector src = G::LocalPlayer->GetViewAngles();
	if(Vars.Rage.Legit.Soomth != 0)
		aim_angle = Smooth(src, aim_angle, Vars.Rage.Legit.Soomth);
	//G::UserCmd->tick_count = m_ent->m_lastUCmdSimulationTicks();
	if (Vars.Misc.NoSway/* && G::LocalPlayer->isSniper()*/ && distance > 50.f)
	{
		Vector Dynamic = G::LocalPlayer->GetDynamic();
		Vector TempViewAngles = G::LocalPlayer->GetViewAngles();
		Vector Breath = Dynamic - TempViewAngles;
		static Vector LastBreath = { 0.f,0.f,0.f };
		if (LastBreath != Breath)
		{
			aim_angle = (aim_angle + LastBreath) - Breath;
			LastBreath = Breath;
		}
	}

	aim_angle.Clamp();
	
	if (Vars.Rage.Silent && Vars.RageMode)
	{
		G::UserCmd->viewangles = QAngle(aim_angle.x, aim_angle.y, aim_angle.z);
	}
	else
	{
		G::LocalPlayer->SetViewAngles(aim_angle);
	}
	if (next_shot > 0.f)
	{
		aimboting = false;
		if (G::LocalPlayer->isSingleShotWeapon() && Vars.Rage.AutoShot && Vars.RageMode)
			G::UserCmd->buttons &= ~IN_ATTACK;
	}
	if (Vars.RageMode && Vars.Rage.AutoShot)
	{
		if (!G::LocalPlayer->isSingleShotWeapon())
		{
			aimboting = true;
			G::SendPacket = true;
			if (Vars.Rage.AutoShot && distance < Vars.Rage.MaxAutoShotDis)
			{
				G::UserCmd->buttons |= IN_ATTACK;
				shoting = true;
			}
		}
		else
		{
			if (next_shot <= 0.f)
			{
				aimboting = true;
				G::SendPacket = true;
				if (Vars.Rage.AutoShot && distance < Vars.Rage.MaxAutoShotDis)
				{
					G::UserCmd->buttons |= IN_ATTACK;
					shoting = true;
				}
			}
		}
	}
	else
	{
		aimboting = true;
	//	G::SendPacket = true;
	}

		
	/*
	
	if (next_shot <= 0.f)
	{
		aimboting = true;
		G::SendPacket = true;
		if (Vars.Rage.AutoShot && distance < Vars.Rage.MaxAutoShotDis)
		{
			//G::UserCmd->buttons |= IN_ATTACK;
			G::LocalPlayer->StartShot(true);
			shoting = true;
		}
	}
	else
	{
		aimboting = false;
		if (G::LocalPlayer->isSingleShotWeapon())
			G::UserCmd->buttons &= ~IN_ATTACK;
	}*/
	//SEProtectEnd();
}

void CRageBot::AntiAim()
{
	//SEProtectStartMutation();
	if (G::LocalPlayer->GetbulletSpeed() < 300
		|| (G::UserCmd->buttons & IN_USE) || G::PressedKeys[KEY_E] || (G::UserCmd->buttons & IN_ATTACK) || G::PressedKeys[MOUSE_LEFT]
		|| !(G::LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		//goAntiAim = false;
		//G::SendPacket = true;
		return;
	}
	//if (G::LocalPlayer->GetWeaponID() == 7)
	//	return;
	QAngle temp = G::UserCmd->viewangles;
	if (Vars.Rage.AntiAim.AtPlayer)
	{
		if (m_BastFovTarget)
		{
			if(m_BastFovTarget->isAlive())
				temp.yaw = CalcAngle(G::LocalPlayer->GetEyePosition(), m_BastFovTarget->GetEyePosition()).y;
		}
	}

	/*
	switch (Vars.Rage.AntiAim.Pitch)
	{
	case AA_Pitch_DOWN:
		G::UserCmd->viewangles.pitch = 89.f;
		break;
	case AA_Pitch_Zero:
		G::UserCmd->viewangles.pitch = 0.f;
		break;
	case AA_Pitch_UP:
		G::UserCmd->viewangles.pitch = -89.f;
		break;
	case AA_Pitch_Mix:
		G::UserCmd->viewangles.pitch = CUtils::RandomFloat(-89.f,89.f);
		break;
	default:
		G::UserCmd->viewangles.pitch = 89.f;
		break;
	}*/

	int yaw = Vars.Rage.AntiAim.Yaw;
	if (yaw != AA_YAW_LispFake)
	{
		switch (yaw)
		{
		case AA_Yaw_Backward:
			temp.yaw -= 180.f;
			break;
		case AA_Yaw_FastSpin:
			temp.yaw = (I::Globals->curtime * 9000.0);
			break;
		case AA_Yaw_SlowSpin:
			temp.yaw = (float)(fmod(I::Globals->curtime / 1.5f * 360.0f, 360.0f));
			break;
		case AA_Yaw_Jitter:
		{
			if (!Vars.Rage.AntiAim.AtPlayer)
				temp.yaw = (G::UserCmd->command_number % 2) ? 270.0f : 90.0f;
			else
				temp.yaw -= (G::UserCmd->command_number % 2) ? 270.0f : 90.0f;

		}break;
		case AA_Yaw_MixJitter:
		{
			if (!Vars.Rage.AntiAim.AtPlayer)
				temp.yaw = CUtils::RandomFloat(-90.f, 90.f);
			else
				temp.yaw -= CUtils::RandomFloat(-90.f, 90.f);
		}break;
		case AA_Yaw_Rand:
			temp.yaw = CUtils::RandomFloat(-180.f, 180.f);
			break;
		case AA_Yaw_SideWayL:
			temp.yaw -= 90.f;
			break;
		case AA_Yaw_SideWayR:
			temp.yaw += 90.f;
			break;
		}
	}
	else
	{
		if (G::UserCmd->command_number % 2)
			temp.yaw += 323210000.f;
		else
			temp.yaw -= 323210000.f;
	}
	G::UserCmd->viewangles.yaw = temp.yaw;
	if (yaw != AA_YAW_LispFake)
		G::UserCmd->viewangles.Clamp();
	if (Vars.Rage.AntiAim.Pitch == AA_Pitch_Lisp)
		G::UserCmd->viewangles.pitch = 1080.f;
	else
		G::UserCmd->viewangles.pitch = 89.f;
	//SEProtectEnd();
}