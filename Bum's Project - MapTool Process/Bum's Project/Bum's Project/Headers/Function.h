#pragma once

//template<class T>
template<typename T>
static void safe_delete(T& rData)		//댕글리 포인터를 방지하기 위해서 
{
	if(rData)
	{
		delete rData;
		rData = NULL;
	}
}
template<typename T>
static void safe_release(T& rData)	
{
	if (NULL != rData)
	{
		rData->Release();
		rData = NULL;
	}
}

inline RECT RectMake(float x, float y, float width, float height)
{
	RECT rc = {
		static_cast<long>(x - width / 2),
		static_cast<long>(y - height / 2),
		static_cast<long>(x + width / 2),
		static_cast<long>(y + height / 2),
	};

	return rc;
}

inline float Distance(float x1, float y1, float x2, float y2)
{
	float fX = x2 - x1;
	float fY = y2 - y1;
	float fDist = sqrt((fX * fX) + (fY * fY));

	return fDist;
}