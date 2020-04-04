#pragma once

#include "Include.h"

class CGameObject;
class CBridge
{
protected:
	CGameObject* m_pGameObject;

	//�긴�������� �̿��� ����Ʈ ���
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

