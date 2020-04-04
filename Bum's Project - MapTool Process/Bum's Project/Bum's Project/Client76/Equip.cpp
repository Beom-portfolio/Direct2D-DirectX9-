#include "stdafx.h"
#include "Equip.h"
#include "ObjMgr.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "Mouse.h"
#include "Item.h"
#include "TimeMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Inven.h"

bool CEquip::m_bRenderCheckEquip = false;

void CEquip::AddEquipItem(eItem ItemType)
{
	eEquipIndex Index;

	switch (ItemType)
	{
	case ITEM_BS:
		Index = EQUIP_THREE;
		CPlayer::g_iAtt += 200;
		break;
	case ITEM_HELMET:
		Index = EQUIP_ONE;
		CPlayer::g_iDef += 50;
		break;
	case ITEM_HEAVY:
		Index = EQUIP_TWO;
		CPlayer::g_iDef += 100;
		break;
	case ITEM_SHOES:
		Index = EQUIP_FOUR;
		CPlayer::g_iDef += 50;
		break;
	case ITEM_RING:
		Index = EQUIP_FIVE;
		CPlayer::g_iAtt += 50;
		CPlayer::g_iDef += 50;
		break;
	}

	CItem* Temp = new CItem(m_tInfo.vPos.x, m_tInfo.vPos.y, Index,
							ItemType, false);
	Temp->Initialize();
	m_vecEquipItem.push_back(Temp);
}

HRESULT CEquip::Initialize(void)
{
	m_wstrObjKey = L"Equip";

	m_tInfo.vPos = D3DXVECTOR3(300.f, 250.f, 0.f);
	m_tInfo.fCX = 195;
	m_tInfo.fCY = 277;

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);

	m_rcDragEquip =
		RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 130.f, 195, 20);

	m_fTime = 0.f;

	m_EquipIndex = EQUIP_MAX;

	return S_OK;
}

int CEquip::Update(void)
{
	m_pUI = CObjMgr::GetInstance()->FindGameObject<CUserInterface>();

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);
	m_rcDragEquip =
		RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 130.f, 195, 20);
	
	//Rectangle(GetDC(g_hWnd), m_rcDragEquip.left,
	//	m_rcDragEquip.top,
	//	m_rcDragEquip.right,
	//	m_rcDragEquip.bottom);


	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	m_bDragCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rcDragEquip, vMouse);

	if (m_bDragCheck == true && GetAsyncKeyState(VK_LBUTTON))
	{
		m_tInfo.vPos.x = vMouse.x;
		m_tInfo.vPos.y = vMouse.y + 130.f;

		CUserInterface::g_YSort = true;
	}
	//
	for (size_t i = 0; i < m_vecEquipItem.size(); ++i)
	{
		if (m_vecEquipItem[i]->RUpdate(m_tInfo.vPos.x, m_tInfo.vPos.y) == 1)
		{
			UnEquipItem(m_vecEquipItem[i]->GetEquipIndex(), m_vecEquipItem[i]
				->GetItem());
		}
	}

	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	m_fTime += GET_TIME;

	return 0;
}

void CEquip::Render(void)
{
	const TEX_INFO* pEquipTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str());

	if (pEquipTexture == NULL)
	{
		ERROR_MSG(L"장착 이미지 X");
		return;
	}

	float fX = CENTER_POS(pEquipTexture->ImageInfo.Width)  + 70;
	float fY = CENTER_POS(pEquipTexture->ImageInfo.Height) - 45;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pEquipTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	for (size_t i = 0; i < m_vecEquipItem.size(); ++i)
	{
		m_vecEquipItem[i]->Render();
	}
}

void CEquip::Release(void)
{
}

void CEquip::UnEquipItem(eEquipIndex EquipIndex, eItem ItemType)
{
	switch (ItemType)
	{
	case ITEM_BS:
		CPlayer::g_iAtt -= 200;
		break;
	case ITEM_HELMET:
		CPlayer::g_iDef -= 50;
		break;
	case ITEM_HEAVY:
		CPlayer::g_iDef -= 100;
		break;
	case ITEM_SHOES:
		CPlayer::g_iDef -= 50;
		break;
	case ITEM_RING:
		CPlayer::g_iAtt -= 50;
		CPlayer::g_iDef -= 50;
		break;
	}

	CInven *Temp = CObjMgr::GetInstance()->FindGameObject<CUserInterface>()
		->GetPInven();

	vector<CItem*>::iterator iter     = m_vecEquipItem.begin();
	vector<CItem*>::iterator iter_end = m_vecEquipItem.end();

	int iCnt = 0;

	for (auto i = iter; i != iter_end;)
	{
		if ((*i)->GetEquipIndex() == EquipIndex)
		{
			//아이템일 경우
			Temp->AddUnEquipItem((*i)->GetItem());
			CSoundMgr::GetInstance()->PlaySound(L"Drop.wav", CSoundMgr::Channel_Eff);
			i = m_vecEquipItem.erase(i);
		}
		else
		{
			++i;
		}

		iter_end = m_vecEquipItem.end();
		++iCnt;
	}
}

CEquip::CEquip()
{
}


CEquip::~CEquip()
{
}
