#include "stdafx.h"
#include "BossStage.h"
#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "Boss.h"
#include "HpBar.h"
#include "MpBar.h"
#include "RenderMgr.h"
#include "UserInterface.h"
#include "Cursor.h"
#include "Monster.h"
#include "Portal.h"

HRESULT CBossStage::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->LoadImagePath(L"../Data/ImagePath.txt")))
	{
		ERROR_MSG(L"멀티텍스쳐 이미지 로드 실패!");
		return E_FAIL;
	}

	//플레이어

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CBackGround>::CreateGameObject(),
		OBJ_TYPE_BACKGROUND);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<Tile>::CreateGameObject(),
		OBJ_TYPE_TILE);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPortal>::CreateGameObject(),
		OBJ_TYPE_PORTAL);

	CObjMgr::GetInstance()->FindGameObject<CPortal>()->SetPos(800.f, 412.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER);

	CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(D3DXVECTOR3(844.f, 485.f, 0.f));

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CBoss>::CreateGameObject(),
		OBJ_TYPE_BOSS);
	


	return S_OK;
}

int CBossStage::Update(void)
{
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CBossStage::Render(void)
{
	CObjMgr::GetInstance()->Render();
	//CRenderMgr::GetInstance()->Render();
}

void CBossStage::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CBossStage::CBossStage()
{
}


CBossStage::~CBossStage()
{
	Release();
}
