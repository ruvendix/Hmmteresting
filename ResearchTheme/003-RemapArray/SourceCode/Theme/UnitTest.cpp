// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// RemapArray를 테스트합니다.
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
		printf("삽입 경과 시간: %f초 (%d개)\n", sec.count(), elemCnt);

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < elemCnt; ++i)
		{
			int value = std::rand() % elemCnt; // 0 ~ elemCnt
			arrRemap.Erase(value);
		}
		end = std::chrono::steady_clock::now();
		sec = end - start;

		printf("삭제 경과 시간: %f초 (%d개)\n\n", sec.count(), elemCnt);
		printf("Dense 크기: %d\tSparse 크기: %d\n", arrRemap.DenseSize(), arrRemap.SparseSize());

		arrRemap.Clear();
		//}
	}

	void TestRemapArray_SparseVector()
	{
		printf("===============================================================================\n");
		printf("<RemapArray_SparseVector 테스트!>\n");
		RemapArray_SparseVector<int, elemCnt> arrRemap;
		TestRemapArray(arrRemap);
		printf("===============================================================================\n");
	}

	void TestRemapArray_SparseMap()
	{
		printf("===============================================================================\n");
		printf("<RemapArray_SparseMap 테스트!>\n");
		RemapArray_SparseMap<int, elemCnt> arrRemap;
		TestRemapArray(arrRemap);
		printf("===============================================================================\n");
	}
}