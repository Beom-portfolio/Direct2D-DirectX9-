#pragma once
#include "UserInterface.h"

class CUserInterface;
class CItem;
class CShop :
	public CUserInterface
{
private:
	CUserInterface    *m_pUI;
private:
	bool		m_bDragCheck;
	RECT		m_rcDragShop;
private:
	vector<CItem*>	 m_vecItem;
	vector<CItem*>   m_vecBuyList;
private:
	INFO		     m_tTotalInfo;
	int				 m_iBuyListCnt;
	int				 m_iBuyTotal;
private:
	INFO		m_tOKInfo;
	RECT		m_rcOKButton;
	int			m_iButtonframe;
public:
	static bool m_bRenderCheckShop;
public:
	vector<CItem*>*	 GetvecBuyList(void)
	{
		return &m_vecBuyList;
	}
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CShop();
	virtual ~CShop();
};

