#pragma once


class CRender
{
public:
	CRender();
	~CRender();
private:
	void MiscTab();
	void VisualTab();
	void AimBotTab();
public:
	void CreateIMGUI(HWND hWnd, ID3D11Device *pDevice, ID3D11DeviceContext *pContext);
	void Begin();
	void Render();
	void End();
	void EspPlayer();
	bool IsShow() { return m_bShow; }
private:
	bool m_bShow;
	ID3D11Device *m_pDevice;
	ID3D11DeviceContext *m_pContext;
};
CRender *GetRender();
