#pragma once

#include "Include.h"

class CAStar
{
	//DECLARE_SINGLETON(CAStar);

private:
	list<NODE*>		m_OpenList;			//조사할대상
	list<NODE*>		m_CloseList;		//조사한대상
	list<int>		m_BestList;			//가야할 최단 경로.

private:
	int		m_iStartIndex;
	int		m_iEndIndex;

public:
	list<int>* GetBestList(void)
	{
		return &m_BestList;
	}

public:
	void AStarStartPos(const D3DXVECTOR3& vStartPos
		, const D3DXVECTOR3& vEndPos);
	void AStarStart(const int& iStartIndex
				  , const int& iEndIndex);
	void MakeRoute(void);
	NODE* MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pTile);
	bool ListCheck(const int& iIndex);

	void Release(void);

public:
	bool Picking(const D3DXVECTOR3& vPos, const TILE* pTile);
	int  GetTileIndex(const D3DXVECTOR3& vPos);

public:
	static bool Compare(const NODE* pNode1, const NODE* pNode2);

public:
	CAStar();
	~CAStar();
};

