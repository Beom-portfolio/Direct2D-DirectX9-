#pragma once
#include "scene.h"
#include "Include.h"
class CLogo :
	public CScene
{
private:
	HANDLE			 m_hThread;
	CRITICAL_SECTION m_Crt;
private:
	static unsigned int __stdcall ImageLoadThreadFunc(void* pArg);
	CRITICAL_SECTION GetCrt(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CLogo(void);
	virtual ~CLogo(void);
};
