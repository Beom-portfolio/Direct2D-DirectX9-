#pragma once

#include "Include.h"

class CObserver abstract
{
public:
	//iMessage : �����ϴ� ������Ÿ���� �����ϴ� �ɼ�
	virtual void Update(int iMessage, void* pData)PURE;

public:
	CObserver();
	virtual ~CObserver();
};

