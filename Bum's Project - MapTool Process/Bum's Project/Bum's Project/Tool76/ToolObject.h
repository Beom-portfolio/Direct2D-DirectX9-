#pragma once

#include "Include.h"

class CTool76View;
class CToolObject
{
public:
	static bool ObjActiveCheck;
private:
	vector<OBJINFO*>	m_vecObjInfo;
	CTool76View*		m_pMainView;
	OBJINFO*			m_pObj;
	MINISIZE			m_MiniSize;
public:
	void SetMainView(CTool76View* pView)
	{
		m_pMainView = pView;
	}
	void SetDrawID(int DrawID)
	{
		m_pObj->byDrawID = DrawID;
	}
	void SetMiniSize(MINISIZE MiniSize)
	{
		m_MiniSize = MiniSize;
	}
public:
	vector<OBJINFO*>* GetToolObj(void)
	{
		return &m_vecObjInfo;
	}
public:
	HRESULT Initialize(void);
	int     Update(void);
	void	Render(void);
	void	Release(void);

public:
	void MiniMapRender(void);
public:
	void ClickLButton(D3DXVECTOR3& vMousePos);

public:
	CToolObject();
	~CToolObject();
};

