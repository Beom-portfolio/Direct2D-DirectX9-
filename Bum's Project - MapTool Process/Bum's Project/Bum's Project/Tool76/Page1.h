#pragma once


// CPage1 ��ȭ �����Դϴ�.

class CPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
