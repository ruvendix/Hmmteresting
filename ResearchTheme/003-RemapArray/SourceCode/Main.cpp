// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "UnitTest.h"
#include "RemapArray/RemapArray_SparseVector.hpp"
#include "RemapArray/RemapArray_SparseMap.hpp"

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	unit_test::TestRemapArray_SparseVector();
	unit_test::TestRemapArray_SparseMap();
	return 0;
}