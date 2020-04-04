#include "stdafx.h"
#include "MonHpBar.h"
#include "Device.h"
#include "TextureMgr.h"

HRESULT CMonHpBar::Initialize(void)
{
	m_wstrObjKey = L"EmptyBar";
	m_fHP = 1.f;

	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, 50, 3);

	m_iMaxHp = m_iHp;

	return S_OK;
}

int CMonHpBar::Update(void)
{
	//사용안함
	return 0;
}

int CMonHpBar::Update(D3DXVECTOR3 Pos, int Hp)
{
	m_tInfo.vPos = D3DXVECTOR3(Pos.x, Pos.y - m_iBottom, Pos.z);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;
	
	//
	D3DXMATRIX matHTrans, matHScale;

	D3DXMatrixScaling(&matHScale, m_fHP, 0.9f, 0.f);
	D3DXMatrixTranslation(&matHTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tHP.matWorld = matHScale * matHTrans;

	float Temp;

	if (m_iMaxHp - m_iHp >= 0.f && m_iHp > 0)
		Temp = 50 - (float(m_iMaxHp - m_iHp) / m_iMaxHp) * 50;
	else
		Temp = 0.f;

	m_rcHP = RectMake(m_tHP.vPos.x, m_tHP.vPos.y, Temp, 3.f);

	return 0;
}

void CMonHpBar::Render(void)
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
		GetTexture(m_wstrObjKey.c_str());

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
		GetTexture(L"MonsterHP");

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

void CMonHpBar::Release(void)
{
}

CMonHpBar::CMonHpBar()
{
}

CMonHpBar::CMonHpBar(D3DXVECTOR3 Pos, int Hp, int Bottom)
{
	m_iHp = Hp;
	m_iBottom = Bottom;
	m_tHP.vPos = D3DXVECTOR3(Pos.x, Pos.y - m_iBottom, Pos.z);
}


CMonHpBar::~CMonHpBar()
{
	Release();
}
