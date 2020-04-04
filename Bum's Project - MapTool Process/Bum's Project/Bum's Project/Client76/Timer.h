#pragma once

#include "Include.h"

// Ŭ���� ����� �����ϴ� ���(����)

// 0. ���(enum, const), macro
// 1. �����ڵ�
// 2. �Ҹ���
// - Getter
// - Setter
// 3. public ����
// 4. public �Լ�
// 5. protected ����
// 6. protected �Լ�
// 7. private ����
// 8. private �Լ�
// 9. �� Ŭ������ ��üȭ �ϱ� ���� �Լ�
// 10. ��ü�� �޸� �����ϱ� ���� �Լ�
// 

class CTimer
{
private:				
	//�� �ڴ�� ����� ������ ���ϰ� �ϱ�����
	//private���� �Ժη� ������ ���ش�.						
	//Ŭ���� ��üȭ.(Ŭ���� ���ǿ� ���� �޸𸮿� �Ҵ��ϰڴ�.)
	explicit CTimer();
	virtual ~CTimer();
public:
	float Get_TimeDelta(void) const
	{
		return m_fTimeDelta;
	}
public:
	HRESULT Initialize(void);
private:
	LARGE_INTEGER m_FrameTime;
	LARGE_INTEGER m_FixTime;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CpuTick;
private:
	float		  m_fTimeDelta;
public:
	void	Compute_Timer(void);
public:
	static CTimer* Create(void);
	//������ ���õ� �Լ�.
	//Create�Լ��� ����Ͽ� �����ϰ� �Ѵ�.
	//Static�� ���� ���� : ��ü���� ȣ�Ⱑ��
public:
	void Release(void);
};

