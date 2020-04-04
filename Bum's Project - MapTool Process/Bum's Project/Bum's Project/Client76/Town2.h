#pragma once
#include "Scene.h"
class CTown2 :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CTown2();
	virtual ~CTown2();
};

