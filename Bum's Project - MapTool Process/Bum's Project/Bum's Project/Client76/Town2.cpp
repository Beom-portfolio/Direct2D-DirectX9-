#include "stdafx.h"
#include "Town2.h"
#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "Portal.h"
#include "Cursor.h"
#include "UserInterface.h"
#include "HpBar.h"
#include "MpBar.h"
#include "SceneMgr.h"

HRESULT CTown2::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->LoadImagePath(L"../Data/ImagePath.txt")))
	{
		ERROR_MSG(L"멀티텍스쳐 이미지 로드 실패!");
		return E_FAIL;
	}


	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CBackGround>::CreateGameObject(),
		OBJ_TYPE_BACKGROUND);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<Tile>::CreateGameObject(),
		OBJ_TYPE_TILE);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPortal>::CreateGameObject(),
		OBJ_TYPE_PORTAL);

	CObjMgr::GetInstance()->FindGameObject<CPortal>()->SetPos(860.f, 494.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER);
	
	if (CSceneMgr::m_bFieldCheck == true)
	{
		CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(664.f, 1008.f);
		CSceneMgr::m_bFieldCheck = false;
	}
	else if (CSceneMgr::m_bHouseCheck == true)
	{
		CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(607.f, 641.f);
		CSceneMgr::m_bHouseCheck = false;
	}
	else
	{
		CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(800.f, 800.f);
	}

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CHpBar>::CreateGameObject(),
		OBJ_TYPE_UI);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CMpBar>::CreateGameObject(),
		OBJ_TYPE_UI);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CUserInterface>::CreateGameObject(),
		OBJ_TYPE_UI);




	return S_OK;
}

int CTown2::Update(void)
{
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CTown2::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void CTown2::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CTown2::CTown2()
{
}

CTown2::~CTown2()
{
	Release();
}
