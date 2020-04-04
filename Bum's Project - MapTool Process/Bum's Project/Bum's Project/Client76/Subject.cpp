#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"


void CSubject::AddObserver(CObserver * pObserver)
{
	m_listObserver.push_back(pObserver);
}

void CSubject::RemoveObserver(CObserver * pObserver)
{
	list<CObserver*>::iterator iter = m_listObserver.begin();
	list<CObserver*>::iterator iter_end = m_listObserver.end();

	for (iter; iter != iter_end; )
	{
		if ((*iter) == pObserver)
		{
			iter = m_listObserver.erase(iter);
		}
		else
			++iter;
	}

}

void CSubject::Notify(int iMessage, void * pData)
{
	list<CObserver*>::iterator iter     = m_listObserver.begin();
	list<CObserver*>::iterator iter_end = m_listObserver.end();

	for (iter; iter != iter_end; ++iter)
	{
		(*iter)->Update(iMessage, pData);
	}
}

void CSubject::Release(void)
{
	m_listObserver.clear();
}

CSubject::CSubject()
{
}


CSubject::~CSubject()
{
	Release();
}
