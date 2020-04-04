#include "stdafx.h"
#include "EffectBridge.h"
#include "TextureMgr.h"
#include "GameObject.h"
#include "Device.h"


HRESULT CEffectBridge::Initialize(eSkill SkillType)
{
	return S_OK;
}

int CEffectBridge::Update(INFO & rInfo)
{
	return 0;
}

void CEffectBridge::Render(void)
{
	const TEX_INFO* pEffectTexture
		= CTextureMgr::GetInstance()->GetTexture(
			m_pGameObject->GetObjKey().c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pEffectTexture == NULL)
		return;

	float fX = CENTER_POS(pEffectTexture->ImageInfo.Width);
	float fY = CENTER_POS(pEffectTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(
			&m_pGameObject->GetInfo()->matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pEffectTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(210, 255, 255, 255)
	);
}

void CEffectBridge::Release(void)
{
}

CEffectBridge::CEffectBridge()
{
}


CEffectBridge::~CEffectBridge()
{
	Release();
}
