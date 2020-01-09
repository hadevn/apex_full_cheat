#pragma warning(default:4996)
#include "hooks.h"
#include "globals.h"
#include "Common.h"
#include "Color.h"
#include <math.h>
#include "Cheat.h"
#include "D3dDraw.h"

ID3D11DeviceContext * g_pContext = NULL;
ID3D11RenderTargetView* g_pRenderTargetView = NULL;
CCheats *g_pCheat;
vector<DRAWSTRING> g_DrawString;
WNDPROC oWndProc = nullptr;
_PeekMessageW Old_PeekMessageW;
_CreateMove OLD_CreateMove; 
_GetChecksum GetChecksum;
//_CopyPoint CopyPoint;
extern void InstallCreatMoveHook();
void FakeLag()
{
	static int choked = 0;
	int choke = std::min<int>(Vars.Misc.AdaptiveFakeLag ? static_cast<int>(std::ceilf(64 / (G::LocalPlayer->GetvecAbsVelocity().Length() * I::Globals->interval_per_tick))) : Vars.Misc.FakeLag, 14);
	if ((G::UserCmd->buttons & IN_ATTACK) || G::LocalPlayer->GetvecAbsVelocity().Length() < 50.0f || (G::UserCmd->buttons & IN_USE) || Vars.Misc.EnableSpeedHack)
	{
		G::SendPacket = true;
		choked = 0;
	}
	else
	{
		G::SendPacket = (choked > choke);
		if (G::SendPacket)
			choked = 0;
		else
			choked++;
	}
	//DbgPrintA("G::SendPacket : %d choked: %d", G::SendPacket, choked);
}
void doSpeedHack()
{
	if (Vars.Misc.SpeedHackKey == 0)
		*(float*)(global::g_hGameImage + OFFSET::g_GameSpeedHack) = Vars.Misc.Speed;
	else
		if (G::PressedKeys[Vars.Misc.SpeedHackKey])
			*(float*)(global::g_hGameImage + OFFSET::g_GameSpeedHack) = Vars.Misc.Speed;
		else
			*(float*)(global::g_hGameImage + OFFSET::g_GameSpeedHack) = 1.f;
}
void updateSendPack()
{
	DWORD64 SendPacket = (global::g_hGameImage + OFFSET::g_SendPacket);
	if (!IsBadReadPtr((void*)SendPacket, sizeof(SendPacket)))
		*(bool*)SendPacket = G::SendPacket;
}
void doNoSpread()
{
	if (Vars.Misc.NoSpread)
	{
		DWORD64 weapon = G::LocalPlayer->GetWeapon();
		if (weapon)
		{
			*(float*)(weapon + 0x1370) = -1.f;
			*(float*)(weapon + 0x1380) = -1.f;
		}
	}
}
void AutoDuck()
{
	if (!Vars.Misc.AutoDuck || G::LocalPlayer->GetvecAbsVelocity().Length() > 50.f || (G::UserCmd->buttons & IN_USE))
		return;
	static bool counter = false;
	static int counte = 0;
	if (counte >= Vars.Misc.AutoDuckLimit) {
		counte = 0;
		counter = !counter;
	}
	counte++;
	//G::UserCmd->buttons |= IN_BULLRUSH;
	if (counter) {
		G::UserCmd->buttons |= IN_DUCK;
		if (Vars.Misc.FakeDuck)
			G::SendPacket = true;
	}
	else {
		G::UserCmd->buttons &= ~IN_DUCK;
		if (Vars.Misc.FakeDuck)
			G::SendPacket = false;
	}
}
void SpeedHack()
{
	static int ticks = 0;
	DWORD64 SpeedHackDw = (global::g_hGameImage + OFFSET::g_GameSpeedHack);
	if (!IsBadReadPtr((void*)SpeedHackDw, sizeof(SpeedHackDw)))
	{
		if (Vars.Misc.EnableSpeedHack)
		{
			if (!Vars.Misc.FakeLagSpeedHack)
			{
				doSpeedHack();
			}
			else
			{
				Vars.Misc.FakeLag = 0;
				if (Vars.Misc.SpeedHackKey == 0 || G::PressedKeys[Vars.Misc.SpeedHackKey])
				{
					ticks++;
					int tmp = 15;
					if (!Vars.RageMode)
						tmp = 10;
					if (ticks <= tmp)
						G::SendPacket = false;
					else
					{
						G::SendPacket = true;
						ticks = 0;
					}
				}
				if (!G::SendPacket)
				{
					doSpeedHack();
				}
				else
					*(float*)SpeedHackDw = 1.f;
			}

		}
		else
			*(float*)SpeedHackDw = 1.f;
	}
}
__int64 __fastcall Hooks::MyCreateMove(CInput * pInput, int sequence_number, float input_sample_frametime, bool active)
{
	updateSendPack();
	__int64 Result =  OLD_CreateMove(pInput, sequence_number, input_sample_frametime,active);
	G::LocalPlayer = (CBaseEntity*)I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayerID());
	if (!I::Engine->IsInGame() || !GetCheat())
	{
		G::SendPacket = true;
		return Result;
	}
	CUserCmd* pCMD = reinterpret_cast<CUserCmd*>(*(reinterpret_cast<std::uintptr_t*>(pInput) + 31) + 0x280 * (sequence_number % 750));
	if (!pCMD || pCMD->command_number == NULL)
		return Result;
	G::UserCmd = pCMD;
	if (!G::LocalPlayer || !G::LocalPlayer->isAlive())
	{
		G::SendPacket = true;
		return Result;
	}
	if (Vars.Misc.Bhop)
		E::Misc->Bunnyhop();
