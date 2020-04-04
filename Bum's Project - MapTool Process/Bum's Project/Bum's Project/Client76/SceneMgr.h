#pragma once

#include "Include.h"

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr);
public:
	static bool	m_bHouseCheck;
	static bool m_bFieldCheck;

private:
	CScene*		m_pScene;

private:
	eSceneType  m_eType;
	bool		m_bChangeScene;

public:
	void SetScene(eSceneType eType);
	void SetChangeScene(eSceneType eType);

public:
	eSceneType GetSceneType(void)
	{
		return m_eType;
	}

public:
	HRESULT	Initialize(void);
	int		Update(void);
	void	Render(void);
	void	Release(void);


private:
	CSceneMgr(void);
public:
	~CSceneMgr(void);
};
