#pragma once
#include "texture.h"

class CSingleTexture :
	public CTexture
{
private:
	TEX_INFO*		m_pTextInfo;		//싱글이미지를 보관하기 위한 멤버변수.

public:
	virtual HRESULT InsertTexture(const TCHAR* pPath,				
								  const TCHAR* pStateKey = L"",
							 	  const int& iCount = 0);

	virtual const TEX_INFO* GetTexture(const TCHAR* pKey = L""
									 , const int& iCount = 0);

	virtual void Release(void);

public:
	CSingleTexture(void);
	virtual ~CSingleTexture(void);
};
