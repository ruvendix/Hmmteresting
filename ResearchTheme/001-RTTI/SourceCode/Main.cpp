// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "Manager\PerformanceProfileManager.h"

#include "RTTI_Test.h"

//////////////////////////////////////////////////////////////////////////
// 프로그램이 시작되는 곳이에요.
Int32 main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const Uint32 inputCnt = 400000000; // 4억

	Test_Static_Cast<Child*>(trace_new Child, inputCnt);
	Test_Dyamic_Cast<Child*>(trace_new Child, inputCnt);
	Test_Kind_Cast<Child*>(trace_new Child, inputCnt);
	Test_KCL_Dynamic_Cast<ChildKCL*>(trace_new ChildKCL, inputCnt);

	PerformanceProfileMgr::I()->Report();
	return 0;
}