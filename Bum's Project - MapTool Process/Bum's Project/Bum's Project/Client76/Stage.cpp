#include "StdAfx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "Test.h"
#include "Weapon.h"
#include "Monster.h"
#include "RenderMgr.h"
#include "HpBar.h"
#include "MpBar.h"
#include "UserInterface.h"
#include "Damage.h"
#include "Cursor.h"
#include "Portal.h"

HRESULT CStage::Initialize(void)
{

	if (FAILED(CTextureMgr::GetInstance()->LoadImagePath(L"../Data/ImagePath.txt")))
	{
		ERROR_MSG(L"멀티텍스쳐 이미지 로드 실패!");
		return E_FAIL;
	}


	//데미지
	//플레이어
	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CBackGround>::CreateGameObject(),
		OBJ_TYPE_BACKGROUND	);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<Tile>::CreateGameObject(),
		OBJ_TYPE_TILE);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPortal>::CreateGameObject(),
		OBJ_TYPE_PORTAL);

	CObjMgr::GetInstance()->FindGameObject<CPortal>()->SetPos(1570.f, 430.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CPlayer>::CreateGameObject(),
		OBJ_TYPE_PLAYER	);

	CObjMgr::GetInstance()->FindGameObject<CPlayer>()->SetPos(2871.f, 588.f);

	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CMonster>::CreateGameObject(),
		OBJ_TYPE_MONSTER);

	return S_OK;
}

int CStage::Update(void)
{
	CObjMgr::GetInstance()->Update();


	return 0;
}

void CStage::Render(void)
{
	CObjMgr::GetInstance()->Render();
	//CRenderMgr::GetInstance()->Render();
}

void CStage::Release(void)
{
	CObjMgr::GetInstance()->Release();
}

CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}
