#include "StdAfx.h"
#include "ObjMgr.h"
#include "GameObject.h"
#include "RenderMgr.h"
#include "Tile.h"
#include "DataSubject.h"
#include "Subject.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CObjMgr);

void CObjMgr::LoadItemData(void)
{

}

void CObjMgr::AddGameObject(CGameObject* pObject, eObjectType eType)
{
	m_ObjList[eType].push_back(pObject);
}

list<CGameObject*>* CObjMgr::GetList(void)
{
	return m_ObjList;
}

const vector<TILE*>* CObjMgr::GetTile(void)
{
	return dynamic_cast<Tile*>
		(m_ObjList[OBJ_TYPE_TILE].front())->GetTile();
}

HRESULT CObjMgr::Initialize(void)
{
	return S_OK;
}

int CObjMgr::Update(void)
{
	for(size_t i = 0; i < OBJ_TYPE_MAX; ++i)
	{
		list<CGameObject*>::iterator iter = m_ObjList[i].begin();
		list<CGameObject*>::iterator iter_end = m_ObjList[i].end();

		for(iter; iter != iter_end; )
		{
			if( (*iter)->Update() == 1 )
			{
				safe_delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				CRenderMgr::GetInstance()->AddObject((*iter), (*iter)->GetRenderType());
				++iter;
			}
		}
	}

	return 0;
}

void CObjMgr::Render(void)
{
	for(size_t i = 0; i < OBJ_TYPE_MAX; ++i)
	{
		list<CGameObject*>::iterator iter     = m_ObjList[i].begin();
		list<CGameObject*>::iterator iter_end = m_ObjList[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render();
		}
	}
}

void CObjMgr::Release(void)
{
	for(size_t i = 0; i < OBJ_TYPE_UI; ++i)
	{
		list<CGameObject*>::iterator iter = m_ObjList[i].begin();
		list<CGameObject*>::iterator iter_end = m_ObjList[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			safe_delete(*iter);
		}
		m_ObjList[i].clear();
	}
	
	CDataSubject::GetInstance()->Release();
}

void CObjMgr::Release(eObjectType eType)
{
	for(size_t i = 0; i < OBJ_TYPE_MAX; ++i)
	{
		list<CGameObject*>::iterator iter = m_ObjList[i].begin();
		list<CGameObject*>::iterator iter_end = m_ObjList[i].end();

		if(eType == i)
			continue;

		for(iter; iter != iter_end; ++iter)
		{
			safe_delete(*iter);
		}
		m_ObjList[i].clear();
	}
}

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}
