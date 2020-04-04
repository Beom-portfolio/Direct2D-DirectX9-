#include "stdafx.h"
#include "JHpBar.h"
#include "UIObserver.h"
#include "DataSubject.h"
#include "Device.h"

HRESULT JHpBar::Initialize(void)
{
	m_iHp = 0;
	m_tInfo.vPos = D3DXVECTOR3(0, -20, 0);

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->AddObserver(m_pObserver);

	return S_OK;
}

int JHpBar::Update(void)
{
	m_iHp = D_CAST(CUIObserver*, m_pObserver)->GetJUnitData()->iHp;

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);

	matParent = *D_CAST(CUIObserver*, m_pObserver)->GetJMatrix();

	m_tInfo.matWorld = matTrans * matParent;

	return 0;
}

void JHpBar::Render(void)
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

void JHpBar::Release(void)
{
	safe_delete(m_pObserver);
}

JHpBar::JHpBar()
{
}


JHpBar::~JHpBar()
{
	Release();
}
