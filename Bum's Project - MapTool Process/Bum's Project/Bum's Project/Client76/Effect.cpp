#include "stdafx.h"
#include "Effect.h"
#include "Bridge.h"
#include "EffectBuffer.h"

HRESULT CEffect::Initialize(void)
{
	if (m_pBridge)
		m_pBridge->SetGameObject(this);

	m_wstrObjKey = L"Player Skill";

	m_RenderType = RENDER_EFFECT;

	return S_OK;
}
int CEffect::Update(void)
{
	int iResult = 0;

	if (m_pBridge)
		iResult = m_pBridge->Update(m_tInfo);

	if (iResult == 1)
		return 1;

	if (CEffectBuffer::g_bAllSkillCheck == true)
		m_RenderType = RENDER_BACKGROUND;
	else
		m_RenderType = RENDER_EFFECT;

	return 0;
}

void CEffect::Render(void)
{
	if (m_pBridge)
		m_pBridge->Render();
}

void CEffect::Release(void)
{
	safe_delete(m_pBridge);
}

CEffect::CEffect()
{
	m_pBridge = NULL;
}


CEffect::~CEffect()
{
	Release();
}
