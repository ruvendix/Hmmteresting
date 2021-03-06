// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "UnitTest.h"
#include "RemapArray/RemapArray_SparseVector.hpp"
#include "RemapArray/RemapArray_SparseMap.hpp"

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	unit_test::TestRemapArray_SparseVector();
	unit_test::TestRemapArray_SparseMap();
	return 0;
}