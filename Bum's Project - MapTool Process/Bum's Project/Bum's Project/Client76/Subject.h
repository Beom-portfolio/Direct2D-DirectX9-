#pragma once

#include "Include.h"

class CObserver;
class CSubject
{
protected:
	list<CObserver*> m_listObserver;

public:
	//관찰자 등록함수
	virtual void AddObserver(CObserver* pObserver);
	//관찰자 해제함수
	virtual void RemoveObserver(CObserver* pObserver);
	//관찰자들에게 갱신 데이터 알림 함수
	virtual void Notify(int iMessage, void* pData = NULL);

	virtual void Release(void);

public:
	CSubject();
	virtual ~CSubject();
};

