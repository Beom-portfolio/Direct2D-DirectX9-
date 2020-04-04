#pragma once

#include "Include.h"

class CTool76View;
class Monster
{
public:
	static bool MonActiveCheck;
private:
	vector<MONINFO*>	m_vecMonInfo;
	CTool76View*		m_pMainView;
	MONINFO*			m_pMon;
	MINISIZE			m_MiniSize;
public:
	void SetMainView(CTool76View* pView)
	{
		m_pMainView = pView;
	}
	void SetDrawID(int DrawID)
	{
		m_pMon->byDrawID = DrawID;
	}
	void SetMiniSize(MINISIZE MiniSize)
	{
		m_MiniSize = MiniSize;
	}
public:
	vector<MONINFO*>* GetToolMon(void)
	{
		return &m_vecMonInfo;
	}
public:
	HRESULT Initialize(void);
	int     Update(void);
	void	Render(void);
	void	Release(void);

public:
	void MiniMapRender(void);
public:
	void ClickLButton(D3DXVECTOR3 & vMousePos);

public:
	Monster();
	~Monster();
};

