#pragma once
#include "afxwin.h"

// CMonsterTool ��ȭ �����Դϴ�.
#include "Include.h"

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)
private:
	map<CString, CImage*>		m_ObjPngImage;
	OBJINFO						m_ObjInfo;
public:
	int		m_iDrawID;

public:
	void HorizontalScroll(void);
public:
	CMonsterTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonsterTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListImagePath();
	CListBox m_listBoxImagePath;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;
	afx_msg void OnStnClickedPictureMonster();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
