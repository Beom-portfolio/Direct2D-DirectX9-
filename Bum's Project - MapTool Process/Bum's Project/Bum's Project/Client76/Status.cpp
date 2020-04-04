#include "stdafx.h"
#include "Status.h"
#include "Item.h"
#include "TimeMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Equip.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "GameObject.h"

bool CStatus::m_bRenderCheckStatus = false;

HRESULT CStatus::Initialize(void)
{
	m_wstrObjKey = L"Status";

	m_tInfo.vPos = D3DXVECTOR3(170.f, 150.f, 0.f);
	m_tInfo.fCX = 345;
	m_tInfo.fCY = 305;

	m_fTime = 0.f;

	return S_OK;
}

int CStatus::Update(void)
{
	m_pUI = CObjMgr::GetInstance()->FindGameObject<CUserInterface>();

	D3DXMATRIX Trans;

	D3DXMatrixTranslation(&Trans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = Trans;

	UpdateFont();

	m_fTime += GET_TIME;

	return 0;
}

void CStatus::Render(void)
{
	const TEX_INFO* pStatusTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str());

	if (pStatusTexture == NULL)
	{
		ERROR_MSG(L"½ºÅÝ ÀÌ¹ÌÁö X");
		return;
	}

	float fX = CENTER_POS(pStatusTexture->ImageInfo.Width);
	float fY = CENTER_POS(pStatusTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(
		pStatusTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	RenderFont();
}

void CStatus::Release(void)
{
}

void CStatus::UpdateFont(void)
{
	D3DXMATRIX Trans_L;

	D3DXMatrixTranslation(&Trans_L,
		m_tInfo.vPos.x + 45.f,
		m_tInfo.vPos.y - 120.f, 0.f);

	m_tLevel.matWorld = Trans_L;

	//
	D3DXMATRIX Trans_N;

	D3DXMatrixTranslation(&Trans_N,
		m_tInfo.vPos.x + 45.f,
		m_tInfo.vPos.y - 100.f, 0.f);

	m_tName.matWorld = Trans_N;

	//
	D3DXMATRIX Trans_A;

	D3DXMatrixTranslation(&Trans_A,
		m_tInfo.vPos.x - 120.f,
		m_tInfo.vPos.y + 25.f, 0.f);

	m_tAtt.matWorld = Trans_A;

	//
	D3DXMATRIX Trans_D;

	D3DXMatrixTranslation(&Trans_D,
		m_tInfo.vPos.x - 120.f,
		m_tInfo.vPos.y + 45.f, 0.f);

	m_tDef.matWorld = Trans_D;

	//
	D3DXMATRIX Trans_H;

	D3DXMatrixTranslation(&Trans_H,
		m_tInfo.vPos.x + 40.f,
		m_tInfo.vPos.y + 25.f, 0.f);

	m_tHp.matWorld = Trans_H;

	//
	D3DXMATRIX Trans_M;

	D3DXMatrixTranslation(&Trans_M,
		m_tInfo.vPos.x + 40.f,
		m_tInfo.vPos.y + 45.f, 0.f);

	m_tMp.matWorld = Trans_M;
}

void CStatus::RenderFont(void)
{
	TCHAR szInfoText[MIDDLE_STR] = L"";

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tLevel.matWorld);

	wsprintf(szInfoText, L"%d", CPlayer::g_iLevel);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tName.matWorld);

	wsprintf(szInfoText, L"76±â ±è½Â¹ü");

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tAtt.matWorld);

	wsprintf(szInfoText, L"%d", CPlayer::g_iAtt);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tDef.matWorld);

	wsprintf(szInfoText, L"%d", CPlayer::g_iDef);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tHp.matWorld);

	wsprintf(szInfoText, L"%d/%d", CPlayer::g_iHp, CPlayer::g_iMaxHp);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tMp.matWorld);

	wsprintf(szInfoText, L"%d/%d", CPlayer::g_iMp, CPlayer::g_iMaxMp);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szInfoText,
		lstrlen(szInfoText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

CStatus::CStatus()
{
}


CStatus::~CStatus()
{
}
