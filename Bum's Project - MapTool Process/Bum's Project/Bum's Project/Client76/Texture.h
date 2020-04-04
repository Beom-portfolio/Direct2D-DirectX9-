#pragma once

#include "Include.h"

class CTexture abstract
{
public:
	virtual HRESULT InsertTexture(const TCHAR* pPath,				//이미지 경로.
								  const TCHAR* pStateKey = L"",	//스프라이트를 출력할때 상태값을 표현.
								  const int& iCount = 0)PURE;	//이미지 장수.

	virtual const TEX_INFO* GetTexture(const TCHAR* pKey = L"", const int& iCount = 0)PURE;

	virtual void Release(void)PURE;

public:
	CTexture(void);
	virtual ~CTexture(void);
};
