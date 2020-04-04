#pragma once



// CMyForm 폼 뷰입니다.

//##[17.07.14_03-01 : 실제 메모리 할당하자.
#include "Include.h"
#include "UnitTool.h"
#include "MapTool.h"
#include "PathFind.h"
#include "ObjTool.h"
#include "MonsterTool.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

private:
	//##[17.07.14_01]
	CFont		m_Font;

private:
	//##[17.07.14_03] : 다이얼로그를 생성하기 위한 변수를 추가.
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;
	CPathFind	m_PathFind;
	CObjTool    m_ObjTool;
	CMonsterTool m_MonTool;
private:
	eStageType m_StageType;
	XYCOUNT	   m_XYCount;
	MINISIZE   m_MiniSize;

public:
	CMapTool* GetMapTool(void)
	{
		return &m_MapTool;
	}

	void SetMousePos(float x, float y)
	{
		//UpdateData(TRUE);

		m_strXPos.Format(_T("%f"), x);
		m_strYPos.Format(_T("%f"), y);

		UpdateData(FALSE);

		Invalidate(FALSE);
	}

public:
	//타일 변경시 XY카운트와 스크롤값 타일 초기화를 해줌
	void AutoInitialize(void);

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyForm();

public:
	enum { IDD = IDD_MYFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonTest();
	CString m_strXCount;		//##[17.07.14_05] : 리소스뷰에서 변수를 추가하면 자동으로 생성된다.
	CString m_strYCount;
	afx_msg void OnBnClickedButtonMapTool();
	afx_msg void OnBnClickedButtonPathFind();
	afx_msg void OnBnClickedBackChange();
	afx_msg void OnBnClickedTileChange();
	afx_msg void OnBnClickedAutoChange();
	afx_msg void OnBnClickedMiniPlus();
	afx_msg void OnBnClickedMiniMinus();
	afx_msg void OnBnClickedObjtool();
	CString m_strXPos;
	CString m_strYPos;
	afx_msg void OnBnClickedShowIndex();
	afx_msg void OnBnClickedMonsterTool();
};


