#pragma once

#include "Include.h"

class CObserver;
class CSubject
{
protected:
	list<CObserver*> m_listObserver;

public:
	//������ ����Լ�
	virtual void AddObserver(CObserver* pObserver);
	//������ �����Լ�
	virtual void RemoveObserver(CObserver* pObserver);
	//�����ڵ鿡�� ���� ������ �˸� �Լ�
	virtual void Notify(int iMessage, void* pData = NULL);

	virtual void Release(void);

public:
	CSubject();
	virtual ~CSubject();
};

