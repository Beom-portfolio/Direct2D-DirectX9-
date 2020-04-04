#pragma once
#include "Scene.h"
class CSmithy2 :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CSmithy2();
	virtual ~CSmithy2();
};

