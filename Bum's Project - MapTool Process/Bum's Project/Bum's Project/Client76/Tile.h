#pragma once
#include "GameObject.h"
class Tile :
	public CGameObject
{
private:
	vector<TILE*>		m_vecTile;
	const TEX_INFO*     m_pTileTex;
	XYCOUNT				m_BackCount;
	POINT				m_ptTileRender;
private:
	wstring				m_wstrStateKey;

public:
	static bool			m_RenderCheck;
	static XYCOUNT		g_BackCount;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	const vector<TILE*>*	GetTile(void)
	{
		return &m_vecTile;
	}
	const XYCOUNT	GetTileCount(void)
	{
		return m_BackCount;
	}

public:
	void KeyInput(void);
	void LoadTile(void);
	void MouseScrollCheck(void);

public:
	Tile();
	virtual ~Tile();
};

