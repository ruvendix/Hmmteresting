// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArray�� �׽�Ʈ�մϴ�.
// =====================================================================================

#include "PCH.h"
#include "UnitTest.h"

#include "RemapArray\RemapArray_SparseVector.hpp"
#include "RemapArray\RemapArray_SparseMap.hpp"
#include "UnitTest.h"

namespace unit_test
{
	const int elemCnt = 10000;

	template <typename TRemapArray>
	void TestRemapArray(TRemapArray& arrRemap)
	{
		std::srand((unsigned int)std::time(nullptr));

		//while (true)
		//{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		for (int i = 0; i < elemCnt; ++i)
		{
			arrRemap.PushBack(i);
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::duration<float> sec = end - start;
		printf("���� ��� �ð�: %f�� (%d��)\n", sec.count(), elemCnt);

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < elemCnt; ++i)
		{
			int value = std::rand() % elemCnt; // 0 ~ elemCnt
			arrRemap.Erase(value);
		}
		end = std::chrono::steady_clock::now();
		sec = end - start;

		printf("���� ��� �ð�: %f�� (%d��)\n\n", sec.count(), elemCnt);
		printf("Dense ũ��: %d\tSparse ũ��: %d\n", arrRemap.DenseSize(), arrRemap.SparseSize());

		arrRemap.Clear();
		//}
	}

	void TestRemapArray_SparseVector()
	{
		printf("===============================================================================\n");
		printf("<RemapArray_SparseVector �׽�Ʈ!>\n");
		RemapArray_SparseVector<int, elemCnt> arrRemap;
		TestRemapArray(arrRemap);
		printf("===============================================================================\n");
	}

	void TestRemapArray_SparseMap()
	{
		printf("===============================================================================\n");
		printf("<RemapArray_SparseMap �׽�Ʈ!>\n");
		RemapArray_SparseMap<int, elemCnt> arrRemap;
		TestRemapArray(arrRemap);
		printf("===============================================================================\n");
	}
}