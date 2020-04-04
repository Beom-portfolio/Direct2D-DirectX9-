#pragma once
#include "Bridge.h"


class CEffectBridge :
	public CBridge
{
public:
	virtual HRESULT Initialize(eSkill SkillType);
	virtual int		Update(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEffectBridge();
	virtual ~CEffectBridge();
};

