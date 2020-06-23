// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArrayd���� Sparse�� std::vector�� �����Դϴ�.
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

		m_dense.resize(size); // ������ �迭��!
		Reserve(16); // Entity�� ó������ ���� �����Ƿ�...

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

		if (HasElem(elem))
		{
			printf("%d�� �̹� �ִµ�?\n", elem);
			return false;
		}

		if (m_sparse.empty() == true)
		{
			m_sparse.resize(16);
		}
		else if (elem >= static_cast<ElemType>(m_sparse.size()))
		{
			m_sparse.resize(elem * 2); // ������ 2�踸 ����!
		}

		// �̰� ���� ������!
		*m_pNextDenseLocation = elem;
		m_sparse[elem] = m_pNextDenseLocation; // elem�� ū ���� �´ٸ� �޸� Ȯ �þ �� ����...
		++m_pNextDenseLocation;

		return true;
	}

	bool Erase(const ElemType& elem)
	{
		if (Empty() == true)
		{
			return false;
		}

		// Sparse�� Elem ��ġ�� �����ɴϴ�.
		CHECK_RANGE(elem, 0, static_cast<ElemType>(m_sparse.size()));
		ElemTypePtr pTargetElem = m_sparse[elem];
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

		for (ElemTypePtr i = Begin(); i != m_pNextDenseLocation; ++i)
		{
			if (HasElem(*i) == false)
			{
				continue;
			}

			func(*i); // System�� ���� ��!
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
	std::vector<ElemTypePtr> m_sparse; // dynamic(��� �þ�� �ϹǷ�...)
};

#endif