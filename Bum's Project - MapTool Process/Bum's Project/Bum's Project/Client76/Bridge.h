#pragma once

#include "Include.h"

class CGameObject;
class CBridge
{
protected:
	CGameObject* m_pGameObject;

	//브릿지패턴을 이용한 이펙트 출력
	wstring      m_wstrStateKey;
	FRAME		 m_tFrame;

public:
	void SetGameObject(CGameObject* pObject)
	{
		m_pGameObject = pObject;
	}

public:
	virtual HRESULT Initialize(eSkill SkillType)PURE;
	virtual int		Update(INFO& rInfo)PURE;
	virtual void    Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CBridge();
	virtual ~CBridge();
};

