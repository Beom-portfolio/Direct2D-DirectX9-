#pragma once
#include "GameObject.h"

#include "Include.h"

class CTest :
	public CGameObject
{
private:
	wstring m_wstrStateKey;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

private:
	void MyMatrixCheck(void);
	void KeyCheck(void);
	void AStarMove(void);
public:
	CTest();
	virtual ~CTest();
};

