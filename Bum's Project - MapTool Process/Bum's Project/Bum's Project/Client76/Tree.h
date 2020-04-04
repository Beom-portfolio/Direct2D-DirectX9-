#pragma once
#include "GameObject.h"
class CTree :
	public CGameObject
{
private:
	vector<OBJINFO*>	m_vecTree;
	vector<OBJINFO*>    m_vecTree_Back;
	const OBJINFO*		m_pTree;

private:
	RECT m_testrc;

private:
	wstring				m_wstrStateKey;
	static bool			m_RenderCheck;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void YSorting(void);
	void AlpaCheck(void);
	void RenderBack(void);
	void LoadTree(void); 
	
public:
	CTree();
	virtual ~CTree();
};

