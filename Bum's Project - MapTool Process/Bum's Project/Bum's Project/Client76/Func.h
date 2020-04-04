#pragma once
#include "stdafx.h"
#include "Include.h"


class CStringCmp
{
public:
	CStringCmp(const TCHAR* pKey)
		: m_pKey(pKey) {}

public:
	template <typename T>
	bool operator()(T& dst) // find_if�� ���� ������.
	{
		return !lstrcmp(dst.first, m_pKey);
	}

private:
	const TCHAR*	m_pKey;
};