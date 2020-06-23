// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArray에서 사용하는 유틸입니다.
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