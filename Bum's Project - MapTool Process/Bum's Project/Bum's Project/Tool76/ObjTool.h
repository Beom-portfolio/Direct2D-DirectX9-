#pragma once
#include "afxwin.h"


// CObjTool ��ȭ �����Դϴ�.
#include "Include.h"

class CObjTool : public CDialog
{
	DECLARE_DYNAMIC(CObjTool)
private:
	map<CString, CImage*>		m_ObjPngImage;
	OBJINFO						m_ObjInfo;
public:
	int		m_iDrawID;

public:
	void HorizontalScroll(void);

public:
	CObjTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListImagePath();
	CListBox m_listBoxImagePath;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
