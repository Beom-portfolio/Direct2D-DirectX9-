#include "stdafx.h"
#include "UserInterface.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Damage.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Inven.h"
#include "Shop.h"
#include "Equip.h"
#include "Status.h"

bool CUserInterface::g_YSort = false;

HRESULT CUserInterface::Initialize(void)
{
	m_wstrObjKey = L"STATUS";
	m_wstrStateKey = L"Status";

	m_RenderType = RENDER_UI;

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tHP.vPos = D3DXVECTOR3(99.f, 21.f, 0.f);
	m_tMP.vPos = D3DXVECTOR3(99.f, 38.f, 0.f);

	m_tHP.fCX = 84;
	m_tHP.fCY = 14;
	m_tMP.fCX = 84;
	m_tMP.fCY = 14;

	m_fHP = 1.f;
	m_fMP = 1.f;

	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, m_tHP.fCX, m_tHP.fCY);
	m_rcMP = RectMake(m_tMP.vPos.x, m_tMP.vPos.y, m_tMP.fCX, m_tMP.fCY);

	m_pPlayerData = CObjMgr::GetInstance()->FindGameObject<CPlayer>()->GetUnitData();

	m_iMaxHP = m_pPlayerData->iHp;
	m_iMaxMP = m_pPlayerData->iMp;

	//
	m_pInven = new CInven;
	m_pInven->Initialize();

	m_pShop = new CShop;
	m_pShop->Initialize();

	m_pEquip = new CEquip;
	m_pEquip->Initialize();

	m_pStatus = new CStatus;
	m_pStatus->Initialize();

	return S_OK;
}

int CUserInterface::Update(void)
{
	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	UpdateBar();
	//

	D3DXMATRIX TransSlot;

	D3DXMatrixTranslation(&TransSlot,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y + 500, 0.f);

	m_tSlot.matWorld = TransSlot;

	UpdateBar();

	if (CShop::m_bRenderCheckShop == true)
		m_pShop->Update();

	if (CInven::m_bRenderCheckInven == true)
		m_pInven->Update();

	if (CEquip::m_bRenderCheckEquip == true)
		m_pEquip->Update();

	if (CStatus::m_bRenderCheckStatus == true)
		m_pStatus->Update();

	return 0;
}

void CUserInterface::Render(void)
{
	//기본 스테이터스
	const TEX_INFO* pUITexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str());

	if (pUITexture == NULL)
	{
		ERROR_MSG(L"UI 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pUITexture->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	RenderBar();

	
	const TEX_INFO* pSlotTexture = CTextureMgr::GetInstance()->
		GetTexture(L"QuickSlot");

	if (pSlotTexture == NULL)
	{
		ERROR_MSG(L"UI 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tSlot.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pSlotTexture->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	if (CStatus::m_bRenderCheckStatus == true)
		m_pStatus->Render();

	//
	if (g_YSort == false)
	{
		if (CShop::m_bRenderCheckShop == true)
			m_pShop->Render();

		if (CEquip::m_bRenderCheckEquip == true)
			m_pEquip->Render();

		if (CInven::m_bRenderCheckInven == true)
			m_pInven->Render();
	}
	else
	{
		if (CInven::m_bRenderCheckInven == true)
			m_pInven->Render();
		
		if (CEquip::m_bRenderCheckEquip == true)
			m_pEquip->Render();

		if (CShop::m_bRenderCheckShop == true)
			m_pShop->Render();
	}

}

void CUserInterface::Release(void)
{
}


void CUserInterface::RenderBar(void)
{
	const TEX_INFO* pHPTexture = CTextureMgr::GetInstance()->GetTexture(L"HP", L"Bar");

	if (pHPTexture == NULL)
		return;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tHP.matWorld);
	
	CDevice::GetInstance()->GetSprite()->Draw(
		pHPTexture->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//

	const TEX_INFO* pMPTexture = CTextureMgr::GetInstance()->GetTexture(L"MP", L"Bar");

	if (pMPTexture == NULL)
		return;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tMP.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pMPTexture->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUserInterface::UpdateBar(void)
{
	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, 84, 14);
	m_rcMP = RectMake(m_tMP.vPos.x, m_tMP.vPos.y, 84, 14);

	m_fHP = (float(CPlayer::g_iHp) / CPlayer::g_iMaxHp);
	m_fMP = (float(CPlayer::g_iMp) / CPlayer::g_iMaxMp);

	D3DXMATRIX matTrans, matScale;

	D3DXMatrixTranslation(&matTrans, m_tHP.vPos.x, m_tHP.vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, m_fHP, 1.f, 0.f);

	m_tHP.matWorld = matScale * matTrans;

	//
	D3DXMATRIX matMTrans, matMScale;

	D3DXMatrixTranslation(&matMTrans, m_tMP.vPos.x, m_tMP.vPos.y, 0.f);
	D3DXMatrixScaling(&matMScale, m_fMP, 1.f, 0.f);

	m_tMP.matWorld = matMScale * matMTrans;

}

CUserInterface::CUserInterface()
{
	m_RenderType = RENDER_UI;
}


CUserInterface::~CUserInterface()
{
}
