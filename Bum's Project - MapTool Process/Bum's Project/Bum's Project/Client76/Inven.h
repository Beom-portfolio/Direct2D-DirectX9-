#pragma once
#include "UserInterface.h"


class CItem;
class CUserInterface;
class CInven :
	public CUserInterface
{
//º¤ÅÍ·Î ºó ¾ÆÀÌÅÛÄ­ ¸¸µé¾î¾ßÇÔ.
public:
	static bool m_bRenderCheckInven;
private:
	bool		m_bDragCheck;
	RECT		m_rcDragInven;
	eInvenIndex m_InvecIndex;
	float		fTime;
private:
	bool		m_bHpPotion;
	bool		m_bMpPotion;
	FRAME		m_tPotionFrame;
	INFO		m_tPotion;
private:
	INFO		m_tCoin;
private:
	vector<CItem*> m_vecItem;
private:
	CUserInterface * m_pUI;
public:
	void	MyMatrix(void);
	void	MyFrame(void);
	void    RenderPotionEffect(void);
	void    AddInvenItem(vector<CItem*> *vecItem, int Cost);
	void    AddUnEquipItem(eItem ItemType);
	void    SellInvenItem(eInvenIndex InvenIndex);
	void	EquipInvenItem(eInvenIndex InvenIndex);
	void    SetInvenIndex(eInvenIndex Index)
	{
		m_InvecIndex = Index;
	}
	void    SwapItem(CItem *A, CItem *B);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CInven();
	virtual ~CInven();
};

