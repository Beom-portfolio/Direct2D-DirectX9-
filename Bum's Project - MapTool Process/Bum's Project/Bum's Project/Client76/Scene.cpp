#include "StdAfx.h"
#include "Scene.h"
#include "TextureMgr.h"

CScene::CScene(void)
{
	//싱글 텍스쳐를 여기서 불러오겠다.
	//BackGround//
	//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/BossRoom.png"
		, L"Boss"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Dungeon.png"
		, L"Dungeon"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Field.png"
		, L"Field"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/House.png"
		, L"House"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy.png"
		, L"Smithy"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy2.png"
		, L"Smithy2"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Store.png"
		, L"Store"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town.png"
		, L"Town"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town2.png"
		, L"Town2"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	//////////////////////////////////////////////////////////////////////////

	//TestPlayer
	//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	    (L"../Texture/Resorce/Player/Stand/Down/Maximin_Down_Stand0.png"
		, L"Test"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	//////////////////////////////////////////////////////////////////////////

	//UI
	//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/HPBar.png"
		, L"HP"
		, TEX_SINGLE, L"Bar",1)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/MPBar.png"
		, L"MP"
		, TEX_SINGLE, L"Bar", 1)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/PlayerStatus.png"
		, L"STATUS"
		, TEX_SINGLE, L"Status", 1)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/SmallBar.png"
		, L"Small"
		, TEX_SINGLE, L"Bar", 1)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/SmallHpBar.png"
		, L"SmallHP"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/SmallMpBar.png"
		, L"SmallMP"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/MonsterHpBar.png"
		, L"MonsterHP"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/MonsterBar.png"
		, L"EmptyBar"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/Inven.png"
		, L"Inven"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/QuickSlot1.png"
		, L"QuickSlot"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/EquipWindow.png"
		, L"Equip"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/StatusWindow.png"
		, L"Status"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/ExpBar.png"
		, L"ExpBar"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/SPBar.png"
		, L"SPBar"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//아이템
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/BloodSword.png"
		, L"BloodSword"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/RedPotion.png"
		, L"RedPotion"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/BluePotion.png"
		, L"BluePotion"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/FabricHood.png"
		, L"FabricHood"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/HeavyArmor.png"
		, L"HeavyArmor"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/LeatherShoes.png"
		, L"LeatherShoes"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Item/RedRing.png"
		, L"RedRing"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}


	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//상점
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Interface/ShopWindow.png"
		, L"Shop"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}
	//////////////////////////////////////////////////////////////////////////
	
	//멀티
	//보스
	//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Effect/Impact/Impact%d.png"
		, L"Impact"
		, TEX_MULTI
		, L"Impact", 5)))
	{
		ERROR_MSG(L"멀티 이미지 로드 실패!");
	}
	////Logo
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(L"../Texture/Resorce/Logo/Logo.png"
		, L"Logo"
		, TEX_SINGLE)))
	{
		ERROR_MSG(L"싱글 이미지 로드 실패!");
	}

}


CScene::~CScene(void)
{
}
