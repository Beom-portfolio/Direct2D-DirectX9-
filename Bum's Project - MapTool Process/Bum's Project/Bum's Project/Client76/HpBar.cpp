#include "stdafx.h"
#include "HpBar.h"
#include "UIObserver.h"
#include "DataSubject.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Player.h"

HRESULT CHpBar::Initialize(void)
{
	m_iHp = 0;
	m_tInfo.vPos = D3DXVECTOR3(0, 20, 0);
	m_tHP.vPos = D3DXVECTOR3(0, 18, 0);

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->AddObserver(m_pObserver);

	m_wstrObjKey = L"Small";
	m_wstrStateKey = L"Bar";

	m_fHP = 1.f;

	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, 50, 3);

	return S_OK; 
}

int CHpBar::Update(void)
{
	m_iHp = CPlayer::g_iHp;

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);
	
	matParent = *D_CAST(CUIObserver*, m_pObserver)->GetMatrix();

	m_tInfo.matWorld = matTrans * matParent;
	//
	D3DXMATRIX matHTrans, matHScale,  matHParent;

	D3DXMatrixScaling(&matHScale, m_fHP, 1.f, 0.f);
	D3DXMatrixTranslation(&matHTrans,
		m_tHP.vPos.x,
		m_tHP.vPos.y,
		0.f);

	matHParent = *D_CAST(CUIObserver*, m_pObserver)->GetMatrix();

	m_tHP.matWorld = matHScale * matHTrans * matHParent;

	float Temp;
	
	if (CPlayer::g_iMaxHp - m_iHp >= 0 && m_iHp > 0)
		Temp = 50 - (float(CPlayer::g_iMaxHp - m_iHp) / CPlayer::g_iMaxHp) * 50;
	else
		Temp = 0.f;

	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, Temp, 3);

	return 0;
}

void CHpBar::Render(void)
{
	/*CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	TCHAR szHpText[MIDDLE_STR] = L"";

	wsprintf(szHpText, L"HP : %d", m_iHp);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szHpText,
		lstrlen(szHpText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);*/
	const TEX_INFO* pUITexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str());

	if (pUITexture == NULL)
	{
		ERROR_MSG(L"UI 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	
	float fX = CENTER_POS(pUITexture->ImageInfo.Width);
	float fY = CENTER_POS(pUITexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pUITexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	const TEX_INFO* pHTexture = CTextureMgr::GetInstance()->
		GetTexture(L"SmallHP");

	if (pUITexture == NULL)
	{
		ERROR_MSG(L"UI 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tHP.matWorld);

	fX = CENTER_POS(pHTexture->ImageInfo.Width);
	fY = CENTER_POS(pHTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pHTexture->pTexture,
		&m_rcHP,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CHpBar::Release(void)
{
	CDataSubject::GetInstance()->RemoveObserver(m_pObserver);
	safe_delete(m_pObserver);
}

CHpBar::CHpBar()
{
}


CHpBar::~CHpBar()
{
	Release();
}
