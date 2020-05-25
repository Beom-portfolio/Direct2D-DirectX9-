#include "stdafx.h"
#include "Item.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "Mouse.h"
#include "Inven.h"
#include "UserInterface.h"
#include "TimeMgr.h"

HRESULT CItem::Initialize(void)
{
	m_tInfo.fCX = 24;
	m_tInfo.fCY = 24;

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y,
		m_tInfo.fCX, m_tInfo.fCY);

	m_bDragCheck = false;

	m_bClickCheck = false;

	m_bRClickCheck = false;

	m_bOneChangeCheck = false;

	m_fTime = 0;

	return S_OK;
}

int CItem::Update(void)
{
	return 0;
}

int CItem::Update(D3DXVECTOR3 vPos)
{
	m_tInfo.vPos.x = vPos.x - 300 / 2.f;
	m_tInfo.vPos.y = vPos.y - 290 / 2.f + m_fFar;

	m_OriginPos.x = m_tInfo.vPos.x;
	m_OriginPos.y = m_tInfo.vPos.y;

	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	//충돌

	if (m_bOneChangeCheck == false)
	{
		m_bDragCheck = CCollisionMgr::GetInstance()
			->InvenDragCheckCollisionCheck(m_rc, vMouse);

		if (m_bDragCheck == true && GetAsyncKeyState(VK_LBUTTON))
		{

			m_bClickCheck = true;

			m_tInfo.vPos.x = vMouse.x;
			m_tInfo.vPos.y = vMouse.y;

			m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y,
				m_tInfo.fCX, m_tInfo.fCY);

			CUserInterface::g_YSort = false;
		}
		else
		{
			m_bClickCheck = false;

			m_rc = RectMake(m_OriginPos.x, m_OriginPos.y,
				m_tInfo.fCX, m_tInfo.fCY);
		}
	}

	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	m_fTime += GET_TIME;


	if (m_bClickCheck == true)
		return 1;
	else
		return 0;

}

int CItem::RUpdate(float vPosX, float vPosY)

{
	/*if (m_bEquipItemCheck == true)
	{
		m_tInfo.vPos.x = vPosX - 155 / 2.f;
		m_tInfo.vPos.y = vPosY - 190 / 2.f + m_fFar;

		m_OriginPos.x = m_tInfo.vPos.x;
		m_OriginPos.y = m_tInfo.vPos.y;
	}
	else
	{
		m_tInfo.vPos.x = vPosX - 300 / 2.f;
		m_tInfo.vPos.y = vPosY - 290 / 2.f + m_fFar;

		m_OriginPos.x = m_tInfo.vPos.x;
		m_OriginPos.y = m_tInfo.vPos.y;
	}*/

	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y,
		m_tInfo.fCX, m_tInfo.fCY);

	/*Rectangle(GetDC(g_hWnd), m_rc.left, m_rc.top,
		m_rc.right, m_rc.bottom);*/

	//충돌
	m_bDragCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rc, vMouse);

	if (m_bDragCheck == true &&
		GetAsyncKeyState(VK_RBUTTON) &&
		m_fTime > 0.3f)
	{
		m_bRClickCheck = true;

		m_fTime = 0.f;

		CUserInterface::g_YSort = true;
	}
	else
	{
		m_bRClickCheck = false;
	}

	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	m_fTime += GET_TIME;

	if (m_bRClickCheck == true)
		return 1;
	else
		return 0;
}


void CItem::Render(void)
{
	const TEX_INFO* pItemTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str());

	TCHAR szItemText[MIDDLE_STR] = L"";
	TCHAR szItemPrice[MIDDLE_STR] = L"";

	if (pItemTexture == NULL)
	{
		ERROR_MSG(L"아이템 이미지 X");
		return;
	}

	float fX = CENTER_POS(pItemTexture->ImageInfo.Width);
	float fY = CENTER_POS(pItemTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pItemTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	if (m_bEquipItemCheck == true)
	{
		D3DXMATRIX NameTrans;

		D3DXMatrixTranslation(&NameTrans,
			m_tInfo.vPos.x + 20.f,
			m_tInfo.vPos.y - 10.f, 0.f);

		m_tInfo.matWorld = NameTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		wsprintf(szItemText, m_wstrObjKey.c_str());
		wsprintf(szItemPrice, m_wstrItemPrice.c_str());

		//아이템
		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(),
			szItemText,
			lstrlen(szItemText),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 0, 255, 0)
		);
	}
	else
	{
		D3DXMATRIX NameTrans;

		D3DXMatrixTranslation(&NameTrans,
			m_tInfo.vPos.x + 50.f,
			m_tInfo.vPos.y - 10.f, 0.f);

		m_tInfo.matWorld = NameTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		wsprintf(szItemText, m_wstrObjKey.c_str());
		wsprintf(szItemPrice, m_wstrItemPrice.c_str());

		//아이템
		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(),
			szItemText,
			lstrlen(szItemText),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}

	if (m_bShopItemCheck == true)
	{
		D3DXMATRIX PriceTrans;

		D3DXMatrixTranslation(&PriceTrans,
			m_tInfo.vPos.x + 270.f,
			m_tInfo.vPos.y - 10.f, 0.f);

		m_tInfo.matWorld = PriceTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		//가격
		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(),
			szItemPrice,
			lstrlen(szItemPrice),
			NULL,
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}


	/*Rectangle(GetDC(g_hWnd), m_rc.left, m_rc.top,
	m_rc.right, m_rc.bottom);*/
}

