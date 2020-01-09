#include "../Cheat.h"
#include "Render.h"

CRender *GetRender()
{
	static CRender s;
	return &s;
}

CRender::CRender()
{
}


CRender::~CRender()
{
}

void CRender::CreateIMGUI(HWND hWnd, ID3D11Device *pDevice, ID3D11DeviceContext *pContext)
{
	m_bShow = true;
	m_pDevice = pDevice;
	m_pContext = pContext;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 12.0f, &config, io.Fonts->GetGlyphRangesChinese());
	ImGui_ImplDX11_Init(hWnd, pDevice, pContext);
	ImGui_ImplDX11_CreateDeviceObjects();
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);

	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);

	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 13.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 3.0f;
	style.GrabRounding = 3.0f;

	Hooks::oWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (DWORD_PTR)Hooks::hkWndProc);
}

void CRender::Begin()
{
	ImGui_ImplDX11_NewFrame();

}


void CRender::AimBotTab()
{
	/*
	ImGui::Checkbox(charenc(jhzm), &Vars.Aimbot.AimbotEnable);
	//-----

	ImGui::Separator();
	ImGui::Columns(2, charenc(aimbotconfig), true);
	{
		ImGui::Combo(charenc(zmaj), &Vars.Aimbot.AimKey, keyNames, ARRAYSIZE(keyNames));
		ImGui::SliderFloat(charenc(fovSTRBYTE), &Vars.Aimbot.FOV, 1.f, 20.f);
		ImGui::SliderFloat(charenc(zdmzjl), &Vars.Aimbot.Dist, 1.f, 1000.f);
		ImGui::Checkbox(charenc(mzyj), &Vars.Aimbot.AimMother);
	}

	ImGui::NextColumn();
	{
		ImGui::Combo(charenc(zmbw), &Vars.Aimbot.Bone, AimBones, ARRAYSIZE(AimBones));
		ImGui::Checkbox(charenc(sjbw), &Vars.Aimbot.RandBone);
	}
	if (ImGui::Button(charenc(tc)))
		canExit = true;
	ImGui::Columns(1);
	ImGui::Separator();

	*/
}

void CRender::VisualTab()
{
	/*
	ImGui::Checkbox(charenc(jhesp), &Vars.Visual.VisualEnable);
	//----- 

	ImGui::Separator();
	ImGui::Columns(3, charenc(VisualConfig), true);
	{
		ImGui::Checkbox(charenc(xszx), &Vars.Visual.DrawCrosshair);
		ImGui::Checkbox(charenc(xsfk), &Vars.Visual.Box);
		ImGui::Checkbox(charenc(xsgg), &Vars.Visual.Ske);
		ImGui::Checkbox(charenc(xsxl), &Vars.Visual.Health);
		ImGui::Checkbox(charenc(xsdy), &Vars.Visual.isShowTeammate);
		ImGui::Checkbox(charenc(xszjdj), &Vars.Visual.isShowCar);
		ImGui::Checkbox(charenc(glzswp), &Vars.Visual.isFilter);
		ImGui::Checkbox(charenc(xsdwjkjsjg), &Vars.Visual.NearPlayerDetectWarning);

		ImGui::Checkbox(charenc("Ping"), &Vars.Visual.isShowPing);
	}

	ImGui::NextColumn();
	{
		ImGui::RadioButton(charenc(gbwzxx), &Vars.Visual.StrShow, 0);
		ImGui::RadioButton(charenc(xsszxljlxs), &Vars.Visual.StrShow, 1);
		ImGui::RadioButton(charenc(xsszxljlxsgdxx), &Vars.Visual.StrShow, 2);
		ImGui::SliderFloat(charenc(hsjgzdjl), &Vars.Visual.RedWarnDST, 1, Vars.Visual.YellowWarnDST);
		ImGui::SliderFloat(charenc(huangsejgzdjl), &Vars.Visual.YellowWarnDST, Vars.Visual.RedWarnDST, 1000);
		ImGui::SliderInt(charenc(zyxswp), &Vars.Visual.wespdt, 1, 1000);
		ImGui::SliderInt(charenc(zyxswj), &Vars.Visual.maxDST, 1, 1500);
	}
	ImGui::NextColumn();
	{
		ImGui::Checkbox(charenc(jhdjxs), &Vars.Visual.isShowItem);					// 激活道具显示
		ImGui::Checkbox(charenc(xswq), &Vars.Visual.isShowGun);							// 显示武器
		ImGui::Checkbox(charenc(显示弹药), &Vars.Visual.isShowAmmo);					// 显示弹药
		ImGui::Checkbox(charenc(武器配件), &Vars.Visual.isShowPart);							// 显示武器配件
		ImGui::Checkbox(charenc(显示药物), &Vars.Visual.isShowDrug);							// 显示药物
		ImGui::Checkbox(charenc(显示头盔防弹衣背包), &Vars.Visual.isShowEquip);						// 显示头盔/防弹衣/背包
		ImGui::Checkbox(charenc(显示其他), &Vars.Visual.isShowOther);						// 显示其他
	}
	ImGui::Columns(1);
	ImGui::Separator();
	*/
}

void CRender::MiscTab()
{
	/*
	ImGui::Checkbox(charenc(EnablesMisc), &Vars.Misc.MiscEnable);
	//-----

	ImGui::Separator();
	ImGui::Columns(2, charenc("MiscConfig"), true);
	{
		ImGui::Checkbox(charenc(KJWHD), &Vars.Misc.NoSway);
		ImGui::Checkbox(charenc(ZDWXZ), &Vars.Misc.NoGravity);
		ImGui::Checkbox(charenc(jhjs), &Vars.Misc.SpeedHack);
		//	ImGui::Checkbox(charenc(RageSpeedFuckUp), &Vars.Misc.RageSpeedHack);
	}
	ImGui::NextColumn();
	{
		ImGui::Checkbox(charenc(KSCYSZCY), &Vars.Misc.FastUseAndInWaterUser);
		ImGui::Checkbox(charenc(FastDuck), &Vars.Misc.FastProne);
		ImGui::SliderFloat(charenc(sudu), &Vars.Misc.MaxSpeed, 1.f, 720.f);
		//	ImGui::SliderInt(charenc(RageSpeedFuckUp), &Vars.Misc.FuckUp, 1, 10);
		//	ImGui::Checkbox(charenc(XGSH), &Vars.Misc.HitDamage);
	}

	ImGui::Columns(1);
	ImGui::Separator();
	*/

}
ImColor mainColor = ImColor(54, 54, 54, 255);
void CRender::Render()
{
	return;
	if (!m_bShow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("RooKie", &Vars.Menu.Opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders ))
	{
		const char* tabs[] = {
			"TAB1",
			"TAB2",
			"TAB3"
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
		}

		switch (page)
		{
		case 0:
			AimBotTab();
			break;
		case 1:
			VisualTab();
			break;
		case 2:
			MiscTab();
			break;
		}
	}
}

void CRender::End()
{
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CRender::EspPlayer()
{

}