//	E::Misc->AutoStrafe();
	if (Vars.Rage.Enabled)
	{
		if (Vars.Rage.EnabledAimbot)
			E::RageBot->Rage();
		if (Vars.Rage.AntiAim.Enable)
		{
			CFixMove fixMove;
			fixMove.Start();
			E::RageBot->AntiAim();
			fixMove.End();
		}	
	}
	if (Vars.Misc.FakeLag != 0)
		FakeLag();
	else if (!Vars.Rage.AntiAim.Enable)
		G::SendPacket = true;
	if (Vars.Misc.AutoPistol)
	{
		if (G::LocalPlayer->isSingleShotWeapon())
		{
			if (G::UserCmd->buttons & IN_ATTACK)
			{
				static bool bFlip = false;
				if (bFlip)
					G::UserCmd->buttons &= ~IN_ATTACK;
				bFlip = !bFlip;
			}
		}
	}
	doNoSpread();
	SpeedHack();
	AutoDuck();
	if (!(Vars.Rage.AntiAim.Enable && (Vars.Rage.AntiAim.Pitch == AA_Pitch_Lisp || Vars.Rage.AntiAim.Yaw == AA_YAW_LispFake)))
		G::UserCmd->viewangles.Clamp();
	if (G::UserCmd->forwardmove > 1.f)
		G::UserCmd->forwardmove = 1.f;
	else if (G::UserCmd->forwardmove < -1.f)
		G::UserCmd->forwardmove = -1.f;
	if (G::UserCmd->sidemove > 1.f)
		G::UserCmd->sidemove = 1.f;
	else if (G::UserCmd->sidemove < -1.f)
		G::UserCmd->sidemove = -1.f;
	if (G::UserCmd->upmove > 1.f)
		G::UserCmd->upmove = 1.f;
	else if (G::UserCmd->upmove < -1.f)
		G::UserCmd->upmove = -1.f;
	
	return GetChecksum((DWORD64*)pCMD);
	//SEProtectEnd();
}




void CFixMove::Start()
{
	m_oldangle = G::UserCmd->viewangles;
	m_oldforward = G::UserCmd->forwardmove;
	m_oldsidemove = G::UserCmd->sidemove;
}

