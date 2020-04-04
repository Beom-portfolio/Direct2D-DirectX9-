#pragma once
#include "Observer.h"
class CUIObserver :
	public CObserver
{
private:
	UNIT_DATA	m_tData;
	D3DXMATRIX  m_matMatrix;

public:
	const UNIT_DATA*  GetUnitData(void);
	const D3DXMATRIX* GetMatrix(void);

public:
	virtual void Update(int iMessage, void* pData);

public:
	CUIObserver();
	virtual ~CUIObserver();
};

