#pragma once

#include "Include.h"

class CMonster;
class CPlayer;
class CGameObject;
class CRenderMgr
{
	DECLARE_SINGLETON(CRenderMgr);
private:
	vector<CGameObject*>	m_vecObjectRender[RENDER_END];

private:
	CPlayer*				m_pPlayer;
	CMonster*				m_pMonster;

public:
	void AddObject(CGameObject* pObject, eRenderType eType);

public:
	void YSort(void);
	void Erase(void);
	void Render(void);

private:
	static bool Compare(CGameObject* pObj1, CGameObject* pObj2);

private:
	CRenderMgr();
public:
	~CRenderMgr();
};

