#pragma once

#include "Include.h"

// 클래스 헤더를 정의하는 방식(구조)

// 0. 상수(enum, const), macro
// 1. 생성자들
// 2. 소멸자
// - Getter
// - Setter
// 3. public 변수
// 4. public 함수
// 5. protected 변수
// 6. protected 함수
// 7. private 변수
// 8. private 함수
// 9. 이 클래스를 객체화 하기 위한 함수
// 10. 객체를 메모리 해제하기 위한 함수
// 

class CTimer
{
private:				
	//니 멋대로 만들고 지우지 못하게 하기위함
	//private으로 함부로 못열게 해준다.						
	//클래스 객체화.(클래스 정의에 따라서 메모리에 할당하겠다.)
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
	//생성과 관련된 함수.
	//Create함수를 사용하여 생성하게 한다.
	//Static을 쓰는 이유 : 객체없이 호출가능
public:
	void Release(void);
};

