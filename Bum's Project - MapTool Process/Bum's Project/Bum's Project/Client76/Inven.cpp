#include "stdafx.h"
#include "Inven.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "Mouse.h"
#include "Item.h"
#include "Shop.h"
#include "TimeMgr.h"
#include "Equip.h"

bool CInven::m_bRenderCheckInven = false;

void CInven::MyMatrix(void)
{
	D3DXVECTOR3 vPlayerPos = CObjMgr::GetInstance()->FindGameObject<CPlayer>()->GetNormInfo().vPos;

	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;


	D3DXMatrixScaling(&matScale,
		1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans,
		vPlayerPos.x + m_vScroll.x,
		vPlayerPos.y + m_vScroll.y,
		0.f
	);

	m_tPotion.matWorld = matScale * matTrans;
}

void CInven::MyFrame(void)
{
	m_tPotionFrame.fIndex += GET_TIME * m_tPotionFrame.fCount * 2.f;

	if (m_tPotionFrame.fIndex >= m_tPotionFrame.fMax)
	{
		m_tPotionFrame.fIndex = 0.f;
		m_bHpPotion = false;
		m_bMpPotion = false;
	}
}

void CInven::RenderPotionEffect(void)
{
	TCHAR wstrPotionType[MIDDLE_STR] = L"";

	if (m_bHpPotion == true)
	{
		wsprintf(wstrPotionType, L"HpPotion");
	}
	else
	{
		wsprintf(wstrPotionType, L"MpPotion");
	}

	const TEX_INFO* pPotionTex =
		CTextureMgr::GetInstance()->GetTexture(
			L"Effect",
			wstrPotionType,
			static_cast<int>(m_tPotionFrame.fIndex)
		);

	if (pPotionTex == NULL)
	{
		ERROR_MSG(L"포션 이미지 X");
		return;
	}

	float fX = CENTER_POS(pPotionTex->ImageInfo.Width);
	float fY = CENTER_POS(pPotionTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tPotion.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pPotionTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CInven::AddInvenItem(vector<CItem*> *vecItem, int Cost)
{
	int InvenSize;
	InvenSize = m_vecItem.size();

	CPlayer::g_iPlayerMoney -= Cost;

	vector<CItem*>::iterator iter = vecItem->begin();
	vector<CItem*>::iterator iter_end = vecItem->end();

	for (auto i = iter; i != iter_end;)
	{
		CItem* Temp = new CItem(m_tInfo.vPos,
			static_cast<eInvenIndex>(InvenSize),
			(*i)->GetItem());
		Temp->Initialize();
		m_vecItem.push_back(Temp);

		++InvenSize;

		i = vecItem->erase(i);

		iter_end = vecItem->end();
	}
}

void CInven::AddUnEquipItem(eItem ItemType)
{
	int InvenSize = m_vecItem.size();

	
	CItem* Temp = new CItem(m_tInfo.vPos,
		static_cast<eInvenIndex>(InvenSize),
		ItemType);
	Temp->Initialize();
	m_vecItem.push_back(Temp);

	//++InvenSize;
}

void CInven::SellInvenItem(eInvenIndex InvenIndex)
{
	vector<CItem*>::iterator iter = m_vecItem.begin();
	vector<CItem*>::iterator iter_end = m_vecItem.end();

	int iCnt = 0;

	for (auto i = iter; i != iter_end;)
	{
		if ((*i)->GetIndex() == InvenIndex)
		{
			CPlayer::g_iPlayerMoney += (*i)->GetItemPrice();
			i = m_vecItem.erase(i);
		}
		else if ((*i)->GetIndex() > InvenIndex)
		{
			(*i)->SetIndexType(static_cast<eInvenIndex>(iCnt - 1));
			(*i)->IndexType();
			++i;
		}
		else
		{
			++i;
		}

		iter_end = m_vecItem.end();
		++iCnt;
	}

	CSoundMgr::GetInstance()->PlaySound(L"ShopResult.wav", CSoundMgr::Channel_Eff);
}

void CInven::EquipInvenItem(eInvenIndex InvenIndex)
{
	CEquip *Temp = CObjMgr::GetInstance()->FindGameObject<CUserInterface>()
		->GetPEquip();

	vector<CItem*>::iterator iter = m_vecItem.begin();
	vector<CItem*>::iterator iter_end = m_vecItem.end();

	int iCnt = 0;

	for (auto i = iter; i != iter_end;)
	{
		if ((*i)->GetIndex() == InvenIndex)
		{
			if ((*i)->GetItem() == ITEM_REDP ||
				(*i)->GetItem() == ITEM_BLUEP)
			{
				//포션일 경우
				//먹고 지운다.
				//포션일 경우
				if ((*i)->GetItem() == ITEM_REDP)
				{
					m_bHpPotion = true;

					CPlayer::g_iHp *= 0;
					CPlayer::g_iHp = CPlayer::g_iMaxHp;

				}
				else
				{
					m_bMpPotion = true;

					CPlayer::g_iMp *= 0;
					CPlayer::g_iMp = CPlayer::g_iMaxMp;
				}

				CSoundMgr::GetInstance()->PlaySound(L"PotionDrug.wav", CSoundMgr::Channel_Eff);

				i = m_vecItem.erase(i);
			}
			else
			{
				//아이템일 경우
				Temp->AddEquipItem((*i)->GetItem());

				CSoundMgr::GetInstance()->PlaySound(L"Drop.wav", CSoundMgr::Channel_Eff);

				i = m_vecItem.erase(i);
			}
		}
		else if ((*i)->GetIndex() > InvenIndex)
		{
			(*i)->SetIndexType(static_cast<eInvenIndex>(iCnt - 1));
			(*i)->IndexType();
			++i;
		}
		else
		{
			++i;
		}

		iter_end = m_vecItem.end();
		++iCnt;
	}
}

void CInven::SwapItem(CItem * A, CItem * B)
{
	eItem TempItem = A->GetItem();
	A->SetItemType(B->GetItem());
	B->SetItemType(TempItem);

	INFO TempINFO = A->GetNormInfo();
	A->SetNormInfo(B->GetNormInfo());
	B->SetNormInfo(TempINFO);

	A->IndexType();
	A->ItemType();
	B->IndexType();
	B->ItemType();
	
	A->Initialize();
	B->Initialize();
}

HRESULT CInven::Initialize(void)
{
	m_wstrObjKey = L"Inven";

	m_tInfo.vPos = D3DXVECTOR3(630.f, 250.f, 0.f);
	m_tInfo.fCX = 345;
	m_tInfo.fCY = 400;

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);
	
	m_rcDragInven = 
		   RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 183.f, 345, 30);
	
	m_fTime = 0.f;
	fTime = 0.f;

	m_bHpPotion = false;
	m_bMpPotion = false;

	m_tPotionFrame = FRAME(0.f, 21.f, 21.f);

	m_InvecIndex = INVEN_MAX;

	return S_OK;
}

