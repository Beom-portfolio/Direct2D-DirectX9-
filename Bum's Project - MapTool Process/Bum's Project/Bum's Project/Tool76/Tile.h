#pragma once

#include "Include.h"

class CTool76View;
class CTile
{
private:
	vector<TILE*>		m_vecTile;
	CTool76View*		m_pMainView;			//뷰창에 있는 스크롤 정보를 얻어오기 위해서.
	XYCOUNT				m_xyCount;
	MINISIZE			m_MiniSize;

	bool				m_RenderCheck_Text;

public:
	XYCOUNT			GetXYCount(void)
	{
		return m_xyCount;
	}
	vector<TILE*>*	GetTile(void)
	{
		return &m_vecTile;
	}
	MINISIZE		GetMiniSize(void)
	{
		return m_MiniSize;
	}
	bool GetTextRender(void)
	{
		return m_RenderCheck_Text;
	}
public:
	void SetMainView(CTool76View* pView)
	{
		m_pMainView = pView;
	}
	void SetXYCount(XYCOUNT _XY)
	{
		m_xyCount = _XY;
	}
	void SetMiniSize(MINISIZE MiniSize)
	{
		m_MiniSize = MiniSize;
	}
	void SetVecTile(vector<TILE*>* VecTile)
	{
		m_vecTile = *VecTile;
	}
	void SetTextRender(bool check)
	{
		m_RenderCheck_Text = check;
	}
public:
	int		GetTileIndex(const D3DXVECTOR3& vMousePos);
	void	TileChange(const D3DXVECTOR3& vMousePos, const int& iDrawID);

	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);

public:
	HRESULT Initialize(void);
	int     Update(void);
	void	Render(void);
	void	Release(void);

public:
	void MiniMapRender(void);

public:
	CTile(void);
	~CTile(void);
};
