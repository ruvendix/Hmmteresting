// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArrayd���� Sparse�� std::unordered_map�� �����Դϴ�.
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

		m_dense.resize(size); // ������ �迭��!
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

	// �׽�Ʈ�� �Լ�
	constexpr size_t SparseSize() const
	{
		return (m_sparse.size());
	}

	bool PushBack(const ElemType& elem)
	{
		if (DenseSize() >= Capacity())
		{
			printf("Dense �뷮 �ʰ�!\n");
			return false;
		}

		if (FindElemLocation(elem) != nullptr)
		{
			printf("%d�� �̹� �ִµ�?\n", elem);
			return false;
		}

		// �̰� ���� ������!
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

		// Sparse�� Elem ��ġ�� �����ɴϴ�
		const ElemTypePtr pTargetElem = FindElemLocation(elem);
		if (pTargetElem == nullptr)
		{
			CHECK_NULLPTR_RETURN_NOBREAK(pTargetElem, false);
		}

		// Dense�� ������ Elem�� �����ɴϴ�.
		const ElemType& lastElem = RemapArrayUtil::LastElem(*this, ElemType());

		// Sparse�� Elem ��ġ�� Dense�� ���� �����ɴϴ�.
		ElemType& targetElem = *pTargetElem;

		// targetElem�� LastElem�� ���� ����� ������ �˴ϴ�.
		if (targetElem != lastElem)
		{
			// swap���� ���� ���� �����ϴ� �� �� �����ϴ�.
			targetElem = lastElem;

			// LastElem�� ��ü�Ǿ����Ƿ� Sparse������ LastElem�� ��ġ�� �������ݴϴ�.
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

			func(*pCurrentLocation); // System�� ���� ��!
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
	std::unordered_map<ElemType, ElemTypePtr> m_sparse; // dynamic(��� �þ�� �ϹǷ�...)
	ElemTypePtr m_pNextDenseLocation = nullptr;
};

#endif