void CItem::Release(void)
{
}

void CItem::ItemType(void)
{
	switch (m_eItemType)
	{
	case ITEM_BS:
		m_wstrObjKey = L"BloodSword";
		m_iItemPrice = 4000;
		m_wstrItemPrice = L"4000";
		break;
	case ITEM_REDP:
		m_wstrObjKey = L"RedPotion";
		m_iItemPrice = 200;
		m_wstrItemPrice = L"200";
		break;
	case ITEM_BLUEP:
		m_wstrObjKey = L"BluePotion";
		m_iItemPrice = 200;
		m_wstrItemPrice = L"200";
		break;
	case ITEM_HELMET:
		m_wstrObjKey = L"FabricHood";
		m_iItemPrice = 1000;
		m_wstrItemPrice = L"1000";
		break;
	case ITEM_HEAVY:
		m_wstrObjKey = L"HeavyArmor";
		m_iItemPrice = 2000;
		m_wstrItemPrice = L"2000";
		break;
	case ITEM_SHOES:
		m_wstrObjKey = L"LeatherShoes";
		m_iItemPrice = 1500;
		m_wstrItemPrice = L"1500";
		break;
	case ITEM_RING:
		m_wstrObjKey = L"RedRing";
		m_iItemPrice = 2000;
		m_wstrItemPrice = L"2000";
		break;
	}
}

void CItem::IndexType(void)
{
	switch (m_eIndex)
	{
	case INVEN_ONE:
		m_fFar = 0.f;
		break;
	case INVEN_TWO:
		m_fFar = 25.f;
		break;
	case INVEN_THREE:
		m_fFar = 50.f;
		break;
	case INVEN_FOUR:
		m_fFar = 75.f;
		break;
	case INVEN_FIVE:
		m_fFar = 100.f;
		break;
	case INVEN_SIX:
		m_fFar = 125.f;
		break;
	case INVEN_SEVEN:
		m_fFar = 150.f;
		break;
	case INVEN_EIGHT:
		m_fFar = 175.f;
		break;
	case INVEN_NINE:
		m_fFar = 200.f;
		break;
	case INVEN_TEN:
		m_fFar = 225.f;
		break;
	case INVEN_ELEVEN:
		m_fFar = 250.f;
		break;
	case INVEN_TWELVE:
		m_fFar = 275.f;
		break;
	}
}

void CItem::EquipIndexType(void)
{
	switch (m_eEquipIndex)
	{
	case EQUIP_ONE:
		m_fFar = 0.f;
		break;
	case EQUIP_TWO:
		m_fFar = 30.f;
		break;
	case EQUIP_THREE:
		m_fFar = 60.f;
		break;
	case EQUIP_FOUR:
		m_fFar = 90.f;
		break;
	case EQUIP_FIVE:
		m_fFar = 120.f;
		break;
	case EQUIP_SIX:
		m_fFar = 150.f;
		break;
	case EQUIP_SEVEN:
		m_fFar = 180.f;
		break;
	case EQUIP_EIGHT:
		m_fFar = 175.f;
		break;
	}
}

CItem::CItem()
{
}

CItem::CItem(D3DXVECTOR3 vPos, eInvenIndex Index,
	eItem Item)
{
	m_bEquipItemCheck = false;
	m_eIndex = Index;
	m_eItemType = Item;
	m_fFar = 0.f;

	ItemType();
	IndexType();

	m_tInfo.vPos.x = vPos.x - 300/2.f;
	m_tInfo.vPos.y = vPos.y - 290/2.f + m_fFar;
}

CItem::CItem(float vPosX, float vPosY, eInvenIndex Index,
	eItem Item, bool ShopItemCheck = false)
{
	m_bEquipItemCheck = false;
	m_bShopItemCheck = ShopItemCheck;
	m_eIndex = Index;
	m_eItemType = Item;
	m_fFar = 0.f;

	ItemType();
	IndexType();

	m_tInfo.vPos.x = vPosX - 300 / 2.f;
	m_tInfo.vPos.y = vPosY - 290 / 2.f + m_fFar;
}

CItem::CItem(float vPosX, float vPosY, eEquipIndex Index,
			 eItem Item, bool ShopItemCheck)
{
	m_bEquipItemCheck = true;

	m_bShopItemCheck = ShopItemCheck;
	m_eEquipIndex = Index;
	m_eItemType = Item;
	m_fFar = 0.f;

	ItemType();
	EquipIndexType();

	m_tInfo.vPos.x = vPosX - 300 / 2.f;
	m_tInfo.vPos.y = vPosY - 100 / 2.f + m_fFar;
}


CItem::~CItem()
{
}
