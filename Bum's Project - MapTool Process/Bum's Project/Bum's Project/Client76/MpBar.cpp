#include "stdafx.h"
#include "MpBar.h"
#include "UiObserver.h"
#include "DataSubject.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Player.h"

HRESULT CMpBar::Initialize(void)
{
	m_iMp = 0;
	m_tInfo.vPos = D3DXVECTOR3(0, 0, 0);
	m_tMP.vPos = D3DXVECTOR3(0, 22, 0);

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->AddObserver(m_pObserver);

	m_fMP = 1.f;

	m_rcMP = RectMake(m_tMP.vPos.x, m_tMP.vPos.y, 50, 3);

	return S_OK;
}

int CMpBar::Update(void)
{
	m_iMp = CPlayer::g_iMp;

	D3DXMATRIX matTrans, matScale, matParent;

	D3DXMatrixScaling(&matScale, m_fMP, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tMP.vPos.x,
		m_tMP.vPos.y,
		0.f);

	matParent = *D_CAST(CUIObserver*,m_pObserver)->GetMatrix();

	m_tMP.matWorld = matScale * matTrans * matParent;

	float Temp = 50 - (float(CPlayer::g_iMaxMp - m_iMp) / CPlayer::g_iMaxMp) * 50;

	m_rcMP = RectMake(m_tMP.vPos.x, m_tMP.vPos.y, Temp, 3);

	return 0;
}

void CMpBar::Render(void)
{
	/*CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	TCHAR szMpText[MIDDLE_STR] = L"";

	wsprintf(szMpText, L"MP : %d", m_iMp);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szMpText,
		lstrlen(szMpText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);*/
	const TEX_INFO* pMTexture = CTextureMgr::GetInstance()->
		GetTexture(L"SmallMP");

	if (pMTexture == NULL)
	{
		ERROR_MSG(L"UI ÀÌ¹ÌÁö X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tMP.matWorld);

	float fX = CENTER_POS(pMTexture->ImageInfo.Width);
	float fY = CENTER_POS(pMTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pMTexture->pTexture,
		&m_rcMP,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CMpBar::Release(void)
{
	CDataSubject::GetInstance()->RemoveObserver(m_pObserver);
	safe_delete(m_pObserver);
}

CMpBar::CMpBar()
{
}


CMpBar::~CMpBar()
{
	Release();
}
