// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArrayd에서 Sparse가 std::vector인 버전입니다.
// =====================================================================================

#ifndef REMAP_ARRAY_SPARSE_VECTOR__H__
#define REMAP_ARRAY_SPARSE_VECTOR__H__

#include "PCH.h"
#include "RemapArrayUtil.hpp"

template <typename TElem, size_t size>
class RemapArray_SparseVector
{
	friend class RemapArrayUtil;

public:
	using ElemType = TElem;
	using ElemTypePtr = TElem*;
	using ThisType = RemapArray_SparseVector<ElemType, size>;

	RemapArray_SparseVector()
	{
		static_assert(std::is_integral_v<ElemType>, "ElemType isn't integral!");

		m_dense.resize(size); // 고정된 배열임!
		Reserve(16); // Entity가 처음에는 많지 않으므로...

		m_pNextDenseLocation = Begin();
	}

	RemapArray_SparseVector(const RemapArray_SparseVector&) = delete;
	RemapArray_SparseVector& operator=(const RemapArray_SparseVector&) = delete;

	RemapArray_SparseVector(RemapArray_SparseVector&&) = delete;
	RemapArray_SparseVector& operator=(RemapArray_SparseVector&&) = delete;

	void Reserve(size_t capacity)
	{
		m_sparse.reserve(capacity);
	}

	void Resize(size_t size)
	{
		m_sparse.resize(size);
	}
		
	void Clear()
	{
		m_sparse.clear();
		m_pNextDenseLocation = Begin();
	}

	bool HasElem(ElemType elem) const
	{
		//VRM_CORE_ASSERT_OP(x, < , TCapacity);
		CHECK_RANGE_RETURN_NOBREAK(elem, 0, static_cast<ElemType>(m_sparse.size()), false);
		return (m_sparse[elem] != nullptr);
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

		if (HasElem(elem))
		{
			printf("%d는 이미 있는데?\n", elem);
			return false;
		}

		if (m_sparse.empty() == true)
		{
			m_sparse.resize(16);
		}
		else if (elem >= static_cast<ElemType>(m_sparse.size()))
		{
			m_sparse.resize(elem * 2); // 개수의 2배만 증가!
		}

		// 이게 실제 구현부!
		*m_pNextDenseLocation = elem;
		m_sparse[elem] = m_pNextDenseLocation; // elem에 큰 값이 온다면 메모리 확 늘어날 수 있음...
		++m_pNextDenseLocation;

		return true;
	}

	bool Erase(const ElemType& elem)
	{
		if (Empty() == true)
		{
			return false;
		}

		// Sparse의 Elem 위치를 가져옵니다.
		CHECK_RANGE(elem, 0, static_cast<ElemType>(m_sparse.size()));
		ElemTypePtr pTargetElem = m_sparse[elem];
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

		for (ElemTypePtr i = Begin(); i != m_pNextDenseLocation; ++i)
		{
			if (HasElem(*i) == false)
			{
				continue;
			}

			func(*i); // System을 넣을 것!
		}
	}

	ElemTypePtr Begin() const
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
	ElemTypePtr m_pNextDenseLocation = nullptr;
	std::vector<ElemType> m_dense; // fixed
	std::vector<ElemTypePtr> m_sparse; // dynamic(계속 늘어나야 하므로...)
};

#endif