#include "stdafx.h"
#include "Shop.h"
#include "Item.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "UserInterface.h"
#include "ObjMgr.h"
#include "Inven.h"
#include "Player.h"

bool CShop::m_bRenderCheckShop = false;

HRESULT CShop::Initialize(void)
{
	m_wstrObjKey = L"Shop";
	m_tInfo.vPos = D3DXVECTOR3(250.f, 310.f, 0.f);
	m_tInfo.fCX = 401;
	m_tInfo.fCY = 421;
	
	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);

	m_rcDragShop =
		RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 200.f, 401, 30);
	//
	m_wstrStateKey = L"OKButton";
	m_tOKInfo.vPos.x = m_tInfo.vPos.x + 160.f;
	m_tOKInfo.vPos.y = m_tInfo.vPos.y + 190.f;
	m_tOKInfo.fCX = 32;
	m_tOKInfo.fCY = 14;
	m_rcOKButton = RectMake(m_tOKInfo.vPos.x, m_tOKInfo.vPos.y,
							m_tOKInfo.fCX, m_tOKInfo.fCY);
	m_iButtonframe = 1;


	for (int i = 0; i < 7; ++i)
	{
		CItem* Temp = new CItem(m_tInfo.vPos.x - 5.f,
			m_tInfo.vPos.y,
			static_cast<eInvenIndex>(i),
			static_cast<eItem>(i), true);

		Temp->Initialize();
		m_vecItem.push_back(Temp);
	}

	m_iBuyListCnt = 1;

	m_iBuyTotal = 0;

	return S_OK;
}

int CShop::Update(void)
{
	//위쪽 렉트(인벤을 움직임)
	//
	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);
	m_rcDragShop =
		RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y - 200.f, 401, 30);
	//
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	//충돌
	m_bDragCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rcDragShop, vMouse);

	if (m_bDragCheck == true && GetAsyncKeyState(VK_LBUTTON))
	{
		m_tInfo.vPos.x = vMouse.x;
		m_tInfo.vPos.y = vMouse.y + 200.f;

		CUserInterface::g_YSort = true;
	}

	//
	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i]->RUpdate(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y) == 1)
		{
			if (m_iBuyListCnt < 5)
			{
				CItem* TempItem = new CItem(m_tInfo.vPos.x - 5.f,
					m_tInfo.vPos.y + 180.f,
					static_cast<eInvenIndex>(m_iBuyListCnt),
					m_vecItem[i]->GetItem(), true);
				m_vecBuyList.push_back(TempItem);
				++m_iBuyListCnt;

				m_iBuyTotal += TempItem->GetItemPrice();
			}
		}
	}

	for (size_t i = 0; i < m_vecBuyList.size(); ++i)
	{
		m_vecBuyList[i]->RUpdate(m_tInfo.vPos.x - 5.f, m_tInfo.vPos.y + 180.f);
	}

	//
	if (m_bRenderCheckShop == false)
	{
		vector<CItem*>::iterator iter     = m_vecBuyList.begin();
		vector<CItem*>::iterator iter_end = m_vecBuyList.end();

		for (auto i = iter;i != iter_end;)
		{
			if ((*i) != NULL)
			{
				safe_delete(*i);
				i = m_vecBuyList.erase(i);
				iter_end = m_vecBuyList.end();
			}
			else
				++i;

		}
		m_iBuyListCnt = 1;
		m_iBuyTotal = 0;
	}

	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	//확인
	m_tOKInfo.vPos.x = m_tInfo.vPos.x + 160.f;
	m_tOKInfo.vPos.y = m_tInfo.vPos.y + 190.f;

	m_rcOKButton = RectMake(m_tOKInfo.vPos.x, m_tOKInfo.vPos.y,
		m_tOKInfo.fCX, m_tOKInfo.fCY);


	if (CCollisionMgr::GetInstance()->InvenDragCheckCollisionCheck(m_rcOKButton, vMouse))
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_iButtonframe = 1;
			if (!(m_vecBuyList.empty()))
			{
				//플레이어의 돈이 없으면 사지지 않음
				if (CPlayer::g_iPlayerMoney - m_iBuyTotal < 0)
					return 0;
				
				//구매 
				m_pUI = CObjMgr::GetInstance()->FindGameObject<CUserInterface>();
				CInven*	pInven = D_CAST(CUserInterface*, m_pUI)->GetPInven();

				pInven->AddInvenItem(&m_vecBuyList, m_iBuyTotal);
				m_iBuyListCnt = 1;
				m_iBuyTotal = 0;

				CSoundMgr::GetInstance()->PlaySound(L"ShopResult.wav", CSoundMgr::Channel_Eff);
			}
		}
		else
		{
			m_iButtonframe = 0;
		}
	}
	else
	{
		m_iButtonframe = 0;
	}

	D3DXMATRIX TransOK;

	D3DXMatrixTranslation(&TransOK,
		m_tOKInfo.vPos.x,
		m_tOKInfo.vPos.y, 0.f);

	m_tOKInfo.matWorld = TransOK;

	//총가격
	m_tTotalInfo.vPos.x = m_tInfo.vPos.x - 30.f;
	m_tTotalInfo.vPos.y = m_tInfo.vPos.y + 185.f;

	D3DXMATRIX TransTotal;

	D3DXMatrixTranslation(&TransTotal,
		m_tTotalInfo.vPos.x,
		m_tTotalInfo.vPos.y, 0.f);

	m_tTotalInfo.matWorld = TransTotal;

	return 0;
}

void CShop::Render(void)
{
	/*Rectangle(GetDC(g_hWnd), m_rcDragShop.left, m_rcDragShop.top,
		m_rcDragShop.right, m_rcDragShop.bottom);*/

	//기본 스테이터스
	const TEX_INFO* pShopTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str());

	if (pShopTexture == NULL)
	{
		ERROR_MSG(L"인벤토리 이미지 X");
		return;
	}

	float fX = CENTER_POS(pShopTexture->ImageInfo.Width);
	float fY = CENTER_POS(pShopTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pShopTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	for (size_t i = 0; i < m_vecItem.size(); ++i)
	{
		m_vecItem[i]->Render();
	}

	for (size_t i = 0; i < m_vecBuyList.size(); ++i)
	{
		m_vecBuyList[i]->Render();
	}


	//확인 버튼
	/*Rectangle(GetDC(g_hWnd), m_rcOKButton.left, m_rcOKButton.top,
		m_rcOKButton.right, m_rcOKButton.bottom);*/

	//기본 스테이터스
	const TEX_INFO* pOKTexture = CTextureMgr::GetInstance()->
		GetTexture(L"Interface", m_wstrStateKey.c_str(), m_iButtonframe);

	if (pOKTexture == NULL)
	{
		ERROR_MSG(L"인벤토리 이미지 X");
		return;
	}

	fX = CENTER_POS(pOKTexture->ImageInfo.Width);
	fY = CENTER_POS(pOKTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tOKInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pOKTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);



	
	//가격
	TCHAR szTotalPrice[MIDDLE_STR] = L"";

	wsprintf(szTotalPrice, L"%d", m_iBuyTotal);


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tTotalInfo.matWorld);


	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szTotalPrice,
		lstrlen(szTotalPrice),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

void CShop::Release(void)
{
}

CShop::CShop()
{
}


CShop::~CShop()
{
}
