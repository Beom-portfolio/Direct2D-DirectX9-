#pragma once
#include "GameObject.h"

#include "Include.h"


class CObserver;
class CInven;
class CShop;
class CEquip;
class CStatus;
class CUserInterface
	:public CGameObject
{
public:
	static bool g_YSort;
protected:
	CObserver*		m_pObserver;

protected:
	wstring			m_wstrStateKey;
	INFO			m_tHP;
	INFO			m_tMP;
	
	/*INFO		m_tSmall;
	INFO		m_tSHP;
	INFO		m_tSMP;*/

	float       m_fHP;
	float		m_fMP;

	RECT		m_rcHP;
	RECT		m_rcMP;

	int			m_iMaxHP;
	int			m_iMaxMP;

	UNIT_DATA   *m_pPlayerData;

private:
	CInven		*m_pInven;
	CShop		*m_pShop;
	CEquip      *m_pEquip;
	CStatus		*m_pStatus;
private:
	INFO		m_tSlot;
public:
	CInven*		GetPInven(void)
	{
		return m_pInven;
	}
	CShop*		GetPShop(void)
	{
		return m_pShop;
	}
	CEquip*		GetPEquip(void)
	{
		return m_pEquip;
	}

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	void RenderBar(void);
	void UpdateBar(void);

public:
	CUserInterface();
	virtual ~CUserInterface();
};

