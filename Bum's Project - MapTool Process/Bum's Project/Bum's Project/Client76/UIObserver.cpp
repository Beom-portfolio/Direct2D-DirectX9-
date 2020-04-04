#include "stdafx.h"
#include "UIObserver.h"
#include "DataSubject.h"


const UNIT_DATA * CUIObserver::GetUnitData(void)
{
	return &m_tData;
}

const D3DXMATRIX * CUIObserver::GetMatrix(void)
{
	return &m_matMatrix;
}

void CUIObserver::Update(int iMessage, void * pData)
{
	list<void*>* pDataList = CDataSubject::GetInstance()->GetDataList(iMessage);

	if (pDataList == NULL)
		return;

	list<void*>::iterator iter;
	iter = find(pDataList->begin(), pDataList->end(), pData);

	switch (iMessage)
	{
	case MESSAGE_PLAYER_DATA:
		m_tData = *((UNIT_DATA*)(*iter));
		break;

	case MESSAGE_PLAYER_MATRIX:
		m_matMatrix = *((D3DXMATRIX*)(*iter));
		break;
	}
}

CUIObserver::CUIObserver()
{
}


CUIObserver::~CUIObserver()
{

}