void CFixMove::End()
{
	float yaw_delta = G::UserCmd->viewangles.yaw - m_oldangle.yaw;
	float f1;
	float f2;

	if (m_oldangle.yaw < 0.f)
		f1 = 360.0f + m_oldangle.yaw;
	else
		f1 = m_oldangle.yaw;

	if (G::UserCmd->viewangles.yaw < 0.0f)
		f2 = 360.0f + G::UserCmd->viewangles.yaw;
	else
		f2 = G::UserCmd->viewangles.yaw;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);
	yaw_delta = 360.0f - yaw_delta;

	G::UserCmd->forwardmove = cos(DEG2RAD(yaw_delta)) * m_oldforward + cos(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
	G::UserCmd->sidemove = sin(DEG2RAD(yaw_delta)) * m_oldforward + sin(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
}
void InitMyMenu()
{
	//SEProtectStartMutation();
	ImGuiStyle * style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	//style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f); 
	//SEProtectEnd();
}
void RagebotTab()
{
	//SEProtectStartMutation();
	ImGui::Checkbox(XorString("Enable Rage"), &Vars.Rage.Enabled);
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("RAGE1", ImVec2(0, 0), true);
		{

			ImGui::Checkbox(XorString("Enable Aim"), &Vars.Rage.EnabledAimbot);
			ImGui::Separator();
			ImGui::Checkbox(XorString("AimKey"), &Vars.Rage.EnableAimBotKey);
			ImGui::Combo(XorString("Key"), &Vars.Rage.AimBotKey, keyNames, ARRAYSIZE(keyNames));
			ImGui::SliderFloat(XorString("Fov"), &Vars.Rage.FOV, 1.f, 360.f, "%.0f");
			if (Vars.RageMode)
				ImGui::Checkbox(XorString("Auto Shot"), &Vars.Rage.AutoShot);
			ImGui::Checkbox(XorString("Visual Check"), &Vars.Rage.VisualCheck);
			ImGui::SliderInt(XorString("Soomth"), &Vars.Rage.Legit.Soomth, 0, 100);
			if(Vars.RageMode)
				ImGui::Checkbox(XorString("Silent Aim"), &Vars.Rage.Silent);
	//		ImGui::Checkbox(XorString("Extrapolate Tick"), &Vars.Rage.ExtrapolateTick);
			ImGui::Checkbox(XorString("Player Predict"), &Vars.Rage.Predict);//
			ImGui::Checkbox(XorString("One Shot"), &Vars.Rage.OneShot);
			ImGui::Checkbox(XorString("Baim Shotgun"), &Vars.Rage.BaimShotGun);
			ImGui::Checkbox(XorString("NoSway"), &Vars.Misc.NoSway);
			ImGui::SliderFloat(XorString("Max Aim Distance"), &Vars.Rage.MaxDis, 0.1f, 500.f, "%.1f");
			ImGui::SliderFloat(XorString("Max AutoShot Distance"), &Vars.Rage.MaxAutoShotDis, 10.f, 500.f, "%.1f");
			ImGui::Separator();
			ImGui::Text(XorString("Target"));
			ImGui::Separator();
			ImGui::Combo(XorString("Scan Method"), &Vars.Rage.TargetMethod, targetMode, ARRAYSIZE(targetMode));
			ImGui::Text(XorString("HitBox"));
			ImGui::Separator();
			ImGui::Checkbox(XorString("Head"), &Vars.Rage.Hitboxs[0]);
			ImGui::Checkbox(XorString("Neck"), &Vars.Rage.Hitboxs[1]);
			ImGui::Checkbox(XorString("Abdomen"), &Vars.Rage.Hitboxs[2]);
			ImGui::Separator();
			ImGui::EndChild();
		}

	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild(XorString("RAGE2"), ImVec2(0, 0), true);
		{
			ImGui::Text(XorString("Legit Aim"));
			ImGui::Separator();
			ImGui::Checkbox(XorString("Enable Legit"), &Vars.Rage.Legit.EnableLegit);
			ImGui::SliderInt(XorString("Baim X Shot"), &Vars.Rage.Legit.BaimAfterXshot, 0, 25);
			ImGui::SliderInt(XorString("Baim Low HP"), &Vars.Rage.Legit.BaimLowHP, 0, 100);
			ImGui::SliderInt(XorString("Stop Aim X Shot"), &Vars.Rage.Legit.StopAfterXshot, 0, 25);
			ImGui::Separator();
			if (Vars.RageMode)
			{
				ImGui::Checkbox(XorString("Enable AntiAim"), &Vars.Rage.AntiAim.Enable);
				ImGui::Separator();
				ImGui::Combo(XorString("Pitch"), &Vars.Rage.AntiAim.Pitch, AntiAim_X, ARRAYSIZE(AntiAim_X));
				ImGui::Combo(XorString("Real Yaw"), &Vars.Rage.AntiAim.Yaw, AntiAim_Y, ARRAYSIZE(AntiAim_Y));
				ImGui::Checkbox(XorString("Aways At Player"), &Vars.Rage.AntiAim.AtPlayer);
				ImGui::Separator();
			}else
			{
				ImGui::Text(XorString("Here is AntiAim"));
				ImGui::Text(XorString("But you are LegitMode"));
				ImGui::Text(XorString("So if you want use antiaim,just press 'Enable RageMode' in Misc"));
			}
			ImGui::EndChild();
		}
	}
	//SEProtectEnd();
}
void VisualTab()
{
	//SEProtectStartMutation();

	ImGui::Checkbox(XorString("Enable Visual"), &Vars.Visuals.Enabled);
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("ESP1", ImVec2(0, 0), true);
		{
			ImGui::Checkbox(XorString("Player Esp"), &Vars.Visuals.PlayerEnable);
			ImGui::Separator();
			ImGui::Columns(2, "##c1", false);
			ImGui::Checkbox(XorString("Name"), &Vars.Visuals.Name);
			ImGui::Checkbox(XorString("Box"), &Vars.Visuals.Box);
			ImGui::Checkbox(XorString("Skeleton"), &Vars.Visuals.Skeleton);
			ImGui::Checkbox(XorString("Health"), &Vars.Visuals.Health);
		
			ImGui::NextColumn();
			ImGui::Checkbox(XorString("Distance"), &Vars.Visuals.Distance);
			ImGui::Checkbox(XorString("Glow"), &Vars.Visuals.Glow);
			ImGui::Checkbox(XorString("Weapon"), &Vars.Visuals.Weapon);
			ImGui::Checkbox(XorString("Shield"), &Vars.Visuals.Shield);

			ImGui::Separator();
			ImGui::Columns(1);
			ImGui::SliderFloat(XorString("MaxDis"), &Vars.Visuals.MaxPlayerDis, 10.f, 1500.f);
			ImGui::Checkbox(XorString("AimSpot"), &Vars.Visuals.AimSpot); //崩溃
			ImGui::SliderFloat(XorString("MaxSpot"), &Vars.Visuals.MaxSpot, 10.f, 6000.f);
			//ImGui::Checkbox(XorString("Aim Warning"), &Vars.Visuals.AimWarning);
			//ImGui::Checkbox(XorString("Draw Fov"), &Vars.Visuals.DrawFov);
			//ImGui::Checkbox(XorString("Circular"), &Vars.Visuals.Circular);
			ImGui::EndChild();
		}

	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("ESP2", ImVec2(0, 0), true);
		{
			ImGui::Checkbox(XorString("Item Esp"), &Vars.Visuals.ItemEnable);
			ImGui::Separator();
			
			ImGui::Columns(2, "##c1", false);
			ImGui::Checkbox("Weapons", &Vars.Visuals.ItemWeapons);
			ImGui::Checkbox("Ammo", &Vars.Visuals.ItemAmmo);
			ImGui::Checkbox("Healing", &Vars.Visuals.ItemHealing);
			ImGui::Checkbox("Shield", &Vars.Visuals.ItemShield);
			ImGui::NextColumn();
			ImGui::Checkbox("Grenades", &Vars.Visuals.ItemGrenades);
			ImGui::Checkbox("Scopes", &Vars.Visuals.ItemScopes);
			ImGui::Checkbox("Attachments", &Vars.Visuals.ItemAttachments);
			ImGui::NextColumn();	
			ImGui::Columns(1);
			ImGui::SliderFloat("MaxDis", &Vars.Visuals.MaxItemDis, 10.f, 1500.f);
			ImGui::Separator();
			ImGui::Checkbox(XorString("Enable Radar"), &Vars.Visuals.Radar.Enable);
			ImGui::SliderFloat(XorString("MaxDistance"), &Vars.Visuals.Radar.MaxDis, 10.f, 2000.f, "%.1f");//最大玩家距离
			ImGui::Checkbox(XorString("Enemy Only"), &Vars.Visuals.Radar.EnemyOnly);
			ImGui::Checkbox(XorString("Visible Only"), &Vars.Visuals.Radar.VisibleOnly);
			ImGui::Checkbox(XorString("View Check"), &Vars.Visuals.Radar.ViewCheck);
			ImGui::Text("Alpha"); ImGui::SameLine();
			ImGui::SliderInt("Alpha##0", &Vars.Visuals.Radar.Alpha, 0, 255);
			ImGui::Text("Zoom"); ImGui::SameLine();
			ImGui::SliderFloat("Zoom##0", &Vars.Visuals.Radar.Zoom, 0.f, 10.f);
			ImGui::Text("Type");
			ImGui::Combo("##1", &Vars.Visuals.Radar.Type, "Box\0Filled box\0Circle\0Circle filled\0\0", -1);
			if (ImGui::Button(XorString("ResetRadar"), ImVec2(120, 0))) Vars.Visuals.Radar.NextResetRadar = true;
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	//SEProtectEnd();

}

void MiscHackTab()
{

	//SEProtectStartMutation();
	ImGui::Text(XorString("Misc"));
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("MISC", ImVec2(0, 0), true);
		{
			ImGui::Text(XorString("MoveMent"));
			ImGui::Separator();
			//这边做加速什么的
			if (Vars.RageMode)
				ImGui::Checkbox(XorString("Bhop"), &Vars.Misc.Bhop),
				ImGui::Checkbox(XorString("AutoDuck"), &Vars.Misc.AutoDuck),
				ImGui::SliderInt(XorString("AutoDuck Limit"), &Vars.Misc.AutoDuckLimit, 1, 14),
				ImGui::Checkbox(XorString("Fake Duck"), &Vars.Misc.FakeDuck);
			ImGui::Checkbox(XorString("SpeedHack"), &Vars.Misc.EnableSpeedHack);
			ImGui::Combo(XorString("SpeedHack Key"), &Vars.Misc.SpeedHackKey, keyNames, ARRAYSIZE(keyNames));
			ImGui::SliderFloat(XorString("Speed"), &Vars.Misc.Speed, 1.f, 3.f, "%.1f");
			if (Vars.RageMode)
				ImGui::Checkbox(XorString("FakeLag SpeedHack"), &Vars.Misc.FakeLagSpeedHack);
			ImGui::Separator();
			ImGui::EndChild();
		}

	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("MISC2", ImVec2(0, 0), true);
		{
			ImGui::Text(XorString("Other"));
			ImGui::Separator();
			if (Vars.RageMode)
				ImGui::Checkbox(XorString("Auto-Pistol"), &Vars.Misc.AutoPistol);
			ImGui::Checkbox(XorString("NoSpread"), &Vars.Misc.NoSpread);
			if (Vars.RageMode)
			{
				ImGui::SliderInt(XorString("FakeLag"), &Vars.Misc.FakeLag, 0, 14);
				ImGui::Checkbox(XorString("FakeLag Adaptive"), &Vars.Misc.AdaptiveFakeLag);
			}


			if (!Vars.RageMode)
			{
				ImGui::Text(XorString("LETS HAVE FUN"));
				if (ImGui::Button(XorString("[!!!]Enable RageMode")))
				{
					InstallCreatMoveHook();
					Vars.RageMode = true;
				}

			}
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	//SEProtectEnd();
}
void MainWindows()
{
	//SEProtectStartMutation();
	//ImGui::GetIO().MouseDrawCursor = Vars.Menu.Opened;
	ImGui::GetIO().MouseDrawCursor = false;
	static int page = 0;
	if (Vars.Menu.Opened)
	{
		static int page = 0;
		ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin(XorString("RooKie AA3Cheatz For Apex 2019"), &Vars.Menu.Opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		{
			const char* tabs[] = {
				"Aim",
				"Visual",
				"Misc"
			};
			int tabs_size = sizeof(tabs) / sizeof(tabs[0]);

			for (int i = 0; i < tabs_size; i++)
			{
				ImVec2 windowSize = ImGui::GetWindowSize();
				int width = windowSize.x / tabs_size - 9;

				int distance;
				if (i == page)
					distance = 0;
				else
					distance = i > page ? i - page : page - i;
				/*
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					mainColor.Value.x - (distance * 0.035f),
					mainColor.Value.y - (distance * 0.035f),
					mainColor.Value.z - (distance * 0.035f),
					mainColor.Value.w
				);
				ImGui::GetStyle().Colors[ImGuiCol_Button] = mainColor;
				*/
				if (ImGui::Button(tabs[i], ImVec2(width, 0)))
					page = i;
				if (i < tabs_size - 1)
					ImGui::SameLine();
			}

			switch (page)
			{
			case 0:
				RagebotTab();
				break;
			case 1:
				VisualTab();
				break;
			case 2:
				MiscHackTab();
				break;
			}
			ImGui::End();
		}
		/*
		ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin(u8"RooKie's AA3Cheats For Apex 2019", &Vars.Menu.Opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
		{
			const char* tabs[] = {
				WStringToUTF8(L"暴力功能").c_str(),
				WStringToUTF8(L"温柔功能").c_str(),
				WStringToUTF8(L"视觉功能").c_str(),
				WStringToUTF8(L"其他功能").c_str()
			};
			int tabs_size = 3;//sizeof(tabs) / sizeof(tabs[0]);

			for (int i = 0; i < tabs_size; i++)
			{
				ImVec2 windowSize = ImGui::GetWindowSize();
				int width = windowSize.x / tabs_size - 9;

				int distance;
				if (i == page)
					distance = 0;
				else
					distance = i > page ? i - page : page - i;
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					mainColor.Value.x - (distance * 0.035f),
					mainColor.Value.y - (distance * 0.035f),
					mainColor.Value.z - (distance * 0.035f),
					mainColor.Value.w
				);
				ImGui::GetStyle().Colors[ImGuiCol_Button] = mainColor;

				if (ImGui::Button(tabs[i], ImVec2(width, 0)))
					page = i;
				if (i < tabs_size - 1)
					ImGui::SameLine(); 
				if (ImGui::Button(tabs[i], ImVec2(width, 0)))
					page = i;
				if (i < tabs_size - 1)
					ImGui::SameLine();
			}
			switch (page)
			{
			case 0:
				RagebotTab();
				break;
			case 1:
				LegitbotTab();
				break;
			case 2:
				VisualTab();
				break;
			case 3:
				MiscHackTab();
				break;
			}
			ImGui::End();
		}*/
	}
	//SEProtectEnd();
}

Vector RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck, bool angleInRadians = false)
{
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;
	
	float Yaw = angle - 90.0f;
	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;
	*viewCheck = y_1 < 0;
	x_1 *= zoom;
	y_1 *= zoom;
	int sizX = sizeX / 2;
	int sizY = sizeY / 2;
	x_1 += sizX;
	
	y_1 += sizY;
	if (x_1 < 5)
		x_1 = 5;
	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;
	if (y_1 < 5)
		y_1 = 5;
	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;
	x_1 += posX;
	y_1 += posY;
	return Vector(x_1, y_1, 0);
}
ImU32 GetU32(int r, int b, int g, int a)
{
	return ((a & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (r & 0xff);
}
void DrawRadar()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec2 oldPadding = style.WindowPadding;
	float oldAlpha = style.Colors[ImGuiCol_WindowBg].w;
	style.WindowPadding = ImVec2(0, 0);
	ImGui::GetStyle().Alpha = (float)Vars.Visuals.Radar.Alpha / 255.0f;
	if (ImGui::Begin("Duck", &Vars.Menu.Opened, ImVec2(200, 200), 0.4F, ImGuiWindowFlags_NoTitleBar) /*| ImGuiWindowFlags_NoTitleBar*/)
	{
		ImVec2 siz = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();
		if (Vars.Visuals.Radar.NextResetRadar)
		{
			ImGui::SetWindowSize(ImVec2(200, 200));
			Vars.Visuals.Radar.NextResetRadar = false;
		}
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
		windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), GetU32(255, 255, 255, 255), 1.5f);
		windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), GetU32(255, 255, 255, 255), 1.5f);
		if (I::Engine->IsInGame())
		{
			CBaseEntity* pLocalEntity = G::LocalPlayer;
			if (pLocalEntity)
			{
				Vector LocalPos = pLocalEntity->GetEyePosition();
				Vector shit = G::LocalPlayer->GetViewAngles();
				QAngle ang = QAngle(shit.x, shit.y, shit.z);

				for (int i = 1; i < I::ClientEntList->GetHighestEntityIndex(); i++)
				{

					CBaseEntity* pBaseEntity = (CBaseEntity*)I::ClientEntList->GetClientEntity(i);

					if (!pBaseEntity)
						continue;
					DWORD64 m_iSignifierName = pBaseEntity->m_iSignifierName();

					if (!m_iSignifierName)
						continue;
					char szName[64] = { 0 };
					CUtils::ReadData(m_iSignifierName, szName, sizeof(szName));
					if (strcmp(szName, "player") == 0)	// Crashes
					{
						if (!pBaseEntity
							|| pBaseEntity == G::LocalPlayer
							|| !pBaseEntity->isAlive())
							continue;


						float distance = (pBaseEntity->m_localOrigin() - G::LocalPlayer->m_localOrigin()).Length() * 0.01905f;	//距离
						if (distance > Vars.Visuals.Radar.MaxDis)
							continue;


						bool bIsEnemy = pLocalEntity->m_iTeamNum() != pBaseEntity->m_iTeamNum();
						bool isVisibled = pBaseEntity->IsVisible(10);
						if (Vars.Visuals.Radar.EnemyOnly && !bIsEnemy)
							continue;
						bool viewCheck = false;
						Vector EntityPos = RotatePoint(pBaseEntity->m_localOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.yaw, Vars.Visuals.Radar.Zoom, &viewCheck);
						if (!viewCheck && Vars.Visuals.Radar.ViewCheck)
							isVisibled = false;
						ImU32 clr = bIsEnemy ? (isVisibled ? GetU32(0, 255, 0, 255) : GetU32(255, 255, 255, 255)) : GetU32(0, 0, 255, 255);
						if (Vars.Visuals.Radar.VisibleOnly && !isVisibled)
							continue;
						if (Vars.Visuals.Radar.VisibleOnly && !isVisibled)
							continue;
						int s = 4;
						switch (Vars.Visuals.Radar.Type) // 0 - Box; 1 - Filled box; 2 - Circle; 3 - Filled circle;
						{
						case 0:
						{
							windowDrawList->AddRect(ImVec2(EntityPos.x - s, EntityPos.y - s),
								ImVec2(EntityPos.x + s, EntityPos.y + s),
								clr);
							break;
						}
						case 1:
						{
							windowDrawList->AddRectFilled(ImVec2(EntityPos.x - s, EntityPos.y - s),
								ImVec2(EntityPos.x + s, EntityPos.y + s),
								clr);
							break;
						}
						case 2:
						{
							windowDrawList->AddCircle(ImVec2(EntityPos.x, EntityPos.y), s, clr);
							break;
						}
						case 3:
						{
							windowDrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), s, clr);
							break;
						}
						default:
							break;
						}
					}
				}


			}
		}
	}
	ImGui::End();
	style.WindowPadding = oldPadding;
	ImGui::GetStyle().Alpha = oldAlpha;
}
tD3D11Present Present = nullptr;
ID3D11Device *g_pDevice = NULL;

