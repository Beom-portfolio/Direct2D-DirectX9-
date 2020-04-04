#include "StdAfx.h"
#include "MainGame.h"
#include "Device.h"
#include "scenemgr.h"
#include "TextureMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Player.h"


int	 CPlayer::g_iPlayerMoney = 10000;
int  CPlayer::g_iLevel = 1;
int  CPlayer::g_iAtt = 100;
int  CPlayer::g_iDef = 10;
int  CPlayer::g_iMaxHp = 10000;
int  CPlayer::g_iMaxMp = 10000;
int  CPlayer::g_iHp = CPlayer::g_iMaxHp;
int  CPlayer::g_iMp = CPlayer::g_iMaxMp;

void CMainGame::FPS_Render(void)
{
	D3DXMatrixTranslation(&m_matTrans, 670, 0, 0.f);
	
	++m_iCount;

	//m_fTime += CTimeMgr::GetInstance()->GetTime();

	m_fTime += GET_TIME;

	if(m_fTime > 1.f)
	{
		m_fTime = 0.f;

		wsprintf(m_szFps, L"\n\n\n\nFPS : %d", m_iCount);

		m_iCount = 0;
	}

	m_pDevice->GetSprite()->SetTransform(&m_matTrans);

	m_pDevice->GetFont()->DrawTextW(
		m_pDevice->GetSprite(),
		m_szFps,
		lstrlen(m_szFps),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
		);
}

HRESULT CMainGame::Initialize(void)
{
	CSoundMgr::GetInstance()->LoadSoundFile();

	CTimeMgr::GetInstance()->InitTime();


	if(FAILED(m_pDevice->Init3D()))
	{
		ERROR_MSG(L"장치 초기화 실패!");
		return E_FAIL;
	}

	CSceneMgr::GetInstance()->Initialize();
	CSceneMgr::GetInstance()->SetChangeScene(SCENE_LOGO);


	return S_OK;
}

int CMainGame::Update(void)
{
	KeyTest();

	CSoundMgr::GetInstance()->UpdateSound();
	CTimeMgr::GetInstance()->SetTime();
	CSceneMgr::GetInstance()->Update();

	return 0;
}

void CMainGame::Render(void)
{
	m_pDevice->Render_Begin();

	CSceneMgr::GetInstance()->Render();

	FPS_Render();
	
	m_pDevice->Render_End();

	m_pDevice->GetDevice()->Present(NULL, NULL, g_hWnd, NULL);
}

void CMainGame::Release(void)
{
	m_pDevice->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
}

void CMainGame::KeyTest(void)
{

}

CMainGame::CMainGame(void)
:m_pDevice(CDevice::GetInstance())
,m_fTime(0.f)
,m_iCount(0)
{
	ZeroMemory(m_szFps, sizeof(TCHAR) * MIN_STR);
	D3DXMatrixIdentity(&m_matTrans);
}

CMainGame::~CMainGame(void)
{
	Release();
}
