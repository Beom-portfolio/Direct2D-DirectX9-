#include "stdafx.h"
#include "RenderMgr.h"
#include "GameObject.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "Tree.h"

IMPLEMENT_SINGLETON(CRenderMgr);

void CRenderMgr::AddObject(CGameObject * pObject, eRenderType eType)
{
	m_vecObjectRender[eType].push_back(pObject);
}

void CRenderMgr::YSort(void)
{
	
}

void CRenderMgr::Erase(void)
{

}

void CRenderMgr::Render(void)
{
	/*sort(m_vecObjectRender[RENDER_WORLD].begin()
		, m_vecObjectRender[RENDER_WORLD].end()
		, CRenderMgr::Compare);*/

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		int iMaxSize = m_vecObjectRender[i].size();

		/*if (i == RENDER_EFFECT)
		{
			if (m_vecObjectRender[RENDER_EFFECT].empty() == m_vecObjectRender[i].empty())
				continue;
		}*/

		for (int j = 0; j < iMaxSize; ++j)
		{
			m_vecObjectRender[i][j]->Render();
			//i : Type
			//j : 객체 수
		}

		m_vecObjectRender[i].clear();
	}
}

bool CRenderMgr::Compare(CGameObject * pObj1, CGameObject * pObj2)
{
	//조건문
	//pObj1 : 플레이어
	//pObj2 : 몬스터

	//pObj2->

	return true;
}

CRenderMgr::CRenderMgr()
	:m_pPlayer(NULL)
	,m_pMonster(NULL)
{
}


CRenderMgr::~CRenderMgr()
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_vecObjectRender[i].clear();
	}
}
