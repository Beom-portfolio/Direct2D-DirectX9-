#include "stdafx.h"
#include "Smithy2.h"
#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"


HRESULT CSmithy2::Initialize(void)
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
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER);


	return S_OK;
}

int CSmithy2::Update(void)
{
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CSmithy2::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void CSmithy2::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CSmithy2::CSmithy2()
{
}


CSmithy2::~CSmithy2()
{
	Release();
}
