#include "StdAfx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "Field.h"
#include "Stage.h"
#include "BossStage.h"
#include "House.h"
#include "Smithy.h"
#include "Smithy2.h"
#include "Store.h"
#include "Town.h"
#include "Town2.h"
#include "GameObject.h"

bool CSceneMgr::m_bFieldCheck = false;
bool CSceneMgr::m_bHouseCheck = false;

IMPLEMENT_SINGLETON(CSceneMgr);

void CSceneMgr::SetScene(eSceneType eType)
{
	CSoundMgr::GetInstance()->StopAll();

	CSoundMgr::GetInstance()->PlaySound(L"Menu.wav", CSoundMgr::Channel_Eff);

	safe_delete(m_pScene);

	switch (eType)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;

	case SCENE_FIELD:
		m_pScene = new CField;
		CGameObject::m_vScroll.x = -1254;
		CGameObject::m_vScroll.y = -729;
		m_bFieldCheck = true;
		CSoundMgr::GetInstance()->PlayBGM(L"Field.wav", CSoundMgr::Channel_BGM);
		break;

	case SCENE_STAGE:
		m_pScene = new CStage;
		CGameObject::m_vScroll.x = -2471;
		CGameObject::m_vScroll.y = -288;
		CSoundMgr::GetInstance()->PlayBGM(L"Field.wav", CSoundMgr::Channel_BGM);
		break;

	case SCENE_BOSSSTAGE:
		m_pScene = new CBossStage;
		CGameObject::m_vScroll.x = -444;
		CGameObject::m_vScroll.y = -185;
		CSoundMgr::GetInstance()->PlayBGM(L"InfiniteWarbgm.wav", CSoundMgr::Channel_BGM);
		break;

	case SCENE_HOUSE:
		m_pScene = new CHouse;
		CGameObject::m_vScroll.x = 155;
		CGameObject::m_vScroll.y = -404;
		m_bHouseCheck = true;
		CSoundMgr::GetInstance()->PlayBGM(L"Shop.wav", CSoundMgr::Channel_BGM);
		break;

	case SCENE_SMITHY:
		m_pScene = new CSmithy;
		break;

	case SCENE_SMITHY2:
		m_pScene = new CSmithy2;
		break;

	case SCENE_STORE:
		m_pScene = new CStore;
		break;

	case SCENE_TOWN:
		m_pScene = new CTown;
		break;

	case SCENE_TOWN2:
		m_pScene = new CTown2;
		if (CSceneMgr::m_bFieldCheck == true)
		{
			CGameObject::m_vScroll.x = -264;
			CGameObject::m_vScroll.y = -708;
		}
		else if (CSceneMgr::m_bHouseCheck == true)
		{
			CGameObject::m_vScroll.x = -207;
			CGameObject::m_vScroll.y = -341;
		}
		else
		{
			CGameObject::m_vScroll.x = -400;
			CGameObject::m_vScroll.y = -500;
		}
		CSoundMgr::GetInstance()->PlayBGM(L"Village1.wav", CSoundMgr::Channel_BGM);
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::SetChangeScene(eSceneType eType)
{
	m_bChangeScene = true;
	m_eType		   = eType;
}

HRESULT CSceneMgr::Initialize(void)
{
	return S_OK;
}

int CSceneMgr::Update(void)
{
	if(m_bChangeScene)
	{
		m_bChangeScene = false;
		SetScene(m_eType);
	}

	if(m_pScene)
		m_pScene->Update();

	return 0;
}

void CSceneMgr::Render(void)
{
	if(m_pScene)
		m_pScene->Render();
}

void CSceneMgr::Release(void)
{
	safe_delete(m_pScene);
}

CSceneMgr::CSceneMgr(void)
{
	m_pScene		= NULL;
	m_bChangeScene	= false;
	m_eType			= SCENE_LOGO;
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}
