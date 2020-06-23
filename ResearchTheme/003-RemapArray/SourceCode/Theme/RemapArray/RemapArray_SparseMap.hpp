// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArrayd에서 Sparse가 std::unordered_map인 버전입니다.
// =====================================================================================

#ifndef REMAP_ARRAY_SPARSE_MAP__H__
#define REMAP_ARRAY_SPARSE_MAP__H__

#include "PCH.h"
#include "RemapArrayUtil.hpp"

template <typename TElem, size_t size>
class RemapArray_SparseMap
{
	friend class RemapArrayUtil;

public:
	using ElemType = TElem;
	using ElemTypePtr = TElem*;
	using ThisType = RemapArray_SparseMap<ElemType, size>;

	RemapArray_SparseMap()
	{
		static_assert(std::is_integral_v<ElemType>, "ElemType isn't integral!");

		m_dense.resize(size); // 고정된 배열임!
		m_pNextDenseLocation = Begin();
	}

	RemapArray_SparseMap(const RemapArray_SparseMap&) = delete;
	RemapArray_SparseMap& operator=(const RemapArray_SparseMap&) = delete;

	RemapArray_SparseMap(RemapArray_SparseMap&&) = delete;
	RemapArray_SparseMap& operator=(RemapArray_SparseMap&&) = delete;
		
	void Clear()
	{
		m_sparse.clear();
		m_pNextDenseLocation = Begin();
	}

	ElemTypePtr FindElemLocation(ElemType elem) const
	{
		const auto& iter = m_sparse.find(elem);
		if (iter == m_sparse.cend())
		{
			return nullptr;
		}

		return iter->second;
	}

	constexpr size_t Capacity() const
	{
		return size;
	}

	constexpr size_t DenseSize() const
	{
		return (m_pNextDenseLocation - Begin());
	}

	// 테스트용 함수
	constexpr size_t SparseSize() const
	{
		return (m_sparse.size());
	}

	bool PushBack(const ElemType& elem)
	{
		if (DenseSize() >= Capacity())
		{
			printf("Dense 용량 초과!\n");
			return false;
		}

		if (FindElemLocation(elem) != nullptr)
		{
			printf("%d는 이미 있는데?\n", elem);
			return false;
		}

		// 이게 실제 구현부!
		*m_pNextDenseLocation = elem;
		m_sparse.insert(std::make_pair(elem, m_pNextDenseLocation));
		++m_pNextDenseLocation;

		return true;
	}

	bool Erase(const ElemType& elem)
	{
		if (Empty() == true)
		{
			return false;
		}

		// Sparse의 Elem 위치를 가져옵니다
		const ElemTypePtr pTargetElem = FindElemLocation(elem);
		if (pTargetElem == nullptr)
		{
			CHECK_NULLPTR_RETURN_NOBREAK(pTargetElem, false);
		}

		// Dense의 마지막 Elem을 가져옵니다.
		const ElemType& lastElem = RemapArrayUtil::LastElem(*this, ElemType());

		// Sparse의 Elem 위치로 Dense의 값을 가져옵니다.
		ElemType& targetElem = *pTargetElem;

		// targetElem이 LastElem일 때는 사이즈만 깎으면 됩니다.
		if (targetElem != lastElem)
		{
			// swap보다 직접 값을 대입하는 게 더 빠릅니다.
			targetElem = lastElem;

			// LastElem과 교체되었으므로 Sparse에서도 LastElem의 위치를 조정해줍니다.
			//CHECK_BOUNDARAY(0, lastElem, m_vecSparse->size());
			m_sparse[lastElem] = pTargetElem;
		}

		RemapArrayUtil::Nullify(*this, elem);
		RemapArrayUtil::DecreaseSize(*this);

		return true;
	}

	bool Empty() const
	{
		return (m_pNextDenseLocation == Begin());
	}

	void PopBack()
	{
		if (Empty())
		{
			return;
		}

		RemapArrayUtil::Nullify(*this, Back());
		RemapArrayUtil::DecreaseSize(*this);
	}

	const ElemType& Back() const
	{
		// VRM_CORE_ASSERT_OP(size(), > , 0);
		//VRM_CORE_ASSERT(has(*(last_element_ptr())));
		return RemapArrayUtil::LastElem(*this, ElemType());
	}

	template <typename TFunc>
	void ForEach(TFunc&& func) const
	{
		if (Empty() == true)
		{
			return;
		}

		for (ElemTypePtr pCurrentLocation = Begin(); pCurrentLocation != m_pNextDenseLocation; ++pCurrentLocation)
		{
			if (FindElemLocation(*pCurrentLocation) == nullptr)
			{
				continue;
			}

			func(*pCurrentLocation); // System을 넣을 것!
		}
	}

	const ElemTypePtr Begin() const
	{
		return const_cast<ElemTypePtr>(m_dense.data());
	}

	const ElemTypePtr End() const
	{
		return m_pNextDenseLocation;
	}

	const ElemType& At(int idx) const
	{
		CHECK_RANGE(idx, 0, static_cast<int>(DenseSize()));
		return m_dense[idx];
	}

private:
	std::vector<ElemType> m_dense; // fixed
	std::unordered_map<ElemType, ElemTypePtr> m_sparse; // dynamic(계속 늘어나야 하므로...)
	ElemTypePtr m_pNextDenseLocation = nullptr;
};

#endif