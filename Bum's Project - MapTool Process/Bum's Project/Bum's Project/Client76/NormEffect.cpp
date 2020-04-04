#include "stdafx.h"
#include "NormEffect.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

HRESULT CNormEffect::Initialize(void)
{
	m_RenderType = RENDER_EFFECT;

	m_wstrObjKey = L"Effect";

	switch (m_eEffectType)
	{
	case EFFECT_PLAYER:
		m_wstrStateKey = L"MagicHit";
		m_tFrame = FRAME(0, 4.f, 4.f);
		break;
	case EFFECT_MONSTER:
		m_wstrStateKey = L"MonsterHit";
		m_tFrame = FRAME(0, 4.f, 4.f);
		break;
	}

	return S_OK;
}

int CNormEffect::Update(void)
{
	return 0;
}

int CNormEffect::Update(D3DXVECTOR3 Pos)
{
	MyMetrixCheck(Pos);
	if(MyFrameCheck() == 1)
	{
		m_fTime += GET_TIME;
		return 1;
	}
	else
	{
		m_fTime += GET_TIME;
		return 0;
	}

}

void CNormEffect::MyMetrixCheck(D3DXVECTOR3 Pos)
{
	m_tInfo.vPos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);

	D3DXMATRIX matTrans, matScale;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y - 20.f,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;
}

int CNormEffect::MyFrameCheck(void)
{
	m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * 2.5f;

	if (m_tFrame.fIndex >= m_tFrame.fMax)
	{
		m_tFrame.fIndex = 0.f;
		return 0;
	}
	else
	{
		return 1;
	}
}

void CNormEffect::Render(void)
{
	const TEX_INFO* pDmgEffectTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pDmgEffectTexture == NULL)
	{
		ERROR_MSG(L"이펙트 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	float fX = CENTER_POS(pDmgEffectTexture->ImageInfo.Width);
	float fY = CENTER_POS(pDmgEffectTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pDmgEffectTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CNormEffect::Release(void)
{
}

CNormEffect::CNormEffect()
{
}

CNormEffect::CNormEffect(D3DXVECTOR3 Pos, eEffectType EffectType)
{
	m_tInfo.vPos = Pos;
	m_eEffectType = EffectType;
}


CNormEffect::~CNormEffect()
{
}
