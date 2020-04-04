#pragma once

#include "Include.h"

class CObserver abstract
{
public:
	//iMessage : 구독하는 데이터타입을 지정하는 옵션
	virtual void Update(int iMessage, void* pData)PURE;

public:
	CObserver();
	virtual ~CObserver();
};

