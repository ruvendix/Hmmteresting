// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "Manager\PerformanceProfileManager.h"

#include "RTTI_Test.h"

//////////////////////////////////////////////////////////////////////////
// ���α׷��� ���۵Ǵ� ���̿���.
Int32 main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const Uint32 inputCnt = 400000000; // 4��

	Test_Static_Cast<Child*>(trace_new Child, inputCnt);
	Test_Dyamic_Cast<Child*>(trace_new Child, inputCnt);
	Test_Kind_Cast<Child*>(trace_new Child, inputCnt);
	Test_KCL_Dynamic_Cast<ChildKCL*>(trace_new ChildKCL, inputCnt);

	PerformanceProfileMgr::I()->Report();
	return 0;
}