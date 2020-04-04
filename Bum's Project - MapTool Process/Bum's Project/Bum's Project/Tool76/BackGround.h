#pragma once

#include "Include.h"

class CTool76View;
class CBackGround
{
private:
	vector<BACK*>		m_vecBack;
	CTool76View*		m_pMainView;
	eStageType			m_Back_Type;
	TCHAR				*szBackType;
	int					iBackType;
	MINISIZE            m_MiniSize;

public:
	void SetMainView(CTool76View* pView)
	{
		m_pMainView = pView; 
	}
	void SetStageType(eStageType pType)
	{
		m_Back_Type = pType;
	}
	
	void SetStageTypeFromLoad(int	iBackType);

	void SetMiniSize(MINISIZE MiniSize)
	{
		m_MiniSize = MiniSize;
	}
public:
	vector<BACK*>*	GetBackGround(void)
	{
		return &m_vecBack;
	}
	TCHAR*			GetBackType(void)
	{
		return szBackType;
	}
	int			GetBackIntType(void)
	{
		return iBackType;
	}
public:
	HRESULT Initialize(void);
	int     Update(void);
	void	Render(void);
	void	Release(void);

public:
	void MiniMapRender(void);

public:
	CBackGround(void);
	~CBackGround(void);
};
