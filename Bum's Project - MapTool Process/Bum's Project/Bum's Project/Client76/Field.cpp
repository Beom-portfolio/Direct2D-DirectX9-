#include "stdafx.h"
#include "Field.h"
#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "UserInterface.h"
#include "HpBar.h"
#include "MpBar.h"
#include "Cursor.h"
#include "Portal.h"

HRESULT CField::Initialize(void)
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

	CObjMgr::GetInstance()->FindGameObject<CPortal>()->SetPos(1670.f, 880.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CTree>::CreateGameObject(),
		OBJ_TYPE_TREE);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER);

	CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(1654.f, 1029.f);

	return S_OK;
}

int CField::Update(void)
{
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CField::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void CField::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CField::CField()
{
}


CField::~CField()
{
	Release();
}
