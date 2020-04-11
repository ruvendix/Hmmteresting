// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// RTTI를 테스트하기 위한 파일입니다.
// =====================================================================================

#ifndef RTTI_TEST__H__
#define RTTI_TEST__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"
#include "Manager\PerformanceProfileManager.h"

#include "FastRTTI\FastRTTI.h"
#include "KCL\KCL.h"

class Parent
{
	DECLARE_ROOT_RTTI(Parent);

public:
	Parent() = default;
	virtual ~Parent() = default;

	void ParentFunc()
	{
		printf("부모 함수!\n");
	}
};

class Child : public Parent
{
	DECLARE_RTTI(Child, Parent);

public:
	using Parent::Parent;
	virtual ~Child() = default;

	void ChildFunc()
	{
		printf("자식 함수!\n");
	}

	void ChildFunc2()
	{
		for (Int32 i = 0; i < 11; ++i)
		{
			m_child *= 3;
		}
	}

private:
	Uint32 m_child = 1;
};

class Child2 : public Child
{
	DECLARE_RTTI(Child2, Child);

public:
	using Child::Child;
	virtual ~Child2() = default;

	void Child2Func()
	{
		printf("자식 함수2!\n");
	}
};

class Child3 : public Child2
{
	DECLARE_RTTI(Child3, Child2);

public:
	using Child2::Child2;
	virtual ~Child3() = default;

	void Child3Func()
	{
		printf("자식 함수3!\n");
	}
};

class Child4 : public Child3
{
	DECLARE_RTTI(Child4, Child3);

public:
	using Child3::Child3;
	virtual ~Child4() = default;

	void Child4Func()
	{
		printf("자식 함수4!\n");
	}
};

class Child5 : public Child4
{
	DECLARE_RTTI(Child5, Child4);

public:
	using Child4::Child4;
	virtual ~Child5() = default;

	void Child5Func()
	{
		printf("자식 함수5!\n");
	}
};

class ParentKCL
{
	KCL_RTTI_IMPL();

public:
	ParentKCL() = default;
	virtual ~ParentKCL() = default;

	void ParentFunc()
	{
		printf("부모 함수!\n");
	}
};
KCL_RTTI_REGISTER(ParentKCL);

class ChildKCL : public ParentKCL
{
	KCL_RTTI_IMPL();

public:
	using ParentKCL::ParentKCL;
	virtual ~ChildKCL() = default;

	void ChildFunc()
	{
		printf("자식 함수!\n");
	}

	void ChildFunc2()
	{
		for (Int32 i = 0; i < 11; ++i)
		{
			m_child *= 3;
		}
	}

private:
	Uint32 m_child = 1;
};
KCL_RTTI_REGISTER(ChildKCL, ParentKCL)

class ChildKCL2 : public ChildKCL
{
	KCL_RTTI_IMPL();

public:
	using ChildKCL::ChildKCL;
	virtual ~ChildKCL2() = default;

	void Child2Func()
	{
		printf("자식 함수2!\n");
	}
};
KCL_RTTI_REGISTER(ChildKCL2, ChildKCL)

class ChildKCL3 : public ChildKCL2
{
	KCL_RTTI_IMPL();

public:
	using ChildKCL2::ChildKCL2;
	virtual ~ChildKCL3() = default;

	void Child3Func()
	{
		printf("자식 함수3!\n");
	}
};
KCL_RTTI_REGISTER(ChildKCL3, ChildKCL2)

class ChildKCL4 : public ChildKCL3
{
	KCL_RTTI_IMPL();

public:
	using ChildKCL3::ChildKCL3;
	virtual ~ChildKCL4() = default;

	void Child4Func()
	{
		printf("자식 함수4!\n");
	}
};
KCL_RTTI_REGISTER(ChildKCL4, ChildKCL3)

class ChildKCL5 : public ChildKCL4
{
	KCL_RTTI_IMPL();

public:
	using ChildKCL4::ChildKCL4;
	virtual ~ChildKCL5() = default;

	void Child5Func()
	{
		printf("자식 함수5!\n");
	}
};
KCL_RTTI_REGISTER(ChildKCL5, ChildKCL4)

template <typename TParent>
bool IsKindOf(const TParent* pChild)
{
	const char* szParentClassName = TParent::GetRTTI()->getClassName();

	const FastRTTI* pRTTI = pChild->OnGetRTTI();
	while (pRTTI != nullptr)
	{
		if (pRTTI->getClassName() == szParentClassName)
		{
			return true;
		}

		pRTTI = pRTTI->getParent();
	}

	return false;
}

template <typename TDestRTTI, typename TSrcRTTI>
bool IsSameOf(const TSrcRTTI* pSrcRTTI)
{
	if (pSrcRTTI == nullptr)
	{
		return false;
	}

	if (pSrcRTTI->OnGetRTTI()->getClassName() == std::remove_pointer_t<TDestRTTI>::GetRTTI()->getClassName())
	{
		return true;
	}

	return false;
}

template <typename TChild, typename TParent>
TChild KindCast(const TParent* pChild)
{
	using TChildPrototype = std::remove_pointer_t<TChild>;

	if (IsSameOf<TChildPrototype*>(pChild))
	{
		return (TChildPrototype*)(pChild);
	}

	return nullptr;
}

template <typename TRTTI>
void Test_Static_Cast(Parent* pRTTI, Uint32 inputCnt)
{
	PERFORMANCE_PROFILE_START(inputCnt);
	for (Uint32 i = 0; i < inputCnt; ++i)
	{
		static_cast<std::remove_pointer_t<TRTTI>*>(pRTTI)->ChildFunc2();
	}
	PERFORMANCE_PROFILE_END();

	printf("Test_Static_Cast 완료!\n");
	SAFE_DELETE(pRTTI);
}

template <typename TRTTI>
void Test_Dynamic_Cast(Parent* pRTTI, Uint32 inputCnt)
{
	PERFORMANCE_PROFILE_START(inputCnt);
	for (Uint32 i = 0; i < inputCnt; ++i)
	{
		dynamic_cast<std::remove_pointer_t<TRTTI>*>(pRTTI)->ChildFunc2();
	}
	PERFORMANCE_PROFILE_END();

	printf("Test_Dyamic_Cast 완료!\n");
	SAFE_DELETE(pRTTI);
}

template <typename TRTTI>
void Test_Kind_Cast(Parent* pRTTI, Uint32 inputCnt)
{
	PERFORMANCE_PROFILE_START(inputCnt);
	for (Uint32 i = 0; i < inputCnt; ++i)
	{
		KindCast<std::remove_pointer_t<TRTTI>*>(pRTTI)->ChildFunc2();
	}
	PERFORMANCE_PROFILE_END();

	printf("Test_Kind_Cast 완료!\n");
	SAFE_DELETE(pRTTI);
}

template <typename TRTTI>
void Test_KCL_Dynamic_Cast(ParentKCL* pRTTI, Uint32 inputCnt)
{
	PERFORMANCE_PROFILE_START(inputCnt);
	for (Uint32 i = 0; i < inputCnt; ++i)
	{
		kcl_dynamic_cast<std::remove_pointer_t<TRTTI>*>(pRTTI)->ChildFunc2();
	}
	PERFORMANCE_PROFILE_END();

	printf("Test_KCL_Dynamic_Cast 완료!\n");
	SAFE_DELETE(pRTTI);
}

#endif