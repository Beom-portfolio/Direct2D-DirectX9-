#include "stdafx.h"
#include "BWHpBar.h"
#include "UIObserver.h"
#include "DataSubject.h"
#include "Device.h"


HRESULT CBWHpBar::Initialize(void)
{
	m_iHp = 0;
	m_tInfo.vPos = D3DXVECTOR3(0, -20, 0);

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->AddObserver(m_pObserver);

	return S_OK;
}

int CBWHpBar::Update(void)
{
	m_iHp = D_CAST(CUIObserver*, m_pObserver)->GetBWUnitData()->iHp;

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);

	matParent = *D_CAST(CUIObserver*, m_pObserver)->GetBWMatrix();

	m_tInfo.matWorld = matTrans * matParent;

	return 0;
}

void CBWHpBar::Render(void)
{
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	TCHAR szHpText[MIDDLE_STR] = L"";

	wsprintf(szHpText, L"HP : %d", m_iHp);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szHpText,
		lstrlen(szHpText),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CBWHpBar::Release(void)
{
	safe_delete(m_pObserver);
}

CBWHpBar::CBWHpBar()
{
}


CBWHpBar::~CBWHpBar()
{
	Release();
}
