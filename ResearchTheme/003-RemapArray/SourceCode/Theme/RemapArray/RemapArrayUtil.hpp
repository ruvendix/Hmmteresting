// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArray���� ����ϴ� ��ƿ�Դϴ�.
// =====================================================================================

#ifndef REMAP_ARRAY_UTIL__H__
#define REMAP_ARRAY_UTIL__H__

#include "PCH.h"

class RemapArrayUtil
{
public:
	RemapArrayUtil(const RemapArrayUtil&) = delete;
	RemapArrayUtil& operator=(const RemapArrayUtil&) = delete;

	RemapArrayUtil(RemapArrayUtil&&) = delete;
	RemapArrayUtil& operator=(RemapArrayUtil&&) = delete;

	template <typename TRemapArray, typename TElem>
	static void Nullify(TRemapArray& remapArray, TElem elem)
	{
		remapArray.m_sparse[elem] = nullptr;
	}

	template <typename TRemapArray>
	static void DecreaseSize(TRemapArray& remapArray)
	{
		--remapArray.m_pNextDenseLocation;
	}

	template <typename TRemapArray, typename TElem>
	static const TElem& LastElem(TRemapArray& remapArray, TElem)
	{
		return *(remapArray.m_pNextDenseLocation - 1);
	}

private:
	RemapArrayUtil() = default;
	~RemapArrayUtil() = default;
};

#endif