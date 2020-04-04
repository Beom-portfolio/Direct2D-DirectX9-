#include "stdafx.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "SceneMgr.h"

//IMPLEMENT_SINGLETON(CAStar);

CAStar::CAStar()
{
}


CAStar::~CAStar()
{
	Release();
}

void CAStar::AStarStartPos(const D3DXVECTOR3 & vStartPos
						   ,const D3DXVECTOR3 & vEndPos)
{
	m_iStartIndex = GetTileIndex(vStartPos);
	m_iEndIndex = GetTileIndex(vEndPos);

	AStarStart(m_iStartIndex, m_iEndIndex);
}

void CAStar::AStarStart(const int & iStartIndex, const int & iEndIndex)
{
	if (iStartIndex == iEndIndex)
		return;

	const vector<TILE*>* pVecTile
		= CObjMgr::GetInstance()->FindGameObject<Tile>()->GetTile();

	if (pVecTile == NULL)
		return;

	if (iEndIndex == -1)
		return;

	if ((*pVecTile)[iEndIndex]->byOption == 1)
		return;

	Release();

	MakeRoute();
}

void CAStar::MakeRoute(void)
{
	XYCOUNT BackCount = Tile::g_BackCount;

	NODE* pFirstNode = new NODE;

	pFirstNode->iIndex = m_iStartIndex;

	pFirstNode->pParent = NULL;

	pFirstNode->fCost = 0.f;

	m_CloseList.push_back(pFirstNode);

	const vector<TILE*>* pVecTile
		= CObjMgr::GetInstance()->FindGameObject<Tile>()->GetTile();

	if (pVecTile == NULL)
		return;

	NODE* pMakeNode = NULL;
	int   iIndex = 0;

	while (true)
	{
		int TILEX = BackCount.iXCount;
		int TILEY = BackCount.iYCount;

		//##위쪽 타일
		iIndex = pFirstNode->iIndex - TILEX * 2;

		if (pFirstNode->iIndex >= TILEX * 2 &&
			((*pVecTile)[iIndex]->byOption ==  0||
			(*pVecTile)[iIndex]->byOption  ==  2||
			(*pVecTile)[iIndex]->byOption  ==  3||
			(*pVecTile)[iIndex]->byOption  ==  4 ) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##아래쪽 타일
		iIndex = pFirstNode->iIndex + TILEX * 2;

		if (pFirstNode->iIndex < (TILEX * TILEY) - (TILEX * 2) &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##왼쪽 타일
		iIndex = pFirstNode->iIndex - 1;

		if (pFirstNode->iIndex % TILEX != 0 &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##오른쪽 타일
		iIndex = pFirstNode->iIndex + 1;

		if (pFirstNode->iIndex % TILEX != TILEX - 1 &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##오른쪽 위 타일
		iIndex = pFirstNode->iIndex - (TILEX - (pFirstNode->iIndex / TILEX) % 2);

		//예외처리가 추가적으로 더 필요하다.
		if (pFirstNode->iIndex >= TILEX - 1 &&
			pFirstNode->iIndex % (TILEX) != (TILEX - 1) &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##오른쪽 아래 타일
		iIndex = pFirstNode->iIndex + (TILEX + (pFirstNode->iIndex / TILEX) % 2);

		//예외처리가 추가적으로 더 필요하다.
		if (pFirstNode->iIndex < (TILEX * TILEY) - TILEX  &&
			pFirstNode->iIndex % (TILEX) != (TILEX - 1) &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##왼쪽 아래 타일
		iIndex = pFirstNode->iIndex + (TILEX + (pFirstNode->iIndex / TILEX) % 2) - 1;

		//예외처리가 추가적으로 더 필요하다.
		if (pFirstNode->iIndex < (TILEX * TILEY) - TILEX  &&
			pFirstNode->iIndex % (TILEX) != 0 &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}


		//##왼쪽 위 타일
		iIndex = pFirstNode->iIndex - (TILEX - (pFirstNode->iIndex / TILEX) % 2) - 1;

		//예외처리가 추가적으로 더 필요하다.
		if (pFirstNode->iIndex >= TILEX - 1 &&
			pFirstNode->iIndex % (TILEX) != 0 &&
			((*pVecTile)[iIndex]->byOption == 0 ||
			(*pVecTile)[iIndex]->byOption == 2 ||
				(*pVecTile)[iIndex]->byOption == 3 ||
				(*pVecTile)[iIndex]->byOption == 4) &&
			ListCheck(iIndex))
		{
			pMakeNode = MakeNode(iIndex, pFirstNode, pVecTile);
			m_OpenList.push_back(pMakeNode);
		}

		//OpenList에 담긴 비용을 정렬한다.
		m_OpenList.sort(Compare);

		//가장 적은 비용의 노드(타일을)
		list<NODE*>::iterator iter = m_OpenList.begin();
		pFirstNode = *iter;

		m_CloseList.push_back(*iter);
		m_OpenList.erase(iter);

		if (pFirstNode->iIndex == m_iEndIndex)
		{
			//BestList를 얻어내자.
			while (true)
			{
				m_BestList.push_back(pFirstNode->iIndex);

				//도착지점에서부터 시작지점까지 Node...
				pFirstNode = pFirstNode->pParent;

				if (pFirstNode->iIndex == m_iStartIndex)
					break;
			}

			//원소를 반전시킨다.
			m_BestList.reverse();
			break;
		}
	}

}

NODE * CAStar::MakeNode(int iIndex, NODE * pParent, const vector<TILE*>* pTile)
{
	NODE* pNode = new NODE;

	ZeroMemory(pNode, sizeof(NODE));

	pNode->iIndex = iIndex;
	pNode->pParent = pParent;

	D3DXVECTOR3 fDist = (*pTile)[iIndex]->vPos - (*pTile)[pParent->iIndex]->vPos;
	
	float fPlayerCost = D3DXVec3Length(&fDist);

	fDist = (*pTile)[iIndex]->vPos - (*pTile)[m_iEndIndex]->vPos;

	float fEndCost = D3DXVec3Length(&fDist);

	pNode->fCost = fPlayerCost + fEndCost;

	return pNode;
}

bool CAStar::ListCheck(const int & iIndex)
{
	for (list<NODE*>::iterator iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if (((*iter))->iIndex == iIndex)
			return false;
	}

	for (list<NODE*>::iterator iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if (((*iter))->iIndex == iIndex)
			return false;
	}

	return true;
}

void CAStar::Release(void)
{
	for_each(m_OpenList.begin(), m_OpenList.end(), DeleteObj());
	m_OpenList.clear();

	for_each(m_CloseList.begin(), m_CloseList.end(), DeleteObj());
	m_CloseList.clear();

	m_BestList.clear();
}

bool CAStar::Picking(const D3DXVECTOR3 & vPos, const TILE * pTile)
{
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(pTile->vPos.x,
		pTile->vPos.y - TILECY / 2.f,
		0.f),

		D3DXVECTOR3(pTile->vPos.x + TILECX / 2.f,
		pTile->vPos.y,
		0.f),

		D3DXVECTOR3(pTile->vPos.x,
		pTile->vPos.y + TILECY / 2.f,
		0.f),

		D3DXVECTOR3(pTile->vPos.x - TILECX / 2.f,
		pTile->vPos.y,
		0.f)
	};

	D3DXVECTOR3 vDirection[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3 vNormal[4] =
	{
		D3DXVECTOR3(vDirection[0].y,
		-vDirection[0].x,
		0.f),

		D3DXVECTOR3(vDirection[1].y,
		-vDirection[1].x,
		0.f),

		D3DXVECTOR3(vDirection[2].y,
		-vDirection[2].x,
		0.f),

		D3DXVECTOR3(vDirection[3].y,
		-vDirection[3].x,
		0.f)
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3 vTemp = vPos - vPoint[i];

		D3DXVec3Normalize(&vTemp, &vTemp);

		float fDotResult = D3DXVec3Dot(&vTemp, &vNormal[i]);

		if (fDotResult > 0.f)
			return false;
	}

	return true;
}

int CAStar::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	const vector<TILE*>* pVecTile
		= CObjMgr::GetInstance()->FindGameObject<Tile>()->GetTile();

	if (pVecTile == NULL)
		return -1;

	for (size_t i = 0; i < pVecTile->size(); ++i)
	{
		if (Picking(vPos, (*pVecTile)[i]))
		{
			return i;
		}
	}

	return -1;
}

bool CAStar::Compare(const NODE * pNode1, const NODE * pNode2)
{
	return pNode1->fCost < pNode2->fCost;
}