int CInven::Update(void)
{
	m_pUI = CObjMgr::GetInstance()->FindGameObject<CUserInterface>();
	//마우스 움직임 관리 해야함
	//위쪽 렉트(인벤을 움직임)
	//
	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);
	m_rcDragInven =
		   RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 183.f, 345, 30);
	//
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	//충돌
	m_bDragCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rcDragInven, vMouse);

	if (m_bDragCheck == true && GetAsyncKeyState(VK_LBUTTON))
	{
		m_tInfo.vPos.x = vMouse.x;
		m_tInfo.vPos.y = vMouse.y + 183.f;

		CUserInterface::g_YSort = false;
	}


	//
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i]->Update(m_tInfo.vPos) == 1)
		{
			m_InvecIndex = m_vecItem[i]->GetIndex();
		}
	}

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i]->RUpdate(m_tInfo.vPos.x, m_tInfo.vPos.y) == 1
			&& fTime > 0.5f)
		{
			//Equip으로 들어가야함
			//if(ITEM)
			EquipInvenItem(static_cast<eInvenIndex>(i));
			fTime = 0.f;
		}
	}

	//
	if (m_InvecIndex != INVEN_MAX)
	{
		for (size_t i = 0; i < m_vecItem.size(); ++i)
		{
			if (i == m_InvecIndex)
			{
				m_vecItem[i]->SetOneChangeCheck(false);
			}
			else
				m_vecItem[i]->SetOneChangeCheck(true);
		}

		if (m_vecItem[m_InvecIndex]->GetClickCheck() == false)
		{

			//사이즈가 하나있을때
			if (m_vecItem.size() == 1)
			{
				if (CCollisionMgr::GetInstance()
					->ShopSellCheck(m_pUI->GetPShop(),
						vMouse) == true && m_fTime > 0.4f)
				{
					//판매
					SellInvenItem(m_InvecIndex);
					m_fTime = 0.f;
				}
			}

			//스왑
			for (size_t i = 0; i < m_vecItem.size(); ++i)
			{
				if (i != m_InvecIndex)
				{
					if (CCollisionMgr::GetInstance()
						->InvenItemSwapCheck(m_vecItem[i],
							vMouse) == true)
					{
						//swap(m_vecItem[i], m_vecItem[m_InvecIndex]);
						SwapItem(m_vecItem[i], m_vecItem[m_InvecIndex]);
					}

					if (CCollisionMgr::GetInstance()
						->ShopSellCheck(m_pUI->GetPShop(),
							vMouse) == true && m_fTime > 0.4f)
					{
						//판매
						SellInvenItem(m_InvecIndex);
						m_fTime = 0.f;
					}
				}

				for (size_t i = 0; i < m_vecItem.size(); ++i)
				{
					m_vecItem[i]->SetOneChangeCheck(false);
					m_vecItem[i]->Initialize();
				}
			}	
		
			m_InvecIndex = INVEN_MAX;		
		}
	}
	
	
	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	//돈
	m_tCoin.vPos.x = m_tInfo.vPos.x + 90.f;
	m_tCoin.vPos.y = m_tInfo.vPos.y + 176.f;

	D3DXMATRIX TransTotal;

	D3DXMatrixTranslation(&TransTotal,
		m_tCoin.vPos.x,
		m_tCoin.vPos.y, 0.f);

	m_tCoin.matWorld = TransTotal;

	if (m_bHpPotion == true || m_bMpPotion == true)
	{
		MyMatrix();
		MyFrame();
	}

	fTime += GET_TIME;
	m_fTime += GET_TIME;

	return 0;

}

void CInven::Render(void)
{
	/*Rectangle(GetDC(g_hWnd), m_rcDragInven.left, m_rcDragInven.top,
		m_rcDragInven.right, m_rcDragInven.bottom);*/

	if (m_bHpPotion == true || m_bMpPotion == true)
	{
		RenderPotionEffect();
	}

	//기본 스테이터스
	const TEX_INFO* pInvenTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str());

	if (pInvenTexture == NULL)
	{
		ERROR_MSG(L"인벤토리 이미지 X");
		return;
	}

	float fX = CENTER_POS(pInvenTexture->ImageInfo.Width);
	float fY = CENTER_POS(pInvenTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pInvenTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Render();
	}

	//가격
	TCHAR szCoin[MIDDLE_STR] = L"";

	wsprintf(szCoin, L"%d", CPlayer::g_iPlayerMoney);


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tCoin.matWorld);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szCoin,
		lstrlen(szCoin),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);



}

void CInven::Release(void)
{
}

CInven::CInven()
{
}


CInven::~CInven()
{
}
