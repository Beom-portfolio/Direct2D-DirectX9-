#pragma once


// CPopup ��ȭ �����Դϴ�.

class CMySheet;
class CPopup : public CDialog
{
	DECLARE_DYNAMIC(CPopup)

private:
	//[17.07.21_02]	: �˾�Ŭ�������� ��Ʈ�� ��������.
	CMySheet*		m_pMySheet;

public:
	CPopup(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPopup();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
