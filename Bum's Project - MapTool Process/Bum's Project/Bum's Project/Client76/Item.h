#pragma once
#include "GameObject.h"

class CItem :
	public CGameObject
{
private:
	float	m_fFar;
	bool    m_bShopItemCheck;
	bool	m_bEquipItemCheck;
	bool	m_bDragCheck;
	bool    m_bClickCheck;
	bool    m_bRClickCheck;
	bool    m_bOneChangeCheck;
	eInvenIndex m_eIndex;
	eEquipIndex m_eEquipIndex;
	eItem		m_eItemType;
private:
	int			m_iItemPrice;
	wstring		m_wstrItemPrice;
private:
	D3DXVECTOR3	 m_OriginPos;
public:
	bool		GetClickCheck(void)
	{
		return m_bClickCheck;
	}
	eInvenIndex GetIndex(void)
	{
		return m_eIndex;
	}
	eEquipIndex GetEquipIndex(void)
	{
		return m_eEquipIndex;
	}
	eItem		GetItem(void)
	{
		return m_eItemType;
	}
	int			GetItemPrice(void)
	{
		return m_iItemPrice;
	}
public:
	void SetOneChangeCheck(bool Check)
	{
		m_bOneChangeCheck = Check;
	}
	void SetItemType(eItem	Item)
	{
		m_eItemType = Item;
	}
	void SetIndexType(eInvenIndex	Index)
	{
		m_eIndex = Index;
	}
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	int		Update(D3DXVECTOR3 vPos);
	int     RUpdate(float vPosX, float vPosY);
	void	ItemType(void);
	void	IndexType(void);
	void    EquipIndexType(void);
public:
	CItem();
	CItem(D3DXVECTOR3 vPos, eInvenIndex Index,
		eItem Item);
	CItem(float vPosX, float vPosY, eInvenIndex Index,
		eItem Item, bool ShopItemCheck);
	CItem(float vPosX, float vPosY, eEquipIndex Index,
		eItem Item, bool ShopItemCheck);
	virtual ~CItem();
};

