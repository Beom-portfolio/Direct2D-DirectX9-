#pragma once

#include "Effect.h"

template<typename T>
class CEffectFactory abstract
{
public:
	static CGameObject* CreateEffect(eSkill SkillType)
	{
		CGameObject* pEffect = new CEffect;

		CBridge*     pBridge = new T;

		D_CAST(CEffect*, pEffect)->SetBridge(pBridge);

		pEffect->Initialize();
		pBridge->Initialize(SkillType);

		return pEffect;
	}
};