HRESULT Hooks::PresentHooked(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT flags)
{
	//SEProtectStartMutation();
	static bool bInit = true;
	if (bInit) 
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)(&g_pDevice))))
		{
			g_pDevice->GetImmediateContext(&g_pContext);
		}
		//获取后缓冲区地址
		ID3D11Texture2D* renderTargetTexture = nullptr;
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<PVOID*>(&renderTargetTexture))))
		{
			g_pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
			renderTargetTexture->Release();
		}

		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 15.0f, &config, io.Fonts->GetGlyphRangesChinese());
		ImGui_ImplDX11_Init(g_hGameWnd, g_pDevice, g_pContext);
		ImGui_ImplDX11_CreateDeviceObjects();
		InitMyMenu();
		Vars.Rage.Hitboxs[0] = true;
		Vars.Rage.Hitboxs[1] = true;
		Vars.Rage.Hitboxs[2] = true;
		g_pCheat = new CCheats;
		bInit = false;
	}
	g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
	ImGui_ImplDX11_NewFrame();
	g_DrawString.clear();
	g_pCheat->Process();
	MainWindows();
	if (Vars.Visuals.Radar.Enable)
		DrawRadar();
	if (!Vars.RageMode)
	{
		if (Vars.Rage.Enabled && Vars.Rage.EnabledAimbot)
			E::RageBot->Rage();
		SpeedHack();
		doNoSpread();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return Present(pSwapChain, SyncInterval, flags);
	//SEProtectEnd();
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OpenMenu()
{
	static bool is_down = false;
	static bool is_clicked = false;

	if (G::PressedKeys[VK_INSERT])
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!G::PressedKeys[VK_INSERT] && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked)
	{
		//	Vars.Menu.main = !Vars.Menu.main;
		Vars.Menu.Opened = !Vars.Menu.Opened;
	}
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Hooks::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//SEProtectStartMutation();

//	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
//		return true;
	ImGuiIO& io = ImGui::GetIO();
	switch (uMsg)
	{
	case WM_SIZE:
	{

		break;
	}
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		G::PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		G::PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		G::PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		G::PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		G::PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		G::PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1.0f : -1.0f;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	case WM_KEYDOWN:
		G::PressedKeys[wParam] = true;
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		break;
	case WM_KEYUP:
		G::PressedKeys[wParam] = false;
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			G::PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			G::PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(wParam);
		if (button == XBUTTON1)
		{
			G::PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			G::PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	}

	OpenMenu();
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	//SEProtectEnd();
}
// simple as fuck
template <typename T> T HookVirtual(void* func, T Hook)
{
	DWORD oldProtect = 0;
	VirtualProtectEx(GetCurrentProcess(), func, 4, PAGE_EXECUTE_READWRITE, &oldProtect);

	T original = *(T*)func;
	*(T*)func = Hook;

	VirtualProtectEx(GetCurrentProcess(), func, 4, oldProtect, &oldProtect);

	return original;
}
void Hooks::InitDX11Hook()
{
	//SEProtectStartMutation();
	InitItemName();
	DWORD64 *pSwapChainVTable = (DWORD64 *)(*(DWORD64*)(*(DWORD64 *)(global::g_hGameImage + OFFSET::uDX11Base)));
	g_hGameWnd = FindWindowA("Respawn001", NULL);
	ImGui::CreateContext();//初始化IMGUI
	oWndProc = (WNDPROC)SetWindowLongPtr(g_hGameWnd, GWLP_WNDPROC, (DWORD_PTR)Hooks::hkWndProc);
	if (oWndProc == nullptr) 
		return;
	Present = (tD3D11Present)HookVirtual((void*)&pSwapChainVTable[8], Hooks::PresentHooked);
	return;
	//SEProtectEnd();
}
Variables Vars;


