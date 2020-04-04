#include "stdafx.h"
#include "House.h"
#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "NPC.h"
#include "UserInterface.h"
#include "HpBar.h"
#include "MpBar.h"
#include "Portal.h"
#include "Cursor.h"

HRESULT CHouse::Initialize(void)
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

	CObjMgr::GetInstance()->FindGameObject<CPortal>()->SetPos(183.f, 733.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CNPC>::CreateGameObject(),
		OBJ_TYPE_NPC
	);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER);

	CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(244.f, 704.f);



	return S_OK;
}

int CHouse::Update(void)
{
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CHouse::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void CHouse::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CHouse::CHouse()
{
}


CHouse::~CHouse()
{
	Release();
}
