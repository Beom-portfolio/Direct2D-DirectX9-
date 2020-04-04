#include "stdafx.h"
#include "DCHpBar.h"
#include "UIObserver.h"
#include "DataSubject.h"
#include "Device.h"


HRESULT CDCHpBar::Initialize(void)
{
	m_iHp = 0;
	m_tInfo.vPos = D3DXVECTOR3(0, -20, 0);

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->AddObserver(m_pObserver);

	return S_OK;
}

int CDCHpBar::Update(void)
{
	m_iHp = D_CAST(CUIObserver*, m_pObserver)->GetDCUnitData()->iHp;

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);

	matParent = *D_CAST(CUIObserver*, m_pObserver)->GetDCMatrix();

	m_tInfo.matWorld = matTrans * matParent;

	return 0;
}

void CDCHpBar::Render(void)
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

void CDCHpBar::Release(void)
{
	safe_delete(m_pObserver);
}

CDCHpBar::CDCHpBar()
{
}


CDCHpBar::~CDCHpBar()
{
	Release();
}
