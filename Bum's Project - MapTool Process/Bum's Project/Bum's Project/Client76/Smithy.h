#pragma once
#include "Scene.h"
class CSmithy :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CSmithy();
	virtual ~CSmithy();
};

