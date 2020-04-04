#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

HRESULT CTimer::Initialize(void)
{
	QueryPerformanceCounter(&m_FrameTime);		//현재 Cpu의 시간을 받아온다.
	QueryPerformanceCounter(&m_FixTime);		//지금은 초기화를 한다고 생각하자!
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);

	return NOERROR;
}

void CTimer::Compute_Timer(void)
{
	QueryPerformanceCounter(&m_FrameTime);

	if ((m_FrameTime.QuadPart - m_LastTime.QuadPart) > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);

		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTimeDelta = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}

CTimer * CTimer::Create(void)
{
	CTimer*		pInstance = new CTimer();

	if (FAILED(pInstance->Initialize()))
	{
		MessageBox(0, L"CTimer Created Failed", L"System Error", MB_OK);
		safe_release(pInstance);
	}

	return pInstance;
}

void CTimer::Release(void)
{
	delete this;
}


