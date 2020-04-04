#pragma once

#define SAFE_DELETE(p) ( if(p){ delete p; p = NULL; } )
#define SAFE_DELETE_ARRAY(p) if(p){ delete[] p; p = NULL; }

#define CENTER_POS(x) (x / 2.f)

#define DECLARE_SINGLETON(ClassName)	\
public:									\
	static ClassName* GetInstance()		\
	{									\
	if(NULL == m_pInstance)			\
	m_pInstance = new ClassName;\
	return m_pInstance;				\
	}									\
	void DestroyInstance()				\
	{									\
	if(m_pInstance)					\
		{								\
		delete m_pInstance;			\
		m_pInstance = NULL;			\
		}								\
	}									\
private:								\
	static ClassName* m_pInstance;		\

#define IMPLEMENT_SINGLETON(ClassName)	\
	ClassName* ClassName::m_pInstance = NULL;\

#define ERROR_MSG(Text)		\
	MessageBox(g_hWnd, Text, L"Error!", MB_OK)

#define GET_TIME CTimeMgr::GetInstance()->GetTime()

#define D_CAST(CLASS, VAL) dynamic_cast<CLASS>(VAL)

#define S_CAST(CLASS, VAL) static_cast<CLASS>(VAL)