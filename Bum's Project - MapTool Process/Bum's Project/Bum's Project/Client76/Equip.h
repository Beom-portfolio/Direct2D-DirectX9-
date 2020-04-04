#pragma once
#include "UserInterface.h"


class CItem;
class CUserInterface;
class CEquip :
	public CUserInterface
{
public:
	static bool m_bRenderCheckEquip;
private:
	bool		m_bDragCheck;
	RECT		m_rcDragEquip;
	eEquipIndex	m_EquipIndex;
	float		fTime;
private:
	vector<CItem*> m_vecEquipItem;
private:
	CUserInterface *m_pUI;
public:
	void    AddEquipItem(eItem ItemType);
public:
	void	SetEquipIndex(eEquipIndex Index)
	{
		m_EquipIndex = Index;
	}
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void UnEquipItem(eEquipIndex EquipIndex, eItem ItemType);
public:
	CEquip();
	virtual ~CEquip();
};

