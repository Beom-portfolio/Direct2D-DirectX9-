#pragma once
#include "Scene.h"
class CTown :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CTown();
	virtual ~CTown();
};

