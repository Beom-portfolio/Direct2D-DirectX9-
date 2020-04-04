#pragma once



// CMySheet

#include "Page1.h"
#include "Page2.h"

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)

//[17.07.21_04]
//페이지를 멤버변수로 가지고 있자.

private:
	CPage1	m_Page1;
	CPage2	m_Page2;

public:				//[17.07.21_01]
	CMySheet(void);	//갹기본 생성자를 만들자 우리는 대입연산이 필요없다.
	CMySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMySheet();

protected:
	DECLARE_MESSAGE_MAP()
};


